//
//  AdMobPlugin.cpp
//  CurshPop
//
//  Created by Mr.Ru on 2015. 11. 15..
//
//


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "cocos2d.h"
#include "AdMobPlugin.h"
#include "platform/android/jni/JniHelper.h"
#include "AdMobCtrl.h"
//-- 이벤트 등록
extern "C"
{
    void Java_com_admob_AdMob_nativeOnAdMobFullScreenPreLoaded(JNIEnv * env, jobject obj)
    {
        AdMobCtrl::getInstance()->onAdMobFullScreen_PreLoaded();
    }
    void Java_com_admob_AdMob_nativeOnAdMobFullScreenClose(JNIEnv * env, jobject obj)
    {
        AdMobCtrl::getInstance()->onAdMobFullScreen_Close();
    }
    void Java_com_admob_AdMob_nativeOnAdMobBannerLoaded(JNIEnv * env, jobject obj)
    {
        AdMobCtrl::getInstance()->onAdMobBanner_Loaded();
    }
}


void AdMobPlugin::AdMobFullScreen_Init(char *szCodeID , bool bSim)
{
    cocos2d::JniMethodInfo methodInfo;
    std::string strADCodeID=szCodeID ;
    
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/admob/AdMob","initInterstital", "(Ljava/lang/String;Z)V"))
    {
        return ;
    }
    
    jstring stringArg = methodInfo.env->NewStringUTF(strADCodeID.c_str());
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg,bSim);
    methodInfo.env->DeleteLocalRef(stringArg);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return;
}//전면광고를 초기화한다. .. 광고ID , 출시용은 bSim=false로 설정하자
void AdMobPlugin::AdMobBanner_Init(char *szCodeID , bool bSim)
{
    cocos2d::JniMethodInfo methodInfo;
    std::string strADCodeID=szCodeID ;
    
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/admob/AdMob","initBanner", "(Ljava/lang/String;Z)V"))
    {
        return ;
    }
    jstring stringArg = methodInfo.env->NewStringUTF(strADCodeID.c_str());
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg,bSim);
    methodInfo.env->DeleteLocalRef(stringArg);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return;
}//배너광고


void AdMobPlugin::AdMobFullScreen_ReLoad(char *szCodeID)
{
    cocos2d::JniMethodInfo methodInfo;
    std::string strADCodeID=szCodeID ;
    
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/admob/AdMob","ReRloadInterstital", "(Ljava/lang/String;)V"))
    {
        return ;
    }
    jstring stringArg = methodInfo.env->NewStringUTF(strADCodeID.c_str());
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
    methodInfo.env->DeleteLocalRef(stringArg);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return;
    
}


void AdMobPlugin::AdMobFullScreen_Show()
{
    cocos2d::JniMethodInfo methodInfo;
    
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/admob/AdMob","showImterstitial", "()V"))
    {
        return ;
    }
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return;
}

void AdMobPlugin::AdMobBanner_Show()
{
    cocos2d::JniMethodInfo methodInfo;
    
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/admob/AdMob","AdMobBannerShow", "()V"))
    {
        return ;
    }
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return;
}
void AdMobPlugin::AdMobBanner_Hide()
{
    cocos2d::JniMethodInfo methodInfo;
    
    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com/admob/AdMob","AdMobBannerHide", "()V"))
    {
        return ;
    }
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    return;
}

#else

// IOS는 따로구현

#endif

