/*----------------------------------------------------------------------------
**			PRE-DEFINITIONS FOR MODULE
**--------------------------------------------------------------------------*/
#ifdef DEBUG
#undef DEBUG
#endif


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "ui/UIWebView.h"
#include "cocos-ext.h"
#include "json/document.h"
#include <vector>
#include <cstdlib>
#ifdef SDKBOX_ENABLED
//#include "PluginAdMob/PluginAdMob.h"
#endif
//#include "jsoncpp/json.h

#define USE_AUDIO_ENGINE 1
//#define USE_SIMPLE_AUDIO_ENGINE 1

#ifdef USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
#else //USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif
using namespace cocos2d::experimental;
using namespace std;
using namespace chrono;
USING_NS_CC;
USING_NS_CC_EXT;
//#include "jsoncpp/json.h"

#define GL_MAX                            0x8008

#define SIMULATOR
/*----------------------------------------------------------------------------
**			INCLUDE FILES FOR MODULE
**--------------------------------------------------------------------------*/
#include "Def.h"

#ifdef DEBUG
#define DEMOSKIP	DEMO_QUEST0
#endif


/*----------------------------------------------------------------------------
**			VARIABLES FOR MODULE
**--------------------------------------------------------------------------*/
#include "Data.h"

#include "Core.h"
#include "CoreClass.h"
// 전역 변수 정의 (한 번만)
//#include "Net.h"

/*----------------------------------------------------------------------------
**			FUCTION PROTOTYPES
**--------------------------------------------------------------------------*/
#include "Func.h"
#include "Write.h"

//#include "SimpleAudioEngine.h"


//#include "AdmobLib/AdMob/AdMobCtrl.h"
//#include "AdmobLib/AdMob/AdMobPlugin.h"
//#include "AdmobLib/IOS/AdMob.h"


using namespace cocos2d;
using namespace rapidjson;

#ifdef SDKBOX_ENABLED

#endif



Scene* Core::createScene()
{
	int i;
	// 'scene' is an autorelease object

	curScene = Scene::create();

	// 'layer' is an autorelease object

	auto layer = Core::create();
	layer->retain();
	curScene->addChild(layer);

	for (i = 0; i < TOTALBUFFER; i++) {
		bufferLayer[i] = Layer::create();
		bufferLayer[i]->retain();
	}

	return curScene;
}

bool Core::onTouchBegan(Touch* touch, Event* unused_event)
{
	int i;
	auto touchPoint = touch->getLocation();
	//log("onTouchBegan id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);

	startTouchX = touchPoint.x;
	startTouchY = touchPoint.y;

	if (touch) {
		touchX = touchPoint.x;
		touchY = touchPoint.y;

		if (is_press_finished == true && autoScroll == false) {
			isTouchKey = TOUCH_PRESS;
			is_key_pressed = true;
			is_touchkey_pressed = true;
			is_press_finished = false;
			//touchFrame = MAXKEYPRESSED;
			touchFrame = FPS;
			touchedFrame = 1;

			for (i = MAXKEYPRESSED - 1; i > 0; i--)
				memcpy(touchPressedKey[i], touchPressedKey[i - 1], sizeof(touchPressedKey[i]));

			touchPressedKey[0][0] = (short)touchPoint.x;
			touchPressedKey[0][1] = (short)touchPoint.y;

			systemKey = 0;

			if (touchModeOld == null) {
				startTouchCheck = true;

				ExecTouchFunc(touchPressedKey[0][0], touchPressedKey[0][1]);

				startTouchCheck = false;

			}

			scDir = SCROLL_NOTHING;
			if (touchIdleFrame > TOUCHIDLEFRAME)
				idleHelpCnt++;

		}
	}
	return true;
}

void Core::onTouchMoved(Touch* touch, Event* unused_event)
{
	int i;
	rapidSwipe = false;
	OBJECT * pObj = &ao[raidPlayer];

	auto touchPoint = touch->getLocation();

	//log("onTouchMoved id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);
	if (touch) {
		touchX = touchPoint.x;
		touchY = touchPoint.y;
	}

	if (joyPressed) {
		float dx = touchPoint.x - joyStartX;
		float dy = touchPoint.y - joyStartY;

		float len = sqrtf(dx * dx + dy * dy);

		if (len > JOYKNOBMAX) {
			dx = dx / len * JOYKNOBMAX;
			dy = dy / len * JOYKNOBMAX;
			len = JOYKNOBMAX;
		}

		joyDx = dx;
		joyDy = dy * 0.75;
		joyPower = len / JOYKNOBMAX;

		float angle = atan2f(dy, dx);

		// 8방향
		if (joyPower < 0.2f) joyDir = -1;
		// 오른쪽
		else if (angle >= -0.392f && angle < 0.392f) {
			joyDir = 0;
			systemKey = AVK_6;
		}
		// 위오른쪽
		else if (angle >= 0.392f && angle < 1.178f)
		{
			joyDir = 1;
			systemKey = AVK_3;
		}
		// 위
		else if (angle >= 1.178f && angle < 1.963f)
		{
			joyDir = 2;
			systemKey = AVK_2;
		}
		// 위왼쪽
		else if (angle >= 1.963f && angle < 2.748f)
		{
			joyDir = 3;
			systemKey = AVK_1;
		}
		// 왼쪽
		else if (angle >= 2.748f || angle < -2.748f)
		{
			joyDir = 4;
			systemKey = AVK_4;
		}
		// 아래왼쪽
		else if (angle >= -2.748f && angle < -1.963f)
		{
			joyDir = 5;
			systemKey = AVK_7;
		}
		// 아래
		else if (angle >= -1.963f && angle < -1.178f)
		{
			joyDir = 6;
			systemKey = AVK_8;
		}
		// 아래오른쪽
		else if (angle >= -1.178f && angle < -0.392f)
		{
			joyDir = 7;
			systemKey = AVK_9;
		}

		isTouchKey = TOUCH_DRAG;
		return;
	}

	if (touch && touchModeOld == NULL && autoScroll == false) {
		touchIdleFrame = 0;
		if (touchIdleFrame > TOUCHIDLEFRAME)
			idleHelpCnt++;
		if (touchPoint.y <= DY && ((Abs(touchPressedKey[0][0] - touchPoint.x) > SWIPE_DISTANCE_X) || (Abs(touchPressedKey[0][1] - touchPoint.y) > SWIPE_DISTANCE_Y))) {
			int oldKey = systemKey;

			if (touchFrame % FPS == 0)
				touchFrame = FPS;

			for (i = MAXKEYPRESSED - 1; i > 0; i--)
				memcpy(touchPressedKey[i], touchPressedKey[i - 1], sizeof(touchPressedKey[i]));

			touchPressedKey[0][0] = (short)touchPoint.x;
			touchPressedKey[0][1] = (short)touchPoint.y;

			if ((Abs(touchPressedKey[1][0] - touchPressedKey[0][0]) > RAPIDSWIPE_DX)) {
				rapidSwipe = RAPIDSWIPE_HORIZONTAL;
			}

			if ((Abs(touchPressedKey[1][1] - touchPressedKey[0][1]) > RAPIDSWIPE_DY))
			{
				if (touchPressedKey[1][1] - touchPressedKey[0][1] < -RAPIDSWIPE_DY)
					rapidSwipe = RAPIDSWIPE_VERTICAL_UP;
				else
					rapidSwipe = RAPIDSWIPE_VERTICAL_DOWN;
			}

			if (systemKey == AVK_7 || systemKey == AVK_9 || systemKey == AVK_0 || systemKey == AVK_STAR || systemKey == AVK_POUND)
				systemKey = oldKey;
			else {
				isTouchKey = TOUCH_DRAG;

				if (keyHandle == MK_PLAY && swipeLock == false && scRecoveryFrameX == 0 && (curMenu == MENU_COLLECTIONS || curMenu == MENU_SHOP || curMenu == MENU_CREW || curMenu == MENU_CASTLE || curMenu == MENU_PLAY)) {
					touchFrame = FPS;

					if (scDir == SCROLL_NOTHING) {
						switch (curMenu) {
						case MENU_PLAY:
						case MENU_COLLECTIONS:
						case MENU_SHOP:
						case MENU_CREW:
						case MENU_CASTLE:
							//x축 이동값이 크면
							if (Abs(touchPressedKey[0][0] - touchPressedKey[1][0]) - Abs(touchPressedKey[0][1] - touchPressedKey[1][1]) > 0)
								scDir = SCROLL_HORIZONTAL;
							else
								scDir = SCROLL_VERTICAL;
							break;


						}
					}
					if (scDir == SCROLL_HORIZONTAL) {
						switch (curMenu) {
						default:
							scX += (touchPressedKey[0][0] - touchPressedKey[1][0]);
							
							if (scX > DX / 2) {
								if (curMenu == MENU_SHOP && menuX > 0) {
									menuX--;
									menuFrame = 0;
									systemKey = TOUCH_FUNC_HOME_LEFT;
									stageInfoDepth = 0;
									stageInfoFrame = 0;
									scX = -scX;
									scRecoveryFrameX = 0;
									scRecoveryFrameX = 1;
									gameMenuPop = false;

								}
							}
							else if (scX < -DX / 2) {

								if (curMenu == MENU_SHOP && menuX < TOTALPOPUPSTORE - 1) {
									menuX++;
									menuFrame = 0;
									systemKey = TOUCH_FUNC_HOME_LEFT;
									stageInfoDepth = 0;
									stageInfoFrame = 0;
									scX = -scX;
									scRecoveryFrameX = 0;
									scRecoveryFrameX = 1;
									gameMenuPop = false;

								}
							}
							break;
						}
						
					}
					else if (scDir == SCROLL_VERTICAL) {
						switch (curMenu) {
						//case MENU_PLAY:
						//	scY[curMenu] -= (touchPressedKey[0][1] - touchPressedKey[1][1]);
						//	break;
						default:
							scY[curMenu] += (touchPressedKey[0][1] - touchPressedKey[1][1]);
							break;
						}
					}

				}
				else {
					//x축 이동값이 크면
					if (Abs(touchPressedKey[0][0] - touchPressedKey[1][0]) - Abs(touchPressedKey[0][1] - touchPressedKey[1][1]) > 0)
						scDir = SCROLL_HORIZONTAL;
					else
						scDir = SCROLL_VERTICAL;
					if (scDir == SCROLL_VERTICAL) {
						switch (curMenu) {
						//case MENU_PLAY:
						//	scY[curMenu] -= (touchPressedKey[0][1] - touchPressedKey[1][1]);
						//	break;
						default:
						 scY[curMenu] += (touchPressedKey[0][1] - touchPressedKey[1][1]);
						 break;
						}
					}
				}
			}


		}
		else if (touchPoint.y > DY && is_press_finished == true) {

			int oldKey = systemKey;

			for (i = MAXKEYPRESSED; i > 0; i--)
				memcpy(touchPressedKey[i], touchPressedKey[i - 1], sizeof(touchPressedKey[i]));

			touchPressedKey[0][0] = (short)touchPoint.x;
			touchPressedKey[0][1] = (short)touchPoint.y;

			if (touchFrame % FPS == 0)
				touchFrame = FPS;

			ExecTouchFunc(touchPoint.x, touchPoint.y);

			if (oldKey != systemKey) {
				isTouchKey = TOUCH_PRESS;
				is_key_pressed = true;
				is_touchkey_pressed = true;
				is_press_finished = false;
				touchFrame = FPS;
			}
			else
				systemKey = oldKey;
		}
	}

}

