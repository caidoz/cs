#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Text.h"


//���
void DrawWindow3(int x, int y, int w, int h, int index, float zoom)
{
	int i;
	int cnt;

	//호출부는 BUFFER_CARDFRAME 프리렌더 한 곳뿐이므로 항상 라이브로 그린다.
	//완성된 텍스처를 곧바로 찍던 아래 경로는 호출부가 없어 남겨만 둔다.
	//index = Min(TOTALMAPTYPE - 1, index);
	//DrawImage(ITEMCARDSIZE_X, ITEMCARDSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[BUFFER_CARDFRAME_IMG + index], BUFFER_CARDFRAME_IMG + index);
	{

		DrawFrame(x, y, w, h, FRAME_SHOPBALLOON);

		if (index >= 0) {

			SetSectionClip(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, false);
			if (w >= 128 * _2X || h >= 128 * _2X) {
				switch ((cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG)) {
				case MAPTYPE_VALLEY:
					MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, 0x5F3B2D);
					break;
				case MAPTYPE_ELF:
					MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, 0x242B31);
					break;
				case MAPTYPE_GOLEMVALLEY:
					MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, 0x0A0208);
					break;
				case MAPTYPE_DRAGON:
					MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, 0x170805);
					break;
				case MAPTYPE_DARKNESS:
					MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, 0x0A2F3D);
					break;
				case MAPTYPE_GHOST:
					MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, 0x2B2F20);
					break;
				case MAPTYPE_DEVILCASTLE:
					MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, 0x182424);
					break;
				default:
					MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, mapColor[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG)]);
					break;
				}
				if (cardImgBg[index * 6] - MAP_BG_IMG == MAPTYPE_TOLEM) {
					for (i = 0; i < w / (mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0] * 2) + 1; i++) {
						DrawImage(mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0], mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1], 0 * _2X, 0 * _2X, x + (float)(4 * _2X + i * mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0] * 2) * zoom, y + (float)(-CREWHEIGHT + mapBg[cardImgBg[index * WINDOWBGDATASIZE + 3] * 4 + 1] + 4 * _2X + 4 * TSIZE) * zoom, false, false, false, false, false, zoom, sprite[cardImgBg[index * WINDOWBGDATASIZE + 0]], cardImgBg[index * WINDOWBGDATASIZE + 0]);
						DrawImage(mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0], mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1], 0 * _2X, 0 * _2X, x + (float)(4 * _2X + i * mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0] * 2 + mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0]) * zoom, y + (float)(-CREWHEIGHT + mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1] + 4 * _2X + 4 * TSIZE) * zoom, true, false, false, false, false, zoom, sprite[cardImgBg[index * WINDOWBGDATASIZE + 0]], cardImgBg[index * WINDOWBGDATASIZE + 0]);
					}
				}
				else {
					for (i = 0; i < w / mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0] + 1; i++) {
						DrawImage(mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0], mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1], 0 * _2X, 0 * _2X, x + (float)(4 * _2X + i * mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0]) * zoom, y + (float)(-CREWHEIGHT + mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1] + 4 * _2X + 4 * TSIZE) * zoom, false, false, false, false, false, zoom, sprite[cardImgBg[index * WINDOWBGDATASIZE + 0]], cardImgBg[index * WINDOWBGDATASIZE + 0]);
					}
				}

				DrawTileDirect(cardImgBg[index * WINDOWBGDATASIZE + 3], x, y - h, zoom);
			}
			else {
				DrawImage(w - (float)4 * _2X * zoom, h - (float)4 * _2X * zoom, cardImgBg[index * WINDOWBGDATASIZE + 1], cardImgBg[index * WINDOWBGDATASIZE + 2], x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, false, false, false, false, false, zoom, sprite[cardImgBg[index * WINDOWBGDATASIZE + 0]], cardImgBg[index * WINDOWBGDATASIZE + 0]);
				DrawTileDirect(cardImgBg[index * WINDOWBGDATASIZE + 3], x + (float)cardImgBg[index * WINDOWBGDATASIZE + 4] * zoom, y + (float)cardImgBg[index * WINDOWBGDATASIZE + 5] * zoom, zoom);
			}

			UnSectionClip(false);

			SetAlpha(16);
			MemRect(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 4 * _2X, 0x000000);
			SetAlpha(32);
		}
	}
}


//���
void DrawWindow4(int x, int y, int w, int h, int index, float zoom)
{
	int i;
	int cnt;

	DrawFrame(x, y, w, h, FRAME_SHOPBALLOON);

	if (index >= 0) {

		SetSectionClip(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, w - (float)8 * _2X * zoom, h - (float)8 * _2X * zoom, false);
		if (w >= 128 * _2X || h >= 128 * _2X) {
			switch ((cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG)) {
			case MAPTYPE_VALLEY:
				MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, h - (float)14 * _2X * zoom, 0x5F3B2D);
				break;
			case MAPTYPE_ELF:
				MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, h - (float)14 * _2X * zoom, 0x242B31);
				break;
			case MAPTYPE_GOLEMVALLEY:
				MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, h - (float)14 * _2X * zoom, 0x0A0208);
				break;
			case MAPTYPE_DRAGON:
				MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, h - (float)14 * _2X * zoom, 0x170805);
				break;
			case MAPTYPE_DARKNESS:
				MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, h - (float)14 * _2X * zoom, 0x0A2F3D);
				break;
			case MAPTYPE_GHOST:
				MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, h - (float)14 * _2X * zoom, 0x2B2F20);
				break;
			case MAPTYPE_DEVILCASTLE:
				MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, h - (float)14 * _2X * zoom, 0x182429);
				break;
			default:
				MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, h - (float)14 * _2X * zoom, mapColor[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG)]);
				break;
			}
			if (cardImgBg[index * 6] - MAP_BG_IMG == MAPTYPE_TOLEM) {
				for (i = 0; i < w / (mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0] * 2) + 1; i++) {
					DrawImage(mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0], mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1], 0 * _2X, 0 * _2X, x + 4 * _2X + i * mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0] * 2, y - CREWHEIGHT + mapBg[cardImgBg[index * WINDOWBGDATASIZE + 3] * 4 + 1] + 4 * _2X + 4 * TSIZE, false, false, false, false, false, 1.0f, sprite[cardImgBg[index * WINDOWBGDATASIZE + 0]], cardImgBg[index * WINDOWBGDATASIZE + 0]);
					DrawImage(mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0], mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1], 0 * _2X, 0 * _2X, x + 4 * _2X + i * mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0] * 2 + mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0], y - CREWHEIGHT + mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1] + 4 * _2X + 4 * TSIZE, true, false, false, false, false, 1.0f, sprite[cardImgBg[index * WINDOWBGDATASIZE + 0]], cardImgBg[index * WINDOWBGDATASIZE + 0]);
				}
			}
			else {
				for (i = 0; i < w / mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0] + 1; i++) {
					DrawImage(mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0], mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1], 0 * _2X, 0 * _2X, x + 4 * _2X + i * mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 0], y - CREWHEIGHT + mapBg[(cardImgBg[index * WINDOWBGDATASIZE + 0] - MAP_BG_IMG) * 4 + 1] + 4 * _2X + 4 * TSIZE, false, false, false, false, false, 1.0f, sprite[cardImgBg[index * WINDOWBGDATASIZE + 0]], cardImgBg[index * WINDOWBGDATASIZE + 0]);
				}
			}

			DrawTileDirect(cardImgBg[index * WINDOWBGDATASIZE + 3], x, y - h, zoom);
		}
		else {
			DrawImage(w - 9 * _2X, h - 9 * _2X, cardImgBg[index * WINDOWBGDATASIZE + 1], cardImgBg[index * WINDOWBGDATASIZE + 2], x + 4 * _2X, y - 4 * _2X, false, false, false, false, false, zoom, sprite[cardImgBg[index * WINDOWBGDATASIZE + 0]], cardImgBg[index * WINDOWBGDATASIZE + 0]);
			DrawTileDirect(cardImgBg[index * WINDOWBGDATASIZE + 3], x + cardImgBg[index * WINDOWBGDATASIZE + 4], y + cardImgBg[index * WINDOWBGDATASIZE + 5], zoom);
		}

		SetAlpha(16);
		MemRect(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, w - (float)8 * _2X * zoom, h - (float)14 * _2X * zoom, 0x000000);
		SetAlpha(32);

		UnSectionClip(false);
	}
}

//���
void DrawWindow5(int x, int y, int w, int h, int mapIdx, float zoom, int mapOffsetY)
{
	int i;
	int cnt;
	int mapType = mapDatas[mapIdx][7];

	DrawFrame(x, y, w, h, FRAME_SHOPBALLOON);

	SetSectionClip(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, w - (float)8 * _2X * zoom, h - (float)8 * _2X * zoom, false);

	MemRect(x + (float)(4 * _2X) * zoom, y - (float)4 * _2X * zoom, w - (float)(8 * _2X) * zoom, (h - (float)8 * _2X * zoom) / 2, mapColor[mapType]);

	switch (mapType) {
	case MAPTYPE_VALLEY:
		MemRect(x + (float)(4 * _2X) * zoom, y - h / 2, w - (float)(8 * _2X) * zoom, h / 2, 0x5F3B2D);
		break;
	case MAPTYPE_ELF:
		MemRect(x + (float)(4 * _2X) * zoom, y - h / 2, w - (float)(8 * _2X) * zoom, h / 2, 0x242B31);
		break;
	case MAPTYPE_GOLEMVALLEY:
		MemRect(x + (float)(4 * _2X) * zoom, y - h / 2, w - (float)(8 * _2X) * zoom, h / 2, 0x0A0208);
		break;
	case MAPTYPE_DRAGON:
		MemRect(x + (float)(4 * _2X) * zoom, y - h / 2, w - (float)(8 * _2X) * zoom, h / 2, 0x170805);
		break;
	case MAPTYPE_DARKNESS:
		MemRect(x + (float)(4 * _2X) * zoom, y - h / 2, w - (float)(8 * _2X) * zoom, h / 2, 0x0A2F3D);
		break;
	case MAPTYPE_GHOST:
		MemRect(x + (float)(4 * _2X) * zoom, y - h / 2, w - (float)(8 * _2X) * zoom, h / 2, 0x2B2F20);
		break;
	case MAPTYPE_DEVILCASTLE:
		MemRect(x + (float)(4 * _2X) * zoom, y - h / 2, w - (float)(8 * _2X) * zoom, h / 2, 0x182429);
		break;
	default:
		MemRect(x + (float)(4 * _2X) * zoom, y - h / 2, w - (float)(8 * _2X) * zoom, h / 2, mapColor[mapType]);
		break;
	}

	if (mapBg[mapType * 4 + 0] != 0) {
		if (mapType == MAPTYPE_TOLEM) {
			for (i = 0; i < w / (mapBg[mapType * 4 + 0] * 2) + 1; i++) {
				DrawImage(mapBg[mapType * 4 + 0], mapBg[mapType * 4 + 1], 0 * _2X, 0 * _2X, x + (float)(4 * _2X + i * mapBg[mapType * 4 + 0] * 2) * zoom, y + (float)(-CREWHEIGHT + mapBg[mapType * 4 + 1] + 4 * _2X + 4 * TSIZE) * zoom, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapType], MAP_BG_IMG + mapType);
				DrawImage(mapBg[mapType * 4 + 0], mapBg[mapType * 4 + 1], 0 * _2X, 0 * _2X, x + (float)(4 * _2X + i * mapBg[mapType * 4 + 0] * 2 + mapBg[mapType * 4 + 0]) * zoom, y + (float)(-CREWHEIGHT + mapBg[mapType * 4 + 1] + 4 * _2X + 4 * TSIZE) * zoom, true, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapType], MAP_BG_IMG + mapType);
			}
		}
		else {
			for (i = 0; i < w / mapBg[mapType * 4 + 0] + 1; i++) {
				DrawImage(mapBg[mapType * 4 + 0], mapBg[mapType * 4 + 1], 0 * _2X, 0 * _2X, x + (float)(4 * _2X + i * mapBg[mapType * 4 + 0]) * zoom, y + (float)(-CREWHEIGHT + mapBg[mapType * 4 + 1] + 4 * _2X + 4 * TSIZE) * zoom, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapType], MAP_BG_IMG + mapType);
			}
		}
	}

	DrawTileDirect(mapIdx, x, y - h + mapOffsetY, zoom);

	//SetAlpha(12);
	//MemRect(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, w - (float)8 * _2X * zoom, h - (float)14 * _2X * zoom, 0x000000, cvtDest, cvtLayer, buffering);
	//SetAlpha(32);

	UnSectionClip(false);
}

// Draw�ڵ�
void VersionDraw(void)
{
	int y;

	return;

	if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID)
		y = DY / 2 + MINDY / 2 - GNBHEIGHT;
	else
		y = DY - GNBHEIGHT - 4 * _2X;

	SetAlpha(24);
	MemRect(0, y, 64 * _2X, 26 * _2X, COLOR_BLACK);
	SetAlpha(32);
	//SetFontColor(COLOR_WHITE);
	DrawText(TEXT_VERSION, 8, y - 1 * _2X, 1.0f);
	DrawAlpha(8, y - 1 * _2X - 14 * _2X, ALPHA_MACRO, FONT_SMALL, 1.0f, false);
	DrawAlpha(8 + 32 * _2X, y - 1 * _2X - 14 * _2X, option.macro == true ? ALPHA_ON : ALPHA_OFF, FONT_SMALL, 1.0f, false);

	if (option.macro == true)
		DrawNum(LOG_COUNT - macroTimes + 1, 8 + 52 * _2X, y - 1 * _2X - 14 * _2X, NUM_FONT_SMALL, LEFT, 0, false, true, 1.0f, true);
}

void NoSpaceDraw(void)
{
	MemRect(0, 0, DX, DY, 0x000000);
	//��������� �����մϴ�.
	LineTextStr(tempStr, DX / 2 - 70, DY / 2 - 40, 140, -1, -1, 1.0f);
}

