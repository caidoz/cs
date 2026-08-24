#include "cocos2d.h"

#ifndef _FUNC_H_
#include "Func.h"
#endif

#ifndef _CORE_H_
#include "Core.h"
#endif

#ifndef _FUNC_NET_H_
#include "Func_Net.h"
#endif

#ifndef _TEXT_H_
#include "Text.h"
#endif

#ifndef _CONFIG_NET_H_
#include "Config/NetConfig.h"
#endif

#include "network/HttpClient.h"

#include <map>
#include <string>
#include <vector>

USING_NS_CC;

//=============================================================================
// 서버 통신 계층
//
// 구역은 여섯이다.
//   1. 문자열 유틸      - 덤프 형식의 이스케이프 규칙
//   2. 덤프 만들기      - robin -> 텍스트
//   3. 덤프 읽기        - 텍스트 -> robin
//   4. 임시 로컬 서버   - NET_SERVER_URL 이 비어 있을 때 쓰는 길
//   5. 진짜 서버        - HttpClient. NET_SERVER_URL 이 있을 때 쓰는 길
//   6. 클라이언트 API   - 요청 큐와 지연
//
// 4와 5는 같은 일을 하는 두 갈래이고, 고르는 기준은 NET_SERVER_URL 한 줄이다
// (Config/NetConfig.h). 비어 있으면 예전과 한 글자도 다르지 않게 동작한다.
// Content.cpp 가 CDN 을 그렇게 다루고 있어서 같은 꼴로 맞췄다.
//=============================================================================

long long gNetUserId = 0;
long long gNetRevision = 0;

//서버 시각 - 기기 시각. 서버에 못 붙었으면 0이라 기기 시계를 그대로 쓴다.
//자세한 이유는 Func_Net.h 주석을 보라.
long gNetTimeOffset = 0;

void NetSetServerTime(long serverNow)
{
	long before = gNetTimeOffset;

	//기기 시계 원본과 견준다. 여기서 MC_knlCurrentTimeStamp() 를 쓰면 이미
	//더해둔 오프셋이 또 들어가서 값이 자기를 물고 커진다.
	gNetTimeOffset = serverNow - MC_knlRawTimeStamp();

	//많이 틀어져 있으면 남겨 둔다. 기기 시계가 이상하다는 뜻이라 나중에
	//"왜 시간이 안 맞나" 를 볼 때 실마리가 된다. 1분 미만은 흔한 오차다.
	if (gNetTimeOffset > 60 || gNetTimeOffset < -60)
		CCLOG("NetSetServerTime: 기기 시계가 서버와 %ld초 차이난다", gNetTimeOffset);
	else if (before != gNetTimeOffset)
		CCLOG("NetSetServerTime: 오프셋 %ld초", gNetTimeOffset);
}

//서버가 마지막으로 준 몸통. 저장할 때 여기에 새로 만들어 넣고 보낸다.
static std::string sNetBody;

//=============================================================================
// 1. 문자열 유틸
//
// 규칙은 전부 MariaDB LOAD DATA INFILE의 기본값이다. 직접 정한 것이 없다.
// 그래야 이 파일이 나중에 변환 없이 그대로 DB로 들어간다.
//   필드 구분 \t / 행 구분 \n / 이스케이프 \ / NULL은 \N
//=============================================================================

static void NetEscape(const char* src, std::string& out)
{
	if (src == NULL)
		return;

	for (const unsigned char* p = (const unsigned char*)src; *p; p++) {
		switch (*p) {
		case '\\': out += "\\\\"; break;
		case '\t': out += "\\t"; break;
		case '\n': out += "\\n"; break;
		case '\r': out += "\\r"; break;
		case 0x1a: out += "\\Z"; break;
		default:   out += (char)*p; break;
		}
	}
}

static std::string NetUnescape(const std::string& s)
{
	std::string out;
	size_t i;

	out.reserve(s.size());

	for (i = 0; i < s.size(); i++) {
		if (s[i] != '\\' || i + 1 >= s.size()) {
			out += s[i];
			continue;
		}

		i++;

		switch (s[i]) {
		case 't': out += '\t'; break;
		case 'n': out += '\n'; break;
		case 'r': out += '\r'; break;
		case '0': out += '\0'; break;
		case 'Z': out += (char)0x1a; break;
		//\N(NULL)은 값이 없다는 뜻이라 빈 문자열이 된다.
		case 'N': break;
		default:  out += s[i]; break;
		}
	}

	return out;
}

//CRC32. zlib을 끌어오지 않으려고 여기서 만든다. 표준 다항식(0xEDB88320).
static unsigned int NetCrc32(const char* buf, size_t len)
{
	unsigned int crc = 0xFFFFFFFFu;
	size_t i;
	int k;

	for (i = 0; i < len; i++) {
		crc ^= (unsigned char)buf[i];

		for (k = 0; k < 8; k++)
			crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
	}

	return ~crc;
}

//=============================================================================
// 2. 덤프 만들기
//=============================================================================

//표 하나를 쌓는 동안 쓰는 것. 행 수를 미리 알 수 없어서 모았다가 한 번에 붙인다.
struct NetTableOut {
	std::string name;
	std::string cols;
	std::vector<std::string> rows;
	std::string cur;	//지금 쌓고 있는 행
};

static NetTableOut sOut;

static void TableBegin(const char* name, const char* cols)
{
	sOut.name = name;
	sOut.cols = cols;
	sOut.rows.clear();
	sOut.cur.clear();
}

//한 행 안에서 값을 이어 붙인다. 첫 값이 아니면 앞에 탭을 넣는다.
static void PutSep(void)
{
	if (!sOut.cur.empty())
		sOut.cur += '\t';
}

static void PutNum(long long v)
{
	char buf[32];

	PutSep();
	sprintf(buf, "%lld", v);
	sOut.cur += buf;
}

static void PutStr(const char* s)
{
	PutSep();
	NetEscape(s, sOut.cur);
}

static void RowEnd(void)
{
	sOut.rows.push_back(sOut.cur);
	sOut.cur.clear();
}

static void TableEnd(std::string& body)
{
	char head[128];
	size_t i;

	body += "\n#table\t";
	body += sOut.name;
	body += "\n#cols\t";
	body += sOut.cols;

	sprintf(head, "\n#rows\t%d\n", (int)sOut.rows.size());
	body += head;

	for (i = 0; i < sOut.rows.size(); i++) {
		body += sOut.rows[i];
		body += '\n';
	}
}

