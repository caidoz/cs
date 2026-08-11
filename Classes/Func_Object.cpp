#include "Core.h"
#include "Func.h"
#include "Data.h"

// Object ±×¸®±â °ü·Ã
void GetMotionPtr(OBJECT* pObj)
{
	switch (pObj->cmf) {
	case ROBIN:
		skillStartFrame = robinSkillStartFrame;
		skillClosingFrame = robinSkillClosingFrame;
		skillMotion = robinSkillMotion;

		break;
	case DIANA:
		skillStartFrame = dianaSkillStartFrame;
		skillClosingFrame = dianaSkillClosingFrame;

		skillMotion = dianaSkillMotion;
		break;
	case MAXX:
		skillStartFrame = maxxSkillStartFrame;
		skillClosingFrame = maxxSkillClosingFrame;

		skillMotion = maxxSkillMotion;
		break;
	}
}

void EraseCmf(OBJECT* pObj)
{
	int i;

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active && pObj != &ao[i] && cmfLoaded[ao[i].cmf] == enemyData[pObj->type * ENEMYDATASIZE])
			return;
	}

	cmfLoaded[pObj->cmf] = -1;
}

void DrawObj(OBJECT* pObj)
{
	int i;
	int obj = GetObjFromPtr(pObj);
	int tempGrayScale;

	if (obj < ITEMOBJ) {
		if (pObj->zoom >= 2) {
			//¼®È­
		}

		if (obj >= PLAYER && obj < PLAYERALL && pObj->dead == true && pObj->drawHandler != REGENDRAW)
			grayScale = 32;

		if (pObj->attacked)
			SetBlend(Max(0, (pObj->attackedFrame - 2) << 2), 0xCCCCCC);

		if (pObj->debuf[POISON])
			SetBlend(8 + Abs(3 - (pObj->debuf[POISON] % 5)) * 4, 0x006600);

		if (pObj->debuf[CURSE])
			SetBlend(8 + Abs(3 - (pObj->debuf[CURSE] % 5)) * 4, 0x330066);

		if (pObj->debuf[SLOW])
			grayScale = 24;

		if (pObj->debuf[STUN])
			grayScale = 32;

		//Æ¼¾î¸Ë °ËÀº»ö ÀÔÈ÷±â
		if (pObj->type == ENEMY_BAHAMUT
			|| pObj->type == ENEMY_BAHAMUT_RED
			|| pObj->type == ENEMY_BAHAMUT_BLUE
			|| pObj->type == ENEMY_BAHAMUT_PURPLE
			|| pObj->type == ENEMY_BAHAMUT_GREEN
			|| pObj->type == ENEMY_BAHAMUT_GOLD
			|| pObj->type == ENEMY_BAHAMUT_BLACK)
			SetBlend(pObj->mainFrame, 0x000000);
	}

	i = pObj->x;

#ifndef INVINCIBLE
	if (pObj->attackedFrame > 1 && obj >= ENEMY)
		switch (pObj->type) {
		case OBJ_BOX:
			if (pObj->status != BOXSTATUS_APPEAR)
				//	pObj->y += 2 * DIR(pObj->attackedFrame % 2) * _2X;
				//else
				pObj->x += 4 * DIR(pObj->attackedFrame % 2) * _2X;
			break;
		default:
			pObj->x += 4 * DIR(pObj->attackedFrame % 2) * _2X;
			break;
		}

#endif

	switch (pObj->drawHandler) {
	case PLAYERDRAW:
		tempGrayScale = grayScale;
		//if (pObj->moveHandler == CUTOFFMOVE)
		if ((obj == DIANA || obj == MAXX) && IsGetHero(obj) == false)
			grayScale = 32;
		PlayerDraw(pObj);
		grayScale = tempGrayScale;
		break;
	case NORMALDRAW:
		NormalDraw(pObj);
		break;
	case BULLETLASERDRAW:
		BulletLaserDraw(pObj);
		break;
	case BULLETGUIDEDDRAW:
		BulletGuidedDraw(pObj);
		break;
	case BULLETSATELITEDRAW:
		BulletSateliteDraw(pObj);
		break;
	case BULLETHEALDRAW:
		BulletHealDraw(pObj);
		break;
	case BULLETBOOMERANGDRAW:
		BulletBoomerangDraw(pObj);
		break;
	case BULLETITEMDRAW:
		BulletItemDraw(pObj);
		break;
	case BULLETCREWDRAW:
		BulletCrewDraw(pObj);
		break;
	case CREWDRAW:

		//¾ÆÁ÷ ·¹º§¾÷ÀÌ ¾ÈµÇ¾î ÀÖ°Å³ª °ø°Ý¹ÞÀº »óÅÂ¸é
		//if (pObj->curStar < pObj->maxStar || !pObj->maxStar)
		//{
		//	grayScale = 32;
		//}
		EnemyDraw(pObj);
		//grayScale = 0;

		if (pObj->curStar < pObj->maxStar)
		{
			DrawEffect(DEBUF_STUN0 + frame % 6, pObj->x, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + 0 * _2X - ry - OBJIMGGAP), pObj->dirX, false, pObj->zoom);
		}
		break;
	case ENEMYDRAW:

		if ((pObj->type == ENEMY_FOGRA
			|| pObj->type == ENEMY_FOGRA_RED
			|| pObj->type == ENEMY_FOGRA_BLUE
			|| pObj->type == ENEMY_FOGRA_PURPLE
			|| pObj->type == ENEMY_FOGRA_GREEN
			|| pObj->type == ENEMY_FOGRA_GOLD
			|| pObj->type == ENEMY_FOGRA_BLACK)
			&& pObj->motion >= PO_C40_SHOT0 && pObj->motion <= PO_C40_SHOT11) {
			SetAlpha(pObj->frame * 8);
			EnemyDraw(pObj);
			SetAlpha(32);
		}
		else {
			EnemyDraw(pObj);
		}
		//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ö±ï¿½
		switch (pObj->type) {
		case ENEMY_CASTLE_BOSS2:
		case ENEMY_CASTLE_BOSS2_RED:
		case ENEMY_CASTLE_BOSS2_BLUE:
		case ENEMY_CASTLE_BOSS2_PURPLE:
		case ENEMY_CASTLE_BOSS2_GREEN:
		case ENEMY_CASTLE_BOSS2_GOLD:
		case ENEMY_CASTLE_BOSS2_BLACK:
		case ENEMY_MAMMOTH:
		case ENEMY_MAMMOTH_RED:
		case ENEMY_MAMMOTH_BLUE:
		case ENEMY_MAMMOTH_PURPLE:
		case ENEMY_MAMMOTH_GREEN:
		case ENEMY_MAMMOTH_GOLD:
		case ENEMY_MAMMOTH_BLACK:
			if (pObj->moveHandler == ENEMYMOVE) {
				ShieldBarDraw(pObj->shield, pObj->shieldMax, pObj->x - rx - (SIMPLEHPBARWIDTH / 2), STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + pObj->cpy - 30 * _2X * pObj->zoom) - ry, pObj->zoom, COLOR_SKY);
			}
			break;
		case ENEMY_CASTLE_BOSS1:
		case ENEMY_CASTLE_BOSS1_RED:
		case ENEMY_CASTLE_BOSS1_BLUE:
		case ENEMY_CASTLE_BOSS1_PURPLE:
		case ENEMY_CASTLE_BOSS1_GREEN:
		case ENEMY_CASTLE_BOSS1_GOLD:
		case ENEMY_CASTLE_BOSS1_BLACK:
			//if (pObj->moveHandler == DEBRIONARMMOVE && pObj->jumpFrame > 0) {
			if (pObj->moveHandler == DEBRIONARMMOVE) {
				switch (Abs(GetObjFromPtr(pObj) - pObj->mom)) {
				case 1:
					SimpleHpBarDraw(pObj->hp, pObj->maxhp, pObj->x - rx - (48 * _2X), STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 48 * _2X) - ry, pObj->zoom, ENEMYHPBARCOLOR);
					break;
				case 2:
					SimpleHpBarDraw(pObj->hp, pObj->maxhp, pObj->x - rx + (28 * _2X), STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 48 * _2X) - ry, pObj->zoom, ENEMYHPBARCOLOR);
					break;
				case 3:
					SimpleHpBarDraw(pObj->hp, pObj->maxhp, pObj->x - rx - (48 * _2X), STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + 32 * _2X) - ry, pObj->zoom, ENEMYHPBARCOLOR);
					break;
				case 4:
					SimpleHpBarDraw(pObj->hp, pObj->maxhp, pObj->x - rx + (28 * _2X), STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + 32 * _2X) - ry, pObj->zoom, ENEMYHPBARCOLOR);
					break;
				}

				//MemRect(pObj->x - rx - (pObj->dirX == LEFT ? 73 * _2X : 0), STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y) - ry, 48 * _2X, 4 * _2X, 0xCC0000, cvtDest, cvtLayer, buffering);
				//MemRect(pObj->x - rx - (pObj->dirX == LEFT ? 73 * _2X : 0), STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y) - ry, pObj->hp * 48 * _2X / pObj->maxhp, 4 * _2X, 0x00FF00, cvtDest, cvtLayer, buffering);
				if (pObj->jumpFrame > 0)
					pObj->jumpFrame--;
			}
			else if (pObj->moveHandler == DEBRIONBODYMOVE) {
				SimpleHpBarDraw(pObj->hp, pObj->maxhp, pObj->x - rx - (float)(SIMPLEHPBARWIDTH + 2 * _2X) / 2, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + 8 * _2X) - ry, pObj->zoom, ENEMYHPBARCOLOR);
			}
			break;
		case ENEMY_CASTLE_BOSS3:
		case ENEMY_CASTLE_BOSS3_RED:
		case ENEMY_CASTLE_BOSS3_BLUE:
		case ENEMY_CASTLE_BOSS3_PURPLE:
		case ENEMY_CASTLE_BOSS3_GREEN:
		case ENEMY_CASTLE_BOSS3_GOLD:
		case ENEMY_CASTLE_BOSS3_BLACK:
			if (pObj->moveHandler == FOLLOWMOMMOVE && pObj->jumpFrame > 0) {
				SimpleHpBarDraw(pObj->hp, pObj->maxhp, pObj->x - rx + 54 * _2X, pObj->y - ry + (pObj->motion == PO_C50_UPSKIN ? -130 * _2X : 0), pObj->zoom, ENEMYHPBARCOLOR);

				//MemRect(pObj->x - rx + 40 * _2X, pObj->y - ry + (pObj->motion == PO_C50_UPSKIN ? -130 * _2X : 0), 48 * _2X, 4 * _2X, 0xCC0000, cvtDest, cvtLayer, buffering);
				//MemRect(pObj->x - rx + 40 * _2X, pObj->y - ry + (pObj->motion == PO_C50_UPSKIN ? -130 * _2X : 0), pObj->hp * 48 * _2X / pObj->maxhp, 4 * _2X, 0x00FF00, cvtDest, cvtLayer, buffering);
				pObj->jumpFrame--;
			}
			else if (pObj->moveHandler == BUGMOVE && pObj->attackFrame > 0) {
				SimpleHpBarDraw(pObj->hp, pObj->maxhp, pObj->x - rx - 10 * _2X, pObj->y - ry - 20 * _2X, pObj->zoom, ENEMYHPBARCOLOR);

				//MemRect(pObj->x - rx - 10 * _2X, pObj->y - ry - 20 * _2X, 24 * _2X, 4 * _2X, 0xCC0000, cvtDest, cvtLayer, buffering);
				//MemRect(pObj->x - rx - 10 * _2X, pObj->y - ry - 20 * _2X, pObj->hp * 24 * _2X / pObj->maxhp, 4 * _2X, 0x00FF00, cvtDest, cvtLayer, buffering);
				pObj->attackFrame--;
			}
			break;

		}

		//MemRect(xOffset + pObj->x - rx - (float)(SIMPLEHPBARWIDTH + 2 * _2X) / 2, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y - ry - OBJIMGGAP - 0 * _2X, (float)(SIMPLEHPBARWIDTH + 2 * _2X), (float)(SIMPLEHPBARHEIGHT + 2 * _2X), COLOR_NAVY, cvtDest, cvtLayer, buffering);
		//MemRect(xOffset + pObj->x - rx - (float)(SIMPLEHPBARWIDTH) / 2, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y - ry - OBJIMGGAP - 1 * _2X, 24 * _2X * pObj->hp / pObj->maxhp, (float)(SIMPLEHPBARHEIGHT), ENEMYHPBARCOLOR, cvtDest, cvtLayer, buffering);

		break;
	case CLOUDDRAW:
		CloudDraw(pObj);
		break;
	case SPIDERDRAW:
		SpiderDraw(pObj);
		break;
	case SKELDRAW:
		SkelDraw(pObj);
		break;
	case MACHINEDRAW:
		MachineDraw(pObj);
		break;
	case LASERDRAW:
		LaserDraw(pObj);
		break;
	case GHOSTDRAW:
		GhostDraw(pObj);
		break;
	case VANISHDRAW:
		VanishDraw(pObj);
		break;
	case REGENDRAW:
		RegenDraw(pObj);
		break;
	case NEUTRALDRAW:
		NeutralDraw(pObj);
		break;
	case BOXDRAW:
		BoxDraw(pObj);
		break;
	}

	pObj->x = i;

	grayScale = 0;
	UnSetBlend();

	if (obj < NEUTRAL) {

		//¼Ó¼º Å¸°ÝÈ¿°ú
		if (pObj->attr && pObj->moveHandler < BULLET3WAYMOVE) {
			int aType = pObj->attr % 10;
			int aFrame = pObj->attr / 10;

			if (aType == FROST) {
				switch (aFrame) {
				case 3:
					SetBlend(32, COLOR_WHITE);
					break;
				case 4:
					SetBlend(24, COLOR_WHITE);
					break;
				case 5:
					SetBlend(16, COLOR_WHITE);
					break;
				default:
					aFrame = Max(6, aFrame - 5);
					break;
				}
			}

			aType--;
			DrawEffect(attrEffect[aType * 20 + aFrame], pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);
			UnSetBlend();
		}

		//µð¹öÇÁ È¿°ú
		i = 0;

		do {
			int dMotion = debufEffect[i * 12 + ((debufStartFrame[i] - pObj->debuf[i]) / MOTIONDIV) % 12];

			if (pObj->debuf[i] && dMotion > 0)
				DrawEffect(dMotion, xOffset + pObj->x - rx +
					(((pObj->type == ENEMY_CASTLE_BOSS3
						|| pObj->type == ENEMY_CASTLE_BOSS3_RED
						|| pObj->type == ENEMY_CASTLE_BOSS3_BLUE
						|| pObj->type == ENEMY_CASTLE_BOSS3_PURPLE
						|| pObj->type == ENEMY_CASTLE_BOSS3_GREEN
						|| pObj->type == ENEMY_CASTLE_BOSS3_GOLD
						|| pObj->type == ENEMY_CASTLE_BOSS3_BLACK)
						&& pObj->moveHandler != BUGMOVE) ? (float)35 * _2X * pObj->zoom : 0 * _2X), STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + (i == SLOW ? Abs(3 - (float)(pObj->debuf[SLOW] % 5) * _2X * pObj->zoom) - 4 * _2X * pObj->zoom : 0) - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);

			i++;
		} while (i < TOTALDEBUF);

		SetAlpha(32);
	}

	//ï¿½æµ¹ï¿½ï¿½ï¿½ï¿½ ï¿½×¸ï¿½ï¿½ï¿½
#ifdef GUIDELINE
	MemRectFrame(xOffset + pObj->x + pObj->cpx - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + pObj->cpy - ry - OBJIMGGAP), pObj->cx, pObj->cy, 0xFFFF00);
	MemRectFrame(xOffset + pObj->x + pObj->apx - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + pObj->apy - ry - OBJIMGGAP), pObj->ax, pObj->ay, 0xFF0000);
#endif
}

