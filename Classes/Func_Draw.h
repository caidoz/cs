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
void TitleSkillViewerCommand(int command);
void TitleTermsCommand(int command);
void OpeningDraw(void);
void LobbyDraw(void);
void LoadoutDraw(void);				//출정 준비 화면
void StageMapOverlayDraw(void);		//이 판의 자리 열다섯
void StageMapSetOpen(bool on);
bool StageMapOpen(void);
bool LoadoutOpen(void);
void LoadoutSetOpen(bool on);
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
int LoadoutSlotInven(int slot);		//화면에 보이는 칸 -> 가방 번호
void LobbySkyUpdate(float delta);
bool LobbyCamTouchBegan(int id, float x, float y);
bool LobbyCamTouchMoved(int id, float x, float y);
bool LobbyCamTouchEnded(int id);

//---- 성 격자 인벤토리 시험판 (Func_Draw.cpp) ----
//시험이 끝나면 이 네 줄과 Func_Draw.cpp 의 블록을 통째로 지운다.
void GridTestDraw(void);
int GetStageInventoryTop(void);
float GetStageWorldLift(void);
void GridTestPick(int n, bool fromShop);
void GridTestRelease(void);
void GridTestToggle(void);
void GridTestSkipOffer(void);
void GridTestReroll(void);
void GridTestRefresh(void);			//시험용. 값 없이 세 칸을 다시 돌린다
int GridShopPrice(int base);		//성 할인을 거친 값				//값을 치르고 룰렛을 다시 돌린다
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
int GridTestTotalItemCount(void);
int StageGearList(int obj, StageSword* out, int maxCnt);	//누구든 장비 목록
int StageFoeGearList(StageSword* out, int maxCnt);	//지금 몬스터 장비
long long StageGearArmor(int obj);					//방어구 값의 합
void StageGearApplyStat(OBJECT* pObj);				//가방 장비 스탯을 더한다
long long StageGearReduce(int obj, long long damage);//방어구를 거친 피해
bool kShopPartIsSword(int part);
int GridTestCellCnt(int castle);
void GridTestResetStage(void);
bool GridTestOfferOpen(void);
int GridTestDockTop(void);
void GridTestAdvanceWave(void);
bool GridTestIsOpen(void);
void DrawCmfPopUp(int, int, int, int, int, int, int, int, int, float zoom, int dir = LEFT);
void GNBDraw(int, int);
void BattleMinimapDraw(int x, int y, float zoom);
void StartPvpTest(void);
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
