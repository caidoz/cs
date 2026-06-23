#include "Core.h"
#include "Data.h"
#include "Func.h"

// Utility 함수들
unsigned short Convert_Char_KSC5601_To_UCS2(unsigned char byte1, unsigned char byte2)
{
	int tab_idx = ((int)byte1 - 0x00a1) * 94 + (int)byte2 - 0x00a1;
	signed short code_ucs2;

	if (tab_idx - 1410 >= 0 && tab_idx - 1410 < sizeof(unicode_table) / 2) {
		code_ucs2 = unicode_table[tab_idx - 1410];

		if (code_ucs2 != -1)
			return code_ucs2;
	}

	return 0;
}

int TextToString(char* src, int count, char* dst)
{
	unsigned short unicode;
	unsigned char bytes[4];
	int nbytes;
	int i, j;
	int len = 0;

	i = 0;

	for (i = 0; i < count; i++) {
		if (!src[i])
			break;
		unicode = src[i];
		if (unicode < 0x80) {
			nbytes = 1;
			bytes[0] = unicode;
		}
		else {
			unicode = Convert_Char_KSC5601_To_UCS2(src[i], src[i + 1]);
			//unicode -= 0xAC00;
			//UCS2toUTF8(&unicode, 1, (char*)bytes[0]);

			if (unicode < 0x800) {
				nbytes = 2;
				bytes[1] = (unicode & 0x3f) | 0x80;
				bytes[0] = ((unicode << 2) & 0xcf00 | 0xc000) >> 8;
			}
			else {
				nbytes = 3;
				bytes[2] = (unicode & 0x3f) | 0x80;
				bytes[1] = ((unicode << 2) & 0x3f00 | 0x8000) >> 8;
				bytes[0] = ((unicode << 4) & 0x3f0000 | 0xe00000) >> 16;
			}
			i++;
		}

		for (j = 0; j < nbytes; j++) {
			dst[len] = bytes[j];
			len++;
		}
	}
	dst[len] = '\0';
	return len;
}

/* UCS2toUTF8
* converts UCS2 array to UTF8 string
*/
int UCS2toUTF8(unsigned short* ucs2, int count, char* dst)
{
	unsigned short unicode;
	unsigned char bytes[4];
	int nbytes;
	int i, j;
	int len = 0;

	for (i = 0; i < count; i++) {
		unicode = ucs2[i];

		if (unicode < 0x80) {
			nbytes = 1;
			bytes[0] = unicode;
		}
		else if (unicode < 0x800) {
			nbytes = 2;
			bytes[1] = (unicode & 0x3f) | 0x80;
			bytes[0] = ((unicode << 2) & 0xcf00 | 0xc000) >> 8;
		}
		else {
			nbytes = 3;
			bytes[2] = (unicode & 0x3f) | 0x80;
			bytes[1] = ((unicode << 2) & 0x3f00 | 0x8000) >> 8;
			bytes[0] = ((unicode << 4) & 0x3f0000 | 0xe00000) >> 16;
		}

		for (j = 0; j < nbytes; j++) {
			dst[len] = bytes[j];
			len++;
		}
	}
	dst[len] = '\0';
	return len;
}

void TouchArrow2(int flag, int x, int y, int pos, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	//flag// 1==상하좌우//2==좌우//3=v=상하//
	if (touch && !touchDrawButton) {
		SetAlpha(32 - Abs(frame * 2 % 32 - 16));
		switch (flag) {
		case 1:
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + DX / 2 - 21 * _2X, y + (DY >> 1) + pos, false, 270.0f, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + DX - 16 * _2X, y + (DY >> 1) + 41 * _2X / 2 + 1 * _2X, false, false, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + DX / 2 - 21 * _2X, y + (DY >> 1) - pos + 16 * _2X, false, 90.0f, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + 0 * _2X, y + (DY >> 1) + 41 * _2X / 2 + 1 * _2X, false, 180.0f, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			break;
		case 2:
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + DX - 16 * _2X - 8 * _2X, y + pos + 21 * _2X, false, false, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + 8 * _2X, y + pos + 21 * _2X, false, 180.0f, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			break;
		case 3:
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + DX / 2 - 21 * _2X, y - pos, false, 90.0f, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + DX / 2 - 21 * _2X, y + pos - 16 * _2X, false, 270.0f, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			break;
		case 4:
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + 0 * _2X, y + pos + 21 * _2X, false, 180.0f, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			break;
		case 5:
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + DX - 16 * _2X, y + pos + 21 * _2X, false, false, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			break;
		case 6:
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + (DX - STATUSWIN_X) / 2 + 164 * _2X + 144 * _2X - 16 * _2X, y + pos + 21 * _2X, false, false, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			DrawImage(16 * _2X, 41 * _2X, 240 * _2X, 0 * _2X, x + (DX - STATUSWIN_X) / 2 + 164 * _2X - 8 * _2X, y + pos + 21 * _2X, false, 180.0f, false, false, false, 1.0f, sprite[TOUCH_IMG], cvtDest, cvtLayer, TOUCH_IMG, buffering);
			break;
		}
		SetAlpha(32);
	}
}

