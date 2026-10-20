#pragma once

#define OPENING_SCENE_COUNT 5
#define OPENING_TEXT_PER_SCENE 3
#define OPENING_TOTAL_TEXT (OPENING_SCENE_COUNT * OPENING_TEXT_PER_SCENE)

enum OpeningState
{
	OPENING_STATE_TEXT,
	OPENING_STATE_TEXT_WAIT,
	OPENING_STATE_SCENE_WAIT,
	OPENING_STATE_END
};

const int openingTextId[] =
{
	TEXT_OPENING_0_0,
	TEXT_OPENING_1_0,
	TEXT_OPENING_2_0,
	TEXT_OPENING_3_0,
	TEXT_OPENING_4_0
};
// Draw핸들
void DrawWindow3(int x, int y, int w, int h, int index, float zoom);
void DrawWindow4(int x, int y, int w, int h, int index, float zoom);
void DrawWindow5(int x, int y, int w, int h, int mapIdx, float zoom, int mapOffsetY);

void VersionDraw(void);

#if DUMP_CMF_PNG
//캐릭터 그림을 한 프레임에 한 장씩 PNG 로 떨군다(Config/BuildConfig.h).
void DumpCmfStep(void);
#endif
void LogoDraw(void);
void LoadingDraw(void);
void TitleDraw(void);
#ifdef GAMEDEBUG
bool TitleCastleDebugDraw(void);
bool TitleCastleDebugActive(void);
void CastlePartsDrawRect(int level, int x, int yTop, int w, int h);

//성을 세로선(axisX)을 축으로 접어 그린다. 켠 뒤에는 반드시 다시 끈다 -
//한 장면 안에서 한쪽만 돌려 세우는 용도다.
void CastlePartsSetMirror(bool on, float axisX);

//켜면 성이 화면 왼쪽으로 붙지 않고 준 자리에 그대로 선다.
void CastlePartsSetFreePlace(bool on);

//이 배율로 그렸을 때 화면에서 차지하는 폭과 높이. 성마다 그림의
//가로세로비가 달라, 폭만 맞추면 홀쭉한 성이 화면을 넘는다.
bool CastlePartsDrawSize(int castleLevel, float scale, float* w, float* h);

//로비와 전투가 성을 그리는 폭. 성 단계와 상관없이 늘 같다.
float CastlePartsWorldWidth(void);

//이 네모로 그렸을 때 바퀴가 닿을 화면 y. 두 성을 같은 줄에 세울 때 쓴다.
float CastlePartsWheelLine(int castleLevel, int yTop, int w, int h);
void CastlePartsNaturalSize(int level, float* w, float* h);
float CastlePartsRoomScale(void);
void CastlePartsVisualBounds(int level, float scale, float* left, float* right);
void CastlePartsPartAnchor(int level, int part, float* x, float* y);
float CastlePartsFloatOffset(int level);
void TitleCastleDebugButton(void);
bool TitleCastleDebugCommand(int command);
#endif
void TitleSkillViewerCommand(int command);
void TitleTermsCommand(int command);
void OpeningDraw(void);
void LobbyDraw(void);
void LoadoutDraw(void);				//출정 준비 화면
void StageMapOverlayDraw(void);		//이 판의 자리 열다섯
void StageMapSetOpen(bool on);
bool StageMapOpen(void);
void StageShopOfferCardsDraw(void);		//5지선다 선택 카드 목록
bool LoadoutOpen(void);
bool BattleEntryLocked(void);
void LoadoutSetOpen(bool on);
//성의 대포 파츠 단계에 맞는 포를 인벤토리에 둔다. 출정 준비를 열 때 부른다.
void CannonGrantEnsure(void);

//가방에 실린 대포. 없으면 false - 그때는 아무것도 안 쏜다.
bool StageBagCannon(int* castle, int* level, int* slot);