void LogoDraw(void)
{
	//DrawGrid(0 - (frame % DY), DY + (frame % DY), DY * 2, DY * 2, TSIZE * _2X, TSIZE * _2X, 0 * 2, 0 * 2 + 1, gScreenBuffer);

	int i;
	std::string fileName;

	MemRect(0, DY, DX, DY, COLOR_WHITE);

	DrawArray(IMG_LOGO, DX / 2 - imgArray[IMG_LOGO * 4 + 2] / 2, DY / 2 + imgArray[IMG_LOGO * 4 + 3] / 2, 1.0f);
	DrawAlphaFrame(DX / 2 - GetAlphaWidth(ALPHA_BIGPIXEL, FONT_SMALL, 1.0f) / 2, DY / 2 - imgArray[IMG_LOGO * 4 + 3] / 2 - 8, ALPHA_BIGPIXEL, frame, FONT_SMALL, false, 1.0f);

	switch (frame) {
	case 1:
		for (i = 0; i < BUFFER_CARDFRAME_IMG; i++) {
			LoadImg(i);
		}
		break;
	case 2:
		for (i = 0; i < BUFFER_CARDFRAME_IMG; i++) {
			LoadTexture(i);
		}
		break;
	case 3://BUFFER_PLAY
		if (doubleBuffer) {
			bufferTexture[BUFFER_PLAY] = cocos2d::RenderTexture::create(DX, DY);
			bufferTexture[BUFFER_PLAY]->retain();
			bufferTexture[BUFFER_PLAY]->setAnchorPoint(Vec2(0, 1.0f));
			bufferTexture[BUFFER_PLAY]->setPosition(0, DY);
		}
		break;
	case 4://BUFFER_CASTLE
		if (doubleBuffer) {
		}
		break;
	case 5://BUFFER_ARENA
		if (doubleBuffer) {
			bufferTexture[BUFFER_RAID] = cocos2d::RenderTexture::create(DX, DY);
			bufferTexture[BUFFER_RAID]->retain();
			bufferTexture[BUFFER_RAID]->setAnchorPoint(Vec2(0, 1.0f));
			bufferTexture[BUFFER_RAID]->setPosition(0, DY);
		}
		break;
	case 6://BUFFER_SHOP
		if (doubleBuffer) {
			bufferTexture[BUFFER_SHOP] = cocos2d::RenderTexture::create(DX, DY);
			bufferTexture[BUFFER_SHOP]->retain();
			bufferTexture[BUFFER_SHOP]->setAnchorPoint(Vec2(0, 1.0f));
			bufferTexture[BUFFER_SHOP]->setPosition(0, DY);

			PushRenderTarget(bufferTexture[BUFFER_SHOP], bufferLayer[BUFFER_SHOP]);
			DrawImage(640 * _2X, 512 * _2X, 0 * _2X, 0 * _2X, xOffset, DY, false, false, false, false, false, 1.0f, sprite[UI_PAPER_BG_UP_IMG], UI_PAPER_BG_UP_IMG);
			DrawImage(640 * _2X, 362 * _2X, 0 * _2X, 0 * _2X, xOffset, DY - 512 * _2X, false, false, false, false, false, 1.0f, sprite[UI_PAPER_BG_DOWN_IMG], UI_PAPER_BG_DOWN_IMG);
			PopRenderTarget();


			//DrawBg(TOLEM1, STATUSWIN_Y, bufferTexture[BUFFER_SHOP], bufferLayer[BUFFER_SHOP], true);

			//ShopDraw_Back(DX / 2 - STATUSWIN_X / 2, DY / 2 + MINDY / 2, bufferTexture[BUFFER_SHOP], bufferLayer[BUFFER_SHOP], doubleBuffer);
		}
		break;
	case 7://BUFFER_TILE
		if (doubleBuffer) {
			TILEDX = 46 * TSIZE;
			TILEDY = 42 * TSIZE;

			bufferTexture[BUFFER_TILE] = cocos2d::RenderTexture::create(TILEDX, TILEDY);
			bufferTexture[BUFFER_TILE]->retain();
			bufferTexture[BUFFER_TILE]->setAnchorPoint(Vec2(0, 1.0f));
			bufferTexture[BUFFER_TILE]->setPosition(0, DY);

			//DrawTile(robinmap, 0, bufferTexture[BUFFER_TILE], bufferLayer[BUFFER_TILE], doubleBuffer);
		}
		break;
	case 8:
		for (i = 0; i < M_ROULETTEUP; i++) {
			fileName = GetResourceName(RES_SOUND, i);
#if USE_AUDIO_ENGINE
			AudioEngine::preload(fileName.c_str());
			audioVolume[i] = 0.3f;
#elif USE_SIMPLE_AUDIO_ENGINE
			CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(fileName.c_str());
#endif
		}
		break;
	case 9:
		for (i = M_ROULETTEUP; i < TOTALMUSIC; i++) {
			fileName = GetResourceName(RES_SOUND, i);
#if USE_AUDIO_ENGINE
			AudioEngine::preload(fileName.c_str());
			if (i == M_ERROR)
				audioVolume[i] = 0.1f;
			else
				audioVolume[i] = 0.3f;
#elif USE_SIMPLE_AUDIO_ENGINE
			CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(fileName.c_str());
#endif
		}
		break;
	case 10:
		MakeAiHouse();
		break;
	case 11:
		break;
	case 12:
		robin.castle = 0;
		robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];
		break;
	case 13://MAPTYPE_TOLEM
	case 14://MAPTYPE_TOLEMINSIDE
	case 15://MAPTYPE_SWAMP
	case 16://MAPTYPE_VALLEY
	case 17://MAPTYPE_ATLANTICE
	case 18://MAPTYPE_SEWAGE
	case 19://MAPTYPE_CASTLE
	case 20://MAPTYPE_PLAIN
	case 21://MAPTYPE_ELF
	case 22://MAPTYPE_FLAME
	case 23://MAPTYPE_FROST
	case 24://MAPTYPE_THUNDER
	case 25://MAPTYPE_LIGHT
	case 26://MAPTYPE_GOLEMVALLEY
	case 27://MAPTYPE_DARKNESS
	case 28://MAPTYPE_DRAGON
	case 29://MAPTYPE_GHOST
	case 30://MAPTYPE_DEVILCASTLE
	case 31://MAPTYPE_SPACE
		if (doubleBuffer) {
			bufferTexture[BUFFER_CARDFRAME + frame - 13] = cocos2d::RenderTexture::create(ITEMCARDSIZE_X, ITEMCARDSIZE_Y);
			bufferTexture[BUFFER_CARDFRAME + frame - 13]->retain();
			bufferTexture[BUFFER_CARDFRAME + frame - 13]->setAnchorPoint(Vec2(0, 1.0f));
			bufferTexture[BUFFER_CARDFRAME + frame - 13]->setPosition(0, DY);

			PushRenderTarget(bufferTexture[BUFFER_CARDFRAME + frame - 13], bufferLayer[BUFFER_CARDFRAME + frame - 13]);
			DrawWindow3(0, ITEMCARDSIZE_Y, ITEMCARDSIZE_X, ITEMCARDSIZE_Y, (frame - 13), 1.0f);
			PopRenderTarget();

			texture[BUFFER_CARDFRAME_IMG + frame - 13] = bufferTexture[BUFFER_CARDFRAME + frame - 13]->getSprite()->getTexture();

			sprite[BUFFER_CARDFRAME_IMG + frame - 13] = Sprite::createWithTexture(texture[BUFFER_CARDFRAME_IMG + frame - 13]);
			//���⼭ �ؽ��ķκ��� �̹����� �����.

			//DrawTile(robinmap, 0, bufferTexture[BUFFER_TILE], bufferLayer[BUFFER_TILE], doubleBuffer);
		}
		break;
	case 32://BUFFER_OPTIONBUTTON_GREEN
	case 33://BUFFER_OPTIONBUTTON_RED
	case 34://BUFFER_OPTIONBUTTON_BLUE
	case 35://BUFFER_OPTIONBUTTON_GREY
		if (doubleBuffer) {
			bufferTexture[BUFFER_OPTIONBUTTON_GREEN + frame - 32] = cocos2d::RenderTexture::create(OPTIONBUTTONSIZE_X, OPTIONBUTTONSIZE_Y);
			bufferTexture[BUFFER_OPTIONBUTTON_GREEN + frame - 32]->retain();
			bufferTexture[BUFFER_OPTIONBUTTON_GREEN + frame - 32]->setAnchorPoint(Vec2(0, 1.0f));
			bufferTexture[BUFFER_OPTIONBUTTON_GREEN + frame - 32]->setPosition(0, DY);

			PushRenderTarget(bufferTexture[BUFFER_OPTIONBUTTON_GREEN + frame - 32], bufferLayer[BUFFER_OPTIONBUTTON_GREEN + frame - 32]);
			DrawFrame(0, OPTIONBUTTONSIZE_Y, OPTIONBUTTONSIZE_X, OPTIONBUTTONSIZE_Y, FRAME_GREEN + frame - 32);
			PopRenderTarget();

			texture[BUFFER_OPTIONBUTTON_GREEN_IMG + frame - 32] = bufferTexture[BUFFER_OPTIONBUTTON_GREEN + frame - 32]->getSprite()->getTexture();

			sprite[BUFFER_OPTIONBUTTON_GREEN_IMG + frame - 32] = Sprite::createWithTexture(texture[BUFFER_OPTIONBUTTON_GREEN_IMG + frame - 32]);

		}
		break;
	case 36://BUFFER_CREWUPGRADEBUTTON_GREEN
	case 37://BUFFER_CREWUPGRADEBUTTON_GREY
		if (doubleBuffer) {
			bufferTexture[BUFFER_CREWUPGRADEBUTTON_GREEN + frame - 36] = cocos2d::RenderTexture::create(CREWUPGRADEBUTTONSIZE_X, CREWUPGRADEBUTTONSIZE_Y);
			bufferTexture[BUFFER_CREWUPGRADEBUTTON_GREEN + frame - 36]->retain();
			bufferTexture[BUFFER_CREWUPGRADEBUTTON_GREEN + frame - 36]->setAnchorPoint(Vec2(0, 1.0f));
			bufferTexture[BUFFER_CREWUPGRADEBUTTON_GREEN + frame - 36]->setPosition(0, DY);

			PushRenderTarget(bufferTexture[BUFFER_CREWUPGRADEBUTTON_GREEN + frame - 36], bufferLayer[BUFFER_CREWUPGRADEBUTTON_GREEN + frame - 36]);
			DrawFrame(0, CREWUPGRADEBUTTONSIZE_Y, CREWUPGRADEBUTTONSIZE_X, CREWUPGRADEBUTTONSIZE_Y, frame == 36 ? FRAME_GREEN : FRAME_GREY);
			PopRenderTarget();

			texture[BUFFER_CREWUPGRADEBUTTON_GREEN_IMG + frame - 36] = bufferTexture[BUFFER_CREWUPGRADEBUTTON_GREEN + frame - 36]->getSprite()->getTexture();

			sprite[BUFFER_CREWUPGRADEBUTTON_GREEN_IMG + frame - 36] = Sprite::createWithTexture(texture[BUFFER_CREWUPGRADEBUTTON_GREEN_IMG + frame - 36]);

		}
		break;
	case 38:
		//if (doubleBuffer) {
		//	DrawBackMap(-78 * _2X, (float)82 * _2X * (DY / DX), LASTDEVIL25, 0.9f, bufferTexture[BUFFER_CONTROLER], bufferLayer[BUFFER_CONTROLER], true);
		//}
		break;

	case 40:
		GotoTitle();
		break;
		//case 16:
		//	DrawGoldNum(9876543210, DX / 2, DY / 2, RIGHT, 0, -1, true, 1, gScreenBuffer, gScreenLayer, false);
		//	break;
	}
}

void LoadingDraw(void)
{
	return;

	SetAlpha(24);
	MemRect(0, DY, DX, DY, COLOR_NAVY);
	SetAlpha(32);
	DrawCmfDetailShadow(CMF_NPC_DOG, 0, DX / 2, DY / 2, RIGHT, 1.0f);
	CenterAlpha(DX / 2, DY / 2 - 8 * _2X, ALPHA_LOADING, FONT_SMALL, false, 1.0f);
}