void DrawPlayer(OBJECT* pObj, int motion, int x, int y, int dirF, float zoom, float rotation, bool center, bool shadow)
{
	int i, fixedImg;
	int costume;
	int type;
	int imgFile = 0;
	int dx;
	int imgFileE = 0;
	const signed short* cPtr;
	int obj = GetObjFromPtr(pObj);
	int tempAlpha = m_lgrpAlpha;
	int tempZoom = zoom;
	int centerX = 0;
	int centerY = 0;

	if (shadow == true)
		ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x - (float)(12 * _2X) * zoom, y + (float)(8 * _2X) * zoom, SHADOW_IMG, zoom);

	if (motion >= 2000) {
		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		i = levelUpMIC[(motion - 2000) * 2 + 1];
		cPtr = &levelUpMI[levelUpMIC[(motion - 2000) * 2] * 4];
	}
	else if (motion >= 1000) {
		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		i = sateliteMotionCnt[(motion - 1000) * 2 + 1];
		cPtr = &sateliteMotion[sateliteMotionCnt[(motion - 1000) * 2] * 4];
	}
	else {
		i = cmd_m_cnt[pObj->cmf][motion * 2 + 1];
		cPtr = &cmd_m_img[pObj->cmf][cmd_m_cnt[pObj->cmf][motion * 2] * 4];
	}

	do {
		int imgOffsetX = 0;
		int imgOffsetY = 0;
		float magnify;
		int dirX;
		int tempAlpha = m_lgrpAlpha;
		int tempAlpha2 = m_lgrpAlpha;
		int pxl;
		int partsRotation = 0;

		int extra = false;
		const unsigned short* ucPtr;

		fixedImg = *cPtr;
		type = *(cPtr + 3);

		//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
		magnify = ((type >> 6) + 1) * zoom;

		//¹æÇâ
		dirX = (dirF + type) % 2;

		//¹ÝÅõ¸í °ª
//Åõ¸íµµ »ó´ëÁ¶Àý
		if (type & 0x30) {
			tempAlpha = (tempAlpha * (4 - ((type & 0x30) >> 4))) >> 2;
		}

		if (!tempAlpha)
			continue;

		//¶óÀÌÆ° È¿°úÀÎÁö ÃßÃâ
		if (type & 0x08)
			pxl = 1;
		else
			pxl = 0;

		imgFile = ROBIN_PART_IMG + pObj->type * ROBIN_IMG_CNT;

		switch (pObj->cmf) {
		case ROBIN:
			if (fixedImg < IMG_C0_62)
				imgFile = COMMON_CMF_IMG;
			else if (fixedImg < IMG_C0_65) {
				//costume = pObj->equipImg[EQUIP_ARMOR] == EMPTY ? 0 : pObj->equipImg[EQUIP_ARMOR] * TOTALGRADE + pObj->equip[EQUIP_ARMOR].grade;
				costume = pObj->equip[EQUIP_ARMOR].type == EMPTY ? 0 : pObj->equip[EQUIP_ARMOR].detail + 1;
				imgFile = COSTUME_ARMOR_ROBIN_IMG + costume;
			}
			else if (fixedImg < IMG_C0_67) {
				//costume = pObj->equipImg[EQUIP_PANTS] == EMPTY ? 0 : pObj->equipImg[EQUIP_PANTS] * TOTALGRADE + pObj->equip[EQUIP_PANTS].grade;
				costume = pObj->equip[EQUIP_PANTS].type == EMPTY ? 0 : pObj->equip[EQUIP_PANTS].detail + 1;
				imgFile = COSTUME_PANTS_ROBIN_IMG + costume;
			}
			else if (fixedImg < IMG_C0_72) {
				imgFile = MONSTER_IMG;
				extra = true;
			}
			else if (fixedImg < IMG_C0_95) {
				//costume = pObj->equipImg[EQUIP_GLOVE] == EMPTY ? 0 : pObj->equipImg[EQUIP_GLOVE] * TOTALGRADE + pObj->equip[EQUIP_GLOVE].grade;
				costume = pObj->equip[EQUIP_GLOVE].type == EMPTY ? 0 : pObj->equip[EQUIP_GLOVE].detail + 1;
				imgFile = COSTUME_GLOVE_ROBIN_IMG + costume;

			}
			else if (fixedImg < IMG_C0_106) {
				//costume = pObj->equipImg[EQUIP_BOOTS] == EMPTY ? 0 : pObj->equipImg[EQUIP_BOOTS] * TOTALGRADE + pObj->equip[EQUIP_BOOTS].grade;
				costume = pObj->equip[EQUIP_BOOTS].type == EMPTY ? 0 : pObj->equip[EQUIP_BOOTS].detail + 1;
				imgFile = COSTUME_BOOTS_ROBIN_IMG + costume;
			}
			else if (fixedImg < IMG_C0_108) {
				//costume = pObj->equipImg[EQUIP_HELM] == EMPTY ? 0 : pObj->equipImg[EQUIP_HELM] * TOTALGRADE + pObj->equip[EQUIP_HELM].grade;
				costume = pObj->equip[EQUIP_HELM].type == EMPTY ? 0 : pObj->equip[EQUIP_HELM].detail + 1;
				imgFile = COSTUME_HELM_ROBIN_IMG + costume;
				extra = true;
			}
			else if (fixedImg < IMG_C0_110) {
				//costume = pObj->equipImg[EQUIP_WEAPON] == EMPTY ? 0 : pObj->equipImg[EQUIP_WEAPON] * TOTALGRADE + pObj->equip[EQUIP_WEAPON].grade;
				costume = pObj->equip[EQUIP_WEAPON].type == EMPTY ? 0 : pObj->equip[EQUIP_WEAPON].detail + 1;
				imgFile = COSTUME_WEAPON_ROBIN_IMG + costume;
			}
			else if (fixedImg < IMG_C0_151)
				imgFile = WEAPON_EFFECT_IMG;
			else
				imgFile = HIT_IMG;
			break;
		case DIANA:
			if (fixedImg < IMG_C1_45)
				imgFile = COMMON_CMF_IMG;
			else if (fixedImg < IMG_C1_48) {
				//costume = pObj->equipImg[EQUIP_ARMOR] == EMPTY ? 0 : pObj->equipImg[EQUIP_ARMOR] * TOTALGRADE + pObj->equip[EQUIP_ARMOR].grade;
				costume = pObj->equip[EQUIP_ARMOR].type == EMPTY ? 0 : pObj->equip[EQUIP_ARMOR].detail + 1;
				imgFile = COSTUME_ARMOR_DIANA_IMG + costume;
			}
			else if (fixedImg < IMG_C1_50) {
				//costume = pObj->equipImg[EQUIP_PANTS] == EMPTY ? 0 : pObj->equipImg[EQUIP_PANTS] * TOTALGRADE + pObj->equip[EQUIP_PANTS].grade;
				costume = pObj->equip[EQUIP_PANTS].type == EMPTY ? 0 : pObj->equip[EQUIP_PANTS].detail + 1;
				imgFile = COSTUME_PANTS_DIANA_IMG + costume;
			}
			else if (fixedImg < IMG_C1_64) {
				imgFile = MONSTER_IMG + DIANA;

				if (fixedImg < IMG_C1_55)
					extra = true;
			}
			else if (fixedImg < IMG_C1_80) {
				//costume = pObj->equipImg[EQUIP_GLOVE] == EMPTY ? 0 : pObj->equipImg[EQUIP_GLOVE] * TOTALGRADE + pObj->equip[EQUIP_GLOVE].grade;
				costume = pObj->equip[EQUIP_GLOVE].type == EMPTY ? 0 : pObj->equip[EQUIP_GLOVE].detail + 1;
				imgFile = COSTUME_GLOVE_DIANA_IMG + costume;
			}
			else if (fixedImg < IMG_C1_92) {
				//costume = pObj->equipImg[EQUIP_BOOTS] == EMPTY ? 0 : pObj->equipImg[EQUIP_BOOTS] * TOTALGRADE + pObj->equip[EQUIP_BOOTS].grade;
				costume = pObj->equip[EQUIP_BOOTS].type == EMPTY ? 0 : pObj->equip[EQUIP_BOOTS].detail + 1;
				imgFile = COSTUME_BOOTS_DIANA_IMG + costume;
			}
			else if (fixedImg < IMG_C1_94) {
				//costume = pObj->equipImg[EQUIP_HELM] == EMPTY ? 0 : pObj->equipImg[EQUIP_HELM] * TOTALGRADE + pObj->equip[EQUIP_HELM].grade;
				costume = pObj->equip[EQUIP_HELM].type == EMPTY ? 0 : pObj->equip[EQUIP_HELM].detail + 1;
				imgFile = COSTUME_HELM_DIANA_IMG + costume;
				extra = true;
			}
			else if (fixedImg < IMG_C1_96) {
				//costume = pObj->equipImg[EQUIP_WEAPON] == EMPTY ? 0 : pObj->equipImg[EQUIP_WEAPON] * TOTALGRADE + pObj->equip[EQUIP_WEAPON].grade;
				costume = pObj->equip[EQUIP_WEAPON].type == EMPTY ? 0 : pObj->equip[EQUIP_WEAPON].detail + 1;
				imgFile = COSTUME_WEAPON_DIANA_IMG + costume;
			}
			else
				imgFile = WEAPON_EFFECT_IMG;
			break;
		case MAXX:
			if (fixedImg < IMG_C2_44)
				imgFile = COMMON_CMF_IMG;
			else if (fixedImg < IMG_C2_47) {
				//costume = pObj->equipImg[EQUIP_ARMOR] == EMPTY ? 0 : pObj->equipImg[EQUIP_ARMOR] * TOTALGRADE + pObj->equip[EQUIP_ARMOR].grade;
				costume = pObj->equip[EQUIP_ARMOR].type == EMPTY ? 0 : pObj->equip[EQUIP_ARMOR].detail + 1;
				imgFile = COSTUME_ARMOR_MAXX_IMG + costume;
			}
			else if (fixedImg < IMG_C2_49) {
				//costume = pObj->equipImg[EQUIP_PANTS] == EMPTY ? 0 : pObj->equipImg[EQUIP_PANTS] * TOTALGRADE + pObj->equip[EQUIP_PANTS].grade;
				costume = pObj->equip[EQUIP_PANTS].type == EMPTY ? 0 : pObj->equip[EQUIP_PANTS].detail + 1;
				imgFile = COSTUME_PANTS_MAXX_IMG + costume;
			}
			else if (fixedImg < IMG_C2_54) {
				imgFile = MONSTER_IMG + MAXX;
				extra = true;
			}
			else if (fixedImg < IMG_C2_66) {
				//costume = pObj->equipImg[EQUIP_GLOVE] == EMPTY ? 0 : pObj->equipImg[EQUIP_GLOVE] * TOTALGRADE + pObj->equip[EQUIP_GLOVE].grade;
				costume = pObj->equip[EQUIP_GLOVE].type == EMPTY ? 0 : pObj->equip[EQUIP_GLOVE].detail + 1;
				imgFile = COSTUME_GLOVE_MAXX_IMG + costume;
			}
			else if (fixedImg < IMG_C2_80) {
				//costume = pObj->equipImg[EQUIP_BOOTS] == EMPTY ? 0 : pObj->equipImg[EQUIP_BOOTS] * TOTALGRADE + pObj->equip[EQUIP_BOOTS].grade;
				costume = pObj->equip[EQUIP_BOOTS].type == EMPTY ? 0 : pObj->equip[EQUIP_BOOTS].detail + 1;
				imgFile = COSTUME_BOOTS_MAXX_IMG + costume;
			}
			else if (fixedImg < IMG_C2_82) {
				//costume = pObj->equipImg[EQUIP_HELM] == EMPTY ? 0 : pObj->equipImg[EQUIP_HELM] * TOTALGRADE + pObj->equip[EQUIP_HELM].grade;
				costume = pObj->equip[EQUIP_HELM].type == EMPTY ? 0 : pObj->equip[EQUIP_HELM].detail + 1;
				imgFile = COSTUME_HELM_MAXX_IMG + costume;
				extra = true;
			}
			else if (fixedImg < IMG_C2_84) {
				if (pObj->drawHandler == BULLETBOOMERANGDRAW) {
					//costume = ao[ao[obj].target].equipImg[EQUIP_WEAPON] == EMPTY ? 0 : ao[ao[obj].target].equipImg[EQUIP_WEAPON] * TOTALGRADE + ao[ao[obj].target].equip[EQUIP_WEAPON].grade;
					costume = ao[ao[obj].target].equip[EQUIP_WEAPON].type == EMPTY ? 0 : ao[ao[obj].target].equip[EQUIP_WEAPON].detail + 1;
				}
				else {
					//costume = pObj->equipImg[EQUIP_WEAPON] == EMPTY ? 0 : pObj->equipImg[EQUIP_WEAPON] * TOTALGRADE + pObj->equip[EQUIP_WEAPON].grade;
					costume = pObj->equip[EQUIP_WEAPON].type == EMPTY ? 0 : pObj->equip[EQUIP_WEAPON].detail + 1;
				}

				imgFile = COSTUME_WEAPON_MAXX_IMG + costume;

				if (fixedImg == IMG_C2_82 && boomerangAway[GetObjFromPtr(pObj)]) {
					cPtr += 4;
					i--;
					continue;
				}
			}
			else
				imgFile = WEAPON_EFFECT_IMG;
			break;
		}

		if (sprite[imgFile] == 0) {
			cPtr += 4;
			i--;
			continue;
		}

		ucPtr = &cmd_i_offset[pObj->cmf][fixedImg * 4];

		dx = cmd_i_offset[pObj->cmf][fixedImg * 4 + 2];

		switch (type & 0x06) {
		case _00:
			partsRotation = 0;
			break;
		case _09:
			partsRotation = 90;
			if (dirF == RIGHT) {
				dx = cmd_i_offset[pObj->cmf][fixedImg * 4 + 3];
			}
			break;
		case _18:
			partsRotation = 180;
			break;
		case _27:
			partsRotation = 270;
			if (dirF == RIGHT) {
				dx = cmd_i_offset[pObj->cmf][fixedImg * 4 + 3];
			}
			break;
		}

		if (extra && pObj->head) {
			magnify *= 2;
			imgOffsetY = -*(ucPtr + 3) * zoom;
			extra = 2;
		}

		else
			extra = 1;



		if (*(cPtr + 2) == -128 * _2X) {
			imgOffsetY = y % (int)((float)32 * _2X * zoom) + (float)32 * _2X * zoom;

			do {
				DrawImage(
					*(ucPtr + 2), *(ucPtr + 3), *ucPtr, *(ucPtr + 1),
					x + (dirF == 0 ?
						((float)(*(cPtr + 1) + centerX) * zoom * extra * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * extra * sin(CC_DEGREES_TO_RADIANS(rotation))) :
						((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * extra * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * extra * sin(CC_DEGREES_TO_RADIANS(rotation)))
						) + imgOffsetX,
					y - (float)128 * _2X * zoom + imgOffsetY - (dirF == 0 ?
						((float)(*(cPtr + 1) + centerX) * zoom * extra * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * extra * cos(CC_DEGREES_TO_RADIANS(rotation))) :
						((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * extra * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * extra * cos(CC_DEGREES_TO_RADIANS(rotation)))
						),
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

				imgOffsetY += (float)32 * _2X * zoom;
			} while (imgOffsetY < DY + (float)32 * _2X * zoom);
		}
		else {
			DrawImage(
				*(ucPtr + 2), *(ucPtr + 3), *ucPtr, *(ucPtr + 1),
				x + (dirF == 0 ?
					((float)(*(cPtr + 1) + centerX) * zoom * extra * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * extra * sin(CC_DEGREES_TO_RADIANS(rotation))) :
					((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * extra * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * extra * sin(CC_DEGREES_TO_RADIANS(rotation)))
					) + imgOffsetX,
				y - (dirF == 0 ?
					((float)(*(cPtr + 1) + centerX) * zoom * extra * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * extra * cos(CC_DEGREES_TO_RADIANS(rotation))) :
					((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * extra * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * extra * cos(CC_DEGREES_TO_RADIANS(rotation)))
					) + imgOffsetY,
				dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

		}

		//±â¸ðÀ¸´Â ÀÌÆåÆ®
		if (imgFile == ROBIN_PART_IMG + ROBIN_IMG_WEAPON && motion >= PO_C0_A0 && motion <= PO_C0_A11 && concentrateMotion[pObj->concentrate]) {
			SetAlpha(4 + pObj->concentrate);
			DrawPlayer(pObj, (pObj->concentrate == 24 ? PO_C0_CONCENTRATE5 + robin.playtime % 3 : concentrateMotion[pObj->concentrate]) + ((motion >= PO_C0_A8) ? 8 : 0), x - DIR(dirF) * (*(cPtr + 1) * zoom * extra + imgOffsetX), imgOffsetY, dirF, zoom, false, false, false);
			SetAlpha(32);
		}

		cPtr += 4;
		i--;
	} while (i > 0);

	//¸»Ç³¼± ±×¸®±â
}

void DrawPlayerIcon(int type, int x, int y, int zoom)
{
	clipX3 = clipX;
	clipY3 = clipY;
	clipX4 = clipX2;
	clipY4 = clipY2;

	DrawFrame(x, y, 24 * _2X * zoom, 20 * _2X * zoom, FRAME_SHOPBALLOON);
	SetSectionClip(x + 2 * _2X, y - 2 * _2X, 24 * _2X * zoom - 4 * _2X, 20 * _2X * zoom - 4 * _2X, false);
	ao[type].head = true;
	DrawPlayer(&ao[type], 0, x + 2 * _2X + 14 * _2X * zoom, y - 32 * _2X * zoom, LEFT, zoom, false, false, false);
	ao[type].head = false;
	UnSectionClip(false);

	clipX = clipX3;
	clipY = clipY3;
	clipX2 = clipX4;
	clipY2 = clipY4;

}

void DrawCmf(OBJECT* pObj, float rotation, float zoom, bool center)
{
	int i, fixedImg, j;
	int type;
	int imgFile = 0;
	int y = pObj->y;
	int dx;
	int centerX = 0;
	int centerY = 0;

	const signed short* cPtr;

	i = cmd_m_cnt[pObj->cmf][pObj->motion * 2 + 1];
	cPtr = &cmd_m_img[pObj->cmf][cmd_m_cnt[pObj->cmf][pObj->motion * 2] * 4];

	if (center == true) {
		centerX = -(cmfMotionImgSize[pObj->cmf][pObj->motion * 4 + 0] + (cmfMotionImgSize[pObj->cmf][pObj->motion * 4 + 2] / 2));
		centerY = -(cmfMotionImgSize[pObj->cmf][pObj->motion * 4 + 1] + (cmfMotionImgSize[pObj->cmf][pObj->motion * 4 + 3] / 2));
	}

	do {
		int imgOffsetX = 0;
		int imgOffsetY = 0;
		float magnify;
		int dirX;
		int tempAlpha = m_lgrpAlpha;
		int tempAlpha2 = m_lgrpAlpha;
		int pxl;
		int partsRotation = 0;

		fixedImg = *cPtr;
		type = *(cPtr + 3);

		//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
		magnify = ((type >> 6) + 1) * zoom;

		//¹æÇâ
		dirX = (pObj->dirF + type) % 2;

		//¹ÝÅõ¸í °ª
//Åõ¸íµµ »ó´ëÁ¶Àý
		if (type & 0x30) {
			tempAlpha = (tempAlpha * (4 - ((type & 0x30) >> 4))) >> 2;
		}

		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½×¸ï¿½ï¿½Ê¿ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (!tempAlpha) {
		}
		else {
			//¶óÀÌÆ° È¿°úÀÎÁö ÃßÃâ
			if (type & 0x08)
				pxl = 1;
			else
				pxl = 0;

			imgFile = COMMON_CMF_IMG;
			j = 0;

			while (j < 3 && fixedImg >= cmf_i_div[pObj->cmf][j * 2]) {
				imgFile = cmf_i_div[pObj->cmf][j * 2 + 1];
				j++;
			}

			dx = cmd_i_offset[pObj->cmf][fixedImg * 4 + 2];

			switch (type & 0x06) {
			case _00:
				partsRotation = 0;
				break;
			case _09:
				partsRotation = 90;
				if (pObj->dirF == RIGHT) {
					dx = cmd_i_offset[pObj->cmf][fixedImg * 4 + 3];
				}
				break;
			case _18:
				partsRotation = 180;
				break;
			case _27:
				partsRotation = 270;
				if (pObj->dirF == RIGHT) {
					dx = cmd_i_offset[pObj->cmf][fixedImg * 4 + 3];
				}
				break;
			}


			switch (pObj->type) {
			case ENEMY_DEATH:
			case ENEMY_DEATH_RED:
			case ENEMY_DEATH_BLUE:
			case ENEMY_DEATH_PURPLE:
			case ENEMY_DEATH_GREEN:
			case ENEMY_DEATH_GOLD:
			case ENEMY_DEATH_BLACK:
				if (pObj->etc > DEATH_BROKEN && fixedImg == IMG_C31_24) {
					i--;
					cPtr += 4;
					continue;
				}
				break;
			case ENEMY_MAMMOTH:
			case ENEMY_MAMMOTH_RED:
			case ENEMY_MAMMOTH_BLUE:
			case ENEMY_MAMMOTH_PURPLE:
			case ENEMY_MAMMOTH_GREEN:
			case ENEMY_MAMMOTH_GOLD:
			case ENEMY_MAMMOTH_BLACK:
				if (pObj->etc > MAMMOTH_BREAK1 && (fixedImg == IMG_C21_17 || fixedImg == IMG_C21_18 || fixedImg == IMG_C21_9 || fixedImg == IMG_C21_21 || fixedImg == IMG_C21_22 || fixedImg == IMG_C21_23)) {
					i--;
					cPtr += 4;
					continue;
				}
				else if (pObj->etc > MAMMOTH_BREAK0 && (fixedImg == IMG_C21_17 || fixedImg == IMG_C21_18)) {
					i--;
					cPtr += 4;
					continue;
				}
				break;
			case NPC_DELPIOS:
				if (fixedImg == IMG_C95_13 || fixedImg == IMG_C95_14) {
					j = 0;

					imgOffsetX = pObj->x - rx;
					imgOffsetY = STATUSWIN_Y + (rh - 4) * TSIZE + y - ry + OBJIMGGAP;

					do {
						if (pObj->dirF == LEFT)
							DrawImage(
								cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
								xOffset + ((float)(*(cPtr + 1) + centerX) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
								-((float)(*(cPtr + 1) + centerX) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
								dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
						else
							DrawImage(
								cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
								xOffset + ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
								-((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
								dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

						imgOffsetX += 82 * _2X * magnify;
						imgOffsetY += 1 * _2X * magnify;
					} while (imgOffsetX < DX);
				}
				break;
			case NPC_LABETH:
			case ENEMY_LABETH:
			case ENEMY_LABETH_RED:
			case ENEMY_LABETH_BLUE:
			case ENEMY_LABETH_PURPLE:
			case ENEMY_LABETH_GREEN:
			case ENEMY_LABETH_GOLD:
			case ENEMY_LABETH_BLACK:
				if (fixedImg == IMG_C109_30 || fixedImg == IMG_C109_31) {
					j = 0;
					imgOffsetX = pObj->x - rx;
					imgOffsetY = STATUSWIN_Y + (rh - 4) * TSIZE + y - ry + OBJIMGGAP;

					do {

						if (pObj->dirF == LEFT)
							DrawImage(
								cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
								xOffset + ((float)(*(cPtr + 1) + centerX) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
								-((float)(*(cPtr + 1) + centerX) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
								dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
						else
							DrawImage(
								cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
								xOffset + ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
								-((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
								dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);


						imgOffsetY -= cmd_i_offset[pObj->cmf][fixedImg * 4 + 3] * magnify;

					} while (imgOffsetY > -STATUSWIN_Y);

					imgOffsetY = 0;
				}
				break;
			case NPC_ELEIN:
			case NPC_AUSTIN:
				if ((pObj->type == NPC_ELEIN && fixedImg == IMG_C111_15) || (pObj->type == NPC_AUSTIN && fixedImg == IMG_C121_12)) {
					j = 0;
					imgOffsetX = pObj->x - rx;
					imgOffsetY = STATUSWIN_Y + (rh - 4) * TSIZE + y - ry + OBJIMGGAP;

					do {
						imgOffsetY -= 96 * _2X * magnify;

						if (pObj->dirF == LEFT)
							DrawImage(
								cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
								xOffset + ((float)(*(cPtr + 1) + centerX) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
								-((float)(*(cPtr + 1) + centerX) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
								dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
						else
							DrawImage(
								cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
								xOffset + ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
								-((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
								dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

					} while (imgOffsetY > DY + 96 * _2X);

					imgOffsetY = 0;
				}
				break;
			case ENEMY_FOGRA:
			case ENEMY_FOGRA_RED:
			case ENEMY_FOGRA_BLUE:
			case ENEMY_FOGRA_PURPLE:
			case ENEMY_FOGRA_GREEN:
			case ENEMY_FOGRA_GOLD:
			case ENEMY_FOGRA_BLACK:
				if (fixedImg == IMG_C40_19 && (pObj->etc == FOGRA_MOVE || pObj->etc == FOGRA_NEUTRAL)) {
					if (ao[NearPlayer(pObj)].active == true)
						imgOffsetX += Min((ao[NearPlayer(pObj)].x - pObj->x) / 10, 22) * _2X * magnify;
				}
				break;
			case ENEMY_BAHAMUT:
			case ENEMY_BAHAMUT_RED:
			case ENEMY_BAHAMUT_BLUE:
			case ENEMY_BAHAMUT_PURPLE:
			case ENEMY_BAHAMUT_GREEN:
			case ENEMY_BAHAMUT_GOLD:
			case ENEMY_BAHAMUT_BLACK:
				if (fixedImg >= IMG_C43_25 || (fixedImg == IMG_C43_8 || fixedImg == IMG_C43_9)) {
					UnSetBlend();
				}
				break;
			case ENEMY_CASTLE_BOSS3:
			case ENEMY_CASTLE_BOSS3_RED:
			case ENEMY_CASTLE_BOSS3_BLUE:
			case ENEMY_CASTLE_BOSS3_PURPLE:
			case ENEMY_CASTLE_BOSS3_GREEN:
			case ENEMY_CASTLE_BOSS3_GOLD:
			case ENEMY_CASTLE_BOSS3_BLACK:
				if (fixedImg == IMG_C50_31 || fixedImg == IMG_C50_32) {
					imgOffsetX = pObj->x - rx + (1 - 2 * pObj->dirX) * (*(cPtr + 1) * magnify - 14 * _2X);
					if (pObj->dirX == LEFT) {

						do {
							imgOffsetX -= (1 - 2 * pObj->dirX) * 80 * _2X * magnify;

							if (pObj->dirF == LEFT)
								DrawImage(
									cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
									xOffset + ((float)(*(cPtr + 1) + centerX) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
									-((float)(*(cPtr + 1) + centerX) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
									dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
							else
								DrawImage(
									cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
									xOffset + ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
									-((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
									dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
						} while (imgOffsetX > 0);
					}
					else {
						do {
							imgOffsetX -= (1 - 2 * pObj->dirX) * 80 * _2X * magnify;

							if (pObj->dirF == LEFT)
								DrawImage(
									cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
									xOffset + ((float)(*(cPtr + 1) + centerX) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
									-((float)(*(cPtr + 1) + centerX) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
									dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
							else
								DrawImage(
									cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
									xOffset + ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
									-((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
									dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
						} while (imgOffsetX < DX);
					}
					imgOffsetX = 0;
				}
				break;
			case ENEMY_CASTLE_BOSS4:
			case ENEMY_CASTLE_BOSS4_RED:
			case ENEMY_CASTLE_BOSS4_BLUE:
			case ENEMY_CASTLE_BOSS4_PURPLE:
			case ENEMY_CASTLE_BOSS4_GREEN:
			case ENEMY_CASTLE_BOSS4_GOLD:
			case ENEMY_CASTLE_BOSS4_BLACK:

				// ÇÃ·¹ÀÌ¾î ÇÑ¹ø´õ ±×¸®°í ¼Õ°¡¶ôÀ» ±×¸°´Ù
				if (fixedImg == IMG_C51_39) {
					DrawPlayer(&ao[NearPlayer(pObj)], ao[NearPlayer(pObj)].motion, ao[NearPlayer(pObj)].x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (ao[raidPlayer].y - OBJIMGGAP) - ry, ao[NearPlayer(pObj)].dirF, ao[NearPlayer(pObj)].zoom, false, false, false);
				}
				break;
			}
		}

		if (!((pObj->type == NPC_LABETH || pObj->type == ENEMY_LABETH || pObj->type == ENEMY_LABETH_RED || pObj->type == ENEMY_LABETH_BLUE || pObj->type == ENEMY_LABETH_PURPLE || pObj->type == ENEMY_LABETH_GREEN || pObj->type == ENEMY_LABETH_GOLD || pObj->type == ENEMY_LABETH_BLACK) && (fixedImg == IMG_C109_30 || fixedImg == IMG_C109_31))) {
			imgOffsetX = pObj->x - rx;

			if (pObj->dirF == LEFT)
				DrawImage(
					cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
					xOffset + ((float)(*(cPtr + 1) + centerX) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
					STATUSWIN_Y + (rh - 4) * TSIZE - y + OBJIMGGAP - ry - ((float)(*(cPtr + 1) + centerX) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
			else
				DrawImage(
					cmd_i_offset[pObj->cmf][fixedImg * 4 + 2], cmd_i_offset[pObj->cmf][fixedImg * 4 + 3], cmd_i_offset[pObj->cmf][fixedImg * 4], cmd_i_offset[pObj->cmf][fixedImg * 4 + 1],
					xOffset + ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
					STATUSWIN_Y + (rh - 4) * TSIZE - y + OBJIMGGAP - ry - ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
		}

		cPtr += 4;
		i--;
	} while (i > 0);

	if (pObj->type == ENEMY_BAHAMUT
		|| pObj->type == ENEMY_BAHAMUT_RED
		|| pObj->type == ENEMY_BAHAMUT_BLUE
		|| pObj->type == ENEMY_BAHAMUT_PURPLE
		|| pObj->type == ENEMY_BAHAMUT_GREEN
		|| pObj->type == ENEMY_BAHAMUT_GOLD
		|| pObj->type == ENEMY_BAHAMUT_BLACK)
		UnSetBlend();
}

void DrawCmfDetail(int cmf, int motion, int x, int y, int dirF, float zoom, float rotation, bool center)
{
	int i, fixedImg, j;
	int type;
	int imgFile = 0;
	int dx;
	int centerX = 0;
	int centerY = 0;

	const signed short* cPtr;

	//cmf °¡ ÀÛÀ¸¸é 
	if (cmf < TOTALCHAR) {
		DrawPlayer(&ao[cmf], motion, x, y, ao[cmf].dirF, zoom, rotation, center, false);
		return;
	}

	i = cmd_m_cnt[cmf][motion * 2 + 1];
	cPtr = &cmd_m_img[cmf][cmd_m_cnt[cmf][motion * 2] * 4];

	if (center == true) {
		centerX = -(cmfMotionImgSize[cmf][motion * 4 + 0] + (cmfMotionImgSize[cmf][motion * 4 + 2] / 2));
		centerY = -(cmfMotionImgSize[cmf][motion * 4 + 1] + (cmfMotionImgSize[cmf][motion * 4 + 3] / 2));
	}

	do {
		int imgOffsetX = 0;
		int imgOffsetY = 0;
		float magnify;
		int dirX;
		int tempAlpha = m_lgrpAlpha;
		int tempAlpha2 = m_lgrpAlpha;
		int pxl;
		int partsRotation = 0;


		fixedImg = *cPtr;
		type = *(cPtr + 3);

		//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
		magnify = ((type >> 6) + 1) * zoom;

		//¹æÇâ
		dirX = (dirF + type) % 2;
		//ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½

		//¹ÝÅõ¸í °ª
		//Åõ¸íµµ »ó´ëÁ¶Àý
		if (type & 0x30) {
			tempAlpha = (tempAlpha * (4 - ((type & 0x30) >> 4))) >> 2;
		}

		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½×¸ï¿½ï¿½Ê¿ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (!tempAlpha) {
		}
		else {
			//¶óÀÌÆ° È¿°úÀÎÁö ÃßÃâ
			if (type & 0x08)
				pxl = 1;
			else
				pxl = 0;

			imgFile = COMMON_CMF_IMG;
			j = 0;

			while (j < 3 && fixedImg >= cmf_i_div[cmf][j * 2]) {
				imgFile = cmf_i_div[cmf][j * 2 + 1];
				j++;
			}

			dx = cmd_i_offset[cmf][fixedImg * 4 + 2];

			switch (type & 0x06) {
			case _00:
				partsRotation = 0;
				break;
			case _09:
				partsRotation = 90;
				if (dirF == RIGHT) {
					dx = cmd_i_offset[cmf][fixedImg * 4 + 3];
				}
				break;
			case _18:
				partsRotation = 180;
				break;
			case _27:
				partsRotation = 270;
				if (dirF == RIGHT) {
					dx = cmd_i_offset[cmf][fixedImg * 4 + 3];
				}
				break;
			}

			if (dirF == LEFT)
				DrawImage(
					cmd_i_offset[cmf][fixedImg * 4 + 2], cmd_i_offset[cmf][fixedImg * 4 + 3], cmd_i_offset[cmf][fixedImg * 4], cmd_i_offset[cmf][fixedImg * 4 + 1],
					x + ((float)(*(cPtr + 1) + centerX) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
					y - ((float)(*(cPtr + 1) + centerX) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
			else
				DrawImage(
					cmd_i_offset[cmf][fixedImg * 4 + 2], cmd_i_offset[cmf][fixedImg * 4 + 3], cmd_i_offset[cmf][fixedImg * 4], cmd_i_offset[cmf][fixedImg * 4 + 1],
					x + ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
					y - ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

		}
		cPtr += 4;
		i--;
	} while (i > 0);
}


void DrawCmfDetailScale(int cmf, int motion, int x, int y, int dirF, float zoomX, float zoomY, float rotation, bool center)
{
	int i, fixedImg, j;
	int type;
	int imgFile = 0;
	int dx;
	int centerX = 0;
	int centerY = 0;
	float zoom = zoomX;

	const signed short* cPtr;

	//cmf °¡ ÀÛÀ¸¸é 
	if (cmf < TOTALCHAR) {
		DrawPlayer(&ao[cmf], motion, x, y, ao[cmf].dirF, zoom, rotation, center, false);
		return;
	}

	i = cmd_m_cnt[cmf][motion * 2 + 1];
	cPtr = &cmd_m_img[cmf][cmd_m_cnt[cmf][motion * 2] * 4];

	if (center == true) {
		centerX = -(cmfMotionImgSize[cmf][motion * 4 + 0] + (cmfMotionImgSize[cmf][motion * 4 + 2] / 2));
		centerY = -(cmfMotionImgSize[cmf][motion * 4 + 1] + (cmfMotionImgSize[cmf][motion * 4 + 3] / 2));
	}

	do {
		int imgOffsetX = 0;
		int imgOffsetY = 0;
		float magnify;
		int dirX;
		int tempAlpha = m_lgrpAlpha;
		int tempAlpha2 = m_lgrpAlpha;
		int pxl;
		int partsRotation = 0;


		fixedImg = *cPtr;
		type = *(cPtr + 3);

		//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
		magnify = ((type >> 6) + 1) * zoom;

		//¹æÇâ
		dirX = (dirF + type) % 2;
		//ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½

		//¹ÝÅõ¸í °ª
		//Åõ¸íµµ »ó´ëÁ¶Àý
		if (type & 0x30) {
			tempAlpha = (tempAlpha * (4 - ((type & 0x30) >> 4))) >> 2;
		}

		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½×¸ï¿½ï¿½Ê¿ï¿½ ï¿½ï¿½ï¿½ï¿½
		if (!tempAlpha) {
		}
		else {
			//¶óÀÌÆ° È¿°úÀÎÁö ÃßÃâ
			if (type & 0x08)
				pxl = 1;
			else
				pxl = 0;

			imgFile = COMMON_CMF_IMG;
			j = 0;

			while (j < 3 && fixedImg >= cmf_i_div[cmf][j * 2]) {
				imgFile = cmf_i_div[cmf][j * 2 + 1];
				j++;
			}

			dx = cmd_i_offset[cmf][fixedImg * 4 + 2];

			switch (type & 0x06) {
			case _00:
				partsRotation = 0;
				break;
			case _09:
				partsRotation = 90;
				if (dirF == RIGHT) {
					dx = cmd_i_offset[cmf][fixedImg * 4 + 3];
				}
				break;
			case _18:
				partsRotation = 180;
				break;
			case _27:
				partsRotation = 270;
				if (dirF == RIGHT) {
					dx = cmd_i_offset[cmf][fixedImg * 4 + 3];
				}
				break;
			}

			if (dirF == LEFT)
				DrawImage(
					cmd_i_offset[cmf][fixedImg * 4 + 2], cmd_i_offset[cmf][fixedImg * 4 + 3], cmd_i_offset[cmf][fixedImg * 4], cmd_i_offset[cmf][fixedImg * 4 + 1],
					x + ((float)(*(cPtr + 1) + centerX) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
					y - ((float)(*(cPtr + 1) + centerX) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
			else
				DrawImage(
					cmd_i_offset[cmf][fixedImg * 4 + 2], cmd_i_offset[cmf][fixedImg * 4 + 3], cmd_i_offset[cmf][fixedImg * 4], cmd_i_offset[cmf][fixedImg * 4 + 1],
					x + ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2) + centerY) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
					y - ((float)(-(*(cPtr + 1) + centerX) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2) + centerY) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

		}
		cPtr += 4;
		i--;
	} while (i > 0);
}


void DrawCommonShadow(int cmf, int x, int y, int dirF, float zoom)
{
	SetAlpha(24);
	if (IsBigCmf(cmf) == true)
		ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x - (float)20 * _2X * zoom, y + (float)10 * _2X * zoom, SHADOW_IMG, zoom);
	else
		ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x - (float)12 * _2X * zoom, y + (float)10 * _2X * zoom, SHADOW_IMG, zoom);
	SetAlpha(32);
}

void DrawCmfDetailShadow(int cmf, int motion, int x, int y, int dirF, float zoom)
{
	if (IsBigCmf(cmf) == true)
		ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x - (float)20 * _2X * zoom, y + (float)8 * _2X * zoom, SHADOW_IMG, zoom);
	else
		ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x - (float)12 * _2X * zoom, y + (float)8 * _2X * zoom, SHADOW_IMG, zoom);

	DrawCmfDetail(cmf, motion, x, y, dirF, zoom, false, false);
}

void DrawEffect(int idx, int x, int y, int dirF, float rotation, float zoom)
{
	int i, type, where, imgFile = 0, bDepth = 0, dx;

	const signed short* cPtr;

	//zoom = 2;

	if (idx >= 10000) {
		idx -= 10000;
		i = titleMIC[idx * 2 + 1];
		idx = titleMIC[idx * 2];
		cPtr = &titleMI[idx * 4];
		imgFile = TITLE_IMG;
		where = 3;
	}
	//tenbytenMIC
	else if (idx >= 5000) {

	}
	else if (idx >= 1000) {
		idx -= 1000;
		if (idx > 100)
			idx = idx;
		i = hitMIC[idx * 2 + 1];
		idx = hitMIC[idx * 2];
		cPtr = &hitMI[idx * 4];
		where = 1;
	}
	else {
		i = effectMIC[idx * 2 + 1];
		idx = effectMIC[idx * 2];
		cPtr = &effectMI[idx * 4];
		where = 0;
	}

	do {
		float magnify;
		float x2 = (float)*(cPtr + 1);
		const signed short* ucPtr;
		int dirX;
		int tempAlpha = m_lgrpAlpha;
		int tempAlpha2 = m_lgrpAlpha;
		int pxl;
		int partsRotation = 0;

		switch (where) {
		case 0:
			ucPtr = &effectOff[(*cPtr) * 4];

			if ((*cPtr) < IMG_EFFECT_2)
				imgFile = COMMON_CMF_IMG;
			else if ((*cPtr) < IMG_EFFECT_76)
				imgFile = EFFECT_IMG;
			else if ((*cPtr) < IMG_EFFECT_119)
				imgFile = COMMON_IMG;
			else
				imgFile = ATTR_IMG;
			break;
		case 1:
			ucPtr = &hitOff[(*cPtr) * 4];

			if ((*cPtr) < IMG_HIT_12)
				imgFile = EFFECT_IMG;
			else if ((*cPtr) < IMG_HIT_16)
				imgFile = COMMON_CMF_IMG;
			else
				imgFile = HIT_IMG;
			break;
		case 2:
		case 3:
			ucPtr = &titleOff[(*cPtr) * 4];
			break;
		}

		type = *(cPtr + 3);
		magnify = ((type >> 6) + 1) * zoom;

		dirX = (dirF + type) % 2;

		if ((*cPtr) == IMG_EFFECT_145)
			ucPtr += 4;
		else if ((*cPtr) == IMG_EFFECT_74) {
			bDepth = blendDepth;
			blendDepth = 0;
			tempAlpha >>= 1;
		}

		if (type & 0x08)
			pxl = 1;
		else
			pxl = 0;

		dx = *(ucPtr + 2);

		switch (type & 0x06) {
		case _00:
			partsRotation = 0;
			break;
		case _09:
			partsRotation = 90;
			if (dirF == RIGHT) {
				dx = *(ucPtr + 3);
			}
			break;
		case _18:
			partsRotation = 180;
			break;
		case _27:
			partsRotation = 270;
			if (dirF == RIGHT) {
				dx = *(ucPtr + 3);
			}
			break;
		}

		switch (idx) {
			//°­Å¸°ÝÈ¿°ú À§Ä¡º¸Á¤
		case 7:
		case 9:
		case 18:
			if (where == 0) {
				x2 = DX / 2 - (float)(160 * _2X) * zoom;
				break;
			}
		case 19:
			if (where == 0) {
				x2 = -(float)(134 * _2X) * zoom;
				break;
			}
		default:
			x2 = x + (dirF == 0 ? x2 * zoom : -*(ucPtr + ((type & 0x02) ? 3 : 2)) * magnify - x2 * zoom);
			break;
		}

		GetSpriteIndex(imgFile);
		if (where == 1 && (*cPtr) < IMG_HIT_3)
			//if (dirF == LEFT)
			DrawImage(
				*(ucPtr + 2), *(ucPtr + 3), *ucPtr, *(ucPtr + 1),
				x2,
				y - *(cPtr + 2) * zoom,
				dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
		else
			DrawImage(
				*(ucPtr + 2), *(ucPtr + 3), *ucPtr, *(ucPtr + 1),
				x2,
				y - *(cPtr + 2) * zoom,
				dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

		if ((*cPtr) == IMG_EFFECT_123)
			UnSetBlend();
		else if ((*cPtr) == IMG_EFFECT_74) {
			blendDepth = bDepth;
			tempAlpha <<= 1;
		}

		cPtr += 4;
		i--;
		idx++;
	} while (i > 0);
}

void DrawNeutral(int idx, int x, int y, int dirF, float zoom)
{
	int i, type, imgFile;
	const signed short* cPtr;
	int dx;
	int rotation = 0;

	//if (zoom == 0)
	//	zoom = 1;
	i = objMIC[idx * 2 + 1];
	idx = objMIC[idx * 2];
	cPtr = &objMI[idx * 4];

	do {
		int imgOffsetX = 0;
		int imgOffsetY = 0;
		float magnify;
		int extra = false;
		int pxl;
		int dirX;
		int tempAlpha = m_lgrpAlpha;
		int tempAlpha2 = m_lgrpAlpha;
		int partsRotation = 0;

		if (*cPtr < IMG_OBJ_72)
			imgFile = COMMON_IMG;
		else if (*cPtr < IMG_OBJ_79)
			imgFile = COMMON_CMF_IMG;
		else if (*cPtr < IMG_OBJ_94)
			imgFile = EFFECT_IMG;
		else if (*cPtr < IMG_OBJ_97)
			imgFile = GATE_IMG;
		else if (*cPtr < IMG_OBJ_103)
			imgFile = MAP_OBJ_IMG + 3;//bg3
		else if (*cPtr < IMG_OBJ_111)
			imgFile = MAP_OBJ_IMG + 4;//bg4
		else if (*cPtr < IMG_OBJ_116)
			imgFile = MAP_OBJ_IMG + 7;//bg7
		else if (*cPtr < IMG_OBJ_127)
			imgFile = MAP_OBJ_IMG + 9;//bg9
		else if (*cPtr < IMG_OBJ_139)
			imgFile = MAP_OBJ_IMG + 10;//bg10
		else if (*cPtr < IMG_OBJ_149)
			imgFile = MAP_OBJ_IMG + 10;//bg10
		else if (*cPtr < IMG_OBJ_153)
			imgFile = MAP_OBJ_IMG + 12;//bg12
		else if (*cPtr < IMG_OBJ_156)
			imgFile = MAP_OBJ_IMG + 11;//bg11
		else if (*cPtr < IMG_OBJ_159)
			imgFile = MAP_OBJ_IMG + 14;//bg14
		else if (*cPtr < IMG_OBJ_179)
			imgFile = MAP_OBJ_IMG + 15;//bg15
		else if (*cPtr < IMG_OBJ_192)
			imgFile = MAP_OBJ_IMG + 18;//bg18
		else if (*cPtr < IMG_OBJ_222)
			imgFile = TREE_IMG;
		else 
			imgFile = FLAG_IMG;


		//type = *(cPtr + 3) & 0xFF;
		type = *(cPtr + 3);
		magnify = ((type >> 6) + 1) * zoom;

		dirX = (dirF + type) % 2;

		if (type & 0x30) {
			tempAlpha = (tempAlpha * (4 - ((type & 0x30) >> 4))) >> 2;
			//SetAlpha(tempAlpha);
		}

		//¶óÀÌÆ° È¿°úÀÎÁö ÃßÃâ
		if (type & 0x08)
			pxl = 1;
		else
			pxl = 0;

		dx = objOff[(*cPtr) * 4 + 2];

		switch (type & 0x06) {
		case _00:
			partsRotation = 0;
			break;
		case _09:
			partsRotation = 90;
			if (dirF == RIGHT) {
				dx = objOff[(*cPtr) * 4 + 3];
			}
			break;
		case _18:
			partsRotation = 180;
			break;
		case _27:
			partsRotation = 270;
			if (dirF == RIGHT) {
				dx = objOff[(*cPtr) * 4 + 3];
			}
			break;
		}

		if (*(cPtr + 2) == -128 * _2X) {
			imgOffsetY = (y % (32 * _2X)) - 32 * _2X;

			do {
				if (dirF == LEFT)
					DrawImage(
						objOff[(*cPtr) * 4 + 2], objOff[(*cPtr) * 4 + 3], objOff[(*cPtr) * 4], objOff[(*cPtr) * 4 + 1],
						x + ((float)(*(cPtr + 1)/* + centerX*/) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2)/* + centerY*/) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
						y - ((float)(*(cPtr + 1)/* + centerX*/) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2)/* + centerY*/) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
						dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
				else
					DrawImage(
						objOff[(*cPtr) * 4 + 2], objOff[(*cPtr) * 4 + 3], objOff[(*cPtr) * 4], objOff[(*cPtr) * 4 + 1],
						x + ((float)(-(*(cPtr + 1)/* + centerX*/) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2)/* + centerY*/) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
						y - ((float)(-(*(cPtr + 1)/* + centerX*/) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2)/* + centerY*/) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
						dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

				imgOffsetY += 32 * _2X;
			} while (imgOffsetY < y - ry);
		}
		else {
			if (dirF == LEFT)
				DrawImage(
					objOff[(*cPtr) * 4 + 2], objOff[(*cPtr) * 4 + 3], objOff[(*cPtr) * 4], objOff[(*cPtr) * 4 + 1],
					x + ((float)(*(cPtr + 1)/* + centerX*/) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2)/* + centerY*/) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
					y - ((float)(*(cPtr + 1)/* + centerX*/) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2)/* + centerY*/) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);
			else
				DrawImage(
					objOff[(*cPtr) * 4 + 2], objOff[(*cPtr) * 4 + 3], objOff[(*cPtr) * 4], objOff[(*cPtr) * 4 + 1],
					x + ((float)(-(*(cPtr + 1)/* + centerX*/) - dx * ((type >> 6) + 1)) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation)) - (float)(*(cPtr + 2)/* + centerY*/) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetX,
					y - ((float)(-(*(cPtr + 1)/* + centerX*/) - dx * ((type >> 6) + 1)) * zoom * sin(CC_DEGREES_TO_RADIANS(rotation)) + (float)(*(cPtr + 2)/* + centerY*/) * zoom * cos(CC_DEGREES_TO_RADIANS(rotation))) + imgOffsetY,
					dirX, partsRotation, rotation, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

		}

		cPtr += 4;
		i--;
		idx++;
	} while (i > 0);
}

void DrawBgEffect(int idx, int x, int y, int dirF, float zoom)
{
	int i, type, imgFile, where;
	int drawx, drawy;
	const signed short* cPtr;
	const unsigned short* offPtr;

	if (idx >= 3000) {
		idx -= 3000;
		i = arenaMIC[idx * 2 + 1];
		idx = arenaMIC[idx * 2];
		cPtr = &arenaMI[idx * 4];

		where = 3;
	}
	else if (idx >= 2000) {
		idx -= 2000;
		i = 2;
		idx *= 2;
		cPtr = &waterfallMI[idx * 4];

		where = 2;
	}
	else if (idx >= 1000) {
		idx -= 1000;
		i = sunShineMIC[idx * 2 + 1];
		idx = sunShineMIC[idx * 2];
		cPtr = &sunShineMI[idx * 4];

		where = 1;
	}
	else {
		i = bgObjMIC[idx * 2 + 1];
		idx = bgObjMIC[idx * 2];
		cPtr = &bgObjMI[idx * 4];

		where = 0;
	}

	do {
		switch (where) {
		case 3:
			if (*cPtr < IMG_ARENA_10)
				imgFile = COMMON_IMG;
			else if (*cPtr < IMG_ARENA_11)
				imgFile = COMMON_CMF_IMG;
			else if (*cPtr < IMG_ARENA_12)
				imgFile = EFFECT_IMG;
			else
				imgFile = ETC_IMG;
			break;
		case 2:
			imgFile = WATER_IMG;
			break;
		case 1:
			imgFile = SHINE_IMG;
			break;
		case 0:
			imgFile = MAP_OBJ_IMG + mapData[7];
			break;
		}

		int imgOffsetX = 0;
		int imgOffsetY = 0;
		float magnify;
		int dirX;
		int tempAlpha = m_lgrpAlpha;
		int tempAlpha2 = m_lgrpAlpha;
		int pxl;
		int partsRotation = 0;


		if (!sprite[imgFile])
			LoadImg(imgFile);

		switch (imgFile) {
		case COMMON_IMG:
		case COMMON_CMF_IMG:
		case EFFECT_IMG:
		case ETC_IMG:
			offPtr = &arenaOff[*cPtr * 4];
			break;
		case WATER_IMG:
			offPtr = &atlanticeImg[*cPtr * 4 + (mapData[7] == MAPTYPE_DARKNESS ? 12 : 0)];
			break;
		case SHINE_IMG:
			offPtr = &sunShineOff[*cPtr * 4];
			break;
		default:
			offPtr = &bgObjOff[*cPtr * 4];
			break;
		}

		type = *(cPtr + 3);

		magnify = ((type >> 6) + 1) * zoom;

		//¹æÇâ
		dirX = (dirF + type) % 2;

		//¹ÝÅõ¸í °ª
		//Åõ¸íµµ »ó´ëÁ¶Àý
		if (type & 0x30) {
			tempAlpha = (tempAlpha * (4 - ((type & 0x30) >> 4))) >> 2;
		}

		if (type & 0x08)
			pxl = 1;
		else
			pxl = 0;

		switch (type & 0x06) {
		case _00:
			partsRotation = 0;
			break;
		case _09:
			partsRotation = 90;
			break;
		case _18:
			partsRotation = 180;
			break;
		case _27:
			partsRotation = 270;
			break;
		}

		drawx = x + (float)((dirF == 0 ? *(cPtr + 1) : (-*(offPtr + ((type & 0x02) ? 3 : 2)) * ((type >> 6) + 1) - *(cPtr + 1)))) * zoom;
		drawy = y + (float)(-*(cPtr + 2)) * zoom;

		DrawImage(*(offPtr + 2), *(offPtr + 3), *offPtr, *(offPtr + 1), drawx, drawy, dirX, partsRotation, 0, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

		cPtr += 4;
		i--;
		idx++;
	} while (i > 0);
}

void DrawBgEffectDetail(int idx, int x, int y, int dirF, int res)
{
	int i, type, imgFile;
	int drawx, drawy;
	const signed short* cPtr;
	const unsigned short* offPtr;

	if (idx >= 3000) {
		idx -= 3000;
		i = arenaMIC[idx * 2 + 1];
		idx = arenaMIC[idx * 2];
		cPtr = &arenaMI[idx * 4];

		imgFile = COMMON_IMG;
	}
	else if (idx >= 2000) {
		idx -= 2000;
		i = 2;
		idx *= 2;
		cPtr = &waterfallMI[idx * 4];

		imgFile = WATER_IMG;
	}
	else if (idx >= 1000) {
		idx -= 1000;
		i = sunShineMIC[idx * 2 + 1];
		idx = sunShineMIC[idx * 2];
		cPtr = &sunShineMI[idx * 4];

		imgFile = SHINE_IMG;
	}
	else {
		i = bgObjMIC[idx * 2 + 1];
		idx = bgObjMIC[idx * 2];
		cPtr = &bgObjMI[idx * 4];

		imgFile = MAP_OBJ_IMG + res;
	}

	if (!sprite[imgFile])
		LoadImg(imgFile);

	do {
		int imgOffsetX = 0;
		int imgOffsetY = 0;
		float magnify;
		int dirX;
		int tempAlpha = m_lgrpAlpha;
		int tempAlpha2 = m_lgrpAlpha;
		int pxl;
		int partsRotation = 0;

		switch (imgFile) {
		case COMMON_IMG:
			offPtr = &arenaOff[*cPtr * 4];
			break;
		case WATER_IMG:
			offPtr = &atlanticeImg[*cPtr * 4 + (mapData[7] == MAPTYPE_DARKNESS ? 12 : 0)];
			break;
		case SHINE_IMG:
			offPtr = &sunShineOff[*cPtr * 4];
			break;
		default:
			offPtr = &bgObjOff[*cPtr * 4];
			break;
		}

		type = *(cPtr + 3);

		magnify = ((type >> 6) + 1);

		//¹æÇâ
		dirX = (dirF + type) % 2;

		//¹ÝÅõ¸í °ª
		//Åõ¸íµµ »ó´ëÁ¶Àý
		if (type & 0x30) {
			tempAlpha = (tempAlpha * (4 - ((type & 0x30) >> 4))) >> 2;
		}

		if (type & 0x08)
			pxl = 1;
		else
			pxl = 0;

		switch (type & 0x06) {
		case _00:
			partsRotation = 0;
			break;
		case _09:
			partsRotation = 90;
			break;
		case _18:
			partsRotation = 180;
			break;
		case _27:
			partsRotation = 270;
			break;
		}

		drawx = x + (dirF == 0 ? *(cPtr + 1) : (-*(offPtr + ((type & 0x02) ? 3 : 2)) * ((type >> 6) + 1) - *(cPtr + 1)));
		drawy = y - *(cPtr + 2);

		DrawImage(*(offPtr + 2), *(offPtr + 3), *offPtr, *(offPtr + 1), drawx, drawy, dirX, partsRotation, 0, pxl, tempAlpha, magnify, sprite[imgFile], imgFile);

		cPtr += 4;
		i--;
		idx++;
	} while (i > 0);
}

void DrawEmoticon(int type, int icon, int frame, int x, int y, float zoom)
{
	if (icon >= ICON_BOX) {
		DrawIcon(icon, x - (float)BOXSIZE_X / 2 * zoom / 3 - (float)3 * _2X * zoom / 3, y + (float)BOXSIZE_Y * zoom / 3 - (float)12 * _2X * zoom / 3, zoom / 3, true, false, false, true);
	}
	else if (type == 1)
		DrawEffect(EMOTICON_ZZZ0 + frame % 12, x, y, 0, false, zoom);
	else {
		if (frame > 2) {
			frame -= 3;

			switch (type) {
			default:
				DrawEffect(emoticonRate[type * 2] + frame % emoticonRate[type * 2 + 1], x, y, 0, false, zoom);
				break;
			case EMOTICON_SCOWL:
				DrawEffect(scowlEffect[frame % 8], x, y, 0, false, zoom);
				break;
			case EMOTICON_SWEAT:
				DrawEffect(sweatEffect[frame % 7], x, y, 0, false, zoom);
				break;
			case EMOTICON_QUESTION:
				DrawEffect(questionEffect[frame % 10], x, y, 0, false, zoom);
				break;
			case EMOTICON_SURPRISE:
			case EMOTICON_HEART:
			case EMOTICON_HAPPY:
				DrawEffect(emoticonRate[type * 2] + surpriseEffect[frame % 5], x, y, 0, false, zoom);
				break;
			case EMOTICON_REWARDICON:
				if (icon == ICON_GOLD)
					icon = ICON_GOLD + frame % GOLDICONFRAME;
				DrawIcon(icon, x - (float)(ITEMICONSIZE / 2) * zoom, y + (float)(ITEMICONSIZE / 2) * zoom, 0.9f * zoom, COLOR_BROWN, false, false, true);
				break;
			case EMOTICON_REWARDBOX:
				//DrawBoxSpecial(x, y - (float)(ITEMICONSIZE / 2) * zoom / 2, LEFT, icon - ICON_BOX, zoom / 2, false, false, false, cvtDest, cvtLayer, buffering);
				break;
			}
		}
	}
}

void PlayerDraw(OBJECT* pObj)
{
	int i;
	int tempMotion = pObj->motion;
	int obj = GetObjFromPtr(pObj);
	int tempAlpha = m_lgrpAlpha;

	if (movie.robinMotion[obj] != 0) {
		pObj->motion = movie.robinMotion[obj];

		InitMotion(pObj);
	}

	//·¹º§¾÷ È¿°ú
	if (pObj->levelUpFrame && pObj->levelUpFrame < 11)
		DrawPlayer(pObj, 2000 - 1 + LEVELUP_BACK0 + pObj->levelUpFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, pObj->zoom, false, false, false);

	else if (pObj->statUpFrame && pObj->statUpFrame < 11)
		DrawPlayer(pObj, 2000 - 1 + LEVELUP_BACK0 + pObj->statUpFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, pObj->zoom, false, false, false);

	if (pObj->invincible / 2 % 2 == 0 || pObj->levelUpFrame == 0) {
		//¸Â¾ÒÀ»¶§ »ö È¿°ú
		if (pObj->attackedFrame)
			SetBlend(Max(0, (pObj->attackedFrame - 2) << 2), 0xFF0000);

		//ÇÃ·¹ÀÌ¾î
		DrawPlayer(pObj, pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, pObj->zoom, false, false, false);

		UnSetBlend();
	}

	//ÇÃ·¹ÀÌ¾î ¾Õ¿¡ ±×·ÁÁö´Â È¿°ú
	tempMotion = pObj->motion;

	if (!isDemo) {
		for (i = 0; i < TOTALBUFF; i++) {
			if (pObj->buff[i] > 0) {
				if (i < TOTALPLAYERBUFF) {
					//ï¿½ï¿½Å³ ï¿½ï¿½ï¿½ï¿½
					const unsigned short* ptrBuff = &buffData[i * 4];

					if (i == INC_IGNORE && (pObj->buff[i] - 1) % 2 == 1)
						pObj->motion = PO_C1_DENY1;
					else
						pObj->motion = *(ptrBuff + 3) + (pObj->buff[i] == 1 ? *(ptrBuff + 2) : ((pObj->buff[i] - 1) % *(ptrBuff + 2)));

					InitMotion(pObj);
					SetAlpha(Max(4, 24 - (32 - tempAlpha)));
					DrawPlayer(pObj, pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, 0, pObj->zoom, false, false, false);
					SetAlpha(tempAlpha);
				}
				else {
					int bFrame;

					if (buffBlend[i - INC_DAMAGE_RING])
						SetBlend(12, buffBlend[i - INC_DAMAGE_RING]);

					if (i >= INC_DAMAGE_ARENA)
						bFrame = robin.playtime;
					else
						bFrame = pObj->buff[i];

					//¹ÝÁö¹öÇÁ
					switch (i) {
					default:
						if (pObj->buff[i] % 6 != 5)
							DrawEffect(BUFF_DMG0 + bFrame % 6, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);
						break;
					case INC_DEFENSE_RING:
					case INC_EVASION_RING:
					case INC_STUN_RING:
					case INC_EXP_RING:
					case INC_DEFENSE_ARENA:
					case INC_MAGIC_ARENA:
						DrawEffect(BUFF_ARMOR0 + bFrame % 12, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);
						break;
					}

					UnSetBlend();
				}
			}
		}
	}

	if (pObj->motion != tempMotion) {
		pObj->motion = tempMotion;
		InitMotion(pObj);
	}

	//ÀÚ¼® ºÙ´Â È¿°ú
	if (pObj->canMagnet) {
		if (pObj->magnet)
			DrawEffect(MAGNET_ACTIVE0 + robin.playtime % 5, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);
		else
			DrawEffect(MAGNET_DEACTIVE0 + robin.playtime % 12, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);
	}

	//ÇÃ·¹ÀÌ¾î ÇÇ°ÝÈ¿°ú
	//¹«Àû½Ã°£
	if (pObj->attackedFrame > ATTACKEDFRAME + 1)
		DrawEffect(1000 + 10 - pObj->attackedFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);

	//¸¶³ªÈ¸º¹È¿°ú
	if (pObj->mpRestore)
		DrawEffect(EFFECT_RESTORE0 - 1 + pObj->mpRestore, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);

	//Ã¼·ÂÈ¸º¹È¿°ú
	if (pObj->hpRestore)
		DrawEffect(EFFECT_RESTORE0 - 1 + pObj->hpRestore, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);

	//»óÅÂÀÌ»ó È¸º¹È¿°ú
	if (pObj->statusRestore)
		DrawEffect(EFFECT_CURE0 - 1 + pObj->statusRestore, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);

	//¸¶³ªÈí¼ö È¿°ú
	if (pObj->mpDrain)
		DrawEffect(EFFECT_DRAIN0 - 1 + pObj->mpDrain, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);

	//Ã¼·Â Èí¼ö È¿°ú
	if (pObj->hpDrain)
		DrawEffect(EFFECT_CURE0 - 1 + pObj->hpDrain, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);

	if (pObj->hpDrain) {
		SetBlend(16, 0xFF0000);
		DrawEffect(EFFECT_DRAIN0 - 1 + pObj->hpDrain, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);
	}

	UnSetBlend();

	//·¹º§¾÷ È¿°ú
	if (pObj->levelUpFrame && pObj->levelUpFrame < 11)
		DrawPlayer(pObj, 2000 - 1 + LEVELUP_FRONT0 + pObj->levelUpFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, pObj->zoom, false, false, false);
	else if (pObj->statUpFrame && pObj->statUpFrame < 11)
		DrawPlayer(pObj, 2000 - 1 + LEVELUP_FRONT0 + pObj->statUpFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, pObj->zoom, false, false, false);

}

void NormalDraw(OBJECT* pObj)
{
	InitMotion(pObj);
	DrawPlayer(pObj, pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, pObj->zoom, false, false, false);
}

void BulletLaserDraw(OBJECT* pObj)
{
	NormalDraw(pObj);

	//ï¿½æµ¹ï¿½ï¿½ ï¿½ï¿½ï¿?
	if (pObj->status) {
		int xx = pObj->x - (float)(DIR(pObj->dirX) * TSIZE / 2) * pObj->zoom;
		int yy = pObj->y - (float)(DIR(pObj->dirY) * TSIZE / 2) * pObj->zoom;

		//we.bmp
		DrawImage(20 * _2X, 18 * _2X, 0 * _2X, 121 * _2X, xOffset + xx - rx - (float)(16 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (yy - (float)(16 * _2X) * pObj->zoom) - ry, false, false, false, true, false, pObj->zoom, sprite[WEAPON_EFFECT_IMG], WEAPON_EFFECT_IMG);
	}
}

void BulletGuidedDraw(OBJECT* pObj)
{
	InitMotion(pObj);

	//¹Ì»çÀÏ ±×·ÁÁÖ±â
	DrawPlayer(pObj, pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, 0, pObj->zoom, false, false, false);

}

void BulletSateliteDraw(OBJECT* pObj)
{
	int i, tempMotion;
	int tempAlpha = m_lgrpAlpha;

	if (pObj->frame > 24) {
		//Áö»ó ·¹ÀÌÀú /±×¸®±â
		SetAlpha(24 - (32 - tempAlpha));
		tempMotion = satelliteShotMotion[Min(24 + 36 * 3 + 36 * 3 - 1, pObj->frame - 24 + (24 + 36 * 3))];

		for (i = pObj->y; i >= -96 * _2X * pObj->zoom * 2; i -= 96 * _2X * pObj->zoom * 2)
			DrawPlayer(pObj, 1000 + tempMotion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (i - OBJIMGGAP) - ry, 0, pObj->zoom * 2, false, false, false);

		if (tempMotion >= PO_C1_SATLASER_SHOT5) {
			//cc.bmp
			//¹Ù´ÚÀ» ±×·ÁÁÖ´Â°Í
			//DrawImage(20 * _2X, 20 * _2X, 40 * _2X, 83 * _2X, xOffset + pObj->x - rx + (float)(satelliteShotData[(tempMotion - PO_C1_SATLASER_SHOT5) * 3]) * pObj->zoom * 2, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y + (float)(satelliteShotData[(tempMotion - PO_C1_SATLASER_SHOT5) * 3 + 1]) * pObj->zoom * 2) - ry, false, false, false, false, false, (float)(satelliteShotData[(tempMotion - PO_C1_SATLASER_SHOT5) * 3 + 2]) * pObj->zoom * 2, sprite[COMMON_CMF_IMG], cvtDest, cvtLayer, COMMON_CMF_IMG, buffering);
		}

		SetAlpha(tempAlpha);
	}

	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½×·ï¿½ï¿½Ö´ï¿½ ï¿½Îºï¿½

	clipX3 = clipX;
	clipY3 = clipY;
	clipX4 = clipX2;
	clipY4 = clipY2;

	SetSectionClip(DX - (float)64 * _2X * pObj->zoom * 2, DY, (float)64 * _2X * pObj->zoom * 2, (float)64 * _2X * pObj->zoom * 2, false);
	DrawPlayer(pObj, 1000 + satelliteShotMotion[Min(24 + 36 * 3 - 1, pObj->frame)], xOffset + DX - 2 * xOffset - (float)64 * _2X * pObj->zoom * 2, DY, 0, pObj->zoom * 2,
		false, false, false);

	UnSectionClip(false);

	clipX = clipX3;
	clipY = clipY3;
	clipX2 = clipX4;
	clipY2 = clipY4;
}

void BulletHealDraw(OBJECT* pObj)
{
	if (pObj->frame > 1)
		DrawPlayer(pObj, pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, 0, pObj->zoom, false, false, false);
}

void BulletBoomerangDraw(OBJECT* pObj)
{
	if ((pObj->attack == MAXX_SKILL_CAMPING || pObj->attack == MAXX_SKILL_HORMING) && pObj->icon != 0)
		DrawPlayer(pObj, pObj->motion + 4 + ((robin.playtime + 3) % 4), pObj->icon - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->name - OBJIMGGAP) - ry, pObj->dirF, pObj->zoom, false, false, false);

	DrawPlayer(pObj, pObj->motion + (robin.playtime % 4), xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, pObj->dirF, pObj->zoom, false, false, false);
}

void BulletItemDraw(OBJECT* pObj)
{
	SetAlpha(10);
	DrawIcon(pObj->icon, xOffset - rx + (float)(pObj->jumpFrame * _2X - 8 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->attackFrame * _2X - OBJIMGGAP - 8 * _2X) - ry, pObj->zoom, false, false, false, true);
	SetAlpha(21);
	DrawIcon(pObj->icon, xOffset - rx + (float)(pObj->hp * _2X - 8 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->maxhp * _2X - OBJIMGGAP - 8 * _2X) - ry, pObj->zoom, false, false, false, true);
	SetAlpha(32);

	if (pObj->status == 0)
		DrawIcon(pObj->icon, xOffset - rx + pObj->x - (float)(8 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP + 8 * _2X) - ry, pObj->zoom, false, false, false, true);
	else
		DrawEffect((pObj->etc == 0 ? HIT_ITEM_SMALL0 : HIT_ITEM_LARGE0) + 1000 - 1 + pObj->mainFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, 0, false, pObj->zoom);
}

void BulletCrewDraw(OBJECT* pObj)
{
	int i;
	//SetAlpha(10);
	//DrawCrewBulletIcon(pObj->icon, xOffset - rx + pObj->x + (float)(pObj->jumpFrame * _2X - CREWBULLETICONSIZE / 2) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y +  - OBJIMGGAP - CREWBULLETICONSIZE / 2 * pObj->zoom) - ry, pObj->zoom, cvtDest, cvtLayer, buffering);
	//SetAlpha(21);
	//DrawCrewBulletIcon(pObj->icon, xOffset - rx + pObj->x + (float)(pObj->hp * _2X - CREWBULLETICONSIZE / 2) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP - CREWBULLETICONSIZE / 2 * pObj->zoom) - ry, pObj->zoom, cvtDest, cvtLayer, buffering);
	//SetAlpha(32);

	//if (pObj->status == 0)
	SetColor(itemColor[frame / 2 % 6]);
	
	for (i = 0; i < 4; i++) {
		DrawCrewBulletIcon(pObj->icon, xOffset - rx + pObj->x - (float)(CREWBULLETICONSIZE / 2) * pObj->zoom + (float)solidPosition[2 * i + 0] * 8 * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP - CREWBULLETICONSIZE / 2 * pObj->zoom) - ry + (float)solidPosition[2 * i + 1] * 8 * pObj->zoom, pObj->zoom);
	}

	SetColor(false);

	DrawCrewBulletIcon(pObj->icon, xOffset - rx + pObj->x - (float)(CREWBULLETICONSIZE / 2) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP - CREWBULLETICONSIZE / 2 * pObj->zoom) - ry, pObj->zoom);
	//else
	//	DrawEffect((pObj->etc == 0 ? HIT_ITEM_SMALL0 : HIT_ITEM_LARGE0) + 1000 - 1 + pObj->mainFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, 0, false, pObj->zoom, cvtDest, cvtLayer, buffering);

	return;
	SetAlpha(10);
	DrawCrewBulletIcon(pObj->icon, xOffset - rx + (float)(pObj->jumpFrame * _2X - 8 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->attackFrame * _2X - OBJIMGGAP - 8 * _2X) - ry, pObj->zoom);
	SetAlpha(21);
	DrawCrewBulletIcon(pObj->icon, xOffset - rx + (float)(pObj->hp * _2X - 8 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->maxhp * _2X - OBJIMGGAP - 8 * _2X) - ry, pObj->zoom);
	SetAlpha(32);

	if (pObj->status == 0)
		DrawCrewBulletIcon(pObj->icon, xOffset - rx + pObj->x - (float)(8 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP + 8 * _2X) - ry, pObj->zoom);
	else
		DrawEffect((pObj->etc == 0 ? HIT_ITEM_SMALL0 : HIT_ITEM_LARGE0) + 1000 - 1 + pObj->mainFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - OBJIMGGAP) - ry, 0, false, pObj->zoom);
}

void EnemyProfileDraw(int x, int y, int enemyIdx, int star, int lv, float zoom)
{
	DrawFrame(x, y, (float)(36 * _2X) * zoom, (float)(36 * _2X) * zoom, FRAME_SHOPBALLOON);

	clipX3 = clipX;
	clipY3 = clipY;
	clipX4 = clipX2;
	clipY4 = clipY2;

	SetSectionClip(x + (float)(2 * _2X) * zoom, y - (float)(2 * _2X) * zoom, (float)(36 * _2X - 4 * _2X) * zoom, (float)(36 * _2X - 4 * _2X) * zoom, false);
	ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(36 * _2X / 2 - 20 * _2X) * zoom, y + (float)(-32 * _2X + 8 * _2X) * zoom, SHADOW_IMG, zoom);

	if (enemyIdx < ENEMY_SNAIL)
		DrawPlayerCostume(
			enemyIdx,
			robin.charData[enemyIdx].equip[EQUIP_WEAPON].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_WEAPON].detail : -1, robin.charData[enemyIdx].equip[EQUIP_WEAPON].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_WEAPON].grade : 0,
			robin.charData[enemyIdx].equip[EQUIP_GLOVE].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_GLOVE].detail : -1, robin.charData[enemyIdx].equip[EQUIP_GLOVE].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_GLOVE].grade : 0,
			robin.charData[enemyIdx].equip[EQUIP_HELM].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_HELM].detail : -1, robin.charData[enemyIdx].equip[EQUIP_HELM].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_HELM].grade : 0,
			robin.charData[enemyIdx].equip[EQUIP_ARMOR].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_ARMOR].detail : -1, robin.charData[enemyIdx].equip[EQUIP_ARMOR].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_ARMOR].grade : 0,
			robin.charData[enemyIdx].equip[EQUIP_PANTS].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_PANTS].detail : -1, robin.charData[enemyIdx].equip[EQUIP_PANTS].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_PANTS].grade : 0,
			robin.charData[enemyIdx].equip[EQUIP_BOOTS].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_BOOTS].detail : -1, robin.charData[enemyIdx].equip[EQUIP_BOOTS].type != EMPTY ? robin.charData[enemyIdx].equip[EQUIP_BOOTS].grade : 0,

			x + (float)(36 * _2X / 2) * zoom, y + (float)(-32 * _2X) * zoom, RIGHT, false, zoom * HOUSEPLAYERZOOM);
	//DrawCmfDetailShadow(enemyIdx, enemyBigIconPos[3 * enemyIdx + 0], x + (float)(36 * _2X / 2 + enemyBigIconPos[3 * enemyIdx + 1]) * zoom, y + (float)(-32 * _2X + enemyBigIconPos[3 * enemyIdx + 2] + 4 * _2X) * zoom, RIGHT, zoom, cvtDest, cvtLayer, buffering);
	//DrawPlayer(&ao[enemyIdx], false, x + (float)(36 * _2X / 2) * zoom, y + (float)(-32 * _2X) * zoom, RIGHT, HOUSEZOOM * zoom, false, false, false, cvtDest, cvtLayer, buffering);
	else
		DrawCmfDetail(enemyData[enemyIdx * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[3 * enemyIdx + 0], x + (float)(36 * _2X / 2 + enemyBigIconPos[3 * enemyIdx + 1]) * zoom, y + (float)(-32 * _2X + enemyBigIconPos[3 * enemyIdx + 2] + 4 * _2X) * zoom, LEFT, zoom, false, false);

	UnSectionClip(false);

	if (star)
		DrawStar(ICON_STAR, x + (float)(18 * _2X) * zoom, y + (float)(ITEMICONSIZE / 2 * 0.6f + ITEMICONSIZE * 0.6f / 2) * zoom, star, star, star, CENTER, true, 0.6f * zoom);

	if (lv)
		DrawLv(lv, x + (float)(20 * _2X) * zoom, y - (float)36 * _2X * zoom, 0.8f * zoom, CENTER);

	clipX = clipX3;
	clipY = clipY3;
	clipX2 = clipX4;
	clipY2 = clipY4;

}

void EnemyDraw(OBJECT* pObj)
{
	int temp = 0;
	int i;
	int obj = GetObjFromPtr(pObj);

	if ((pObj->type == ENEMY_LARVA
		|| pObj->type == ENEMY_LARVA_RED
		|| pObj->type == ENEMY_LARVA_BLUE
		|| pObj->type == ENEMY_LARVA_PURPLE
		|| pObj->type == ENEMY_LARVA_GREEN
		|| pObj->type == ENEMY_LARVA_GOLD
		|| pObj->type == ENEMY_LARVA_BLACK)
		&& pObj->etc == LARVA_HIDED)
		return;
	if (pObj->levelUpFrame > 0 && pObj->levelUpFrame < 11) {
		ao[NPC].cmf = ao[NPC].type = ROBIN;
		//ao[NPC].x = pObj->x;
		//ao[NPC].y = pObj->y;
		DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_BACK0 + pObj->levelUpFrame, pObj->x, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y - ry + OBJIMGGAP, false, pObj->zoom, false, false, false);
	}

	if (pObj->hp * 5 < pObj->maxhp)
		SetBlend(4 + Abs(3 - (robin.playtime % 5)) * 4, 0xFF0000);
	else if (pObj->debuf[STUN] > 0)
		SetBlend(4 + Abs(3 - (robin.playtime % 5)) * 4, 0x333333);

	if ((pObj->type == ENEMY_CASTLE_BOSS1
		|| pObj->type == ENEMY_CASTLE_BOSS1_RED
		|| pObj->type == ENEMY_CASTLE_BOSS1_BLUE
		|| pObj->type == ENEMY_CASTLE_BOSS1_PURPLE
		|| pObj->type == ENEMY_CASTLE_BOSS1_GREEN
		|| pObj->type == ENEMY_CASTLE_BOSS1_GOLD
		|| pObj->type == ENEMY_CASTLE_BOSS1_BLACK)
		&& (pObj->etc == CASTLEBOSS1_UARM_MOVE || pObj->etc == CASTLEBOSS1_DARM_MOVE) && pObj->frame > 8) {
		int disX = pObj->x + (float)(DIR(pObj->dirF) * 10 * _2X) * pObj->zoom;
		int disY = pObj->y;

		if (disY < ao[pObj->mom].y) {
			while (disY < ao[pObj->mom].y - 18 * _2X) {
				//c48.bmp
				DrawImage(20 * _2X, 20 * _2X, 73 * _2X, 52 * _2X, xOffset - rx + disX - (float)(10 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (disY - (float)20 * _2X * pObj->zoom) - ry, false, false, false, false, false, pObj->zoom, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);

				disY += (float)(24 * _2X) * pObj->zoom;
				disX -= (float)(DIR(pObj->dirF) * 24 * _2X) * pObj->zoom;
			};
		}
		else {
			while (disY > ao[pObj->mom].y + 18 * _2X) {
				//c48.bmp
				DrawImage(20 * _2X, 20 * _2X, 73 * _2X, 52 * _2X, xOffset - rx + disX - (float)(10 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - (disY - (float)20 * _2X * pObj->zoom) - ry, false, false, false, false, false, pObj->zoom, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);

				disY -= (float)(24 * _2X) * pObj->zoom;
				disX -= (float)(DIR(pObj->dirF) * 24 * _2X) * pObj->zoom;
			};
		}
	}

	if ((pObj->type == ENEMY_CASTLE_BOSS3
		|| pObj->type == ENEMY_CASTLE_BOSS3_RED
		|| pObj->type == ENEMY_CASTLE_BOSS3_BLUE
		|| pObj->type == ENEMY_CASTLE_BOSS3_PURPLE
		|| pObj->type == ENEMY_CASTLE_BOSS3_GREEN
		|| pObj->type == ENEMY_CASTLE_BOSS3_GOLD
		|| pObj->type == ENEMY_CASTLE_BOSS3_BLACK
		) && pObj->moveHandler == SLINGMOVE) {
		//c50.bmp
		//DrawImage(12 * _2X, 12 * _2X, 0 * _2X, 216 * _2X, pObj->x + pObj->cx + pObj->dx * 2 - rx - (float)6 * _2X * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y + pObj->cy + pObj->dy * 2 - ry - (float)6 * _2X * pObj->zoom, false, false, false, false, false, pObj->zoom, sprite[MONSTER_IMG + pObj->cmf], cvtDest, cvtLayer, MONSTER_IMG + pObj->cmf, buffering);
		//DrawImage(18 * _2X, 18 * _2X, 26 * _2X, 200 * _2X, pObj->x + pObj->cx / 2 + pObj->dx * 1 - rx - (float)9 * _2X * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y + pObj->cy + pObj->dy * 1 - ry - (float)9 * _2X * pObj->zoom, false, false, false, false, false, pObj->zoom, sprite[MONSTER_IMG + pObj->cmf], cvtDest, cvtLayer, MONSTER_IMG + pObj->cmf, buffering);

		//DrawImage(12 * _2X, 12 * _2X, 0 * _2X, 216 * _2X, pObj->cpx - rx - (float)6 * _2X * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->cpy - ry + (float)6 * _2X * pObj->zoom, false, false, false, false, false, pObj->zoom, sprite[MONSTER_IMG + pObj->cmf], cvtDest, cvtLayer, MONSTER_IMG + pObj->cmf, buffering);
		//DrawImage(18 * _2X, 18 * _2X, 26 * _2X, 200 * _2X, pObj->cx - rx - (float)9 * _2X * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->cy - ry + (float)9 * _2X * pObj->zoom, false, false, false, false, false, pObj->zoom, sprite[MONSTER_IMG + pObj->cmf], cvtDest, cvtLayer, MONSTER_IMG + pObj->cmf, buffering);
	}

	DrawCmf(pObj, false, pObj->zoom, false);

	if (pObj->levelUpFrame > 0 && pObj->levelUpFrame < 11) {
		ao[NPC].cmf = ao[NPC].type = ROBIN;
		//ao[NPC].x = pObj->x;
		//ao[NPC].y = pObj->y;
		DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_FRONT0 + pObj->levelUpFrame, pObj->x, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y - ry + OBJIMGGAP, false, pObj->zoom, false, false, false);
		DrawEffect(EFFECT_LEVELUP_TEXT0 - 1 + (pObj->levelUpFrame < 11 ? pObj->levelUpFrame : Max(11, pObj->levelUpFrame - 5)), pObj->x, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y - ry + OBJIMGGAP - (float)(16 * _2X) * pObj->zoom, 0, false, pObj->zoom);

	}
	/*
	switch (pObj->type) {
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
		temp = pObj->motion;
		pObj->motion = PO_C50_UPSKIN;
		DrawCmf(pObj, false, pObj->zoom, false, cvtDest, cvtLayer, buffering);
		pObj->motion = PO_C50_DOWNSKIN;
		DrawCmf(pObj, false, pObj->zoom, false, cvtDest, cvtLayer, buffering);
		pObj->motion = temp;
		break;
	}
	*/
}

void CloudDraw(OBJECT* pObj)
{
	int i, x, y, w;
	int height = GetObjHeight(pObj);

	EnemyDraw(pObj);

	switch (pObj->motion) {
	case PO_C24_A4:
		for (i = 0; i <= height; i += TSIZE) {
			if ((i / TSIZE) % 2 == 0) {
				x = 27 * _2X;
				y = 51 * _2X;
				w = 14 * _2X;
			}
			else {
				x = 26 * _2X;
				y = 35 * _2X;
				w = 16 * _2X;
			}

			//c24.bmp


			DrawImage(w, 16 * _2X, x, y, xOffset + pObj->x - 10 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 15 * _2X + (16 * _2X * (i / TSIZE))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);
		}

		SetAlpha(12);
		//c24.bmp
		DrawImage(32 * _2X, 18 * _2X, 56 * _2X, 68 * _2X, xOffset + pObj->x - 15 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 15 * _2X + (16 * _2X * ((i - (i - height)) / TSIZE))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);
		SetAlpha(32);
		break;
	case PO_C24_A5:
		for (i = 0; i <= height; i += TSIZE) {
			if ((i / TSIZE) % 2 == 0) {
				x = 6 * _2X;
				y = 35 * _2X;
				w = 20 * _2X;
			}
			else {
				x = 6 * _2X;
				y = 51 * _2X;
				w = 21 * _2X;
			}

			//c24.bmp
			DrawImage(w, 16 * _2X, x, y, xOffset + pObj->x - 10 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 15 * _2X + (16 * _2X * (i / TSIZE))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);
		}

		//c24.bmp
		DrawImage(32 * _2X, 18 * _2X, 56 * _2X, 68 * _2X, xOffset + pObj->x - 15 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 15 * _2X + (16 * _2X * ((i - (i - height)) / TSIZE))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);

		//c24.bmp
		DrawImage(28 * _2X, 28 * _2X, 42 * _2X, 20 * _2X, xOffset + pObj->x - 14 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 25 * _2X) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);
		break;
	case PO_C24_A6:
		SetAlpha(12);

		for (i = 32 * _2X; i <= height; i += 16 * _2X)
			//c24.bmp
			DrawImage(6 * _2X, 32 * _2X, 0 * _2X, 35 * _2X, xOffset + pObj->x - 8 * _2X - rx + Random(5) * _2X, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 47 * _2X + (32 * _2X * (i / (32 * _2X)))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);

		//c24.bmp
		DrawImage(32 * _2X, 18 * _2X, 56 * _2X, 68 * _2X, xOffset + pObj->x - 15 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pObj->y - 15 * _2X + (16 * _2X * ((i - (i - height)) / TSIZE))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);
		SetAlpha(32);
		break;
	}
}

void SpiderDraw(OBJECT* pObj)
{
	int i = 0, h, y;        //w = 64

	switch (pObj->motion) {
	case PO_C27_U_LAY2:
	case PO_C27_D_LAY2:
		h = 18 * _2X;

		while (i < 6) {
			if (pObj->dirF == RIGHT || i != 0) {
				//y = pObj->motion == PO_C27_U_LAY2 ? (int)(pObj->y + (float)6 * _2X * pObj->zoom - (float)20 * _2X * (pObj->zoom - 1)) : (int)(pObj->y + ry + (float)(-20 * _2X - h / 2) * pObj->zoom - (float)20 * _2X * (pObj->zoom - 1));
				y = pObj->motion == PO_C27_U_LAY2 ? (int)(pObj->y + (float)6 * _2X * pObj->zoom) : (int)(pObj->y + ry + (float)(-20 * _2X - h / 2) * pObj->zoom);
				//c27.bmp
				DrawImage(64 * _2X, h, 0 * _2X, 73 * _2X, xOffset + pObj->x - rx + (float)(64 * _2X * i * DIR(pObj->dirF)) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - y, false, false, false, false, false, pObj->zoom, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);
			}

			i++;
		}
		PlayMusic(M_MACHINE);
		break;
	case PO_C27_U_LAY3:
	case PO_C27_D_LAY3:
		h = 8 * _2X;

		while (i < 6) {
			if (pObj->dirF == RIGHT || i != 0) {
				//y = pObj->motion == PO_C27_U_LAY3 ? pObj->y + (float)(9 * _2X) * pObj->zoom - (float)20 * _2X * (pObj->zoom - 1): pObj->y + ry + (float)(-(20 * _2X) - h / 2) * pObj->zoom - (float)20 * _2X * (pObj->zoom - 1);
				y = pObj->motion == PO_C27_U_LAY3 ? pObj->y + (float)(9 * _2X) * pObj->zoom - (float)20 * _2X * (pObj->zoom - 1) : pObj->y + ry + (float)(-(20 * _2X) - h / 2) * pObj->zoom;
				//c27.bmp
				DrawImage(64 * _2X, h, 0 * _2X, 103 * _2X, xOffset + pObj->x - rx + (float)(64 * _2X * i * DIR(pObj->dirF)) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - y, false, false, false, false, false, pObj->zoom, sprite[MONSTER_IMG + pObj->cmf], MONSTER_IMG + pObj->cmf);
			}

			i++;
		}
		PlayMusic(M_MACHINE);
		break;
	}

	EnemyDraw(pObj);
}

void SkelDraw(OBJECT* pObj)
{
	if (pObj->status == 1)
		SetAlpha(32 - pObj->frame);

	DrawCmf(pObj, false, pObj->zoom, false);
	SetAlpha(32);
}

void MachineDraw(OBJECT* pObj)
{
	DrawCmf(pObj, false, pObj->zoom, false);
}

void LaserDraw(OBJECT* pObj)
{
	int i;
	float zoom = pObj->zoom;


	if (pObj->frame > 1) {
		memset(pObj, 0, sizeof(OBJECT));
		return;
	}

	for (i = 0; i <= pObj->x / (float)(32 * _2X * zoom) + 4; i++) {
		pObj->x -= (float)32 * _2X * zoom;
		DrawCmf(pObj, false, zoom, false);
	}
}

void GhostDraw(OBJECT* pObj)
{
	SetAlpha(pObj->attack);

	EnemyDraw(pObj);

	SetAlpha(32);

	if (pObj->attack <= 20)
		pObj->attack++;
}

void VanishDraw(OBJECT* pObj)
{
	if (pObj->frame < FPS / 2) {
		if (pObj->frame >= FPS / 3 - 2 * 4) {
			SetBlend(16 + (pObj->frame - (FPS / 3 - 2 * 4)) / 2, COLOR_WHITE);
			SetAlpha(32 - (pObj->frame - (FPS / 3 - 2 * 4)) / 2);
		}
		if (pObj->type < TOTALCHAR)
			PlayerDraw(pObj);
		else
			DrawCmf(pObj, false, pObj->zoom, false);
		SetAlpha(32);

		if (pObj->frame >= FPS / 3 - 2 * 4)
			DrawEffect((pObj->frame - (FPS / 3 - 2 * 4)) / 2 + HIT_DEAD1, xOffset + PxlLeft(pObj) + pObj->cx / 2 - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (PxlUp(pObj) + pObj->cy / 2 - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);
		else
			DrawEffect(HIT_ITEM_LARGE0 + 1000 - 1 + pObj->frame % 5, xOffset + PxlLeft(pObj) + pObj->cx / 2 - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (PxlUp(pObj) + pObj->cy / 2 - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom);
	}


}

void RegenDraw(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);
	//ÀüÅõ½Å Ã³À½ÀÇ µîÀå½Å¿¡¼­´Â 
	if (obj < SOLDIER + 1) {
		//ï¿½ï¿½ï¿½â¼­ ï¿½Ä¸é¿¡ ï¿½×·ï¿½ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½×·ï¿½ï¿½Ö°ï¿½
	}
	else {

		SetBlend(32 - pObj->frame, 0x000000);
		SetAlpha(pObj->frame);
	}
	if (pObj->type < TOTALCHAR)
		PlayerDraw(pObj);
	else
		DrawCmf(pObj, false, pObj->zoom, false);
	if (obj < SOLDIER + 1) {
		//ï¿½ï¿½ï¿½â¼­ ï¿½ï¿½ï¿½é¿¡ Ä³ï¿½ï¿½ï¿½Í°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½×·ï¿½ï¿½Ø´ï¿½.
	}
	else {
		SetAlpha(32);
		UnSetBlend();
	}

	//DrawCmfDetail(CMF_NPC_HEART, summonMotion[Min(19, pObj->frame)], pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE + (float)64 * _2X * pObj->zoom - (PxlUp(pObj) + pObj->cy / 2 - OBJIMGGAP) - ry, LEFT, pObj->zoom, false, false, cvtDest, cvtLayer, buffering);
	//if (pObj->frame < 3) {
	//	DrawEffect(pObj->frame + HIT_DEAD1, xOffset + PxlLeft(pObj) + pObj->cx / 2 - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (PxlUp(pObj) + pObj->cy / 2 - OBJIMGGAP) - ry, pObj->dirF, false, pObj->zoom, cvtDest, cvtLayer, buffering);
	//}
}

void NeutralDraw(OBJECT* pObj)
{
	int i;
	unsigned char* maPtr;
	float gapX, gapY;
	float iconZoom;

	switch (pObj->type) {
	case OBJ_DOOR:
		//door.bmp

		DrawImage(16 * _2X, pObj->cy, pObj->icon * 16 * _2X, 48 * _2X - pObj->cy, xOffset + pObj->x - rx + pObj->cpx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP + 1 * _2X) * pObj->zoom), false, false, false, false, false, pObj->zoom, sprite[DOOR_IMG], DOOR_IMG);
		DrawImage(16 * _2X, pObj->cy, pObj->icon * 16 * _2X, 48 * _2X - pObj->cy, xOffset + pObj->x - rx + pObj->cpx + (float)(16 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP + 1 * _2X) * pObj->zoom), true, false, false, false, false, pObj->zoom, sprite[DOOR_IMG], DOOR_IMG);

		maPtr = &mapArray[(pObj->y / TSIZE) * mapData[1] + (pObj->x - 8 * _2X) / TSIZE];

		//t0.bmp
		DrawImage(TSIZE, TSIZE, (*maPtr - 1) % MAXTILE * TSIZE, (*maPtr - 1) / MAXTILE * TSIZE, xOffset - rx + (pObj->x - (float)(8 * _2X) * pObj->zoom) / TSIZE * TSIZE, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y / TSIZE * TSIZE), false, false, false, false, false, pObj->zoom, sprite[MAP_TILE_IMG + mapData[7]], MAP_TILE_IMG + mapData[7]);
		DrawImage(TSIZE, TSIZE, (*maPtr - 1) % MAXTILE * TSIZE, (*maPtr - 1) / MAXTILE * TSIZE, xOffset - rx + (pObj->x + (float)(8 * _2X) * pObj->zoom) / TSIZE * TSIZE, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y / TSIZE * TSIZE), false, false, false, false, false, pObj->zoom, sprite[MAP_TILE_IMG + mapData[7]], MAP_TILE_IMG + mapData[7]);

		if (pObj->mainFrame) {
			//¹Ù´Ú¸ÕÁö
			DrawNeutral(OBJ_DOORDUST0 - 1 + pObj->mainFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - OBJIMGGAP), 0, pObj->zoom);
			DrawNeutral(OBJ_DOORDUST0 - 1 + pObj->mainFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - OBJIMGGAP), 1, pObj->zoom);
		}

		if (pObj->jumpFrame) {
			//¹Ù´Ú¸ÕÁö
			DrawNeutral(OBJ_DOORDUST7 - 1 + pObj->jumpFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - (float)OBJIMGGAP * pObj->zoom), 0, pObj->zoom);
			DrawNeutral(OBJ_DOORDUST7 - 1 + pObj->jumpFrame, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - (float)OBJIMGGAP * pObj->zoom), 1, pObj->zoom);
		}
		break;
	case OBJ_REPULSION:
		SetAlpha(32 - Abs(robin.playtime % 16 - 8) * 4);
		//bg11.bmp
		DrawImage(12 * _2X, 12 * _2X, 46 * _2X, 28 * _2X, xOffset + pObj->x - rx - (float)(6 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP - 6 * _2X) * pObj->zoom), false, false, false, false, false, pObj->zoom, sprite[MAP_OBJ_IMG], MAP_OBJ_IMG);
		break;
	case OBJ_ITEM:


		switch (pObj->mainFrame % 20) {
		case 5:
		case 7:
			SetBlend(16, COLOR_WHITE);
			break;
		case 6:
			SetBlend(32, COLOR_WHITE);
			break;
		}

		// ÀÏÁ¤½Ã°£(30ÃÊÁ¤µµ) ÀÌ»óµÇ¸é ±ôºýÀÌ´Ù°¡ »ç¶óÁü
		/*
		if (pObj->mainFrame > 3000 && pObj->def < ITEM_QUEST) {

			SetAlpha(pObj->mainFrame % 33);

			if (pObj->mainFrame > 3600) {
				memset(pObj, 0, sizeof(OBJECT));
				return;
			}
		}
		*/

		if (pObj->def == ITEM_GOLD)
			DrawIcon(ICON_GOLD + (frame % GOLDICONFRAME), xOffset + pObj->x - (float)(ITEMICONSIZE / 2) * pObj->zoom - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-ITEMICONSIZE - OBJIMGGAP) * pObj->zoom), pObj->zoom, false, false, false, true);
		else
			DrawIcon(GetItemIcon(pObj->def, pObj->apx, pObj->apy), xOffset + pObj->x - (float)(8 * _2X) * pObj->zoom - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-16 * _2X - OBJIMGGAP) * pObj->zoom), pObj->zoom, false, false, false, true);

		UnSetBlend();

		if (pObj->mainFrame % 20 < 4)
			DrawNeutral(OBJ_ITEM0 + pObj->mainFrame % 4, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - (float)(OBJIMGGAP)*pObj->zoom), 0, pObj->zoom);

		break;
	case OBJ_CLOAKING:
		if (pObj->mainFrame >= 48)
			break;
		else if (pObj->mainFrame < 8)
			SetAlpha(pObj->mainFrame * 4);
		else if (pObj->mainFrame > 40)
			SetAlpha((48 - pObj->mainFrame) * 4);

		goto DEFAULT;
	case OBJ_SOUL:
		if (pObj->status)
			DrawEffect(EFFECT_SLOT0 + pObj->frame, pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y), 0, false, pObj->zoom);
		break;
	case OBJ_WARP:
		if (pObj->status && !isDemo) {
			if (pObj->status < 4)
				DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - robin.playtime % 8), xOffset + pObj->x - rx + pObj->cx / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + pObj->cy - (float)(11 * _2X) * pObj->zoom), 0, false, pObj->zoom);
			else
				DrawEffect(EFFECT_INSIDE_ARROW0 + Abs(4 - robin.playtime % 8), xOffset + pObj->x - rx - (float)(8 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + pObj->cy / 3), 1, false, pObj->zoom);
		}
		break;
	case OBJ_PUSH:
		if (pObj->etc != PUSH_NORMAL && pObj->str == 0)
			DrawNeutral(OBJ_PUSHDEST0, xOffset + pushArray[pObj->etc * 2] * TSIZE - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - pushArray[pObj->etc * 2 + 1] * TSIZE, pObj->dirF, pObj->zoom);

		goto DEFAULT;
	case OBJ_CARPET:
		SetAlpha(32 - pObj->attackFrame * 2);

		goto DEFAULT;
	case OBJ_ICEBREAK:
		SetAlpha(24);
	case OBJ_MAXXTRAP:
	case OBJ_SUNBLOCK:
	case OBJ_BREAKSTONE:
	case OBJ_GOLEMBLOCK:
	case OBJ_BALLBLOCK:
		maPtr = (unsigned char*)&neutralData[pObj->type * NEUTRALDATASIZE];

		DrawNeutral(pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - (float)(OBJIMGGAP)*pObj->zoom), pObj->dirF, pObj->zoom);
		SetAlpha(32);

		if (pObj->status && pObj->motion < *(maPtr + 9) + 3)
			DrawEffect(pObj->motion - (*(maPtr + 9)), xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-TSIZE - OBJIMGGAP) * pObj->zoom), 1 - ao[raidPlayer].dirF, false, pObj->zoom);
		break;
	case OBJ_MAGMA:
		if (pObj->status) {
			//¸¶±×¸¶ Áß´ÜºÎºÐ
			for (i = 0; i < pObj->jumpFrame - 1; i++)
				DrawNeutral(OBJ_MAGMA6, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - (float)(i * 16 * _2X) * pObj->zoom), 0, pObj->zoom);

			//¸¶±×¸¶ ÇÏ´ÜºÎºÐ
			DrawNeutral(OBJ_MAGMA0 + (robin.playtime % 3), xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y), 0, pObj->zoom);

			if (pObj->jumpFrame)
				//¸¶±×¸¶ »ó´ÜºÎºÐ
				DrawNeutral(OBJ_MAGMA3 + (robin.playtime % 3), xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - (float)(i * 16 * _2X) * pObj->zoom), 0, pObj->zoom);
		}
		break;
	case OBJ_BRIDGE:
		for (i = 0; i < 18 - pObj->mainFrame / 2; i += 6) {
			if (i / 6 == (18 - pObj->mainFrame / 2) / 6) {
				DrawNeutral(pObj->motion + (pObj->mainFrame / 2 % 6) + pObj->str * 6, xOffset + pObj->x - rx + (float)(i / 6 * 32 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - pObj->y, 0, pObj->zoom);
				DrawNeutral(pObj->motion + (pObj->mainFrame / 2 % 6) + pObj->str * 6, xOffset + pObj->x + pObj->cx - rx - (float)(i / 6 * 32 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - pObj->y, 1, pObj->zoom);
			}
			else {
				DrawNeutral(pObj->motion + pObj->str * 6, xOffset + pObj->x - rx + (float)(i / 6 * 32 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - pObj->y, 0, pObj->zoom);
				DrawNeutral(pObj->motion + pObj->str * 6, xOffset + pObj->x + pObj->cx - rx - (float)(i / 6 * 32 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - pObj->y, 1, pObj->zoom);
			}
		}
		break;
	case OBJ_STALACTITE:
		if (pObj->etc == 4)
			SetAlpha(pObj->mainFrame);

		DrawBgEffect(pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y), 0, pObj->zoom);
		break;
	case OBJ_SPIKE:
		if (pObj->etc == 4)
			SetAlpha(pObj->mainFrame);

		DrawNeutral(pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y), pObj->dirF, pObj->zoom);
		break;
	case OBJ_MAGNET:
		DrawNeutral(OBJ_MAGNET4 - Abs(robin.playtime % 8 - 4), xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - OBJIMGGAP), pObj->dirF, pObj->zoom);

		if (pObj->etc)
			DrawEffect(MAGNET_ACTIVE0 + (robin.playtime % 5), xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - OBJIMGGAP + 13), 0, false, pObj->zoom);
		break;
	case OBJ_SLED:
		if (pObj->etc == 3)
			SetAlpha(pObj->mainFrame);

		goto DEFAULT;
	case OBJ_INVISIBLE:
		if (pObj->status)
			goto DEFAULT;

		break;
	case OBJ_DIMENSION:
		goto DEFAULT;
	case OBJ_CATCHER:
		if (pObj->status) {
			SetAlpha(24);
			DrawEffect(BUFF_DMG0 + robin.playtime % 5, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + 8 * _2X), 0, false, pObj->zoom);
			SetAlpha(32);
		}
		break;
	case OBJ_CYCLON:
		if (pObj->status)
			DrawNeutral(OBJ_CYCLON7 + robin.playtime % 3, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y), 0, pObj->zoom);
		else
			DrawNeutral(OBJ_CYCLON0 + robin.playtime % 7, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y), 0, pObj->zoom);
		break;
	case OBJ_FLOWER:
		DrawIcon(198, xOffset + pObj->x - 8 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - 16 * _2X - OBJIMGGAP), pObj->zoom, false, false, false, true);
		break;
	case OBJ_GOLD:
		UnSetBlend();
		switch (mapData[7]) {
		case MAPTYPE_TOLEM:	//Åç·½¸¶À» ¹Ù±ù//0
			DrawImage(108 * _2X, 80 * _2X, 0 * _2X, 0 * _2X, xOffset + pObj->x - rx - (float)(6 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP - 6 * _2X) * pObj->zoom), false, false, false, false, false, pObj->zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);

			break;
		case MAPTYPE_TOLEMINSIDE:	//Åç·½¸¶À» Áý¾È//1
			break;
		case MAPTYPE_SWAMP:	//ï¿½ç·¹ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½//2
			DrawImage(108 * _2X, 80 * _2X, 0 * _2X, 0 * _2X, xOffset + pObj->x - rx - (float)(56 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP - 112 * _2X) * pObj->zoom), false, false, false, false, false, pObj->zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(66 * _2X, 32 * _2X, 0 * _2X, 80 * _2X, xOffset + pObj->x - rx - (float)(56 * _2X - 24 * _2X) * pObj->zoom, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP - 32 * _2X) * pObj->zoom), false, false, false, false, false, pObj->zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);

			//°ñµå
			iconZoom = 0.7f;
			for (i = 0; i < 4; i++) {
				//gapX = treeGoldPos[2 * i + 0];
				//gapY = treeGoldPos[2 * i + 1];

				DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, xOffset + pObj->x - rx - (float)(56 * _2X) * pObj->zoom + gapX * pObj->zoom - (float)ITEMICONSIZE * iconZoom * pObj->zoom / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP - 112 * _2X) * pObj->zoom) + gapY * pObj->zoom + (float)ITEMICONSIZE * iconZoom * pObj->zoom / 2, pObj->zoom * iconZoom, COLOR_WHITE, false, true, true);
			}
			//°ñµå¹é
			iconZoom = 0.8f;
			for (i = 0; i < 3; i++) {
				//gapX = treeGoldBagPos[2 * i + 0];
				//gapY = treeGoldBagPos[2 * i + 1];

				DrawIcon(ICON_GOLDBAG, xOffset + pObj->x - rx - (float)(56 * _2X) * pObj->zoom + gapX * pObj->zoom - (float)ITEMICONSIZE * iconZoom * pObj->zoom / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP - 112 * _2X) * pObj->zoom) + gapY * pObj->zoom + (float)ITEMICONSIZE * iconZoom * pObj->zoom / 2, pObj->zoom * iconZoom, COLOR_WHITE, false, true, true);
			}
			//¹æÆÐ
			iconZoom = 0.9f;
			for (i = 0; i < 2; i++) {
				//gapX = treeShieldPos[2 * i + 0];
				//gapY = treeShieldPos[2 * i + 1];

				DrawIcon(ICON_SHIELD, xOffset + pObj->x - rx - (float)(56 * _2X) * pObj->zoom + gapX * pObj->zoom - (float)ITEMICONSIZE * iconZoom * pObj->zoom / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP - 112 * _2X) * pObj->zoom) + gapY * pObj->zoom + (float)ITEMICONSIZE * iconZoom * pObj->zoom / 2, pObj->zoom * iconZoom, COLOR_WHITE, false, true, true);
			}
			//ÇÏÆ®
			iconZoom = 1.0f + (float)(32 - Abs(frame % 32 - 16)) / 160;
			for (i = 0; i < 1; i++) {
				//gapX = treeHeartPos[2 * i + 0];
				//gapY = treeHeartPos[2 * i + 1];

				DrawIcon(ICON_HEART, xOffset + pObj->x - rx - (float)(56 * _2X) * pObj->zoom + gapX * pObj->zoom - (float)ITEMICONSIZE * iconZoom * pObj->zoom / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y + (float)(-OBJIMGGAP - 112 * _2X) * pObj->zoom) + gapY * pObj->zoom + (float)ITEMICONSIZE * iconZoom * pObj->zoom / 2, pObj->zoom * iconZoom, COLOR_WHITE, false, true, true);
			}
			break;
		case MAPTYPE_VALLEY:	//±Ý´ÜÀÇ °è°î//3
			break;
		case MAPTYPE_ATLANTICE:	//ï¿½ï¿½Æ²ï¿½ï¿½Æ¼ï¿½ï¿½//4
			break;
		case MAPTYPE_SEWAGE:	//¾Æµ¨¶óÀÎ ÁöÇÏµµ//5
			break;
		case MAPTYPE_CASTLE:	//¾Æµ¨¶óÀÎ ¼º//6
			break;
		case MAPTYPE_PLAIN:	//ï¿½Æµï¿½ ï¿½ï¿½ï¿?/7
			break;
		case MAPTYPE_ELF:	//º§·Î³× ¸¶À»//8
			break;
		case MAPTYPE_FLAME:	//È«ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½//9
			break;
		case MAPTYPE_FROST:	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½//10
			break;
		case MAPTYPE_THUNDER:	//³úÀüÀÇ °ø¹æ//11
			break;
		case MAPTYPE_LIGHT:	//È²È¥ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½//12
			break;
		case MAPTYPE_GOLEMVALLEY:	//°ñ·½ÀÇ Çù°î//13
			break;
		case MAPTYPE_DARKNESS:	//Ä¥ï¿½ï¿½ï¿½ï¿½ ï¿½É¿ï¿½//14
			break;
		case MAPTYPE_DRAGON:	//µå·¡°ïÀÇ ¹«´ý//15
			break;
		case MAPTYPE_GHOST:	//±ÝÁöµÈ ¶¥//16
			break;
		case MAPTYPE_DEVILCASTLE:	//ï¿½ï¿½ï¿½Õ¼ï¿½//17
			break;
		case MAPTYPE_SPACE:	//ï¿½ï¿½ï¿½Ö°ï¿½ï¿½ï¿½//18
			break;
		}
		//DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, xOffset + pObj->x - 8 * _2X * 2 - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - 16 * _2X * 2 - OBJIMGGAP), pObj->zoom * 2, false, false, false, cvtDest, cvtLayer, buffering);
		break;
	DEFAULT:
	default:
		int obj = GetObjFromPtr(pObj);
		if (movie.robinMotion[obj] != 0) {
			pObj->motion = movie.robinMotion[obj];

			//InitMotion(pObj);
		}

		InitMotion(pObj);

		if (pObj->type < OBJ_LEVER) {
			if (pObj->motion != 0xFF) {
				const unsigned short* usPtr = &neutralOff[pObj->motion * 4];
				int imgFile;

				if (pObj->motion < IMG_OBJ_STONE)
					imgFile = COMMON_IMG;
				else
					imgFile = MAP_OBJ_IMG;

				DrawImage(*(usPtr + 2), *(usPtr + 3), *usPtr, *(usPtr + 1), xOffset + pObj->x - rx + pObj->cpx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - OBJIMGGAP + pObj->cpy + neutralOffset[pObj->motion] - ((pObj->type == OBJ_ITEM && pObj->apx == ITEM_QUEST_REEF) ? 12 * _2X : 0 * _2X) * pObj->zoom), pObj->dirF, false, false, false, false, pObj->zoom, sprite[imgFile], imgFile);
				//MemImage(*(usPtr + 2), *(usPtr + 3), *usPtr, *(usPtr + 1), pObj->x - rx + pObj->cpx, pObj->y - ry - OBJIMGGAP + pObj->cpy + d.neutralOffset[pObj->motion] - ((pObj->type == OBJ_ITEM && pObj->apx == ITEM_QUEST_REEF) ? 12 : 0), imgFile);
			}
		}
		else
			DrawNeutral(pObj->motion, xOffset + pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - OBJIMGGAP), pObj->dirF, pObj->zoom);
		break;
	}

	SetAlpha(32);
}


