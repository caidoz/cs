#include "Core.h"
#include "Data.h"
#include "Data/CmfData.h"
#include "Func.h"
#include "Text.h"
#include "Data/SwordSprites.h"
#include "Data/FoeGearData.h"
#include "CastleWheelManager.h"


//���
void DrawWindow3(int x, int y, int w, int h, int index, float zoom)
{
	int i;

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
	//SetAlpha(32);

	UnSectionClip(false);
}

// Draw�ڵ�
#if DUMP_CMF_PNG
//==========================================================================
// 캐릭터 그림 뽑기
//
// 한 프레임에 한 장씩 뽑는다. RenderTexture::saveToFile 이 그리기가 끝난
// 뒤에 저장하는 방식이라, 한 프레임에 여러 장을 걸면 앞의 것이 덮인다.
//
// 동료 먼저, 그 다음 몬스터. 다 끝나면 스스로 멈춘다.
//==========================================================================

static cocos2d::RenderTexture* gDumpRT = nullptr;
static int  gDumpIdx = 0;
static bool gDumpDone = false;

/* 그리기는 그 자리에서 일어나지 않는다.
 *
 * DrawImage 도 RenderTexture::begin 도 렌더 큐에 명령을 쌓아 둘 뿐이고,
 * 실제로 그려지는 것은 프레임 끝이다. 그래서 그린 직후에 newImage 로
 * 읽으면 아직 아무것도 안 그려진 판을 읽는다 - 앞 프레임 것이 나온다.
 *
 * 처음에는 saveToFile 을 썼는데 그것도 큐에 걸리는 것이라 마찬가지였다.
 * 492 장을 뽑아 서로 다른 그림이 355 장뿐이었고, 파일 번호가 통째로 한
 * 칸씩 밀려 있었다.
 *
 * 그래서 두 프레임에 나눈다. 이번 프레임에 그려 두고, 다음 프레임에
 * 읽는다. 그 사이에 프레임이 끝나므로 큐가 비워진다. */
static int  gDumpPending = -1;
static char gDumpPendingName[64] = { 0 };

//한 장 그린다. 읽는 것은 다음 프레임이다.
static bool DumpDrawCmf(int cmf, int motion)
{
	if (cmf < 0 || cmf >= MAXCMF)
		return false;

	//히어로(0~2)는 DrawCmfDetail 이 DrawPlayer 로 넘긴다. 그건 ao[] 를
	//읽는데, 뽑기 중에는 게임을 안 돌려 ao[] 가 비어 있다. 건너뛴다.
	if (cmf < TOTALCHAR)
		return false;

	//슬롯을 먼저 채운다. cmf_i_div / cmf_m_cnt / cmd_i_offset 은 모두
	//CmfRead 가 채워 주는 것이라, 이걸 빼면 게임이 마침 그 자리에
	//읽어 둔 남의 cmf 를 그린다. 색만 다른 변종들이 죄다 같은 그림으로
	//나온 까닭이 이것이었다.
	if (cmfLoaded[cmf] != cmf)
		CmfRead(cmf, cmf);

	if (motion < 0 || motion >= cmf_m_cnt[cmf])
		motion = 0;

	//가운데에 놓는다. center 를 켜면 그림의 한가운데가 이 자리에 온다.
	PushRenderTarget(gDumpRT, nullptr, true);
	DrawCmfDetail(cmf, motion,
		DUMP_CMF_SIZE / 2, DUMP_CMF_SIZE / 2,
		RIGHT, DUMP_CMF_ZOOM, 0, true);
	PopRenderTarget();

	return true;
}

//지난 프레임에 그려 둔 것을 읽어 파일로 낸다.
static void DumpSavePending(void)
{
	if (gDumpPending < 0)
		return;

	gDumpPending = -1;

	cocos2d::Image* img = gDumpRT->newImage(true);

	if (img) {
		const std::string full =
			cocos2d::FileUtils::getInstance()->getWritablePath() + gDumpPendingName;

		img->saveToFile(full, false);
		img->release();
	}
}

//한 프레임에 한 걸음. Core::Run 이 부른다.
void DumpCmfStep(void)
{
	if (gDumpDone)
		return;

	if (gDumpRT == nullptr) {
		gDumpRT = cocos2d::RenderTexture::create(DUMP_CMF_SIZE, DUMP_CMF_SIZE);

		if (gDumpRT == nullptr) {
			CCLOG("[DUMP] RenderTexture 를 못 만들었다");
			gDumpDone = true;
			return;
		}

		gDumpRT->retain();

		//폴더를 먼저 만든다. 저장은 fopen 만 하므로 폴더가 없으면 아무
		//말 없이 실패한다. 파일이 안 생기고 오류도 안 뜬다.
		cocos2d::FileUtils* fu = cocos2d::FileUtils::getInstance();
		const std::string dir = fu->getWritablePath() + "dump/";

		if (!fu->isDirectoryExist(dir))
			fu->createDirectory(dir);

		CCLOG("[DUMP] 시작. 저장 위치 : %s  (폴더 %s)",
			dir.c_str(), fu->isDirectoryExist(dir) ? "있음" : "못 만듦");

		//어느 파일을 읽고 있는지 확인한다. 깨진 그림이 나오면 여기가
		//기대와 다른지부터 본다.
		{
			const int probe[] = { 3, 4, 123, 124, 243, 249 };

			for (int k = 0; k < 6; k++) {
				const int c = probe[k];
				const int img = MONSTER_IMG + c;
				const std::string fn = GetResourceName(RES_IMG, img);
				cocos2d::Sprite* sp = sprite[img];

				CCLOG("[DUMP] cmf %d -> img %d, 파일 %s, 스프라이트 %s %dx%d",
					c, img, fn.c_str(), sp ? "있음" : "없음",
					sp ? (int)sp->getTexture()->getPixelsWide() : -1,
					sp ? (int)sp->getTexture()->getPixelsHigh() : -1);
			}
		}
	}

	//① 지난 프레임에 그려 둔 것을 먼저 읽는다.
	DumpSavePending();

	//② 이번 프레임에 다음 것을 그린다.
	const int total = gTotalCrew + (gTotalEnemy - ENEMY_SNAIL);

	if (gDumpIdx >= total) {
		CCLOG("[DUMP] 끝. 동료 %d, 몬스터 %d 장. "
			"BuildConfig.h 의 DUMP_CMF_PNG 를 0 으로 되돌려라.",
			gTotalCrew, gTotalEnemy - ENEMY_SNAIL);
		gDumpDone = true;
		return;
	}

	if (gDumpIdx < gTotalCrew) {
		const int i = gDumpIdx;
		const int type = crewData[i * CREWDATASIZE + CREWDATA_TYPE];
		const int cmf = enemyData[type * ENEMYDATASIZE + ENEMYDATA_CMF];

		//대기 모션의 첫 장. crewPos 의 0 번이 그 자리다.
		if (DumpDrawCmf(cmf, crewPos[type * 5 + 0])) {
			sprintf(gDumpPendingName, "dump/crew_%d.png", i);
			gDumpPending = i;
		}

		if ((i + 1) % 20 == 0)
			CCLOG("[DUMP] 동료 %d / %d", i + 1, gTotalCrew);
	}
	else {
		//몬스터 번호는 3 부터다. 0~2 는 히어로가 쓴다(content/README.md).
		const int e = (gDumpIdx - gTotalCrew) + ENEMY_SNAIL;
		const int cmf = enemyData[e * ENEMYDATASIZE + ENEMYDATA_CMF];

		if (DumpDrawCmf(cmf, crewPos[e * 5 + 0])) {
			sprintf(gDumpPendingName, "dump/enemy_%d.png", e);
			gDumpPending = e;
		}

		if ((e - ENEMY_SNAIL) % 50 == 0)
			CCLOG("[DUMP] 몬스터 %d / %d",
				e - ENEMY_SNAIL, gTotalEnemy - ENEMY_SNAIL);
	}

	gDumpIdx++;
}
#endif