void TitleDraw(void)
{
	int i, j, k;
	std::string fileName;
	int x = 0, y = MINDY_MIN / 2 + DY / 2 + (MINDY_MIN - MINDY) / 2;
	float zoom;
	float scale = 0.7f;
	int width = GetGoldAlphaWidth(ALPHA_RANDOM, FONT_GOLD_LARGE, scale) + 8 * _2X + GetGoldAlphaWidth(ALPHA_SWORD, FONT_GOLD_LARGE, scale);
	int remainBoxCnt;
	int monCmf[] = { CMF_FROG , CMF_FROG_RED , CMF_FROG_BLUE, CMF_FROG_PURPLE, CMF_FROG_GREEN, CMF_FROG_GOLD, CMF_FROG_BLACK };

	int curQuest = robin.quest;
	int questCmf = questInfo[robin.quest * QUESTINFODATASIZE];
	int questRequest = questInfo[robin.quest * QUESTINFODATASIZE + 2];
	int itemType = questRequestItem[questRequest * 3];
	int itemDetail = questRequestItem[questRequest * 3 + 1];
	int itemGrade = questRequestItem[questRequest * 3 + 2];

	switch (curMenu) {
	case MENU_LOADING://�� ó���� 100 ������ ȭ�鿬��
#ifdef COSTUMETEST
		if (frame == 1) {



			SetEnemyUser();




		}

		//DrawPlayer(&ao[DIANA], 1000 + PO_C1_SATLASER_SHOT0 + frame / 10 % PO_C1_SATLASER_SAT20, DX / 2, DY / 2, LEFT, 2.0f, false, false, gScreenBuffer, gScreenLayer, false);

		//for (i = ACTIONCARD_SUMMON_SNAIL; i < ACTIONCARD_SUMMON_ELKEIN + 1; i++) {
		//	DrawRouletteCard(0, i, 1, ROULETTECARDSIZE_X * ((i - ACTIONCARD_SUMMON_SNAIL) % 7), DY - ROULETTECARDSIZE_Y * ((i - ACTIONCARD_SUMMON_SNAIL) / 7), 1.0f, false, false, PLAYER, false, gScreenBuffer, gScreenLayer, false);
		//}

		//DrawFrame(DX / 2, DY / 2, CREWUPGRADEBUTTONSIZE_X, CREWUPGRADEBUTTONSIZE_Y, FRAME_GREEN, gScreenBuffer, gScreenLayer, false);
		//DrawSkillCard(0, 0, 1, DX / 2 - REWARDCARDSIZE_X, DY / 2 + REWARDCARDSIZE_Y, 2.0f, gScreenBuffer, gScreenLayer, false);
		//MemRect(DX / 2 + points[(frame % 1000)][0], DY / 2 + points[(frame % 1000)][1], 2 * _2X, 2 * _2X, COLOR_WHITE, gScreenBuffer, gScreenLayer, false);
		zoom = 1.0f;
		DrawDioramaCrew(&enemyHouse, xOffset + DX / 2 - (float)(DIORAMASIZE_X / 2) * zoom, DY / 2 + (float)DIORAMASIZE_Y / 2 * zoom, zoom, frame % 100, false, false, false);
		//EnemyUserProfileDraw(robin.enemyUserIdx, robin.stage, robin.room, 40 * _2X, DY - 80 * _2X, 0.1f + (float)(frame / FPS % 12) * 0.1f, gScreenBuffer, gScreenLayer, false);
		/*
		DrawPlayerCostume(
			3, 1,
			3, 1,
			3, 1,
			3, 1,
			3, 1,
			3, 1,

			(float)(DX / 2) * 1, (float)(DY / 2) * 1, RIGHT, false, 1.0f, gScreenBuffer, gScreenLayer, false
		);


		for (i = 0; i < 7; i++) {
			DrawCmfDetail(monCmf[i], 0, DX / 2 - 80 * _2X + (160 * _2X) * (i % 2), DY / 2 + 160 * _2X - 80 * _2X * (i / 2), LEFT, 1.0f, false, false, gScreenBuffer, gScreenLayer, false);
		}
		*/
		//DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + DX / 2 - DIORAMASIZE_X / 2, y - DY / 2 + DIORAMASIZE_Y / 2 + 72 * _2X, false, false, false, false, false, 1.0f, sprite[MAP_DIORAMA_IMG + houseOrder[0]], gScreenBuffer, gScreenLayer, MAP_DIORAMA_IMG + houseOrder[0], false);
		//NewCollectionDraw(0, DY, 1.0f, gScreenBuffer, gScreenLayer, false);
#else
		DrawImage(640, 1024, 0, 0, xOffset + DX / 2 - 320 * _2X / 2, DY / 2 + 512 * _2X / 2, false, false, false, false, false, 1.0f, sprite[TITLE_IMG], TITLE_IMG);

		//DrawGoldAlpha(xOffset + DX / 2, DY / 2 - 80 * _2X, ALPHA_COIN, FONT_GOLD_LARGE, scale + 1.0f, CENTER, frame % FPS < FPS / 2 ? true : false, false, gScreenBuffer, gScreenLayer, false);
		//DrawGoldAlpha(xOffset + DX / 2, DY / 2 - 124 * _2X, ALPHA_SWORD, FONT_GOLD_LARGE, scale + 0.4f, CENTER, frame % FPS < FPS / 2 ? true : false, false, gScreenBuffer, gScreenLayer, false);

		//DrawGoldAlpha(xOffset + DX / 2, DY / 2 - 64 * _2X, ALPHA_RANDOM, FONT_GOLD_LARGE, scale - 0.1f, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
		//DrawGoldAlpha(xOffset + DX / 2, DY / 2 - 84 * _2X, ALPHA_CASTLE, FONT_GOLD_LARGE, scale + 0.4f, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
		//DrawGoldAlpha(xOffset + DX / 2, DY / 2 - 114 * _2X, ALPHA_HERO, FONT_GOLD_LARGE, scale + 1.5f, CENTER, false, false, gScreenBuffer, gScreenLayer, false);


		/*

		if (frame % FPS < FPS / 2)
			DrawGoldAlpha(xOffset + DX / 2, DY / 2 - 88 * _2X, ALPHA_COIN, FONT_GOLD_LARGE, scale + 0.7f, CENTER, true, false, gScreenBuffer, gScreenLayer, false);
		else {
			DrawGoldAlpha(xOffset + DX / 2, DY / 2 - 88 * _2X, ALPHA_COIN, FONT_GOLD_LARGE, scale + 0.7f, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
			DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, xOffset + DX / 2 - 10 * _2X, DY / 2 - 100 * _2X, 0.5f, false, false, false, true, gScreenBuffer, gScreenLayer, false);
		}

		DrawGoldAlpha(xOffset + DX / 2, DY / 2 - 124 * _2X, ALPHA_SWORD, FONT_GOLD_LARGE, scale + 0.3f, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
		*/

		
		switch (frame) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		//	break;
		case 22:
			//frame = 21;

			//DrawIcon(ICON_HEART, DX - ITEMICONSIZE * 2, ITEMICONSIZE * 2 + BOTTOMMENUHEIGHT, 1.0f + Abs(32 - frame % 64) * 0.01f, false, false, false, false, gScreenBuffer, gScreenLayer, false);
			//DrawHeart(DX - ITEMICONSIZE, ITEMICONSIZE + BOTTOMMENUHEIGHT, false, false, LEFT, 1.0f, gScreenBuffer, gScreenLayer, false);
			//DrawFrame(0, 120 * _2X, DX, 120 * _2X, FRAME_TALKWIN, gScreenBuffer, gScreenLayer, false);

			//DrawWindow2(30 * _2X, DY - 30 * _2X, 120 * _2X, 60 * _2X, COLOR_NAVY, 1.0f, gScreenBuffer, gScreenLayer, false);
			//DrawWindow2(30 * _2X, DY - 130 * _2X, 120 * _2X, 60 * _2X, COLOR_NAVY, 0.5f, gScreenBuffer, gScreenLayer, false);
			//DrawWindow2(30 * _2X, DY - 230 * _2X, 120 * _2X, 60 * _2X, COLOR_NAVY, 0.2f, gScreenBuffer, gScreenLayer, false);

			//DrawBigNumTTF(1000, 0, DY, NUM_FONT_LARGE, LEFT, false, false, (float)((REWARDCARDSIZE_X - 8 * _2X) / 2) * 1.0f, false, 0.7f, true, gScreenBuffer, gScreenLayer, false);
			//DrawBigNumTTF(10000, 0, DY - 20 * _2X, NUM_FONT_LARGE, LEFT, false, false, (float)((REWARDCARDSIZE_X - 8 * _2X) / 2) * 1.0f, false, 1.0f, true, gScreenBuffer, gScreenLayer, false);
			LoadingBarDraw(xOffset + DX / 2 - 525 * _2X / 2 + 180 * _2X, 40 * _2X, frame);
			break;
			//case CURTAINFRAME - 1:
			//case 23:
		default:

			touchDisable = false;

			DrawItemCard(ITEM_CREW, CREW_SEBASTIAN, GRADE_NORMAL, 1, 1, false, xOffset + 0, 100 * _2X, TEXT_NEWGAME, 0.55f, true, TOUCH_FUNC_DEBUG_RESETGAME, TOUCH_FUNC_DEBUG_RESETGAME, true, 0);
			
			DrawItemCard(ITEM_CREW, CREW_KING, GRADE_NORMAL, 1, 1, false, xOffset + DX / 2 + 120 * _2X - 32 * _2X, 100 * _2X, TEXT_CONTINUE, 0.55f, true, TOUCH_FUNC_DEBUG_MAXSTATUS, TOUCH_FUNC_DEBUG_MAXSTATUS, true, 0);

			//SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_GOTOPLAY);


			//DrawCmfDetailShadow(CMF_NPC_SEBASTIAN, 0, DX / 2 - 64 * _2X, DY / 2 - 256 * _2X, RIGHT, 2, gScreenBuffer, gScreenLayer, false);
			//DrawHand(xOffset + DX / 2 - 64 * _2X - 32 * _2X, DY / 2 - 256 * _2X + 100 * _2X - 16 * _2X, frame / 2, 2.0f, gScreenBuffer, gScreenLayer, false);

			//MemRectBoth(xOffset + DX / 2 - 64 * _2X - 40 * _2X, DY / 2 - 256 * _2X + 24 * _2X, 48 * _2X, 11 * _2X, COLOR_BLACK, COLOR_WHITE, gScreenBuffer, gScreenLayer, false);
			//CenterAlpha(xOffset + DX / 2 - 64 * _2X - 16 * _2X, DY / 2 - 256 * _2X + 24 * _2X - 2 * _2X, ALPHA_NEWGAME, FONT_SMALL, false, 1.0f, gScreenBuffer, gScreenLayer, false);

			//DrawTextButton(DX / 2 - 32 * _2X, DY / 2 - 128 * _2X, 64 * _2X, 28 * _2X, frame, false, 1.0f, false, TEXT_NEWGAME, gScreenBuffer, gScreenLayer, false);
			//SetRectPoint(DX / 2 - 32 * _2X - 8 * _2X, DY / 2 - 128 * _2X + 8 * _2X, 64 * _2X + 16 * _2X, 28 * _2X + 16 * _2X, TOUCH_FUNC_GOTODEMO);

			//DrawTextButton(DX / 2 - 32 * _2X, DY / 2 - 208 * _2X, 64 * _2X, 28 * _2X, frame, false, 1.0f, false, TEXT_CONTINUE, gScreenBuffer, gScreenLayer, false);
			//SetRectPoint(DX / 2 - 32 * _2X - 8 * _2X, DY / 2 - 208 * _2X + 8 * _2X, 64 * _2X + 16 * _2X, 28 * _2X + 16 * _2X, TOUCH_FUNC_GOTOPLAY);

			//DrawRewardCard(ITEM_SWORD, 1, GRADE_NORMAL, 1, 1, DX / 2, DY / 2, false, 2.0f, true, false, true, STAR3 + 1, STAR3 + 1, true, 0, gScreenBuffer, gScreenLayer, false);
			//if (robin.bossRoom == true) {
			//	GotoBoss();

			//}
			//else {
			
			//option.gameControl = CONTROL_MANUAL;
			//drawHandle = MD_OPENING;
			//keyHandle = MK_TALK;
			//openingTextPage = 0;
			//SetFrameText(TEXT_OPENING_0_0, DX - 32 * _2X, 3, 1.4f);
			break;
		}

#endif
		break;
		//�α��� �̷��� ������ �α��� ����
	case MENU_LOGIN:
		MemRect(0, DY, DX, DY, COLOR_BLACK);
		for (i = 0; i < TOTAL_LOGIN; i++) {
			MemRect(DX / 2 - 128 * _2X, DY / 2 + 64 * _2X * 2 - 64 * _2X * i, 256 * _2X, 48 * _2X, COLOR_WHITE);
			DrawImage(32 * _2X, 32 * _2X, i * 32 * _2X, 147 * _2X, DX / 2 - 120 * _2X, DY / 2 + 64 * _2X * 2 - 64 * _2X * i - 8 * _2X, false, false, false, false, false, 1.0f, sprite[ETC_IMG], ETC_IMG);
			SetFontColor(COLOR_GREY);
			CenterTextSolid(TEXT_LOGIN_FACEBOOK + i, DX / 2 + 24 * _2X, DY / 2 + 64 * _2X * 2 - 64 * _2X * i - 20 * _2X, 1.0f);
			SetRectPoint(DX / 2 - 128 * _2X, DY / 2 + 64 * _2X * 2 - 64 * _2X * i, 256 * _2X, 48 * _2X, TOUCH_FUNC_TITLE_LOGIN_FACEBOOK + i);
		}
		break;
		//�������
	case MENU_POLICY:
		SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_TITLE);
		break;
	}


}

void OpeningDraw(void)
{
	int imgW = 765;
	int imgH = 1024;
	int imgX = DX / 2 - imgW / 2;
	int imgY = DY / 2 + imgH / 2;

	int textX = 32 * _2X;
	int textY = 80 * _2X;
	int textW = DX - 64 * _2X;
	float textZoom = 1.4f;

	int openingScene = openingTextPage / OPENING_TEXT_PER_SCENE;
	int textIndex = TEXT_OPENING_0_0 + openingTextPage;

	MemRect(0, DY, DX, DY, COLOR_BLACK);

	DrawImage(
		imgW, imgH,
		0, 0,
		imgX, imgY,
		false, false, false, false, false,
		1.0f,
		sprite[OP0_IMG + openingScene],
		OP0_IMG + openingScene);

	FrameText(
		TEXTPTR(textIndex),
		textX,
		textY,
		textW,
		textLines,
		0,
		textZoom);
}

void DrawCmfPopUp(int cmf, int textIdx, int x, int y, int dx, int dy, int textDx, int line, int startFrame, float zoom, int dir)
{
	//DrawImage((float)POPUPWINDOWSIZE_X * zoom, (float)(POPUPWINDOWSIZE_Y)*zoom, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);
	SetAlpha(24);
	MemRect(x, y, dx, dy, 0x2A2A3A);
	SetAlpha(32);

	// "DAY" �ؽ�Ʈ (�����ϰ� ǥ��)
	//char dayText[32];
	//sprintf(dayText, "DAY %d", day);
	DrawImage(512, 19, 2, 612, x + dx / 2 - (float)(512 / 2) * zoom, y - (float)0 * _2X * zoom, false, false, false, false, false, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	DrawImage(512, 19, 2, 612, x + dx / 2 - (float)(512 / 2) * zoom, y - (float)(dy - 16 * _2X) * zoom, false, false, false, false, false, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

	if (popUpFrame > startFrame + 1) {
		if (popUpFrame == startFrame + 2)
			PlayMusic(M_JUMP);
		//ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(280 * _2X - 20 * _2X) * zoom, y - (float)(0 * _2X - 8 * _2X) * zoom, SHADOW_IMG, zoom, cvtDest, cvtLayer, buffering);
		//DrawCmfDetail(cmf, popUpFrame - (startFrame + 1) - 1 < 12 ? frame % 4 : 0, x + (float)(280 * _2X) * zoom, y - float(0 * _2X - (popUpFrame - (startFrame + 1) - 1 < 7 ? jumpFullFrame2[popUpFrame - (startFrame + 1) - 1] : 0)) * zoom, LEFT, zoom * 2, false, false, cvtDest, cvtLayer, buffering);
		ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(32 * _2X - 20 * _2X) * zoom, y - (float)(64 * _2X - 8 * _2X) * zoom, SHADOW_IMG, zoom);
		DrawCmfDetail(cmf, popUpFrame - (startFrame + 1) - 1 < 12 ? frame % 4 : 0, x + (float)(32 * _2X) * zoom, y - float(64 * _2X - (popUpFrame - (startFrame + 1) - 1 < 7 ? jumpFullFrame2[popUpFrame - (startFrame + 1) - 1] : 0)) * zoom, dir, zoom * 2, false, false);

	}

	if (textIdx) {
		//if (popUpFrame == startFrame + 2)
		//	SetFrameText(textIdx, textDx, line, zoom);

		if (popUpFrame > startFrame + 2) {
			SetFontColor(COLOR_WHITE);
			FrameText(TEXTPTR(textIdx), x + (float)((DX - 512) / 2 + 40 * _2X) * zoom, y - (float)(16 * _2X) * zoom, 1.2f * textDx, textLines, textCurPage, 1.2f * zoom);
			//SetFontColor(COLOR_WHITE);
		}
	}

	popUpFrame++;
}

void GNBDraw(int x, int y)
{
	int i;

	//�޴���ư
	DrawImage(140, 145, 1, 1, x + DX - (float)148 * 0.45f, y - 1 * _2X, false, false, false, false, false, 0.45f, sprite[UI_NEW_IMG], UI_NEW_IMG);
	switch (drawHandle) {
	default:
		if (curMenu == MENU_PLAY) {
			if (xOffset != 0)//ȭ���� 
				SetRectPoint(x, y, DX, DY, (curMenu == MENU_PLAY ? TOUCH_FUNC_GAMEMENU : TOUCH_FUNC_GAMEMENU_OUT));
			else
				SetRectPoint(x + DX - 36 * _2X, y, 36 * _2X, 40 * _2X, (curMenu == MENU_PLAY ? TOUCH_FUNC_GAMEMENU : TOUCH_FUNC_GAMEMENU_OUT));
		}
		else {
			SetRectPoint(x + DX - 36 * _2X, y, 36 * _2X, 40 * _2X, (curMenu == MENU_PLAY ? TOUCH_FUNC_GAMEMENU : TOUCH_FUNC_GAMEMENU_OUT));
		}
		break;
	case MD_BATTLE:
		//SetRectPoint(x, y, DX, DY, (curMenu == MENU_PLAY ? TOUCH_FUNC_GAMEMENU : TOUCH_FUNC_GAMEMENU_OUT));
		break;
	case MD_BOSSRAID:
		SetAlpha(32 - Abs(frame % 32 - 16));
		DrawImage(18 * _2X, 14 * _2X, 58 * _2X, 174 * _2X, x + DX - 32 * _2X + 6 * _2X, y - 2 * _2X - 7 * _2X, false, false, false, false, false, 1.0f, sprite[COMMON_IMG], COMMON_IMG);
		SetAlpha(32);

		SetRectPoint(x + DX - 48 * _2X, y, 48 * _2X, 48 * _2X, TOUCH_FUNC_BOSSRAID_OUT);

		break;
	}
}

void ActiveHelpDraw()
{
	int i;
	int startX, startY, width;
	ITEM* it;

	if (curtainFrame == 0)
		touchIdleFrame++;

	switch (drawHandle) {
	case MD_BATTLE:

		break;
	case MD_RAID:
		if (attackSequence == ATTACKSEQUENCE_READY && !curtainFrame) {
			//DrawAlpha(x + 4 * _2X, y - 2 * _2X)
			SetAlpha(32 - Abs(robin.playtime % 16 - 8));
			CenterText(TEXT_TARGETING_RAID, xOffset + DX / 2 - 80 * _2X + 160 * _2X / 2 + 2 * _2X, STATUSWIN_Y2 + HEARTBARGAP - 3 * _2X, 1.0f);
			SetAlpha(32);
		}

		break;
	}
}

void LogDraw(LOG* g)
{
	int enemyType = GetTypeFromCmf(g->cmf);
	DrawFrame(g->x - (float)(LOG_X / 2) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom, (float)LOG_X * g->zoom, (float)LOG_Y * g->zoom, FRAME_SHOPBALLOON);

	switch (g->type) {
	case LOG_EVENT_QUESTSTART:
		DrawIcon(g->icon, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(8 * _2X) * g->zoom, g->zoom * 1.5f, false, false, true, true);
		//SetFontColor(COLOR_BROWN);
		LineTextStrSolid(g->text, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 8 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X) * g->zoom, (float)(LOG_X - 40 * _2X) * g->zoom, -1, -1, g->zoom);
		//SetFontColor(COLOR_WHITE);
		break;
	case LOG_EVENT_BATTLESTART:
		DrawIcon(g->icon, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(8 * _2X) * g->zoom, g->zoom * 1.5f, false, false, true, true);

		//SetFontColor(COLOR_BROWN);
		LineTextStr(g->text, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 14 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X) * g->zoom, (float)(LOG_X - 40 * _2X) * g->zoom, -1, -1, g->zoom);
		//SetFontColor(COLOR_WHITE);
		break;
	case LOG_EVENT_RAIDSTART:
		//DrawNeutral(OBJ_BOX0 + boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], g->x - (float)(LOG_X / 2) * g->zoom + (float)(22 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(32 * _2X) * g->zoom, LEFT, 1.6 * g->zoom, cvtDest, cvtLayer, buffering);
		DrawIcon(g->icon, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(8 * _2X) * g->zoom, g->zoom * 1.5f, false, false, true, true);

		//SetFontColor(COLOR_BROWN);
		LineTextStr(g->text, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 14 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X) * g->zoom, (float)(LOG_X - 40 * _2X) * g->zoom, -1, -1, g->zoom);
		break;
	case LOG_RAID:
		DrawCmfDetailShadow(g->cmf, crewPos[enemyType * 5 + 0], g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 16 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(32 * _2X) * g->zoom, LEFT, g->zoom);
		DrawGoldAlpha(g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 20 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(34 * _2X) * g->zoom, ALPHA_BOSS, FONT_GOLD_LARGE, g->zoom * 0.5f, CENTER, true, false);
		LineTextStr(g->text, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 14 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X) * g->zoom, (float)(LOG_X - 40 * _2X) * g->zoom, -1, -1, g->zoom);

		DrawIcon(g->icon == ICON_GOLD ? g->icon + frame % GOLDICONFRAME : 0, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 16 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X + 26 * _2X) * g->zoom, g->zoom, false, false, false, true);
		DrawNum(g->count, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 16 * _2X + 20 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X + 28 * _2X) * g->zoom, NUM_FONT_NORMAL, LEFT, false, MINUS, true, g->zoom, true);
		break;
	case LOG_BATTLE:
		DrawCmfDetailShadow(g->cmf, crewPos[enemyType * 5 + 0], g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 16 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(32 * _2X) * g->zoom, LEFT, g->zoom);
		DrawGoldAlpha(g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 20 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(34 * _2X) * g->zoom, ALPHA_BOSS, FONT_GOLD_LARGE, g->zoom * 0.5f, CENTER, true, false);
		grayScale = 32;
		DrawCmfDetailShadow(g->cmf2, crewPos[enemyType * 5 + 0], g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 16 * _2X + 160 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(40 * _2X) * g->zoom, LEFT, g->zoom);
		grayScale = 0;
		DrawEffect(DEBUF_STUN0 + frame / MOTIONDIV % 6, g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 16 * _2X + 160 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(40 * _2X) * g->zoom, LEFT, false, g->zoom);
		LineTextStr(g->text, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 14 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X) * g->zoom, (float)(LOG_X - 80 * _2X) * g->zoom, -1, -1, g->zoom);
		break;
	case LOG_BOSSGETCOIN:
		DrawCmfDetailShadow(g->cmf, crewPos[enemyType * 5 + 0], g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 16 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(32 * _2X) * g->zoom, LEFT, g->zoom);
		DrawGoldAlpha(g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 20 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(34 * _2X) * g->zoom, ALPHA_BOSS, FONT_GOLD_LARGE, g->zoom * 0.5f, CENTER, true, false);
		DrawCmfDetailShadow(g->cmf2, crewPos[enemyType * 5 + 0], g->x - (float)(LOG_X / 2) * g->zoom + (float)(4 * _2X + 16 * _2X + 160 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(40 * _2X) * g->zoom, LEFT, g->zoom);
		LineTextStr(g->text, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 14 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X) * g->zoom, (float)(LOG_X - 80 * _2X) * g->zoom, -1, -1, g->zoom);
		DrawIcon(g->icon == ICON_GOLD ? g->icon + frame % GOLDICONFRAME : 0, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 16 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X + 26 * _2X) * g->zoom, g->zoom, false, false, false, true);
		DrawNum(g->count, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 16 * _2X + 20 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X + 28 * _2X) * g->zoom, NUM_FONT_NORMAL, LEFT, false, PLUS, true, g->zoom, true);

		break;
	case LOG_SKILL:
		DrawSkillIcon(g->icon, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(8 * _2X) * g->zoom, g->zoom * 1.5f);
		SetFontColor(COLOR_BROWN);
		LineTextStrSolid(g->text, g->x - (float)(LOG_X / 2) * g->zoom + (float)(8 * _2X + (float)16 * _2X * 1.5f + 8 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X) * g->zoom, (float)(LOG_X - 40 * _2X) * g->zoom, -1, -1, g->zoom);
		SetFontColor(COLOR_WHITE);
		break;
	case LOG_BETHEART:
		//���ڸ� �����ְ�
		PushButtonDraw(g->cmf, g->x - (float)(LOG_X / 3 + 8 * _2X) * g->zoom, g->y - (float)(LOG_Y * 2 / 5) * g->zoom, false, g->zoom, false);
		DrawBox(ao[ITEMBOX].etc, g->x - (float)(LOG_X / 3 + 8 * _2X) * g->zoom, g->y - (float)(LOG_Y * 2 / 5) * g->zoom, LEFT, false, false, false, false, true, g->zoom * 2.0f);
		DrawHeartButton(g->count, g->x - (float)(0 * _2X) * g->zoom/* + (float)(2 * _2X) * g->zoom*/, g->y + (float)(LOG_Y / 2) * g->zoom + (float)(-0 * _2X) * g->zoom, g->zoom * 1.0f, false, false);
		LineTextStr(g->text, g->x - (float)(LOG_X / 5) * g->zoom/* + (float)(8 * _2X + (float)16 * _2X * 1.5f + 58 * _2X) * g->zoom*/, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(30 * _2X) * g->zoom, (float)(LOG_X - BOXSIZE_X + ITEMICONSIZE) * g->zoom, -1, -1, g->zoom);
		break;
	case LOG_BETCOIN:
		DrawRouletteNumIcon(g->count, g->icon, g->x, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X) * g->zoom, true, CENTER, g->zoom);

		SetFontColor(COLOR_BROWN);
		LineTextStrSolid(g->text, g->x - (float)(LOG_X / 2 - 4 * _2X) * g->zoom, g->y + (float)(LOG_Y / 2) * g->zoom - (float)(4 * _2X + ITEMICONSIZE + 4 * _2X) * g->zoom, (float)(LOG_X)*g->zoom, -1, -1, g->zoom);
		SetFontColor(COLOR_WHITE);
		break;
	}
}

