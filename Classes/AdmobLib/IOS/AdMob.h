//
//  AdMob.h
//  CurshPop
//
//  Created by Mr.Ru on 2015. 11. 25..
//
//

#ifndef AdMob_h
#define AdMob_h

#import <UIKit/UIKit.h>
#import <GoogleMobileAds/GADInterstitial.h>
#import <GoogleMobileAds/GADBannerView.h>


@interface AdMob : NSObject < GADInterstitialDelegate , GADBannerViewDelegate>
{
    
    GADBannerView *m_pAdMobBanner;
    BOOL m_bInterstital_Sim;
    BOOL m_bBanner_Sim;
}
@property(nonatomic,retain) GADInterstitial *admob_Iner;

+(AdMob*) AdMobgetInstance;


-(void)showImterstitial;
-(void)initInterstital:(NSString*)strCodeId :(BOOL)bSim;
-(void)proloadRequest;
-(GADRequest *)createRequest;
-(void)ReRloadInterstital:(NSString*)strCodeId;

- (GADInterstitial *)createAndLoadInterstitial:(NSString*)strCodeId;
-(void)initBanner:(NSString*)strCodeId :(BOOL)bSim;

-(void)showBanner;
-(void)hideBanner;


@end

#endif /* AdMob_h */
