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
//Lv1 1×1, Lv2 1×2, Lv3 2×2, Lv4 2×4 (가로 2 × 세로 4). 합쳐도 칸이 줄지 않는다.
inline int BlockW(int level) { static const int w[BLOCK_LV_MAX + 1] = { 0, 1, 1, 2, 2 }; return (level < 1 || level > BLOCK_LV_MAX) ? 0 : w[level]; }
inline int BlockH(int level) { static const int h[BLOCK_LV_MAX + 1] = { 0, 1, 2, 2, 4 }; return (level < 1 || level > BLOCK_LV_MAX) ? 0 : h[level]; }
inline int BlockCells(int level) { return BlockW(level) * BlockH(level); }
//Lv n 하나를 만드는 데 드는 Lv1 장수 = 2^(n-1)
inline int BlockCards(int level) { return level < 1 ? 0 : 1 << (level - 1); }

//---- 수치 (§16) ----
//동료·검: Lv1 base ×1, Lv2 base ×3, Lv3 ult, Lv4 ult ×3
inline long long BlockDamage(int level, long long base, long long ult) {
	switch (level) {
	case 1: return base;
	case 2: return base * 3;
	case 3: return ult;
	case 4: return ult * 3;
	}
	return 0;
}
//표식: 이후 타격 +30/60/100/150 %
inline int ExposePct(int level) { static const int p[BLOCK_LV_MAX + 1] = { 0, 30, 60, 100, 150 }; return (level < 1 || level > BLOCK_LV_MAX) ? 0 : p[level]; }
//고무: 다음 블록 ×2/3/4/5
inline int InspireMul(int level) { return level < 1 ? 1 : level + 1; }
//강타: 자기 피해 +50/75/100/150 %
inline int StrikePct(int level) { static const int p[BLOCK_LV_MAX + 1] = { 0, 50, 75, 100, 150 }; return (level < 1 || level > BLOCK_LV_MAX) ? 0 : p[level]; }
//연타: 탄 수. 단일 적에는 피해 합이 같고, 적이 n 마리면 n 마리 전부 맞는다
inline int VolleyHits(int level) { static const int h[BLOCK_LV_MAX + 1] = { 0, 3, 5, 8, 12 }; return (level < 1 || level > BLOCK_LV_MAX) ? 0 : h[level]; }
//빙결: Lv3 적 턴 1회, Lv4 2회 삭제. Lv1·2 는 적 공격 절반(플래그)
inline int ChillSkipTurns(int level) { return level >= 4 ? 2 : level == 3 ? 1 : 0; }
//지속: 피해의 50% 가 Lv 교환 동안 남는다
inline int BurnPct(int) { return 50; }
inline int BurnTurns(int level) { return level; }
//목걸이: 하트 +1/+3 (Lv1·2), 룰렛 +1/+3 (Lv3·4)
inline int NeckHearts(int level) { return level == 1 ? 1 : level == 2 ? 3 : 0; }
inline int NeckSpins(int level) { return level == 3 ? 1 : level == 4 ? 3 : 0; }
//갑옷: 보호 1회 (Lv1·2), 적 턴 1/2회 삭제 (Lv3·4). Lv2 는 적 공격 절반도
inline int ArmorGuards(int level) { return (level == 1 || level == 2) ? 1 : 0; }
inline int ArmorSkipTurns(int level) { return level >= 4 ? 2 : level == 3 ? 1 : 0; }

//---- 계열 ----
struct Lineage {
	int kind;			//LineageKind
	int id;				//동료 번호. 장비는 -1
	int trait;			//BlockTrait. 장비는 TRAIT_NONE
	long long base;		//Lv1 한 방. 동료는 SKILL1 값, 검은 히어로 평타
	long long ult;		//Lv3 한 방. 동료는 SKILL3 값, 검은 히어로 궁극기
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
		for (int dy = 0; dy < BlockH(k.level); dy++)
			for (int dx = 0; dx < BlockW(k.level); dx++)
				grid[k.y + dy][k.x + dx] = i;
	}
}

inline bool Fits(const Board& b, int level, int x, int y, int ignoreA = -1, int ignoreB = -1) {
	int w = BlockW(level), h = BlockH(level);
	if (w == 0 || x < 0 || y < 0 || x + w > BOARD_W || y + h > BOARD_H) return false;
	int grid[BOARD_H][BOARD_W];
	Occupancy(b, grid, ignoreA, ignoreB);
	for (int dy = 0; dy < h; dy++) for (int dx = 0; dx < w; dx++)
		if (grid[y + dy][x + dx] >= 0) return false;
	return true;
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
inline bool AnyFit(const Board& b, int level) {
	for (int y = 0; y < BOARD_H; y++) for (int x = 0; x < BOARD_W; x++)
		if (Fits(b, level, x, y)) return true;
	return false;
}

//블록을 새로 놓는다. 성공하면 블록 번호, 실패 -1.
inline int Place(Board& b, int lineage, int level, int x, int y) {
	if (lineage < 0 || lineage >= BOARD_LINEAGES || !Fits(b, level, x, y)) return -1;
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
	if (!Fits(b, b.block[idx].level, x, y, idx)) return false;
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
	int lv = T.level + 1, w = BlockW(lv), h = BlockH(lv);
	int x = T.x, y = T.y;
	if (x + w > BOARD_W) x = BOARD_W - w;
	if (y + h > BOARD_H) y = BOARD_H - h;
	if (!Fits(b, lv, x, y, a, t)) return false;
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
		if (b.tray[i] > 0 && !AnyFit(b, b.tray[i])) return true;
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
			dmg = BlockDamage(k.level, L.base, L.ult);
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

//공격 뒤: 판을 비우고 룰렛을 다시 채운다. 적 턴 처리는 EnemyTurn 이 한다.
inline void AfterAttack(Board& b, const AttackPlan& p) {
	for (int i = 0; i < BOARD_MAX_BLOCKS; i++) b.block[i].active = false;
	b.spinsLeft = BOARD_SPINS + p.spinsGained;
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
//계열당 장수 = 룰렛 횟수 × 3 / 계열 수(10장 = Lv4 + Lv2). 큰 블록부터
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
		long long d = BlockDamage(b.block[i].level, L.base, L.ult);
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