void Core::onTouchCancelled(Touch* touch, Event* unused_event)
{
	auto touchPoint = touch->getLocation();
	OBJECT * pObj = &ao[raidPlayer];
	rapidSwipe = false;

	endTouchX = touchPoint.x;
	endTouchY = touchPoint.y;

	//log("onTouchEnded id = %d, x = %f, y = %f", touch->getID(), touchPoint.x, touchPoint.y);

	if (touch) {
		if (touchModeOld == NULL && autoScroll == false) {
			if (touchIdleFrame >= TOUCHIDLEFRAME + idleHelpCnt * FPS && arenaStatus == STATUS_PLAY && attackSequence == ATTACKSEQUENCE_READY && tutorialMode == true) {
				if ((drawHandle == MD_PLAY && autoPlay == false) || (drawHandle == MD_BATTLE && autoPlay == false) || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID)
				{
					touchIdleFrame = 0;
					isTouchKey = TOUCH_RELEASE;
					is_key_released = true;
					is_release_finished = false;

					systemRelease = systemKey = null;
					return;
				}
			}
			touchIdleFrame = 0;

			if ((Abs(touchPressedKey[1][0] - touchPressedKey[0][0]) > RAPIDSWIPE_DX) && touchedFrame > 0)
				rapidSwipe = RAPIDSWIPE_HORIZONTAL;

			if ((Abs(touchPressedKey[1][1] - touchPressedKey[0][1]) > RAPIDSWIPE_DY) && touchedFrame > 0)
			{
				if (touchPressedKey[1][1] - touchPressedKey[0][1] < -RAPIDSWIPE_DY)
					rapidSwipe = RAPIDSWIPE_VERTICAL_UP;
				else
					rapidSwipe = RAPIDSWIPE_VERTICAL_DOWN;
			}

			isTouchKey = TOUCH_RELEASE;
			is_key_released = true;
			is_release_finished = false;

			joyPressed = false;
			joyReturning = true;

			joyReturnSpeed = 0.22f;
			joyPower = 0;
			joyDir = -1;

			systemRelease = systemKey;

		}
	}

	//조이스틱을 일정시간 누르고 있으면
	if (autoPlay == false && touchedFrame >= AUTOPLAYFRAME && GetTouchFunc(touchX, touchY) == TOUCH_FUNC_USE_HEART) {
		autoPlay = true;
		autoButtonText = false;
	}
}

void Core::onTouchEnded(Touch* touch, Event *unused_event)
{
	OBJECT * pObj = &ao[raidPlayer];
	rapidSwipe = false;

	auto touchPoint = touch->getLocation();

	endTouchX = touchPoint.x;
	endTouchY = touchPoint.y;

	if (touch) {
		if (touchModeOld == NULL && autoScroll == false) {

			if (touchIdleFrame >= TOUCHIDLEFRAME + idleHelpCnt * FPS && arenaStatus == STATUS_PLAY && attackSequence == ATTACKSEQUENCE_READY && tutorialMode == true) {
				if ((drawHandle == MD_PLAY && autoPlay == false) || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID)
				{
					touchIdleFrame = 0;
					isTouchKey = TOUCH_RELEASE;
					is_key_released = true;
					is_release_finished = false;

					systemRelease = systemKey = null;



					return;
				}
			}

			touchIdleFrame = 0;

			if ((Abs(touchPressedKey[1][0] - touchPressedKey[0][0]) > RAPIDSWIPE_DX) && touchedFrame > 0)
				rapidSwipe = RAPIDSWIPE_HORIZONTAL;

			if ((Abs(touchPressedKey[1][1] - touchPressedKey[0][1]) > RAPIDSWIPE_DY) && touchedFrame > 0)
			{
				if (touchPressedKey[1][1] - touchPressedKey[0][1] < -RAPIDSWIPE_DY)
					rapidSwipe = RAPIDSWIPE_VERTICAL_UP;
				else
					rapidSwipe = RAPIDSWIPE_VERTICAL_DOWN;
			}

				
				//curMenu == MENU_PLAY
				if (curMenu == MENU_CREW ||
					curMenu == MENU_COLLECTIONS ||
					curMenu == MENU_CASTLE ||
					curMenu == MENU_SHOP ||
					curMenu == MENU_STARSHOP ||
					curMenu == MENU_PLAY
					) {
					if (rapidSwipe) {
						//y축으로 이동하면
						if ((touchPressedKey[0][1] - touchPressedKey[1][1]) > 0 && scDir == SCROLL_VERTICAL) {
							switch (curMenu) {
							default:
								scAccelY = -Min(TSIZE * 3, Max(TSIZE * 3, (touchPressedKey[0][1] - touchPressedKey[1][1])));
								break;
							//위쪽으로 갈수록 높은것일 때 이 스크롤을 쓰자
							case MENU_PLAY:
								scAccelY = +Min(TSIZE * 3, Max(TSIZE * 3, (touchPressedKey[0][1] - touchPressedKey[1][1])));
								break;
							}
						}
						else if ((touchPressedKey[0][1] - touchPressedKey[1][1]) < 0 && scDir == SCROLL_VERTICAL) {
							switch (curMenu) {
							default:
								scAccelY = +Min(TSIZE * 3, Max(TSIZE * 3, (touchPressedKey[0][1] - touchPressedKey[1][1])));
								break;
							//위로 스크롤
							case MENU_PLAY:
								scAccelY = -Min(TSIZE * 3, Max(TSIZE * 3, (touchPressedKey[0][1] - touchPressedKey[1][1])));
								break;
							}
						}
					}
					switch (curMenu) {
					default:
						scT[curMenu] = GetScrollDy(curMenu) - DY + GNBHEIGHT + BOTTOMMENUHEIGHT;
						break;
					case MENU_CREW:
						scT[curMenu] = GetScrollDy(curMenu) - DY + GNBHEIGHT + BOTTOMMENUHEIGHT + 406 - 112;
						break;
					case MENU_COLLECTIONS:
						scT[curMenu] = GetScrollDy(curMenu) - DY + GNBHEIGHT + BOTTOMMENUHEIGHT + 500;
						break;
					case MENU_CASTLE:
						scT[curMenu] = GetScrollDy(curMenu) - DY + GNBHEIGHT + BOTTOMMENUHEIGHT + 500;
						break;
					}
					switch (curMenu) {
					default:
						if (scY[curMenu] < 0 || scY[curMenu] > scT[curMenu]) {
							scRecoveryFrameY = 1;
							scAccelY = 0;
						}
						break;
					//위로 스크롤
					case MENU_PLAY:
						if (scY[curMenu] > 0 || scY[curMenu] < -scT[curMenu]) {
							scRecoveryFrameY = 1;
							scAccelY = 0;
						}
						break;
					}

				}

			scRecoveryFrameX = 1;

			isTouchKey = TOUCH_RELEASE;
			is_key_released = true;
			is_release_finished = false;

			joyPressed = false;
			joyReturning = true;

			joyReturnSpeed = 0.22f;
			joyPower = 0;
			joyDir = -1;

			systemRelease = systemKey;
		}
	}
}

void Core::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Core::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Core::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Core::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


}

void Core::onExit()
{
	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}

// on "init" you need to initialize your instance
bool Core::init()
{
	int i;
	std::string fileName;

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	renderer = Director::getInstance()->getRenderer();
	parentTransform = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto winSize = Director::getInstance()->getVisibleSize();


	//그레이스케일 쉐이더
	shader_gray = new GLProgram();
	shader_gray->initWithByteArrays(vsh_gray, fsh_gray);

	shader_gray->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shader_gray->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shader_gray->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);

	shader_gray->link();
	shader_gray->updateUniforms();
	shader_gray->retain();

	ShaderCache::getInstance()->addGLProgram(shader_gray, "grayscale");

	//호이트 쉐이더
	shader_white = new GLProgram();
	shader_white->initWithByteArrays(vsh_white, fsh_white);

	shader_white->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shader_white->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shader_white->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);

	shader_white->link();
	shader_white->updateUniforms();
	shader_white->retain();

	ShaderCache::getInstance()->addGLProgram(shader_white, "whitescale");

	//라이튼 쉐이더
	shader_lighten = new GLProgram();
	shader_lighten->initWithByteArrays(vsh_lighten, fsh_lighten);

	shader_lighten->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shader_lighten->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shader_lighten->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);

	shader_lighten->link();
	shader_lighten->updateUniforms();
	shader_lighten->retain();

	ShaderCache::getInstance()->addGLProgram(shader_lighten, "lighten");

	//블랜딩 기본값
	BLEND_ORIGIN.src = GL_SRC_ALPHA;
	BLEND_ORIGIN.dst = GL_ONE_MINUS_SRC_ALPHA;

	//블랜드
	BLEND_BLENDMODE.src = GL_SRC_ALPHA;
	BLEND_BLENDMODE.dst = GL_ONE_MINUS_SRC_ALPHA;

	//라이튼 그림자가 어두움
	BLEND_LIGHTEN.src = GL_ONE;
	BLEND_LIGHTEN.dst = GL_ONE;

	//그림자용
	BLEND_SHADOW.src = GL_DST_COLOR;
	BLEND_SHADOW.dst = GL_ONE_MINUS_SRC_ALPHA;

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);



	netLock = 0;

	offX = 0;
	offY = 0;

	DX = visibleSize.width;
	DY = visibleSize.height;

	SCREENRATIO = UpDiv(DY * 100 * 100 / DX, 100);

	REALDY = PLAYAREA_Y;
	STATUSWIN_Y = DY - REALDY;
	xOffset = (DX - PLAYAREA_X) / 2;

	//화면버퍼 렌더링. 모든 드로우를 gScreenBuffer에 모아 프레임당 한 번 화면에 표시한다.
	screenBuffer = true;

#ifdef DOUBLEBUFFERING
	doubleBuffer = true;
#else
	doubleBuffer = false;
#endif


	//Initialize
	loadedMap = -1;
	effect.sound = 0;


	thickColor = 0x000000;
	SetFontColor(COLOR_WHITE);
	SetColor(0x000000);

	isDemo = 0;
	curID = -1;
	tipIndex = -1;

	InitContext();
	InitScreenBuffer();//DX/DY가 확정된 뒤에 호출해야 한다.
	InitGraphics();

	touch = true;
	touchMode = TOUCH_OK;
	touchOK = false;
	touchYESNO = false;
	touchCount = 1;

	UnSectionClip(false);

	fontImage = new CCImage();
	fontImage->initWithImageFile("res/f.png");
	fontImageWidth = fontImage->getWidth();
	fontImageHeight = fontImage->getHeight();
	fontImageDataLen = fontImage->getDataLen();

	fontImageData = new unsigned char[fontImage->getDataLen() * 4];
	fontImageData = fontImage->getData();

	fontImage->retain();

	LoadImg(LOGO_IMG);
	LoadTexture(LOGO_IMG);

	LoadImg(COMMON_IMG);
	LoadTexture(COMMON_IMG);

	LoadImg(MEMRECT_IMG);
	LoadTexture(MEMRECT_IMG);

	LoadImg(TOUCH_IMG);
	LoadTexture(TOUCH_IMG);

	LoadImg(EFFECT_IMG);
	LoadTexture(EFFECT_IMG);

	LoadImg(NUM2_IMG);
	LoadTexture(NUM2_IMG);

	LoadOption();
	LoadAiHouse();

	winSize.width = DX - 16 * 2 * _2X;
	winSize.height = DY - 16 * 2 * _2X;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	_webView = cocos2d::experimental::ui::WebView::create();
	_webView->setPosition(visibleSize / 2);
	_webView->setContentSize(winSize);
	_webView->loadURL("https://www.bigpixel.kr");
	_webView->setScalesPageToFit(true);
	this->addChild(_webView);
	_webView->setVisible(false);
#endif
#ifdef LOCALPUSH
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//_NativeInterface = new NativeInterface();
	//_NativeInterface->Noti_init();
	//_NativeInterface->Jni_callSpeakString("Oh, My God!", voiceType);
	NativeInterface::Noti_init();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Noti_init();
#endif
#endif


#ifdef SDKBOX_ENABLED
	/*
	// ui
	{
		Menu* menu = Menu::create(
								  MenuItemFont::create("load banner", [](Ref*) { sdkbox::PluginAdMob::cache(kHomeBanner); }),
								  MenuItemFont::create("show banner", [](Ref*) { sdkbox::PluginAdMob::show(kHomeBanner);  }),
								  MenuItemFont::create("hide banner", [](Ref*) { sdkbox::PluginAdMob::hide(kHomeBanner);  }),
								  MenuItemFont::create("is banner available", [=](Ref*) {
			showText(StringUtils::format("is %s available %d", kHomeBanner.c_str(), sdkbox::PluginAdMob::isAvailable(kHomeBanner)));
		}),

								  MenuItemFont::create("load interstitial", [](Ref*) { sdkbox::PluginAdMob::cache(kGameOverAd); }),
								  MenuItemFont::create("show interstitial", [](Ref*) { sdkbox::PluginAdMob::show(kGameOverAd);  }),
								  MenuItemFont::create("is interstital available", [=](Ref*) {
			showText(StringUtils::format("is %s available %d", kGameOverAd.c_str(), sdkbox::PluginAdMob::isAvailable(kGameOverAd)));
		}),
								  MenuItemFont::create("load rewarded video", [](Ref*) {
			sdkbox::PluginAdMob::cache(kRewardedAd);
		}),
								  MenuItemFont::create("show rewarded video", [](Ref*) {
			sdkbox::PluginAdMob::show(kRewardedAd);
		}),
								  NULL);
		menu->alignItemsVerticallyWithPadding(20);
		menu->setPosition(size.width/2, size.height/2);
		addChild(menu);
	}

	sdkbox::PluginAdMob::setListener(new IMListener());
	 */