int GetEventMenuPosX(int eventType, int eventStatus)
{
	int i;
	int eventIdx = robin.eventCnt - 1;
	for (i = 0; i < MAXGAMEEVENT; i++) {
		if (robin.gameEvent[i].type == eventType) {
			eventIdx = i;
			break;
		}
	}

	switch (eventType) {
	case EVENTTYPE_QUEST:
	case EVENTTYPE_PVP:
	case EVENTTYPE_DEBTDISCOUNT:
	case EVENTTYPE_DOUBLE:
	case EVENTTYPE_BOSSRAID:
	case EVENTTYPE_TOUCHGAME:
		switch (eventStatus)
		{
		case EVENT_OPEN:
			robin.gameEvent[eventIdx].speed = 32 * _2X;
			robin.gameEvent[eventIdx].speedIncrement = -1 * _2X;
			robin.gameEvent[eventIdx].targetX = DX - 20 * _2X;
			robin.gameEvent[eventIdx].x = DX - 20 * _2X + FPS * EVENTMOVE_DX;
			break;
		case EVENT_DOING:
			robin.gameEvent[eventIdx].speed = 0 * _2X;
			robin.gameEvent[eventIdx].speedIncrement = 0 * _2X;
			robin.gameEvent[eventIdx].targetX = DX - 20 * _2X;
			robin.gameEvent[eventIdx].x = DX - 20 * _2X;
			break;
		case EVENT_CLOSE:
			//if (robin.gameEvent[eventIdx].frame > 0)
			//	return DX - 20 * _2X + (robin.gameEvent[eventIdx].frame * EVENTMOVE_DX);
			//else
			robin.gameEvent[eventIdx].speed = 32 * _2X;
			robin.gameEvent[eventIdx].speedIncrement = -1 * _2X;
			robin.gameEvent[eventIdx].targetX = DX - 20 * _2X + FPS * EVENTMOVE_DX;
			robin.gameEvent[eventIdx].x = DX - 20 * _2X;
			break;
		}
		break;
	case EVENTTYPE_SHOP:
	case EVENTTYPE_DEBUG_NEWGAME:
	case EVENTTYPE_DEBUG_MAXGAME:
		switch (eventStatus)
		{
		case EVENT_OPEN:
			//if (robin.gameEvent[eventIdx].frame > 0)
			//	return 20 * _2X + (-FPS + robin.gameEvent[eventIdx].frame) * EVENTMOVE_DX;
			//else
			robin.gameEvent[eventIdx].speed = 32 * _2X;
			robin.gameEvent[eventIdx].speedIncrement = -1 * _2X;
			robin.gameEvent[eventIdx].targetX = 20 * _2X;
			robin.gameEvent[eventIdx].x = 20 * _2X - FPS * EVENTMOVE_DX;
			break;
		case EVENT_DOING:
			robin.gameEvent[eventIdx].speed = 0 * _2X;
			robin.gameEvent[eventIdx].speedIncrement = 0 * _2X;
			robin.gameEvent[eventIdx].targetX = 20 * _2X;
			robin.gameEvent[eventIdx].x = 20 * _2X;
			break;
		case EVENT_CLOSE:
			robin.gameEvent[eventIdx].speed = 32 * _2X;
			robin.gameEvent[eventIdx].speedIncrement = -1 * _2X;
			robin.gameEvent[eventIdx].targetX = 20 * _2X - FPS * EVENTMOVE_DX;
			robin.gameEvent[eventIdx].x = 20 * _2X;
			break;
		}
		break;
	}

	return robin.gameEvent[eventIdx].x;
}

int GetEventMenuPosY(int eventType, int eventStatus)
{
	int i;
	int eventIdx = robin.eventCnt - 1;

	for (i = 0; i < MAXGAMEEVENT; i++) {
		if (robin.gameEvent[i].type == eventType) {
			eventIdx = i;
			break;
		}
	}

	int yPos = DY - GNBHEIGHT - REWARDCARDSIZE_Y - 3 * ITEMICONSIZE;
	int yPos2 = DY - GNBHEIGHT - REWARDCARDSIZE_Y - 3 * ITEMICONSIZE;

	for (i = 0; i < eventIdx; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_PVP:
		case EVENTTYPE_QUEST:
		case EVENTTYPE_DEBTDISCOUNT:
		case EVENTTYPE_DOUBLE:
		case EVENTTYPE_BOSSRAID:
		case EVENTTYPE_TOUCHGAME:
			yPos2 -= 48 * _2X;

			break;
		case EVENTTYPE_SHOP:
		case EVENTTYPE_DEBUG_NEWGAME:
		case EVENTTYPE_DEBUG_MAXGAME:
			yPos -= 48 * _2X;

			break;
		}
	}

	switch (eventType) {
	case EVENTTYPE_PVP:
	case EVENTTYPE_QUEST:
	case EVENTTYPE_DEBTDISCOUNT:
	case EVENTTYPE_DOUBLE:
	case EVENTTYPE_BOSSRAID:
	case EVENTTYPE_TOUCHGAME:
		return yPos2;
	case EVENTTYPE_SHOP:
	case EVENTTYPE_DEBUG_NEWGAME:
	case EVENTTYPE_DEBUG_MAXGAME:
		return yPos;
	}
}

//��� �̺�Ʈ ��Ȳ�� ��Ʈ���ϴ� �Լ�
//�̺�Ʈ�� ũ�� ������ �߻��ϴ� �������� �̺�Ʈ��
//���� ����Ʈ�� �ٴ� �ΰ� ����Ʈ�� Ȯ���� �� �ִ�.
//�ش� �Լ����� �پ��� 
void EventScheduler(void)
{
	int i;
	int eventIdx = -1;

	int curQuest = robin.quest;
	int questCmf = questInfo[robin.quest * QUESTINFODATASIZE];
	int questRequest = questInfo[robin.quest * QUESTINFODATASIZE + 2];
	int itemType = questRequestItem[questRequest * 3];
	int itemDetail = questRequestItem[questRequest * 3 + 1];
	int itemGrade = questRequestItem[questRequest * 3 + 2];
	int questIcon;

	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);
	//TEST
	return;
	//���� ������ �ε����̸� ����� �ʴ´�.
	if ((curtainFrame || infoFrame || areaFrame))
		return;

	//���� ������ �������� �ʴٸ�

	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_SHOP:
			eventIdx = i;
			break;
		}
	}

	//���� �����̺�Ʈ�� �ϳ��� ���ٸ�
	if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1 && robin.maxStage[robin.stage] >= (gameEventOpenStage[EVENTTYPE_SHOP]) / TOTALROOM && robin.maxRoom[robin.stage] >= (gameEventOpenStage[EVENTTYPE_SHOP]) % TOTALROOM) {
		InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_SHOP, false, ICON_EVENT_BOX, FREEITEMTIME, TOUCH_FUNC_EVENT_SHOP);
		//SetPopUp(POPUPTYPE_QUESTINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
		//	false, false, false, false, false,
		//	false, false, false, false, false,
		//	false, false, false, false, false);

	}

	eventIdx = -1;

	//���� ���� ���� ����Ʈ�� ���ٸ� ��������Ʈ�� �÷�������

	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_QUEST:
			eventIdx = i;
			break;
		}
	}

	//���� �����̺�Ʈ�� �ϳ��� ���ٸ�
	if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1 && robin.maxStage[robin.stage] >= (gameEventOpenStage[EVENTTYPE_QUEST]) / TOTALROOM && robin.maxRoom[robin.stage] >= (gameEventOpenStage[EVENTTYPE_QUEST]) % TOTALROOM) {
		questIcon = GetItemIcon(questRequestItem[robin.quest * 3 + 0], questRequestItem[robin.quest * 3 + 1], questRequestItem[robin.quest * 3 + 2]);
		if (questInfo[robin.quest * QUESTINFODATASIZE + 1] == QUESTTYPE_RAID)
			questIcon = ICON_RAID;
		else if (questInfo[robin.quest * QUESTINFODATASIZE + 1] == QUESTTYPE_BATTLE)
			questIcon = ICON_BATTLE;
		//else
		//	questIcon = ICON_SUMMON + questInfo[robin.quest * QUESTINFODATASIZE + 0];
		InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_QUEST, questInfo[robin.quest * QUESTINFODATASIZE + 1], questIcon, questInfo[robin.quest * QUESTINFODATASIZE + 4], TOUCH_FUNC_EVENT_QUEST);
#ifdef INITPOPUP
		SetPopUp(POPUPTYPE_QUESTINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false);
#endif
		//rouletteOpen[GetRouletteIdx(collectionIdx, ACTIONCARD_QUEST)] = true;


	}

	eventIdx = -1;

	//���� ���� PVP ����Ʈ�� ���ٸ� PVP ����Ʈ�� �÷�������.
	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_PVP:
			eventIdx = i;
			break;
		}
	}

	//���� �����̺�Ʈ�� �ϳ��� ���ٸ�
	if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1 && robin.maxStage[robin.stage] >= (gameEventOpenStage[EVENTTYPE_PVP]) / TOTALROOM && robin.maxRoom[robin.stage] >= (gameEventOpenStage[EVENTTYPE_PVP]) % TOTALROOM) {
		//if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1) {
		InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_PVP, false, pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0], pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 1], TOUCH_FUNC_EVENT_PVP);
#ifdef INITPOPUP
		SetPopUp(POPUPTYPE_PVPQUESTINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false);
#endif

	}

	eventIdx = -1;

	//���� ������ �̺�Ʈ�� ������

	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_DEBTDISCOUNT:
			eventIdx = i;
			break;
		}
	}

	if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1 && robin.maxStage[robin.stage] >= (gameEventOpenStage[EVENTTYPE_DEBTDISCOUNT]) / TOTALROOM && robin.maxRoom[robin.stage] >= (gameEventOpenStage[EVENTTYPE_DEBTDISCOUNT]) % TOTALROOM) {
#ifdef INITPOPUP
		SetPopUp(POPUPTYPE_DEPTDISCOUNT, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false);
#endif

	}

	eventIdx = -1;

	//���� ���� �̺�Ʈ�� ������

	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_DOUBLE:
			eventIdx = i;
			break;
		}
	}

	if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1 && robin.maxStage[robin.stage] >= (gameEventOpenStage[EVENTTYPE_DOUBLE]) / TOTALROOM && robin.maxRoom[robin.stage] >= (gameEventOpenStage[EVENTTYPE_DOUBLE]) % TOTALROOM) {
#ifdef INITPOPUP
		SetPopUp(POPUPTYPE_fDOUBLE, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false);
#endif

	}
