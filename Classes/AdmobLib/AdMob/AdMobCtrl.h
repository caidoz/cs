//
//  AdMobCtrl.hpp
//  AdmobTest
//
//  Created by Mr.Ru on 2015. 11. 15..
//
//

#ifndef AdMobCtrl_hpp
#define AdMobCtrl_hpp
#include "cocos2d.h"
#include "AdMobPlugin.h"


class AdMobCtrl
{
public:
    static AdMobCtrl* getInstance();
    static void destroyInstance();
    
    AdMobCtrl();
    ~AdMobCtrl();
    
    
    void    InitAdMob(char *szFullAddID, char *szBannerID, bool bSim);//AdMob초기화
    
    
public:
    void AdMobFullScreen_Init(char *szCodeID , bool bSim);//전면광고를 초기화한다. .. 광고ID , 출시용은 bSim=false로 설정하자
    void AdMobBanner_Init(char *szCodeID , bool bSim);//배너광고
    
    
    void    AdMobFullScreen_ReLoad();
    void    AdMobFullScreen_Show();
    
    
    void    AdMobBanner_Show();
    void    AdMobBanner_Hide();
    
    
    void    onAdMobFullScreen_PreLoaded();  //전체 광고 로드됐다.
    void    onAdMobFullScreen_Close();//유저가 광고 닫았을때 이벤트
    
    void    onAdMobBanner_Loaded(); //배너광고 로드됐다.
    
public:
    
    bool    isLoadedFullAD();   //전면광고 로드돼었나
    bool    isLoadedBannerAD(); // 배너광고 로드돼었나
    bool    isView_FullAD();//전면광고를 보여주고있는가
    bool    isView_BannerAD();//배너광고 보여주고있는가
    
private:
    
    static AdMobCtrl* s_singleInstance;
    
    AdMobPlugin *m_pAdMob;
    
    char szFullAD_ID[100];
    char szBannerAD_ID[100];
    bool    m_bSim;
    
    
    bool    m_bLoaded_Full; // 전체광고 로드되었나
    bool    m_bLoaded_Banner;   // 배너광고 로드되었나
    
    bool    m_bshow_FullAD; //전면광고 보여주고있다.
    bool    m_bshow_Banner; //배너광고를 보여주고있다.
    
    
};

#endif /* AdMobCtrl_hpp */