void VersionDraw(void)
{
	//타이틀에서 문의/세이브 확인에 필요한 버전, 계정, 데이터 리비전을
	//한 번에 확인한다. 화면 최상단 안전 여백 바로 아래에 고정한다.
	if (drawHandle != MD_TITLE)
		return;

	const int x = 5 * _2X;
	const int y = DY - 5 * _2X;
	const int w = 154 * _2X;
	const int h = 43 * _2X;
	char account[64];
	char revision[64];
	sprintf(account, "User ID  %lld", gNetUserId);
	sprintf(revision, "Data revision  %lld", gNetRevision);

	SetAlpha(14);
	MemRectRound(x, y, w, h, COLOR_BLACK, 5 * _2X);
	SetAlpha(32);
	SetFontColor(COLOR_WHITE);
	DrawText(TEXT_VERSION, x + 7 * _2X, y - 5 * _2X, 0.72f);
	DrawTextStrSystem(account, x + 7 * _2X, y - 18 * _2X,
		0.58f, LEFT, true);
	DrawTextStrSystem(revision, x + 7 * _2X, y - 31 * _2X,
		0.58f, LEFT, true);
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

namespace
{
	struct TitleSkillRange
	{
		int start;
		int count;
		int text;
	};

	const TitleSkillRange titleRobinSkills[] = {
		{ ROBIN_ATTACK_AIRCRASH_START, ROBIN_ATTACK_AIRCRASH_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_AIRCRASH },
		{ ROBIN_ATTACK_STAB_START, ROBIN_ATTACK_STAB_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_STAB },
		{ ROBIN_ATTACK_BOOSTSLASH_START, ROBIN_ATTACK_BOOSTSLASH_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_BOOSTSLASH },
		{ ROBIN_ATTACK_HYPERCHARGE_START, ROBIN_ATTACK_HYPERCHARGE_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_HYPERCHARGE },
		{ ROBIN_ATTACK_SOULCRASH_START, ROBIN_ATTACK_SOULCRASH_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_SOULCRASH },
		{ ROBIN_ATTACK_ABSOLUTEPIERCE_START, ROBIN_ATTACK_ABSOLUTEPIERCE_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_ABSOLUTEPIERCE },
		{ ROBIN_ATTACK_KILLALL_START, ROBIN_ATTACK_KILLALL_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_KILLALL },
		{ ROBIN_ATTACK_DEFENSE_START, ROBIN_ATTACK_DEFENSE_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_DEFENSE },
		{ ROBIN_ATTACK_BARRIER_START, ROBIN_ATTACK_BARRIER_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_BARRIER },
		{ ROBIN_ATTACK_HPRESTORE_START, ROBIN_ATTACK_HPRESTORE_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_HPRESTORE },
		{ ROBIN_ATTACK_MPRESTORE_START, ROBIN_ATTACK_MPRESTORE_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_MPRESTORE },
		{ ROBIN_ATTACK_REFLECTOR_START, ROBIN_ATTACK_REFLECTOR_CNT, TEXT_ACTIONCARD_SKILL_ROBIN_REFLECTOR }
	};
	const TitleSkillRange titleDianaSkills[] = {
		{ DIANA_SKILL_3WAY_START, DIANA_SKILL_3WAY_CNT, TEXT_ACTIONCARD_SKILL_DIANA_3WAY },
		{ DIANA_SKILL_LASER_START, DIANA_SKILL_LASER_CNT, TEXT_ACTIONCARD_SKILL_DIANA_LASER },
		{ DIANA_SKILL_BOMBSHOT_START, DIANA_SKILL_BOMBSHOT_CNT, TEXT_ACTIONCARD_SKILL_DIANA_BOMBSHOT },
		{ DIANA_SKILL_GUIDEDSHOT_START, DIANA_SKILL_GUIDEDSHOT_CNT, TEXT_ACTIONCARD_SKILL_DIANA_GUIDESHOT },
		{ DIANA_SKILL_SPRAYSHOT_START, DIANA_SKILL_SPRAYSHOT_CNT, TEXT_ACTIONCARD_SKILL_DIANA_SPRAYSHOT },
		{ DIANA_SKILL_SATELLITESHOT_START, DIANA_SKILL_SATELLITESHOT_CNT, TEXT_ACTIONCARD_SKILL_DIANA_SATELLITESHOT },
		{ DIANA_SKILL_HEALSHOT_START, DIANA_SKILL_HEALSHOT_CNT, TEXT_ACTIONCARD_SKILL_DIANA_HEALSHOT },
		{ DIANA_SKILL_FEELUP_START, DIANA_SKILL_FEELUP_CNT, TEXT_ACTIONCARD_SKILL_DIANA_FEELUP },
		{ DIANA_SKILL_VAMPIRE_START, DIANA_SKILL_VAMPIRE_CNT, TEXT_ACTIONCARD_SKILL_DIANA_VAMPIRE },
		{ DIANA_SKILL_FOCUS_START, DIANA_SKILL_FOCUS_CNT, TEXT_ACTIONCARD_SKILL_DIANA_FOCUS },
		{ DIANA_SKILL_FAMAS_START, DIANA_SKILL_FAMAS_CNT, TEXT_ACTIONCARD_SKILL_DIANA_FAMAS }
	};
	const TitleSkillRange titleMaxxSkills[] = {
		{ MAXX_SKILL_KICK_START, MAXX_SKILL_KICK_CNT, TEXT_ACTIONCARD_SKILL_MAXX_KICK },
		{ MAXX_SKILL_SHORT_START, MAXX_SKILL_SHORT_CNT, TEXT_ACTIONCARD_SKILL_MAXX_SHORT },
		{ MAXX_SKILL_AIR_START, MAXX_SKILL_AIR_CNT, TEXT_ACTIONCARD_SKILL_MAXX_AIR },
		{ MAXX_SKILL_CAMPING_START, MAXX_SKILL_CAMPING_CNT, TEXT_ACTIONCARD_SKILL_MAXX_CAMPING },
		{ MAXX_SKILL_HORMING_START, MAXX_SKILL_HORMING_CNT, TEXT_ACTIONCARD_SKILL_MAXX_HORMING },
		{ MAXX_SKILL_CIRCLE_START, MAXX_SKILL_CIRCLE_CNT, TEXT_ACTIONCARD_SKILL_MAXX_CIRCLE },
		{ MAXX_SKILL_MEGA_START, MAXX_SKILL_MEGA_CNT, TEXT_ACTIONCARD_SKILL_MAXX_MEGA },
		{ MAXX_SKILL_BLOOD_START, MAXX_SKILL_BLOOD_CNT, TEXT_ACTIONCARD_SKILL_MAXX_BLOOD },
		{ MAXX_SKILL_DAZZLE_START, MAXX_SKILL_DAZZLE_CNT, TEXT_ACTIONCARD_SKILL_MAXX_DAZZLE },
		{ MAXX_SKILL_SIGH_START, MAXX_SKILL_SIGH_CNT, TEXT_ACTIONCARD_SKILL_MAXX_SIGH },
		{ MAXX_SKILL_SPLIT_START, MAXX_SKILL_SPLIT_CNT, TEXT_ACTIONCARD_SKILL_MAXX_SPLIT }
	};

	int titleSkillHero = ROBIN;
	int titleCmfWindowStart = 0;
	int titleSkillIndex = 0;
	int titleSkillFrame = 0;
	bool titleSkillViewerActive = false;
	bool titleSkillPlaying = false;
	bool titleSkillPaused = false;
	bool titleSkillReadyNext = false;

	const TitleSkillRange* GetTitleSkillRanges(int hero, int* count)
	{
		if (hero == DIANA) {
			*count = sizeof(titleDianaSkills) / sizeof(titleDianaSkills[0]);
			return titleDianaSkills;
		}
		if (hero == MAXX) {
			*count = sizeof(titleMaxxSkills) / sizeof(titleMaxxSkills[0]);
			return titleMaxxSkills;
		}
		*count = sizeof(titleRobinSkills) / sizeof(titleRobinSkills[0]);
		return titleRobinSkills;
	}

	const unsigned short* GetTitleSkillMotion(int hero)
	{
		if (hero == DIANA)
			return dianaSkillMotion;
		if (hero == MAXX)
			return maxxSkillMotion;
		return robinSkillMotion;
	}

	void GetTitleMotionDefineName(int hero, int motion, char* name)
	{
		//현재 리터칭/진단의 중심인 로빈 A/CRASH 보간 프레임은 실제 enum
		//이름까지 복원한다. 다른 계열도 최소한 영웅 접두사와 실제 motion id가
		//항상 보이게 해서 데이터와 바로 대조할 수 있게 한다.
		if (hero == ROBIN && motion >= PO_C0_A0 && motion <= PO_C0_A24) {
			sprintf(name, "PO_C0_A%d", motion - PO_C0_A0);
		}
		else if (hero == ROBIN && motion >= PO_C0_A0_1 && motion <= PO_C0_A23_3) {
			int offset = motion - PO_C0_A0_1;
			sprintf(name, "PO_C0_A%d_%d", offset / 3, offset % 3 + 1);
		}
		else if (hero == ROBIN && motion >= PO_C0_CRASH0 && motion <= PO_C0_CRASH5) {
			sprintf(name, "PO_C0_CRASH%d", motion - PO_C0_CRASH0);
		}
		else if (hero == ROBIN && motion >= PO_C0_CRASH0_1 && motion <= PO_C0_CRASH4_3) {
			int offset = motion - PO_C0_CRASH0_1;
			sprintf(name, "PO_C0_CRASH%d_%d", offset / 3, offset % 3 + 1);
		}
		else {
			sprintf(name, "PO_C%d_(%d)", hero, motion);
		}
	}

	//======================================================================
	// 타이틀 장비 디버그
	//
	// 누를 때마다 여섯 칸(무기 ~ 신발)의 장비가 한 단씩 좋아진다. 그림이
	// 바뀌는 것을 눈으로 보려는 것이라, 능력치가 아니라 detail 과 등급을
	// 끝까지 올린다. 마지막 단에서 한 번 더 누르면 처음(맨몸)으로 돌아온다.
	//
	// 원래 끼고 있던 장비는 처음 누를 때 받아 두고, 0 단으로 돌아올 때
	// 그대로 되돌린다 - 디버그 때문에 세이브의 장비가 사라지면 안 된다.
	//======================================================================
	enum { TITLE_GEAR_STEP = 4 };	//0 = 원래대로, 1 ~ 3 = 점점 좋은 장비

	static int titleGearStep = 0;
	static bool titleGearSaved = false;
	static ITEM titleGearBackup[TOTALEQUIP];

	//여섯 칸에 들어갈 물건. 칸 순서는 EQUIP_WEAPON ~ EQUIP_BOOTS 다.
	static const int kTitleGearType[6] = {
		ITEM_SWORD, ITEM_HELM, ITEM_ARMOR, ITEM_GLOVE, ITEM_PANTS, ITEM_BOOTS
	};

	//칸마다 그림이 있는 마지막 번호. 이 값까지 올라간다.
	static const int kTitleGearLast[6] = {
		TOTALSWORD - 1, TOTALHELM - 1, TOTALARMOR - 1, 5, 5, 5
	};

	void TitleGearApply(int step)
	{
		OBJECT* hero = &ao[ROBIN];
		int i;

		//처음 만지는 순간에 원래 장비를 받아 둔다.
		if (!titleGearSaved) {
			memcpy(titleGearBackup, hero->equip, sizeof(titleGearBackup));
			titleGearSaved = true;
		}

		if (step <= 0) {
			memcpy(hero->equip, titleGearBackup, sizeof(titleGearBackup));
			RefreshStat(hero);
			return;
		}

		for (i = 0; i < 6; i++) {
			//단이 오를수록 번호도 등급도 끝으로 간다.
			const int detail = kTitleGearLast[i] * step / (TITLE_GEAR_STEP - 1);
			const int grade = Min(TOTALGRADE - 1,
				(TOTALGRADE - 1) * step / (TITLE_GEAR_STEP - 1));

			MakeItem(&hero->equip[i], kTitleGearType[i], ITEMMAXLEVEL,
				grade, Max(0, detail), EMPTY);
		}

		RefreshStat(hero);
	}

	//버튼 자리. 모션 뷰어의 영웅 탭 바로 아래다.
	void TitleGearBtnRect(int* x, int* y, int* w, int* h)
	{
		*w = 72 * _2X;
		*h = 20 * _2X;
		*x = xOffset + DX / 2 - *w / 2;
		*y = DY - 12 * _2X - 58 * _2X - 4 * _2X;
	}

	void DrawTitleGearButton(void)
	{
		char str[32];
		int x, y, w, h;

		TitleGearBtnRect(&x, &y, &w, &h);

		MemRectBoth(x, y, w, h, titleGearStep > 0 ? COLOR_BROWN : COLOR_BLACK, COLOR_WHITE);
		SetFontColor(COLOR_WHITE);

		if (titleGearStep <= 0)
			sprintf(str, "장비 없음");
		else
			sprintf(str, "장비 %d/%d", titleGearStep, TITLE_GEAR_STEP - 1);

		CenterTextStrSolid(str, x + w / 2, y - h + 5 * _2X, 0.6f);
		SetRectPoint(x, y, w, h, TOUCH_FUNC_TITLE_GEAR);
	}

	//버튼을 눌렀다. 한 단 올리고, 끝까지 갔으면 처음으로 돌아온다.
	void TitleGearNext(void)
	{
		titleGearStep = (titleGearStep + 1) % TITLE_GEAR_STEP;
		TitleGearApply(titleGearStep);
	}

	void DrawTitleSkillViewer()
	{
		const int tabW = 72 * _2X;
		const int tabH = 58 * _2X;
		const int tabY = DY - 12 * _2X;
		const int tabX = xOffset + DX / 2 - tabW * 3 / 2;
		int i;

		for (i = 0; i < 3; i++) {
			int cmf = titleCmfWindowStart + i;
			char cmfNumber[16];
			//저장 데이터에 아직 영웅이 없더라도 타이틀 뷰어에서는 각 영웅의
			//고유 CMF를 사용한다. 그렇지 않으면 빈 OBJECT가 로빈처럼 그려질 수 있다.
			if (cmf < TOTALPLAYER) {
				ao[cmf].type = cmf;
				ao[cmf].cmf = cmf;
			}
			MemRectBoth(tabX + tabW * i, tabY, tabW, tabH,
				titleSkillViewerActive && titleSkillHero == cmf ? COLOR_YELLOW : COLOR_BLACK,
				COLOR_WHITE);
			if (cmf < TOTALPLAYER)
				DrawPlayer(&ao[cmf], frame / 6 % 4,
					tabX + tabW * i + tabW / 2, tabY - tabH + 10 * _2X,
					RIGHT, 0.85f, false, false, false);
			else
				DrawCmfDetail(cmf, frame / 6 % Max(1, (int)cmf_m_cnt[cmf]),
					tabX + tabW * i + tabW / 2, tabY - tabH + 10 * _2X,
					RIGHT, 0.85f, false, false);
			sprintf(cmfNumber, "%d", cmf);
			SetFontColor(COLOR_WHITE);
			CenterTextStrSolid(cmfNumber, tabX + tabW * i + tabW / 2,
				tabY - 6 * _2X, 0.8f);
			SetRectPoint(tabX + tabW * i, tabY, tabW, tabH,
				TOUCH_FUNC_TITLE_SKILL_ROBIN + i);
		}

		//장비를 갈아 끼우는 버튼. 탭 아래에 늘 보인다.
		DrawTitleGearButton();

		if (!titleSkillViewerActive)
			return;

		int skillCount = 0;
		const TitleSkillRange* ranges = titleSkillHero < TOTALPLAYER
			? GetTitleSkillRanges(titleSkillHero, &skillCount) : 0;
		if (titleSkillHero >= TOTALPLAYER) {
			for (skillCount = 0; skillCount < MAXSTATUS; skillCount++) {
				if (cmf_status_data[titleSkillHero][skillCount][0] <= 0)
					break;
			}
			skillCount = Max(1, skillCount);
			titleSkillIndex = Min(titleSkillIndex, skillCount - 1);
		}
		const TitleSkillRange* skill = ranges ? &ranges[titleSkillIndex] : 0;
		const unsigned short* motions = titleSkillHero < TOTALPLAYER
			? GetTitleSkillMotion(titleSkillHero) : 0;
		int motionFrameCount = skill ? skill->count
			: Max(1, (int)cmf_status_data[titleSkillHero][titleSkillIndex][0]);
		int motion = 0;
		int previewY = DY / 2 - 70 * _2X;
		char motionDefine[64];

		if (titleSkillPlaying || titleSkillReadyNext)
			motion = skill ? motions[(skill->start + titleSkillFrame) * 4]
				: cmf_status_data[titleSkillHero][titleSkillIndex][titleSkillFrame + 2];

		//킬링존 후반은 RFIRE13에서 점프한 뒤 공중에서 아래로 사격한다.
		//전투에서는 _JUMP0/_ADDJUMPFRAME2가 OBJECT 좌표를 움직이지만 타이틀
		//뷰어는 DrawPlayer만 호출하므로 그 이동이 빠진다. 같은 구간에 미리보기
		//용 포물선을 적용해 공중 사격 자세가 실제 흐름대로 보이게 한다.
		if (titleSkillHero == DIANA && titleSkillIndex == 4 && titleSkillFrame >= 115) {
			int jumpFrame = Min(titleSkillFrame - 115, 35);
			int rise = jumpFrame <= 12 ? jumpFrame * 6 : Max(0, 72 - (jumpFrame - 12) * 3);
			previewY += rise * _2X;
		}

		const int viewerX = xOffset + DX / 2 - 110 * _2X;
		const int viewerY = DY / 2 + 150 * _2X;
		const int viewerW = 220 * _2X;
		const int viewerH = 300 * _2X;
		SetAlpha(21);
		MemRect(viewerX, viewerY, viewerW, viewerH, COLOR_NAVY);
		SetAlpha(32);
		if (titleSkillHero < TOTALPLAYER)
			DrawPlayer(&ao[titleSkillHero], motion, xOffset + DX / 2, previewY,
				RIGHT, 2.0f, false, false, true);
		else
			DrawCmfDetail(titleSkillHero, motion, xOffset + DX / 2, previewY,
				RIGHT, 2.0f, false, false);
		SetFontColor(COLOR_WHITE);
		if (skill)
			CenterTextSolid(skill->text, xOffset + DX / 2, viewerY - viewerH + 52 * _2X, 1.2f);
		else
		{
			char stateText[32];
			sprintf(stateText, "CMF STATE %d / %d", titleSkillIndex, skillCount - 1);
			CenterTextStrSolid(stateText, xOffset + DX / 2,
				viewerY - viewerH + 52 * _2X, 1.2f);
		}
		GetTitleMotionDefineName(titleSkillHero, motion, motionDefine);
		CenterTextStrSolid(motionDefine, xOffset + DX / 2,
			viewerY - viewerH + 30 * _2X, 0.95f);
		char cmfText[32];
		sprintf(cmfText, "CMF = %d / %d", titleSkillHero, MAXCMF - 1);
		CenterTextStrSolid(cmfText, xOffset + DX / 2,
			viewerY - viewerH + 12 * _2X, 0.9f);
		if (titleSkillPaused)
			CenterTextStrSolid("PAUSE", xOffset + DX / 2, viewerY - 18 * _2X, 1.0f);

		//캐릭터 판 안은 재생/재개, 판 바깥은 일시정지다. 영웅 탭과 기존
		//하단 NEW/MAX GAME 카드는 바깥 일시정지 영역에서 제외한다.
		SetRectPoint(viewerX, viewerY, viewerW, viewerH, TOUCH_FUNC_TITLE_SKILL_PLAY);
		SetRectPoint(xOffset, tabY - tabH, DX, tabY - tabH - viewerY,
			TOUCH_FUNC_TITLE_SKILL_PAUSE);
		SetRectPoint(xOffset, viewerY, viewerX - xOffset, viewerH,
			TOUCH_FUNC_TITLE_SKILL_PAUSE);
		SetRectPoint(viewerX + viewerW, viewerY, xOffset + DX - viewerX - viewerW, viewerH,
			TOUCH_FUNC_TITLE_SKILL_PAUSE);
		SetRectPoint(xOffset, viewerY - viewerH, DX, viewerY - viewerH - 60 * _2X,
			TOUCH_FUNC_TITLE_SKILL_PAUSE);

		if (titleSkillPlaying && !titleSkillPaused) {
			titleSkillFrame++;
			if (titleSkillFrame >= motionFrameCount) {
				titleSkillFrame = motionFrameCount - 1;
				titleSkillPlaying = false;
				titleSkillReadyNext = true;
			}
		}

		const int arrowW = 42 * _2X;
		const int arrowH = 72 * _2X;
		const int arrowY = DY / 2 + arrowH / 2;
		MemRectBoth(xOffset + 8 * _2X, arrowY, arrowW, arrowH, COLOR_NAVY, COLOR_WHITE);
		MemRectBoth(xOffset + DX - 8 * _2X - arrowW, arrowY, arrowW, arrowH, COLOR_NAVY, COLOR_WHITE);
		SetFontColor(COLOR_WHITE);
		CenterTextStrSolid("<", xOffset + 8 * _2X + arrowW / 2, arrowY - 18 * _2X, 1.8f);
		CenterTextStrSolid(">", xOffset + DX - 8 * _2X - arrowW / 2, arrowY - 18 * _2X, 1.8f);
		SetRectPoint(xOffset + 8 * _2X, arrowY, arrowW, arrowH, TOUCH_FUNC_TITLE_SKILL_PREV_CMF);
		SetRectPoint(xOffset + DX - 8 * _2X - arrowW, arrowY, arrowW, arrowH, TOUCH_FUNC_TITLE_SKILL_NEXT_CMF);

		//---- 한 칸씩 넘기기 ----
		//
		//판 안을 누르면 처음부터 재생, 판 밖을 누르면 일시정지다. 그 사이에
		//"멈춘 채로 한 칸만"이 없어서 어느 프레임이 깨졌는지 볼 수가 없었다.
		//
		//누를 때마다 다음 칸으로 가고 끝에서 처음으로 돈다. 재생 중에 눌러도
		//바로 멈추고 그 다음 칸을 보여준다.
		{
			const int stepH = 48 * _2X;
			const int stepY = arrowY - arrowH - 8 * _2X;
			const int stepX = xOffset + DX - 8 * _2X - arrowW;
			char stepText[32];

			MemRectBoth(stepX, stepY, arrowW, stepH, COLOR_NAVY, COLOR_WHITE);
			SetFontColor(COLOR_WHITE);
			CenterTextStrSolid("S", stepX + arrowW / 2,
				stepY - 14 * _2X, 1.4f);

			//지금 몇 번째 칸인지. 이게 없으면 눌러도 넘어갔는지 모른다.
			sprintf(stepText, "%d/%d", titleSkillFrame, motionFrameCount - 1);
			CenterTextStrSolid(stepText, stepX + arrowW / 2,
				stepY - 34 * _2X, 0.62f);

			SetRectPoint(stepX, stepY, arrowW, stepH,
				TOUCH_FUNC_TITLE_SKILL_STEP);
		}
	}
}

void TitleSkillViewerCommand(int command)
{
	if (command >= TOUCH_FUNC_TITLE_SKILL_ROBIN && command <= TOUCH_FUNC_TITLE_SKILL_MAXX) {
		titleSkillHero = titleCmfWindowStart
			+ command - TOUCH_FUNC_TITLE_SKILL_ROBIN;
		titleSkillIndex = 0;
		titleSkillFrame = 0;
		titleSkillPlaying = false;
		titleSkillPaused = false;
		titleSkillReadyNext = false;
		titleSkillViewerActive = true;
		return;
	}
	if (command == TOUCH_FUNC_TITLE_SKILL_PREV_CMF
		|| command == TOUCH_FUNC_TITLE_SKILL_NEXT_CMF) {
		int delta = command == TOUCH_FUNC_TITLE_SKILL_PREV_CMF ? -1 : 1;
		int oldWindowStart = titleCmfWindowStart;
		titleCmfWindowStart = Max(0, Min(MAXCMF - 3, titleCmfWindowStart + delta));
		if (titleCmfWindowStart != oldWindowStart)
			titleSkillHero = Max(titleCmfWindowStart,
				Min(titleCmfWindowStart + 2, titleSkillHero + delta));
		titleSkillIndex = 0;
		titleSkillFrame = 0;
		titleSkillPlaying = false;
		titleSkillPaused = false;
		titleSkillReadyNext = false;
		titleSkillViewerActive = true;
		return;
	}

	if (command == TOUCH_FUNC_TITLE_GEAR) {
		TitleGearNext();
		return;
	}

	if (command == TOUCH_FUNC_TITLE_SKILL_PLAY && titleSkillViewerActive && !titleSkillPlaying) {
		if (titleSkillReadyNext) {
			if (titleSkillHero < TOTALPLAYER) {
				int skillCount = 0;
				GetTitleSkillRanges(titleSkillHero, &skillCount);
				titleSkillIndex = (titleSkillIndex + 1) % skillCount;
			}
			else {
				int stateCount = 0;
				while (stateCount < MAXSTATUS
					&& cmf_status_data[titleSkillHero][stateCount][0] > 0)
					stateCount++;
				titleSkillIndex = (titleSkillIndex + 1) % Max(1, stateCount);
			}
		}
		titleSkillFrame = 0;
		titleSkillPlaying = true;
		titleSkillPaused = false;
		titleSkillReadyNext = false;
	}
	else if (command == TOUCH_FUNC_TITLE_SKILL_PLAY && titleSkillPlaying) {
		titleSkillPaused = false;
	}
	else if (command == TOUCH_FUNC_TITLE_SKILL_PAUSE && titleSkillPlaying) {
		titleSkillPaused = true;
	}
	else if (command == TOUCH_FUNC_TITLE_SKILL_STEP && titleSkillViewerActive) {
		//---- 한 칸 넘기기 ----
		//
		//칸 수를 여기서 다시 세는 것은 그리는 쪽과 같은 값을 봐야 하기
		//때문이다. 영웅은 스킬 구간의 길이, 그 밖의 cmf 는 상태표의 길이다.
		int motionFrameCount = 1;

		if (titleSkillHero < TOTALPLAYER) {
			int skillCount = 0;
			const TitleSkillRange* ranges =
				GetTitleSkillRanges(titleSkillHero, &skillCount);

			if (ranges && skillCount > 0)
				motionFrameCount = ranges[Min(titleSkillIndex,
					skillCount - 1)].count;
		}
		else
			motionFrameCount = Max(1,
				(int)cmf_status_data[titleSkillHero][titleSkillIndex][0]);

		motionFrameCount = Max(1, motionFrameCount);

		//재생 중이었으면 멈추고 그 다음 칸을 보여준다. 멈춰 있었으면
		//그냥 다음 칸이다. 어느 쪽이든 누른 만큼만 움직인다.
		titleSkillFrame = (titleSkillFrame + 1) % motionFrameCount;
		titleSkillPlaying = true;
		titleSkillPaused = true;
		titleSkillReadyNext = false;
	}
}

namespace
{
	bool titleTermsRequired = false;
	bool titleTermsMarketing = false;
	bool titleTermsNight = false;

	void DrawTitleTermsCheck(int x, int y, bool checked, const char* label, int touchFunc)
	{
		const int box = 30 * _2X;
		MemRect(x, y, box, box, COLOR_WHITE);
		MemRectFrame(x, y, box, box, checked ? COLOR_REALRED : COLOR_GREY);
		if (checked) {
			SetFontColor(COLOR_REALRED);
			CenterTextStr("V", x + box / 2, y - box / 2 + 7 * _2X, 1.5f);
		}
		SetFontColor(COLOR_DARKGREY);
		//체크박스와 별개로 문구도 왼쪽 8px, 위쪽 4px 이동한다.
		DrawTextStrSystem(label, x + box + 2 * _2X, y - 7 * _2X,
			1.20f, LEFT, false);
		SetRectPoint(x, y, DX - (x - xOffset) * 2, box + 8 * _2X, touchFunc);
	}

	void DrawTitleTermsGate(void)
	{
		//처음 시안의 창 크기는 유지하고 내용만 읽기 쉽게 만든다.
		const int panelW = Min(DX - 32 * _2X, 430 * _2X);
		const int panelH = 330 * _2X;
		const int x = xOffset + DX / 2 - panelW / 2;
		const int y = DY / 2 + panelH / 2;
		const int rowX = x + 12 * _2X;

		//뒤 타이틀의 테스트 버튼이 눌리지 않도록 약관 터치 영역만 다시 쌓는다.
		ResetRectPoint();
		SetAlpha(22);
		MemRect(0, DY, DX, DY, COLOR_BLACK);
		SetAlpha(32);
		MemRect(x, y, panelW, panelH, 0xFFF8E8);
		MemRectFrame(x, y, panelW, panelH, COLOR_ORANGE);

		SetFontColor(COLOR_WHITE);
		CenterTextStr("게임 이용 동의", xOffset + DX / 2, y - 24 * _2X, 1.86f);
		SetFontColor(COLOR_DARKGREY);
		DrawTextStrSystem("처음 한 번만 확인합니다.", xOffset + DX / 2,
			y - 59 * _2X, 1.10f, CENTER, false);

		DrawTitleTermsCheck(rowX, y - 88 * _2X, titleTermsRequired,
			"[필수] 이용약관 및 개인정보 처리방침 동의", TOUCH_FUNC_TITLE_TERMS_REQUIRED);
		DrawTitleTermsCheck(rowX, y - 137 * _2X, titleTermsMarketing,
			"[선택] 이벤트 및 마케팅 정보 수신", TOUCH_FUNC_TITLE_TERMS_MARKETING);
		DrawTitleTermsCheck(rowX, y - 186 * _2X, titleTermsNight,
			"[선택] 야간 알림 수신", TOUCH_FUNC_TITLE_TERMS_NIGHT);

		const char* serviceText = "이용약관 보기";
		const char* privacyText = "개인정보 처리방침 보기";
		const int linkCenter1 = x + panelW / 4 - 32 * _2X;
		const int linkCenter2 = x + panelW * 3 / 4;
		const float linkZoom = 1.155f;
		const int linkY = y - 226 * _2X;
		const int linkTextY = linkY - 4 * _2X;
		SetFontColor(COLOR_DARKGREY);
		DrawTextStrSystem(serviceText, linkCenter1, linkTextY, linkZoom, CENTER, false);
		DrawTextStrSystem(privacyText, linkCenter2, linkTextY, linkZoom, CENTER, false);
		const int serviceW = (int)StringWidthTTF(serviceText, linkZoom);
		const int privacyW = (int)StringWidthTTF(privacyText, linkZoom);
		MemRect(linkCenter1 - serviceW / 2, linkY - 22 * _2X, serviceW, 2 * _2X, COLOR_NAVY);
		MemRect(linkCenter2 - privacyW / 2, linkY - 22 * _2X, privacyW, 2 * _2X, COLOR_NAVY);
		SetRectPoint(linkCenter1 - serviceW / 2 - 8 * _2X, linkY + 6 * _2X,
			serviceW + 16 * _2X, 34 * _2X, TOUCH_FUNC_TITLE_TERMS_SERVICE);
		SetRectPoint(linkCenter2 - privacyW / 2 - 8 * _2X, linkY + 6 * _2X,
			privacyW + 16 * _2X, 34 * _2X, TOUCH_FUNC_TITLE_TERMS_PRIVACY);

		const int baseButtonW = (int)((panelW - 84 * _2X) * 0.8f);
		const int baseButtonH = (int)(66 * _2X * 0.8f);
		const int baseButtonX = x + panelW / 2 - baseButtonW / 2;
		const int baseButtonY = y - 264 * _2X;
		int buttonX = baseButtonX;
		int buttonY = baseButtonY;
		int buttonW = baseButtonW;
		int buttonH = baseButtonH;
		const float press = GetButtonPressScale(buttonX, buttonY, buttonW, buttonH);
		if (press != 1.0f) {
			buttonX -= (int)((float)buttonW * (press - 1.0f) / 2);
			buttonY += (int)((float)buttonH * (press - 1.0f) / 2);
			buttonW = (int)((float)buttonW * press);
			buttonH = (int)((float)buttonH * press);
		}
		DrawFrame(buttonX, buttonY, buttonW, buttonH,
			titleTermsRequired ? FRAME_GREEN : FRAME_GREY);
		SetFontColor(COLOR_WHITE);
		CenterTextStr("동의하고 시작", buttonX + buttonW / 2,
			buttonY - buttonH / 2 + 11 * _2X, 2.0f * press);
		//눌림 연출로 바뀐 좌표가 아니라 원래 버튼 전체를 터치 영역으로 쓴다.
		SetRectPoint(baseButtonX, baseButtonY, baseButtonW, baseButtonH,
			TOUCH_FUNC_TITLE_TERMS_ACCEPT);
		SetFontColor(COLOR_WHITE);
	}

	void DrawTitleBootLoading(void)
	{
		//약관 CDN 확인, 로그인, DB 세이브 수신 중에는 타이틀의 시작 버튼을
		//누를 수 없다. 로고에서 끝낸 리소스 로딩과 서버 초기화를 구분해서
		//보여준다.
		ResetRectPoint();
		SetAlpha(18);
		MemRect(0, DY, DX, DY, COLOR_BLACK);
		SetAlpha(32);
		SetFontColor(COLOR_WHITE);
		CenterTextStr("서버 데이터 확인 중...", xOffset + DX / 2,
			DY / 2 - 110 * _2X, 0.9f);
	}

	void DrawTitleLoginGate(void)
	{
		const int panelW = Min(DX - 32 * _2X, 430 * _2X);
		const int panelH = 330 * _2X;
		const int x = xOffset + DX / 2 - panelW / 2;
		const int y = DY / 2 + panelH / 2;
		const int buttonW = 250 * _2X;
		const int buttonH = 40 * _2X;
		const int buttonX = xOffset + DX / 2 - buttonW / 2;
		const char* labels[TOTAL_LOGIN] = {
			"Facebook으로 로그인", "Google로 로그인",
			"Apple로 로그인", "게스트로 시작"
		};

		ResetRectPoint();
		SetAlpha(22);
		MemRect(0, DY, DX, DY, COLOR_BLACK);
		SetAlpha(32);
		MemRect(x, y, panelW, panelH, 0xFFF8E8);
		MemRectFrame(x, y, panelW, panelH, COLOR_ORANGE);

		SetFontColor(COLOR_WHITE);
		CenterTextStr("로그인", xOffset + DX / 2, y - 27 * _2X, 1.65f);
		SetFontColor(COLOR_DARKGREY);
		DrawTextStrSystem("게임 데이터를 안전하게 저장합니다.",
			xOffset + DX / 2, y - 56 * _2X, 0.88f, CENTER, false);

		for (int i = 0; i < TOTAL_LOGIN; i++) {
			const int by = y - (78 + i * 50) * _2X;
			const bool guest = (i == LOGIN_GUEST);
			DrawFrame(buttonX, by, buttonW, buttonH,
				guest ? FRAME_GREEN : FRAME_BLUE);

			//ETC_IMG의 147행에는 Facebook/Google/Apple/Guest 아이콘이
			//32x32 순서로 이미 들어 있다. 버튼 왼쪽 여백 안에 맞춰 쓴다.
			const int oldGray = grayScale;
			DrawImage(32 * _2X, 32 * _2X,
				i * 32 * _2X, 147 * _2X,
				buttonX + 8 * _2X, by - 4 * _2X,
				false, false, false, false, false, 1.0f,
				sprite[ETC_IMG], ETC_IMG);
			grayScale = oldGray;

			SetFontColor(COLOR_WHITE);
			DrawTextStrSystem(labels[i], buttonX + 48 * _2X,
				by - buttonH / 2 + 6 * _2X, 0.95f, LEFT, false);

			SetRectPoint(buttonX, by, buttonW, buttonH,
				TOUCH_FUNC_TITLE_LOGIN_FACEBOOK + i);
		}
	}
}

void TitleTermsCommand(int command)
{
	if (!NetTermsPending())
		return;

	switch (command) {
	case TOUCH_FUNC_TITLE_TERMS_REQUIRED:
		titleTermsRequired = !titleTermsRequired;
		PlayMusic(M_BUTTON);
		break;
	case TOUCH_FUNC_TITLE_TERMS_MARKETING:
		titleTermsMarketing = !titleTermsMarketing;
		PlayMusic(M_BUTTON);
		break;
	case TOUCH_FUNC_TITLE_TERMS_NIGHT:
		titleTermsNight = !titleTermsNight;
		PlayMusic(M_BUTTON);
		break;
	case TOUCH_FUNC_TITLE_TERMS_SERVICE:
		PlayMusic(M_SELECT);
		NetOpenTerms(false);
		break;
	case TOUCH_FUNC_TITLE_TERMS_PRIVACY:
		PlayMusic(M_SELECT);
		NetOpenTerms(true);
		break;
	case TOUCH_FUNC_TITLE_TERMS_ACCEPT:
		if (titleTermsRequired) {
			PlayMusic(M_LEVELUP);
			NetAgreeTerms(true, titleTermsMarketing, titleTermsNight);
		}
		else {
			PlayMusic(M_ERROR);
		}
		break;
	}
}

void TitleDraw(void)
{
	int i;
	std::string fileName;
	int x = 0, y = MINDY_MIN / 2 + DY / 2 + (MINDY_MIN - MINDY) / 2;
	float zoom;
	float scale = 0.7f;
	int width = GetGoldAlphaWidth(ALPHA_RANDOM, FONT_GOLD_LARGE, scale) + 8 * _2X + GetGoldAlphaWidth(ALPHA_SWORD, FONT_GOLD_LARGE, scale);
	int monCmf[] = { CMF_FROG , CMF_FROG_RED , CMF_FROG_BLUE, CMF_FROG_PURPLE, CMF_FROG_GREEN, CMF_FROG_GOLD, CMF_FROG_BLACK };

	int questRequest = questInfo[robin.quest * QUESTINFODATASIZE + 2];

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
		MemRect(0, DY, DX, DY, 0x000000);
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


			//DrawBigNumTTF(1000, 0, DY, NUM_FONT_LARGE, LEFT, false, false, (float)((REWARDCARDSIZE_X - 8 * _2X) / 2) * 1.0f, false, 0.7f, true, gScreenBuffer, gScreenLayer, false);
			//DrawBigNumTTF(10000, 0, DY - 20 * _2X, NUM_FONT_LARGE, LEFT, false, false, (float)((REWARDCARDSIZE_X - 8 * _2X) / 2) * 1.0f, false, 1.0f, true, gScreenBuffer, gScreenLayer, false);
			LoadingBarDraw(xOffset + DX / 2 - 525 * _2X / 2 + 180 * _2X, 40 * _2X, frame);
			break;
			//case CURTAINFRAME - 1:
			//case 23:
		default:

			touchDisable = false;
#if SHOW_TITLE_MOTION_VIEWER
			// 스킬 모션을 한 프레임씩 넘겨 보는 개발용 화면.
			DrawTitleSkillViewer();
#endif

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

	if (NetTermsPending())
		DrawTitleTermsGate();
	else if (NetLoginChoicePending()) {
		curMenu = MENU_LOGIN;
		DrawTitleLoginGate();
	}
	else if (NetBootstrapPoll() == NETRESULT_NONE)
		DrawTitleBootLoading();

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

//==========================================================================
// 성 격자 인벤토리 - 시험 모듈
//
// [무엇인가]
// 성 실루엣 모양의 격자에 장비를 끌어다 놓고, 휴지통으로 끌어다 버리면
// 팔리는 것까지를 손으로 만져 보기 위한 판이다. 규칙이 손에 맞는지는
// 표로는 알 수 없고 끌어 봐야 안다.
//
// [왜 로비에 얹었나]
// 전투와 엮이지 않은 곳이 여기뿐이다. 판이 도는 중에는 카드를 놓을 때
// 전투를 멈춰야 하는데, 그 결정을 하기 전에 배치 자체가 재미있는지부터
// 봐야 한다.
//
// [왜 한 파일에 몰아넣었나]
// 소스 목록이 win32 / iOS / Android 세 곳에 손으로 적혀 있어서, 새 .cpp
// 하나를 만들면 세 군데를 고쳐야 한다(그 중 pbxproj 는 UUID 를 손으로
// 만들어야 한다). 시험이 끝나고 정식 기능이 되면 그때 떼어 낸다.
// 떼기 쉽도록 이 블록 안에서만 돌게 짰다 - 바깥이 부르는 것은 아래 네
// 개뿐이다.
//
//     GridTestDraw()      매 프레임 그리기
//     GridTestPick()      터치가 눌린 순간
//     GridTestRelease()   손을 뗀 순간
//     GridTestToggle()    열고 닫기
//==========================================================================

//---- 성의 가방 칸 ----
//
// 성마다 다르다. 첫 성은 손바닥만 하고 마지막 성은 화면 폭을 채운다.
// 자리가 늘어나는 것 자체가 성을 올리는 이유여야 해서, 크기가 곧 보상이다.
//
// 칸은 표로 읽는다(Data/CastleData.cpp 의 castleGridCell). 몇 칸인지, 칸마다
// 어디인지가 다 거기 있다. 그리기, 끌어다 놓기, 칸 세기가 모두 이 표 하나를
// 본다 - 셋이 따로 계산하면 보이는 칸과 놓이는 칸이 어긋난다.
//
// 전에는 성 번호에서 가로 x 세로를 셈하고 두 줄마다 양옆을 깎는 식으로
// 모양을 만들었다. 식으로는 탑 모양이나 가운데가 빈 모양을 못 만든다.
static const int kGridMaxW = GRIDTEST_W;

static int gGridW = 0;			//이번 성 칸들의 가로 폭(가장 오른쪽 열 + 1)
static int gGridH = 0;			//세로 폭(가장 윗 행 + 1)
static int gGridCastle = -1;	//gGridMask 가 어느 성의 것인가

//표를 한 번 펼쳐 둔 것. 칸이 쓰이는지를 매번 표에서 찾지 않는다.
static bool gGridMask[GRIDTEST_H][GRIDTEST_W];

static int GridCastleIdx(int castle)
{
	return Min(TOTALCASTLE - 1, Max(0, castle));
}

//이 성의 가방 칸 수. 로비의 판 설명도 이 값을 쓴다.
int GridTestCellCnt(int castle)
{
	return castleGridCellCnt[GridCastleIdx(castle)];
}

//표에서 이 성의 칸을 펼친다. 성이 바뀔 때만 다시 펼친다.
static void GridLoadCells(int castle)
{
	const int c = GridCastleIdx(castle);

	if (c == gGridCastle)
		return;

	gGridCastle = c;
	gGridW = 0;
	gGridH = 0;
	memset(gGridMask, 0, sizeof(gGridMask));

	const int start = castleGridCellStart[c];
	const int cnt = castleGridCellCnt[c];

	for (int i = 0; i < cnt; ++i) {
		const int col = castleGridCell[(start + i) * 2];
		const int row = castleGridCell[(start + i) * 2 + 1];

		//격자 밖을 가리키는 칸은 버린다. 표를 손으로 고치다 틀려도 배열
		//밖을 쓰지 않는다.
		if (col < 0 || col >= GRIDTEST_W || row < 0 || row >= GRIDTEST_H)
			continue;

		gGridMask[row][col] = true;
		gGridW = Max(gGridW, col + 1);
		gGridH = Max(gGridH, row + 1);
	}
}

static bool GridMaskAt(int col, int row)
{
	if (col < 0 || row < 0 || col >= GRIDTEST_W || row >= GRIDTEST_H)
		return false;

	return gGridMask[row][col];
}

//---- 살 수 있는 장비 ----
//
// 크기는 부위의 생김새에서 온다. 검은 세로로 길고, 갑옷은 몸통이라
// 제일 크고, 장신구는 점이다. 값은 자리를 얼마나 먹느냐에 대충 맞췄다.
//
// 등급은 액자 색에 쓴다. 검의 크기는 SwordSprites.h의 실제 칸 규격이다.
struct GridPart {
	int type;
	int detail;
	int grade;
	int w, h;		//격자에서 차지하는 칸. 눕혔으면 이미 바뀐 값이다
	int price;
	const char* name;
	bool rot;		//90도 눕혔는가. 그릴 때 돌린다
};

//---- 눕히기 ----
//
//템빨용사처럼 아이템을 90도 돌려 놓을 수 있다. 세로로 긴 검이 성의 높이를
//넘으면 눕혀서 넓은 아랫줄에 넣는다.
static GridPart GridPartRotated(const GridPart& p)
{
	GridPart r = p;

	r.w = p.h;
	r.h = p.w;
	r.rot = !p.rot;
	return r;
}

static const GridPart kShopPart[GRIDTEST_SHOPCNT] = {
	//---- 검 ----
	//
	//길이(세로 칸)가 곧 검의 길이다. 짧은 검은 판정이 좁고 빠르게
	//지나가고, 대검은 넓고 묵직하다. 격자에서 정한 크기가 전투 감각으로
	//그대로 이어지게 하려고 같은 값을 쓴다.
	//
	//detail 은 ItemDef 의 검 번호다. 번호가 클수록 좋은 검이라, 연참
	//차례를 매길 때 이 번호를 그대로 쓴다.
	{ ITEM_SWORD,   1, GRADE_NORMAL, swordTileSize[1 * 2], swordTileSize[1 * 2 + 1],  60, "롱소드" },
	{ ITEM_SWORD,  10, GRADE_RARE, swordTileSize[10 * 2], swordTileSize[10 * 2 + 1], 180, "플레임소드" },
	{ ITEM_SWORD,  11, GRADE_RARE, swordTileSize[11 * 2], swordTileSize[11 * 2 + 1], 200, "아이스소드" },
	{ ITEM_SWORD,  21, GRADE_LEGEND, swordTileSize[21 * 2], swordTileSize[21 * 2 + 1], 600, "엑스칼리버" },

	//---- 방어구 · 장신구 ----
	{ ITEM_HELM,    1, GRADE_SUPERIOR, 2, 2,  80, "강철투구" },
	{ ITEM_ARMOR,   1, GRADE_SUPERIOR, 2, 2, 140, "판금갑옷" },
	{ ITEM_GUNTLET, 1, GRADE_NORMAL,   2, 2,  40, "건틀릿" },
	{ ITEM_KILT,    1, GRADE_NORMAL,   2, 2,  70, "판금바지" },
	{ ITEM_GREAVES, 1, GRADE_NORMAL,   1, 2,  40, "강철장화" },
	{ ITEM_RING,    0, GRADE_EPIC,     1, 1, 200, "룬반지" },
};

//---- 검마다 잔상 색 ----
//
//실제 전투에서는 _EDGE_YELLOW / RED / BLUE / VIOLET 잔상이 이미 그려져
//있어서 그 넷에 배당하면 된다(Def/SkillDef.h). 여기서는 미리보기라
//색만 흉내 낸다.
//
//표에 없는 검은 은빛으로 둔다. 검을 더 넣어도 조용히 어긋나지 않는다.
static int GridSwordTrail(int detail)
{
	switch (detail) {
	case 10: return 0xE0603C;	//플레임 - 붉은 잔상
	case 11: return 0x4FA3D9;	//아이스 - 푸른 잔상
	case 21: return 0xD9A441;	//엑스칼리버 - 금빛
	case 23: return 0x8A4787;	//다크소드 - 보랏빛
	}

	return 0xDFD9C0;	//은빛
}

//검 길이가 타격 감각을 정한다. 칸 수를 그대로 쓴다.
static const char* GridSwordFeel(int h)
{
	if (h <= 3)
		return "빠름";
	if (h == 4)
		return "보통";

	return "묵직";
}


//등급마다 액자 색. 아이콘만으로는 좋은 것과 나쁜 것이 구별이 안 된다.
static const int kGradeColor[TOTALGRADE] = {
	0x8A8A8A,	//일반
	0x4FA3D9,	//상급
	0x51C46A,	//희귀
	0xD9A441,	//세트
	0xB061D9,	//에픽
	0xE0603C,	//전설
};

//---- 격자에 놓인 것 ----
//
//상점에서 산 것이든 아웃게임 장비든 같은 모양(GridPart)으로 들고 있다.
//그려지고, 끌리고, 자리를 먹는 방식이 둘 다 같아야 해서다.
struct GridSlot {
	GridPart part;	//무엇인가
	int shop;		//상점에서 샀다면 그 kShopPart 번호. 장비면 -1
	int equip;		//아웃게임 장비라면 그 장비 칸(EQUIP_*). 아니면 -1
	int col, row;	//왼쪽 아래 칸
	bool used;

	//---- 진짜 장비 ----
	//
	//옵션과 소켓이 붙은 게임의 ITEM 그대로다. 전투가 턴제를 벗어나면서
	//칸에 놓인 것이 곧 스탯이 되어야 하므로, 크기만 아는 껍데기로는
	//모자란다. MakeItem 이 채운다.
	ITEM item;
	int level;		//같은 것이 겹친 횟수. 1 부터
};

static GridSlot gGridItem[GRIDTEST_MAXITEM];

//격자는 전투 화면에 붙박이로 붙는다. 접을 수는 있다.
static bool gGridOpen = true;

//---- 몬스터를 눕힐 때마다 내미는 세 갈래 ----
//
//gOfferOn 이 서 있는 동안만 카드 세 장이 뜬다. 하나를 사거나 넘기면
//내려간다.
//
//카드는 세 가지다. 장비는 격자에 끌어다 놓아야 산다 - 성이 가방이므로
//자리가 곧 값이다. 동료와 몬스터는 격자를 차지하지 않고 곧바로 히어로
//곁에 서므로 누르는 순간 산다.
enum {
	OFFER_PART = 0,		//장비. kShopPart 의 한 줄
	OFFER_CREW,			//편성표의 동료 하나가 이번 판에 합류한다
	OFFER_MONSTER,		//방금 눕힌 몬스터가 아군이 된다
};

struct OfferCard {
	int kind;
	int part;		//OFFER_PART 일 때 kShopPart 번호
	int crewType;	//그 밖일 때 서는 개체의 타입. 동료도 몬스터 타입이다
	int price;
};

static OfferCard gOffer[GRIDTEST_OFFERCNT];
static bool gOfferOn = false;

//---- 룰렛 ----
//
//칸마다 남은 회전 프레임과, 도는 동안 보여 줄 임시 그림이다. 회전이
//끝나기 전에는 누를 수 없다. 돌아가는 중에 집히면 무엇을 샀는지 모른다.
static int gOfferSpin[GRIDTEST_OFFERCNT];
static int gOfferFace[GRIDTEST_OFFERCNT];

//동료와 몬스터 카드의 값과 나오는 몫(백분율). 나머지가 장비다.
//
//몬스터가 동료보다 싸다. 편성표의 동료는 키워 둔 것이라 믿을 만하고,
//몬스터는 방금 싸운 놈이라 쓸 만한지는 데려와 봐야 안다.
static const int kOfferCrewPrice = 80;
static const int kOfferMonsterPrice = 50;
static const int kOfferCrewPct = 30;
static const int kOfferMonsterPct = 30;



//---- 끌고 있는 것 ----
//
// 조이스틱과 같은 방식이다(Func_Input 의 TOUCH_FUNC_MOVE). 누르는 순간
// 켜고, 움직이는 동안은 touchX / touchY 를 그냥 읽고, 떼는 순간 끈다.
// 이 코드베이스의 터치는 매 프레임 다시 등록되는 사각형이라, 드래그처럼
// 프레임을 넘기는 것은 이렇게 전역 상태로 들고 있어야 한다.
static bool gGridDragOn = false;
static GridPart gGridDragDesc;		//손에 든 것
static int gGridDragShop = -1;		//상점에서 집었다면 그 kShopPart 번호
static int gGridDragFrom = -1;		//-1 이면 상점에서 새로 사는 것

//판이 새로 열렸고 아직 장착 장비를 가방에 넣지 않았다.
static bool gGridGearPending = false;

//세운 채로는 안 들어가는 자리라 눕혀서 놓는다. 끄는 동안 매 프레임 정한다.
static bool gGridDragRot = false;

//누른 자리. 거의 안 움직이고 떼면 "끈 것"이 아니라 "누른 것"이라 돌린다.
static int gGridPressX = 0;
static int gGridPressY = 0;

//놓을 자리를 잡을 때 쓰는 보정. 카드 한가운데를 손가락에 맞춘다.
static int gGridDragCol = -1;
static int gGridDragRow = -1;
static bool gGridDragValid = false;

//마지막으로 한 일. 화면 아래에 한 줄로 띄운다. 무엇이 왜 안 됐는지
//보이지 않으면 시험이 안 된다.
static char gGridMsg[64] = { 0, };
static int gGridMsgFrame = 0;

//---- 자리 계산 ----
//
// 칸 크기와 격자 원점을 한 곳에서 정한다. 그리기와 터치 판정이 서로
// 다른 식을 쓰면 눈에 보이는 자리와 눌리는 자리가 어긋난다.
static int gGridCell = 0;
static int gGridX = 0;			//0 번 열의 왼쪽
static int gGridBottom = 0;		//0 번 행의 아랫변

//격자 바로 위에 얹는 한 줄. 연참 미리보기와 골드/칸이 여기 들어간다.
#define GRIDTEST_HUDH (36 * _2X)

//격자가 화면에서 차지할 수 있는 높이. 몫에 더해 주는 값만큼 칸이
//커진다. 나머지 높이는 전투 화면과 아래 상점 줄이 나눠 쓴다.
#define GRIDTEST_MAXRATE 0.30f
#define GRIDTEST_EXTRAH (32 * _2X)

//======================================================================
// 하단 상점 줄
//
// 격자 아래에 깔리는 판이다. 위에서부터 룰렛 네 칸, 값, 나오는 몫,
// 가진 골드, 맨 아래가 지도 / 전투 시작 / 도감 줄이다.
//
// 자리를 늘 비워 둔다. 몬스터를 눕힐 때마다 나타났다 사라지면 격자가
// 위아래로 뛰어서, 끌어다 놓던 손이 매번 자리를 다시 찾아야 한다.
//======================================================================
#define STAGE_SHOP_GAP		(6 * _2X)
#define STAGE_SHOP_CARDH	(34 * _2X)	//룰렛 칸 그림
#define STAGE_SHOP_PRICEH	(9 * _2X)	//그 아래 값표
#define STAGE_SHOP_BTNW		(96 * _2X)	//전투 버튼 너비. 원본 그림이 192 다
#define STAGE_SHOP_BTNH		(STAGE_SHOP_BTNW * 62 / 192)
#define STAGE_SHOP_SIDEW	(44 * _2X)	//지도 / 도감 칸 너비

//돌아가는 시간. 칸마다 조금씩 늦게 멈춘다 - 넷이 동시에 서면
//무엇이 걸렸는지 눈이 못 따라간다.
#define STAGE_ROULETTE_FRAME	(FPS * 2 / 3)
#define STAGE_ROULETTE_STAGGER	(FPS / 5)
#define STAGE_ROULETTE_TICK		3		//돌아가는 동안 그림이 바뀌는 간격
#define STAGE_REROLL_GOLD		10		//다시 뽑는 값

//바닥 메뉴는 전투 중에 그리지 않는다. 그 자리를 비워 두면 화면 아래가
//검은 띠로 남으므로, 판을 화면 맨 아래(0)에 붙인다.
//======================================================================
// 전투가 붙으면 아래가 내려간다
//
// 싸우는 동안에는 고를 것이 없다. 격자와 상점 줄을 화면 밖으로 내리고,
// 전투 장면도 조금 내려 위쪽을 비운다. 그 빈자리에 적의 가방이 뜬다.
//
// 룰렛이 열리면(한 마리 눕혔다) 도로 올라온다.
//======================================================================
#define STAGE_UI_SLIDE_SPEED	0.14f	//한 프레임에 좁히는 몫
#define STAGE_UI_DROP_RATE		0.60f	//아래 UI 가 내려가는 거리(화면 몫)
#define STAGE_SCENE_DROP_RATE	0.16f	//전투 장면이 내려가는 거리

static float gStageUiSlide = 0.0f;		//0 이면 보인다, 1 이면 다 내려갔다

//이번 프레임의 자리. 그리는 쪽과 재는 쪽이 같은 값을 써야 한다.
static int StageUiDrop(void)	{ return (int)(gStageUiSlide * DY * STAGE_UI_DROP_RATE); }
static int StageSceneDrop(void)	{ return (int)(gStageUiSlide * DY * STAGE_SCENE_DROP_RATE); }

//싸우는 중인가. 룰렛이 열려 있으면 고르는 중이라 아니다.
static bool StageUiHidden(void)
{
	return IsStageRealtime() && StageRtAutoOn() && !GridTestOfferOpen();
}

static void StageUiSlideStep(void)
{
	const float target = StageUiHidden() ? 1.0f : 0.0f;

	gStageUiSlide += (target - gStageUiSlide) * STAGE_UI_SLIDE_SPEED;

	if (gStageUiSlide < 0.002f) gStageUiSlide = 0.0f;
	if (gStageUiSlide > 0.998f) gStageUiSlide = 1.0f;
}

static int StageShopBtnTop(void)	{ return 4 * _2X + STAGE_SHOP_BTNH - StageUiDrop(); }
static int StageShopGoldTop(void)	{ return StageShopBtnTop() + 14 * _2X; }
static int StageShopPctTop(void)	{ return StageShopGoldTop() + 9 * _2X; }
static int StageShopSlotTop(void)	{ return StageShopPctTop() + 4 * _2X + STAGE_SHOP_CARDH + STAGE_SHOP_PRICEH; }
static int StageShopTop(void)		{ return StageShopSlotTop() + 4 * _2X; }

//내려가기 전, 상점 줄이 다 보일 때의 윗변. 격자는 이 자리에서 시작해
//상점이 빠진 만큼 아래로 내려온다.
static int StageShopTopBase(void)	{ return StageShopTop() + StageUiDrop(); }

//격자가 내려앉는 거리. 싸우는 동안 격자는 사라지지 않는다 - 무엇을 끼고
//싸우는지는 싸우는 내내 보여야 한다. 상점 줄이 비운 자리로 내려올 뿐이다.
static int StageGridDrop(void)
{
	return (int)(gStageUiSlide * (StageShopTopBase() - 4 * _2X));
}

static void GridTestLayout(void)
{
	GridLoadCells(robin.castle);
	//칸은 한 변 24 * _2X 까지 키운다. 12 * _2X 에서는 칸이 손가락보다 작아
	//끌어다 놓기가 어려웠다. 가장 넓은 성(12칸)이 화면 폭 안에 들어오는 것이
	//상한이다 - 그보다 크게 잡으면 폭에 맞춘 값이 대신 걸린다.
	//---- 칸 크기 ----
	//
	//폭과 높이 둘 다에 맞춘다. 폭만 보고 잡으면 줄이 많은 성에서 격자가
	//전투 화면을 밀어 올려 히어로가 화면 밖으로 나간다. 격자에 내주는
	//높이는 화면의 GRIDTEST_MAXRATE 까지다.
	const int roomH = (int)(DY * GRIDTEST_MAXRATE) + GRIDTEST_EXTRAH - GRIDTEST_HUDH;
	const int fitH = Max(1, roomH / Max(1, gGridH));

	gGridCell = Max(10 * _2X,
		Min(Min(24 * _2X, (DX - 24 * _2X) / kGridMaxW), fitH)) & ~1;
	gGridX = DX / 2 - gGridCell * gGridW / 2;
	gGridBottom = StageShopTopBase() - StageGridDrop();
}

int GetStageInventoryTop(void)
{
	GridTestLayout();

	//전투 장면이 딛는 줄이다. 격자가 내려앉으면 장면도 같이 내려와
	//위쪽이 빈다 - 그 자리에 적의 가방이 뜬다.
	return gGridBottom + gGridH * gGridCell + GRIDTEST_HUDH;
}

float GetStageWorldLift(void)
{
	// Preparation uses the tall inventory. Keep the complete battlefield 144
	// screen pixels higher, then return smoothly as the UI slides away.
	return (1.0f - gStageUiSlide) * 72.0f * _2X;
}

static inline int GridCellX(int col) { return gGridX + col * gGridCell; }
//그리기 좌표는 사각형의 윗변이다. row 0 이 맨 아랫줄이므로 한 칸 올린다.
static inline int GridCellY(int row) { return gGridBottom + (row + 1) * gGridCell; }
//격자 전체의 윗변.
static inline int GridTopY(void) { return gGridBottom + gGridH * gGridCell; }

//---- 내림 나눗셈 ----
//
// C 의 / 는 음수에서 0 쪽으로 자른다. -0.7 칸이 -1 이 아니라 0 이 된다.
// 칸 번호를 그렇게 구하면 격자 왼쪽이나 위쪽 바깥에 놓은 것이 첫 열,
// 첫 행에 붙는다. 실제로 상점 카드를 격자 옆 허공에 떨어뜨렸는데
// 0 번 칸에 들어가면서 골드까지 빠져나갔다.
//
// 밖은 밖으로 나와야 아래의 col >= 0 검사가 제 일을 한다.
static inline int GridFloorDiv(int a, int b)
{
	return (a >= 0) ? (a / b) : -(((-a) + b - 1) / b);
}

//휴지통 자리. 격자 위 한 줄의 오른쪽 끝이다.
//
//격자가 화면 폭을 거의 다 쓰므로 옆에는 자리가 없다. 위 한 줄에
//연참 미리보기와 나란히 앉힌다.
static void GridTrashRect(int* x, int* y, int* w, int* h)
{
	*w = 30 * _2X;
	*h = 16 * _2X;
	*x = DX - *w - 6 * _2X;
	*y = GridTopY() + GRIDTEST_HUDH - 2 * _2X;
}

//---- 전투가 끝나고 내미는 세 갈래 ----
//
//격자 위에 뜬다. 한 판에 한 번, 셋 중 하나를 골라 격자에 놓으면
//닫힌다. 열 칸짜리 상점 줄을 없애고 이것으로 바꾼 것은, 아무 때나
//살 수 있으면 "무엇을 포기할까"가 사라지기 때문이다.
static void GridOfferRect(int n, int* x, int* y, int* w, int* h)
{
	const int cw = (DX - STAGE_SHOP_GAP * (GRIDTEST_OFFERCNT + 1)) / GRIDTEST_OFFERCNT;

	*w = cw;
	*h = STAGE_SHOP_CARDH;
	*x = STAGE_SHOP_GAP + n * (cw + STAGE_SHOP_GAP);
	*y = StageShopSlotTop();
}

//맨 아래 가운데. 전투 / 전투 시작 버튼이 앉는 자리다.
//Func_Battle 의 StageRtDrawButton 이 같은 자리를 쓴다.
void StageShopBtnRect(int* x, int* y, int* w, int* h)
{
	*w = STAGE_SHOP_BTNW;
	*h = STAGE_SHOP_BTNH;
	*x = DX / 2 - *w / 2;
	*y = StageShopBtnTop();
}

static void GridTestSay(const char* msg)
{
	strncpy(gGridMsg, msg, sizeof(gGridMsg) - 1);
	gGridMsg[sizeof(gGridMsg) - 1] = 0;
	gGridMsgFrame = FPS * 2;
}

//======================================================================
// 적의 가방
//
// 몬스터도 장비를 낀다. 무엇을 끼고 있는지 보여야 "저놈이 왜 세게 치는가"
// 를 알 수 있다. 싸우는 동안 화면 위쪽에 뜬다.
//
// 표를 따로 두지 않고 몬스터 종류와 판 수로 정한다. 같은 놈은 늘 같은
// 것을 낀다 - 매번 달라지면 외울 수가 없다.
//======================================================================
#define STAGE_FOE_INVEN_W	6
#define STAGE_FOE_INVEN_H	2
#define STAGE_FOE_INVEN_MAX	FOEGEAR_BAGMAX

static void GridTestDrawCard(const GridPart* p, int x, int y, int w, int h, int alpha);

//---- 몬스터 장비 목록 ----
//
//표(FoeGearData.h)에 적힌 놈은 표대로, 없는 놈은 종류와 판으로 굴려서
//정한다. 굴림도 같은 놈, 같은 판이면 늘 같은 결과다.
//
//out[0] 이 장착 무기다(gear = true). 제 공격 모션으로 친다. 나머지는
//가방이고, 그중 검은 날아가서 친다.
static int StageFoeTier(int obj);

//---- 가방 장비의 스탯 ----
//
//RefreshStat 이 장착 칸(equip[])만 본다. 이 판의 장비는 가방에 여러 점이
//놓이므로, 그 뒤에 여기서 한 점씩 더한다. 옵션을 읽는 자리는
//RefreshStat 과 같은 표(optionStat)다 - 두 곳이 다른 표를 보면 같은
//장비가 히어로와 몬스터에게 다르게 붙는다.
static void StageGearAddItem(OBJECT* pObj, const ITEM* it)
{
	if (it->type == EMPTY)
		return;

	//값 자체는 부위에 따라 갈라 붙인다.
	if (it->type == ITEM_SWORD)
		pObj->ps[PS_DMG] += it->value;
	else
		pObj->ps[PS_ARMOR] += it->value;

	for (int j = 0; j < TOTALOPTION; j++) {
		const int* tPtr = &it->option[j][0];

		if (*tPtr == EMPTYINT)
			continue;

		if (optionStat[*tPtr] >= 0)
			pObj->ps[optionStat[*tPtr]] +=
				(*tPtr >= SUFFIX_HPDECREASE) ? -*(tPtr + 1) : *(tPtr + 1);
	}
}

//누구든 제 가방의 장비 스탯을 더한다. RefreshStat 뒤에 부른다.
void StageGearApplyStat(OBJECT* pObj)
{
	const int obj = GetObjFromPtr(pObj);

	if (obj < 0 || !IsStageRealtime())
		return;

	//히어로는 격자에 놓인 것이 그대로 가방이다.
	if (obj == PLAYER) {
		for (int i = 0; i < GRIDTEST_MAXITEM; i++) {
			//장착 칸의 장비는 RefreshStat 이 이미 더했다. 두 번 더하면
			//끼고 들어온 장비만 두 배가 된다.
			if (gGridItem[i].used == false || gGridItem[i].equip >= 0)
				continue;

			StageGearAddItem(pObj, &gGridItem[i].item);
		}

		return;
	}

	//동료와 몬스터는 표에서 읽은 것으로 그 자리에서 만든다.
	StageSword gear[FOEGEAR_BAGMAX + 1];
	const int cnt = StageGearList(obj, gear, FOEGEAR_BAGMAX + 1);

	for (int i = 0; i < cnt; i++) {
		const GridPart* p = &kShopPart[gear[i].part];
		ITEM made;

		//등급과 레벨은 등장 시점의 난이도로 오른 값이다. 표에 적힌 것은
		//"무엇을 끼는가" 뿐이다.
		MakeItem(&made, p->type, Max(1, StageFoeTier(obj) + 1),
			gear[i].grade, p->detail, EMPTY);
		made.value = gear[i].value;
		StageGearAddItem(pObj, &made);
	}
}

//지금 서 있는 몬스터의 장비. 적 가방을 그릴 때 쓴다.
int StageFoeGearList(StageSword* out, int max)
{
	return StageGearList(StageRtFoe(), out, max);
}

//---- 방어구 ----
//
//검이 아닌 장비의 값을 더한 것이다. 이 값이 클수록 덜 맞는다. 히어로도
//동료도 몬스터도 같은 자로 잰다.
long long StageGearArmor(int obj)
{
	StageSword gear[GRIDTEST_MAXITEM];
	const int cnt = StageGearList(obj, gear, GRIDTEST_MAXITEM);
	long long sum = 0;

	for (int i = 0; i < cnt; i++)
		if (!kShopPartIsSword(gear[i].part))
			sum += kShopPart[gear[i].part].price;

	return sum;
}

//방어구를 거친 피해. STAGE_ARMOR_SOFT 만큼 쌓일 때마다 절반씩 줄어든다.
long long StageGearReduce(int obj, long long damage)
{
	const long long armor = StageGearArmor(obj);

	if (armor <= 0 || damage <= 0)
		return damage;

	return Max(1LL, damage * STAGE_ARMOR_SOFT / (STAGE_ARMOR_SOFT + armor));
}

//상점 표의 그 번호가 검인가. 검만 날아간다.
bool kShopPartIsSword(int part)
{
	return part >= 0 && part < GRIDTEST_SHOPCNT
		&& kShopPart[part].type == ITEM_SWORD;
}

//======================================================================
// 같은 몬스터, 뒤에 나오면 더 센 장비
//
// 몬스터 하나가 판을 건너 여러 번 나온다. 표에는 "무엇을 끼는가"만
// 적고, 실제로 어떤 등급의 무엇을 끼는지는 나오는 그 순간에 정한다.
//
// 난이도 = 판 수 + 몬스터 등급(별) + 이번 판에서 몇 번째로 나왔는가.
// 뒤로 갈수록 검은 사다리를 타고 오르고, 등급도 같이 오른다. 그래서
// 적의 가방을 열어 보면 "이놈은 아까 그놈이 아니다" 가 보인다.
//======================================================================
#define STAGE_FOE_SWORD_STEP	3	//난이도 이만큼마다 검이 한 단 오른다
#define STAGE_FOE_GRADE_STEP	4	//난이도 이만큼마다 등급이 한 단 오른다
#define STAGE_FOE_VALUE_PCT		15	//난이도 한 단마다 오르는 값의 몫

//검 사다리. 앞에서 뒤로 갈수록 좋은 검이다(kShopPart 번호).
static const int kFoeSwordLadder[] = { 0, 1, 2, 3 };
enum { FOESWORDLADDERCNT = (int)(sizeof(kFoeSwordLadder) / sizeof(kFoeSwordLadder[0])) };

//이 몬스터가 지금 얼마나 센 자리에 서 있는가.
static int StageFoeTier(int obj)
{
	if (obj < 0 || obj >= TOTALOBJECT)
		return 0;

	const int type = ao[obj].type;
	const int star = enemyData[type * ENEMYDATASIZE + ENEMYDATA_STAR];

	//이번 판에서 몇 마리째인가도 센다. 같은 판 안에서도 뒤에 나오는 놈이
	//조금씩 세진다 - 열다섯 마리가 다 같으면 판이 늘어진다.
	return robin.stage + Max(0, star) + arenaKill / 5;
}

//사다리를 타고 오른 장비 번호.
static int StageFoePartAt(int part, int tier)
{
	if (!kShopPartIsSword(part))
		return part;

	//검은 사다리를 탄다. 표에 적힌 검이 사다리의 몇 단인지 찾아, 거기서
	//난이도만큼 올라간다.
	int at = 0;

	for (int i = 0; i < FOESWORDLADDERCNT; i++)
		if (kFoeSwordLadder[i] == part) {
			at = i;
			break;
		}

	at = Min(FOESWORDLADDERCNT - 1, at + tier / STAGE_FOE_SWORD_STEP);
	return kFoeSwordLadder[at];
}

//난이도로 오른 등급.
static int StageFoeGradeAt(int part, int tier)
{
	const int base = (part >= 0 && part < GRIDTEST_SHOPCNT)
		? kShopPart[part].grade : GRADE_NORMAL;

	return Min(TOTALGRADE - 1, base + tier / STAGE_FOE_GRADE_STEP);
}

//난이도로 오른 값.
static int StageFoeValueAt(int part, int tier)
{
	const int base = (part >= 0 && part < GRIDTEST_SHOPCNT)
		? kShopPart[part].price : 0;

	return base * (100 + tier * STAGE_FOE_VALUE_PCT) / 100;
}

//장비 한 점을 난이도에 맞춰 채운다.
static void StageFoeFill(StageSword* out, int part, int tier, bool gear, int slot)
{
	const int up = StageFoePartAt(part, tier);

	out->slot = slot;
	out->part = up;
	out->detail = kShopPart[up].detail;
	out->value = StageFoeValueAt(up, tier);
	out->grade = StageFoeGradeAt(up, tier);
	out->gear = gear;
}

//---- 누구의 장비든 같은 자리에서 읽는다 ----
//
//히어로는 성의 격자가 곧 가방이다. 동료와 몬스터는 표(FoeGearData.h)를
//본다 - 동료도 몬스터 종류라 같은 표로 찾는다. 표에 없으면 종류와 판으로
//굴린다.
int StageGearList(int obj, StageSword* out, int max)
{
	if (obj < 0 || obj >= TOTALOBJECT || max <= 0)
		return 0;

	if (obj == PLAYER)
		return GridTestSwords(out, max);

	if (!ao[obj].active)
		return 0;

	const int type = ao[obj].type;
	const int tier = StageFoeTier(obj);
	int n = 0;
	int row = -1;

	for (int i = 0; i < FOEGEARROWCNT; i++)
		if (foeGearRow[i].type == type) {
			row = i;
			break;
		}

	//표에 적힌 장비를 그대로 넣는다.
	if (row >= 0) {
		const FoeGearRow* g = &foeGearRow[row];

		if (g->equip >= 0 && g->equip < GRIDTEST_SHOPCNT && n < max) {
			StageFoeFill(&out[n], g->equip, tier, true, n);
			n++;
		}

		for (int i = 0; i < FOEGEAR_BAGMAX && n < max; i++) {
			if (g->bag[i] < 0 || g->bag[i] >= GRIDTEST_SHOPCNT)
				continue;

			StageFoeFill(&out[n], g->bag[i], tier, false, n);
			n++;
		}

		return n;
	}

	//표에 없는 놈. 종류와 판으로 굴린다.
	//동료든 몬스터든 같은 식이다.
	unsigned int seed = (unsigned int)(type * 2654435761u + robin.stage * 40503u);
	const int cnt = Min(max, 1 + (robin.stage + type) % STAGE_FOE_INVEN_MAX);

	for (int i = 0; i < cnt; i++) {
		seed = seed * 1103515245u + 12345u;

		StageFoeFill(&out[n], (int)((seed >> 16) % GRIDTEST_SHOPCNT), tier, i == 0, n);
		n++;
	}

	return n;
}

//적의 가방을 화면 위쪽에 그린다. alpha 0 이면 아무것도 안 한다.
static void StageFoeInvenDraw(int alpha)
{
	StageSword gear[STAGE_FOE_INVEN_MAX + 1];
	int i;

	if (alpha <= 0)
		return;

	const int foe = StageRtFoe();

	if (foe < 0 || !ao[foe].active || ao[foe].dead)
		return;

	const int cell = 20 * _2X;
	const int w = STAGE_FOE_INVEN_W * cell;
	const int h = STAGE_FOE_INVEN_H * cell;
	const int x = DX / 2 - w / 2;
	const int y = DY - 46 * _2X;	//리본 아래

	SetAlpha(alpha / 2);
	MemRect(x - 3 * _2X, y + 3 * _2X, w + 6 * _2X, h + 6 * _2X, 0x14121F);
	SetAlpha(alpha);
	MemRectFrame(x - 3 * _2X, y + 3 * _2X, w + 6 * _2X, h + 6 * _2X, 0x77404A);

	for (int r = 0; r < STAGE_FOE_INVEN_H; r++)
		for (int c = 0; c < STAGE_FOE_INVEN_W; c++)
			MemRectFrame(x + c * cell, y - r * cell, cell, cell, 0x33314A);

	const int cnt = StageFoeGearList(gear, STAGE_FOE_INVEN_MAX + 1);

	for (i = 0; i < cnt; i++) {
		GridPart shown = kShopPart[gear[i].part];
		const GridPart* p = &shown;

		//등급이 올랐으면 테두리 색도 같이 오른다. 열어 보면 "이놈은 아까
		//그놈이 아니다" 가 색으로 먼저 보여야 한다.
		shown.grade = gear[i].grade;

		const int cw = Min(STAGE_FOE_INVEN_W, p->w) * cell;
		const int ch = Min(STAGE_FOE_INVEN_H, p->h) * cell;
		const int cx = x + (i % 3) * 2 * cell;
		const int cy = y - (i / 3) * cell;

		GridTestDrawCard(p, cx, cy, cw, ch, alpha);
	}

	SetFontColor(COLOR_GREY);
	CenterTextStrSolid("적의 장비", DX / 2, y + 3 * _2X + 12 * _2X, 0.46f);
}

//---- 룰렛 칸 아래 값표 ----
//
//값을 카드 안에 적으면 그림이 가려진다. 카드 밑에 띠로 따로 붙인다.
//price 가 음수면 아직 값이 없는 칸(잠김 또는 회전 중)이다.
static void GridShopPriceStrip(int n, int price, bool afford)
{
	char str[32];
	int x, y, w, h;

	GridOfferRect(n, &x, &y, &w, &h);
	y -= h;
	h = STAGE_SHOP_PRICEH;

	MemRect(x, y, w, h, price < 0 ? 0x16161F : (afford ? 0x2C2A18 : 0x241A1A));
	MemRectFrame(x, y, w, h, price < 0 ? 0x3A3F5A : (afford ? 0xC9A227 : 0x77404A));
	SetFontColor(price < 0 ? COLOR_GREY : (afford ? COLOR_WHITE : COLOR_GREY));

	if (price < 0)
		CenterTextStrSolid("-", x + w / 2, y - h + 3 * _2X, 0.5f);
	else {
		sprintf(str, "%d", price);
		CenterTextStrSolid(str, x + w / 2, y - h + 3 * _2X, 0.5f);
	}
}

//======================================================================
// 격자 장비의 스탯
//
// 칸에 놓인 것은 게임의 ITEM 그대로다. 옵션도 소켓도 붙는다. 레벨은
// 같은 장비가 겹친 횟수이고, 겹칠수록 값이 오른다.
//
// STAGE_GEAR_EVOLVE 만큼 겹치면 한 등급 오른다(진화). 그때 레벨은 1 로
// 돌아간다 - 같은 것을 계속 먹이면 언젠가 전설이 된다.
//======================================================================
#define STAGE_GEAR_LVUP_PCT	25	//레벨 하나마다 오르는 값의 몫(백분율)
#define STAGE_GEAR_EVOLVE	5	//이만큼 겹치면 한 등급 오른다

//칸 하나의 진짜 장비를 만든다. 판이 오를수록 좋은 것이 나온다.
static void GridMakeItem(GridSlot* s)
{
	const GridPart* p = &s->part;
	const int lv = Max(1, robin.stage + 1);

	MakeItem(&s->item, p->type, lv, p->grade, p->detail, EMPTY);
	s->level = 1;
}

//겹친 만큼 값을 올린다. 옵션은 그대로 두고 값만 키운다 - 옵션까지
//불리면 같은 장비를 모으는 것이 다른 모든 길을 덮는다.
static void GridApplyLevel(GridSlot* s)
{
	if (s->level <= 1)
		return;

	const int mod = 100 + (s->level - 1) * STAGE_GEAR_LVUP_PCT;

	s->item.value = (int)((long long)s->item.value * mod / 100);
}

//같은 장비가 이미 격자에 있으면 그 칸 번호를 돌려준다. 없으면 -1.
static int GridFindSame(const GridPart* p, int skip)
{
	for (int i = 0; i < GRIDTEST_MAXITEM; i++) {
		if (i == skip || gGridItem[i].used == false)
			continue;

		const GridPart* q = &gGridItem[i].part;

		if (q->type == p->type && q->detail == p->detail && q->grade == p->grade)
			return i;
	}

	return -1;
}

//같은 것을 하나 더 얻었다. 레벨을 올리고, 다 차면 한 등급 올린다.
static void GridStackItem(int at)
{
	GridSlot* s = &gGridItem[at];

	s->level++;

	if (s->level > STAGE_GEAR_EVOLVE && s->part.grade < TOTALGRADE - 1) {
		//진화. 한 등급 위로 다시 만든다.
		s->part.grade++;
		GridMakeItem(s);
	}

	GridApplyLevel(s);
}

//---- 놓을 수 있는가 ----
//
// 세 가지를 본다. 격자 밖으로 나가는가, 성 모양 밖의 빈 칸을 밟는가,
// 이미 다른 것이 있는가.
//
// skip 은 "이 번호는 없는 셈 친다"는 뜻이다. 이미 놓여 있던 것을 집어
// 옮길 때 제 몸에 걸려서 못 놓는 일을 막는다.
static bool GridTestCanPlace(const GridPart* p, int col, int row, int skip)
{
	int i, cx, cy;

	if (p == nullptr || p->w <= 0 || p->h <= 0)
		return false;

	if (col < 0 || row < 0 || col + p->w > gGridW || row + p->h > gGridH)
		return false;

	for (cy = row; cy < row + p->h; cy++) {
		for (cx = col; cx < col + p->w; cx++) {
			if (GridMaskAt(cx, cy) == false)
				return false;
		}
	}

	for (i = 0; i < GRIDTEST_MAXITEM; i++) {
		if (gGridItem[i].used == false || i == skip)
			continue;

		const GridPart* o = &gGridItem[i].part;

		if (col < gGridItem[i].col + o->w && gGridItem[i].col < col + p->w &&
			row < gGridItem[i].row + o->h && gGridItem[i].row < row + p->h)
			return false;
	}

	return true;
}

//빈 칸을 찾는다. 없으면 -1.
static int GridTestFreeSlot(void)
{
	int i;

	for (i = 0; i < GRIDTEST_MAXITEM; i++) {
		if (gGridItem[i].used == false)
			return i;
	}

	return -1;
}

//카드 한 장을 그린다. 액자를 깔고 그 위에 아이콘을 얹는다.
//
//검은 전투와 같은 세로 스프라이트를 칸 규격에 맞춰 그린다.
//다른 장비는 기존 아이콘을 사용한다.
static void GridTestDrawCard(const GridPart* p, int x, int y, int w, int h, int alpha)
{
	const int col = kGradeColor[Min(TOTALGRADE - 1, Max(0, p->grade))];

	SetAlpha(alpha);
	MemRect(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * _2X, 0x1B1B2E);
	MemRectFrame(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * _2X, col);
	SetAlpha(ALPHA_MAX);

	if (p->type == ITEM_SWORD) {
		const bool drawn = p->rot
			? DrawSwordInBoxRot(p->detail, x + _2X, y - _2X, w - 2 * _2X, h - 2 * _2X, alpha)
			: DrawSwordInBox(p->detail, x + _2X, y - _2X, w - 2 * _2X, h - 2 * _2X, alpha);

		if (drawn)
			return;
	}

	if (p->type == ITEM_GREAVES || p->type == ITEM_SHOES || p->type == ITEM_BOOTS) {
		const bool drawn = p->rot
			? DrawBootsInBoxRot(p->type, p->detail, x + _2X, y - _2X, w - 2 * _2X, h - 2 * _2X, alpha)
			: DrawBootsInBox(p->type, p->detail, x + _2X, y - _2X, w - 2 * _2X, h - 2 * _2X, alpha);

		if (drawn)
			return;
	}

	if (p->type == ITEM_KILT || p->type == ITEM_SKIRT || p->type == ITEM_PANTS) {
		if (DrawPantsInBox(p->type, p->detail, x + _2X, y - _2X, w - 2 * _2X, h - 2 * _2X, alpha))
			return;
	}

	if (p->type == ITEM_GUNTLET || p->type == ITEM_ARMLET || p->type == ITEM_GLOVE) {
		if (DrawGloveInBox(p->type, p->detail, x + _2X, y - _2X, w - 2 * _2X, h - 2 * _2X, alpha))
			return;
	}

	if (p->type == ITEM_ARMOR || p->type == ITEM_VEST) {
		if (DrawArmorInBox(p->type, p->detail, x + _2X, y - _2X, w - 2 * _2X, h - 2 * _2X, alpha))
			return;
	}

	//아이콘은 카드 한가운데. DrawIcon 의 x, y 는 왼쪽 위다.
	DrawIcon(GetItemIcon(p->type, p->detail, p->grade),
		x + w / 2 - ITEMICONSIZE / 2,
		y - h / 2 + ITEMICONSIZE / 2,
		1.0f, false, false, false, true);
}

//---- 쿨타임 ----
//
//검은 칠 준비가 될 때까지 어둡게 가라앉아 있다가, 아래에서부터 밝아지며
//차오른다(템빨용사와 같다). 다 차면 한 번 번쩍이고, 그 번쩍임이 끝나는
//순간 공격이 나간다(Func_Battle 의 스테이지 실시간 전투).
//
//그리기 좌표는 윗변이고 사각형은 아래로 뻗는다. 밝은 쪽이 아래이므로
//어두운 덮개는 윗변에서부터 남은 높이만큼 깐다.
static void GridDrawCharge(int x, int y, int w, int h, float charge, int flash)
{
	const float c = Max(0.0f, Min(1.0f, charge));
	const int dark = h - (int)(h * c);

	if (dark > 0) {
		SetAlpha(18);
		MemRect(x, y, w, dark, 0x000000);
		SetAlpha(ALPHA_MAX);
	}

	if (flash > 0) {
		SetAlpha(Min(28, 8 + flash * 4));
		MemRect(x, y, w, h, 0xFFFFFF);
		SetAlpha(ALPHA_MAX);
	}
}

//---- 검 미리보기 ----
//
// [무엇을 보여주는가]
// 격자에 놓인 검을 늘어놓고, 저마다 몇 초마다 치는지를 적는다.
//
// [검은 저마다 따로 친다]
// 템빨용사와 같은 구조다. 장착 무기와 가방에 넣은 무기가 각자 제
// 쿨타임으로 공격한다. 여기서도 장착 검(히어로의 휘두름)과 격자의 검이
// 서로 기다리지 않는다(Func_Battle 의 스테이지 실시간 전투).
//
// 한 자루가 한 대씩 그 검의 값만큼 넣으므로 검을 모을수록 총량이 는다.
// 격자가 좁아서 검만 쌓을 수 없다는 것이 그 대가다.
//
// [빠르기는 길이에서 온다]
// 긴 검일수록 늦게 친다(StageSwordCooldown). 칸을 많이 먹는 대검은 한 방이
// 무겁고 드물게, 짧은 검은 가볍고 자주 나간다.
//
// [늘어놓는 순서는 약 -> 강]
// 칸이 모자라 다 못 그리면 약한 쪽을 뺀다. 좋은 검이 그림에서 빠지면
// 격자에 무엇이 있는지 잘못 읽힌다.
static void GridTestDrawCombo(int topY)
{
	char str[96];
	int i, j, n = 0;
	int sword[GRIDTEST_MAXITEM];

	//격자에서 검만 걷는다.
	for (i = 0; i < GRIDTEST_MAXITEM; i++) {
		if (gGridItem[i].used == false)
			continue;

		if (gGridItem[i].part.type != ITEM_SWORD)
			continue;

		sword[n++] = i;
	}

	SetFontColor(COLOR_WHITE);

	if (n == 0) {
		SetFontColor(COLOR_GREY);
		CenterTextStrSolid("격자에 검을 놓으면 연참이 생긴다",
			DX / 2, topY, 0.7f);
		return;
	}

	//약한 것부터. detail 이 클수록 좋은 검이다.
	//자루가 많아야 열 몇 개라 단순 삽입정렬로 충분하다.
	for (i = 1; i < n; i++) {
		const int key = sword[i];

		for (j = i - 1;
			j >= 0 && gGridItem[sword[j]].part.detail > gGridItem[key].part.detail;
			j--)
			sword[j + 1] = sword[j];

		sword[j + 1] = key;
	}

	//다 치면 한 번의 공격 슬롯을 넘긴다. 넘치는 자루는 위력으로만 간다.
	//
	//★ 넘칠 때 잘라내는 것은 "약한 쪽"이다. 정렬이 약 -> 강 이므로 앞에서
	//끊으면 제일 좋은 검이 연참에서 빠진다. 실제로 그렇게 짰다가 여섯
	//자루를 놓았을 때 엑스칼리버가 "나머지"로 밀려나는 것을 보고 잡았다.
	//
	//뒤에서 hit 개를 쓰고, 그 안에서는 여전히 약 -> 강 이라 마무리가
	//가장 좋은 검이다.
	const int hit = Min(n, (int)GRIDTEST_MAXCOMBO);
	const int from = n - hit;

	//왼쪽에서 오른쪽으로. 뒤로 갈수록 좋은 검이다.
	const int cw = 52 * _2X;
	const int ch = 40 * _2X;
	const int startX = DX / 2 - cw * hit / 2;
	const int cardY = topY - 12 * _2X;

	for (i = 0; i < hit; i++) {
		const GridPart* p = &gGridItem[sword[from + i]].part;
		const int x = startX + i * cw;
		const int trail = GridSwordTrail(p->detail);

		SetAlpha(22);
		MemRect(x + 2 * _2X, cardY, cw - 4 * _2X, ch, 0x1B1B2E);
		SetAlpha(ALPHA_MAX);
		MemRectFrame(x + 2 * _2X, cardY, cw - 4 * _2X, ch, kGradeColor[p->grade]);


		DrawIcon(GetItemIcon(p->type, p->detail, p->grade),
			x + cw / 2 - ITEMICONSIZE / 2, cardY - 3 * _2X,
			1.0f, false, false, false, true);

		//잔상 색. 검의 성격이 한 줄로 보인다.
		MemRect(x + 6 * _2X, cardY - ch + 14 * _2X, cw - 12 * _2X, 2 * _2X, trail);

		//크기와 빠르기. 몇 초마다 치는지가 그 검의 성격이다.
		SetFontColor(COLOR_WHITE);
		sprintf(str, "%dx%d %.1f초", p->w, p->h,
			StageSwordCooldown(p->detail) / (float)FPS);
		CenterTextStrSolid(str, x + cw / 2, cardY - ch + 10 * _2X, 0.45f);
	}

	//넘치는 자루.
	if (n > hit) {
		SetFontColor(COLOR_GREY);
		sprintf(str, "약한 %d자루는 그림에서만 뺐다", n - hit);
		CenterTextStrSolid(str, DX / 2, cardY - ch - 4 * _2X, 0.6f);
	}
}

//==========================================================================
// 바깥이 부르는 것들
//==========================================================================

static void GridOfferResume(void);

void GridTestToggle(void)
{
	gGridOpen = !gGridOpen;

	//닫을 때 끌던 것을 놓아 준다. 안 그러면 다시 열었을 때 손에 붙어 있다.
	gGridDragOn = false;
	gGridDragShop = -1;
	gGridDragFrom = -1;

	//---- 접는 순간 뜬 판이 있으면 넘긴 것으로 친다 ----
	//
	//판이 떠 있는 동안 다음 웨이브는 서지 않고 기다린다(Func_Gacha.cpp).
	//그대로 접어 버리면 판을 닫을 손이 없어져서 웨이브가 영영 안 선다.
	//접기는 격자를 치우는 것이지 판을 멈추는 것이 아니다.
	if (gGridOpen == false)
		GridOfferResume();
}

//이 타입이 이미 이번 세 갈래에 나왔는가.
static bool GridOfferHasCrew(const OfferCard* made, int madeCnt, int type)
{
	for (int k = 0; k < madeCnt; ++k) {
		if (made[k].kind != OFFER_PART && made[k].crewType == type)
			return true;
	}

	return false;
}

//---- 동료 카드 ----
//
//편성표(robin.slotCrew)에서 고른다. 아웃게임에서 짠 편성이 이번 판에
//뽑혀 들어오는 몫이다. 이미 선 동료와 이번에 나온 동료는 뺀다.
static int GridPickOwnedCrew(const OfferCard* made, int madeCnt)
{
	int pool[MAXCREW];
	int n = 0;

	for (int s = 0; s < MAXCREW; ++s) {
		const int type = robin.slotCrew[s];

		if (type < 0 || GetCrewIdxFromType(type) < 0)
			continue;

		if (StageRtHasCrew(type) || GridOfferHasCrew(made, madeCnt, type))
			continue;

		pool[n++] = type;
	}

	return (n > 0) ? pool[Random(n)] : -1;
}

//---- 몬스터 카드 ----
//
//방금 눕힌 놈이 먼저다. "잡은 것을 데려온다"가 눈에 보여야 한다.
//
//다만 동료 표(crewData)에 없는 몬스터는 스킬도 총알도 없어서, 데려와도
//서 있기만 한다. 그때는 동료 표에서 하나를 대신 고른다.
static int GridPickMonster(int killedType, const OfferCard* made, int madeCnt)
{
	if (killedType > 0 && GetCrewIdxFromType(killedType) >= 0
		&& !StageRtHasCrew(killedType)
		&& !GridOfferHasCrew(made, madeCnt, killedType))
		return killedType;

	for (int tries = 0; tries < 8 && gTotalCrew > 0; ++tries) {
		const int type = crewData[Random(gTotalCrew) * CREWDATASIZE + CREWDATA_TYPE];

		if (type <= 0 || StageRtHasCrew(type)
			|| GridOfferHasCrew(made, madeCnt, type))
			continue;

		return type;
	}

	return -1;
}

//---- 세 갈래를 새로 뽑는다 ----
//
//동료와 몬스터는 설 자리가 남았을 때만 섞는다. 꽉 찼는데 내밀면 살 수
//없는 카드가 한 장 끼어 세 갈래가 두 갈래가 된다. 뽑을 것이 없으면
//장비로 채운다.
//
//장비도 같은 것이 두 장 나오면 안 된다. 겹치면 다시 뽑는다.
static void GridOfferRoll(int killedType)
{
	int i, j;
	const bool crewRoom = !StageRtCrewFull();

	for (i = 0; i < GRIDTEST_OFFERCNT; i++) {
		OfferCard* c = &gOffer[i];
		const int roll = crewRoom ? Random(100) : 0;

		memset(c, 0, sizeof(OfferCard));
		c->kind = OFFER_PART;

		if (roll >= 100 - kOfferMonsterPct) {
			const int type = GridPickMonster(killedType, gOffer, i);

			if (type >= 0) {
				c->kind = OFFER_MONSTER;
				c->crewType = type;
				c->price = kOfferMonsterPrice;
				continue;
			}
		}
		else if (roll >= 100 - kOfferMonsterPct - kOfferCrewPct) {
			const int type = GridPickOwnedCrew(gOffer, i);

			if (type >= 0) {
				c->kind = OFFER_CREW;
				c->crewType = type;
				c->price = kOfferCrewPrice;
				continue;
			}
		}

		for (;;) {
			c->part = Random(GRIDTEST_SHOPCNT);

			for (j = 0; j < i; j++)
				if (gOffer[j].kind == OFFER_PART && gOffer[j].part == c->part)
					break;

			if (j == i)
				break;
		}

		c->price = kShopPart[c->part].price;
	}

	//칸마다 조금씩 늦게 멈춘다.
	for (i = 0; i < GRIDTEST_OFFERCNT; i++) {
		gOfferSpin[i] = STAGE_ROULETTE_FRAME + i * STAGE_ROULETTE_STAGGER;
		gOfferFace[i] = Random(GRIDTEST_SHOPCNT);
	}

	gOfferOn = true;
}

//돌아가는 중인가. 그동안은 그 칸을 누를 수 없다.
static bool GridOfferSpinning(int n)
{
	return n >= 0 && n < GRIDTEST_OFFERCNT && gOfferSpin[n] > 0;
}

//---- 다시 뽑기 ----
//
//값을 치르고 네 칸을 새로 돌린다. 원하는 것이 없을 때 골드를 쓰는
//길이다. 골드가 모자라면 아무 일도 없다.
void GridTestReroll(void)
{
	if (gOfferOn == false)
		return;

	for (int i = 0; i < GRIDTEST_OFFERCNT; i++)
		if (gOfferSpin[i] > 0)
			return;

	if (robin.gold < STAGE_REROLL_GOLD) {
		PlayMusic(M_ERROR);
		GridTestSay("골드가 모자라다");
		return;
	}

	robin.gold -= STAGE_REROLL_GOLD;
	GridOfferRoll(-1);
}

//지도와 도감. 자리만 잡아 두었다.
void GridTestShopSide(bool book)
{
	GridTestSay(book ? "도감은 아직이다" : "지도는 아직이다");
}

//---- 판을 연다 ----
//
//몬스터를 한 마리 눕힌 자리(Func_Movement 의 VanishMove)에서 부른다.
//killedType 은 눕힌 몬스터다 - 몬스터 카드가 그놈을 데려온다.
//
//판을 열었으면 true 다. 부른 쪽은 그때 다음 몬스터를 세우지 않고 기다린다.
bool GridTestBeginOffer(int killedType)
{
	if (gGridOpen == false)
		return false;

	GridOfferRoll(killedType);

	//---- 고르는 동안 전투를 멈춘다 ----
	//
	//WaveControler() 는 waveStatus 가 PLAY 일 때만 돈다(Func_Map). 눕혀
	//두면 다음 몬스터가 서지 않는다. 손이 둘로 갈라지면 안 된다 - 카드를
	//끄는 중에 몬스터가 때리면 어느 쪽을 봐야 할지 알 수 없다.
	//
	//입력 잠금은 오히려 푼다. 걸어 두면 touchFunc 가 초입에서 돌아가
	//카드가 눌리지도 않는다.
	waveStatus = WAVESTATUS_END;
	waveAnnounceTouchLock = false;
	touchDisable = false;

	return true;
}

//---- 판을 닫고 다음 판을 세운다 ----
//
//Func_Gacha.cpp 가 미뤄 둔 일을 여기서 그대로 한다. 미룬 쪽과 하는 쪽이
//떨어져 있으므로, 저쪽 else 갈래가 바뀌면 여기도 같이 바뀌어야 한다.
static void GridOfferResume(void)
{
	if (gOfferOn == false)
		return;

	gOfferOn = false;
	gGridDragOn = false;
	gGridDragShop = -1;
	gGridDragFrom = -1;

	GridTestAdvanceWave();
}

//---- 다음 몬스터를 세운다 ----
//
//이 줄에 아직 남았으면 그대로 두면 WaveControler 가 이어서 세운다.
//줄을 다 눕혔으면 다음 줄로 넘긴다 - 전에는 상자를 닫는 자리에서
//넘겼는데(Func_Gacha), 상자가 판 끝에만 떨어지게 되면서 줄을 넘길 손이
//여기밖에 남지 않았다.
//
//세 갈래와 따로 떼어 둔 것은, 격자를 접어 두면 판이 안 열리기 때문이다.
//그때도 줄은 넘어가야 한다. 안 그러면 줄을 다 눕힌 자리에서 아무도 서지
//않아 전투가 멈춘다.
void GridTestAdvanceWave(void)
{
	if (robin.curWaveIdx >= GetMaxWaveCnt() && AliveEnemyCnt() == 0) {
		robin.waveIdx++;
		robin.curWaveIdx = 0;
		memset(&robin.waveActive, 0, sizeof(robin.waveActive));

		//등장 조건이 "waveTimeStamp 로부터 몇 초가 지났나" 라서, 안 고치면
		//판을 고르던 시간까지 흘러간 것으로 쳐서 다음 줄이 한꺼번에 튀어
		//나온다.
		robin.waveTimeStamp = MC_knlCurrentTimeStamp();

		bar[BAR_BOSSHP].max = GetTotalWaveHp(robin.waveIdx);
	}

	waveStatus = WAVESTATUS_PLAY;

	//다음 몬스터가 서고 웨이브 타이틀이 끝날 때까지 입력 공백이 없어야
	//한다. 첫 몬스터가 생길 때 Func_Map.cpp 가 이 잠금을 이어받아 푼다.
	waveAnnounceTouchLock = true;
	touchDisable = true;
}

//안 사고 넘긴다. 골드를 아끼는 것도 한 갈래라 넘기는 길이 있어야 한다.
void GridTestSkipOffer(void)
{
	if (gOfferOn == false)
		return;

	GridOfferResume();
	StageRtSetAuto(true);
	// This green start button bypasses StageRtToggleAuto, so clear the
	// cinematic combat zoom on this path too.
	ClearCombatZoom();
	GridTestSay("이번 판은 넘겼다");
}

//---- 동료 / 몬스터 카드를 산다 ----
//
//끌어다 놓을 자리가 없다. 격자가 아니라 히어로 곁에 서기 때문이다.
//그래서 누르는 순간 값을 치르고 세운다.
static void GridOfferBuyCrew(const OfferCard* c)
{
	if (robin.gold < c->price) {
		GridTestSay("골드가 모자란다");
		return;
	}

	//자리가 없으면 값을 받지 않는다. 받고 못 세우면 골드만 사라진다.
	if (StageRtAddCrew(c->crewType) == false) {
		GridTestSay("더 설 자리가 없다");
		return;
	}

	robin.gold -= c->price;

	snprintf(gGridMsg, sizeof(gGridMsg), "%s 합류  -%d",
		textId[TEXT_MONSTERNAME_START + c->crewType], c->price);
	gGridMsgFrame = FPS * 2;

	GridOfferResume();
}

//---- 격자에 놓인 검 ----
//
//검은 저마다 제 쿨타임으로 친다(Func_Battle 의 스테이지 실시간 전투).
//장착 검과 따로 돈다.
//
//값은 아이템을 만들 때 쓰는 표(MakeItemValue)에서 온다. 장착 검과 같은
//자로 재야 둘을 견줄 수 있다.
//
//집어 든 검(끌고 있는 중)은 격자에서 빠진 것으로 친다. 손에 든 동안은
//치지 않는다.
int GridTestSwords(StageSword* out, int maxCnt)
{
	int n = 0;

	for (int i = 0; i < GRIDTEST_MAXITEM && n < maxCnt; ++i) {
		if (gGridItem[i].used == false)
			continue;

		const GridPart* p = &gGridItem[i].part;

		if (p->type != ITEM_SWORD)
			continue;

		out[n].slot = i;
		//칸의 물건이 바뀌었는지 가리는 열쇠. 장비는 장비 칸 번호로 가른다.
		out[n].part = (gGridItem[i].shop >= 0)
			? gGridItem[i].shop : 1000 + gGridItem[i].equip;
		out[n].gear = (gGridItem[i].equip >= 0);
		out[n].detail = p->detail;
		out[n].grade = p->grade;

		//겹쳐서 오른 레벨이 그대로 위력이다. 칸에 든 진짜 ITEM 의 값을
		//쓰면 레벨업과 진화가 바로 전투에 먹힌다.
		out[n].value = Max(1, (gGridItem[i].item.type != EMPTY)
			? gGridItem[i].item.value
			: MakeItemValue(p->type, p->detail, p->grade, 1));
		n++;
	}

	return n;
}

int GridTestTotalItemCount(void)
{
	int cnt = 0;
	for (int i = 0; i < GRIDTEST_MAXITEM; ++i) {
		if (gGridItem[i].used) cnt++;
	}
	return cnt;
}

//---- 판이 새로 시작할 때 ----
//
//뽑은 것은 그 판에서만 산다. 격자와 떠 있던 세 갈래를 비운다.
void GridTestResetStage(void)
{
	memset(gGridItem, 0, sizeof(gGridItem));

	//장착 장비는 다음에 격자를 그릴 때 넣는다. 지금은 히어로가 아직 안
	//섰을 수 있다(START 는 GotoPlay 보다 먼저 이 함수를 부른다).
	gGridGearPending = true;
	gOfferOn = false;
	gGridDragOn = false;
	gGridDragShop = -1;
	gGridDragFrom = -1;
	gGridDragRot = false;
	gGridMsgFrame = 0;
}

bool GridTestIsOpen(void)
{
	return gGridOpen;
}

bool GridTestOfferOpen(void)
{
	return gOfferOn;
}

//격자 위 한 줄(연참 / 골드)의 윗변. 그 위는 전투 버튼과 세 갈래가 쓴다.
//
//격자를 한 번도 안 그렸으면 칸 크기가 0 이다. 그때는 바닥 메뉴 위를 준다.
int GridTestDockTop(void)
{
	if (gGridCell <= 0)
		return BOTTOMMENUHEIGHT + GRIDTEST_HUDH;

	return GridTopY() + GRIDTEST_HUDH;
}

//누르는 순간. fromShop 이면 n 은 세 갈래 중 몇 번째인가, 아니면
//격자에 이미 놓여 있는 것의 번호다.
void GridTestPick(int n, bool fromShop)
{
	if (gGridOpen == false)
		return;

	//눕히기는 끄는 동안 다시 정한다. 앞 끌기의 판정을 이어 쓰지 않는다.
	gGridDragRot = false;

	if (fromShop) {
		if (gOfferOn == false)
			return;

		if (n < 0 || n >= GRIDTEST_OFFERCNT)
			return;

		//돌아가는 칸은 아직 무엇인지 정해지지 않았다.
		if (GridOfferSpinning(n))
			return;

		if (gOffer[n].kind != OFFER_PART) {
			GridOfferBuyCrew(&gOffer[n]);
			return;
		}

		//장비 값은 놓는 순간에 치른다. 집기만 하고 도로 놓을 수 있어야 한다.
		gGridDragOn = true;
		gGridDragDesc = kShopPart[gOffer[n].part];
		gGridDragShop = gOffer[n].part;
		gGridDragFrom = -1;
	}
	else {
		if (n < 0 || n >= GRIDTEST_MAXITEM || gGridItem[n].used == false)
			return;

		gGridDragOn = true;
		gGridDragDesc = gGridItem[n].part;
		gGridDragShop = gGridItem[n].shop;
		gGridDragFrom = n;
		gGridPressX = touchX;
		gGridPressY = touchY;

		//집는 순간 격자에서 뺀다. 그래야 제자리로 도로 놓을 수 있고,
		//놓을 자리 판정에서 제 몸에 걸리지 않는다.
		gGridItem[n].used = false;
	}
}

//손을 뗀 순간. 여기서만 값이 오간다.
void GridTestRelease(void)
{
	int tx, ty, tw, th;

	if (gGridDragOn == false)
		return;

	//---- 제자리에서 누르고 뗐다 - 돌린다 ----
	//
	//격자에 놓인 것을 거의 안 움직이고 떼면 끌기가 아니라 누르기다. 그
	//자리에서 90도 돌린다. 돌린 모양이 그 자리에 안 들어가면 그대로 둔다.
	if (gGridDragFrom >= 0
		&& Abs(touchX - gGridPressX) <= 8 * _2X
		&& Abs(touchY - gGridPressY) <= 8 * _2X) {
		GridSlot* s = &gGridItem[gGridDragFrom];
		const GridPart turned = GridPartRotated(s->part);

		gGridDragOn = false;
		gGridDragShop = -1;
		gGridDragFrom = -1;

		if (GridTestCanPlace(&turned, s->col, s->row, -1))
			s->part = turned;
		else
			GridTestSay("돌릴 자리가 없다");

		s->used = true;
		return;
	}

	//손에 든 것을 먼저 받아 둔다. 아래에서 끌기 상태를 지운다.
	//세운 채로 안 들어가 눕혀 놓기로 정해졌으면 눕힌 것을 놓는다.
	const GridPart held = gGridDragRot
		? GridPartRotated(gGridDragDesc) : gGridDragDesc;
	const int shop = gGridDragShop;
	const int from = gGridDragFrom;
	const GridPart* p = &held;

	gGridDragOn = false;
	gGridDragShop = -1;
	gGridDragFrom = -1;

	//---- 휴지통 ----
	GridTrashRect(&tx, &ty, &tw, &th);

	if (touchX >= tx && touchX <= tx + tw && touchY <= ty && touchY >= ty - th) {
		if (from < 0) {
			//상점에서 집어 바로 버린 것. 산 적이 없으니 줄 돈도 없다.
			GridTestSay("사지 않은 것은 팔 수 없다");
			return;
		}

		//아웃게임 장비는 팔 수 없다. 여기서 팔면 인벤토리의 진짜 장비가
		//사라진다. 제자리로 돌린다.
		if (gGridItem[from].equip >= 0) {
			gGridItem[from].used = true;
			GridTestSay("장착 장비는 팔 수 없다");
			return;
		}

		//판 값은 산 값의 절반이다. 되사기를 반복해 돈을 버는 길을 막는다.
		const int back = p->price / 2;

		robin.gold += back;
		sprintf(gGridMsg, "%s 판매  +%d", p->name, back);
		gGridMsgFrame = FPS * 2;
		return;
	}

	//---- 격자 ----
	if (gGridDragValid && gGridDragCol >= 0 && gGridDragRow >= 0) {
		if (from < 0) {
			if (robin.gold < p->price) {
				//살 수 없다. 소리로도 알린다 - 격자에 놓으려던 손은
				//글자를 읽고 있지 않다.
				PlayMusic(M_ERROR);
				GridTestSay("골드가 모자란다");
				return;
			}

			const int slot = GridTestFreeSlot();

			if (slot < 0) {
				GridTestSay("더 놓을 수 없다");
				return;
			}

			robin.gold -= p->price;

			//---- 같은 것이 이미 있으면 겹친다 ----
			//
			//칸을 또 먹지 않고 그 자리의 장비가 세진다. 자리가 좁은
			//성에서도 같은 것을 계속 사는 길이 열린다.
			const int same = GridFindSame(&held, -1);

			if (same >= 0) {
				GridStackItem(same);
				sprintf(gGridMsg, "%s 겹침 Lv%d  -%d",
					p->name, gGridItem[same].level, p->price);
				gGridMsgFrame = FPS * 2;
				GridOfferResume();
				return;
			}

			gGridItem[slot].used = true;
			gGridItem[slot].part = held;
			gGridItem[slot].shop = shop;
			gGridItem[slot].equip = -1;
			gGridItem[slot].col = gGridDragCol;
			gGridItem[slot].row = gGridDragRow;
			GridMakeItem(&gGridItem[slot]);

			sprintf(gGridMsg, "%s 구입  -%d", p->name, p->price);
			gGridMsgFrame = FPS * 2;

			//한 판에 하나만 산다. 골랐으면 나머지 두 갈래는 사라지고
			//곧바로 다음 판이 선다 - 그래야 고른 것이 고른 값을 한다.
			GridOfferResume();
		}
		else {
			//자리만 옮긴다. 값은 오가지 않는다.
			gGridItem[from].used = true;
			gGridItem[from].part = held;
			gGridItem[from].col = gGridDragCol;
			gGridItem[from].row = gGridDragRow;
		}

		return;
	}

	//---- 어디에도 못 놓았다 ----
	//
	//격자에서 집은 것은 제자리로 돌린다. 집었다가 허공에 놓았다고
	//사라지면 손이 미끄러진 것만으로 장비를 잃는다.
	if (from >= 0) {
		gGridItem[from].used = true;
		GridTestSay("제자리로");
		return;
	}

	//상점에서 집어 격자 밖에 놓은 것. 값은 오가지 않았지만 아무 말도
	//없으면 "샀는데 사라졌나" 싶어진다. 골드 부족과 자리 부족은 이미
	//말해 주는데 여기만 조용했다.
	GridTestSay("격자 안에 놓아야 산다");
}

//장착 장비는 인벤토리의 진짜 ITEM 을 그대로 쓴다.
static void GridSetGearItem(GridSlot* s, const ITEM* it)
{
	s->item = *it;
	s->level = 1;
}

//---- 장착 장비 한 점의 모양 ----
//
//검은 전투 스프라이트의 칸 규격(swordTileSize)을 그대로 쓴다. 상점의 검과
//같은 표라, 같은 검이면 장착했든 샀든 같은 크기다.
//
//나머지는 부위의 생김새로 정한다. 상점의 같은 부위와 같은 크기다.
static void GridGearPart(const ITEM* it, GridPart* out)
{
	const int swordCnt = (int)(sizeof(swordTileSize) / sizeof(swordTileSize[0]) / 2);

	memset(out, 0, sizeof(GridPart));
	out->type = it->type;
	out->detail = it->detail;
	out->grade = it->grade;
	out->price = 0;
	out->name = "장착 장비";
	out->w = 1;
	out->h = 1;

	if (it->type == ITEM_SWORD) {
		if (it->detail >= 0 && it->detail < swordCnt) {
			out->w = swordTileSize[it->detail * 2];
			out->h = swordTileSize[it->detail * 2 + 1];
		}
		return;
	}

	switch (it->type) {
	case ITEM_HELM: case ITEM_HAT: case ITEM_CAP:
		out->w = 2; out->h = 2; break;
	case ITEM_ARMOR: case ITEM_VEST:
		out->w = 2; out->h = (it->detail < 4) ? 2 : 3; break;
	case ITEM_COAT:
		out->w = 2; out->h = 3; break;
	case ITEM_GUNTLET: case ITEM_ARMLET: case ITEM_GLOVE:
		out->w = 2; out->h = 2; break;
	case ITEM_KILT: case ITEM_SKIRT: case ITEM_PANTS:
		out->w = 2; out->h = 2; break;
	case ITEM_GREAVES: case ITEM_SHOES: case ITEM_BOOTS:
		out->w = 1; out->h = 2; break;
	default:
		break;
	}
}

//아래 줄, 왼쪽 칸부터 처음 들어가는 자리를 찾는다.
static bool GridFindSpot(const GridPart* p, int* outCol, int* outRow)
{
	for (int row = 0; row < gGridH; ++row) {
		for (int col = 0; col < gGridW; ++col) {
			if (GridTestCanPlace(p, col, row, -1)) {
				*outCol = col;
				*outRow = row;
				return true;
			}
		}
	}

	return false;
}

//---- 판이 열리면 장착 장비가 가방에 들어간다 ----
//
//템빨용사와 같다. 아웃게임에서 낀 장비는 스탯만 주는 것이 아니라 시작
//아이템으로 가방 칸을 먹는다. 무기는 가방 안에서 제 쿨타임으로 친다.
//
//무기를 먼저, 그다음 넓은 것부터 놓는다. 큰 것을 나중에 두면 자리가 잘게
//쪼개져서 들어갈 곳이 없어진다.
//
//자리가 없어 못 넣은 장비는 이번 판에 가방에 없다. 몇 개인지 알린다 -
//말없이 빠지면 장비가 사라진 것으로 보인다.
static void GridPlaceGear(void)
{
	const OBJECT* hero = &ao[PLAYER];
	int order[TOTALEQUIP];
	GridPart parts[TOTALEQUIP];
	int n = 0;
	int missed = 0;

	gGridGearPending = false;

	for (int e = 0; e < TOTALEQUIP; ++e) {
		if (hero->equip[e].type == EMPTY)
			continue;

		GridGearPart(&hero->equip[e], &parts[e]);
		order[n++] = e;
	}

	for (int i = 1; i < n; ++i) {
		const int key = order[i];
		const bool keyWeapon = (key == EQUIP_WEAPON);
		const int keyArea = parts[key].w * parts[key].h;
		int j = i - 1;

		while (j >= 0) {
			const int o = order[j];
			const bool before = keyWeapon
				|| (o != EQUIP_WEAPON && parts[o].w * parts[o].h < keyArea);

			if (!before)
				break;

			order[j + 1] = o;
			--j;
		}

		order[j + 1] = key;
	}

	for (int k = 0; k < n; ++k) {
		const int e = order[k];
		const int slot = GridTestFreeSlot();
		int col, row;

		if (slot < 0)
			break;

		//세워서 안 들어가면 눕혀 본다. 성보다 긴 검이 여기서 들어간다.
		if (!GridFindSpot(&parts[e], &col, &row)) {
			const GridPart turned = GridPartRotated(parts[e]);

			if (!GridFindSpot(&turned, &col, &row)) {
				missed++;
				continue;
			}

			parts[e] = turned;
		}

		gGridItem[slot].part = parts[e];
		gGridItem[slot].shop = -1;
		gGridItem[slot].equip = e;
		gGridItem[slot].col = col;
		gGridItem[slot].row = row;
		gGridItem[slot].used = true;

		//끼고 들어온 장비는 인벤토리의 진짜 ITEM 그대로다. 옵션도 그대로
		//따라 들어온다. 스탯은 RefreshStat 이 이미 더했으므로 여기 것은
		//그리기와 겹치기에만 쓰인다.
		GridSetGearItem(&gGridItem[slot], &hero->equip[e]);
	}

	if (missed > 0) {
		snprintf(gGridMsg, sizeof(gGridMsg), "장비 %d개가 성에 안 들어갔다", missed);
		gGridMsgFrame = FPS * 3;
	}

	// 화면에서 신발 드래그 앤 드롭 및 배치를 즉시 확인할 수 있도록,
	// 장착된 신발이 없으면 현재 영웅 타입에 맞는 신발을 인벤토리에 넣어준다.
	bool hasBoots = false;
	for (int i = 0; i < GRIDTEST_MAXITEM; ++i) {
		if (gGridItem[i].used && (gGridItem[i].part.type == ITEM_GREAVES ||
			gGridItem[i].part.type == ITEM_SHOES || gGridItem[i].part.type == ITEM_BOOTS)) {
			hasBoots = true;
			break;
		}
	}
	if (!hasBoots) {
		int bootType = ITEM_GREAVES;
		if (hero->type == DIANA) bootType = ITEM_SHOES;
		else if (hero->type == MAXX) bootType = ITEM_BOOTS;

		GridPart bootPart;
		memset(&bootPart, 0, sizeof(GridPart));
		bootPart.type = bootType;
		bootPart.detail = 1;
		bootPart.grade = GRADE_RARE;
		bootPart.w = 1;
		bootPart.h = 2;
		bootPart.name = (bootType == ITEM_GREAVES) ? "체인 그리브" : (bootType == ITEM_SHOES ? "가죽 부츠" : "전투화");

		int col, row;
		if (GridFindSpot(&bootPart, &col, &row)) {
			const int slot = GridTestFreeSlot();
			if (slot >= 0) {
				gGridItem[slot].part = bootPart;
				gGridItem[slot].shop = -1;
				gGridItem[slot].equip = -1;
				gGridItem[slot].col = col;
				gGridItem[slot].row = row;
				gGridItem[slot].used = true;
				MakeItem(&gGridItem[slot].item, bootType, 1, bootPart.grade, bootPart.detail, 0);
			}
		}
	}

	// 화면에서 하의(바지/치마/킬트) 드래그 앤 드롭 및 배치를 즉시 확인할 수 있도록,
	// 장착된 하의가 없으면 현재 영웅 타입에 맞는 하의를 인벤토리에 넣어준다.
	bool hasPants = false;
	for (int i = 0; i < GRIDTEST_MAXITEM; ++i) {
		if (gGridItem[i].used && (gGridItem[i].part.type == ITEM_KILT ||
			gGridItem[i].part.type == ITEM_SKIRT || gGridItem[i].part.type == ITEM_PANTS)) {
			hasPants = true;
			break;
		}
	}
	if (!hasPants) {
		int pantsType = ITEM_KILT;
		if (hero->type == DIANA) pantsType = ITEM_SKIRT;
		else if (hero->type == MAXX) pantsType = ITEM_PANTS;

		GridPart pantsPart;
		memset(&pantsPart, 0, sizeof(GridPart));
		pantsPart.type = pantsType;
		pantsPart.detail = 1;
		pantsPart.grade = GRADE_RARE;
		pantsPart.w = 2;
		pantsPart.h = 2;
		pantsPart.name = (pantsType == ITEM_KILT) ? "체인 킬트" : (pantsType == ITEM_SKIRT ? "빈티지 스커트" : "카프스킨 팬츠");

		int col, row;
		if (GridFindSpot(&pantsPart, &col, &row)) {
			const int slot = GridTestFreeSlot();
			if (slot >= 0) {
				gGridItem[slot].part = pantsPart;
				gGridItem[slot].shop = -1;
				gGridItem[slot].equip = -1;
				gGridItem[slot].col = col;
				gGridItem[slot].row = row;
				gGridItem[slot].used = true;
				MakeItem(&gGridItem[slot].item, pantsType, 1, pantsPart.grade, pantsPart.detail, 0);
			}
		}
	}

	// 화면에서 장갑/건틀릿/팔찌 드래그 앤 드롭 및 배치를 즉시 확인할 수 있도록,
	// 장착된 장갑이 없으면 현재 영웅 타입에 맞는 장갑을 인벤토리에 넣어준다.
	bool hasGlove = false;
	for (int i = 0; i < GRIDTEST_MAXITEM; ++i) {
		if (gGridItem[i].used && (gGridItem[i].part.type == ITEM_GUNTLET ||
			gGridItem[i].part.type == ITEM_ARMLET || gGridItem[i].part.type == ITEM_GLOVE)) {
			hasGlove = true;
			break;
		}
	}
	if (!hasGlove) {
		int gloveType = ITEM_GUNTLET;
		if (hero->type == DIANA) gloveType = ITEM_ARMLET;
		else if (hero->type == MAXX) gloveType = ITEM_GLOVE;

		GridPart glovePart;
		memset(&glovePart, 0, sizeof(GridPart));
		glovePart.type = gloveType;
		glovePart.detail = 1;
		glovePart.grade = GRADE_RARE;
		glovePart.w = 2;
		glovePart.h = 2;
		glovePart.name = (gloveType == ITEM_GUNTLET) ? "체인 건틀릿" : (gloveType == ITEM_ARMLET ? "사막 팔찌" : "이중매듭 장갑");

		int col, row;
		if (GridFindSpot(&glovePart, &col, &row)) {
			const int slot = GridTestFreeSlot();
			if (slot >= 0) {
				gGridItem[slot].part = glovePart;
				gGridItem[slot].shop = -1;
				gGridItem[slot].equip = -1;
				gGridItem[slot].col = col;
				gGridItem[slot].row = row;
				gGridItem[slot].used = true;
				MakeItem(&gGridItem[slot].item, gloveType, 1, glovePart.grade, glovePart.detail, 0);
			}
		}
	}

	// 화면에서 갑옷 드래그 앤 드롭 및 배치를 즉시 확인할 수 있도록,
	// 장착된 갑옷이 없으면 현재 영웅 타입에 맞는 갑옷을 인벤토리에 넣어준다.
	bool hasArmor = false;
	for (int i = 0; i < GRIDTEST_MAXITEM; ++i) {
		if (gGridItem[i].used && (gGridItem[i].part.type == ITEM_ARMOR ||
			gGridItem[i].part.type == ITEM_VEST || gGridItem[i].part.type == ITEM_COAT)) {
			hasArmor = true;
			break;
		}
	}
	if (!hasArmor) {
		int armorType = ITEM_ARMOR;
		if (hero->type == DIANA) armorType = ITEM_VEST;
		else if (hero->type == MAXX) armorType = ITEM_COAT;

		GridPart armorPart;
		memset(&armorPart, 0, sizeof(GridPart));
		armorPart.type = armorType;
		armorPart.detail = 1;
		armorPart.grade = GRADE_RARE;
		armorPart.w = 2;
		armorPart.h = 2;
		armorPart.name = (armorType == ITEM_ARMOR) ? "비늘 갑옷" : (armorType == ITEM_VEST ? "가죽 조끼" : "전투 코트");

		int col, row;
		if (GridFindSpot(&armorPart, &col, &row)) {
			const int slot = GridTestFreeSlot();
			if (slot >= 0) {
				gGridItem[slot].part = armorPart;
				gGridItem[slot].shop = -1;
				gGridItem[slot].equip = -1;
				gGridItem[slot].col = col;
				gGridItem[slot].row = row;
				gGridItem[slot].used = true;
				MakeItem(&gGridItem[slot].item, armorType, 1, armorPart.grade, armorPart.detail, 0);
			}
		}
	}
}

void GridTestDraw(void)
{
	char str[96];
	int i, x, y, w, h;

	if (gGridOpen == false)
		return;

	GridTestLayout();

	//---- 판이 열렸으면 장착 장비부터 넣는다 ----
	//
	//히어로가 선 뒤에야 장비를 읽을 수 있다. 등장 연출 중(REGENMOVE)이어도
	//장비는 이미 실려 있다(SetHero).
	if (gGridGearPending
		&& (ao[PLAYER].active || ao[PLAYER].moveHandler == REGENMOVE))
		GridPlaceGear();

	//---- 뒤는 덮지 않는다 ----
	//
	//격자가 앉은 띠를 어둡게 깔았더니 배경이 다 가려졌다. 칸마다 반투명
	//바탕을 깔므로(아래 격자 그리기) 덮개 없이도 칸은 읽힌다.

	//---- 끌고 있는 것의 목적지를 먼저 정한다 ----
	//
	//격자를 그리면서 같이 정하면, 칸을 그리는 순서에 따라 강조가 한
	//프레임씩 늦는다. 먼저 정하고 그린 뒤 마지막에 손에 든 것을 얹는다.
	gGridDragValid = false;
	gGridDragCol = -1;
	gGridDragRow = -1;

	if (gGridDragOn) {
		const GridPart* p = &gGridDragDesc;

		//카드 한가운데를 손가락에 맞춘다. 왼쪽 위를 맞추면 큰 카드가
		//손가락에서 멀리 떨어져 어디에 놓이는지 감이 안 온다.
		const int left = touchX - p->w * gGridCell / 2;
		const int bottom = touchY - p->h * gGridCell / 2;

		//반 칸 넘게 걸치면 그 칸으로 붙는다. row 는 아랫줄 기준이다.
		gGridDragCol = GridFloorDiv(left - gGridX + gGridCell / 2, gGridCell);
		gGridDragRow = GridFloorDiv(bottom - gGridBottom + gGridCell / 2, gGridCell);

		gGridDragValid = GridTestCanPlace(&gGridDragDesc,
			gGridDragCol, gGridDragRow, gGridDragFrom);
		gGridDragRot = false;

		//---- 세워서 안 들어가면 눕혀 본다 ----
		//
		//성의 높이를 넘는 긴 검을 넣는 길이다. 눕힌 모양의 한가운데를
		//손가락에 다시 맞춰 자리를 잡는다.
		if (!gGridDragValid) {
			const GridPart turned = GridPartRotated(gGridDragDesc);
			const int tl = touchX - turned.w * gGridCell / 2;
			const int tb = touchY - turned.h * gGridCell / 2;
			const int tc = GridFloorDiv(tl - gGridX + gGridCell / 2, gGridCell);
			const int tr = GridFloorDiv(tb - gGridBottom + gGridCell / 2, gGridCell);

			if (GridTestCanPlace(&turned, tc, tr, gGridDragFrom)) {
				gGridDragRot = true;
				gGridDragValid = true;
				gGridDragCol = tc;
				gGridDragRow = tr;
			}
		}
	}

	//---- 격자 ----
	//
	//표의 칸을 하나씩 그린다(castleGridCell). 네모를 다 훑으며 빈 칸을 거르지
	//않는다 - 그려지는 것이 곧 표에 적힌 것이어야 한다.
	{
		const int castle = GridCastleIdx(robin.castle);
		const int start = castleGridCellStart[castle];

		for (i = 0; i < castleGridCellCnt[castle]; i++) {
			const int cx = castleGridCell[(start + i) * 2];
			const int cy = castleGridCell[(start + i) * 2 + 1];

			if (GridMaskAt(cx, cy) == false)
				continue;

			x = GridCellX(cx);
			y = GridCellY(cy);

			SetAlpha(20);
			MemRect(x, y, gGridCell - 1 * _2X, gGridCell - 1 * _2X, 0x3A3A5C);
			SetAlpha(ALPHA_MAX);
			MemRectFrame(x, y, gGridCell - 1 * _2X, gGridCell - 1 * _2X, 0x555580);
		}
	}

	//---- 놓여 있는 것 ----
	for (i = 0; i < GRIDTEST_MAXITEM; i++) {
		if (gGridItem[i].used == false)
			continue;

		const GridPart* p = &gGridItem[i].part;

		x = GridCellX(gGridItem[i].col);
		//row 는 아랫줄이다. 사각형의 윗변은 맨 윗줄에서 온다.
		y = GridCellY(gGridItem[i].row + p->h - 1);
		w = p->w * gGridCell;
		h = p->h * gGridCell;

		GridTestDrawCard(p, x, y, w, h, ALPHA_MAX);

		//검은 쿨타임을 덮어 그린다. 가방 안에서 치는 것은 검뿐이다.
		if (p->type == ITEM_SWORD) {
			float charge = 0.0f;
			int flash = 0;

			if (StageRtSwordCharge(i, &charge, &flash))
				GridDrawCharge(x, y, w, h, charge, flash);
		}

		//아웃게임에서 끼고 들어온 장비. 팔 수 없다는 것이 눈에 보여야 한다.
		if (gGridItem[i].equip >= 0) {
			SetFontColor(COLOR_WHITE);
			CenterTextStrSolid("장착", x + 12 * _2X, y - 2 * _2X, 0.4f);
		}

		//겹쳐서 오른 레벨. 1 이면 적지 않는다 - 모든 칸에 Lv1 이 붙으면
		//눈이 갈 곳을 잃는다.
		if (gGridItem[i].level > 1) {
			char lv[16];

			SetFontColor(COLOR_YELLOW);
			sprintf(lv, "Lv%d", gGridItem[i].level);
			CenterTextStrSolid(lv, x + w - 12 * _2X, y - h + 10 * _2X, 0.44f);
		}

		//집어 갈 수 있는 자리. 그린 자리와 같은 사각형이어야 한다.
		SetRectPoint(x, y, w, h, TOUCH_FUNC_GRIDTEST_ITEM + i);
	}

	//---- 놓일 자리 미리보기 ----
	//
	// 초록이면 놓인다, 빨강이면 안 놓인다. 사다리꼴 격자는 어디가
	// 밖인지가 눈에 잘 안 들어와서 색으로 말해 줘야 한다.
	if (gGridDragOn && gGridDragCol >= 0 && gGridDragRow >= 0) {
		const GridPart shown = gGridDragRot
			? GridPartRotated(gGridDragDesc) : gGridDragDesc;
		const GridPart* p = &shown;

		x = GridCellX(gGridDragCol);
		y = GridCellY(gGridDragRow + p->h - 1);
		w = p->w * gGridCell;
		h = p->h * gGridCell;

		SetAlpha(14);
		MemRect(x, y, w, h, gGridDragValid ? 0x33FF66 : 0xFF3344);
		SetAlpha(ALPHA_MAX);
		MemRectFrame(x, y, w, h, gGridDragValid ? 0x33FF66 : 0xFF3344);
	}

	//---- 싸우는 동안은 아래를 내린다 ----
	StageUiSlideStep();
	StageFoeInvenDraw((int)(ALPHA_MAX * gStageUiSlide));

	//---- 하단 상점 줄 ----
	//
	//룰렛 네 칸이다. 몬스터를 한 마리 눕히면 네 칸이 돌아가고, 멈춘
	//자리의 것을 값을 치르고 산다. 장비는 집어서 격자에 놓는 순간
	//값이 나간다 - 집기만 하고 도로 놓을 수 있어야 "얼마나 큰 것을
	//감당할 수 있나"를 자리와 견주어 볼 수 있다.
	//
	//싸우는 동안에도 판은 그 자리에 있다. 칸만 잠겨 있다.
	{
		//판 바닥
		SetAlpha(24);
		MemRect(0, StageShopTop(), DX, StageShopTop(), 0x14121F);
		SetAlpha(ALPHA_MAX);

		for (i = 0; i < GRIDTEST_OFFERCNT; i++) {
			const OfferCard* c = &gOffer[i];

			GridOfferRect(i, &x, &y, &w, &h);

			//---- 잠긴 칸 ----
			//
			//아직 아무도 안 눕혔다. 무엇이 나올 자리인지만 보여 준다.
			if (gOfferOn == false) {
				SetAlpha(10);
				MemRect(x, y, w, h, 0x22223C);
				SetAlpha(ALPHA_MAX);
				MemRectFrame(x, y, w, h, 0x3A3F5A);
				SetFontColor(COLOR_GREY);
				CenterTextStrSolid("잠김", x + w / 2, y - h / 2 - 4 * _2X, 0.56f);
				GridShopPriceStrip(i, -1, false);
				continue;
			}

			//---- 돌아가는 칸 ----
			//
			//멈출 때까지 장비 그림이 빠르게 바뀐다. 멈춘 뒤에야 누를 수 있다.
			if (gOfferSpin[i] > 0) {
				const GridPart* f = &kShopPart[gOfferFace[i]];

				gOfferSpin[i]--;
				if (gOfferSpin[i] % STAGE_ROULETTE_TICK == 0)
					gOfferFace[i] = Random(GRIDTEST_SHOPCNT);

				SetAlpha(24);
				MemRect(x, y, w, h, 0x2A2A44);
				SetAlpha(ALPHA_MAX);
				MemRectFrame(x, y, w, h, 0xFFD700);

				bool drawn = false;
				if (f->type == ITEM_SWORD)
					drawn = DrawSwordInBox(f->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 14 * _2X, 20);
				else if (f->type == ITEM_GREAVES || f->type == ITEM_SHOES || f->type == ITEM_BOOTS)
					drawn = DrawBootsInBox(f->type, f->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 14 * _2X, 20);
				else if (f->type == ITEM_KILT || f->type == ITEM_SKIRT || f->type == ITEM_PANTS)
					drawn = DrawPantsInBox(f->type, f->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 14 * _2X, 20);
				else if (f->type == ITEM_GUNTLET || f->type == ITEM_ARMLET || f->type == ITEM_GLOVE)
					drawn = DrawGloveInBox(f->type, f->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 14 * _2X, 20);
				else if (f->type == ITEM_ARMOR || f->type == ITEM_VEST)
					drawn = DrawArmorInBox(f->type, f->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 14 * _2X, 20);

				if (!drawn) {
					DrawIcon(GetItemIcon(f->type, f->detail, f->grade),
						x + w / 2 - ITEMICONSIZE / 2, y - 8 * _2X,
						1.0f, false, false, false, true);
				}

				GridShopPriceStrip(i, -1, false);
				continue;
			}

			//---- 동료 / 몬스터 ----
			//
			//아이콘이 없으므로 그 몸을 작게 세운다. 누가 오는지는 얼굴로
			//알아봐야 한다.
			if (c->kind != OFFER_PART) {
				const bool afford = (robin.gold >= c->price);
				const int type = c->crewType;
				const int cmf = enemyData[type * ENEMYDATASIZE + ENEMYDATA_CMF];
				const int idle = crewPos[type * 5]
					+ frame / 8 % Max(1, (int)crewPos[type * 5 + 1]);

				SetAlpha(afford ? 30 : 14);
				MemRect(x, y, w, h, 0x22223C);
				SetAlpha(ALPHA_MAX);
				MemRectFrame(x, y, w, h,
					c->kind == OFFER_CREW ? 0x66CCFF : 0xFF8844);

				DrawCmfDetailShadow(cmf, idle, x + w / 2, y - 26 * _2X, RIGHT,
					enemyIconZoom[type] * 0.6f);

				SetFontColor(afford ? COLOR_WHITE : COLOR_GREY);
				CenterTextStrSolid(textId[TEXT_MONSTERNAME_START + type],
					x + w / 2, y - h + 14 * _2X, 0.52f);
				CenterTextStrSolid(c->kind == OFFER_CREW ? "동료" : "몬스터",
					x + w / 2, y - h + 4 * _2X, 0.46f);
				GridShopPriceStrip(i, c->price, afford);

				SetRectPoint(x, y, w, h, TOUCH_FUNC_GRIDTEST_OFFER + i);
				continue;
			}

			const GridPart* p = &kShopPart[c->part];
			const bool afford = (robin.gold >= p->price);

			SetAlpha(afford ? 30 : 14);
			MemRect(x, y, w, h, 0x22223C);
			SetAlpha(ALPHA_MAX);
			MemRectFrame(x, y, w, h, kGradeColor[p->grade]);

			bool drawn = false;
			if (p->type == ITEM_SWORD)
				drawn = DrawSwordInBox(p->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 40 * _2X, ALPHA_MAX);
			else if (p->type == ITEM_GREAVES || p->type == ITEM_SHOES || p->type == ITEM_BOOTS)
				drawn = DrawBootsInBox(p->type, p->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 40 * _2X, ALPHA_MAX);
			else if (p->type == ITEM_KILT || p->type == ITEM_SKIRT || p->type == ITEM_PANTS)
				drawn = DrawPantsInBox(p->type, p->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 40 * _2X, ALPHA_MAX);
			else if (p->type == ITEM_GUNTLET || p->type == ITEM_ARMLET || p->type == ITEM_GLOVE)
				drawn = DrawGloveInBox(p->type, p->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 40 * _2X, ALPHA_MAX);
			else if (p->type == ITEM_ARMOR || p->type == ITEM_VEST)
				drawn = DrawArmorInBox(p->type, p->detail, x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 40 * _2X, ALPHA_MAX);

			if (!drawn) {
				DrawIcon(GetItemIcon(p->type, p->detail, p->grade),
					x + w / 2 - ITEMICONSIZE / 2, y - 8 * _2X,
					1.0f, false, false, false, true);
			}

			SetFontColor(afford ? COLOR_WHITE : COLOR_GREY);
			CenterTextStrSolid(p->name, x + w / 2, y - h + 14 * _2X, 0.52f);
			sprintf(str, "%dx%d", p->w, p->h);
			CenterTextStrSolid(str, x + w / 2, y - h + 4 * _2X, 0.46f);
			GridShopPriceStrip(i, p->price, afford);

			SetRectPoint(x, y, w, h, TOUCH_FUNC_GRIDTEST_OFFER + i);
		}

		//---- 나오는 몫 ----
		//
		//무엇이 얼마나 나오는지 적어 둔다. 다시 뽑을지 말지는 이 수를
		//보고 정하는 것이라, 숨기면 다시 뽑기가 도박이 된다.
		SetFontColor(COLOR_GREY);
		sprintf(str, "장비 %d%%   동료 %d%%   몬스터 %d%%",
			100 - kOfferCrewPct - kOfferMonsterPct, kOfferCrewPct, kOfferMonsterPct);
		CenterTextStrSolid(str, DX / 2, StageShopPctTop() - 2 * _2X, 0.46f);

		//---- 다시 뽑기 ----
		//
		//오른쪽 끝. 값을 옆에 적는다.
		w = STAGE_SHOP_SIDEW;
		h = 16 * _2X;
		x = DX - w - STAGE_SHOP_GAP;
		y = StageShopPctTop() + 2 * _2X;

		if (gOfferOn) {
			const bool canRoll = robin.gold >= STAGE_REROLL_GOLD;

			MemRect(x, y, w, h, canRoll ? 0x2A2A3A : 0x1A1A22);
			MemRectFrame(x, y, w, h, canRoll ? 0xC9A227 : 0x555566);
			SetFontColor(canRoll ? COLOR_WHITE : COLOR_GREY);
			sprintf(str, "%d 다시", STAGE_REROLL_GOLD);
			CenterTextStrSolid(str, x + w / 2, y - h + 4 * _2X, 0.46f);
			SetRectPoint(x, y, w, h, TOUCH_FUNC_STAGE_REROLL);
		}

		//---- 가진 골드 ----
		//
		//동전 그림과 수를 나란히 놓는다. 수만 있으면 그것이 골드인지
		//다른 값인지 알 수 없다.
		{
			const float gz = 0.5f;
			const int numW = GetGoldNumDx(robin.gold, false, false, true, 0.6f);
			const int iconW = (int)(ITEMICONSIZE * gz);
			const int gx = DX / 2 - (numW + iconW) / 2;

			DrawIcon(ICON_GOLD, gx, StageShopGoldTop(), gz, false, true, true, true);
			DrawGoldNum(robin.gold, gx + iconW + 2 * _2X, StageShopGoldTop(),
				RIGHT, false, false, true, 0.6f);
		}

		//---- 지도 / 도감 ----
		//
		//전투 시작 버튼 양옆. 버튼 그림 위에 아이콘만 얹는다. 글자를
		//넣으면 좁은 칸에서 두 줄이 되어 버튼이 지저분해진다.
		for (i = 0; i < 2; i++) {
			const float sideZoom = (float)STAGE_SHOP_SIDEW / 192.0f;

			w = STAGE_SHOP_SIDEW;
			h = (int)(62 * sideZoom);
			x = i == 0 ? STAGE_SHOP_GAP * 2 : DX - w - STAGE_SHOP_GAP * 2;
			y = StageShopBtnTop();

			DrawTouchLargeButton(x, y, 192, 62, "",
				i == 0 ? TOUCH_FUNC_STAGE_MAP : TOUCH_FUNC_STAGE_BOOK,
				FRAME_BLUE, sideZoom);

			DrawIcon(i == 0 ? ITEM_MAP_ICON : SLOTICON_WEAPON,
				x + w / 2 - ITEMICONSIZE / 2, y - h / 2 + ITEMICONSIZE / 2,
				0.8f, false, false, true, true);
		}
	}

#if 0	//휴지통은 화면에서 뺐다. 파는 길은 나중에 다시 정한다.
	//---- 휴지통 ----
	GridTrashRect(&x, &y, &w, &h);

	//끌고 있는 동안 손가락이 위에 있으면 붉게 달군다. 놓으면 팔린다는
	//것을 놓기 전에 알려 줘야 한다.
	const bool overTrash = gGridDragOn &&
		touchX >= x && touchX <= x + w && touchY <= y && touchY >= y - h;

	SetAlpha(overTrash ? 30 : 18);
	MemRect(x, y, w, h, overTrash ? 0x772222 : 0x2A2A3A);
	SetAlpha(ALPHA_MAX);
	MemRectFrame(x, y, w, h, overTrash ? 0xFF5555 : 0x777799);

	SetFontColor(overTrash ? COLOR_WHITE : COLOR_GREY);
	CenterTextStrSolid("팔기", x + w / 2, y - h + 4 * _2X, 0.6f);
#endif

	//---- 연참 미리보기 ----
	//
	//격자에 놓인 검을 작은 카드로 한 번 더 늘어놓던 줄이다. 같은 검이
	//화면에 둘로 보여서 뺐다.
	//GridTestDrawCombo(GridTopY() + 14 * _2X);

	//---- 남은 골드와 쓴 칸 ----
	int usedCell = 0;

	for (i = 0; i < GRIDTEST_MAXITEM; i++) {
		if (gGridItem[i].used)
			usedCell += gGridItem[i].part.w * gGridItem[i].part.h;
	}

	//칸 수도 표에서 읽는다.
	const int totalCell = GridTestCellCnt(robin.castle);

	//쓴 칸과 골드는 아래 상점 줄에서 본다. 여기 또 적으면 같은 수가
	//화면에 둘이 되어 어느 쪽이 맞는지 헷갈린다.
	(void)usedCell;
	(void)totalCell;

	//---- 한 일 ----
	if (gGridMsgFrame > 0) {
		gGridMsgFrame--;
		SetFontColor(COLOR_WHITE);
		CenterTextStrSolid(gGridMsg, DX / 2, gGridBottom - 3 * _2X, 0.7f);
	}

	//---- 손에 든 것 ----
	//
	// 맨 마지막에 그린다. 격자든 상점이든 휴지통이든 그 위를 지나가야
	// 하므로 무엇보다 앞에 있어야 한다.
	if (gGridDragOn) {
		const GridPart held = gGridDragRot
			? GridPartRotated(gGridDragDesc) : gGridDragDesc;
		const GridPart* p = &held;

		w = p->w * gGridCell;
		h = p->h * gGridCell;

		GridTestDrawCard(p, touchX - w / 2, touchY + h / 2, w, h, 26);
	}

	//---- 접기 ----
	//
	//전에는 GNB 바로 밑에 두었는데, 그 자리는 GNB 가 화면 전체에 깐
	//터치영역(TOUCH_FUNC_GAMEMENU)과 겹쳐 눌러도 아무 일이 없었다.
	//격자 위 한 줄로 내려 잡는다. 여기는 이 모듈이 마지막에 등록하므로
	//GetTouchFunc 의 뒤에서부터 찾기에 걸린다.
	w = 30 * _2X;
	h = 16 * _2X;
	x = 6 * _2X;
	y = GridTopY() + GRIDTEST_HUDH - 2 * _2X;

	MemRect(x, y, w, h, 0x442233);
	MemRectFrame(x, y, w, h, 0xCC6688);
	SetFontColor(COLOR_WHITE);
	CenterTextStrSolid("접기", x + w / 2, y - h + 4 * _2X, 0.6f);
	SetRectPoint(x, y, w, h, TOUCH_FUNC_GRIDTEST_TOGGLE);
}

//======================================================================
// 로비 성 카메라
//
// 로비에는 성 그림(castle0 ~ castle9) 한 장을 깐다. 두 손가락으로 벌리고
// 오므려 확대/축소하고, 한 손가락으로 밀어 성의 구석구석을 본다.
//
// 배율 1 은 성의 가로가 화면 가로에 꼭 맞는 크기다. 거기서 1 ~ 2 배.
// 가로 기준이라 화면이 세로로 길든 짧든 성이 가로를 채운 데서 더 줄지 않는다.
// 기준점(gLobbyCamX/Y)은 화면 한가운데에 오는 그림 안의 점이다(그림
// 픽셀, 위가 0). 그림이 화면보다 크면 그림 끝이 화면 안으로 들어오지
// 않게 막고, 작으면 그 방향은 가운데에 둔다.
//======================================================================
#define LOBBY_CAM_ZOOM_MIN		1.0f
#define LOBBY_CAM_ZOOM_MAX		2.0f
#define LOBBY_CAM_ZOOM_STEP		1.02f	//디버그 버튼을 누르고 있을 때 한 프레임에
#define LOBBY_CAM_DRAG_START	(6 * _2X)	//이만큼 움직여야 끌기로 본다
#define LOBBY_CAM_DEBUG_BUTTONS	1		//시뮬레이터용 확대/축소 버튼

static float gLobbyCamZoom = 1.0f;
static float gLobbyCamX = -1.0f;	//음수면 아직 안 정했다. 처음 그릴 때 가운데로
static float gLobbyCamY = -1.0f;
static int gLobbyCamImg = -1;		//기준점을 정한 그림. 성이 바뀌면 다시 가운데로

//손가락 둘까지 기억한다. [0] 이 먼저 닿은 손가락이다.
struct LobbyCamFinger {
	bool on;
	int id;
	float x, y;
	bool orphan;	//핀치 중 첫째가 먼저 떨어져 혼자 남았다. 뗄 때까지 무시한다
};
static LobbyCamFinger gLobbyFinger[2];
static bool gLobbyPanOn = false;		//첫 손가락이 끌기로 바뀌었다
static bool gLobbyPanBlocked = false;	//버튼 위에서 눌렀다 - 밀지 않는다
static bool gLobbyPinchOn = false;
static float gLobbyPinchDist = 1.0f;
static float gLobbyPinchZoom = 1.0f;
static int gLobbyZoomHold = 0;			//디버그 버튼: +1 확대, -1 축소

//이번 프레임에 성을 그린 자리. 캐릭터를 성 위에 세울 때 쓴다.
static float gLobbyCastleLeft = 0;
static float gLobbyCastleTop = 0;
static float gLobbyCastleScale = 1;
static float gLobbyCastleW = 0;
static float gLobbyCastleH = 0;

//성 그림 안의 비율 자리(u: 왼쪽 0 ~ 오른쪽 1, v: 위 0 ~ 아래 1)를
//DrawObj 가 쓰는 오브젝트 좌표로 바꾼다. DrawObj 는 화면에
//  x' = xOffset + x - rx,  y' = STATUSWIN_Y + (rh - 4) * TSIZE - (y - OBJIMGGAP) - ry
//로 찍으므로 그 역이다.
static void LobbyCastleToObj(float u, float v, float* x, float* y)
{
	const float sx = gLobbyCastleLeft + u * gLobbyCastleW * gLobbyCastleScale;
	const float sy = gLobbyCastleTop - v * gLobbyCastleH * gLobbyCastleScale;

	*x = sx - xOffset + rx;
	*y = (float)(STATUSWIN_Y + (rh - 4) * TSIZE) - ry + OBJIMGGAP - sy;
}

//캐릭터 크기. 성 층고와 문 크기에 맞춰 0.70 을 곱하고, 성 그림이 그려진
//배율을 그대로 따른다.
//
//성 그림은 가로가 제각각이라(416 ~ 922px) 화면 가로에 맞추면 그림마다
//실제 배율이 다르다. 캐릭터도 같은 배율을 곱해야 어느 성에서나 성과의
//비율이 같다. 가로 LOBBY_CHAR_REF_W 인 성을 가로에 맞췄을 때 예전
//크기(DIORAMAZOOM * 0.70)가 되게 잡았다.
#define LOBBY_CHAR_REF_W		922.0f	//castle9 가로

static float LobbyCharZoom(void)
{
	return DIORAMAZOOM * 0.70f * gLobbyCastleScale * LOBBY_CHAR_REF_W / DX;
}

//성 그림 위 자리. 모든 성 그림이 아래 가운데에 성문, 맨 아래가 바닥이라
//그 바닥 띠에 세운다. 발코니 같은 성마다 다른 자리는 아직 표가 없다.
#define LOBBY_HERO_U			0.50f
#define LOBBY_HERO_V			0.965f
#define LOBBY_GROUND_V_BACK		0.925f
#define LOBBY_GROUND_V_FRONT	0.975f

static int LobbyCastleImg(void)
{
	return CASTLE0_IMG + Max(0, Min(robin.castle, CASTLE9_IMG - CASTLE0_IMG));
}

//그림 크기. 아직 못 읽었으면 false
static bool LobbyCastleSize(float* w, float* h)
{
	const int img = LobbyCastleImg();

	if (!sprite[img]) LoadImg(img);
	if (!sprite[img]) return false;

	const auto size = sprite[img]->getContentSize();
	*w = size.width;
	*h = size.height;
	return *w > 0 && *h > 0;
}

//지금 배율에서 그림 1픽셀이 화면 몇 픽셀인가
static float LobbyCamScale(float imgW)
{
	return (float)DX / imgW * gLobbyCamZoom;
}

//성을 보여 주는 세로 영역. 하단 메뉴 위부터 화면 위 끝까지다.
//성의 맨 아래가 하단 버튼에 가리지 않게 이 영역 안에서만 움직인다.
static bool gLobbyCastleMenuOpen = false;

void LobbyCastleMenuCommand(int func)
{
    if (func == TOUCH_FUNC_LOBBY_CASTLE)
        gLobbyCastleMenuOpen = !gLobbyCastleMenuOpen;
    else
        gLobbyCastleMenuOpen = false;
}

static float LobbyViewBottom(void)
{
	return (float)BOTTOMMENUHEIGHT + 82 * _2X;
}

static float LobbyViewCY(void)
{
	return (DY + LobbyViewBottom()) / 2.0f;
}

//기준점을 그림 경계 안으로 되돌린다.
static void LobbyCamClamp(void)
{
	float w, h;

	if (!LobbyCastleSize(&w, &h))
		return;

	gLobbyCamZoom = Max(LOBBY_CAM_ZOOM_MIN, Min(LOBBY_CAM_ZOOM_MAX, gLobbyCamZoom));

	const float s = LobbyCamScale(w);
	const float halfW = DX / 2.0f / s;
	const float halfH = (DY - LobbyViewBottom()) / 2.0f / s;

	if (w <= halfW * 2)
		gLobbyCamX = w / 2;
	else
		gLobbyCamX = Max(halfW, Min(w - halfW, gLobbyCamX));

	//영역보다 낮은 성은 바닥(하단 메뉴 위)에 붙인다.
	if (h <= halfH * 2)
		gLobbyCamY = h - halfH;
	else
		gLobbyCamY = Max(halfH, Min(h - halfH, gLobbyCamY));
}

//화면의 한 점(px, py)을 붙잡은 채 배율을 바꾼다. 핀치 가운데가 그대로 있다.
static void LobbyCamZoomAt(float zoom, float px, float py)
{
	float w, h;

	if (!LobbyCastleSize(&w, &h))
		return;

	const float s0 = LobbyCamScale(w);
	const float ix = gLobbyCamX + (px - DX / 2.0f) / s0;
	const float iy = gLobbyCamY - (py - LobbyViewCY()) / s0;

	gLobbyCamZoom = Max(LOBBY_CAM_ZOOM_MIN, Min(LOBBY_CAM_ZOOM_MAX, zoom));

	const float s1 = LobbyCamScale(w);
	gLobbyCamX = ix - (px - DX / 2.0f) / s1;
	gLobbyCamY = iy + (py - LobbyViewCY()) / s1;
	LobbyCamClamp();
}

#if LOBBY_CAM_DEBUG_BUTTONS
//성 0~9 전환 테스트 버튼
static const int kCastleBtnW = 17 * _2X;
static const int kCastleBtnH = 18 * _2X;
static const int kCastleBtnGap = 1 * _2X;

static int LobbyCastleBtnY(void)
{
	return BOTTOMMENUHEIGHT + 4 * _2X;
}

static int LobbyCastleBtnX(int n)
{
	(void)n;
	return 3 * _2X;
}

static int LobbyCastleBtnItemY(int n)
{
	return LobbyCastleBtnY() + (n + 1) * (kCastleBtnH + kCastleBtnGap);
}

static int LobbyCastleBtnHit(float x, float y)
{
	for (int n = 0; n < 10; n++) {
		if (GetRectPoint((int)x, (int)y, LobbyCastleBtnX(n), LobbyCastleBtnItemY(n),
			kCastleBtnW, kCastleBtnH))
			return n;
	}
	return -1;
}

//---- 성 토글 버튼 ----
//누를 때마다 castle0 -> castle1 -> ... -> castle9 -> castle0 으로 넘긴다.
//확대/축소 버튼 왼쪽에 같은 크기로 둔다.
static int LobbyCastleToggleX(void);
static int LobbyCastleToggleY(void);
static const int kCastleToggleW = 28 * _2X;
static const int kCastleToggleH = 18 * _2X;

static bool LobbyCastleToggleHit(float x, float y)
{
	return GetRectPoint((int)x, (int)y, LobbyCastleToggleX(), LobbyCastleToggleY(),
		kCastleToggleW, kCastleToggleH) != 0;
}

static void LobbyCastleToggleDraw(void)
{
	char str[16];
	const int x = LobbyCastleToggleX();
	const int y = LobbyCastleToggleY();

	MemRect(x, y, kCastleToggleW, kCastleToggleH, 0x1B2E3A);
	MemRectFrame(x, y, kCastleToggleW, kCastleToggleH, 0x5FA0B0);
	SetFontColor(COLOR_WHITE);
	sprintf(str, "성 %d", Max(0, Min(robin.castle, 9)));
	CenterTextStrSolid(str, x + kCastleToggleW / 2, y - kCastleToggleH + 5 * _2X, 0.5f);
}

static void LobbyCastleButtonsDraw(void)
{
	const int curCastle = Max(0, Min(robin.castle, 9));
	char str[16];

	for (int n = 0; n < 10; n++) {
		const int btnX = LobbyCastleBtnX(n);
		const int btnY = LobbyCastleBtnItemY(n);
		const bool selected = (curCastle == n);

		MemRect(btnX, btnY, kCastleBtnW, kCastleBtnH, selected ? 0x6A521A : 0x1A1E2E);
		MemRectFrame(btnX, btnY, kCastleBtnW, kCastleBtnH, selected ? 0xFFD700 : 0x485275);
		if (selected) {
			MemRectFrame(btnX + 1, btnY - 1, kCastleBtnW - 2, kCastleBtnH - 2, 0xFFE680);
		}
		SetFontColor(selected ? COLOR_WHITE : COLOR_GREY);
		sprintf(str, "%d", n);
		CenterTextStrSolid(str, btnX + kCastleBtnW / 2, btnY - kCastleBtnH + 4 * _2X, selected ? 0.65f : 0.55f);
	}
}

//디버그 버튼 자리. 그리는 곳과 누르는 곳이 같은 값을 쓴다.
static const int kLobbyZoomBtnW = 28 * _2X;
static const int kLobbyZoomBtnH = 18 * _2X;

static int LobbyZoomBtnY(void)
{
	return BOTTOMMENUHEIGHT + 12 * _2X;
}

static int LobbyCastleToggleX(void)
{
	return LobbyCastleBtnX(10) + 2 * _2X;
}

static int LobbyCastleToggleY(void)
{
	return LobbyZoomBtnY();
}

static int LobbyZoomBtnX(int n)
{
	(void)n;
	return DX - 3 * _2X - kLobbyZoomBtnW;
}

static int LobbyZoomBtnItemY(int n)
{
	return LobbyZoomBtnY() + (n + 1) * (kLobbyZoomBtnH + 2 * _2X);
}

static int LobbyZoomBtnHit(float x, float y)
{
	for (int n = 0; n < 2; n++) {
		if (GetRectPoint((int)x, (int)y, LobbyZoomBtnX(n), LobbyZoomBtnItemY(n),
			kLobbyZoomBtnW, kLobbyZoomBtnH))
			return n == 0 ? -1 : +1;
	}
	return 0;
}
#endif

static float LobbyFingerDist(void)
{
	const float dx = gLobbyFinger[0].x - gLobbyFinger[1].x;
	const float dy = gLobbyFinger[0].y - gLobbyFinger[1].y;

	return Max(1.0f, sqrtf(dx * dx + dy * dy));
}

//true 를 돌려주면 이 터치는 여기서 먹었다(일반 터치로 넘기지 않는다).
bool LobbyCamTouchBegan(int id, float x, float y)
{
	//첫 손가락. 일반 터치(버튼)도 그대로 받게 false 를 돌려준다.
	if (!gLobbyFinger[0].on) {
		gLobbyFinger[0] = { true, id, x, y, false };
		gLobbyFinger[1].on = false;
		gLobbyPanOn = false;
		gLobbyPinchOn = false;
		gLobbyZoomHold = 0;
#if LOBBY_CAM_DEBUG_BUTTONS
		const int castleHit = gLobbyCastleMenuOpen ? -1 : LobbyCastleBtnHit(x, y);
		if (castleHit >= 0) {
			robin.castle = castleHit;
			gLobbyCamImg = -1;
			gLobbyPanBlocked = true;
			return true;
		}
		gLobbyZoomHold = gLobbyCastleMenuOpen ? 0 : LobbyZoomBtnHit(x, y);
#endif
		//버튼 위에서 누른 것은 밀기가 아니다.
		gLobbyPanBlocked = gLobbyZoomHold != 0 || GetTouchFunc((int)x, (int)y) != 0;
		return gLobbyZoomHold != 0;
	}

	if (gLobbyFinger[1].on)
		return true;

	if (gLobbyCastleMenuOpen || popUpCnt > 0) return true;
	//두 번째 손가락 - 핀치를 연다.
	gLobbyFinger[1] = { true, id, x, y, false };
	gLobbyPinchOn = true;
	gLobbyPanOn = false;
	gLobbyZoomHold = 0;
	gLobbyPinchDist = LobbyFingerDist();
	gLobbyPinchZoom = gLobbyCamZoom;
	return true;
}

bool LobbyCamTouchMoved(int id, float x, float y)
{
	int n;

	for (n = 0; n < 2; n++)
		if (gLobbyFinger[n].on && gLobbyFinger[n].id == id)
			break;
	if (n == 2)
		return false;

	if (gLobbyFinger[n].orphan)
		return true;

	const float oldX = gLobbyFinger[n].x;
	const float oldY = gLobbyFinger[n].y;

	gLobbyFinger[n].x = x;
	gLobbyFinger[n].y = y;

	if (gLobbyPinchOn) {
		const float mx = (gLobbyFinger[0].x + gLobbyFinger[1].x) / 2;
		const float my = (gLobbyFinger[0].y + gLobbyFinger[1].y) / 2;

		LobbyCamZoomAt(gLobbyPinchZoom * LobbyFingerDist() / gLobbyPinchDist, mx, my);
		return true;
	}

	if (gLobbyZoomHold != 0)
		return true;

	if (gLobbyPanBlocked)
		return false;

	float w, h;

	if (!LobbyCastleSize(&w, &h))
		return false;

	//손가락을 따라 그림을 민다. 화면은 y 가 위로, 그림은 아래로 늘어난다.
	gLobbyCamX -= (x - oldX) / LobbyCamScale(w);
	gLobbyCamY += (y - oldY) / LobbyCamScale(w);
	LobbyCamClamp();
	return false;
}

bool LobbyCamTouchEnded(int id)
{
	gLobbyZoomHold = 0;

	if (gLobbyFinger[1].on && gLobbyFinger[1].id == id) {
		//둘째를 뗐다. 첫째가 남아 있어도 밀기는 다음 터치부터.
		gLobbyFinger[1].on = false;
		gLobbyPinchOn = false;
		gLobbyPanBlocked = true;
		return true;
	}

	if (gLobbyFinger[0].on && gLobbyFinger[0].id == id) {
		const bool orphan = gLobbyFinger[0].orphan;

		//핀치 중 첫째를 먼저 뗐다. 남은 둘째는 뗄 때까지 무시한다.
		gLobbyFinger[0] = gLobbyFinger[1];
		gLobbyFinger[0].orphan = gLobbyFinger[0].on;
		gLobbyFinger[1].on = false;
		gLobbyPinchOn = false;
		gLobbyPanBlocked = true;
		return orphan;
	}

	return false;
}

//성 한 장을 지금 카메라로 그린다.
#include "LobbySkyRender.h"

static void LobbyCastlePrepare(void)
{
	float w, h;
	const int img = LobbyCastleImg();

	if (!LobbyCastleSize(&w, &h))
		return;

	if (gLobbyCamImg != img || gLobbyCamX < 0) {
		gLobbyCamImg = img;
		gLobbyCamZoom = 1.0f;
		gLobbyCamX = w / 2;
		gLobbyCamY = h;	//처음엔 성문이 보이게 맨 아래부터. Clamp 가 영역에 맞춘다
	}

#if LOBBY_CAM_DEBUG_BUTTONS
	//누르고 있는 동안 화면 가운데를 붙잡고 배율을 바꾼다.
	if (gLobbyZoomHold != 0)
		LobbyCamZoomAt(gLobbyCamZoom * (gLobbyZoomHold > 0
			? LOBBY_CAM_ZOOM_STEP : 1.0f / LOBBY_CAM_ZOOM_STEP), DX / 2.0f, LobbyViewCY());
#endif
	LobbyCamClamp();

}

static void LobbyCastleDraw(void)
{
	float w, h;
	const int img = LobbyCastleImg();
	if (!LobbyCastleSize(&w, &h)) return;

	const float s = LobbyCamScale(w);
	const int left = (int)(DX / 2.0f - gLobbyCamX * s);
	const int top = (int)(LobbyViewCY() + gLobbyCamY * s);
	const int castleIdx = Max(0, Min(robin.castle, 9));
	const float imageBottom = top - h * s;
	const float radius = CastleWheels::GetWheelRadius(castleIdx, s);
	// Tuck the upper part of the wheel into the base.  This removes the long
	// hanging axle seen when the whole wheel was placed below the image.
	const float wheelGround = imageBottom - radius * 1.20f;

	// Give the lobby castle an actual ground plane. It belongs to the castle
	// presentation and is drawn before the castle and its front wheels.
	if (!sprite[BATTLE_BG_GROUND_IMG]) LoadImg(BATTLE_BG_GROUND_IMG);
	if (sprite[BATTLE_BG_GROUND_IMG]) {
		const auto groundSize = sprite[BATTLE_BG_GROUND_IMG]->getContentSize();
		const float groundScale = Max((float)DX / groundSize.width, 0.55f);
		// The visible grass edge in this asset sits below its nominal contact row.
		// Raise only the lobby ground so the grass meets the wheel bottoms.
		const int groundTop = (int)(wheelGround + groundSize.height * groundScale * 0.59f)
			+ 10 * _2X;
		DrawImage((int)groundSize.width, (int)groundSize.height, 0, 0,
			0, groundTop, false, false, false, false, false, groundScale,
			sprite[BATTLE_BG_GROUND_IMG], BATTLE_BG_GROUND_IMG);
	}

	DrawImage((int)w, (int)h, 0, 0, left, top,
		false, false, false, false, false, s, sprite[img], img);

	// Only the visible front-side wheels are drawn, above the castle sprite.
	CastleWheels::DrawCastleWheels(castleIdx, (float)left, imageBottom,
		w, s, wheelGround, false);

	gLobbyCastleLeft = (float)left;
	gLobbyCastleTop = (float)top;
	gLobbyCastleScale = s;
	gLobbyCastleW = w;
	gLobbyCastleH = h;
}

#if LOBBY_CAM_DEBUG_BUTTONS
static void LobbyZoomButtonsDraw(void)
{
	char str[32];

	for (int n = 0; n < 2; n++) {
		const int x = LobbyZoomBtnX(n);
		const int y = LobbyZoomBtnItemY(n);
		const bool held = gLobbyZoomHold == (n == 0 ? -1 : +1);

		MemRect(x, y, kLobbyZoomBtnW, kLobbyZoomBtnH, held ? 0x5A4A20 : 0x202030);
		MemRectFrame(x, y, kLobbyZoomBtnW, kLobbyZoomBtnH, 0xC9A227);
		SetFontColor(COLOR_WHITE);
		CenterTextStrSolid(n == 0 ? "축소" : "확대",
			x + kLobbyZoomBtnW / 2, y - kLobbyZoomBtnH + 5 * _2X, 0.5f);
	}

	sprintf(str, "x%.2f", gLobbyCamZoom);
	const double skyHour = LobbySkyCycle::hour(LobbySky::seconds);
	sprintf(str, "x%.2f  %02d:%02d / 5m", gLobbyCamZoom,
		(int)skyHour, (int)(skyHour * 60) % 60);
	CenterTextStrSolid(str, LobbyZoomBtnX(0) + kLobbyZoomBtnW / 2,
		LobbyZoomBtnItemY(1) + 9 * _2X, 0.36f);
}
#endif

void LobbyDraw(void)
{
	char str[96];
	ResetRectPoint();
	LobbyCastlePrepare();
	LobbySky::draw();

	// 디오라마 대신 성 그림 한 장을 카메라(확대/이동)로 그린다.
	LobbyCastleDraw();
	LobbySky::drawFront();

	// 히어로와 동료는 성 그림 위 비율 자리(LobbyCastleToObj)에 세운다.
	// 확대/이동하면 성과 같이 움직이고 같이 커진다.

	// 동료의 순수 걷기(Walk) 모션 탐색 람다
	auto GetCrewWalkMotion = [](int cmf, int type, int& outFrames, const signed short*& outMotions) -> bool {
		outFrames = 0;
		outMotions = nullptr;

		// 비행선/탑승물이나 프레임 수가 1 이하인 정지형/석상은 절대 걷기 불가
		if (type == NPC_SHIP || crewPos[type * 5 + 1] <= 1)
			return false;

		if (cmf < 0 || cmf >= REALMAXCMF)
			return false;

		// cmf_status_data[cmf][1] (State 1)이 걷기 모션 상태인지 검사
		const signed short* st = cmf_status_data[cmf][1];
		if (!st)
			return false;

		const int frames = (int)st[0];
		if (frames < 4 || frames > 64)
			return false;

		// 첫 모션 확인: 대기 모션(0~3) 다음의 걷기 시작 모션 (4~7번 범위)
		const signed short firstMotion = st[2];
		if (firstMotion < 4 || firstMotion > 7)
			return false;

		// 상태 내에 실제 수평 이동(dx != 0)이 존재하는지 확인
		bool hasMoveX = false;
		for (int f = 0; f < frames; ++f) {
			if (st[2 + frames + f] != 0) {
				hasMoveX = true;
				break;
			}
		}

		if (!hasMoveX)
			return false;

		outFrames = frames;
		outMotions = &st[2];
		return true;
	};

	// 성내 포지션 구분
	enum LobbyCrewRole {
		LOBBY_ROLE_SPIRE        = 0, // 첨탑 꼭대기 망루 -> 완전 고정
		LOBBY_ROLE_WALL_TOP     = 1, // 성벽 상단 외곽/회랑 난간
		LOBBY_ROLE_WALL_MID     = 2, // 중앙 발코니 / 회랑
		LOBBY_ROLE_GROUND_LEFT  = 3, // 바닥 좌측 안뜰 (히어로 좌측 독립 셀)
		LOBBY_ROLE_GROUND_RIGHT = 4, // 바닥 우측 안뜰 (히어로 우측 독립 셀)
	};

	struct LobbySlotInstance {
		LobbyCrewRole role;
		float baseX;
		float baseY;
		bool allowPatrol; // 걷기 모션이 있을 때 순찰/배회 허용 여부
		float maxRoamX;   // 배회 가로 반경
	};

	const int curCastle = Max(0, Min(robin.castle, 9));

	// 성별 히어로 기본 위치 (대문 앞 계단/양탄자 중심)
	static const struct { float u, v; } kCastleHeroPos[10] = {
		{ 0.50f, 0.88f }, // Castle 0
		{ 0.50f, 0.90f }, // Castle 1
		{ 0.50f, 0.91f }, // Castle 2
		{ 0.50f, 0.92f }, // Castle 3
		{ 0.50f, 0.93f }, // Castle 4
		{ 0.50f, 0.93f }, // Castle 5
		{ 0.50f, 0.94f }, // Castle 6
		{ 0.50f, 0.94f }, // Castle 7
		{ 0.54f, 0.95f }, // Castle 8
		{ 0.52f, 0.95f }, // Castle 9
	};

	// 히어로 자리
	float heroCenterX, heroY;
	LobbyCastleToObj(kCastleHeroPos[curCastle].u, kCastleHeroPos[curCastle].v, &heroCenterX, &heroY);

	const float charZoom = LobbyCharZoom();

	struct CastleSlotDef {
		LobbyCrewRole role;
		float u;
		float v;
		bool allowPatrol;
		float maxRoamX;
	};

	// Castle 0: 1층 원형 석조 성채 (416x448)
	static const CastleSlotDef kCastleSlots0[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 4)
		{ LOBBY_ROLE_GROUND_LEFT,  0.20f, 0.88f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.32f, 0.87f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.68f, 0.87f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.80f, 0.88f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.12f, 0.92f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.88f, 0.92f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_LEFT,  0.26f, 0.82f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.74f, 0.82f, false,  0.0f },
		// 2층 옥상 성벽 (순찰 2, 고정 3)
		{ LOBBY_ROLE_WALL_TOP,     0.25f, 0.37f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.72f, 0.37f, true,   6.0f * _2X },
		{ LOBBY_ROLE_SPIRE,        0.38f, 0.32f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.63f, 0.35f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.50f, 0.38f, false,  0.0f },
	};

	// Castle 1: 2층 구조 성채 (491x683)
	static const CastleSlotDef kCastleSlots1[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 3)
		{ LOBBY_ROLE_GROUND_LEFT,  0.20f, 0.90f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.32f, 0.90f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.68f, 0.90f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.82f, 0.90f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.10f, 0.93f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.90f, 0.93f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.76f, 0.85f, false,  0.0f },
		// 2층 성벽 테라스 (순찰 3, 고정 2)
		{ LOBBY_ROLE_WALL_MID,     0.25f, 0.53f, true,   8.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.35f, 0.53f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.65f, 0.52f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.76f, 0.52f, false,  0.0f },
		{ LOBBY_ROLE_WALL_MID,     0.50f, 0.54f, false,  0.0f },
		// 3층 주탑 망루 (고정 3)
		{ LOBBY_ROLE_SPIRE,        0.40f, 0.30f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.60f, 0.30f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.50f, 0.30f, false,  0.0f },
	};

	// Castle 2: 포탑 성채 (507x818)
	static const CastleSlotDef kCastleSlots2[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 4)
		{ LOBBY_ROLE_GROUND_LEFT,  0.20f, 0.91f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.32f, 0.91f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.68f, 0.91f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.82f, 0.92f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.10f, 0.94f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.90f, 0.94f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_LEFT,  0.18f, 0.85f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.76f, 0.86f, false,  0.0f },
		// 2층 정원 테라스 및 포탑 (순찰 2, 고정 3)
		{ LOBBY_ROLE_WALL_MID,     0.34f, 0.53f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.65f, 0.53f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.50f, 0.54f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.22f, 0.45f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.78f, 0.45f, false,  0.0f },
		// 3층 주탑 (고정 3)
		{ LOBBY_ROLE_SPIRE,        0.42f, 0.24f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.58f, 0.24f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.50f, 0.23f, false,  0.0f },
	};

	// Castle 3: 차양/상점 성 (543x943)
	static const CastleSlotDef kCastleSlots3[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 3)
		{ LOBBY_ROLE_GROUND_LEFT,  0.20f, 0.92f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.32f, 0.92f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.68f, 0.92f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.84f, 0.92f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.12f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.90f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_LEFT,  0.12f, 0.85f, false,  0.0f },
		// 2층 테라스 & 포탑 (순찰 2, 고정 3)
		{ LOBBY_ROLE_WALL_MID,     0.35f, 0.51f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.65f, 0.51f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.50f, 0.52f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.16f, 0.49f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.84f, 0.49f, false,  0.0f },
		// 3층 발코니 (순찰 1, 고정 2)
		{ LOBBY_ROLE_WALL_TOP,     0.50f, 0.36f, true,   5.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.38f, 0.35f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.62f, 0.35f, false,  0.0f },
		// 4층 주탑 망루 (고정 3)
		{ LOBBY_ROLE_SPIRE,        0.44f, 0.16f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.56f, 0.16f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.74f, 0.28f, false,  0.0f },
	};

	// Castle 4: 연금술 요새 (553x1021)
	static const CastleSlotDef kCastleSlots4[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 3)
		{ LOBBY_ROLE_GROUND_LEFT,  0.20f, 0.93f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.32f, 0.93f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.68f, 0.93f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.84f, 0.93f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.10f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.90f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_WALL_MID,     0.76f, 0.74f, false,  0.0f },
		// 2층 중앙 테라스 (순찰 2, 고정 2)
		{ LOBBY_ROLE_WALL_MID,     0.34f, 0.53f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.62f, 0.53f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.50f, 0.53f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.78f, 0.52f, false,  0.0f },
		// 3층 좌탑 & 크레인 (순찰 1, 고정 1)
		{ LOBBY_ROLE_WALL_TOP,     0.42f, 0.39f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.24f, 0.29f, false,  0.0f },
		// 4층 중앙탑 & 첨탑 (고정 4)
		{ LOBBY_ROLE_SPIRE,        0.54f, 0.17f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.62f, 0.17f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.80f, 0.30f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.34f, 0.22f, false,  0.0f },
	};

	// Castle 5: 도르래/시계탑 요새 (558x1127)
	static const CastleSlotDef kCastleSlots5[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 2)
		{ LOBBY_ROLE_GROUND_LEFT,  0.20f, 0.93f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.32f, 0.93f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.68f, 0.93f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.84f, 0.93f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.12f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.90f, 0.95f, false,  0.0f },
		// 2층 오픈 살롱 (순찰 2, 고정 2)
		{ LOBBY_ROLE_WALL_MID,     0.20f, 0.48f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.45f, 0.56f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.55f, 0.56f, false,  0.0f },
		{ LOBBY_ROLE_WALL_MID,     0.70f, 0.56f, false,  0.0f },
		// 3층 크레인 데크 & 제단 (순찰 1, 고정 2)
		{ LOBBY_ROLE_WALL_TOP,     0.45f, 0.38f, true,   5.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.30f, 0.43f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.74f, 0.42f, false,  0.0f },
		// 4층 회랑 & 첨탑 (고정 3)
		{ LOBBY_ROLE_SPIRE,        0.65f, 0.23f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.43f, 0.18f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.65f, 0.08f, false,  0.0f },
	};

	// Castle 6: 마법사 6층 타워 (561x1362)
	static const CastleSlotDef kCastleSlots6[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 2)
		{ LOBBY_ROLE_GROUND_LEFT,  0.20f, 0.94f, true,  10.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.32f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.68f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.82f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.12f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_WALL_MID,     0.80f, 0.82f, false,  0.0f },
		// 2층 마도서 도서관 (순찰 2, 고정 2)
		{ LOBBY_ROLE_WALL_MID,     0.45f, 0.71f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.55f, 0.71f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.38f, 0.70f, false,  0.0f },
		{ LOBBY_ROLE_WALL_MID,     0.76f, 0.69f, false,  0.0f },
		// 3층 실험실 제단 (순찰 1, 고정 2)
		{ LOBBY_ROLE_WALL_TOP,     0.48f, 0.56f, true,   5.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.28f, 0.56f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.74f, 0.56f, false,  0.0f },
		// 4층 서재 (고정 1)
		{ LOBBY_ROLE_WALL_TOP,     0.50f, 0.45f, false,  0.0f },
		// 5층 점성술 테라스 (순찰 1, 고정 2)
		{ LOBBY_ROLE_WALL_TOP,     0.44f, 0.34f, true,   5.0f * _2X },
		{ LOBBY_ROLE_SPIRE,        0.26f, 0.28f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.73f, 0.28f, false,  0.0f },
		// 6층 수정첨탑 (고정 1)
		{ LOBBY_ROLE_SPIRE,        0.56f, 0.20f, false,  0.0f },
	};

	// Castle 7: 폭포 대성당 요새 (676x1388)
	static const CastleSlotDef kCastleSlots7[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 2)
		{ LOBBY_ROLE_GROUND_LEFT,  0.23f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.35f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.65f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.78f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.12f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.88f, 0.95f, false,  0.0f },
		// 2층 정원 성벽 (순찰 3, 고정 1)
		{ LOBBY_ROLE_WALL_MID,     0.18f, 0.68f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.45f, 0.66f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.55f, 0.66f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.80f, 0.68f, false,  0.0f },
		// 3층 대계단 / 천문대 (순찰 2, 고정 2)
		{ LOBBY_ROLE_WALL_MID,     0.28f, 0.52f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.65f, 0.52f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.50f, 0.53f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.86f, 0.54f, false,  0.0f },
		// 4층 성전 발코니 (고정 3)
		{ LOBBY_ROLE_WALL_TOP,     0.50f, 0.41f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.25f, 0.35f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.72f, 0.35f, false,  0.0f },
		// 5층 고층 성소 / 첨탑 (고정 2)
		{ LOBBY_ROLE_SPIRE,        0.50f, 0.27f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.52f, 0.15f, false,  0.0f },
	};

	// Castle 8: 붉은 지붕 대궁전 (781x1481)
	static const CastleSlotDef kCastleSlots8[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 2)
		{ LOBBY_ROLE_GROUND_LEFT,  0.22f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.36f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.70f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.82f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.12f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.88f, 0.95f, false,  0.0f },
		// 2층 아치형 회랑 (순찰 3, 고정 1)
		{ LOBBY_ROLE_WALL_MID,     0.20f, 0.70f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.42f, 0.70f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.62f, 0.70f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.82f, 0.69f, false,  0.0f },
		// 3층 살롱 / 티테이블 (순찰 2, 고정 3)
		{ LOBBY_ROLE_WALL_MID,     0.40f, 0.60f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.55f, 0.60f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.65f, 0.60f, false,  0.0f },
		{ LOBBY_ROLE_WALL_MID,     0.16f, 0.58f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.84f, 0.54f, false,  0.0f },
		// 4층 연회장 (순찰 2, 고정 2)
		{ LOBBY_ROLE_WALL_TOP,     0.48f, 0.50f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.58f, 0.50f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.30f, 0.45f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.15f, 0.42f, false,  0.0f },
		// 5층 집무실 (고정 1)
		{ LOBBY_ROLE_WALL_TOP,     0.52f, 0.40f, false,  0.0f },
		// 6층 붉은 원뿔 첨탑 (고정 3)
		{ LOBBY_ROLE_SPIRE,        0.32f, 0.25f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.52f, 0.25f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.72f, 0.25f, false,  0.0f },
	};

	// Castle 9: 구름 위 천상 성채 (922x1700)
	static const CastleSlotDef kCastleSlots9[] = {
		// 1층 바닥 안뜰 (보행 4, 고정 2)
		{ LOBBY_ROLE_GROUND_LEFT,  0.20f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.36f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.68f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.82f, 0.94f, true,   8.0f * _2X },
		{ LOBBY_ROLE_GROUND_LEFT,  0.10f, 0.95f, false,  0.0f },
		{ LOBBY_ROLE_GROUND_RIGHT, 0.90f, 0.95f, false,  0.0f },
		// 2층 수정 성소 (순찰 3, 고정 2)
		{ LOBBY_ROLE_WALL_MID,     0.50f, 0.73f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.40f, 0.72f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.60f, 0.72f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.18f, 0.72f, false,  0.0f },
		{ LOBBY_ROLE_WALL_MID,     0.82f, 0.72f, false,  0.0f },
		// 3층 샹들리에 회랑 (순찰 3, 고정 2)
		{ LOBBY_ROLE_WALL_MID,     0.50f, 0.62f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.40f, 0.61f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.60f, 0.61f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_MID,     0.20f, 0.60f, false,  0.0f },
		{ LOBBY_ROLE_WALL_MID,     0.80f, 0.60f, false,  0.0f },
		// 4층 대제단 티어 (순찰 1, 고정 4)
		{ LOBBY_ROLE_WALL_TOP,     0.50f, 0.53f, true,   6.0f * _2X },
		{ LOBBY_ROLE_WALL_TOP,     0.30f, 0.46f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.70f, 0.46f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.12f, 0.52f, false,  0.0f },
		{ LOBBY_ROLE_WALL_TOP,     0.84f, 0.52f, false,  0.0f },
		// 5층~7층 왕실 문장 발코니 및 천상 첨탑 (고정 3)
		{ LOBBY_ROLE_WALL_TOP,     0.50f, 0.43f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.25f, 0.20f, false,  0.0f },
		{ LOBBY_ROLE_SPIRE,        0.75f, 0.20f, false,  0.0f },
	};

	struct CastleSlotTable {
		const CastleSlotDef* slots;
		int count;
	};

	static const CastleSlotTable kCastleSlotTables[10] = {
		{ kCastleSlots0, sizeof(kCastleSlots0) / sizeof(kCastleSlots0[0]) },
		{ kCastleSlots1, sizeof(kCastleSlots1) / sizeof(kCastleSlots1[0]) },
		{ kCastleSlots2, sizeof(kCastleSlots2) / sizeof(kCastleSlots2[0]) },
		{ kCastleSlots3, sizeof(kCastleSlots3) / sizeof(kCastleSlots3[0]) },
		{ kCastleSlots4, sizeof(kCastleSlots4) / sizeof(kCastleSlots4[0]) },
		{ kCastleSlots5, sizeof(kCastleSlots5) / sizeof(kCastleSlots5[0]) },
		{ kCastleSlots6, sizeof(kCastleSlots6) / sizeof(kCastleSlots6[0]) },
		{ kCastleSlots7, sizeof(kCastleSlots7) / sizeof(kCastleSlots7[0]) },
		{ kCastleSlots8, sizeof(kCastleSlots8) / sizeof(kCastleSlots8[0]) },
		{ kCastleSlots9, sizeof(kCastleSlots9) / sizeof(kCastleSlots9[0]) },
	};

	const CastleSlotTable& slotTable = kCastleSlotTables[curCastle];

	LobbySlotInstance walkSlots[24];
	int walkSlotsCount = 0;
	LobbySlotInstance fixedSlots[24];
	int fixedSlotsCount = 0;

	for (int s = 0; s < slotTable.count; ++s) {
		const CastleSlotDef& def = slotTable.slots[s];
		float x, y;
		LobbyCastleToObj(def.u, def.v, &x, &y);
		LobbySlotInstance inst = {
			def.role,
			x,
			y,
			def.allowPatrol,
			def.maxRoamX * charZoom / (DIORAMAZOOM * 0.70f)
		};
		if (def.allowPatrol) {
			if (walkSlotsCount < 24)
				walkSlots[walkSlotsCount++] = inst;
		}
		else {
			if (fixedSlotsCount < 24)
				fixedSlots[fixedSlotsCount++] = inst;
		}
	}

	// 1단계: 로비에 등장할 보유 크루 선별 (슬롯 장착 크루 우선, 그 후 보유한 크루)
	static int candidateCrew[24];
	int candidateCount = 0;
	bool selected[CAP_CREW] = { false };

	// 1순위: 전투 슬롯에 장착된 크루 (최우선 배치)
	for (int s = 0; s < MAXCREW && candidateCount < 24; ++s) {
		const int enemyType = robin.slotCrew[s];
		if (enemyType < 0)
			continue;
		const int crewIdx = GetCrewIdxFromType(enemyType);
		if (crewIdx < 0 || crewIdx >= gTotalCrew)
			continue;
		// 비행선/탑승물은 로비 동료에서 제외
		if (crewData[crewIdx * CREWDATASIZE + CREWDATA_TYPE] == NPC_SHIP)
			continue;
		int invenIdx = GetInvenIdx(ITEM_CREW, crewIdx, GRADE_NORMAL);
		if (invenIdx >= 0 && robin.inven[invenIdx].count >= 1 && !selected[crewIdx]) {
			candidateCrew[candidateCount++] = crewIdx;
			selected[crewIdx] = true;
		}
	}
	// 2순위: 인벤토리에 보유 중인 나머지 크루 (최대 정원 24명까지 중복 없이 등록)
	for (int i = 0; i < gTotalCrew && candidateCount < 24; ++i) {
		if (selected[i])
			continue;
		if (crewData[i * CREWDATASIZE + CREWDATA_TYPE] == NPC_SHIP)
			continue;
		int invenIdx = GetInvenIdx(ITEM_CREW, i, GRADE_NORMAL);
		if (invenIdx >= 0 && robin.inven[invenIdx].count >= 1) {
			candidateCrew[candidateCount++] = i;
			selected[i] = true;
		}
	}

	// 2단계: 크루 성향(보행 가능 vs 고정 대기)에 따라 슬롯 분배
	int walkingCrew[24];
	int walkingCrewCount = 0;
	int standingCrew[24];
	int standingCrewCount = 0;

	for (int i = 0; i < candidateCount; ++i) {
		const int crewIdx = candidateCrew[i];
		const int type = crewData[crewIdx * CREWDATASIZE + CREWDATA_TYPE];
		const int cmf = enemyData[type * ENEMYDATASIZE + ENEMYDATA_CMF];
		int dummyF = 0;
		const signed short* dummyM = nullptr;
		if (GetCrewWalkMotion(cmf, type, dummyF, dummyM)) {
			walkingCrew[walkingCrewCount++] = crewIdx;
		}
		else {
			standingCrew[standingCrewCount++] = crewIdx;
		}
	}

	struct AssignedCrew {
		int crewIdx;
		LobbySlotInstance slot;
	};
	AssignedCrew assigned[24];
	int assignedCount = 0;

	int walkSlotIdx = 0;
	int fixedSlotIdx = 0;

	// 걷기 가능한 크루는 걷기 허용 슬롯(바닥 안뜰, 성벽 순찰로)에 우선 배치
	for (int i = 0; i < walkingCrewCount; ++i) {
		if (walkSlotIdx < walkSlotsCount) {
			assigned[assignedCount++] = { walkingCrew[i], walkSlots[walkSlotIdx++] };
		}
		else if (fixedSlotIdx < fixedSlotsCount) {
			assigned[assignedCount++] = { walkingCrew[i], fixedSlots[fixedSlotIdx++] };
		}
	}

	// 걷기 모션이 없는 고정/대기 크루는 고정 슬롯(첨탑 망루, 성벽 초소)에 우선 배치
	for (int i = 0; i < standingCrewCount; ++i) {
		if (fixedSlotIdx < fixedSlotsCount) {
			assigned[assignedCount++] = { standingCrew[i], fixedSlots[fixedSlotIdx++] };
		}
		else if (walkSlotIdx < walkSlotsCount) {
			assigned[assignedCount++] = { standingCrew[i], walkSlots[walkSlotIdx++] };
		}
	}

	// 3단계: 선별/배치된 크루들의 모션 및 이동 연산
	static OBJECT lobbyCrewList[CAP_CREW];
	int owned = 0;

	for (int i = 0; i < assignedCount; ++i) {
		const int crewIdx = assigned[i].crewIdx;
		const LobbySlotInstance& slot = assigned[i].slot;

		OBJECT* pCrew = &lobbyCrewList[owned];
		memset(pCrew, 0, sizeof(OBJECT));
		pCrew->type = crewData[crewIdx * CREWDATASIZE + CREWDATA_TYPE];
		pCrew->cmf = enemyData[pCrew->type * ENEMYDATASIZE + ENEMYDATA_CMF];
		SetNpc(pCrew);
		pCrew->active = true;
		pCrew->dead = false;

		// 걷는 모션 유무 확인 및 걷기 모션 데이터 획득 (순수 Walk 모션만 허용)
		int walkFrames = 0;
		const signed short* walkMotions = nullptr;
		const bool hasWalkMotion = GetCrewWalkMotion(pCrew->cmf, pCrew->type, walkFrames, walkMotions);

		// 실제로 걷는 동작을 할 것인가? (걷는 모션 보유 + 슬롯에서 이동 허용 + 첨탑이 아님)
		const bool isWalking = hasWalkMotion && slot.allowPatrol && (slot.role != LOBBY_ROLE_SPIRE);

		float roleZoomScale = 1.0f;
		if (slot.role == LOBBY_ROLE_SPIRE) roleZoomScale = 0.75f;
		else if (slot.role == LOBBY_ROLE_WALL_TOP) roleZoomScale = 0.85f;
		else if (slot.role == LOBBY_ROLE_WALL_MID) roleZoomScale = 0.90f;
		else roleZoomScale = 1.00f;

		pCrew->y = slot.baseY;

		if (isWalking) {
			// 실제 걷는 동료: 좌우로 자연스럽게 이동하며 걷기 모션 재생
			const float speed = 0.009f + (owned % 3) * 0.002f;
			const float phaseX = frame * speed + owned * 1.9f;
			pCrew->x = slot.baseX + sinf(phaseX) * slot.maxRoamX;
			pCrew->dirX = pCrew->dirF = (cosf(phaseX) >= 0.0f) ? RIGHT : LEFT;

			const int animDiv = (walkFrames >= 12) ? 2 : ((walkFrames >= 6) ? 4 : 8);
			const int animStep = ((frame / animDiv) + owned * 3) % walkFrames;
			pCrew->motion = walkMotions[animStep];
		}
		else {
			// 고정/대기 동료: 제자리에서 숨쉬는 자연스러운 대기 모션만 재생 (좌우 두리번거림 없이 중앙을 향해 시선 고정)
			pCrew->x = slot.baseX;
			pCrew->dirX = pCrew->dirF = (slot.baseX < heroCenterX) ? RIGHT : LEFT;
			const int idleFrames = Max(1, (int)crewPos[pCrew->type * 5 + 1]);
			pCrew->motion = crewPos[pCrew->type * 5] + (frame / 6 + owned) % idleFrames;
		}

		// 모션 유효성 안전 보정 (스프라이트가 없는 모션 번호 방지)
		if (cmd_m_cnt[pCrew->cmf] == nullptr || cmd_m_cnt[pCrew->cmf][pCrew->motion * 2 + 1] == 0) {
			pCrew->motion = crewPos[pCrew->type * 5];
		}

		pCrew->nx = pCrew->x;
		pCrew->ny = pCrew->y;
		pCrew->frame = frame + owned * MOTIONDIV;
		// 전투와 독립된 로비 전용 확대 배율 적용
		pCrew->zoom = enemyIconZoom[pCrew->type] * CREWZOOM * LOBBY_CREW_ZOOM_SCALE * roleZoomScale * charZoom;
		owned++;
	}

	// Y-sorting: 화면 위(성 상단/뒤쪽)부터 화면 아래(바닥/앞쪽) 순서로 렌더링하여 입체감 확보
	static int drawOrder[CAP_CREW];
	for (int k = 0; k < owned; ++k)
		drawOrder[k] = k;
	for (int k = 1; k < owned; ++k) {
		int key = drawOrder[k];
		float keyY = lobbyCrewList[key].y;
		int m = k - 1;
		while (m >= 0 && lobbyCrewList[drawOrder[m]].y > keyY) {
			drawOrder[m + 1] = drawOrder[m];
			m--;
		}
		drawOrder[m + 1] = key;
	}

	// 1단계: 발밑 그림자 먼저 렌더링 (캐릭터 발밑에 정상적으로 그림자가 깔리도록 처리)
	for (int k = 0; k < owned; ++k) {
		const OBJECT* pCrew = &lobbyCrewList[drawOrder[k]];
		const float shadowX = pCrew->x - (IsBigCmf(pCrew->cmf) ? 20.0f : 12.0f) * _2X * pCrew->zoom;
		const float shadowY = STATUSWIN_Y + (rh - 4) * TSIZE - (pCrew->y - OBJIMGGAP) - ry + 8.0f * _2X * pCrew->zoom;
		if (IsBigCmf(pCrew->cmf))
			ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, shadowX, shadowY, SHADOW_IMG, pCrew->zoom);
		else
			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, shadowX, shadowY, SHADOW_IMG, pCrew->zoom);
	}

	// 2단계: 크루 스프라이트 렌더링
	for (int k = 0; k < owned; ++k) {
		DrawObj(&lobbyCrewList[drawOrder[k]]);
	}

	// 3단계: 히어로. 성문 앞 한가운데. 자리와 크기만 잠깐 바꿔 그리고 되돌린다.
	if (ao[ROBIN].active) {
		OBJECT* hero = &ao[ROBIN];
		const float bx = hero->x, by = hero->y, bnx = hero->nx, bny = hero->ny, bz = hero->zoom;

		hero->x = hero->nx = heroCenterX;
		hero->y = hero->ny = heroY;
		hero->zoom = bz * charZoom;

		ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X,
			hero->x - 12.0f * _2X * hero->zoom,
			STATUSWIN_Y + (rh - 4) * TSIZE - (hero->y - OBJIMGGAP) - ry + 8.0f * _2X * hero->zoom,
			SHADOW_IMG, hero->zoom);
		DrawObj(hero);

		hero->x = bx; hero->y = by; hero->nx = bnx; hero->ny = bny; hero->zoom = bz;
	}

