//
//  AdMobPlugin.hpp
//  AdmobTest
//
//  Created by Mr.Ru on 2015. 11. 15..
//
//

#ifndef AdMobPlugin_hpp
#define AdMobPlugin_hpp


class AdMobPlugin
{
public:
    void AdMobFullScreen_Init(char *szCodeID , bool bSim);//전면광고를 초기화한다. .. 광고ID , 출시용은 bSim=false로 설정하자
    void AdMobBanner_Init(char *szCodeID , bool bSim);//배너광고
    
    
    void AdMobFullScreen_ReLoad(char *szCodeID);
    void AdMobFullScreen_Show();
    
    void AdMobBanner_Show();
    void AdMobBanner_Hide();
    
};
#endif /* AdMobPlugin_hpp */