#endif

	drawHandle = MD_LOGO;
	keyHandle = NULL;

	robinmap = -1;

	option.cutOff = CUTOFF2;
	effectOnlyPlayer = EFFECT_ONLY_PLAYER;
	focusOnPlayer = true;
	onlyPlayerDmgNumBig = false;

	frame = 0;

	SetScreenRatio();

	int gap = (DY - GNBHEIGHT - 640 * 133 / 100) / 2;

	if (gap > 0) {
		QUESTBARYGAP += gap;
		
		BAR_BOTTOMMENUGAP += gap;
		BOXPOSITION_Y += gap;
		
	}
	

	for (i = MAXCMF - 1; i >= 0; i--) {
		cmfLoaded[i] = -1;
		CmfRead(i, i);
	}
	
	if (!LoadFile(SAVEFILE, saveMem, sizeof(ROBINDATA))) {
		NewGame();
	}
	else {
		LoadGame();
	}

	for (i = 0; i < MAXRENDERCNT; i++)
		renderSpriteIndex[i] = -1;
	for (i = 0; i < TOTALIMG; i++)
		sameRenderSpriteMax[i] = 0;

	ResetLabel();


	this->schedule(schedule_selector(Core::Run));

	/*
	_webView = cocos2d::experimental::ui::WebView::create();
	_webView->setPosition(DX / 2);
	_webView->setContentSize(DX * 0.5);
	_webView->loadURL("http://www.baidu.com");
	_webView->setScalesPageToFit(true);
	_webView->setOnShouldStartLoading(CC_CALLBACK_2(WebViewTest::onWebViewShouldStartLoading, this));
	_webView->setOnDidFinishLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFinishLoading, this));
	_webView->setOnDidFailLoading(CC_CALLBACK_2(WebViewTest::onWebViewDidFailLoading, this));

	this->addChild(_webView);
	*/

	return true;
}

void Core::Run(float delta) {

	int i;
	//항상 현재 시간을 세팅해 준다.
	currentTimeStamp = MC_knlCurrentTimeStamp();

	if (wholeFrame % FRAMEPER == 0) {
		//프레임 정리.
		//풀 커서 초기화와 스프라이트 상태 복원은 렌더 방식과 무관하게 항상 해야 한다.
		//씬에서 떼어내는 작업(removeChild)만 레거시 직접 렌더일 때 필요하다.
		//화면버퍼 모드에서는 애초에 씬에 붙이지 않고 visit()으로 타겟에 기록하기 때문이다.
		{
			if (!screenBuffer) {
				for (i = 0; i < TOTALBUFFER; i++) {
					curScene->removeChild(bufferTexture[BUFFER_PLAY + i]);
				}
			}

			curBufferCnt = 0;
			memset(&curBufferSpriteArr, 0, sizeof(curBufferSpriteArr));
			memset(&sameBufferSpriteCur, 0, sizeof(sameBufferSpriteCur));
			memset(&sameBufferSpriteArr, 0, sizeof(sameBufferSpriteArr));

			if (!screenBuffer) {
				for (i = 0; i < totalFontLabelCnt; i++) {
					curScene->removeChild(fontLabel[i]);
				}
			}
			curFontLabelCnt = 0;
			memset(&curFontLabelArr, 0, sizeof(curFontLabelArr));
			memset(&sameFontLabelCur, 0, sizeof(sameFontLabelCur));
			memset(&sameFontLabelArr, 0, sizeof(sameFontLabelArr));

			if (!screenBuffer) {
				for (i = 0; i < curTextLabelCnt; i++) {
					curScene->removeChild(textLabel[curTextLabelArr[i]]);
				}
			}
			curTextLabelCnt = 0;
			memset(&curTextLabelArr, 0, sizeof(curTextLabelArr));
			memset(&sameTextLabelCur, 0, sizeof(sameTextLabelCur));
			memset(&sameTextLabelArr, 0, sizeof(sameTextLabelArr));

			for (i = 0; i < curRenderCnt; i++) {

				if (!screenBuffer)
					curScene->removeChild(renderSprite[curRenderSpriteArr[i]], false);

				renderSprite[curRenderSpriteArr[i]]->setScale(1.0f);
				renderSprite[curRenderSpriteArr[i]]->setFlippedX(false);
				renderSprite[curRenderSpriteArr[i]]->setRotation(0);
				renderSprite[curRenderSpriteArr[i]]->setOpacity(EMPTY);
				renderSprite[curRenderSpriteArr[i]]->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
				renderSprite[curRenderSpriteArr[i]]->setBlendFunc(BLEND_ORIGIN);
				renderSprite[curRenderSpriteArr[i]]->setColor(Color3B((0xFFFFFF >> 16) & 0xFF, (0xFFFFFF >> 8) & 0xFF, 0xFFFFFF & 0xFF));
			}
			curRenderCnt = 0;
			memset(&curRenderSpriteArr, 0, sizeof(curRenderSpriteArr));
			memset(&sameRenderSpriteCur, 0, sizeof(sameRenderSpriteCur));
			memset(&sameRenderSpriteArr, 0, sizeof(sameRenderSpriteArr));

		}


		if (isTouchKey == TOUCH_DRAG || (is_press_finished == false && is_key_pressed == true)) {

			KeyCore();

			if (isTouchKey == TOUCH_PRESS)
				is_touchkey_pressed = false;
			if (touchModeOld && (systemKey == AVK_5 || systemKey == AVK_CLR)) {
				touchMode = touchModeOld;
				touchModeOld = null;
			}
		}
		else if (is_release_finished == false && is_key_released == true && scDir == SCROLL_NOTHING) {
			ReleaseCore();
		}

		RefreshQuestTime();
		RefreshHeartTime();
		RefreshEnemyTime();

		if (running == true) {
			//한 프레임의 모든 드로우를 화면버퍼에 모은 뒤 한 번만 화면에 표시한다.
			BeginScreenBuffer();
			PaintClet(0, DY, DX, DY);
			EndScreenBuffer();
		}

	}

	wholeFrame++;
}


void DoubleBuffering(int drawHandleIdx)
{
	int i;
	int temprx = rx;
	
	offX = 0;
	offY = 0;

	LoadingDraw();

	//배경/타일을 오프스크린 버퍼에 미리 그려 둔다.
	//화면버퍼가 열려 있는 중에 호출되므로 PushRenderTarget이 상위 타겟을 저장·복원한다.
	//doubleBuffer가 꺼진 빌드에서는 기존처럼 현재 타겟(화면)에 바로 그린다.
	if (doubleBuffer) {
		PushRenderTarget(bufferTexture[BUFFER_PLAY], bufferLayer[BUFFER_PLAY], true);
		DrawBg(robinmap, STATUSWIN_Y, 1.0f);
		PopRenderTarget();

		PushRenderTarget(bufferTexture[BUFFER_TILE], bufferLayer[BUFFER_TILE], true);
		DrawTile(robinmap, 0, 1.0f);
		PopRenderTarget();
	}
	else {
		DrawBg(robinmap, STATUSWIN_Y, 1.0f);
		DrawTile(robinmap, 0, 1.0f);
	}

	SetSectionClip(0, STATUSWIN_Y, DX, STATUSWIN_Y - STATUSWIN_Y2, false);
	rx = 0;
	
	rx = temprx;
	UnSectionClip(false);

}