void DrawShadowPlayer(OBJECT* pObj)
{
	int i, j, k;
	int shadowTileY, shadowBlockY;
	int bcLeft = 0, bcRight = 0;
	int offset = (pObj->x - 12 * _2X < 0) ? 12 * _2X - pObj->x : 0 * _2X;
	int sLeft, sRight;
	int tHeight, bHeight;

	float tempZoom = pObj->zoom;
	pObj->zoom = 1.0f;

	//±×¸²ÀÚ »çÀÌÁî¿¡ µû¸¥ ¸î°³ÀÇ ÆÄÃ÷·Î ºÐ¸®½ÃÅ³²¨³Ä¸¦ °è»êÇÑµÚ
	for (i = (pObj->x - 12 * _2X) / TSIZE; i <= (pObj->x + 12 * _2X) / TSIZE; i++) {
		//ï¿½ï¿½ ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½é¼­ ï¿½Ù´ï¿½ï¿½Ì¶ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ñ´ï¿?
		for (j = pObj->y / TSIZE, tHeight = 0; j < rh - 1; j++) {
			//¹Ù´ÚÀÌ¶û ´ê¾ÒÀ¸¸é
			if (mapInfoArray[mapInfoOff + j * rw + i] >= TILE_BLOCK || (pObj->inTile == GROUND && pObj->onWater > 0 && mapInfoArray[mapInfoOff + j * rw + i] >= TILE_WATER) || j == rh - 2) {
				//±×¸²ÀÚ ÀüÃ¼ÀÇ ÁÂÃø °æ°è¸é : (pObj->x - 12)
				//ï¿½×¸ï¿½ï¿½ï¿½ ï¿½ï¿½Ã¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : (pObj->x + 12)
				//ÇöÀç Å¸ÀÏÀÇ ÁÂÃø °æ°è¸é : i * TSIZE;
				//ï¿½ï¿½ï¿½ï¿½ Å¸ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : (i + 1) * TSIZE
				//±×·Á¾ßÇÒ ÁöÁ¡ÀÇ ÁÂÃø °æ°è¸é : max(pObj->x - 12, i * TSIZE)
				//ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : min(pObj->x + 12, (i + 1) * TSIZE)
				//±×·Á¾ß ÇÒ ±×¸²ÀÚÀÇ Æø : min(pObj->x + 12, (i + 1) * TSIZE) - max(pObj->x - 12, i * TSIZE)

				sLeft = Max(pObj->x - 12 * _2X, i * TSIZE);
				sRight = Min(pObj->x + 12 * _2X, (i + 1) * TSIZE);
				shadowTileY = j * TSIZE;

				if (j == rh - 2)
					shadowTileY += 10000;

				//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ñ´ï¿?
				for (k = ENEMY, shadowBlockY = 20000, bHeight = 0; k < ITEMOBJ; k++) {
					OBJECT* pCompare = &ao[k];
					int compY = PxlUp(pCompare);

					if (pCompare->active && pCompare->block && pCompare->drawHandler && compY < shadowTileY && compY < shadowBlockY && sLeft < PxlRight(pCompare) && PxlLeft(pCompare) < sRight && PxlDown(pObj) <= compY) {
						shadowBlockY = compY;
						bHeight = (compY - pObj->y) / TSIZE;

						bcLeft = Max(PxlLeft(pCompare), sLeft);
						bcRight = Min(PxlRight(pCompare), sRight);
					}
				}

				//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½×¸ï¿½ï¿½Ú°ï¿½ ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ï´ï¿½ ï¿½ï¿½ï¿?
				if (shadowBlockY < shadowTileY) {
					//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½×·ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½×¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ù¸ï¿½
					if (bcLeft == sLeft) {
						pObj->nHeight = bHeight;
						ShadowImage(bcRight - sLeft, 16 * _2X, offset, 0, xOffset + sLeft - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (shadowBlockY - 14 * _2X) - ry, COMMON_IMG, pObj->zoom);

						//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ® ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½×·ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½×¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ù¸ï¿½ï¿½Ù¸ï¿½ Å¸ï¿½ï¿½ï¿½Ê¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Îºï¿½ï¿½ï¿½ ï¿½Ñ¹ï¿½ ï¿½ï¿½ ï¿½×·ï¿½ï¿½Ø´ï¿½.
						if (bcRight != sRight) {
							pObj->nHeight = tHeight;
							ShadowImage(sRight - bcRight, 16 * _2X, offset + bcRight - sLeft, 0, xOffset + bcRight - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (shadowTileY - 14 * _2X) - ry, COMMON_IMG, pObj->zoom);
						}
					}
					//´Ù¸£´Ù¸é
					else {
						//ï¿½ì¼± Å¸ï¿½ï¿½ï¿½Ê¿ï¿½ ï¿½ï¿½ï¿½ÊºÎºï¿½ï¿½ï¿½ ï¿½Ñ¹ï¿½ ï¿½×¸ï¿½ï¿½ï¿½
						pObj->nHeight = tHeight;
						ShadowImage(bcLeft - sLeft, 16 * _2X, offset, 0, xOffset + sLeft - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (shadowTileY - 14 * _2X) - ry, COMMON_IMG, pObj->zoom);

						//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ®ï¿½Ê¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Îºï¿½ï¿½ï¿½ ï¿½×¸ï¿½ï¿½ï¿½
						pObj->nHeight = bHeight;
						ShadowImage(bcRight - bcLeft, 16 * _2X, offset + bcLeft - sLeft, 0, xOffset + bcLeft - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (shadowBlockY - 14 * _2X) - ry, COMMON_IMG, pObj->zoom);
					}
				}
				//Å¸ï¿½Ï¿ï¿½ ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ï´ï¿½ ï¿½ï¿½ï¿?
				else if (shadowTileY < 10000) {
					pObj->nHeight = tHeight;
					ShadowImage(sRight - sLeft, 16 * _2X, offset, 0, xOffset + sLeft - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (shadowTileY - 14 * _2X) - ry, COMMON_IMG, pObj->zoom);
				}

				offset += sRight - sLeft;
				break;
			}

			tHeight++;
		}
	}

	pObj->zoom = tempZoom;
}

