//
//  AdMob.m
//  CurshPop
//
//  Created by Mr.Ru on 2015. 11. 25..
//
//

#import "AdMob.h"

#import "AppController.h"

#include "../Classes/AdMob/AdMobCtrl.h"

@implementation AdMob


static AdMob *shared=nil;

extern "C"
{
    /////
    //전면광고 초기화
    void AdMob_Init_Interstitia(char *szCodeID, bool bSim)
    {
        [AdMob AdMobgetInstance];
        
        NSString* strCodeId = [NSString stringWithUTF8String:szCodeID];
        [shared initInterstital:strCodeId:bSim];
        
    }
    void AdMob_Init_Banner(char *szCodeID, bool bSim)
    {
        [AdMob AdMobgetInstance];
        NSString* strCodeId = [NSString stringWithUTF8String:szCodeID];
        [shared initBanner:strCodeId:bSim];
    }
    
    /////
    void AdMob_ReLoad_Interstitia(char *szCodeID)// 초기화
    {
        NSString* strCodeId = [NSString stringWithUTF8String:szCodeID];
        [shared ReRloadInterstital:strCodeId];
        
    }
    //전체 광고 보기
    void AdMob_showInterstitial()
    {
        [shared showImterstitial];
        
    }
    
    
    // 배너광고
    
    void AdMob_BannerShow()
    {
        [shared showBanner];
    }
    void AdMob_BannerHide()
    {
        [shared hideBanner];
    }
    
}

void AdMobPlugin::AdMobFullScreen_Init(char *szCodeID , bool bSim)//전면광고를 초기화한다. .. 광고ID , 출시용은 bSim=false로 설정하자
{
    AdMob_Init_Interstitia(szCodeID, bSim);
}
void AdMobPlugin::AdMobBanner_Init(char *szCodeID , bool bSim)//배너광고
{
    AdMob_Init_Banner(szCodeID,bSim);
}

void AdMobPlugin::AdMobFullScreen_ReLoad(char *szCodeID)
{
    AdMob_ReLoad_Interstitia(szCodeID);
}

void AdMobPlugin::AdMobFullScreen_Show()
{
    AdMob_showInterstitial();
}
void AdMobPlugin::AdMobBanner_Show()
{
    AdMob_BannerShow();
}
void AdMobPlugin::AdMobBanner_Hide()
{
    AdMob_BannerHide();
}


/////////////////////////////////////////////////////////////////////////////




#pragma mark -
#pragma mark AdMob lifecycle

+ (AdMob*) AdMobgetInstance
{
    
    if (shared ==nil)
    {
        shared=[[AdMob alloc]init];
    }
    return shared;
}

- (void) interstitial:(GADInterstitial *)admob_Iner didFailToReceiveAdWithError:(GADRequestError *)error
{
    //광로 로드가 실패했을때 호출
}
- (void) interstitialDidReceiveAd:(GADInterstitial *)admob_Iner
{
    //광고를 받았을때 호출
    AdMobCtrl::getInstance()->onAdMobFullScreen_PreLoaded();
    
}
-(void) interstitialDidDismissScreen:(GADInterstitial *)admob_Iner
{
    //X 버튼 눌러서 광고를 닫았을때 호출
    AdMobCtrl::getInstance()->onAdMobFullScreen_Close();
}

//--아래 함수가 호출되면 광고가 뜬다함
-(void) showImterstitial
{
    if (self.admob_Iner.isReady)
    {
        //CCLOG("Ready");
       
        RootViewController *pView=[[AppController getInstance]viewController ];
        [self.admob_Iner presentFromRootViewController:(UIViewController*)pView];
        
    }
    else
    {
        //CCLOG("Not Ready");
        [self proloadRequest];
    }
}

#pragma mark GADRequest generation

//초기화 함수
-(void)initInterstital:(NSString*)strCodeId :(BOOL)bSim;
{
    NSLog(@"Google Mobile Ads SDK version: %@", [GADRequest sdkVersion]);
    
    m_bInterstital_Sim=bSim;
    
    self.admob_Iner=[self createAndLoadInterstitial:strCodeId];
}