//가방 내 대포 소켓 인접 시너지
struct CannonSynergy {
	int fireEssenceCnt;
	int iceEssenceCnt;
	int thunderEssenceCnt;
	int magicEssenceCnt;
	int swordCnt;
	int swordBonusDmg;
	int crewArtilleryCnt;
	int shieldCnt;
	int cooldownReductionPct;
	float scaleBonus;
	int extraHits;
};
void StageCannonQuerySynergy(CannonSynergy* out);

//동료 4대 카테고리 역할
enum CrewRole {
	CREW_ROLE_COMMANDER = 0, // 지휘형: 가방에 작전서 제공 -> 쿨타임 완료 시 히어로 궁극기 발동
	CREW_ROLE_ARTILLERY,     // 포격형: 성 대포 쿨타임/화력 증폭
	CREW_ROLE_BLACKSMITH,    // 지원/대장장이형: 인접 장비 강화 및 요새 수리/실드 회복
	CREW_ROLE_STRIKER,       // 공격형: 성 위에서 원거리 지속 화력 투사
	TOTAL_CREW_ROLES
};
CrewRole GetCrewRole(int crewType);
const char* GetCrewRoleName(CrewRole role);
int GetCrewRoleColor(CrewRole role);
void GridEnsureTacticScroll(void);

//히어로 장비 6대 부위 카테고리
enum GearCategory {
	GEAR_CAT_WEAPON = 0,
	GEAR_CAT_ARMOR,
	GEAR_CAT_HELM,
	GEAR_CAT_GLOVE,
	GEAR_CAT_PANTS,
	GEAR_CAT_BOOTS,
	GEAR_CAT_SHIELD,
	GEAR_CAT_CREW,
	GEAR_CAT_RECIPE,
	TOTAL_GEAR_CATS
};
GearCategory GetItemGearCategory(int itemType);
bool GridSlotHasAdjacentCategory(int slot, GearCategory cat);
long long GridTestPantsHpBonus(void);
bool GridCrewHasAdjacentPants(int crewIndex);
bool GridSlotAdjacentToRocky(int slot);
int GetCrewIdxFromType(int type);

int LoadoutPoint(void);				//이번 판에 쓸 수 있는 점수
int LoadoutUsed(void);
int LoadoutCost(const ITEM* it);
int LoadoutFind(int invenIdx);
bool LoadoutToggle(int invenIdx);
void LoadoutSetTab(int tab);		//전체 / 무기 / 방어구 / 장신구
int LoadoutList(int* out, int max);	//지금 탭에 보이는 가방 칸
void LoadoutScrollRow(int dir);		//목록을 한 줄씩 밀어 본다
void LoadoutScrollReset(void);
void LoadoutToggleView(void);		//목록 <-> 격자
void LoadoutAuto(void);				//점수 안에서 좋은 것부터 담는다
void LoadoutClear(void);
int LoadoutTab(void);
int LoadoutSlotInven(int slot);		//화면에 보이는 칸 -> 가방 번호
void LobbySkyUpdate(float delta);
bool LobbyCamTouchBegan(int id, float x, float y);
bool LobbyCamTouchMoved(int id, float x, float y);
bool LobbyCamTouchEnded(int id);

//---- 성 격자 인벤토리 시험판 (Func_Draw.cpp) ----
//시험이 끝나면 이 네 줄과 Func_Draw.cpp 의 블록을 통째로 지운다.
void GridTestDraw(void);
int GetStageInventoryTop(void);
int GetStageInventoryWidth(void);
void StageBridgeHpDraw(void);
// Shared 32px-grid cannon art; castle/level are zero based, bounds use top-left Y.
void DrawInventoryCannonIcon(int castle,int level,int x,int y,int width,int height);
void DrawInventoryCannonThumbnail(int castle,int level,int x,int y,int width,int height);
void StageShopPreviewOpen(void);
float CastlePartsCannonBaseY(int castleLevel);
bool StageShopPreviewPurchaseChecks(void);
//성 안의 히어로와 동료. 로비와 전투가 같이 쓴다.
bool CastleRoomCoverPreview(int operation);
bool CastleCrewDeckPoint(int slot,float* x,float* y);
bool SdRoomDeckReviewCheck(void);
bool StarterSdWheelReview(bool remember);
bool StarterSdUpgradeReviewCheck(void);
bool SecondSdUpgradeReviewCheck(void);
bool ThirdSdUpgradeReviewCheck(void);
bool TenthSdUpgradeReviewCheck(void);
bool CastleFixedWidthReviewCheck(int operation);
bool CastleUniformReviewCheck(void);
bool CastleIndividualReviewCheck(int operation);
bool CastleInteriorSyncReviewCheck(int operation);
bool CastleRoomToggleTap(float startX,float startY,float endX,float endY);
bool PvpCastleDebugReviewCheck();
bool NinthSdUpgradeReviewCheck(void);
bool EighthSdUpgradeReviewCheck(void);
bool SeventhSdUpgradeReviewCheck(void);
bool SixthSdUpgradeReviewCheck(void);
bool FifthSdUpgradeReviewCheck(void);
bool FourthSdUpgradeReviewCheck(void);
void CastleCrewDrawAt(float left, float top, float w, float h, float scale,
                      int castle, bool battle);
