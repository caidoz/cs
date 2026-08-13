#include "Core.h"

// ===== Shader 문자열 정의 =====
const char* vsh_gray = R"(
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main()
{
	gl_Position = CC_PMatrix * a_position;
	v_fragmentColor = a_color;
	v_texCoord = a_texCoord;
}
)";

const char* fsh_gray = R"(
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main()
{
	vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	float gray = dot(v_orColor.rgb, vec3(0.2126, 0.7152, 0.0722));
	gl_FragColor = vec4(gray, gray, gray, v_orColor.a);
}
)";

const char* vsh_white = R"(
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main()
{
	gl_Position = CC_PMatrix * a_position;
	v_fragmentColor = a_color;
	v_texCoord = a_texCoord;
}
)";

const char* fsh_white = R"(
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main()
{
	vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	float white = dot(v_orColor.rgb, vec3(1.0, 1.0, 1.0));
	gl_FragColor = vec4(white, white, white, v_orColor.a);
}
)";

const char* vsh_lighten = R"(
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;
uniform		mat4 u_MVMatrix;
uniform		mat4 u_PMatrix;
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main()
{
	gl_Position = u_PMatrix * u_MVMatrix * a_position;
	v_fragmentColor = a_color;
	v_texCoord = a_texCoord;
}
)";

const char* fsh_lighten = R"(
#ifdef GL_ES
precision lowp float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform sampler2D u_mask;
void main()
{
	vec4 vC = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	gl_FragColor = vec4(vC.r * 1.2, vC.g * 1.2, vC.b * 1.2, vC.a);
}
)";

//스팟라이트 쉐이더. 화면버퍼 한 장에 통째로 걸어 특정 위치만 밝게 남기고
//나머지를 어둡게 덮는다. 예전 ProcessRadius()가 DX*DY/2 감쇠 테이블을 미리
//만들어 두던 것을 픽셀마다 매 프레임 계산하는 것으로 대체한다.
const char* vsh_spotlight = R"(
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main()
{
	gl_Position = CC_PMatrix * a_position;
	v_fragmentColor = a_color;
	v_texCoord = a_texCoord;
}
)";

const char* fsh_spotlight = R"(
#ifdef GL_ES
precision mediump float;
#endif
uniform vec2  u_resolution;	//(DX, DY)
uniform vec2  u_texScale;	//텍스처가 2의 거듭제곱으로 패딩된 만큼 보정. 안 되면 (1, 1)
//스팟은 여러 개를 동시에 켤 수 있다(MAXSPOTLIGHT). 안 쓰는 칸은 중심을 화면 밖 멀리,
//inner=0/radius=1로 채워 보내므로 아무 데도 밝히지 않는다. 개수를 uniform으로 넘겨
//분기하지 않는 이유는 GLSL ES 1.00에서 루프 조건에 uniform을 쓰기 까다롭기 때문이다.
uniform vec2  u_center[4];	//스팟 중심. 픽셀 좌표
uniform float u_inner[4];	//여기까지는 원본 밝기 그대로
uniform float u_radius[4];	//여기부터 바깥은 완전히 어두움
uniform float u_darkness;	//바깥 밝기. 0.0이면 완전 검정
//암전에서 뺄 사각형도 여러 개다(대화창 + 로그창처럼 동시에 떠 있을 수 있다).
//안 쓰는 칸은 폭 0으로 보내면 건너뛴다.
uniform vec4  u_keepRect[2];	//(x, 윗변 y, 폭, 높이)
uniform float u_keepSoft[2];	//사각형 가장자리가 풀어지는 폭
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main()
{
	vec4 color = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);

	//RenderTexture는 화면보다 큰 텍스처에 담길 수 있어 v_texCoord가 0~1이 아니다.
	//먼저 0~1로 되돌린다. RenderTexture 스프라이트는 setFlippedY(true)라
	//이 좌표의 y=1이 화면 위쪽, 즉 게임 좌표의 y=DY와 그대로 맞는다.
	vec2 uv = v_texCoord / u_texScale;

	//정규화 좌표로 거리를 재면 화면비 때문에 원이 타원이 된다. 픽셀 좌표로 환산해서 잰다.
	vec2 sp = uv * u_resolution;

	float light = 0.0;

	for (int i = 0; i < 4; i++) {
		float d = distance(sp, u_center[i]);
		light = max(light, 1.0 - smoothstep(u_inner[i], u_radius[i], d));
	}

	//대화창/로그창처럼 암전에서 빼야 하는 영역. 사각형 바깥까지의 거리로 가장자리를 풀어준다.
	for (int k = 0; k < 2; k++) {
		if (u_keepRect[k].z > 0.0) {
			vec2 halfSize = vec2(u_keepRect[k].z, u_keepRect[k].w) * 0.5;
			vec2 rectCenter = vec2(u_keepRect[k].x + halfSize.x, u_keepRect[k].y - halfSize.y);
			vec2 q = abs(sp - rectCenter) - halfSize;
			float rd = length(max(q, 0.0)) + min(max(q.x, q.y), 0.0);

			light = max(light, 1.0 - smoothstep(0.0, u_keepSoft[k], rd));
		}
	}

	light = mix(u_darkness, 1.0, light);

	gl_FragColor = vec4(color.rgb * light, color.a);
}
)";

GLProgram* shader_gray;
GLProgram* shader_white;
GLProgram* shader_lighten;
GLProgram* shader_spotlight;
GLProgram* shader_outline;
GLProgramState* shader_state_outline;
GLProgramState* shader_state_default;

BlendFunc BLEND_ORIGIN;
BlendFunc BLEND_BLENDMODE;
BlendFunc BLEND_LIGHTEN;
BlendFunc BLEND_SHADOW;

ReelJumpState gReelJump[TOTALREEL];
// [MOD-G] “3개 확정 후 종료 딜레이” 카운터
int sEndDelayLeft = -1;

int logIndex;

//시스템
cocos2d::Sprite* sprite[TOTALIMG];
cocos2d::Texture2D* texture[TOTALIMG];
//없으면 이미지 추가(없다는 기준은 rendeSpriteIndex == -1 이면
cocos2d::Sprite* renderSprite[MAXRENDERCNT];//이미지 신규생성시 사용
int renderSpriteIndex[MAXRENDERCNT];//이미지 신규생성시 사용 - 렌더스프라이트가 TOTALIMG 중에 몇번을 담았는가
//0값이 기본이고 이미지가 생성되면 카운트가 하나 늘어나는거지
int sameRenderSpriteMax[TOTALIMG];//현재 최대 몇개까지 추가되었는가
//현재 sameRenderSpriteMax에 도달하지 않았는지를 판단해서 기존것을 사용하고 하나씩 카운트를 증가시키는거지
int sameRenderSpriteCur[TOTALIMG];//이번 드로우에 몇개까지 쓰고 있는가.(프레임마다 초기화됨)
int sameRenderSpriteArr[TOTALIMG][3000];//배열에 특정인덱스의 이미지를 렌더스프라이트 몇번에 들어가있는지를 저장하는 배열
int curRenderSpriteArr[MAXRENDERCNT];
int getSpriteIdx;
int getSpriteTexture;
int totalRenderCnt = 0;//현재 그려야 하는 총 개수
int curRenderCnt = 0;//현재 그려야 하는 총 개수

