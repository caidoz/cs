#pragma once
#define BOX_OPEN_FRAME           10
#define BOX_OPEN_CHANGE_FRAME     6
#define BOX_CLOSE_FRAME           8

// 공격 줌
bool HitZoomOn(void);
void HitZoomPoint(int* x, int* y);
void HitZoomUpdate(void);
void HitZoomPause(void);
void HitZoomResume(void);
void SetFocusZoom(int obj);
void ClearFocusZoom(void);
void RequestFocusZoom(int obj, int priority);
void ClearFocusZoomRequest(void);

// Image Handling & Drawing
void LoadImg(int);
void LoadTexture(int);
void LoadSpriteFromTexture(int);
void LoadFontLabelFromString(std::string);
void AfterSpriting(cocos2d::Sprite*);
int GetSpriteIndex(int);
void FreeImg(int);
std::string GetResourceName(int, int);
void DrawBuffer(int x, int y, int w, int h, cocos2d::RenderTexture*);
void DrawArray(int, int, int, float zoom);
void RotateImage(int w, int h, int xs, int ys, int x, int y, bool flipX, float rotation, int effect, int alpha, float zoom, Vec2 anchorPoint, cocos2d::Sprite * src, int srcIdx);
void DrawImage(int w, int h, int xs, int ys, int x, int y, bool flipX, int cmfRotation, float rotation, int effect, int alpha, float zoom, cocos2d::Sprite * src, int srcIdx);
void DrawImageScale(int w, int h, int xs, int ys, int x, int y, bool flipX, int cmfRotation, float rotation, int effect, int alpha, float zoomX, float zoomY, cocos2d::Sprite* src, int srcIdx);
void ShadowImage(int, int, int, int, int, int, int, float);
void ProcessWave(void);
void Waterize(int, int, int, int);
void ZoomImage(int, int, int);
void GammaImage(int, int, float);
void InitContext(void);

// Screen Buffer / Render Target
void InitScreenBuffer(void);
void BeginScreenBuffer(void);
void EndScreenBuffer(void);
void PushRenderTarget(cocos2d::RenderTexture* dest, cocos2d::Layer* layer, bool clear = false);
void PopRenderTarget(void);
bool IsOffscreenTarget(void);

//스팟라이트. 매 프레임 켜주면 유지되고, 안 켜면 자동으로 꺼진다.
void SetSpotlight(float x, float y, float inner, float radius, float darkness);
void SetSpotlightKeepRect(float x, float y, float w, float h, float soft);

void SetSectionClip(int, int, int, int, bool);
void UnSectionClip(bool);
void SetColor(int);
void SetFontColor(int);
void ScreenDarken(int);
void MemRectFrameThick(int, int, int, int, int, int);
void MemRect(int x, int y, int w, int h, int fillCol);
void MemRectFrame(int, int, int, int, int);
void MemRectBoth(int, int, int, int, int, int);
void MemRectRound(int, int, int, int, int, int);
void DrawFrame(int, int, int, int, int);
void DrawWindow5(int x, int y, int w, int h, int mapIdx, float zoom, int mapOffsetY);
void DrawWindow4(int, int, int, int, int, float zoom);
void DrawWindow3(int, int, int, int, int, float zoom);
void DrawRoundBar(int x, int y, float percent, int type, int color, int alpha, float zoom);
void DrawGuage(int x, int y, int w, int h, long cur, long max, int bgCol, int fullCol, float zoom);
float DrawRouletteNumIcon(long long, int, int, int, bool, int align, float zoom);
void DrawLabelStr(int x, int y, char* str, float zoom);
void DrawLabel(int, int, int, float zoom);
void DrawStageLabel(int x, int y, int textIdx, int stage, int room, bool label, float zoom);
void DrawDiorama(int x, int y, int type, float zoom);
void DrawDioramaEnemy(int x, int y, int stage, int room, float zoom, int dropFrame);
void DrawDioramaCrew(HOUSE* housePtr, int x, int y, float zoom, int dropFrame, bool hand, bool star, int emoticon);
void DrawStageDiorama(int x, int y, int stage, int room, bool label, float zoom, bool cur, bool hand, bool star);
void GradiationFrame(int, int, int, int, int);
void SetBlend(int, int);
void UnSetBlend(void);
void SetAlpha(int);
float GetAlphaWidth(int, int, float);
float GetAlphaWidth2(int, float);
float GetGoldAlphaWidth(int idx, int type, float zoom);
void DrawGoldAlpha(int x, int y, int idx, int type, float zoom, int align, bool ani, float rotation);
void DrawGoldAlphaText(int x, int y, const char* text, int type, float zoom, int align, bool ani, float rotation);
void DrawAlpha(int x, int y, int idx, int type, float zoom, float rotation);
void DrawAlpha2(int x, int y, int idx, float zoom, float rotation);
void CenterAlpha(int, int, int, int, float, float);
void DrawAlphaFrame(int, int, int, int, int, float, float);
void addCommasToNumber(int number, bool showSign, char* result, size_t bufferSize);
int GetNumFigure(long long int);
float GetNumDx2(long long int num, int sign, int digit, bool comma, float zoom, bool fixed);
float GetNumDx(long long int num, int sign, int font, int digit, bool comma, float zoom, bool fixed);
float GetGoldNumDx(long long int, int, int, bool, float);
float GetBigNumGoldDx(long long int num, int sign, int font, int digit, bool comma, float width, float zoom);
float GetBigNumDxTTF(long long int num, int sign, int font, int digit, bool comma, float width, float zoom, bool fixed);
float GetBigNumDx(long long int num, int sign, int font, int digit, bool comma, float width, float zoom, bool fixed);
void DrawXNumGold(long long int num, int x, int y, bool ani, float zoom, int align, int digit);
void DrawSlashNum(int min, int max, int x, int y, float width, float zoom);
float DrawNumTTF(long long int num, int x, int y, int font, int align, int digit, bool sign, bool comma, float zoom, bool fixed);
void DrawNum2(long long int num, int x, int y, int align, int digit, int sign, bool comma, float zoom, bool fixed);
void DrawNum(long long int num, int x, int y, int font, int align, int digit, bool sign, bool comma, float zoom, bool fixed);
void DrawGoldNum(long long int num, int x, int y, int align, int digit, int sign, bool comma, float zoom);
void DrawBigNumGold(long long int num, int x, int y, int font, int align, int digit, int sign, float width, bool comma, float zoom);
float DrawBigNumTTF(long long int num, int x, int y, int font, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed);
void DrawBigNum(long long int num, int x, int y, int font, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed);
void DrawNum2AutoSpaceing(long long int num, int x, int y, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed, bool bold);
void DrawBigNum2Bold(long long int num, int x, int y, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed);
void DrawBigNum2(long long int num, int x, int y, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed);
void DrawStarNum(int icon, int star, int x, int y, float zoom);
void DrawStar(int icon, int x, int y, int cnt, int curMax, int max, int align, bool bigStar, float zoom);
void DrawHeartButton(int cnt, int x, int y, float zoom, bool ani, bool betFrame);
void DrawAttackButton(int cnt, int x, int y, float zoom, bool ani, bool betFrame, int downFrame);
void JoyStickDraw(int cnt, int x, int y, float joyDx, float joyDy, float joyPower, float zoom, bool ani, bool betFrame, int downFrame);
void DrawJumpButton(int cnt, int x, int y, float zoom, bool ani, bool betFrame, int downFrame);
int GetMaxShield(void);
int GetInitHeart(void);
int GetHeartAmount(void);
void LoadingBarDraw(int, int, int);
void DrawBuyButton(int x, int y, int w, int h, int fra, int frameColor, long long amount, int currency, float zoom, bool ani, int sign, float discount);
void DrawTextButton(int x, int y, int w, int h, int fra, int gray, float zoom, bool ani, int textIdx);
void DrawMaxButton(int x, int y, int w, int h, int alphaIdx, float zoom);
void DrawTouchButton(int, int, const char*, int);
void DrawTouchLargeButton(int, int, int, int, const char*, int, int, float zoom);
void DrawAlarmMark(int x, int y, int count, float zoom);
void DrawPlusMark(int x, int y, float zoom);
void DrawXMark(int x, int y, float zoom);

