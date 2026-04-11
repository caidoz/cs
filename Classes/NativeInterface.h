#pragma once

#ifndef __NATIVEINTERFACE_H__
#define __NATIVEINTERFACE_H__

#include "Def.h"

#include "cocos2d.h"
#include <iostream>
#include <string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
extern "C"
{
	extern void Jni_callSpeakString(const char *javaString, int voiceType);

	extern void Noti_show(std::string message, int interval, int tag);
	extern void Noti_cancel(int tag);
	extern void Noti_init(void);
}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
class NativeInterface
{
public:
	static void Jni_callSpeakString(const char *javaString, int voiceType);
	static void Noti_show(std::string message, int interval, int tag);
	static void Noti_cancel(int tag);
	static void Noti_init(void);
};
#endif
#endif /* defined(__NATIVEINTERFACE_H__) */
//#endif