//없으면 이미지 추가(없다는 기준은 rendeSpriteIndex == -1 이면
cocos2d::Sprite* bufferSprite[MAXBUFFERSPRITECNT];//이미지 신규생성시 사용
int bufferSpriteIndex[MAXBUFFERSPRITECNT];//이미지 신규생성시 사용 - 렌더스프라이트가 TOTALIMG 중에 몇번을 담았는가
//0값이 기본이고 이미지가 생성되면 카운트가 하나 늘어나는거지
int sameBufferSpriteMax[TOTALIMG];//현재 최대 몇개까지 추가되었는가
//현재 sameRenderSpriteMax에 도달하지 않았는지를 판단해서 기존것을 사용하고 하나씩 카운트를 증가시키는거지
int sameBufferSpriteCur[TOTALIMG];//이번 드로우에 몇개까지 쓰고 있는가.(프레임마다 초기화됨)
int sameBufferSpriteArr[TOTALIMG][60 * 47];//배열에 특정인덱스의 이미지를 렌더스프라이트 몇번에 들어가있는지를 저장하는 배열
int curBufferSpriteArr[MAXBUFFERSPRITECNT];
int getBufferSpriteIdx;
int getBufferSpriteTexture;
int totalBufferCnt = 0;
int curBufferCnt = 0;

int bufferSpriteCnt = 0;

int tileBufferSpriteIndex;

//#ifdef TTFFONT
Vec2 labelPosition;
std::string compareString;
std::string labelString;

TTFConfig ttfconfig;
cocos2d::Label* fontLabelWidth;//폰트 넓이용 넓이
cocos2d::Label* fontLabel[MAXFONTLABELCNT];//라벨 신규생성시 사용
int fontLabelIndex[MAXFONTLABELCNT];//라벨 신규생성시 사용 - 텍스트라벨이 폰트라벨 중 몇번을 담았는가
int fontLabelMotherIndex[MAXFONTLABELCNT];//만약 복제가 되는 경우 몇번을 복제한 것인가
int sameFontLabelMax[TEXT_LENGTH];//현재 최대 몇개까지 추가되었는가
int sameFontLabelCur[TEXT_LENGTH];//이번 드로우에 몇개까지 쓰고 있는가.(프레임마다 초기화됨)
int sameFontLabelArr[TEXT_LENGTH][100];//배열에 특정인덱스의 라벨을 렌더스프라이트 몇번에 들어가있는지를 저장하는 배열
int curFontLabelArr[MAXFONTLABELCNT];//하나 추가될때마다 인덱스를 추가한다

int getFontLabelIdx;
int getFontLabelTexture;

int totalFontLabelCnt = 0;
int curFontLabelCnt = 0;
#ifdef BMFONT
cocos2d::LabelBMFont* textLabel[MAXLABELCNT];
#else
cocos2d::Label* textLabel[MAXLABELCNT];
#endif

int textLabelIndex[MAXLABELCNT];//라벨 신규생성시 사용 - 텍스트라벨이 TOTALIMG 중에 몇번을 담았는가
//0값이 기본이고 이미지가 생성되면 카운트가 하나 늘어나는거지
int sameTextLabelMax[TEXT_LENGTH];//현재 최대 몇개까지 추가되었는가
//현재 sameRenderSpriteMax에 도달하지 않았는지를 판단해서 기존것을 사용하고 하나씩 카운트를 증가시키는거지
int sameTextLabelCur[TEXT_LENGTH];//이번 드로우에 몇개까지 쓰고 있는가.(프레임마다 초기화됨)
int sameTextLabelArr[TEXT_LENGTH][100];//배열에 특정인덱스의 이미지를 렌더스프라이트 몇번에 들어가있는지를 저장하는 배열
int curTextLabelArr[MAXLABELCNT];
int getTextLabelIdx;
int getTextLabelTexture;

int totalTextLabelCnt = 0;
int curTextLabelCnt = 0;

//MC_GrpContext gContext;
cocos2d::RenderTexture* gScreenBuffer;//Screen Buffer
cocos2d::Layer* gScreenLayer;//Screen Buffer

cocos2d::RenderTexture* gRenderTarget = nullptr;
cocos2d::Layer* gRenderLayer = nullptr;

//스팟라이트 상태. 매 프레임 SetSpotlight()으로 세우고 EndScreenBuffer()가 소비한 뒤 끈다.
//드로우 코드가 그리던 자리에서 바로 켤 수 있는 즉시모드 방식이라 꺼주는 걸 잊어도 남지 않는다.
//한 프레임에 SetSpotlight()을 여러 번 부르면 밝은 지점이 그만큼 늘어난다(gSpotlightCnt).
bool gSpotlightOn = false;
int gSpotlightCnt = 0;
float gSpotlightX[MAXSPOTLIGHT] = { 0.0f };
float gSpotlightY[MAXSPOTLIGHT] = { 0.0f };
float gSpotlightInner[MAXSPOTLIGHT] = { 0.0f };
float gSpotlightRadius[MAXSPOTLIGHT] = { 0.0f };
float gSpotlightDarkness = 0.0f;

//튜토리얼에서 지금 눌러야 하는 터치기능. -1이면 제한하지 않는다.
//프레임 시작(터치영역 초기화 지점)에서 GetTutorialTouchFunc()으로 한 번 정한다.
//튜토리얼 안내 대사에서 누른 버튼의 동작을 컷씬이 끝난 뒤 실전투에서 처리하기 위한 예약.
//대사 중에는 keyHandle이 MK_TALK이라 ReleaseCore()가 TalkKey()로만 보내고, 그 동작을 실제로
//수행하는 PlayKey()까지 가지 못한다(동료 바를 눌러도 메뉴가 안 열리고 대사만 끝나던 원인).
//눌린 터치기능을 담아두면 Play()가 플레이로 돌아온 뒤 그대로 처리한다. 0이면 예약 없음.
int tutorialPendingTouchFunc = 0;

//튜토리얼 안내로 동료 메뉴를 연 직후, 새 동료 카드를 눌러 상세보기로 들어갈 때까지만 참.
//저장하지 않는다 - 그 자리에서만 도는 안내라 세이브에 남으면 일반 플레이까지 물든다.
bool tutorialCrewGuide = false;

//장착 버튼부터 성 위 등장까지의 안내 단계. 역시 저장하지 않는다.
int tutorialCrewStep = TUTORIAL_CREWSTEP_NONE;
int tutorialCrewStepFrame = 0;

//장비 장착 안내 단계. 슬롯 고르기부터 성 위 주인공이 갈아입는 것까지.
int tutorialEquipStep = TUTORIAL_EQUIPSTEP_NONE;
int tutorialEquipStepFrame = 0;

//룰렛이 열렸다는 것을 알리는 반짝임. 남은 프레임 수. 0이면 안 그린다.
int rouletteGlowFrame = 0;

//튜토리얼 마지막 보스전: 룰렛 결과를 가장 별이 높은 동료 3개로 강제한다.
//한 번 쓰고 꺼진다(RouletteAttackStart에서 소비).
bool tutorialForceRouletteBest = false;


int gTutorialTouchFunc = TUTORIAL_TOUCH_FREE;
int gTouchHitFunc = TUTORIAL_TOUCH_NONE;

//암전에서 뺄 사각형. 대화창/로그창처럼 스팟과 별개로 밝게 남겨야 하는 UI에 쓴다.
//스팟과 마찬가지로 한 프레임에 여러 번 부르면 그만큼 늘어난다.
int gSpotlightKeepCnt = 0;
float gSpotlightKeepX[MAXKEEPRECT] = { 0.0f };
float gSpotlightKeepY[MAXKEEPRECT] = { 0.0f };
float gSpotlightKeepW[MAXKEEPRECT] = { 0.0f };
float gSpotlightKeepH[MAXKEEPRECT] = { 0.0f };
float gSpotlightKeepSoft[MAXKEEPRECT] = { 0.0f };

