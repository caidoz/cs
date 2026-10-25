// Stage-only balance v1. Included by Func_Battle.cpp after its run actor helpers.
static AllyBalance::CompanionState stageBalancedAllies[64];
static AllyBalance::StatusState stageBalancedStatus;
static int stageBalancedTarget=-1,stageBalancedTargetType=-1,stageBalancedFortify=0;
static int stageBalancedSupply=0,stageBalancedSlowClock=0;
static int stageBalancedBulletPower[TOTALOBJECT]={};
static bool stageBalanceApplying=false;
static int stageBalanceEffects[64]={};

static const AllyBalance::Profile* StageBalancedProfile(int type)
{
    return AllyBalance::Get(GetCrewIdxFromType(type));
}
static void StageAlliesBalanceReset(void)
{
    for(auto& state:stageBalancedAllies) state=AllyBalance::CompanionState();
    stageBalancedStatus=AllyBalance::StatusState();stageBalancedTarget=stageBalancedTargetType=-1;
    stageBalancedFortify=stageBalancedSupply=stageBalancedSlowClock=0;stageBalanceApplying=false;
    memset(stageBalancedBulletPower,0,sizeof(stageBalancedBulletPower));memset(stageBalanceEffects,0,sizeof(stageBalanceEffects));
}
static bool StageBalancedTarget(int target)
{
    return target>=ENEMY && target<NEUTRAL && ao[target].active && !ao[target].dead
        && ao[target].hp>0 && ao[target].moveHandler!=VANISHMOVE;
}
static void StageBalancedEnsureTarget(int target)
{
    if(target!=stageBalancedTarget || (target>=0 && ao[target].type!=stageBalancedTargetType)) {
        stageBalancedStatus=AllyBalance::StatusState();stageBalancedSlowClock=0;
        stageBalancedTarget=target;stageBalancedTargetType=target>=0?ao[target].type:-1;
    }
}
static bool StageBalancedCondition(const AllyBalance::Profile& p,int target)
{
    using C=AllyBalance::Condition;
    const OBJECT& hero=ao[PLAYER];
    const bool foe=StageBalancedTarget(target);
    StageAllyPlacement place={};StageAllyPlacementFor(p.npc,&place);
    switch(p.condition) {
    case C::LowHp:return hero.hp<=hero.maxhp/2;
    case C::HighHp:return hero.hp>hero.maxhp/2;
    case C::LowShield:return hero.shield<=hero.shieldMax/2;
    case C::EnemyLowHp:return foe && ao[target].hp<=ao[target].maxhp/2;
    case C::EnemyHighHp:return foe && ao[target].hp>ao[target].maxhp/2;
    case C::EnemyDebuffed:return foe && stageBalancedStatus.Any();
    case C::EnemyClean:return foe && !stageBalancedStatus.Any();
    case C::Front:return place.front;
    case C::Back:return !place.front;
    case C::AdjacentWeapon:return place.adjacentWeapon;
    case C::AdjacentCrew:return place.adjacentCrew;
    case C::EveryThird:return stageBalancedAllies[p.id].heroAttacks>=3;
    case C::Alone:return !place.adjacentCrew;
    default:return true;
    }
}
static bool StageBalancedDamage(int target,int percent)
{
    if(!StageBalancedTarget(target) || percent<=0) return false;
    OBJECT& hero=ao[PLAYER];const long long previous=hero.ps[PS_DMG];
    hero.ps[PS_DMG]=Max(1LL,previous*percent/100);
    const bool before=stageBalanceApplying;stageBalanceApplying=true;
    AttackObj(PLAYER,target,true);
    stageBalanceApplying=before;hero.ps[PS_DMG]=previous;return true;
}
static bool StageBalancedApply(const AllyBalance::Profile& p,AllyBalance::Action action,int power,int target)
{
    using A=AllyBalance::Action;
    using namespace AllyBalance;
    OBJECT& hero=ao[PLAYER];
    const bool foe=StageBalancedTarget(target);
    switch(action) {
    case A::Shield:
        if(hero.shield>=hero.shieldMax) return false;
        hero.shield=(int)Min((long long)hero.shieldMax,(long long)hero.shield+Max(1LL,(long long)hero.shieldMax*Min(20,power)/100));return true;
    case A::Heal:case A::Repair:
        if(hero.hp>=hero.maxhp) return false;
        hero.hp=Min(hero.maxhp,hero.hp+Max(1LL,hero.maxhp*Min(15,power)/100));return true;
    case A::Supply: {
        const int gain=Min(30-stageBalancedSupply,Min(20,power));
        if(gain<=0) return false;
        stageBalancedSupply+=gain;
        const int maximum=hero.equip[EQUIP_WEAPON].type==ITEM_BOOMERANG?STAGE_MAX_BASIC_COOLDOWN:STAGE_HERO_COOLDOWN;
        stageHeroCool=Min(maximum,stageHeroCool+maximum*gain/100);
        for(int i=0;i<GRIDTEST_MAXITEM;++i)
            stageSwordCool[i]=Min(stageSwordMax[i],stageSwordCool[i]+stageSwordMax[i]*gain/100);
        return true;
    }
    case A::Inspire: {
        bool applied=false;
        for(int i=0;i<MAXCREW;++i) if(ao[CREW+i].active && !ao[CREW+i].dead && ao[CREW+i].type!=p.npc) {
            const auto* other=StageBalancedProfile(ao[CREW+i].type);
            if(other && StageAlliesAreAdjacent(p.npc,other->npc)) {
                stageBalancedAllies[other->id].nextShotBonus=Min(40,stageBalancedAllies[other->id].nextShotBonus+power);
                applied=true;
            }
        }
        return applied;
    }
    case A::Fortify:stageBalancedFortify=Min(25,Max(stageBalancedFortify,power));return true;
    case A::Cleanse:
        for(int i=0;i<TOTALDEBUF;++i) if(hero.debuf[i]>0) {
            hero.debuf[i]=0;hero.debufRemainTurn[i]=0;hero.debufOwner[i]=0;return true;
        }
        return false;
    case A::Volley: {
        if(!foe) return false;
        const int actor=StageAllyLinkActor(p.npc);if(actor<0) return false;
        for(int i=BULLET;i<ENEMYUSEROBJ;++i) if(!ao[i].active) {
            AllyShootAt(actor,1,target);stageBalancedBulletPower[i]=power;return ao[i].active;
        }
        return false;
    }
    case A::Strike:
        if(!foe) return false;
        if(power>=150 && stageBalancedStatus.Consume(Exposed)>0) power=power*125/100;
        return StageBalancedDamage(target,power);
    case A::Leech:
        if(!foe || hero.hp>=hero.maxhp) return false;
        StageBalancedDamage(target,50);
        hero.hp=Min(hero.maxhp,hero.hp+Max(1LL,hero.maxhp*Min(10,power)/100));return true;
    case A::Discharge: {
        if(!foe) return false;
        const int stacks=stageBalancedStatus.Consume(Shocked);
        return stacks>0 && StageBalancedDamage(target,power*stacks/4);
    }
    case A::Burn:case A::Poison:case A::Chill:case A::Shock:case A::Bleed:case A::Expose: {
        if(!foe) return false;
        const Status status=action==A::Burn?Burning:action==A::Poison?Poisoned:action==A::Chill?Chilled:
            action==A::Shock?Shocked:action==A::Bleed?Bleeding:Exposed;
        if((status==Poisoned && ao[target].immune[POISON]) || (status==Chilled && ao[target].immune[SLOW])) return false;
        stageBalancedStatus.Apply(status,Min(3,power),FPS);return true;
    }
    default:return false; // Three prototype companions have their approved handlers.
    }
}
static void StageAlliesBalanceDispatch(StageAllyLink::EventKind kind,int target,std::uint64_t root,bool derived)
{
    if(!StageAllyLinksRunning() || stageBalanceApplying || derived) return;
    StageBalancedEnsureTarget(target);
    const int hero=PlayerHeroType();
    const bool main=(hero==ROBIN && kind==StageAllyLink::RobinHit) || (hero==DIANA && kind==StageAllyLink::DianaShot)
        || (hero==MAXX && kind==StageAllyLink::MaxReturned);
    const bool contact=kind==StageAllyLink::RobinHit || kind==StageAllyLink::DianaShot || kind==StageAllyLink::MaxHit;
    if(contact) {
        StageBalancedDamage(target,stageBalancedStatus.Bleed(root));
        stageBalancedSupply=0;
    }
    if(!main) return;
    for(int i=0;i<64;++i) {
        const auto& p=AllyBalance::Profiles[i];auto& state=stageBalancedAllies[i];
        if(AllyBalance::Prototype(p) || StageAllyLinkActor(p.npc)<0 || !state.Observe((int)kind,root,false)) continue;
        ++state.heroAttacks;
        const auto& synergy=p.synergy[hero];
        if(state.linkClock<AllyBalance::Frames(synergy.cooldownMs,FPS) || !StageBalancedCondition(p,target)) continue;
        if(StageBalancedApply(p,synergy.action,synergy.power,target)) {
            state.linkClock=0;state.flash=FPS/4;++stageBalanceEffects[i];
        }
    }
}
static void StageAlliesBalanceStep(bool running,int target)
{
    StageBalancedEnsureTarget(target);
    const int dot=stageBalancedStatus.Tick(running,FPS);
    if(dot>0) StageBalancedDamage(target,dot);
    const int hero=PlayerHeroType();
    for(int i=0;i<64;++i) {
        const auto& p=AllyBalance::Profiles[i];auto& state=stageBalancedAllies[i];
        if(AllyBalance::Prototype(p)) continue;
        const int limit=AllyBalance::Frames(p.abilityMs,FPS),link=AllyBalance::Frames(p.synergy[hero].cooldownMs,FPS);
        const bool present=StageAllyLinkActor(p.npc)>=0;
        state.Tick(running,present,limit,link);
        if(!running || !present || state.abilityClock<limit || !StageBalancedCondition(p,target)) continue;
        if(StageBalancedApply(p,p.action,p.power,target)) {
            state.abilityClock=0;state.flash=FPS/4;++stageBalanceEffects[i];
            if(p.condition==AllyBalance::Condition::EveryThird) state.heroAttacks=0;
        }
    }
}
static bool StageAlliesBalanceCharge(int type,float* charge,int* flash,const char** label)
{
    const auto* p=StageBalancedProfile(type);
    if(!p || AllyBalance::Prototype(*p) || StageAllyLinkActor(type)<0) return false;
    const auto& state=stageBalancedAllies[p->id];
    *charge=Min(1.0f,state.abilityClock/(float)Max(1,AllyBalance::Frames(p->abilityMs,FPS)));
    *flash=state.flash;
    using A=AllyBalance::Action;
    switch(p->action) {
    case A::Shield:*label="보호";break;
    case A::Heal:case A::Leech:*label="회복";break;
    case A::Repair:*label="수리";break;
    case A::Supply:*label="보급";break;
    case A::Inspire:*label="격려";break;
    case A::Cleanse:*label="정화";break;
    case A::Burn:*label="화상";break;
    case A::Poison:*label="중독";break;
    case A::Chill:*label="냉기";break;
    case A::Shock:case A::Discharge:*label="감전";break;
    case A::Bleed:*label="출혈";break;
    case A::Expose:*label="표식";break;
    case A::Fortify:*label="수호";break;
    default:*label="추가타";break;
    }
    return true;
}
static void StageAlliesBalanceDraw(void)
{
    if(!StageBalancedTarget(stageBalancedTarget) || !stageBalancedStatus.Any()) return;
    float x=0,y=0;StageCombatActorPoint(stageBalancedTarget,&x,&y,true);
    const char* labels[]={"화상","중독","냉기","감전","출혈","취약"};
    const int colors[]={0xFF7744,0x8ED44C,0x66DDFF,0xCCAAFF,0xFF5577,0xFFD45A};
    int row=0;
    for(int s=0;s<AllyBalance::StatusCount;++s) if(stageBalancedStatus.stacks[s]>0) {
        char text[32];sprintf(text,"%s %d",labels[s],stageBalancedStatus.stacks[s]);
        SetFontColor(colors[s]);CenterTextStrSolid(text,(int)x,(int)y+18*_2X+row++*10*_2X,.4f);
    }
}
long long StageAllyBalancedShotBegin(int obj)
{
    if(!IsStageRealtime() || obj<BULLET || obj>=ENEMYUSEROBJ) return -1;
    const int actor=ao[obj].mom;
    if(actor<CREW || actor>=CREW+MAXCREW) return -1;
    const auto* p=StageBalancedProfile(ao[actor].type);if(!p) return -1;
    const long long previous=ao[actor].ps[PS_DMG];
    int percent=p->attackPercent+stageBalancedAllies[p->id].nextShotBonus;
    stageBalancedAllies[p->id].nextShotBonus=0;
    if(stageBalancedBulletPower[obj]>0) percent=percent*stageBalancedBulletPower[obj]/100;
    stageBalancedBulletPower[obj]=0;
    ao[actor].ps[PS_DMG]=Max(1LL,previous*percent/100);return previous;
}
void StageAllyBalancedShotEnd(int obj,long long previousDamage)
{
    if(previousDamage<0 || obj<0 || obj>=TOTALOBJECT) return;
    const int actor=ao[obj].mom;
    if(actor>=CREW && actor<CREW+MAXCREW) ao[actor].ps[PS_DMG]=previousDamage;
}

