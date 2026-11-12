#pragma once
#include "Def/BoardDef.h"

//==========================================================================
// 룰렛 × 합성 판 — 순수 모델
//
// cocos · ao[] · crewData 를 모른다. 난수는 함수 포인터로 받는다. 그래서
// tools/board/test_board_model.cpp 가 cl 하나로 컴파일해 돌린다.
// 게임 쪽(Func_Board.cpp, 다음 단계)은 이 모델의 결과를 turnList 와 연출로
// 옮기기만 한다. 규칙이 사는 곳은 여기 한 군데다.
//==========================================================================
namespace MergeBoard {

typedef int (*RandomFn)(int bound);	//0 <= r < bound

//---- 크기 ----
//2026-11-10 결정: "사람은 한 칸, 장비는 커진다."
//2026-11-11 고침: 사람은 1×2 다. 한 칸에 넣으면 사람 그림의 세로에 맞춰
//  줄어들어 칸 폭이 반도 안 찼다 - 누군지 알아볼 수가 없었다. 세로 두 칸이면
//  폭을 꽉 채우고 선다. ★ 가 올라도 크기는 그대로 1×2 - 사람이 커지는 그림은
//  여전히 어색하다. 합치면 두 칸이 준다.
//2026-11-11 다시 고침: 장비의 칸 모양은 손으로 적지 않는다. 여기 ★2 = 2×1
//  표가 있어서 투구 ★2 가 두 칸을 먹었는데 그림은 1×1 이라 칸 가운데 떠
//  있었다 - 칸과 그림이 다른 표를 봤다. 칸 모양은 그림이 정한다(GridGearPart,
//  CLAUDE.md §9-3). 판은 순수 모델이라 그림을 모르므로 게임이 런을 열 때
//  SetGearShape 로 채운다. 채우기 전은 전부 1×1 - 테스트가 그 값을 쓴다.
//  그래서 커지는 것은 무기뿐이다(검 1×2 → 1×3 → 1×4, 부메랑 2×2). 투구·갑옷·
//  목걸이는 ★ 이 올라도 1×1 에 테두리 색과 코스튬만 바뀐다.
//  세기: 칸이 느는 단은 ×3(1+1 이 2칸이 되니 3배여야 칸당 화력이 는다),
//  칸이 그대로인 단은 ×2(동료와 같다). GearMulOf 가 단마다 가른다.
struct GearShapeTable { signed char w[BOARD_GEAR_SLOTS][BLOCK_LV_MAX + 1]; signed char h[BOARD_GEAR_SLOTS][BLOCK_LV_MAX + 1]; };
inline void ResetGearShapes(GearShapeTable& t) { for (int s = 0; s < BOARD_GEAR_SLOTS; s++) for (int l = 0; l <= BLOCK_LV_MAX; l++) { t.w[s][l] = (signed char)(l >= 1 ? 1 : 0); t.h[s][l] = (signed char)(l >= 1 ? 1 : 0); } }
inline GearShapeTable& GearShapes() { static GearShapeTable t; static bool init = false; if (!init) { init = true; ResetGearShapes(t); } return t; }
inline void ResetGearShapes() { ResetGearShapes(GearShapes()); }
inline void SetGearShape(int slot, int level, int w, int h) { if (slot < 0 || slot >= BOARD_GEAR_SLOTS || level < 1 || level > BLOCK_LV_MAX || w < 1 || h < 1) return; GearShapes().w[slot][level] = (signed char)w; GearShapes().h[slot][level] = (signed char)h; }
inline int GearW(int slot, int level) { return (slot < 0 || slot >= BOARD_GEAR_SLOTS || level < 1 || level > BLOCK_LV_MAX) ? 0 : GearShapes().w[slot][level]; }
inline int GearH(int slot, int level) { return (slot < 0 || slot >= BOARD_GEAR_SLOTS || level < 1 || level > BLOCK_LV_MAX) ? 0 : GearShapes().h[slot][level]; }
inline int GearCells(int slot, int level) { return GearW(slot, level) * GearH(slot, level); }
//종류(LineageKind)로 묻는 호출부: 장비 종류는 LINEAGE_SWORD 부터 차례로 표의 줄이다.
inline int BlockWOf(int kind, int level) { return kind == LINEAGE_CREW ? (level >= 1 && level <= BLOCK_LV_MAX ? 1 : 0) : GearW(kind - LINEAGE_SWORD, level); }
inline int BlockHOf(int kind, int level) { return kind == LINEAGE_CREW ? (level >= 1 && level <= BLOCK_LV_MAX ? 2 : 0) : GearH(kind - LINEAGE_SWORD, level); }
inline int BlockCellsOf(int kind, int level) { return BlockWOf(kind, level) * BlockHOf(kind, level); }
//호환용: 종류를 모르는 호출부는 무기(줄 0) 크기로 본다.
inline int BlockW(int level) { return GearW(0, level); }
inline int BlockH(int level) { return GearH(0, level); }
inline int BlockCells(int level) { return GearCells(0, level); }
//Lv n 하나를 만드는 데 드는 Lv1 장수 = 2^(n-1)
inline int BlockCards(int level) { return level < 1 ? 0 : 1 << (level - 1); }
//한 방의 배수. 동료 ×2(1+1 → 1칸). 장비는 칸이 느는 단만 ×3, 그대로인 단은 ×2.
inline long long CrewMul(int level) { return level < 1 ? 0 : 1LL << (level - 1); }
inline long long GearMulOf(int slot, int level) { if (level < 1) return 0; long long m = 1; for (int i = 2; i <= level; i++) m *= GearCells(slot, i) > GearCells(slot, i - 1) ? 3 : 2; return m; }
inline long long LevelMulOf(int kind, int level) { return kind == LINEAGE_CREW ? CrewMul(level) : GearMulOf(kind - LINEAGE_SWORD, level); }
inline long long LevelMul(int level) { return CrewMul(level); }	//호환용

//---- 수치 (§16) ----
//한 방 = base × 배수(종류별). base 는 그 칸에 선 동료/장비의 값(★ 이 오르면 동료가 바뀌어 base 도 오른다).
//ult 는 더 쓰지 않는다 — 호출부 호환으로 남겨 둔다. 종류를 모르는 호출부는 동료 배수.
inline long long BlockDamage(int level, long long base, long long /*ult*/) { return base * CrewMul(level); }
inline long long BlockDamageOf(int kind, int level, long long base) { return base * LevelMulOf(kind, level); }
//표식: 이후 타격 +20/40/60/80/100/120 %
inline int ExposePct(int level) { static const int p[BLOCK_LV_MAX + 1] = { 0, 20, 40, 60, 80, 100, 120 }; return (level < 1 || level > BLOCK_LV_MAX) ? 0 : p[level]; }
//고무: 다음 블록 ×2/2/3/3/4/4
inline int InspireMul(int level) { static const int m[BLOCK_LV_MAX + 1] = { 1, 2, 2, 3, 3, 4, 4 }; return (level < 1 || level > BLOCK_LV_MAX) ? 1 : m[level]; }
//강타: 자기 피해 +30/50/75/100/125/150 %
inline int StrikePct(int level) { static const int p[BLOCK_LV_MAX + 1] = { 0, 30, 50, 75, 100, 125, 150 }; return (level < 1 || level > BLOCK_LV_MAX) ? 0 : p[level]; }
//연타: 탄 수. 단일 적에는 피해 합이 같고, 적이 n 마리면 n 마리 전부 맞는다
inline int VolleyHits(int level) { static const int h[BLOCK_LV_MAX + 1] = { 0, 2, 3, 4, 6, 8, 10 }; return (level < 1 || level > BLOCK_LV_MAX) ? 0 : h[level]; }
//빙결: Lv3·4 적 턴 1회, Lv5·6 2회 삭제. Lv1·2 는 적 공격 절반(플래그)
inline int ChillSkipTurns(int level) { return level >= 5 ? 2 : level >= 3 ? 1 : 0; }
//지속: 피해의 50% 가 Lv 교환 동안 남는다
inline int BurnPct(int) { return 50; }
inline int BurnTurns(int level) { return level < 1 ? 0 : (level + 1) / 2; }	//1·1·2·2·3·3 교환
//목걸이: 하트 +1/+2/+3 (Lv1~3), 룰렛 +1/+2/+3 (Lv4~6)
inline int NeckHearts(int level) { return (level >= 1 && level <= 3) ? level : 0; }
inline int NeckSpins(int level) { return level >= 4 ? level - 3 : 0; }
//갑옷: 보호 1회 (Lv1·2), 2회 (Lv3). 적 턴 1회 삭제 (Lv4·5), 2회 (Lv6). Lv2 는 적 공격 절반도
inline int ArmorGuards(int level) { return level == 3 ? 2 : (level == 1 || level == 2) ? 1 : 0; }
inline int ArmorSkipTurns(int level) { return level >= 6 ? 2 : level >= 4 ? 1 : 0; }

//---- 계열 ----
struct Lineage {
	int kind;			//LineageKind
	int id;				//동료 계열이면 역할군(CrewRole). 장비는 -1
	int trait;			//BlockTrait. 장비는 TRAIT_NONE
	long long base;		//Lv1 한 방. 동료는 그 ★ 동료의 스킬 값, 검은 히어로 평타
	long long ult;		//(쓰지 않음) 호환용
};

//---- 블록 ----
struct Block {
	bool active;
	int lineage;		//0..BOARD_LINEAGES-1
	int level;			//1..BLOCK_LV_MAX
	int x, y;			//왼쪽 위
};

//---- 판 ----
struct Board {
	Lineage lineage[BOARD_LINEAGES];
	Block block[BOARD_MAX_BLOCKS];
	int tray[BOARD_TRAY];		//트레이의 블록 레벨. 0 = 비었음
	int trayLineage[BOARD_TRAY];
	int spinsLeft;
	int lives;
};

inline void Reset(Board& b, const Lineage lineage[BOARD_LINEAGES], int lives) {
	for (int i = 0; i < BOARD_LINEAGES; i++) b.lineage[i] = lineage[i];
	for (int i = 0; i < BOARD_MAX_BLOCKS; i++) b.block[i].active = false;
	for (int i = 0; i < BOARD_TRAY; i++) { b.tray[i] = 0; b.trayLineage[i] = -1; }
	b.spinsLeft = BOARD_SPINS;
	b.lives = lives;
}

//칸 점유표. ignore 번 블록은 없는 셈 친다(옮기기·합성 판정용).
inline void Occupancy(const Board& b, int grid[BOARD_H][BOARD_W], int ignoreA = -1, int ignoreB = -1) {
	for (int y = 0; y < BOARD_H; y++) for (int x = 0; x < BOARD_W; x++) grid[y][x] = -1;
	for (int i = 0; i < BOARD_MAX_BLOCKS; i++) {
		if (!b.block[i].active || i == ignoreA || i == ignoreB) continue;
		const Block& k = b.block[i];
		int kind = b.lineage[k.lineage].kind;
		for (int dy = 0; dy < BlockHOf(kind, k.level); dy++)
			for (int dx = 0; dx < BlockWOf(kind, k.level); dx++)
				grid[k.y + dy][k.x + dx] = i;
	}
}

inline bool FitsKind(const Board& b, int kind, int level, int x, int y, int ignoreA = -1, int ignoreB = -1) {
	int w = BlockWOf(kind, level), h = BlockHOf(kind, level);
	if (w == 0 || x < 0 || y < 0 || x + w > BOARD_W || y + h > BOARD_H) return false;
	int grid[BOARD_H][BOARD_W];
	Occupancy(b, grid, ignoreA, ignoreB);
	for (int dy = 0; dy < h; dy++) for (int dx = 0; dx < w; dx++)
		if (grid[y + dy][x + dx] >= 0) return false;
	return true;
}
//계열 번호로 종류를 찾아 판정한다.
inline bool Fits(const Board& b, int lineage, int level, int x, int y, int ignoreA = -1, int ignoreB = -1) {
	if (lineage < 0 || lineage >= BOARD_LINEAGES) return false;
	return FitsKind(b, b.lineage[lineage].kind, level, x, y, ignoreA, ignoreB);
}

inline int FreeCells(const Board& b) {
	int grid[BOARD_H][BOARD_W], n = 0;
	Occupancy(b, grid);
	for (int y = 0; y < BOARD_H; y++) for (int x = 0; x < BOARD_W; x++) if (grid[y][x] < 0) n++;
	return n;
}

inline int BlockAt(const Board& b, int x, int y) {
	if (x < 0 || y < 0 || x >= BOARD_W || y >= BOARD_H) return -1;
	int grid[BOARD_H][BOARD_W];
	Occupancy(b, grid);
	return grid[y][x];
}

inline int ActiveBlocks(const Board& b) {
	int n = 0;
	for (int i = 0; i < BOARD_MAX_BLOCKS; i++) if (b.block[i].active) n++;
	return n;
}

//어디든 들어갈 자리가 하나라도 있는가(강제 공격 판정에 쓴다).
inline bool AnyFit(const Board& b, int lineage, int level) {
	for (int y = 0; y < BOARD_H; y++) for (int x = 0; x < BOARD_W; x++)
		if (Fits(b, lineage, level, x, y)) return true;
	return false;
}

//블록을 새로 놓는다. 성공하면 블록 번호, 실패 -1.
inline int Place(Board& b, int lineage, int level, int x, int y) {
	if (lineage < 0 || lineage >= BOARD_LINEAGES || !Fits(b, lineage, level, x, y)) return -1;
	for (int i = 0; i < BOARD_MAX_BLOCKS; i++) {
		if (b.block[i].active) continue;
		b.block[i].active = true;
		b.block[i].lineage = lineage;
		b.block[i].level = level;
		b.block[i].x = x; b.block[i].y = y;
		return i;
	}
	return -1;
}

inline void Remove(Board& b, int idx) {
	if (idx >= 0 && idx < BOARD_MAX_BLOCKS) b.block[idx].active = false;
}

//판 위 블록을 옮긴다. 자기 자리는 비운 셈 친다.
inline bool Move(Board& b, int idx, int x, int y) {
	if (idx < 0 || idx >= BOARD_MAX_BLOCKS || !b.block[idx].active) return false;
	if (!Fits(b, b.block[idx].lineage, b.block[idx].level, x, y, idx)) return false;
	b.block[idx].x = x; b.block[idx].y = y;
	return true;
}

//---- 합성 ----
//같은 계열·같은 Lv 두 블록. 결과는 t(대상) 자리에서 커진다. 커진 크기가
//판 밖으로 나가면 안쪽으로 당겨 본다(두 블록 자리는 비운 셈). 그래도 안
//들어가면 실패 — "커진 크기가 대상 자리에 들어가야 한다"(§16).
inline bool MergeTarget(const Board& b, int a, int t, int* outX, int* outY) {
	if (a < 0 || t < 0 || a == t || a >= BOARD_MAX_BLOCKS || t >= BOARD_MAX_BLOCKS) return false;
	const Block& A = b.block[a]; const Block& T = b.block[t];
	if (!A.active || !T.active || A.lineage != T.lineage || A.level != T.level || A.level >= BLOCK_LV_MAX) return false;
	int kind = b.lineage[T.lineage].kind;
	int lv = T.level + 1, w = BlockWOf(kind, lv), h = BlockHOf(kind, lv);
	int x = T.x, y = T.y;
	if (x + w > BOARD_W) x = BOARD_W - w;
	if (y + h > BOARD_H) y = BOARD_H - h;
	if (!FitsKind(b, kind, lv, x, y, a, t)) return false;
	if (outX) *outX = x;
	if (outY) *outY = y;
	return true;
}
inline bool CanMerge(const Board& b, int a, int t) { return MergeTarget(b, a, t, 0, 0); }
inline bool Merge(Board& b, int a, int t) {
	int x, y;
	if (!MergeTarget(b, a, t, &x, &y)) return false;
	b.block[t].level += 1;
	b.block[t].x = x; b.block[t].y = y;
	b.block[a].active = false;
	return true;
}

//---- 룰렛 ----
//3릴이 계열 3 중에서 뽑는다. 같은 계열 2 → Lv2 + Lv1, 3 → Lv3 하나.
//트레이가 비어 있고 횟수가 남아야 돌린다. 하트는 호출자가 낸다.
inline bool TrayEmpty(const Board& b) {
	for (int i = 0; i < BOARD_TRAY; i++) if (b.tray[i] > 0) return false;
	return true;
}
inline void HandFromReels(const int reel[BOARD_REELS], int outLevel[BOARD_TRAY], int outLineage[BOARD_TRAY]) {
	for (int i = 0; i < BOARD_TRAY; i++) { outLevel[i] = 0; outLineage[i] = -1; }
	if (reel[0] == reel[1] && reel[1] == reel[2]) {
		outLevel[0] = 3; outLineage[0] = reel[0];
		return;
	}
	for (int i = 0; i < BOARD_REELS; i++) {
		for (int j = i + 1; j < BOARD_REELS; j++) {
			if (reel[i] != reel[j]) continue;
			int other = 3 - i - j;
			outLevel[0] = 2; outLineage[0] = reel[i];
			outLevel[1] = 1; outLineage[1] = reel[other];
			return;
		}
	}
	for (int i = 0; i < BOARD_REELS; i++) { outLevel[i] = 1; outLineage[i] = reel[i]; }
}
inline bool Spin(Board& b, RandomFn rnd, int outReel[BOARD_REELS]) {
	if (b.spinsLeft <= 0 || !TrayEmpty(b)) return false;
	int reel[BOARD_REELS];
	for (int i = 0; i < BOARD_REELS; i++) reel[i] = rnd(BOARD_LINEAGES);
	if (outReel) for (int i = 0; i < BOARD_REELS; i++) outReel[i] = reel[i];
	HandFromReels(reel, b.tray, b.trayLineage);
	b.spinsLeft--;
	return true;
}
//트레이 slot 번을 판에 놓는다.
inline int PlaceFromTray(Board& b, int slot, int x, int y) {
	if (slot < 0 || slot >= BOARD_TRAY || b.tray[slot] <= 0) return -1;
	int idx = Place(b, b.trayLineage[slot], b.tray[slot], x, y);
	if (idx < 0) return -1;
	b.tray[slot] = 0; b.trayLineage[slot] = -1;
	return idx;
}
//트레이의 어떤 블록이 들어갈 자리가 없다 = 공격만 남았다.
inline bool TrayStuck(const Board& b) {
	for (int i = 0; i < BOARD_TRAY; i++)
		if (b.tray[i] > 0 && !AnyFit(b, b.trayLineage[i], b.tray[i])) return true;
	return false;
}
inline bool MustAttack(const Board& b) {
	if (b.spinsLeft <= 0 && TrayEmpty(b)) return true;
	return TrayStuck(b);
}

//---- 발사 순서 = 판 읽는 순서 (행 우선, 왼쪽 위부터) ----
inline int FireOrder(const Board& b, int out[BOARD_MAX_BLOCKS]) {
	int n = 0;
	for (int i = 0; i < BOARD_MAX_BLOCKS; i++) if (b.block[i].active) out[n++] = i;
	//삽입 정렬. 36 개 이하.
	for (int i = 1; i < n; i++) {
		int k = out[i], j = i - 1;
		const Block& K = b.block[k];
		while (j >= 0) {
			const Block& J = b.block[out[j]];
			if (J.y < K.y || (J.y == K.y && J.x <= K.x)) break;
			out[j + 1] = out[j]; j--;
		}
		out[j + 1] = k;
	}
	return n;
}

//---- 공격 계획 ----
//판 위 전부를 타순대로 쏜 결과. 피해는 베팅 전 값이고 호출자가 ×bet 한다.
struct AttackPlan {
	long long damage;			//이번 교환에 들어가는 피해 합
	long long burnPerTurn;		//다음 교환 시작마다 들어가는 피해
	int burnTurns;
	int enemyTurnsSkipped;		//빙결·갑옷이 지운 적 턴
	int guards;					//목숨 보호 횟수
	bool enemyAttackHalved;
	int heartsGained;
	int spinsGained;
	int maxVolleyHits;			//적이 여럿일 때 몇 마리까지 맞나
	int order[BOARD_MAX_BLOCKS];
	long long hit[BOARD_MAX_BLOCKS];	//order 와 같은 순서의 블록별 피해
	int count;
};

inline void PlanAttack(const Board& b, AttackPlan& p) {
	p.damage = 0; p.burnPerTurn = 0; p.burnTurns = 0; p.enemyTurnsSkipped = 0;
	p.guards = 0; p.enemyAttackHalved = false; p.heartsGained = 0; p.spinsGained = 0; p.maxVolleyHits = 1;
	p.count = FireOrder(b, p.order);
	int exposePct = 0;		//누적
	int inspireMul = 1;		//다음 블록 하나에만
	for (int n = 0; n < p.count; n++) {
		const Block& k = b.block[p.order[n]];
		const Lineage& L = b.lineage[k.lineage];
		long long dmg = 0;
		switch (L.kind) {
		case LINEAGE_CREW:
		case LINEAGE_SWORD:
			dmg = BlockDamageOf(L.kind, k.level, L.base);
			break;
		case LINEAGE_NECK:
			p.heartsGained += NeckHearts(k.level);
			p.spinsGained += NeckSpins(k.level);
			break;
		case LINEAGE_ARMOR:
			p.guards += ArmorGuards(k.level);
			p.enemyTurnsSkipped += ArmorSkipTurns(k.level);
			if (k.level == 2) p.enemyAttackHalved = true;
			break;
		}
		if (dmg > 0) {
			if (L.trait == TRAIT_STRIKE) dmg += dmg * StrikePct(k.level) / 100;
			dmg += dmg * exposePct / 100;
			dmg *= inspireMul;
			inspireMul = 1;
		}
		switch (L.trait) {
		case TRAIT_EXPOSE: exposePct += ExposePct(k.level); break;
		case TRAIT_INSPIRE: inspireMul = InspireMul(k.level); break;
		case TRAIT_VOLLEY: if (VolleyHits(k.level) > p.maxVolleyHits) p.maxVolleyHits = VolleyHits(k.level); break;
		case TRAIT_CHILL:
			p.enemyTurnsSkipped += ChillSkipTurns(k.level);
			if (k.level <= 2) p.enemyAttackHalved = true;
			break;
		case TRAIT_BURN:
			p.burnPerTurn += dmg * BurnPct(k.level) / 100;
			if (BurnTurns(k.level) > p.burnTurns) p.burnTurns = BurnTurns(k.level);
			break;
		}
		p.hit[n] = dmg;
		p.damage += dmg;
	}
}

//공격 뒤: 판은 그대로 두고(판 유지) 룰렛만 다시 채운다. 적 턴 처리는 EnemyTurn 이 한다.
inline void AfterAttack(Board& b, const AttackPlan& p) {
	b.spinsLeft = BOARD_SPINS + p.spinsGained;
}
//성을 넘길 때처럼 판을 통째로 비울 때.
inline void ClearBoard(Board& b) {
	for (int i = 0; i < BOARD_MAX_BLOCKS; i++) b.block[i].active = false;
}

//적 턴 하나를 받는다. 돌려주는 값 = 잃은 목숨.
inline int EnemyTurn(Board& b, const AttackPlan& p, bool boss) {
	if (p.enemyTurnsSkipped > 0) return 0;
	int cost = boss ? ENEMY_LIFE_COST_BOSS : ENEMY_LIFE_COST_NORMAL;
	if (p.enemyAttackHalved && cost > 1) cost /= 2;
	int lost = cost > p.guards ? cost - p.guards : 0;
	b.lives -= lost;
	if (b.lives < 0) b.lives = 0;
	return lost;
}

//---- 이번 판 최대 (§15-3) ----
//계열당 장수 = 룰렛 횟수 × 3 / 계열 수(10장 = Lv4 + Lv2). 큰 블록부터 (동료는 1칸, 장비는 4+2 칸)
//탐욕으로 만들고, 타순은 표식 → 고무 → 나머지 피해 큰 순. 베팅 ×1.
//이 값이 시작 슬롯 아래 "최대 ×N" 으로 적 체력과 나란히 보인다.
inline long long MaxPotential(const Lineage lineage[BOARD_LINEAGES], int spins = BOARD_SPINS) {
	Board b;
	Reset(b, lineage, RUN_LIVES_BASE);
	int cards = spins * BOARD_REELS / BOARD_LINEAGES;
	int n = 0;
	for (int l = 0; l < BOARD_LINEAGES; l++) {
		int left = cards;
		for (int lv = BLOCK_LV_MAX; lv >= 1; lv--) {
			while (left >= BlockCards(lv) && n < BOARD_MAX_BLOCKS) {
				b.block[n].active = true; b.block[n].lineage = l; b.block[n].level = lv;
				left -= BlockCards(lv); n++;
			}
		}
	}
	//타순을 y 에 적는다. FireOrder 는 y·x 를 비교만 하므로 판 크기를 넘어도 된다.
	//표식(0) → 고무(1) → 나머지(2, 피해 큰 순). 고무 바로 뒤에 가장 큰 블록이 온다.
	for (int i = 0; i < n; i++) {
		const Lineage& L = lineage[b.block[i].lineage];
		long long d = BlockDamageOf(L.kind, b.block[i].level, L.base);
		int bucket = L.trait == TRAIT_EXPOSE ? 0 : L.trait == TRAIT_INSPIRE ? 1 : 2;
		int within = bucket == 2 ? (int)(1000000 - (d > 999999 ? 999999 : d)) : 0;
		b.block[i].y = bucket * 1000000 + within;
		b.block[i].x = i;
	}
	AttackPlan p;
	PlanAttack(b, p);
	return p.damage;
}

} // namespace MergeBoard
