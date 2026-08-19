-- =============================================================================
-- 인삼남 서버 스키마 (MariaDB 10.6+)
--
-- 이 파일이 서버와 클라이언트가 주고받는 데이터의 기준이다.
--
-- 서버가 아직 없는 동안에는 클라이언트 안의 임시 서버가 이 스키마를 파일로
-- 흉내낸다. 그 파일 형식은 server/dumpformat.md 에 적혀 있고, MariaDB의
-- LOAD DATA INFILE이 그대로 읽을 수 있는 형태다. 즉 지금 만드는 파일이
-- 나중에 그대로 이 표들로 들어간다.
--
-- -----------------------------------------------------------------------------
-- 왜 통짜 세이브를 버리는가
-- -----------------------------------------------------------------------------
-- 지금 클라이언트는 ROBINDATA 구조체를 통째로 memcpy해서 save.dat에 쓴다.
-- 그 파일이 1.1MB다. SaveGame()이 32곳에서 불리므로 그대로 서버에 보내면
-- 저장 한 번에 1.1MB가 오간다. 어떤 서버도 못 버틴다.
--
-- 용량의 대부분은 ROBINDATA 안의 고정 배열 두 개다.
--   - OBJECT enemyObj[MAXENEMY * MAXENEMYOBJ]  (250개)
--     OBJECT 하나에 signed char skillLv[TOTAL_SKILL](=1787바이트)와
--     ITEM equip[TOTALEQUIP]가 통째로 들어 있다. 몬스터에게는 쓸모없는 값이다.
--   - ITEM inven[500]  실제 보유량과 상관없이 항상 500칸
--
-- 테이블로 쪼개면 "가진 것만 행"이 되어 수 KB로 떨어진다.
-- 덤으로 ROBINDATA 안의 std::string(닉네임, OBJECT마다 하나씩 총 251개) 문제도
-- 사라진다. 지금은 구조체 통짜 memcpy라 문자열 내용이 아니라 힙 포인터가
-- 파일에 저장되고 있다.
--
-- -----------------------------------------------------------------------------
-- 저장 규약 : 나중 것을 거절한다 (optimistic locking)
-- -----------------------------------------------------------------------------
--   1) 클라이언트는 마지막으로 받은 player.revision을 저장 요청에 같이 보낸다.
--   2) 서버는 한 트랜잭션 안에서 먼저 이것을 실행한다.
--
--        UPDATE player
--           SET ..., revision = revision + 1, updated_at = NOW()
--         WHERE user_id = ? AND revision = ?
--
--   3) 영향받은 행이 0이면 다른 기기가 먼저 저장한 것이다.
--      ROLLBACK 하고 409 CONFLICT로 거절한다. 나중에 온 저장은 버린다.
--   4) 1행이면 나머지 테이블을 같은 트랜잭션 안에서 갱신하고 COMMIT한다.
--
--   즉 revision은 player 한 곳에만 둔다. 테이블마다 두면 부분 성공이 생긴다.
--
-- -----------------------------------------------------------------------------
-- 규칙
-- -----------------------------------------------------------------------------
--   - 시간 컬럼이 두 종류다.
--       *_ts       : 게임 안 타임스탬프(BIGINT). MC_knlCurrentTimeStamp()가 주는
--                    2000-01-01 00:00:00부터의 초. 게임 로직이 이 값으로 계산한다.
--       *_at       : 운영용 DATETIME. 사람이 보고 지표를 뽑는 용도.
--     게임 로직은 *_ts만 본다. 둘을 섞지 않는다.
--   - 밸런스표(Classes/Data/*.h)는 여기 넣지 않는다. 그건 콘텐츠 데이터라
--     별도 문제이고, 섞으면 둘 다 꼬인다.
--   - 열거값을 쓰는 컬럼은 주석에 대응하는 C 열거 이름을 적는다.
--     스키마가 코드보다 오래 살아남으므로 이름이 남아 있어야 한다.
-- =============================================================================

SET NAMES utf8mb4;

-- =============================================================================
-- 1. 계정
-- =============================================================================

CREATE TABLE account (
    user_id       BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
    -- 기기가 처음 실행될 때 만드는 UUID. 게스트 로그인의 유일한 열쇠다.
    -- 이것만으로 로그인되므로 유출되면 계정을 통째로 잃는다.
    -- 정식 서비스에서는 이 값 대신 서버가 발급한 토큰으로 붙어야 한다.
    guest_key     CHAR(36)        NOT NULL,
    created_at    DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,
    last_login_at DATETIME        NULL,
    -- NULL이면 정상. 값이 있으면 그 시각까지 접속 차단.
    banned_until  DATETIME        NULL,
    PRIMARY KEY (user_id),
    UNIQUE KEY uq_account_guest (guest_key)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 플랫폼 연동. 한 계정에 구글과 애플이 동시에 붙을 수 있다.
CREATE TABLE account_link (
    user_id      BIGINT UNSIGNED  NOT NULL,
    -- LoginDef.h의 VERIFY_GOOGLE / VERIFY_APPLE / VERIFY_FACEBOOK / VERIFY_KAKAO
    provider     TINYINT UNSIGNED NOT NULL,
    provider_uid VARCHAR(191)     NOT NULL,
    linked_at    DATETIME         NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (user_id, provider),
    -- 같은 구글 계정이 두 유저에 붙는 것을 막는다.
    UNIQUE KEY uq_link_provider (provider, provider_uid),
    CONSTRAINT fk_link_account FOREIGN KEY (user_id)
        REFERENCES account (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- =============================================================================
-- 2. 플레이어 본체
--
-- ROBINDATA에서 배열이 아닌 스칼라 필드들이 전부 여기로 온다.
-- revision이 이 표에만 있는 것이 중요하다. 위의 저장 규약 참고.
-- =============================================================================

CREATE TABLE player (
    user_id            BIGINT UNSIGNED NOT NULL,
    -- 저장할 때마다 1씩 오른다. 충돌 판정의 기준.
    revision           BIGINT UNSIGNED NOT NULL DEFAULT 1,

    nickname           VARCHAR(24)     NOT NULL DEFAULT '',
    lv                 INT             NOT NULL DEFAULT 1,
    exps               INT             NOT NULL DEFAULT 0,

    -- 재화. 전부 long long이라 BIGINT로 받는다.
    -- Phase 2에서 서버 권위로 넘어가면 클라이언트는 이 값을 제안만 하고
    -- 실제 증감은 서버가 계산한다.
    gold               BIGINT          NOT NULL DEFAULT 0,
    heart              BIGINT          NOT NULL DEFAULT 0,
    medal              BIGINT          NOT NULL DEFAULT 0,
    star               BIGINT          NOT NULL DEFAULT 0,
    hammer             BIGINT          NOT NULL DEFAULT 0,
    coin               BIGINT          NOT NULL DEFAULT 0,
    shield             INT             NOT NULL DEFAULT 0,

    -- 진행도
    castle             SMALLINT        NOT NULL DEFAULT 0,
    stage              SMALLINT        NOT NULL DEFAULT 0,
    room               SMALLINT        NOT NULL DEFAULT 0,
    -- robin.bossRoom : 0 일반방, 1 보스방, 2 골드이벤트
    boss_room          TINYINT         NOT NULL DEFAULT 0,
    max_inven          SMALLINT UNSIGNED NOT NULL DEFAULT 0,
    max_status_cnt     INT             NOT NULL DEFAULT 0,
    playtime           INT             NOT NULL DEFAULT 0,
    event_cnt          INT             NOT NULL DEFAULT 0,

    -- 새 룰렛 시스템
    current_day        INT             NOT NULL DEFAULT 0,
    life_remaining     INT             NOT NULL DEFAULT 0,

    -- 가챠 천장. 5성 이상이 안 나온 횟수.
    crew_miss_cnt      INT             NOT NULL DEFAULT 0,
    equip_miss_cnt     INT             NOT NULL DEFAULT 0,

    -- 게임 안 타임스탬프(초). 기기 시계가 아니라 서버 시각으로 채워야 한다.
    -- 지금 클라이언트는 MC_knlCurrentTimeStamp()로 기기 시계를 쓰고 있어서
    -- 비행기 모드 + 시계 조작으로 하트 충전과 일일보상이 뚫린다.
    start_ts           BIGINT          NOT NULL DEFAULT 0,
    heart_ts           BIGINT          NOT NULL DEFAULT 0,
    free_reward_ts     BIGINT          NOT NULL DEFAULT 0,
    calendar_ts        BIGINT          NOT NULL DEFAULT 0,
    calendar_month_day INT             NOT NULL DEFAULT 0,

    created_at         DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at         DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP
                                       ON UPDATE CURRENT_TIMESTAMP,

    PRIMARY KEY (user_id),
    CONSTRAINT fk_player_account FOREIGN KEY (user_id)
        REFERENCES account (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 성별 최고 진행도. robin.maxStage[TOTALCASTLE] / maxRoom[TOTALCASTLE]
CREATE TABLE player_castle (
    user_id    BIGINT UNSIGNED  NOT NULL,
    castle_idx TINYINT UNSIGNED NOT NULL,  -- CastleDef.h의 성 인덱스
    max_stage  SMALLINT         NOT NULL DEFAULT 0,
    max_room   SMALLINT         NOT NULL DEFAULT 0,
    PRIMARY KEY (user_id, castle_idx),
    CONSTRAINT fk_pcastle_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 켜짐/꺼짐 계열을 한 표에 모은다. 켜진 것만 행으로 넣는다.
-- 배열 전체를 넣으면 demoSeen[TOTALDEMO] + equipGet[ITEM_GEM_START]만으로도
-- 수백 행이 되는데, 대부분 0이라 낭비다.
CREATE TABLE player_flag (
    user_id   BIGINT UNSIGNED  NOT NULL,
    -- 0 = demoSeen (본 연출)
    -- 1 = openedMenu (열린 메뉴)
    -- 2 = statue (세운 석상)
    -- 3 = equipGet (도감 등록된 장비)
    flag_kind TINYINT UNSIGNED NOT NULL,
    flag_idx  SMALLINT UNSIGNED NOT NULL,
    -- openedMenu는 unsigned char라 0/1이 아닐 수 있어 값을 그대로 담는다.
    value     TINYINT UNSIGNED NOT NULL DEFAULT 1,
    PRIMARY KEY (user_id, flag_kind, flag_idx),
    CONSTRAINT fk_pflag_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 소모품 보유량. robin.buffItem[TOTAL_WASTE]
CREATE TABLE player_consumable (
    user_id   BIGINT UNSIGNED   NOT NULL,
    waste_idx SMALLINT UNSIGNED NOT NULL,  -- ITEM_WASTE_* 인덱스
    cnt       INT               NOT NULL DEFAULT 0,
    PRIMARY KEY (user_id, waste_idx),
    CONSTRAINT fk_pcons_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- =============================================================================
-- 3. 인벤토리
--
-- 지금 인벤은 ITEM inven[500] 고정 배열이고, GetInvenIdx(type, detail, grade)로
-- 한 칸을 찾는다. 즉 (종류, 세부, 등급)이 같으면 한 칸에 개수로 쌓인다.
-- 그래서 그 셋을 UNIQUE로 잡는다.
-- =============================================================================

CREATE TABLE inventory (
    item_uid  BIGINT UNSIGNED   NOT NULL AUTO_INCREMENT,
    user_id   BIGINT UNSIGNED   NOT NULL,
    item_type TINYINT UNSIGNED  NOT NULL,  -- ITEM_SWORD .. ITEM_CREW 등
    detail    SMALLINT UNSIGNED NOT NULL,
    grade     TINYINT UNSIGNED  NOT NULL,  -- GRADE_NORMAL ..
    lv        TINYINT UNSIGNED  NOT NULL DEFAULT 0,  -- 0이면 미획득(도감에만 보임)
    cnt       INT UNSIGNED      NOT NULL DEFAULT 0,  -- 동료는 조각 수
    cooldown  SMALLINT UNSIGNED NOT NULL DEFAULT 0,  -- 장비는 강화 단계
    exp       INT               NOT NULL DEFAULT 0,
    seen      TINYINT UNSIGNED  NOT NULL DEFAULT 0,  -- 상세정보를 본 적 있는지
    PRIMARY KEY (item_uid),
    UNIQUE KEY uq_inventory (user_id, item_type, detail, grade),
    CONSTRAINT fk_inv_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- ITEM.option[12][2] 을 펼친 것. 붙어 있는 옵션만 행으로 넣는다.
CREATE TABLE inventory_option (
    item_uid  BIGINT UNSIGNED  NOT NULL,
    slot      TINYINT UNSIGNED NOT NULL,  -- 0 .. 11
    opt_type  INT              NOT NULL,
    opt_value INT              NOT NULL,
    PRIMARY KEY (item_uid, slot),
    CONSTRAINT fk_invopt_item FOREIGN KEY (item_uid)
        REFERENCES inventory (item_uid) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- ITEM.socket[6] 을 펼친 것. 보석이 박힌 소켓만 행으로 넣는다.
CREATE TABLE inventory_socket (
    item_uid BIGINT UNSIGNED  NOT NULL,
    slot     TINYINT UNSIGNED NOT NULL,  -- 0 .. MAXSOCKET-1
    gem      INT              NOT NULL,
    PRIMARY KEY (item_uid, slot),
    CONSTRAINT fk_invsock_item FOREIGN KEY (item_uid)
        REFERENCES inventory (item_uid) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- =============================================================================
-- 4. 히어로 (로빈 / 디아나 / 맥스)
-- ROBINDATA.charData[TOTALPLAYER] + heroesSetting[TOTALCHAR]
-- =============================================================================

CREATE TABLE hero (
    user_id  BIGINT UNSIGNED  NOT NULL,
    hero_idx TINYINT UNSIGNED NOT NULL,  -- ROBIN=0, DIANA=1, MAXX=2
    is_set   TINYINT UNSIGNED NOT NULL DEFAULT 0,  -- heroesSetting[]
    exps     INT              NOT NULL DEFAULT 0,
    hp       BIGINT           NOT NULL DEFAULT 0,
    mp       INT              NOT NULL DEFAULT 0,
    ap       SMALLINT UNSIGNED NOT NULL DEFAULT 0,
    sp       TINYINT UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY (user_id, hero_idx),
    CONSTRAINT fk_hero_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 무엇을 입고 있는지.
--
-- 인벤의 행을 FK로 가리키게 하고 싶지만 지금 게임은 그렇게 돌지 않는다.
-- EquipItem()이 인벤 항목을 pObj->equip[slot]로 memcpy만 하고 인벤에서
-- 지우지는 않는다(지우는 코드가 통째로 주석 처리돼 있다). 즉 장착품은
-- 인벤 항목의 사본이고, 같은 장비를 세 히어로가 동시에 입을 수도 있다.
--
-- 그래서 FK 대신 (종류, 세부, 등급)을 그대로 적는다. 인벤이 그 셋으로
-- UNIQUE라서 사실상 자연키 역할을 한다. 나중에 "장착하면 인벤에서 뺀다"로
-- 바꾸면 그때 item_uid FK로 옮기면 된다.
CREATE TABLE hero_equip (
    user_id   BIGINT UNSIGNED   NOT NULL,
    hero_idx  TINYINT UNSIGNED  NOT NULL,
    slot      TINYINT UNSIGNED  NOT NULL,  -- EQUIP_WEAPON .. EQUIP_RING
    item_type TINYINT UNSIGNED  NOT NULL,
    detail    SMALLINT UNSIGNED NOT NULL,
    grade     TINYINT UNSIGNED  NOT NULL,
    lv        TINYINT UNSIGNED  NOT NULL DEFAULT 0,
    cooldown  SMALLINT UNSIGNED NOT NULL DEFAULT 0,  -- 강화 단계
    PRIMARY KEY (user_id, hero_idx, slot),
    CONSTRAINT fk_hequip_hero FOREIGN KEY (user_id, hero_idx)
        REFERENCES hero (user_id, hero_idx) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- CHARDATA.hotKey[MAXHOTKEY]
CREATE TABLE hero_hotkey (
    user_id  BIGINT UNSIGNED  NOT NULL,
    hero_idx TINYINT UNSIGNED NOT NULL,
    slot     TINYINT UNSIGNED NOT NULL,  -- 0 .. MAXHOTKEY-1
    hk_type  TINYINT UNSIGNED NOT NULL,  -- HOTKEY_SKILL 등
    hk_idx   INT              NOT NULL,
    PRIMARY KEY (user_id, hero_idx, slot),
    CONSTRAINT fk_hhotkey_hero FOREIGN KEY (user_id, hero_idx)
        REFERENCES hero (user_id, hero_idx) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- CHARDATA.skillLv[TOTAL_SKILL]. TOTAL_SKILL이 1787이라 전부 넣으면
-- 유저 한 명당 5361행이 된다. 0이 아닌 것만 넣는다.
CREATE TABLE hero_skill (
    user_id   BIGINT UNSIGNED   NOT NULL,
    hero_idx  TINYINT UNSIGNED  NOT NULL,
    skill_idx SMALLINT UNSIGNED NOT NULL,  -- SKILL_COMMON_ROBIN1 ..
    skill_lv  TINYINT           NOT NULL,
    PRIMARY KEY (user_id, hero_idx, skill_idx),
    CONSTRAINT fk_hskill_hero FOREIGN KEY (user_id, hero_idx)
        REFERENCES hero (user_id, hero_idx) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- CHARDATA.getSkillList[MAXCHARSKILL]. 배운 스킬을 어느 칸에 꽂아뒀는지.
CREATE TABLE hero_skill_slot (
    user_id   BIGINT UNSIGNED   NOT NULL,
    hero_idx  TINYINT UNSIGNED  NOT NULL,
    slot      TINYINT UNSIGNED  NOT NULL,  -- 0 .. MAXCHARSKILL-1
    skill_idx SMALLINT UNSIGNED NOT NULL,
    PRIMARY KEY (user_id, hero_idx, slot),
    CONSTRAINT fk_hsslot_hero FOREIGN KEY (user_id, hero_idx)
        REFERENCES hero (user_id, hero_idx) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- =============================================================================
-- 5. 동료 편성
-- robin.slotCrew[MAXCREW]. -1(빈 칸)은 행을 만들지 않는다.
-- =============================================================================

CREATE TABLE crew_slot (
    user_id   BIGINT UNSIGNED   NOT NULL,
    slot      TINYINT UNSIGNED  NOT NULL,  -- 0 .. MAXCREW-1
    crew_type SMALLINT UNSIGNED NOT NULL,  -- NPC_* (EnemyDef.h)
    PRIMARY KEY (user_id, slot),
    CONSTRAINT fk_crewslot_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- =============================================================================
-- 6. 퀘스트 / 이벤트 / 출석
-- =============================================================================

-- 일반 퀘스트와 PVP 퀘스트가 필드 구성이 같아서 kind로 나눈다.
CREATE TABLE quest_progress (
    user_id        BIGINT UNSIGNED  NOT NULL,
    kind           TINYINT UNSIGNED NOT NULL,  -- 0 = 일반, 1 = PVP
    quest          INT              NOT NULL DEFAULT 0,
    sub_quest      INT              NOT NULL DEFAULT 0,
    detail_quest   INT              NOT NULL DEFAULT 0,  -- PVP만 씀
    cnt            INT              NOT NULL DEFAULT 0,
    started_ts     BIGINT           NOT NULL DEFAULT 0,
    remain_item    BIGINT           NOT NULL DEFAULT 0,
    this_time_item BIGINT           NOT NULL DEFAULT 0,
    PRIMARY KEY (user_id, kind),
    CONSTRAINT fk_quest_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- robin.gameEvent[MAXGAMEEVENT]
--
-- GAMEEVENT 구조체의 절반 이상(x, y, dx, dy, speed, zoom, frame, touchFunc ...)은
-- 화면에서 바가 튀어나오는 연출 상태다. 저장할 이유가 없어서 넣지 않는다.
-- 남기는 것은 "무슨 이벤트가 언제 시작해서 얼마나 남았는가"뿐이다.
CREATE TABLE game_event (
    user_id    BIGINT UNSIGNED  NOT NULL,
    slot       TINYINT UNSIGNED NOT NULL,  -- 0 .. MAXGAMEEVENT-1
    ev_type    TINYINT UNSIGNED NOT NULL,  -- EVENTTYPE_QUEST / _PVP / _SHOP
    sub_type   TINYINT UNSIGNED NOT NULL DEFAULT 0,
    icon       SMALLINT         NOT NULL DEFAULT 0,
    started_ts BIGINT           NOT NULL DEFAULT 0,
    limit_sec  INT              NOT NULL DEFAULT 0,
    status     TINYINT UNSIGNED NOT NULL DEFAULT 0,  -- EVENT_OPEN/_DOING/_CLOSE
    bar_status TINYINT UNSIGNED NOT NULL DEFAULT 0,  -- EVENT_BAR_*
    PRIMARY KEY (user_id, slot),
    CONSTRAINT fk_gevent_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- robin.calendarDayStatus[WEEK]
CREATE TABLE calendar_day (
    user_id  BIGINT UNSIGNED  NOT NULL,
    day_idx  TINYINT UNSIGNED NOT NULL,  -- 0 .. WEEK-1
    status   INT              NOT NULL DEFAULT 0,
    PRIMARY KEY (user_id, day_idx),
    CONSTRAINT fk_calday_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- =============================================================================
-- 7. 전투 세션 (이어하기)
--
-- 체력 높은 적 하나와 텀을 두고 싸우는 구조라 전투 상태가 살아남아야 한다.
--
-- 다만 OBJECT 250개를 통째로 저장할 필요는 없다. 복원하는 CopyEnemyObj()가
-- 어차피 x/y를 nx/ny로 되돌리고 turn / turnPosition / 각종 frame을 0으로
-- 리셋한다. 즉 위치와 애니메이션 상태는 저장해도 버려진다.
-- 실제로 살아남아야 하는 것만 컬럼으로 둔다.
-- =============================================================================

CREATE TABLE battle_session (
    user_id        BIGINT UNSIGNED NOT NULL,
    wave_idx       INT             NOT NULL DEFAULT 0,
    cur_wave_idx   INT             NOT NULL DEFAULT 0,
    wave_ts        BIGINT          NOT NULL DEFAULT 0,
    enemy_user_idx INT             NOT NULL DEFAULT 0,  -- PVP 상대 인덱스
    updated_at     DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP
                                   ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (user_id),
    CONSTRAINT fk_bsession_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE battle_enemy (
    user_id    BIGINT UNSIGNED   NOT NULL,
    -- ao[] 배열에서 ENEMY를 뺀 값. 0 .. MAXENEMY*MAXENEMYOBJ-1
    -- 살아 있는 놈만 행으로 넣는다. 보통 몇 마리뿐이다.
    slot       SMALLINT UNSIGNED NOT NULL,
    -- 몸통이 여러 오브젝트로 쪼개진 보스(용 머리/몸통/팔 등)는 mom이 대표 slot을 가리킨다.
    mom        SMALLINT UNSIGNED NOT NULL,

    enemy_type SMALLINT UNSIGNED NOT NULL,  -- ENEMY_* (EnemyDef.h)
    cmf        SMALLINT UNSIGNED NOT NULL,

    hp         BIGINT            NOT NULL,
    max_hp     BIGINT            NOT NULL,
    -- OBJECT.status / OBJECT.etc. 몬스터 행동 패턴이 이 둘로 갈린다.
    status     TINYINT           NOT NULL DEFAULT 0,
    etc        INT               NOT NULL DEFAULT 0,

    -- 원래 서 있던 자리. 복원할 때 x/y가 이 값으로 되돌아간다.
    nx         INT               NOT NULL DEFAULT 0,
    ny         INT               NOT NULL DEFAULT 0,
    dir_f      TINYINT           NOT NULL DEFAULT 0,

    lv         INT               NOT NULL DEFAULT 0,
    str        BIGINT            NOT NULL DEFAULT 0,
    def        BIGINT            NOT NULL DEFAULT 0,
    attr       SMALLINT UNSIGNED NOT NULL DEFAULT 0,

    -- 스킬 쿨다운. 이걸 안 살리면 재접속으로 보스 스킬을 무한히 피할 수 있다.
    skill_idx  TINYINT UNSIGNED  NOT NULL DEFAULT 0,
    cur_skill  INT               NOT NULL DEFAULT 0,
    cool_time  BIGINT            NOT NULL DEFAULT 0,

    target     SMALLINT UNSIGNED NOT NULL DEFAULT 0,
    dead       TINYINT           NOT NULL DEFAULT 0,

    PRIMARY KEY (user_id, slot),
    CONSTRAINT fk_benemy_session FOREIGN KEY (user_id)
        REFERENCES battle_session (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- OBJECT.buff[TOTALBUFF] / debuf[TOTALDEBUF]. 걸려 있는 것만 행으로 넣는다.
-- 이걸 빼면 재접속으로 독과 기절이 풀린다.
CREATE TABLE battle_enemy_effect (
    user_id  BIGINT UNSIGNED   NOT NULL,
    slot     SMALLINT UNSIGNED NOT NULL,
    kind     TINYINT UNSIGNED  NOT NULL,  -- 0 = buff, 1 = debuf
    eff_idx  SMALLINT UNSIGNED NOT NULL,
    remain   INT               NOT NULL,  -- 남은 프레임/횟수
    owner    TINYINT UNSIGNED  NOT NULL DEFAULT 0,  -- 건 사람
    PRIMARY KEY (user_id, slot, kind, eff_idx),
    CONSTRAINT fk_beffect_enemy FOREIGN KEY (user_id, slot)
        REFERENCES battle_enemy (user_id, slot) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- =============================================================================
-- 8. PVP (내 집 스냅샷)
--
-- 다른 유저가 쳐들어올 때 보는 내 편성. HOUSE 구조체가 이미 userId /
-- userName / userProfileImgIdx를 들고 있어서 처음부터 서버를 전제로 설계돼 있다.
-- 지금은 aiUserData / aiUserHouse로 로컬 AI가 그 자리를 채우고 있다.
-- =============================================================================

CREATE TABLE pvp_house (
    user_id     BIGINT UNSIGNED  NOT NULL,
    house_type  TINYINT UNSIGNED NOT NULL DEFAULT 0,
    profile_img BIGINT           NOT NULL DEFAULT 0,
    -- 쳐들어온 상대가 이기면 가져갈 수 있는 골드
    gold        BIGINT           NOT NULL DEFAULT 0,
    updated_at  DATETIME         NOT NULL DEFAULT CURRENT_TIMESTAMP
                                 ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY (user_id),
    -- 매칭할 때 비슷한 전력끼리 붙이려면 이 값으로 찾는다.
    KEY idx_pvp_gold (gold),
    CONSTRAINT fk_pvphouse_player FOREIGN KEY (user_id)
        REFERENCES player (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

CREATE TABLE pvp_house_crew (
    user_id   BIGINT UNSIGNED   NOT NULL,
    slot      TINYINT UNSIGNED  NOT NULL,  -- 0 .. MAXCREW-1
    crew_type SMALLINT UNSIGNED NOT NULL,
    cur_star  TINYINT UNSIGNED  NOT NULL DEFAULT 0,
    max_star  TINYINT UNSIGNED  NOT NULL DEFAULT 0,
    PRIMARY KEY (user_id, slot),
    CONSTRAINT fk_pvpcrew_house FOREIGN KEY (user_id)
        REFERENCES pvp_house (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- HOUSE.equipImg[TOTALCHAR][TOTALEQUIP]. 남에게 보이는 겉모습.
CREATE TABLE pvp_house_look (
    user_id  BIGINT UNSIGNED  NOT NULL,
    hero_idx TINYINT UNSIGNED NOT NULL,
    slot     TINYINT UNSIGNED NOT NULL,
    img      TINYINT UNSIGNED NOT NULL,
    PRIMARY KEY (user_id, hero_idx, slot),
    CONSTRAINT fk_pvplook_house FOREIGN KEY (user_id)
        REFERENCES pvp_house (user_id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- =============================================================================
-- 10. 운영
-- =============================================================================

-- 저장이 거절된 기록. 충돌이 잦으면 클라이언트 쪽 저장 시점이 잘못된 것이다.
CREATE TABLE save_conflict_log (
    seq          BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
    user_id      BIGINT UNSIGNED NOT NULL,
    sent_rev     BIGINT UNSIGNED NOT NULL,  -- 클라가 보낸 revision
    server_rev   BIGINT UNSIGNED NOT NULL,  -- 서버가 들고 있던 revision
    device_hint  VARCHAR(64)     NULL,
    created_at   DATETIME        NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (seq),
    KEY idx_conflict_user (user_id, created_at)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 스키마 버전. 마이그레이션의 기준점.
CREATE TABLE schema_version (
    version    INT      NOT NULL,
    applied_at DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (version)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

INSERT INTO schema_version (version) VALUES (1);