//---- robin 전체를 덤프 문자열로 ----
static void NetBuildDump(std::string& out)
{
	int i, j;
	char head[256];

	std::string body;

	sprintf(head, "#insamdb\t1\n#schema\t1\n#user\t%lld\n#revision\t%lld\n#written\t%ld\n",
		gNetUserId, gNetRevision, (long)MC_knlCurrentTimeStamp());
	body = head;

	//---- account ----
	TableBegin("account", "user_id");
	PutNum(gNetUserId);
	RowEnd();
	TableEnd(body);

	//---- player ----
	TableBegin("player",
		"user_id\trevision\tnickname\tlv\texps\tgold\theart\tmedal\tstar\thammer\tcoin\tshield"
		"\tcastle\tstage\troom\tboss_room\tmax_inven\tmax_status_cnt\tplaytime\tevent_cnt"
		"\tcurrent_day\tlife_remaining\tcrew_miss_cnt\tequip_miss_cnt"
		"\tstart_ts\theart_ts\tfree_reward_ts\tcalendar_ts\tcalendar_month_day");
	PutNum(gNetUserId);
	PutNum(gNetRevision);
	PutStr(robin.nickname.c_str());
	PutNum(robin.lv);
	PutNum(robin.exps);
	PutNum(robin.gold);
	PutNum(robin.heart);
	PutNum(robin.medal);
	PutNum(robin.star);
	PutNum(robin.hammer);
	PutNum(robin.coin);
	PutNum(robin.shield);
	PutNum(robin.castle);
	PutNum(robin.stage);
	PutNum(robin.room);
	PutNum(robin.bossRoom);
	PutNum(robin.maxInven);
	PutNum(robin.maxStatusCnt);
	PutNum(robin.playtime);
	PutNum(robin.eventCnt);
	PutNum(robin.currentDay);
	PutNum(robin.lifeRemaining);
	PutNum(robin.crewHighGradeMissCount);
	PutNum(robin.equipHighGradeMissCount);
	PutNum(robin.startTime);
	PutNum(robin.heartTimeStamp);
	PutNum(robin.freeRewardTimeStamp);
	PutNum(robin.calendarTimeStamp);
	PutNum(robin.calendarMonthDay);
	RowEnd();
	TableEnd(body);

	//---- player_castle ----
	TableBegin("player_castle", "user_id\tcastle_idx\tmax_stage\tmax_room");
	for (i = 0; i < gTotalCastle; i++) {
		if (robin.maxStage[i] == 0 && robin.maxRoom[i] == 0)
			continue;

		PutNum(gNetUserId);
		PutNum(i);
		PutNum(robin.maxStage[i]);
		PutNum(robin.maxRoom[i]);
		RowEnd();
	}
	TableEnd(body);

	//---- player_flag ----
	//켜진 것만 넣는다. 배열을 통째로 넣으면 대부분 0인 수백 행이 된다.
	TableBegin("player_flag", "user_id\tflag_kind\tflag_idx\tvalue");

	for (i = 0; i < TOTALDEMO; i++)
		if (robin.demoSeen[i]) {
			PutNum(gNetUserId); PutNum(0); PutNum(i); PutNum(1); RowEnd();
		}

	for (i = 0; i < TOTAL_MENU; i++)
		if (robin.openedMenu[i]) {
			PutNum(gNetUserId); PutNum(1); PutNum(i); PutNum(robin.openedMenu[i]); RowEnd();
		}

	for (i = 0; i < TOTAL_STATUE; i++)
		if (robin.statue[i]) {
			PutNum(gNetUserId); PutNum(2); PutNum(i); PutNum(1); RowEnd();
		}

	for (i = 0; i < ITEM_GEM_START; i++)
		if (robin.equipGet[i]) {
			PutNum(gNetUserId); PutNum(3); PutNum(i); PutNum(1); RowEnd();
		}

	TableEnd(body);

	//---- player_consumable ----
	TableBegin("player_consumable", "user_id\twaste_idx\tcnt");
	for (i = 0; i < TOTAL_WASTE; i++) {
		if (robin.buffItem[i] == 0)
			continue;

		PutNum(gNetUserId);
		PutNum(i);
		PutNum(robin.buffItem[i]);
		RowEnd();
	}
	TableEnd(body);

	//---- inventory ----
	//인벤은 앞에서부터 채워지고 type == EMPTY(0xFF)에서 끝난다.
	//item_uid는 나중에 서버가 발급할 값이라 지금은 인벤 자리번호 + 1을 쓴다.
	TableBegin("inventory",
		"item_uid\tuser_id\titem_type\tdetail\tgrade\tlv\tcnt\tcooldown\texp\tseen");

	for (i = 0; i < robin.maxInven; i++) {
		if (robin.inven[i].type == EMPTY)
			break;

		PutNum(i + 1);
		PutNum(gNetUserId);
		PutNum(robin.inven[i].type);
		PutNum(robin.inven[i].detail);
		PutNum(robin.inven[i].grade);
		PutNum(robin.inven[i].lv);
		PutNum(robin.inven[i].count);
		PutNum(robin.inven[i].cooldown);
		PutNum(robin.inven[i].exp);
		PutNum(robin.inven[i].seen ? 1 : 0);
		RowEnd();
	}
	TableEnd(body);

	//---- inventory_option / inventory_socket ----
	TableBegin("inventory_option", "item_uid\tslot\topt_type\topt_value");
	for (i = 0; i < robin.maxInven; i++) {
		if (robin.inven[i].type == EMPTY)
			break;

		for (j = 0; j < 12; j++) {
			if (robin.inven[i].option[j][0] == EMPTYINT)
				continue;

			PutNum(i + 1);
			PutNum(j);
			PutNum(robin.inven[i].option[j][0]);
			PutNum(robin.inven[i].option[j][1]);
			RowEnd();
		}
	}
	TableEnd(body);

	TableBegin("inventory_socket", "item_uid\tslot\tgem");
	for (i = 0; i < robin.maxInven; i++) {
		if (robin.inven[i].type == EMPTY)
			break;

		for (j = 0; j < MAXSOCKET; j++) {
			if (robin.inven[i].socket[j] == EMPTYINT)
				continue;

			PutNum(i + 1);
			PutNum(j);
			PutNum(robin.inven[i].socket[j]);
			RowEnd();
		}
	}
	TableEnd(body);

	//---- hero ----
	TableBegin("hero", "user_id\thero_idx\tis_set\texps\thp\tmp\tap\tsp");
	for (i = 0; i < TOTALPLAYER; i++) {
		PutNum(gNetUserId);
		PutNum(i);
		PutNum(robin.heroesSetting[i] ? 1 : 0);
		PutNum(robin.charData[i].exps);
		PutNum(robin.charData[i].hp);
		PutNum(robin.charData[i].mp);
		PutNum(robin.charData[i].ap);
		PutNum(robin.charData[i].sp);
		RowEnd();
	}
	TableEnd(body);

	//---- hero_equip ----
	//장착품은 인벤 항목의 사본이다(EquipItem()이 복사만 하고 인벤에서 빼지 않는다).
	//그래서 인벤 행을 가리키지 않고 종류/세부/등급을 그대로 적는다.
	TableBegin("hero_equip",
		"user_id\thero_idx\tslot\titem_type\tdetail\tgrade\tlv\tcooldown");
	for (i = 0; i < TOTALPLAYER; i++) {
		for (j = 0; j < TOTALEQUIP; j++) {
			if (robin.charData[i].equip[j].type == EMPTY)
				continue;

			PutNum(gNetUserId);
			PutNum(i);
			PutNum(j);
			PutNum(robin.charData[i].equip[j].type);
			PutNum(robin.charData[i].equip[j].detail);
			PutNum(robin.charData[i].equip[j].grade);
			PutNum(robin.charData[i].equip[j].lv);
			PutNum(robin.charData[i].equip[j].cooldown);
			RowEnd();
		}
	}
	TableEnd(body);

	//---- hero_hotkey ----
	TableBegin("hero_hotkey", "user_id\thero_idx\tslot\thk_type\thk_idx");
	for (i = 0; i < TOTALPLAYER; i++) {
		for (j = 0; j < MAXHOTKEY; j++) {
			if (robin.charData[i].hotKey[j].type == 0)
				continue;

			PutNum(gNetUserId);
			PutNum(i);
			PutNum(j);
			PutNum(robin.charData[i].hotKey[j].type);
			PutNum(robin.charData[i].hotKey[j].idx);
			RowEnd();
		}
	}
	TableEnd(body);

	//---- hero_skill ----
	//skillLv는 TOTAL_SKILL(=1787)칸짜리다. 0이 아닌 것만 넣는다.
	TableBegin("hero_skill", "user_id\thero_idx\tskill_idx\tskill_lv");
	for (i = 0; i < TOTALPLAYER; i++) {
		for (j = 0; j < gTotalSkill; j++) {
			if (robin.charData[i].skillLv[j] == 0)
				continue;

			PutNum(gNetUserId);
			PutNum(i);
			PutNum(j);
			PutNum(robin.charData[i].skillLv[j]);
			RowEnd();
		}
	}
	TableEnd(body);

	//---- hero_skill_slot ----
	TableBegin("hero_skill_slot", "user_id\thero_idx\tslot\tskill_idx");
	for (i = 0; i < TOTALPLAYER; i++) {
		for (j = 0; j < MAXCHARSKILL; j++) {
			if (robin.charData[i].getSkillList[j] == 0)
				continue;

			PutNum(gNetUserId);
			PutNum(i);
			PutNum(j);
			PutNum(robin.charData[i].getSkillList[j]);
			RowEnd();
		}
	}
	TableEnd(body);

	//---- crew_slot ----
	TableBegin("crew_slot", "user_id\tslot\tcrew_type");
	for (i = 0; i < MAXCREW; i++) {
		if (robin.slotCrew[i] < 0)
			continue;

		PutNum(gNetUserId);
		PutNum(i);
		PutNum(robin.slotCrew[i]);
		RowEnd();
	}
	TableEnd(body);

	//---- quest_progress ----
	TableBegin("quest_progress",
		"user_id\tkind\tquest\tsub_quest\tdetail_quest\tcnt\tstarted_ts\tremain_item\tthis_time_item");

	PutNum(gNetUserId); PutNum(0);
	PutNum(robin.quest); PutNum(robin.subQuest); PutNum(0); PutNum(robin.questCnt);
	PutNum(robin.questTimeStamp);
	PutNum(robin.remainQuestItem); PutNum(robin.thisTimeQuestItem);
	RowEnd();

	PutNum(gNetUserId); PutNum(1);
	PutNum(robin.pvpQuest); PutNum(robin.pvpSubQuest); PutNum(robin.pvpDetailQuest); PutNum(robin.pvpQuestCnt);
	PutNum(robin.pvpQuestTimeStamp);
	PutNum(robin.remainPvpQuestItem); PutNum(robin.thisTimePvpQuestItem);
	RowEnd();

	TableEnd(body);

	//---- game_event ----
	//연출 필드(x, y, dx, speed, zoom, frame, touchFunc ...)는 넣지 않는다.
	//화면에서 바가 튀어나오는 애니메이션 상태라 저장할 이유가 없다.
	TableBegin("game_event",
		"user_id\tslot\tev_type\tsub_type\ticon\tstarted_ts\tlimit_sec\tstatus\tbar_status");
	for (i = 0; i < MAXGAMEEVENT; i++) {
		if (robin.gameEvent[i].type == 0)
			continue;

		PutNum(gNetUserId);
		PutNum(i);
		PutNum(robin.gameEvent[i].type);
		PutNum(robin.gameEvent[i].subType);
		PutNum(robin.gameEvent[i].icon);
		PutNum(robin.gameEvent[i].timeStamp);
		PutNum(robin.gameEvent[i].limitTime);
		PutNum(robin.gameEvent[i].status);
		PutNum(robin.gameEvent[i].barStatus);
		RowEnd();
	}
	TableEnd(body);

	//---- calendar_day ----
	TableBegin("calendar_day", "user_id\tday_idx\tstatus");
	for (i = 0; i < WEEK; i++) {
		PutNum(gNetUserId);
		PutNum(i);
		PutNum(robin.calendarDayStatus[i]);
		RowEnd();
	}
	TableEnd(body);

	//---- battle_session ----
	TableBegin("battle_session",
		"user_id\twave_idx\tcur_wave_idx\twave_ts\tenemy_user_idx");
	PutNum(gNetUserId);
	PutNum(robin.waveIdx);
	PutNum(robin.curWaveIdx);
	PutNum(robin.waveTimeStamp);
	PutNum(robin.enemyUserIdx);
	RowEnd();
	TableEnd(body);

	//---- battle_enemy ----
	//살아 있는 놈만 넣는다. 위치와 프레임은 넣지 않는다. 복원하는
	//CopyEnemyObj()가 어차피 x/y를 nx/ny로 되돌리고 프레임을 0으로 리셋한다.
	TableBegin("battle_enemy",
		"user_id\tslot\tmom\tenemy_type\tcmf\thp\tmax_hp\tstatus\tetc"
		"\tnx\tny\tdir_f\tlv\tstr\tdef\tattr\tskill_idx\tcur_skill\tcool_time\ttarget\tdead");

	for (i = 0; i < MAXENEMY * MAXENEMYOBJ; i++) {
		if (robin.enemyObj[i].active == false)
			continue;

		PutNum(gNetUserId);
		PutNum(i);
		PutNum(robin.enemyObj[i].mom);
		PutNum(robin.enemyObj[i].type);
		PutNum(robin.enemyObj[i].cmf);
		PutNum(robin.enemyObj[i].hp);
		PutNum(robin.enemyObj[i].maxhp);
		PutNum(robin.enemyObj[i].status);
		PutNum(robin.enemyObj[i].etc);
		PutNum(robin.enemyObj[i].nx);
		PutNum(robin.enemyObj[i].ny);
		PutNum(robin.enemyObj[i].dirF);
		PutNum(robin.enemyObj[i].lv);
		PutNum(robin.enemyObj[i].str);
		PutNum(robin.enemyObj[i].def);
		PutNum(robin.enemyObj[i].attr);
		PutNum(robin.enemyObj[i].skillIdx);
		PutNum(robin.enemyObj[i].currentSkill);
		PutNum(robin.enemyObj[i].coolTime);
		PutNum(robin.enemyObj[i].target);
		PutNum(robin.enemyObj[i].dead ? 1 : 0);
		RowEnd();
	}
	TableEnd(body);

	//---- battle_enemy_effect ----
	//걸린 것만. 이걸 빼면 재접속으로 독과 기절이 풀린다.
	TableBegin("battle_enemy_effect", "user_id\tslot\tkind\teff_idx\tremain\towner");
	for (i = 0; i < MAXENEMY * MAXENEMYOBJ; i++) {
		if (robin.enemyObj[i].active == false)
			continue;

		for (j = 0; j < TOTALBUFF; j++) {
			if (robin.enemyObj[i].buff[j] == 0)
				continue;

			PutNum(gNetUserId); PutNum(i); PutNum(0); PutNum(j);
			PutNum(robin.enemyObj[i].buff[j]);
			PutNum(robin.enemyObj[i].buffOwner[j]);
			RowEnd();
		}

		for (j = 0; j < TOTALDEBUF; j++) {
			if (robin.enemyObj[i].debuf[j] == 0)
				continue;

			PutNum(gNetUserId); PutNum(i); PutNum(1); PutNum(j);
			PutNum(robin.enemyObj[i].debuf[j]);
			PutNum(robin.enemyObj[i].debufOwner[j]);
			RowEnd();
		}
	}
	TableEnd(body);

	//---- 꼬리 ----
	sprintf(head, "#end\t%08x\n", NetCrc32(body.c_str(), body.size()));

	out = body;
	out += head;
}

