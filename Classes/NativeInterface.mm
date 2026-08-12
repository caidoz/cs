#ifndef _NATIVEINTERFACE_
#define	_NATIVEINTERFACE_

#include "NativeInterface.h"
#include "Def.h"
#import "AVFoundation/AVFoundation.h"

using namespace cocos2d;
using namespace std;

AVSpeechSynthesizer *speechSynthesizer = [[AVSpeechSynthesizer alloc]init];
AVSpeechUtterance *utterance;

void NativeInterface::Jni_callSpeakString(const char *javaString, int voiceType)
{
	//0: rate, 1: pitchMultiplier, 2: volume
	float voiceData[] = {
		0.0f, 0.0f, 0.0f,//VOICE_NOVOICE = 0,
		0.6f, 0.5f, 0.9f,//VOICE_BIGMOUTH,
		0.4f, 1.0f, 1.0f,//VOICE_SKILLANNOUNCER,
		0.6f, 0.5f, 0.9f,//VOICE_SOLDIER,
		0.8f, 0.5f, 1.0f,//VOICE_TITLE,
	};

	if (voiceType == VOICE_NOVOICE)
		return;

	NSString * tempStr = [NSString stringWithUTF8String : ((std::string)javaString).c_str()];

	utterance = [AVSpeechUtterance speechUtteranceWithString : tempStr];
	//if (idx < TOTALSKILL)
	utterance.rate = voiceData[voiceType * 3 + 0];
	//else
	//    utterance.rate = 0.4f;
	utterance.voice = [AVSpeechSynthesisVoice voiceWithLanguage : @"ko-KR"];
		//utterance.voice = AVSpeechSynthesisVoice(identifier: "Yuna")
		utterance.pitchMultiplier = voiceData[voiceType * 3 + 1];
	//utterance.preUtteranceDelay = 0;
	//utterance.postUtteranceDelay = 0;
	//if (idx < TOTALSKILL)
	utterance.volume = voiceData[voiceType * 3 + 2];
	//else
	//    utterance.volume = 0.9f;
	//[utterance setVoice:ko-KR];
	//[utterance setRate:0.5f];
	[speechSynthesizer speakUtterance : utterance];
	 
}

void NativeInterface::Noti_show(std::string message, int interval, int tag)
{
	[[UIApplication sharedApplication] cancelAllLocalNotifications];

	// 通知を作成する
	UILocalNotification *notification = [[UILocalNotification alloc] init];

	//notification.fireDate = [[NSDate date] dateByAddingTimeInterval:interval];
	notification.fireDate = [NSDate dateWithTimeIntervalSinceNow : interval];
	notification.timeZone = [NSTimeZone defaultTimeZone];
	//notification.alertBody = [NSString stringWithCString:message.c_str() encoding:[NSString defaultCStringEncoding]];
	notification.alertBody = [NSString stringWithUTF8String : message.c_str()];
	notification.alertAction = @"Open";
		notification.soundName = UILocalNotificationDefaultSoundName;

	NSNumber* tag1 = [NSNumber numberWithInteger : tag];
	NSDictionary *infoDict = [NSDictionary dictionaryWithObject : tag1 forKey : @"ID"];
	notification.userInfo = infoDict;

	// 通知を登録する
	[[UIApplication sharedApplication] scheduleLocalNotification:notification];

	[notification release];
}

void NativeInterface::Noti_cancel(int tag)
{
	for (UILocalNotification *notification in[[UIApplication sharedApplication] scheduledLocalNotifications]) {
		if ([[notification.userInfo objectForKey : @"ID"] integerValue] == tag) {
			[[UIApplication sharedApplication] cancelLocalNotification:notification];
		}
	}
}

void NativeInterface::Noti_init()
{
	UIUserNotificationType types = (UIUserNotificationType)(UIUserNotificationTypeBadge | UIUserNotificationTypeSound | UIUserNotificationTypeAlert);

	UIUserNotificationSettings* mySettings = [UIUserNotificationSettings settingsForTypes : types categories : nil];

	[[UIApplication sharedApplication] registerUserNotificationSettings:mySettings];
}

#endif
