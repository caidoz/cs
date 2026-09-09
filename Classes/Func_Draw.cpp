#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Text.h"


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
static int pvpTestState = 0; // 0 구름 진입, 1 GO 대기, 2 교전, 3 상자 이동, 4 약탈 완료, 5 패배
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
	pvpTestState = 0;
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
	dioramaZoom = DIORAMAZOOM_BATTLE + dioramaZoomGap;
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

	//---- 동료의 세 시계 ----
	for (int i = 0; i < MAXCREW; ++i) {
		OBJECT* pObj = &ao[CREW + i];

		if (!pObj->active || pObj->dead)
			continue;

		const int crewIdx = GetCrewIdxFromType(pObj->type);
		int base = BOSSRAID_CREW_COOLDOWN;

		if (crewIdx >= 0) {
			const int cool = crewData[crewIdx * CREWDATASIZE + CREWDATA_BOSSCOOL];

			if (cool > 0)
				base = cool;
		}

		const int need[3] = { base, base * PVP_SKILL2_MULT,
			base * PVP_SKILL3_MULT };

		for (int k = 0; k < 3; ++k)
			pvpCrewCool[i][k] = Min(need[k], pvpCrewCool[i][k] + 1);

		//---- 자세 ----
		pObj->frame++;

		if (pvpCrewShot[i] > 0) {
			const signed short* st = cmf_status_data[pObj->cmf][pObj->etc];
			const int cnt = Max(1, (int)st[0]);
			const int at = Min(cnt - 1, PVP_FOE_SHOTMOTION - pvpCrewShot[i]);

			pObj->motion = st[2 + at];
			pvpCrewShot[i]--;
		}
		else if (crewPos[pObj->type * 5 + 1] > 0) {
			pObj->motion = crewPos[pObj->type * 5]
				+ pObj->frame / 4 % crewPos[pObj->type * 5 + 1];
		}

		InitMotion(pObj);

		//---- 쿨타임이 차면 한 발 ----
		//
		//수비측과 같은 규칙이다. 1 차만 총알이고 2 / 3 차는 아직 없다.
		if (pvpCrewCool[i][0] < Max(1, need[0] / PVP_SKILL1_DIV))
			continue;

		pvpCrewCool[i][0] = 0;
		pObj->dirX = pObj->dirF = RIGHT;

		pObj->etc = enemyAttackPattern[
			pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + THERE];

		if (pObj->etc > 0)
			pvpCrewShot[i] = PVP_FOE_SHOTMOTION;

		PvpAllyShoot(CREW + i);
	}

	//---- 수비측 동료 ----
	//
	//성벽에 선 채로 쿨타임마다 우리 히어로에게 총알 한 발을 보낸다.
	//
	//몬스터 AI 를 안 쓴다. 두 가지가 안 맞아서다.
	//
	//    그 코드는 다가와서 때리는 것이라 성벽에 세우면 방향이 어긋난다
	//    동료 타입(NPC_*)에는 몬스터 발사체 데이터가 아예 없다
	//
	//쿨타임 씨앗은 아군과 같은 boss_cool 이다.
	for (int i = 0; i < MAXCREW; ++i) {
		const int obj = PVP_DEFENDER_CREW + i * MAXENEMYOBJ;
		OBJECT* pObj = &ao[obj];

		if (!pObj->active || pObj->dead)
			continue;

		const int crewIdx = GetCrewIdxFromType(pObj->type);
		int base = BOSSRAID_CREW_COOLDOWN;

		if (crewIdx >= 0) {
			const int cool = crewData[crewIdx * CREWDATASIZE + CREWDATA_BOSSCOOL];

			if (cool > 0)
				base = cool;
		}

		const int need[3] = { base, base * PVP_SKILL2_MULT,
			base * PVP_SKILL3_MULT };

		for (int k = 0; k < 3; ++k)
			pvpFoeCool[i][k] = Min(need[k], pvpFoeCool[i][k] + 1);

		//---- 자세 ----
		//
		//쏜 뒤 잠깐은 공격 자세, 나머지는 대기 자세다. 안 두면 총알만 나가고
		//사람은 가만히 서 있어서 누가 쐈는지 안 보인다.
		//
		//보는 쪽은 늘 표적이다. 못 박아 두면 히어로가 지나쳐 간 뒤에도
		//엉뚱한 데를 보고 쏜다.
		pObj->dirX = pObj->dirF =
			(ao[PVP_ATTACKER_ROBIN].x >= pObj->x) ? RIGHT : LEFT;
		pObj->frame++;

		if (pvpFoeShot[i] > 0) {
			const signed short* st = cmf_status_data[pObj->cmf][pObj->etc];
			const int cnt = Max(1, (int)st[0]);
			const int at = Min(cnt - 1, PVP_FOE_SHOTMOTION - pvpFoeShot[i]);

			pObj->motion = st[2 + at];
			pvpFoeShot[i]--;
		}
		else if (crewPos[pObj->type * 5 + 1] > 0) {
			pObj->motion = crewPos[pObj->type * 5]
				+ pObj->frame / 4 % crewPos[pObj->type * 5 + 1];
		}

		InitMotion(pObj);

		//---- 쿨타임이 차면 한 발 ----
		//
		//성벽에 선 채로 쏜다. 내려오지 않는다 - 지킬 자리를 떠나면 성 배치가
		//뜻이 없다.
		//
		//boss_cool 은 보스전 스킬 한 방을 재는 값이라 기본 총알로 쓰기엔
		//너무 길다. PVP_SKILL1_DIV 로 나눠 간격만 줄인다 - 동료별 개성은
		//그대로 남는다.
		//
		//1 차만 총알이다. 2 / 3 차 스킬은 아직 안 붙였다.
		if (pvpFoeCool[i][0] < Max(1, need[0] / PVP_SKILL1_DIV))
			continue;

		pvpFoeCool[i][0] = 0;

		//쏘는 자세로 쓸 공격패턴 상태. 없으면 대기 자세 그대로 둔다.
		pObj->etc = enemyAttackPattern[
			pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + THERE];

		if (pObj->etc > 0)
			pvpFoeShot[i] = PVP_FOE_SHOTMOTION;

		PvpFoeShoot(obj);
	}
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
static void PvpDrawPanel(int x, int y, int w, int h, bool hero)
{
	if (hero)
		DrawPvpHeroPanel(x, y, w, h);
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

	//쿨타임 식은 UpdatePvpCombatLoop 과 같아야 한다. 보여주는 값과 실제로
	//도는 값이 다르면 게이지가 거짓말을 한다.
	int base = crewData[crewIdx * CREWDATASIZE + CREWDATA_BOSSCOOL];

	if (base <= 0)
		base = BOSSRAID_CREW_COOLDOWN;

	const int need[3] = { base, base * PVP_SKILL2_MULT,
		base * PVP_SKILL3_MULT };
	const int* cool = defender ? pvpFoeCool[slot] : pvpCrewCool[slot];
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
	SetAlpha(30);
	MemRect(0, hudTop, DX, hudTop, 0x071229);
	SetAlpha(32);
	const int heroPanelPad = 2 * _2X;
	const int heroPanelW = DX / 2 - heroPanelPad * 2;
	const int heroPanelH = 47 * _2X;
	const int leftPanelX = pvpHeroHudBar[0].x + heroPanelPad;
	const int rightPanelX = pvpHeroHudBar[1].x + heroPanelPad;
	PvpDrawPanel(leftPanelX, hudTop - 2 * _2X,
		heroPanelW, heroPanelH, true);
	PvpDrawPanel(rightPanelX, hudTop - 2 * _2X,
		heroPanelW, heroPanelH, true);
	const int heroY = hudTop - 43 * _2X;
	const int leftHeroX = pvpHeroHudBar[0].x + 25 * _2X;
	const int rightHeroX = pvpHeroHudBar[1].x + heroPanelW - 21 * _2X;
	DrawPlayer(&ao[PVP_ATTACKER_ROBIN], motionData[0], leftHeroX, heroY,
		RIGHT, 0.72f, 0, false, true);
	DrawPlayer(&ao[PVP_DEFENDER_ROBIN], motionData[0], rightHeroX, heroY,
		LEFT, 0.72f, 0, false, true);

	SetFontColor(COLOR_WHITE);
	DrawTextStrSystem("MY ROBIN", leftPanelX + 48 * _2X,
		hudTop - 8 * _2X, 0.88f, LEFT, true);
	DrawTextStrSystem("RIVAL COPY", rightPanelX + heroPanelW - 48 * _2X,
		hudTop - 8 * _2X, 0.88f, RIGHT, true);
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

static void PvpTestCloudDraw(int transitionFrame)
{
	//룰렛의 중앙 암전 셔터와 이어진다. 검은 양쪽 문이 열리며 상대 성을
	//정찰하듯 드러내고, 경계의 청색/적색 선이 양 진영 방향을 남긴다.
	const int total = FPS + FPS / 2;
	float open = Min(1.0f, (float)transitionFrame / (float)Max(1, total));
	open = open * open * (3.0f - 2.0f * open);
	int panelW = DX / 2 + 4 * _2X;
	int shift = (int)((panelW + 12 * _2X) * open);
	MemRect(-shift, DY, panelW, DY, 0x08040D);
	MemRect(DX / 2 + shift, DY, panelW, DY, 0x08040D);
	SetAlpha((int)(28.0f * (1.0f - open)));
	MemRect(DX / 2 - shift - 3 * _2X, DY, 3 * _2X, DY, 0x3B87FF);
	MemRect(DX / 2 + shift, DY, 3 * _2X, DY, 0xFF3158);
	SetAlpha(32);
}

void PvpTestDraw(void)
{
	ResetRectPoint();

	// 월드/캐릭터/총탄/피격 이펙트는 Play()->DrawScreen()->DrawDiorama가
	// 실제 ao[]를 기준으로 이미 그렸다. 이 함수는 PVP 진행과 화면 UI만 담당한다.
	if (pvpObjectsSaved) {
		const int groundY = STATUSWIN_Y + 78 * _2X;
		const bool chestOpen = pvpTestState >= 4;


		pvpTestPlayerHp = Max((long long)0, ao[PVP_ATTACKER_ROBIN].hp);
		pvpTestEnemyHp = Max((long long)0, ao[PVP_DEFENDER_ROBIN].hp);
		PvpDrawCombatHud();

		BarDraw(&bar[BAR_CROWN], bar[BAR_CROWN].zoom);
		BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);
		BarDraw(&bar[BAR_STAR], bar[BAR_STAR].zoom);
		GNBDraw(0, DY - (GNBHEIGHT - GNB_INIT_HEIGHT));

		if (pvpTestState == 0) {
			PvpTestCloudDraw(pvpTestFrame);
			float titleIn = Min(1.0f, (float)pvpTestFrame / (float)Max(1, FPS / 4));
			DrawGoldAlphaText(DX / 2, DY - 92 * _2X, "RIVAL CASTLE",
				FONT_GOLD_LARGE, 1.35f * titleIn, CENTER, true, 0.0f);
			char scoutText[64];
			sprintf(scoutText, "CASTLE %d   LV %d",
				pvpTestDefender.houseType + 1, Max(1, pvpTestDefender.houseType + 1));
			SetFontColor(COLOR_WHITE);
			CenterTextStrSolid(scoutText, DX / 2, DY - 124 * _2X, 0.74f * titleIn);
			if (pvpTestFrame >= FPS + FPS / 2) {
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
				ao[PVP_ATTACKER_ROBIN].moveHandler = null;
				for (int i = 0; i < MAXCREW; i++)
					ao[PVP_DEFENDER_CREW + i * MAXENEMYOBJ].active = false;
			}
			else if (ao[PVP_ATTACKER_ROBIN].dead || ao[PVP_ATTACKER_ROBIN].hp <= 0) {
				pvpTestState = 5;
				pvpTestFrame = 0;
			}
		}
		else if (pvpTestState == 3) {
			ao[PVP_ATTACKER_ROBIN].dirX = ao[PVP_ATTACKER_ROBIN].dirF = RIGHT;
			ao[PVP_ATTACKER_ROBIN].x = Min((float)(DX - 118 * _2X),
				ao[PVP_ATTACKER_ROBIN].x + 4 * _2X);
			ao[PVP_ATTACKER_ROBIN].nx = ao[PVP_ATTACKER_ROBIN].x;
			CenterTextStrSolid("TREASURE!", DX / 2, DY - 112 * _2X, 1.35f);
			if (ao[PVP_ATTACKER_ROBIN].x >= DX - 118 * _2X) {
				pvpTestState = 4;
				pvpTestFrame = 0;
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
		PvpTestCloudDraw(pvpTestFrame);
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