#if LOBBY_CAM_DEBUG_BUTTONS
	LobbyZoomButtonsDraw();
	LobbyCastleButtonsDraw();
#endif

	// 기존 플레이 화면의 상단 GNB와 자원 바를 그대로 쓴다.
	bar[BAR_GOLD].count = robin.gold;
	bar[BAR_STAR].count = robin.coin;
	BarDraw(&bar[BAR_CROWN], bar[BAR_CROWN].zoom);
	BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);
	BarDraw(&bar[BAR_STAR], bar[BAR_STAR].zoom);
	GNBDraw(0, DY - (GNBHEIGHT - GNB_INIT_HEIGHT));

	//======================================================================
	// 임시 패널 - 자리만 잡아 둔 사각형
	//
	// 목업(docs/design/lobby_mockup-v2.png)에 있는 판들이다. 그림이
	// 아직 없어서 사각형과 글자로만 세워 둔다. 자리와 크기가 맞는지
	// 먼저 보고, 그림이 나오면 MemRect 를 DrawImage 로 바꾸면 된다.
	//
	// 값은 아직 표에서 오지 않는다. 어디서 와야 하는지만 주석으로
	// 적어 둔다 - 수를 지어내면 나중에 진짜 값과 구별이 안 된다.
	//======================================================================
	{
		const int panelTop = DY - GNBHEIGHT - 4 * _2X;

		//---- 상단 DAY 및 문페이즈 (낮/밤) 표시 ----
		{
			const int dayW = 84 * _2X;
			const int dayH = 20 * _2X;
			const int dayX = DX / 2 - dayW / 2;
			const int dayY = panelTop;

			// 다크 캡슐 배경 & 은은한 골드 테두리
			MemRect(dayX, dayY, dayW, dayH, 0x1B1428);
			MemRectFrame(dayX, dayY, dayW, dayH, 0xC9A227);

			// 문페이즈 아이콘 (menu.png에 추가한 32x32 아이콘)
			// 낮: 700, 780 / 밤: 740, 780 / 마지막 날: 780, 780
			int phaseSrcX = 700;
			if (IsFinalDayStage())
				phaseSrcX = 780;
			else if (IsStageNight())
				phaseSrcX = 740;

			const float phaseZoom = 0.82f;
			const int iconX = dayX + 3 * _2X;
			const int iconY = dayY - 2 * _2X;
			DrawImage(32, 32, phaseSrcX, 780, iconX, iconY, false, false, false, false, false, phaseZoom, sprite[MENU_IMG], MENU_IMG);

			// DAY 텍스트
			SetFontColor(COLOR_WHITE);
			sprintf(str, "DAY %d / %d", GetStageDay(), CYCLE_DAYS);
			CenterTextStrSolid(str, dayX + 16 * _2X + (dayW - 16 * _2X) / 2, dayY - 14 * _2X, 0.68f);
		}
	}

	// Keep the castle base above the footer, including its characters.
	{
		const float width = Min((float)DX * .50f, 164.0f * _2X);
		const float height = width * 131.0f / 512.0f;
		const int x = (int)((DX - width) / 2);
		const int y = BOTTOMMENUHEIGHT + 48 * _2X;
		const float press = GetButtonScale(TOUCH_FUNC_GOTOBATTLE, x, y, width, height);
		DrawImage(512, 131, 512, 272, x - (int)(width * (press - 1) / 2),
			y + (int)(height * (press - 1) / 2), false, false, false, false, false,
			width / 512.0f * press, sprite[WIN_IMG], WIN_IMG);
		SetRectPoint(x, y, width, height, TOUCH_FUNC_GOTOBATTLE);
		SetFontColor(COLOR_WHITE);
		CenterTextStrSolid("게임 시작", DX / 2, y - (int)(height * .23f), .80f * press);
		const long long admission = GetStageAdmissionHeart(robin.stage);
		sprintf(str, "%lld", admission);
		const float feeZoom = .56f;
		const int numberW = (int)StringWidth(str, feeZoom);
		const float iconZoom = (12.0f * _2X) / Max(1, imgArray[IMG_LIGHTNING * 4 + 3]);
		const int iconW = (int)(imgArray[IMG_LIGHTNING * 4 + 2] * iconZoom);
		const int feeX = (DX - numberW - iconW - 4 * _2X) / 2;
		const int feeY = y - (int)(height * .59f);
		DrawArray(IMG_LIGHTNING, feeX, feeY, iconZoom);
		SetFontColor(robin.heart >= admission ? COLOR_WHITE : COLOR_GREY);
		CenterTextStrSolid(str, feeX + iconW + 4 * _2X + numberW / 2,
			feeY - 2 * _2X, feeZoom);
	}

	// Continuous navigation strip; the current adventure tab is raised.
	const int cells[] = { BOTTOMMENU_CELL_SHOP, BOTTOMMENU_CELL_EQUIP,
		BOTTOMMENU_CELL_ADVENTURE, BOTTOMMENU_CELL_CASTLE, BOTTOMMENU_CELL_DUNGEON };
	const int actions[] = { TOUCH_FUNC_SHOP, TOUCH_FUNC_COLLECTIONS,
		TOUCH_FUNC_LOBBY_ADVENTURE, TOUCH_FUNC_LOBBY_CASTLE, TOUCH_FUNC_LOBBY_DUNGEON };
	const char* names[] = { "상점", "장비", "모험", "성", "던전" };
	MemRect(0, BOTTOMMENUHEIGHT, DX, BOTTOMMENUHEIGHT, 0x17263E);
	MemRect(0, BOTTOMMENUHEIGHT, DX, 2 * _2X, 0x7794BC);
	for (int i = 0; i < 5; ++i) {
		const int left = DX * i / 5;
		const int right = DX * (i + 1) / 5;
		const int cx = (left + right) / 2;
		const bool active = gLobbyCastleMenuOpen ? i == 3 : i == 2;
		const int lift = active ? 6 * _2X : 0;
		const int top = BOTTOMMENUHEIGHT + lift;
		if (active) {
			MemRect(left + 2, top, right - left - 4, top, 0x294976);
			MemRect(left + 2, top, right - left - 4, 2 * _2X, 0xF2CA64);
		}
		if (i) MemRect(left, BOTTOMMENUHEIGHT - 4, 1, BOTTOMMENUHEIGHT - 8, 0x3B5273);
		const float iconSize = Min((float)(right - left - 12), (float)BOTTOMMENUHEIGHT - 20 * _2X);
		const float press = GetButtonScale(actions[i], left, top, right - left, top);
		const float size = iconSize * (active ? 1.14f : 1.0f) * press;
		DrawImage(BOTTOMMENU_CELL, BOTTOMMENU_CELL, BOTTOMMENU_CELL * cells[i], 0,
			cx - (int)(size / 2), top - 2 * _2X, false, false, false, false, false,
			size / BOTTOMMENU_CELL, sprite[BOTTOMMENU_IMG], BOTTOMMENU_IMG);
		SetRectPoint(left, top, right - left, top, actions[i]);
		SetFontColor(active ? COLOR_REALYELLOW : COLOR_WHITE);
		CenterTextStrSolid(names[i], cx, 10 * _2X, .62f);
	}

	if (popUpCnt > 0) gLobbyCastleMenuOpen = false;
	if (gLobbyCastleMenuOpen) {
		// Outside taps dismiss the panel and never drag the castle underneath.
		SetRectPoint(0, DY, DX, DY - BOTTOMMENUHEIGHT - 6 * _2X, TOUCH_FUNC_LOBBY_CASTLE_CLOSE);
		const int w = 114 * _2X;
		const int h = 34 * _2X;
		const int x = Min(DX - w - 4 * _2X, DX * 7 / 10 - w / 2);
		const int y = BOTTOMMENUHEIGHT + 86 * _2X;
		MemRect(x - 3 * _2X, y + 3 * _2X, w + 6 * _2X, 2 * h + 9 * _2X, 0x17263E);
		const char* labels[] = { "성 업그레이드", "동료" };
		const int funcs[] = { TOUCH_FUNC_POPUP_CASTLEMENU, TOUCH_FUNC_POPUP_CREWLIST };
		for (int i = 0; i < 2; ++i) {
			const int top = y - i * (h + 3 * _2X);
			MemRect(x, top, w, h, 0x294976);
			MemRectFrame(x, top, w, h, 0xC9A227);
			SetFontColor(COLOR_WHITE);
			CenterTextStrSolid(labels[i], x + w / 2, top - h / 2 + 5 * _2X, .68f);
			SetRectPoint(x, top, w, h, funcs[i]);
		}
	}
	SetFontColor(COLOR_WHITE);

	//---- 성 격자 인벤토리 시험판 ----
	//
	//격자는 전투 화면에 붙는다(Core.cpp 의 MD_PLAY / MD_BATTLE 에서
	//Play() 뒤에 부른다). 로비에서 같이 그리면 START 버튼 자리를
	//덮어 버리고, 무엇보다 "전투를 보면서 밑단에서 성을 채운다"가
	//이 판의 전부라 전투 화면이 아니면 볼 것이 없다.

	// 기존 상점/히어로/동료 팝업은 로비 위에 그대로 얹는다. 로비를
	// MD_PLAY로 바꾸지 않으므로 팝업을 닫아도 전투 화면으로 새지 않는다.
	for (int i = 0; i < popUpCnt; i++)
		DrawPopUp(i);

	frame++;
}

