#pragma once

#ifndef _DATA_LIST_H_
#define _DATA_LIST_H_

//tools/content/make_pack.py 가 생성한다. 직접 고치지 말 것.
//
//팩에 들어가는 배열 목록이다. 로더(DataPack.cpp)와 팩 생성기가
//이 하나를 같이 쓰므로 둘이 어긋날 수 없다.
//
//X(이름, 원소크기, 종류, 개수, 콘텐츠키, 폭, 시작번호)
//
//콘텐츠키가 DPK_KEY_NONE 이면 길이가 고정이라 팩과 내장본이 정확히
//같아야 한다. 그 외에는 콘텐츠에 맞춰 길어지는 배열이라, 팩이 더
//길어도 용량 안이면 받는다. 개수 = 개수 / 폭 + 시작번호.

#include "AlphaData.h"
#include "BattleData.h"
#include "CastleData.h"
#include "CmfBlob.h"
#include "CmfData.h"
#include "CollectionData.h"
#include "DemoData.h"
#include "DropData.h"
#include "EnemyData.h"
#include "FontData.h"
#include "GachaData.h"
#include "GameData.h"
#include "HeroData.h"
#include "ImgData.h"
#include "ItemData.h"
#include "MapBlob.h"
#include "MapData.h"
#include "ObjectData.h"
#include "QuestData.h"
#include "RewardData.h"
#include "RouletteData.h"
#include "ShopData.h"
#include "SkillData.h"
#include "TextData.h"
#include "UIData.h"
#include "WaveData.h"