bool StageAlliesBalanceReview(void)
{
    using namespace AllyBalance;
    if(!getenv("CS_ALLIES_BALANCE_REVIEW")) return false;
    int abilities=0,links=0;
    const auto fail=[&](int id,int hero,const char* reason) {
        const char* path=getenv("CS_CASTLE_REVIEW_PATH");
        if(path) {FILE* f=fopen((std::string(path)+"details.log").c_str(),"a");
            if(f) {fprintf(f,"FAIL id=%d hero=%d %s\n",id,hero,reason);fclose(f);}}
        return false;
    };
    for(int id=0;id<64;++id) for(int hero=0;hero<3;++hero) {
        const auto& p=Profiles[id];
        if(!StageAlliesBalanceReviewFixture(id,hero)) return fail(id,hero,"placement");
        OBJECT& foe=ao[ENEMY];foe.type=crewData[CREWDATA_TYPE];SetNpc(&foe);
        foe.mom=ENEMY;foe.active=true;foe.dead=false;foe.moveHandler=0;foe.x=foe.nx=DX-60;
        ao[PLAYER].active=true;ao[PLAYER].dead=false;
        waveStatus=WAVESTATUS_PLAY;attackSequence=ATTACKSEQUENCE_READY;StageRtSetAuto(true);
        StageBalancedEnsureTarget(ENEMY);
        StageAllyPlacement place={};
        if(!StageAllyPlacementFor(p.npc,&place)) return fail(id,hero,"grid context");
        const int actor=StageAllyLinkActor(p.npc);
        if(actor<0 || BossRaidCrewCooldown(actor-CREW)!=Frames(p.attackMs,FPS)) return fail(id,hero,"attack timing");
        if(Prototype(p)) continue;
        auto& state=stageBalancedAllies[id];
        const int ability=Frames(p.abilityMs,FPS),link=Frames(p.synergy[hero].cooldownMs,FPS);
        const auto prepare=[&](AllyBalance::Action action) {
            ao[PLAYER].maxhp=1000000000;ao[PLAYER].hp=p.condition==Condition::HighHp?800000000:200000000;
            ao[PLAYER].shieldMax=10000;ao[PLAYER].shield=100;
            foe.maxhp=1000000000;foe.hp=p.condition==Condition::EnemyLowHp?200000000:800000000;
            foe.shield=0;foe.shieldMax=0;foe.dead=false;foe.active=true;foe.moveHandler=0;
            stageBalancedStatus=StatusState();stageBalancedSupply=0;
            if(p.condition==Condition::EnemyDebuffed) stageBalancedStatus.Apply(Poisoned,1,FPS);
            if(action==AllyBalance::Action::Discharge) stageBalancedStatus.Apply(Shocked,4,FPS);
            if(action==AllyBalance::Action::Cleanse) ao[PLAYER].debuf[POISON]=FPS;
            state.heroAttacks=3;
        };
        for(int t=0;t<Max(ability,link);++t) state.Tick(true,true,ability,link);
        prepare(p.action);
        if(!StageBalancedCondition(p,ENEMY)) return fail(id,hero,"authored condition");
        StageAlliesBalanceStep(true,ENEMY);
        if(stageBalanceEffects[id]!=1) return fail(id,hero,"primary ability");
        if(hero==0) ++abilities;
        prepare(p.synergy[hero].action);
        state.linkClock=link;
        const auto kind=hero==ROBIN?StageAllyLink::RobinHit:hero==DIANA?StageAllyLink::DianaShot:StageAllyLink::MaxReturned;
        const int before=stageBalanceEffects[id];
        StageAlliesBalanceDispatch(kind,ENEMY,1000+hero,false);
        if(stageBalanceEffects[id]!=before+1) return fail(id,hero,"hero synergy");
        StageAlliesBalanceDispatch(kind,ENEMY,1000+hero,false);
        StageAlliesBalanceDispatch(kind,ENEMY,1001+hero,true);
        if(stageBalanceEffects[id]!=before+1) return fail(id,hero,"dedup or recursion");
        if(ao[PLAYER].hp>ao[PLAYER].maxhp || ao[PLAYER].shield>ao[PLAYER].shieldMax) return fail(id,hero,"healing cap");
        ++links;
    }
    const bool complete=abilities==61 && links==183;
    StageRunEquipmentEnd();
    for(const auto& state:stageBalancedAllies) if(state.abilityClock || state.linkClock || state.flash || state.nextShotBonus) return false;
    if(stageBalancedStatus.Any() || stageBalancedFortify || stageBalancedSupply) return false;
    return complete;
}