void DrawCmfPopUp(int cmf, int textIdx, int x, int y, int dx, int dy, int textDx, int line, int startFrame, float zoom, int dir)
{
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

//=============================================================================
// PVP test mode
// 서버 매칭이 붙기 전의 화면/진행 검증용이다. 상대 HOUSE 패킷이 준비되면
// StartPvpTest()에서 현재 robin 복사 대신 응답 데이터를 보관하면 된다.
//=============================================================================
static int pvpTestFrame = 0;
//0 격돌/구름/디오라마 줌 진입, 1 GO 대기, 2 교전, 3 상자로 이동해 내리치기, 4 약탈,
//5 패배, 6 닫고 복귀
static int pvpTestState = 0;

//---- 약탈 ----
//
//상자를 연 뒤 동전을 몇 개 남겼는지, 얼마를 남겼는지 센다. 한 프레임에
//조금씩만 내보내므로 그동안 들고 있어야 한다.
static int pvpLootBox = -1;
static int pvpLootCoinLeft = 0;
static long long pvpLootLeft = 0;
static long long pvpLootCoinUnit = 0;
static bool pvpLootSwing = false;
static long long pvpTestPlayerHp = 1000;
static long long pvpTestPlayerMaxHp = 1000;
static long long pvpTestEnemyHp = 1000;
static long long pvpTestEnemyMaxHp = 1000;
static long long pvpTestPlayerDamage = 100;
static long long pvpTestDefenseDamage = 50;
static HOUSE pvpTestDefender;
static int pvpTestPlayerX = 76 * _2X;
static long long pvpTestLoot = 0;
static unsigned char pvpReturnDraw = MD_PLAY;
static unsigned char pvpReturnKey = MK_PLAY;
static OBJECT pvpSavedObjects[TOTALOBJECT];
static bool pvpObjectsSaved = false;
static int pvpSavedRx = 0;
static int pvpSavedRy = 0;
static float pvpSavedDioramaZoom = DIORAMAZOOM;
static int pvpSavedWaveStatus = 0;

//---- PVP 전투 상태 ----
//
//동료마다 세 개의 시계를 돌린다. 찬 것 중 가장 높은 단계를 낸다.
static int pvpCrewCool[MAXCREW][3] = { { 0, }, };
static bool pvpCrewActing[MAXCREW] = { false, };

//수비측도 같은 시계를 돈다. 편성이 같으니 규칙도 같아야 한다.
static int pvpFoeCool[MAXCREW][3] = { { 0, }, };

//---- 차례표 ----
//
//    0..5    아군 동료
//    6       아군 히어로
//    7..12   적 동료
//    13      적 히어로
//
//한 바퀴가 열넷이다. 빈 자리와 쓰러진 자리는 건너뛴다.
enum {
	PVP_TURN_ALLY_CREW = 0,
	PVP_TURN_ALLY_HERO = MAXCREW,
	PVP_TURN_FOE_CREW,
	PVP_TURN_FOE_HERO = PVP_TURN_FOE_CREW + MAXCREW,
	PVP_TURN_TOTAL
};

static int pvpTurnSlot = 0;
static int pvpTurnFrame = 0;
static int pvpTurnGap = 0;
static bool pvpTurnActing = false;

//동료가 제 차례를 몇 번 치렀는가. 스킬은 시계가 아니라 이 횟수로 나간다.
//[0] 아군, [1] 수비.
static int pvpTurnCount[2][MAXCREW] = { { 0, }, };

//이번 차례에 나가는 단계(1~3). 스킬이면 2 이상이고, 그때는 판을 잠깐 세운다.
static int pvpTurnLevel = 1;
static BAR pvpHeroHudBar[2];
static BAR pvpCrewHudBar[2][MAXCREW];
static bool pvpHudBarsReady = false;

//성벽 위의 제자리. 치러 내려갔다가 여기로 돌아온다.
static int pvpFoeHomeY[MAXCREW] = { 0, };

//쏘는 자세를 몇 프레임 더 유지할 것인가. 0 이면 대기 자세다.
static int pvpFoeShot[MAXCREW] = { 0, };
static int pvpCrewShot[MAXCREW] = { 0, };

//---- 스킬 정지 ----
//
//2 / 3 차가 나가는 동안 판을 세운다. 치는 개체와 총알만 움직인다.
//
//보스전처럼 "끝날 때까지"로 안 잡는다. 여기는 열넷이 저마다 도는 판이라
//누구 하나의 끝을 기다리면 판이 자주, 오래 선다. 길이를 못 박는다.
//
//-1 이면 안 멈춰 있다.
static int pvpFreezeObj = -1;
static int pvpFreezeFrame = 0;

int GetPvpSkillFreezeObj(void)
{
	if (drawHandle != MD_PVP)
		return -1;

	return pvpFreezeObj;
}

//치는 개체 하나를 정하고 그만큼 판을 세운다.
static void PvpBeginSkillFreeze(int obj, int level)
{
	if (level < 2)
		return;		//1 차는 저절로 나가는 기본공격이다. 안 세운다.

	pvpFreezeObj = obj;
	pvpFreezeFrame = (level >= 3) ? PVP_FREEZE_SKILL3 : PVP_FREEZE_SKILL2;
}

bool IsPvpCrewActing(int crewSlot)
{
	if (crewSlot < 0 || crewSlot >= MAXCREW)
		return false;

	return pvpCrewActing[crewSlot];
}

void PvpFinishCrewSkill(OBJECT* pObj)
{
	const int slot = GetObjFromPtr(pObj) - CREW;

	if (drawHandle != MD_PVP || slot < 0 || slot >= MAXCREW)
		return;

	pvpCrewActing[slot] = false;
	pObj->attack = 0;
	pObj->turnPosition = HERE;
	pObj->frame = pObj->mainFrame = pObj->attackFrame = 0;
	ActionPlanEnd();
	turn = PLAYER;
}

//---- 싸울 개체 한 명을 세운다 ----
//
//공격측은 앞쪽 칸(히어로/동료), 수비측은 적 칸에 산다. 그런데 수비측도
//실은 히어로와 동료다. "적 칸에 사는 아군 형태"라서 어긋나는 자리가
//많았다 - maxhp 를 안 채워 체력바 폭이 0 으로 나뉘고, 몬스터 모션표를
//히어로에 적용해 몸이 안 그려지고, 지난 판 상태이상이 그대로 딸려왔다.
//
//그 뒤치다꺼리를 여기 한 곳에 모은다. 또 어긋나면 고칠 곳이 여기 하나다.
static void PvpMakeFighter(int dst, const OBJECT& src, bool isHero,
	bool isDefender)
{
	ao[dst] = src;
	ao[dst].active = true;
	ao[dst].dead = false;
	ao[dst].hp = Max((long long)1, ao[dst].ps[PS_HP]);

	//적 칸의 개체는 최대체력을 maxhp 에서 읽는다. 안 채우면 머리 위
	//체력바가 0 으로 나눠 화면 폭만 한 흰 판이 된다.
	ao[dst].maxhp = ao[dst].hp;

	//---- 공격력 ----
	//
	//AttackRobin 은 피해를 ao[obj].str 에서 낸다. 그건 몬스터 칸이고
	//동료 객체에는 안 채워져 있다 - 0 이면 데미지도 0 이라 아무리 맞아도
	//히어로 체력이 안 줄었다.
	//
	//동료의 공격력은 ps[PS_DMG] 다. 그것을 그대로 옮긴다.
	ao[dst].str = Max((long long)1, ao[dst].ps[PS_DMG]);

	//지난 판의 상태이상은 새 판으로 넘어오지 않는다. 넘어오면 머리 위에
	//흰 상태이상 카드가 그대로 떠 있다.
	memset(ao[dst].debuf, 0, sizeof(ao[dst].debuf));
	memset(ao[dst].buff, 0, sizeof(ao[dst].buff));

	//모션표가 둘이다. 히어로는 제 cmf 의 중립모션, 동료는 몬스터 표를 본다.
	//섞어 쓰면 없는 번호가 들어가 몸이 안 그려진다.
	ao[dst].motion = isHero ? PO_C0_N0 : crewPos[ao[dst].type * 5];

	if (isHero) {
		//---- 히어로 크기 ----
		//
		//defaultZoom 을 반드시 같이 세운다. 공격 연출(crewAtkFxFrame)이
		//zoom = defaultZoom * (1 + ...) 로 크기를 내는데, defaultZoom 이
		//엉뚱하면 첫 공격에서 그 값으로 부풀고 그대로 남는다.
		//
		//처음에는 멀쩡하다가 싸움이 시작되면 커지는 것이 그 모양이다.
		//
		//두 히어로가 같은 값을 본다. 적 칸에 산다고 크기가 달라질 이유가 없다.
		if (ao[dst].zoom <= 0.0f)
			ao[dst].zoom = LOBBYZOOM;

		ao[dst].defaultZoom = ao[dst].zoom;
	}
	else {
		ao[dst].defaultZoom = ao[dst].zoom = src.defaultZoom;

		if (ao[dst].zoom <= 0.0f)
			ao[dst].defaultZoom = ao[dst].zoom =
				(float)enemyIconZoom[ao[dst].type] * CREWZOOM;
	}

	ao[dst].dirX = ao[dst].dirF = isDefender ? LEFT : RIGHT;
	ao[dst].moveHandler = null;		//GO 전에는 아무도 안 움직인다
	ao[dst].drawHandler = isHero ? PLAYERDRAW
		: (isDefender ? ENEMYDRAW : CREWDRAW);

	//서로 상대 히어로만 노린다. 동료는 딜러, 히어로는 체력통이다.
	ao[dst].target = isDefender ? PVP_ATTACKER_ROBIN : PVP_DEFENDER_ROBIN;
	ao[dst].turnPosition = HERE;
	ao[dst].frame = ao[dst].mainFrame = ao[dst].attackFrame = 0;
	InitMotion(&ao[dst]);
}

static void SetupPvpCombatObjects(void)
{
	const int castleIdx = castleOrder[robin.castle];
	const int heroPosBase = castleIdx * 2 * TOTALCHAR;
	const int crewPosBase = castleIdx * MAXCREW * 2;
	const OBJECT attacker = pvpSavedObjects[PLAYER];

	memset(ao, 0, sizeof(OBJECT) * TOTALOBJECT);

	//---- 개체 밖에 사는 연출값도 지운다 ----
	//
	//상태이상의 부여/해제 연출은 개체가 아니라 번호로 찾는 전역 배열에
	//들어 있다. memset(ao) 는 그것을 안 지운다.
	//
	//남아 있으면 새 판의 그 번호 개체가 지난 판의 연출을 이어받아, 걸리지도
	//않은 상태이상 카드가 머리 위에 뜬다.
	memset(statusTurnFxFrame, 0, sizeof(statusTurnFxFrame));
	memset(statusApplyFxFrame, 0, sizeof(statusApplyFxFrame));
	memset(statusApplyDebuff, 0, sizeof(statusApplyDebuff));
	memset(statusRecoverFxFrame, 0, sizeof(statusRecoverFxFrame));
	memset(statusRecoverDebuff, 0, sizeof(statusRecoverDebuff));
	memset(statusStackFxFrame, 0, sizeof(statusStackFxFrame));
	memset(crewAtkFxFrame, 0, sizeof(crewAtkFxFrame));

	//---- 공격측 히어로 ----
	//
	//제자리에 그대로 선다. 쳐들어가는 쪽이라 여기서 출발해 앞으로 간다.
	PvpMakeFighter(PVP_ATTACKER_ROBIN, attacker, true, false);
	ao[PVP_ATTACKER_ROBIN].x = ao[PVP_ATTACKER_ROBIN].nx =
		(float)setHeroPos[heroPosBase];
	ao[PVP_ATTACKER_ROBIN].y = ao[PVP_ATTACKER_ROBIN].ny =
		(float)setHeroPos[heroPosBase + 1];

	//---- 수비측 히어로 ----
	//
	//적 칸(ENEMY)에 산다. 그래야 NearEnemy / AttackEnemyCheck 가 찾는다.
	//가운데를 사이에 두고 우리 히어로와 같은 거리에 선다.
	PvpMakeFighter(PVP_DEFENDER_ROBIN, attacker, true, true);
	//화면 가운데를 사이에 두고 우리 히어로와 같은 거리다.
	//
	//DIORAMASIZE_X 로 뒤집고 있었다. 그건 성 그림의 폭이라 화면 가운데와
	//다르고, 그만큼 한쪽으로 밀린다.
	ao[PVP_DEFENDER_ROBIN].x = ao[PVP_DEFENDER_ROBIN].nx =
		(float)DX - ao[PVP_ATTACKER_ROBIN].x;
	ao[PVP_DEFENDER_ROBIN].y = ao[PVP_DEFENDER_ROBIN].ny =
		(float)setHeroPos[heroPosBase + 1];

	//---- 수비측 동료 ----
	//
	//MAXENEMYOBJ 묶음의 루트만 쓴다. 뒤 네 칸은 그 동료가 쏘는 총알 자리로
	//비워 둔다. 번호가 겹치면 총알이 남의 몸을 덮어쓴다.
	//
	//성 배치표를 뒤집지 않고 그대로 쓴다. 이 판은 상대의 성이고 그 성에는
	//우리와 같은 방식으로 편성이 서 있다. 뒤집으면 성 그림의 가운데를
	//어디로 보느냐에 따라 여섯이 통째로 밀린다.
	for (int i = 0; i < MAXCREW; i++) {
		const int src = CREW + i;
		const int dst = PVP_DEFENDER_CREW + i * MAXENEMYOBJ;

		//누가 서는지는 상대 편성표(pvpTestDefender.crew)가 정한다.
		//내 개체의 active 를 보면 등장 연출 중인 동료가 빠진다.
		if (pvpTestDefender.crew[i] <= 0)
			continue;

		//능력치는 아직 내 동료에서 가져온다. 서버 매칭이 붙으면 이 원본이
		//상대에게서 받은 값으로 바뀐다.
		//
		//type 은 넘기기 전에 세운다. PvpMakeFighter 가 type 을 보고 크기
		//(enemyIconZoom)와 모션(crewPos)을 정하기 때문이다. 뒤에 바꾸면
		//엉뚱한 타입의 크기로 그려진다 - 빈 슬롯이었던 자리가 거인이 됐다.
		OBJECT foeSrc = pvpSavedObjects[src];

		foeSrc.type = pvpTestDefender.crew[i];
		foeSrc.defaultZoom = 0.0f;	//타입에 맞게 다시 잡게 한다

		PvpMakeFighter(dst, foeSrc, false, true);
		ao[dst].x = ao[dst].nx =
			(float)castleCrewPosition[crewPosBase + i * 2];
		ao[dst].y = ao[dst].ny =
			(float)castleCrewPosition[crewPosBase + i * 2 + 1];
		pvpFoeHomeY[i] = (int)ao[dst].y;
	}

	//---- 공격측 동료 ----
	//
	//히어로 뒤로 한 칸씩 줄을 선다. 히어로가 오른쪽을 보므로 뒤는 왼쪽이다.
	//
	//성 배치표를 쓰지 않는다. 그 표는 성 위에 흩어 놓는 자리라 줄이 안
	//된다. 적은 성을 지키니 그 표가 맞고, 아군은 쳐들어가는 쪽이다.
	for (int i = 0; i < MAXCREW; i++) {
		const int src = CREW + i;
		const int dst = PVP_ATTACKER_CREW + i;

		//수비측과 같은 편성표를 본다. 기준이 다르면 인원이 갈린다.
		if (robin.slotCrew[i] < 0)
			continue;

		PvpMakeFighter(dst, pvpSavedObjects[src], false, false);
		ao[dst].x = ao[dst].nx = ao[PVP_ATTACKER_ROBIN].x
			- (float)(PVP_ALLY_GAP * (i + 1));
		ao[dst].y = ao[dst].ny = ao[PVP_ATTACKER_ROBIN].y;
	}

	//---- 지킬 상자 ----
	//
	//개체로 세운다. 화면에 직접 그리지 않는다.
	//
	//직접 그리면 일반모드와 y 기준이 달라져 공중에 뜬다. 개체로 두면
	//DrawObj 가 일반모드와 같은 식으로 자리도 그림자도 크기도 정한다.
	//바뀌는 것은 x 와 보는 방향뿐이다.
	//
	//쳐들어간 쪽이라 내 상자는 없다. 지킬 상자는 상대 것 하나뿐이다.
	for (int i = NEUTRAL; i < ITEMOBJ; i++) {
		if (!pvpSavedObjects[i].active
			|| pvpSavedObjects[i].type != OBJ_BOX)
			continue;

		ao[i] = pvpSavedObjects[i];
		ao[i].x = ao[i].nx = (float)DX - pvpSavedObjects[i].x;
		ao[i].dirX = ao[i].dirF = LEFT;
		break;
	}
}

void StartPvpTest(void)
{
	if (drawHandle == MD_PVP)
		return;

	pvpReturnDraw = drawHandle;
	pvpReturnKey = keyHandle;
	memcpy(pvpSavedObjects, ao, sizeof(OBJECT) * TOTALOBJECT);
	pvpObjectsSaved = true;
	pvpSavedRx = rx;
	pvpSavedRy = ry;
	pvpSavedDioramaZoom = dioramaZoom;
	pvpSavedWaveStatus = waveStatus;
	pvpTestFrame = 0;
	//두 성의 VS 대치 화면을 먼저 보여 준 뒤 구름 전환과 실제 전투로 간다.
	pvpTestState = -1;
	pvpHudBarsReady = false;
	//실제 플레이어 능력치를 PVP 테스트 전투의 기준값으로 사용한다.
	//상대는 서버 HOUSE가 없으므로 현재 로빈의 복사본이다.
	pvpTestPlayerMaxHp = Max((long long)1, ao[PLAYER].ps[PS_HP]);
	pvpTestPlayerHp = pvpTestPlayerMaxHp;
	pvpTestEnemyMaxHp = pvpTestPlayerMaxHp;
	pvpTestEnemyHp = pvpTestEnemyMaxHp;
	pvpTestPlayerDamage = Max((long long)1, ao[PLAYER].ps[PS_DMG]);
	pvpTestDefenseDamage = pvpTestPlayerDamage;
	for (int i = 0; i < 3; i++) {
		if (ao[CREW + i].active)
			pvpTestDefenseDamage += Max((long long)1, ao[CREW + i].ps[PS_DMG]);
	}
	pvpTestPlayerX = 76 * _2X;
	pvpTestLoot = 0;
	memset(&pvpTestDefender, 0, sizeof(pvpTestDefender));
	pvpTestDefender.userId = -1; //로컬 복사 상대. 서버 매칭 상대는 실제 userId를 넣는다.
	pvpTestDefender.gold = robin.gold;
	pvpTestDefender.houseType = castleOrder[robin.castle];
	//---- 상대 편성 ----
	//
	//HOUSE.crew 는 MAXCREW 칸이다. 세 칸만 채우고 있었다.
	//
	//누가 있는지는 편성표(robin.slotCrew)가 안다. -1 이 빈 칸이다.
	//
	//ao[].active 를 보면 등장 연출 중인 동료가 빠지고, ao[].type 을 보면
	//빈 칸에 남은 지난 값이 통과한다. 실제로 빈 칸 하나가 적 진영에
	//거인으로 섰다 - 타입 0 의 크기(enemyIconZoom[0] = 1.0)로 잡혀서다.
	//
	//지금은 내 편성을 그대로 베낀다. 서버 매칭이 붙으면 이 줄만 상대
	//유저에게서 받은 값으로 바꾸면 된다 - 아래 세우는 코드는 이 배열만 본다.
	for (int i = 0; i < MAXCREW; i++)
		pvpTestDefender.crew[i] = (robin.slotCrew[i] >= 0)
			? (unsigned short)robin.slotCrew[i] : 0;
	SetupPvpCombatObjects();
	rx = ry = 0;
	waveStatus = WAVESTATUS_PLAY;
	//격돌 화면 뒤에서 전장이 먼저 보이지 않게 아주 작은 디오라마로 시작한다.
	//구름이 화면을 덮은 뒤 PvpTestDraw가 현재 전투 줌까지 키운다.
	dioramaZoom = (DIORAMAZOOM_BATTLE + dioramaZoomGap) * 0.12f;
	drawHandle = MD_PVP;
	keyHandle = MK_PVP;
	curMenu = MENU_PLAY;
	ResetRectPoint();
	PlayMusic(M_OPENWINDOW);
}

//---- 동료 하나를 내보낸다 ----
//
//보스전의 BossRaidActivateCrewSkill 과 같은 일을 한다. 전역 turn 과
//attackSequence 는 안 건드린다 - 실시간이라 하나로 여섯을 못 가린다.
static bool PvpActivateCrewSkill(int slot, int level)
{
	if (drawHandle != MD_PVP || slot < 0 || slot >= MAXCREW
		|| level < 1 || level > 3)
		return false;

	OBJECT* pObj = &ao[CREW + slot];

	if (!pObj->active || pObj->dead)
		return false;

	//나가 있는 동안은 다시 안 내보낸다. 여기서 다시 걸면 하던 동작이
	//처음으로 되돌아간다.
	if (pvpCrewActing[slot] || pObj->turnPosition != HERE)
		return false;

	const int crewIdx = GetCrewIdxFromType(pObj->type);

	if (crewIdx < 0)
		return false;

	const int skill =
		crewData[crewIdx * CREWDATASIZE + CREWDATA_SKILL1 + level - 1];

	if (skill < 0 || skill >= gTotalSkill)
		return false;

	pvpCrewActing[slot] = true;
	pObj->currentSkill = skill;

	const int patternBase = pObj->type * ATTACKPATTERNTOTALDATASIZE + 2
		+ (level - 1) * ATTACKPATTERNDATASIZE;

	pObj->etc = enemyAttackPattern[patternBase + HERE];

	if (!pObj->etc)
		pObj->etc = enemyAttackPattern[
			pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + HERE];

	pObj->target = PVP_DEFENDER_ROBIN;
	pObj->turnPosition = HERE;
	pObj->frame = pObj->mainFrame = pObj->attackFrame = 0;

	//계획의 주인은 치는 그 동료다. 전역 turn 을 넘기면 히어로 기준으로
	//연타 총액과 치명타가 잡힌다.
	ActionPlanBegin(CREW + slot, skill);
	PvpBeginSkillFreeze(CREW + slot, level);
	return true;
}

//차례 번호를 개체 번호로 옮긴다.
static int PvpTurnObj(int slot)
{
	if (slot >= PVP_TURN_ALLY_CREW && slot < PVP_TURN_ALLY_HERO)
		return CREW + slot;

	if (slot == PVP_TURN_ALLY_HERO)
		return PVP_ATTACKER_ROBIN;

	if (slot >= PVP_TURN_FOE_CREW && slot < PVP_TURN_FOE_HERO)
		return PVP_DEFENDER_CREW
			+ (slot - PVP_TURN_FOE_CREW) * MAXENEMYOBJ;

	return PVP_DEFENDER_ROBIN;
}

//---- 한 차례를 시작한다 ----
//
//나설 수 없는 자리(빈 슬롯, 쓰러진 개체)면 false 를 준다. 부르는 쪽이
//다음 자리로 넘긴다.
static bool PvpTurnBegin(int slot)
{
	const int obj = PvpTurnObj(slot);
	OBJECT* pObj = &ao[obj];

	if (!pObj->active || pObj->dead)
		return false;

	if (slot == PVP_TURN_ALLY_HERO || slot == PVP_TURN_FOE_HERO) {
		PvpHeroGiveTurn(obj);
		return true;
	}

	//동료는 제자리에서 한 발 쏘는 것이 한 차례다.
	{
		const bool ally = (slot < PVP_TURN_ALLY_HERO);
		const int side = ally ? 0 : 1;
		const int i = ally ? slot : (slot - PVP_TURN_FOE_CREW);
		int* shot = ally ? &pvpCrewShot[i] : &pvpFoeShot[i];

		//---- 몇 차 스킬인가 ----
		//
		//시계가 아니라 횟수로 잰다. 여기는 차례가 도는 판이라 "몇 번 치면
		//한 번" 이 눈에 보이는 규칙이다.
		//
		//데이터에 그 칸이 없는 동료는 PvpCrewSkillIdx 가 1 차로 내려준다.
		const int done = ++pvpTurnCount[side][i];

		pvpTurnLevel = 1;

		if (done % PVP_SKILL3_EVERY == 0
			&& PvpCrewSkillIdx(pObj->type, 3)
				!= PvpCrewSkillIdx(pObj->type, 1))
			pvpTurnLevel = 3;
		else if (done % PVP_SKILL2_EVERY == 0
			&& PvpCrewSkillIdx(pObj->type, 2)
				!= PvpCrewSkillIdx(pObj->type, 1))
			pvpTurnLevel = 2;

		//쏘는 자세로 쓸 공격패턴 상태. 단계마다 다른 자세가 있으면 그것을
		//쓰고, 없으면 기본 자세로 내린다.
		const int patternBase = pObj->type * ATTACKPATTERNTOTALDATASIZE + 2
			+ (pvpTurnLevel - 1) * ATTACKPATTERNDATASIZE;

		pObj->etc = enemyAttackPattern[patternBase + THERE];

		if (pObj->etc <= 0)
			pObj->etc = enemyAttackPattern[
				pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + THERE];

		if (pObj->etc > 0)
			*shot = PVP_FOE_SHOTMOTION;

		if (ally)
			PvpAllyShoot(CREW + i, pvpTurnLevel);
		else
			PvpFoeShoot(obj, pvpTurnLevel);

		//2 / 3 차는 판을 잠깐 세워 그 한 방만 보여준다.
		if (pvpTurnLevel >= 2) {
			PvpBeginSkillFreeze(obj, pvpTurnLevel);
			PlayMusic(M_POWERUP);
		}
	}

	return true;
}

//이 차례가 끝났는가.
static bool PvpTurnDone(int slot, int frame)
{
	if (slot == PVP_TURN_ALLY_HERO || slot == PVP_TURN_FOE_HERO) {
		//달려가 치고 제자리로 돌아와 서면 끝이다. 한 명 때문에 판이 서지
		//않게 한계도 둔다.
		return PvpHeroTurnBusy(PvpTurnObj(slot)) == false
			|| frame > PVP_TURN_TIMEOUT;
	}

	//---- 쏜 것이 닿을 때까지가 한 차례다 ----
	//
	//자세만 보고 넘기면 총알이 아직 날아가는 중에 다음 사람이 나선다.
	//그러면 화면에 뜬 데미지 숫자가 누구 것인지 알 수 없다.
	if (frame < PVP_TURN_CREW_FRAME)
		return false;

	return PvpCrewBulletAlive(PvpTurnObj(slot)) == false
		|| frame > PVP_TURN_TIMEOUT;
}

//---- 차례표를 한 칸 굴린다 ----
static void PvpTurnStep(void)
{
	if (pvpTurnGap > 0) {
		pvpTurnGap--;
		return;
	}

	if (pvpTurnActing) {
		pvpTurnFrame++;

		if (PvpTurnDone(pvpTurnSlot, pvpTurnFrame) == false)
			return;

		pvpTurnActing = false;
		pvpTurnSlot = (pvpTurnSlot + 1) % PVP_TURN_TOTAL;
		pvpTurnGap = PVP_TURN_GAP;
		return;
	}

	//나설 사람을 찾는다. 한 바퀴를 다 돌아도 아무도 없으면 이번 프레임은
	//그냥 넘긴다 - 다음 프레임에 다시 본다.
	for (int n = 0; n < PVP_TURN_TOTAL; ++n) {
		if (PvpTurnBegin(pvpTurnSlot)) {
			pvpTurnActing = true;
			pvpTurnFrame = 0;
			return;
		}

		pvpTurnSlot = (pvpTurnSlot + 1) % PVP_TURN_TOTAL;
	}
}

//---- 한 프레임 ----
//
//동료마다 시계가 셋이다. 1 차는 짧고 2 차는 꽤 길고 3 차는 아주 길다.
//찬 것 중 가장 높은 단계를 낸다 - 3 차가 터질 때까지 버티는 것이 이 판의
//뼈대이므로, 3 차가 찼는데 1 차를 쏘면 안 된다.
//
//쿨타임의 씨앗은 crew.tsv 의 boss_cool 이다. 동료별 개성(작을수록 자주
//쏜다)이 세 단계에 그대로 따라간다.
static void UpdatePvpCombatLoop(void)
{
	if (drawHandle != MD_PVP || pvpTestState != 2)
		return;

	//---- 멈춰 있는 동안 ----
	//
	//쿨타임도 히어로 전진도 여기서 막힌다. 치는 개체만 MoveObj 가 통과
	//시킨다. 판단하는 자리를 둘로 나누면 서로 어긋난다.
	if (pvpFreezeObj >= 0) {
		if (--pvpFreezeFrame > 0)
			return;

		pvpFreezeObj = -1;
		pvpFreezeFrame = 0;
	}

	//---- 두 히어로 ----
	//
	//일반모드와 같은 규칙으로 다가가 친다. 손으로 짠 전진을 쓰다가 한쪽만
	//안 움직였다 - 두 편이 같은 판이면 같은 코드가 몰아야 한다.
	//
	//우리 히어로는 PlayerMove 의 MD_PVP 갈래가 이미 부른다. 적 히어로는
	//EnemyPlayerMove 에 그 갈래가 없어서 여기서 부른다.
	PvpHeroStep(&ao[PVP_DEFENDER_ROBIN]);

	//---- 동료는 맞지 않는다 ----
	//
	//겨루는 것은 두 히어로다. 동료는 딜러고 히어로가 체력통이라고 정했으니,
	//중간에 선 동료가 쓰러지면 그 규칙이 깨진다.
	//
	//표적을 히어로로 못 박아도 소용이 없다. AttackObj 는 충돌로 대상을
	//고르므로 닿는 것은 다 친다. 수비 동료는 적 칸에 살아서 우리 공격의
	//판정에 그대로 걸리고, 치러 내려오면 더 잘 걸린다.
	//
	//무적 프레임을 매 프레임 다시 세워 판정 자체를 통과시킨다.
	//(Func_Combat.cpp 의 피해 처리가 invincible 이면 그냥 돌아간다)
	for (int i = 0; i < MAXCREW; ++i) {
		ao[CREW + i].invincible = 2;
		ao[PVP_DEFENDER_CREW + i * MAXENEMYOBJ].invincible = 2;
	}

	//---- 자세 ----
	//
	//차례와 상관없이 매 프레임 돈다. 쏜 직후에는 쏘는 자세, 아니면 대기
	//자세다. 안 두면 총알만 나가고 사람은 가만히 서 있어서 누가 쐈는지
	//안 보인다.
	for (int side = 0; side < 2; ++side) {
		for (int i = 0; i < MAXCREW; ++i) {
			const int obj = (side == 0) ? (CREW + i)
				: (PVP_DEFENDER_CREW + i * MAXENEMYOBJ);
			OBJECT* pObj = &ao[obj];
			int* shot = (side == 0) ? &pvpCrewShot[i] : &pvpFoeShot[i];

			if (!pObj->active || pObj->dead)
				continue;

			//보는 쪽은 늘 표적이다. 못 박아 두면 히어로가 지나쳐 간 뒤에도
			//엉뚱한 데를 보고 쏜다.
			pObj->dirX = pObj->dirF = (side == 0) ? RIGHT
				: ((ao[PVP_ATTACKER_ROBIN].x >= pObj->x) ? RIGHT : LEFT);
			pObj->frame++;

			if (*shot > 0) {
				const signed short* st = cmf_status_data[pObj->cmf][pObj->etc];
				const int cnt = Max(1, (int)st[0]);
				const int at = Min(cnt - 1, PVP_FOE_SHOTMOTION - *shot);

				pObj->motion = st[2 + at];
				(*shot)--;
			}
			else if (crewPos[pObj->type * 5 + 1] > 0) {
				pObj->motion = crewPos[pObj->type * 5]
					+ pObj->frame / 4 % crewPos[pObj->type * 5 + 1];
			}

			InitMotion(pObj);
		}
	}

	//---- 한 명씩 차례로 ----
	//
	//아군 동료 여섯 -> 아군 히어로 -> 적 동료 여섯 -> 적 히어로. 이것이
	//한 바퀴다. 저마다 제 쿨타임으로 치던 것을 여기 하나로 모았다.
	PvpTurnStep();
}

//---- 지킬 상자를 찾는다 ----
//
//SetupPvpCombatObjects 가 중립 칸에 하나만 세워 둔다. 번호를 기억해 두지
//않고 그때그때 찾는다 - 어느 칸에 들어갈지는 저장된 배치가 정한다.
static int PvpLootBoxObj(void)
{
	for (int i = NEUTRAL; i < ITEMOBJ; i++) {
		if (ao[i].active && ao[i].type == OBJ_BOX)
			return i;
	}

	return -1;
}

//떨어진 동전이 아직 남아 있는가.
static bool PvpLootCoinAlive(void)
{
	for (int i = ITEMOBJ; i < TOTALOBJECT; i++) {
		if (ao[i].active && ao[i].def == ITEM_GOLD)
			return true;
	}

	return false;
}

//---- 상자를 연다 ----
//
//뺏을 금액을 동전 몇 개로 나눌지 여기서 정한다. 최대 PVP_LOOT_COIN_MAX 개고,
//나누어 떨어지지 않고 남는 몫은 마지막 한 개에 붙인다. 금액이 개수보다 적으면
//그 금액만큼만 만든다 - 0 원짜리는 뿌리지 않는다.
//
//골드는 여기서 한 번에 지급한다. 동전은 그것을 보여주는 연출이다. 전투에서
//몬스터를 칠 때도 같은 순서다(먼저 GetItem, 그 다음 동전).
static void PvpOpenLootBox(int box)
{
	pvpLootBox = box;
	pvpTestLoot = Max((long long)0, pvpTestDefender.gold);

	if (box >= 0) {
		ao[box].motion = BOXSTATUS_OPENING;
		ao[box].status = BOXSTATUS_OPENING;
		ao[box].frame = 0;

		//약탈이 끝날 때까지 열어 둔다. BoxMove 가 이 값을 깎다가 0 이 되면
		//저절로 닫는다.
		ao[box].levelUpFrame = FPS;
	}

	pvpLootCoinLeft = (int)Min((long long)PVP_LOOT_COIN_MAX, pvpTestLoot);
	pvpLootLeft = pvpTestLoot;
	pvpLootCoinUnit = (pvpLootCoinLeft > 0)
		? pvpLootLeft / pvpLootCoinLeft : 0;

	if (pvpTestLoot > 0)
		GetItem(ITEM_GOLD, false, false, false, pvpTestLoot, false);

	PlayMusic(M_OPENWINDOW);
}

void StartPvpTestBattle(void)
{
	if (drawHandle != MD_PVP || pvpTestState != 1)
		return;
	pvpTestState = 2;
	pvpTestFrame = 0;
	memset(pvpCrewCool, 0, sizeof(pvpCrewCool));
	memset(pvpCrewActing, 0, sizeof(pvpCrewActing));
	memset(pvpFoeCool, 0, sizeof(pvpFoeCool));
	memset(pvpFoeShot, 0, sizeof(pvpFoeShot));
	memset(pvpCrewShot, 0, sizeof(pvpCrewShot));
	PvpHeroResetCool();

	pvpTurnSlot = 0;
	pvpTurnFrame = 0;
	pvpTurnGap = 0;
	pvpTurnActing = false;
	pvpTurnLevel = 1;
	memset(pvpTurnCount, 0, sizeof(pvpTurnCount));

	pvpLootBox = -1;
	pvpLootCoinLeft = 0;
	pvpLootLeft = 0;
	pvpLootCoinUnit = 0;
	pvpLootSwing = false;
	pvpFreezeObj = -1;
	pvpFreezeFrame = 0;

	//---- 판이 돌기 시작했다 ----
	//
	//TargetPlayer() 는 arenaStatus 가 STATUS_PLAY 일 때만 대상을 고른다.
	//아무도 안 세우고 있어서 성벽의 수비 동료가 우리 히어로를 영영 못
	//찾았다 - 그래서 안 때리는 것처럼 보였다.
	arenaStatus = STATUS_PLAY;

	ao[PVP_ATTACKER_ROBIN].moveHandler = PLAYERMOVE;
	ao[PVP_DEFENDER_ROBIN].moveHandler = ENEMYPLAYERMOVE;

	//여섯 자리를 다 돈다. 세 명만 돌아서 뒤 세 명이 서 있기만 했다.
	for (int i = 0; i < MAXCREW; i++) {
		//수비 동료는 몬스터 AI(ENEMYMOVE)를 안 쓴다.
		//
		//그 코드는 "몬스터가 다가와 때린다"용이라 성벽에 세워 두면 방향도
		//자리도 제멋대로가 된다. 게다가 동료 타입(NPC_*)에는 몬스터 발사체
		//데이터가 아예 없어서 총알이 안 나간다.
		//
		//제자리에 서서 쿨타임마다 한 발씩 쏘는 것이 전부다. 그건
		//UpdatePvpCombatLoop 이 직접 시킨다.
		int obj = PVP_DEFENDER_CREW + i * MAXENEMYOBJ;
		if (ao[obj].active)
			ao[obj].moveHandler = null;

		//아군 동료도 제자리에 선다. CREWMOVE 는 턴제 전투용이라 표적도
		//자리도 스스로 다시 정해서, 세워 둔 것을 매 프레임 흐트러뜨린다.
		if (ao[CREW + i].active)
			ao[CREW + i].moveHandler = null;
	}
	PlayMusic(M_JUMP);
}

void ExitPvpTest(void)
{
	if (pvpObjectsSaved) {
		memcpy(ao, pvpSavedObjects, sizeof(OBJECT) * TOTALOBJECT);
		rx = pvpSavedRx;
		ry = pvpSavedRy;
		dioramaZoom = pvpSavedDioramaZoom;
		waveStatus = pvpSavedWaveStatus;
		pvpObjectsSaved = false;
	}
	drawHandle = pvpReturnDraw == MD_PVP ? MD_PLAY : pvpReturnDraw;
	keyHandle = pvpReturnKey == MK_PVP ? MK_PLAY : pvpReturnKey;
	curMenu = MENU_PLAY;
	ResetRectPoint();
}

// PVP HUD는 화면 폭에 맞춰 떠 있는 정보만 놓는다. 큰 외곽 프레임이나
// 조작 버튼을 두지 않고, 관전 중 필요한 HP와 세 스킬의 시계만 보여 준다.
static void PvpDrawSkillClock(int skill, int cool, int need, int x, int y,
	int size, bool finisher, int ownerObj)
{
	if (skill < 0 || skill >= gTotalSkill || need <= 0)
		return;

	MemRectRound(x - 1 * _2X, y + 1 * _2X,
		size + 2 * _2X, size + 2 * _2X,
		finisher ? 0x7B3FC6 : 0x182847, 2 * _2X);

	//동료 스킬은 전부 sIcon.png를 쓰지 않는다. 총탄, 소환수, 히어로
	//스킬까지 종류에 맞춰 고르는 공용 카드 렌더러를 사용해야 빈 칸이 없다.
	const float cardZoom = (float)size / (float)SKILLCARDSIZE_X;
	DrawSkillCard(skill, 1, x, y, cardZoom, 0, ownerObj);

	const int remain = Max(0, need - cool);
	const int cover = (int)((long long)size * remain / need);
	if (cover > 0) {
		SetAlpha(18);
		MemRect(x, y, size, cover, COLOR_BLACK);
		SetAlpha(32);
		char sec[8];
		sprintf(sec, "%d", (remain + FPS - 1) / FPS);
		SetFontColor(COLOR_WHITE);
		CenterTextStrSolid(sec, x + size / 2, y - size / 2 + 3 * _2X, 0.55f);
	}
	else {
		const int col = finisher ? 0xFFD34E : 0x6DE8FF;
		MemRect(x, y, size, 1 * _2X, col);
		MemRect(x, y - size + 1 * _2X, size, 1 * _2X, col);
		MemRect(x, y, 1 * _2X, size, col);
		MemRect(x + size - 1 * _2X, y, 1 * _2X, size, col);
	}
}

// option.png에 한 쌍으로 들어 있는 청색/적색 패널을 쓴다. 색을 억지로
// 바꾸지 않으므로 양 진영의 재질과 명암이 같고, 원본 한 조각을 지정한
// 사각형 안에 그려 장식이 화면 좌우로 삐져나오지 않는다.
static void PvpDrawPanel(int x, int y, int w, int h, bool hero,
	int profileIdx = 0, const char* nickname = "", bool defender = false)
{
	if (hero)
		DrawPvpHeroPanel(x, y, w, h, profileIdx, nickname, defender);
	else
		DrawPvpCrewPanel(x, y, w, h);
}

//한 사람이 한 줄이다. 얼굴 옆에 스킬 셋이 이어 붙는다.
//
//전에는 얼굴을 위에, 스킬을 아래에 두었다. 그러면 누구의 스킬인지 눈이
//한 번 위아래로 움직여야 이어진다. 가로로 붙여 한 번에 읽히게 한다.
//
//x 는 줄의 왼쪽 끝, y 는 줄의 위쪽이다.
static void PvpDrawCrewHud(int slot, bool defender, BAR* hudBar)
{
	const int obj = defender
		? PVP_DEFENDER_CREW + slot * MAXENEMYOBJ : PVP_ATTACKER_CREW + slot;

	if (!ao[obj].active)
		return;

	const int crewIdx = GetCrewIdxFromType(ao[obj].type);

	if (crewIdx < 0)
		return;

	const int iconSize = PVPHUD_ICON;
	const int gap = PVPHUD_GAP;
	const int rowW = 78 * _2X;
	const int rowH = 28 * _2X;
	const int x = hudBar->x;
	const int y = hudBar->y;

	//기존 버튼 아틀라스의 판 이미지를 BAR 바닥으로 쓴다. 단색 사각형보다
	//모서리, 광택, 테두리가 살아 있어 게임의 다른 UI와 같은 재질로 보인다.
	PvpDrawPanel(x, y, rowW, rowH, false);

	//프로필 사진을 쓰지 않고 실제 동료를 판 위에 세운다.
	const int crewType = ao[obj].type;
	const int motionCnt = Max(1, crewPos[crewType * 5 + 1]);
	const int crewX = defender
		? x + rowW - 17 * _2X : x + 17 * _2X;
	DrawCmfDetailShadow(enemyData[crewType * ENEMYDATASIZE + ENEMYDATA_CMF],
		crewPos[crewType * 5] + (frame / 8) % motionCnt,
		crewX, y - 27 * _2X,
		defender ? LEFT : RIGHT, 0.76f * enemyIconZoom[crewType]);

	//---- 게이지는 차례표를 보여준다 ----
	//
	//쿨타임으로 돌 때는 남은 시간이었다. 이제 한 명씩 차례로 치므로,
	//"내 차례가 얼마나 가까운가" 가 그 자리에 온다. 제 차례에 가득 찬다.
	//
	//보여주는 값과 실제로 도는 값이 다르면 게이지가 거짓말을 한다. 그래서
	//UpdatePvpCombatLoop 이 쓰는 그 차례표를 그대로 읽는다.
	const int mySlot = defender ? (PVP_TURN_FOE_CREW + slot) : slot;
	const int away = (mySlot - pvpTurnSlot + PVP_TURN_TOTAL) % PVP_TURN_TOTAL;

	//2 / 3 차는 횟수로 나간다. 몇 번 남았는지를 그대로 채운다.
	const int side = defender ? 1 : 0;
	const int done = pvpTurnCount[side][slot];
	const int turnClock[3] = {
		PVP_TURN_TOTAL - away,
		done % PVP_SKILL2_EVERY,
		done % PVP_SKILL3_EVERY
	};
	const int need[3] = { PVP_TURN_TOTAL, PVP_SKILL2_EVERY, PVP_SKILL3_EVERY };
	const int* cool = turnClock;
	const int iconY = y - (rowH - iconSize) / 2;
	const int iconX = defender ? x + 3 * _2X : x + 27 * _2X;

	for (int k = 0; k < 3; ++k) {
		const int skill = crewData[crewIdx * CREWDATASIZE + CREWDATA_SKILL1 + k];

		PvpDrawSkillClock(skill, cool[k], need[k],
			iconX + (iconSize + gap) * k, iconY,
			iconSize, k == 2, obj);
	}
}

static void PvpInitHudBars(int hudTop)
{
	memset(pvpHeroHudBar, 0, sizeof(pvpHeroHudBar));
	memset(pvpCrewHudBar, 0, sizeof(pvpCrewHudBar));
	const int teamW = DX / 2;
	const int crewW = 78 * _2X;
	const int crewH = 28 * _2X;

	for (int side = 0; side < 2; ++side) {
		BAR* hero = &pvpHeroHudBar[side];
		hero->active = true;
		hero->x = side == 0 ? -teamW : DX;
		hero->y = hudTop - 2 * _2X;
		hero->targetX = side == 0 ? 2 * _2X : teamW;
		hero->targetY = hero->y;
		hero->speed = 10 * _2X;

		for (int i = 0; i < MAXCREW; ++i) {
			BAR* b = &pvpCrewHudBar[side][i];
			const int col = i % 2;
			const int row = i / 2;
			b->active = true;
			b->x = side == 0 ? -crewW - i * 4 * _2X
				: DX + i * 4 * _2X;
			b->y = hudTop - 50 * _2X - row * (crewH + 1 * _2X);
			b->targetX = side * teamW + col * crewW + 2 * _2X;
			b->targetY = b->y;
			b->speed = 9 * _2X;
		}
	}
	pvpHudBarsReady = true;
}

static void PvpDrawCombatHud(void)
{
	//전장/디오라마의 클립과 좌표를 이어받지 않는다. 화면에서 보이던 위치보다
	//64 실제 픽셀 아래로 내린 138 단위 높이에 고정한다.
	UnSectionClip(false);
	const int hudTop = 138 * _2X;
	if (!pvpHudBarsReady)
		PvpInitHudBars(hudTop);

	for (int side = 0; side < 2; ++side) {
		GotoPositionBar(&pvpHeroHudBar[side],
			pvpHeroHudBar[side].targetX, pvpHeroHudBar[side].targetY,
			pvpHeroHudBar[side].speed);
		for (int i = 0; i < MAXCREW; ++i) {
			if (pvpTestFrame >= i * 2)
				GotoPositionBar(&pvpCrewHudBar[side][i],
					pvpCrewHudBar[side][i].targetX,
					pvpCrewHudBar[side][i].targetY,
					pvpCrewHudBar[side][i].speed);
		}
	}
	//샘플처럼 하단을 짙은 남색으로 묶고, 각 팀의 히어로 정보는 서로
	//떨어진 플로팅 패널로 올린다.
	//SetAlpha(30);
	//MemRect(0, hudTop, DX, hudTop, 0x071229);
	//SetAlpha(32);
	const int heroPanelPad = 2 * _2X;
	const int heroPanelW = DX / 2 - heroPanelPad * 2;
	const int heroPanelH = 47 * _2X;
	const int leftPanelX = pvpHeroHudBar[0].x + heroPanelPad;
	const int rightPanelX = pvpHeroHudBar[1].x + heroPanelPad;
	const char* myNickname = robin.nickname.empty()
		? "Guest" : robin.nickname.c_str();
	PvpDrawPanel(leftPanelX, hudTop - 2 * _2X,
		heroPanelW, heroPanelH, true, profileImg[0], myNickname, false);
	PvpDrawPanel(rightPanelX, hudTop - 2 * _2X,
		heroPanelW, heroPanelH, true, (int)enemyHouse.userProfileImgIdx,
		"RIVAL COPY", true);
	const int heroY = hudTop - 43 * _2X;
	const int leftHeroX = pvpHeroHudBar[0].x + 25 * _2X;
	const int rightHeroX = pvpHeroHudBar[1].x + heroPanelW - 21 * _2X;
	DrawPlayer(&ao[PVP_ATTACKER_ROBIN], motionData[0], leftHeroX, heroY,
		RIGHT, 0.72f, 0, false, true);
	DrawPlayer(&ao[PVP_DEFENDER_ROBIN], motionData[0], rightHeroX, heroY,
		LEFT, 0.72f, 0, false, true);

	//보스 바의 원본 가로세로 비율은 그대로 둔다. 이름 줄 아래에서 시작해
	//프레임 하단까지 쓰도록 내려 이름과 체력 숫자가 겹치지 않게 한다.
	const float hpZoom = 0.38f;
	const int hpCenterOffset = 100 * _2X;
	VsHpBarDraw(pvpTestPlayerHp, pvpTestPlayerMaxHp,
		leftPanelX + hpCenterOffset, hudTop - 45 * _2X,
		BARCOLOR_GREEN, hpZoom);
	VsHpBarDraw(pvpTestEnemyHp, pvpTestEnemyMaxHp,
		rightPanelX + heroPanelW - hpCenterOffset, hudTop - 45 * _2X,
		BARCOLOR_RED, hpZoom);

	//---- 동료 2열 x 3행 ----
	//
	//STATUSWIN_Y를 쓰면 디오라마가 오르내릴 때 이 여섯 명도 같이 움직인다.
	//모든 좌표를 hudTop과 화면 바닥에서만 계산해 완전히 고정한다.
	for (int i = 0; i < MAXCREW; ++i) {
		PvpDrawCrewHud(i, false, &pvpCrewHudBar[0][i]);
		PvpDrawCrewHud(i, true, &pvpCrewHudBar[1][i]);
	}
}

void PvpTransitionCloudDraw(int transitionFrame)
{
	//cloud.png 네 장만 쓴다. 0은 네 장이 중앙에서 크게 포개져 화면을
	//완전히 덮은 상태, total은 좌/우/상/하 화면 밖으로 빠진 상태다.
	const int total = FPS + FPS / 2;
	float open = Min(1.0f, (float)transitionFrame / (float)Max(1, total));
	open = open * open * (3.0f - 2.0f * open);
	const float cloudZoom = (float)Max(DX, DY) * 0.88f / 512.0f;
	const int cloudW = (int)(512.0f * cloudZoom);
	const int cloudH = (int)(512.0f * cloudZoom);
	const int sideShift = (int)((cloudW + DX / 2) * open);
	const int verticalShift = (int)((cloudH + DY / 2) * open);
	const int centerX = DX / 2 - cloudW / 2;
	const int centerY = DY / 2 + cloudH / 2;

	DrawImage(512, 512, 0, 0, -cloudW / 5 - sideShift, centerY,
		false, false, false, false, false, cloudZoom, sprite[CLOUD_IMG], CLOUD_IMG);
	DrawImage(512, 512, 0, 0, DX - cloudW * 4 / 5 + sideShift, centerY,
		true, false, false, false, false, cloudZoom, sprite[CLOUD_IMG], CLOUD_IMG);
	DrawImage(512, 512, 0, 0, centerX, DY + cloudH / 5 + verticalShift,
		false, false, false, false, false, cloudZoom, sprite[CLOUD_IMG], CLOUD_IMG);
	DrawImage(512, 512, 0, 0, centerX, cloudH * 4 / 5 - verticalShift,
		false, true, false, false, false, cloudZoom, sprite[CLOUD_IMG], CLOUD_IMG);
}

static void PvpCastleStandOffDraw(void)
{
	SetAlpha(32);
	MemRect(0, DY, DX, DY, 0x05071D);
	for (int i = 0; i < 36; ++i) {
		const int sx = (i * 193 + 37) % Max(1, DX);
		const int sy = (i * 107 + 61) % Max(1, DY);
		const int size = (i % 7 == 0) ? 2 * _2X : 1 * _2X;
		SetAlpha(18 + (i + frame / 6) % 14);
		MemRectRound(sx, sy, size, size, 0xDCEBFF, size / 2);
	}
	SetAlpha(32);

	//큰 성은 빠르게 흔들면 가벼워 보인다. 진폭은 작게, 주기는 길게 둔다.
	const float floatY = sinf((float)pvpTestFrame * 0.012f) * 1.5f * _2X;
	//아군 성은 왼쪽 위, 적군 성은 오른쪽 아래로 엇갈린다. 같은 높이에 놓을
	//때보다 서로 침범하는 면적이 줄어 사선 구분을 유지하면서 조금 더 키울 수 있다.
	const float castleZoom = Min(0.60f,
		(float)DX * 0.60f / (float)DIORAMASIZE_X);
	const int leftX = (int)(DX * 0.18f);
	const int rightX = (int)(DX * 0.82f);
	//DrawImage의 y는 이미지 상단이고 아래쪽 끝은 y-height*zoom이다.
	//오른쪽 성의 하단을 하단 메뉴 윗선에 정확히 맞추고 왼쪽 성은 대치
	//구도를 유지할 만큼만 위에 둔다.
	const int rightCastleY = BOTTOMMENUHEIGHT
		+ (int)(DIORAMASIZE_Y * castleZoom);
	//현재 2배 좌표계에서 실제 화면 약 100픽셀만큼 위로 올린다.
	const int castleRaiseY = 50 * _2X;
	const int castleY[2] = {
		rightCastleY + castleRaiseY + (int)(DY * 0.28f + floatY),
		rightCastleY + castleRaiseY - (int)floatY
	};
	const int myCastle = castleOrder[robin.castle];
	const int foeCastle = pvpTestDefender.houseType;

	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0,
		leftX - DIORAMASIZE_X * castleZoom / 2, castleY[0],
		false, false, false, false, false, castleZoom,
		sprite[MAP_DIORAMA_IMG + myCastle], MAP_DIORAMA_IMG + myCastle);
	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0,
		rightX - DIORAMASIZE_X * castleZoom / 2, castleY[1],
		true, false, false, false, false, castleZoom,
		sprite[MAP_DIORAMA_IMG + foeCastle], MAP_DIORAMA_IMG + foeCastle);

	//원래 DrawDiorama가 사용하던 화면 좌표를 디오라마 내부의 0~1 좌표로
	//바꾼 뒤 각 성의 위치/배율에 다시 투영한다. 성을 움직이거나 띄워도
	//히어로와 동료는 성에 배치되어 있던 자리를 그대로 따라간다.
	const float sourceZoom = Max(0.001f, pvpSavedDioramaZoom);
	const float sourceLeft = xOffset + DX / 2.0f
		- DIORAMASIZE_X * sourceZoom / 2.0f;
	const float sourceTop = STATUSWIN_Y + DIORAMASIZE_Y * sourceZoom;
	const float sourceFloorY = STATUSWIN_Y + (rh - 4) * TSIZE;
	const float targetLeft[2] = {
		leftX - DIORAMASIZE_X * castleZoom / 2.0f,
		rightX - DIORAMASIZE_X * castleZoom / 2.0f
	};

	auto GetCastleObjectPoint = [&](const OBJECT* obj, int side,
		int* drawX, int* drawY) {
		const float sourceScreenX = xOffset + obj->x - pvpSavedRx;
		const float sourceScreenY = sourceFloorY
			- (obj->y - OBJIMGGAP) - pvpSavedRy;
		float localX = (sourceScreenX - sourceLeft)
			/ (DIORAMASIZE_X * sourceZoom);
		const float localY = (sourceTop - sourceScreenY)
			/ (DIORAMASIZE_Y * sourceZoom);
		if (side == 1)
			localX = 1.0f - localX;
		*drawX = (int)(targetLeft[side]
			+ localX * DIORAMASIZE_X * castleZoom);
		*drawY = (int)(castleY[side]
			- localY * DIORAMASIZE_Y * castleZoom);
	};

	for (int side = 0; side < 2; ++side) {
		int heroX, heroY;
		GetCastleObjectPoint(&pvpSavedObjects[PLAYER], side, &heroX, &heroY);
		OBJECT hero = pvpSavedObjects[PLAYER];
		DrawPlayer(&hero, motionData[0], heroX, heroY,
			side == 0 ? RIGHT : LEFT,
			castleZoom * DIORAMAZOOM_REMAINDER, 0, false, true);

		for (int i = 0; i < MAXCREW; ++i) {
			const OBJECT* crew = &pvpSavedObjects[CREW + i];
			if (!crew->active)
				continue;
			int crewX, crewY;
			GetCastleObjectPoint(crew, side, &crewX, &crewY);
			DrawCmfDetailShadow(crew->cmf, crewPos[crew->type * 5],
				crewX, crewY, side == 0 ? RIGHT : LEFT,
				castleZoom * DIORAMAZOOM_REMAINDER * enemyIconZoom[crew->type]);
		}
	}

	//좌하단에서 우상단으로 이어지는 연속 분할대. 가로 선분을 촘촘히 이어
	//한 장의 사선 마스크처럼 만들고, 성이 겹치는 중앙 부분을 이 암부로 가린다.
	const int pulse = (int)(2 * _2X
		* (0.5f + 0.5f * sinf(frame * 0.08f)));
	const int crackBottom = 0;
	const int crackTop = DY;
	const int crackBandHalf = 9 * _2X;
	const int scanH = Max(1, 2 * _2X);
	for (int crackY = crackBottom; crackY < crackTop; crackY += scanH) {
		const float t = (float)(crackY - crackBottom)
			/ (float)Max(1, crackTop - crackBottom);
		const int crackX = (int)(DX * (0.31f + 0.38f * t));
		SetAlpha(26);
		MemRect(crackX - crackBandHalf, crackY + scanH,
			crackBandHalf * 2, scanH + 1, 0x01020A);
		SetAlpha(15 + pulse);
		MemRect(crackX - crackBandHalf - 1 * _2X, crackY + scanH,
			2 * _2X, scanH + 1, 0x43A9FF);
		MemRect(crackX + crackBandHalf - 1 * _2X, crackY + scanH,
			2 * _2X, scanH + 1, 0xFF496B);
	}
	SetAlpha(32);

	const float profileSize = 36.0f * _2X;
	const int leftProfileY = Min(DY - 48 * _2X,
		castleY[0] - 8 * _2X);
	const int rightProfileY = rightCastleY + castleRaiseY
		- (int)(DIORAMASIZE_Y * castleZoom)
		+ (int)profileSize + 8 * _2X;
	UserProfileNameDraw(profileImg[0], robin.nickname.empty() ? "Guest" : robin.nickname.c_str(),
		8 * _2X, leftProfileY, profileSize,
		48 * _2X, leftProfileY - 16 * _2X, 0.90f, LEFT);
	UserProfileNameDraw((int)enemyHouse.userProfileImgIdx, "RIVAL COPY",
		DX - 8 * _2X - (int)profileSize, rightProfileY, profileSize,
		DX - 48 * _2X, rightProfileY - 16 * _2X, 0.90f, RIGHT);
	if (pvpTestFrame < FPS + FPS / 2) {
		SetAlpha(Min(32, Max(0, (FPS + FPS / 2 - pvpTestFrame) * 32 / Max(1, FPS / 2))));
		DrawGoldAlphaText(DX / 2, DY - 18 * _2X, "SIEGE READY",
			FONT_GOLD_LARGE, 0.72f, CENTER, true, -7.0f);
		SetAlpha(32);
	}
	DrawGoldAlphaText(DX / 2, DY / 2 + 18 * _2X, "VS",
		FONT_GOLD_LARGE,
		1.75f + 0.10f * sinf((float)pvpTestFrame * 0.08f),
		CENTER, true, -7.0f);
}

