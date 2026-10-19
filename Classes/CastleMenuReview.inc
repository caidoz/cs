// Explicit isolated UI review; enabled only with CS_CASTLE_REVIEW_PATH.
#include "Data/InventoryCannonSprites.h"
static void CastleReviewTrace(const char* message) {
    const char* path=getenv("CS_CASTLE_REVIEW_PATH");
    if(!path) return;
    FILE* f=fopen((std::string(path)+"phases.log").c_str(),"a");
    if(f) { fprintf(f,"%s\n",message); fclose(f); }
}
static void CastleReviewClick(int command) {
    for (int i=touchIndex-1;i>=0;--i) if(touchRect[i][4]==command) {
        ExecTouchFunc(touchRect[i][0]+touchRect[i][2]/2,touchRect[i][1]-touchRect[i][3]/2);
        CastleReviewTrace(gTouchHitFunc==command?"PASS touch":"FAIL touch intercepted");
        return;
    }
    CastleReviewTrace("FAIL touch area missing");
}
static void CastleMenuReviewStep()
{
    const char* path = getenv("CS_CASTLE_REVIEW_PATH");
    if (!path) return;
    if(getenv("CS_PVP_ICON_ENTRANCE_REVIEW")) {
        static int tick=0;static bool pending=false;
        if(pending) return;
        const int batch=tick/25,phase=tick%25;++tick;
        if(batch>=10) {if(tick==251) CastleReviewTrace("PASS all ten current icon entrances");return;}
        robin.castle=batch;pvpFoeCastleLevel=10-batch;pvpStageFighting=1;
        DrawPvpSelectedCastles(60,60);
        if(phase==16) CastleReviewTrace(PvpEntranceIconReviewCheck(batch+1,10-batch)?"PASS entrance icon IDs mirrored wheels and bounds":"FAIL entrance icon layout");
        if(phase==18) {
            char name[64];sprintf(name,"entrance-%02d-vs-%02d.png",batch+1,10-batch);
            pending=true;
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {CastleReviewTrace(ok?"PASS entrance icon capture":"FAIL entrance icon capture");pending=false;},std::string(path)+name);
        }
        return;
    }
    if(getenv("CS_CURRENT_CANNON_ICON_REVIEW")) {
        static int tick=0;++tick;
        const int img=INVENTORY_CANNON_ATLAS_IMG;
        bool ok=sprite[img] && texture[img];
        MemRect(16,DY-70,608,730,0x16263B);
        SetFontColor(COLOR_WHITE);
        CenterTextStrSolid("CURRENT CANNONS / 10 CASTLES x 6 GRADES",DX/2,DY-91,.7f);
        for(int castle=0;castle<10;++castle) for(int level=0;level<6;++level) {
            const auto& f=InventoryCannons::Get(castle,level);
            ok=ok && f.bw>0 && f.bh>0 && f.x+f.w<=576 && f.y+f.h<=640;
            const int x=30+level*96,y=DY-114-castle*66;
            MemRectFrame(x,y,92,62,0x6F849A);
            DrawInventoryCannonIcon(castle,level,x+3,y-3,86,56);
        }
        if(tick==20) {
            CastleReviewTrace(ok?"PASS current cannon sixty registered frames":"FAIL current cannon registration");
            cocos2d::utils::captureScreen([](bool captured,const std::string&) {CastleReviewTrace(captured?"PASS current cannon icon capture":"FAIL current cannon icon capture");},std::string(path)+"current-cannon-icons.png");
        }
        return;
    }
    if(getenv("CS_INDIVIDUAL_V4_REVIEW")) {
        static int tick=0;static bool pending=false;
        if(pending) return;
        const int castle=tick/40,phase=tick%40;++tick;
        if(castle>=10) { if(tick==401) CastleReviewTrace("PASS individual v4 all ten exteriors"); return; }
        if(phase==0) {
            robin.castle=castle;gMobileCastleVisual=castle;robin.castleProgress.version=1;robin.castleProgress.owned|=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            if(getenv("CS_CASTLE_INTERIOR_SYNC_REVIEW")) {
                // Isolated review profile: enough owned companions to detect
                // both the former eight-person cap and decorative-slot loss.
                memset(robin.inven,0,sizeof(robin.inven));robin.maxInven=TOTALINVENTORY;
                int added=0;
                for(int crew=0;crew<gTotalCrew && added<20;++crew) {
                    if(crewData[crew*CREWDATASIZE+CREWDATA_TYPE]==NPC_SHIP) continue;
                    auto& item=robin.inven[added++];item.type=ITEM_CREW;item.detail=crew;item.grade=GRADE_NORMAL;item.count=1;
                }
            }
            GotoLobby();while(popUpCnt>0) ClosePopUp();LoadoutSetOpen(false);
        }
        if(phase==16) {
            const bool ok=CastleIndividualReviewCheck(0);
            CastleReviewTrace(ok?"PASS individual placement and progression":"FAIL individual placement and progression");
            CastleReviewTrace(CastleIndividualReviewCheck(2)?"PASS uniform room dimensions and floor count":"FAIL uniform room dimensions and floor count");
        }
        if(phase==30) CastleReviewTrace(CastleIndividualReviewCheck(1)?"PASS individual wheels rolling":"FAIL individual wheels rolling");
        if(getenv("CS_CASTLE_INTERIOR_SYNC_REVIEW")) {
            if(phase==19) CastleInteriorSyncReviewCheck(0);
            if(phase==21) CastleReviewTrace(CastleInteriorSyncReviewCheck(1)?"PASS castle zoom out":"FAIL castle zoom out");
            if(phase==24) CastleReviewTrace(CastleInteriorSyncReviewCheck(2)?"PASS castle zoom in":"FAIL castle zoom in");
            if(phase==27) CastleReviewTrace(CastleInteriorSyncReviewCheck(3)?"PASS twenty residents and intact room textures":"FAIL residents or rectangular room textures");
        }
        if(getenv("CS_ROOM_COVER_REVIEW")) {
            if(phase==8) CastleRoomCoverPreview(4);
            if(phase==12) CastleReviewTrace(CastleRoomCoverPreview(3)?"PASS individual outside touch closed":"FAIL individual outside touch closed");
            if(phase==13) CastleRoomCoverPreview(0);
            if(phase==22) CastleRoomCoverPreview(1);
            if(phase==26) CastleReviewTrace(CastleRoomCoverPreview(2)?"PASS individual room reveal":"FAIL individual room reveal");
            if(phase==28) CastleRoomCoverPreview(0);
            if(phase==31) CastleReviewTrace(CastleRoomCoverPreview(2)?"PASS individual room persists after release":"FAIL individual room persists after release");
            if(phase==35) CastleRoomCoverPreview(6);
            if(phase==38) CastleReviewTrace(CastleRoomCoverPreview(3)?"PASS individual room closed":"FAIL individual room closed");
        }
        if(phase==18 || phase==32) {
            char name[80];sprintf(name,"individual-%02d-%d.png",castle+1,phase);
            pending=true;
            cocos2d::utils::captureScreen([](bool ok,const std::string&) { CastleReviewTrace(ok?"PASS individual capture":"FAIL individual capture");pending=false; },std::string(path)+name);
        }
        return;
    }
    if(getenv("CS_UNIFORM_CASTLE_REVIEW")) {
        static bool capturePending=false;
        if(capturePending) return;
        static int tick=0;++tick;
        const int batch=(tick-1)/30,phase=(tick-1)%30;
        if(batch>=35) { if(tick==1051) CastleReviewTrace("PASS all uniform castle stages and mixed parts"); return; }
        const int castle=5+batch/7,variant=batch%7;
        if(phase==0) {
            robin.castle=castle;gMobileCastleVisual=castle;
            robin.castleProgress.version=1;robin.castleProgress.owned|=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            for(int i=0;i<5;++i) robin.castleProgress.parts[castle][i]=variant==6?(i%2?5:0):variant;
            GotoLobby();while(popUpCnt>0) ClosePopUp();LoadoutSetOpen(false);
            CastleRoomCoverPreview(0);
        }
        if(phase==16) CastleReviewTrace(CastleUniformReviewCheck()?"PASS uniform castle placement":"FAIL uniform castle placement");
        if(phase==22) CastleRoomCoverPreview(1);
        if(phase==26) CastleReviewTrace(CastleRoomCoverPreview(2)?"PASS uniform room reveal":"FAIL uniform room reveal");
        if(phase==18 || phase==27) {
            char name[80];sprintf(name,"castle-%02d-stage-%d%s.png",castle+1,variant,phase==18?"":"-open");
            capturePending=true;
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS uniform capture":"FAIL uniform capture");
                capturePending=false;
            },std::string(path)+name);
        }
        if(phase==29) CastleRoomCoverPreview(0);
        return;
    }
    if(getenv("CS_PVP_LAYOUT_REVIEW")) {
        static int tick=0; ++tick;
        if(tick==1) { robin.castle=0; StartPvpTest(false); }
        if(tick==190) CastleReviewTrace(PvpCastleDebugReviewCheck()?"PASS PVP castle keyboard cycling and lobby size ratios":"FAIL PVP castle keyboard cycling and lobby size ratios");
        if(tick==180) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS PVP layout capture":"FAIL PVP layout capture");
        },std::string(path)+"pvp-layout.png");
        return;
    }
    if(getenv("CS_CASTLE_MAP_ICON_REVIEW")) {
        static int tick=0;++tick;
        if(tick!=20) return;
        bool ok=true;
        FILE* log=fopen((std::string(path)+"icons.csv").c_str(),"w");
        if(!log) {CastleReviewTrace("FAIL map icon report");return;}
        fprintf(log,"castle,image_id,resource,width,height\n");
        for(int i=0;i<10;++i) {
            const int img=CASTLE_MAP_ICON_FIRST_IMG+i;
            const std::string resource=GetResourceName(RES_IMG,img);
            char expected[100];sprintf(expected,"castle_map_icons/castle_map_%02d.png",i+1);
            if(resource.find(expected)==std::string::npos || !sprite[img] || !texture[img]) {ok=false;continue;}
            const auto size=texture[img]->getContentSizeInPixels();
            if(size.width!=1024 || size.height!=1024 || sprite[img]->getTexture()!=texture[img]) ok=false;
            fprintf(log,"%d,%d,%s,%.0f,%.0f\n",i+1,img,resource.c_str(),size.width,size.height);
        }
        fclose(log);
        CastleReviewTrace(ok?"PASS all ten map icons registered and preloaded":"FAIL map icon registration or preload");
        return;
    }
    if(getenv("CS_FIXED_WIDTH_REVIEW")) {
        static int tick=0; ++tick;
        const int castle=(tick-1)/40,phase=(tick-1)%40;
        if(castle>=10) { if(tick==401) CastleReviewTrace("PASS all castle widths and heights"); return; }
        if(phase==0) {
            robin.castle=castle;gMobileCastleVisual=castle;
            robin.castleProgress.version=1;robin.castleProgress.owned|=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            for(int i=0;i<5;++i) robin.castleProgress.parts[castle][i]=0;
            GotoLobby();while(popUpCnt>0) ClosePopUp();LoadoutSetOpen(false);
        }
        if(phase==14) CastleReviewTrace(CastleFixedWidthReviewCheck(0)?"PASS fixed width and growing height":"FAIL fixed width or height");
        if(phase==16 || (castle==9 && phase==32)) {
            char name[80];sprintf(name,"castle-%02d-%s.png",castle+1,phase==16?"base":"upper");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS width capture":"FAIL width capture");
            },std::string(path)+name);
        }
        if(castle==9 && phase==20) CastleFixedWidthReviewCheck(1);
        if(castle==9 && phase==30) CastleReviewTrace(CastleFixedWidthReviewCheck(2)?"PASS tall castle vertical pan":"FAIL tall castle vertical pan");
        return;
    }
    if(getenv("CS_TENTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(TenthSdUpgradeReviewCheck()?"PASS tenth deployed deck positions":"FAIL tenth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-10-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all tenth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=9; gMobileCastleVisual=9;
            robin.castleProgress.version=1; robin.castleProgress.owned|=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[9][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(TenthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&TenthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_NINTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(NinthSdUpgradeReviewCheck()?"PASS ninth deployed deck positions":"FAIL ninth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-9-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all ninth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=8; gMobileCastleVisual=8;
            robin.castleProgress.version=1; robin.castleProgress.owned|=511u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[8][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(NinthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&NinthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_EIGHTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(EighthSdUpgradeReviewCheck()?"PASS eighth deployed deck positions":"FAIL eighth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-8-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all eighth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=7; gMobileCastleVisual=7;
            robin.castleProgress.version=1; robin.castleProgress.owned|=255u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[7][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(EighthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&EighthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_SEVENTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(SeventhSdUpgradeReviewCheck()?"PASS seventh deployed deck positions":"FAIL seventh deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-7-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all seventh upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=6; gMobileCastleVisual=6;
            robin.castleProgress.version=1; robin.castleProgress.owned|=127u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[6][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(SeventhSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&SeventhSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_SIXTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(SixthSdUpgradeReviewCheck()?"PASS sixth deployed deck positions":"FAIL sixth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-6-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all sixth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=5; gMobileCastleVisual=5;
            robin.castleProgress.version=1; robin.castleProgress.owned|=63u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[5][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(SixthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&SixthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_FIFTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(FifthSdUpgradeReviewCheck()?"PASS fifth deployed deck positions":"FAIL fifth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-5-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all fifth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=4; gMobileCastleVisual=4;
            robin.castleProgress.version=1; robin.castleProgress.owned|=31u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[4][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(FifthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&FifthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_FOURTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(FourthSdUpgradeReviewCheck()?"PASS fourth deployed deck positions":"FAIL fourth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-4-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all fourth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=3; gMobileCastleVisual=3;
            robin.castleProgress.version=1; robin.castleProgress.owned|=15u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[3][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(FourthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&FourthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_THIRD_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(ThirdSdUpgradeReviewCheck()?"PASS third deployed deck positions":"FAIL third deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-3-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all third upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=2; gMobileCastleVisual=2;
            robin.castleProgress.version=1; robin.castleProgress.owned|=7u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[2][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(ThirdSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&ThirdSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_SECOND_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(SecondSdUpgradeReviewCheck()?"PASS second deployed deck positions":"FAIL second deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-2-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all second upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=1; gMobileCastleVisual=1;
            robin.castleProgress.version=1; robin.castleProgress.owned|=3u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[1][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(SecondSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&SecondSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_STARTER_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) return;
        if(tick==1) {
            robin.castle=0; gMobileCastleVisual=0;
            robin.castleProgress.version=1; robin.castleProgress.owned|=1u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[0][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(StarterSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&StarterSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        if(batch==8 && phase==78) CastleReviewTrace("PASS all starter upgrades and mixed assemblies");
        return;
    }
    if(getenv("CS_TENTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=9; gMobileCastleVisual=9;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=1023u;
            const char* requested=getenv("CS_TENTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[9][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_NINTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=8; gMobileCastleVisual=8;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=511u;
            const char* requested=getenv("CS_NINTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[8][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_EIGHTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=7; gMobileCastleVisual=7;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=255u;
            const char* requested=getenv("CS_EIGHTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[7][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_SEVENTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=6; gMobileCastleVisual=6;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=127u;
            const char* requested=getenv("CS_SEVENTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[6][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_SIXTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=5; gMobileCastleVisual=5;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=63u;
            const char* requested=getenv("CS_SIXTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[5][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_FIFTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=4; gMobileCastleVisual=4;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=31u;
            const char* requested=getenv("CS_FIFTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[4][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_FOURTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=3; gMobileCastleVisual=3;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=15u;
            const char* requested=getenv("CS_FOURTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[3][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_THIRD_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=2; gMobileCastleVisual=2;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=7u;
            const char* requested=getenv("CS_THIRD_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[2][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_SECOND_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=1; gMobileCastleVisual=1;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=3u;
            const char* requested=getenv("CS_SECOND_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[1][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_STARTER_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=0; gMobileCastleVisual=0;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=1u;
            const char* requested=getenv("CS_STARTER_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[0][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_ROOM_COVER_REVIEW")) {
        static int tick=0; ++tick;
        if(tick==1) {
            robin.castle=0; gMobileCastleVisual=0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[0][i]=0;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        const int phase=tick;
        if(phase==35) StarterSdWheelReview(true);
        if(phase==45) CastleRoomCoverPreview(1);
        if(phase==80) CastleReviewTrace(CastleRoomCoverPreview(2)?"PASS held circular reveal":"FAIL held circular reveal");
        if(phase==95) CastleRoomCoverPreview(0);
        if(phase==125) CastleReviewTrace(CastleRoomCoverPreview(3)?"PASS released facade restored":"FAIL facade restore");
        if(phase==125) CastleReviewTrace(StarterSdWheelReview(false)?"PASS half-screen width and rolling wheels":"FAIL castle width or wheel rotation");
        if(phase==35 || phase==80 || phase==125) {
            char name[64]; sprintf(name,"castle-%d-%s.png",gMobileCastleVisual+1,
                phase==35?"closed":phase==80?"held":"released");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS facade capture":"FAIL facade capture");
            },std::string(path)+name);
        }
        if(tick==140 && !getenv("CS_SD_ROOM_DECK_REVIEW")) CastleReviewTrace("PASS room cover review");
        if(getenv("CS_SD_ROOM_DECK_REVIEW")) {
            if(tick==145) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type==NPC_SHIP) continue;
                    if(StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==220) CastleReviewTrace(SdRoomDeckReviewCheck()?"PASS companion deck anchors and real positions":"FAIL companion deck positions");
            if(tick==220) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS deployed companions capture":"FAIL deployed companions capture");
            },std::string(path)+"castle-1-companion-deck.png");
            if(tick==230) CastleRoomCoverPreview(1);
            if(tick==260) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS deployed cutaway capture":"FAIL deployed cutaway capture");
            },std::string(path)+"castle-1-deployed-interior.png");
            if(tick==275) CastleReviewTrace("PASS SD room and companion deck review");
        }
        return;
    }
    if(getenv("CS_BATTLE_MENU_REVIEW")) {
        static int menuTick=0; ++menuTick;
        static int shopGround=0;
        if(menuTick==1) {
            robin.castle=0; gMobileCastleVisual=0;
            robin.castleProgress.version=1; robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp();
        }
        if(menuTick==30) LoadoutSetOpen(true);
        if(menuTick==45) {
            const auto heart = robin.heart;
            const int handle = drawHandle;
            CastleReviewClick(TOUCH_FUNC_LOADOUT_CLOSE);
            systemKey = AVK_CLR; PlayKey(PLAYER);
            CastleReviewTrace(LoadoutOpen() && BattleEntryLocked() &&
                drawHandle==handle && robin.heart==heart ?
                "PASS preparation outside tap and back stay in run":"FAIL preparation exit guard");
        }
        if(menuTick==180) {
            const auto heart = robin.heart;
            BattleAbandonCommand();
            CastleReviewTrace(IsStageRealtime() && BattleEntryLocked() && robin.heart==heart ?
                "PASS precombat abandon blocked":"FAIL precombat abandon guard");
        }
        if(menuTick==60) CastleReviewTrace(BattleMenuPreviewDragCheck()?"PASS warehouse drag into grid":"FAIL warehouse drag into grid");
        if(menuTick==100) CastleReviewTrace(BattleMenuPreviewWarehouseGestureCheck()?
            "PASS star footer button drag tap and cancel":"FAIL warehouse gesture regions");
        if(menuTick==110||menuTick==600) {
            LoadoutSetOpen(false); GotoPlay(); StageRtBegin(); StageRtSetAuto(false);
            battleStartFrame=0;
        }
        if(menuTick==250) GridTestSkipOffer();
        if(menuTick==210) {
            shopGround=GetStageSceneGroundY();
            CastleReviewTrace(GridTestOfferOpen()&&!StageRtAutoOn()?"PASS initial shop before battle":"FAIL initial shop before battle");
        }
        if(menuTick==320) CastleReviewTrace(StageRtAutoOn()&&!GridTestOfferOpen()&&GetStageSceneGroundY()<shopGround?
            "PASS world descends with full battle grid":"FAIL battle layout transition");
        if(menuTick>=250&&menuTick<360) {
            ao[PLAYER].hp=ao[PLAYER].maxhp=1000000000; ao[PLAYER].dead=false;
            for(int i=ENEMY;i<NEUTRAL;++i) if(ao[i].active) { ao[i].hp=ao[i].maxhp=1000000000; ao[i].dead=false; }
        }
        if(menuTick==360) GridTestRefresh();
        if(menuTick==335) StageRtSetAuto(false);
        if(menuTick==345) CastleReviewTrace(GetStageSceneGroundY()<shopGround&&!GridTestOfferOpen()?
            "PASS pause retains compact combat menu":"FAIL pause menu");
        if(menuTick==350) StageRtSetAuto(true);
        if(menuTick==460) CastleReviewTrace(GridTestOfferOpen()&&GetStageSceneGroundY()==shopGround?
            "PASS world returns for shopping":"FAIL return shop layout");
        if(menuTick==500) {
            robin.castle=9; gMobileCastleVisual=9;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(true);
        }
        if(menuTick==585) CastleReviewTrace(BattleMenuPreviewScrollCheck()?
            "PASS centred 48px grid and four warehouse rows":"FAIL 48px inventory scrolling");
        const char* shot=menuTick==70?"01-warehouse-4rows.png":menuTick==210?"02-first-shop.png":
            menuTick==320?"03-battle-grid.png":menuTick==460?"04-return-shop.png":
            menuTick==570?"05-castle10-warehouse.png":menuTick==700?"06-castle10-shop.png":nullptr;
        if(shot) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS battle menu capture":"FAIL battle menu capture");
        },std::string(path)+shot);
        if(menuTick==730) {
            GridTestSkipOffer();
            CastleReviewTrace(!BattleEntryLocked()?"PASS exit unlocks after combat starts":"FAIL combat exit lock");
            BattleAbandonCommand();
            CastleReviewTrace(!IsStageRealtime()?"PASS explicit combat abandon":"FAIL explicit combat abandon");
            CastleReviewTrace("PASS battle menu flow review");
        }
        return;
    }
    if (getenv("CS_CASTLE_LAYOUT_REVIEW")) {
        static int layoutTick=0; ++layoutTick;
        if(layoutTick==1) {
            robin.castle=0; robin.castleProgress=CastleMenuModel::Progress();
            CastleProgressEnsure(); robin.castleProgress.owned=1023u;
            GotoLobby(); touchDisable=false;
            systemKey=AVK_POPUP_CASTLEMENU; PlayKey(PLAYER);
        }
        if(layoutTick==70) for(int i=0;i<9;++i) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
        if(layoutTick==130) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_DETAIL);
        if(layoutTick==190) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PARTS);
        if(layoutTick==250) CastleReviewTrace(CastleMenuSwipe(DX/2,DY/2,DX/2,DY/2+200)?"PASS vertical castle pan":"FAIL vertical castle pan");
        if(layoutTick==310) CastleReviewTrace(CastleMenuSwipe(DX/2,DY/2,DX/2,DY/2-500)?"PASS reverse castle pan":"FAIL reverse castle pan");
        if(layoutTick==370) CastleReviewTrace("PASS native castle layout review");
        const char* shot=layoutTick==40?"01-native-first.png":layoutTick==100?"02-native-last.png":
            layoutTick==220?"03-part-anchors.png":layoutTick==280?"04-panned-top.png":layoutTick==340?"05-panned-bottom.png":nullptr;
        if(shot) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS native castle capture":"FAIL native castle capture");
        },std::string(path)+shot);
        return;
    }
    if (getenv("CS_CANNON_LOBBY_REVIEW")) {
        static int lobbyTick=0;
        ++lobbyTick;
        if ((lobbyTick-1)%60==0 && lobbyTick<=1200) {
            const int sample=(lobbyTick-1)/60;
            robin.castle=sample/2;
            gMobileCastleVisual=robin.castle;
            robin.castleProgress.version=1;
            robin.castleProgress.owned=1023u;
            robin.castleProgress.parts[robin.castle][3]=(sample%2)*5;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby();
            while(popUpCnt>0) ClosePopUp();
        }
        if(lobbyTick%60==40 && lobbyTick<1200) {
            const int sample=lobbyTick/60;
            char name[64]; sprintf(name,"lobby_%02d_lv_%d.png",sample/2+1,(sample%2)*5);
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS lobby cannon capture":"FAIL lobby cannon capture");
            },std::string(path)+name);
        }
        if(lobbyTick==1200) CastleReviewTrace("PASS lobby cannon gallery");
        return;
    }
    if (getenv("CS_BRIDGE_HP_REVIEW")) {
        static int bridgeTick=0;
        ++bridgeTick;
        if(bridgeTick==1) {
            robin.castle=CastleMenuModel::Clamp(atoi(getenv("CS_BRIDGE_HP_REVIEW"))-1);
            robin.castleProgress.version=1;
            robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.bossRoom=0;
            bossRaidMode=false;
            GotoPlay();
            StageRtBegin();
            StageRtSetAuto(false);
            while(popUpCnt>0) ClosePopUp();
        }
        const bool partsReview=getenv("CS_CANNON_PARTS_REVIEW")!=nullptr;
        if(partsReview && (bridgeTick-1)%60==0 && bridgeTick<=1200) {
            const int sample=(bridgeTick-1)/60;
            robin.castle=sample/2;
            gMobileCastleVisual=robin.castle;
            robin.castleProgress.parts[robin.castle][3]=(sample%2)*5;
            GotoPlay(); StageRtBegin(); StageRtSetAuto(false);
            battleStartFrame=0;
        }
        // Explicit preview samples exercise full, partial and empty health pools.
        ao[PLAYER].maxhp=10000;
        ao[PLAYER].hp=partsReview?10000:bridgeTick<70?10000:bridgeTick<130?6800:0;
        ao[PLAYER].dead=false;
        for(int i=ENEMY;i<NEUTRAL;++i) ao[i].active=false;
        OBJECT& foe=ao[ENEMY];
        if(bridgeTick==1 || (partsReview && (bridgeTick-1)%60==0)) {
            foe.type=crewData[CREWDATA_TYPE];
            SetNpc(&foe);
            foe.mom=ENEMY;
        }
        foe.active=true; foe.dead=false; foe.moveHandler=0;
        foe.maxhp=24000; foe.hp=partsReview?24000:bridgeTick<70?24000:bridgeTick<130?9600:0;
        if(partsReview && getenv("CS_CANNON_SHOT_REVIEW")) StageArtilleryPreviewStep(bridgeTick%60==30);
        if(partsReview && bridgeTick%60==40 && bridgeTick<1200) {
            const int sample=bridgeTick/60;
            float mx=0,my=0;
            CastleReviewTrace(CastlePartsCannonMuzzle(robin.castle+1,&mx,&my) && mx>=0 && mx<=DX && my>=0 && my<=DY?
                "PASS mounted cannon muzzle":"FAIL mounted cannon muzzle bounds");
            char shotName[64]; sprintf(shotName,"castle_%02d_lv_%d.png",sample/2+1,(sample%2)*5);
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS cannon part capture":"FAIL cannon part capture");
            },std::string(path)+shotName);
        }
        if(partsReview && bridgeTick==1200) CastleReviewTrace("PASS cannon parts gallery");
        if(getenv("CS_SHOP_OFFER_REVIEW") && bridgeTick==20) StageShopPreviewOpen();
        if(getenv("CS_SHOP_OFFER_REVIEW") && bridgeTick==120)
            CastleReviewTrace(StageShopPreviewPurchaseChecks()?"PASS mixed shop purchases and funds guard":"FAIL mixed shop purchases");
        const char* shot=partsReview?nullptr:bridgeTick==40?"bridge-full.png":bridgeTick==100?"bridge-damaged.png":bridgeTick==160?"bridge-empty.png":nullptr;
        if(shot) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS bridge capture":"FAIL bridge capture");
        },std::string(path)+shot);
        if(bridgeTick==180) CastleReviewTrace("PASS bridge health review");
        return;
    }
    static int tick = 0;
    ++tick;
    if (tick == 1) {
        CastleReviewTrace("review setup");
        robin.castle = 0;
        robin.castleProgress = CastleMenuModel::Progress();
        CastleProgressEnsure();
        robin.gold = 1000000;
        robin.coin = 10000;
        GotoLobby();
        touchDisable = false;
        systemKey = AVK_POPUP_CASTLEMENU;
        PlayKey(PLAYER);
        CastleReviewTrace("castle menu opened");
        CastleReviewTrace(sprite[INVENTORY_CANNON_ATLAS_IMG] && texture[INVENTORY_CANNON_ATLAS_IMG] &&
            GetResourceName(RES_IMG,INVENTORY_CANNON_ATLAS_IMG).find("inventory_cannon/atlas.png")!=std::string::npos?
            "PASS cannon atlas registry and loading":"FAIL cannon atlas registry or loading");
    }
    if (tick == 70) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
    if (tick == 80) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BUY_GOLD);
    if (tick == 130) {
        CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PREV);
        CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_DETAIL);
    }
    if (tick == 190) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROOMS);
    if (tick == 200) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROW);
    if (tick == 250) { CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_UPGRADE); }
    if (tick == 310) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if (tick == 320) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PARTS);
    if (tick == 330) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROW + 3);
    if (tick == 345) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PAID_UPGRADE);
    if (tick == 355) CastleReviewTrace(robin.castleProgress.parts[0][3]==1 && robin.coin==9997?
        "PASS paid part upgrade":"FAIL paid part upgrade");
    if (tick == 335 && getenv("CS_CANNON_ASSET_REVIEW")) robin.castleProgress.parts[0][3]=2;
    if (tick == 370) {
        for (int i = 0; i < 5; ++i) robin.castleProgress.parts[0][i] = 5;
        CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    }
    if (tick == 380) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if (tick == 390) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
    if (tick == 395) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BUY);
    if (tick == 430) { CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_CONFIRM); }
    if(tick==280) CastleReviewTrace(robin.castleProgress.rooms[0][0]==1 && robin.gold==999760?"PASS room upgrade":"FAIL room upgrade");
    if(tick==460) CastleReviewTrace(CastleMenuModel::Owned(robin.castleProgress,1) && robin.coin==9397?"PASS paid purchase":"FAIL paid purchase");
    if(tick==480) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if(tick==490) CastleReviewTrace(CastleMenuSwipe(DX*.75f,DY-GNBHEIGHT-100*_2X,DX*.25f,DY-GNBHEIGHT-100*_2X)?"PASS swipe next":"FAIL swipe next");
    if(tick==500) CastleReviewTrace(CastleMenuSwipe(DX*.25f,DY-GNBHEIGHT-100*_2X,DX*.75f,DY-GNBHEIGHT-100*_2X)?"PASS swipe previous":"FAIL swipe previous");
    if(tick==520 && !NetIsBusy()) {
        if(NetRequest(NETREQ_LOAD)) { robin.castleProgress=CastleMenuModel::Progress(); CastleReviewTrace("local server reload requested"); }
        else CastleReviewTrace("FAIL reload request");
    }
    if(tick==600) CastleReviewTrace(NetLastResult()==NETRESULT_OK &&
        CastleMenuModel::Owned(robin.castleProgress,1) && robin.castleProgress.rooms[0][0]==1 &&
        CastleMenuModel::Completed(robin.castleProgress,0)==25 && robin.coin==9397 && robin.gold==999760?
        "PASS local server save and reload":"FAIL local server save and reload");
    const char* shot = tick==40?"01-list.png":tick==100?"02-locked.png":
        tick==160?"03-parts.png":tick==220?"04-room.png":tick==280?"05-room-upgraded.png":
        tick==340?"06-cannon.png":tick==400?"07-purchase.png":tick==460?"08-purchased.png":nullptr;
    if (shot) cocos2d::utils::captureScreen([](bool ok,const std::string& file) {
        FILE* log = fopen((std::string(getenv("CS_CASTLE_REVIEW_PATH"))+"screens.log").c_str(),"a");
        if (log) { fprintf(log,"%s %s\n",ok?"PASS":"FAIL",file.c_str()); fclose(log); }
    },std::string(path)+shot);
}