float CastlePartsUpperH(int castleLevel);
float CastlePartsLeftInset(int castleLevel);
float CastlePartsBodyLift(int castleLevel);
float CastlePartsGroundOffset(int castleLevel);
float GetStageWorldLift(void);
int GetStageSceneGroundY(void);
bool BattleMenuPreviewDragCheck(void);
bool BattleMenuPreviewScrollCheck(void);
bool BattleMenuPreviewWarehouseGestureCheck(void);
void BattleInventoryScroll(int direction);
void BattleWarehouseScroll(int direction);
void GridTestPick(int n, bool fromShop);
void GridTestPickStore(int n);	//성보관함 칸을 집는다
void LoadoutPickStart(int inven);	//출정 준비에서 보관함 칸을 집는다
bool LoadoutToggleAt(int invenIdx, int col, int row);	//끌어다 놓은 칸에 담는다
bool LoadoutMoveTo(int invenIdx, int col, int row);	//담긴 것의 자리만 옮긴다
bool LoadoutRotate(int invenIdx);	//담긴 것을 90 도 돌린다
void LoadoutPickBag(int n);			//가방에 놓인 것을 집는다
void LoadoutPickHero(int hero);		//출정할 히어로를 고른다
void LoadoutSetupPress(void);
void LoadoutRelease(bool cancelled=false);			//그 손을 뗀 순간
void GridTestRelease(void);
void GridTestToggle(void);
void GridTestSkipOffer(void);
void GridTestReroll(void);
void GridTestRefresh(void);			//시험용. 값 없이 세 칸을 다시 돌린다
int GridShopPrice(int base);		//성 할인을 거친 값				//값을 치르고 룰렛을 다시 돌린다
int StageGold(void);				//인게임 전투 재화
void StageGoldSet(int g);
void StageGoldAdd(int delta);
void GridTestShopSide(bool book);		//하단 지도 / 도감 자리
void StageShopBtnRect(int* x, int* y, int* w, int* h);	//전투 시작 버튼 자리
bool GridTestBeginOffer(int killedType);
//격자에 놓인 검 한 자루. 실시간 전투가 자루마다 제 시계로 치게 한다.
//한 자루(또는 한 점)의 장비. 격자에서도, 몬스터 표에서도 같은 모양으로
//나온다. grade 는 등장 시점의 난이도로 올라간 뒤의 등급이다.
struct StageSword {
	int slot;		//격자 칸 번호. 시계를 이 번호에 건다
	int part;		//어떤 검인가. 칸의 검이 바뀌었는지 보는 데 쓴다
	int detail;		//검 번호. 길이(쿨타임)가 여기서 나온다
	int value;
	int grade;		//기본 공격력(MakeItemValue)
	bool gear;		//아웃게임에서 장착하고 들어온 검. 히어로가 휘두른다
};
int GridTestSwords(StageSword* out, int maxCnt);
int GridTestShields(StageSword* out, int maxCnt);
int GridTestTactics(StageSword* out, int maxCnt);
int GridTestTotalItemCount(void);
int StageGearList(int obj, StageSword* out, int maxCnt);	//누구든 장비 목록
int StageFoeGearList(StageSword* out, int maxCnt);	//지금 몬스터 장비
long long StageGearArmor(int obj);					//방어구 값의 합
void StageGearApplyStat(OBJECT* pObj);				//가방 장비 스탯을 더한다
long long StageGearReduce(int obj, long long damage);//방어구를 거친 피해
bool kShopPartIsSword(int part);
int GridTestCellCnt(int castle);
int CastleEquippedCells(void);
int LoadoutCellUsed(void);
void GridTestResetStage(void);
bool GridTestOfferOpen(void);
int GridTestDockTop(void);
void GridTestAdvanceWave(void);
bool GridTestIsOpen(void);
void DrawCmfPopUp(int, int, int, int, int, int, int, int, int, float zoom, int dir = LEFT);
void GNBDraw(int, int);
void BattleMinimapDraw(int x, int y, float zoom);
//---- PVP 진입 ----
//
//withUniverse 가 true 면 우주맵에서 상대를 찾는 화면부터 보여준다. 룰렛
//당첨으로 들어올 때는 그 화면을 룰렛이 이미 보여줬으므로 false 다.
void StartPvpTest(bool withUniverse = true);