//=============================================================================
// 3. 덤프 읽기
//=============================================================================

struct NetTableIn {
	std::vector<std::string> cols;
	std::vector<std::vector<std::string> > rows;
};

typedef std::map<std::string, NetTableIn> NetTableMap;

static void SplitTab(const std::string& line, std::vector<std::string>& out)
{
	size_t from = 0, at;

	out.clear();

	while ((at = line.find('\t', from)) != std::string::npos) {
		out.push_back(line.substr(from, at - from));
		from = at + 1;
	}

	out.push_back(line.substr(from));
}

//컬럼 이름으로 자리번호를 찾는다. 없으면 -1.
//순서가 바뀌거나 컬럼이 빠져도 읽히게 하려고 이름으로 찾는다.
static int ColIdx(const NetTableIn& t, const char* name)
{
	size_t i;

	for (i = 0; i < t.cols.size(); i++)
		if (t.cols[i] == name)
			return (int)i;

	return -1;
}

static long long RowNum(const std::vector<std::string>& row, int idx, long long def)
{
	if (idx < 0 || idx >= (int)row.size() || row[idx].empty() || row[idx] == "\\N")
		return def;

	return atoll(row[idx].c_str());
}

static std::string RowStr(const std::vector<std::string>& row, int idx)
{
	if (idx < 0 || idx >= (int)row.size())
		return std::string();

	return NetUnescape(row[idx]);
}

//덤프 텍스트를 표 묶음으로 쪼갠다. 규격에 안 맞으면 false.
static bool NetParseDump(const std::string& text, NetTableMap& out,
	long long* userId, long long* revision)
{
	std::vector<std::string> lines;
	std::vector<std::string> f;
	size_t from = 0, at;
	size_t i = 0;

	//행 구분은 LF다. CRLF로 들어오면 규격 위반이라 여기서 걸린다.
	while ((at = text.find('\n', from)) != std::string::npos) {
		lines.push_back(text.substr(from, at - from));
		from = at + 1;
	}

	if (from < text.size())
		lines.push_back(text.substr(from));

	//---- 헤더 ----
	while (i < lines.size() && lines[i].empty())
		i++;

	if (i >= lines.size() || lines[i].compare(0, 9, "#insamdb\t") != 0) {
		CCLOG("NetParseDump: #insamdb 줄이 없다");
		return false;
	}

	while (i < lines.size() && !lines[i].empty() && lines[i][0] == '#') {
		SplitTab(lines[i], f);

		if (f[0] == "#table")
			break;

		if (f[0] == "#user" && f.size() > 1 && userId)
			*userId = atoll(f[1].c_str());

		if (f[0] == "#revision" && f.size() > 1 && revision)
			*revision = atoll(f[1].c_str());

		i++;

		while (i < lines.size() && lines[i].empty())
			i++;
	}

	//---- 표들 ----
	for (;;) {
		while (i < lines.size() && lines[i].empty())
			i++;

		if (i >= lines.size())
			break;

		if (lines[i].compare(0, 4, "#end") == 0)
			break;

		if (lines[i].compare(0, 7, "#table\t") != 0) {
			CCLOG("NetParseDump: #table이 와야 하는데 다른 줄이 나왔다");
			return false;
		}

		SplitTab(lines[i], f);
		std::string name = f.size() > 1 ? f[1] : "";
		i++;

		if (i >= lines.size() || lines[i].compare(0, 6, "#cols\t") != 0) {
			CCLOG("NetParseDump: %s 표에 #cols가 없다", name.c_str());
			return false;
		}

		NetTableIn t;
		SplitTab(lines[i], f);
		t.cols.assign(f.begin() + 1, f.end());
		i++;

		if (i >= lines.size() || lines[i].compare(0, 6, "#rows\t") != 0) {
			CCLOG("NetParseDump: %s 표에 #rows가 없다", name.c_str());
			return false;
		}

		SplitTab(lines[i], f);
		int count = f.size() > 1 ? atoi(f[1].c_str()) : 0;
		i++;

		//데이터는 개수로 읽는다. 줄 첫 글자로 판단하지 않으므로 값 안에
		//#이 있어도 상관없다.
		for (int n = 0; n < count; n++) {
			if (i >= lines.size()) {
				CCLOG("NetParseDump: %s 표가 %d행이라는데 모자란다", name.c_str(), count);
				return false;
			}

			std::vector<std::string> row;
			SplitTab(lines[i], row);
			t.rows.push_back(row);
			i++;
		}

		out[name] = t;
	}

	return true;
}