cocos2d::Layer* bufferLayer[TOTALBUFFER];
cocos2d::RenderTexture* bufferTexture[TOTALBUFFER];

#ifdef ATLAS
cocos2d::Sprite* renderAtlas;
#endif

cocos2d::CCImage* fontImage;
int fontImageWidth;
int fontImageHeight;
long fontImageDataLen;

//cocos2d::Sprite* fontImageSolid;
unsigned char* fontImageData;


int* gScreenPtr, * gImagePtr;
cocos2d::Sprite* atlas;
cocos2d::SpriteFrameCache* Cache;

int fontColorIdx[MAXFONTCOLOR];
float global_z;
int nextSeed, tms;
char selectedChar;

int audioID[TOTALMUSIC];
float audioVolume[TOTALMUSIC];

signed short curID;
char netCritical;
char phone[20];
signed char touchQuick = false;
signed char touchQuickIcon = false;
signed char touchDrawButton = false;
signed char touchDrawYesNo = false;
signed char touch;
int touchIndex;
int touchRect[TOTALTOUCHCNT][5];//int rx, int ry, int width, int height, int func
int startTouchRect[5];
int swipeIndex;
int swipeRect[TOTALSWIPECNT][5];//int rx, int ry, int width, int height, int func
bool swipeLock = false;
unsigned char rapidSwipe = false;
signed char DrawButton_OK;
int touch_Select;
signed char touchDownBar = false;
signed char touchOK = false;
signed char touchYESNO = false;
signed int pointX;
signed int pointY;
signed int pointType;
signed int clipX;
signed int clipY;
signed int clipX2;
signed int clipY2;
signed int clipX3;
signed int clipY3;
signed int clipX4;
signed int clipY4;
ClippingNode* clipNode;
signed short STATUSWIN_Y;//전투를 위한 
signed short STATUSWIN_Y_INIT;//초기값
signed short STATUSWIN_Y2;
signed short PLAYAREA_X = 20 * TSIZE;
signed short PLAYAREA_Y = 20 * TSIZE;
signed char yesnoFrame = null;
signed char buy_Mode;

unsigned char imgLoaded;

//추가 다운로드 변수
#ifdef DOWNLOAD
signed char isDown = false;	//추가다운 받았는지 여부//startCelt에서 검색
signed char oldDraw;	//올드변수를 저장하고있다가, 다운로드 완료시 해당 상태로 돌려준다.
#endif

int thickColor;
int fontColor, oldColor;
int baseColor;

const char* textString;	//프레임텍스트용 스트링
unsigned short textStringLength[50];
unsigned short textStringOffset[50];
unsigned char textStartColor[50];
unsigned short textFrame;	//프레임따라 점점 찍힐때 사용
unsigned char textPage;	//원래 길이가 몇페이지 짜리인지 사용
unsigned char textCurPage;	//현재 몇번째 페이지인가
unsigned char textLines;	//몇줄짜리냐
unsigned char textBalloonFrame;

int popUpFrame;

int VERSION;
signed char m_lgrpAlpha;
signed char zoomFrame;
unsigned short waveFrame;
unsigned char* viewRadius;
unsigned char* viewRadius2;
signed char grayScale;
signed char blendDepth;
int blendColor;


unsigned short realRate;
unsigned short refreshRate;
unsigned char mustRefresh = true;
signed char running = true;
signed char resumeFlag = false;

//키조작
int systemKey = null;
int systemRelease = null;
int lastPressedKey;
int realPressedKey;
int releasedKey;
int releaseFrame;
int touchPressedKey[MAXKEYPRESSED][2];
int touchX, touchY;
int startTouchX, startTouchY;
int endTouchX, endTouchY;
bool startTouchCheck = false;

signed char touchMode = null;
signed char touchModeOld = null;
signed char isTouchKey;
signed char twice_released = false;
signed char is_key_pressed = false;
signed char is_key_released = false;
signed char is_press_finished = true;
signed char is_release_finished = true;
signed char key_released = false;
signed char keyLock = false;
signed char multiKey;
signed char keyStatus;
int clearFrame;
int releaseClearFrame;
signed char is_touchkey_pressed = false;

//int keyCount = 0;

unsigned char keyHandle, drawHandle, before_DrawHandle, before_KeyHandle, before_DrawHandle_Gacha, before_CurMenu_Gacha, before_KeyHandle_Gacha, before_DrawHandle_Collections, before_KeyHandle_Collections, before_DrawHandle_NewCard, before_KeyHandle_NewCard, next_DrawHandle, next_KeyHandle, before_DrawHandle_StageClear, before_KeyHandle_StageClear;
unsigned short DX, DY;
unsigned short TILEDX, TILEDY;
unsigned short REALDX, REALDY;
unsigned short SCREENRATIO;
unsigned short BLAHBLAHDRAWSTARTY;
unsigned short RANKINGDRAWSTARTY;
unsigned short SKILLDRAWSTARTY;
unsigned short POPUPPOSITION_Y;
unsigned short notch;
signed int offX, offY;
signed int xOffset;
signed int rw, rh, rx, ry;
signed int frame, demoFrame, timeFrame, touchFrame, touchedFrame, cageFrame = 0;
unsigned char infoType, infoData;
unsigned short infoText, infoFrame, explainFrame, explainText, battleStartFrame;
unsigned short skillInfoFrame;
unsigned short ringFrame;
signed int curSkill;
signed int areaFrame;
signed int phaseFrame;
unsigned char itemFrame;
unsigned char npcGetFrame;
unsigned char stageClearFrame;
unsigned short skillGetFrame;
unsigned short buffItemFrame;
unsigned short getSkill;
unsigned char totalDmgUpdateFrame;
unsigned char onceDmgUpdateFrame;
unsigned char nameFrame, nameObj;
signed char warpFrame, returnFrame;
unsigned char curEnemyFrame;	//현재 적 이름이 몇프레임동안 떠 있나
signed int curEnemy = ENEMY;	//현재 공격중인 몬스터가 누구냐
signed int curPlayer = ROBIN;	//현재 공격받고 있는 주인공은 누구냐
signed char newStart;
signed int gameOverFrame;
signed int questFrame;
signed int alert;
unsigned char minimapFrame;
unsigned char dianaTrapFrame;
signed int volumeFrame;
unsigned char vibrationFrame;
signed int lenzFlag;
unsigned char radiusStatus;


char tempStr[256];
char tempStr2[256];
char tempStr3[256];
char labelStr[512];
char labelStr2[512];
char labelStr3[256];
char skillStr[256];
char ringStr[256];
char skillStr2[256];//스킬상세설명
char ringStr2[256];
char skillStr3[256];//스킬이름
char skillToolTips[256];//스킬이름
char skillBodyStr[256];
char buffItemStr[256];
char buffItemStr2[256];
char infoStr[100];
LOG gameLog[MAXLOG];
LOG battleLog[MAXBATTLELOG];
char optionStr[TOTALMENUOPTION][50];
char itemOptionStr[50];
char screenStr[100];
char playerTitle[24];
char phoneStr[10][8];
int bmFontColor[512];

#ifndef KTF

ROBINDATA robin;
GAMEDATA game;
ALLOCED a;

#else

#ifdef RELOCATE
int dRes;
int robinRes;
int gameRes;
int ac;

DATA* d;
ROBINDATA* robin;
GAMEDATA* game;
ALLOCED* a;
#else
DATA d;
ROBINDATA robin;
GAMEDATA game;
ALLOCED a;
#endif

#endif

