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
void StageArtilleryReset(void) {
    stageArtillery.Reset(gMobileCastleVisual);
    artilleryVolleyTarget=-1;
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
    if(stageArtillery.grade!=CastleArtillery::ClampGrade(gMobileCastleVisual)) StageArtilleryReset();
    if(!running) return;
    stageArtillery.cooldownOverride=CastleCannonCooldown(stageArtillery.grade);
    stageArtillery.upgrade=CastleVisualPartLevel(stageArtillery.grade,3);
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
    // Keep the charge gauge below the barrel and above the castle HP stripe.
    const int w=80*_2X,h=4*_2X;
    const int x=Max(4*_2X,Min(DX-w-4*_2X,(int)mx-w));
    const int y=Max(StageBg::GroundY()+22*_2X,(int)CastlePartsCannonBaseY(grade+1)-18*_2X);
    SetAlpha(24); MemRect(x-3*_2X,y+14*_2X,w+6*_2X,25*_2X,COLOR_NAVY); SetAlpha(ALPHA_MAX);
    MemRect(x,y,w,h,0x182338);
    const float progress=stageArtillery.Progress();
    MemRect(x+_2X,y-_2X,(int)((w-2*_2X)*progress),h-2*_2X,p.color);
    MemRectFrame(x,y,w,h,0xD2BC85);
    char label[96];
    if(stageArtillery.pending||stageArtillery.recoil) sprintf(label,"%s · %d연타",p.name,p.hits);
    else if(stageArtillery.charge) sprintf(label,"%s · 충전",p.name);
    else sprintf(label,"%s %.1fs",p.name,Max(0,CastleCannonCooldown(grade)-stageArtillery.cooldown)/(float)FPS);
    SetFontColor(COLOR_WHITE);
    CenterTextStrSolid(label,x+w/2,y+12*_2X,
        Min(0.62f,w/Max(1.0f,StringWidth(label,1.0f))));
}

void StageArtilleryPreviewStep(bool prime) {
    if(!getenv("CS_CANNON_PARTS_REVIEW") || !getenv("CS_CANNON_SHOT_REVIEW")) return;
    if(prime) { stageArtillery.charge=1; stageArtillery.pending=0; }
    StageArtilleryStep(true,StageRtFoe());
}