#ifdef GAMEDEBUG
	eventIdx = -1;

	//���� ���� ������ ���ٸ� ������ �÷�������.
	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_SHOP:
			eventIdx = i;
			break;
		}
	}

	//���� �����̺�Ʈ�� �ϳ��� ���ٸ�
	if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1 && robin.maxStage[robin.stage] >= (gameEventOpenStage[EVENTTYPE_PVP]) / TOTALROOM && robin.maxRoom[robin.stage] >= (gameEventOpenStage[EVENTTYPE_PVP]) % TOTALROOM)
		InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_SHOP, false, ICON_EVENT_BOX, SHOPEVENTTIME, TOUCH_FUNC_SHOP);

	eventIdx = -1;

	//EVENTTYPE_DEBUG_NEWGAME
	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_DEBUG_NEWGAME:
			eventIdx = i;
			break;
		}
	}

	//���� �����̺�Ʈ�� �ϳ��� ���ٸ�
	if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1 && robin.maxStage[robin.stage] >= (gameEventOpenStage[EVENTTYPE_DEBUG_NEWGAME]) / TOTALROOM && robin.maxRoom[robin.stage] >= (gameEventOpenStage[EVENTTYPE_DEBUG_NEWGAME]) % TOTALROOM)
		InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_DEBUG_NEWGAME, false, ICON_EVENT_BLUEFLAG, INFINITETIME, TOUCH_FUNC_DEBUG_RESETGAME);

	eventIdx = -1;

	//EVENTTYPE_DEBUG_MAXGAME
	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_DEBUG_MAXGAME:
			eventIdx = i;
			break;
		}
	}

	//���� �����̺�Ʈ�� �ϳ��� ���ٸ�
	if (eventIdx == -1 && robin.eventCnt < MAXGAMEEVENT - 1 && robin.maxStage[robin.stage] >= (gameEventOpenStage[EVENTTYPE_PVP]) / TOTALROOM && robin.maxRoom[robin.stage] >= (gameEventOpenStage[EVENTTYPE_PVP]) % TOTALROOM)
		InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_DEBUG_MAXGAME, false, ICON_EVENT_BLUEFLAG, INFINITETIME, TOUCH_FUNC_DEBUG_MAXSTATUS);

	eventIdx = -1;

	//EVENTTYPE_DEBUG_BOSSRAID
	for (i = 0; i < MAXGAMEEVENT; i++) {
		switch (robin.gameEvent[i].type) {
		case EVENTTYPE_BOSSRAID:
			eventIdx = i;
			break;
		}
	}

#endif
}

int GetEventMenuIdx(int eventType)
{
	int i;

	for (i = 0; i < MAXGAMEEVENT; i++) {
		if (robin.gameEvent[i].type == eventType)
			return i;
	}

	return -1;
}

void DeleteEventMenu(int eventIdx)
{
	int i;
	int j;
	for (i = 0; i < MAXGAMEEVENT; i++) {
		if (i == eventIdx) {
			for (j = i; j < MAXGAMEEVENT - 1; j++) {
				memcpy(&robin.gameEvent[j], &robin.gameEvent[j + 1], sizeof(GAMEEVENT));
			}
			memset(&robin.gameEvent[MAXGAMEEVENT - 1], 0, sizeof(GAMEEVENT));
			robin.eventCnt--;
			break;
		}
	}
}

//�̺�Ʈ�޴��� �ʱ�ȭ�ϴ� ��
void InitEventMenu(GAMEEVENT* gEvent, unsigned char type, unsigned char subType, short icon, long limitTime, int touchFunc)
{
	gEvent->type = type;
	gEvent->subType = subType;
	gEvent->icon = icon;
	gEvent->timeStamp = MC_knlCurrentTimeStamp();
	gEvent->limitTime = limitTime;
	//gEvent->limitTime = FPS * 10;
	gEvent->status = EVENT_OPEN;
	gEvent->barStatus = EVENT_BAR_NEW;
	gEvent->touchFunc = touchFunc;
	//gEvent->zoom = 0.1f;
	gEvent->frame = 1;
	gEvent->front = false;
	robin.eventCnt++;

	switch (gEvent->type) {
	case EVENTTYPE_QUEST:
		bar[BAR_QUEST].active = true;
		bar[BAR_QUEST].icon = icon;
		break;
	case EVENTTYPE_PVP:

		break;
	case EVENTTYPE_SHOP:

		break;
	case EVENTTYPE_DEBTDISCOUNT:
		//�����̺�Ʈ���� �� ����ֱ�
		gEvent->value = 20.0f;
		gEvent->icon = icon;
		break;
	case EVENTTYPE_DOUBLE:
		gEvent->icon = icon;
		break;
	case EVENTTYPE_BOSSRAID:
		gEvent->barStatus = BOSSRAID_ROYALFAMILY;//� �������ΰ�
		gEvent->barFrame = 0;//���° �����ΰ�
		gEvent->value = 0;//���� ü�� ����

		//InitBar(BAR_ENEMYUSER);
		break;
	case EVENTTYPE_DEBUG_NEWGAME:
		break;
	case EVENTTYPE_DEBUG_MAXGAME:
		break;
	}

	InitEventPos(gEvent, GetEventMenuPosX(gEvent->type, EVENT_OPEN), GetEventMenuPosY(gEvent->type, EVENT_OPEN), GetEventMenuPosX(gEvent->type, EVENT_DOING), GetEventMenuPosY(gEvent->type, EVENT_DOING), GetEventMenuPosX(gEvent->type, EVENT_DOING), GetEventMenuPosY(gEvent->type, EVENT_DOING), 16 * _2X, -1 * _2X, 1 * _2X, 1 * _2X, FPS, FPS, false, false, false,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	ArrangeEventMenu();
}

void sortArray(int arr[], int index[], int n) {
	int i, j, temp;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > 0 && arr[j + 1] > 0 && arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				temp = index[j];
				index[j] = index[j + 1];
				index[j + 1] = temp;
			}
		}
	}
}

void MainMenuOut(void)
{
	int i;
	//���⼭ ��� �޴��� �����̰�
	bar[BAR_HEART].nx = bar[BAR_HEART].x;
	bar[BAR_HEART].ny = bar[BAR_HEART].y;
	bar[BAR_HEART].targetX2 = bar[BAR_HEART].targetX = bar[BAR_HEART].x;
	bar[BAR_HEART].targetY2 = bar[BAR_HEART].targetY = bar[BAR_HEART].y - 256 * _2X;
	bar[BAR_HEART].speed2 = bar[BAR_HEART].speed = 8 * _2X;
	bar[BAR_HEART].speedIncrement2 = bar[BAR_HEART].speedIncrement = 1 * _2X;
	bar[BAR_HEART].frame = 1;

	bar[BAR_BOX].nx = bar[BAR_BOX].x;
	bar[BAR_BOX].ny = bar[BAR_BOX].y;
	bar[BAR_BOX].targetX2 = bar[BAR_BOX].targetX = bar[BAR_BOX].x;
	bar[BAR_BOX].targetY2 = bar[BAR_BOX].targetY = bar[BAR_BOX].y - 256 * _2X;
	bar[BAR_BOX].speed2 = bar[BAR_BOX].speed = 8 * _2X;
	bar[BAR_BOX].speedIncrement2 = bar[BAR_BOX].speedIncrement = 1 * _2X;
	bar[BAR_BOX].frame = 1;

	bar[BAR_ENEMYUSER].nx = bar[BAR_ENEMYUSER].x;
	bar[BAR_ENEMYUSER].ny = bar[BAR_ENEMYUSER].y;
	bar[BAR_ENEMYUSER].targetX2 = bar[BAR_ENEMYUSER].targetX = bar[BAR_ENEMYUSER].x + 128 * _2X;
	bar[BAR_ENEMYUSER].targetY2 = bar[BAR_ENEMYUSER].targetY = bar[BAR_ENEMYUSER].y;
	bar[BAR_ENEMYUSER].speed2 = bar[BAR_ENEMYUSER].speed = 8 * _2X;
	bar[BAR_ENEMYUSER].speedIncrement2 = bar[BAR_ENEMYUSER].speedIncrement = 1 * _2X;
	bar[BAR_ENEMYUSER].frame = 1;

	bar[BAR_DAILYQUEST].nx = bar[BAR_EQUIP].x;
	bar[BAR_EQUIP].ny = bar[BAR_EQUIP].y;
	bar[BAR_EQUIP].targetX2 = bar[BAR_EQUIP].targetX = bar[BAR_EQUIP].x + 128 * _2X;
	bar[BAR_EQUIP].targetY2 = bar[BAR_EQUIP].targetY = bar[BAR_EQUIP].y;
	bar[BAR_EQUIP].speed2 = bar[BAR_EQUIP].speed = 8 * _2X;
	bar[BAR_EQUIP].speedIncrement2 = bar[BAR_EQUIP].speedIncrement = 1 * _2X;
	bar[BAR_EQUIP].frame = 1;

	bar[BAR_MAINSHOP].nx = bar[BAR_MAINSHOP].x;
	bar[BAR_MAINSHOP].ny = bar[BAR_MAINSHOP].y;
	bar[BAR_MAINSHOP].targetX2 = bar[BAR_MAINSHOP].targetX = bar[BAR_MAINSHOP].x - 128 * _2X;
	bar[BAR_MAINSHOP].targetY2 = bar[BAR_MAINSHOP].targetY = bar[BAR_MAINSHOP].y;
	bar[BAR_MAINSHOP].speed2 = bar[BAR_MAINSHOP].speed = 8 * _2X;
	bar[BAR_MAINSHOP].speedIncrement2 = bar[BAR_MAINSHOP].speedIncrement = 1 * _2X;
	bar[BAR_MAINSHOP].frame = 1;

	bar[BAR_DAILYQUEST].nx = bar[BAR_DAILYQUEST].x;
	bar[BAR_DAILYQUEST].ny = bar[BAR_DAILYQUEST].y;
	bar[BAR_DAILYQUEST].targetX2 = bar[BAR_DAILYQUEST].targetX = bar[BAR_DAILYQUEST].x - 128 * _2X;
	bar[BAR_DAILYQUEST].targetY2 = bar[BAR_DAILYQUEST].targetY = bar[BAR_DAILYQUEST].y;
	bar[BAR_DAILYQUEST].speed2 = bar[BAR_DAILYQUEST].speed = 8 * _2X;
	bar[BAR_DAILYQUEST].speedIncrement2 = bar[BAR_DAILYQUEST].speedIncrement = 1 * _2X;
	bar[BAR_DAILYQUEST].frame = 1;

	bar[BAR_EQUIP].nx = bar[BAR_EQUIP].x;
	bar[BAR_EQUIP].ny = bar[BAR_EQUIP].y;
	bar[BAR_EQUIP].targetX2 = bar[BAR_EQUIP].targetX = bar[BAR_EQUIP].x - 128 * _2X;
	bar[BAR_EQUIP].targetY2 = bar[BAR_EQUIP].targetY = bar[BAR_EQUIP].y;
	bar[BAR_EQUIP].speed2 = bar[BAR_EQUIP].speed = 8 * _2X;
	bar[BAR_EQUIP].speedIncrement2 = bar[BAR_EQUIP].speedIncrement = 1 * _2X;
	bar[BAR_EQUIP].frame = 1;

	bar[BAR_CREWUPGRADE].nx = bar[BAR_CREWUPGRADE].x;
	bar[BAR_CREWUPGRADE].ny = bar[BAR_CREWUPGRADE].y;
	bar[BAR_CREWUPGRADE].targetX2 = bar[BAR_CREWUPGRADE].targetX = bar[BAR_CREWUPGRADE].x + 128 * _2X;
	bar[BAR_CREWUPGRADE].targetY2 = bar[BAR_CREWUPGRADE].targetY = bar[BAR_CREWUPGRADE].y;
	bar[BAR_CREWUPGRADE].speed2 = bar[BAR_CREWUPGRADE].speed = 8 * _2X;
	bar[BAR_CREWUPGRADE].speedIncrement2 = bar[BAR_CREWUPGRADE].speedIncrement = 1 * _2X;
	bar[BAR_CREWUPGRADE].frame = 1;

	bar[BAR_FRIENDS].nx = bar[BAR_FRIENDS].x;
	bar[BAR_FRIENDS].ny = bar[BAR_FRIENDS].y;
	bar[BAR_FRIENDS].targetX2 = bar[BAR_FRIENDS].targetX = bar[BAR_FRIENDS].x + 128 * _2X;
	bar[BAR_FRIENDS].targetY2 = bar[BAR_FRIENDS].targetY = bar[BAR_FRIENDS].y;
	bar[BAR_FRIENDS].speed2 = bar[BAR_FRIENDS].speed = 8 * _2X;
	bar[BAR_FRIENDS].speedIncrement2 = bar[BAR_FRIENDS].speedIncrement = 1 * _2X;
	bar[BAR_FRIENDS].frame = 1;

	bar[BAR_QUEST].nx = bar[BAR_QUEST].x;
	bar[BAR_QUEST].ny = bar[BAR_QUEST].y;
	bar[BAR_QUEST].targetX2 = bar[BAR_QUEST].targetX = bar[BAR_QUEST].x;
	bar[BAR_QUEST].targetY2 = bar[BAR_QUEST].targetY = bar[BAR_QUEST].y + 256 * _2X;
	bar[BAR_QUEST].speed2 = bar[BAR_QUEST].speed = 8 * _2X;
	bar[BAR_QUEST].speedIncrement2 = bar[BAR_QUEST].speedIncrement = 1 * _2X;
	bar[BAR_QUEST].frame = 1;

	for (i = PLAYER; i < TOTALCHAR; i++) {
		bar[BAR_INVENTORY + i].nx = bar[BAR_INVENTORY + i].x;
		bar[BAR_INVENTORY + i].ny = bar[BAR_INVENTORY + i].y;
		bar[BAR_INVENTORY + i].targetX2 = bar[BAR_INVENTORY + i].targetX = bar[BAR_INVENTORY + i].nx - DX;
		bar[BAR_INVENTORY + i].targetY2 = bar[BAR_INVENTORY + i].targetY = bar[BAR_INVENTORY + i].y;
		bar[BAR_INVENTORY + i].speed2 = bar[BAR_INVENTORY + i].speed = 8 * _2X;
		bar[BAR_INVENTORY + i].speedIncrement2 = bar[BAR_INVENTORY + i].speedIncrement = 1 * _2X;
		bar[BAR_INVENTORY + i].zoom2 = bar[BAR_INVENTORY + i].zoom;
		bar[BAR_INVENTORY + i].zoomIncrement2 = bar[BAR_INVENTORY + i].zoomIncrement = 0.0f;
		bar[BAR_INVENTORY + i].zoomEnd2 = bar[BAR_INVENTORY + i].zoomEnd = bar[BAR_INVENTORY + i].zoom;
		bar[BAR_INVENTORY + i].frame = 1;

		bar[BAR_SKILL + i].nx = bar[BAR_SKILL + i].x;
		bar[BAR_SKILL + i].ny = bar[BAR_SKILL + i].y;
		bar[BAR_SKILL + i].targetX2 = bar[BAR_SKILL + i].targetX = bar[BAR_SKILL + i].nx - DX;
		bar[BAR_SKILL + i].targetY2 = bar[BAR_SKILL + i].targetY = bar[BAR_SKILL + i].y;
		bar[BAR_SKILL + i].speed2 = bar[BAR_SKILL + i].speed = 8 * _2X;
		bar[BAR_SKILL + i].speedIncrement2 = bar[BAR_SKILL + i].speedIncrement = 1 * _2X;
		bar[BAR_SKILL + i].zoom2 = bar[BAR_SKILL + i].zoom;
		bar[BAR_SKILL + i].zoomIncrement2 = bar[BAR_SKILL + i].zoomIncrement = 0.0f;
		bar[BAR_SKILL + i].zoomEnd2 = bar[BAR_SKILL + i].zoomEnd = bar[BAR_SKILL + i].zoom;
		bar[BAR_SKILL + i].frame = 1;
	}

	//���⼭���� �̺�Ʈ�޴� �ܰ����� ������
	for (i = 0; i < robin.eventCnt; i++) {
		robin.gameEvent[i].nx = robin.gameEvent[i].x;
		robin.gameEvent[i].ny = robin.gameEvent[i].y;
		if (robin.gameEvent[i].nx < DX / 2)
			robin.gameEvent[i].targetX2 = robin.gameEvent[i].targetX = robin.gameEvent[i].nx - DX;
		else
			robin.gameEvent[i].targetX2 = robin.gameEvent[i].targetX = robin.gameEvent[i].nx + DX;

		robin.gameEvent[i].targetY2 = robin.gameEvent[i].targetY = robin.gameEvent[i].y;
		robin.gameEvent[i].speed2 = robin.gameEvent[i].speed = 8 * _2X;
		robin.gameEvent[i].speedIncrement2 = robin.gameEvent[i].speedIncrement = 1 * _2X;
		robin.gameEvent[i].zoom2 = robin.gameEvent[i].zoom;
		robin.gameEvent[i].zoomIncrement2 = robin.gameEvent[i].zoomIncrement = 0.0f;
		robin.gameEvent[i].zoomEnd2 = robin.gameEvent[i].zoomEnd = robin.gameEvent[i].zoom;
		robin.gameEvent[i].frame = 1;
	}

	ao[ITEMBOX].ny = ao[ITEMBOX].y;
	ao[ITEMBOX].dy = 16 * _2X;
}