char setStr[7][36];
char gemStr[6][20];
char dmgStr[100];
char recipeName[40];
char recipeDesc[TOTALARENA];
char recipeDmg[20];
char itemName[40];
char defaultStatStr[40];

OPTION option;
EFFECT effect;
MOVIE movie;
POPTALK talk;
DMGINFO dmgInfo[TOTALHITMARK];
DMGINFO imgText[TOTALHITMARK];
HITMARK hitMark[TOTALHITMARK];
ICONMARKARR currencyMarkArr[TOTALCURRENCYMARKARR];
ICONMARKARR currencyMarkArr_PopUp[TOTALCURRENCYMARKARR];
ICONMARK currencyMark[TOTALCURRENCYMARK];
ICONMARK currencyMark_PopUp[TOTALCURRENCYMARK];
ICONMARK itemMark[TOTALITEMMARK];
ICONMARK controlMark[TOTALCONTROLMARK];
ICONMARK controlMarkBack[TOTALCONTROLMARK];
bool controlerSpread[TOTALCONTROLMARK];
ICONMARK cardMark[TOTALCARDMARK];
ICONMARK cardMarkBack[TOTALCARDMARK];
//메인보상리스트(여기에 한번 받는 모든 보상 시퀀스 1depth가 들어간다.)
ICONMARK rewardMark[TOTALREWARDMARK];
ICONMARK rewardMarkBack[TOTALREWARDMARK];
ICONMARK rewardMark_PopUp[TOTALREWARDMARK];
//가챠용 박스마크. (가챠를 들어갔을 때 여러개의 박스가 있으면 모두 여기 들어간다.)
ICONMARK boxMark[TOTALBOXMARK];
//박스에서 카드를 깔 때 나오는 것들
ICONMARK boxCardMark[TOTALCARDMARK];//보조박스에서 나온 리워드마크
//소울마크
ICONMARK soulMark;
ICONMARK goldAlphaMark[TOTALGOLDALPHAMARK];

//배틀에서 쓰이는 전투
OBJECT ao[TOTALOBJECT];
BAR bar[TOTAL_BAR];

TEMPSAVE tempSave[3];
CURRENCYEFFECT currencyEffect[TOTAL_CURRENCY];
signed short crX, crY, crW, crH;

char saveMem[sizeof(ROBINDATA)];
char backupMem[sizeof(ROBINDATA)];

//맵 관련 변수
unsigned short focus;
signed short loadedMap;
unsigned char mapData[15];
unsigned char mapArray[3000];
unsigned char mapInfoArray[3000];
unsigned short mapInfoOff;
unsigned char mapRect[MAXRECT * 5];
signed short mapBackObj[MAXBACKOBJ * 3];
signed short mapForeObj[MAXFOREOBJ * 3];
signed short mapNeutralObj[MAXNEUTRALOBJ * 4];
unsigned short mapEnemyObj[TOTALARENA * 4];
signed short bubbleXY[6 * 2];
signed char fadeFrame;
signed char dontWarp;
int fadeColor;


//Splash
POSITION splash;
BGOBJ bgObj[MAXBGOBJECT];
unsigned char splashType;

//TALK 관련 변수
unsigned char talkShakeFrame;

int touchCount;

//cmf 관련 변수
unsigned char costumeImg[MAXPLAYER];
signed short cmfLoaded[REALMAXCMF];	//Loaded Cmf Num
unsigned short cmf_m_cnt[REALMAXCMF];	//Motion Count
unsigned short cmf_i_cnt[REALMAXCMF];	//Image Count
unsigned short cmf_v_cnt[REALMAXCMF];	//Variable Array Length
signed short cmf_i_div[REALMAXCMF][6];	//Image Sprite Relation Info
signed short* old_cmf_ptr[REALMAXCMF];
const unsigned short* cmd_i_offset[REALMAXCMF];	//Image Offset
const unsigned short* cmd_m_cnt[REALMAXCMF];	//Image Count Per Motion
const signed short* cmd_m_crash[REALMAXCMF];	//Crash Area Per Motion
const signed short* cmd_m_img[REALMAXCMF];	//Part Image Num And Offset

signed short cmf_status_data[REALMAXCMF][MAXSTATUS][1024];
const signed short* cmf_change_data[REALMAXCMF];

//플레이어 움직임 관련 변수
const unsigned short* skillStartFrame;
const unsigned short* skillClosingFrame;
const unsigned char* skillMotion;
unsigned char whichPlayer;
unsigned char isDemo;
unsigned short attackDelay;
int sequenceDelay;
unsigned char skillUsed;
unsigned char buffItemUsed;
unsigned char ringUsed;
unsigned char ringUser;

ESCORT escort;
signed char demoPlayerX[SOLDIER + 1];
signed char boomerangAway[SOLDIER + 1];
signed short pDx, pDy;
unsigned char currentQuest;
unsigned char currentTimeQuest; //현재 타임퀘스트 저장.
unsigned short TimeFailDemo;    // 타임퀘스트 실패시 동작해야하는 데모신 저장
unsigned char darkStone;
unsigned char npcdarkStone;

//플레이어 이미지 관련 변수

//문 이미지 관련 변수
unsigned char doorCmf[MAXDOOR];
unsigned char doorCnt;

//아이템 관련 변수
ITEM tempItem;
ITEM helpItem[MAXHELPITEM];
int tempItemIdx;//인벤토리의 몇번인지
signed short itemObj;
unsigned char tempFishItem;
unsigned char nInvenMax, nInvenCnt, nShopCnt;
//int needErase[10];
int shopDesc[MAXNETSHOP];
int cItem;
ITEM focusItem;
int boxNeutral;
int cNeutral;
int progress;
unsigned char extraArmor;
int shopGachaItemCnt = 1;

//메뉴관련 변수
signed char yesNo;
signed char menuDepth;
signed char rewardDepth;
signed char gachaDepth;
signed char newCardDepth;
signed char newCollectionDepth;
signed char stageInfoDepth;
signed int curMenu;//타이틀메뉴, 게임메뉴의 메인값
signed int curHouse;//현재 선택되어 있는 집
signed int curHero;//현재 히어로
signed int curMenuBack;
signed int curEventIdx;//현재 이벤트
int menuFrame;//메뉴 프레임
int menuTalkFrame;//메뉴 프레임 보조
int menuWinFrame;//메뉴 윈도우 프레임
int menuPage, menuPage2;//메뉴페이지
int menuCur;	//위아래로 넘기는 메뉴에서 사용
int menuX, menuY;//x, y로 이동하는 메뉴에서 사용
int menuResult;
int hotKeyFrame;
int menuAni;
int winAniFrame;
int winUpgradeFrame;
int rewardFrame;
int gachaFrame;
int newCardFrame;
int newCollectionFrame;
int stageInfoFrame;
int gachaIndex;//현재 뽑고 있는 상자의 인덱스
int gachaCardIdx;
int stageRewardIdx;
int helpPage;
int helpScene;
int helpFrame;
unsigned char enchantResult;
unsigned char shopType;

int menuIdx, menuIdx2;	//맨 상단 페이지
int menuFocus, menuFocus2;	//현재 어디냐
int menuInfo, menuWindow;	//정보창을 띄울 경우
int menuMessage;//작은 창 0이면 off
int menuItem, menuItem2, menuItem3, menuItem4;
int menuCount;
int menuType;
int menuCountCursor;	//상점에서 사고 팔때 갯수 정하는거
int menuItemCount;	//상점에서 표시되는 갯수
int menuIcon;
signed short invenRecipe[TOTALINVENTORY];	//인벤토리에 레시피
signed short invenRecipeCnt;	//인벤토리에 총 몇개가 있는지
int enchantSlot[INVEN_HCNT];
int enchatSlotCnt;
signed short invenGemCnt;

