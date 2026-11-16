// Native renderer/model smoke review. Activated only by an explicit review environment.
void monsterPartsReviewStep(){
    static bool checked=false,done=false,prepared=false;
    static int sample=0,hold=0;
    if(done||reviewCapturePending)return;
    if(!checked){
        bool valid=true;int cases=0,failures=0;
        for(int npc=3;npc<360;++npc){
            const auto* e=MonsterParts::enemy(npc);
            if(!e||e->cmf!=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF]){valid=false;
                char text[120];std::snprintf(text,sizeof(text),"FAIL mapping npc=%d expected=%d actual=%d",npc,e?e->cmf:-1,enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF]);reviewTrace(text);}
            for(int stage=0;stage<10;++stage)for(int wave:{0,4,9}){
                MonsterBoard::build(stage,wave,npc);
                const auto l=MonsterParts::loadout(npc,wave);
                valid=valid&&l.weaponCount>=1&&l.weaponCount<=3;
                if(MonsterBoard::partCount()!=l.count){valid=false;if(failures++<5){
                    char text[120];std::snprintf(text,sizeof(text),"FAIL board npc=%d stage=%d wave=%d expected=%d actual=%d",npc,stage,wave,l.count,MonsterBoard::partCount());reviewTrace(text);}}
                ++cases;
            }
        }
        for(int page=0;page<MonsterParts::AtlasCount;++page){const int img=MONSTER_PARTS_FIRST_IMG+page;
            if(!sprite[img])LoadImg(img);if(!sprite[img]){valid=false;reviewTrace("FAIL missing monster part atlas");}
        }
        char text[120];std::snprintf(text,sizeof(text),"%s %d native boards, 357 species mappings and two loaded CMF part atlases",valid?"PASS":"FAIL",cases);reviewTrace(text);
        if(!valid){done=true;return;}checked=true;
    }
    static const int npcs[]={12,12,10,28,198};
    static const int waves[]={0,9,9,14,9};
    static const int turns[]={0,2,2,2,2};
    if(sample>=5){reviewTrace("DONE monster parts review");done=true;return;}
    if(!prepared){
        holdVitals=true;debugFirstBoss=false;reviewEnemyNpc=npcs[sample];
        run.stage=0;run.wave=waves[sample];run.setShape(castleShape(0));run.choosing=false;run.lost=false;
        run.enemyMax=10000;run.enemyHp=6000;run.lives=run.maxLives=10000;run.guard=run.guardMax=500;
        run.enemyAttack=100;run.skipTurns=0;run.effects=Effects();run.realVitals=true;
        run.shots.clear();run.nextShot=0;run.counterResolved=false;run.passing=false;
        run.configureMonster(reviewEnemyNpc);run.monsterActionTurn=turns[sample];
        entryElapsed=introElapsed=-1;animation=0;waveTransition=MergeCombat::WaveTransition();
        action=CombatAction();enemyTurn=EnemyTurn();beginEnemyTurn();
        enemyTurn.time.elapsed=enemyTurn.phases.approach+std::max(1,enemyTurn.phases.attack/3);
        run.attacking=false;MonsterBoard::expanded=true;MonsterBoard::selected=1;
        if(sample==0&&enemyTurn.pattern.index!=1){reviewTrace("FAIL boar normal native animation");done=true;return;}
        if(sample==1&&(enemyTurn.hits!=2||enemyTurn.weaponActions.size()!=2||enemyTurn.weaponActions[1]->nativePattern!=0)){reviewTrace("FAIL boar two-weapon bundle or rush mapping");done=true;return;}
        if(sample==2){
            const long long hp=run.enemyHp,lives=run.lives;run.attacking=true;
            const long long heal=run.monsterHealing();const bool applied=run.counterattack();run.attacking=false;
            if(!applied||run.enemyHp!=hp+heal||heal<=0||run.counterHit()<=0||enemyTurn.hits!=run.monsterLoadout().weaponCount){reviewTrace("FAIL native passive regeneration");done=true;return;}
            (void)lives;
            reviewTrace("PASS passive regeneration after attack bundle without a healing action");
        }
        prepared=true;hold=0;return;
    }
    if(++hold<15)return;
    char name[80];std::snprintf(name,sizeof(name),"monster-parts-%02d-npc-%d",sample,npcs[sample]);reviewCapture(name);
    ++sample;prepared=false;
}