// Item Showing
void DrawIcon(int idx, int x, int y, float zoom, int solid, bool ani, bool shadow, float thickness);
int GetHeroSkillIcon(int heroSkillIdx);
void DrawSkillIcon(int, int, int, float);
void DrawCrewBulletIcon(int idx, int x, int y, float zoom);
int GetCrewBulletAni(int idx);
//x, y는 아이콘의 한가운데다(DrawCrewBulletIcon()은 좌상단).
void DrawCrewBulletAni(int idx, int x, int y, float zoom, int ani, int aniFrame);
void DrawSkillCard(int skillIdx, int lv, int x, int y, float zoom, int iconOverride = 0);
void DrawLock(int lv, int x, int y, float zoom);
void DrawPercent(float num, int x, int y, float zoom, int align);
void DrawLv(int lv, int x, int y, float zoom, int align);
void DrawItemIcon(ITEM* it, OBJECT* pObj, int x, int y, float zoom);
void DrawMedalReward(int attackTypeIdx, int x, int y, int w, int h, int step, int str, bool ani, float zoom);
void DrawRedDot(int x, int y, int color, int num, float zoom);
int GetUpgradeLv(int type);
void DrawLevelUpCard(int type, int lv, bool locked, int x, int y, float zoom);
void DrawRewardCardRange(int type, int grade, int detail, long long startCnt, long long endCnt, int x, int y, float zoom, bool cardFrame);
void DrawRewardCard(int type, int detail, int grade, int lv, long long count, int x, int y, bool ani, float zoom, int cardFrame, bool newItem, bool showValue, int curStar, int maxStar, bool shadow, int openFrame);
float GetEquipIconWidth(int itemType, int itemDetail, int itemGrade, float zoom);
void DrawEquipIcon(int itemType, int itemDetail, int itemGrade, int x, int y, float zoom, bool iconAni);
void DrawItemValue(int itemType, int itemDetail, int itemGrade, int itemLv, int x, int y, int align, int plusLv, float zoom, float numWidth);
void DrawRouletteCard(int actionCardIdx, int str, int x, int y, float zoom, int alpha, bool ani, int owner, int lockOpenFrame);
void HitCountCheck(OBJECT* pObj);
void DrawHitCount(OBJECT* pObj, int x, int y, float zoom);
void DrawCycle(int x, int y, int w, int h, int cycle, int full, float zoom);
void DrawTime(int x, int y, int atime, int type, int align, float zoom);
void DrawRemainTime(int x, int y, long long remainSec, int align, float zoom);
void PushButtonDraw(int betType, int x, int y, int motion, float zoom, bool autoPlayText);
void DrawHand(int, int, int, float);
void DrawScroll(int x, int y, int h, int type);
void YesNoDraw(int, int);
void DrawEmptyBox(int, int, int, int);
void BoxInfoDraw(int boxType, int x, int y, float zoom);
void DrawBox(int boxType, int x, int y, int dirX, int motion, int solid, bool ani, bool opened, bool shadow, float zoom);
void OpenBox(OBJECT* pObj);
void DrawCastleBoxXY(int index, bool opened, int dirX, int x, int y, int color, float zoom);
void DrawCastleBox(OBJECT* pObj);
void BoxDraw(OBJECT* pObj);