void DrawPlayerCostume(
	int type,
	int weaponDetail, int weaponGrade,
	int gloveDetail, int gloveGrade,
	int helmDetail, int helmGrade,
	int armorDetail, int armorGrade,
	int pantsDetail, int pantsGrade,
	int bootsDetail, int bootsGrade,

	int x, int y, int dirX, int attackMotion, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	ao[SOLDIER].x = x;
	ao[SOLDIER].y = y;

	ao[SOLDIER].type = ao[SOLDIER].cmf = type;

	if (weaponDetail == -1) {
		ao[SOLDIER].equipImg[EQUIP_WEAPON] = 0;
		ao[SOLDIER].equip[EQUIP_WEAPON].type = EMPTY;
	}
	else {
		ao[SOLDIER].equipImg[EQUIP_WEAPON] = 1 + weaponDetail;
		ao[SOLDIER].equip[EQUIP_WEAPON].detail = weaponDetail;
		ao[SOLDIER].equip[EQUIP_WEAPON].type = ITEM_SWORD + ao[SOLDIER].type;

	}
	ao[SOLDIER].equip[EQUIP_WEAPON].grade = weaponGrade;

	if (gloveDetail == -1) {
		ao[SOLDIER].equipImg[EQUIP_GLOVE] = 0;
		ao[SOLDIER].equip[EQUIP_GLOVE].type = EMPTY;
	}
	else {
		ao[SOLDIER].equipImg[EQUIP_GLOVE] = 1 + gloveDetail;
		ao[SOLDIER].equip[EQUIP_GLOVE].detail = gloveDetail;
		ao[SOLDIER].equip[EQUIP_GLOVE].type = ITEM_GUNTLET + ao[SOLDIER].type;

	}
	ao[SOLDIER].equip[EQUIP_GLOVE].grade = gloveGrade;

	if (helmDetail == -1) {
		ao[SOLDIER].equipImg[EQUIP_HELM] = 0;
		ao[SOLDIER].equip[EQUIP_HELM].type = EMPTY;
	}
	else {
		ao[SOLDIER].equipImg[EQUIP_HELM] = 1 + helmDetail;
		ao[SOLDIER].equip[EQUIP_HELM].detail = helmDetail;
		ao[SOLDIER].equip[EQUIP_HELM].type = ITEM_HELM + ao[SOLDIER].type;

	}
	ao[SOLDIER].equip[EQUIP_HELM].grade = helmGrade;

	if (armorDetail == -1) {
		ao[SOLDIER].equipImg[EQUIP_ARMOR] = 0;
		ao[SOLDIER].equip[EQUIP_ARMOR].type = EMPTY;
	}
	else {
		ao[SOLDIER].equipImg[EQUIP_ARMOR] = 1 + armorDetail;
		ao[SOLDIER].equip[EQUIP_ARMOR].detail = armorDetail;
		ao[SOLDIER].equip[EQUIP_ARMOR].type = ITEM_ARMOR + ao[SOLDIER].type;

	}
	ao[SOLDIER].equip[EQUIP_ARMOR].grade = armorGrade;

	if (pantsDetail == -1) {
		ao[SOLDIER].equipImg[EQUIP_PANTS] = 0;
		ao[SOLDIER].equip[EQUIP_PANTS].type = EMPTY;
	}
	else {
		ao[SOLDIER].equipImg[EQUIP_PANTS] = 1 + pantsDetail;
		ao[SOLDIER].equip[EQUIP_PANTS].detail = pantsDetail;
		ao[SOLDIER].equip[EQUIP_PANTS].type = ITEM_KILT + ao[SOLDIER].type;

	}
	ao[SOLDIER].equip[EQUIP_PANTS].grade = pantsGrade;

	if (bootsDetail == -1) {
		ao[SOLDIER].equipImg[EQUIP_BOOTS] = 0;
		ao[SOLDIER].equip[EQUIP_BOOTS].type = EMPTY;
	}
	else {
		ao[SOLDIER].equipImg[EQUIP_BOOTS] = 1 + bootsDetail;
		ao[SOLDIER].equip[EQUIP_BOOTS].detail = bootsDetail;
		ao[SOLDIER].equip[EQUIP_BOOTS].type = ITEM_GREAVES + ao[SOLDIER].type;

	}
	ao[SOLDIER].equip[EQUIP_BOOTS].grade = bootsGrade;

	DrawPlayer(&ao[SOLDIER], (attackMotion == 2 ? motionData[64 + (ao[SOLDIER].frame / 2 % 32)] : (attackMotion == true ? motionData[ao[SOLDIER].frame / 2 % 64] : 0)), x, y, dirX, zoom, false, false, true, cvtDest, cvtLayer, buffering);
	ao[SOLDIER].frame++;
}

void StatusDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int motion;
	int nearEnemy = NearEnemy(&ao[raidPlayer]);
	int xPos = 0;
	ITEM* it;
	int curIcon;
	float width;
	int i;
	int xGap, yGap;
	int drawHandleBack = drawHandle;
	int userIdx = PLAYER;
	int stageCrewIdx;
	int stageCrewType;
	long long upgradePrice;

	int stageBossIdx = GetStageBossIdx();
	int stageBossType = GetStageBossType();
	int stageBossMaxHp = (robin.stage * TOTALROOM + robin.room + 1) * (100 + enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_ADDHP]);


	xGap = -4 * _2X;
	yGap = TSIZE;

#ifdef CENTERDISPLAY

	switch (drawHandle) {
	case MD_BATTLE:
		break;
	case MD_PLAY:
	//case MD_BATTLE:

		//스테이지 정보


		if (waveStatus == WAVESTATUS_READY) {
			//TEST
			//DrawStageEnemyWave(x + (float)(BATTLEPOSITION_ENEMY_X)* zoom, STATUSWIN_Y + (float)56 * _2X * zoom, stageBossType, zoom, cvtDest, cvtLayer, buffering);

			//SetRectPoint(x + (float)(BATTLEPOSITION_ENEMY_X - 40 * _2X) * zoom, STATUSWIN_Y + (float)136 * _2X * zoom, (float)(80 * _2X) * zoom, (float)(80 * _2X) * zoom, TOUCH_FUNC_POPUP_STAGEREWARD);

			//if (robin.gold >= GetStageAdmissionFee()) {
			//	SetRectPoint(x + (float)(BATTLEPOSITION_ENEMY_X - 40 * _2X * STAGESTARBUTTONZOOM) * zoom, STATUSWIN_Y + (float)(56) * _2X * zoom, (float)(80 * _2X) * STAGESTARBUTTONZOOM * zoom, (float)BUYBUTTON_Y * STAGESTARBUTTONZOOM * zoom, TOUCH_FUNC_GOTOPLAY);
			//}

			//DrawCmfDetailShadow(enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[stageBossType * 5 + 0] + (frame / 2 % crewPos[stageBossType * 5 + 1]), x + (float)(BATTLEPOSITION_ENEMY_X)*zoom, STATUSWIN_Y + (float)56 * _2X * zoom, LEFT, /*enemyIconZoom[stageBossType] **/ zoom, cvtDest, cvtLayer, buffering);

		}
		else if (waveStatus == WAVESTATUS_PLAY) {
			ao[ITEMBOX].y += ao[ITEMBOX].dy;
			if (ao[ITEMBOX].y >= 1024 * _2X)
				ao[ITEMBOX].y = 1024 * _2X;
		}
		else if (waveStatus == WAVESTATUS_END) {
			ao[ITEMBOX].y += ao[ITEMBOX].dy;
			if (ao[ITEMBOX].y < ao[ITEMBOX].ny)
				ao[ITEMBOX].y = ao[ITEMBOX].ny;
		}


		break;
	case MD_RAID:
		//DrawWindow2(xOffset + DX / 2 - DRAWROULETTENUM_SUB_WIDTH / 2, STATUSWIN_Y + DRAWRAIDNUMGAP + 12 * _2X, DRAWROULETTENUM_SUB_WIDTH, DRAWROULETTENUM_SUB_HEIGHT, COLOR_NAVY, 1.0f, cvtDest, cvtLayer, buffering);

		//EnemyUserProfileDraw(robin.enemyUserIdx, robin.stage, robin.room, xOffset + DX / 2 - RAIDGOLDBARWIDTH / 2/*100 * _2X*/, yPos + ENEMYUSERINFOGAP, 1.0f, cvtDest, cvtLayer, buffering);


		break;
	case MD_BOSSRAID:

		break;
	}

#else

#endif
}

void ShopMenuDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawIcon(ICON_EVENT_BOX, x, y, zoom, COLOR_BROWN, false, true, true, cvtDest, cvtLayer, buffering);

}