//---- 표 묶음을 robin에 붓는다 ----
static void NetApplyDump(NetTableMap& tables)
{
	NetTableMap::iterator it;
	size_t r;
	int i, j;

	//player
	if ((it = tables.find("player")) != tables.end() && !it->second.rows.empty()) {
		NetTableIn& t = it->second;
		std::vector<std::string>& v = t.rows[0];

		robin.nickname = RowStr(v, ColIdx(t, "nickname"));
		robin.lv = (int)RowNum(v, ColIdx(t, "lv"), robin.lv);
		robin.exps = (int)RowNum(v, ColIdx(t, "exps"), 0);
		robin.gold = RowNum(v, ColIdx(t, "gold"), 0);
		robin.heart = RowNum(v, ColIdx(t, "heart"), 0);
		robin.medal = RowNum(v, ColIdx(t, "medal"), 0);
		robin.star = RowNum(v, ColIdx(t, "star"), 0);
		robin.hammer = RowNum(v, ColIdx(t, "hammer"), 0);
		robin.coin = RowNum(v, ColIdx(t, "coin"), 0);
		robin.shield = (int)RowNum(v, ColIdx(t, "shield"), 0);
		robin.castle = (int)RowNum(v, ColIdx(t, "castle"), 0);
		robin.stage = (int)RowNum(v, ColIdx(t, "stage"), 0);
		robin.room = (int)RowNum(v, ColIdx(t, "room"), 0);
		robin.bossRoom = (signed char)RowNum(v, ColIdx(t, "boss_room"), 0);
		robin.maxInven = (unsigned short)RowNum(v, ColIdx(t, "max_inven"), robin.maxInven);
		robin.maxStatusCnt = (int)RowNum(v, ColIdx(t, "max_status_cnt"), 0);
		robin.playtime = (int)RowNum(v, ColIdx(t, "playtime"), 0);
		robin.eventCnt = (int)RowNum(v, ColIdx(t, "event_cnt"), 0);
		robin.currentDay = (int)RowNum(v, ColIdx(t, "current_day"), 0);
		robin.lifeRemaining = (int)RowNum(v, ColIdx(t, "life_remaining"), 0);
		robin.crewHighGradeMissCount = (int)RowNum(v, ColIdx(t, "crew_miss_cnt"), 0);
		robin.equipHighGradeMissCount = (int)RowNum(v, ColIdx(t, "equip_miss_cnt"), 0);
		robin.startTime = RowNum(v, ColIdx(t, "start_ts"), 0);
		robin.heartTimeStamp = (long)RowNum(v, ColIdx(t, "heart_ts"), 0);
		robin.freeRewardTimeStamp = (long)RowNum(v, ColIdx(t, "free_reward_ts"), 0);
		robin.calendarTimeStamp = (long)RowNum(v, ColIdx(t, "calendar_ts"), 0);
		robin.calendarMonthDay = (int)RowNum(v, ColIdx(t, "calendar_month_day"), 0);
	}

	//player_castle
	if ((it = tables.find("player_castle")) != tables.end()) {
		NetTableIn& t = it->second;
		int cIdx = ColIdx(t, "castle_idx"), cS = ColIdx(t, "max_stage"), cR = ColIdx(t, "max_room");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cIdx, -1);

			if (i < 0 || i >= CAP_CASTLE)
				continue;

			robin.maxStage[i] = (int)RowNum(t.rows[r], cS, 0);
			robin.maxRoom[i] = (int)RowNum(t.rows[r], cR, 0);
		}
	}

	//player_flag
	if ((it = tables.find("player_flag")) != tables.end()) {
		NetTableIn& t = it->second;
		int cK = ColIdx(t, "flag_kind"), cI = ColIdx(t, "flag_idx"), cV = ColIdx(t, "value");

		for (r = 0; r < t.rows.size(); r++) {
			int kind = (int)RowNum(t.rows[r], cK, -1);
			int idx = (int)RowNum(t.rows[r], cI, -1);
			int val = (int)RowNum(t.rows[r], cV, 1);

			if (idx < 0)
				continue;

			switch (kind) {
			case 0: if (idx < TOTALDEMO) robin.demoSeen[idx] = (val != 0); break;
			case 1: if (idx < TOTAL_MENU) robin.openedMenu[idx] = (unsigned char)val; break;
			case 2: if (idx < TOTAL_STATUE) robin.statue[idx] = (val != 0); break;
			case 3: if (idx < ITEM_GEM_START) robin.equipGet[idx] = (val != 0); break;
			}
		}
	}

	//player_consumable
	if ((it = tables.find("player_consumable")) != tables.end()) {
		NetTableIn& t = it->second;
		int cI = ColIdx(t, "waste_idx"), cC = ColIdx(t, "cnt");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cI, -1);

			if (i >= 0 && i < TOTAL_WASTE)
				robin.buffItem[i] = (int)RowNum(t.rows[r], cC, 0);
		}
	}

	//inventory. 앞에서부터 다시 채우고 남은 자리는 EMPTY로 막는다.
	if ((it = tables.find("inventory")) != tables.end()) {
		NetTableIn& t = it->second;
		int cU = ColIdx(t, "item_uid"), cT = ColIdx(t, "item_type"), cD = ColIdx(t, "detail");
		int cG = ColIdx(t, "grade"), cL = ColIdx(t, "lv"), cC = ColIdx(t, "cnt");
		int cCd = ColIdx(t, "cooldown"), cE = ColIdx(t, "exp"), cS = ColIdx(t, "seen");

		//item_uid -> 인벤 자리번호. 옵션/소켓이 이 번호로 붙는다.
		std::map<long long, int> uidToSlot;

		for (i = 0; i < TOTALINVENTORY; i++) {
			memset(&robin.inven[i], 0, sizeof(ITEM));
			robin.inven[i].type = EMPTY;

			for (j = 0; j < 12; j++)
				robin.inven[i].option[j][0] = EMPTYINT;

			for (j = 0; j < MAXSOCKET; j++)
				robin.inven[i].socket[j] = EMPTYINT;
		}

		int slot = 0;

		for (r = 0; r < t.rows.size() && slot < TOTALINVENTORY; r++) {
			ITEM* p = &robin.inven[slot];

			p->type = (unsigned char)RowNum(t.rows[r], cT, EMPTY);
			p->detail = (unsigned char)RowNum(t.rows[r], cD, 0);
			p->grade = (unsigned char)RowNum(t.rows[r], cG, 0);
			p->lv = (unsigned char)RowNum(t.rows[r], cL, 0);
			p->count = (unsigned int)RowNum(t.rows[r], cC, 0);
			p->cooldown = (unsigned short)RowNum(t.rows[r], cCd, 0);
			p->exp = (int)RowNum(t.rows[r], cE, 0);
			p->seen = RowNum(t.rows[r], cS, 0) != 0;

			uidToSlot[RowNum(t.rows[r], cU, 0)] = slot;
			slot++;
		}

		robin.count = (unsigned short)slot;

		//옵션
		if ((it = tables.find("inventory_option")) != tables.end()) {
			NetTableIn& o = it->second;
			int oU = ColIdx(o, "item_uid"), oS = ColIdx(o, "slot");
			int oT = ColIdx(o, "opt_type"), oV = ColIdx(o, "opt_value");

			for (r = 0; r < o.rows.size(); r++) {
				std::map<long long, int>::iterator f = uidToSlot.find(RowNum(o.rows[r], oU, -1));

				if (f == uidToSlot.end())
					continue;

				j = (int)RowNum(o.rows[r], oS, -1);

				if (j < 0 || j >= 12)
					continue;

				robin.inven[f->second].option[j][0] = (int)RowNum(o.rows[r], oT, EMPTYINT);
				robin.inven[f->second].option[j][1] = (int)RowNum(o.rows[r], oV, 0);
			}
		}

		//소켓
		if ((it = tables.find("inventory_socket")) != tables.end()) {
			NetTableIn& o = it->second;
			int oU = ColIdx(o, "item_uid"), oS = ColIdx(o, "slot"), oG = ColIdx(o, "gem");

			for (r = 0; r < o.rows.size(); r++) {
				std::map<long long, int>::iterator f = uidToSlot.find(RowNum(o.rows[r], oU, -1));

				if (f == uidToSlot.end())
					continue;

				j = (int)RowNum(o.rows[r], oS, -1);

				if (j < 0 || j >= MAXSOCKET)
					continue;

				robin.inven[f->second].socket[j] = (int)RowNum(o.rows[r], oG, EMPTYINT);
			}
		}
	}

	//hero
	if ((it = tables.find("hero")) != tables.end()) {
		NetTableIn& t = it->second;
		int cH = ColIdx(t, "hero_idx"), cSet = ColIdx(t, "is_set"), cE = ColIdx(t, "exps");
		int cHp = ColIdx(t, "hp"), cMp = ColIdx(t, "mp"), cAp = ColIdx(t, "ap"), cSp = ColIdx(t, "sp");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cH, -1);

			if (i < 0 || i >= TOTALPLAYER)
				continue;

			robin.heroesSetting[i] = RowNum(t.rows[r], cSet, 0) != 0;
			robin.charData[i].exps = (int)RowNum(t.rows[r], cE, 0);
			robin.charData[i].hp = RowNum(t.rows[r], cHp, 0);
			robin.charData[i].mp = (int)RowNum(t.rows[r], cMp, 0);
			robin.charData[i].ap = (unsigned short)RowNum(t.rows[r], cAp, 0);
			robin.charData[i].sp = (unsigned char)RowNum(t.rows[r], cSp, 0);
		}
	}

	//hero_equip
	if ((it = tables.find("hero_equip")) != tables.end()) {
		NetTableIn& t = it->second;
		int cH = ColIdx(t, "hero_idx"), cS = ColIdx(t, "slot"), cT = ColIdx(t, "item_type");
		int cD = ColIdx(t, "detail"), cG = ColIdx(t, "grade");
		int cL = ColIdx(t, "lv"), cCd = ColIdx(t, "cooldown");

		for (i = 0; i < TOTALPLAYER; i++)
			for (j = 0; j < TOTALEQUIP; j++)
				robin.charData[i].equip[j].type = EMPTY;

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cH, -1);
			j = (int)RowNum(t.rows[r], cS, -1);

			if (i < 0 || i >= TOTALPLAYER || j < 0 || j >= TOTALEQUIP)
				continue;

			ITEM* p = &robin.charData[i].equip[j];

			p->type = (unsigned char)RowNum(t.rows[r], cT, EMPTY);
			p->detail = (unsigned char)RowNum(t.rows[r], cD, 0);
			p->grade = (unsigned char)RowNum(t.rows[r], cG, 0);
			p->lv = (unsigned char)RowNum(t.rows[r], cL, 0);
			p->cooldown = (unsigned short)RowNum(t.rows[r], cCd, 0);
		}
	}

	//hero_hotkey
	if ((it = tables.find("hero_hotkey")) != tables.end()) {
		NetTableIn& t = it->second;
		int cH = ColIdx(t, "hero_idx"), cS = ColIdx(t, "slot");
		int cT = ColIdx(t, "hk_type"), cI = ColIdx(t, "hk_idx");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cH, -1);
			j = (int)RowNum(t.rows[r], cS, -1);

			if (i < 0 || i >= TOTALPLAYER || j < 0 || j >= MAXHOTKEY)
				continue;

			robin.charData[i].hotKey[j].type = (signed short)RowNum(t.rows[r], cT, 0);
			robin.charData[i].hotKey[j].idx = (signed short)RowNum(t.rows[r], cI, 0);
		}
	}

	//hero_skill
	if ((it = tables.find("hero_skill")) != tables.end()) {
		NetTableIn& t = it->second;
		int cH = ColIdx(t, "hero_idx"), cS = ColIdx(t, "skill_idx"), cL = ColIdx(t, "skill_lv");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cH, -1);
			j = (int)RowNum(t.rows[r], cS, -1);

			if (i < 0 || i >= TOTALPLAYER || j < 0 || j >= CAP_SKILL)
				continue;

			robin.charData[i].skillLv[j] = (signed char)RowNum(t.rows[r], cL, 0);
		}
	}

	//hero_skill_slot
	if ((it = tables.find("hero_skill_slot")) != tables.end()) {
		NetTableIn& t = it->second;
		int cH = ColIdx(t, "hero_idx"), cS = ColIdx(t, "slot"), cI = ColIdx(t, "skill_idx");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cH, -1);
			j = (int)RowNum(t.rows[r], cS, -1);

			if (i < 0 || i >= TOTALPLAYER || j < 0 || j >= MAXCHARSKILL)
				continue;

			robin.charData[i].getSkillList[j] = (unsigned char)RowNum(t.rows[r], cI, 0);
		}
	}

	//crew_slot. 표에 없는 자리는 빈 칸(-1)이다.
	for (i = 0; i < MAXCREW; i++)
		robin.slotCrew[i] = -1;

	if ((it = tables.find("crew_slot")) != tables.end()) {
		NetTableIn& t = it->second;
		int cS = ColIdx(t, "slot"), cT = ColIdx(t, "crew_type");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cS, -1);

			if (i >= 0 && i < MAXCREW)
				robin.slotCrew[i] = (int)RowNum(t.rows[r], cT, -1);
		}
	}

	//quest_progress
	if ((it = tables.find("quest_progress")) != tables.end()) {
		NetTableIn& t = it->second;
		int cK = ColIdx(t, "kind"), cQ = ColIdx(t, "quest"), cSq = ColIdx(t, "sub_quest");
		int cDq = ColIdx(t, "detail_quest"), cC = ColIdx(t, "cnt"), cTs = ColIdx(t, "started_ts");
		int cR = ColIdx(t, "remain_item"), cTh = ColIdx(t, "this_time_item");

		for (r = 0; r < t.rows.size(); r++) {
			if (RowNum(t.rows[r], cK, 0) == 0) {
				robin.quest = (int)RowNum(t.rows[r], cQ, 0);
				robin.subQuest = (int)RowNum(t.rows[r], cSq, 0);
				robin.questCnt = (int)RowNum(t.rows[r], cC, 0);
				robin.questTimeStamp = (long)RowNum(t.rows[r], cTs, 0);
				robin.remainQuestItem = RowNum(t.rows[r], cR, 0);
				robin.thisTimeQuestItem = RowNum(t.rows[r], cTh, 0);
			}
			else {
				robin.pvpQuest = (int)RowNum(t.rows[r], cQ, 0);
				robin.pvpSubQuest = (int)RowNum(t.rows[r], cSq, 0);
				robin.pvpDetailQuest = (int)RowNum(t.rows[r], cDq, 0);
				robin.pvpQuestCnt = (int)RowNum(t.rows[r], cC, 0);
				robin.pvpQuestTimeStamp = (long)RowNum(t.rows[r], cTs, 0);
				robin.remainPvpQuestItem = RowNum(t.rows[r], cR, 0);
				robin.thisTimePvpQuestItem = RowNum(t.rows[r], cTh, 0);
			}
		}
	}

	//game_event
	memset(&robin.gameEvent, 0, sizeof(robin.gameEvent));

	if ((it = tables.find("game_event")) != tables.end()) {
		NetTableIn& t = it->second;
		int cS = ColIdx(t, "slot"), cT = ColIdx(t, "ev_type"), cSt = ColIdx(t, "sub_type");
		int cI = ColIdx(t, "icon"), cTs = ColIdx(t, "started_ts"), cL = ColIdx(t, "limit_sec");
		int cSs = ColIdx(t, "status"), cB = ColIdx(t, "bar_status");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cS, -1);

			if (i < 0 || i >= MAXGAMEEVENT)
				continue;

			robin.gameEvent[i].type = (unsigned char)RowNum(t.rows[r], cT, 0);
			robin.gameEvent[i].subType = (unsigned char)RowNum(t.rows[r], cSt, 0);
			robin.gameEvent[i].icon = (short)RowNum(t.rows[r], cI, 0);
			robin.gameEvent[i].timeStamp = (long)RowNum(t.rows[r], cTs, 0);
			robin.gameEvent[i].limitTime = (long)RowNum(t.rows[r], cL, 0);
			robin.gameEvent[i].status = (unsigned char)RowNum(t.rows[r], cSs, 0);
			robin.gameEvent[i].barStatus = (unsigned char)RowNum(t.rows[r], cB, 0);
		}
	}

	//calendar_day
	if ((it = tables.find("calendar_day")) != tables.end()) {
		NetTableIn& t = it->second;
		int cD = ColIdx(t, "day_idx"), cS = ColIdx(t, "status");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cD, -1);

			if (i >= 0 && i < WEEK)
				robin.calendarDayStatus[i] = (int)RowNum(t.rows[r], cS, 0);
		}
	}

	//battle_session
	if ((it = tables.find("battle_session")) != tables.end() && !it->second.rows.empty()) {
		NetTableIn& t = it->second;
		std::vector<std::string>& v = t.rows[0];

		robin.waveIdx = (int)RowNum(v, ColIdx(t, "wave_idx"), 0);
		robin.curWaveIdx = (int)RowNum(v, ColIdx(t, "cur_wave_idx"), 0);
		robin.waveTimeStamp = (long)RowNum(v, ColIdx(t, "wave_ts"), 0);
		robin.enemyUserIdx = (int)RowNum(v, ColIdx(t, "enemy_user_idx"), 0);
	}

	//battle_enemy
	memset(&robin.enemyObj, 0, sizeof(robin.enemyObj));

	if ((it = tables.find("battle_enemy")) != tables.end()) {
		NetTableIn& t = it->second;
		int cS = ColIdx(t, "slot"), cM = ColIdx(t, "mom"), cT = ColIdx(t, "enemy_type");
		int cC = ColIdx(t, "cmf"), cHp = ColIdx(t, "hp"), cMh = ColIdx(t, "max_hp");
		int cSt = ColIdx(t, "status"), cE = ColIdx(t, "etc");
		int cNx = ColIdx(t, "nx"), cNy = ColIdx(t, "ny"), cDf = ColIdx(t, "dir_f");
		int cL = ColIdx(t, "lv"), cStr = ColIdx(t, "str"), cDef = ColIdx(t, "def");
		int cA = ColIdx(t, "attr"), cSk = ColIdx(t, "skill_idx"), cCs = ColIdx(t, "cur_skill");
		int cCt = ColIdx(t, "cool_time"), cTg = ColIdx(t, "target"), cDd = ColIdx(t, "dead");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cS, -1);

			if (i < 0 || i >= MAXENEMY * MAXENEMYOBJ)
				continue;

			OBJECT* p = &robin.enemyObj[i];

			p->active = true;
			p->mom = (unsigned short)RowNum(t.rows[r], cM, i);
			p->type = (int)RowNum(t.rows[r], cT, 0);
			p->cmf = (signed short)RowNum(t.rows[r], cC, 0);
			p->hp = RowNum(t.rows[r], cHp, 0);
			p->maxhp = RowNum(t.rows[r], cMh, 0);
			p->status = (signed char)RowNum(t.rows[r], cSt, 0);
			p->etc = (int)RowNum(t.rows[r], cE, 0);
			p->nx = p->x = (int)RowNum(t.rows[r], cNx, 0);
			p->ny = p->y = (int)RowNum(t.rows[r], cNy, 0);
			p->dirF = p->dirX = (signed char)RowNum(t.rows[r], cDf, 0);
			p->lv = (int)RowNum(t.rows[r], cL, 0);
			p->str = RowNum(t.rows[r], cStr, 0);
			p->def = RowNum(t.rows[r], cDef, 0);
			p->attr = (unsigned short)RowNum(t.rows[r], cA, 0);
			p->skillIdx = (unsigned char)RowNum(t.rows[r], cSk, 0);
			p->currentSkill = (int)RowNum(t.rows[r], cCs, 0);
			p->coolTime = (long)RowNum(t.rows[r], cCt, 0);
			p->target = (unsigned short)RowNum(t.rows[r], cTg, 0);
			p->dead = (signed char)RowNum(t.rows[r], cDd, 0);
		}
	}

	//battle_enemy_effect
	if ((it = tables.find("battle_enemy_effect")) != tables.end()) {
		NetTableIn& t = it->second;
		int cS = ColIdx(t, "slot"), cK = ColIdx(t, "kind"), cI = ColIdx(t, "eff_idx");
		int cR = ColIdx(t, "remain"), cO = ColIdx(t, "owner");

		for (r = 0; r < t.rows.size(); r++) {
			i = (int)RowNum(t.rows[r], cS, -1);
			j = (int)RowNum(t.rows[r], cI, -1);

			if (i < 0 || i >= MAXENEMY * MAXENEMYOBJ || j < 0)
				continue;

			OBJECT* p = &robin.enemyObj[i];

			if (RowNum(t.rows[r], cK, 0) == 0) {
				if (j < TOTALBUFF) {
					p->buff[j] = (signed short)RowNum(t.rows[r], cR, 0);
					p->buffOwner[j] = (unsigned char)RowNum(t.rows[r], cO, 0);
				}
			}
			else {
				if (j < TOTALDEBUF) {
					p->debuf[j] = (signed int)RowNum(t.rows[r], cR, 0);
					p->debufOwner[j] = (unsigned char)RowNum(t.rows[r], cO, 0);
				}
			}
		}
	}
}