//스크롤 관련 변수
//scS, scE, scT, scC, scP (인벤토리)
//scS2, scE2, scT2, scC2, scP2 (인벤토리)

//스크롤이 필요한 메뉴

signed int scS[TOTAL_MENU];
signed int scE[TOTAL_MENU];
signed int scT[TOTAL_MENU];
signed int scC[TOTAL_MENU];
signed int scP[TOTAL_MENU];

signed int isS, isT, isE, isC;
//scY의 추가 두가지는 하나는 
signed int scX, scY[TOTAL_MENU], snapTargetY[TOTAL_MENU];//x, y 스크롤
signed int scY_Log, scT_Log;

unsigned char scDir = 0;//0이면 스크롤이 없는거고, 1이면 수평, 2명 수직이다.
signed short scRecoveryFrameX, scRecoveryFrameY, scAccelY;//복구
int autoScroll;//자동으로 스크롤을 시킬건지
int autoScrollGap;//해당 프레임에 진행할 스크롤 크기

bool keyCoreDisable = false;
unsigned char vibLevel;
unsigned char stoneWhere;
unsigned short charInfoPage;

int INVEN_VCNT = 4;//인벤토리 세로 몇개인가
int INVEN_TCNT = INVEN_HCNT * INVEN_VCNT;
int GNBHEIGHT = GNB_INIT_HEIGHT;
int BOTTOMMENUHEIGHT = BOTTOMMENU_INIT_HEIGHT;
int NORCH_HEIGHT = 94;
int HOMEBAR_HEIGHT = 54;

REPORTVAR rpVar;
REPORTVAR2 rpVar2;
signed char* rpPtr;

//투기장 & 레이드 관련 변수
unsigned char startFrame;	//게임자체가 로드가 되서 시작할 때 쓰는 프레임
unsigned char startPageCur;	//현재 몇번째 페이지를 가르키고 있는지
unsigned char startPageMax;	//최대 보여줘야 되는 스타트 페이지들이 몇장인지 보여주는 프레임
unsigned char startPage[MAXSTARTPAGE];

unsigned char arenaFrame;	//투기장 시작, 정지 프레임
unsigned char arenaFloorTime;	//다리 열리는 시간
int arenaLimitTime;	//투기장 남은 시간
long arenaTotalTime;	//투기장 타임 (현재 1800초(30분)로 설정됨. 변경시 ArenaResult 소요시간 수정해야함.
unsigned char arenaNpcCnt;
unsigned char arenaResultMember[2];
int arenaGold;
int arenaMedal;
int arenaSoldier;
int arenaIron;
int arenaGoldForGetItem;
unsigned short oldMap;
unsigned short oldX, oldY;
unsigned char oldO2;

int raidInfo[TOTALRAIDSELECTED * RAIDARRAYDATASIZE];//어떤 보스를 내보내고, 어떤 보상을 줄지 결정(보상은 타입, 디테일, 등급 세가지로 결정)


unsigned short arenaFloor;//현재 몇층인지(지하1층부터~~)
signed short arenaScore;
unsigned short arenaKill;	//적 죽인 갯수
signed short arenaItemFrame;	//현재 남은 프레임
signed short arenaDebuf[TOTALDEBUF];	//투기장 들어가기전 상태저장
unsigned char arenaRewardType, arenaRewardLv, arenaRewardDetail, arenaRewardGrade, arenaRewardCnt;	//보상 아이콘을 그려주기 위한 데이터
unsigned char arenaStatus;//0이면 시작전, 1이면 전투중, 2면 클리어

long long int dmg[MAXPLAYER];//현재 플레이어의 토탈데미지를 입력하는 곳
long long int dmgOrder[MAXPLAYER];//그에 따른 순위

unsigned short arenaMotion[MAXPLAYER];

long long int arenaItemPrice[MAXARENAITEM];//현재 아레나 보상 아이템의 가격을 평가한 것
long long int arenaItemOrder[MAXARENAITEM];//가격에 따른 순서를 조정한 것
unsigned short arenaItemEffectFrame[MAXARENAITEM];//현재 아이템을 보여주기 위한 프레임

unsigned short startItemIdx;
unsigned short totalItemCnt;
unsigned short totalItemFrame;

unsigned short arenaDeadCount;
unsigned short arenaItemCount;
unsigned short arenaHitCount;

//0 애들 등장
//1 순위 왕관 등장
//2 1등 캐릭터 즐거워하는 모습
//3 1등 캐릭터에게 아이템 전달
//4 1등 캐릭터 아이템 받고 즐거워하는 모습
//5 2등 캐릭터에게 아이템 전달
//6 3등 캐릭터에게 아이템 전달
//7 4등 캐릭터에게 아이템 전달
//8 5등 캐릭터에게 아이템 전달
//9 6등 캐릭터에게 아이템 전달
//10 7등 캐릭터에게 아이템 전달
//11 8등 캐릭터에게 아이템 전달
//12 9등 캐릭터에게 아이템 전달
//13 10등 캐릭터에게 아이템 전달
//14 유저 보상 박기
//15 아이템 리스트 박기

unsigned char playResultStatus;
unsigned char raidPlayer;

unsigned char skillSlot[RAIDSKILLSLOT];


//길드전 관련 변수
unsigned char guildTimeStr[20];	//남은시간 표시 변수
unsigned int guildTotalScore;	//길드전 누적 점수
int curTime;
signed int rankRecord[16];	//그래프 표시할 것 저장변수
signed int rankWeek;		//몇주차 인지
char rankScore[4][15];	//점수 저장 변수||길드전현황->현재길드전스코어
unsigned char guildCur;		//그래프에서 커서이동때 사용
signed char guildWinner;
unsigned char guildReward[5];		//0 : type, 1:lv, 2:detail, 3:grade, 4:count, 5:첫번째보상골드금액(1천단위)
int goldReward;
unsigned char guildRewardReceive;

int goldEffectFrame;
int medalEffectFrame;
int coinEffectFrame;

int gachaSupporterGrade;
int gachaSupporterIdx;

int temp;
int tempHint;

unsigned char netLock;
//복제방지
char phoneMatch;
char isScreenShot;

char isDragging;//화면을 무언가가 누르고 있다는 변수(드래깅중이라는것)
int pointed;//누른곳이 어떤 영역인가에 해당하는 변수

unsigned char saveFlag[3];//0:SaveGame, 1:SaveOption, 2:SaveEtc
unsigned char soundLoad;

unsigned char toolTip;
unsigned char gameMenuPop;
unsigned char gameMenuDepth;

//#include "automata.h"

//cocos2d::experimental::ui::WebView *_webView;

#ifdef MEMORYTEST
int tempMemory;
int temp1;
int temp2;
int temp3;
int temp4;
int temp5;
int temp6;
int temp7;
int temp8;
int temp9;
int temp10;
int freeMemory;

int dMoveCnt;
M_Uint32* dMove;
#endif

#ifdef DEBUG
int demoSkip;
int debug, g_bDebugDetail, g_bDebugType;
M_Int64 g_lOldTime, g_lCurTime, g_lResultTime;
int tempValue, tempGrade, tempEnemy;
int g_nTestCnt1, g_nTestCnt2, g_nTestCnt3, g_nTestCnt4, g_nTestCnt5, g_nTestCnt6, g_nTestCnt7, g_nTestCnt8, g_nTestCnt9, g_nTestCnt10;
int g_nTestAvg1, g_nTestAvg2, g_nTestAvg3, g_nTestAvg4, g_nTestAvg5, g_nTestAvg6, g_nTestAvg7, g_nTestAvg8, g_nTestAvg9, g_nTestAvg10;
unsigned long p[15], e[15];
char debugStr[256];
int tempMemory;
int freeMemory;
#endif

