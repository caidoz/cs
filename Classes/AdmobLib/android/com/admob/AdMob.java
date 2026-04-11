
package com.admob;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.AdListener;

import android.content.Context;
import android.widget.LinearLayout;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;


public class AdMob 
{
	
	private static AdMob uniqueInstance ;
	
	
	protected static  AdView adView;
	protected static  InterstitialAd interstitial;
	
	protected static Context mActivity;
	
	protected static boolean isAdmobInited = false;
	protected static boolean isSimTest=false;	//�׽�Ʈ�����ΰ�.
  
	private static final String LOG_TAG = "AdMob_";
	
	
	///-- JNI���� �Լ�
	public static native void nativeOnAdMobFullScreenPreLoaded();  //��ü ���� �ε�ƴ�.
	public static native void nativeOnAdMobFullScreenClose();//������ ���� �ݾ����� �̺�Ʈ
	public static native void nativeOnAdMobBannerLoaded(); //��ʱ��� �ε�ƴ�.
	
  /* Your ad unit id. Replace with your actual ad unit id. */
	private AdMob(){ }
	public static AdMob getInstance()
	{ 
		if(uniqueInstance  ==null)
		{ 
			uniqueInstance  = new AdMob ();
			AdMob.initAdmob(Cocos2dxActivity.getContext());	
		}
		return uniqueInstance ;
	}
 
  public void destroy()
  {		
	  
  }
  

  public static void initAdmob(Context pConst)
  {
	  AdMob.mActivity=pConst;
  }
  
  public static void initInterstital(String szCodeID , boolean bSim)//���鱤�� �ʱ�ȭ�Ѵ�. .. ����ID , ��ÿ��� bSim=false�� ��������
  {
	  AdMob.getInstance();
	  
	  AdMob.isSimTest=bSim;
	  AdMob.ReRloadInterstital(szCodeID);	  
  }
  
  public static void ReRloadInterstital(String szCodeID)
  {
 	 AdMob.CreateInterstital(szCodeID);
  }
  
  private static void CreateInterstital(String szCodeID)
  {
	
	  AdMob.interstitial = new InterstitialAd(AdMob.mActivity);
	  AdMob.interstitial.setAdUnitId(szCodeID);  
		// Set the AdListener.
	  Log.d(LOG_TAG, "초기화는 성");
	  AdMob.interstitial.setAdListener(new AdListener()
			  {
			      @Override
			      public void onAdLoaded()
			      {
			        Log.d(LOG_TAG, "onAdLoaded");
			        nativeOnAdMobFullScreenPreLoaded();  //��ü ���� �ε�ƴ�
			      }

			      @Override
			      public void onAdFailedToLoad(int errorCode)
			      {
			        String message = String.format("onAdFailedToLoad (%s)", AdMob.getErrorReason(errorCode));
			        Log.d(LOG_TAG, message);
			      }
			      
			      @Override
			      public void onAdClosed()
			      {
			    	  String message = String.format("onAdClose");
				      Log.d(LOG_TAG, message);
				     
				      nativeOnAdMobFullScreenClose();//������ ���� �ݾ����� �̺�Ʈ
			      }
			    });	
	  Log.d(LOG_TAG, "초기화는 성공 ");
	  
	  AdMob.proloadRequest();
		
  }
  
  private static  void proloadRequest()
  {     
	  Cocos2dxActivity pCont=(Cocos2dxActivity) AdMob.mActivity;
	  
	  pCont.runOnUiThread(new Runnable() 
	  {
		  @Override
		  public void run() 
		  {
			  if(AdMob.isSimTest)
			  {
				  AdRequest adRequest = new AdRequest.Builder()
				  .addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
				  .addTestDevice("여기에 자신의 디바이스ID를 입력")	//내 테스트 안드
				  .build();
				  AdMob.interstitial.loadAd(adRequest);
				  Log.d(LOG_TAG, "로드 성공 ");
			  }
			  else
			  {
				  AdRequest adRequest = new AdRequest.Builder().build();
				  AdMob.interstitial.loadAd(adRequest);
			  }
		  }
	  });
  }
  public static void showImterstitial()
  {
	  Cocos2dxActivity pCont=(Cocos2dxActivity) AdMob.mActivity;
	  
	  pCont.runOnUiThread(new Runnable() 
	  {
		    @Override
		    public void run() 
		    {
		    	if (AdMob.interstitial.isLoaded()) 
		  	  	{
		    		AdMob.interstitial.show();
		    		 Log.d(LOG_TAG, "광고 보여주고있다. ");
		  	    } 
		    	else 
		  	    {
		  	      Log.d(LOG_TAG, "Interstitial ad was not ready to be shown.");
		  	      AdMob.proloadRequest();
		  	    }
		    }
	  });
  }
  
  
  
  /////////////////////////////////////////////////////////////////
  
