#include "Func.h"
#include "TitleLobbyMotion.h"
#include "GameSfx.h"
#include <chrono>
#include <vector>
#include <algorithm>
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

namespace NewSfx {
struct Voice{int audio,cue,priority;};
static std::vector<Voice> voices;
static double last[49];static bool initialized=false;
static int played=0,suppressed=0;
static int priority(int cue){return cue==M_BUTTON||cue==M_SELECT||cue==M_ERROR?8:cue==M_GUNSTRONG||cue==M_LEVELUP||cue==M_CHEER?9:cue==M_RUN||cue==M_TALK?1:5;}
static void prune(){voices.erase(std::remove_if(voices.begin(),voices.end(),[](const Voice& v){return AudioEngine::getState(v.audio)==AudioEngine::AudioState::ERROR;}),voices.end());}
}
int GameSfxPlayedCount(){return NewSfx::played;}
int GameSfxSuppressedCount(){return NewSfx::suppressed;}
int GameSfxActiveCount(){NewSfx::prune();return (int)NewSfx::voices.size();}
void StopGameSfx(){for(const auto& v:NewSfx::voices)AudioEngine::stop(v.audio);NewSfx::voices.clear();}
bool DispatchGameSfx(int cue){
 if(cue<M_ROULETTEUP)return false;if(cue>=TOTALMUSIC)return true;
 static_assert(TOTALMUSIC-M_ROULETTEUP==49,"Update the complete SFX bank when adding IDs");
 using namespace NewSfx;
 if(!option.se){StopGameSfx();return true;}
 if(!initialized){std::fill(last,last+49,-1.e9);initialized=true;}
 const double now=std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
 const int slot=cue-M_ROULETTEUP;const double gap=cue==M_ERROR?.22:cue==M_COIN?.075:cue==M_RUN?.09:cue==M_TALK?.065:cue==M_BUTTON||cue==M_SELECT?.075:.035;
 if(now-last[slot]<gap){++suppressed;return true;}prune();
 const int rank=priority(cue);
 if(voices.size()>=12){auto old=std::min_element(voices.begin(),voices.end(),[](const Voice& a,const Voice& b){return a.priority<b.priority;});if(old->priority>rank){++suppressed;return true;}AudioEngine::stop(old->audio);voices.erase(old);}
 int same=0;for(const auto& v:voices)if(v.cue==cue)++same;
 if(same>=3){auto old=std::find_if(voices.begin(),voices.end(),[&](const Voice& v){return v.cue==cue;});AudioEngine::stop(old->audio);voices.erase(old);}
 const float gain=cue==M_TALK||cue==M_RUN?.28f:cue==M_COIN?.52f:cue==M_BUTTON?.58f:.76f;
 const int id=AudioEngine::play2d(GameSfxPath(cue),false,std::getenv("CS_SFX_REVIEW")?0.f:VOLUME_SE*gain,nullptr);
 if(id>=0){audioID[cue]=id;voices.push_back({id,cue,rank});last[slot]=now;++played;if(std::getenv("CS_SFX_TRACE")){std::printf("SFX PLAY %d %s\n",cue,GameSfxPath(cue).c_str());std::fflush(stdout);}}
 return true;
}

// Sound 관련
void PlayMusic(int idx){
 if(idx<0||idx>=TOTALMUSIC)return;
 if(DispatchGameSfx(idx)){effect.sound=-1;return;}
 // Music and one-shots share enum IDs, but never share mute or playback state.
 if(!option.bgm){Stop();return;}
 StopCampMusic();
 if(drawHandle==MD_PLAY&&idx>=M_TOLEAVIL&&idx<=M_DEVIL)idx=M_TITLE;
 if(idx==curID)return;
 if(curID>=0)AudioEngine::stop(audioID[curID]);
 audioID[idx]=AudioEngine::play2d(GetResourceName(RES_SOUND,idx),true,VOLUME_BGM,nullptr);
 curID=idx;effect.sound=-1;
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

void EffectSound(int music){
 if(music>=M_ROULETTEUP){effect.sound=music;DispatchGameSfx(music);}
 else if(music>=0)PlayMusic(music);
}

void Vibration(void)
{
	if (option.vibration && vibrationFrame == 0) {
		vibrationFrame = FPS;
		cocos2d::Device::vibrate(0.01f);
	}
}