//출정 준비를 PVP 용으로 연다. [세팅 완료] 를 누르면 판이 아니라 격돌로
//들어간다.
void LoadoutOpenForPvp(void);

//---- PVP 열 단계 ----
//
//pvpStageFighting 은 지금 붙고 있는 단계(1~PVP_STAGE_CNT), pvpFoeCastleLevel
//은 상대 성 단계다. VS 화면도 이 둘을 읽는다.
extern int pvpStageFighting;
extern int pvpFoeCastleLevel;
extern int pvpFoeProfileImg;
int PvpMyPower(void);
int PvpStageNow(void);
bool PvpStageOpponent(int stage, HOUSE* out);
void PvpStageClear(int stage);
void StartPvpTestBattle(void);
bool IsPvpCrewActing(int crewSlot);
int GetPvpSkillFreezeObj(void);
void PvpFinishCrewSkill(OBJECT* pObj);
void ExitPvpTest(void);
void PvpTestDraw(void);
void PvpTransitionCloudDraw(int transitionFrame);
void ActiveHelpDraw();
void LogDraw(LOG *);
void KeepLogFromDarken(LOG *);
int GetEventMenuPosX(int eventIdx, int eventStatus);
int GetEventMenuPosY(int eventIdx, int eventStatus);
void EventScheduler(void);
int GetEventMenuIdx(int eventType);
void DeleteEventMenu(int eventIdx);
void InitEventMenu(GAMEEVENT * gEvent, unsigned char type, unsigned char subType, short icon, long limitTime, int touchFunc);
void sortArray(int arr[], int index[], int n);
void MainMenuIn(void);
void ArrangeEventMenu(void);
void EventMenuDraw(GAMEEVENT *);
void GoldQuestMenuDraw(int x, int y, float zoom);
void GameOverDraw(int x, int y, float zoom);
void ClosePopUp(void);
void SetPopUp(int type, int x, int y, int w, int h,
	int itemType, int itemDetail, int itemGrade,
	int rewardType1, int rewardDetail1, int rewardGrade1, long long rewardStartCnt1, long long rewardEndCnt1,
	int rewardType2, int rewardDetail2, int rewardGrade2, long long rewardStartCnt2, long long rewardEndCnt2,
	int rewardType3, int rewardDetail3, int rewardGrade3, long long rewardStartCnt3, long long rewardEndCnt3);
void DrawPopUp(int idx);
void GameMenuDraw(int, int, float zoom);
void BossHpBarDraw(long long count, long long max, int x, int y, float zoom);
void VsHpBarDraw(long long count, long long max, int x, int y, int color,
	float zoom);
void WaveBadgeDrawBeforeBars(void);

void LobbyCastleMenuCommand(int func);

void PvpClashAdvanceNext(void);
void PvpClashToggleAuto(void);
bool PvpClashIsAuto(void);