void MainMenuIn(void)
{
	int i;

	bar[BAR_HEART].targetX2 = bar[BAR_HEART].targetX = bar[BAR_HEART].nx;
	bar[BAR_HEART].targetY2 = bar[BAR_HEART].targetY = bar[BAR_HEART].ny;
	bar[BAR_HEART].speed2 = bar[BAR_HEART].speed = 8 * _2X;
	bar[BAR_HEART].speedIncrement2 = bar[BAR_HEART].speedIncrement = 1 * _2X;
	bar[BAR_HEART].zoom2 = bar[BAR_HEART].zoom = BAR_HEART_ZOOM;
	bar[BAR_HEART].zoomIncrement2 = bar[BAR_HEART].zoomIncrement = 0.0f;
	bar[BAR_HEART].zoomEnd2 = bar[BAR_HEART].zoomEnd = bar[BAR_HEART].zoom;
	bar[BAR_HEART].frame = 1;

	bar[BAR_BOX].targetX2 = bar[BAR_BOX].targetX = bar[BAR_BOX].nx;
	bar[BAR_BOX].targetY2 = bar[BAR_BOX].targetY = bar[BAR_BOX].ny;
	bar[BAR_BOX].speed2 = bar[BAR_BOX].speed = 8 * _2X;
	bar[BAR_BOX].speedIncrement2 = bar[BAR_BOX].speedIncrement = 1 * _2X;
	bar[BAR_BOX].zoom2 = bar[BAR_BOX].zoom = BAR_BOX_ZOOM;
	bar[BAR_BOX].zoomIncrement2 = bar[BAR_BOX].zoomIncrement = 0.0f;
	bar[BAR_BOX].zoomEnd2 = bar[BAR_BOX].zoomEnd = bar[BAR_BOX].zoom;
	bar[BAR_BOX].frame = 1;

	bar[BAR_ENEMYUSER].targetX2 = bar[BAR_ENEMYUSER].targetX = bar[BAR_ENEMYUSER].nx;
	bar[BAR_ENEMYUSER].targetY2 = bar[BAR_ENEMYUSER].targetY = bar[BAR_ENEMYUSER].ny;
	bar[BAR_ENEMYUSER].speed2 = bar[BAR_ENEMYUSER].speed = 8 * _2X;
	bar[BAR_ENEMYUSER].speedIncrement2 = bar[BAR_ENEMYUSER].speedIncrement = 1 * _2X;
	bar[BAR_ENEMYUSER].zoom2 = bar[BAR_ENEMYUSER].zoom = BAR_ENEMYUSER_ZOOM;
	bar[BAR_ENEMYUSER].zoomIncrement2 = bar[BAR_ENEMYUSER].zoomIncrement = 0.0f;
	bar[BAR_ENEMYUSER].zoomEnd2 = bar[BAR_ENEMYUSER].zoomEnd = bar[BAR_ENEMYUSER].zoom;
	bar[BAR_ENEMYUSER].frame = 1;

	bar[BAR_MAINSHOP].targetX2 = bar[BAR_MAINSHOP].targetX = bar[BAR_MAINSHOP].nx;
	bar[BAR_MAINSHOP].targetY2 = bar[BAR_MAINSHOP].targetY = bar[BAR_MAINSHOP].ny;
	bar[BAR_MAINSHOP].speed2 = bar[BAR_MAINSHOP].speed = 8 * _2X;
	bar[BAR_MAINSHOP].speedIncrement2 = bar[BAR_MAINSHOP].speedIncrement = 1 * _2X;
	bar[BAR_MAINSHOP].zoom2 = bar[BAR_MAINSHOP].zoom = BAR_MAINSHOP_ZOOM;
	bar[BAR_MAINSHOP].zoomIncrement2 = bar[BAR_MAINSHOP].zoomIncrement = 0.0f;
	bar[BAR_MAINSHOP].zoomEnd2 = bar[BAR_MAINSHOP].zoomEnd = bar[BAR_MAINSHOP].zoom;
	bar[BAR_MAINSHOP].frame = 1;

	bar[BAR_DAILYQUEST].targetX2 = bar[BAR_DAILYQUEST].targetX = bar[BAR_DAILYQUEST].nx;
	bar[BAR_DAILYQUEST].targetY2 = bar[BAR_DAILYQUEST].targetY = bar[BAR_DAILYQUEST].ny;
	bar[BAR_DAILYQUEST].speed2 = bar[BAR_DAILYQUEST].speed = 8 * _2X;
	bar[BAR_DAILYQUEST].speedIncrement2 = bar[BAR_DAILYQUEST].speedIncrement = 1 * _2X;
	bar[BAR_DAILYQUEST].zoom2 = bar[BAR_DAILYQUEST].zoom = BAR_DAILYQUEST_ZOOM;
	bar[BAR_DAILYQUEST].zoomIncrement2 = bar[BAR_DAILYQUEST].zoomIncrement = 0.0f;
	bar[BAR_DAILYQUEST].zoomEnd2 = bar[BAR_DAILYQUEST].zoomEnd = bar[BAR_DAILYQUEST].zoom;
	bar[BAR_DAILYQUEST].frame = 1;

	bar[BAR_CREWUPGRADE].targetX2 = bar[BAR_CREWUPGRADE].targetX = bar[BAR_CREWUPGRADE].nx;
	bar[BAR_CREWUPGRADE].targetY2 = bar[BAR_CREWUPGRADE].targetY = bar[BAR_CREWUPGRADE].ny;
	bar[BAR_CREWUPGRADE].speed2 = bar[BAR_CREWUPGRADE].speed = 8 * _2X;
	bar[BAR_CREWUPGRADE].speedIncrement2 = bar[BAR_CREWUPGRADE].speedIncrement = 1 * _2X;
	bar[BAR_CREWUPGRADE].zoom2 = bar[BAR_CREWUPGRADE].zoom = BAR_CREWUPGRADE_ZOOM;
	bar[BAR_CREWUPGRADE].zoomIncrement2 = bar[BAR_CREWUPGRADE].zoomIncrement = 0.0f;
	bar[BAR_CREWUPGRADE].zoomEnd2 = bar[BAR_CREWUPGRADE].zoomEnd = bar[BAR_CREWUPGRADE].zoom;
	bar[BAR_CREWUPGRADE].frame = 1;

	bar[BAR_EQUIP].targetX2 = bar[BAR_EQUIP].targetX = bar[BAR_EQUIP].nx;
	bar[BAR_EQUIP].targetY2 = bar[BAR_EQUIP].targetY = bar[BAR_EQUIP].ny;
	bar[BAR_EQUIP].speed2 = bar[BAR_EQUIP].speed = 8 * _2X;
	bar[BAR_EQUIP].speedIncrement2 = bar[BAR_EQUIP].speedIncrement = 1 * _2X;
	bar[BAR_EQUIP].zoom2 = bar[BAR_EQUIP].zoom = BAR_COLLECTIONS_ZOOM;
	bar[BAR_EQUIP].zoomIncrement2 = bar[BAR_EQUIP].zoomIncrement = 0.0f;
	bar[BAR_EQUIP].zoomEnd2 = bar[BAR_EQUIP].zoomEnd = bar[BAR_EQUIP].zoom;
	bar[BAR_EQUIP].frame = 1;

	bar[BAR_FRIENDS].targetX2 = bar[BAR_FRIENDS].targetX = bar[BAR_FRIENDS].nx;
	bar[BAR_FRIENDS].targetY2 = bar[BAR_FRIENDS].targetY = bar[BAR_FRIENDS].ny;
	bar[BAR_FRIENDS].speed2 = bar[BAR_FRIENDS].speed = 8 * _2X;
	bar[BAR_FRIENDS].speedIncrement2 = bar[BAR_FRIENDS].speedIncrement = 1 * _2X;
	bar[BAR_FRIENDS].zoom2 = bar[BAR_FRIENDS].zoom = BAR_FRIENDS_ZOOM;
	bar[BAR_FRIENDS].zoomIncrement2 = bar[BAR_FRIENDS].zoomIncrement = 0.0f;
	bar[BAR_FRIENDS].zoomEnd2 = bar[BAR_FRIENDS].zoomEnd = bar[BAR_FRIENDS].zoom;
	bar[BAR_FRIENDS].frame = 1;

	bar[BAR_QUEST].targetX2 = bar[BAR_QUEST].targetX = bar[BAR_QUEST].nx;
	bar[BAR_QUEST].targetY2 = bar[BAR_QUEST].targetY = bar[BAR_QUEST].ny;
	bar[BAR_QUEST].speed2 = bar[BAR_QUEST].speed = 8 * _2X;
	bar[BAR_QUEST].speedIncrement2 = bar[BAR_QUEST].speedIncrement = 1 * _2X;
	bar[BAR_QUEST].zoom2 = bar[BAR_QUEST].zoom = BAR_QUEST_ZOOM;
	bar[BAR_QUEST].zoomIncrement2 = bar[BAR_QUEST].zoomIncrement = 0.0f;
	bar[BAR_QUEST].zoomEnd2 = bar[BAR_QUEST].zoomEnd = bar[BAR_QUEST].zoom;
	bar[BAR_QUEST].frame = 1;

	for (i = PLAYER; i < TOTALCHAR; i++) {
		bar[BAR_INVENTORY + i].targetX2 = bar[BAR_INVENTORY + i].targetX = bar[BAR_INVENTORY + i].nx;
		bar[BAR_INVENTORY + i].targetY2 = bar[BAR_INVENTORY + i].targetY = bar[BAR_INVENTORY + i].ny;
		bar[BAR_INVENTORY + i].speed2 = bar[BAR_INVENTORY + i].speed = 8 * _2X;
		bar[BAR_INVENTORY + i].speedIncrement2 = bar[BAR_INVENTORY + i].speedIncrement = 1 * _2X;
		bar[BAR_INVENTORY + i].zoom2 = bar[BAR_INVENTORY + i].zoom = BAR_INVENTORY_ZOOM;
		bar[BAR_INVENTORY + i].zoomIncrement2 = bar[BAR_INVENTORY + i].zoomIncrement = 0.0f;
		bar[BAR_INVENTORY + i].zoomEnd2 = bar[BAR_INVENTORY + i].zoomEnd = bar[BAR_INVENTORY + i].zoom;
		bar[BAR_INVENTORY + i].frame = 1;

		bar[BAR_SKILL + i].targetX2 = bar[BAR_SKILL + i].targetX = bar[BAR_SKILL + i].nx;
		bar[BAR_SKILL + i].targetY2 = bar[BAR_SKILL + i].targetY = bar[BAR_SKILL + i].ny;
		bar[BAR_SKILL + i].speed2 = bar[BAR_SKILL + i].speed = 8 * _2X;
		bar[BAR_SKILL + i].speedIncrement2 = bar[BAR_SKILL + i].speedIncrement = 1 * _2X;
		bar[BAR_SKILL + i].zoom2 = bar[BAR_SKILL + i].zoom = BAR_SKILL_ZOOM;
		bar[BAR_SKILL + i].zoomIncrement2 = bar[BAR_SKILL + i].zoomIncrement = 0.0f;
		bar[BAR_SKILL + i].zoomEnd2 = bar[BAR_SKILL + i].zoomEnd = bar[BAR_SKILL + i].zoom;
		bar[BAR_SKILL + i].frame = 1;
	}

	//���⼭���� �̺�Ʈ�޴� �ٽ� �鿩������
	for (i = 0; i < robin.eventCnt; i++) {
		robin.gameEvent[i].targetX2 = robin.gameEvent[i].targetX = robin.gameEvent[i].nx;
		robin.gameEvent[i].targetY2 = robin.gameEvent[i].targetY = robin.gameEvent[i].ny;
		robin.gameEvent[i].speed2 = robin.gameEvent[i].speed = 8 * _2X;
		robin.gameEvent[i].speedIncrement2 = robin.gameEvent[i].speedIncrement = 1 * _2X;
		robin.gameEvent[i].zoom2 = robin.gameEvent[i].zoom;
		robin.gameEvent[i].zoomIncrement2 = robin.gameEvent[i].zoomIncrement = 0.0f;
		robin.gameEvent[i].zoomEnd2 = robin.gameEvent[i].zoomEnd = robin.gameEvent[i].zoom;
		robin.gameEvent[i].frame = 1;
	}

	waveStatus = WAVESTATUS_READY;
	attackSequence = ATTACKSEQUENCE_READY;
	arenaStatus = STATUS_PLAY;
	keyHandle = MK_PLAY;

	ao[NEUTRAL].status = BOXSTATUS_CLOSED;

	//ao[ITEMBOX].dy = -8 * _2X;

}

void ArrangeEventMenu(void)
{
	int i, j = 0, k = 0;
	int curArr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int indexArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	//int nextArr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//���ǰ� �������(���ڰ� ���� �������) �ٽ� ��迭�ϴ�
	for (i = 0; i < MAXGAMEEVENT; i++) {
		//Ȱ��ȭ �Ǿ� ������
		if (robin.gameEvent[i].type > EVENTTYPE_NONE) {
			curArr[j] = robin.gameEvent[i].type;
			j++;
		}
	}

	sortArray(curArr, indexArr, MAXGAMEEVENT);

	memset(&gameEventArr, 0, sizeof(gameEventArr));

	for (i = 0; i < MAXGAMEEVENT; i++) {
		memcpy(&gameEventArr[i], &robin.gameEvent[indexArr[i]], sizeof(GAMEEVENT));
	}

	for (i = 0; i < MAXGAMEEVENT; i++) {
		memcpy(&robin.gameEvent[i], &gameEventArr[i], sizeof(GAMEEVENT));
	}
}