- (GADInterstitial *)createAndLoadInterstitial:(NSString*)strCodeId
{
    GADInterstitial *interstitial = [[[GADInterstitial alloc] initWithAdUnitID:strCodeId]autorelease];
    interstitial.delegate = self;
    
    [interstitial loadRequest:[self createRequest]];
    return interstitial;
}

-(void)ReRloadInterstital:(NSString*)strCodeId
{
    self.admob_Iner = [self createAndLoadInterstitial:strCodeId];
}


//미리 광고를 불러오는 함수
-(void)proloadRequest
{
    //CCLOG("pre load");
    
    [self admob_Iner];
    [self.admob_Iner loadRequest:[self createRequest]];
    
}

-(GADRequest *)createRequest
{
    GADRequest *request=[GADRequest request];
    if (m_bInterstital_Sim)
    {
        request.testDevices=@[kGADSimulatorID,@"여기에 자신의 디바이스ID를 입력"];
    }
    
    
    return request;
}


/////

-(void)initBanner:(NSString*)strCodeId :(BOOL)bSim;
{
    //    320x50	Standard Banner	Phones and Tablets	kGADAdSizeBanner
    //    320x100	Large Banner	Phones and Tablets	kGADAdSizeLargeBanner
    //    300x250	IAB Medium Rectangle	Phones and Tablets	kGADAdSizeMediumRectangle
    //    468x60	IAB Full-Size Banner	Tablets	kGADAdSizeFullBanner
    //    728x90	IAB Leaderboard	Tablets	kGADAdSizeLeaderboard
    //    Screen width x 32|50|90	Smart Banner	Phones and Tablets	kGADAdSizeSmartBannerPortrait
    //    kGADAdSizeSmartBannerLandscape
    
    
    //@"ca-app-pub-8495701001450403/9232108574"
    
    NSLog(@"Google Mobile Ads SDK version: %@", [GADRequest sdkVersion]);
    m_bBanner_Sim=bSim;
    
    
    RootViewController *pView=[[AppController getInstance]viewController] ;
    
    UIViewController*pV=(UIViewController*)pView;
    
    CGPoint origin=CGPointMake((pV.view.frame.size.width- 320)/2 ,pV.view.frame.size.height- 50) ;
    m_pAdMobBanner=[[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner origin:origin ];
    m_pAdMobBanner.delegate=self;
    m_pAdMobBanner.adUnitID=strCodeId;
    m_pAdMobBanner.rootViewController=pV;
    
    // m_pAdMobBanner.si
    
    
    [pV.view addSubview:m_pAdMobBanner];
    m_pAdMobBanner.autoloadEnabled=true;
    m_pAdMobBanner.hidden =YES;
    
    GADRequest *adRequest=[GADRequest request];
    
    if (m_bBanner_Sim)
    {
        adRequest.testDevices=@[kGADSimulatorID,@"여기에 자신의 디바이스ID를 입력"];
    }
    
    
    [m_pAdMobBanner loadRequest:adRequest];
    
    
}

-(void)showBanner
{
    m_pAdMobBanner.hidden =NO;
}
-(void)hideBanner
{
    m_pAdMobBanner.hidden =YES;
}


- (void)adViewDidReceiveAd:(GADBannerView *)bannerView
{
    //CCLOG("배너 로드됌");
    AdMobCtrl::getInstance()->onAdMobBanner_Loaded();
}
- (void)adView:(GADBannerView *)bannerView
didFailToReceiveAdWithError:(GADRequestError *)error
{
    CCLOG("배너 로드 실패");
    
}

- (void)adViewWillPresentScreen:(GADBannerView *)bannerView
{
    
    CCLOG("배너 화면1");
    
}
- (void)adViewDidDismissScreen:(GADBannerView *)bannerView
{
    CCLOG("배너 화면2");
}
- (void)adViewWillDismissScreen:(GADBannerView *)bannerView
{
    CCLOG("배너 화면3");
}
- (void)adViewWillLeaveApplication:(GADBannerView *)bannerView
{
    CCLOG("배너 화면4");
}


@end