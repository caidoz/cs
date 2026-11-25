#include "Func.h"
#include "TitleLobbyMotion.h"
#include <cstdio>
#include <cstdlib>

namespace { int campMusicId=-1,campFadeId=-1;bool campLobbyTrack=false;float campFadeAge=.75f; }
static void StopCampMusic(){
 if(campMusicId>=0)AudioEngine::stop(campMusicId);
 if(campFadeId>=0)AudioEngine::stop(campFadeId);
 campMusicId=campFadeId=-1;campFadeAge=.75f;
}
void PlayCampMusic(bool lobby){
 if(!option.bgm){StopCampMusic();return;}
 if(campMusicId<0||campLobbyTrack!=lobby){
  if(campFadeId>=0)AudioEngine::stop(campFadeId);
  campFadeId=campMusicId;campLobbyTrack=lobby;campFadeAge=0;
  if(curID>=0){AudioEngine::stop(audioID[curID]);curID=-1;}
  campMusicId=AudioEngine::play2d(lobby?"res/lobby-embers-techno-trot.ogg":"res/lobby-embers-at-rest.ogg",true,0,nullptr);
 }
 campFadeAge+=std::max(0.f,std::min(.1f,cocos2d::Director::getInstance()->getDeltaTime()));
 const float fade=std::min(1.f,campFadeAge/.75f);
 if(campMusicId>=0)AudioEngine::setVolume(campMusicId,VOLUME_BGM*fade);
 if(campFadeId>=0){AudioEngine::setVolume(campFadeId,VOLUME_BGM*(1-fade));if(fade>=1){AudioEngine::stop(campFadeId);campFadeId=-1;}}
 static bool logged[2]={false,false};
 if(!logged[lobby]&&std::getenv("CS_CAMP_AUDIO_REVIEW")&&campMusicId>=0&&AudioEngine::getState(campMusicId)==AudioEngine::AudioState::PLAYING&&AudioEngine::getDuration(campMusicId)>(lobby?59:47)){
  logged[lobby]=true;std::printf("PASS native %s loop decoded and playing\n",lobby?"60-second lobby techno trot":"48-second original title");std::fflush(stdout);
 }
}

// Sound 관련
void PlayMusic(int idx)
{
 if(idx>=0&&idx<M_ROULETTEUP)StopCampMusic();
	if (idx < 0)
		return;

	//if (idx < M_ROULETTEUP)
	//	idx = M_TITLE;

	if (option.bgm == false)
		if (idx < M_ROULETTEUP) {
			curID = -1;
			return;
		}

	if (option.se == false)
		if (idx >= M_ROULETTEUP) {
			curID = -1;
			return;
		}

	if (idx < M_ROULETTEUP) {
		if (drawHandle == MD_PLAY && idx >= M_TOLEAVIL && idx <= M_DEVIL)
			idx = M_TITLE;
		if (idx == curID)
			return;

		if (curID != -1)
			AudioEngine::stop(audioID[curID]);
		audioID[idx] = AudioEngine::play2d(GetResourceName(RES_SOUND, idx).c_str(), true, VOLUME_BGM, nullptr);
		//AudioEngine::setVolume(audioID[idx], VOLUME_BGM);

	}
	else {
		audioID[idx] = AudioEngine::play2d(GetResourceName(RES_SOUND, idx).c_str(), false, idx == M_COIN || idx == M_DOWN ? VOLUME_BGM_MUTE : VOLUME_SE, nullptr);

	}

	if (idx < M_ROULETTEUP)
		curID = idx;
	effect.sound = -1;
}

void Stop()
{
 StopCampMusic();
	if (curID != -1)
		AudioEngine::stop(audioID[curID]);

	curID = -1;
}

void TimerMusic()
{

	//플레이중이면 배경음을 틀어준다.
	switch (drawHandle) {
	case MD_PLAY:
		if (bossRaidMode == true)
			PlayMusic(M_EVENT_FUNNY);
		else if (robin.bossRoom == true) {
			PlayMusic(M_BOSS);
		}
		else {
			PlayMusic(M_TITLE);
		}
		break;
	case MD_BATTLE:
	case MD_RAID:
		PlayMusic(M_EVENT_EMERG);
		break;
	}
}

void EffectSound(int music)
{
	if (curID == -1)
		effect.sound = music;
	else if (music > M_ENDING)
		effect.sound = music;

	switch (music) {
	case M_SWORDHIT://칼맞음			//32
	case M_GUNHIT://총맞음			//33
	case M_BOOMERANGHIT://부메랑맞음		//34
		music = M_SWORDHIT;
		break;
	}

	switch (music) {
	case M_SWORDHIT://칼맞음			//32
	case M_GUNHIT://총맞음			//33
	case M_BOOMERANGHIT://부메랑맞음		//34
	case M_LASER://레이저		//36
	case M_BUFF_PINK://핑크색버프	//38
	case M_BUFF_YELLOW://노란색버프	//39
	case M_BUFF_BLUE://파란색버프	//40
	case M_BUFF_RED://빨간색버프	//41
	case M_BANG://터지는소리	//42
	case M_KUNG:	//거대몬스터가 점프했다가 떨어지거나~(쿵)	//44
	case M_OPENDOOR:	//문열때 나는 소리	//45
		//Vibration();
		break;
	}

	audioID[music] = AudioEngine::play2d(GetResourceName(RES_SOUND, music).c_str(), false, 1.0f, nullptr);

	if (music == M_ERROR)
		AudioEngine::setVolume(audioID[music], VOLUME_BGM);
	else
		AudioEngine::setVolume(audioID[music], VOLUME_SE);

}

void Vibration(void)
{
	if (option.vibration && vibrationFrame == 0) {
		vibrationFrame = FPS;
		cocos2d::Device::vibrate(0.01f);
	}
}
