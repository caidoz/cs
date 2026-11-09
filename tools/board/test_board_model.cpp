#include "../../Classes/BoardModel.h"
#include <cassert>
#include <iostream>
using namespace MergeBoard;

static int gSeq[64]; static int gSeqN = 0, gSeqI = 0;
static int SeqRandom(int bound) { int v = gSeq[gSeqI++ % (gSeqN ? gSeqN : 1)]; return v % bound; }
static void SetSeq(int a, int b, int c) { gSeq[0] = a; gSeq[1] = b; gSeq[2] = c; gSeqN = 3; gSeqI = 0; }

int main() {
	//---- 크기 1·2·4, 장수 1·2·4. 3단이 끝 ----
	assert(BLOCK_LV_MAX == 3);
	assert(BlockCells(1) == 1 && BlockCells(2) == 2 && BlockCells(3) == 4);
	assert(BlockCards(1) == 1 && BlockCards(2) == 2 && BlockCards(3) == 4);
	assert(BlockW(3) == 2 && BlockH(3) == 2);
	assert(BlockCells(0) == 0 && BlockCells(4) == 0);

	//---- 계열당 10장 = Lv3 ×2 + Lv2 = 10칸, 셋이면 30칸 ≤ 36 ----
	{
		int cards = BOARD_SPINS * BOARD_REELS / BOARD_LINEAGES;
		assert(cards == 10);
		int cells = 0, left = cards;
		for (int lv = BLOCK_LV_MAX; lv >= 1; lv--) while (left >= BlockCards(lv)) { left -= BlockCards(lv); cells += BlockCells(lv); }
		assert(cells == 10 && left == 0);
		assert(cells * BOARD_LINEAGES == 30 && 30 <= BOARD_CELLS);
	}

	//---- 손: 꽝 / 짝 / 셋 ----
	{
		int lv[3], ln[3];
		int r1[3] = { 0, 1, 2 }; HandFromReels(r1, lv, ln);
		assert(lv[0] == 1 && lv[1] == 1 && lv[2] == 1 && ln[0] == 0 && ln[1] == 1 && ln[2] == 2);
		int r2[3] = { 2, 0, 2 }; HandFromReels(r2, lv, ln);
		assert(lv[0] == 2 && ln[0] == 2 && lv[1] == 1 && ln[1] == 0 && lv[2] == 0);
		int r3[3] = { 1, 1, 1 }; HandFromReels(r3, lv, ln);
		assert(lv[0] == 3 && ln[0] == 1 && lv[1] == 0 && lv[2] == 0);
	}

	Lineage L[BOARD_LINEAGES] = {
		{ LINEAGE_CREW, 42, TRAIT_EXPOSE, 100, 1000 },		//세바스찬: 표식
		{ LINEAGE_CREW, 36, TRAIT_INSPIRE, 100, 1000 },	//로키: 고무
		{ LINEAGE_SWORD, -1, TRAIT_NONE, 50, 2000 },		//검: 히어로
	};
	Board b;
	Reset(b, L, RUN_LIVES_BASE);
	assert(b.spinsLeft == BOARD_SPINS && b.lives == 3 && FreeCells(b) == 36 && TrayEmpty(b));

	//---- 스핀 → 트레이 → 배치 ----
	SetSeq(0, 0, 1);
	int reel[3];
	assert(Spin(b, SeqRandom, reel));
	assert(b.spinsLeft == 9 && b.tray[0] == 2 && b.trayLineage[0] == 0 && b.tray[1] == 1 && b.trayLineage[1] == 1);
	assert(!Spin(b, SeqRandom, reel));			//트레이가 안 비었으면 못 돌린다
	int i0 = PlaceFromTray(b, 0, 0, 0);			//Lv2 1×2 at (0,0)
	assert(i0 >= 0 && BlockAt(b, 0, 0) == i0 && BlockAt(b, 0, 1) == i0 && BlockAt(b, 1, 0) == -1);
	assert(PlaceFromTray(b, 1, 0, 1) == -1);	//겹침
	int i1 = PlaceFromTray(b, 1, 5, 5);
	assert(i1 >= 0 && TrayEmpty(b) && FreeCells(b) == 33);

	//---- 옮기기 ----
	assert(Move(b, i0, 0, 0));					//제자리
	assert(!Move(b, i0, 0, 5));					//1×2 가 바닥을 넘음
	assert(Move(b, i0, 2, 2));
	assert(BlockAt(b, 0, 0) == -1 && BlockAt(b, 2, 3) == i0);

	//---- 합성: 같은 계열·같은 Lv 만, 대상 자리에서 커진다 ----
	int a = Place(b, 0, 2, 4, 0);				//Lv2 at (4,0)
	assert(a >= 0);
	assert(!CanMerge(b, a, i1));				//계열 다름(0 vs 1)
	assert(CanMerge(b, a, i0));
	assert(Merge(b, a, i0));
	assert(!b.block[a].active && b.block[i0].level == 3 && b.block[i0].x == 2 && b.block[i0].y == 2);
	assert(BlockAt(b, 3, 3) == i0 && FreeCells(b) == 36 - 4 - 1);
	//판 끝에서 커지면 안쪽으로 당긴다
	int e1 = Place(b, 2, 1, 5, 0), e2 = Place(b, 2, 1, 5, 1);
	assert(e1 >= 0 && e2 >= 0 && Merge(b, e1, e2));	//1×1 + 1×1 → 1×2 at (5,1) 는 바닥 안이므로 그대로
	assert(b.block[e2].level == 2 && b.block[e2].x == 5 && b.block[e2].y == 1);
	int e3 = Place(b, 2, 2, 5, 3);				//1×2 at (5,3)
	assert(e3 >= 0 && Merge(b, e2, e3));			//→ Lv3 2×2: x 5→4, y 3 유지
	assert(b.block[e3].level == 3 && b.block[e3].x == 4 && b.block[e3].y == 3);
	//Lv3 상한: Lv3 끼리는 못 합친다
	{
		Board c; Reset(c, L, 3);
		int p = Place(c, 0, 3, 0, 0), q = Place(c, 0, 3, 2, 0);
		assert(p >= 0 && q >= 0 && !CanMerge(c, p, q));
		//Lv2 + Lv2 → Lv3 2×2 가 들어갈 자리가 없으면 실패
		Board d; Reset(d, L, 3);
		int r = Place(d, 0, 2, 0, 4), s = Place(d, 0, 2, 5, 4);	//둘 다 바닥 두 줄, 양 끝
		assert(r >= 0 && s >= 0);
		for (int x = 1; x < 5; x++) for (int y = 4; y < 6; y++) Place(d, 1, 1, x, y);	//바닥 두 줄 사이를 채움
		for (int x = 0; x < 6; x++) for (int y = 0; y < 4; y++) Place(d, 1, 1, x, y);	//위 네 줄을 채움
		assert(!CanMerge(d, r, s));
	}

	//---- 발사 순서 = 행 우선 ----
	{
		Board c; Reset(c, L, 3);
		int p = Place(c, 0, 1, 5, 0), q = Place(c, 1, 1, 0, 1), r = Place(c, 2, 1, 0, 0);
		int order[BOARD_MAX_BLOCKS];
		int n = FireOrder(c, order);
		assert(n == 3 && order[0] == r && order[1] == p && order[2] == q);
	}

	//---- 특성: 표식 → 고무 → 궁극기 (§14-3) ----
	{
		Board c; Reset(c, L, 3);
		Place(c, 0, 1, 0, 0);	//표식 Lv1: 100, 이후 +30%
		Place(c, 1, 2, 1, 0);	//고무 Lv2: 300 ×1.3 = 390, 다음 ×3
		Place(c, 2, 3, 2, 0);	//검 Lv3 궁극기 2000 ×1.3 ×3 = 7800
		AttackPlan p; PlanAttack(c, p);
		assert(p.count == 3 && p.hit[0] == 100 && p.hit[1] == 390 && p.hit[2] == 7800);
		assert(p.damage == 100 + 390 + 7800);
		//거꾸로 두면
		Board e; Reset(e, L, 3);
		Place(e, 2, 3, 0, 0);	//궁극기 맨몸 2000
		Place(e, 1, 2, 2, 0);	//고무 300, 다음 ×3 — 다음이 표식 Lv1
		Place(e, 0, 1, 3, 0);	//표식 100 ×3 = 300
		AttackPlan q; PlanAttack(e, q);
		assert(q.damage == 2000 + 300 + 300);
		assert(p.damage > q.damage * 3);
	}

	//---- 장비 블록: 목걸이·갑옷, 적 턴 ----
	{
		Lineage G[BOARD_LINEAGES] = {
			{ LINEAGE_NECK, -1, TRAIT_NONE, 0, 0 },
			{ LINEAGE_ARMOR, -1, TRAIT_NONE, 0, 0 },
			{ LINEAGE_CREW, 5, TRAIT_CHILL, 100, 1000 },
		};
		Board c; Reset(c, G, 3);
		Place(c, 0, 2, 0, 0);	//목걸이 Lv2: 하트 +3
		Place(c, 0, 3, 2, 0);	//목걸이 Lv3: 룰렛 +1
		Place(c, 1, 1, 4, 0);	//갑옷 Lv1: 보호 1
		Place(c, 2, 2, 5, 0);	//빙결 Lv2: 적 공격 절반
		AttackPlan p; PlanAttack(c, p);
		assert(p.heartsGained == 3 && p.spinsGained == 2 && p.guards == 1 && p.enemyAttackHalved && p.enemyTurnsSkipped == 0);
		assert(p.damage == 300);
		assert(EnemyTurn(c, p, true) == 0 && c.lives == 3);		//보스 2 → 절반 1 → 보호 1 → 0
		AttackPlan none = {}; none.guards = 0;
		assert(EnemyTurn(c, none, true) == 2 && c.lives == 1);
		assert(EnemyTurn(c, none, false) == 1 && c.lives == 0);
		AfterAttack(c, p);
		assert(ActiveBlocks(c) == 0 && c.spinsLeft == BOARD_SPINS + 2);
		//빙결 Lv3 는 적 턴을 지운다
		Board d; Reset(d, G, 3);
		Place(d, 2, 3, 0, 0);
		AttackPlan q; PlanAttack(d, q);
		assert(q.enemyTurnsSkipped == 1 && EnemyTurn(d, q, true) == 0 && d.lives == 3);
	}

	//---- 강제 공격: 룰렛 0 또는 트레이 막힘 ----
	{
		Board c; Reset(c, L, 3);
		assert(!MustAttack(c));
		c.spinsLeft = 0;
		assert(MustAttack(c));
		Board d; Reset(d, L, 3);
		for (int x = 0; x < 6; x++) for (int y = 0; y < 6; y++) Place(d, 0, 1, x, y);
		assert(FreeCells(d) == 0);
		d.tray[0] = 1; d.trayLineage[0] = 0;
		assert(TrayStuck(d) && MustAttack(d));
	}

	//---- 이번 판 최대: 계열당 Lv3 ×2 + Lv2 ----
	{
		long long mx = MaxPotential(L);
		//표식 Lv3 1000 (+100%) → 표식 Lv3 1000×2=2000 (누적 200%) → 표식 Lv2 300×3=900 (누적 260%)
		//→ 고무 Lv3 1000×3.6=3600, 다음 ×4 → 고무 Lv3 1000×3.6×4=14400, 다음 ×4 → 고무 Lv2 300×3.6×4=4320, 다음 ×3
		//→ 검 Lv3 2000×3.6×3=21600 → 검 Lv3 2000×3.6=7200 → 검 Lv2 150×3.6=540
		assert(mx == 1000 + 2000 + 900 + 3600 + 14400 + 4320 + 21600 + 7200 + 540);
		assert(mx > 0 && MaxPotential(L, 0) == 0);
	}

	std::cout << "PASS board model: sizes 1/2/4 (3 levels), 30 cells in 36, hands, place/move/merge growth, row-major fire order, expose->inspire->ult, gear blocks, forced attack, max potential\n";
	return 0;
}