void PvpTestDraw(void)
{
	ResetRectPoint();
	if (pvpObjectsSaved && pvpTestState == -1) {
		//두 성과 승무원 배치를 잠깐 보여 준 뒤 실제 적 성 전장으로 전환한다.
		PvpCastleStandOffDraw();
		pvpTestFrame++;
		if (pvpTestFrame >= FPS * 2) {
			pvpTestState = 0;
			pvpTestFrame = 0;
		}
		return;
	}

	// 월드/캐릭터/총탄/피격 이펙트는 Play()->DrawScreen()->DrawDiorama가
	// 실제 ao[]를 기준으로 이미 그렸다. 이 함수는 PVP 진행과 화면 UI만 담당한다.
	if (pvpObjectsSaved) {
		const int groundY = STATUSWIN_Y + 78 * _2X;
		const bool chestOpen = pvpTestState >= 4;


		pvpTestPlayerHp = Max((long long)0, ao[PVP_ATTACKER_ROBIN].hp);
		pvpTestEnemyHp = Max((long long)0, ao[PVP_DEFENDER_ROBIN].hp);
		if (pvpTestState != 0)
			PvpDrawCombatHud();

		//격돌 화면에는 양 팀 정보와 VS만 남긴다. 전투용 GNB는 구름 전환이
		//끝나 실제 교전 상태에 들어간 뒤부터 표시한다.
		if (pvpTestState != 0) {
			BarDraw(&bar[BAR_CROWN], bar[BAR_CROWN].zoom);
			BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);
			BarDraw(&bar[BAR_STAR], bar[BAR_STAR].zoom);
			GNBDraw(0, DY - (GNBHEIGHT - GNB_INIT_HEIGHT));
		}

		if (pvpTestState == 0) {
			const int loadingHold = FPS / 2;
			const int reveal = FPS + FPS / 2;
			const int revealEnd = loadingHold + reveal;
			const float battleZoom = DIORAMAZOOM_BATTLE + dioramaZoomGap;

			if (pvpTestFrame < loadingHold) {
				//씬과 전투 개체 준비가 끝날 때까지 네 구름을 완전히 닫아 둔다.
				PvpTransitionCloudDraw(0);
			}
			else {
				float t = Min(1.0f, (float)(pvpTestFrame - loadingHold)
					/ (float)Max(1, reveal));
				const float ease = 1.0f - powf(1.0f - t, 3.0f);
				dioramaZoom = battleZoom * (0.12f + 0.88f * ease);
				PvpTransitionCloudDraw((int)((FPS + FPS / 2) * t));
			}

			if (pvpTestFrame >= revealEnd) {
				dioramaZoom = battleZoom;
				pvpTestState = 1;
				pvpTestFrame = 0;
				StartPvpTestBattle();
			}
		}
		else if (pvpTestState == 1) {
			// 외부 상태 변경으로 이 프레임에 들어와도 조작을 기다리지 않는다.
			StartPvpTestBattle();
		}
		else if (pvpTestState == 2) {
			UpdatePvpCombatLoop();

			if (ao[PVP_DEFENDER_ROBIN].dead || ao[PVP_DEFENDER_ROBIN].hp <= 0) {
				pvpTestState = 3;
				pvpTestFrame = 0;
				pvpLootSwing = false;

				//moveHandler 는 그대로 둔다. 상자 앞에서 한 대 쳐야 하는데,
				//공격 모션을 넘기는 것이 PlayerMove 다. 끄면 칼을 든 자세로
				//굳는다. 표적(수비 히어로)이 죽었으므로 PvpHeroStep 은 첫 줄에서
				//되돌아가고, 여기서 정한 자리와 모션만 남는다.
				for (int i = 0; i < MAXCREW; i++)
					ao[PVP_DEFENDER_CREW + i * MAXENEMYOBJ].active = false;
			}
			else if (ao[PVP_ATTACKER_ROBIN].dead || ao[PVP_ATTACKER_ROBIN].hp <= 0) {
				pvpTestState = 5;
				pvpTestFrame = 0;
			}
		}
		else if (pvpTestState == 3) {
			//---- 상자 앞까지 가서 한 대 친다 ----
			//
			//상대를 눕혔다고 상자가 저절로 열리지는 않는다. 걸어가서 내리쳐야
			//열린다 - 전투가 끝나고도 한 번 더 할 일이 남아 있어야 약탈이
			//약탈로 보인다.
			OBJECT* hero = &ao[PVP_ATTACKER_ROBIN];
			const int box = PvpLootBoxObj();
			const int stopX = (box >= 0)
				? ao[box].x - GetAttackRange(PVP_ATTACKER_ROBIN)
				: (int)(DX - 118 * _2X);
			int loopMotion;

			hero->dirX = hero->dirF = RIGHT;

			if (hero->attack) {
				//치는 중이다. 모션은 PlayerMove 가 넘긴다.
			}
			else if (hero->x < stopX) {
				hero->x = Min(stopX, hero->x + PVP_HERO_SPEED);
				hero->nx = hero->x;
				hero->frame++;
				loopMotion = GetHeroLoopMotion(hero->cmf, HEROLOOP_RUN,
					hero->frame);
				hero->motion = (loopMotion < 0)
					? PO_C0_R0 + walkFrame[hero->frame / 2 % 4] : loopMotion;
			}
			else if (pvpLootSwing == false) {
				//상자 앞이다. 한 대.
				pvpLootSwing = true;
				hero->x = hero->nx = stopX;
				hero->attack = ATTACK_NORMAL;
				GetMotionPtr(hero);
				hero->attackFrame = skillStartFrame[ATTACK_NORMAL];
				HitCountCheck(hero);
			}
			else {
				//다 쳤다. 뚜껑이 열린다.
				PvpOpenLootBox(box);
				pvpTestState = 4;
				pvpTestFrame = 0;
			}

			CenterTextStrSolid("TREASURE!", DX / 2, DY - 112 * _2X, 1.35f);
		}
		else if (pvpTestState == 4) {
			//---- 동전이 쏟아지고 골드바로 빨려 들어간다 ----
			//
			//한꺼번에 다 내보내지 않는다. 개체 칸이 모자라기도 하고, 무엇보다
			//한 프레임에 다 나오면 쏟아지는 것으로 안 보인다.
			for (int n = 0; n < PVP_LOOT_SPAWN_PER_FRAME
				&& pvpLootCoinLeft > 0 && pvpLootBox >= 0; n++) {
				//마지막 한 개가 남은 몫을 다 가져간다. 나누어 떨어지지 않아
				//생기는 잔돈이 사라지지 않게.
				const long long amount = (pvpLootCoinLeft > 1)
					? pvpLootCoinUnit : pvpLootLeft;
				const int coin = DropItem(&ao[pvpLootBox], ITEM_GOLD);

				//빈 칸이 없으면 다음 프레임에 다시 온다.
				if (coin < ITEMOBJ)
					break;

				ao[coin].defaultZoom = ao[coin].zoom = 1.5f;
				ao[coin].ax = (int)amount;

				//ENEMY 보다 작은 번호는 "우리가 먹는다" 는 뜻이다.
				ao[coin].target = PVP_ATTACKER_ROBIN;

				pvpLootLeft -= amount;
				pvpLootCoinLeft--;
			}

			//동전이 다 나올 때까지 뚜껑을 열어 둔다.
			if (pvpLootBox >= 0 && pvpLootCoinLeft > 0)
				ao[pvpLootBox].levelUpFrame = FPS;

			char lootText[64];
			sprintf(lootText, "GOLD +%lld", pvpTestLoot);
			SetFontColor(0xFFD43B);
			CenterTextStrSolid("RAID SUCCESS", DX / 2, DY - 112 * _2X, 1.55f);
			CenterTextStrSolid(lootText, DX / 2, DY - 142 * _2X, 1.2f);
			SetFontColor(COLOR_WHITE);

			//마지막 한 닢까지 골드바에 들어가야 끝난다. 땅에 남은 동전과
			//날아가는 중인 표시를 둘 다 본다.
			if (pvpLootCoinLeft == 0 && currencyMarkCnt == 0
				&& PvpLootCoinAlive() == false) {
				pvpTestState = 6;
				pvpTestFrame = 0;
			}
		}
		else if (pvpTestState == 6) {
			//---- 들어올 때처럼 닫고 나간다 ----
			//
			//열리며 들어왔으니 닫히며 나간다. 같은 그림을 거꾸로 돌린다.
			const int total = FPS + FPS / 2;

			CenterTextStrSolid("RAID SUCCESS", DX / 2, DY - 112 * _2X, 1.55f);
			PvpTransitionCloudDraw(total
				* Max(0, PVP_LOOT_CLOSE_FRAME - pvpTestFrame)
				/ PVP_LOOT_CLOSE_FRAME);

			if (pvpTestFrame >= PVP_LOOT_CLOSE_FRAME) {
				ExitPvpTest();
				return;
			}
		}
		else {
			SetFontColor(0xFF7777);
			CenterTextStrSolid("RAID FAILED", DX / 2, DY - 112 * _2X, 1.55f);
		}

		SetFontColor(COLOR_WHITE);
		pvpTestFrame++;
		return;
	}

	const float castleZoom = (float)DX / (float)DIORAMASIZE_X;
	const int castleX = 0;
	const int castleY = STATUSWIN_Y + (int)((float)DIORAMASIZE_Y * castleZoom);
	const int groundY = STATUSWIN_Y + 78 * _2X;

	//현재 내 성을 상대 성 데이터의 임시 복사본으로 사용한다. 공격받는 성이므로
	//배경 원본을 좌우 반전해서 수비측 출입구/배치를 오른쪽 방향으로 보이게 한다.
	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0,
		castleX, castleY, true, false, false, false, false,
		castleZoom, sprite[MAP_DIORAMA_IMG + pvpTestDefender.houseType],
		MAP_DIORAMA_IMG + pvpTestDefender.houseType);

	//수비측 상자. 승리 후 공격자가 여기까지 달려가 약탈한다.
	const bool chestOpen = pvpTestState >= 4;


	//성 위 수비 동료. 현재 슬롯의 타입을 그대로 사용하되 빈 슬롯은 건너뛴다.
	for (int i = 0; i < MAXCREW; i++) {
		int crewType = pvpTestDefender.crew[i];
		if (crewType > 0) {
			int cmf = enemyData[crewType * ENEMYDATASIZE + ENEMYDATA_CMF];
			int motion = crewPos[crewType * 5] + (frame / 8 + i) % Max(1, crewPos[crewType * 5 + 1]);
			DrawCmfDetailShadow(cmf, motion,
				DX - (82 + i * 54) * _2X,
				STATUSWIN_Y + (226 + (i % 2) * 28) * _2X,
				LEFT, 0.72f);
		}
	}

	//양측 로빈. 교전 중에는 간단한 왕복 흔들림으로 기본공격 타격감을 표시한다.
	const int combatFrame = Max(0, pvpTestFrame - 45);
	const bool playerStrike = pvpTestState == 2 && pvpTestFrame >= 45 && combatFrame % 42 < 12;
	const bool defenseStrike = pvpTestState == 2 && pvpTestFrame >= 45 && combatFrame % 42 >= 20 && combatFrame % 42 < 32;
	int fightPulse = playerStrike ? Abs((pvpTestFrame % 12) - 6) / 2 : 0;
	int enemyX = DX - 112 * _2X - fightPulse * _2X;
	int enemyMotion = defenseStrike ? ROBIN_ATTACK_NORMAL_START + (combatFrame % 12) :
		crewPos[ROBIN * 5] + frame / 8 % Max(1, crewPos[ROBIN * 5 + 1]);
	int playerMotion = playerStrike ? ROBIN_ATTACK_NORMAL_START + (combatFrame % 12) :
		crewPos[ROBIN * 5] + frame / 8 % Max(1, crewPos[ROBIN * 5 + 1]);
	DrawCmfDetailShadow(ROBIN, enemyMotion,
		enemyX, groundY, LEFT, 1.0f);
	DrawCmfDetailShadow(ROBIN, playerMotion,
		pvpTestPlayerX + fightPulse * _2X, groundY, RIGHT, 1.0f);

	//수비 동료의 일반 원거리 공격을 임시 탄도로 표시한다. 실제 스킬 오브젝트를
	//붙일 때에도 같은 42프레임 타격 시점을 사용한다.
	if (defenseStrike) {
		float t = (float)(combatFrame % 42 - 20) / 12.0f;
		int bulletX = (int)((DX - 132 * _2X) * (1.0f - t) +
			(pvpTestPlayerX + 16 * _2X) * t);
		int bulletY = groundY + 52 * _2X + (int)(12 * _2X * sin(t * M_PI));
		SetAlpha(22);
		MemRectRound(bulletX, bulletY, 18 * _2X, 6 * _2X,
			0xFFD34D, 3 * _2X);
		SetAlpha(32);
	}

	VsHpBarDraw(pvpTestPlayerHp, pvpTestPlayerMaxHp,
		86 * _2X, DY - 72 * _2X, BARCOLOR_GREEN, 0.58f);
	VsHpBarDraw(pvpTestEnemyHp, pvpTestEnemyMaxHp,
		DX - 86 * _2X, DY - 72 * _2X, BARCOLOR_RED, 0.58f);
	SetFontColor(COLOR_WHITE);
	CenterTextStrSolid("MY ROBIN", 86 * _2X, DY - 72 * _2X, 0.72f);
	CenterTextStrSolid("RIVAL COPY", DX - 86 * _2X, DY - 72 * _2X, 0.72f);

	//기존 상단 GNB 바 시리즈를 PVP에서도 유지한다. 전투 전용 체력 표시는
	//그 아래 줄에 별도로 둔다.
	BarDraw(&bar[BAR_CROWN], bar[BAR_CROWN].zoom);
	BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);
	BarDraw(&bar[BAR_STAR], bar[BAR_STAR].zoom);
	GNBDraw(0, DY - (GNBHEIGHT - GNB_INIT_HEIGHT));

	//공통 뒤로가기. 테스트 도중 언제든 원래 플레이 화면으로 복귀한다.
	MemRectRound(8 * _2X, DY - 8 * _2X, 42 * _2X, 34 * _2X,
		0x4B2788, 7 * _2X);
	CenterTextStrSolid("<", 29 * _2X, DY - 29 * _2X, 1.3f);
	SetRectPoint(8 * _2X, DY - 8 * _2X,
		42 * _2X, 34 * _2X, TOUCH_FUNC_PVP_TEST_BACK);

	if (pvpTestState == 0) {
		PvpTransitionCloudDraw(pvpTestFrame);
		CenterTextStrSolid("PVP RAID", DX / 2, DY - 112 * _2X, 1.55f);
		if (pvpTestFrame >= FPS + FPS / 2) {
			pvpTestState = 1;
			pvpTestFrame = 0;
			pvpTestPlayerX = 92 * _2X;
		}
	}
	else if (pvpTestState == 1) {
		//공격 전 정찰 구간. 사용자가 성/동료 배치를 충분히 본 뒤 GO를 누른다.
		const int goW = 126 * _2X;
		const int goH = 52 * _2X;
		const int goX = DX / 2 - goW / 2;
		const int goY = 72 * _2X;
		float press = GetButtonPressScale(goX, goY, goW, goH);
		int gapX = (int)((float)goW * (press - 1.0f) / 2.0f);
		int gapY = (int)((float)goH * (press - 1.0f) / 2.0f);
		MemRectRound(goX - gapX, goY + gapY,
			(int)((float)goW * press), (int)((float)goH * press),
			0x15952B, 10 * _2X);
		SetFontColor(COLOR_WHITE);
		CenterTextStrSolid("GO!", DX / 2, goY - goH / 2 + 7 * _2X, 1.8f * press);
		SetRectPoint(goX, goY, goW, goH, TOUCH_FUNC_PVP_TEST_GO);
		CenterTextStrSolid("상대 성을 확인한 뒤 공격하세요", DX / 2,
			goY + 28 * _2X, 0.78f);
	}
	else if (pvpTestState == 2) {
		if (pvpTestFrame < 45)
			pvpTestPlayerX = Min(164 * _2X, pvpTestPlayerX + 2 * _2X);

		//내 로빈의 기본공격과 상대 로빈+성 위 동료들의 일반공격을 교대로 표현한다.
		if (pvpTestFrame >= 45 && combatFrame > 0 && combatFrame % 42 == 0)
			pvpTestEnemyHp = Max((long long)0, pvpTestEnemyHp - pvpTestPlayerDamage);
		if (pvpTestFrame >= 45 && combatFrame > 20 && combatFrame % 42 == 20)
			pvpTestPlayerHp = Max((long long)0, pvpTestPlayerHp - pvpTestDefenseDamage);

		if (pvpTestEnemyHp <= 0) {
			pvpTestState = 3;
			pvpTestFrame = 0;
		}
		else if (pvpTestPlayerHp <= 0) {
			pvpTestState = 5;
			pvpTestFrame = 0;
		}
	}
	else if (pvpTestState == 3) {
		pvpTestPlayerX = Min(DX - 118 * _2X,
			pvpTestPlayerX + 4 * _2X);
		CenterTextStrSolid("TREASURE!", DX / 2, DY - 112 * _2X, 1.35f);
		if (pvpTestPlayerX >= DX - 118 * _2X) {
			pvpTestState = 4;
			pvpTestFrame = 0;
			//승리 시 HOUSE가 보유한 골드를 전부 약탈 대상으로 잡는다.
			//로컬 복사 상대(userId == -1)는 자기 돈을 복제 지급하지 않고 표시만 한다.
			pvpTestLoot = Max((long long)0, pvpTestDefender.gold);
			PlayMusic(M_OPENWINDOW);
		}
	}
	else if (pvpTestState == 4) {
		char lootText[64];
		sprintf(lootText, "GOLD +%lld", pvpTestLoot);
		SetFontColor(0xFFD43B);
		CenterTextStrSolid("RAID SUCCESS", DX / 2, DY - 112 * _2X, 1.55f);
		CenterTextStrSolid(lootText, DX / 2, DY - 142 * _2X, 1.2f);
	}
	else {
		SetFontColor(0xFF7777);
		CenterTextStrSolid("RAID FAILED", DX / 2, DY - 112 * _2X, 1.55f);
	}

	SetFontColor(COLOR_WHITE);
	pvpTestFrame++;
}

