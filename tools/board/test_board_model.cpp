#include "../../Classes/BoardModel.h"
#include <cassert>
#include <iostream>
using namespace MergeBoard;

static int gSeq[64]; static int gSeqN = 0, gSeqI = 0;
static int SeqRandom(int bound) { int v = gSeq[gSeqI++ % (gSeqN ? gSeqN : 1)]; return v % bound; }
static void SetSeq(int a, int b, int c) { gSeq[0] = a; gSeq[1] = b; gSeq[2] = c; gSeqN = 3; gSeqI = 0; }

int main() {
	//---- 6단 = ★. 사람은 1×2 두 칸, 장비는 한 칸씩 ----
	assert(BLOCK_LV_MAX == 6);
	for (int lv = 1; lv <= 6; lv++) {
		assert(BlockCellsOf(LINEAGE_CREW, lv) == 2 && BlockWOf(LINEAGE_CREW, lv) == 1 && BlockHOf(LINEAGE_CREW, lv) == 2);
		assert(BlockCellsOf(LINEAGE_SWORD, lv) == lv && BlockCellsOf(LINEAGE_ARMOR, lv) == lv);
		assert(BlockCards(lv) == (1 << (lv - 1)));
		assert(CrewMul(lv) == (1 << (lv - 1)));
	}
	assert(GearW(2) == 2 && GearH(2) == 1 && GearW(4) == 2 && GearH(4) == 2 && GearW(5) == 5 && GearW(6) == 3 && GearH(6) == 2);
	assert(GearMul(1) == 1 && GearMul(2) == 3 && GearMul(3) == 9 && GearMul(6) == 243);
	//1+1 이 2칸이 되는 장비는 3배여야 칸당 화력이 는다. 동료는 1+1(4칸)이 2칸이라 2배면 는다.
	for (int lv = 2; lv <= 6; lv++) {
		assert(GearMul(lv) * BlockCellsOf(LINEAGE_SWORD, lv - 1) > GearMul(lv - 1) * BlockCellsOf(LINEAGE_SWORD, lv));
		assert(CrewMul(lv) > CrewMul(lv - 1));
	}
	assert(BlockCellsOf(LINEAGE_CREW, 0) == 0 && BlockCellsOf(LINEAGE_SWORD, 7) == 0);

	//---- 계열당 10장(룰렛 10회 × 3 / 3) = Lv4 + Lv2. 동료 4칸, 장비 6칸 ----
	{
		int cards = BOARD_SPINS * BOARD_REELS / BOARD_LINEAGES;
		assert(cards == 10);
		int crewCells = 0, gearCells = 0, left = cards;
		for (int lv = BLOCK_LV_MAX; lv >= 1; lv--) while (left >= BlockCards(lv)) { left -= BlockCards(lv); crewCells += BlockCellsOf(LINEAGE_CREW, lv); gearCells += BlockCellsOf(LINEAGE_SWORD, lv); }
		assert(left == 0 && crewCells == 4 && gearCells == 6);
		assert(crewCells * 2 + gearCells <= BOARD_CELLS);
	}

	//---- 손: 꽝 / 짝 / 셋 (표 함수는 남겨 둔다. 릴 매치로 ★2·3 을 바로 주는 규칙은 §20 에서 폐지) ----
	{
		int lv[3], ln[3];
		int r1[3] = { 0, 1, 2 }; HandFromReels(r1, lv, ln);
		assert(lv[0] == 1 && lv[1] == 1 && lv[2] == 1 && ln[0] == 0 && ln[1] == 1 && ln[2] == 2);
		int r3[3] = { 1, 1, 1 }; HandFromReels(r3, lv, ln);
		assert(lv[0] == 3 && ln[0] == 1);
	}

	Lineage L[BOARD_LINEAGES] = {
		{ LINEAGE_CREW, ROLE_COMMANDER, TRAIT_EXPOSE, 100, 0 },	//지휘: 표식
		{ LINEAGE_CREW, ROLE_SUPPORT, TRAIT_INSPIRE, 100, 0 },		//지원: 고무
		{ LINEAGE_SWORD, -1, TRAIT_NONE, 50, 0 },					//검: 히어로
	};
	Board b;
	Reset(b, L, RUN_LIVES_BASE);
	assert(b.spinsLeft == BOARD_SPINS && b.lives == 3 && FreeCells(b) == 36 && TrayEmpty(b));

	//---- 스핀 → 트레이 → 배치 (동료는 Lv 가 올라도 1×2) ----
	SetSeq(0, 0, 1);
	int reel[3];
	assert(Spin(b, SeqRandom, reel));
	assert(b.spinsLeft == 9 && b.tray[0] == 2 && b.trayLineage[0] == 0 && b.tray[1] == 1 && b.trayLineage[1] == 1);
	assert(!Spin(b, SeqRandom, reel));			//트레이가 안 비었으면 못 돌린다
	int i0 = PlaceFromTray(b, 0, 0, 0);			//동료 Lv2 = 1×2 at (0,0)
	assert(i0 >= 0 && BlockAt(b, 0, 0) == i0 && BlockAt(b, 0, 1) == i0 && BlockAt(b, 0, 2) == -1);
	assert(PlaceFromTray(b, 1, 0, 0) == -1);	//겹침
	assert(PlaceFromTray(b, 1, 5, 5) == -1);	//1×2 는 마지막 줄에서 판을 넘는다
	int i1 = PlaceFromTray(b, 1, 5, 4);
	assert(i1 >= 0 && TrayEmpty(b) && FreeCells(b) == 32);

	//---- 옮기기 ----
	assert(Move(b, i0, 2, 2) && BlockAt(b, 0, 0) == -1 && BlockAt(b, 2, 2) == i0);
	{
		int g = Place(b, 2, 2, 0, 0);			//검 Lv2 = 2×1 at (0,0)
		assert(g >= 0 && BlockAt(b, 1, 0) == g);
		assert(!Move(b, g, 5, 0));				//2×1 이 오른쪽을 넘음
		assert(Move(b, g, 4, 0) && BlockAt(b, 5, 0) == g);
		Remove(b, g);
	}

	//---- 합성: 동료는 제자리에서 1×2 그대로 ----
	int a = Place(b, 0, 2, 4, 0);				//동료 Lv2 at (4,0)
	assert(a >= 0);
	assert(!CanMerge(b, a, i1));				//계열 다름(0 vs 1)
	assert(CanMerge(b, a, i0) && Merge(b, a, i0));
	assert(!b.block[a].active && b.block[i0].level == 3 && b.block[i0].x == 2 && b.block[i0].y == 2);
	assert(BlockAt(b, 2, 2) == i0 && BlockAt(b, 2, 3) == i0 && BlockAt(b, 3, 3) == -1 && FreeCells(b) == 36 - 4);
	//꽉 찬 판에서도 동료 둘은 합쳐진다
	{
		Board c; Reset(c, L, 3);
		for (int x = 0; x < 6; x++) for (int y = 0; y < 6; y++) Place(c, 1, 1, x, y);
		int p = BlockAt(c, 0, 0), q = BlockAt(c, 1, 0);
		assert(FreeCells(c) == 0 && CanMerge(c, p, q) && Merge(c, p, q) && FreeCells(c) == 2 && c.block[q].level == 2);
	}

	//---- 합성: 장비는 커진다. 끝에서는 안쪽으로 당기고, 자리가 없으면 실패 ----
	{
		Board c; Reset(c, L, 3);
		int e1 = Place(c, 2, 1, 5, 0), e2 = Place(c, 2, 1, 5, 1);
		assert(e1 >= 0 && e2 >= 0 && Merge(c, e1, e2));	//1×1 + 1×1 → 2×1: x 5→4
		assert(c.block[e2].level == 2 && c.block[e2].x == 4 && c.block[e2].y == 1 && BlockAt(c, 5, 1) == e2);
		int e3 = Place(c, 2, 2, 0, 1);
		assert(e3 >= 0 && Merge(c, e3, e2));				//2×1 + 2×1 → 3×1: x 4→3
		assert(c.block[e2].level == 3 && c.block[e2].x == 3 && BlockAt(c, 5, 1) == e2 && FreeCells(c) == 33);
		int e4 = Place(c, 2, 3, 0, 3);
		assert(e4 >= 0 && Merge(c, e4, e2));				//3×1 + 3×1 → 2×2 at (3,1)
		assert(c.block[e2].level == 4 && c.block[e2].x == 3 && c.block[e2].y == 1 && BlockAt(c, 4, 2) == e2);
		int e5 = Place(c, 2, 4, 0, 4);
		assert(e5 >= 0 && Merge(c, e5, e2));				//2×2 + 2×2 → 5×1: x 3→1
		assert(c.block[e2].level == 5 && c.block[e2].x == 1 && c.block[e2].y == 1 && BlockAt(c, 5, 1) == e2 && BlockAt(c, 0, 1) == -1);
		int e6 = Place(c, 2, 5, 0, 4);
		assert(e6 >= 0 && Merge(c, e6, e2));				//5×1 + 5×1 → 3×2 at (1,1)
		assert(c.block[e2].level == 6 && c.block[e2].x == 1 && c.block[e2].y == 1 && BlockAt(c, 3, 2) == e2);
		int e7 = Place(c, 2, 6, 0, 4);
		assert(e7 >= 0 && !CanMerge(c, e7, e2));			//Lv6 끼리는 못 합친다
		//꽉 찬 판에서 장비 Lv1 둘은 2칸이 없어 못 합친다
		Board d; Reset(d, L, 3);
		for (int x = 0; x < 6; x++) for (int y = 0; y < 6; y++) Place(d, 2, 1, x, y);
		assert(FreeCells(d) == 0 && !CanMerge(d, BlockAt(d, 0, 0), BlockAt(d, 1, 0)));
		Remove(d, BlockAt(d, 2, 0));
		assert(CanMerge(d, BlockAt(d, 0, 0), BlockAt(d, 1, 0)));
	}

	//---- 발사 순서 = 행 우선 ----
	{
		Board c; Reset(c, L, 3);
		int p = Place(c, 0, 1, 5, 0), q = Place(c, 1, 1, 0, 1), r = Place(c, 2, 1, 0, 0);
		int order[BOARD_MAX_BLOCKS];
		int n = FireOrder(c, order);
		assert(n == 3 && order[0] == r && order[1] == p && order[2] == q);
	}

	//---- 특성: 표식 → 고무 → 검 (§14-3). 동료 ×2, 장비 ×3 ----
	{
		Board c; Reset(c, L, 3);
		Place(c, 0, 1, 0, 0);	//표식 Lv1: 100, 이후 +20%
		Place(c, 1, 2, 1, 0);	//고무 Lv2: 100×2=200 ×1.2 = 240, 다음 ×2
		Place(c, 2, 3, 2, 0);	//검 Lv3: 50×9=450 ×1.2 ×2 = 1080
		AttackPlan p; PlanAttack(c, p);
		assert(p.count == 3 && p.hit[0] == 100 && p.hit[1] == 240 && p.hit[2] == 1080);
		assert(p.damage == 1420);
		Board e; Reset(e, L, 3);
		Place(e, 2, 3, 0, 0);	//검 맨몸 450
		Place(e, 1, 2, 3, 0);	//고무 200, 다음 ×2
		Place(e, 0, 1, 4, 0);	//표식 100 ×2 = 200
		AttackPlan q; PlanAttack(e, q);
		assert(q.damage == 850 && p.damage > q.damage);
	}

	//---- 장비 블록: 목걸이·갑옷, 적 턴, 판 유지 ----
	{
		Lineage G[BOARD_LINEAGES] = {
			{ LINEAGE_NECK, -1, TRAIT_NONE, 0, 0 },
			{ LINEAGE_ARMOR, -1, TRAIT_NONE, 0, 0 },
			{ LINEAGE_CREW, ROLE_STRIKER, TRAIT_CHILL, 100, 0 },
		};
		Board c; Reset(c, G, 3);
		Place(c, 0, 2, 0, 0);	//목걸이 Lv2 (2×1): 하트 +2
		Place(c, 0, 4, 2, 0);	//목걸이 Lv4 (2×2): 룰렛 +1
		Place(c, 1, 1, 4, 0);	//갑옷 Lv1: 보호 1
		Place(c, 2, 2, 5, 0);	//빙결 Lv2: 적 공격 절반, 피해 100×2
		AttackPlan p; PlanAttack(c, p);
		assert(p.heartsGained == 2 && p.spinsGained == 1 && p.guards == 1 && p.enemyAttackHalved && p.enemyTurnsSkipped == 0);
		assert(p.damage == 200);
		assert(EnemyTurn(c, p, true) == 0 && c.lives == 3);		//보스 2 → 절반 1 → 보호 1 → 0
		AttackPlan none = {}; none.guards = 0;
		assert(EnemyTurn(c, none, true) == 2 && c.lives == 1);
		assert(EnemyTurn(c, none, false) == 1 && c.lives == 0);
		int before = ActiveBlocks(c);
		AfterAttack(c, p);
		assert(ActiveBlocks(c) == before && c.spinsLeft == BOARD_SPINS + 1);	//판은 남는다
		ClearBoard(c);
		assert(ActiveBlocks(c) == 0);
		Board d; Reset(d, G, 3);
		Place(d, 2, 5, 0, 0);	//빙결 Lv5 (동료, 1×2)
		AttackPlan q; PlanAttack(d, q);
		assert(q.enemyTurnsSkipped == 2 && EnemyTurn(d, q, true) == 0 && d.lives == 3);
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
		//35칸 찬 판: 동료 Lv1 은 들어가고 검 Lv2(2×1)는 못 들어간다
		Remove(d, BlockAt(d, 5, 5));
		d.tray[0] = 1; d.trayLineage[0] = 0; assert(!TrayStuck(d));
		d.tray[0] = 2; d.trayLineage[0] = 2; assert(TrayStuck(d));
	}

	//---- 이번 판 최대: 계열당 Lv4 + Lv2 ----
	{
		long long mx = MaxPotential(L);
		//표식 Lv4 800 (+80%) → 표식 Lv2 200×1.8=360 (+40% → 120%)
		//→ 고무 Lv4 800×2.2=1760, 다음 ×3 → 고무 Lv2 200×2.2×3=1320, 다음 ×2
		//→ 검 Lv4 50×27=1350 ×2.2 ×2 = 5940 → 검 Lv2 150×2.2=330
		assert(mx == 800 + 360 + 1760 + 1320 + 5940 + 330);
		assert(MaxPotential(L, 0) == 0);
	}

	std::cout << "PASS board model: crew 1x2 at every star (x2), gear grows one cell per level (x3), hands, place/move/merge, row-major fire order, expose->inspire->sword, gear blocks, board persists, forced attack, max potential\n";
	return 0;
}