//=============================================================================
// 4. 임시 로컬 서버
//
// ★ 진짜 서버가 붙으면 이 구역만 HttpClient 호출로 갈아끼운다.
//   위아래 구역은 그대로 둔다. 그러라고 나눠 놓은 것이다.
//
// 여기서 하는 일은 서버가 할 일과 같다.
//   - 요청을 받고
//   - revision을 검사해서 나중 것을 거절하고
//   - 파일(=DB)에 원자적으로 쓴다
//=============================================================================

static std::string ServerPath(const char* name)
{
	std::string path = FileUtils::getInstance()->getWritablePath();

	path.append(name);
	return path;
}

//파일 통째로 읽기
static bool ServerReadFile(const char* name, std::string& out)
{
	FILE* fp = fopen(ServerPath(name).c_str(), "rb");
	char buf[4096];
	size_t got;

	if (!fp)
		return false;

	out.clear();

	while ((got = fread(buf, 1, sizeof(buf), fp)) > 0)
		out.append(buf, got);

	fclose(fp);
	return true;
}

//원자적으로 쓰기.
//임시파일에 다 쓰고 나서 rename으로 바꿔친다. rename은 같은 파일시스템 안에서
//원자적이라(iOS/안드로이드 모두), 저장 도중에 앱이 죽어도 파일은 "이전 것 전체"
//아니면 "새 것 전체"다. 반쯤 쓰인 상태가 존재하지 않는다.
static bool ServerWriteFile(const char* name, const std::string& data)
{
	std::string tmp = ServerPath(SERVERDBTEMP);
	std::string dst = ServerPath(name);

	FILE* fp = fopen(tmp.c_str(), "wb");

	if (!fp) {
		CCLOG("ServerWriteFile: 임시파일을 못 만든다 %s", tmp.c_str());
		return false;
	}

	if (fwrite(data.c_str(), 1, data.size(), fp) != data.size()) {
		fclose(fp);
		remove(tmp.c_str());
		CCLOG("ServerWriteFile: 다 못 썼다(디스크가 찼나)");
		return false;
	}

	fflush(fp);
	fclose(fp);

	//윈도우 rename()은 대상이 있으면 실패한다. 개발용 win32에서만 쓰는 경로다.
	//iOS/안드로이드에서는 아래 remove 없이 rename 한 번으로 끝난다.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	remove(dst.c_str());
#endif

	if (rename(tmp.c_str(), dst.c_str()) != 0) {
		CCLOG("ServerWriteFile: rename 실패");
		remove(tmp.c_str());
		return false;
	}

	return true;
}

//서버가 들고 있는 revision을 본다. 파일이 없으면 0.
static long long ServerReadRevision(void)
{
	std::string text;
	size_t at, end;

	if (!ServerReadFile(SERVERDBFILE, text))
		return 0;

	at = text.find("#revision\t");

	if (at == std::string::npos)
		return 0;

	at += 10;
	end = text.find('\n', at);

	return atoll(text.substr(at, end - at).c_str());
}

//서버의 지금 시각.
//
//★ 진짜 서버가 붙으면 여기가 "응답에 실려 온 서버 시각" 을 돌려주게 된다.
//지금은 임시 서버가 곧 이 기기라 기기 시계를 그대로 준다. 그래서 오프셋이
//0이 나오고, 예전과 똑같이 동작한다. 얼개만 미리 깔아두는 것이다.
//
//여기서 MC_knlCurrentTimeStamp() 를 쓰면 안 된다. 그건 오프셋이 이미 더해진
//값이라, 그걸로 오프셋을 다시 구하면 값이 자기를 물고 커진다.
static long ServerNow(void)
{
	return MC_knlRawTimeStamp();
}

//---- 서버 : 로그인 ----
static int ServerLogin(void)
{
	//서버에 닿았으니 시각을 맞춘다. 답을 주는 모든 길목에서 한다.
	NetSetServerTime(ServerNow());

	std::string text;
	size_t at, end;

	if (!ServerReadFile(SERVERDBFILE, text)) {
		//처음 온 손님. 계정을 만들어 준다.
		//진짜 서버라면 AUTO_INCREMENT가 번호를 준다. 여기서는 시간과 난수를
		//섞어 만든다. 시간만 쓰면 같은 초에 만든 계정끼리 번호가 겹치고,
		//로그에서 타임스탬프와 헷갈린다.
		gNetUserId = (long long)MC_knlRawTimeStamp() * 1000 + Random(1000);
		gNetRevision = 0;
		return NETRESULT_ERR_NOTFOUND;
	}

	at = text.find("#user\t");

	if (at != std::string::npos) {
		at += 6;
		end = text.find('\n', at);
		gNetUserId = atoll(text.substr(at, end - at).c_str());
	}

	gNetRevision = ServerReadRevision();
	return NETRESULT_OK;
}

//---- 파일에 있는 것을 robin 에 올린다 ----
//
//임시 서버에게는 이것이 "세이브 내려주기"이고, 진짜 서버를 쓸 때는 서버에
//못 붙었을 때 기대는 오프라인 캐시다. 하는 일이 같아서 하나로 둔다.
//
//wantUser 가 0이 아니면 캐시의 주인이 그 계정인지 본다. 기기를 갈거나 앱을
//지웠다 깔면 열쇠가 새로 생기는데, 그때 남아 있던 지난 계정의 캐시를 올리면
//남의 세이브를 자기 것으로 들고 있게 된다. 그 상태로 저장하면 서버가 403으로
//거절한다.
//
//여기서 시각을 건드리지 않는 것은 일부러다. 캐시는 서버가 아니라서 "지금
//몇 시인지" 를 알려줄 자격이 없다. NetInit() 이 gNetTimeOffset 을 남겨두는
//것과 같은 이유다.
static int LoadFromCache(long long wantUser)
{
	std::string text;
	NetTableMap tables;
	long long userId = 0, revision = 0;

	if (!ServerReadFile(SERVERDBFILE, text))
		return NETRESULT_ERR_NOTFOUND;

	if (!NetParseDump(text, tables, &userId, &revision))
		return NETRESULT_ERR_FORMAT;

	if (wantUser != 0 && userId != wantUser) {
		CCLOG("LoadFromCache: 캐시가 다른 계정 것이다 (%lld, 지금은 %lld). 안 쓴다",
			userId, wantUser);
		return NETRESULT_ERR_FORMAT;
	}

	gNetUserId = userId;
	gNetRevision = revision;

	NetApplyDump(tables);
	return NETRESULT_OK;
}