void EnemyUserProfileDraw_Box(HOUSE* housePtr, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float width = 0;
	float textPos = 0.0f;
	float iconZoom = zoom * 0.8f;
	float textZoom = zoom * 0.6f;
	float profileZoom = zoom * 1.4f;

	//long long betCnt = housePtr->gold * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet);
	long long betCnt = housePtr->gold;


	DrawImage(25 * _2X, 57 * _2X, 0 * _2X, 130 * _2X, x + (float)(RAIDGOLDBARWIDTH)*zoom / 2 - (float)25 * _2X * zoom, y + (float)-0 * _2X * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + MAPTYPE_CASTLE], cvtDest, cvtLayer, MAP_OBJ_IMG + MAPTYPE_CASTLE, buffering);
	DrawImage(25 * _2X, 57 * _2X, 0 * _2X, 130 * _2X, x + (float)(RAIDGOLDBARWIDTH)*zoom / 2 - (float)25 * _2X * zoom + (float)25 * _2X * zoom, y + (float)-0 * _2X * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + MAPTYPE_CASTLE], cvtDest, cvtLayer, MAP_OBJ_IMG + MAPTYPE_CASTLE, buffering);
	DrawLabel(x, y - (float)(RAIDGOLDBARHEIGHT - 16 * _2X) * zoom, TEXT_NICKNAME + robin.enemyUserIdx, 0.6f * zoom, cvtDest, cvtLayer, buffering);


	//DrawLabel(x + (float)(RAIDGOLDBARWIDTH)* zoom / 2 - (float)40 * _2X * zoom, y + (float)26 * _2X * zoom, TEXT_ALPHA_COINSWORD, zoom, cvtDest, cvtLayer, buffering);
	DrawFrame(x + (float)(RAIDGOLDBARWIDTH - PROFILEIMG_X * 0.85f) / 2 * zoom + (float)-1 * _2X * zoom, y - (float)(23 * _2X) * zoom, (float)(PROFILEIMG_X + 2 * _2X) * 0.85f * zoom, (float)(PROFILEIMG_Y + 2 * _2X) * 0.8f * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
	DrawImage(PROFILEIMG_X, PROFILEIMG_Y, 0, 0, x + (float)(RAIDGOLDBARWIDTH - PROFILEIMG_X * 0.85f) / 2 * zoom, y - (float)(24 * _2X) * zoom, false, false, false, false, false, zoom * 0.85f, sprite[PROFILE_IMG + housePtr->userProfileImgIdx], cvtDest, cvtLayer, PROFILE_IMG + housePtr->userProfileImgIdx, buffering);

	//MemRectRound(x, y, (float)RAIDGOLDBARWIDTH * zoom, (float)14 * _2X * zoom, COLOR_NAVY, 1 * _2X, cvtDest, cvtLayer, buffering);
	//CenterText(TEXT_NICKNAME + robin.enemyUserIdx, x + (float)RAIDGOLDBARWIDTH / 2 * zoom, y - (float)(2 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);

	//DrawLabel(x, y + (float)(16 * _2X) * zoom, TEXT_NICKNAME + 38/*robin.enemyUserIdx*/, textZoom, cvtDest, cvtLayer, buffering);
	//CenterText(TEXT_NICKNAME + robin.enemyUserIdx, x + (float)RAIDGOLDBARWIDTH / 2 * zoom, y - (float)(PROFILEIMG_Y + 2 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

	//DrawRouletteNumIcon(betCnt, ICON_GOLD + frame % GOLDICONFRAME, x + (float)RAIDGOLDBARWIDTH / 2 * zoom, y - (float)(0 * _2X) * zoom, false, CENTER, zoom, cvtDest, cvtLayer, buffering);

	width = (float)(ITEMICONSIZE + 2 * _2X) * iconZoom + GetBigNumDx(betCnt, false, NUM_FONT_NORMAL, false, true, (float)(RAIDGOLDBARWIDTH - PROFILEIMG_X) * zoom, zoom, false);

	DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(RAIDGOLDBARWIDTH / 2 * zoom - width / 2), y - (float)(10 * _2X) * zoom, iconZoom, COLOR_BROWN, false, false, true, cvtDest, cvtLayer, buffering);