  private static void createBanner(String szCodeID , boolean bSim)//��ʱ���
  {
	  AdMob.adView = new AdView(AdMob.mActivity);
	  
	  AdMob.isSimTest=bSim;
	  AdMob.adView.setAdSize(AdSize.BANNER);
	  AdMob.adView.setAdUnitId(szCodeID);
	  
	  LinearLayout layout;
	  LinearLayout mainLayout;
	 
	  
	  mainLayout = new LinearLayout (AdMob.mActivity);
	  WindowManager wm = (WindowManager) AdMob.mActivity.getSystemService ("window");
		
		WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams ();
		mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
		mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
		mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
		mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
		mLayoutParams.gravity = Gravity.BOTTOM;
		
		wm.addView (AdMob.adView, mLayoutParams);
	  
	  
	  // Set the AdListener.
		AdMob.adView.setAdListener(new AdListener() 
	  {
	      /** Called when an ad is clicked and about to return to the application. */
	      @Override
	      public void onAdClosed() 
	      {
	        Log.d(LOG_TAG, "onAdClosed");
	      }

	      
	      /** Called when an ad failed to load. */
	      @Override
	      public void onAdFailedToLoad(int error)
	      {
	        String message = "onAdFailedToLoad: " + AdMob.getErrorReason(error);
	        Log.d(LOG_TAG, message);
	      }

	      /**
	       * Called when an ad is clicked and going to start a new Activity that will
	       * leave the application (e.g. breaking out to the Browser or Maps
	       * application).
	       */
	      @Override
	      public void onAdLeftApplication()
	      {
	        Log.d(LOG_TAG, "onAdLeftApplication");
	      }

	      /**
	       * Called when an Activity is created in front of the app (e.g. an
	       * interstitial is shown, or an ad is clicked and launches a new Activity).
	       */
	      @Override
	      public void onAdOpened()
	      {
	        Log.d(LOG_TAG, "onAdOpened");
	      }

	      /** Called when an ad is loaded. */
	      @Override
	      public void onAdLoaded() 
	      {
	        Log.d(LOG_TAG, "onAdLoaded");
	    	nativeOnAdMobBannerLoaded(); //��ʱ��� �ε�ƴ�.
	    	
	      }
	    });    
	    
	  if(AdMob.isSimTest)
	  {
		  AdRequest adRequest = new AdRequest.Builder()
	      .addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
	      .addTestDevice("여기에 자신의 디바이스ID를 입력")	//내 테스트 안드
	      .build();
		  AdMob.adView.loadAd(adRequest);
	  }
	  else
	  {
		  AdRequest adRequest = new AdRequest.Builder()
	      .build();
		  AdMob.adView.loadAd(adRequest);
	  }	  
  }
  
  public static void initBanner(final String szCodeID , final boolean bSim)//��ʱ���
  {
	  AdMob.getInstance();
	  Cocos2dxActivity pCont=(Cocos2dxActivity) AdMob.mActivity;
	  
	  pCont.runOnUiThread(new Runnable() 
	  {
		    @Override
		    public void run() 
		    {
		    	AdMob.createBanner(szCodeID,bSim);
		    }
	  });
  }
  

  public static void AdMobBannerShow()
  {
	  Cocos2dxActivity pCont=(Cocos2dxActivity) AdMob.mActivity;
	  
	  pCont.runOnUiThread(new Runnable() 
	  {
		    @Override
		    public void run() 
		    {
				  if(AdMob.adView.isEnabled())
				  {
					  AdMob.adView.setEnabled(true);
				  }
				  if(AdMob.adView.getVisibility() ==4)
				  {
					  AdMob.adView.setVisibility(View.VISIBLE);
				  }
		    }
	  });
	  
  }
  public static void AdMobBannerHide()
  {
	  Cocos2dxActivity pCont=(Cocos2dxActivity) AdMob.mActivity;
	  pCont.runOnUiThread(new Runnable() 
	  {
		    @Override
		    public void run() 
		    {
		    	
		    	Log.d(LOG_TAG, "배너창 닫았");
		    	AdMob.adView.setEnabled(false);
				
				if(AdMob.adView.getVisibility() !=4)
				{
				  AdMob.adView.setVisibility(View.INVISIBLE);
				}
		    }
	  });
  }


  
  /** Gets a string error reason from an error code. */
  public static String getErrorReason(int errorCode) 
  {
    String errorReason = "";
    switch(errorCode) {
      case AdRequest.ERROR_CODE_INTERNAL_ERROR:
        errorReason = "Internal error";
        break;
      case AdRequest.ERROR_CODE_INVALID_REQUEST:
        errorReason = "Invalid request";
        break;
      case AdRequest.ERROR_CODE_NETWORK_ERROR:
        errorReason = "Network Error";
        break;
      case AdRequest.ERROR_CODE_NO_FILL:
        errorReason = "No fill";
        break;
    }
    return errorReason;
  }


}