//---- 서버 : 세이브 내려주기 ----
static int ServerLoad(void)
{
	//서버에 닿았으니 시각을 맞춘다.
	NetSetServerTime(ServerNow());

	//임시 서버는 이 기기가 곧 서버라 주인을 따질 것이 없다.
	return LoadFromCache(0);
}

//덤프 안의 player 표에서 revision 칸만 새 값으로 갈아끼운다.
//revision은 서버가 정하는 값이라 클라이언트가 적어 보낸 것을 믿지 않는다.
//컬럼 자리번호는 #cols 줄에서 이름으로 찾는다. 컬럼 순서가 바뀌어도 견딘다.
static bool ServerSetPlayerRevision(std::string& text, long long newRev)
{
	size_t at, colsAt, colsEnd, rowsAt, rowAt, rowEnd;
	std::vector<std::string> cols;
	std::vector<std::string> row;
	std::string line;
	char buf[64];
	int idx = -1;
	size_t i;

	at = text.find("\n#table\tplayer\n");

	if (at == std::string::npos)
		return false;

	colsAt = text.find("#cols\t", at);

	if (colsAt == std::string::npos)
		return false;

	colsEnd = text.find('\n', colsAt);
	SplitTab(text.substr(colsAt, colsEnd - colsAt), cols);

	//cols[0]은 "#cols"라 한 칸 밀려 있다.
	for (i = 1; i < cols.size(); i++)
		if (cols[i] == "revision") {
			idx = (int)i - 1;
			break;
		}

	if (idx < 0)
		return false;

	rowsAt = text.find("#rows\t", colsEnd);

	if (rowsAt == std::string::npos)
		return false;

	rowAt = text.find('\n', rowsAt) + 1;
	rowEnd = text.find('\n', rowAt);

	if (rowEnd == std::string::npos)
		return false;

	SplitTab(text.substr(rowAt, rowEnd - rowAt), row);

	if (idx >= (int)row.size())
		return false;

	sprintf(buf, "%lld", newRev);
	row[idx] = buf;

	line.clear();

	for (i = 0; i < row.size(); i++) {
		if (i)
			line += '\t';

		line += row[i];
	}

	text.replace(rowAt, rowEnd - rowAt, line);
	return true;
}

//---- 서버 : 세이브 받기 ----
//body는 클라이언트가 만든 덤프다. 그 안의 #revision이 서버가 들고 있는 것과
//같아야 받아준다. 다르면 다른 기기가 먼저 저장한 것이므로 거절한다.
static int ServerSave(const std::string& body)
{
	//서버에 닿았으니 시각을 맞춘다.
	NetSetServerTime(ServerNow());

	long long serverRev = ServerReadRevision();
	long long sentRev = 0;
	size_t at, end;

	at = body.find("#revision\t");

	if (at != std::string::npos) {
		at += 10;
		end = body.find('\n', at);
		sentRev = atoll(body.substr(at, end - at).c_str());
	}

	if (sentRev != serverRev) {
		//나중에 온 저장을 버린다. 클라이언트는 다시 받아서 이어가야 한다.
		CCLOG("ServerSave: 충돌. 보낸 revision=%lld 서버=%lld", sentRev, serverRev);
		return NETRESULT_ERR_CONFLICT;
	}

	//받아들인다. revision을 올려서 다시 쓴다.
	//revision은 서버가 정하는 값이라 클라이언트가 보낸 값을 그대로 두면 안 된다.
	//헤더(#revision)와 player 표의 revision 칸 두 곳에 다 있으므로 둘 다 고친다.
	//한쪽만 고치면 이 파일을 DB에 넣었을 때 player.revision이 헤더와 어긋난다.
	long long newRev = serverRev + 1;
	std::string text = body;
	char buf[64];

	at = text.find("#revision\t");

	if (at != std::string::npos) {
		end = text.find('\n', at);
		sprintf(buf, "#revision\t%lld", newRev);
		text.replace(at, end - at, buf);
	}

	if (!ServerSetPlayerRevision(text, newRev)) {
		CCLOG("ServerSave: player 표의 revision 칸을 못 찾았다");
		return NETRESULT_ERR_FORMAT;
	}

	//꼬리의 체크섬을 다시 계산한다.
	at = text.rfind("#end\t");

	if (at != std::string::npos) {
		std::string head = text.substr(0, at);

		sprintf(buf, "#end\t%08x\n", NetCrc32(head.c_str(), head.size()));
		text = head + buf;
	}

	if (!ServerWriteFile(SERVERDBFILE, text))
		return NETRESULT_ERR_NETWORK;

	gNetRevision = newRev;
	return NETRESULT_OK;
}

//=============================================================================
// 5. 진짜 서버
//
// 구역 4와 하는 일이 같다. 다만 파일 대신 HTTP 를 탄다.
//
// 형식은 하나도 안 바뀐다. 보내는 것도 받는 것도 구역 2·3이 다루는 그 덤프
// 텍스트 그대로다. JSON 으로 감싸지 않는 이유가 이것이다 — 감싸면 파서가
// 양쪽에 하나씩 더 생긴다.
//=============================================================================

//서버를 쓰는가. NetConfig.h 의 한 줄이 정한다.
static bool UsingServer(void)
{
	return NET_SERVER_URL[0] != '\0';
}

//---- 게스트 열쇠 ----
//
// 첫 실행에 UUID 를 하나 만들어 쓰기 가능 경로에 둔다. 이것이 계정의 유일한
// 열쇠다. 예전에는 임시 서버가 user_id 를 시간과 난수로 지어냈는데, 진짜
// 서버가 붙으면 번호는 AUTO_INCREMENT 가 주므로 그 자리가 통째로 사라진다.

static std::string sGuestKey;

//RFC 4122 v4. 난수 128비트에서 버전과 변형 비트만 정해준다.
static std::string NetMakeUuid(void)
{
	static const char* hex = "0123456789abcdef";
	char buf[37];
	int i;

	for (i = 0; i < 36; i++)
		buf[i] = hex[Random(16)];

	buf[8] = buf[13] = buf[18] = buf[23] = '-';
	buf[14] = '4';					//버전 4
	buf[19] = hex[8 + Random(4)];	//변형 10xx
	buf[36] = 0;

	return std::string(buf);
}

static const std::string& NetGuestKey(void)
{
	std::string text;

	if (!sGuestKey.empty())
		return sGuestKey;

	if (ServerReadFile(NET_GUESTKEYFILE, text)) {
		//앞뒤 공백을 턴다. 손으로 넣어보는 일이 있다.
		size_t b = text.find_first_not_of(" \t\r\n");
		size_t e = text.find_last_not_of(" \t\r\n");

		if (b != std::string::npos)
			sGuestKey = text.substr(b, e - b + 1);
	}

	if (sGuestKey.size() != 36) {
		sGuestKey = NetMakeUuid();

		//못 적으면 다음 실행에 계정이 새로 생긴다. 조용히 넘기면 안 된다.
		if (ServerWriteFile(NET_GUESTKEYFILE, sGuestKey))
			CCLOG("NetGuestKey: 새 열쇠를 만들었다");
		else
			CCLOG("NetGuestKey: 열쇠를 못 적었다. 다음 실행에 계정이 새로 생긴다");
	}

	return sGuestKey;
}

//---- 도는 요청 하나 ----
//
// 한 번에 하나만 돈다(구역 6이 그렇게 막는다). 그래서 상태를 하나만 둔다.

enum {
	NETHTTP_IDLE = 0,
	NETHTTP_WAIT,
	NETHTTP_DONE,
};

static int sHttpState = NETHTTP_IDLE;
static long sHttpCode = 0;
static bool sHttpReached = false;	//서버에 닿기는 했는가
static std::string sHttpBody;

//요청마다 번호를 매긴다. 늦게 도착한 지난 요청의 답을 지금 것으로 착각하면
//안 된다. NetInit() 이 번호를 올려서 도는 것을 통째로 버리기도 한다.
static int sHttpGen = 0;

//요청 객체는 하나를 만들어 계속 쓴다.
//
//매번 new 하면 안 된다. 그 객체를 지우는 것은 libcocos2d.dll 안의
//Ref::release() 인데, 만드는 것은 이쪽(cs.exe)이다. 모듈이 다르면 힙이
//어긋나서, 지우는 순간 힙이 깨지거나 잠긴다. 실제로 그 증상으로 게임 루프가
//통째로 멈췄다.
//
//한 번에 한 요청만 도는 것은 구역 6이 막아주므로(sReq), 하나면 충분하다.
//덤으로 요청마다 할당이 없어진다.
static network::HttpRequest* sHttpReq = NULL;

static void HttpBegin(int reqType, const std::string& body)
{
	std::vector<std::string> headers;

	if (sHttpReq == NULL) {
		sHttpReq = new (std::nothrow) network::HttpRequest();

		if (sHttpReq == NULL)
			return;

		//놓지 않는다. 계수가 0이 되면 위에 적은 그 delete 가 일어난다.
		sHttpReq->retain();
	}

	network::HttpRequest* req = sHttpReq;
	std::string url = NET_SERVER_URL;
	int gen = ++sHttpGen;

	sHttpState = NETHTTP_WAIT;
	sHttpCode = 0;
	sHttpReached = false;
	sHttpBody.clear();

	switch (reqType) {
	case NETREQ_LOGIN:
		url += "/v1/login";
		req->setRequestType(network::HttpRequest::Type::POST);
		req->setRequestData(NetGuestKey().c_str(), NetGuestKey().size());
		break;

	case NETREQ_LOAD:
		url += "/v1/save";
		req->setRequestType(network::HttpRequest::Type::GET);
		break;

	default:
		url += "/v1/save";
		req->setRequestType(network::HttpRequest::Type::POST);
		req->setRequestData(body.c_str(), body.size());
		break;
	}

	req->setUrl(url);

	//---- 자격증명 ----
	//
	// 1단계는 게스트 열쇠를 그대로 보낸다. 3단계에서 세션 토큰으로 바뀌는데,
	// 그때 고칠 곳은 아래 한 줄이다. 구글·애플 연동이 붙어도 이 구역의
	// 나머지는 그대로 간다.
	headers.push_back("Content-Type: text/plain; charset=utf-8");
	headers.push_back(std::string("X-Guest-Key: ") + NetGuestKey());
	req->setHeaders(headers);

	req->setResponseCallback([gen](network::HttpClient* /*c*/,
		network::HttpResponse* res) {

		//여기는 메인 실이다. HttpClient 가 게임 루프로 넘겨준다.
		//그래서 잠금이 필요 없다. Content.cpp 도 같은 얼개다.
		if (gen != sHttpGen)
			return;		//지나간 요청의 답이다. 버린다.

		if (res && res->isSucceed()) {
			std::vector<char>* d = res->getResponseData();

			sHttpReached = true;
			sHttpCode = res->getResponseCode();

			if (d && !d->empty())
				sHttpBody.assign(d->begin(), d->end());
		}
		else if (res) {
			CCLOG("Net: 못 붙었다 (%s)", res->getErrorBuffer());
		}

		sHttpState = NETHTTP_DONE;
	});

	network::HttpClient::getInstance()->send(req);
}