void GNBDraw(int x, int y)
{
	//---- 좌상단 퀵버튼 ----
	//
	//상점은 하단 네 칸의 첫 자리로 내려갔다. 같은 곳으로 가는 문이 화면에
	//둘이면 어느 쪽이 진짜인지 헷갈린다.
	//
	//PVP 시험 버튼은 성 메뉴 칸에서 아이콘을 빌려 쓰고 있었다. 그 자리는
	//이제 성 배지가 쓴다.
	//
	//두 버튼 다 자리만 비운다. 눌렀을 때 가는 곳은 그대로 살아 있다.
#if SHOW_SHOP_EVENT_ICON || SHOW_PVP_TEST_BUTTON
	if (curMenu == MENU_PLAY && drawHandle == MD_PLAY) {
		const float shopZoom = 0.72f;
		const float shopX = (float)x + 4.0f * _2X
			- (float)DX * GetBossRaidEntranceProgress();
		const float shopY = (float)y - 4.0f * _2X;
		const float pressZoom = GetButtonPressScale(
			shopX, shopY,
			(float)MAINMENU_X * shopZoom,
			(float)MAINMENU_Y * shopZoom);
		const float drawZoom = shopZoom * pressZoom;
		const float pressGapX = (float)MAINMENU_X * (drawZoom - shopZoom) / 2.0f;
		const float pressGapY = (float)MAINMENU_Y * (drawZoom - shopZoom) / 2.0f;

#if SHOW_SHOP_EVENT_ICON
		DrawBarIcon(BAR_MAINSHOP,
			(int)(shopX - pressGapX),
			(int)(shopY + pressGapY),
			drawZoom);

		if (menuPressPossible()) {
			SetRectPoint(shopX, shopY,
				(float)MAINMENU_X * shopZoom,
				(float)MAINMENU_Y * shopZoom,
				TOUCH_FUNC_SHOP);
		}
#endif

#if SHOW_PVP_TEST_BUTTON
		//PVP 서버 연결 전까지 쓰는 테스트 진입 버튼. 상점 바로 아래에 두며
		//아이콘은 임시로 성 메뉴 셀을 사용한다.
		const float pvpY = shopY - (float)MAINMENU_Y * shopZoom - 4.0f * _2X;
		const float pvpPress = GetButtonPressScale(
			shopX, pvpY,
			(float)MAINMENU_X * shopZoom,
			(float)MAINMENU_Y * shopZoom);
		const float pvpDrawZoom = shopZoom * pvpPress;
		const float pvpGapX = (float)MAINMENU_X * (pvpDrawZoom - shopZoom) / 2.0f;
		const float pvpGapY = (float)MAINMENU_Y * (pvpDrawZoom - shopZoom) / 2.0f;

		DrawBarIcon(BAR_CASTLE,
			(int)(shopX - pvpGapX),
			(int)(pvpY + pvpGapY),
			pvpDrawZoom);
		CenterTextStrSolid("PVP",
			(int)(shopX + (float)MAINMENU_X * shopZoom / 2.0f),
			(int)(pvpY - (float)MAINMENU_Y * shopZoom + 8.0f * _2X),
			0.62f);

		if (menuPressPossible()) {
			SetRectPoint(shopX, pvpY,
				(float)MAINMENU_X * shopZoom,
				(float)MAINMENU_Y * shopZoom,
				TOUCH_FUNC_PVP_TEST);
		}
#endif
	}
#endif

	//�޴���ư
	DrawImage(140, 145, 1, 1, x + DX - (float)148 * 0.45f, y - 1 * _2X, false, false, false, false, false, 0.45f, sprite[UI_NEW_IMG], UI_NEW_IMG);
	switch (drawHandle) {
	default:
		if (curMenu == MENU_PLAY) {
			if (xOffset != 0)//ȭ���� 
				SetRectPoint(x, y, DX, DY, (curMenu == MENU_PLAY ? TOUCH_FUNC_GAMEMENU : TOUCH_FUNC_GAMEMENU_OUT));
			else
				SetRectPoint(x + DX - 36 * _2X, y, 36 * _2X, 40 * _2X, (curMenu == MENU_PLAY ? TOUCH_FUNC_SETTING : TOUCH_FUNC_GAMEMENU_OUT));
		}
		else {
			//우측상단 톱니바퀴는 환경설정 팝업을 띄운다.
			SetRectPoint(x + DX - 36 * _2X, y, 36 * _2X, 40 * _2X, (curMenu == MENU_PLAY ? TOUCH_FUNC_SETTING : TOUCH_FUNC_GAMEMENU_OUT));
		}
		break;
	case MD_BATTLE:
		//SetRectPoint(x, y, DX, DY, (curMenu == MENU_PLAY ? TOUCH_FUNC_GAMEMENU : TOUCH_FUNC_GAMEMENU_OUT));
		break;
	case MD_BOSSRAID:
		// 보스전에서도 우측 상단 환경설정은 같은 자리에 그대로 둔다.
		SetRectPoint(x + DX - 36 * _2X, y, 36 * _2X, 40 * _2X,
			TOUCH_FUNC_SETTING);
		break;
	}
}