void DrawShadowCommon(OBJECT* pObj)
{
	int i, j;
	int offset1, offset2;
	int sLeft;
	int sRight;
	int obj = GetObjFromPtr(pObj);

	//±×¸²ÀÚ »çÀÌÁî¿¡ µû¸¥ ¸î°³ÀÇ ÆÄÃ÷·Î ºÐ¸®½ÃÅ³²¨³Ä¸¦ °è»êÇÑµÚ
	sLeft = PxlLeft(pObj) - 4 * _2X;
	sRight = PxlRight(pObj) + 4 * _2X;

	if (pObj->cpx == 0 || pObj->cx == 0)
		return;

	for (i = sLeft / TSIZE; i <= sRight / TSIZE; i++) {
		//ï¿½ï¿½ ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½é¼­ ï¿½Ù´ï¿½ï¿½Ì¶ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ñ´ï¿?
		pObj->nHeight = 0;

		for (j = PxlDown(pObj) / TSIZE; j < rh - 1; j++) {
			//¹Ù´ÚÀÌ¶û ´ê¾ÒÀ¸¸é
			if (mapInfoArray[mapInfoOff + j * rw + i] >= TILE_BLOCK) {
				int y = j * TSIZE + ry - 14 * _2X;

				if (obj >= NEUTRAL) {
					y += pObj->attr;

					if (pObj->type == OBJ_BOX)
						y -= 3 * _2X;
				}

				//±×¸²ÀÚ ÀüÃ¼ÀÇ ÁÂÃø °æ°è¸é : sLeft
				//ï¿½×¸ï¿½ï¿½ï¿½ ï¿½ï¿½Ã¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : sRight
				//ÇöÀç Å¸ÀÏÀÇ ÁÂÃø °æ°è¸é : i * TSIZE;
				//ï¿½ï¿½ï¿½ï¿½ Å¸ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : (i + 1) * TSIZE
				//±×·Á¾ßÇÒ ÁöÁ¡ÀÇ ÁÂÃø °æ°è¸é : max(sLeft, i * TSIZE)
				//ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : min(sRight, (i + 1) * TSIZE)
				//±×·Á¾ß ÇÒ ±×¸²ÀÚÀÇ Æø : min(sRight, (i + 1) * TSIZE) - max(sLeft, i * TSIZE)
				if (sLeft >= i * TSIZE)
					//ï¿½ï¿½ï¿½ï¿½
					ShadowImage((i + 1) * TSIZE - sLeft, 16 * _2X, 24 * _2X, 0, xOffset + (float)sLeft - rx, (STATUSWIN_Y + (rh - 4) * TSIZE - y), COMMON_IMG, pObj->zoom);
				else if (sRight <= (i + 1) * TSIZE)
					//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
					ShadowImage(sRight - i * TSIZE, 16 * _2X, 64 * _2X - (sRight - i * TSIZE), 0, xOffset + (float)i * TSIZE - rx, (STATUSWIN_Y + (rh - 4) * TSIZE - y), COMMON_IMG, pObj->zoom);
				else {
					offset1 = 0;
					offset2 = 0;

					if (sLeft >= (i - 1) * TSIZE && TSIZE - (sLeft % TSIZE) < 12 * _2X) {
						//ï¿½ï¿½ï¿½Ê¿ï¿½ï¿½ï¿½ ï¿½Î¹ï¿½Â°
						offset1 = (sLeft + 12 * _2X) % TSIZE;
						ShadowImage((sLeft + 12 * _2X) % TSIZE, 16 * _2X, 36 * _2X - offset1, 0, xOffset + (float)i * TSIZE - rx, (float)(STATUSWIN_Y + (rh - 4) * TSIZE - y), COMMON_IMG, pObj->zoom);
					}

					if (sRight < (i + 2) * TSIZE && sRight % TSIZE < 12 * _2X) {
						//ï¿½ï¿½ï¿½ï¿½ï¿½Ê¿ï¿½ï¿½ï¿½ ï¿½Î¹ï¿½Â°
						offset2 = (i + 1) * TSIZE - (sRight - 12 * _2X);
						ShadowImage((i + 1) * TSIZE - (sRight - 12 * _2X), 16 * _2X, 52 * _2X, 0, xOffset + (float)(sRight - 12 * _2X) - rx, (float)(STATUSWIN_Y + (rh - 4) * TSIZE - y), COMMON_IMG, pObj->zoom);
					}

					ShadowImage(TSIZE - (offset1 + offset2), 16 * _2X, 36 * _2X, 0, xOffset + (float)(i * TSIZE + offset1) - rx, STATUSWIN_Y + (float)((rh - 4) * TSIZE - y), COMMON_IMG, pObj->zoom);
				}
				break;
			}

			pObj->nHeight++;
		}
	}
}

int GetTypeFromCmf(int cmf)
{
	int i;
	for (i = 0; i < TOTALENEMY; i++) {
		if (enemyData[i * ENEMYDATASIZE + ENEMYDATA_CMF] == cmf)
			return i;
	}
}


int GetDistanceTile(OBJECT* pObj, int dist)
{
	int count = 0;
	int tSwap = pObj->x;

	pObj->x += (pObj->dirX == LEFT) ? -50 * _2X : 50 * _2X;

	while (!TileCrash(pObj) && count < dist) {
		pObj->x += pObj->dirX == LEFT ? -TSIZE : TSIZE;
		count++;
	}

	pObj->x = tSwap;

	return count;
}

void DianaStoneMove(OBJECT* pObj)
{
	if (pObj->motion >= OBJ_BOARD5)
		pObj->motion = Max(OBJ_BOARD5, OBJ_BOARD5 - 16 + (pObj->mainFrame % 20));
	else
		pObj->motion++;

	pObj->mainFrame++;
}