//cd C:\Users\polyp\Desktop\CP\cs\proj.android
//gradlew.bat :cs:assembleDebug 2>&1 | findstr /i "error: error failed failure fatal exception"


#include "Content.h"
#include "AppDelegate.h"
#include "CoreClass.h"
//#define SDKBOX_ENABLED
#ifdef SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#endif

 #define USE_AUDIO_ENGINE 1
 //#define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#ifdef USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#else //USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;
static cocos2d::Size designResolutionSize = cocos2d::Size(640, 640 * 133 / 100);
//static cocos2d::Size designResolutionSize = cocos2d::Size(640, 640 * 208 / 100);
//static cocos2d::Size designResolutionSize = cocos2d::Size(1080, 2340);
//static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 2048);
static cocos2d::Size smallResolutionSize = cocos2d::Size(320, 480);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(768, 1024);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1536, 2048);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
	AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
	//GLContextAttrs glContextAttrs = { 0, 0, 0, 0, 0, 8, 0 };
	//GLContextAttrs glContextAttrs = { 4, 4, 4, 4, 16, 0, 0 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	//내려받은 콘텐츠 폴더를 검색 경로 맨 앞에 넣는다.
	//리소스를 하나라도 읽기 전에 해야 한다. 나중에 하면 이미 읽어둔 것이
	//앱에 딸려온 옛 파일로 굳는다.
	ContentInstallSearchPath();

#ifdef SDKBOX_ENABLED
	sdkbox::PluginAdMob::init();
#endif
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("인삼남:인생이 삼일 남았다!", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		// Set the design resolution
		//glview->setFrameSize(640, 640 * 134 / 100);//WINDOWS
		//glview->setFrameSize(640, 640 * 134 / 100);//WINDOWS
		//glview->setFrameSize(640, 640 * 167 / 100);//WINDOWS
		glview->setFrameSize(640, 640 * 220 / 100);//WINDOWS

#else
		glview = GLViewImpl::create("인삼남:인생이 삼일 남았다!");
#endif

		
		director->setOpenGLView(glview);
	}
	
	auto frameSize = glview->getFrameSize();
	float designW = 640.0f;
	float designH = designW * frameSize.height / frameSize.width;

	glview->setDesignResolutionSize(
		designW,
		designH,
		ResolutionPolicy::FIXED_WIDTH
	);

	// turn on display FPS
	//director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60.0f);
	//director->setAnimationInterval(1.0f / 6.0f);
	//director->setAnimationInterval(1.0f / 20.0f);

	//CCLog("AppDelegate frameSize %f, %f", frameSize.width, frameSize.height); //디바이스 해상도
	//CCLog("AppDelegete director %f, %f", director->getWinSize().width, director->getWinSize().height); //개발 해상도 
	
																										  /*
	// if the frame's height is larger than the height of medium size.
	if (frameSize.height > mediumResolutionSize.height)
	{        
		director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
	}
	// if the frame's height is larger than the height of small size.
	else if (frameSize.height > smallResolutionSize.height)
	{        
		director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
	}
	// if the frame's height is smaller than the height of medium size.
	else
	{        
		director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
	}
	*/

	cocos2d::Device::setKeepScreenOn(true);

	register_all_packages();

	// create a scene. it's an autorelease object
	auto scene = Core::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {

	Director::getInstance()->startAnimation();
	
#if USE_AUDIO_ENGINE
	AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
