//
//  AdMobCtrl.cpp
//  AdmobTest
//
//  Created by Mr.Ru on 2015. 11. 15..
//
//


#include "AdMobCtrl.h"


USING_NS_CC;
AdMobCtrl* AdMobCtrl::s_singleInstance = nullptr;

AdMobCtrl* AdMobCtrl::getInstance()
{
    if (s_singleInstance == nullptr)
    {
        s_singleInstance = new (std::nothrow) AdMobCtrl();
        // Add the first auto release pool
        new cocos2d::AutoreleasePool("cocos2d autorelease pool");
    }
    return s_singleInstance;
}

void AdMobCtrl::destroyInstance()
{
    delete s_singleInstance;
    s_singleInstance = nullptr;
}

AdMobCtrl::AdMobCtrl()
{
    m_pAdMob=new AdMobPlugin;
    m_bLoaded_Full=false; // 전체광고 로드되었나
    m_bLoaded_Banner=false;   // 배너광고 로드되었나
    m_bshow_FullAD=false;
    m_bshow_Banner=false;
}
AdMobCtrl::~AdMobCtrl()
{
    delete m_pAdMob;
}
void    AdMobCtrl::InitAdMob(char *szFullAddID, char *szBannerID, bool bSim)//AdMob초기화
{
    m_bSim=bSim;
    sprintf(szFullAD_ID, "%s",szFullAddID);
    sprintf(szBannerAD_ID, "%s" ,szBannerID);
    
    AdMobFullScreen_Init(szFullAD_ID, bSim);
    AdMobBanner_Init(szBannerAD_ID,bSim );
    
}

void AdMobCtrl::AdMobFullScreen_Init(char *szCodeID , bool bSim)//전면광고를 초기화한다. .. 광고ID , 출시용은 bSim=false로 설정하자
{
    m_pAdMob->AdMobFullScreen_Init(szCodeID,bSim);
}
void AdMobCtrl::AdMobBanner_Init(char *szCodeID , bool bSim)//배너광고
{
    m_pAdMob->AdMobBanner_Init(szCodeID,bSim);
}

void AdMobCtrl::AdMobFullScreen_ReLoad()
{
    m_pAdMob->AdMobFullScreen_ReLoad(szFullAD_ID);
}

void AdMobCtrl::AdMobFullScreen_Show()
{
    if (m_bLoaded_Full)
    {
        m_pAdMob->AdMobFullScreen_Show();
        m_bshow_FullAD=true;
    }
    
}
void    AdMobCtrl::AdMobBanner_Show()
{
    if (m_bshow_Banner==false)
    {
        m_pAdMob->AdMobBanner_Show();
    }
    m_bshow_Banner=true;
    
}
void    AdMobCtrl::AdMobBanner_Hide()
{
    m_pAdMob->AdMobBanner_Hide();
    m_bshow_Banner=false;
}


void    AdMobCtrl::onAdMobFullScreen_PreLoaded()  //전체 광고 로드됐다.
{
    log("광고로드됌");
    m_bLoaded_Full=true; // 전체광고 로드되었나
}

void    AdMobCtrl::onAdMobFullScreen_Close()//유저가 광고 닫았을때 이벤트
{
    log("광고 닫음");
    m_bLoaded_Full=false; // 전체광고 로드되었나
    m_bshow_FullAD=false;
    AdMobFullScreen_ReLoad();
}

void    AdMobCtrl::onAdMobBanner_Loaded() //배너광고 로드됐다.
{
    log("배너광고 로드됐음요");

    if (m_bLoaded_Banner)
    {
        m_pAdMob->AdMobBanner_Show();
    }
}







bool    AdMobCtrl::isLoadedFullAD()   //전면광고 로드돼었나
{
    return m_bLoaded_Full;
    
}
bool    AdMobCtrl::isLoadedBannerAD() // 배너광고 로드돼었나
{
    return m_bLoaded_Banner;
}
bool    AdMobCtrl::isView_FullAD()//전면광고를 보여주고있는가
{
    return m_bshow_FullAD;
}
bool    AdMobCtrl::isView_BannerAD()//배너광고 보여주고있는가
{
    return m_bshow_Banner;
}