//메타행 하나를 꺼낸다. 없으면 0.
static long long NetPeekMeta(const std::string& text, const char* key)
{
	std::string tag = std::string(key) + "\t";
	size_t at = text.find(tag);
	size_t end;

	//머리에 있어야 한다. 값 안에 우연히 같은 글자가 있을 수 있다.
	if (at == std::string::npos)
		return 0;

	if (at != 0 && text[at - 1] != '\n')
		return 0;

	at += tag.size();
	end = text.find('\n', at);

	return atoll(text.substr(at, end - at).c_str());
}

//답 하나를 해석한다. 상태 코드와 NETRESULT_* 의 대응은 계획서의 표 그대로다.
static int NetTakeResponse(int reqType)
{
	NetTableMap tables;
	long long userId = 0, revision = 0;
	long long now;

	if (!sHttpReached)
		return NETRESULT_ERR_NETWORK;

	//어떤 답이든 #now 가 실려 온다. 무엇보다 먼저 시각을 맞춘다.
	//거절당한 답에도 실려 있고, 그것도 맞는 시각이다.
	now = NetPeekMeta(sHttpBody, "#now");

	if (now > 0)
		NetSetServerTime((long)now);

	switch (sHttpCode) {
	case 200:
		break;

	case 404:
		//이 계정에 세이브가 없다. 클라이언트는 새 게임을 시작한다.
		return NETRESULT_ERR_NOTFOUND;

	case 409:
		//다른 기기가 먼저 저장했다. 몸통에 서버가 들고 있는 덤프가 실려
		//오지만, 지금은 구역 6의 재로드 경로를 그대로 쓴다. 왕복 한 번을
		//아끼는 것은 나중에 정리할 일이고, 지금 고치면 검증할 것이 는다.
		return NETRESULT_ERR_CONFLICT;

	case 400:
		CCLOG("Net: 서버가 규격 위반이라고 한다");
		return NETRESULT_ERR_FORMAT;

	case 401:
	case 403:
		//클라이언트에 인증 전용 결과값이 아직 없어서 "못 붙었다"로 뭉갠다.
		//3단계에서 NETRESULT_ERR_AUTH 를 만들고 여기를 고친다.
		CCLOG("Net: 인증이 거절됐다 (HTTP %ld)", sHttpCode);
		return NETRESULT_ERR_NETWORK;

	default:
		CCLOG("Net: HTTP %ld", sHttpCode);
		return NETRESULT_ERR_NETWORK;
	}

	switch (reqType) {
	case NETREQ_LOGIN:
		//메타행만 온다. 표는 없다.
		gNetUserId = NetPeekMeta(sHttpBody, "#user");
		gNetRevision = NetPeekMeta(sHttpBody, "#revision");

		if (gNetUserId == 0) {
			CCLOG("Net: 로그인 답에 #user 가 없다");
			return NETRESULT_ERR_FORMAT;
		}

		return NETRESULT_OK;

	case NETREQ_LOAD:
		if (!NetParseDump(sHttpBody, tables, &userId, &revision))
			return NETRESULT_ERR_FORMAT;

		gNetUserId = userId;
		gNetRevision = revision;

		NetApplyDump(tables);

		//받은 것을 오프라인 캐시로 남긴다. 서버가 정답이고 이 파일은 사본이다.
		//다음에 서버에 못 붙으면 이것으로 계속 논다.
		if (!ServerWriteFile(SERVERDBFILE, sHttpBody))
			CCLOG("Net: 오프라인 캐시를 못 남겼다");

		return NETRESULT_OK;

	default:
		//저장이 받아들여졌다. revision 은 서버가 정한다.
		gNetRevision = NetPeekMeta(sHttpBody, "#revision");
		return NETRESULT_OK;
	}
}

//---- 두 갈래를 하나로 ----
//
// 구역 6은 어느 길로 가는지 몰라도 되게 한다.

static void ServerBegin(int reqType, const std::string& body)
{
	if (UsingServer())
		HttpBegin(reqType, body);
}

//답이 왔는지 본다. 아직이면 false 를 주고, 구역 6은 다음 프레임에 또 묻는다.
static bool ServerPoll(int reqType, int* out)
{
	if (!UsingServer()) {
		//임시 서버는 파일이라 그 자리에서 끝난다.
		switch (reqType) {
		case NETREQ_LOGIN:
			*out = ServerLogin();
			break;

		case NETREQ_LOAD:
			*out = ServerLoad();
			break;

		case NETREQ_SAVE:
			*out = ServerSave(sNetBody);
			break;

		default:
			*out = NETRESULT_ERR_NETWORK;
			break;
		}

		return true;
	}

	if (sHttpState != NETHTTP_DONE)
		return false;

	sHttpState = NETHTTP_IDLE;
	*out = NetTakeResponse(reqType);

	return true;
}

//=============================================================================
// 6. 클라이언트 API
//=============================================================================

static int sReq = NETREQ_NONE;		//지금 도는 요청
static int sDelay = 0;				//남은 지연 프레임
static bool sSent = false;			//그 요청을 이미 띄웠는가
static int sLastReq = NETREQ_NONE;
static int sLastResult = NETRESULT_NONE;

//---- 부팅 ----
//로그인 다음에 로드를 해야 하는데, 진짜 서버에서는 둘 다 답을 기다린다.
//그 두 걸음을 여기서 센다.
enum {
	NETBOOT_NONE = 0,
	NETBOOT_LOGIN,
	NETBOOT_LOAD,
	NETBOOT_DONE,
};

static int sBootStep = NETBOOT_NONE;
static int sBootResult = NETRESULT_NONE;

//---- 저장 재시도 ----
//보내려다 못 보낸 것을 얼마나 기다렸다 또 해볼지. 바로 다시 하면 서버가
//죽어 있을 때 매 프레임 두드린다.
static int sSaveWait = 0;

//서버에 세이브가 없다. 이 기기에 있던 것을 올린다.
//
//처음 서버에 붙는 기기가 여기로 온다. 그동안은 임시 서버가 serverdb.dat 으로
//처리하고 있었고, SaveGame() 은 옛 save.dat 을 더 이상 쓰지 않는다. 그래서
//지금까지 논 것은 그 파일에만 있다. 여기서 안 올리면 통째로 사라진다.
//
//형식이 같으므로 변환할 것이 없다. 그대로 올리면 된다.
static int NetBootMigrate(void)
{
	long long serverUser = gNetUserId;

	//주인을 안 따진다. 이 파일은 임시 서버가 쓴 것이라 그 안의 user_id 는
	//서버가 준 번호가 아니다. 그것을 견주면 자기 세이브를 자기가 버린다.
	if (LoadFromCache(0) != NETRESULT_OK)
		return NETRESULT_ERR_NOTFOUND;

	//번호는 이제 서버가 준다. 임시 서버가 시간과 난수로 지어낸 번호는 버린다.
	//이것을 안 고치면 저장할 때 서버가 "남의 세이브다"로 거절한다.
	gNetUserId = serverUser;

	//서버에는 아직 아무것도 없으므로 0에서 시작한다.
	gNetRevision = 0;

	CCLOG("NetBootstrap: 서버에 없다. 이 기기의 세이브를 올린다 (user=%lld)", gNetUserId);

	NetMarkDirty();
	NetFlush();

	return NETRESULT_OK;
}

//서버에 못 붙었다. 오프라인 캐시로 시작해 본다.
static int NetBootFallback(int result)
{
	//"없다"는 못 붙은 것이 아니라 서버가 제대로 답한 것이다. 그때는 이
	//기기에 있던 것을 올리는 쪽으로 간다.
	if (result == NETRESULT_ERR_NOTFOUND)
		return NetBootMigrate();

	//로그인이 됐으면 그 계정 것인지 따진다. 로그인부터 실패했으면 따질
	//기준이 없으므로 캐시를 그대로 믿는다.
	if (LoadFromCache(gNetUserId) != NETRESULT_OK)
		return result;

	CCLOG("NetBootstrap: 서버에 못 붙었다. 오프라인 캐시로 시작한다 (revision=%lld)",
		gNetRevision);

	return NETRESULT_OK;
}

static bool sDirty = false;			//올릴 변경이 쌓여 있는지
static int sHold = 0;				//묶어 보내려고 기다리는 프레임
static int sDirtyAge = 0;			//처음 변경이 생긴 뒤 지난 프레임

//---- 충돌 복구 ----
//저장이 거절되면 서버 것을 다시 받아야 한다. 그 일을 여기서 기억한다.
static bool sNeedReload = false;	//충돌 때문에 다시 받아야 한다
static int sReloadTry = 0;			//다시 받기를 몇 번 실패했나
static int sReloadWait = 0;			//다음 시도까지 남은 프레임
static bool sConflictNotice = false;	//사용자에게 아직 안 알렸다
static int sConflictShow = 0;		//구석에 문구를 띄울 남은 프레임

//다시 받기가 계속 실패할 때 얼마나 기다렸다 또 해볼지.
//바로 다시 하면 서버가 죽어 있을 때 매 프레임 두드린다.
enum {
	NETRELOAD_WAIT = 60 * 3,	//3초
	NETRELOAD_MAXTRY = 5,
	NETCONFLICT_SHOWFRAME = 60 * 6,	//문구를 6초쯤 띄운다
};

void NetInit(void)
{
	sReq = NETREQ_NONE;
	sDelay = 0;
	sSent = false;
	sLastReq = NETREQ_NONE;
	sLastResult = NETRESULT_NONE;
	sBootStep = NETBOOT_NONE;
	sBootResult = NETRESULT_NONE;
	sSaveWait = 0;

	//도는 요청이 있으면 그 답을 버린다. 번호가 바뀌면 콜백이 스스로 물러난다.
	sHttpGen++;
	sHttpState = NETHTTP_IDLE;

	//받는 데 오래 걸리면 포기한다. HttpClient 는 하나짜리라 이 값이
	//콘텐츠 갱신에도 같이 걸린다. 기본값보다 짧지 않으므로 그쪽은 손해가 없다.
	network::HttpClient::getInstance()->setTimeoutForConnect(NET_TIMEOUT_SEC);
	network::HttpClient::getInstance()->setTimeoutForRead(NET_TIMEOUT_SEC);
	sDirty = false;
	sHold = 0;
	sDirtyAge = 0;
	sNeedReload = false;
	sReloadTry = 0;
	sReloadWait = 0;
	sConflictNotice = false;
	sConflictShow = 0;
	sNetBody.clear();

	//gNetTimeOffset 은 일부러 안 지운다. 한 번 서버와 맞춘 시각은 통신 상태와
	//무관하게 계속 맞다. 여기서 0으로 되돌리면 재연결 사이에 시각이 기기
	//시계로 튀었다가 다시 돌아온다. 그 사이에 일일 초기화가 걸리면 곤란하다.
}

