// Included by Func_Battle.cpp: combat adapter and renderer for the pure model.
namespace {
CastleArtillery::State stageArtillery;
int artilleryGeneration[TOTALOBJECT]={0};
int artilleryVolleyTarget=-1,artilleryVolleyGeneration=0;

CastleArtillery::Point ArtilleryTargetPoint(int foe) {
    CastleArtillery::Point point={Min((float)DX-32*_2X,256.0f*_2X),
        (float)StageBg::GroundY()+28*_2X};
    const OBJECT* e=&ao[foe];
    if(e->cmf>=0 && e->cmf<TOTALCMF && e->motion>=0 && e->motion<cmf_m_cnt[e->cmf]) {
        const signed short* bounds=cmfMotionImgSizeBlob+cmfMotionImgSizeSlot[e->cmf]+e->motion*4;
        const float z=enemyIconZoom[e->type]*1.75f;
        point.x-=(bounds[0]+bounds[2]*0.5f)*z;
        point.y=StageBg::GroundY()-3*_2X-(bounds[1]+bounds[3]*0.5f)*z;
    }
    return point;
}
bool ArtilleryTargetValid(const CastleArtillery::Shot& shot) {
    return shot.target>=ENEMY && shot.target<NEUTRAL && StageRtFoeAlive(shot.target)
        && artilleryGeneration[shot.target]==shot.generation;
}
void ArtilleryHit(int target) {
    OBJECT* hero=&ao[PLAYER];
    const long long damage=hero->ps[PS_DMG];
    const int attackFrame=hero->attackFrame,attackLv=hero->attackLv;
    hero->ps[PS_DMG]=Max(1LL,damage*CastleCannonDamagePercent(stageArtillery.grade)/100);
    AttackObj(PLAYER,target,true);
    hero->ps[PS_DMG]=damage;
    hero->attackFrame=attackFrame; hero->attackLv=attackLv;
}
void ArtillerySprite(int group,int animation,float x,float y,float size,float angle=0,int opacity=ALPHA_MAX) {
    const CastleArtilleryFrame& f=kCastleArtilleryFrames[group*8+(animation%8)];
    const float z=size/Max(f.w,f.h);
    RotateImage(f.w,f.h,f.x,f.y,(int)x,(int)y,false,angle,0,opacity,z,
        Vec2(0.5f,0.5f),sprite[CASTLE_ARTILLERY_IMG],CASTLE_ARTILLERY_IMG);
}
void ArtilleryBeam(const CastleArtillery::Shot& s,int animation) {
    const float dx=s.destination.x-s.from.x,dy=s.destination.y-s.from.y;
    const float length=std::sqrt(dx*dx+dy*dy);
    const float thickness=(10+3*CastleArtillery::ClampUpgrade(s.upgrade))*_2X;
    const int pieces=Max(1,(int)std::ceil(length/thickness));
    const float angle=-std::atan2(dy,dx)*180/3.14159265f;
    for(int i=0;i<pieces;++i) {
        const float t=(i+0.5f)/pieces;
        ArtillerySprite(stageArtillery.grade,animation,s.from.x+dx*t,s.from.y+dy*t,
            thickness+2*_2X,angle);
    }
}
}

void StageArtilleryNotifySpawn(int obj) {
    if(obj>=0 && obj<TOTALOBJECT) ++artilleryGeneration[obj];
}
void StageArtilleryReset(int castle) {
    // castle 이 음수면 가방에 실린 포를 본다. 없으면 성 그림을 따른다 -
    // 판 밖에서 불릴 때 기준이 하나는 있어야 한다.
    if(castle<0) { int c=gMobileCastleVisual; StageBagCannon(&c,NULL,NULL); castle=c; }
    stageArtillery.Reset(castle);
    artilleryVolleyTarget=-1;
}