void ActiveHelpDraw()
{

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

//떠 있는 로그창을 스팟라이트 암전에서 빼준다.
//로그는 화면 맨 위에 얹는 알림이라 안내용 암전에 같이 묻히면 읽을 수가 없다.
//사각형은 LogDraw()가 DrawFrame()에 넘기는 것과 같은 값이다.
void KeepLogFromDarken(LOG* g)
{
	if (g->frame <= 0 && g->frame2 <= 0)
		return;

	SetSpotlightKeepRect(
		g->x - (float)(LOG_X / 2) * g->zoom,
		g->y + (float)(LOG_Y / 2) * g->zoom,
		(float)LOG_X * g->zoom,
		(float)LOG_Y * g->zoom,
		8 * _2X);
}

void LogDraw(LOG* g)
{
	int enemyType = GetTypeFromCmf(g->cmf);

	//로그는 화면 맨 위에 얹는 알림이라 어떤 화면 위에서도 통째로 보여야 한다.
	//앞서 그린 메뉴가 SetSectionClip()을 걸어둔 채로 넘어오면 DrawTextStrSystem()의
	//클리핑 검사(y > clipY)에 걸려 틀과 아이콘만 남고 글자가 통째로 사라진다.
	UnSectionClip(false);

	//위로 빠져나가기 시작할 때 살짝 주저앉았다 튀어 오르는 반동.
	//frame2가 2차 목적지(화면 위)로 올라가는 구간의 프레임 수라 그 앞머리에만 준다.
	//아래 그리기가 전부 g->y를 기준으로 하므로 그리는 동안만 값을 옮기고 끝에서 되돌린다.
	const int BOUNCEFRAME = FPS / 5;
	int logYBack = g->y;

	if (g->frame2 > 0 && g->frame2 < BOUNCEFRAME)
		g->y -= (int)((float)(6 * _2X) * sinf(3.141592f * (float)g->frame2 / (float)BOUNCEFRAME));

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
	case LOG_SIMPLE:
	{
		//왼쪽에 아이콘 한 개, 오른쪽에 한 줄 텍스트. 아이콘은 종류마다 그리는 함수가 다르다.
		//지나가는 알림이라 읽을 시간이 짧다. 아이콘/글자를 크게 잡는다.
		const float ICONZOOM = 2.4f;		//아이콘 배율
		const float TEXTZOOM = 1.1f;		//글자 배율
		const int ICONBOX = 40 * _2X;		//아이콘이 차지하는 폭

		float iconX = g->x - (float)(LOG_X / 2) * g->zoom + (float)(10 * _2X) * g->zoom;
		float iconY = g->y + (float)(LOG_Y / 2) * g->zoom - (float)(10 * _2X) * g->zoom;
		//글자는 아이콘에서 8픽셀 더 떼고, 캐릭터는 4픽셀 왼쪽으로 붙인다.
		float textX = g->x - (float)(LOG_X / 2) * g->zoom + (float)(10 * _2X + ICONBOX) * g->zoom + 8;
		float textW = (float)(LOG_X - 20 * _2X - ICONBOX) * g->zoom - 8;

		switch (g->iconType) {
		case LOGICON_CREW:
		{
			//동료는 아이콘이 없다. 실제 캐릭터 그림(cmf)을 그대로 쓴다.
			//crewPos[]는 타입별 서있는 모션의 시작 프레임이라 cmf에서 타입을 되짚어야 한다.
			//DrawCmfDetailShadow()는 발밑 기준이라 아이콘 칸 아래쪽에 세운다.
			int crewType = GetTypeFromCmf(g->iconA);

			//DrawCmfDetailShadow()는 발밑 기준이라 로그창 아래쪽에 세운다.
			//그대로 두면 바닥에 너무 붙어 보여서 8픽셀 띄운다(y는 위로 갈수록 커진다).
			DrawCmfDetailShadow(g->iconA, crewPos[crewType * 5 + 0],
				iconX + (float)(ICONBOX / 2) * g->zoom - 4,
				iconY - (float)(LOG_Y - 16 * _2X) * g->zoom + 8,
				RIGHT, g->zoom * 1.6f);
			break;
		}
		case LOGICON_EQUIP:
			//장비는 type/detail/grade에서 아이콘을 뽑는다.
			DrawIcon(GetItemIcon(g->iconA, g->iconB, g->iconC), iconX, iconY, g->zoom * ICONZOOM, false, false, true, true);
			break;
		case LOGICON_CASTLE:
			//성은 디오라마 그림을 축소해서 쓴다.
			DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0,
				iconX, iconY,
				false, false, false, false, false,
				0.16f * g->zoom,
				sprite[MAP_DIORAMA_IMG + g->iconA], MAP_DIORAMA_IMG + g->iconA);
			break;
		case LOGICON_ICON:
			DrawIcon(g->iconA + (g->iconA == ICON_GOLD ? frame % GOLDICONFRAME : 0), iconX, iconY, g->zoom * ICONZOOM, false, false, true, true);
			break;
		default:	//LOGICON_NONE - 아이콘 없이 텍스트만. 텍스트를 왼쪽 끝까지 당긴다.
			textX = g->x - (float)(LOG_X / 2) * g->zoom + (float)(10 * _2X) * g->zoom;
			textW = (float)(LOG_X - 20 * _2X) * g->zoom;
			break;
		}

		//로그 바탕(FRAME_SHOPBALLOON)이 밝아서 기본 폰트색(흰색)으로 쓰면 글자가 안 보인다.
		//LOG_SKILL/LOG_BETCOIN과 같은 방식으로 어두운 색을 씌우고 원래대로 돌려놓는다.
		SetFontColor(COLOR_BROWN);
		LineTextStrSolid(g->text, textX,
			g->y + (float)(LOG_Y / 2) * g->zoom - (float)(8 * _2X) * g->zoom,
			textW, -1, -1, g->zoom * TEXTZOOM);
		SetFontColor(COLOR_WHITE);
		break;
	}
	}

	//반동으로 옮겨놨던 y를 되돌린다. 이게 빠지면 매 프레임 조금씩 위로 밀려 올라간다.
	g->y = logYBack;
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

	int questRequest = questInfo[robin.quest * QUESTINFODATASIZE + 2];
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
#if SHOW_SHOP_EVENT_ICON
		InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_SHOP, false, ICON_EVENT_BOX, FREEITEMTIME, TOUCH_FUNC_EVENT_SHOP);