void PaintClet(int x, int y, int w, int h)
{
	int i, j, k;
	float zoom;

	if (refreshRate < FPS) {
		Director::getInstance()->setAnimationInterval(1.0f / refreshRate);
		refreshRate = FPS;
	}
	else
		Director::getInstance()->setAnimationInterval(1.0f / refreshRate);

	clearFrame = Max(clearFrame - 1, 0);

	if (MC_knlCurrentTime() - clearFrame > 300 + touch * 100) {
		for (i = PLAYER; i < TOTALCHAR; i++)
			memset(ao[i].pressedKey, 0, sizeof(ao[i].pressedKey));
	}

	if (MC_knlCurrentTime() - releaseClearFrame > 300 + touch * 100)
		releasedKey = 0;

	if (scRecoveryFrameX > 0) {
		if (scX > 0) {
			scX -= Max(TSIZE * 2 * _2X - scRecoveryFrameX * 2 * _2X, 1 * _2X);
			scRecoveryFrameX++;
			if (scX < 0)
				scX = 0;
		}
		else if (scX < 0) {
			scX += Max(TSIZE * 2 * _2X - scRecoveryFrameX * 2 * _2X, 1 * _2X);
			scRecoveryFrameX++;
			if (scX > 0)
				scX = 0;
		}
		else
			scRecoveryFrameX--;

		if (scX == 0 && scY[curMenu] == 0)
			scRecoveryFrameX = 0;
	}

	if (scAccelY) {
		switch (curMenu) {
		default:
			scY[curMenu] -= scAccelY;
			scAccelY = scAccelY * 4 / 5;
			break;
		//위로 스크롤
		case MENU_PLAY:
			scY[curMenu] += scAccelY;

			scAccelY = scAccelY * 4 / 5;
			break;
		}


		if (scAccelY == 0) {
			scRecoveryFrameY = 1;

			// ★ 이 시점의 scY[curMenu] 기준으로 가장 가까운 성 index 계산
			int divisor = GetScrollDy(curMenu) / (TOTALCASTLE + 1);

			// 현재 위치가 몇 번째 성 사이쯤인지 (실수 인덱스)
			float fIndex = -(float)scY[curMenu] / (float)divisor;

			// 가장 가까운 성 인덱스 = 반올림
			nearestIndex = (int)floorf(fIndex + 0.5f);

			// 성 개수에 맞게 클램프 (0 ~ maxCastleIndex)
			int maxCastleIndex = scT[curMenu] / divisor;   // scT[curMenu]가 전체 높이라고 가정
			if (nearestIndex < 0) nearestIndex = 0;
			if (nearestIndex > maxCastleIndex) nearestIndex = maxCastleIndex;

			// ★ 스냅 타겟 Y 고정
			snapTargetY[curMenu] = -nearestIndex * divisor;
		}
	}

	if (scRecoveryFrameY > 0) {
		switch (curMenu) {
		default:
			if (scY[curMenu] < 0) {
				scY[curMenu] += Max(TSIZE * 2 - scRecoveryFrameY * _2X, 1 * _2X);
				scRecoveryFrameY++;
				if (scY[curMenu] > 0)
					scY[curMenu] = 0;
			}

			if (scY[curMenu] > scT[curMenu]) {
				scY[curMenu] -= Max(TSIZE * 2 - scRecoveryFrameY * _2X, 1 * _2X);
				scRecoveryFrameY++;
				if (scY[curMenu] < scT[curMenu])
					scY[curMenu] = scT[curMenu];
			}
			break;
		//위로 스크롤
		case MENU_PLAY:
			//이건 맨 하단
			if (scY[curMenu] > 0) {
				scY[curMenu] -= Max(TSIZE * 2 * _2X - scRecoveryFrameY * 2 * _2X, 1 * _2X);
				scRecoveryFrameY++;
				if (scY[curMenu] < 0)
					scY[curMenu] = 0;
			}
			//이건 맨 상단
			else if (scY[curMenu] < -scT[curMenu]) {
				scY[curMenu] += Max(TSIZE * 2 * _2X - scRecoveryFrameY * 2 * _2X, 1 * _2X);
				scRecoveryFrameY++;
				if (scY[curMenu] > -scT[curMenu])
					scY[curMenu] = -scT[curMenu];
			}
			//이건 중단으로 여기서 세팅을 해줘야 함
			else {
				int target = snapTargetY[curMenu];

				int dir = 0;
				if (target < scY[curMenu])      dir = -1; // 위로 올리기 (Y 감소)
				else if (target > scY[curMenu]) dir = 1;  // 아래로 내리기 (Y 증가)

				int step = Max(TSIZE * 2 * _2X - scRecoveryFrameY * 2 * _2X, 1 * _2X);
				int nextY = scY[curMenu] + dir * step;

				bool reached = false;
				if (dir < 0 && nextY <= target)       reached = true;
				else if (dir > 0 && nextY >= target)  reached = true;
				else if (dir == 0 || scY[curMenu] == target) reached = true;

				if (reached) {
					scY[curMenu] = target;
					scRecoveryFrameY = 0;  // 스냅 끝
				}
				else {
					scY[curMenu] = nextY;
					scRecoveryFrameY++;
				}
			}
			break;
		}

		if (scY[curMenu] == 0)
			scRecoveryFrameY = 0;
	}

	if (autoScroll) {
		autoScrollGap = autoScroll - scY[curMenu];
		if (autoScrollGap < 0)
			scY[curMenu] += Min(-TSIZE, autoScrollGap);
		else
			scY[curMenu] += Min(TSIZE, autoScrollGap);

		switch (curMenu) {
		default:
			if (Abs(autoScroll - scY[curMenu]) < TSIZE) {
				scY[curMenu] = autoScroll;
				autoScroll = 0;
			}
			break;
		}

	}

	if (effect.shake) {
		offX = (8 - effect.shake) * DIR(effect.shake % 2) * _2X;
		effect.shake++;

		if (effect.shake == 8) {
			effect.shake = 0;
			offX = 0;
		}
	}

	effect.sound = -1;
	touchIndex = 0;//인덱스 초기화
	swipeIndex = 0;

	if (mustRefresh == true) {
		if (isScreenShot == false) {
			switch (drawHandle) {
			case MD_LOGO:
				LogoDraw();
				break;
			case MD_TITLE:
				TitleDraw();
				break;
			case MD_OPENING:
				OpeningDraw();
				break;
			case MD_PLAY:
			case MD_BATTLE:
				Play();
				if (curMenu == MENU_PLAY) {
					for (i = 0; i < M_ROULETTEUP; i++)
						AudioEngine::setVolume(audioID[i], VOLUME_BGM);
				}
				else {
					for (i = 0; i < M_ROULETTEUP; i++)
						AudioEngine::setVolume(audioID[i], VOLUME_BGM_MUTE);
				}
				break;
			case MD_RAID:
				Play();
				break;
			case MD_BOSSRAID:
				Play();
				break;
			case MD_DEMO:
				Demo();
				break;
			case MD_ALERT:
				AlertDraw();
				break;
			case MD_GACHA:
				Play();
				GachaDraw();
				break;
			case MD_STAGECLEAR:
				Play();
				ResetRectPoint();
				effect.color2 = COLOR_BLACK;
				break;
			case MD_BATTLELOADING:
				BattleLoadingUpdate();
				BattleLoadingDraw();
				break;
			}
		}

		//mustRefresh = false;
	}


	//아이템 효과가 나오면
	for (i = 0; i < TOTALITEMMARK; i++) {
		if (itemMark[i].frame > 0) {
			GotoPosition(itemMark[i].targetX, itemMark[i].targetY, i, 16 * _2X, ICONMARK_ITEM);

			if (itemMark[i].alpha) {
				SetAlpha(Max(0, 32 - itemMark[i].alpha));

				if (itemMark[i].alpha < TRANSPARENCY_MAX)
					itemMark[i].alpha++;

				SetAlpha(32);
			}

			if ((itemMark[i].targetX - itemMark[i].x) * (itemMark[i].targetX - itemMark[i].x) + (itemMark[i].targetY - itemMark[i].y) * (itemMark[i].targetY - itemMark[i].y) < (16 * _2X) * (16 * _2X)) {
				//PlayMusic(M_COIN);
				switch (itemMark[i].icon) {
				case ICON_GOLD:
					break;
				default:
					boxOpenFrame = 3;
					break;
				}
				memset(&itemMark[i], 0, sizeof(ICONMARK));
			}
			else {
				itemMark[i].frame++;
				if (itemMark[i].alpha < TRANSPARENCY_MAX)
					switch (itemMark[i].icon) {
					case ICON_GOLD:
						DrawIcon(ICON_GOLD + itemMark[i].frame % GOLDICONFRAME, itemMark[i].x, itemMark[i].y, _3X, false, false, false, true);
						DrawNeutral(OBJ_ITEM0 + itemMark[i].frame % 4, itemMark[i].x + 24 * _2X, itemMark[i].y - 36 * _2X, 0, 2);
						break;
					default:
						DrawImage(itemMark[i].imageDx, itemMark[i].imageDy, itemMark[i].imageOffX, itemMark[i].imageOffY, itemMark[i].x, itemMark[i].y, false, false, false, false, false, 2.0f, sprite[itemMark[i].resNum], itemMark[i].resNum);
						DrawNeutral(OBJ_ITEM0 + itemMark[i].frame % 4, itemMark[i].x + 16 * _2X, itemMark[i].y - 32 * _2X, 0, 2);
						break;
					}
			}

			SetAlpha(32);
		}
	}

	if (soulMark.frame2 > 0) {
		GotoPosition(soulMark.targetX2, soulMark.targetY2, false, soulMark.speed2, ICONMARK_SOUL);

		soulMark.speed2 += soulMark.speedIncrement2;
		soulMark.zoom2 += soulMark.zoomIncrement2;

		if (soulMark.speed2 < 8 * _2X)
			soulMark.speed2 = 8 * _2X;

		//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
		if (soulMark.zoomIncrement2 > 0 && soulMark.zoom2 > soulMark.zoomEnd2)
			soulMark.zoom2 = soulMark.zoomEnd2;
		if (soulMark.zoomIncrement2 < 0 && soulMark.zoom2 < soulMark.zoomEnd2)
			soulMark.zoom2 = soulMark.zoomEnd2;

		if ((soulMark.targetX2 - soulMark.x) * (soulMark.targetX2 - soulMark.x) + (soulMark.targetY2 - soulMark.y) * (soulMark.targetY2 - soulMark.y) < 2 * soulMark.speed2 * soulMark.speed2 || soulMark.frame2 >= soulMark.waitingFrame2) {
		}
		else {
			soulMark.frame2++;
		}

		if (soulMark.attackStr > 0) {
			ao[ENEMY].x = xOffset + soulMark.x;
			ao[ENEMY].y = STATUSWIN_Y + (rh - 4) * TSIZE - (soulMark.y - 80 * _2X * ao[ENEMY].zoom) - ry;
			ao[ENEMY].defaultZoom = ao[ENEMY].zoom = soulMark.zoom;

			DrawCmfDetail(ao[ENEMY].cmf, ao[ENEMY].motion, ao[ENEMY].x, soulMark.y - 80 * _2X * ao[ENEMY].zoom, ao[ENEMY].dirF, ao[ENEMY].zoom, false, false);
		}

		DrawCmfDetail(CMF_NPC_HEART, soulMark.attackStr ? PO_C122_SPARK0 + robin.playtime / MOTIONDIV % 8 : 0, soulMark.x, soulMark.y, LEFT, soulMark.zoom2, false, false);


	}
	else if (soulMark.frame > 0) {
		GotoPosition(soulMark.targetX, soulMark.targetY, false, soulMark.speed, ICONMARK_SOUL);

		soulMark.speed += soulMark.speedIncrement;
		soulMark.zoom += soulMark.zoomIncrement;

		if (soulMark.speed < 8 * _2X)
			soulMark.speed = 8 * _2X;

		//만약 증가량이 0보다 크면
		//end보다 크면 end에서 멈춘다.
		if (soulMark.zoomIncrement > 0 && soulMark.zoom > soulMark.zoomEnd)
			soulMark.zoom = soulMark.zoomEnd;
		if (soulMark.zoomIncrement < 0 && soulMark.zoom < soulMark.zoomEnd)
			soulMark.zoom = soulMark.zoomEnd;

		if ((soulMark.targetX - soulMark.x) * (soulMark.targetX - soulMark.x) + (soulMark.targetY - soulMark.y) * (soulMark.targetY - soulMark.y) < 2 * soulMark.speed * soulMark.speed && soulMark.frame >= soulMark.waitingFrame) {
			//두번째 세팅이 있으면 
			if (soulMark.frame >= soulMark.waitingFrame) {
				soulMark.frame2 = 1;
			}
			else {
			}
		}
		else {
			soulMark.frame++;
		}

		if (soulMark.attackStr > 0) {
			ao[ENEMY].x = soulMark.x;
			ao[ENEMY].y = STATUSWIN_Y + (rh - 4) * TSIZE - (soulMark.y - 80 * _2X * ao[ENEMY].zoom) - ry;
			ao[ENEMY].defaultZoom = ao[ENEMY].zoom = soulMark.zoom;

			DrawCmfDetail(ao[ENEMY].cmf, ao[ENEMY].motion, ao[ENEMY].x, soulMark.y - 80 * _2X * ao[ENEMY].zoom, ao[ENEMY].dirF, ao[ENEMY].zoom, false, false);
		}

		DrawCmfDetail(CMF_NPC_HEART, soulMark.attackStr ? PO_C122_SPARK0 + robin.playtime / MOTIONDIV % 8 : 0, soulMark.x, soulMark.y, LEFT, soulMark.zoom, false, false);
	}

	//골드마크
	//커런시 효과가 나오면

	for (i = 0; i < TOTALGOLDALPHAMARK; i++) {
		//프레임2가 크면
		if (goldAlphaMark[i].frame2 > 0) {

			GotoPosition(goldAlphaMark[i].targetX2, goldAlphaMark[i].targetY2, i, goldAlphaMark[i].speed2, ICONMARK_GOLDALPHA);
			goldAlphaMark[i].speed2 += goldAlphaMark[i].speedIncrement2;
			goldAlphaMark[i].zoom2 += goldAlphaMark[i].zoomIncrement2;

			if (goldAlphaMark[i].speed2 < 8 * _2X)
				goldAlphaMark[i].speed2 = 8 * _2X;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (goldAlphaMark[i].zoomIncrement2 > 0 && goldAlphaMark[i].zoom2 > goldAlphaMark[i].zoomEnd2)
				goldAlphaMark[i].zoom2 = goldAlphaMark[i].zoomEnd2;
			if (goldAlphaMark[i].zoomIncrement2 < 0 && goldAlphaMark[i].zoom2 < goldAlphaMark[i].zoomEnd2)
				goldAlphaMark[i].zoom2 = goldAlphaMark[i].zoomEnd2;

			if ((goldAlphaMark[i].targetX2 - goldAlphaMark[i].x) * (goldAlphaMark[i].targetX2 - goldAlphaMark[i].x) + (goldAlphaMark[i].targetY2 - goldAlphaMark[i].y) * (goldAlphaMark[i].targetY2 - goldAlphaMark[i].y) < 2 * goldAlphaMark[i].speed2 * goldAlphaMark[i].speed2 && goldAlphaMark[i].frame2 >= goldAlphaMark[i].waitingFrame2) {
				//PlayMusic(M_COIN);
				switch (goldAlphaMark[i].icon) {
				case ICON_GOLD:
					break;
				default:
					boxOpenFrame = 3;
					break;
				}
				memset(&goldAlphaMark[i], 0, sizeof(ICONMARK));
			}
			else {
				goldAlphaMark[i].frame++;
				if (goldAlphaMark[i].alpha < TRANSPARENCY_MAX)
					switch (goldAlphaMark[i].icon) {
					case ICON_GOLD:
						DrawIcon(ICON_GOLD + goldAlphaMark[i].frame % GOLDICONFRAME, goldAlphaMark[i].x, goldAlphaMark[i].y, _3X, false, false, false, true);
						DrawNeutral(OBJ_ITEM0 + goldAlphaMark[i].frame % 4, goldAlphaMark[i].x + 24 * _2X, goldAlphaMark[i].y - 36 * _2X, 0, 2);
						break;
					default:
						DrawImage(goldAlphaMark[i].imageDx, goldAlphaMark[i].imageDy, goldAlphaMark[i].imageOffX, goldAlphaMark[i].imageOffY, goldAlphaMark[i].x, goldAlphaMark[i].y, false, false, false, false, false, 2.0f, sprite[goldAlphaMark[i].resNum], goldAlphaMark[i].resNum);
						DrawNeutral(OBJ_ITEM0 + goldAlphaMark[i].frame % 4, goldAlphaMark[i].x + 16 * _2X, goldAlphaMark[i].y - 32 * _2X, 0, 2);
						break;
					}
			}

			SetAlpha(32);
		}
		else if (goldAlphaMark[i].frame > 0) {
			GotoPosition(goldAlphaMark[i].targetX, goldAlphaMark[i].targetY, i, goldAlphaMark[i].speed, ICONMARK_GOLDALPHA);
			goldAlphaMark[i].speed += goldAlphaMark[i].speedIncrement;
			goldAlphaMark[i].zoom += goldAlphaMark[i].zoomIncrement;

			if (goldAlphaMark[i].speed < 8 * _2X)
				goldAlphaMark[i].speed = 8 * _2X;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (goldAlphaMark[i].zoomIncrement > 0 && goldAlphaMark[i].zoom > goldAlphaMark[i].zoomEnd)
				goldAlphaMark[i].zoom = goldAlphaMark[i].zoomEnd;
			if (goldAlphaMark[i].zoomIncrement < 0 && goldAlphaMark[i].zoom < goldAlphaMark[i].zoomEnd)
				goldAlphaMark[i].zoom = goldAlphaMark[i].zoomEnd;

			if ((goldAlphaMark[i].targetX - goldAlphaMark[i].x) * (goldAlphaMark[i].targetX - goldAlphaMark[i].x) + (goldAlphaMark[i].targetY - goldAlphaMark[i].y) * (goldAlphaMark[i].targetY - goldAlphaMark[i].y) < 2 * goldAlphaMark[i].speed * goldAlphaMark[i].speed && goldAlphaMark[i].frame >= goldAlphaMark[i].waitingFrame) {
				//두번째 세팅이 있으면 
				if (goldAlphaMark[i].targetX2 != 0 || goldAlphaMark[i].targetY2 != 0) {
					goldAlphaMark[i].frame2 = 1;
				}
			}
			else {
				goldAlphaMark[i].frame++;
			}

			DrawGoldAlpha(goldAlphaMark[i].x, goldAlphaMark[i].y, goldAlphaMark[i].icon, FONT_GOLD_LARGE, goldAlphaMark[i].zoom, CENTER, false, false);
		}
	}

	
	//커런시 효과를 생성하는 함수
	for (i = 0; i < TOTALCURRENCYMARKARR; i++) {
		if (currencyMarkArr[i].frame > 0) {
			SetCurrencyMark(currencyMarkArr[i].x, currencyMarkArr[i].y, currencyMarkArr[i].targetX, currencyMarkArr[i].targetY, currencyMarkArr[i].targetX2, currencyMarkArr[i].targetY2, currencyMarkArr[i].speed, currencyMarkArr[i].speedIncrement, currencyMarkArr[i].speed2, currencyMarkArr[i].speedIncrement2, currencyMarkArr[i].waitingFrame, currencyMarkArr[i].waitingFrame2, currencyMarkArr[i].icon, currencyMarkArr[i].moveAngle, currencyMarkArr[i].amount, currencyMarkArr[i].type, currencyMarkArr[i].zoom, currencyMarkArr[i].zoomEnd, currencyMarkArr[i].zoomIncrement, currencyMarkArr[i].zoom2, currencyMarkArr[i].zoomEnd2, currencyMarkArr[i].zoomIncrement2, currencyMarkArr[i].bar);

			if (currencyMarkArr[i].frame == currencyMarkArr[i].iconMarkCnt) {
				memset(&currencyMarkArr[i], 0, sizeof(currencyMarkArr[i]));
			}
			else
				currencyMarkArr[i].frame++;
		}
	}

	//카드가 나오면
	for (i = 0; i < TOTALREWARDMARK; i++) {
		if (rewardMark[i].frame2 > 0) {
			GotoPosition(rewardMark[i].targetX2, rewardMark[i].targetY2, i, rewardMark[i].speed2, ICONMARK_REWARD);
			rewardMark[i].speed2 += rewardMark[i].speedIncrement2;
			rewardMark[i].zoom2 += rewardMark[i].zoomIncrement2;


			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (rewardMark[i].zoomIncrement2 > 0 && rewardMark[i].zoom2 > rewardMark[i].zoomEnd2)
				rewardMark[i].zoom2 = rewardMark[i].zoomEnd2;
			if (rewardMark[i].zoomIncrement2 < 0 && rewardMark[i].zoom2 < rewardMark[i].zoomEnd2)
				rewardMark[i].zoom2 = rewardMark[i].zoomEnd2;

			if ((rewardMark[i].targetX2 - rewardMark[i].x) * (rewardMark[i].targetX2 - rewardMark[i].x) + (rewardMark[i].targetY2 - rewardMark[i].y) * (rewardMark[i].targetY2 - rewardMark[i].y) < 2 * rewardMark[i].speed2 * rewardMark[i].speed2 && rewardMark[i].frame2 >= rewardMark[i].waitingFrame2) {
				rewardMark[i].x = rewardMark[i].targetX2;
				rewardMark[i].y = rewardMark[i].targetY2;
				

			}
			else {
				rewardMark[i].frame2++;
			}

			if (rewardMark[i].type == ITEM_CREW) {
				curStar = maxStar = enemyData[crewData[rewardMark[i].detail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR] + 1;
			}
			else {
				curStar = maxStar = GetItemStar(rewardMark[i].type, rewardMark[i].detail, rewardMark[i].grade);
			}

			DrawRewardCard(rewardMark[i].type, rewardMark[i].detail, rewardMark[i].grade, rewardMark[i].cooldown, rewardMark[i].amount, xOffset + rewardMark[i].x - (float)(REWARDCARDSIZE_X) / 2 * rewardMark[i].zoom2, rewardMark[i].y + (float)(REWARDCARDSIZE_Y) / 2 * rewardMark[i].zoom2, false, rewardMark[i].zoom2, rewardMark[i].cardFrame, rewardMark[i].newItem, true, curStar, maxStar, true, rewardMark[i].openFrame);

		}
		else if (rewardMark[i].frame > 0) {
			GotoPosition(rewardMark[i].targetX, rewardMark[i].targetY, i, rewardMark[i].speed, ICONMARK_REWARD);

			rewardMark[i].speed += rewardMark[i].speedIncrement;
			rewardMark[i].zoom += rewardMark[i].zoomIncrement;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (rewardMark[i].zoomIncrement > 0 && rewardMark[i].zoom > rewardMark[i].zoomEnd)
				rewardMark[i].zoom = rewardMark[i].zoomEnd;
			if (rewardMark[i].zoomIncrement < 0 && rewardMark[i].zoom < rewardMark[i].zoomEnd)
				rewardMark[i].zoom = rewardMark[i].zoomEnd;

			if ((rewardMark[i].targetX - rewardMark[i].x) * (rewardMark[i].targetX - rewardMark[i].x) + (rewardMark[i].targetY - rewardMark[i].y) * (rewardMark[i].targetY - rewardMark[i].y) < 2 * rewardMark[i].speed * rewardMark[i].speed && rewardMark[i].frame >= rewardMark[i].waitingFrame) {
				rewardMark[i].x = rewardMark[i].targetX;
				rewardMark[i].y = rewardMark[i].targetY;

				if (rewardMark[i].targetX2 != 0 || rewardMark[i].targetY2 != 0) {
					rewardMark[i].frame2 = 1;
				}
				else {
					currencyEffect[rewardMark[i].type].iconFrame += CURRENCYMARKEFFECTFRAME;

					if (currencyEffect[rewardMark[i].type].endValue - currencyEffect[rewardMark[i].type].startValue <= 10)
						currencyEffect[rewardMark[i].type].totalFrame = currencyEffect[rewardMark[i].type].frame = 1;
					else if (currencyEffect[rewardMark[i].type].endValue - currencyEffect[rewardMark[i].type].startValue <= 100)
						currencyEffect[rewardMark[i].type].totalFrame = currencyEffect[rewardMark[i].type].frame = FPS;
					else if (currencyEffect[rewardMark[i].type].endValue - currencyEffect[rewardMark[i].type].startValue <= 1000)
						currencyEffect[rewardMark[i].type].totalFrame = currencyEffect[rewardMark[i].type].frame = FPS * 2;
					else if (currencyEffect[rewardMark[i].type].endValue - currencyEffect[rewardMark[i].type].startValue <= 10000)
						currencyEffect[rewardMark[i].type].totalFrame = currencyEffect[rewardMark[i].type].frame = FPS * 3;
					else if (currencyEffect[rewardMark[i].type].endValue - currencyEffect[rewardMark[i].type].startValue <= 100000)
						currencyEffect[rewardMark[i].type].totalFrame = currencyEffect[rewardMark[i].type].frame = FPS * 4;
					else
						currencyEffect[rewardMark[i].type].totalFrame = currencyEffect[rewardMark[i].type].frame = FPS * 5;

					//memset(&rewardMark[i], 0, sizeof(ICONMARK));
				}
			}
			else {
				rewardMark[i].frame++;
			}

			if (rewardMark[i].type == ITEM_CREW) {
				curStar = maxStar = enemyData[crewData[rewardMark[i].detail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR] + 1;
			}
			else {
				curStar = maxStar = GetItemStar(rewardMark[i].type, rewardMark[i].detail, rewardMark[i].grade);
			}

			DrawRewardCard(rewardMark[i].type, rewardMark[i].detail, rewardMark[i].grade, rewardMark[i].cooldown, rewardMark[i].amount, xOffset + rewardMark[i].x - (float)(REWARDCARDSIZE_X) / 2 * rewardMark[i].zoom, rewardMark[i].y + (float)(REWARDCARDSIZE_Y) / 2 * rewardMark[i].zoom, false, rewardMark[i].zoom, rewardMark[i].cardFrame, rewardMark[i].newItem, true, curStar, maxStar, true, rewardMark[i].openFrame);


		}
	}


	//커런시 효과가 나오면
	for (i = 0; i < TOTALCURRENCYMARK; i++) {
		//프레임2가 크면
		if (currencyMark[i].frame2 > 0) {

			GotoPosition(currencyMark[i].targetX2, currencyMark[i].targetY2, i, currencyMark[i].speed2, ICONMARK_CURRENCY);
			currencyMark[i].speed2 += currencyMark[i].speedIncrement2;
			currencyMark[i].zoom2 += currencyMark[i].zoomIncrement2;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (currencyMark[i].zoomIncrement2 > 0 && currencyMark[i].zoom2 > currencyMark[i].zoomEnd2)
				currencyMark[i].zoom2 = currencyMark[i].zoomEnd2;
			if (currencyMark[i].zoomIncrement2 < 0 && currencyMark[i].zoom2 < currencyMark[i].zoomEnd2)
				currencyMark[i].zoom2 = currencyMark[i].zoomEnd2;

			if ((currencyMark[i].targetX2 - currencyMark[i].x) * (currencyMark[i].targetX2 - currencyMark[i].x) + (currencyMark[i].targetY2 - currencyMark[i].y) * (currencyMark[i].targetY2 - currencyMark[i].y) < 2 * currencyMark[i].speed2 * currencyMark[i].speed2 && currencyMark[i].frame2 >= currencyMark[i].waitingFrame2) {

				currencyEffect[currencyMark[i].type].iconFrame += CURRENCYMARKEFFECTFRAME;

				if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 10)
					currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = 1;
				else if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 100)
					currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS;
				else if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 1000)
					currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS * 2;
				else if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 10000)
					currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS * 3;
				else if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 100000)
					currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS * 4;
				else
					currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS * 5;

				if (currencyMark[i].type == CURRENCY_EXP)
					AddBar(&bar[BAR_CROWN], 1, BARFRAME);
				else if (currencyMark[i].type == CURRENCY_GOLD) {
					
				}
				memset(&currencyMark[i], 0, sizeof(ICONMARK));
				currencyMarkCnt--;
				//if (currencyMarkCnt == 0 && attackSequence == ATTACKSEQUENCE_ACTION)
				//	WhoIsNextTurn();
			}
			else {
				currencyMark[i].frame2++;
			}
			if (currencyMark[i].frame2 > 0) {

				if (currencyMark[i].icon == ICON_CROWN || currencyMark[i].icon == ICON_STAR) {
					if (currencyMark[i].amount > 0) {
						DrawStarNum(currencyMark[i].icon, currencyMark[i].amount, currencyMark[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].zoom2);
					}
					else
						DrawIcon(currencyMark[i].icon + (currencyMark[i].icon == ICON_GOLD ? currencyMark[i].frame2 % GOLDICONFRAME : 0), currencyMark[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].zoom2, COLOR_WHITE, false, false, true);
				}
				else if (currencyMark[i].icon == ICON_SHIELD) {
					if (currencyMark[i].amount > 0) {
						DrawNumTTF(currencyMark[i].amount, currencyMark[i].x, currencyMark[i].y - (float)(ITEMICONSIZE + 2 * _2X) / 2 * currencyMark[i].zoom2, NUM_FONT_LARGE, CENTER, false, PLUS, true, currencyMark[i].zoom2 / 2, false);
					}
					DrawIcon(currencyMark[i].icon + (currencyMark[i].icon == ICON_GOLD ? currencyMark[i].frame2 % GOLDICONFRAME : 0), currencyMark[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].zoom2, COLOR_WHITE, false, false, true);
				}
				else
					DrawIcon(currencyMark[i].icon + (currencyMark[i].icon == ICON_GOLD ? currencyMark[i].frame2 % GOLDICONFRAME : 0), currencyMark[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].zoom2, COLOR_WHITE, false, false, true);

			}
		}
		else if (currencyMark[i].frame > 0) {
			GotoPosition(currencyMark[i].targetX, currencyMark[i].targetY, i, currencyMark[i].speed, ICONMARK_CURRENCY);
			currencyMark[i].speed += currencyMark[i].speedIncrement;
			currencyMark[i].zoom += currencyMark[i].zoomIncrement;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (currencyMark[i].zoomIncrement > 0 && currencyMark[i].zoom > currencyMark[i].zoomEnd)
				currencyMark[i].zoom = currencyMark[i].zoomEnd;
			if (currencyMark[i].zoomIncrement < 0 && currencyMark[i].zoom < currencyMark[i].zoomEnd)
				currencyMark[i].zoom = currencyMark[i].zoomEnd;

			if ((currencyMark[i].targetX - currencyMark[i].x) * (currencyMark[i].targetX - currencyMark[i].x) + (currencyMark[i].targetY - currencyMark[i].y) * (currencyMark[i].targetY - currencyMark[i].y) < 2 * currencyMark[i].speed * currencyMark[i].speed && currencyMark[i].frame >= currencyMark[i].waitingFrame) {
				//if (currencyMark[i].frame >= currencyMark[i].waitingFrame) {
					//PlayMusic(M_COIN);
					//두번째 세팅이 있으면 
				if (currencyMark[i].targetX2 != 0 || currencyMark[i].targetY2 != 0) {
					currencyMark[i].frame2 = 1;
					switch (drawHandle) {
					default:
						AddBar(&bar[BAR_GOLD], currencyMark[i].amount, BARFRAME);
						break;
					case MD_PLAY:
					case MD_BATTLE:
						switch (currencyMark[i].bar) {
						case BAR_GOLD:
							AddBar(&bar[BAR_GOLD], currencyMark[i].amount, BARFRAME);
							break;
						case BAR_BATTLECOIN:
							//ao[NEUTRAL].status = BOXSTATUS_OPENED;
							if (currencyMark[i].amount > 0)
								OpenBox(&ao[NEUTRAL]);
							AddBar(&bar[BAR_BATTLECOIN], currencyMark[i].amount, BARFRAME);
							break;
						}
						break;
					}
				}
				else {
					currencyEffect[currencyMark[i].type].iconFrame += CURRENCYMARKEFFECTFRAME;

					if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 10)
						currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = 1;
					else if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 100)
						currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS;
					else if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 1000)
						currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS * 2;
					else if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 10000)
						currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS * 3;
					else if (currencyEffect[currencyMark[i].type].endValue - currencyEffect[currencyMark[i].type].startValue <= 100000)
						currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS * 4;
					else
						currencyEffect[currencyMark[i].type].totalFrame = currencyEffect[currencyMark[i].type].frame = FPS * 5;

					memset(&currencyMark[i], 0, sizeof(ICONMARK));
					currencyMarkCnt--;
				}
			}
			else {
				currencyMark[i].frame++;
			}

			if (currencyMark[i].frame > 0) {
				if (currencyMark[i].icon == ICON_CROWN || currencyMark[i].icon == ICON_STAR) {
					if (currencyMark[i].amount > 0) {
						DrawStarNum(currencyMark[i].icon, currencyMark[i].amount, currencyMark[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom, currencyMark[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom, currencyMark[i].zoom);
					}
					else
						DrawIcon(currencyMark[i].icon + (currencyMark[i].icon == ICON_GOLD ? currencyMark[i].frame % GOLDICONFRAME : 0), currencyMark[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom, currencyMark[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom, currencyMark[i].zoom, COLOR_WHITE, false, false, true);
				}
				else if (currencyMark[i].icon == ICON_SHIELD) {
					if (currencyMark[i].amount > 0 && currencyMark[i].targetX == currencyMark[i].x && currencyMark[i].targetY == currencyMark[i].y) {
						DrawNumTTF(currencyMark[i].amount, currencyMark[i].x, currencyMark[i].y - (float)(ITEMICONSIZE + 2 * _2X) / 2 * currencyMark[i].zoom2, NUM_FONT_LARGE, CENTER, false, PLUS, true, currencyMark[i].zoom2 / 2, false);
					}
					DrawIcon(currencyMark[i].icon + (currencyMark[i].icon == ICON_GOLD ? currencyMark[i].frame2 % GOLDICONFRAME : 0), currencyMark[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom2, currencyMark[i].zoom2, COLOR_WHITE, false, false, true);
				}
				else
					DrawIcon(currencyMark[i].icon + (currencyMark[i].icon == ICON_GOLD ? currencyMark[i].frame % GOLDICONFRAME : 0), currencyMark[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom, currencyMark[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark[i].zoom, currencyMark[i].zoom, COLOR_WHITE, false, false, true);

			}
		}
	}

	if (popUpCnt > 0) {
		ScreenDarken(SCREENDARKEN);
		ResetRectPoint();
		DrawPopUp(popUpCnt - 1);
	}

	int boxMotion = OBJ_BOX0;
	//박스가 나오면
	for (i = 0; i < TOTALBOXMARK; i++) {
		if (boxMark[i].frame2 > 0) {
			GotoPosition(boxMark[i].targetX2, boxMark[i].targetY2, i, boxMark[i].speed2, ICONMARK_BOX);
			boxMark[i].speed2 += boxMark[i].speedIncrement2;
			boxMark[i].zoom2 += boxMark[i].zoomIncrement2;


			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (boxMark[i].zoomIncrement2 > 0 && boxMark[i].zoom2 > boxMark[i].zoomEnd2)
				boxMark[i].zoom2 = boxMark[i].zoomEnd2;
			if (boxMark[i].zoomIncrement2 < 0 && boxMark[i].zoom2 < boxMark[i].zoomEnd2)
				boxMark[i].zoom2 = boxMark[i].zoomEnd2;

			if ((boxMark[i].targetX2 - boxMark[i].x) * (boxMark[i].targetX2 - boxMark[i].x) + (boxMark[i].targetY2 - boxMark[i].y) * (boxMark[i].targetY2 - boxMark[i].y) < 2 * boxMark[i].speed2 * boxMark[i].speed2 && boxMark[i].frame2 >= boxMark[i].waitingFrame2) {
				boxMark[i].x = boxMark[i].targetX2;
				boxMark[i].y = boxMark[i].targetY2;
			}
			else {
				boxMark[i].frame2++;
			}

			//if (boxMark[i].openFrame > 0) {
			//	boxMotion = OBJ_BOX0 + Min(3 + (boxMark[i].openFrame / MOTIONDIV / MOTIONDIV) % 4, (boxMark[i].openFrame / MOTIONDIV));

			//	boxMark[i].openFrame++;
			//}

			DrawBox(boxMark[i].detail, xOffset + boxMark[i].x, boxMark[i].y, boxMark[i].dirX, boxMark[i].motion, itemColor[frame % 6], true, boxMark[i].openFrame, false, boxMark[i].zoom2);

			//if (boxMark[i].detail == BOX_INGAME)
			//	DrawNeutral(boxMotion, xOffset + boxMark[i].x, boxMark[i].y - (float)BOXSIZE_Y * boxMark[i].zoom2 / 2, LEFT, boxMark[i].zoom2, gScreenBuffer, gScreenLayer, false);
			//else
			//	DrawCastleBoxXY(boxMark[i].detail, true, RIGHT, xOffset + boxMark[i].x, boxMark[i].y - (float)BOXSIZE_Y * boxMark[i].zoom2 / 2, itemColor[frame % 6], boxMark[i].zoom2, gScreenBuffer, gScreenLayer, false);

			if (boxMark[i].openFrame == true && boxMark[i].detail != BOX_INGAME)
				DrawEffect(EFFECT_HOLY0 + (frame / MOTIONDIV % 10), xOffset + boxMark[i].x, boxMark[i].y - (float)BOXSIZE_Y / 2 * boxMark[i].zoom2, LEFT, false, 1.2f * boxMark[i].zoom2);

		}
		else if (boxMark[i].frame > 0) {
			GotoPosition(boxMark[i].targetX, boxMark[i].targetY, i, boxMark[i].speed, ICONMARK_BOX);

			boxMark[i].speed += boxMark[i].speedIncrement;
			boxMark[i].zoom += boxMark[i].zoomIncrement;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (boxMark[i].zoomIncrement > 0 && boxMark[i].zoom > boxMark[i].zoomEnd)
				boxMark[i].zoom = boxMark[i].zoomEnd;
			if (boxMark[i].zoomIncrement < 0 && boxMark[i].zoom < boxMark[i].zoomEnd)
				boxMark[i].zoom = boxMark[i].zoomEnd;

			if ((boxMark[i].targetX - boxMark[i].x) * (boxMark[i].targetX - boxMark[i].x) + (boxMark[i].targetY - boxMark[i].y) * (boxMark[i].targetY - boxMark[i].y) < 2 * boxMark[i].speed * boxMark[i].speed && boxMark[i].frame >= boxMark[i].waitingFrame) {

					//두번째 세팅이 있으면 
				boxMark[i].x = boxMark[i].targetX;
				boxMark[i].y = boxMark[i].targetY;

				if (boxMark[i].targetX2 != 0 || boxMark[i].targetY2 != 0) {
					boxMark[i].frame2 = 1;
				}
				else {
					currencyEffect[boxMark[i].type].iconFrame += CURRENCYMARKEFFECTFRAME;

					if (currencyEffect[boxMark[i].type].endValue - currencyEffect[boxMark[i].type].startValue <= 10)
						currencyEffect[boxMark[i].type].totalFrame = currencyEffect[boxMark[i].type].frame = 1;
					else if (currencyEffect[boxMark[i].type].endValue - currencyEffect[boxMark[i].type].startValue <= 100)
						currencyEffect[boxMark[i].type].totalFrame = currencyEffect[boxMark[i].type].frame = FPS;
					else if (currencyEffect[boxMark[i].type].endValue - currencyEffect[boxMark[i].type].startValue <= 1000)
						currencyEffect[boxMark[i].type].totalFrame = currencyEffect[boxMark[i].type].frame = FPS * 2;
					else if (currencyEffect[boxMark[i].type].endValue - currencyEffect[boxMark[i].type].startValue <= 10000)
						currencyEffect[boxMark[i].type].totalFrame = currencyEffect[boxMark[i].type].frame = FPS * 3;
					else if (currencyEffect[boxMark[i].type].endValue - currencyEffect[boxMark[i].type].startValue <= 100000)
						currencyEffect[boxMark[i].type].totalFrame = currencyEffect[boxMark[i].type].frame = FPS * 4;
					else
						currencyEffect[boxMark[i].type].totalFrame = currencyEffect[boxMark[i].type].frame = FPS * 5;

				}
			}
			else {
				boxMark[i].frame++;
			}

			//if (boxMark[i].openFrame > 0) {
			//	boxMotion = OBJ_BOX0 + Min(3 + (boxMark[i].openFrame / MOTIONDIV / MOTIONDIV) % 4, (boxMark[i].openFrame / MOTIONDIV));

			//	boxMark[i].openFrame++;
			//}

			DrawBox(boxMark[i].detail, xOffset + boxMark[i].x, boxMark[i].y, boxMark[i].dirX, false, itemColor[frame % 6], true, boxMark[i].motion, false, boxMark[i].zoom);

			//if (boxMark[i].detail == BOX_INGAME)
			//	DrawNeutral(boxMotion, xOffset + boxMark[i].x, boxMark[i].y - (float)BOXSIZE_Y * boxMark[i].zoom / 2, LEFT, boxMark[i].zoom, gScreenBuffer, gScreenLayer, false);
			//else
			//	DrawCastleBoxXY(boxMark[i].detail, true, RIGHT, xOffset + boxMark[i].x, boxMark[i].y - (float)BOXSIZE_Y * boxMark[i].zoom / 2, itemColor[frame % 6], boxMark[i].zoom, gScreenBuffer, gScreenLayer, false);

			if (boxMark[i].openFrame == true && boxMark[i].detail != BOX_INGAME)
				DrawEffect(EFFECT_HOLY0 + (frame / MOTIONDIV % 10), xOffset + boxMark[i].x, boxMark[i].y - (float)BOXSIZE_Y / 2 * boxMark[i].zoom, LEFT, false, 1.2f * boxMark[i].zoom);


		}
	}

	//박스가 나오면
	for (i = 0; i < TOTALCARDMARK; i++) {
		if (boxCardMark[i].frame2 > 0) {
			if (boxCardMark[i].manual == false) {
				GotoPosition(boxCardMark[i].targetX2, boxCardMark[i].targetY2, i, boxCardMark[i].speed2, ICONMARK_BOXCARD);
				boxCardMark[i].speed2 += boxCardMark[i].speedIncrement2;
				boxCardMark[i].zoom2 += boxCardMark[i].zoomIncrement2;


				//만약 증가량이 0보다 크면
				//end보다 크면 end에서 멈춘다.
				if (boxCardMark[i].zoomIncrement2 > 0 && boxCardMark[i].zoom2 > boxCardMark[i].zoomEnd2)
					boxCardMark[i].zoom2 = boxCardMark[i].zoomEnd2;
				if (boxCardMark[i].zoomIncrement2 < 0 && boxCardMark[i].zoom2 < boxCardMark[i].zoomEnd2)
					boxCardMark[i].zoom2 = boxCardMark[i].zoomEnd2;

				if ((boxCardMark[i].targetX2 - boxCardMark[i].x) * (boxCardMark[i].targetX2 - boxCardMark[i].x) + (boxCardMark[i].targetY2 - boxCardMark[i].y) * (boxCardMark[i].targetY2 - boxCardMark[i].y) < 2 * boxCardMark[i].speed2 * boxCardMark[i].speed2 && boxCardMark[i].frame2 >= boxCardMark[i].waitingFrame2) {
					boxCardMark[i].x = boxCardMark[i].targetX2;
					boxCardMark[i].y = boxCardMark[i].targetY2;
				}
				else {
					boxCardMark[i].frame2++;
				}
			}
			if (boxCardMark[i].type == ITEM_CREW) {
				curStar = maxStar = enemyData[crewData[boxCardMark[i].detail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR] + 1;
			}
			else {
				//curStar = maxStar = GetItemStar(boxCardMark[i].type, boxCardMark[i].detail, boxCardMark[i].grade);
				curStar = boxCardMark[i].cooldown;
				maxStar = ITEMMAXLEVEL;
			}

			DrawRewardCard(boxCardMark[i].type, boxCardMark[i].detail, boxCardMark[i].grade, boxCardMark[i].cooldown, boxCardMark[i].amount, xOffset + boxCardMark[i].x - (float)(REWARDCARDSIZE_X) / 2 * boxCardMark[i].zoom2, boxCardMark[i].y + (float)(REWARDCARDSIZE_Y) / 2 * boxCardMark[i].zoom2, false, boxCardMark[i].zoom2, boxCardMark[i].cardFrame, boxCardMark[i].newItem, true, boxCardMark[i].openFrame, curStar, maxStar, true);

		}
		else if (boxCardMark[i].frame > 0) {
			if (boxCardMark[i].manual == false) {
				GotoPosition(boxCardMark[i].targetX, boxCardMark[i].targetY, i, boxCardMark[i].speed, ICONMARK_BOXCARD);

				boxCardMark[i].speed += boxCardMark[i].speedIncrement;
				boxCardMark[i].zoom += boxCardMark[i].zoomIncrement;

				//만약 증가량이 0보다 크면
				//end보다 크면 end에서 멈춘다.
				if (boxCardMark[i].zoomIncrement > 0 && boxCardMark[i].zoom > boxCardMark[i].zoomEnd)
					boxCardMark[i].zoom = boxCardMark[i].zoomEnd;
				if (boxCardMark[i].zoomIncrement < 0 && boxCardMark[i].zoom < boxCardMark[i].zoomEnd)
					boxCardMark[i].zoom = boxCardMark[i].zoomEnd;

				if ((boxCardMark[i].targetX - boxCardMark[i].x) * (boxCardMark[i].targetX - boxCardMark[i].x) + (boxCardMark[i].targetY - boxCardMark[i].y) * (boxCardMark[i].targetY - boxCardMark[i].y) < 2 * boxCardMark[i].speed * boxCardMark[i].speed && boxCardMark[i].frame >= boxCardMark[i].waitingFrame) {
					//if (boxCardMark[i].frame >= boxCardMark[i].waitingFrame) {
						//PlayMusic(M_COIN);
						//두번째 세팅이 있으면 
					boxCardMark[i].x = boxCardMark[i].targetX;
					boxCardMark[i].y = boxCardMark[i].targetY;

					if (boxCardMark[i].targetX2 != 0 || boxCardMark[i].targetY2 != 0) {
						boxCardMark[i].frame2 = 1;
					}
					else {
						currencyEffect[boxCardMark[i].type].iconFrame += CURRENCYMARKEFFECTFRAME;

						if (currencyEffect[boxCardMark[i].type].endValue - currencyEffect[boxCardMark[i].type].startValue <= 10)
							currencyEffect[boxCardMark[i].type].totalFrame = currencyEffect[boxCardMark[i].type].frame = 1;
						else if (currencyEffect[boxCardMark[i].type].endValue - currencyEffect[boxCardMark[i].type].startValue <= 100)
							currencyEffect[boxCardMark[i].type].totalFrame = currencyEffect[boxCardMark[i].type].frame = FPS;
						else if (currencyEffect[boxCardMark[i].type].endValue - currencyEffect[boxCardMark[i].type].startValue <= 1000)
							currencyEffect[boxCardMark[i].type].totalFrame = currencyEffect[boxCardMark[i].type].frame = FPS * 2;
						else if (currencyEffect[boxCardMark[i].type].endValue - currencyEffect[boxCardMark[i].type].startValue <= 10000)
							currencyEffect[boxCardMark[i].type].totalFrame = currencyEffect[boxCardMark[i].type].frame = FPS * 3;
						else if (currencyEffect[boxCardMark[i].type].endValue - currencyEffect[boxCardMark[i].type].startValue <= 100000)
							currencyEffect[boxCardMark[i].type].totalFrame = currencyEffect[boxCardMark[i].type].frame = FPS * 4;
						else
							currencyEffect[boxCardMark[i].type].totalFrame = currencyEffect[boxCardMark[i].type].frame = FPS * 5;
					}
				}
				else {
					boxCardMark[i].frame++;
				}
			}

			if (boxCardMark[i].type == ITEM_CREW) {
				curStar = maxStar = enemyData[crewData[boxCardMark[i].detail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR] + 1;
			}
			else {
				//curStar = maxStar = GetItemStar(boxCardMark[i].type, boxCardMark[i].detail, boxCardMark[i].grade);
				curStar = boxCardMark[i].cooldown;
				maxStar = ITEMMAXLEVEL;
			}

			DrawRewardCard(boxCardMark[i].type, boxCardMark[i].detail, boxCardMark[i].grade, boxCardMark[i].cooldown, boxCardMark[i].amount, xOffset + boxCardMark[i].x - (float)(REWARDCARDSIZE_X) / 2 * boxCardMark[i].zoom, boxCardMark[i].y + (float)(REWARDCARDSIZE_Y) / 2 * boxCardMark[i].zoom, false, boxCardMark[i].zoom, boxCardMark[i].cardFrame, boxCardMark[i].newItem, true, curStar, maxStar, true, boxCardMark[i].openFrame);

		}
	}

	//커런시 효과를 생성하는 함수
	for (i = 0; i < TOTALCURRENCYMARKARR; i++) {
		if (currencyMarkArr_PopUp[i].frame > 0) {
			SetCurrencyMark_PopUp(currencyMarkArr_PopUp[i].x, currencyMarkArr_PopUp[i].y, currencyMarkArr_PopUp[i].targetX, currencyMarkArr_PopUp[i].targetY, currencyMarkArr_PopUp[i].targetX2, currencyMarkArr_PopUp[i].targetY2, currencyMarkArr_PopUp[i].speed, currencyMarkArr_PopUp[i].speedIncrement, currencyMarkArr_PopUp[i].speed2, currencyMarkArr_PopUp[i].speedIncrement2, currencyMarkArr_PopUp[i].waitingFrame, currencyMarkArr_PopUp[i].waitingFrame2, currencyMarkArr_PopUp[i].icon, currencyMarkArr_PopUp[i].moveAngle, currencyMarkArr_PopUp[i].amount, currencyMarkArr_PopUp[i].type, currencyMarkArr_PopUp[i].zoom, currencyMarkArr_PopUp[i].zoomEnd, currencyMarkArr_PopUp[i].zoomIncrement, currencyMarkArr_PopUp[i].zoom2, currencyMarkArr_PopUp[i].zoomEnd2, currencyMarkArr_PopUp[i].zoomIncrement2);

			if (currencyMarkArr_PopUp[i].frame == currencyMarkArr_PopUp[i].iconMarkCnt) {
				memset(&currencyMarkArr_PopUp[i], 0, sizeof(currencyMarkArr_PopUp[i]));
			}
			else
				currencyMarkArr_PopUp[i].frame++;
		}
	}

	//커런시 효과가 나오면
	for (i = 0; i < TOTALCURRENCYMARK; i++) {
		//프레임2가 크면
		if (currencyMark_PopUp[i].frame2 > 0) {
			GotoPosition(currencyMark_PopUp[i].targetX2, currencyMark_PopUp[i].targetY2, i, currencyMark_PopUp[i].speed2, ICONMARK_CURRENCY_POPUP);
			currencyMark_PopUp[i].speed2 += currencyMark_PopUp[i].speedIncrement2;
			currencyMark_PopUp[i].zoom2 += currencyMark_PopUp[i].zoomIncrement2;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (currencyMark_PopUp[i].zoomIncrement2 > 0 && currencyMark_PopUp[i].zoom2 > currencyMark_PopUp[i].zoomEnd2)
				currencyMark_PopUp[i].zoom2 = currencyMark_PopUp[i].zoomEnd2;
			if (currencyMark_PopUp[i].zoomIncrement2 < 0 && currencyMark_PopUp[i].zoom2 < currencyMark_PopUp[i].zoomEnd2)
				currencyMark_PopUp[i].zoom2 = currencyMark_PopUp[i].zoomEnd2;

			if ((currencyMark_PopUp[i].targetX2 - currencyMark_PopUp[i].x) * (currencyMark_PopUp[i].targetX2 - currencyMark_PopUp[i].x) + (currencyMark_PopUp[i].targetY2 - currencyMark_PopUp[i].y) * (currencyMark_PopUp[i].targetY2 - currencyMark_PopUp[i].y) < 2 * currencyMark_PopUp[i].speed2 * currencyMark_PopUp[i].speed2 && currencyMark_PopUp[i].frame2 >= currencyMark_PopUp[i].waitingFrame2 && currencyMark_PopUp[i].waitingFrame2 != CURRENCYDONTERASE) {
				//if (currencyMark_PopUp[i].frame2 >= currencyMark_PopUp[i].waitingFrame2) {
					//PlayMusic(M_COIN);
				currencyEffect[currencyMark_PopUp[i].type].iconFrame += CURRENCYMARKEFFECTFRAME;

				if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 10)
					currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = 1;
				else if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 100)
					currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS;
				else if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 1000)
					currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS * 2;
				else if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 10000)
					currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS * 3;
				else if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 100000)
					currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS * 4;
				else
					currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS * 5;

				if (currencyMark[i].type == CURRENCY_EXP)
					AddBar(&bar[BAR_CROWN], 1, BARFRAME);

				memset(&currencyMark_PopUp[i], 0, sizeof(ICONMARK));

			}
			else {
				currencyMark_PopUp[i].frame2++;
			}
			if (currencyMark_PopUp[i].frame2 > 0) {

				if (currencyMark_PopUp[i].icon == ICON_CROWN || currencyMark_PopUp[i].icon == ICON_STAR) {
					if (currencyMark_PopUp[i].amount > 0) {
						DrawStarNum(currencyMark_PopUp[i].icon, currencyMark_PopUp[i].amount, currencyMark_PopUp[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom2, currencyMark_PopUp[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom2, currencyMark_PopUp[i].zoom2);
					}
					else
						DrawIcon(currencyMark_PopUp[i].icon + (currencyMark_PopUp[i].icon == ICON_GOLD ? currencyMark_PopUp[i].frame2 % GOLDICONFRAME : 0), currencyMark_PopUp[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom2, currencyMark_PopUp[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom2, currencyMark_PopUp[i].zoom2, COLOR_WHITE, false, false, true);
				}
				else
					DrawIcon(currencyMark_PopUp[i].icon + (currencyMark_PopUp[i].icon == ICON_GOLD ? currencyMark_PopUp[i].frame2 % GOLDICONFRAME : 0), currencyMark_PopUp[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom2, currencyMark_PopUp[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom2, currencyMark_PopUp[i].zoom2, COLOR_WHITE, false, false, true);

			}
		}
		else if (currencyMark_PopUp[i].frame > 0) {
			GotoPosition(currencyMark_PopUp[i].targetX, currencyMark_PopUp[i].targetY, i, currencyMark_PopUp[i].speed, ICONMARK_CURRENCY_POPUP);
			currencyMark_PopUp[i].speed += currencyMark_PopUp[i].speedIncrement;
			currencyMark_PopUp[i].zoom += currencyMark_PopUp[i].zoomIncrement;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (currencyMark_PopUp[i].zoomIncrement > 0 && currencyMark_PopUp[i].zoom > currencyMark_PopUp[i].zoomEnd)
				currencyMark_PopUp[i].zoom = currencyMark_PopUp[i].zoomEnd;
			if (currencyMark_PopUp[i].zoomIncrement < 0 && currencyMark_PopUp[i].zoom < currencyMark_PopUp[i].zoomEnd)
				currencyMark_PopUp[i].zoom = currencyMark_PopUp[i].zoomEnd;

			if ((currencyMark_PopUp[i].targetX - currencyMark_PopUp[i].x) * (currencyMark_PopUp[i].targetX - currencyMark_PopUp[i].x) + (currencyMark_PopUp[i].targetY - currencyMark_PopUp[i].y) * (currencyMark_PopUp[i].targetY - currencyMark_PopUp[i].y) < 2 * currencyMark_PopUp[i].speed * currencyMark_PopUp[i].speed && currencyMark_PopUp[i].frame >= currencyMark_PopUp[i].waitingFrame) {
				//if (currencyMark_PopUp[i].frame >= currencyMark_PopUp[i].waitingFrame) {
					//PlayMusic(M_COIN);
					//두번째 세팅이 있으면 
				if (currencyMark_PopUp[i].targetX2 != 0 || currencyMark_PopUp[i].targetY2 != 0) {
					currencyMark_PopUp[i].frame2 = 1;
				}
				else {
					currencyEffect[currencyMark_PopUp[i].type].iconFrame += CURRENCYMARKEFFECTFRAME;

					if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 10)
						currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = 1;
					else if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 100)
						currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS;
					else if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 1000)
						currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS * 2;
					else if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 10000)
						currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS * 3;
					else if (currencyEffect[currencyMark_PopUp[i].type].endValue - currencyEffect[currencyMark_PopUp[i].type].startValue <= 100000)
						currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS * 4;
					else
						currencyEffect[currencyMark_PopUp[i].type].totalFrame = currencyEffect[currencyMark_PopUp[i].type].frame = FPS * 5;

					memset(&currencyMark_PopUp[i], 0, sizeof(ICONMARK));
				}
			}
			else {
				currencyMark_PopUp[i].frame++;
			}

			if (currencyMark_PopUp[i].frame > 0) {
				if (currencyMark_PopUp[i].icon == ICON_CROWN || currencyMark_PopUp[i].icon == ICON_STAR) {
					if (currencyMark_PopUp[i].amount > 0) {
						DrawStarNum(currencyMark_PopUp[i].icon, currencyMark_PopUp[i].amount, currencyMark_PopUp[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom, currencyMark_PopUp[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom, currencyMark_PopUp[i].zoom);
					}
					else
						DrawIcon(currencyMark_PopUp[i].icon + (currencyMark_PopUp[i].icon == ICON_GOLD ? currencyMark_PopUp[i].frame % GOLDICONFRAME : 0), currencyMark_PopUp[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom, currencyMark_PopUp[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom, currencyMark_PopUp[i].zoom, COLOR_WHITE, false, false, true);

				}
				else
					DrawIcon(currencyMark_PopUp[i].icon + (currencyMark_PopUp[i].icon == ICON_GOLD ? currencyMark_PopUp[i].frame % GOLDICONFRAME : 0), currencyMark_PopUp[i].x - (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom, currencyMark_PopUp[i].y + (float)(ITEMICONSIZE) / 2 * currencyMark_PopUp[i].zoom, currencyMark_PopUp[i].zoom, COLOR_WHITE, false, false, true);

			}
		}
	}

	for (i = 0; i < MAXLOG; i++) {
		if (gameLog[i].frame2 > 0) {
			GotoPositionLog(gameLog[i].targetX2, gameLog[i].targetY2, i, gameLog[i].speed2, ICONMARK_CURRENCY);
			gameLog[i].speed2 += gameLog[i].speedIncrement2;
			gameLog[i].zoom2 += gameLog[i].zoomIncrement2;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (gameLog[i].zoomIncrement2 > 0 && gameLog[i].zoom2 > gameLog[i].zoomEnd2)
				gameLog[i].zoom2 = gameLog[i].zoomEnd2;
			if (gameLog[i].zoomIncrement2 < 0 && gameLog[i].zoom2 < gameLog[i].zoomEnd2)
				gameLog[i].zoom2 = gameLog[i].zoomEnd2;

			if ((gameLog[i].targetX2 - gameLog[i].x) * (gameLog[i].targetX2 - gameLog[i].x) + (gameLog[i].targetY2 - gameLog[i].y) * (gameLog[i].targetY2 - gameLog[i].y) < 2 * gameLog[i].speed2 * gameLog[i].speed2 && gameLog[i].frame2 >= gameLog[i].waitingFrame2) {
				memset(&gameLog[i], 0, sizeof(ICONMARK));

				for (j = 0; j < MAXLOG; j++) {
					if (gameLog[j].active == true && gameLog[j].frame == 0 && gameLog[j].frame2 == 0) {
						gameLog[j].frame = 1;
						break;
					}
				}

			}
			else {
				gameLog[i].frame2++;
			}
			if (gameLog[i].frame2 > 0)
				LogDraw(&gameLog[i]);

		}
		else if (gameLog[i].frame > 0) {
			GotoPositionLog(gameLog[i].targetX, gameLog[i].targetY, i, gameLog[i].speed, ICONMARK_CURRENCY);
			gameLog[i].speed += gameLog[i].speedIncrement;
			gameLog[i].zoom += gameLog[i].zoomIncrement;

			//if (gameLog[i].speed < 4 * _2X)
			//	gameLog[i].speed = 4 * _2X;

			//만약 증가량이 0보다 크면
			//end보다 크면 end에서 멈춘다.
			if (gameLog[i].zoomIncrement > 0 && gameLog[i].zoom > gameLog[i].zoomEnd)
				gameLog[i].zoom = gameLog[i].zoomEnd;
			if (gameLog[i].zoomIncrement < 0 && gameLog[i].zoom < gameLog[i].zoomEnd)
				gameLog[i].zoom = gameLog[i].zoomEnd;

			if ((gameLog[i].targetX - gameLog[i].x) * (gameLog[i].targetX - gameLog[i].x) + (gameLog[i].targetY - gameLog[i].y) * (gameLog[i].targetY - gameLog[i].y) < 2 * gameLog[i].speed * gameLog[i].speed && gameLog[i].frame >= gameLog[i].waitingFrame) {
				//if (gameLog[i].frame >= gameLog[i].waitingFrame) {
					//PlayMusic(M_COIN);
					//두번째 세팅이 있으면 
				if (gameLog[i].targetX2 != 0 || gameLog[i].targetY2 != 0) {
					gameLog[i].frame2 = 1;
				}
				else {
					memset(&gameLog[i], 0, sizeof(LOG));

					for (j = 0; j < MAXLOG; j++) {
						if (gameLog[j].active == true && gameLog[j].frame == 0 && gameLog[j].frame2 == 0) {
							gameLog[j].frame = 1;
							break;
						}
					}

				}
			}
			else {
				gameLog[i].frame++;
			}

			if (gameLog[i].frame > 0)
				LogDraw(&gameLog[i]);

		}
	}
	//popMenu
	if (drawHandle == MD_NEWCOLLECTION || drawHandle == MD_NEWCARD) {
		if (popUpFrame == 0)
			zoom = 1.0f;
		else if (popUpFrame > 0)
			zoom = popUpFrameData[popUpFrame];

		if (popUpFrame > 0)
			popUpFrame++;

		if (popUpFrame == 8)
			popUpFrame = 0;
	}

	//얘네들은 최상위단에 별도로 그려줘야 한다.
	switch (drawHandle) {
	case MD_NEWCOLLECTION:
		NewCollectionDraw(DX / 2 - (float)(DX / 2) * zoom, DY / 2 + (float)(236 * _2X) * zoom, zoom);
		break;
	case MD_NEWCARD:
		NewCardDraw();
		break;
	case MD_STAGECLEAR:
		StageInfoDraw(robin.stage, robin.room, false, false, xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2), POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2, zoom);
		break;
	}
	
	//여기서 튜토리얼 팝업을 띄워준다.

	//여기서 캐릭터 선택 팝업을 띄워준다.

	if (touch && touchFrame)
		DrawTouchPoint();

	if (vibrationFrame)
		vibrationFrame--;

	if (resumeFlag == true)
		resumeFlag = false;

#ifdef GUIDELINE
	int iStart = 0;
	int iEnd = rh - 4;
	int jStart = 0;
	int jEnd = rw - 4;

	//for (i = 0; i < rw + 2; i++)
	//	for (j = 0; j < rh + 2; j++)
	//		if (mapInfoArray[i * (rw + 2) + j] == TILE_BLOCK)
	//			MemRect(TSIZE * j, STATUSWIN_Y + (rh - 4) * TSIZE - TSIZE * i, TSIZE, TSIZE, COLOR_BLACK, gScreenBuffer, gScreenLayer, false);

	if (touchDisable == false) {
		for (i = 0; i < touchIndex; i++)
			MemRectFrame(touchRect[i][0], touchRect[i][1], touchRect[i][2], touchRect[i][3], 0xFF0000);
		for (i = 0; i < swipeIndex; i++)
			MemRectFrame(swipeRect[i][0], swipeRect[i][1], swipeRect[i][2], swipeRect[i][3], 0xFFFF00);

		for (i = 0; i < TOTALRAIDBOX; i++)
			MemRectFrame(xOffset + raidBox[i].x + raidBox[i].cpx, raidBox[i].y + raidBox[i].cpy, raidBox[i].cx, raidBox[i].cy, 0xFFFF00);

		MemRectFrame(xOffset + ao[NPC].x + ao[NPC].cpx, ao[NPC].y + ao[NPC].cpy, ao[NPC].cx, ao[NPC].cy, 0xFFFF00);
	}
		
#endif

	MemRectFrame(0, DY, 1, 1, 0x000000);

	frame++;
	if (touchedFrame > 0)
		touchedFrame++;

	VersionDraw();
}

//세이브데이터에 획득경험치, 변경된 레벨, 보상까지 같이 다 저장해 준다.
void SS_UserLevelUp(int getExp)
{
	/*
	int tempLevel;
	tempLevel = robin.lv;

	robin.exps += getExp;

	while (robin.exps >= NextExp(robin.lv)) {
		//lv
		GetLevelUpReward(robin.lv);
		robin.lv++;
		robin.
	}
	*/

}

int CheckSpace(int space)
{
	//int sp = MC_fsAvailable();

	//if (sp != M_E_ERROR && sp < space)
	//	return space - sp;
	//else
	return space;
}

long MC_knlCurrentTime()
{
	timeval tv;
	gettimeofday(&tv, NULL);
	long lMillisec = tv.tv_usec / 1000 + tv.tv_sec * 1000;
	return lMillisec;
}

long MC_knlCurrentTimeStamp()
{
	time_t timer;
	struct tm y2k = { 0 };
	double seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(timer, mktime(&y2k));

	//printf ("%.f seconds since January 1, 2000 in the current timezone", seconds);

	return seconds;
}










