#ifdef EXPVERSION
M_Boolean yesno_Draw;
M_Boolean buy_Confirm;
#endif

//추가된 투기장 관련 변수
unsigned short caveMap = 0;			//현재 어디 투기장인지.
unsigned short caveEnemyAlive[159 * 2];

unsigned short caveCountEmy = 0;
unsigned short caveCountEmy2 = 0;
unsigned short caveKill = 0;		//투기장 몬스터 퇴치수.(신규 투기장은 몬스터를 모두 잡으면 끝남)
unsigned short caveItemType;
unsigned short caveItemText;
unsigned short caveItemDetail;
unsigned short caveItemCnt = 0;
unsigned short caveItemGrade = 0;
unsigned char caveMapData = 0;

unsigned char cave1TotalEmy[15] =
{ 2, 5, 7, 3, 3, 4, 3, 6, 6, 4, 7, 5, 9, 6, 5 };//75
unsigned char cave2TotalEmy[18] =
{ 0, 5, 0, 5, 5, 3, 6, 4, 0, 3, 3, 4, 5, 5, 2, 7, 5, 4 };//66
unsigned char cave3TotalEmy[30] =
{ 7, 5, 0, 5, 7, 6, 2, 5, 6, 7, 4, 7, 5, 5, 6, 5, 0, 0, 0, 9, 4, 5, 8, 9, 6, 7, 8, 6, 7, 8 };//159
unsigned char cave4TotalEmy[28] =
{ 2, 5, 0, 5, 3, 3, 4, 6, 4, 5, 5, 2, 2, 6, 8, 3, 3, 4, 3, 0, 7, 5, 5, 8, 4, 7, 6, 2 };//117
//433//5
//436//5
//439//5
//459//5
//488//7
//493//7
unsigned short caveItemPer[4][16] = {
	{1500, 4500, 8000, 10000,	//톨레아
	1500, 4500, 8000, 10000,
	500, 2500, 6400, 10000,
	500, 2500, 6400, 10000},
	{1500, 4500, 7650, 10000,	//아틀란티스
	1500, 4500, 7650, 10000,
	500, 2500, 6400, 10000,
	500, 2500, 6400, 10000},
	{2000, 5000, 8700, 10000,	//아델라인
	2000, 5000, 8700, 10000,
	500, 2500, 6400, 10000,
	500, 2500, 6400, 10000},
	{3000, 6000, 8700, 10000,	//홍염지대
	3000, 6000, 8700, 10000,
	500, 2500, 9700, 10000,
	500, 2500, 9700, 10000}
};

unsigned char caveItemAcc[24] = {
	//9, 25, 5, 20, 9, 25, 5, 20, 9, 25, 5, 20, ///neck
	9, 25, 5, 26, 9, 25, 5, 26, 9, 25, 5, 26,
	13, 14, 7, 11, 13, 14, 7, 11, 13, 14, 7, 11,	//ring
};


//키비시스 자루	: 미래의 거울 / 9
//세이렌의 피리	: 용자의 시계 / 25
//황혼의 성배	: 메피스토 피리 / 5
//로젤린의 꽃	: 난쟁이의 공 / 20

//재앙의 거울	: 미래의 거울 / 9
//영웅의 서사시	: 용자의 시계 / 25
//유니콘의 뿔	: 메피스토 피리 / 5
//황금 조개		: 난쟁이의 공 / 20

//천사의 날개	: 미래의 거울 / 9
//금단의 과실	: 용자의 시계 / 25
//죽음의 올가미	: 메피스토 피리 / 5
//조각난 영혼	: 난쟁이의 공 / 20
//
//충성의 반지	: 승자의 반지 / 13
//황제의 반지	: 궁극의 반지 / 14
//절대 반지		: 폭주의 반지 / 7
//니벨룽겐 반지	: 신념의 반지 / 11

//은하수 반지	: 승자의 반지 / 13
//약속의 반지	: 궁극의 반지 / 14
//요정의 반지	: 폭주의 반지 / 7
//흡마 반지		: 신념의 반지 / 11

//번뇌의 반지	: 승자의 반지 / 13
//불사의 반지	: 궁극의 반지 / 14
//황금 반지		: 폭주의 반지 / 7
//봉인된 반지	: 신념의 반지 / 11
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
experimental::ui::WebView* _webView;
#endif



int adX; //광고의 x포지션
int adY; //광고의 y포지션
int adFrame;//광고의 프레임
int adType;//광고의 타입
int adProfile;//광고의 프로필 사진
int adHero;

int tipIndex;

int mapSeenCount;
int mapSeenCountHelp;

int boxOpenFrame;
unsigned char voiceType;

cocos2d::Scene* curScene;

int wholeFrame;

bool screenBuffer;
bool doubleBuffer;

signed short robinmap;
signed short playmap;
signed short dioramaType;//현재 디오라마


//CCLabelTTF * textLabel;

bool onceAnnounced;
int profileImg[MAXPLAYER];
unsigned char playerHeadZoom = false;//ALLHEADZOOM;//PLAYERHEADZOOM;// false;//
bool effectOnlyPlayer = false;//EFFECT_ONLY_PLAYER
bool focusOnPlayer = false;//FOCUSONPLAYER
bool onlyPlayerDmgNumBig = false;//ONLYPLAYERDMGNUMBIG
int skillSelectTime;
int macroTimes = LOG_COUNT;

Mat4 parentTransform;
Renderer* renderer;

std::random_device rd;

int touchIdleFrame;
int idleHelpCnt = 0;
int idleHelpType = 0;//이동을 시킬지, 공격을 하라고 할지
int idleHelpObj = ENEMY;

int MINDY = MINDY_MIN;
int EQUIP_WIN_HEIGHT = MINDY;

#ifdef DEVELOPMENT
int DEBUG_STAR = STAR8;
#else
int TOTAL_OPENED_TIER = TIER_GOLD;
int DEBUG_STAR = 3;
#endif

bool tutorialMode;
int tutorialStep;

int floatingMessage;

bool playClear = false;

ITEM gachaItem[MAXGACHAITEM];

int miniGacha;
int miniGachaCnt;
int miniGachaIcon;
int miniGachaType;
int miniGachaTypeFrom;
int miniGachaTypeTo;
int miniGachaDetail;
int miniGachaDetailFrom;
int miniGachaDetailTo;
int miniGachaGrade;
int miniGachaGradeFrom;
int miniGachaGradeTo;
int miniGachaFloor;

int HEARTTIME = 60 * 60;
int FREEITEMTIME = 18 * 60 * 60;
int realPlayerCnt;

bool textInput = false;

unsigned short gachaIcon[5];
unsigned char gachaGrade[5];

int SOLDIERSALE = 10;

int curLabMain;
int curLabSub;

int GNB_GAP = 64 * _2X;

int outline = GRADE_NORMAL;
#ifdef ONESKILLTEST
int oneSkillTest = ONESKILLTEST;
#endif

float VOLUME_BGM = 0.2f;
float VOLUME_SE = 0.3f;
float VOLUME_BGM_MUTE = 0.1f;

int ironFrame;
int medalFrame;
int heartFrame;
int goldFrame;
int starFrame;
int hammerFrame;
int shieldFrame;

