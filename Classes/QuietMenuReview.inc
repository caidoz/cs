// Native visual review of transparent rarity cards and every live chest pose.
static bool QuietMenuReview(const char* path){
 if(!getenv("CS_QUIET_CARD_REVIEW"))return false;
 cocos2d::Director::getInstance()->setDisplayStats(false);
 static int tick=0;static bool pending=false;if(pending)return true;++tick;
 if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
 if(tick<20)return true;
 const int page=Min(5,(tick-20)/20),top=DY-78;
 MemRect(0,top,DX,top,0x07111B);ResetRectPoint();
 SetFontColor(0xC8C4B7);CenterTextStrSolid(page==0?"TRANSPARENT CARDS / 6 RARITIES":page==5?"DIAMONDS / PREMIUM CURRENCY":"CHESTS / CLOSED + OPEN",DX/2,top-16,.7f);
 if(page==0){
  const int w=(DX-64)/3,h=Min(250,(top-80)/2),pitch=w+8;
  for(int rank=1;rank<=6;++rank){
   const int x=24+(rank-1)%3*pitch,y=top-64-(rank-1)/3*(h+14);
   DrawQuietCardFrame(x,y,w,h,rank,rank==5);
   const int icon=GetItemIcon(ITEM_SWORD,rank-1,GRADE_NORMAL),size=Min(w-40,h-60);
   DrawIcon(icon,x+(w-size)/2,y-(h-size)/2,size/(float)ITEMICONSIZE,0,false,false,true);
   char name[32];snprintf(name,sizeof(name),"RANK %d",rank);SetFontColor(0xC8C4B7);CenterTextStrSolid(name,x+w/2,y-h+26,.55f);
  }
 }else if(page==5){
  const int cw=DX/3,rh=Min(280,(top-64)/2);
  for(int tier=0;tier<6;++tier){
   const int img=SHOP_GEM_BUNDLE_FIRST_IMG+tier;if(!sprite[img])LoadImg(img);if(!sprite[img])continue;
   const auto size=sprite[img]->getTexture()->getContentSizeInPixels();const float z=Min((cw-24)/size.width,(rh-44)/size.height);
   const int x=(tier%3)*cw+(int)((cw-size.width*z)/2),y=top-64-(tier/3)*rh;
   DrawImage((int)size.width,(int)size.height,0,0,x,y,false,0,0,0,0,z,sprite[img],img);
  }
 }else{
  const int cw=DX/3,rh=Min(220,(top-64)/3);
  for(int slot=0;slot<9;++slot){
   const int index=(page-1)*9+slot;if(index>=33)break;
   const int img=BOX0_IMG+index;if(!sprite[img])LoadImg(img);if(!sprite[img])continue;
   const int x=slot%3*cw,y=top-60-slot/3*rh;
   const float z=Min((cw-16)/1024.f,(rh-30)/512.f);
   DrawImage(1024,512,0,0,x+(cw-(int)(1024*z))/2,y,false,0,0,0,0,z,sprite[img],img);
   char name[32];snprintf(name,sizeof(name),"BOX %02d",index);SetFontColor(0xC8C4B7);CenterTextStrSolid(name,x+cw/2,y-(int)(512*z)-12,.5f);
  }
 }
 if((tick-20)%20==10){
  char file[48];snprintf(file,sizeof(file),"quiet-assets-%d.png",page);pending=true;
  cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS quiet native capture":"FAIL quiet native capture");},std::string(path)+file);
 }
 if(tick==138)CastleReviewTrace("DONE quiet cards and 33 chest poses review");
 return true;
}