bool NetTakeConflictNotice(void)
{
	bool had = sConflictNotice;

	sConflictNotice = false;
	return had;
}

bool NetIsBusy(void)
{
	return sReq != NETREQ_NONE;
}

int NetLastRequest(void)
{
	return sLastReq;
}

int NetLastResult(void)
{
	return sLastResult;
}

//요청 하나를 띄운다. 답은 NETDELAY_MIN~MAX 프레임 뒤에 온다.
bool NetRequest(int reqType)
{
	if (sReq != NETREQ_NONE)
		return false;

	//보낼 것을 지금 만들어 둔다. 답이 올 때까지 robin이 바뀔 수 있으므로
	//전송 시점의 값을 찍어 두어야 한다. 진짜 서버도 이렇게 동작한다.
	if (reqType == NETREQ_SAVE)
		NetBuildDump(sNetBody);

	sReq = reqType;
	sSent = false;
	sLastResult = NETRESULT_NONE;

	//지연은 "기다림을 견디는 코드"를 미리 만들려고 넣은 흉내다. 진짜 서버가
	//붙으면 진짜로 기다리게 되므로 흉내를 얹을 이유가 없다.
	sDelay = UsingServer() ? 0
		: NETDELAY_MIN + Random(NETDELAY_MAX - NETDELAY_MIN + 1);

	return true;
}

void NetMarkDirty(void)
{
	//처음 더러워진 시점만 기록한다. 이어지는 호출로 나이를 되돌리면
	//아래 상한이 영영 안 걸린다.
	if (sDirty == false)
		sDirtyAge = 0;

	sDirty = true;
	sHold = NETSAVE_HOLDFRAME;
}

void NetFlush(void)
{
	sHold = 0;
}

void NetUpdate(void)
{

	//---- 도는 요청 진행 ----
	if (sReq != NETREQ_NONE) {
		if (sDelay > 0) {
			sDelay--;
			return;
		}

		//지연이 다 됐다. 여기가 "서버에 닿는" 순간이다.
		if (!sSent) {
			ServerBegin(sReq, sNetBody);
			sSent = true;
		}

		//진짜 서버면 답이 몇 프레임 뒤에 온다. 그동안 게임은 계속 돈다.
		if (!ServerPoll(sReq, &sLastResult))
			return;


		sSent = false;
		sLastReq = sReq;
		sReq = NETREQ_NONE;

		//---- 저장이 거절됐다 ----
		//
		//다른 기기가 먼저 저장했다는 뜻이다. 이쪽이 들고 있는 revision 이
		//낡았으므로, 그냥 두면 다음 저장도 또 거절당한다. 영영 안 맞는다.
		//
		//서버 것을 다시 받아 덮는 수밖에 없다. 먼저 저장한 쪽을 남기기로
		//정했으니, 이 기기에서 마지막 저장 뒤에 한 일은 사라진다.
		if (sLastResult == NETRESULT_ERR_CONFLICT) {
			CCLOG("NetUpdate: 저장이 거절됐다(다른 기기가 먼저 저장). 서버 것을 받는다");

			sNeedReload = true;
			sReloadTry = 0;
			sReloadWait = 0;

			//보내려고 쌓아둔 것은 버린다. 서버가 안 받은 것이므로 다시
			//보내봐야 또 거절당하고, 곧 서버 것으로 덮일 값이다.
			sDirty = false;
			sHold = 0;
			sDirtyAge = 0;
		}

		//---- 저장을 못 보냈다 ----
		//
		//충돌은 여기가 아니다. 그건 서버가 제대로 답한 것이고 위에서 다뤘다.
		//여기는 못 붙었거나 서버가 잘못된 경우다.
		//
		//SaveGame() 은 더 이상 파일을 쓰지 않는다(Func_System.cpp). 그래서
		//여기서 남기지 않으면 오프라인에서 논 판이 통째로 사라진다.
		if (sLastReq == NETREQ_SAVE) {
			if (sLastResult == NETRESULT_OK) {
				sSaveWait = 0;
			}
			else if (sLastResult != NETRESULT_ERR_CONFLICT) {
				if (ServerWriteFile(SERVERDBFILE, sNetBody))
					CCLOG("NetUpdate: 저장을 못 보냈다. 캐시에 남긴다");
				else
					CCLOG("NetUpdate: 저장도 캐시도 못 했다");

				//다시 보낸다. 보낼 것은 그때 새로 만든다(NetRequest 가 한다).
				//지금 몸통을 그대로 아껴두는 것보다 그 시점의 robin 이 맞다.
				sDirty = true;
				sDirtyAge = 0;
				sSaveWait = NETSAVE_RETRYWAIT;
			}
		}

		//---- 충돌 뒤 다시 받기가 끝났다 ----
		if (sNeedReload && sLastReq == NETREQ_LOAD) {
			if (sLastResult == NETRESULT_OK ||
				sLastResult == NETRESULT_ERR_NOTFOUND) {
				//받아서 덮었다. robin 이 서버 것으로 바뀌었다.
				sNeedReload = false;
				sConflictNotice = true;
				sConflictShow = NETCONFLICT_SHOWFRAME;

				//방금 덮은 것을 도로 올리면 안 된다. 서버와 같은 값이다.
				sDirty = false;
				sHold = 0;
				sDirtyAge = 0;

				CCLOG("NetUpdate: 서버 것으로 되돌렸다 (revision=%lld)", gNetRevision);
			}
			else {
				//못 받았다. 잠시 뒤 다시 해본다. 바로 또 하면 서버가 죽어
				//있을 때 매 프레임 두드린다.
				sReloadTry++;
				sReloadWait = NETRELOAD_WAIT;

				if (sReloadTry >= NETRELOAD_MAXTRY) {
					//그만 둔다. 다음에 저장할 일이 생기면 또 거절당하고
					//여기로 돌아온다. 그때 다시 해보면 된다.
					sNeedReload = false;
					CCLOG("NetUpdate: 서버 것을 %d번 못 받았다. 나중에 다시 한다",
						sReloadTry);
				}
			}
		}

		//---- 부팅 한 걸음 ----
		//로그인이 끝났으면 이어서 로드를 띄운다. 둘 다 끝나야 게임이 뜬다.
		if (sBootStep == NETBOOT_LOGIN && sLastReq == NETREQ_LOGIN) {
			if (sLastResult == NETRESULT_OK) {
				sBootStep = NETBOOT_LOAD;
				NetRequest(NETREQ_LOAD);
			}
			else {
				sBootResult = NetBootFallback(sLastResult);
				sBootStep = NETBOOT_DONE;
			}
		}
		else if (sBootStep == NETBOOT_LOAD && sLastReq == NETREQ_LOAD) {
			sBootResult = (sLastResult == NETRESULT_OK)
				? NETRESULT_OK : NetBootFallback(sLastResult);
			sBootStep = NETBOOT_DONE;
		}

		return;
	}

	//---- 충돌 때문에 다시 받아야 한다 ----
	//저장보다 먼저 한다. 낡은 revision 으로 또 보내봐야 거절만 당한다.
	if (sNeedReload) {
		if (sReloadWait > 0) {
			sReloadWait--;
			return;
		}

		NetRequest(NETREQ_LOAD);
		return;
	}

	//---- 쌓인 저장 내보내기 ----
	if (sDirty == false)
		return;

	//못 보내서 다시 해보는 중이면 기다린다.
	if (sSaveWait > 0) {
		sSaveWait--;
		return;
	}

	sDirtyAge++;

	//잠잠해지길 기다린다. 다만 계속 시끄러우면(전투 중 SaveGame()이 연달아
	//불리는 경우) 영영 못 보내므로 상한을 둔다.
	if (sHold > 0 && sDirtyAge < NETSAVE_MAXHOLDFRAME) {
		sHold--;
		return;
	}

	if (NetRequest(NETREQ_SAVE)) {
		sDirty = false;
		sDirtyAge = 0;
	}
}

//부팅을 띄운다. 곧바로 돌아온다.
//
//임시 서버(NET_SERVER_URL 이 비었을 때)는 파일이라 그 자리에서 끝난다.
//예전과 똑같이 동작한다. 진짜 서버면 로그인과 로드가 각각 답을 기다리므로
//NetBootstrapPoll() 이 NETRESULT_NONE 을 주는 동안 부르는 쪽이 기다려야 한다.
void NetBootstrapBegin(void)
{
	NetInit();

	if (!UsingServer()) {
		sBootResult = ServerLogin();

		if (sBootResult == NETRESULT_OK)
			sBootResult = ServerLoad();

		sBootStep = NETBOOT_DONE;
		return;
	}

	sBootStep = NETBOOT_LOGIN;
	sBootResult = NETRESULT_NONE;

	NetRequest(NETREQ_LOGIN);
}

//부팅이 끝났으면 결과를, 아직이면 NETRESULT_NONE 을 준다.
//NetUpdate() 가 돌아야 진행된다.
int NetBootstrapPoll(void)
{
	return sBootStep == NETBOOT_DONE ? sBootResult : NETRESULT_NONE;
}

//통신 중이라는 표시. 지연이 눈에 보여야 "기다리는 화면"을 만들 생각을 한다.
void NetIndicatorDraw(void)
{
	float w = 56 * _2X;
	float h = 14 * _2X;
	float x = DX - w - 4 * _2X;
	float y = DY - 4 * _2X;
	int dot;

	//---- 충돌로 되돌렸다는 알림 ----
	//진행이 사라진 것이라 조용히 넘기면 안 된다. 잠시 띄운다.
	//게임 쪽에서 제대로 된 팝업을 붙이면 NetTakeConflictNotice()로 가져가고
	//여기는 안 뜬다.
	if (sConflictShow > 0) {
		float bw = 200 * _2X;
		float bh = 16 * _2X;
		float bx = DX / 2 - bw / 2;
		float by = DY - 24 * _2X;

		sConflictShow--;

		SetAlpha(26);
		MemRect(bx, by, bw, bh, COLOR_BLACK);
		SetAlpha(32);

		SetFontColor(COLOR_WHITE);
		CenterText(TEXT_NET_CONFLICT, DX / 2, by - 3 * _2X, 1.0f);
		SetFontColor(COLOR_WHITE);
	}

	if (sReq == NETREQ_NONE)
		return;

	SetAlpha(24);
	MemRect(x, y, w, h, COLOR_BLACK);
	SetAlpha(32);

	//점 세 개가 도는 것으로 "가는 중"을 보여준다.
	dot = (frame / 10) % 4;

	SetFontColor(COLOR_WHITE);

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s%.*s", sReq == NETREQ_SAVE ? "SAVE" : "NET", dot, "...");

	DrawTextStrSystem(tempStr, x + 4 * _2X, y - 2 * _2X, 1.0f, LEFT, false);
	SetFontColor(COLOR_WHITE);
}