void EventMenuDraw(GAMEEVENT* gEvent)
{
	long long start, end, current;
	long remainTime = Max(0, gEvent->limitTime - (MC_knlCurrentTimeStamp() - gEvent->timeStamp));

	switch (gEvent->type) {
	case EVENTTYPE_PVP:
		switch (gEvent->barStatus) {
		default:
			PvpEventBarDraw(gEvent, xOffset + gEvent->x + (float)(-PVPQUESTBARWIDTH - 32 * _2X * 1) * gEvent->zoom, gEvent->y + (float)(PVPQUESTBARHEIGHT / 2) * gEvent->zoom, pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0], robin.pvpQuestCnt, pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + TOTALPVPDETAILREQUEST - 1], false, true, gEvent->zoom);
			break;
		case EVENT_BAR_GUAGE_FILL:
			PvpEventBarDraw(gEvent, xOffset + gEvent->x + (float)(-PVPQUESTBARWIDTH - 32 * _2X * 1) * gEvent->zoom, gEvent->y + (float)(PVPQUESTBARHEIGHT / 2) * gEvent->zoom, pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0], rouletteNum, pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + TOTALPVPDETAILREQUEST - 1], false, true, gEvent->zoom);
			break;
		}
		break;
	}

	switch (gEvent->type) {
	default:
		if (gEvent->type == EVENTTYPE_DOUBLE) {
			//SetAlpha(28);
		}
		switch (gEvent->subType) {
			//case QUESTTYPE_ITEM:
			//case QUESTTYPE_ITEM_BATTLE:
			//case QUESTTYPE_ITEM_RAID:
			//case QUESTTYPE_BATTLE:
		default:
			DrawIcon(gEvent->icon + (gEvent->icon == ICON_GOLD ? frame % GOLDICONFRAME : 0), xOffset + gEvent->x + (float)(-8 * _2X * 2 - 1 * _2X) * gEvent->zoom, gEvent->y + (float)(ITEMICONSIZE + 2 * _2X) * gEvent->zoom * 2.0f / 2, gEvent->zoom * 2.0f, ICON_OUTLINE_COLOR, false, false, true);
			break;
			//case QUESTTYPE_RAID:
			//	DrawNeutral(OBJ_BOX0 + boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], gEvent->x, gEvent->y - (float)12 * _2X * gEvent->zoom, LEFT, 1.2f * gEvent->zoom, cvtDest, cvtLayer, buffering);
			//	break;

		}
		if (gEvent->type == EVENTTYPE_DOUBLE) {
			//SetAlpha(32);
			DrawGoldAlpha(xOffset + gEvent->x - (float)16 * _2X * gEvent->zoom, gEvent->y - (float)4 * _2X * gEvent->zoom, ALPHA_X, FONT_GOLD_LARGE, gEvent->zoom / 2, LEFT, true, false);
			DrawGoldNum(2, xOffset + gEvent->x - (float)4 * _2X * gEvent->zoom, gEvent->y + (float)4 * _2X * gEvent->zoom, LEFT, false, false, false, Min(0.1f * (frame % FPS), 1.0f) * gEvent->zoom);
		}
		break;
	case EVENTTYPE_DEBUG_NEWGAME:
	case EVENTTYPE_DEBUG_MAXGAME:
		DrawIcon(gEvent->icon, xOffset + gEvent->x + (float)(-ITEMICONSIZE - 1 * _2X) * gEvent->zoom * 2.0f / 2, gEvent->y + (float)(ITEMICONSIZE + 1 * _2X) * gEvent->zoom * 2.0f / 2, gEvent->zoom * 2.0f, ICON_OUTLINE_COLOR, false, false, true);
		break;
	case EVENTTYPE_DEBTDISCOUNT:
		ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, xOffset + gEvent->x - (float)20 * _2X * gEvent->zoom, gEvent->y - (float)8 * _2X * gEvent->zoom, SHADOW_IMG, gEvent->zoom);
		DrawNeutral(EFFECT_CRAFT0 + (frame / 2 / MOTIONDIV) % 3, xOffset + gEvent->x, gEvent->y - (float)12 * _2X * gEvent->zoom, LEFT, gEvent->zoom);
		break;
	case EVENTTYPE_BOSSRAID:
		DrawCmfDetailShadow(enemyData[goldQuestNpc[gEvent->barStatus * BOSSRAIDSIZE + BOSSRAIDSIZE - 1] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[goldQuestNpc[gEvent->barStatus * BOSSRAIDSIZE + BOSSRAIDSIZE - 1] * 5 + 0], xOffset + gEvent->x, gEvent->y - (float)16 * _2X * gEvent->zoom, LEFT, gEvent->zoom * (float)goldQuestZoomData[gEvent->barStatus * 2 + 1]);
		break;
	}

	switch (gEvent->type) {
	case EVENTTYPE_SHOP:
		//�������� ȹ���� �� �ִ� Ÿ�̹��� �Ǹ�
		if (remainTime > 3600)
			DrawTime(xOffset + gEvent->x, gEvent->y - (float)32 * _2X * gEvent->zoom / 2, remainTime, TIME_HOUR_MINUTE, CENTER, gEvent->zoom * 0.8f);
		else {
			DrawRedDot(gEvent->x + (float)(32 * _2X / 2 * gEvent->zoom - 9 * _2X * gEvent->zoom * 1.5f), gEvent->y + (float)(36 * _2X / 2) * gEvent->zoom, COLOR_WHITE, false, gEvent->zoom * 1.5f);
		}
		break;
	default:
		DrawTime(xOffset + gEvent->x, gEvent->y - (float)32 * _2X * gEvent->zoom / 2, remainTime, remainTime > 3600 ? TIME_HOUR_MINUTE : TIME_MINUTE_SECONDS, CENTER, gEvent->zoom * 0.8f);
		break;
	case EVENTTYPE_DEBUG_NEWGAME:
	case EVENTTYPE_DEBUG_MAXGAME:
		CenterAlpha(xOffset + gEvent->x, gEvent->y - (float)36 * _2X * gEvent->zoom / 2, gEvent->type == EVENTTYPE_DEBUG_NEWGAME ? ALPHA_NEWGAME : ALPHA_MAXGAME, FONT_SMALL, false, gEvent->zoom);
		break;
	case EVENTTYPE_DEBUG_ENEMYATTACK:
		DrawAlpha(xOffset + gEvent->x - (float)(20 * _2X) * gEvent->zoom, gEvent->y - (float)(36 * _2X) * gEvent->zoom / 2, ALPHA_ATK, FONT_SMALL, gEvent->zoom, false);
		DrawAlpha(xOffset + gEvent->x + (float)(-20 * _2X + 24 * _2X) * gEvent->zoom, gEvent->y - (float)(36 * _2X) * gEvent->zoom / 2, ONLYATTACKMODE == true ? ALPHA_N : ALPHA_Y, FONT_SMALL, gEvent->zoom, false);
		break;
	}

	if (menuPressPossible())
		SetRectPoint(xOffset + gEvent->x + (float)(-ITEMICONSIZE - 4 * _2X) * gEvent->zoom, gEvent->y + (float)(ITEMICONSIZE + 4 * _2X) * gEvent->zoom, (float)(38 * _2X) * gEvent->zoom, (float)(38 * _2X) * gEvent->zoom, gEvent->touchFunc);
}

void GoldQuestMenuDraw(int x, int y, float zoom)
{
	int i, j;
	int rewardType, rewardDetail, rewardGrade;
	long long rewardCnt;
	OBJECT* pObj = &ao[PLAYER];
	gEvent = &robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)];
	int enemyType;
	int enemyCmf;
	float gapX = (float)8 * _2X * zoom;
	float gapY = -(float)5 * _2X * zoom;

	float degree = 90.0f - atan((float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + 1 * 2 + 1] - goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + 0 * 2 + 1]) / (float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + 1 * 2 + 0] - goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + 0 * 2 + 0])) * 180 / M_PI;
	float radian = degree * M_PI / 180;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	//DrawWindow5(x + (float)(16 * _2X) * zoom, y - (float)(124 * _2X) * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(POPUPWINDOWSIZE_Y - 152 * _2X) * zoom, CASTLE3, zoom, cvtDest, cvtLayer, buffering);

	CenterText(TEXT_BOSSRAID, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y - (float)(4 * _2X) * zoom, zoom);

	for (i = BOSSRAIDSIZE - 1; i >= 0; i--) {
		if (i != BOSSRAIDSIZE - 1) {
			for (j = 0; j < 3; j++) {
				DrawImage(17 * _2X, 24 * _2X, 0 * _2X, 112 * _2X, x + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 0] * zoom, y + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 1] * zoom, false, false, false, false, false, zoom / 2, sprite[MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE], MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE);
				DrawImage(17 * _2X, 24 * _2X, 0 * _2X, 112 * _2X, x + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 0] * zoom + (float)17 * _2X * zoom / 2, y + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 1] * zoom, true, false, false, false, false, zoom / 2, sprite[MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE], MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE);

				//Ŭ�����ϸ� ���긦 ���ش�.
				if ((int)(gEvent->barStatus) > i) {
					SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
					DrawImage(10 * _2X, 20 * _2X, 28 * _2X, 136 * _2X, x + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 0] * zoom - (float)10 * _2X * zoom / 2 + gapX, y + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 1] * zoom + (float)10 * _2X * zoom / 2 + gapY, false, false, false, false, false, zoom / 2, sprite[MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE], MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE);
					DrawImage(10 * _2X, 20 * _2X, 28 * _2X, 136 * _2X, x + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 0] * zoom + gapX, y + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 1] * zoom + (float)10 * _2X * zoom / 2 + gapY, true, false, false, false, false, zoom / 2, sprite[MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE], MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE);
					SetAlpha(32);

					DrawImage(8 * _2X, 16 * _2X, 106 * _2X, 0 + 16 * _2X * (IMG_BG_REDORB + i % 5 - IMG_BG_REDORB), x + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 0] * zoom - (float)8 * _2X * zoom / 2 + gapX, y + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 1] * zoom + (float)8 * _2X * zoom / 2 + gapY, false, false, false, false, false, zoom / 2, sprite[MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE], MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE);
					DrawImage(8 * _2X, 16 * _2X, 106 * _2X, 0 + 16 * _2X * (IMG_BG_REDORB + i % 5 - IMG_BG_REDORB), x + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 0] * zoom + gapX, y + (float)goldQuestDotPosition[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 3 * 2 + i * 3 * 2 + j * 2 + 1] * zoom + (float)8 * _2X * zoom / 2 + gapY, true, false, false, false, false, zoom / 2, sprite[MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE], MAP_OBJ_IMG + MAPTYPE_DEVILCASTLE);

				}
				//goldQuestDotPosition
			}
		}
	}

	for (i = BOSSRAIDSIZE - 1; i >= 0; i--) {

		switch (i) {
		default:
			DrawBox(goldQuestBox[(int)(gEvent->barStatus) * BOSSRAIDSIZE + (int)(i)], x + (float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + i * 2 + 0]) * zoom - (float)16 * _2X * zoom - (float)(BOXSIZE_X) * 2 / 3 * zoom / 2 * 2 / 3 + (i / 2 % 2 == 0 ? -(float)18 * _2X * zoom : (float)20 * _2X * zoom), y + (float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + i * 2 + 1]) * zoom + (float)10 * _2X * zoom + (float)10 * _2X * zoom, LEFT, false, false, true, i >= i ? false : true, true, zoom * 2 / 3 * 2 / 3);

			DrawCmfDetailShadow(enemyData[goldQuestNpc[(int)(gEvent->barStatus) * BOSSRAIDSIZE + i] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[goldQuestNpc[(int)(gEvent->barStatus) * BOSSRAIDSIZE + i] * 5 + 0], x + (float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + i * 2 + 0]) * zoom - (float)16 * _2X * zoom, y + (float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + i * 2 + 1]) * zoom - (float)(24 * _2X) * zoom, i / 2 % 2 == 0 ? RIGHT : LEFT, LOBBYZOOM * zoom);

			break;
		}

		SetRectPoint(x + (float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + i * 2 + 0]) * zoom - (float)(BOXSIZE_X)*zoom + (float)8 * _2X * zoom, y + (float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + i * 2 + 1]) * zoom + (float)24 * _2X * zoom, (float)BOXSIZE_X * zoom, (float)BOXSIZE_Y * zoom, TOUCH_FUNC_EVENT_BOSSRAID_REWARDINFO + i);
	}
	
	DrawText(TEXT_REMAINTIME, x + (float)64 * _2X * zoom, y - (float)452 * _2X * zoom, zoom);

	DrawTime(x + (float)(128 * _2X) * zoom, y - (float)(450 * _2X) * zoom, Max(gEvent->limitTime - (MC_knlCurrentTimeStamp() - gEvent->timeStamp), 0), TIME_HOUR_MINUTE, LEFT, zoom);

	DrawTextButton(x + (POPUPWINDOWSIZE_X / 2 - 80 * _2X / 2) * zoom, y - (POPUPWINDOWSIZE_Y - 4 * ITEMICONSIZE) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, FRAME_GREEN, false, zoom, false, TEXT_ADVENTURE);

	switch (menuDepth) {
	case 0:
		SetRectPoint(x + (POPUPWINDOWSIZE_X / 2 - 80 * _2X / 2) * zoom, y - (POPUPWINDOWSIZE_Y - 4 * ITEMICONSIZE) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, TOUCH_FUNC_GOTOBOSSRAID);
		break;
	case 1:
		ResetRectPoint();
		if (curtainFrame == 0) {
			GotoBoss();
		}
		break;
	}
}

void GameOverDraw(int x, int y, float zoom)
{
	int i;
	float fontZoom = 1.5f;

	//SetAlpha(20);
	//MemRect(0, DY, DX, DY, COLOR_BLACK, cvtDest, cvtLayer, buffering);
	//SetAlpha(32);

	DrawGoldAlpha(DX / 2, DY - GNBHEIGHT - 16 * _2X, ALPHA_STAGEFAILED, FONT_GOLD_LARGE, fontZoom * zoom, CENTER, true, false);

	//SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
	//DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, zoom, CENTER, false, false, cvtDest, cvtLayer, buffering);
	//SetAlpha(32);

	//SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_STAGEFAILED);
	gameOverFrame++;

	if (gameOverFrame == FPS) {
		for (i = ENEMY; i < NEUTRAL; i++)
			memset(&ao[i], 0, sizeof(OBJECT));
		for (i = ROBIN; i < TOTALCHAR; i++)
			ResurrectionEffect(&ao[i]);

		MainMenuIn();

		memset(&popUp[popUpCnt - 1], 0, sizeof(POPUP));
		popUpCnt--;
		PlayMusic(M_CLOSEWINDOW);
	}
}

void ClosePopUp(void)
{
	//it = &ao[PLAYER].equip[EQUIP_WEAPON];
			//collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);
			//���� �˾��� �������ε� PVP����Ʈ�� �Ϲ�����Ʈ�� ������ ���̽�ƽ ����Ʈ�� ����� �ش�. 
	
	if (menuDepth > 0) {
		menuDepth--;
	}
	else {

		switch (popUp[popUpCnt - 1].type) {
		case MENU_PLAY:
		case MENU_COLLECTIONS:
		case MENU_SHOP:
		case MENU_STARSHOP:
		case MENU_NEWS:
		case MENU_GIFTS:
		case MENU_LEADERBOARD:
		case MENU_INVITEFREINDS:
		case MENU_CALENDAR:
			curMenu = MENU_PLAY;
			break;
		}

		if ((popUp[popUpCnt - 1].type == POPUPTYPE_QUESTINFO || popUp[popUpCnt - 1].type == POPUPTYPE_PVPQUESTINFO)) {
			if (popUp[popUpCnt - 1].type == POPUPTYPE_QUESTINFO) {
			}
			else if (popUp[popUpCnt - 1].type == POPUPTYPE_PVPQUESTINFO) {
			}
		}
		memset(&popUp[popUpCnt - 1], 0, sizeof(POPUP));
		popUpCnt--;

	}

	PlayMusic(M_CLOSEWINDOW);

}