#define DATA_LIST(X) \
	X(demoAlpha, 1, DPK_UINT, 50, DPK_KEY_NONE, 0, 0) \
	X(alphaData, 1, DPK_UINT, 2817, DPK_KEY_NONE, 0, 0) \
	X(alphaX, 2, DPK_UINT, 296, DPK_KEY_NONE, 0, 0) \
	X(alpha2, 2, DPK_INT, 222, DPK_KEY_NONE, 0, 0) \
	X(goldAlphaInfo, 2, DPK_UINT, 444, DPK_KEY_NONE, 0, 0) \
	X(alphaY, 2, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(battleMotion, 4, DPK_INT, 90, DPK_KEY_NONE, 0, 0) \
	X(houseGold, 8, DPK_INT, 12, DPK_KEY_NONE, 0, 0) \
	X(wheelCrewPos, 4, DPK_INT, 10, DPK_KEY_NONE, 0, 0) \
	X(gameEventOpenStage, 2, DPK_UINT, 24, DPK_KEY_NONE, 0, 0) \
	X(activeSkillProb, 4, DPK_INT, activeSkillProb_ROWS * activeSkillProb_COLS, DPK_KEY_NONE, 0, 0) \
	X(popUpFrameData, 4, DPK_FLOAT, 8, DPK_KEY_NONE, 0, 0) \
	X(hitAlpha, 2, DPK_INT, 3, DPK_KEY_NONE, 0, 0) \
	X(raidAlpha, 2, DPK_INT, 3, DPK_KEY_NONE, 0, 0) \
	X(battleData, 4, DPK_INT, 3, DPK_KEY_NONE, 0, 0) \
	X(skillInitData, 4, DPK_INT, 18, DPK_KEY_NONE, 0, 0) \
	X(arenaOff, 2, DPK_UINT, 72, DPK_KEY_NONE, 0, 0) \
	X(arenaMI, 2, DPK_INT, 360, DPK_KEY_NONE, 0, 0) \
	X(arenaMIC, 1, DPK_UINT, 46, DPK_KEY_NONE, 0, 0) \
	X(castleOrder, 4, DPK_INT, 19, DPK_KEY_CASTLE, 1, 0) \
	X(castleBoxColor, 4, DPK_INT, 19, DPK_KEY_CASTLE, 1, 0) \
	X(castleBoxGold, 8, DPK_INT, 19, DPK_KEY_CASTLE, 1, 0) \
	X(castleStarLimit, 4, DPK_INT, 19, DPK_KEY_CASTLE, 1, 0) \
	X(setHeroPos, 4, DPK_INT, 114, DPK_KEY_CASTLE, 6, 0) \
	X(setEnemyPos, 4, DPK_INT, 114, DPK_KEY_CASTLE, 6, 0) \
	X(castleCrewPosition, 4, DPK_INT, 228, DPK_KEY_CASTLE, 12, 0) \
	X(cmfOffBlob, 2, DPK_UINT, 12692, DPK_KEY_FREE, 0, 0) \
	X(cmfOffSlot, 4, DPK_UINT, 429, DPK_KEY_CMF, 1, 0) \
	X(cmfMotionImgBlob, 2, DPK_INT, 306052, DPK_KEY_FREE, 0, 0) \
	X(cmfMotionImgSlot, 4, DPK_UINT, 429, DPK_KEY_CMF, 1, 0) \
	X(cmfMotionImgCntBlob, 2, DPK_UINT, 18002, DPK_KEY_FREE, 0, 0) \
	X(cmfMotionImgCntSlot, 4, DPK_UINT, 429, DPK_KEY_CMF, 1, 0) \
	X(cmfMotionImgSizeBlob, 2, DPK_INT, 36004, DPK_KEY_FREE, 0, 0) \
	X(cmfMotionImgSizeSlot, 4, DPK_UINT, 429, DPK_KEY_CMF, 1, 0) \
	X(cmfCrashSizeBlob, 2, DPK_INT, 72008, DPK_KEY_FREE, 0, 0) \
	X(cmfCrashSizeSlot, 4, DPK_UINT, 429, DPK_KEY_CMF, 1, 0) \
	X(cmfHeroLoopBlob, 2, DPK_UINT, 192, DPK_KEY_FREE, 0, 0) \
	X(cmfHeroLoopSlot, 4, DPK_UINT, 3, DPK_KEY_CMF_HERO, 1, 0) \
	X(cmfMoveInfoBlob, 2, DPK_INT, 49476, DPK_KEY_FREE, 0, 0) \
	X(cmfMoveInfoSlot, 4, DPK_UINT, 429, DPK_KEY_CMF, 1, 0) \
	X(cmfImgOff, 2, DPK_INT, 2145, DPK_KEY_NONE, 0, 0) \
	X(cmfTotalMotion, 2, DPK_UINT, 429, DPK_KEY_NONE, 0, 0) \
	X(cmfTotalOff, 2, DPK_UINT, 429, DPK_KEY_NONE, 0, 0) \
	X(cmfVar, 2, DPK_UINT, 429, DPK_KEY_NONE, 0, 0) \
	X(costumeSize, 2, DPK_UINT, 36, DPK_KEY_NONE, 0, 0) \
	X(costumeOff, 2, DPK_UINT, 600, DPK_KEY_NONE, 0, 0) \
	X(collectionLvLimit, 4, DPK_INT, 24, DPK_KEY_NONE, 0, 0) \
	X(collectionData, 4, DPK_INT, 720, DPK_KEY_NONE, 0, 0) \
	X(collectionsCategoryInfo, 1, DPK_UINT, 72, DPK_KEY_NONE, 0, 0) \
	X(demoData, 2, DPK_INT, 105, DPK_KEY_NONE, 0, 0) \
	X(frameData, 2, DPK_INT, 162, DPK_KEY_NONE, 0, 0) \
	X(demoItem, 2, DPK_UINT, 60, DPK_KEY_NONE, 0, 0) \
	X(boxDropProc, 4, DPK_INT, boxDropProc_ROWS * boxDropProc_COLS, DPK_KEY_NONE, 0, 0) \
	X(proc1, 2, DPK_UINT, 2, DPK_KEY_NONE, 0, 0) \
	X(proc2, 2, DPK_UINT, 3, DPK_KEY_NONE, 0, 0) \
	X(proc3, 2, DPK_UINT, 4, DPK_KEY_NONE, 0, 0) \
	X(proc4, 2, DPK_UINT, 5, DPK_KEY_NONE, 0, 0) \
	X(proc5, 2, DPK_UINT, 6, DPK_KEY_NONE, 0, 0) \
	X(proc6, 2, DPK_UINT, 7, DPK_KEY_NONE, 0, 0) \
	X(proc7, 2, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(proc8, 2, DPK_UINT, 9, DPK_KEY_NONE, 0, 0) \
	X(proc9, 2, DPK_UINT, 10, DPK_KEY_NONE, 0, 0) \
	X(proc10, 2, DPK_UINT, 11, DPK_KEY_NONE, 0, 0) \
	X(proc11, 2, DPK_UINT, 12, DPK_KEY_NONE, 0, 0) \
	X(proc12, 2, DPK_UINT, 13, DPK_KEY_NONE, 0, 0) \
	X(proc13, 2, DPK_UINT, 14, DPK_KEY_NONE, 0, 0) \
	X(proc14, 2, DPK_UINT, 15, DPK_KEY_NONE, 0, 0) \
	X(proc15, 2, DPK_UINT, 16, DPK_KEY_NONE, 0, 0) \
	X(proc16, 2, DPK_UINT, 17, DPK_KEY_NONE, 0, 0) \
	X(proc17, 2, DPK_UINT, 18, DPK_KEY_NONE, 0, 0) \
	X(proc18, 2, DPK_UINT, 19, DPK_KEY_NONE, 0, 0) \
	X(proc19, 2, DPK_UINT, 20, DPK_KEY_NONE, 0, 0) \
	X(proc20, 2, DPK_UINT, 21, DPK_KEY_NONE, 0, 0) \
	X(proc21, 2, DPK_UINT, 22, DPK_KEY_NONE, 0, 0) \
	X(proc22, 2, DPK_UINT, 23, DPK_KEY_NONE, 0, 0) \
	X(proc23, 2, DPK_UINT, 24, DPK_KEY_NONE, 0, 0) \
	X(proc24, 2, DPK_UINT, 25, DPK_KEY_NONE, 0, 0) \
	X(proc25, 2, DPK_UINT, 26, DPK_KEY_NONE, 0, 0) \
	X(proc26, 2, DPK_UINT, 27, DPK_KEY_NONE, 0, 0) \
	X(proc27, 2, DPK_UINT, 28, DPK_KEY_NONE, 0, 0) \
	X(proc28, 2, DPK_UINT, 29, DPK_KEY_NONE, 0, 0) \
	X(proc29, 2, DPK_UINT, 30, DPK_KEY_NONE, 0, 0) \
	X(proc30, 2, DPK_UINT, 31, DPK_KEY_NONE, 0, 0) \
	X(proc31, 2, DPK_UINT, 32, DPK_KEY_NONE, 0, 0) \
	X(proc32, 2, DPK_UINT, 33, DPK_KEY_NONE, 0, 0) \
	X(proc33, 2, DPK_UINT, 34, DPK_KEY_NONE, 0, 0) \
	X(proc34, 2, DPK_UINT, 35, DPK_KEY_NONE, 0, 0) \
	X(monStr, 8, DPK_INT, 500, DPK_KEY_NONE, 0, 0) \
	X(bossHp, 8, DPK_INT, 100, DPK_KEY_NONE, 0, 0) \
	X(bossStr, 8, DPK_INT, 100, DPK_KEY_NONE, 0, 0) \
	X(summonMotion, 2, DPK_INT, 30, DPK_KEY_NONE, 0, 0) \
	X(slimeMotion, 1, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(enemyAttackPattern, 2, DPK_INT, 8620, DPK_KEY_ENEMY, 20, 0) \
	X(enemyIconZoom, 4, DPK_FLOAT, 431, DPK_KEY_ENEMY, 1, 0) \
	X(enemyZoom, 4, DPK_FLOAT, 431, DPK_KEY_ENEMY, 1, 0) \
	X(enemyBossZoom, 4, DPK_FLOAT, 431, DPK_KEY_ENEMY, 1, 0) \
	X(enemyData, 2, DPK_INT, 3448, DPK_KEY_ENEMY, 8, 0) \
	X(enemyStatInfo, 8, DPK_INT, 1293, DPK_KEY_ENEMY, 3, 0) \
	X(enemyAttr, 2, DPK_INT, 5136, DPK_KEY_NONE, 0, 0) \
	X(goldNumData, 2, DPK_UINT, 60, DPK_KEY_NONE, 0, 0) \
	X(largeNumData, 2, DPK_UINT, 40, DPK_KEY_NONE, 0, 0) \
	X(mediumNumData, 2, DPK_UINT, 40, DPK_KEY_NONE, 0, 0) \
	X(itemColorText, 1, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(fontInfo, 2, DPK_INT, 128, DPK_KEY_NONE, 0, 0) \
	X(miniGachaDetailRate, 4, DPK_INT, 8, DPK_KEY_NONE, 0, 0) \
	X(attackSequenceFrameData, 2, DPK_UINT, 7, DPK_KEY_NONE, 0, 0) \
	X(betCoin, 1, DPK_UINT, 5, DPK_KEY_NONE, 0, 0) \
	X(betHeart, 1, DPK_UINT, 7, DPK_KEY_NONE, 0, 0) \
	X(skillUpgradeGold, 8, DPK_INT, 900, DPK_KEY_NONE, 0, 0) \
	X(attrToDebuf, 1, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(attrEffect, 1, DPK_UINT, 120, DPK_KEY_NONE, 0, 0) \
	X(playerMainStat, 1, DPK_UINT, 3, DPK_KEY_NONE, 0, 0) \
	X(zoomData, 1, DPK_UINT, 5, DPK_KEY_NONE, 0, 0) \
	X(debufToAttr, 1, DPK_UINT, 6, DPK_KEY_NONE, 0, 0) \
	X(signCurve, 1, DPK_INT, 16, DPK_KEY_NONE, 0, 0) \
	X(optionInfo, 1, DPK_UINT, 54, DPK_KEY_NONE, 0, 0) \
	X(sin1024, 2, DPK_UINT, 91, DPK_KEY_NONE, 0, 0) \
	X(tan1024, 2, DPK_UINT, 91, DPK_KEY_NONE, 0, 0) \
	X(crewStarUpgradeGold, 8, DPK_INT, 2500, DPK_KEY_NONE, 0, 0) \
	X(crewLvUpgradeGold, 8, DPK_UINT, 1600, DPK_KEY_NONE, 0, 0) \
	X(monXYGap, 2, DPK_INT, 856, DPK_KEY_ENEMY, 2, 3) \
	X(lvUpExp, 8, DPK_INT, 99, DPK_KEY_NONE, 0, 0) \
	X(defaultStat, 4, DPK_INT, 3, DPK_KEY_NONE, 0, 0) \
	X(attackDelayFrame, 4, DPK_INT, 3, DPK_KEY_NONE, 0, 0) \
	X(attackDefaultFrame, 4, DPK_INT, 3, DPK_KEY_NONE, 0, 0) \
	X(attackCountPerOnce, 4, DPK_INT, 3, DPK_KEY_NONE, 0, 0) \
	X(skillEfficiency, 4, DPK_FLOAT, 3, DPK_KEY_NONE, 0, 0) \
	X(dx_walk, 4, DPK_INT, 3, DPK_KEY_NONE, 0, 0) \
	X(walkFrame, 1, DPK_UINT, 4, DPK_KEY_NONE, 0, 0) \
	X(crewBulletLvUpDmgPercent, 4, DPK_INT, 10, DPK_KEY_NONE, 0, 0) \
	X(crewData, 4, DPK_INT, 384, DPK_KEY_CREW, 6, 0) \
	X(jumpUpMotion, 2, DPK_INT, 56, DPK_KEY_NONE, 0, 0) \
	X(jumpDownMotion, 2, DPK_INT, 107, DPK_KEY_NONE, 0, 0) \
	X(backHomeMotion, 2, DPK_INT, 105, DPK_KEY_NONE, 0, 0) \
	X(jump, 1, DPK_INT, 20, DPK_KEY_NONE, 0, 0) \
	X(jumpFullFrame, 2, DPK_INT, 11, DPK_KEY_NONE, 0, 0) \
	X(alphaJumpFrame, 2, DPK_INT, 11, DPK_KEY_NONE, 0, 0) \
	X(jumpFullFrame2, 2, DPK_INT, 7, DPK_KEY_NONE, 0, 0) \
	X(charEtcData, 1, DPK_UINT, 6, DPK_KEY_NONE, 0, 0) \
	X(robinSkillStartFrame, 2, DPK_UINT, 23, DPK_KEY_NONE, 0, 0) \
	X(robinSkillClosingFrame, 2, DPK_UINT, 23, DPK_KEY_NONE, 0, 0) \
	X(dianaSkillStartFrame, 2, DPK_UINT, 23, DPK_KEY_NONE, 0, 0) \
	X(dianaSkillClosingFrame, 2, DPK_UINT, 23, DPK_KEY_NONE, 0, 0) \
	X(maxxSkillStartFrame, 2, DPK_UINT, 22, DPK_KEY_NONE, 0, 0) \
	X(maxxSkillClosingFrame, 2, DPK_UINT, 22, DPK_KEY_NONE, 0, 0) \
	X(robinSkillMotion, 2, DPK_UINT, 8612, DPK_KEY_NONE, 0, 0) \
	X(dianaSkillMotion, 2, DPK_UINT, 7964, DPK_KEY_NONE, 0, 0) \
	X(maxxSkillMotion, 2, DPK_UINT, 3652, DPK_KEY_NONE, 0, 0) \
	X(dianaHelmPos, 1, DPK_INT, 50, DPK_KEY_NONE, 0, 0) \
	X(maxxHelmPos, 1, DPK_INT, 50, DPK_KEY_NONE, 0, 0) \
	X(concentrateMotion, 2, DPK_UINT, 25, DPK_KEY_NONE, 0, 0) \
	X(bombShotMotion, 2, DPK_UINT, 88, DPK_KEY_NONE, 0, 0) \
	X(satelliteShotMotion, 2, DPK_UINT, 240, DPK_KEY_NONE, 0, 0) \
	X(satelliteShotData, 2, DPK_INT, 15, DPK_KEY_NONE, 0, 0) \
	X(hitMarkData, 1, DPK_UINT, 15, DPK_KEY_NONE, 0, 0) \
	X(buffData, 2, DPK_UINT, 52, DPK_KEY_NONE, 0, 0) \
	X(dianaBulletData, 2, DPK_UINT, 35, DPK_KEY_NONE, 0, 0) \
	X(maxxBoomerangData, 2, DPK_INT, 119, DPK_KEY_NONE, 0, 0) \
	X(normalboomerangData, 2, DPK_INT, 64, DPK_KEY_NONE, 0, 0) \
	X(sateliteMotion, 2, DPK_INT, 816, DPK_KEY_NONE, 0, 0) \
	X(levelUpMIC, 1, DPK_UINT, 40, DPK_KEY_NONE, 0, 0) \
	X(debufStartFrame, 4, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(debufEffect, 1, DPK_UINT, 72, DPK_KEY_NONE, 0, 0) \
	X(emoticonRate, 1, DPK_UINT, 26, DPK_KEY_NONE, 0, 0) \
	X(scowlEffect, 1, DPK_INT, 8, DPK_KEY_NONE, 0, 0) \
	X(sweatEffect, 1, DPK_INT, 7, DPK_KEY_NONE, 0, 0) \
	X(questionEffect, 1, DPK_INT, 10, DPK_KEY_NONE, 0, 0) \
	X(surpriseEffect, 1, DPK_INT, 5, DPK_KEY_NONE, 0, 0) \
	X(stunMotion, 2, DPK_UINT, 10, DPK_KEY_NONE, 0, 0) \
	X(equipSlotPos, 2, DPK_INT, 24, DPK_KEY_NONE, 0, 0) \
	X(equipSlotPos2, 2, DPK_INT, 32, DPK_KEY_NONE, 0, 0) \
	X(statueInfo, 1, DPK_UINT, 16, DPK_KEY_NONE, 0, 0) \
	X(deadMotion, 2, DPK_UINT, 24, DPK_KEY_NONE, 0, 0) \
	X(motionData, 2, DPK_UINT, 96, DPK_KEY_NONE, 0, 0) \
	X(imgArray, 2, DPK_UINT, 340, DPK_KEY_NONE, 0, 0) \
	X(neutralOff, 2, DPK_UINT, 32, DPK_KEY_NONE, 0, 0) \
	X(logoOff, 2, DPK_UINT, 80, DPK_KEY_NONE, 0, 0) \
	X(neutralOffset, 1, DPK_INT, 8, DPK_KEY_NONE, 0, 0) \
	X(balloonPos, 1, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(imgTextPos, 1, DPK_INT, 20, DPK_KEY_NONE, 0, 0) \
	X(imgTextFrame, 1, DPK_INT, 22, DPK_KEY_NONE, 0, 0) \
	X(titleOff, 2, DPK_INT, 148, DPK_KEY_NONE, 0, 0) \
	X(effectOff, 2, DPK_INT, 624, DPK_KEY_NONE, 0, 0) \
	X(effectMI, 2, DPK_INT, 4288, DPK_KEY_NONE, 0, 0) \
	X(hitOff, 2, DPK_INT, 220, DPK_KEY_NONE, 0, 0) \
	X(titleMI, 2, DPK_INT, 216, DPK_KEY_NONE, 0, 0) \
	X(tenbytenMI, 2, DPK_INT, 468, DPK_KEY_NONE, 0, 0) \
	X(hitMI, 2, DPK_INT, 2096, DPK_KEY_NONE, 0, 0) \
	X(objOff, 2, DPK_UINT, 1008, DPK_KEY_NONE, 0, 0) \
	X(itemTypeCnt, 2, DPK_UINT, 34, DPK_KEY_NONE, 0, 0) \
	X(swordInfoList, 4, DPK_INT, 4, DPK_KEY_NONE, 0, 0) \
	X(newCardEffect, 2, DPK_INT, 84, DPK_KEY_NONE, 0, 0) \
	X(equipDataType, 4, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(openedItemData, 2, DPK_UINT, 20, DPK_KEY_NONE, 0, 0) \
	X(itemLevelLimit, 1, DPK_UINT, 16, DPK_KEY_NONE, 0, 0) \
	X(itemExpAcce, 4, DPK_INT, 50, DPK_KEY_NONE, 0, 0) \
	X(itemExp, 4, DPK_INT, 224, DPK_KEY_NONE, 0, 0) \
	X(itemMaterialExpAcce, 4, DPK_INT, 50, DPK_KEY_NONE, 0, 0) \
	X(itemMaterialExp, 4, DPK_INT, 225, DPK_KEY_NONE, 0, 0) \
	X(itemEvolutionItem, 8, DPK_INT, 240, DPK_KEY_NONE, 0, 0) \
	X(itemUpgradeHammer, 8, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(revolutionMedal, 2, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(itemColor, 4, DPK_UINT, 10, DPK_KEY_NONE, 0, 0) \
	X(buffBlend, 4, DPK_UINT, 16, DPK_KEY_NONE, 0, 0) \
	X(swordMaxBet, 1, DPK_UINT, 40, DPK_KEY_NONE, 0, 0) \
	X(swordHeart, 1, DPK_UINT, 40, DPK_KEY_NONE, 0, 0) \
	X(swordGold, 8, DPK_INT, 40, DPK_KEY_NONE, 0, 0) \
	X(itemPrice, 8, DPK_UINT, 328, DPK_KEY_NONE, 0, 0) \
	X(itemSellPrice, 4, DPK_UINT, 301, DPK_KEY_NONE, 0, 0) \
	X(itemStar, 2, DPK_UINT, 565, DPK_KEY_NONE, 0, 0) \
	X(itemStartCnt, 2, DPK_UINT, 41, DPK_KEY_NONE, 0, 0) \
	X(boxEquipType, 1, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(materialDropData, 1, DPK_UINT, 270, DPK_KEY_NONE, 0, 0) \
	X(wasteDropData, 1, DPK_UINT, 1215, DPK_KEY_NONE, 0, 0) \
	X(itemValueType, 4, DPK_INT, 20, DPK_KEY_NONE, 0, 0) \
	X(itemValueTypeText, 4, DPK_INT, 20, DPK_KEY_NONE, 0, 0) \
	X(itemEquipSlot, 1, DPK_UINT, 18, DPK_KEY_NONE, 0, 0) \
	X(itemSlotEquip, 1, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(wasteDrop, 1, DPK_UINT, 30, DPK_KEY_NONE, 0, 0) \
	X(wasteValue, 1, DPK_UINT, 7, DPK_KEY_NONE, 0, 0) \
	X(weaponRange, 1, DPK_UINT, 3, DPK_KEY_NONE, 0, 0) \
	X(itemValue, 4, DPK_UINT, 171, DPK_KEY_NONE, 0, 0) \
	X(gradeRatio, 1, DPK_UINT, 6, DPK_KEY_NONE, 0, 0) \
	X(typeRatio, 1, DPK_UINT, 18, DPK_KEY_NONE, 0, 0) \
	X(acceOptionStatMatch, 1, DPK_UINT, 12, DPK_KEY_NONE, 0, 0) \
	X(acceDefaultStatValue, 4, DPK_UINT, 300, DPK_KEY_NONE, 0, 0) \
	X(neckOptionStatValue, 4, DPK_UINT, 1400, DPK_KEY_NONE, 0, 0) \
	X(ringOptionStatValue, 4, DPK_UINT, 900, DPK_KEY_NONE, 0, 0) \
	X(gemOptionStatValue, 4, DPK_UINT, 300, DPK_KEY_NONE, 0, 0) \
	X(itemUpgradeValue, 4, DPK_UINT, 2592, DPK_KEY_NONE, 0, 0) \
	X(itemRatio, 1, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(itemPow, 2, DPK_UINT, 220, DPK_KEY_NONE, 0, 0) \
	X(itemLv, 1, DPK_UINT, 144, DPK_KEY_NONE, 0, 0) \
	X(itemStat, 1, DPK_UINT, 144, DPK_KEY_NONE, 0, 0) \
	X(enchantData, 4, DPK_UINT, 4320, DPK_KEY_NONE, 0, 0) \
	X(itemCooltime, 1, DPK_UINT, 23, DPK_KEY_NONE, 0, 0) \
	X(itemIconTable, 2, DPK_UINT, 447, DPK_KEY_NONE, 0, 0) \
	X(neckOption, 4, DPK_UINT, 168, DPK_KEY_NONE, 0, 0) \
	X(neckRingDefaultValue, 4, DPK_INT, 300, DPK_KEY_NONE, 0, 0) \
	X(ringOption, 1, DPK_INT, 126, DPK_KEY_NONE, 0, 0) \
	X(optionRange, 4, DPK_INT, 366, DPK_KEY_NONE, 0, 0) \
	X(optionValue, 1, DPK_INT, 61, DPK_KEY_NONE, 0, 0) \
	X(setItem, 1, DPK_UINT, 1302, DPK_KEY_NONE, 0, 0) \
	X(setOption, 4, DPK_INT, 1404, DPK_KEY_NONE, 0, 0) \
	X(legendItem, 4, DPK_UINT, 648, DPK_KEY_NONE, 0, 0) \
	X(optionStat, 1, DPK_INT, 79, DPK_KEY_NONE, 0, 0) \
	X(option_prefix, 1, DPK_INT, 128, DPK_KEY_NONE, 0, 0) \
	X(option_suffix, 1, DPK_INT, 128, DPK_KEY_NONE, 0, 0) \
	X(option_count_prefix, 1, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(option_count_suffix, 1, DPK_UINT, 8, DPK_KEY_NONE, 0, 0) \
	X(gemOption, 1, DPK_UINT, 81, DPK_KEY_NONE, 0, 0) \
	X(gemPrice, 4, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(enchantRate, 4, DPK_INT, 300, DPK_KEY_NONE, 0, 0) \
	X(extraSetItem, 1, DPK_UINT, 576, DPK_KEY_NONE, 0, 0) \
	X(newItemReward, 4, DPK_INT, 684, DPK_KEY_NONE, 0, 0) \
	X(upgradeCostCrew, 4, DPK_INT, upgradeCostCrew_ROWS * upgradeCostCrew_COLS, DPK_KEY_NONE, 0, 0) \
	X(upgradeCostEquip, 4, DPK_INT, upgradeCostEquip_ROWS * upgradeCostEquip_COLS, DPK_KEY_NONE, 0, 0) \
	X(mapPtrBlob, 1, DPK_UINT, 246959, DPK_KEY_FREE, 0, 0) \
	X(mapPtrIdx, 4, DPK_UINT, 426, DPK_KEY_MAP, 1, -1) \
	X(mapTilePtrBlob, 1, DPK_UINT, 246959, DPK_KEY_FREE, 0, 0) \
	X(mapTilePtrIdx, 4, DPK_UINT, 426, DPK_KEY_MAP, 1, -1) \
	X(mapRectPtrBlob, 1, DPK_UINT, 1058, DPK_KEY_FREE, 0, 0) \
	X(mapRectPtrIdx, 4, DPK_UINT, 426, DPK_KEY_MAP, 1, -1) \
	X(mapBackPtrBlob, 2, DPK_INT, 15581, DPK_KEY_FREE, 0, 0) \
	X(mapBackPtrIdx, 4, DPK_UINT, 426, DPK_KEY_MAP, 1, -1) \
	X(mapObjPtrBlob, 2, DPK_INT, 1963, DPK_KEY_FREE, 0, 0) \
	X(mapObjPtrIdx, 4, DPK_UINT, 426, DPK_KEY_MAP, 1, -1) \
	X(mapNeutralPtrBlob, 2, DPK_INT, 981, DPK_KEY_FREE, 0, 0) \
	X(mapNeutralPtrIdx, 4, DPK_UINT, 426, DPK_KEY_MAP, 1, -1) \
	X(mapEnemyPtrBlob, 2, DPK_UINT, 505, DPK_KEY_FREE, 0, 0) \
	X(mapEnemyPtrIdx, 4, DPK_UINT, 426, DPK_KEY_MAP, 1, -1) \
	X(mapRectSize, 4, DPK_UINT, 425, DPK_KEY_MAP, 1, 0) \
	X(mapBackSize, 4, DPK_UINT, 425, DPK_KEY_MAP, 1, 0) \
	X(mapObjSize, 4, DPK_UINT, 425, DPK_KEY_MAP, 1, 0) \
	X(mapNeutralSize, 4, DPK_UINT, 425, DPK_KEY_MAP, 1, 0) \
	X(mapEnemySize, 4, DPK_UINT, 425, DPK_KEY_MAP, 1, 0) \
	X(mapColor, 4, DPK_UINT, 19, DPK_KEY_NONE, 0, 0) \
	X(doorToKey, 1, DPK_INT, 16, DPK_KEY_NONE, 0, 0) \
	X(doorArray, 1, DPK_UINT, 40, DPK_KEY_NONE, 0, 0) \
	X(pushArray, 1, DPK_UINT, 2, DPK_KEY_NONE, 0, 0) \
	X(boxStar, 1, DPK_UINT, 56, DPK_KEY_NONE, 0, 0) \
	X(boxArray, 1, DPK_UINT, 4, DPK_KEY_NONE, 0, 0) \
	X(markArray, 1, DPK_UINT, 7, DPK_KEY_NONE, 0, 0) \
	X(itemArray, 1, DPK_UINT, 6, DPK_KEY_NONE, 0, 0) \
	X(dianaStoneArray, 1, DPK_UINT, 1, DPK_KEY_NONE, 0, 0) \
	X(magmaArray, 1, DPK_UINT, 1, DPK_KEY_NONE, 0, 0) \
	X(wormHoleArray, 1, DPK_UINT, 3, DPK_KEY_NONE, 0, 0) \
	X(warpArrayType, 1, DPK_UINT, 57, DPK_KEY_NONE, 0, 0) \
	X(warpArray, 2, DPK_INT, 280, DPK_KEY_NONE, 0, 0) \
	X(backObjImg, 2, DPK_UINT, 1148, DPK_KEY_NONE, 0, 0) \
	X(bgObjOff, 2, DPK_UINT, 656, DPK_KEY_NONE, 0, 0) \
	X(bgObjMI, 2, DPK_INT, 3220, DPK_KEY_NONE, 0, 0) \
	X(sunShineOff, 2, DPK_UINT, 24, DPK_KEY_NONE, 0, 0) \
	X(sunShineMI, 2, DPK_INT, 504, DPK_KEY_NONE, 0, 0) \
	X(sunShineMIC, 1, DPK_UINT, 44, DPK_KEY_NONE, 0, 0) \
	X(sateliteMotionCnt, 1, DPK_UINT, 62, DPK_KEY_NONE, 0, 0) \
	X(neutralData, 2, DPK_INT, 506, DPK_KEY_NONE, 0, 0) \
	X(mapBg, 2, DPK_UINT, 76, DPK_KEY_NONE, 0, 0) \
	X(waterfallMI, 2, DPK_INT, 48, DPK_KEY_NONE, 0, 0) \
	X(atlanticeImg, 2, DPK_UINT, 80, DPK_KEY_NONE, 0, 0) \
	X(swampImg, 2, DPK_UINT, 52, DPK_KEY_NONE, 0, 0) \
	X(swampSplash, 1, DPK_INT, 56, DPK_KEY_NONE, 0, 0) \
	X(swampBubble, 1, DPK_UINT, 164, DPK_KEY_NONE, 0, 0) \
	X(sunShineMotion, 1, DPK_INT, 48, DPK_KEY_NONE, 0, 0) \
	X(sewageFallHeight, 1, DPK_UINT, 10, DPK_KEY_NONE, 0, 0) \
	X(tileEmpty, 1, DPK_UINT, 1672, DPK_KEY_NONE, 0, 0) \
	X(objMI, 2, DPK_INT, 5408, DPK_KEY_NONE, 0, 0) \
	X(levelUpMI, 2, DPK_INT, 244, DPK_KEY_NONE, 0, 0) \
	X(objectData, 2, DPK_INT, 423, DPK_KEY_NONE, 0, 0) \
	X(boxNeutralAnimation, 1, DPK_INT, 4, DPK_KEY_NONE, 0, 0) \
	X(boxOpenAnimation, 1, DPK_INT, 20, DPK_KEY_NONE, 0, 0) \
	X(boxOpenItemFrameInfo, 4, DPK_FLOAT, 378, DPK_KEY_NONE, 0, 0) \
	X(goldQuestBox, 4, DPK_INT, 10, DPK_KEY_NONE, 0, 0) \
	X(goldQuestNpc, 4, DPK_INT, 10, DPK_KEY_NONE, 0, 0) \
	X(goldQuestZokboIcon, 4, DPK_INT, 21, DPK_KEY_NONE, 0, 0) \
	X(goldQuestZokboValue, 4, DPK_FLOAT, 10, DPK_KEY_NONE, 0, 0) \
	X(goldQuestResultItem, 4, DPK_INT, 30, DPK_KEY_NONE, 0, 0) \
	X(goldQuestReward, 8, DPK_INT, 150, DPK_KEY_NONE, 0, 0) \
	X(pvpQuestInfo, 4, DPK_UINT, 510, DPK_KEY_NONE, 0, 0) \
	X(pvpQuestRequest, 4, DPK_UINT, 5040, DPK_KEY_NONE, 0, 0) \
	X(pvpQuestReward, 8, DPK_UINT, 20280, DPK_KEY_NONE, 0, 0) \
	X(questRequestItem, 4, DPK_UINT, 496, DPK_KEY_NONE, 0, 0) \
	X(questRequestItemCntData, 8, DPK_UINT, 900, DPK_KEY_NONE, 0, 0) \
	X(questReward, 8, DPK_UINT, 3600, DPK_KEY_NONE, 0, 0) \
	X(questInfo, 4, DPK_INT, 108, DPK_KEY_NONE, 0, 0) \
	X(goldQuestDotPosition, 4, DPK_INT, 60, DPK_KEY_NONE, 0, 0) \
	X(goldQuestZoomData, 4, DPK_FLOAT, 20, DPK_KEY_NONE, 0, 0) \
	X(battleRewardMedal, 4, DPK_INT, 7, DPK_KEY_NONE, 0, 0) \
	X(battleRewardGold, 8, DPK_INT, 80, DPK_KEY_NONE, 0, 0) \
	X(bossGold, 8, DPK_INT, 100, DPK_KEY_NONE, 0, 0) \
	X(raidRewardMedal, 4, DPK_INT, 7, DPK_KEY_NONE, 0, 0) \
	X(stageClearBox, 8, DPK_INT, 51, DPK_KEY_NONE, 0, 0) \
	X(levelUpCategory, 4, DPK_INT, 9, DPK_KEY_NONE, 0, 0) \
	X(levelUpReward, 8, DPK_INT, 200, DPK_KEY_NONE, 0, 0) \
	X(stageClearReward, 8, DPK_INT, 1200, DPK_KEY_NONE, 0, 0) \
	X(equipGetRewardHeart, 8, DPK_INT, 432, DPK_KEY_NONE, 0, 0) \
	X(crewReward, 8, DPK_UINT, 140, DPK_KEY_NONE, 0, 0) \
	X(crewGetReward, 4, DPK_UINT, 132, DPK_KEY_NONE, 0, 0) \
	X(bossReward, 8, DPK_INT, 400, DPK_KEY_NONE, 0, 0) \
	X(calendarPos, 4, DPK_INT, 32, DPK_KEY_NONE, 0, 0) \
	X(calendarMonthlyRewardDay, 4, DPK_INT, 4, DPK_KEY_NONE, 0, 0) \
	X(calendarInfo1Month, 8, DPK_INT, 120, DPK_KEY_NONE, 0, 0) \
	X(calendarInfo1Week, 8, DPK_INT, 40, DPK_KEY_NONE, 0, 0) \
	X(collectionReward, 4, DPK_INT, 96, DPK_KEY_NONE, 0, 0) \
	X(rouletteAttackStr, 1, DPK_UINT, 324, DPK_KEY_NONE, 0, 0) \
	X(rouletteRaidStr, 1, DPK_UINT, 28, DPK_KEY_NONE, 0, 0) \
	X(attackDelayPerType, 4, DPK_INT, 9, DPK_KEY_NONE, 0, 0) \
	X(currencyShop, 4, DPK_INT, 126, DPK_KEY_NONE, 0, 0) \
	X(quickShopData, 1, DPK_UINT, 162, DPK_KEY_NONE, 0, 0) \
	X(skillData, 4, DPK_INT, 6666, DPK_KEY_SKILL, 29, 0) \
	X(barrierEtcData, 2, DPK_UINT, 15, DPK_KEY_NONE, 0, 0) \
	X(berserkEtcData, 2, DPK_UINT, 15, DPK_KEY_NONE, 0, 0) \
	X(skillToStat, 1, DPK_INT, 7, DPK_KEY_NONE, 0, 0) \
	X(skillDescMod, 1, DPK_UINT, 27, DPK_KEY_NONE, 0, 0) \
	X(crewBulletAni, 1, DPK_UINT, 78, DPK_KEY_NONE, 0, 0) \
	X(areaName, 4, DPK_INT, 15, DPK_KEY_NONE, 0, 0) \
	X(unicode_table, 2, DPK_UINT, 2350, DPK_KEY_NONE, 0, 0) \
	X(itemNameStart, 2, DPK_UINT, 39, DPK_KEY_NONE, 0, 0) \
	X(alphaOff, 2, DPK_UINT, 499, DPK_KEY_NONE, 0, 0) \
	X(alertText, 2, DPK_INT, 9, DPK_KEY_NONE, 0, 0) \
	X(colorSet, 4, DPK_INT, 52, DPK_KEY_NONE, 0, 0) \
	X(currencyIcon, 2, DPK_UINT, 10, DPK_KEY_NONE, 0, 0) \
	X(solidPosition, 4, DPK_INT, 8, DPK_KEY_NONE, 0, 0) \
	X(openFrame, 4, DPK_INT, 7, DPK_KEY_NONE, 0, 0) \
	X(statIcon, 2, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(menuOpened, 1, DPK_UINT, 24, DPK_KEY_NONE, 0, 0) \
	X(listMenuIcon, 2, DPK_UINT, 22, DPK_KEY_NONE, 0, 0) \
	X(crewPos, 2, DPK_INT, 2155, DPK_KEY_ENEMY, 5, 0) \
	X(enemyIconPos, 2, DPK_INT, 1293, DPK_KEY_ENEMY, 3, 0) \
	X(enemyBigIconPos, 2, DPK_INT, 1293, DPK_KEY_ENEMY, 3, 0) \
	X(enemySkillIconPos, 2, DPK_INT, 1293, DPK_KEY_ENEMY, 3, 0) \
	X(cardImgBg, 2, DPK_INT, 114, DPK_KEY_NONE, 0, 0) \
	X(equipIconPos, 4, DPK_INT, 12, DPK_KEY_NONE, 0, 0) \
	X(runMotion, 4, DPK_INT, 4, DPK_KEY_NONE, 0, 0) \
	X(curtainPosX, 4, DPK_INT, 240, DPK_KEY_NONE, 0, 0) \
	X(raidEquipPos, 2, DPK_INT, 12, DPK_KEY_NONE, 0, 0) \
	X(scrollDx, 4, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(cardFrameColorData, 4, DPK_INT, 60, DPK_KEY_NONE, 0, 0) \
	X(colorData, 4, DPK_INT, 56, DPK_KEY_NONE, 0, 0) \
	X(activeSkillCardBg, 4, DPK_INT, 21, DPK_KEY_NONE, 0, 0) \
	X(mainMenuWidth, 2, DPK_UINT, 5, DPK_KEY_NONE, 0, 0) \
	X(titleMIC, 2, DPK_UINT, 6, DPK_KEY_NONE, 0, 0) \
	X(effectMIC, 2, DPK_UINT, 556, DPK_KEY_NONE, 0, 0) \
	X(hitMIC, 2, DPK_UINT, 102, DPK_KEY_NONE, 0, 0) \
	X(objMIC, 2, DPK_UINT, 604, DPK_KEY_NONE, 0, 0) \
	X(bgObjMIC, 2, DPK_UINT, 402, DPK_KEY_NONE, 0, 0) \
	X(palette, 1, DPK_UINT, 2048, DPK_KEY_NONE, 0, 0) \
	X(blindFrame, 1, DPK_UINT, 9, DPK_KEY_NONE, 0, 0) \
	X(alertData, 2, DPK_UINT, 45, DPK_KEY_NONE, 0, 0) \
	X(skillTreePos, 2, DPK_UINT, 360, DPK_KEY_NONE, 0, 0) \
	X(fontGradiation, 4, DPK_UINT, 21, DPK_KEY_NONE, 0, 0) \
	X(enemyWinPos, 2, DPK_INT, 8, DPK_KEY_NONE, 0, 0) \
	X(shakePosX, 4, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(shakePosY, 4, DPK_INT, 6, DPK_KEY_NONE, 0, 0) \
	X(selectColor, 4, DPK_UINT, 4, DPK_KEY_NONE, 0, 0) \
	X(goldQuestPositionData, 4, DPK_INT, 20, DPK_KEY_NONE, 0, 0) \
	X(boss, 4, DPK_INT, 18, DPK_KEY_NONE, 0, 0) \
	X(wave, 4, DPK_INT, 90000, DPK_KEY_NONE, 0, 0) \
	X(stageGold, 8, DPK_INT, 1000, DPK_KEY_NONE, 0, 0) \
	/* 끝 */

#endif