int goldCount;
int goldCountFrame;
int joyStickFrame = 0;
int joyStickAni = 0;
int joyStickDir = LEFT;

int raidChance;//처음에 5번을 주고 한번 싸울때마다 

int dmgIndex;
int subDmgIndex;

long currentTimeStamp;

int remainedTurn;
int remainedTurnFrame;//애니메이션을 담당 1로 세팅하면 30까지 증가되면서 숫자가 좌우로 회전하면서 하나 빠지면서 바뀌면서 스탑
//NEUTRAL	가만히 있을 때
//PLAYER	주인공이 공격시
//ENEMY		적에게 공격시
//공격시 
int turn;
int turnFrame;
int turnPosition;

int rouletteSequence;
int curRouletteStart;//몇번째 부터 시작하는건지
int totalRouletteCnt;//최종적으로 나와야 되는 룰렛개수//현재 위에 올라가 있는 룰렛 개수

//공격연출관련
int attackSequence;//
int attackSequenceBack;
int attackType;//
int actionCardIdx;
int attackStr;//
int attackStartIdx;
int questRewardType;
int attackAttr;
int boxDropItemType;

int attackSequenceBefore;

//여기서부터 현재 룰렛이 어떤게 나왔는지 데이터. 이 데이터를 기반으로 어떤것을 내보내는지 정한다
//unsigned char roulette
int actionCardArr[TOTALCONTROLMARK];
int actionCardCnt;

int curtainFrame;

int subAttackType;//추가타라던가 이런것들
int subAttackStr;
int subAttackIcon;
//현재 카드메뉴가 뒷면이 노출되었는지
char cardMenuBack[TOTALEQUIP];
//+면 닫히는 상태로 1씩 빼주면서 0으로 간다.
//-면 열리는 상태로 1씩 더해주면서 0으로 간다.

int totalProb;
int probSum[TOTALJOKBO];

int totalBattleProb;
int battleProbSum[TOTALBATTLEJOKBO];

int totalBossRaidProb;
int bossRaidProbSum[TOTALBOSSRAIDJOKBO];

int totalQuestRequestItemCnt;
unsigned int questRequestItemCnt[TOTALQUESTREQUEST * TOTALSUBQUEST];

int startX, startY, targetX, targetY, targetX2, targetY2;

long long rouletteNum;
long long rouletteNumSub;
long long rouletteNumBar;
long long rouletteNumPvpBar;

long long rouletteNum_before;

int debugAttack;

ITEM rewardItem[MAXREWARDITEM];//메인 리워드 아이템
ITEM rewardItemBack[MAXREWARDITEM];//백업
int rewardItemCnt;//현재 획득된 아이템
int curRewardItem;//현재 획득진행중에 있는 아이템
int focusedItem;//메인리스트에서
int focusedSubItem;//서브리스트
bool newItem;

int boxCnt;//토탈 박스 카운트
int newCollectionCnt;//이번에 새로운 컬렉션이 완성된 카운트
int newCardCnt;//새로운 카드 카운트
int curBox;

ITEM boxCardItem[TOTALBOXMARK][MAXCARDREWARDITEM];
int boxCardItemCnt[TOTALBOXMARK];

int rewardIndex;
int pvpRewardIndex;

int newItemCnt;
int newItemIdx[MAXBOXREWARDITEM];
int newItemType[MAXBOXREWARDITEM];
int newItemDetail[MAXBOXREWARDITEM];
int newItemGrade[MAXBOXREWARDITEM];


int curNewItemIdx;

int curRewardBoxIdx;

bool ONLYATTACKMODE = false;


int ROULETTEINTERVAL = 3;

int ROULETTEWHEELTIME;

int ROULETTESPREADTIME = SPREADDIV * MAXROULETTE;
int ROULETTESELECTTIME = FPS * 5;

int TOTAL_OPENEDMENU;


//상대위치

#ifdef MYKING
int DRAWROULETTENUMGAP = 192 * _2X - 16 * _2X;
int DRAWROULETTENUMGAP_SUB = DRAWROULETTENUMGAP + 98 * _2X;
int QUESTBARYGAP = DRAWROULETTENUMGAP_SUB - DRAWROULETTENUM_SUB_HEIGHT + 8 * _2X;
int DRAWROULETTENUMGAP_RAID = DRAWROULETTENUMGAP_SUB - 64 * _2X;
#else
int DRAWROULETTENUMGAP = 88 * _2X;// 192 * _2X - 8 * _2X;
int DRAWROULETTENUMGAP_SUB = DRAWROULETTENUMGAP + 72 * _2X;
int QUESTBARYGAP = DRAWROULETTENUMGAP_SUB - (float)(DRAWROULETTENUM_SUB_HEIGHT * 0.9f);
int DRAWROULETTENUMGAP_RAID = DRAWROULETTENUMGAP_SUB - 56 * _2X;
int DRAWRAIDNUMGAP = DRAWROULETTENUMGAP_SUB + 92 * _2X;
int RAIDUSERPROFILEGAP = 64 * _2X;
int HPBARGAP = 0 * _2X;
int BAR_UPPERMENUGAP = 0 * _2X;
int BAR_BOTTOMMENUGAP = 0 * _2X;
int BOXPOSITION_Y = 420 * _2X;//160 * _2X;//300 * _2X;//408 * _2X;//

int BOXITEM_Y = 128 * _2X;
#endif

int STAGELABELGAP = QUESTBARYGAP - QUESTBARHEIGHT - 4 * _2X;

int DRAWROULETTENUMGAP_BATTLE = DRAWROULETTENUMGAP + 92 * _2X;
int DRAWROULETTENUMGAP_ALPHA = RAIDREWARDGOLD_Y + 46 * _2X;

int ENEMYUSERINFOGAP = 58 * _2X;
int STAGEBOSSINFOGAP = 148 * _2X;
int ENEMYHPBARYGAP = QUESTBARYGAP - 40 * _2X;

int HITPOSITIONGAP = 168 * _2X;
int HITPOSITIONGAP2 = -80 * _2X;

int JOKBOGAP_INIT = 160 * _2X;
int JOKBOGAP = JOKBOGAP_INIT;
int HEARTBARGAP = -29 * _2X;
#ifdef MYKING
int CARDPOSITIONGAP = 132 * _2X;
#else
int CARDPOSITIONGAP = 144 * _2X;
#endif

int HITPOSITION_CREW = 280 * _2X;
int HITPOSITION_HITSTART = 368 * _2X;
int HITPOSITION_HITMODE = 406 * _2X - 8 * _2X;

int PLAYINFO_GAP = 192 * _2X;

POPUP popUp[MAXPOPUP];

int arr[2];

int newCollectionIdx[MAXNEWCOLLECTIONLIST];
int curNewCollection;

int initControlerFrame = 0;
int crewInitializeFrame = 0;

GAMEEVENT gameEventArr[MAXGAMEEVENT];

int pvpRewardPosition[3][2];

int joyStick = PUSHBUTTON;

int curStar, curMaxStar, maxStar;

int totalHouse = TOTALOPENDHOUSE;
int popUpCnt = 0;


int points[MAX_POINTS][2]; // 좌표를 저장할 배열 (x, y 각각을 1차원 배열로 저장)
int boxPoints[MAX_POINTS][2];

int selectedCrew;

bool rouletteOpen[SKILLPERSWORD];
bool loadRoulette = false;
int newCollection;

int attackedCrewIdx;//공격당한 인덱스
int bossGetCoinCrewIdx;//보스에게 도움을 준 인덱스

//스테이지에서 빚갚아주면 애니메이션 하는거
int stageUpgradeMotion[MAXCREW];