#ifdef NUMTTF
	DrawBigNumTTF(betCnt, x + (float)(RAIDGOLDBARWIDTH / 2 * zoom - width / 2) + (float)(ITEMICONSIZE + 2 * _2X) * iconZoom, y - (float)(10 * _2X + 1 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, false, false, (float)(RAIDGOLDBARWIDTH - PROFILEIMG_X) * zoom, true, zoom, false, cvtDest, cvtLayer, buffering);
#else
	DrawBigNum(betCnt, x + (float)(RAIDGOLDBARWIDTH / 2 * zoom - width / 2) + (float)(ITEMICONSIZE + 2 * _2X) * iconZoom, y - (float)(10 * _2X + 1 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, false, false, (float)(RAIDGOLDBARWIDTH - PROFILEIMG_X) * zoom, true, zoom, false, cvtDest, cvtLayer, buffering);
#endif

}

void EnemyUserProfileDraw(HOUSE* housePtr, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float width = 0;
	float textPos = 0.0f;
	float iconZoom = zoom * 1.2f;
	float textZoom = zoom * 0.8f;
	float profileZoom = zoom * 1.5f;
	long long betCnt = housePtr->gold;

	width = (float)PROFILEIMG_X * profileZoom + (float)(ITEMICONSIZE + 2 * _2X) * iconZoom + GetBigNumDx(betCnt, false, NUM_FONT_NORMAL, false, true, (float)(RAIDGOLDBARWIDTH - PROFILEIMG_X) * zoom, zoom * 1.5f, false);

	return;

	DrawLabel(x - width / 2 + (float)(PROFILEIMG_X + 4 * _2X) * profileZoom, y, TEXT_NICKNAME + robin.enemyUserIdx, zoom, cvtDest, cvtLayer, buffering);


	DrawFrame(x - width / 2, y - (float)(1 * _2X) * zoom, (float)(PROFILEIMG_X + 2 * _2X) * profileZoom, (float)(PROFILEIMG_Y + 2 * _2X) * profileZoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
	DrawImage(PROFILEIMG_X, PROFILEIMG_Y, 0, 0, x - width / 2 + (float)1 * _2X * profileZoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, profileZoom, sprite[PROFILE_IMG + housePtr->userProfileImgIdx], cvtDest, cvtLayer, PROFILE_IMG + housePtr->userProfileImgIdx, buffering);

	
	DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x - width / 2 + (float)(PROFILEIMG_X + 4 * _2X) * profileZoom, y - (float)(32 * _2X) * zoom, iconZoom, COLOR_BROWN, false, false, true, cvtDest, cvtLayer, buffering);
#ifdef NUMTTF
	DrawBigNumTTF(betCnt, x + (float)(RAIDGOLDBARWIDTH / 2 * zoom - width / 2) + (float)(ITEMICONSIZE + 2 * _2X) * iconZoom, y - (float)(10 * _2X + 1 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, false, false, (float)(RAIDGOLDBARWIDTH - PROFILEIMG_X) * zoom, true, zoom, false, cvtDest, cvtLayer, buffering);
#else
	DrawBigNum(betCnt, x - width / 2 + (float)(PROFILEIMG_X + 4 * _2X) * profileZoom + (float)(ITEMICONSIZE + 2 * _2X) * iconZoom, y - (float)(32 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, false, false, width, true, zoom * 1.5f, false, cvtDest, cvtLayer, buffering);
#endif

}

void EffectDrawOnlyBg(int yPos, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j, y;
	const unsigned char* bgPtr;
	const unsigned short* bgPtrShort;
	signed short* bbPtr = bubbleXY;
	OBJECT* pPlayer;

#ifndef BGEFFECTDRAW
	return;
#endif

	//수중 거품
	for (i = 0; i < 6; i++, bbPtr += 2) {
		if (*bbPtr || *(bbPtr + 1)) {
			if (drawHandle == MD_PLAY) {
				DrawArray(IMG_BUBBLE_SWAMP0 + (mapData[7] == MAPTYPE_SWAMP ? 0 : 2), (float)(xOffset + *bbPtr - rx - 7 * _2X + Random(4)) * zoom, yPos + (float)((rh - 4) * TSIZE + *(bbPtr + 1) - ry - 7 * _2X + Random(4) * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
				DrawArray(IMG_BUBBLE_SWAMP1 + (mapData[7] == MAPTYPE_SWAMP ? 0 : 2), (float)(xOffset + *bbPtr - rx - 3 * _2X + Random(4)) * zoom, yPos + (float)((rh - 4) * TSIZE + *(bbPtr + 1) - ry - 3 * _2X + Random(4) * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			}
			else {
				DrawArray(IMG_BUBBLE_SWAMP0 + (mapData[7] == MAPTYPE_SWAMP ? 0 : 2), (float)(xOffset + *bbPtr - rx - 7 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE + *(bbPtr + 1) - ry - 7 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
				DrawArray(IMG_BUBBLE_SWAMP1 + (mapData[7] == MAPTYPE_SWAMP ? 0 : 2), (float)(xOffset + *bbPtr - rx - 3 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE + *(bbPtr + 1) - ry - 3 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			}
		}
	}

	//수면효과
	for (i = 0; i < mapData[4]; i++) {
		if (mapRect[i * 5 + 4] == 254) {
			SetAlpha(24);

			for (j = 0; j < mapRect[i * 5 + 2]; j += 3)
				//water.bmp
				DrawImage(Min((mapRect[i * 5 + 2] - j) * 16, 48) * _2X, 12 * _2X, 0 * _2X, 16 * _2X + ((robin.playtime / 2 + j) % 3) * 28 * _2X, (float)(xOffset + ((mapRect[i * 5] + j) << 4) * _2X - rx) * zoom, yPos + (float)((rh - 4) * TSIZE + (mapRect[i * 5 + 1] << 4) * _2X - ry - 12 * _2X) * zoom, false, false, false, false, false, zoom, sprite[WATER_IMG], cvtDest, cvtLayer, WATER_IMG, buffering);

			//웨이브
			for (j = 0; j < realPlayerCnt; j++) {
				pPlayer = &ao[PLAYER + j];

				if (pPlayer->x >= (mapRect[i * 5] << 4) * _2X && pPlayer->x <= ((mapRect[i * 5] + mapRect[i * 5 + 2]) << 4) * _2X && pPlayer->y >= (mapRect[i * 5 + 1] << 4) * _2X - 12 * _2X && pPlayer->y <= (mapRect[i * 5 + 1] << 4) * _2X + 12 * _2X) {
					bgPtrShort = &atlanticeImg[swampSplash[(robin.playtime % 6) * 4] * 4];
					DrawImage(*(bgPtrShort + 2), *(bgPtrShort + 3), *bgPtrShort, *(bgPtrShort + 1), (float)(xOffset + pPlayer->x + swampSplash[(robin.playtime % 6) * 4 + 1 + pPlayer->dirF] - rx) * zoom, yPos + (float)((rh - 4) * TSIZE + (mapRect[i * 5 + 1] << 4) * _2X - 6 * _2X + swampSplash[(robin.playtime % 6) * 4 + 3] - ry) * zoom, false, false, false, false, false, zoom, sprite[WATER_IMG], cvtDest, cvtLayer, WATER_IMG, buffering);
				}
			}

			SetAlpha(32);
		}
	}

	pPlayer = &ao[raidPlayer];

	//입수효과
	if (splash.frame && splashType != 0) {
		if (splashType == 1) {
			//아래쪽
			bgPtrShort = &atlanticeImg[swampSplash[(splash.frame - 1) * 4] * 4];
			DrawImage(*(bgPtrShort + 2), *(bgPtrShort + 3), *bgPtrShort, *(bgPtrShort + 1), (float)(xOffset + splash.x + swampSplash[(splash.frame - 1) * 4 + 1 + pPlayer->dirF] - rx) * zoom, yPos + (float)((rh - 4) * TSIZE + splash.y + swampSplash[(splash.frame - 1) * 4 + 3] - ry + 4 * _2X) * zoom, false, false, false, false, false, zoom, sprite[WATER_IMG], cvtDest, cvtLayer, WATER_IMG, buffering);

			bgPtrShort = &atlanticeImg[swampSplash[(splash.frame + 5) * 4] * 4];
			DrawImage(*(bgPtrShort + 2), *(bgPtrShort + 3), *bgPtrShort, *(bgPtrShort + 1), (float)(xOffset + splash.x + swampSplash[(splash.frame + 5) * 4 + 1 + splash.dir] - rx) * zoom, yPos + (float)((rh - 4) * TSIZE + splash.y + swampSplash[(splash.frame + 5) * 4 + 3] - ry) * zoom, false, false, false, false, false, 1.0f, sprite[WATER_IMG], cvtDest, cvtLayer, WATER_IMG, buffering);
		}
		else
			DrawBgEffect(BG4_SIDE2 + 1 - splash.frame, (float)(xOffset + splash.x - rx) * zoom, yPos + (float)((rh - 4) * TSIZE + splash.y - ry) * zoom, splash.dir, zoom, cvtDest, cvtLayer, buffering);
	}

	//수중 사각형
	switch (mapData[7]) {
	case MAPTYPE_SWAMP:
	case MAPTYPE_ATLANTICE:
	case MAPTYPE_FROST:
	case MAPTYPE_CASTLE:
		SetAlpha(16);

		for (i = 0; i < mapData[4]; i++) {
			bgPtr = &mapRect[i * 5];

			if (*(bgPtr + 4) < 254) {
				MemRect((float)(xOffset + (*bgPtr << 3) * _2X - rx) * zoom, yPos + (float)((rh - 4) * TSIZE - (*(bgPtr + 1) << 3) * _2X - ry) * zoom, (float)(*(bgPtr + 2) << 3) * _2X * zoom, (float)(*(bgPtr + 3) << 3) * _2X * zoom, 0x392439, cvtDest, cvtLayer, buffering);

				if (mapData[7] != MAPTYPE_SWAMP/* && option.effect*/) {
					for (j = 0; j < *(bgPtr + 3); j += 2)
						Waterize((float)(xOffset + (*bgPtr << 3) * _2X - rx) * zoom, yPos + (float)((rh - 4) * TSIZE - ((*(bgPtr + 1) + j) << 3) * _2X - ry) * zoom, (float)(*(bgPtr + 2) << 3) * _2X * zoom, (float)Min(16, (*(bgPtr + 3) - j) << 3) * _2X * zoom, cvtDest, cvtLayer, buffering);
				}
			}
		}

		SetAlpha(32);
		break;
	case MAPTYPE_SEWAGE:
		//하수구 폭포
		for (i = 0; i < mapData[4]; i++) {
			bgPtr = &mapRect[i * 5];
			y = (rh - 4) * TSIZE - (*(bgPtr + 1) << 4) * _2X - ry;
			j = (*bgPtr << 4) * _2X - rx - *(bgPtr + 2) * _2X / 2;

			//if (PxlUp(pPlayer) - ry > y + *(bgPtr + 3) && PxlLeft(pPlayer) - rx < j + *(bgPtr + 2) && PxlRight(pPlayer) - rx > j)
			//	SetSectionClip(0, 0, DX, PxlUp(pPlayer) - ry, buffering);

			SetAlpha(16);
			MemRect((float)(xOffset + j) * zoom, yPos + (float)(y + *(bgPtr + 3) * _2X) * zoom, (float)*(bgPtr + 2) * _2X * zoom, 1000, 0x1C6DCC, cvtDest, cvtLayer, buffering);
			SetAlpha(32);

			DrawBgEffect((*(bgPtr + 2) == 10 ? 5 : 0) + BG5_WATERFALL0 + (robin.playtime % 5), (float)(xOffset + (*bgPtr << 4) * _2X - rx) * zoom, yPos + (float)y * zoom, 0, zoom, cvtDest, cvtLayer, buffering);

			do {
				DrawBgEffect((*(bgPtr + 2) == 10 ? 5 : 0) + BG5_WATER0 + (robin.playtime % 5), (float)(xOffset + (*bgPtr << 4) * _2X - rx) * zoom, yPos + (float)y * zoom, 0, zoom, cvtDest, cvtLayer, buffering);
				y -= sewageFallHeight[(*(bgPtr + 2) == 10 ? 5 : 0) + (robin.playtime % 5)];
			} while (y > 0);
#ifdef CLIPPING
			if (clipY2 > 0) {
#endif
				y = (rh - 4) * TSIZE - (*(bgPtr + 1) << 4) * _2X - ry;
				j = (*bgPtr << 4) * _2X - rx - *(bgPtr + 2) * _2X / 2;

				//SetSectionClip(0, yPos + PxlUp(pPlayer) - ry, DX, DY - PxlUp(pPlayer) + ry, buffering);

				SetAlpha(8);
				MemRect((float)(xOffset + j) * zoom, yPos + (float)(y + *(bgPtr + 3) * _2X) * zoom, (float)(*(bgPtr + 2) * _2X) * zoom, 1000, 0x1C6DCC, cvtDest, cvtLayer, buffering);

				do {
					DrawBgEffect((*(bgPtr + 2) == 10 ? 5 : 0) + BG5_WATER0 + (robin.playtime % 5), (float)(xOffset + (*bgPtr << 4) * _2X - rx) * zoom, yPos + (float)y * zoom, 0, zoom, cvtDest, cvtLayer, buffering);
					y -= (float)(sewageFallHeight[(*(bgPtr + 2) == 10 ? 5 : 0) + (robin.playtime % 5)]) * zoom;
				} while (y > 0);

				//UnSectionClip(false);
				SetAlpha(24);

				if (pPlayer->active)
					DrawBgEffect(2000 + BG_WATERFALL_SPLASH0 + (*(bgPtr + 2) == 10 ? 3 : 0) + robin.playtime % 3, (float)(xOffset + (*bgPtr << 4) * _2X - rx) * zoom, yPos + (float)(pPlayer->y - OBJIMGGAP - ry) * zoom, 0, zoom, cvtDest, cvtLayer, buffering);
#ifdef CLIPPING
			}
#endif

			SetAlpha(32);
		}
		break;
	case MAPTYPE_DARKNESS:
		//어둠의 정령 진흙
		for (i = 0; i < mapData[5]; i++) {
			signed short* mbObj = &mapBackObj[i * 3];

			if (*mbObj == IMG_BG14_1) {
				bgPtrShort = &backObjImg[Abs(*mbObj) * 4];
				y = (rh - 4) * TSIZE - ry - (*(mbObj + 2) + 16 * _2X);

				SetAlpha(24);
				MemRect((float)(xOffset - rx + *(mbObj + 1) + 2 * _2X) * zoom, yPos + (float)y * zoom, (float)22 * _2X * zoom, 1000, 0x826C44, cvtDest, cvtLayer, buffering);
				SetAlpha(32);

				DrawBgEffect(BG14_WATERFALL0 + (robin.playtime % 5), (float)(xOffset - rx + *(mbObj + 1) + 13 * _2X) * zoom, yPos + (float)y * zoom, 0, zoom, cvtDest, cvtLayer, buffering);

				do {
					DrawBgEffect(BG14_WATER0 + (robin.playtime % 5), (float)(xOffset - rx + *(mbObj + 1) + 13 * _2X) * zoom, yPos + (float)y * zoom, 0, zoom, cvtDest, cvtLayer, buffering);
					y -= sewageFallHeight[robin.playtime % 5];
				} while (y > 0);

#ifdef CLIPPING
				if (clipY2 > 0) {
#endif
					y = (rh - 4) * TSIZE - ry - (*(mbObj + 2) + 16 * _2X);

					SetAlpha(8);
					MemRect((float)(xOffset - rx + *(mbObj + 1) + 2 * _2X) * zoom, yPos + (float)y * zoom, (float)22 * _2X * zoom, 1000, 0x826C44, cvtDest, cvtLayer, buffering);

					DrawBgEffect(BG14_WATERFALL0 + (robin.playtime % 5), (float)(xOffset - rx + *(mbObj + 1) + 13 * _2X) * zoom, yPos + (float)y * zoom, 0, zoom, cvtDest, cvtLayer, buffering);

					do {
						DrawBgEffect(BG14_WATER0 + (robin.playtime % 5), (float)(xOffset - rx + *(mbObj + 1) + 13 * _2X) * zoom, yPos + (float)y * zoom, 0, zoom, cvtDest, cvtLayer, buffering);
						y -= sewageFallHeight[robin.playtime % 5];
					} while (y > 0);

					SetAlpha(24);

					if (pPlayer->active)
						DrawBgEffect(2000 + BG_WATERFALL_SPLASH0 + robin.playtime % 3, (float)(xOffset - rx + *(mbObj + 1) + 13 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE + pPlayer->y - OBJIMGGAP - ry) * zoom, 0, zoom, cvtDest, cvtLayer, buffering);
#ifdef CLIPPING
				}
#endif
				SetAlpha(32);
			}
		}
		break;
	}

	//물
	for (i = 0; i < mapData[4]; i++) {
		if (mapRect[i * 5 + 4] == EMPTY) {
			//수면
			if (mapData[7] == MAPTYPE_SWAMP) {
				//톨레아습지
				for (j = 0; j < mapRect[i * 5 + 2]; j++) {
					bgPtrShort = &swampImg[(((robin.playtime / 2 + j) % 3) + 5) * 4];
					DrawImage(*(bgPtrShort + 2), *(bgPtrShort + 3), *bgPtrShort, *(bgPtrShort + 1), (float)(xOffset + ((mapRect[i * 5] + j) << 4) * _2X - rx) * zoom, yPos + (float)((rh - 4) * TSIZE - (16 + (mapRect[i * 5 + 1] << 4) * _2X + ((robin.playtime / 2 % 3) % 2)) - ry) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG], cvtDest, cvtLayer, MAP_OBJ_IMG, buffering);
				}
			}
			else {
				//아틀란티스
				SetAlpha(24);
				//수면
				for (j = 0; j < mapRect[i * 5 + 2]; j += 3)
					//water.bmp
					DrawImage(Min((mapRect[i * 5 + 2] - j) * 16, 48) * _2X, 12 * _2X, 0, 16 * _2X + ((robin.playtime / 2 + j) % 3) * 28 * _2X, (float)(xOffset + ((mapRect[i * 5] + j) << 4) * _2X - rx) * zoom, yPos + (float)((rh - 4) * TSIZE - (16 * _2X + (mapRect[i * 5 + 1] << 4) * _2X) - ry) * zoom, false, false, false, false, false, zoom, sprite[WATER_IMG], cvtDest, cvtLayer, WATER_IMG, buffering);

				SetAlpha(32);
			}

			//웨이브
			if (pPlayer->x >= (mapRect[i * 5] << 4) * _2X && pPlayer->x <= ((mapRect[i * 5] + mapRect[i * 5 + 2]) << 4) * _2X && pPlayer->y >= (mapRect[i * 5 + 1] << 4) * _2X + 16 * _2X && pPlayer->y <= (mapRect[i * 5 + 1] << 4) * _2X + 40 * _2X) {
				int imgFile;

				if (mapData[7] == MAPTYPE_SWAMP) {
					//톨레아습지
					SetAlpha(16);
					bgPtrShort = &swampImg[swampSplash[(robin.playtime % 6) * 4] * 4];
					imgFile = MAP_OBJ_IMG;
				}
				else {
					//아틀란티스
					SetAlpha(24);
					bgPtrShort = &atlanticeImg[swampSplash[(robin.playtime % 6) * 4] * 4];
					imgFile = WATER_IMG;
				}

				DrawImage(*(bgPtrShort + 2), *(bgPtrShort + 3), *bgPtrShort, *(bgPtrShort + 1), (float)(xOffset + pPlayer->x + swampSplash[(robin.playtime % 6) * 4 + 1 + pPlayer->dirF] - rx) * zoom, yPos + (float)((rh - 4) * TSIZE - ((mapRect[i * 5 + 1] << 4) * _2X + 22 * _2X + swampSplash[(robin.playtime % 6) * 4 + 3]) - ry) * zoom, false, false, false, false, false, zoom, sprite[imgFile], cvtDest, cvtLayer, imgFile, buffering);
				SetAlpha(32);
			}
		}
	}

	//입수효과
	if (splash.frame && splashType == 0) {
		int imgFile;

		if (mapData[7] == MAPTYPE_SWAMP) {
			SetAlpha(16);
			bgPtrShort = &swampImg[swampSplash[(splash.frame - 1) * 4] * 4];
			imgFile = MAP_OBJ_IMG;
		}
		else {
			bgPtrShort = &atlanticeImg[swampSplash[(splash.frame - 1) * 4] * 4];
			imgFile = WATER_IMG;
		}

		DrawImage(*(bgPtrShort + 2), *(bgPtrShort + 3), *bgPtrShort, *(bgPtrShort + 1), (float)(xOffset + splash.x + swampSplash[(splash.frame - 1) * 4 + 1 + pPlayer->dirF] - rx) * zoom, yPos + (float)((rh - 4) * TSIZE + splash.y + swampSplash[(splash.frame - 1) * 4 + 3] - ry + 4) * zoom, false, false, false, false, false, zoom, sprite[imgFile], cvtDest, cvtLayer, imgFile, buffering);

		if (mapData[7] == MAPTYPE_SWAMP)
			bgPtrShort = &swampImg[swampSplash[(splash.frame + 5) * 4] * 4];
		else
			bgPtrShort = &atlanticeImg[swampSplash[(splash.frame + 5) * 4] * 4];

		DrawImage(*(bgPtrShort + 2), *(bgPtrShort + 3), *bgPtrShort, *(bgPtrShort + 1), (float)(xOffset + splash.x + swampSplash[(splash.frame + 5) * 4 + 1 + splash.dir] - rx) * zoom, yPos + (float)((rh - 4) * TSIZE + splash.y + swampSplash[(splash.frame + 5) * 4 + 3] - ry) * zoom, false, false, false, false, false, zoom, sprite[imgFile], cvtDest, cvtLayer, imgFile, buffering);

		SetAlpha(32);
	}

	//if (option.effect) {
	switch (mapData[7]) {
	case MAPTYPE_PLAIN:
		//아델라인 평원 나비
		for (i = 0; i < MAXBGOBJECT; i++) {
			if (bgObj[i].active)
				DrawBgEffect(BG7_BUTTERFLY0 + (robin.playtime / 2 + i) % 3, (float)(xOffset + bgObj[i].x - rx) * zoom, yPos + (float)((rh - 4) * TSIZE - bgObj[i].y - ry) * zoom, bgObj[i].etc, zoom, cvtDest, cvtLayer, buffering);
			else
				break;
		}
	case MAPTYPE_TOLEM:
	case MAPTYPE_VALLEY:
	case MAPTYPE_ELF:
	case MAPTYPE_LIGHT:
	case MAPTYPE_CASTLE:
		//햇살
		j = (robin.playtime + (drawHandle == MD_PLAY ? Random(3) : 0)) % 24;

		grayScale = 0;

		//GammaImage(0, 5, gScreenBuffer);

		SetAlpha(24 + areaFrame);
		DrawBgEffect(1000 + sunShineMotion[j], (float)DX * zoom, yPos + (float)((rh - 4) * TSIZE) * zoom, 0, zoom, cvtDest, cvtLayer, buffering);

		if (sunShineMotion[24 + j] >= 0)
			DrawBgEffect(1000 + sunShineMotion[24 + j], (float)(DX - 192 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - 176 * _2X) * zoom, 0, zoom, cvtDest, cvtLayer, buffering);

		SetAlpha(32);
		break;
	case MAPTYPE_SWAMP:

		//안개
		for (i = 0; i < MAXBGOBJECT; i++) {
			if (bgObj[i].active)
				DrawBgEffect(BG2_MIST0 + bgObj[i].etc, (float)(bgObj[i].x - rx) * zoom, yPos + (float)((rh - 4) * TSIZE - bgObj[i].y - ry) * zoom, 0, zoom, cvtDest, cvtLayer, buffering);
			else
				break;
		}
		break;
	}
	//}
}

void EffectDraw(int yPos, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j, y;
	signed short* bbPtr = bubbleXY;
	OBJECT* pPlayer;

	pPlayer = &ao[raidPlayer];

	EffectDrawOnlyBg(yPos, zoom, cvtDest, cvtLayer, buffering);

	//산소 처리
	if (pPlayer->O2 != OXYGEN && isDemo == false && pPlayer->dead == false) {
		MemRect((float)(xOffset + pPlayer->x - rx - 12 * _2X) * zoom, (float)(pPlayer->y - ry - OBJIMGGAP - 32 * _2X) * zoom, (float)24 * _2X * zoom, (float)2 * _2X * zoom, 0xCC0000, cvtDest, cvtLayer, buffering);
		MemRect((float)(xOffset + pPlayer->x - rx - 12 * _2X) * zoom, (float)(pPlayer->y - ry - OBJIMGGAP - 32 * _2X) * zoom, (float)pPlayer->O2 * 24 * _2X / OXYGEN * zoom, (float)2 * _2X * zoom, 0x00FF00, cvtDest, cvtLayer, buffering);
	}

	i = TOTALHITMARK;

	do {
		i--;

		if (hitMark[i].frame > 0 && hitMark[i].etc == HITMARK_LARGE) {
			//if (option.effect)
			GammaImage(48 - hitMark[i].frame * 2, 0, zoom, cvtDest, cvtLayer, buffering);
			//GammaImage(16 + hitMark[i].frame * 4, 0);
			break;
		}
	} while (i > 0);

#ifdef HITMARKSHOW
	//if (option.effect)
	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame > 0) {
			if (hitMark[i].x != 0 || hitMark[i].y != 0) {

				DrawEffect(1000 - 1 + hitMarkData[hitMark[i].type * 3 + (hitMark[i].etc == 0 ? 0 : 1)] + hitMark[i].frame, (float)(xOffset + hitMark[i].x - rx), (float)(STATUSWIN_Y + (rh - 4) * TSIZE - hitMark[i].y - ry + OBJIMGGAP), hitMark[i].dir, false, hitMark[i].zoom, cvtDest, cvtLayer, buffering);

				if (hitMark[i].etc == HITMARK_LARGE && hitMark[i].frame < 4)
					//if (option.effect)
					DrawEffect(HIT_LARGE1 - 1 + hitMark[i].frame, (float)(xOffset + hitMark[i].x - rx), (float)(STATUSWIN_Y + (rh - 4) * TSIZE - hitMark[i].y - ry + OBJIMGGAP + 8 * _2X), hitMark[i].dir, false, hitMark[i].zoom, cvtDest, cvtLayer, buffering);
			}
		}
	}
#endif

	if (pPlayer->inTile == SWAMP) {
		//늪지일때
		if (pPlayer->debuf[BLIND] && pPlayer->debuf[BLIND] >= 8)
			GammaImage(0, 7, zoom, cvtDest, cvtLayer, buffering);
		else //if (option.effect)
			GammaImage(0, 1, zoom, cvtDest, cvtLayer, buffering);
	}
	else if (pPlayer->debuf[BLIND])
		//실명일때
		GammaImage(0, 7, zoom, cvtDest, cvtLayer, buffering);

	//if (option.effect) {
	if (effect.edge) {
		if (effect.edge > 0)
			GammaImage(effect.edge, 2, zoom, cvtDest, cvtLayer, buffering);
		else
			GammaImage(-effect.edge, 3, zoom, cvtDest, cvtLayer, buffering);

		effect.edge /= 2;
	}
	//}

	UnSectionClip(false);


	//대미지 숫자
	for (i = 0; i < TOTALHITMARK; i++) {
		if (dmgInfo[i].type > 0) {
			int tMag = 0;

			if (dmgInfo[i].color)
				SetColor(dmgInfo[i].color);

			if (dmgInfo[i].pos < BULLET)
				SetBlend(12, 0xFF0000);

			j = dmgInfoData[DMGNUMFRAME + dmgInfo[i].frame];

			if (dmgInfo[i].type == 2) {
				if (dmgInfo[i].frame < 5) {
					tMag++;
					SetAlpha(32 - dmgInfo[i].frame * 4);
					MemRect(0, -ry + dmgInfo[i].y + (float)20 * _2X * dmgInfo[i].zoom, DX, 2 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					m_lgrpAlpha -= 3;
					MemRect(0, -ry + dmgInfo[i].y + (float)19 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					MemRect(0, -ry + dmgInfo[i].y + (float)22 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					m_lgrpAlpha -= 3;
					MemRect(0, -ry + dmgInfo[i].y + (float)18 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					MemRect(0, -ry + dmgInfo[i].y + (float)23 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					m_lgrpAlpha -= 3;
					MemRect(0, -ry + dmgInfo[i].y + (float)17 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					MemRect(0, -ry + dmgInfo[i].y + (float)24 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					m_lgrpAlpha -= 3;
					MemRect(0, -ry + dmgInfo[i].y + (float)16 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					MemRect(0, -ry + dmgInfo[i].y + (float)25 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					m_lgrpAlpha -= 3;
					MemRect(0, -ry + dmgInfo[i].y + (float)15 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					MemRect(0, -ry + dmgInfo[i].y + (float)26 * _2X * dmgInfo[i].zoom, DX, 1 * _2X, 0xFFFFFF, cvtDest, cvtLayer, buffering);
					m_lgrpAlpha = 0;
					//SetAlpha(32);
				}
				else
					j = NUM_FONT_NORMAL;
			}

			if (dmgInfo[i].frame < 2)
				tMag++;

			//SetAlpha(dmgInfoData[DMGNUMFRAME * 2 + dmgInfo[i].frame]);

			if (dmgInfo[i].owner >= ENEMY)
				SetColor(0xFF0000);

			if (dmgInfo[i].owner < ENEMY) {
				dmgIndex = 0;
			}

			//SetAlpha(32);
			DrawNum(dmgInfo[i].dmg, -rx + dmgInfo[i].x, -ry + dmgInfo[i].y, j, CENTER, 0, MINUS, true, dmgInfo[i].zoom, false, cvtDest, cvtLayer, buffering);

			SetColor(false);

			SetAlpha(32);
			UnSetBlend();
		}
	}


	y = STATUSWIN_Y + ROULETTECARDSIZE_Y + TSIZE;

	int gap;
	//전투메세지 텍스트
	for (i = 0; i < TOTALHITMARK; i++) {
		if (imgText[i].type) {
			if (imgText[i].frame < FPS * MOTIONDIV) {
				SetAlpha(32);
				j = Random(7) * _2X - 3 * _2X;
				y = Random(5) * _2X - 2 * _2X;
			}
			else {
				SetAlpha(32 - (imgText[i].frame - FPS * MOTIONDIV));
				imgText[i].zoom -= 0.5f / MOTIONDIV;

				if (imgText[i].zoom < 0)
					memset(&imgText[i], 0, sizeof(imgText[i]));

				j = 0;
				y = 0;

			}

			gap = 0;

			switch (imgText[i].type) {
			case EFFECT_TEXT_MISS:
				//ef.bmp
				//if (option.effect) {
				if (imgText[i].dmg < BULLET)
					DrawImage(33 * _2X, 12 * _2X, 164 * _2X, 223 * _2X, (float)(xOffset + imgText[i].x - (float)33 * _2X * imgText[i].zoom / 2 + j) * zoom, (float)(imgText[i].y + (float)12 * _2X * imgText[i].zoom / 2 + y) * zoom, false, false, false, false, false, imgText[i].zoom * zoom, sprite[EFFECT_IMG], cvtDest, cvtLayer, EFFECT_IMG, buffering);
				else
					DrawImage(33 * _2X, 12 * _2X, 197 * _2X, 223 * _2X, (float)(xOffset + imgText[i].x - (float)33 * _2X * imgText[i].zoom / 2 + j) * zoom, (float)(imgText[i].y + (float)12 * _2X * imgText[i].zoom / 2 + y) * zoom, false, false, false, false, false, imgText[i].zoom * zoom, sprite[EFFECT_IMG], cvtDest, cvtLayer, EFFECT_IMG, buffering);
				//}
				break;
			case EFFECT_TEXT_EVASION:
				//ef.bmp
				//if (option.effect)
				DrawImage(31 * _2X, 11 * _2X, 184 * _2X, 179 * _2X, (float)(xOffset + imgText[i].x - (float)(31 * _2X) * imgText[i].zoom / 2 + j) * zoom, (float)(imgText[i].y + (float)11 * _2X * imgText[i].zoom / 2 - y) * zoom, false, false, false, false, false, imgText[i].zoom * zoom, sprite[EFFECT_IMG], cvtDest, cvtLayer, EFFECT_IMG, buffering);
				break;
			case EFFECT_TEXT_REGIST:
				//ef.bmp
				//if (option.effect)
				DrawImage(46 * _2X, 12 * _2X, 67 * _2X, 56 * _2X, (float)(xOffset + imgText[i].x - (float)(46 * _2X) * imgText[i].zoom / 2 + j) * zoom, (float)(imgText[i].y + (float)12 * _2X * imgText[i].zoom / 2 + y) * zoom, false, false, false, false, false, imgText[i].zoom * zoom, sprite[EFFECT_IMG], cvtDest, cvtLayer, EFFECT_IMG, buffering);
				break;
			case EFFECT_TEXT_CRITICAL:
				if (imgText[i].dmg >= ENEMY) {
					SetBlend(8, 0x000000);
					//if (option.effect)
					DrawEffect(Min(3, imgText[i].frame) + EFFECT_CRITICAL_TEXT0, (float)(xOffset + imgText[i].x + j + gap) * zoom, (float)(imgText[i].y + (float)0 * _2X * imgText[i].zoom / 2 + y) * zoom, 0, false, imgText[i].zoom * zoom, cvtDest, cvtLayer, buffering);
					UnSetBlend();
					break;
				}
			case EFFECT_TEXT_PIERCE:
			case EFFECT_TEXT_EXTRA:
			case EFFECT_TEXT_GUARD:
				//if (option.effect)
				DrawEffect(Min(3, imgText[i].frame) + EFFECT_CRITICAL_TEXT0 + (imgText[i].type - EFFECT_TEXT_CRITICAL) * 4, (float)(xOffset + imgText[i].x + gap) * zoom, (float)(imgText[i].y + (float)12 * _2X * imgText[i].zoom / 2 + y) * zoom, 0, false, imgText[i].zoom * zoom, cvtDest, cvtLayer, buffering);
				break;
			}

			SetAlpha(32);
		}
	}

	//경험치 텍스트
	for (i = 0; i < TOTALHITMARK; i++) {
		if (imgText[i].type == EFFECT_TEXT_EXP) {
			SetBlend(12, 0xFFFFF00);
			//if (option.effect)
			DrawNum(imgText[i].dmg, (float)(xOffset + imgText[i].x - rx - 6 * _2X) * zoom, (float)(STATUSWIN_Y + (rh - 4) * TSIZE + imgText[i].y - ry) * zoom, NUM_FONT_NORMAL, RIGHT, 0, 0, true, zoom, false, cvtDest, cvtLayer, buffering);
			UnSetBlend();

			if (imgText[i].frame > 4)
				SetAlpha(24 - (imgText[i].frame - 4) * 1);
			else
				SetAlpha(24);

			//ef.bmp
			//if (option.effect)
			DrawImage(31 * _2X, 11 * _2X, 184 * _2X, 179 * _2X, (float)(xOffset + imgText[i].x - rx - 4 * _2X) * zoom, (float)(STATUSWIN_Y + (rh - 4) * TSIZE + imgText[i].y - ry) * zoom, false, false, false, false, false, zoom, sprite[EFFECT_IMG], cvtDest, cvtLayer, EFFECT_IMG, buffering);
			SetAlpha(32);
		}
	}

	//레벨업 텍스트
	for (j = 0; j < realPlayerCnt; j++) {
		pPlayer = &ao[PLAYER + j];
		if (pPlayer->levelUpFrame) {
			//if (option.effect)
			DrawEffect(EFFECT_LEVELUP_TEXT0 - 1 + (pPlayer->levelUpFrame < 11 ? pPlayer->levelUpFrame : Max(11, pPlayer->levelUpFrame - 5)), (float)(xOffset + pPlayer->x - rx) * zoom, (float)(STATUSWIN_Y + (rh - 4) * TSIZE - PxlUp(pPlayer) - ry + OBJIMGGAP + 20 * _2X) * zoom, 0, false, pPlayer->zoom * zoom, cvtDest, cvtLayer, buffering);
		}
	}

	if (zoomFrame) {
		zoomFrame--;
		warpFrame += 2;

		ZoomImage((float)(xOffset + pPlayer->x - rx) * zoom, (float)(pPlayer->y - ry) * zoom, cvtDest, cvtLayer, (float)(256 + zoomData[zoomFrame]) * zoom, buffering);
		GammaImage(warpFrame, 0, zoom, cvtDest, cvtLayer, buffering);

		if (zoomFrame == 0) {
			if (drawHandle == MD_BATTLE)
				keyHandle = MK_BATTLE;
			else if (drawHandle == MD_RAID)
				keyHandle = MK_RAID;
			else if (drawHandle == MD_BOSSRAID)
				keyHandle = MK_BOSSRAID;
			else
				keyHandle = MK_PLAY;
			nameFrame = INFOFRAME;
			warpFrame = 0;
		}
	}


	if (fadeFrame) {
		//어두워짐
		if (fadeFrame > 0)
			SetAlpha((fadeFrame - 1));
		//밝아짐
		else if (fadeFrame < 0)
			SetAlpha(32 - (-fadeFrame + 1));

		//MemRect(xOffset, DY, DX - 2 * xOffset, DY, fadeColor, cvtDest, cvtLayer, buffering);
		//MemRect((float)(xOffset) * zoom, (float)(DY) * zoom, (float)(DX) * zoom, (float)(DY - STATUSWIN_Y) * zoom, fadeColor, cvtDest, cvtLayer, buffering);
		MemRect((float)(xOffset)*zoom, (float)(DY)*zoom, (float)(DX)*zoom, (float)(DY)*zoom, fadeColor, cvtDest, cvtLayer, buffering);

		SetAlpha(32);
	}

	if (heartFrame) {
		heartFrame--;
	}

	//보스전에서의 화면 특수 효과
	/*
	for (i = 0; i < TOTAL)
	if (robin.bossRoom == true) {
		SetAlpha(4 + Abs(8 - frame) % 16);
		MemRect(0, DY, DX, 8 * _2X, COLOR_WHITE, cvtDest, cvtLayer, buffering);
		MemRect(0, DY - 8 * _2X, 8 * _2X, DY - 16 * _2X, COLOR_WHITE, cvtDest, cvtLayer, buffering);
		MemRect(DX - 8 * _2X, DY - 8 * _2X, 8 * _2X, DY - 16 * _2X, COLOR_WHITE, cvtDest, cvtLayer, buffering);
		MemRect(0, 8 * _2X, DX, 8 * _2X, COLOR_WHITE, cvtDest, cvtLayer, buffering);
		SetAlpha(32);
	}
	*/
}

void DrawTouchPoint(void)
{
	SetAlpha(20);
	DrawEffect(MAGNET_ACTIVE0 + touchFrame / MOTIONDIV % 5, touchX, touchY - 16 * _2X, RIGHT, false, 1.0f, gScreenBuffer, gScreenLayer, false);

	SetAlpha(32);

	touchFrame--;
}


void InitBanner(void)
{
	char szID1[100];
	char szID2[100];

	sprintf(szID1, "ca-app-pub-ID");   //전면광고
	sprintf(szID2, "ca-app-pub-ID");   //배너광고
}