#endif
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
#if SHOW_SHOP_EVENT_ICON
		InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_SHOP, false, ICON_EVENT_BOX, SHOPEVENTTIME, TOUCH_FUNC_SHOP);
#endif

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

	bar[BAR_SOCIAL].targetX2 = bar[BAR_SOCIAL].targetX = bar[BAR_SOCIAL].nx;
	bar[BAR_SOCIAL].targetY2 = bar[BAR_SOCIAL].targetY = bar[BAR_SOCIAL].ny;
	bar[BAR_SOCIAL].speed2 = bar[BAR_SOCIAL].speed = 8 * _2X;
	bar[BAR_SOCIAL].speedIncrement2 = bar[BAR_SOCIAL].speedIncrement = 1 * _2X;
	bar[BAR_SOCIAL].zoom2 = bar[BAR_SOCIAL].zoom = BAR_SOCIAL_ZOOM;
	bar[BAR_SOCIAL].zoomIncrement2 = bar[BAR_SOCIAL].zoomIncrement = 0.0f;
	bar[BAR_SOCIAL].zoomEnd2 = bar[BAR_SOCIAL].zoomEnd = bar[BAR_SOCIAL].zoom;
	bar[BAR_SOCIAL].frame = 1;

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
	int i, j = 0;
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
#if !SHOW_SHOP_EVENT_ICON
	//상점은 하단 네 칸의 첫 자리에 있다. 같은 곳으로 가는 문이 화면에 둘이면
	//어느 쪽이 진짜인지 헷갈린다.
	//
	//만드는 자리만 막으면 이미 저장된 판에서는 아이콘이 그대로 남는다.
	//그리는 자리에서 막아야 없앤 것이 된다. 터치영역도 여기서 잡으므로
	//같이 사라진다.
	if (gEvent->type == EVENTTYPE_SHOP)
		return;
#endif

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

	// 3일 보스 아이콘은 전투 화면에 상시 노출되는 진입점이다. 일반 메뉴는
	// 공격 연출 중 입력을 막더라도, 이 아이콘의 입장 정보창까지 막으면
	// 그림만 보이고 눌리지 않는 상태가 된다.
	if (menuPressPossible() || gEvent->type == EVENTTYPE_BOSSRAID) {
		// 기존 세이브에 들어 있는 GAMEEVENT::touchFunc는 과거 enum 번호일 수
		// 있다. 보스 얼굴은 정상인데 다른 보스룸 명령이 실행되는 것을 막기
		// 위해 3일 보스만큼은 현재의 팝업 명령으로 강제 연결한다.
		int eventTouchFunc = gEvent->type == EVENTTYPE_BOSSRAID
			? TOUCH_FUNC_EVENT_BOSSRAID : gEvent->touchFunc;
		SetRectPoint(xOffset + gEvent->x + (float)(-ITEMICONSIZE - 4 * _2X) * gEvent->zoom,
			gEvent->y + (float)(ITEMICONSIZE + 4 * _2X) * gEvent->zoom,
			(float)(38 * _2X) * gEvent->zoom, (float)(38 * _2X) * gEvent->zoom,
			eventTouchFunc);
	}
}

void GoldQuestMenuDraw(int x, int y, float zoom)
{
	//창은 스스로 자리를 잡는다. 동료 상세와 같은 설계판을 쓰므로
	//받은 x/y/zoom 은 안 쓴다 - 세 곳에서 부르는데 저마다 다른 값을
	//넘겨서, 그대로 두면 부르는 자리마다 창이 다르게 보인다.
	(void)x; (void)y; (void)zoom;

	BossRaidDetailDraw();
	return;
#if 0
	int i, j;
	gEvent = &robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)];
	float gapX = (float)8 * _2X * zoom;
	float gapY = -(float)5 * _2X * zoom;

	float degree = 90.0f - atan((float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + 1 * 2 + 1] - goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + 0 * 2 + 1]) / (float)(goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + 1 * 2 + 0] - goldQuestPositionData[(int)(gEvent->barStatus) * BOSSRAIDSIZE * 2 + 0 * 2 + 0])) * 180 / M_PI;



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
#endif
}

void GameOverDraw(int x, int y, float zoom)
{
	int i;
	float fontZoom = 1.5f;

	//SetAlpha(20);
	//SetAlpha(32);

	DrawGoldAlpha(DX / 2, DY - GNBHEIGHT - 16 * _2X, ALPHA_STAGEFAILED, FONT_GOLD_LARGE, fontZoom * zoom, CENTER, true, false);

	//SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
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
		const int closingPopUpType = popUp[popUpCnt - 1].type;
		if (closingPopUpType == POPUPTYPE_FRIENDS || closingPopUpType == POPUPTYPE_READERBOARD)
			curMenu = MENU_PLAY;

		switch (closingPopUpType) {
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
	case POPUPTYPE_IAP_CONFIRM:
		IapConfirmDraw(p->itemType, p->itemDetail, p->x, p->y, p->zoom);
		break;
	case POPUPTYPE_GACHA_RATES:
		GachaRatesDraw(p->itemDetail);
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
		HeroStatDraw(&ao[curHero], xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_CREWUPGRADE:
		CrewMenuDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_CREWLIST:
		CrewMenuDraw(
			xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom,
			DY - GNBHEIGHT,
			p->zoom);
		break;
	case POPUPTYPE_COLLECTIONS:
		CollectionsDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, DY - GNBHEIGHT, p->zoom);
		break;
	case POPUPTYPE_FRIENDS:
		SocialDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom,
			p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_READERBOARD:
		SocialDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom,
			p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_OPTION:
		OptionDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_OPTION_LANGUAGE:
		OptionLanguageDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_OPTION_PUSHALARM:
		OptionPushAlarmDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_OPTION_HELP:
		OptionHelpDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * p->zoom, p->y + (float)POPUPWINDOWSIZE_Y / 2 * p->zoom, p->zoom);
		break;
	case POPUPTYPE_ENEMYUSER:
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

	//환경설정과 그 하위 창들은 창 자체의 타이틀바에 X버튼이 있으므로
	//좌측상단 뒤로가기를 그리지 않는다.
	//
	//동료 상세(menuDepth 1)도 마찬가지다. 그 창은 제 오른쪽 위에 닫기 버튼을
	//달고 있어서, 좌측상단 화살표까지 있으면 닫는 버튼이 둘이 된다. 게다가
	//화살표는 창 밖에 떠 있어서 어느 창을 닫는 것인지도 헷갈린다.
	//동료 상세와 장비 상세 둘 다 제 닫기 버튼을 달고 있다.
	bool detailOpen = ((p->type == POPUPTYPE_CREWLIST || p->type == POPUPTYPE_COLLECTIONS)
		&& menuDepth == 1);

	if (p->zoom == 1.0f && detailOpen == false
		&& (p->type != POPUPTYPE_ITEMCOMPARE && p->type != POPUPTYPE_STAGE && p->type != POPUPTYPE_GAMEOVER
		&& p->type != POPUPTYPE_OPTION
		&& p->type != POPUPTYPE_OPTION_LANGUAGE
		&& p->type != POPUPTYPE_OPTION_PUSHALARM
		&& p->type != POPUPTYPE_OPTION_HELP
		&& p->type != POPUPTYPE_IAP_CONFIRM
		&& p->type != POPUPTYPE_GACHA_RATES
		//멸망전 입장창도 제 오른쪽 위에 닫기 버튼을 달고 있다.
		&& p->type != POPUPTYPE_BOSSRAID)) {
		float xMarkZoom = 1.0f;
		DrawXMark((float)(18) * p->zoom, DY - GNBHEIGHT - (float)(22) * p->zoom, xMarkZoom* p->zoom);

		SetRectPoint((float)(18)* p->zoom, DY - GNBHEIGHT - (float)(22) * p->zoom, (float)64 * xMarkZoom * p->zoom, (float)64 * xMarkZoom * p->zoom, TOUCH_FUNC_POPUP_CLOSE);

		//튜토리얼 5단: 뒤로가기를 눌러 성으로 돌아가게 한다.
		//사각형은 바로 위 SetRectPoint()에 넘긴 것과 같은 값이라 스팟과 터치영역이 겹친다.
		if (GetTutorialCrewCloseTouchFunc() || GetTutorialEquipCloseTouchFunc()) {
			float bx = (float)(18) * p->zoom;
			float by = DY - GNBHEIGHT - (float)(22) * p->zoom;
			float bs = (float)64 * xMarkZoom * p->zoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			//손 크기는 앞 단계들과 같게 맞춘다.
			float handZoom = 2.0f;
			float handW = (float)imgArray[IMG_HAND1 * 4 + 2] * handZoom;
			float handH = (float)imgArray[IMG_HAND1 * 4 + 3] * handZoom;

			DrawHand(bx + bs / 2 - handW, by - bs / 2 + handH, robin.playtime / MOTIONDIV, handZoom);

			SetSpotlight(bx + bs / 2, by - bs / 2,
				bs * 0.6f * pulse, bs * 1.1f * pulse, 0.25f);
		}
	}

	p->frame++;
}

void GameMenuDraw(int x, int y, float zoom)
{
	int i, j;
	//int dy = 29 * _2X;
	int dy =  (DY - 16 * _2X - (GNBHEIGHT - GNB_INIT_HEIGHT)) / TOTAL_OPENEDMENU;
	int w = GAMEMENUWIN_X;

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



			//���������
			//if (robin.openedMenu[i] == CLOSE) {

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
				DrawBarIcon(BAR_SOCIAL, x, y - dy * j - (dy - ITEMICONSIZE * 2) / 2 - 8 * _2X + (float)(MAINMENU_Y / 2) * zoom, 0.8f * zoom);
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
				break;
			case MENU_GIFTS:
				break;
			case MENU_CALENDAR:
				break;
			case MENU_SETTING:
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