int bossRaidMode;//그냥 일반보스는 bossRoom은 true이고,	보스레이드는 이 변수를 쓴다. 

int subQuestCnt[TOTALQUEST];

GAMEEVENT* gEvent;

int swordSkillCnt[TOTAL_COLLECTIONS];//검별 스킬 개수
int swordSkillProb[TOTAL_COLLECTIONS * SKILLPERSWORD];//컬렉션 확률 

//여기는 서버로부터 로딩해 오는 것인데 일단 로컬에 저장한걸 불러오는 형식으로 하자.
HOUSE enemyHouse;
HOUSE stageHouse;//
//임시서버데이터
HOUSE aiUserHouse[TOTALAI];//서버 교신이 없는 상태에서의 AI
HOUSE* selectedHouse;//현재 선택된 하우스
HOUSE tempHouse;

int curCardMark;
int currencyMarkCnt;


int wheelSpeed;
int wheelAngle;
int wheelAccel;
int wheelFrame;
int wheelMaxSpeed;
int arrowTouched;
int WHEELMAXSPEED = FPS;
int WHEELINITSPEED = 8;
int WHEELINITACCEL = 2;

//배틀이 걸렸을 때 정보
int battleTarget;//현재 적의 crew 인덱스로 null이거나 아니거나 상관없이 선택된 crew[i]의 i를 의미한다.
bool battleShield;
long long battleGold;

int raidTarget;
long long raidGold;
int raidAttack;

OBJECT raidBox[TOTALRAIDBOX];

int bet;
int betBattle;

int rouletteArr[SKILLPERSWORD];

int tabMenuFrame[TOTALEQUIP];
int maxRouletteCnt;

float boxDropPercent[TOTAL_BOX][TOTAL_BOXDROP];


int XNUMGAP = 0;
int YNUMGAP = -24 * _2X;

int nearestIndex;

int curMaxCrew;

int slotFrame = 0;
int turnListIdx;
int enemyTurnStartIdx;
int totalTurn;
int turnList[PLAYERALL + MAXWAVEENEMY];
int crewIdList[MAXCREW] = { -1, -1, -1, -1, -1, -1 };
int crewCnt = 0;
int heroCnt = 0;
int showCrewCnt = 0; // 로딩 화면에서 현재까지 "공개/합류 연출로 보여줄" 크루 수(0..crewCnt)
int showHeroCnt = 0;

int leaderCrewId = -1;   // 0..TOTAL_CREW-1 or -1
bool hasLeader = false;

// 중앙 카드에 표시할 현재 공개 캐릭터(robin.slotCrew[showCrewCnt]를 기반으로)
int cardCmf = -1;
int cardAlpha = 0;

// 1) 타겟 결과 (예시) : aoOffset(0~8)로 받는다고 가정
int gRouletteStartAoOffset[TOTALREEL] = { -1, -1, -1 };
int gRouletteResultAoOffset[TOTALREEL] = { -1, -1, -1 };  // 최종 확정 3명 (aoOffset). 비어있는 릴은 -1
int gRouletteResultCnt = 0;                               // 이번 판에 실제로 사용하는 릴 수
bool gRouletteNewSpin = false;                            // 새 판 시작 신호(RouletteDraw()의 static 상태머신 강제 초기화)
int gRouletteSkillIdx[TOTALREEL] = { -1, -1, -1 };
int rouletteFrame;
// 3개 다 확정 후 "한 번만" 합성/이동 연출 트리거
bool gRouletteSkillDispatchStarted = false;

bool gRouletteResultValid = false;

int blState = BL_REVEAL;
int blStateFrame = 0;
int blFrame = 0;

int finishOffsetX = 0;

int bgScrollX = 0;
int bgScrollY = 0;

// ===== 소환 연출 =====
int summonCrewId = -1;
int summonCmf = -1;
int summonFromX, summonFromY;
int summonX, summonY;
int summonToX, summonToY;
int summonMidX = 0, summonMidY = 0;
float summonScale = 0.5f;
int summonHold = 0;          // 센터 박히는 홀드 프레임 카운터(옵션)
int summonStar = 1;          // 현재 소환 크루의 별등급(1~9)
int celebFlash = 0;          // 축하 플래시(0이면 없음)
int shake = 0;               // 화면 흔들림 강도(0이면 없음)
int joinFromX = 0;
int joinFromY = 0;

bool needPickSummonFromBg = false;
bool pickedSummonFromBg = false;
bool hideSummonBgTile = false;
int  hideBgCmf = -1;
int summonType = -1;

// 로딩바 진행률(“등장 단계” 기반)
int loadPct = 0;

// ---------- pity 상태 ----------
int gNoHighStarCount = 0; // STAR7+ 안 나온 연속 횟수

// ---------- 소프트 분산 상태 ----------
int gRecentRegionCount[TOTALCASTLE] = { 0 }; // 최근 등장 횟수
int gRecentStarCount[10] = { 0 };            // STAR 연속 패널티

// ================================
// 게임 상태 전역 변수 선언 (extern)
// 실제 정의는 GameState.cpp에 있음
// ================================

// 전투 관련
int attackDelayBefore = 0;
int attackTypeBefore = 0;
int attackStrBefore = 0;
int rewardItemCntBefore = 0;
int maxHitCnt = 0;
int sequenceFrame = 0;
int raidFrame = 0;
int continuousAttackFrame = 0;
int raidCnt = 0;

// 자동 플레이
bool autoPlay = false;
bool autoSelect = false;
bool autoSkill = false;
int autoFrame = 0;
bool autoButtonText = true;

// 화면
float screenZoom = 1.0f;
float dioramaZoom = DIORAMAZOOM;
float dioramaZoomGap = 0.0f;
float battleZoom = 1.0f;
int screenDarken = 0;

// 게임 상태
int waveStatus = WAVESTATUS_READY;
int levelUpFrame = 0;
int levelUpStatus = 0;
int maxUserLv = 0;
bool bossOn = false;
int touchDisable = 3 * FPS;
bool tutorialWaitingEnemyLand = false;
bool tutorialAttackPending = false;
int tutorialPendingDemo = -1;

//DEBUG: SetRoom() 리로드 원인 추적용 임시 진단 전역. 원인 확인되면 제거.
int gDebugSetRoomReloadCount = 0;
int gDebugSetRoomReloadFrame = -1;
int gDebugSetRoomReloadAttackSeq = -1;
int gDebugSetRoomReloadArenaStatus = -1;
int gDebugSetRoomReloadWaveStatus = -1;

int floatOffsetY;

int openingScene;
int openingText;
int openingWaitFrame;
int openingState;
int openingPrevTextPage;
int openingTextPage;
bool openingSceneWait;

float joyStartX;
float joyStartY;
float joyDx;
float joyDy;
float joyPower;
int joyDir;
bool joyPressed;
bool joyReturning;
float joyReturnSpeed;

bool gachaLuckyBox;

bool gachaPrepared;

// 현재 적에게서 획득한 상자 정보
int gachaBoxDetail;
int gachaBoxGrade;

// 카드 한 장씩 공개할 때 사용하는 인덱스
int gachaOpenCardIdx;

// 현재 카드의 등장 완료 여부
bool gachaCurrentCardReady;

// 보상을 실제 인벤토리에 넣었는지
bool gachaRewardReceived;

int manualCardMarkIdx;

int previousOpenCardIdx;

int trayCardCount;

bool waitingForTrayComplete;

int previousGachaDepth;

int summaryFrame;

int flyToBarFrame;

int getItemFrame;

bool gachaCardSkipRequested;