//---- 가방 칸에 그릴 쿨타임 ----
//
// 그 칸이 지금 쏘는 포일 때만 참이다. charge 는 0~1, flash 는 다 찼을 때의
// 번쩍임이다. 검(StageRtSwordCharge)과 같은 모양으로 돌려준다.
bool StageArtilleryCharge(int slot,float* charge,int* flash) {
    int bagSlot=-1;
    if(!IsStageRealtime() || !StageBagCannon(NULL,NULL,&bagSlot) || bagSlot!=slot) return false;
    if(charge) *charge=stageArtillery.charge
        /(float)Max(1,(int)CastleArtillery::State::ChargeFrames);
    if(flash) *flash=stageArtillery.recoil;
    return true;
}
bool StageArtilleryVisual(float* charge,float* recoil,int* burst) {
    *charge=0; *recoil=0; *burst=0;
    if(!IsStageRealtime() || stageArtillery.grade!=CastleArtillery::ClampGrade(gMobileCastleVisual)) return false;
    *charge=stageArtillery.charge/(float)CastleArtillery::State::ChargeFrames;
    *recoil=stageArtillery.recoil/8.0f;
    *burst=stageArtillery.pending;
    return true;
}
void StageArtilleryStep(bool running,int foe) {
    // 쏘는 주인은 가방에 실린 포다. 성에 붙어 혼자 쏘던 것을 옮겼다.
    // 안 싣고 왔으면 아무 일도 없다.
    int bagCastle=0,bagLevel=0;
    if(!StageBagCannon(&bagCastle,&bagLevel,NULL)) { StageArtilleryReset(); return; }
    if(stageArtillery.grade!=CastleArtillery::ClampGrade(bagCastle)) StageArtilleryReset(bagCastle);
    if(!running) return;
    stageArtillery.cooldownOverride=CastleCannonCooldown(stageArtillery.grade);
    // 단계는 성 그림이 아니라 실어 온 그 포의 것이다.
    stageArtillery.upgrade=bagLevel;
    const int grade=stageArtillery.grade;
    CastleArtillery::Point muzzle={0,0};
    if(!CastlePartsCannonMuzzle(grade+1,&muzzle.x,&muzzle.y)) return;
    const int target=StageRtFoeAlive(foe)?foe:-1;
    const int generation=target>=0?artilleryGeneration[target]:0;
    if(stageArtillery.pending && (target!=artilleryVolleyTarget || generation!=artilleryVolleyGeneration))
        stageArtillery.pending=0;
    if(stageArtillery.charge==1 && target>=0) {
        artilleryVolleyTarget=target; artilleryVolleyGeneration=generation;
    }
    const CastleArtillery::Point destination=target>=0?ArtilleryTargetPoint(target):muzzle;
    stageArtillery.Tick(target,generation,muzzle,destination);
    for(int i=0;i<CastleArtillery::State::Capacity;++i) {
        CastleArtillery::Shot& shot=stageArtillery.shots[i];
        if(!shot.active) continue;
        if(shot.impact) { if(--shot.impact==0) shot.active=false; continue; }
        if(!ArtilleryTargetValid(shot)) { shot.active=false; continue; }
        const CastleArtillery::Point point=ArtilleryTargetPoint(shot.target);
        if(stageArtillery.Move(shot,point,8*_2X)) ArtilleryHit(shot.target);
    }
}
void StageArtilleryDraw(void) {
    if(!IsStageRealtime()) return;
    if(!StageBagCannon(NULL,NULL,NULL)) return;   // 안 싣고 왔으면 그릴 것도 없다
    if(!sprite[CASTLE_ARTILLERY_IMG]) LoadImg(CASTLE_ARTILLERY_IMG);
    if(!texture[CASTLE_ARTILLERY_IMG]) LoadTexture(CASTLE_ARTILLERY_IMG);
    if(!sprite[CASTLE_ARTILLERY_IMG] || !texture[CASTLE_ARTILLERY_IMG]) return;
    const int grade=stageArtillery.grade;
    const CastleArtillery::Profile& p=CastleArtillery::Of(grade);
    const float muzzleScale=CastleArtillery::ProjectileScale(CastleVisualPartLevel(grade,3));
    float mx=0,my=0;
    if(!CastlePartsCannonMuzzle(grade+1,&mx,&my)) return;
    if(stageArtillery.charge) {
        const int animation=(CastleArtillery::State::ChargeFrames-stageArtillery.charge)*8/
            CastleArtillery::State::ChargeFrames;
        ArtillerySprite(20+grade,animation,mx,my,(14+grade)*_2X*muzzleScale);
    }
    if(stageArtillery.recoil) {
        const int animation=8-stageArtillery.recoil;
        ArtillerySprite(20+grade,animation,mx+8*_2X,my,(22+grade)*_2X*muzzleScale);
        if(p.kind==CastleArtillery::Gatling) {
            for(int i=0;i<3;++i) {
                const float angle=(animation*60+i*120)*3.14159265f/180;
                ArtillerySprite(20+grade,animation,mx+std::cos(angle)*5*_2X,
                    my+std::sin(angle)*5*_2X,6*_2X);
            }
        }
    }
    if(p.kind==CastleArtillery::Gatling && (stageArtillery.pending||stageArtillery.recoil||stageArtillery.charge)) {
        const int phase=stageArtillery.charge?CastleArtillery::State::ChargeFrames-stageArtillery.charge:
            (p.hits-stageArtillery.pending)*p.interval-stageArtillery.burstClock;
        ArtillerySprite(30,Max(0,phase)/2,mx-6*_2X,my,15*_2X);
    }
    for(int i=0;i<CastleArtillery::State::Capacity;++i) {
        const CastleArtillery::Shot& s=stageArtillery.shots[i];
        if(!s.active) continue;
        const int animation=s.age/3;
        const float shotScale=CastleArtillery::ProjectileScale(s.upgrade);
        if(s.impact) {
            const int impact=(CastleArtillery::State::ImpactFrames-s.impact)*8/CastleArtillery::State::ImpactFrames;
            ArtillerySprite(10+grade,impact,s.position.x,s.position.y,(p.size+12)*_2X*shotScale);
            if(p.kind==CastleArtillery::Laser) ArtilleryBeam(s,impact);
            if(p.kind==CastleArtillery::Electric)
                DrawEffect(EFFECT_THUNDER0+impact,s.position.x,s.position.y,0,0,0.85f*shotScale);
            if(p.kind==CastleArtillery::Ice)
                DrawEffect(EFFECT_ICE0+impact,s.position.x,s.position.y,0,0,0.85f*shotScale);
            continue;
        }
        if(p.kind==CastleArtillery::Laser) { ArtilleryBeam(s,animation); continue; }
        const float dx=s.position.x-s.previous.x,dy=s.position.y-s.previous.y;
        const float angle=p.kind==CastleArtillery::Rock?s.age*12.0f:
            (p.kind==CastleArtillery::Homing||p.kind==CastleArtillery::Rockets)?
            -std::atan2(dy,dx)*180/3.14159265f:0;
        if(p.kind==CastleArtillery::Flame||p.kind==CastleArtillery::Homing||p.kind==CastleArtillery::Rockets) {
            ArtillerySprite(20+grade,animation,s.previous.x,s.previous.y,p.size*_2X*0.6f*shotScale);
        }
        for(int trail=0;trail<s.upgrade/2;++trail)
            ArtillerySprite(grade,animation,s.previous.x-dx*.6f*trail,s.previous.y-dy*.6f*trail,
                p.size*_2X*shotScale*.7f,angle,12-trail*3);
        ArtillerySprite(grade,animation,s.position.x,s.position.y,p.size*_2X*shotScale,angle);
    }
    // 충전 게이지와 "투석포 4.5s" 줄은 걷어냈다.
    //
    // 대포는 이제 가방에 실린 물건이고, 쿨타임은 그 칸 위에 그린다
    // (Func_Draw.cpp 의 가방 그리기). 같은 것을 화면 아래에 또 적으면
    // 한 가지를 두 자리에서 읽게 된다.
}

//---- 대포 점검용 ----
//
//환경변수 두 개가 다 켜져 있을 때만 돈다. 성 파츠와 발사를 눈으로
//맞춰 보는 자리라 평소에는 아무 일도 안 한다.
void StageArtilleryPreviewStep(bool prime) {
    if(!getenv("CS_CANNON_PARTS_REVIEW") || !getenv("CS_CANNON_SHOT_REVIEW")) return;
    if(prime) { stageArtillery.charge=1; stageArtillery.pending=0; }
    StageArtilleryStep(true,StageRtFoe());
}
