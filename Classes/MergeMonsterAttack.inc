// One native attack animation per active part weapon, never more than three.
void beginEnemyTurn(){
    MonsterBoard::ensure();enemyTurn=EnemyTurn();enemyTurn.started=true;
    enemyTurn.damage=run.counterDamage();enemyTurn.rawDamage=run.counterHit();enemyTurn.healing=run.monsterHealing();
    const int npc=combatEnemyNpc(),cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
    const auto l=run.monsterLoadout();enemyTurn.hits=std::max(1,std::min(3,l.weaponCount));
    if(cmf>=0&&cmf<MAXCMF){
        if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
        for(int weapon=0;weapon<enemyTurn.hits;++weapon){
            const auto& a=MonsterParts::action(npc,weapon);
            const auto p=nativeEnemyPattern(npc,cmf,a.nativePattern);
            enemyTurn.weaponActions.push_back(&a);enemyTurn.rawShares.push_back(run.monsterWeaponDamage(weapon));
            if(weapon==0){
                enemyTurn.pattern=p;enemyTurn.definition=&a;
                statusFrames(cmf,p.approach,enemyTurn.walk,&enemyTurn.walkDistance);
                statusFrames(cmf,p.back,enemyTurn.back,&enemyTurn.backDistance);
                statusFrames(cmf,p.rest,enemyTurn.rest,nullptr);
            }
            std::vector<int> motion;
            if(p.index>=0)statusFrames(cmf,p.attack,motion,nullptr);
            if(motion.empty())statusFrames(cmf,enemyAttackPattern[npc*ATTACKPATTERNTOTALDATASIZE],motion,nullptr);
            if(motion.empty())motion.push_back(crewPos[npc*5]);
            enemyTurn.weaponStarts.push_back((int)enemyTurn.motion.size());
            enemyTurn.impacts.push_back((int)enemyTurn.motion.size()+(int)motion.size()/2);
            enemyTurn.motion.insert(enemyTurn.motion.end(),motion.begin(),motion.end());
        }
        const Layout layoutNow=layout();enemyTurn.homeX=(int)(DX*.85f);
        const bool canMove=!enemyTurn.walkDistance.empty()&&enemyTurn.walkDistance.back()>0;
        enemyTurn.attackX=MergeCombat::enemyAttackPosition(enemyTurn.homeX,(float)monsterHeroX(layoutNow),enemyTurn.pattern.range,monsterZoom(layoutNow,npc,cmf),canMove);
        enemyTurn.moves=enemyTurn.attackX<enemyTurn.homeX;
        enemyTurn.prepares=enemyTurn.pattern.index>=0&&enemyTurn.pattern.approach!=enemyAttackPattern[npc*ATTACKPATTERNTOTALDATASIZE];
    }
    const int approach=enemyTurn.moves||enemyTurn.prepares?(int)enemyTurn.walk.size():0;
    const int back=enemyTurn.moves&&enemyTurn.back.empty()?approach:(int)enemyTurn.back.size();
    enemyTurn.phases.begin(approach,(int)enemyTurn.motion.size(),back,std::max(12,(int)enemyTurn.rest.size()));
    if(enemyTurn.impacts.empty())enemyTurn.impacts.push_back(enemyTurn.phases.impact());
    else for(int& frame:enemyTurn.impacts)frame+=approach;
    enemyTurn.time.begin(enemyTurn.phases.end(),enemyTurn.impacts.front(),0,1);
}