void SetPopUp(int type, int x, int y, int w, int h,
	int itemType, int itemDetail, int itemGrade,
	int rewardType1, int rewardDetail1, int rewardGrade1, long long rewardStartCnt1, long long rewardEndCnt1,
	int rewardType2, int rewardDetail2, int rewardGrade2, long long rewardStartCnt2, long long rewardEndCnt2,
	int rewardType3, int rewardDetail3, int rewardGrade3, long long rewardStartCnt3, long long rewardEndCnt3)
{
	//return;

	popUp[popUpCnt].active = true;

	popUp[popUpCnt].type = type;
	popUp[popUpCnt].x = x;
	popUp[popUpCnt].y = y;
	popUp[popUpCnt].w = w;
	popUp[popUpCnt].h = h;

	popUp[popUpCnt].itemType = itemType;
	popUp[popUpCnt].itemDetail = itemDetail;
	popUp[popUpCnt].itemGrade = itemGrade;

	popUp[popUpCnt].rewardType[0] = rewardType1;
	popUp[popUpCnt].rewardDetail[0] = rewardDetail1;
	popUp[popUpCnt].rewardGrade[0] = rewardGrade1;
	popUp[popUpCnt].rewardStartCnt[0] = rewardStartCnt1;
	popUp[popUpCnt].rewardEndCnt[0] = rewardEndCnt1;

	popUp[popUpCnt].rewardType[1] = rewardType2;
	popUp[popUpCnt].rewardDetail[1] = rewardDetail2;
	popUp[popUpCnt].rewardGrade[1] = rewardGrade2;
	popUp[popUpCnt].rewardStartCnt[1] = rewardStartCnt2;
	popUp[popUpCnt].rewardEndCnt[1] = rewardEndCnt2;

	popUp[popUpCnt].rewardType[2] = rewardType3;
	popUp[popUpCnt].rewardDetail[2] = rewardDetail3;
	popUp[popUpCnt].rewardGrade[2] = rewardGrade3;
	popUp[popUpCnt].rewardStartCnt[2] = rewardStartCnt3;
	popUp[popUpCnt].rewardEndCnt[2] = rewardEndCnt3;

	popUp[popUpCnt].frame = 0;
	popUp[popUpCnt].popUpFrame = 1;
	popUpCnt++;

	//��� �ʱ�ȭ
	if (type == POPUPTYPE_STAGE)
		memset(&stageUpgradeMotion, 0, sizeof(stageUpgradeMotion));

	PlayMusic(M_OPENWINDOW);

	//SetPopUp()은 입력 처리에서 불리므로 화면버퍼가 열리기 전이다.
	//여기서 그리면 AfterSpriting()이 curScene에 스프라이트를 영구히 붙여
	//매 프레임 화면버퍼를 덮어버린다. 암전은 PaintClet()이 popUpCnt > 0 동안
	//매 프레임 처리하므로 여기서는 부르지 않는다.
	//ScreenDarken(SCREENDARKEN);

}

void DrawPopUp(int idx)
{
	int i, j = 0;
	POPUP* p = &popUp[idx];
	int menuCurBack;
	int menuDepthBack;
	int curStar;
	int maxStar;
	float plusY = (float)64 * _2X * p->zoom;
	
	if (p->popUpFrame == 0)
		p->zoom = 1.0f;
	else if (p->popUpFrame > 0)
		p->zoom = popUpFrameData[p->popUpFrame];

	if (p->popUpFrame > 0)
		p->popUpFrame++;

	if (p->popUpFrame == 8)
		p->popUpFrame = 0;

	switch (p->type) {
	case POPUPTYPE_BOXINFO:
		BoxInfoDraw(p->itemDetail, xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);

		break;
	case POPUPTYPE_BOXREWARD:
		//�������� Ŀ����
		DrawFrame(p->x - (float)p->w * p->zoom / 2, p->y + plusY + (float)p->h * p->zoom / 2, (float)p->w * p->zoom, (float)p->h * p->zoom, FRAME_SHOPBALLOON);

		if (p->frame > POPUPFRAME)
			DrawBox(p->itemDetail, p->x - (float)p->w * p->zoom / 2 + (float)BOXSIZE_X / 4 * p->zoom, p->y + plusY + (float)BOXSIZE_Y / 3 * p->zoom, LEFT, Min(1, (float)(((float)p->frame - POPUPFRAME) / POPUPFRAME)), true, false, false, true, p->zoom * 2);

		for (i = 0; i < BOX1MAXREWARDITEM; i++) {
			if (p->rewardStartCnt[i] > 0) {
				if (p->frame > 2 * POPUPFRAME + j * POPUPFRAME) {
					DrawRewardCardRange(p->rewardType[i], p->rewardDetail[i], p->rewardGrade[i], p->rewardStartCnt[i], p->rewardEndCnt[i], p->x - (float)p->w * p->zoom / 2 + (float)(4 * _2X + (REWARDCARDSIZE_X + 2 * _2X) * j + (REWARDCARDSIZE_X / 2) - (REWARDCARDSIZE_X / 2) * Min(((float)(p->frame - (2 * POPUPFRAME + j * POPUPFRAME)) / POPUPFRAME), 1)) * p->zoom, p->y + plusY + (float)p->h * p->zoom / 2 - (float)28 * _2X * p->zoom - (float)REWARDCARDSIZE_Y / 2 * p->zoom + (float)(REWARDCARDSIZE_Y / 2) * Min(((float)(p->frame - (2 * POPUPFRAME + j * POPUPFRAME)) / POPUPFRAME), 1), Min(((float)(p->frame - (2 * POPUPFRAME + j * POPUPFRAME)) / POPUPFRAME), 1) * p->zoom, true);
				}
				j++;
			}
		}

		memset(&tempStr, 0, sizeof(tempStr));
		sprintf(tempStr, "%s %d %s", textId[TEXT_STAGE], robin.stage + 1, textId[TEXT_REWARD]);

		DrawLabelStr(p->x - (float)24 * _2X * p->zoom, p->y + plusY + (float)60 * _2X * p->zoom, tempStr, p->zoom);

		break;
	case POPUPTYPE_QUESTINFO:
		QuestMenuDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);

		break;
	case POPUPTYPE_PVPQUESTINFO:
		PvpQuestMenuDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);

		break;
	case POPUPTYPE_SHOPINFO:
		ShopDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, DY - GNBHEIGHT, p->zoom);
		break;
	case POPUPTYPE_CASTLEMENU:
		CastleMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, DY - GNBHEIGHT, p->zoom);
		break;
	case POPUPTYPE_DAILYQUEST:
		DailyQuestDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_EVENTSHOP:
		ShopDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, DY - GNBHEIGHT, p->zoom);
		break;
	case POPUPTYPE_NEWS:
		NewsDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_CALENDAR:
		CalendarDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)(POPUPWINDOWSIZE_Y / 2) * p->zoom, p->zoom);
		break;
	case POPUPTYPE_STAGE:
		//SetAlpha(20);
		//MemRect(0, DY, DX, DY, COLOR_BLACK, cvtDest, cvtLayer, buffering);
		//SetAlpha(32);
		StageInfoDraw(robin.stage, robin.room, GetCombatPower(&ao[ENEMY]), true, DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_BOSSRAID:
		GoldQuestMenuDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_JOKBO:
		JokboDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_DEPTDISCOUNT:
		DeptDiscountDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_DOUBLE:
		DoubleGoldDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_ITEMCOMPARE:
		ItemDetailDraw(&ao[robin.newItem.type % 3].equip[itemEquipSlot[robin.newItem.type]], xOffset + DX / 2 - (int)(float)(ITEMDETAILWINDOWSIZE_X / 2) * p->zoom, p->y + ITEMDETAILWINDOWSIZE_Y / 2 + 0 * _2X + (float)(ITEMDETAILWINDOWSIZE_Y / 2) * p->zoom, p->zoom, true, false);
		ItemDetailDraw(&robin.newItem, xOffset + DX / 2 - (int)(float)(ITEMDETAILWINDOWSIZE_X / 2) * p->zoom, p->y - ITEMDETAILWINDOWSIZE_Y / 2 + 40 * _2X - 64 * _2X + (float)(ITEMDETAILWINDOWSIZE_Y / 2) * p->zoom, p->zoom, false, false);
		break;
	case POPUPTYPE_ITEMDETAIL:
		ItemDetailDraw(&ao[PLAYER].equip[itemEquipSlot[p->itemType]], xOffset + DX / 2 - (int)(float)(ITEMDETAILWINDOWSIZE_X / 2) * p->zoom, p->y, p->zoom, false, true);
		break;
	case POPUPTYPE_LEVELUP:
		LevelUpMenuDraw(robin.lv, false, xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_HEROSTAT:
		//CollectionsDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom, cvtDest, cvtLayer, buffering);
		HeroStatDraw(&ao[curHero], xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_CREWUPGRADE:
		CrewMenuDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_CREWLIST:
		//CrewListDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + scY[curMenu], p->zoom, cvtDest, cvtLayer, buffering);
		CrewMenuDraw(
			xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom,
			DY - GNBHEIGHT,
			p->zoom);
		break;
	case POPUPTYPE_COLLECTIONS:
		CollectionsDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, DY - GNBHEIGHT, p->zoom);
		break;
	case POPUPTYPE_FRIENDS:

		break;
	case POPUPTYPE_OPTION:
		OptionDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_ENEMYUSER:
		//DrawDioramaCrew(&enemyHouse, DX / 2 - (float)(POPUPWINDOWSIZE_X / 2 + 15 * _2X) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom - (float)80 * _2X * p->zoom, p->zoom, stageInfoFrame, false, false, false, cvtDest, cvtLayer, buffering);
		EnemyUserProfileDraw(&enemyHouse, DX / 2 - (float)(RAIDGOLDBARWIDTH / 2) * p->zoom * 1.5f, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom - (float)52 * _2X * p->zoom + (float)RAIDGOLDBARHEIGHT / 2 * p->zoom * 1.5f, p->zoom * 1.5f);
		break;
	case POPUPTYPE_GAMEOVER:
		GameOverDraw(0, DY, 1.0f);
		break;
	case POPUPTYPE_HOWTOGETHEROES:
		//���⿡ ����θ� ��� ����� �׷��ش�.
		HowToGetHeroesDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_HOWTOGETCREWS:
		//���⿡ �������븦 ��� ����� �׷��ش�.
		HowToGetCrewsDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	}
	//���ư

	if (p->zoom == 1.0f && (p->type != POPUPTYPE_ITEMCOMPARE && p->type != POPUPTYPE_STAGE && p->type != POPUPTYPE_GAMEOVER)) {
		float xMarkZoom = 1.0f;
		DrawXMark((float)(18) * p->zoom, DY - GNBHEIGHT - (float)(22) * p->zoom, xMarkZoom* p->zoom);

		SetRectPoint((float)(18)* p->zoom, DY - GNBHEIGHT - (float)(22) * p->zoom, (float)64 * xMarkZoom * p->zoom, (float)64 * xMarkZoom * p->zoom, TOUCH_FUNC_POPUP_CLOSE);
	}

	p->frame++;
}

void GameMenuDraw(int x, int y, float zoom)
{
	int i, j, motion;
	//int dy = 29 * _2X;
	int dy =  (DY - 16 * _2X - (GNBHEIGHT - GNB_INIT_HEIGHT)) / TOTAL_OPENEDMENU;
	int w = GAMEMENUWIN_X;
	ITEM* it;
	int tempX, tempY;

	if (dy > MAINMENU_Y)
		dy = MAINMENU_Y;

	x = xOffset + DX;
	y = DY;

	DrawFrame(x, y, w, DY, FRAME_SHOPBALLOON);

	y = DY - 28 * _2X - (GNBHEIGHT - GNB_INIT_HEIGHT);

	j = 0;

	for (i = 0; i < MENU_JOKBO; i++) {
		if (robin.openedMenu[i] == OPENED) {
			DrawText(TEXT_MENU_PLAY + i, x + 58 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 - 8 * _2X, 2.0f);

			//ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + 8 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 - 20 * _2X, SHADOW_IMG, 1.0f, cvtDest, cvtLayer, buffering);


			//���������
			//if (robin.openedMenu[i] == CLOSE) {
			//	DrawIcon(ICON_EVENT_LOCK, x + 12 * _2X, y - dy * (j)-dy / 2 + 6 * _2X + ITEMICONSIZE, 2, false, false, false, cvtDest, cvtLayer, buffering);

			//}
			//else
			switch (i) {
			case MENU_PLAY://ĳ���͸޴� : ĳ���͸� �������ϰ� ����(STAT_STR, STAT_VIT, STAT_AGI, STAT_INT)�� ��� �κ�
				//DrawNeutral(OBJ_LEVER0, x + 28 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 - 20 * _2X, LEFT, 2, gScreenBuffer, gScreenLayer, false);
				DrawNeutral(OBJ_BOX0 + boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], x + 28 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 - 32 * _2X, LEFT, 2.0f * zoom);
				break;

			default:
				DrawIcon(listMenuIcon[i], x + 12 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2, 2, false, false, false, true);
				break;
			case MENU_FRIENDS:
				DrawImage(40 * _2X, 40 * _2X, 40 * _2X, 0 * _2X, x + 10 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 + 2 * _2X, false, false, false, false, 32, 1, sprite[MENUICON_IMG], MENUICON_IMG);
				break;
			case MENU_HERO:
				DrawBarIcon(BAR_CASTLE, x, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 - 8 * _2X + (float)(MAINMENU_Y / 2) * zoom, 0.8f * zoom);
				break;
			case MENU_CREW:
				DrawBarIcon(BAR_CREW, x, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 - 8 * _2X + (float)(MAINMENU_Y / 2) * zoom, 0.8f * zoom);
				break;
			case MENU_COLLECTIONS:
				DrawBarIcon(BAR_EQUIP, x, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 - 8 * _2X + (float)(MAINMENU_Y / 2) * zoom, 0.8f * zoom);
				break;
			case MENU_SHOP:
				DrawBarIcon(BAR_MAINSHOP, x, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 - 8 * _2X + (float)(MAINMENU_Y / 2) * zoom, 0.8f * zoom);
				break;
			case MENU_NEWS:
				DrawImage(40 * _2X, 40 * _2X, 40 * _2X * 5, 0 * _2X, x + 8 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 + 2 * _2X, false, false, false, false, 32, 1, sprite[MENUICON_IMG], MENUICON_IMG);
				break;
			case MENU_GIFTS:
				DrawImage(40 * _2X, 40 * _2X, 40 * _2X * 6, 0 * _2X, x + 8 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 + 2 * _2X, false, false, false, false, 32, 1, sprite[MENUICON_IMG], MENUICON_IMG);
				break;
			case MENU_CALENDAR:
				DrawImage(40 * _2X, 40 * _2X, 40 * _2X * 7, 0 * _2X, x + 8 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 + 2 * _2X, false, false, false, false, 32, 1, sprite[MENUICON_IMG], MENUICON_IMG);
				break;
			case MENU_SETTING:
				DrawImage(40 * _2X, 40 * _2X, 40 * _2X * 8, 0 * _2X, x + 8 * _2X, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 + ITEMICONSIZE / 2 + 2 * _2X, false, false, false, false, 32, 1, sprite[MENUICON_IMG], MENUICON_IMG);
				break;
			case MENU_GAMERESET:
				//�����̱� ������ �׳� �ؽ�Ʈ�� ����ش�.
				break;
			}

			grayScale = 0;

			if (i < TOTAL_MENU - 1)
				MemRect(x + 4 * _2X, y - dy * (j + 1) + 8 * _2X, w - 8 * _2X, 2 * _2X, 0xEEEEEE);

			if (robin.openedMenu[i] == OPENED)
				SetRectPoint(x, y - dy * j + 8 * _2X, w, dy, TOUCH_FUNC_PLAY + i);

			j++;
		}

	}
	//���� ����Ʈ�� ���� ���¸�
	if (curMenu == MENU_LIST && xOffset == -GAMEMENUWIN_X) {
		SetRectPoint(0, DY, x, DY, TOUCH_FUNC_GAMEMENU_OUT);
	}
}