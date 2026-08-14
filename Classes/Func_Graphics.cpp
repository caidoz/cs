#include "Core.h"
#include "Func.h"
#include "Text.h"
#include "Data.h"

// Image Handling & Drawing
void NewGameImgLoad(void)
{
	int i;

	costumeImg[ROBIN] = ROBIN;
	costumeImg[DIANA] = DIANA;
	costumeImg[MAXX] = MAXX;

	ao[ROBIN].cmf = ao[ROBIN].type = ROBIN;
	ao[DIANA].cmf = ao[DIANA].type = DIANA;
	ao[MAXX].cmf = ao[MAXX].type = MAXX;

	for (i = ROBIN; i < TOTALPLAYER; i++) {
		memset(&ao[i].equipImg, 0, sizeof(ao[i].equipImg));
		ao[i].equipImg[EQUIP_WEAPON] = 1 + itemStartCnt[i];
	}
}

void LoadImg(int index)
{
	std::string fileName;
	fileName = null;
	//�̹����� �׳� �о �ε��ϴ� ���?
	if (index < TOTALIMG) {
		fileName = GetResourceName(RES_IMG, index);
		sprite[index] = Sprite::create(fileName);

		sprite[index]->retain();
		sprite[index]->getTexture()->setAliasTexParameters();
	}
}

void LoadTexture(int index)
{
	std::string fileName;

	//�̹����� �׳� �о �ε��ϴ� ���?
	if (index < TOTALIMG) {
		fileName = GetResourceName(RES_IMG, index);
		texture[index] = Director::getInstance()->getTextureCache()->addImage(fileName);
		//texture[index]->setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444);
		texture[index]->retain();
		//sprite[index]->setAnchorPoint(Vec2(0, 0));
		texture[index]->setAliasTexParameters();
	}
}

void LoadSpriteFromTexture(int textureIdx)
{
	GetSpriteIndex(textureIdx);
	//renderSprite[spriteIdx]->autorelease();

	//만약 이미지를 추가해야 된다면
	if (getSpriteIdx == totalRenderCnt) {
		renderSprite[getSpriteIdx] = Sprite::createWithTexture(texture[textureIdx]);
		renderSprite[getSpriteIdx]->retain();
		renderSpriteIndex[getSpriteIdx] = getSpriteTexture;

		sameRenderSpriteArr[textureIdx][sameRenderSpriteCur[textureIdx]] = totalRenderCnt;
		sameRenderSpriteMax[textureIdx]++;
		sameRenderSpriteCur[textureIdx]++;
		totalRenderCnt++;
	}
	//기존것을 쓴다면
	renderSprite[getSpriteIdx]->getTexture()->setAliasTexParameters();
	renderSprite[getSpriteIdx]->setOpacity((int)(m_lgrpAlpha * EMPTY / 32));
	renderSprite[getSpriteIdx]->setFlippedX(false);
	renderSprite[getSpriteIdx]->setRotation(0);
	renderSprite[getSpriteIdx]->setAnchorPoint(Vec2(0, 1.0f));

	if (grayScale)
		//renderSprite[getSpriteIdx]->setGLProgram(shader_gray);
		renderSprite[getSpriteIdx]->setGLProgram(GLProgramCache::getInstance()->getGLProgram("grayscale"));
	else
		renderSprite[getSpriteIdx]->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
}

void LoadBuffSpriteFromTexture(int textureIdx, cocos2d::Layer* cvtLayer)
{
	GetBufferSpriteIndex(textureIdx, cvtLayer);
	//renderSprite[spriteIdx]->autorelease();

	//만약 이미지를 추가해야 된다면
	if (getBufferSpriteIdx == totalBufferCnt) {
		bufferSprite[getBufferSpriteIdx] = Sprite::createWithTexture(texture[textureIdx]);
		bufferSprite[getBufferSpriteIdx]->retain();
		bufferSpriteIndex[getBufferSpriteIdx] = getBufferSpriteTexture;

		sameBufferSpriteArr[textureIdx][sameBufferSpriteCur[textureIdx]] = totalBufferCnt;
		sameBufferSpriteMax[textureIdx]++;
		sameBufferSpriteCur[textureIdx]++;
		totalBufferCnt++;
		cvtLayer->addChild(bufferSprite[getBufferSpriteIdx]);
	}
	//기존것을 쓴다면
	bufferSprite[getBufferSpriteIdx]->getTexture()->setAliasTexParameters();
	bufferSprite[getBufferSpriteIdx]->setOpacity((int)(m_lgrpAlpha * EMPTY / 32));
	bufferSprite[getBufferSpriteIdx]->setFlippedX(false);
	bufferSprite[getBufferSpriteIdx]->setRotation(0);
	bufferSprite[getBufferSpriteIdx]->setAnchorPoint(Vec2(0, 1.0f));
	if (grayScale)
		//renderSprite[getSpriteIdx]->setGLProgram(shader_gray);
		bufferSprite[getBufferSpriteIdx]->setGLProgram(GLProgramCache::getInstance()->getGLProgram("grayscale"));
	else
		bufferSprite[getBufferSpriteIdx]->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	curBufferSpriteArr[curBufferCnt] = getBufferSpriteIdx;
	curBufferCnt++;
}

//��ο���?������ �ܰ�. ���� ���� Ÿ�ٿ� ���� ���?�����?������.
//gRenderTarget �� ���� ������(BeginScreenBuffer/PushRenderTarget) �̹� begin() �� Ÿ�ٿ�
//���?visit() ���� �׸���. Ÿ���� ������/���� ������ �� ���� begin/end �ϹǷ�
//드로우 콜마다 렌더타겟을 바인딩하거나 renderer->render() 로 플러시하지 않는다.
//gRenderTarget �� nullptr �̸� ��������Ʈ�� ���� ���̴� ���Ž� ��θ�?����.
void AfterSpriting(cocos2d::Sprite* src) {

	if (gRenderTarget)
		src->visit();
	//화면버퍼를 쓰는 동안에는 Core::Run의 정리 루프가 removeChild를 하지 않는다.
	//그래서 여기서 addChild하면 씬에 영구히 남아 매 프레임 화면버퍼를 덮는다.
	//렌더타겟 밖에서 들어온 드로우는 그릴 곳이 없으므로 버린다.
	else if (!screenBuffer)
		curScene->addChild(src);

	//���?��ε�?�̹� �����ӿ� �� Ǯ ��������Ʈ�� �����?�д�.
	//Core::Run �� ������ �������� ��������Ʈ ���¸� �ǵ����� �� ���δ�.
	curRenderSpriteArr[curRenderCnt] = getSpriteIdx;
	curRenderCnt++;

	glBlendEquation(GL_FUNC_ADD);
}


//���� ��ε��Ǿ�?�ִ°� �����ؼ� ���?�ε����� ���?�Ǵ��� 
int GetSpriteIndex(int index)
{
	int i;
	int sameCnt = 0;
	getSpriteTexture = index;

	if (sameRenderSpriteCur[index] < sameRenderSpriteMax[index]) {
		for (i = 0; i < MAXRENDERCNT; i++) {
			if (renderSpriteIndex[i] == index) {
				if (sameRenderSpriteCur[index] == sameCnt) {
					sameRenderSpriteArr[index][sameRenderSpriteCur[index]] = i;
					sameRenderSpriteCur[index]++;
					getSpriteIdx = i;
					return i;
				}
				sameCnt++;
			}
		}
	}
	else {
		getSpriteIdx = totalRenderCnt;
		return totalRenderCnt;
	}

	return false;
}

//���� ��ε��Ǿ�?�ִ°� �����ؼ� ���?�ε����� ���?�Ǵ��� 
int GetBufferSpriteIndex(int index, cocos2d::Layer* cvtLayer)
{
	int i;
	int sameCnt = 0;
	getBufferSpriteTexture = index;

	if (sameBufferSpriteCur[index] < sameBufferSpriteMax[index]) {
		for (i = 0; i < MAXBUFFERSPRITECNT; i++) {
			if (bufferSpriteIndex[i] == index) {
				if (sameBufferSpriteCur[index] == sameCnt) {
					sameBufferSpriteArr[index][sameBufferSpriteCur[index]] = i;
					sameBufferSpriteCur[index]++;
					getBufferSpriteIdx = i;
					return i;
				}
				sameCnt++;
			}
		}
	}
	else {
		getBufferSpriteIdx = totalBufferCnt;
		return totalBufferCnt;
	}
	return false;
}

//���� ��ε��Ǿ�?�ִ°� �����ؼ� ���?�ε����� ���?�Ǵ��� 
int GetTextLabelIndex(int index)
{
	int i;
	int sameCnt = 0;
	getTextLabelTexture = index;

	if (sameTextLabelCur[index] < sameTextLabelMax[index]) {
		for (i = 0; i < MAXLABELCNT; i++) {
			if (textLabelIndex[i] == index) {
				if (sameTextLabelCur[index] == sameCnt) {
					sameTextLabelArr[index][sameTextLabelCur[index]] = i;
					sameTextLabelCur[index]++;
					getTextLabelIdx = i;
					return i;
				}
				sameCnt++;
			}
		}
	}
	else {
		getTextLabelIdx = totalTextLabelCnt;
		return totalTextLabelCnt;
	}

	return false;
}



std::string convertToString(char* a, int size)
{
	int i;
	std::string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

//Ÿ�԰� �ε����� ���� ���ϸ� ���� �� ���ϸ��� �� ���ۿ� ��Ƽ�?�����ϱ�
std::string  GetResourceName(int type, int idx)
{
	std::string fileName;

	//파일명 정하기
	fileName = null;

	switch (type) {
	case RES_MAP:
		fileName = "m" + std::to_string(idx) + ".dat";
		break;
	case RES_CMF:
		fileName = "cmf" + std::to_string(idx) + ".dat";
		break;
	case RES_IMG:
	{
		temp = TEXT_IMGNAME_START + idx;

		if (idx < MAP_TILE_IMG && idx >= ROBIN_PART_IMG) {
			if (idx >= ROBIN_PART_IMG && idx < DIANA_PART_IMG && costumeImg[ROBIN] != ROBIN)
				temp = TEXT_IMGNAME_START + idx + ROBIN_IMG_CNT * costumeImg[ROBIN];
			else if (idx >= DIANA_PART_IMG && idx < MAXX_PART_IMG && costumeImg[DIANA] != DIANA)
				temp = TEXT_IMGNAME_START + idx - DIANA_PART_IMG + ROBIN_PART_IMG + ROBIN_IMG_CNT * costumeImg[DIANA];
			else if (idx >= MAXX_PART_IMG && idx < RANK_PART_IMG && costumeImg[MAXX] != MAXX)
				temp = TEXT_IMGNAME_START + idx - MAXX_PART_IMG + ROBIN_PART_IMG + ROBIN_IMG_CNT * costumeImg[MAXX];
			else if (idx < MAP_TILE_IMG && idx >= RANK_PART_IMG)
				temp = TEXT_IMGNAME_START + idx - RANK_PART_IMG + ROBIN_PART_IMG + ROBIN_IMG_CNT * costumeImg[3];
		}

		//if (idx >= MONSTER_IMG)
		//	fileName = "res/" + textId[temp] + std::to_string(cmfLoaded[idx - MONSTER_IMG]) + ".png";
		//else if (idx >= MAP_BG_IMG)
		//	fileName = "res/" + textId[temp] + std::to_string(mapData[7]) + ".png";
		//else if (idx >= MAP_TILE_IMG)
		//	fileName = "res/" + textId[temp] + std::to_string(Min(MAPTYPE_DEVILCASTLE, mapData[7])) + ".png";
		//else if (idx >= FACE_IMG && idx <= CHAR_IMG)
		//	fileName = "res/" + textId[temp] + std::to_string(idx - FACE_IMG) + ".png";
		//else if (idx >= ITEM_IMG && idx <= FACE_IMG)
		//	fileName = "res/" + textId[temp] + std::to_string(idx - ITEM_IMG) + ".png";
		//else

		fileName = "res/" + std::string(textId[temp]) + ".png";

	}
	break;
	case RES_SOUND:
		fileName = "sounds/" + std::to_string(idx) + ".mp3";
		break;
	}

	return fileName;
}

int GetTypeByZoom(int type, int zoom)
{
	return type;
}

void DrawBuffer(int x, int y, int w, int h, cocos2d::RenderTexture* cvtDest)
{
	if (doubleBuffer) {
		cvtDest->setPosition(Vec2(x, y));
		//cvtDest->setAnchorPoint(Vec2(0.0f, 1.0f));
		cvtDest->getSprite()->setAnchorPoint(Vec2(0.0f, 1.0f));

		//�̸� �׷� �� ������ũ�� ���۸� ���� Ÿ��(ȭ�����?�� �ռ��Ѵ�.
		if (gRenderTarget) {
			//RenderTexture �� 3���� visit �����ε尡 0���� Node::visit() �� �����Ƿ�
			//Node* �� �޾Ƽ� ȣ���Ѵ�. ���ο��� RenderTexture �� �������̵��?���� ����ġ�ȴ�.
			cocos2d::Node* node = cvtDest;
			node->visit();
		}
		else
			curScene->addChild(cvtDest);
	}
}

void DrawArray(int index, int x, int y, float zoom)
{
	int res = Abs(index);
	int xs, ys, w, h;

	if (res < IMG_STAR)
		res = LOGO_IMG;
	else
		res = COMMON_IMG;

	if (!sprite[res])
		LoadImg(res);

	if (index < 0) {
		DrawImage(imgArray[-index * 4 + 2], imgArray[-index * 4 + 3], imgArray[-index * 4], imgArray[-index * 4 + 1], x, y, true, false, false, false, false, zoom, sprite[res], res);
		return;
	}

	xs = imgArray[index * 4];
	ys = imgArray[index * 4 + 1];
	w = imgArray[index * 4 + 2];
	h = imgArray[index * 4 + 3];

	x += offX;
	y += offY;
	//x -= imgArray[index * 4 + 4];
	//y -= imgArray[index * 4 + 5];

	DrawImage(w, h, xs, ys, x, y, false, false, false, false, false, zoom, sprite[res], res);
}

void RotateImage(int w, int h, int xs, int ys, int x, int y, bool flipX, float rotation, int effect, int alpha, float zoom, Vec2 anchorPoint, cocos2d::Sprite* src, int srcIdx)
{
	int tempAlpha = m_lgrpAlpha;

	if (alpha > 0) {
		SetAlpha(alpha);
	}


	GetSpriteIndex(srcIdx);

	if (getSpriteIdx == totalRenderCnt) {
		renderSprite[getSpriteIdx] = Sprite::createWithSpriteFrame(src->getSpriteFrame());
		renderSprite[getSpriteIdx]->retain();
		renderSpriteIndex[getSpriteIdx] = getSpriteTexture;

		sameRenderSpriteArr[srcIdx][sameRenderSpriteCur[srcIdx]] = totalRenderCnt;
		sameRenderSpriteMax[srcIdx]++;
		sameRenderSpriteCur[srcIdx]++;
		totalRenderCnt++;
	}

	renderSprite[getSpriteIdx]->getTexture()->setAliasTexParameters();

	//�׷��� ������
	if (grayScale) {
		if (grayScale != 32) {

		}
		renderSprite[getSpriteIdx]->setGLProgram(GLProgramCache::getInstance()->getGLProgram("grayscale"));
	}
	else
		renderSprite[getSpriteIdx]->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	//�����嵪��
	if (blendDepth) {
		renderSprite[getSpriteIdx]->setBlendFunc(BLEND_BLENDMODE);
	}
	//라이튼효과
	if (effect) {
		renderSprite[getSpriteIdx]->setBlendFunc(BLEND_LIGHTEN);
		glBlendEquation(GL_MAX_EXT);
		SetAlpha(m_lgrpAlpha - LIGHTENALPHA);
	}
	renderSprite[getSpriteIdx]->setOpacity((int)(m_lgrpAlpha * EMPTY / 32));
	renderSprite[getSpriteIdx]->setFlippedX(flipX);
	renderSprite[getSpriteIdx]->setScale(zoom);
	renderSprite[getSpriteIdx]->setAnchorPoint(anchorPoint);
	renderSprite[getSpriteIdx]->setRotation(rotation);

	renderSprite[getSpriteIdx]->setTextureRect(Rect(xs, ys, w, h));
	renderSprite[getSpriteIdx]->setPosition(Vec2(x, y));

	if (baseColor)//if (baseColor != 0x000000 && !baseColor)
	{
		if (baseColor == 0xFFFFFF && !grayScale)
			renderSprite[getSpriteIdx]->setGLProgram(GLProgramCache::getInstance()->getGLProgram("whitescale"));
		else
			renderSprite[getSpriteIdx]->setColor(Color3B((baseColor >> 16) & 0xFF, (baseColor >> 8) & 0xFF, baseColor & 0xFF));
	}
	else if (!grayScale)
		renderSprite[getSpriteIdx]->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));

	AfterSpriting(renderSprite[getSpriteIdx]);

	SetAlpha(tempAlpha);
}

void DrawImage(int w, int h, int xs, int ys, int x, int y, bool flipX, int cmfRotation, float rotation, int effect, int alpha, float zoom, cocos2d::Sprite* src, int srcIdx)
{
	DrawImageScale(
		w, h,
		xs, ys,
		x, y,
		flipX,
		cmfRotation,
		rotation,
		effect,
		alpha,
		zoom, zoom,   // ���� zoom�� X/Y ���� ������ ����
		src,
		srcIdx);
}

void DrawImageScale(int w, int h, int xs, int ys, int x, int y, bool flipX, int cmfRotation, float rotation, int effect, int alpha, float zoomX, float zoomY, cocos2d::Sprite* src, int srcIdx)
{
	if (zoomX <= 0.0f || zoomY <= 0.0f)
		return;

	int tempAlpha = m_lgrpAlpha;

#ifdef CLIPPING

	if (flipX == false) {
		switch (cmfRotation) {
		case 0:
			if (x < clipX) {
				xs += (float)(clipX - x) / zoomX;
				w -= (float)(clipX - x) / zoomX;
				x = clipX;
			}
			if (x + (float)w * zoomX > clipX2) {
				w = (float)(clipX2 - x) / zoomX;
			}
			if (y > clipY) {
				ys += (float)(y - clipY) / zoomY;
				h -= (float)(y - clipY) / zoomY;
				y = clipY;
			}
			if (y - (float)h * zoomY < clipY2) {
				h = (float)(y - clipY2) / zoomY;
			}
			if (w <= 0 || h <= 0)
				return;
			break;

		case 90:
			// ȸ�� 90�������� ȭ�� X�� ���̰� ���� h * zoomY
			// ȭ�� Y�� ���̰� ���� w * zoomX
			if (x < clipX) {
				h += (float)(x - clipX) / zoomY;
				x = clipX;
			}
			if (x + (float)h * zoomY > clipX2) {
				ys += (float)(x + (float)h * zoomY - clipX2) / zoomY;
				h = (float)(clipX2 - x) / zoomY;
			}
			if (y > clipY) {
				xs += (float)(y - clipY) / zoomX;
				w -= (float)(y - clipY) / zoomX;
				y = clipY;
			}
			if (y - (float)w * zoomX < clipY2) {
				w = (float)(y - clipY2) / zoomX;
			}
			if (w <= 0 || h <= 0)
				return;
			break;

		case 180:
			if (x < clipX) {
				w += (float)(x - clipX) / zoomX;
				x = clipX;
			}
			if (x + (float)w * zoomX > clipX2) {
				xs += (float)(x + (float)w * zoomX - clipX2) / zoomX;
				w = (float)(clipX2 - x) / zoomX;
			}
			if (y > clipY) {
				h -= (float)(y - clipY) / zoomY;
				y = clipY;
			}
			if (y - (float)h * zoomY < clipY2) {
				ys += (float)(clipY2 - ((float)y - (float)h * zoomY)) / zoomY;
				h -= (float)(clipY2 - ((float)y - (float)h * zoomY)) / zoomY;
			}
			if (w <= 0 || h <= 0)
				return;
			break;

		case 270:
			if (x < clipX) {
				ys += (float)(clipX - x) / zoomY;
				h -= (float)(clipX - x) / zoomY;
				x = clipX;
			}
			if (x + (float)h * zoomY > clipX2) {
				h -= (float)(x + (float)h * zoomY - clipX2) / zoomY;
			}
			if (y > clipY) {
				w -= (float)(y - clipY) / zoomX;
				y = clipY;
			}
			if (y - (float)w * zoomX < clipY2) {
				xs += (float)(clipY2 - ((float)y - (float)w * zoomX)) / zoomX;
				w = (float)(y - clipY2) / zoomX;
			}
			if (w <= 0 || h <= 0)
				return;
			break;
		}
	}
	else {
		switch (cmfRotation) {
		case 0:
			if (x < clipX) {
				w -= (float)(clipX - x) / zoomX;
				x = clipX;
			}
			if (x + (float)w * zoomX > clipX2) {
				xs += (float)(x + (float)w * zoomX - clipX2) / zoomX;
				w -= (float)(x + (float)w * zoomX - clipX2) / zoomX;
			}
			if (y > clipY) {
				ys += (float)(y - clipY) / zoomY;
				h -= (float)(y - clipY) / zoomY;
				y = clipY;
			}
			if (y - (float)h * zoomY < clipY2) {
				h = (float)(y - clipY2) / zoomY;
			}
			if (w <= 0 || h <= 0)
				return;
			break;

		case 90:
			if (x < clipX) {
				ys -= (float)(x - clipX) / zoomY;
				h += (float)(x - clipX) / zoomY;
				x = clipX;
			}
			if (x + (float)h * zoomY > clipX2) {
				h = (float)(clipX2 - x) / zoomY;
			}
			if (y > clipY) {
				xs += (float)(y - clipY) / zoomX;
				w -= (float)(y - clipY) / zoomX;
				y = clipY;
			}
			if (y - (float)w * zoomX < clipY2) {
				w -= (float)(clipY2 - (y - (float)w * zoomX)) / zoomX;
			}
			if (w <= 0 || h <= 0)
				return;
			break;

		case 180:
			if (x < clipX) {
				xs -= (float)(x - clipX) / zoomX;
				w += (float)(x - clipX) / zoomX;
				x = clipX;
			}
			if (x + (float)w * zoomX > clipX2) {
				w = (float)(clipX2 - x) / zoomX;
			}
			if (y > clipY) {
				h -= (float)(y - clipY) / zoomY;
				y = clipY;
			}
			if (y - (float)h * zoomY < clipY2) {
				ys += (float)(clipY2 - (y - (float)h * zoomY)) / zoomY;
				h -= (float)(clipY2 - (y - (float)h * zoomY)) / zoomY;
			}
			if (w <= 0 || h <= 0)
				return;
			break;

		case 270:
			if (x < clipX) {
				h += (float)(x - clipX) / zoomY;
				x = clipX;
			}
			if (x + (float)h * zoomY > clipX2) {
				ys += (float)(x + (float)h * zoomY - clipX2) / zoomY;
				h = (float)(clipX2 - x) / zoomY;
			}
			if (y > clipY) {
				w -= (float)(y - clipY) / zoomX;
				y = clipY;
			}
			if (y - (float)w * zoomX < clipY2) {
				xs += (float)(clipY2 - (y - (float)w * zoomX)) / zoomX;
				w = (float)(y - clipY2) / zoomX;
			}
			if (w <= 0 || h <= 0)
				return;
			break;
		}
	}

#endif

	if (alpha > 0) {
		SetAlpha(alpha);
	}

	GetSpriteIndex(srcIdx);

	if (getSpriteIdx == totalRenderCnt) {
		renderSprite[getSpriteIdx] = Sprite::createWithSpriteFrame(src->getSpriteFrame());
		renderSprite[getSpriteIdx]->retain();
		renderSpriteIndex[getSpriteIdx] = getSpriteTexture;

		sameRenderSpriteArr[srcIdx][sameRenderSpriteCur[srcIdx]] = totalRenderCnt;
		sameRenderSpriteMax[srcIdx]++;
		sameRenderSpriteCur[srcIdx]++;
		totalRenderCnt++;
	}

	renderSprite[getSpriteIdx]->getTexture()->setAliasTexParameters();

	if (grayScale) {
		renderSprite[getSpriteIdx]->setGLProgram(
			GLProgramCache::getInstance()->getGLProgram("grayscale")
		);
	}
	else {
		renderSprite[getSpriteIdx]->setGLProgram(
			GLProgramCache::getInstance()->getGLProgram(
				GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP
			)
		);
	}

	if (blendDepth) {
		renderSprite[getSpriteIdx]->setBlendFunc(BLEND_BLENDMODE);
	}

	if (effect) {
		renderSprite[getSpriteIdx]->setBlendFunc(BLEND_LIGHTEN);
		glBlendEquation(GL_MAX_EXT);
		SetAlpha(m_lgrpAlpha - LIGHTENALPHA);
	}

	renderSprite[getSpriteIdx]->setOpacity((int)(m_lgrpAlpha * EMPTY / 32));
	renderSprite[getSpriteIdx]->setFlippedX(flipX);

	renderSprite[getSpriteIdx]->setScaleX(zoomX);
	renderSprite[getSpriteIdx]->setScaleY(zoomY);

	switch (cmfRotation) {
	case 0:
		renderSprite[getSpriteIdx]->setRotation(rotation);
		renderSprite[getSpriteIdx]->setAnchorPoint(Vec2(0.0f, 1.0f));
		break;

	case 90:
		if (flipX == true) {
			renderSprite[getSpriteIdx]->setRotation(rotation + 270);
			renderSprite[getSpriteIdx]->setAnchorPoint(Vec2(1.0f, 1.0f));
		}
		else {
			renderSprite[getSpriteIdx]->setRotation(rotation + 90);
			renderSprite[getSpriteIdx]->setAnchorPoint(Vec2(0.0f, 0.0f));
		}
		break;

	case 180:
		renderSprite[getSpriteIdx]->setRotation(rotation + 180);
		renderSprite[getSpriteIdx]->setAnchorPoint(Vec2(1.0f, 0.0f));
		break;

	case 270:
		if (flipX == true) {
			renderSprite[getSpriteIdx]->setRotation(rotation + 90);
			renderSprite[getSpriteIdx]->setAnchorPoint(Vec2(0.0f, 0.0f));
		}
		else {
			renderSprite[getSpriteIdx]->setRotation(rotation + 270);
			renderSprite[getSpriteIdx]->setAnchorPoint(Vec2(1.0f, 1.0f));
		}
		break;
	}

	renderSprite[getSpriteIdx]->setTextureRect(Rect(xs, ys, w, h));
	renderSprite[getSpriteIdx]->setPosition(Vec2(x, y));

	if (baseColor) {
		if (baseColor == 0xFFFFFF && !grayScale) {
			renderSprite[getSpriteIdx]->setGLProgram(
				GLProgramCache::getInstance()->getGLProgram("whitescale")
			);
		}
		else {
			renderSprite[getSpriteIdx]->setColor(Color3B(
				(baseColor >> 16) & 0xFF,
				(baseColor >> 8) & 0xFF,
				baseColor & 0xFF
			));
		}
	}
	else if (!grayScale) {
		renderSprite[getSpriteIdx]->setGLProgram(
			GLProgramCache::getInstance()->getGLProgram(
				GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP
			)
		);
	}

	AfterSpriting(renderSprite[getSpriteIdx]);

	SetAlpha(tempAlpha);
}

void BrightImage(int w, int h, int xs, int ys, int x, int y, int res, float zoom)
{
	cocos2d::Sprite* src;

	if (m_lgrpAlpha == 0)
		return;

	x += offX;
	y += offY;
#ifdef CLIPPING
	if (x < clipX) { xs -= (x - clipX); w += (x - clipX); x = clipX; }
	if (x + w > clipX2) { w = clipX2 - x; }
	if (y > clipY) { ys += (y - clipY); h -= (y - clipY); y = clipY; }
	if (y - h < clipY2) { h = y - clipY2; }
	if (w <= 0 || h <= 0)
		return;
#endif

	if (!sprite[res])
		LoadImg(res);

	LoadSpriteFromTexture(res);
	src = renderSprite[getSpriteIdx];

	if (grayScale) {
		if (grayScale != 32) {

		}
		src->setGLProgram(GLProgramCache::getInstance()->getGLProgram("grayscale"));
	}
	else
		src->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));

	src->setBlendFunc(BLEND_LIGHTEN);
	glBlendEquation(GL_MAX_EXT);
	SetAlpha(m_lgrpAlpha - LIGHTENALPHA);
	src->setTextureRect(Rect(xs, ys, w, h));
	src->setPosition(Vec2(x, y));
	if (baseColor)//if (baseColor != 0x000000 && !baseColor)
	{
		if (baseColor == 0xFFFFFF && !grayScale)
			src->setGLProgram(GLProgramCache::getInstance()->getGLProgram("whitescale"));
		else
			src->setColor(Color3B((baseColor >> 16) & 0xFF, (baseColor >> 8) & 0xFF, baseColor & 0xFF));
	}
	else if (!grayScale)
		src->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));


	AfterSpriting(src);

	SetAlpha(m_lgrpAlpha + LIGHTENALPHA);
}

void ShadowImage(int w, int h, int xs, int ys, int x, int y, int res, float magnify)
{
	cocos2d::Sprite* src;

	if (m_lgrpAlpha == 0)
		return;

	//x += offX;
	//y += offY;
#ifdef CLIPPING
	if (x < clipX) { xs -= (x - clipX) / magnify; w -= (clipX - x) / magnify; x = clipX; }
	if (x + w > clipX2) { w = (clipX2 - x) / magnify; }
	if (y > clipY) { ys += (y - clipY) / magnify; h -= (y - clipY) / magnify; y = clipY; }
	if (y - h < clipY2) { h = (y - clipY2) / magnify; }
	if (w <= 0 || h <= 0)
		return;
#endif

	if (!sprite[res])
		LoadImg(res);

	LoadSpriteFromTexture(res);
	src = renderSprite[getSpriteIdx];

	src->setBlendFunc(BLEND_SHADOW);
	src->setScale(magnify);
	src->setTextureRect(Rect(xs, ys, w, h));
	src->setPosition(Vec2(x, y));
	if (baseColor)//if (baseColor != 0x000000 && !baseColor)
	{
		if (baseColor == 0xFFFFFF)
			src->setGLProgram(GLProgramCache::getInstance()->getGLProgram("whitescale"));
		else
			src->setColor(Color3B((baseColor >> 16) & 0xFF, (baseColor >> 8) & 0xFF, baseColor & 0xFF));
	}
	else
		src->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));


	AfterSpriting(src);
}


void ProcessWave(void)
{
	int i, j;

	waveFrame++;

	if (waveFrame > 1000) {
		InitGraphics();
		waveFrame = 0;
	}

	for (i = 1; i < WAVE_DIAMETER - 1; i++) {
		for (j = 0; j < WAVE_DIAMETER; j++) {
			a.waves[i * WAVE_DIAMETER + j] = (signed short)(
				((a.waves[(i - 1) * WAVE_DIAMETER + j - 1] +
					a.waves[(i - 1) * WAVE_DIAMETER + j] +
					a.waves[(i - 1) * WAVE_DIAMETER + j + 1] +
					a.waves[i * WAVE_DIAMETER + j - 1] +
					a.waves[i * WAVE_DIAMETER + j + 1] +
					a.waves[(i + 1) * WAVE_DIAMETER + j - 1] +
					a.waves[(i + 1) * WAVE_DIAMETER + j] +
					a.waves[(i + 1) * WAVE_DIAMETER + j + 1]) >> 2) -
				a.waves[i * WAVE_DIAMETER + j]);
		}
	}
}

void Waterize(int x, int y, int w, int h)
{
	//int i, j;
	//unsigned short *xx, *yy;
	//int xOffset, yOffset, tPxl = 0;

#ifdef CLIPPING
	if (x < clipX) { w += (x - clipX); x = clipX; }
	if (x + w > clipX2) { w = clipX2 - x; }
	if (y < clipY) { h += (y - clipY); y = clipY; }
	if (y > clipY2) { h = Min(h, h - (clipY2 - y)); }
	if (w <= 0 || h <= 0)
		return;
#endif
}

void ZoomImage(int cx, int cy, int zoom)
{
	if (zoom == 256)
		return;

	cx = Max(0, Min(DX - 1, cx));
	cy = Max(0, Min(DY - 1, cy));

	//화면버퍼를 직접 스케일하지 않는다.
	//Stage 3에서 인자로 받던 렌더텍스처(buff)를 gRenderTarget으로 바꿨는데, 그건 프레임 중
	//gScreenBuffer라서 화면 전체가 대상이 되어버렸다. 게다가 zoom / 256이 정수 나눗셈이라
	//zoom이 256 미만이면 setScale(0)이 되고, 되돌리는 코드가 없어 화면이 영영 사라진다
	//(메뉴를 열면 단색만 보이던 원인). cx, cy는 계산만 하고 쓰지도 않아 중심 기준 확대도
	//구현돼 있지 않았다. 확대 연출이 필요하면 화면버퍼가 아닌 별도 대상에 다시 만들어야 한다.
	//gRenderTarget->setScale(float(zoom) / 256.0f);
}
//
void GammaImage(int gamma, int type, float zoom)
{
	/*
	cocos2d::RenderTexture* buff = cvtDest;
	cocos2d::Layer*dest;
	cocos2d::Layer*src;
	cocos2d::Layer*pDest;
	int i, j, mask, mask2, gap1, gap2;
	unsigned char *pRadius, *pView;

	switch (type) {
	case 0:
		if (gamma == 32)
			return;

		src = buff;
		dest = src + (DY * DX >> 1);

		//��ü���� ���?����
		if (gamma > 63)
			src->beginWithClear(1.0, 1.0, 1.0, 1.0);//memset(src, COLOR_WHITEFF, (DY * DX) << 1);
		else if (gamma > 32) {
			//gamma
		}
		else if (gamma > 0) {
			//gamma
		}
		else
			src->beginWithClear(0, 0, 0, 1.0);//memset(src, 0x000000, (DY * DX) << 1);
		break;
	case 1:
	case 7:
		//특정 위치 중심으로 퍼지면서 밝기 감소
		if (viewRadius[0] == 0)
			ProcessRadius(0, 2);

		if (viewRadius2[0] == 0)
			ProcessRadius(2, 0);

		break;
	case 2:
		//테두리 밝게
		src = buff;
		dest = src + (DY * DX >> 1);
		break;
	case 3:
		//테두리 어둡게
		src = buff;
		dest = src + (DY * DX >> 1);
		break;
	case 4:
		src = buff;
		dest = src + (DY * DX >> 1);
		break;
	case 5:
		//특정 위치 중심으로 퍼지면서 밝기 감소
		if (viewRadius == 0)
			ProcessRadius(1, Max(3, radiusStatus + 2));

		src = buff;
		dest = src + (DY * DX >> 1);
		break;
	case 6:
		//그레이스케일
		if (gamma == 0)
			return;

		pDest = buff + (DY * DX);
		break;
	}
 */
}

void InitContext(void)
{
	//int offset[2];
	m_lgrpAlpha = 32;
}

/*----------------------------------------------------------------------------
**			SCREEN BUFFER / RENDER TARGET
**--------------------------------------------------------------------------*/

//ȭ����۸�?������ �����Ѵ�. DX/DY �� Ȯ���� ��(Core::init)�� �� ���� ȣ���ؾ� �Ѵ�.
void InitScreenBuffer(void)
{
	if (gScreenBuffer)
		return;

	gScreenLayer = cocos2d::Layer::create();
	gScreenLayer->retain();

	gScreenBuffer = cocos2d::RenderTexture::create(DX, DY);
	gScreenBuffer->retain();
	//DrawBuffer() �� ���� ��ǥ �Ծ�: �»��?����(anchor 0,1)�� ��ġ�� (0, DY)
	gScreenBuffer->getSprite()->setAnchorPoint(Vec2(0.0f, 1.0f));
	gScreenBuffer->setPosition(Vec2(0, DY));
}

//������ ����. ������ ���?��ο�� ȭ����ۿ�?���δ�.
void BeginScreenBuffer(void)
{
	if (!screenBuffer || !gScreenBuffer)
		return;

	gScreenBuffer->beginWithClear(0, 0, 0, 0);

	gRenderTarget = gScreenBuffer;
	gRenderLayer = gScreenLayer;
}

//������ ����. ȭ����۸�?�ݰ�, ���� �� ���� �ٿ� ȭ�鿡 ǥ���Ѵ�.
//스팟라이트를 이번 프레임에 켠다. EndScreenBuffer()가 소비한 뒤 자동으로 꺼지므로
//강조하고 싶은 프레임마다 그리는 자리에서 불러주면 된다.
//x, y는 게임 좌표(y가 위로 증가, 화면 위쪽이 DY)의 스팟 중심이다.
//inner까지는 원본 밝기 그대로, radius 바깥은 전부 darkness로 덮인다.
//
//한 프레임에 여러 번 부르면 그만큼 밝은 지점이 늘어난다(최대 MAXSPOTLIGHT개).
//한 번만 부르던 기존 호출부는 그대로 하나짜리로 동작한다.
//darkness는 스팟마다 따로 둘 수 없어(암전은 화면 전체에 한 번 깔린다) 마지막 값이 이긴다.
void SetSpotlight(float x, float y, float inner, float radius, float darkness)
{
	gSpotlightDarkness = darkness;

	if (gSpotlightCnt >= MAXSPOTLIGHT)
		return;

	gSpotlightX[gSpotlightCnt] = x;
	gSpotlightY[gSpotlightCnt] = y;
	gSpotlightInner[gSpotlightCnt] = inner;
	gSpotlightRadius[gSpotlightCnt] = radius;
	gSpotlightCnt++;

	gSpotlightOn = true;
}

//암전에서 뺄 사각형을 지정한다. 대화창처럼 스팟과 별개로 밝게 남겨야 하는 UI에 쓴다.
//x, y는 사각형의 왼쪽/윗변이고 h는 아래로 뻗는다. DrawCmfPopUp() 등과 인자가 같다.
//SetSpotlight()과 마찬가지로 EndScreenBuffer()가 소비한 뒤 꺼진다.
//한 프레임에 여러 번 부르면 그만큼 늘어난다(최대 MAXKEEPRECT개).
void SetSpotlightKeepRect(float x, float y, float w, float h, float soft)
{
	if (gSpotlightKeepCnt >= MAXKEEPRECT)
		return;

	gSpotlightKeepX[gSpotlightKeepCnt] = x;
	gSpotlightKeepY[gSpotlightKeepCnt] = y;
	gSpotlightKeepW[gSpotlightKeepCnt] = w;
	gSpotlightKeepH[gSpotlightKeepCnt] = h;
	gSpotlightKeepSoft[gSpotlightKeepCnt] = soft;
	gSpotlightKeepCnt++;
}

void ClearSpotlight(void)
{
	gSpotlightOn = false;
	gSpotlightCnt = 0;
	gSpotlightKeepCnt = 0;
}

//화면버퍼 스프라이트에 스팟라이트 쉐이더를 걸거나 원래 쉐이더로 되돌린다.
static void ApplySpotlight(void)
{
	static cocos2d::GLProgram* savedScreenProgram = nullptr;
	static bool spotlightApplied = false;

	cocos2d::Sprite* sp = gScreenBuffer->getSprite();

	if (sp == nullptr)
		return;

	if (gSpotlightOn == false) {
		//셰이더를 매 프레임 갈아끼우지 않도록, 걸어둔 상태일 때만 되돌린다.
		if (spotlightApplied) {
			sp->setGLProgram(savedScreenProgram ? savedScreenProgram
				: GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));
			spotlightApplied = false;
		}
		return;
	}

	if (spotlightApplied == false) {
		//원래 쉐이더는 처음 한 번만 기억해 둔다. 되돌릴 때 쓴다.
		if (savedScreenProgram == nullptr)
			savedScreenProgram = sp->getGLProgram();

		sp->setGLProgram(shader_spotlight);
		spotlightApplied = true;
	}

	cocos2d::GLProgramState* st = sp->getGLProgramState();

	if (st) {
		//NPOT을 못 쓰는 기기에서는 텍스처가 2의 거듭제곱으로 패딩되어
		//v_texCoord가 0~1을 다 쓰지 않는다. 그 비율을 넘겨 셰이더에서 되돌린다.
		Vec2 texScale(1.0f, 1.0f);
		cocos2d::Texture2D* tex = sp->getTexture();

		if (tex && tex->getPixelsWide() > 0 && tex->getPixelsHigh() > 0) {
			texScale.x = tex->getContentSize().width / (float)tex->getPixelsWide();
			texScale.y = tex->getContentSize().height / (float)tex->getPixelsHigh();
		}

		//셰이더는 항상 MAXSPOTLIGHT개를 다 훑는다(GLSL ES 1.00에서 uniform으로 루프를
		//끊기가 까다롭다). 안 쓰는 칸은 화면 밖 멀리에 반경 1로 두면 밝기 기여가 0이 된다.
		//inner == radius면 smoothstep이 정의되지 않으므로 반드시 벌려 둔다.
		//static이어야 한다. setUniformVec2v()/setUniformFloatv()는 값을 복사하지 않고
		//넘긴 포인터를 그대로 들고 있다가 실제로 그릴 때 읽는다(CCGLProgramState.cpp의
		//UniformValue::setVec2v). 지역배열로 두면 이 함수를 빠져나온 뒤 사라진 스택을
		//읽어서 스팟라이트가 통째로 엉뚱하게 계산된다.
		static Vec2 spotCenter[MAXSPOTLIGHT];
		static float spotInner[MAXSPOTLIGHT];
		static float spotRadius[MAXSPOTLIGHT];
		static Vec4 keepRect[MAXKEEPRECT];
		static float keepSoft[MAXKEEPRECT];

		for (int k = 0; k < MAXKEEPRECT; k++) {
			if (k < gSpotlightKeepCnt) {
				keepRect[k] = Vec4(gSpotlightKeepX[k], gSpotlightKeepY[k], gSpotlightKeepW[k], gSpotlightKeepH[k]);
				keepSoft[k] = gSpotlightKeepSoft[k] > 0.0f ? gSpotlightKeepSoft[k] : 1.0f;
			}
			else {
				//폭이 0이면 셰이더가 건너뛴다.
				keepRect[k] = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
				keepSoft[k] = 1.0f;
			}
		}

		for (int s = 0; s < MAXSPOTLIGHT; s++) {
			if (s < gSpotlightCnt) {
				spotCenter[s] = Vec2(gSpotlightX[s], gSpotlightY[s]);
				spotInner[s] = gSpotlightInner[s];
				spotRadius[s] = Max(gSpotlightRadius[s], gSpotlightInner[s] + 1.0f);
			}
			else {
				spotCenter[s] = Vec2(-100000.0f, -100000.0f);
				spotInner[s] = 0.0f;
				spotRadius[s] = 1.0f;
			}
		}

		st->setUniformVec2("u_texScale", texScale);
		st->setUniformVec2("u_resolution", Vec2((float)DX, (float)DY));
		st->setUniformVec2v("u_center", MAXSPOTLIGHT, spotCenter);
		st->setUniformFloatv("u_inner", MAXSPOTLIGHT, spotInner);
		st->setUniformFloatv("u_radius", MAXSPOTLIGHT, spotRadius);
		st->setUniformFloat("u_darkness", gSpotlightDarkness);
		st->setUniformVec4v("u_keepRect", MAXKEEPRECT, keepRect);
		st->setUniformFloatv("u_keepSoft", MAXKEEPRECT, keepSoft);
	}

	//즉시모드. 다음 프레임에 다시 켜지 않으면 꺼진다.
	gSpotlightOn = false;
	gSpotlightCnt = 0;
	gSpotlightKeepCnt = 0;
}

void EndScreenBuffer(void)
{
	if (!screenBuffer || !gScreenBuffer)
		return;

	gScreenBuffer->end();

	gRenderTarget = nullptr;
	gRenderLayer = nullptr;

	ApplySpotlight();

	//���� ���� ȭ����۴�?�� ������ ���ŵǹǷ� ������ ���� �ʿ䰡 ����.
	if (gScreenBuffer->getParent() == nullptr)
		curScene->addChild(gScreenBuffer);
}

//������ũ�� ����(bufferTexture[BUFFER_*])�� ���� Ÿ���� ��ȯ�Ѵ�.
//�����ؽ�ó�� ��ø begin �� �� �ǹǷ� ���� �ִ� ���� Ÿ���� �ݾ� �ΰ� Pop ���� �ǻ츰��.
static cocos2d::RenderTexture* savedRenderTarget = nullptr;
static cocos2d::Layer* savedRenderLayer = nullptr;

void PushRenderTarget(cocos2d::RenderTexture* dest, cocos2d::Layer* layer, bool clear)
{
	if (!dest)
		return;

	savedRenderTarget = gRenderTarget;
	savedRenderLayer = gRenderLayer;

	if (savedRenderTarget)
		savedRenderTarget->end();

	if (clear)
		dest->beginWithClear(0, 0, 0, 0);
	else
		dest->begin();

	gRenderTarget = dest;
	gRenderLayer = layer;
}

void PopRenderTarget(void)
{
	if (gRenderTarget)
		gRenderTarget->end();

	//�ݾ� �ξ��� ���� Ÿ���� �ٽ� ����. beginWithClear �� �ƴ϶� begin �̾��?
	//�̹� �׷� �� ������ �������� �ʴ´�.
	if (savedRenderTarget)
		savedRenderTarget->begin();

	gRenderTarget = savedRenderTarget;
	gRenderLayer = savedRenderLayer;

	savedRenderTarget = nullptr;
	savedRenderLayer = nullptr;
}

//?�면보다 ???�프?�크�?버퍼(bufferTexture[BUFFER_*])??그리??중인지.
//?�면버퍼???�면�?같�? ?�기?��?�??�외?�다.
//?�로???�수가 ?�던 buffering ?�자 �??�립 범위 ?�단?�으로만 ?��? 부분을 ?�체한??
bool IsOffscreenTarget(void)
{
	return gRenderTarget != nullptr && gRenderTarget != gScreenBuffer;
}

void SetSectionClip(int x, int y, int w, int h, bool outScreen)
{
	if (outScreen) {
		clipX = x;
		clipY = y;
		clipX2 = x + w;
		clipY2 = y - h;
	}
	else {
		clipX = Max(0, x);
		clipY = Min(DY, y);
		clipX2 = Min(DX, x + w);
		clipY2 = Max(0, y - h);
	}
}


void UnSectionClip(bool outScreen)
{
	if (outScreen) {
		clipX = -DX * 10;
		clipY = DY * 10 - 1;
		clipX2 = DX * 10;
		clipY2 = -DY * 10 + 1;
	}
	else {
		clipX = 0;
		clipY = DY;
		clipX2 = DX;
		clipY2 = 0;
	}
}

void SetColor(int color)
{
	baseColor = color;
}

void SetFontColor(int color)
{
	fontColor = color;
}

void ScreenDarken(int alpha)
{
	int i;
	//return;
	if (alpha > 0) {
		if (screenDarken == false)
			screenDarken = true;
		else
			screenDarken++;

		if (screenDarken > alpha)
			screenDarken = alpha;
	}
	else if (alpha == 0) {
		if (screenDarken > 0)
			screenDarken--;
	}

	if (screenDarken > 0) {
		SetAlpha(screenDarken);
		MemRect(0, DY, DX, DY, COLOR_BLACK);
		SetAlpha(32);
	}
}

void MemRectFrameThick(int x, int y, int w, int h, int fillCol, int thick)
{
	int i;
	for (i = 0; i < thick; i++) {
		MemRectFrame(x + i, y - i, w - i * 2, h - 2 * i, fillCol);
	}
}

void MemRect(int x, int y, int w, int h, int fillCol)
{
	cocos2d::Sprite* src;
	int color = fillCol;

	//x += offX;
	//y += offY;
#ifdef CLIPPING
	if (x < clipX) { w += (x - clipX); x = clipX; }
	if (x + w > clipX2) { w = clipX2 - x; }
	if (y > clipY) { h -= (y - clipY); y = clipY; }
	if (y - h < clipY2) { h = y - clipY2; }
	if (w <= 0 || h <= 0)
		return;
#endif


	LoadSpriteFromTexture(MEMRECT_IMG);
	src = renderSprite[getSpriteIdx];

	src->setPosition(Vec2(x, y));
	src->setTextureRect(Rect(0, 0, w, h));
	renderSprite[getSpriteIdx]->setColor(Color3B((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF));
	AfterSpriting(src);
}

void MemRectFrame(int x, int y, int w, int h, int frameCol)
{
	cocos2d::Sprite* src;
	int color = frameCol;

	//x += offX;
	//y += offY;

#ifdef CLIPPING
	if (x < clipX) { w += (x - clipX); x = clipX; }
	if (x + w > clipX2) { w = clipX2 - x; }
	if (y > clipY) { h -= (y - clipY); y = clipY; }
	if (y - h < clipY2) { h = y - clipY2; }
	if (w <= 0 || h <= 0)
		return;
#endif

	//Left
	MemRect(x, y, 1 * _2X, h, frameCol);

	//Up
	MemRect(x, y, w, 1 * _2X, frameCol);

	//Right
	MemRect(x + w - 1 * _2X, y, 1 * _2X, h, frameCol);

	//Down
	MemRect(x, y - h + 1 * _2X, w, 1 * _2X, frameCol);
}

void MemRectBoth(int x, int y, int w, int h, int frameCol, int fillCol)
{
	MemRectFrame(x, y, w, h, frameCol);
	MemRect(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * _2X, fillCol);
}

void MemRectBothThick(int x, int y, int w, int h, int frameCol, int fillCol)
{
	MemRect(x, y, w, 2 * _2X, frameCol);
	MemRect(x, y - 2 * _2X, 2 * _2X, h - 2 * _2X * 2, frameCol);
	MemRect(x + w - 2 * _2X, y - 2 * _2X, 2 * _2X, h - 2 * _2X * 2, frameCol);
	MemRect(x, y - h + 2 * _2X, w, 2 * _2X, frameCol);

	MemRect(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 4 * _2X, fillCol);
}

//�ձ� �簢��ä���?
void MemRectRound(int x, int y, int w, int h, int fillCol, int empty)
{
	int j = 0;
	float dx, dy, r = 0;
	int dx2, dy2;

	dx2 = 0;
	dy2 = empty;

	//���⼭ empty�� �����̿� ���?���簢���� ũ��
	for (r = 0; r <= 90; r++) {
		dx = ((float)empty) * sin(CC_DEGREES_TO_RADIANS(r));
		dy = ((float)empty) * cos(CC_DEGREES_TO_RADIANS(r));

		if ((dx2 != (int)dx || dy2 != (int)dy) && ((int)dx < empty || (int)dy < empty)) {
			dx2 = (int)dx;
			dy2 = (int)dy;

			MemRect(x + empty - (int)dx, y - empty + (int)dy, w - (empty - (int)dx) * 2, (int)dy, fillCol);
			MemRect(x + empty - (int)dx, y + empty - h, w - (empty - (int)dx) * 2, (int)dy, fillCol);
			j++;
		}
	}

	MemRect(x, y - empty, w, h - 2 * empty, fillCol);
}

void MemRectGraph(int x, int y, int w, int h, int type)
{
	int i = 0;
	int height = h;
	int gap[5] = { 4, 7, 11, 15, 10000 };

	do {
		height = Min(h, gap[i]);
		MemRect(x, y, w, height, colorData[36 + type * 5 + i]);
		y += height;
		h -= height;
		i++;
	} while (h > 0 && i < 5);
}

//color1 �� ���� ���Ѱ�, color2, color3, color4�� ���� ���Ѱ�
void DrawColorFrame(int x, int y, int w, int h, int color1, int color2, int color3, int color4)
{
	//CC_PROFILER_START("");

	MemRectBoth(x, y, w, h, color4, color1);
	MemRect(x + 1 * _2X, y - 1 * _2X, w - 3 * _2X, 1 * _2X, color1);
	MemRect(x + 1 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, color1);
	MemRect(x + w - 2 * _2X, y - 1 * _2X, 1 * _2X, 1 * _2X, color2);
	MemRect(x + 1 * _2X, y - (h - 2 * _2X), 1 * _2X, 1 * _2X, color2);
	MemRect(x + w - 2 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, color3);
	MemRect(x + 2 * _2X, y - (h - 2 * _2X), w - 3 * _2X, 1 * _2X, color3);

	//CC_PROFILER_STOP("")//CC_PROFILER_DISPLAY_TIMERS();
}

void DrawFrame(int x, int y, int w, int h, int type)
{
	int i, j, t;
	int curAlpha = m_lgrpAlpha;
	int color;

	//if (type == FRAME_SHOPBALLOON)
	//	return;

	if (w == 0 || h == 0)
		return;

	switch (type) {
	case FRAME_GNB:
		MemRectRound(x, y, w, h, 0xCCCCCC, 1 * _2X);
		MemRectRound(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * _2X, COLOR_NAVY, 1 * _2X);

		break;
	case FRAME_NOFRAME:
		SetAlpha(32 + curAlpha - 32);
		MemRectRound(x + 2 * _2X, y - 2 * _2X, w, h, COLOR_BLACK, 2 * _2X);

		SetAlpha(28 + curAlpha - 32);
		MemRectRound(x, y, w, h, 0x1B2843, 2 * _2X);
		SetAlpha(32 + curAlpha - 32);
		break;
	case FRAME_NORMAL:
	case FRAME_MENUWIN:
	case FRAME_MENUWIN_QUICK:
	case FRAME_MENUWIN_INFO:
	case FRAME_MENUDAILY:
	case FRAME_GAMEOVER:
		if (type != FRAME_NORMAL) {
			j = 0;

			for (i = 0; i < 16; i++) {
				if (i * (h / 16 + 1) < h - 12)
					j++;
				else
					break;
			}

			i = j;

			for (i = 0; i < j; i++) {
				SetAlpha(16 + i);
				MemRect(x, y - (float)i * (h / 16 * _2X + 1) * _2X, w, (h / 16 + 1) * _2X, 0x2A395C);
			}
		}
		else {
			SetAlpha(16);
			MemRect(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 4 * _2X, 0x1B2843);
		}

		SetAlpha(32);

		MemRect(x + 1 * _2X, y - 0, w - 2 * _2X, 1 * _2X, COLOR_WIN_DARK);
		MemRect(x + 0, y - 1 * _2X, 1 * _2X, h - 2 * _2X, COLOR_WIN_DARK);
		MemRect(x + w - 1 * _2X, y - 1 * _2X, 1 * _2X, h - 2 * _2X, COLOR_WIN_DARK);
		MemRect(x + 1 * _2X, y - (h - 1 * _2X), w - 2 * _2X, 1 * _2X, COLOR_WIN_DARK);

		MemRectFrame(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * _2X, COLOR_WIN_MID);

		MemRect(x + 1 * _2X, y - 1 * _2X, 1 * _2X, 1 * _2X, COLOR_WIN_DARK);
		MemRect(x + w - 2 * _2X, y - 1 * _2X, 1 * _2X, 1 * _2X, COLOR_WIN_DARK);
		MemRect(x + 1 * _2X, y - (h - 2 * _2X), 1 * _2X, 1 * _2X, COLOR_WIN_DARK);
		MemRect(x + w - 2 * _2X, y - (h - 2 * _2X), 1 * _2X, 1 * _2X, COLOR_WIN_DARK);

		MemRectFrame(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 4 * _2X, COLOR_WIN_LIGHT);

		if (type != FRAME_NORMAL) {
			switch (type) {
			case FRAME_MENUDAILY:
				MemRectFrame(x + 3 * _2X, y - 3 * _2X, w - 6 * _2X, h - 6 * _2X, COLOR_WIN_MID);
				MemRectFrame(x + 4 * _2X, y - 4 * _2X, w - 8 * _2X, h - 8 * _2X, COLOR_WIN_DARK);
				break;
			case FRAME_MENUWIN:
			case FRAME_GAMEOVER:
				MemRectFrame(x + 3 * _2X, y - 3 * _2X, w - 6, h - 16, COLOR_WIN_MID);
				MemRectFrame(x + 4, y - 4, w - 8, h - 18, COLOR_WIN_DARK);
				break;
			default:
				//case FRAME_MENUWIN_QUICK:
				MemRectFrame(x + 3, y - 3, w - 6, h - 27, COLOR_WIN_MID);
				MemRectFrame(x + 4, y - 4, w - 8, h - 29, COLOR_WIN_DARK);
				break;
			}

			MemRect(x + 3, y - 3, 1, 1, COLOR_WIN_LIGHT);
			MemRect(x + w - 4, y - 3, 1, 1, COLOR_WIN_LIGHT);

			if (type == FRAME_GAMEOVER) {
				MemRectBoth(x + (w - 64) / 2, y - 3, 64, 11, COLOR_WIN_MID, COLOR_WIN_LIGHT);
				MemRect(x + (w - 64) / 2, y - 3, 64, 1, COLOR_WIN_LIGHT);
				MemRect(x + (w - 64) / 2 - 1, y - 5, 1, 9, COLOR_WIN_DARK);
				MemRect(x + (w - 64) / 2 + 64, y - 5, 1, 9, COLOR_WIN_DARK);
				MemRect(x + (w - 64) / 2, y - 14, 64, 1, COLOR_WIN_DARK);

				for (i = 0; i < 4; i++)
					MemRect(x + (w - 64) / 2 + 2 + 59 * (i % 2), y - (3 + 8 * (i / 2)), 1, 1, COLOR_WIN_DOT);
			}
			else {
				MemRectBoth(x + (w - 86) / 2, y - 3, 86, 15, COLOR_WIN_MID, COLOR_WIN_LIGHT);
				MemRect(x + (w - 86) / 2, y - 3, 86, 1, COLOR_WIN_LIGHT);
				MemRect(x + (w - 86) / 2 - 1, y - 5, 1, 13, COLOR_WIN_DARK);
				MemRect(x + (w - 86) / 2 + 86, y - 5, 1, 13, COLOR_WIN_DARK);
				MemRect(x + (w - 86) / 2, y - 18, 86, 1, COLOR_WIN_DARK);

				for (i = 0; i < 4; i++)
					MemRect(x + (w - 86) / 2 + 2 + 81 * (i % 2), y - (5 + 10 * (i / 2)), 1, 1, COLOR_WIN_DOT);
			}

			switch (type) {
			case FRAME_MENUDAILY:
				break;
			case FRAME_MENUWIN:
			case FRAME_GAMEOVER:
				MemRect(x + 3, y - (h - 14), 1, 1, COLOR_WIN_LIGHT);
				MemRect(x + w - 4, y - (h - 14), 1, 1, COLOR_WIN_LIGHT);
				MemRect(x + 3, y - (h - 13), w - 6, 11, COLOR_WIN_LIGHT);
				break;
			default:
				//case FRAME_MENUWIN_QUICK:
				MemRect(x + 3, y - (h - 25), 1, 1, COLOR_WIN_LIGHT);
				MemRect(x + w - 4, y - (h - 25), 1, 1, COLOR_WIN_LIGHT);
				MemRect(x + 3, y - (h - 24), w - 6, 22, COLOR_WIN_LIGHT);
				break;
			}
		}
		break;
	case FRAME_BUTTON:
		MemRect(x + 1 * _2X, y - 0 * _2X, w - 3 * _2X, 1 * _2X, COLOR_WIN_DARK_GREEN1);
		MemRect(x, y - 1 * _2X, 1 * _2X, h - 2 * _2X, COLOR_WIN_LIGHT_GREEN1);
		MemRect(x + w - 2 * _2X, y - 1 * _2X, 1 * _2X, h - 2 * _2X, COLOR_WIN_LIGHT_GREEN1);
		MemRect(x + 1 * _2X, y - 1 * _2X, w - 3 * _2X, h - 2 * _2X, COLOR_WIN_MID_GREEN1);
		MemRect(x + w - 2 * _2X, y, 1 * _2X, 1 * _2X, COLOR_WIN_MID_GREEN1);
		MemRect(x + w - 1 * _2X, y - 1 * _2X, 1 * _2X, h - 2 * _2X, COLOR_WIN_MIDDARK_GREEN1);
		MemRect(x + 1 * _2X, y - (h - 1 * _2X), w - 2 * _2X, 1 * _2X, COLOR_WIN_MIDDARK_GREEN1);

		for (i = 0; i < 4; i++)
			MemRect(x + 2 * _2X + (w - 5 * _2X) * (i % 2), y - (2 * _2X + (h - 5 * _2X) * (i / 2)), 1 * _2X, 1 * _2X, COLOR_WIN_DOT_GREEN1);
		break;
	case FRAME_CHOICEBUTTON:
		MemRectBoth(x, y, w, h, COLOR_WIN_DARK, COLOR_WIN_MID);
		//MemRect(x + 1 * _2X, y - 1 * _2X, w - 3 * _2X, 1 * _2X, COLOR_WIN_LIGHT, cvtDest, cvtLayer, buffering);
		//MemRect(x + 1 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, COLOR_WIN_LIGHT, cvtDest, cvtLayer, buffering);
		//MemRect(x + w - 2 * _2X, y - 1 * _2X, 1 * _2X, 1 * _2X, COLOR_WIN_MID, cvtDest, cvtLayer, buffering);
		//MemRect(x + 1 * _2X, y - (h - 2 * _2X), 1 * _2X, 1 * _2X, COLOR_WIN_MID, cvtDest, cvtLayer, buffering);
		//MemRect(x + w - 2 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, COLOR_WIN_MIDDARK, cvtDest, cvtLayer, buffering);
		//MemRect(x + 2 * _2X, y - (h - 2 * _2X), w - 3 * _2X, 1 * _2X, COLOR_WIN_MIDDARK, cvtDest, cvtLayer, buffering);

		MemRect(x + 1 * _2X, y - 1 * _2X, w - 3 * _2X, 1 * _2X, 0x1286C3);
		MemRect(x + 1 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, 0x1286C3);
		MemRect(x + w - 2 * _2X, y - 1 * _2X, 1 * _2X, 1 * _2X, 0x0A63A4);
		MemRect(x + 1 * _2X, y - (h - 2 * _2X), 1 * _2X, 1 * _2X, 0x0A63A4);
		MemRect(x + w - 2 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, 0x034185);
		MemRect(x + 2 * _2X, y - (h - 2 * _2X), w - 3 * _2X, 1 * _2X, 0x034185);

		break;
	case FRAME_CHOICEBUTTON2:
		MemRectBoth(x, y, w, h, COLOR_WIN_DARK, 0x0196AC);
		MemRect(x + 1 * _2X, y - 1 * _2X, w - 3 * _2X, 1 * _2X, 0x14B8D5);
		MemRect(x + 1 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, 0x14B8D5);
		MemRect(x + w - 2 * _2X, y - 1 * _2X, 1 * _2X, 1 * _2X, 0x00718E);
		MemRect(x + 1 * _2X, y - (h - 2 * _2X), 1 * _2X, 1 * _2X, 0x00718E);
		MemRect(x + w - 2 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, 0x00506E);
		MemRect(x + 2 * _2X, y - (h - 2 * _2X), w - 3 * _2X, 1 * _2X, 0x00506E);

		break;
	case FRAME_CHOICEBUTTON_BEIGE:
		MemRectBoth(x, y, w, h, COLOR_WIN_DARK_BROWN1, COLOR_BEIGE);
		MemRect(x + 1 * _2X, y - 1 * _2X, w - 3 * _2X, 1 * _2X, COLOR_BEIGE);
		MemRect(x + 1 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, COLOR_BEIGE);
		MemRect(x + w - 2 * _2X, y - 1 * _2X, 1 * _2X, 1 * _2X, COLOR_WIN_MID_BROWN1);
		MemRect(x + 1 * _2X, y - (h - 2 * _2X), 1 * _2X, 1 * _2X, COLOR_WIN_MID_BROWN1);
		MemRect(x + w - 2 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, COLOR_WIN_MIDDARK_BROWN1);
		MemRect(x + 2 * _2X, y - (h - 2 * _2X), w - 3 * _2X, 1 * _2X, COLOR_WIN_MIDDARK_BROWN1);
		break;
	case FRAME_TALKWIN:
		MemRect(x + 1 * _2X, y - 0 * _2X, w - 2 * _2X, 1 * _2X, 0x3A3A49);
		MemRect(x + 1 * _2X, y - 1 * _2X, 1 * _2X, h - 2 * _2X, 0x3A3A49);
		MemRect(x + w - 1 * _2X, y - 1 * _2X, 1 * _2X, h - 2 * _2X, 0x3A3A49);
		MemRect(x + 1 * _2X, y - (h - 1 * _2X), w - 2 * _2X, 1 * _2X, 0x3A3A49);
		MemRectFrame(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * _2X, 0x797982);
		MemRectFrame(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 4 * _2X, 0x3A3A49);
		for (i = 0; i < 4; i++)
			MemRect(x + 2 * _2X + (w - 5 * _2X) * (i % 2), y - (2 * _2X + (h - 5 * _2X) * (i / 2)), 1 * _2X, 1 * _2X, 0xB4AC9C);
		SetAlpha(24);
		MemRect(x + 3, y - 3, w - 6, h - 6, 0x414771);
		SetAlpha(32);
		break;
	case FRAME_SHOPBALLOON:
		//color = 0xFFFFF0;
		color = 0x818CDA;
		MemRect(x + 2 * _2X, y - 0 * _2X, w - 4 * _2X, 1 * _2X, color);
		MemRect(x, y - 2 * _2X, 1 * _2X, h - 4 * _2X, color);
		MemRect(x + w - 1 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, color);
		MemRect(x + 2 * _2X, y - (h - 1 * _2X), w - 4 * _2X, 1 * _2X, color);
		MemRectBoth(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * _2X, 0xCCFFFF, 0xFFFFF0/*COLOR_WHITE*/);
		for (i = 0; i < 4; i++) {
			MemRect(x + 1 * _2X + (w - 3 * _2X) * (i % 2), y - (1 * _2X + (h - 3 * _2X) * (i / 2)), 1 * _2X, 1 * _2X, 0x818CDA);
			MemRect(x + 2 * _2X + (w - 5 * _2X) * (i % 2), y - (1 * _2X + (h - 3 * _2X) * (i / 2)), 1 * _2X, 1 * _2X, 0xB9D7FC);
			MemRect(x + 1 * _2X + (w - 3 * _2X) * (i % 2), y - (2 * _2X + (h - 5 * _2X) * (i / 2)), 1 * _2X, 1 * _2X, 0xB9D7FC);
		}
		break;
	case FRAME_ANIINFO:
		if (winAniFrame < 7) {
			for (t = 0, i = 0; i <= winAniFrame; i++) {
				if (t + (7 - i) * _2X * (7 - i) * _2X > w && t + (7 - i) * _2X * (7 - i) * _2X > h)
					break;

				t += (7 - i) * _2X * (7 - i) * _2X;
			}

			if (w > h) {
				h = h * t / w;
				w = t;
			}
			else {
				w = w * t / h;
				h = t;
			}
		}

		//DrawFrame(x - w / 2, y + h / 2, w, h, FRAME_NORMAL, cvtDest);
		DrawFrame(x - w / 2, y + h / 2, w, h, FRAME_SHOPBALLOON);
		winAniFrame++;
		break;
	case FRAME_GREEN:
		/*
		if (w == OPTIONBUTTONSIZE_X && h == OPTIONBUTTONSIZE_Y && buffering == false) {
			DrawImage(OPTIONBUTTONSIZE_X, OPTIONBUTTONSIZE_Y, 0, 0, x, y, false, false, false, false, false, 1.0f, sprite[BUFFER_OPTIONBUTTON_GREEN_IMG], cvtDest, cvtLayer, BUFFER_OPTIONBUTTON_GREEN_IMG, buffering);

			//DrawBuffer(x, y, w, h, bufferTexture[BUFFER_OPTIONBUTTON_GREEN]);
		}
		else if (w == CREWUPGRADEBUTTONSIZE_X && h == CREWUPGRADEBUTTONSIZE_Y && buffering == false) {
			DrawImage(CREWUPGRADEBUTTONSIZE_X, CREWUPGRADEBUTTONSIZE_Y, 0, 0, x, y, false, false, false, false, false, 1.0f, sprite[BUFFER_CREWUPGRADEBUTTON_GREEN_IMG], cvtDest, cvtLayer, BUFFER_CREWUPGRADEBUTTON_GREEN_IMG, buffering);

			//DrawBuffer(x, y, w, h, bufferTexture[BUFFER_CREWUPGRADEBUTTON_GREEN]);
		}
		else
		*/
		GradiationFrame(x, y, w, h, 4);
		break;
	case FRAME_RED:
		/*
		if (w == OPTIONBUTTONSIZE_X && h == OPTIONBUTTONSIZE_Y && buffering == false) {
			DrawImage(OPTIONBUTTONSIZE_X, OPTIONBUTTONSIZE_Y, 0, 0, x, y, false, false, false, false, false, 1.0f, sprite[BUFFER_OPTIONBUTTON_RED_IMG], cvtDest, cvtLayer, BUFFER_OPTIONBUTTON_RED_IMG, buffering);

			//DrawBuffer(x, y, w, h, bufferTexture[BUFFER_OPTIONBUTTON_RED]);
		}
		else
		*/
		GradiationFrame(x, y, w, h, 5);
		break;
	case FRAME_BLUE:
		/*
		if (w == OPTIONBUTTONSIZE_X && h == OPTIONBUTTONSIZE_Y && buffering == false) {
			DrawImage(OPTIONBUTTONSIZE_X, OPTIONBUTTONSIZE_Y, 0, 0, x, y, false, false, false, false, false, 1.0f, sprite[BUFFER_OPTIONBUTTON_BLUE_IMG], cvtDest, cvtLayer, BUFFER_OPTIONBUTTON_BLUE_IMG, buffering);

			//DrawBuffer(x, y, w, h, bufferTexture[BUFFER_OPTIONBUTTON_BLUE]);
		}
		else
		*/
		GradiationFrame(x, y, w, h, 6);
		break;
	case FRAME_GREY:
		/*
		if (w == OPTIONBUTTONSIZE_X && h == OPTIONBUTTONSIZE_Y && buffering == false) {
			DrawImage(OPTIONBUTTONSIZE_X, OPTIONBUTTONSIZE_Y, 0, 0, x, y, false, false, false, false, false, 1.0f, sprite[BUFFER_OPTIONBUTTON_GREY_IMG], cvtDest, cvtLayer, BUFFER_OPTIONBUTTON_GREY_IMG, buffering);

			//DrawBuffer(x, y, w, h, bufferTexture[BUFFER_OPTIONBUTTON_GREY]);
		}
		else if (w == CREWUPGRADEBUTTONSIZE_X && h == CREWUPGRADEBUTTONSIZE_Y && buffering == false) {
			DrawImage(CREWUPGRADEBUTTONSIZE_X, CREWUPGRADEBUTTONSIZE_Y, 0, 0, x, y, false, false, false, false, false, 1.0f, sprite[BUFFER_CREWUPGRADEBUTTON_GREY_IMG], cvtDest, cvtLayer, BUFFER_CREWUPGRADEBUTTON_GREY_IMG, buffering);

			//DrawBuffer(x, y, w, h, bufferTexture[BUFFER_CREWUPGRADEBUTTON_GREY]);
		}
		else
		*/
		GradiationFrame(x, y, w, h, 7);
		break;
	case FRAME_WHITEROUND:
		SetAlpha(24);
		MemRect(x, y, w, h, COLOR_NAVY);
		SetAlpha(32);
		MemRectFrameThick(x, y, w, h, COLOR_WHITE, 4 * _2X);

		break;
	}
}

void DrawEquipFrame(int x, int y, int w, int h, int baseColor, int frameColor)
{
	int i;

	MemRect(x + 2 * _2X, y - 0 * _2X, w - 4 * _2X, 1 * _2X, 0x818CDA);
	MemRect(x, y - 2 * _2X, 1 * _2X, h - 4 * _2X, 0x818CDA);
	MemRect(x + w - 1 * _2X, y - 2 * _2X, 1 * _2X, h - 4 * _2X, 0x818CDA);
	MemRect(x + 2 * _2X, y - (h - 1 * _2X), w - 4 * _2X, 1 * _2X, 0x818CDA);
	MemRectBoth(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * _2X, 0xCCFFFF, baseColor);
	for (i = 0; i < 4; i++) {
		MemRect(x + 1 * _2X + (w - 3 * _2X) * (i % 2), y - (1 * _2X + (h - 3 * _2X) * (i / 2)), 1 * _2X, 1 * _2X, 0x818CDA);
		MemRect(x + 2 * _2X + (w - 5 * _2X) * (i % 2), y - (1 * _2X + (h - 3 * _2X) * (i / 2)), 1 * _2X, 1 * _2X, 0xB9D7FC);
		MemRect(x + 1 * _2X + (w - 3 * _2X) * (i % 2), y - (2 * _2X + (h - 5 * _2X) * (i / 2)), 1 * _2X, 1 * _2X, 0xB9D7FC);
	}
}

void DrawRoundBar(int x, int y, float percent, int type, int color, int alpha, float zoom)
{
	int tempAlpha;
	//tempAlpha = m_lgrpAlpha;
	switch (type) {
	case ROUNDBAR_BIG:
		DrawImage(444, 129, 302, 1, x, y, false, false, false, false, alpha == false ? false : alpha, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		//if (alpha)
		//	SetAlpha(alpha);
		DrawImage((float)411 * percent, 94, 318, 132 + 95 * color, x + (float)16 * zoom, y - (float)16 * zoom, false, false, false, false, alpha == false ? false : alpha, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		break;
	case ROUNDBAR_SMALL:
		DrawImage(272, 129, 747, 1, x, y, false, false, false, false, alpha == false ? false : alpha, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		//if (alpha)
		//	SetAlpha(alpha);
		DrawImage((float)239 * percent, 94, 763, 132 + 95 * color, x + (float)16 * zoom, y - (float)16 * zoom, false, false, false, false, alpha == false ? false : alpha, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		break;
	}
	//switch (type) {
	//case BARCOLOR_RED:
	//	DrawImage(413, 96, 317, 132, x + (float)16 * zoom, y - (float)14 * zoom, false, false, false, false, false, zoom, sprite[UI_NEW_IMG], cvtDest, cvtLayer, UI_NEW_IMG, buffering);
	//	break;

	//case BARCOLOR_YELLOW:
	//	DrawImage(413, 95, 317, 229, x + (float)16 * zoom, y - (float)14 * zoom, false, false, false, false, false, zoom, sprite[UI_NEW_IMG], cvtDest, cvtLayer, UI_NEW_IMG, buffering);
	//	break;
	//}
	//SetAlpha(tempAlpha);
}

void DrawGuage(int x, int y, int w, int h, long cur, long max, int bgCol, int fullCol, float zoom)
{
	int realWidth = (w - (float)8 * _2X * zoom) * cur / max;
	int realHeight = h - (float)8 * _2X * zoom;

	DrawFrame(x, y, (float)w, (float)h, FRAME_SHOPBALLOON);
	MemRectRound(x + (float)(4 * _2X) * zoom, y - (float)(4 * _2X) * zoom, realWidth, realHeight, fullCol, (float)4 * _2X * zoom);

	//MemRectRound(x, y, w, h, COLOR_BROWN, (float)4 * _2X * zoom, cvtDest, cvtLayer, buffering);
	//MemRectRound(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, w - (float)8 * _2X * zoom, h - (float)8 * _2X * zoom, COLOR_WHITE, (float)4 * _2X * zoom, cvtDest, cvtLayer, buffering);
	//MemRect(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, realWidth, realHeight, fullCol, cvtDest, cvtLayer, buffering);

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%ld / %ld", cur, max);
	CenterTextStr(tempStr, x + w / 2, y - (float)(h / 2 - FONT_HEIGHT / 2 * zoom), zoom);
}

void DrawRouletteNum(long long num, int icon, int x, int y, bool ani, float zoom)
{
	float width = GetNumDx(num, false, NUM_FONT_LARGE, false, true, zoom, false) + (float)ITEMICONSIZE * zoom + (float)(2 * _2X) * zoom;
	
	//일반숫자 2배수
	DrawIcon(icon, x - width / 2, y, zoom, COLOR_BROWN, false, false, true);
	DrawNum(num, x - width / 2 + (float)ITEMICONSIZE * zoom + (float)(4 * _2X) * zoom, y + (float)(1 * _2X), NUM_FONT_LARGE, LEFT, 0, false, true, zoom, false);

	//DrawNumTTF(num, x - width / 2 + (float)ITEMICONSIZE * zoom + (float)(4 * _2X) * zoom, y + (float)(1 * _2X), NUM_FONT_LARGE, LEFT, 0, false, true, zoom, false, cvtDest, cvtLayer, buffering);

}

void DrawRouletteNumSmall(long long num, int icon, int x, int y, bool ani, float zoom)
{
	float width = GetNumDx(num, num < 0 ? MINUS : false, NUM_FONT_LARGE, false, true, zoom, false);// +ITEMICONSIZE * zoom + 4 * _2X * zoom;
	//일반숫자 2배수
	//DrawIcon(icon, x - width / 2, y, zoom, true, false, false, cvtDest, cvtLayer, buffering);
	DrawNum(num, x - width / 2 + ITEMICONSIZE * zoom + 4 * _2X * zoom, y + 1 * _2X, NUM_FONT_LARGE, CENTER, 0, num < 0 ? MINUS : false, true, zoom, false);
	//DrawNumTTF(num, x - width / 2 + ITEMICONSIZE * zoom + 4 * _2X * zoom, y + 1 * _2X, NUM_FONT_LARGE, CENTER, 0, num < 0 ? MINUS : false, true, zoom, false, cvtDest, cvtLayer, buffering);

}

float DrawRouletteNumIcon(long long num, int icon, int x, int y, bool ani, int align, float zoom)
{
	//float zoom = 2;
	float width = GetNumDx(num, false, NUM_FONT_LARGE, false, true, 1.0f * zoom, false) + (float)ITEMICONSIZE * zoom + (float)(4 * _2X) * zoom;

	switch (align) {
	case CENTER:
		x -= width / 2;
		break;
	case RIGHT:
		x -= width;
		break;
	}
	//일반숫자 2배수
	DrawIcon(icon, x, y - (float)(1 * _2X) * zoom, zoom, COLOR_BROWN, ani, false, true);
	DrawNum(num, x + (float)ITEMICONSIZE * zoom + (float)(4 * _2X) * zoom, y, NUM_FONT_LARGE, LEFT, 0, false, true, zoom, false);

	//DrawNumTTF(num, x + (float)ITEMICONSIZE * zoom + (float)(4 * _2X) * zoom, y - (float)2 * _2X * zoom, NUM_FONT_LARGE, LEFT, 0, false, true, (float)1.3f * zoom, false, cvtDest, cvtLayer, buffering);

	return width;
}

void DrawLabelStr(int x, int y, char* str, float zoom)
{
	float LABELZOOM = 1.1f;
	SetColor(false);
	//SetFontColor(COLOR_WHITE);
	DrawImage(objOff[IMG_OBJ_53 * 4 + 2], objOff[IMG_OBJ_53 * 4 + 3], objOff[IMG_OBJ_53 * 4 + 0], objOff[IMG_OBJ_53 * 4 + 1], x, y, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], COMMON_IMG);
	DrawImage(objOff[IMG_OBJ_54 * 4 + 2], objOff[IMG_OBJ_54 * 4 + 3], objOff[IMG_OBJ_54 * 4 + 0], objOff[IMG_OBJ_54 * 4 + 1], x + (float)(13 * _2X * _2X) * zoom, y - (float)(1 * _2X * _2X) * zoom, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], COMMON_IMG);
	DrawImage(objOff[IMG_OBJ_55 * 4 + 2], objOff[IMG_OBJ_55 * 4 + 3], objOff[IMG_OBJ_55 * 4 + 0], objOff[IMG_OBJ_55 * 4 + 1], x + (float)(27 * _2X * _2X) * zoom, y - (float)(3 * _2X * _2X) * zoom, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], COMMON_IMG);
	DrawImage(objOff[IMG_OBJ_56 * 4 + 2], objOff[IMG_OBJ_56 * 4 + 3], objOff[IMG_OBJ_56 * 4 + 0], objOff[IMG_OBJ_56 * 4 + 1], x + (float)(35 * _2X * _2X) * zoom, y - (float)(2 * _2X * _2X) * zoom, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], COMMON_IMG);
	if (str[0])
		CenterTextStr(str, x + (float)(21 * _2X * _2X) * zoom, y - (float)(16 * _2X) * zoom + (float)11 * _2X / 2 * LABELZOOM * zoom, LABELZOOM * zoom);

}

void DrawLabel(int x, int y, int textIdx, float zoom)
{
	float LABELZOOM = 1.1f;
	float IMGZOOM = 0.5f;

	x += (float)(16 * _2X * _2X) * zoom;
	SetColor(false);
	//SetFontColor(COLOR_WHITE);
	SetAlpha(16);
	MemRect(x + (float)(-480 / 2) * IMGZOOM * zoom, y - (float)6 * _2X, (float)480 * IMGZOOM * zoom, (float)20 * _2X * zoom, COLOR_NAVY);
	SetAlpha(32);

	DrawImage(512, 19, 2, 612, x + (float)(-512 / 2) * IMGZOOM * zoom, y - (float)4 * _2X, false, false, false, false, false, IMGZOOM * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	DrawImage(512, 19, 2, 612, x + (float)(-512 / 2) * IMGZOOM * zoom, y - (float)22 * _2X, false, false, false, false, false, IMGZOOM * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

	//DrawImage(objOff[IMG_OBJ_53 * 4 + 2], objOff[IMG_OBJ_53 * 4 + 3], objOff[IMG_OBJ_53 * 4 + 0], objOff[IMG_OBJ_53 * 4 + 1], x, y, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], cvtDest, cvtLayer, COMMON_IMG, buffering);
	//DrawImage(objOff[IMG_OBJ_54 * 4 + 2], objOff[IMG_OBJ_54 * 4 + 3], objOff[IMG_OBJ_54 * 4 + 0], objOff[IMG_OBJ_54 * 4 + 1], x + (float)(13 * _2X * _2X) * zoom, y - (float)(1 * _2X * _2X) * zoom, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], cvtDest, cvtLayer, COMMON_IMG, buffering);
	//DrawImage(objOff[IMG_OBJ_55 * 4 + 2], objOff[IMG_OBJ_55 * 4 + 3], objOff[IMG_OBJ_55 * 4 + 0], objOff[IMG_OBJ_55 * 4 + 1], x + (float)(27 * _2X * _2X) * zoom, y - (float)(3 * _2X * _2X) * zoom, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], cvtDest, cvtLayer, COMMON_IMG, buffering);
	//DrawImage(objOff[IMG_OBJ_56 * 4 + 2], objOff[IMG_OBJ_56 * 4 + 3], objOff[IMG_OBJ_56 * 4 + 0], objOff[IMG_OBJ_56 * 4 + 1], x + (float)(35 * _2X * _2X) * zoom, y - (float)(2 * _2X * _2X) * zoom, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], cvtDest, cvtLayer, COMMON_IMG, buffering);
	if (textIdx)
		CenterText(textIdx, x, y - (float)(16 * _2X) * zoom + (float)11 * _2X / 2 * LABELZOOM * zoom, LABELZOOM * zoom);
	//CenterText(textIdx, x + (float)(21 * _2X * _2X) * zoom, y - (float)(16 * _2X) * zoom + (float)11 * _2X / 2 * LABELZOOM * zoom, LABELZOOM * zoom, cvtDest, cvtLayer, buffering);
}

//�� ���׹� �����?
void DrawStageEnemyWave(int x, int y, int stageBossType, float zoom)
{

	//return;

	DrawBox(stageClearBox[robin.stage], x + (float)(32 * _2X) * zoom, y, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], COLOR_WHITE, true, false, true, 1.2f * zoom);

	DrawCmfDetailShadow(enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[stageBossType * 5 + 0] + (frame / 2 % crewPos[stageBossType * 5 + 1]), x, y, LEFT, /*enemyIconZoom[stageBossType] **/ zoom);

	DrawStageLabel(x, y + (float)92 * _2X * zoom, TEXT_STAGE, robin.stage, robin.room, true, zoom);

	DrawBuyButton(x + (float)(-24 * _2X * STAGESTARBUTTONZOOM) * zoom, y, (float)(80 * _2X) * STAGESTARBUTTONZOOM * zoom, (float)BUYBUTTON_Y * STAGESTARBUTTONZOOM * zoom, frame, robin.gold < GetStageAdmissionFee() ? FRAME_GREY : FRAME_GREEN, GetStageAdmissionFee(), CURRENCY_GOLD, STAGESTARBUTTONZOOM * zoom, false, false, false);

}

void DrawStageLabel(int x, int y, int textIdx, int stage, int room, bool label, float zoom)
{
	//float width = StringWidth(textId[textIdx], zoom) + (float)(4 * _2X) * zoom + GetNumDx(stage * TOTALROOM + room + 1, false, NUM_FONT_NORMAL, false, false, zoom, false);// + GetNumDx(room, MINUS, NUM_FONT_NORMAL, false, false, zoom);// +(float)(4 * _2X) * zoom + StringWidth(textId[TEXT_FLOOR], zoom);
	float width;

	memset(tempStr, 0, sizeof(tempStr));
	//sprintf(tempStr, "%s %d-%d", textId[textIdx], stage + 1, room + 1);
	sprintf(tempStr, "%s %d", textId[textIdx], room + 1);

	//width = StringWidth(tempStr) + StringWidth(textId[textIdx], zoom);// + GetNumDx(room, MINUS, NUM_FONT_NORMAL, false, false, zoom);// +(float)(4 * _2X) * zoom + StringWidth(textId[TEXT_FLOOR], zoom);

	SetColor(false);
	//SetFontColor(COLOR_WHITE);

	if (label == true) {
		DrawImage(512, 19, 2, 612, x + (float)(-512 / 2) * zoom, y + (float)8 * _2X * zoom, false, false, false, false, false, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

		//DrawLabel(x + (float)( - 88 * _2X) / 2 * zoom, y + (float)8 * _2X * zoom, false, zoom, cvtDest, cvtLayer, buffering);
	}

	CenterTextStr(tempStr, x, y, 1.2f * zoom);
	//몇
	//DrawText(stage * TOTALROOM + room + 1, x - width / 2, y + (float)(1 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, false, false, false, zoom, false, cvtDest, cvtLayer, buffering);

	//��������
	//DrawText(textIdx, x - width / 2 + (float)(4 * _2X) * zoom + GetNumDx(stage * TOTALROOM + room + 1, false, NUM_FONT_NORMAL, false, false, zoom, false), y, zoom, cvtDest, cvtLayer, buffering);

}


//�ϳ��� ����󸶸�?�׸��� �Լ�
//����󸶾���?������Ʈ�� �޾Ƽ� �׷��ִµ�, ��ġ�� �ٸ���. 
//
void DrawDiorama(int x, int y, int type, float zoom)
{
	int i = 0, j = 0, k = 0, l = 0;
	int sortedCrewIdx[TOTAL_CREW + TOTALCHAR];
	int sortedCrewY[TOTAL_CREW + TOTALCHAR];
	int crewType, crewCmf;
	int crewX, crewY;
	int crewMotion = false;
	float cloudZoom;
	float zoomBefore;
	int objStartY = STATUSWIN_Y + (rh - 4) * TSIZE;

	memset(&sortedCrewIdx, -1, sizeof(sortedCrewIdx));
	memset(&sortedCrewY, -1, sizeof(sortedCrewY));

	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + type], MAP_DIORAMA_IMG + type);
	
#ifdef MAPTEST
	SetAlpha(8);
	SetSectionClip(xOffset, DY, DX - 2 * xOffset, DY - STATUSWIN_Y, false);

	if (effect.color == 0x9900FF) {
		DrawBackMap(xOffset, STATUSWIN_Y, robinmap, 1.0f);

		//��Ʈ���� ���� �Ȱ� �Ѹ���
		if (frame / MOTIONDIV % 4 == 0)
			demoFrame++;

		//SetAlpha(Min(demoFrame, 8));
		MemRect(xOffset, STATUSWIN_Y, DX - 2 * xOffset, REALDY, 0x7B48AE);

		for (i = -64 * _2X; i < rw * TSIZE + 64 * _2X; i += 64 * _2X) {
			//큰안개
			SetAlpha(Min(demoFrame, 16));
			//c51.bmp
			DrawImage(64 * _2X, 48 * _2X, 194 * _2X, 0 * _2X, xOffset + i - rx - (demoFrame % 64), STATUSWIN_Y + 128 * _2X - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + CMF_CASTLE_BOSS4], MONSTER_IMG + CMF_CASTLE_BOSS4);
			DrawImage(64 * _2X, 48 * _2X, 194 * _2X, 0 * _2X, xOffset + i - rx + (demoFrame % 64), STATUSWIN_Y + 88 * _2X - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + CMF_CASTLE_BOSS4], MONSTER_IMG + CMF_CASTLE_BOSS4);

			//작은안개
			//c51.bmp
			//작은 - 큰안개
			DrawImage(80 * _2X, 16 * _2X, 76 * _2X, 140 * _2X, xOffset + i - 28 * _2X - rx - (demoFrame % 64) * _2X, STATUSWIN_Y + (96 * _2X - (21 * _2X * (i % 2))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + CMF_CASTLE_BOSS4], MONSTER_IMG + CMF_CASTLE_BOSS4);
			//작은 - 중간안개
			DrawImage(32 * _2X, 6 * _2X, 156 * _2X, 147 * _2X, xOffset + i - 22 * _2X - rx + (demoFrame % 32) * _2X, STATUSWIN_Y + (78 * _2X - (19 * _2X * (i % 2))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + CMF_CASTLE_BOSS4], MONSTER_IMG + CMF_CASTLE_BOSS4);
			//작은 - 작은안개
			DrawImage(26 * _2X, 4 * _2X, 61 * _2X, 78 * _2X, xOffset + i + 23 * _2X - rx - (demoFrame % 26) * _2X, STATUSWIN_Y + (69 * _2X - (20 * _2X * (i % 2))) - ry, false, false, false, false, false, 1.0f, sprite[MONSTER_IMG + CMF_CASTLE_BOSS4], MONSTER_IMG + CMF_CASTLE_BOSS4);

		}

		SetAlpha(32);
	}
	else {
		if (doubleBuffer) {
			switch (drawHandle) {
			default:
				switch (drawHandle) {
				case MD_PLAY:
				case MD_DEMO:
				case MD_BATTLE:
				case MD_RAID:
				case MD_BOSSRAID:
					DrawBuffer(xOffset, DY, DX, DY, bufferTexture[BUFFER_PLAY]);

					SetSectionClip(xOffset, STATUSWIN_Y + (rh - 4) * TSIZE, DX - 2 * xOffset, (rh - 4) * TSIZE, false);

					DrawBackMapFar(xOffset - rx / TSIZE, STATUSWIN_Y, robinmap, rw * TSIZE, 1.0f);

					//���⿡ 
					UnSectionClip(false);
					break;
				}


				DrawBuffer(xOffset - rx + offX, -ry + offY + STATUSWIN_Y + TILEDY, (rw - 4) * TSIZE, (rh - 4) * TSIZE, bufferTexture[BUFFER_TILE]);

				//근경 파트1
				DrawBackMapFront(xOffset - rx + offX, -ry + offY + STATUSWIN_Y, robinmap, 1.0f);

				//if (attackDelay) {
				//	SetAlpha(24);
				//	MemRect(xOffset, STATUSWIN_Y + TILEDY, DX - 2 * xOffset, TILEDY, effect.color, gScreenBuffer, gScreenLayer, false);
				//	SetAlpha(32);
				//}
#ifdef CURTAIN
				tempCurtainFrame = curtainFrame;
				curtainFrame = 0;
				TheaterDraw();
				curtainFrame = tempCurtainFrame;
#endif
				break;
			}
		}
		else {
			DrawBackMap(xOffset, STATUSWIN_Y, robinmap, 1.0f);
		}
	}

	if (effect.color) {
		SetAlpha(24);
		MemRect(xOffset, STATUSWIN_Y + TILEDY, DX - 2 * xOffset, TILEDY, effect.color);
		SetAlpha(32);
	}

	UnSectionClip(false);

	//#ifdef CENTERDISPLAY
	//	SetSectionClip(xOffset, DY, DX - 2 * xOffset, DY - STATUSWIN_Y, false);
	//#endif
	SetAlpha(32);
#endif

	//if (drawHandle == MD_PLAY)
	//	DrawLabel(x + (float)(DIORAMASIZE_X / 2 - 48 * _2X) * zoom, y, TEXT_MAPNAME + dioramaMap[type], zoom * 1.5f, cvtDest, cvtLayer, buffering);
	switch (drawHandle) {
	case MD_DEMO:
	case MD_PLAY:
	case MD_BATTLE:
	case MD_GACHA:
		
		if (!effect.color)
			for (i = NEUTRAL; i < ITEMOBJ; i++) {
				if (ao[i].active && ao[i].attr) {
					zoomBefore = ao[i].zoom;
					ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
					if (ao[i].type == OBJ_BOX)
						ShadowImage(40 * _2X, 16 * _2X, 25 * _2X, 1 * _2X, ao[i].x - (float)20 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
					else
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
					//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
					ao[i].zoom = zoomBefore;
				}
			}

		//�׸��ں��� ���� �׷����� �ϴ� ������Ʈ
		if (!effect.color)
			for (i = NEUTRAL; i < ITEMOBJ; i++) {
				if (ao[i].active) {
					switch (ao[i].type) {
					case OBJ_BRIDGE:
						ao[i].str = 0;
					case OBJ_MOVE:
					case OBJ_DROP:
					case OBJ_SEWAGESTONE:
					case OBJ_MARK:
					case OBJ_CLOAKING:
					case OBJ_PUSH:
					case OBJ_CARPET:
					case OBJ_DIANATRAP:
					case OBJ_DIANASTONE:
					case OBJ_MAXXTRAP:
					case OBJ_GATE:
					case OBJ_SUNBLOCK:
					case OBJ_BREAKSTONE:
					case OBJ_MAGMA:
					case OBJ_MAGMABLOCK:
					case OBJ_SLED:
					case OBJ_ICEBREAK:
					case OBJ_INVISIBLE:
					case OBJ_DIMENSION:
					case OBJ_GOLEMBLOCK:
					case OBJ_BALLBLOCK:
						ao[i].zoom *= dioramaZoom;
						ao[i].y -= floatOffsetY;
						DrawObj(&ao[i]);
						ao[i].y += floatOffsetY;
						ao[i].zoom /= dioramaZoom;
						break;
					}
				}
			}

		//배 그려주기
		for (i = ENEMY; i < NEUTRAL; i++) {
			if (ao[i].type == NPC_SHIP && ao[i].active == true) {
				ao[i].zoom *= dioramaZoom;
				DrawObj(&ao[i]);
				ao[i].zoom /= zoomBefore;
			}
		}

		//상자 그림자
		if (ao[ITEMBOX].active == true) {
			zoomBefore = ao[ITEMBOX].zoom;
			ao[ITEMBOX].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[ITEMBOX].x - (float)12 * _2X * ao[ITEMBOX].zoom, objStartY - BOXPOSITION_Y - ry + (float)14 * _2X * ao[ITEMBOX].zoom, SHADOW_IMG, ao[ITEMBOX].zoom);
			ao[ITEMBOX].zoom = zoomBefore;
		}
		//ShadowImage(&ao[ITEMBOX], cvtDest, cvtLayer, buffering);

	//주인공 그림자
		for (i = 0; i < CASTLEALL; i++) {
			//CASTLEALL은 CREW + TOTAL_CREW(동료 "종류" 수)로 잡힌 값이라, 실제 오브젝트 배열에서는
			//ENEMY 구간까지 넘어간다(지금 값으로 CASTLEALL=67, ENEMY=47). 그대로 두면 적에게도
			//여기서 그림자가 한 번 더 그려지고, 아래 "적 그림자"와 합쳐 이중으로 찍힌다.
			//예전에는 둘 다 몬스터 자기 y에 그려져 정확히 겹쳐서 안 보였는데, 적 그림자를
			//주인공 바닥선으로 옮기면서 두 개가 떨어져 드러났다.
			if (i >= ENEMY)
				break;

			if (ao[i].active) {
				if (ao[i].moveHandler == PLAYERMOVE) {
					//��Ƴ�?�ڴ� ����϶�?�׸��� �׸��� ����
					if ((ao[i].type == DIANA && ao[i].motion == PO_C1_SLEEP) || ao[i].motion == PO_C0_WARP5)
						continue;
					else {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						ao[i].zoom = zoomBefore;
					}
				}
				else {
					if (ao[i].etc != 17) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;
					}
					//DrawShadowPlayer(&ao[i], cvtDest, cvtLayer, buffering);
				}
			}
		}

		//적 그림자
		for (i = ENEMY; i < TOTALOBJECT; i++) {
			if (ao[i].active && ao[i].moveHandler < BULLET3WAYMOVE) {
				//몬스터 그림자는 자기 발밑이 아니라 주인공과 같은 바닥선에 그린다.
				//ENEMY_ONEEYE처럼 공중에 뜬 적은 자기 y에 붙이면 그림자까지 같이 떠버리고,
				//그렇다고 충돌검사용 타일 바닥에 맞추면 성벽처럼 지형 높이가 제멋대로인 곳에서
				//엉뚱한 데 찍힌다. 전투는 주인공과 몬스터가 같은 바닥선에 서는 구도라 이게 맞다.
				//
				//아래 case들이 전부 ao[i].y로 그림자 위치를 잡으므로, 그리는 동안만 값을
				//바꿔치기하고 되돌린다(BAHAMUT case가 floatOffsetY로 하던 것과 같은 방식).
				//되돌리기 전에 빠져나가는 continue/return이 없어야 하는데, 이 루프에는 없다.
				//NEUTRAL 이후(상자/아이템 등)는 원래 자리에 그려야 해서 건드리지 않는다.
				int shadowYBack = ao[i].y;

				if (i < NEUTRAL)
					ao[i].y = ao[ROBIN].ny;

				switch (ao[i].type) {
				case NPC_KING:
					if (ao[i].etc != 3 && ao[i].etc != 2) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;

					}
					break;
				case NPC_DOBEL:
				case NPC_GAGEL:
					if (ao[i].etc != 7 && ao[i].etc != 8) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;
					}
					break;
				case ENEMY_ANGEL:
				case ENEMY_ANGEL_RED:
				case ENEMY_ANGEL_BLUE:
				case ENEMY_ANGEL_PURPLE:
				case ENEMY_ANGEL_GREEN:
				case ENEMY_ANGEL_GOLD:
				case ENEMY_ANGEL_BLACK:
					if (ao[i].etc < ANGEL_DASHUP) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;
					}
					break;
				case ENEMY_CASTLE_BOSS1:
				case ENEMY_CASTLE_BOSS1_RED:
				case ENEMY_CASTLE_BOSS1_BLUE:
				case ENEMY_CASTLE_BOSS1_PURPLE:
				case ENEMY_CASTLE_BOSS1_GREEN:
				case ENEMY_CASTLE_BOSS1_GOLD:
				case ENEMY_CASTLE_BOSS1_BLACK:
				case ENEMY_CIRCLE:
				case ENEMY_CIRCLE_RED:
				case ENEMY_CIRCLE_BLUE:
				case ENEMY_CIRCLE_PURPLE:
				case ENEMY_CIRCLE_GREEN:
				case ENEMY_CIRCLE_GOLD:
				case ENEMY_CIRCLE_BLACK:
				case ENEMY_FOGRA:
				case ENEMY_FOGRA_RED:
				case ENEMY_FOGRA_BLUE:
				case ENEMY_FOGRA_PURPLE:
				case ENEMY_FOGRA_GREEN:
				case ENEMY_FOGRA_GOLD:
				case ENEMY_FOGRA_BLACK:
				case NPC_FOUNTAIN:
				case ENEMY_DARKDRAGON:
				case ENEMY_DARKDRAGON_RED:
				case ENEMY_DARKDRAGON_BLUE:
				case ENEMY_DARKDRAGON_PURPLE:
				case ENEMY_DARKDRAGON_GREEN:
				case ENEMY_DARKDRAGON_GOLD:
				case ENEMY_DARKDRAGON_BLACK:
				case ENEMY_GHOST:
				case ENEMY_GHOST_RED:
				case ENEMY_GHOST_BLUE:
				case ENEMY_GHOST_PURPLE:
				case ENEMY_GHOST_GREEN:
				case ENEMY_GHOST_GOLD:
				case ENEMY_GHOST_BLACK:
				case ENEMY_SHIP:
				case ENEMY_SHIP_RED:
				case ENEMY_SHIP_BLUE:
				case ENEMY_SHIP_PURPLE:
				case ENEMY_SHIP_GREEN:
				case ENEMY_SHIP_GOLD:
				case ENEMY_SHIP_BLACK:
				case ENEMY_BULLET_NOSHADOW:
				case NPC_SHIP:
				case ENEMY_DEATH:
				case ENEMY_DEATH_RED:
				case ENEMY_DEATH_BLUE:
				case ENEMY_DEATH_PURPLE:
				case ENEMY_DEATH_GREEN:
				case ENEMY_DEATH_GOLD:
				case ENEMY_DEATH_BLACK:
				case ENEMY_LIGHTNING:
				case ENEMY_LIGHTNING_RED:
				case ENEMY_LIGHTNING_BLUE:
				case ENEMY_LIGHTNING_PURPLE:
				case ENEMY_LIGHTNING_GREEN:
				case ENEMY_LIGHTNING_GOLD:
				case ENEMY_LIGHTNING_BLACK:
				case ENEMY_SLIME:
				case ENEMY_SLIME_RED:
				case ENEMY_SLIME_BLUE:
				case ENEMY_SLIME_PURPLE:
				case ENEMY_SLIME_GREEN:
				case ENEMY_SLIME_GOLD:
				case ENEMY_SLIME_BLACK:
					break;
				case NPC_LABETH:
				case ENEMY_LABETH:
				case ENEMY_LABETH_RED:
				case ENEMY_LABETH_BLUE:
				case ENEMY_LABETH_PURPLE:
				case ENEMY_LABETH_GREEN:
				case ENEMY_LABETH_GOLD:
				case ENEMY_LABETH_BLACK:
					if (ao[i].moveHandler != STRAIGHTMOVE) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;
					}
					break;
				case ENEMY_LARVA:
				case ENEMY_LARVA_RED:
				case ENEMY_LARVA_BLUE:
				case ENEMY_LARVA_PURPLE:
				case ENEMY_LARVA_GREEN:
				case ENEMY_LARVA_GOLD:
				case ENEMY_LARVA_BLACK:
					if (ao[i].etc != LARVA_HIDED) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;
					}
					break;
				case ENEMY_SLING:
				case ENEMY_SLING_RED:
				case ENEMY_SLING_BLUE:
				case ENEMY_SLING_PURPLE:
				case ENEMY_SLING_GREEN:
				case ENEMY_SLING_GOLD:
				case ENEMY_SLING_BLACK:
					if (ao[i].moveHandler != SLINGMOVE) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;
					}
					break;
				case ENEMY_SPACE2:
				case ENEMY_SPACE2_RED:
				case ENEMY_SPACE2_BLUE:
				case ENEMY_SPACE2_PURPLE:
				case ENEMY_SPACE2_GREEN:
				case ENEMY_SPACE2_GOLD:
				case ENEMY_SPACE2_BLACK:
					if (ao[i].moveHandler != STRAIGHTMOVE) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;
					}
					break;
				case ENEMY_BAHAMUT:
				case ENEMY_BAHAMUT_RED:
				case ENEMY_BAHAMUT_BLUE:
				case ENEMY_BAHAMUT_PURPLE:
				case ENEMY_BAHAMUT_GREEN:
				case ENEMY_BAHAMUT_GOLD:
				case ENEMY_BAHAMUT_BLACK:
					//if (ao[i].moveHandler == BAHAMUTBODYMOVE)
					zoomBefore = ao[i].zoom;
					ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
					ao[i].y -= floatOffsetY;
					ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
					//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
					ao[i].y += floatOffsetY;
					ao[i].zoom = zoomBefore;
					break;
				default:
					if (ao[i].moveHandler != MERCHANTMOVE) {
						zoomBefore = ao[i].zoom;
						ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
						ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom, objStartY - (ao[i].y - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom, SHADOW_IMG, ao[i].zoom);
						//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
						ao[i].zoom = zoomBefore;
					}
					break;
				}

				//그림자용으로 바꿔놨던 y를 되돌린다. 이게 빠지면 몬스터가 주인공 높이로 순간이동한다.
				ao[i].y = shadowYBack;
			}
		}

		if (skillUsed == false && buffItemUsed == false)
			//아이템 그림자
			for (i = ITEMOBJ; i < TOTALOBJECT; i++) {
				if (ao[i].active/* && ao[i].status == WALK*/) {
					int pxl;

					switch (ao[i].mainFrame % 9) {
					default:
						pxl = 2;
						break;
					case 1:
					case 2:
					case 3:
						pxl = 1;
						break;
					case 5:
					case 6:
					case 7:
						pxl = 3;
						break;
					}

					//c.bmp
					zoomBefore = ao[i].zoom;
					ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;
					
					float jumpHeight = ao[i].ny - ao[i].y;

					if (jumpHeight < 0.0f)
						jumpHeight = 0.0f;

					float maxJumpHeight = 40.0f * _2X;

					// 0.0 ~ 1.0
					float jumpRatio = jumpHeight / maxJumpHeight;

					if (jumpRatio > 1.0f)
						jumpRatio = 1.0f;

					// �ְ������� ���� ũ���� 55%���� ���?
					float shadowJumpScale = 1.0f - jumpRatio * 0.45f;

					ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, ao[i].x - (float)12 * _2X * ao[i].zoom * shadowJumpScale, objStartY - (ao[i].ny - OBJIMGGAP) - ry + (float)8 * _2X * ao[i].zoom * shadowJumpScale, SHADOW_IMG, ao[i].zoom * shadowJumpScale);
					//DrawShadowCommon(&ao[i], cvtDest, cvtLayer, buffering);
					ao[i].zoom = zoomBefore;
				}
			}

		InitContext();
		if (!effect.color)
			if (skillUsed == false && buffItemUsed == false)
				//�÷��̾�� ���� �׷��� �ϴ� ������Ʈ(�⺻)
				for (i = NEUTRAL; i < TOTALOBJECT; i++) {
					if (ao[i].active) {
						switch (ao[i].type) {
						case OBJ_MOVE:
						case OBJ_DROP:
						case OBJ_SEWAGESTONE:
						case OBJ_REPULSION:
						case OBJ_MARK:
						case OBJ_CLOAKING:
						case OBJ_PUSH:
						case OBJ_CARPET:
						case OBJ_DIANATRAP:
						case OBJ_DIANASTONE:
						case OBJ_MAXXTRAP:
						case OBJ_GATE:
						case OBJ_SUNBLOCK:
						case OBJ_BREAKSTONE:
						case OBJ_BUBBLE:
						case OBJ_MAGMA:
						case OBJ_MAGMABLOCK:
						case OBJ_BRIDGE:
						case OBJ_STALACTITE:
						case OBJ_SPIKE:
						case OBJ_MAGNET:
						case OBJ_SLED:
						case OBJ_ICEBREAK:
						case OBJ_INVISIBLE:
						case OBJ_DIMENSION:
						case OBJ_GOLEMBLOCK:
						case OBJ_BALLBLOCK:
						case OBJ_CYCLON:
						case OBJ_ITEM:
							break;
						default:
							ao[i].zoom *= dioramaZoom;
							DrawObj(&ao[i]);
							ao[i].zoom /= dioramaZoom;
							break;
						}
					}
				}


		//EnemyUserProfileDraw(&enemyHouse, xOffset + ao[ENEMYUSEROBJ].x - ry - RAIDGOLDBARWIDTH / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ao[ENEMYUSEROBJ].y - ry - ao[ENEMYUSEROBJ].cpy + RAIDGOLDBARHEIGHT, ao[ENEMYUSEROBJ].zoom, gScreenBuffer, gScreenLayer, false);

		//적 그리기
		for (i = TOTALOBJECT - 1; i >= NEUTRAL; i--) {
			if (ao[i].active) {
#ifdef HITMARKWHITE
				if (ao[i].attacked)
					SetColor(COLOR_WHITE);
				else if (ao[i].dead == true) {
					SetColor(COLOR_GREY);
				}
#endif
				ao[i].zoom *= dioramaZoom;
				DrawObj(&ao[i]);
				ao[i].zoom /= dioramaZoom;
#ifdef HITMARKWHITE
				SetColor(false);
#endif
			}
		}

		//����׸���?
		for (i = BULLET; i >= CREW; i--) {
			if (ao[i].active && ao[i].type != NPC_SHIP && i != SOLDIER) {

				if (playerHeadZoom) {
					ao[i].head = true;
				}

				ao[i].zoom *= dioramaZoom;
				DrawObj(&ao[i]);
				ao[i].zoom /= dioramaZoom;

				ao[i].head = false;

				//if (ao[i].attack == ATTACK_NORMAL && ao[i].attackFrame <= attackDelayFrame[ao[i].type]) {
				//	MemRect(ao[i].x - 12 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - ao[i].y - 1 * _2X, 24 * _2X * ao[i].attackFrame / attackDelayFrame[ao[i].type], 2 * _2X, COLOR_REALRED, gScreenBuffer, gScreenLayer, false);
				//}

				grayScale = 0;
				SetColor(false);


			}
		}

		//적 그리기
		for (i = ENEMY; i < NEUTRAL; i++) {
			if (ao[i].active && ao[i].type != NPC_SHIP) {
#ifdef HITMARKWHITE
				if (ao[i].attacked)
					SetColor(COLOR_WHITE);
				else if (ao[i].dead == true) {
					SetColor(COLOR_GREY);
				}
#endif
				if (ao[i].type == ENEMY_SHIP
					|| ao[i].type == ENEMY_SHIP_RED
					|| ao[i].type == ENEMY_SHIP_BLUE
					|| ao[i].type == ENEMY_SHIP_PURPLE
					|| ao[i].type == ENEMY_SHIP_GREEN
					|| ao[i].type == ENEMY_SHIP_GOLD
					|| ao[i].type == ENEMY_SHIP_BLACK) {
					int j;

					for (j = i + 4; j >= i; j--)
						if (ao[j].active) {
							ao[i].zoom *= dioramaZoom;
							DrawObj(&ao[i]);
							ao[i].zoom /= dioramaZoom;
						}

					i += 4;
				}
				else if (ao[i].type == ENEMY_DARKDRAGON
					|| ao[i].type == ENEMY_DARKDRAGON_RED
					|| ao[i].type == ENEMY_DARKDRAGON_BLUE
					|| ao[i].type == ENEMY_DARKDRAGON_PURPLE
					|| ao[i].type == ENEMY_DARKDRAGON_GREEN
					|| ao[i].type == ENEMY_DARKDRAGON_GOLD
					|| ao[i].type == ENEMY_DARKDRAGON_BLACK) {
					int j;

					for (j = i + ao[i].status; j >= i; j--) {
						if (ao[j].active) {
							ao[i].zoom *= dioramaZoom;
							DrawObj(&ao[i]);
							ao[i].zoom /= dioramaZoom;

						}
					}

					i += ao[i].status;
				}
				else {
					ao[i].zoom *= dioramaZoom;
					DrawObj(&ao[i]);
					ao[i].zoom /= dioramaZoom;
				}
#ifdef HITMARKWHITE
				SetColor(false);
#endif
			}
		}

		
		//솔져 그리기
		for (i = CREW - 1; i >= 0; i--) {
			if (ao[i].active && ao[i].type != NPC_SHIP) {

				if (playerHeadZoom) {
					ao[i].head = true;
				}

				ao[i].zoom *= dioramaZoom;
				DrawObj(&ao[i]);
				ao[i].zoom /= dioramaZoom;

				ao[i].head = false;

				//if (ao[i].attack == ATTACK_NORMAL && ao[i].attackFrame <= attackDelayFrame[ao[i].type]) {
				//	MemRect(ao[i].x - 12 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - ao[i].y - 1 * _2X, 24 * _2X * ao[i].attackFrame / attackDelayFrame[ao[i].type], 2 * _2X, COLOR_REALRED, gScreenBuffer, gScreenLayer, false);
				//}

				grayScale = 0;
				SetColor(false);


			}
		}

		//플레이어 그리기
		for (i = SOLDIER + MAXENEMYOBJ - 1; i >= SOLDIER; i--) {
			if (ao[i].active) {

				if (playerHeadZoom) {
					ao[i].head = true;
				}

				ao[i].zoom *= dioramaZoom;
				DrawObj(&ao[i]);
				ao[i].zoom /= dioramaZoom;

				ao[i].head = false;

				//if (ao[i].attack == ATTACK_NORMAL && ao[i].attackFrame <= attackDelayFrame[ao[i].type]) {
				//	MemRect(ao[i].x - 12 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - ao[i].y - 1 * _2X, 24 * _2X * ao[i].attackFrame / attackDelayFrame[ao[i].type], 2 * _2X, COLOR_REALRED, gScreenBuffer, gScreenLayer, false);
				//}

				grayScale = 0;
				SetColor(false);


			}
		}

		//탄환 그리기
		for (i = ENEMYUSEROBJ - 1; i >= BULLET; i--) {
			if (ao[i].active && ao[i].type != NPC_SHIP) {

				if (playerHeadZoom) {
					ao[i].head = true;
				}

				ao[i].zoom *= dioramaZoom;
				DrawObj(&ao[i]);
				ao[i].zoom /= dioramaZoom;

				ao[i].head = false;

				//if (ao[i].attack == ATTACK_NORMAL && ao[i].attackFrame <= attackDelayFrame[ao[i].type]) {
				//	MemRect(ao[i].x - 12 * _2X - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - ao[i].y - 1 * _2X, 24 * _2X * ao[i].attackFrame / attackDelayFrame[ao[i].type], 2 * _2X, COLOR_REALRED, gScreenBuffer, gScreenLayer, false);
				//}

				grayScale = 0;
				SetColor(false);


			}
		}

		//체력바
		for (i = ITEMOBJ - 1; i >= 0; i--) {
			if (ao[i].active && ao[i].type != NPC_SHIP && ((i < TOTALCHAR && ao[i].ps[PS_HP] > 0) || (i >= ENEMY && i < NEUTRAL && ao[i].maxhp > 0)) && ao[i].moveHandler != REGENMOVE) {

				zoomBefore = ao[i].zoom;
				ao[i].zoom = dioramaZoom * DIORAMAZOOM_REMAINDER;

				//몬스터 체력바는 몬스터 바로 밑이 아니라 주인공 체력바와 같은 높이에 둔다.
				//그림자를 주인공 바닥선에 그리므로(위 "적 그림자" 참고) 체력바도 같은 기준을 써야
				//공중에 뜬 적이나 크기가 큰 보스에서 바가 몸통에 파묻히거나 혼자 내려가지 않는다.
				//아래 SimpleHpBarDraw()들이 전부 ao[i].y로 위치를 잡으므로 그 동안만 값을 바꾼다.
				//몬스터 zoom으로 오프셋을 주면 보스처럼 큰 놈만 바가 따로 놀아서, 보정 없이
				//주인공 바닥선을 그대로 쓴다. 주인공 바는 자기 y로 그려지고 서 있을 땐 y == ny다.
				int hpYBack = ao[i].y;

				if (i >= ENEMY && i < NEUTRAL)
					ao[i].y = ao[ROBIN].ny;

				switch (ao[i].moveHandler) {
				case BAHAMUTHEADMOVE:
					SimpleHpBarDraw(ao[i].hp, i < TOTALCHAR ? ao[i].ps[PS_HP] : ao[i].maxhp, xOffset + ao[i].x - rx - (float)(SIMPLEHPBARWIDTH + 2 * _2X) / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ao[i].y - ry - OBJIMGGAP - 16 * _2X, ao[i].zoom, i >= ENEMY ? ENEMYHPBARCOLOR : PLAYERHPBARCOLOR);
					break;
				case DEBRIONARMMOVE:
				case DEBRIONBODYMOVE:
					SimpleHpBarDraw(ao[i].hp, i < TOTALCHAR ? ao[i].ps[PS_HP] : ao[i].maxhp, xOffset + ao[i].x - rx - (float)(SIMPLEHPBARWIDTH + 2 * _2X) / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ao[i].y - ry - OBJIMGGAP - 0 * _2X, ao[i].zoom, i >= ENEMY ? ENEMYHPBARCOLOR : PLAYERHPBARCOLOR);
					break;
				default:
					//SimpleHpBarDraw(ao[i].hp, i < TOTALCHAR ? ao[i].ps[PS_HP] : ao[i].maxhp, xOffset + ao[i].x - rx - (float)(SIMPLEHPBARWIDTH + 2 * _2X) / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ao[i].y - ry - OBJIMGGAP - 0 * _2X, 1.0f/*ao[i].zoom*/, i >= ENEMY ? ENEMYHPBARCOLOR : PLAYERHPBARCOLOR, cvtDest, cvtLayer, buffering);
					SimpleHpBarDraw(ao[i].hp, i < TOTALCHAR ? ao[i].ps[PS_HP] : ao[i].maxhp, xOffset + ao[i].x - rx - (float)(SIMPLEHPBARWIDTH + 2 * _2X) / 2, STATUSWIN_Y + (rh - 4) * TSIZE - ao[i].y - ry - OBJIMGGAP - 0 * _2X, ao[i].zoom, i >= ENEMY ? ENEMYHPBARCOLOR : PLAYERHPBARCOLOR);
					break;
				}
				/*
				switch (i) {
				case ROBIN:
				case DIANA:
				case MAXX:
					if (bar[BAR_PLAYERHP + i].addView)
						DrawNum2AutoSpaceing(bar[BAR_PLAYERHP + i].add, xOffset + ao[i].x - rx - (float)(SIMPLEHPBARWIDTH + 2 * _2X) / 2 + (float)(SIMPLEHPBARWIDTH), STATUSWIN_Y + (rh - 4) * TSIZE - ao[i].y - ry - OBJIMGGAP - 0 * _2X + (float)8 * _2X, RIGHT, false, bar[BAR_PLAYERHP + i].add >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.3f * ao[i].zoom, false, true);
					break;
				default:
					if (i >= ENEMY && i < NEUTRAL) {
						if (ao[i].mom == i && bar[BAR_ENEMYHP + GetEnemyBarIdx(i)].addView) {
							DrawNum2AutoSpaceing(bar[BAR_PLAYERHP + i].add, xOffset + ao[i].x - rx - (float)(SIMPLEHPBARWIDTH + 2 * _2X) / 2 + (float)(SIMPLEHPBARWIDTH), STATUSWIN_Y + (rh - 4) * TSIZE - ao[i].y - ry - OBJIMGGAP - 0 * _2X + (float)8 * _2X, RIGHT, false, bar[BAR_ENEMYHP + i].add >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.3f * ao[i].zoom, false, true);
						}
					}
					break;
				}
				*/
				//체력바용으로 바꿔놨던 y를 되돌린다.
				ao[i].y = hpYBack;
				ao[i].zoom = zoomBefore;
			}
		}

		if (skillUsed == false && buffItemUsed == false)
			//���ΰ� ���� �׷����� �ϴ� �߸�������Ʈ
			for (i = NEUTRAL; i < TOTALOBJECT; i++) {
				if (ao[i].active) {
					switch (ao[i].type) {
					case OBJ_BRIDGE:
						ao[i].str = 1;
					case OBJ_REPULSION:
					case OBJ_BUBBLE:
					case OBJ_STALACTITE:
					case OBJ_SPIKE:
					case OBJ_MAGNET:
					case OBJ_CYCLON:
					case OBJ_ITEM:
						ao[i].zoom *= dioramaZoom;
						DrawObj(&ao[i]);
						ao[i].zoom /= dioramaZoom;
						break;
					}
				}
			}

		//��Ƴ�?���� �۵��� ȿ��
		if (skillUsed == false || buffItemUsed == false)
			if (dianaTrapFrame)
				DrawNeutral(OBJ_STAMPEFFECT0 + (dianaTrapFrame % 10), xOffset + ao[dianaTrapFrame / 10 + NEUTRAL].x - rx, objStartY - ao[dianaTrapFrame / 10 + NEUTRAL].y - ry + OBJIMGGAP, 0, ao[dianaTrapFrame / 10 + NEUTRAL].zoom);

#ifdef DEBUG
		g_nTestCnt4++;
		g_nTestAvg4 += (int)GetTimeGap();
#endif

		UnSectionClip(false);


		if (buffItemUsed > 0 && attackDelay == 0) {
			for (i = 0; i < TOTALBUFF; i++) {
				if (ao[raidPlayer].buff[i] > 0) {
					if (i < TOTALPLAYERBUFF) {
						//��ų ����
						const unsigned short* ptrBuff = &buffData[i * 4];

						if (i == INC_IGNORE && (ao[raidPlayer].buff[i] - 1) % 2 == 1)
							ao[raidPlayer].motion = PO_C1_DENY1;
						else
							ao[raidPlayer].motion = *(ptrBuff + 3) + (ao[raidPlayer].buff[i] == 1 ? *(ptrBuff + 2) : ((ao[raidPlayer].buff[i] - 1) % *(ptrBuff + 2)));

						InitMotion(&ao[raidPlayer]);
						SetAlpha(24);
						if (playerHeadZoom)
							ao[raidPlayer].head = true;
						ao[raidPlayer].zoom *= dioramaZoom;
						DrawPlayer(&ao[raidPlayer], ao[raidPlayer].motion, -rx + (rw - 4) * TSIZE / 2 - 2 * TSIZE, -ry + objStartY, ao[raidPlayer].dirF, 3, false, false, false);
						ao[raidPlayer].zoom /= dioramaZoom;
						ao[raidPlayer].head = false;
						SetAlpha(32);
					}
					else {
						int bFrame;

						if (buffBlend[i - INC_DAMAGE_RING])
							SetBlend(12, buffBlend[i - INC_DAMAGE_RING]);

						if (i >= INC_DAMAGE_ARENA)
							bFrame = robin.playtime;
						else
							bFrame = ao[raidPlayer].buff[i];

						//반지버프
						switch (i) {
						default:
							if (ao[raidPlayer].buff[i] % 6 != 5)
								DrawEffect(BUFF_DMG0 + bFrame % 6, -rx + (rw - 4) * TSIZE / 2 - 2 * TSIZE, -ry + objStartY, ao[raidPlayer].dirF, false, 3);
							break;
						case INC_DEFENSE_RING:
						case INC_EVASION_RING:
						case INC_STUN_RING:
						case INC_EXP_RING:
						case INC_DEFENSE_ARENA:
						case INC_MAGIC_ARENA:
							DrawEffect(BUFF_ARMOR0 + bFrame % 12, -rx + (rw - 4) * TSIZE / 2 - 2 * TSIZE, -ry + objStartY, ao[raidPlayer].dirF, false, 3);
							break;
						}

						UnSetBlend();
					}
				}
			}
		}

		for (i = 0; i < NEUTRAL; i++) {
			if (ao[i].active) {
				//퀘스트 관련 아이콘
				if (ao[i].str == -1 && ao[i].def > 0 && !robin.bossRoom)
					DrawEffect(EFFECT_QUEST0_0 + (ao[i].def - QUESTREADY) * 5 + Abs(4 - ao[i].frame % 9), ao[i].x - rx, objStartY - (ao[i].y - OBJIMGGAP) - ry, 0, false, ao[i].zoom);

				//이모티콘

				if (ao[i].moveHandler < BULLET3WAYMOVE && ao[i].icon && areaFrame == 0 && arenaFrame == 0) {

					int bFrame = Min(2, ao[i].icon / TOTALEMOTICON);

					if (ao[i].icon % TOTALEMOTICON > 1) {

						DrawArray(IMG_BALLOON0 + bFrame, ao[i].x - rx + balloonPos[bFrame * 2] + ao[i].dirF * 4 * _2X, objStartY - (ao[i].y + ao[i].cpy + 24 * _2X - OBJIMGGAP) - ry - balloonPos[bFrame * 2 + 1], zoom);
					}

					SetAlpha(32);

					DrawEmoticon(ao[i].icon % TOTALEMOTICON, ao[i].iconFrame, ao[i].icon / TOTALEMOTICON, ao[i].x + 2 * _2X * DIR(ao[i].dirF) - rx, objStartY - (ao[i].y + ao[i].cpy - 19 * _2X - OBJIMGGAP) - ry, 1.0f);
				}
			}
		}

		//���� ���� �ð� �׷��ֱ�
		for (i = ENEMY; i < NEUTRAL; i++) {
			if (ao[i].active && ao[i].moveHandler < BULLET3WAYMOVE && ao[i].skillIdx > 0) {
				DrawFrame(ao[i].x + 2 * _2X * DIR(ao[i].dirF) - rx - 24 * _2X, objStartY - (ao[i].y + ao[i].cpy - 19 * _2X - OBJIMGGAP) - ry, 48 * _2X, 20 * _2X, FRAME_SHOPBALLOON);
			}

			//생성 그리기
			for (i = SOLDIER; i < NEUTRAL; i++) {
				if (ao[i].active && ao[i].drawHandler == REGENDRAW && ao[i].type != NPC_SHIP) {
					ao[i].zoom *= dioramaZoom;
					DrawCmfDetail(CMF_NPC_HEART, summonMotion[Min(19, ao[i].frame)], ao[i].x - rx, objStartY + (float)64 * _2X * ao[i].zoom - (PxlUp(&ao[i]) + ao[i].cy / 2 - OBJIMGGAP) - ry, LEFT, ao[i].zoom, false, false);
					ao[i].zoom /= dioramaZoom;
				}
			}


		}

		for (i = 0; i < TOTALHITMARK; i++) {
			if (dmgInfo[i].frame > 0) {
				SetColor(dmgInfo[i].color);
				DrawNum2(dmgInfo[i].dmg, dmgInfo[i].x, dmgInfo[i].y, CENTER, false, MINUS, true, dmgInfo[i].zoom, false);
				SetColor(false);

				dmgInfo[i].frame++;

				if (dmgInfo[i].frame == FPS)
					memset(&dmgInfo[i], 0, sizeof(dmgInfo));
			}
		}

		if (!effect.color2)
			EffectDraw(x + (float)STATUSWIN_Y, zoom);

		//DrawImage(640, 640, 0, 0, 0, DY, false, false, false, false, false, zoom, sprite[TREE_IMG], cvtDest, cvtLayer, TREE_IMG, buffering);
		//DrawImage(160, 201, (1 % 30) % 6 * 161, (1 % 30) / 6 * 201, DX / 2, DY / 2, false, false, false, false, false, zoom, sprite[TREE_IMG], cvtDest, cvtLayer, TREE_IMG, buffering);
		break;
	}
}

void DrawGrid(int x, int y, int w, int h, int dx, int dy, int color1, int color2)
{
	int i, j;
	int iCnt = (w / dx) + ((w % dx) ? 1 : 0);
	int jCnt = (h / dy) + ((h % dy) ? 1 : 0);
	//return;

	//MemRect(x, y, w, h, color1, cvtDest);
	for (i = 0; i < iCnt; i++) {
		for (j = 0; j < jCnt; j++) {
			if ((i + j) % 2)
				MemRect(x + i * dx, y - j * dy, dx, dy, colorSet[4 * color1]);
			//DrawColorFrame(x + i * dx, y - j * dy, dx, dy, colorSet[4 * color1], colorSet[4 * color1 + 1], colorSet[4 * color1 + 2], colorSet[4 * color1 + 3], cvtDest, cvtLayer, buffering);
			else
				MemRect(x + i * dx, y - j * dy, dx, dy, colorSet[4 * color2]);
			//DrawColorFrame(x + i * dx, y - j * dy, dx, dy, colorSet[4 * color2], colorSet[4 * color2 + 1], colorSet[4 * color2 + 2], colorSet[4 * color2 + 3], cvtDest, cvtLayer, buffering);
		}
	}
}

//type 0이 가로타입, 1가 세로타입
void GradiationFrame(int x, int y, int w, int h, int type)
{
	switch (type) {
	case 0:
		MemRect(x, y, 1 * _2X, h, 0x3D5996);//1
		MemRect(x + w - 1 * _2X, y, 1 * _2X, h, 0x3D5996);
		MemRect(x + 1 * _2X, y, 2 * _2X, h, 0x324A7D);//2
		MemRect(x + w - 1 * _2X - 2 * _2X, y, 2 * _2X, h, 0x324A7D);
		MemRect(x + 1 * _2X + 2 * _2X, y, 3 * _2X, h, 0x2D426F);//3
		MemRect(x + w - 1 * _2X - 2 * _2X - 3 * _2X, y, 3 * _2X, h, 0x2D426F);
		MemRect(x + 1 * _2X + 2 * _2X + 3 * _2X, y, 4 * _2X, h, 0x283A62);//4
		MemRect(x + w - 1 * _2X - 2 * _2X - 3 * _2X - 4 * _2X, y, 4 * _2X, h, 0x283A62);
		MemRect(x + 1 * _2X + 2 * _2X + 3 * _2X + 4 * _2X, y, 5 * _2X, h, 0x223254);//5
		MemRect(x + w - 1 * _2X - 2 * _2X - 3 * _2X - 4 * _2X - 5 * _2X, y, 5 * _2X, h, 0x223254);

		MemRect(x + 15 * _2X, y, w - 15 * _2X * 2, h, 0x1D2B47);//6
		break;
	case 1:
		MemRect(x, y, w, h / 3, 0x44475B);
		MemRect(x, y - h / 3, w, h / 3, 0x4D5170);
		MemRect(x, y - h / 3 * 2, w, h / 3, 0x565F83);
		break;
	case 2:
		MemRect(x, y, w, h / 5, 0x664445);
		MemRect(x, y - h / 5 * 1, w, h / 5, 0x886645);
		MemRect(x, y - h / 5 * 2, w, h / 5, 0xB8965A);
		MemRect(x, y - h / 5 * 3, w, h / 5, 0xE6D699);
		MemRect(x, y - h / 5 * 4, w, h / 5, 0xFFFFCC);
		break;
	case 3:
		MemRect(x, y, w, h / 5, 0x005D65);
		MemRect(x, y - h / 5, w, h / 5, 0x007E8A);
		MemRect(x, y - h / 5 * 2, w, h / 5, 0x0095A2);
		MemRect(x, y - h / 5 * 3, w, h / 5, 0x00C2D3);
		MemRect(x, y - h / 5 * 4, w, h - (h / 5 * 4), 0xA7F7FF);
		break;
	case 4://녹색
		MemRectRound(x + 0 * _2X, y - 0 * _2X, w - 0 * _2X, h - 0 * 2 * _2X, 0x154F03, 4 * _2X);
		MemRectRound(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * 2 * _2X, 0x73F32C, 4 * _2X);
		MemRectRound(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 3 * 2 * _2X, 0x2FBA09, 4 * _2X);
		MemRectRound(x + 3 * _2X, y - 3 * _2X, w - 6 * _2X, h / 2, 0x6BEB24, 4 * _2X);
		break;
	case 5://빨간
		MemRectRound(x + 0 * _2X, y - 0 * _2X, w - 0 * _2X, h - 0 * 2 * _2X, 0x663300, 4 * _2X);
		MemRectRound(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * 2 * _2X, 0xE79EA5, 4 * _2X);
		MemRectRound(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 3 * 2 * _2X, 0x8E251F, 4 * _2X);
		MemRectRound(x + 3 * _2X, y - 3 * _2X, w - 6 * _2X, h / 2, 0xE8534D, 4 * _2X);
		break;
	case 6://�Ķ���(������ ���ø޴��� ���� ��)
		MemRectRound(x + 0 * _2X, y - 0 * _2X, w - 0 * _2X, h - 0 * 2 * _2X, 0x003399, 4 * _2X);
		MemRectRound(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * 2 * _2X, 0xA9D8F2, 4 * _2X);
		MemRectRound(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 3 * 2 * _2X, 0x2D66BD, 4 * _2X);
		MemRectRound(x + 3 * _2X, y - 3 * _2X, w - 6 * _2X, h / 2, 0x68ADF8, 4 * _2X);
		break;
	case 7://회색
		MemRectRound(x + 0 * _2X, y - 0 * _2X, w - 0 * _2X, h - 0 * 2 * _2X, 0x666666, 4 * _2X);
		MemRectRound(x + 1 * _2X, y - 1 * _2X, w - 2 * _2X, h - 2 * 2 * _2X, 0xF1F2F6, 4 * _2X);
		MemRectRound(x + 2 * _2X, y - 2 * _2X, w - 4 * _2X, h - 3 * 2 * _2X, 0xBAC3D2, 4 * _2X);
		MemRectRound(x + 3 * _2X, y - 3 * _2X, w - 6 * _2X, h / 2, 0xDAE1EB, 4 * _2X);
		break;

	}
}

void SetBlend(int depth, int color)
{
	int dTemp;
	int originCol = color;

	color = ((color >> 8) & 0xF800) | ((color >> 5) & 0x07E0) | ((color >> 3) & 0x001F);

	if (blendColor && blendDepth) {
		dTemp = (depth << 5) / Max(1, (blendDepth + depth));
		blendColor = (((((blendColor & 0xF81F) * (32 - dTemp)) >> 5) & 0xF81F) | ((((blendColor & 0x07E0) * (32 - dTemp)) >> 5) & 0x07E0)) + (((((color & 0xF81F) * dTemp) >> 5) & 0xF81F) | ((((color & 0x07E0) * dTemp) >> 5) & 0x07E0));
		blendDepth = (depth + blendDepth) >> 1;
	}
	else {
		blendColor = color;
		blendDepth = depth;
	}

	/*
	if (originCol == 0xFFFFFF)
		SetColor(0xFFFFFF);
	else
		SetColor(blendColor);
	*/

	SetColor(originCol);
	//SetColor(blendColor);
}

void UnSetBlend(void)
{
	blendColor = 0;
	blendDepth = 0;
	//grayScale = 0;//Abs(32 - frame % 64);

	SetColor(false);
}

void SetAlpha(int alpha)
{
	if (alpha > 32)
		alpha = 32;
	else if (alpha < 4)
		alpha = 4;

	m_lgrpAlpha = alpha;
	//MC_grpSetContext(&gContext, MC_GRP_CONTEXT_ALPHA_IDX, (void *)((m_lgrpAlpha << 3) - 1));
}

float GetAlphaWidth(int idx, int type, float zoom)
{
	int i;
	float w = 0;

	for (i = alphaOff[idx]; i < alphaOff[idx + 1]; i++) {
		w += alphaX[TOTALALPHA * (type * 2 + 1) + alphaData[i]];

		switch (type) {
		default:
			w++;
			break;
		case FONT_SMALL:
		case FONT_SMALL2:
		case FONT_LARGE:
			w--;
			break;
		}
	}

	return (float)(w + 1) * zoom;
}
//일단 대문자만 하자. 소문자는 나중에 필요하면
float GetAlphaWidth2(int idx, float zoom)
{
	int i;
	float w = 0;

	for (i = alphaOff[idx]; i < alphaOff[idx + 1]; i++) {
		w += alpha2[alphaData[i] * 6];
		w += 2 * _2X;
	}

	return (float)(w + 2 * _2X) * zoom;
}

float GetGoldAlphaWidth(int idx, int type, float zoom)
{
	int i;
	float w = 0;

	for (i = alphaOff[idx]; i < alphaOff[idx + 1]; i++) {
		w += goldAlphaInfo[TOTALALPHA * 6 * type + TOTALALPHA * 0 + alphaData[i]];

		//switch (type) {
		//default:
		//	w--;
		//	break;
		//}
	}

	return (float)(w + 1) * zoom;
}

void DrawGoldAlpha(int x, int y, int idx, int type, float zoom, int align, bool ani, float rotation)
{
	int i, j;
	float w;
	int h, srcX, srcY, gapX, gapY;
	float width = 0;

	width = GetGoldAlphaWidth(idx, type, zoom);

	switch (align) {
	case LEFT:
		break;
	case CENTER:
		x -= width / 2;
		break;
	case RIGHT:
		x -= width;
		break;
	}

	for (i = alphaOff[idx]; i < alphaOff[idx + 1]; i++) {
		w = goldAlphaInfo[TOTALALPHA * 6 * type + TOTALALPHA * 0 + alphaData[i]];
		h = goldAlphaInfo[TOTALALPHA * 6 * type + TOTALALPHA * 1 + alphaData[i]];
		srcX = goldAlphaInfo[TOTALALPHA * 6 * type + TOTALALPHA * 2 + alphaData[i]];
		srcY = goldAlphaInfo[TOTALALPHA * 6 * type + TOTALALPHA * 3 + alphaData[i]];
		gapX = goldAlphaInfo[TOTALALPHA * 6 * type + TOTALALPHA * 4 + alphaData[i]] * zoom;
		gapY = goldAlphaInfo[TOTALALPHA * 6 * type + TOTALALPHA * 5 + alphaData[i]] * zoom;

		if (alphaData[i] != SPC) {
			SetColor(COLOR_BROWN);
			for (j = 0; j < 4; j++) {
				DrawImage(w, h, srcX, srcY, x + (float)solidPosition[2 * j + 0] * zoom, y + (float)solidPosition[2 * j + 1] * zoom + (ani == true ? alphaJumpFrame[(i - alphaOff[idx] + frame / MOTIONDIV) % 11] / _2X * zoom : 0), false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			}
			SetColor(false);
			DrawImage(w, h, srcX, srcY, x, y + (ani == true ? alphaJumpFrame[(i - alphaOff[idx] + frame / MOTIONDIV) % 11] / _2X * zoom : 0), false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);

		}
		x += (float)(w - 1 * _2X) * zoom;
	}
}

void DrawAlpha(int x, int y, int idx, int type, float zoom, float rotation)
{
	int i, w;


	//#ifdef TTFFONT
	//	DrawTextStrSystem(textId[idx], x, y, zoom, LEFT, true, cvtDest, cvtLayer, buffering);
	//#else
	//	DrawTextStr(TEXTPTR(idx), x, y, cvtDest, cvtLayer, buffering);
	//#endif

	//	return;

	for (i = alphaOff[idx]; i < alphaOff[idx + 1]; i++) {
		w = alphaX[TOTALALPHA * (type * 2 + 1) + alphaData[i]];

		switch (alphaData[i]) {
		case SPC:
			break;
		case DOT:
			//DrawTextStr(".", x, y, zoom, cvtDest, cvtLayer, buffering);
			if (type == FONT_LARGE)
				DrawImage(3 * _2X, 11 * _2X, 106 * _2X, 196 * _2X, x, y, false, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);
			else if (type == FONT_SMALL)
				DrawImage(w, alphaY[4 + type], alphaX[TOTALALPHA * type * 2 + alphaData[i]], alphaY[type], x, y, false, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);
			break;
		default:
			DrawImage(w, alphaY[4 + type], alphaX[TOTALALPHA * type * 2 + alphaData[i]], alphaY[type], x, y, false, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);
			break;
		}

		switch (type) {
		default:
			x += (float)(w - 1) * zoom;
			break;
		case FONT_LARGE:
			x += (float)w * zoom;
			break;
		}
	}
}

void DrawAlpha2(int x, int y, int idx, float zoom, float rotation)
{
	int i, w;

	for (i = alphaOff[idx]; i < alphaOff[idx + 1]; i++) {
		switch (alphaData[i]) {
		case SPC:
			break;
		default:
			DrawImage(alpha2[alphaData[i] * 6], alpha2[alphaData[i] * 6 + 1], alpha2[alphaData[i] * 6 + 2], alpha2[alphaData[i] * 6 + 3], x + (float)alpha2[alphaData[i] * 6 + 4] * zoom, y + (float)alpha2[alphaData[i] * 6 + 5] * zoom, false, false, false, false, false, zoom, sprite[NUM2_IMG], NUM2_IMG);
			break;
		}

		x += (float)(alpha2[alphaData[i] * 6] + 1 * _2X) * zoom;
	}
}


void CenterAlpha(int x, int y, int idx, int type, float rotation, float zoom)
{
	DrawAlpha(x - GetAlphaWidth(idx, type, zoom) / 2, y, idx, type, zoom, rotation);
}

//������ �����ӿ� ���� ��µ�?ù���ڴ� �빮��, �ڿ� ���ڴ� �ҹ��ڷ� ���?�Լ�
void DrawAlphaFrame(int x, int y, int idx, int frame, int font, float rotaion, float zoom)
{
	int i, w;
	int type;

	for (i = alphaOff[idx]; i < ((alphaOff[idx] + frame) < alphaOff[idx + 1] ? (alphaOff[idx] + frame) : alphaOff[idx + 1]); i++) {
		if (i == alphaOff[idx] || alphaData[i - 1] == SPC)//대문자
			type = font;
		else
			type = font;

		w = alphaX[TOTALALPHA * (type * 2 + 1) + alphaData[i]];

		if (alphaData[i] != SPC)
			DrawImage(w, alphaY[4 + type], alphaX[TOTALALPHA * type * 2 + alphaData[i]], alphaY[type], x, y - (type == FONT_SMALL ? 4 : 0) * _2X, false, false, false, false, m_lgrpAlpha, zoom, sprite[COMMON_IMG], COMMON_IMG);

		switch (type) {
		default:
			x += (float)(w - 1 * _2X) * zoom;
			break;
		case FONT_LARGE:
			if (i == 201)		//Exit Dungeon �� ���?���̰� ���?���ڰ� ���ĺ��̹Ƿ�,,
				x += (float)(w + 1 * _2X) * zoom;
			else
				x += (float)(w - 1 * _2X) * zoom;
			break;
		}
	}

	//if (frame % 5 == 0)
	//	PlayMusic(M_TALK);
}

void addCommasToNumber(int number, bool showSign, char* result, size_t bufferSize)
{
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << (showSign ? std::showpos : std::noshowpos) << number;
	std::string formattedNumber = ss.str();

	// 결과 문자열을 char 배열로 복사
	strncpy(result, formattedNumber.c_str(), bufferSize - 1);
	// �������� NULL ���ڿ� �߰�
	result[bufferSize - 1] = '\0';
}

int GetNumFigure(long long int num)
{
	//자리수 구하는 함수
	int i = 0;

	num = Abs(num);

	do {
		i++;
		num = num / 10;
	} while (num);

	return i;
}

float GetNumDx2(long long int num, int sign, int digit, bool comma, float zoom, bool fixed)
{
	int i;
	float width = 0;
	num = Abs(num);
	long long int numOrigin = num;
	int figureNum = GetNumFigure(num);
	int widthNum = 0;
	int widestNum = 5;//이미지 숫자중에 가장 넓이가 넓은 것은 5


	if (fixed == true) {
		for (i = 0; i < figureNum; i++)
			widthNum += widestNum * pow(10, i);

		do {
			width += (float)(num2Off[(num % 10) * 6 + 0] + 2 * _2X) * zoom;

			widthNum = widthNum / 10;
			digit--;
		} while (widthNum != 0 || digit > 0);
	}
	else {
		do {
			width += (float)(num2Off[(num % 10) * 6 + 0] + 2 * _2X) * zoom;

			num = num / 10;
			digit--;
		} while (num != 0 || digit > 0);
	}

	if (sign) {
		width += (float)(53 + 2 * _2X) * zoom;
	}
	//자릿수 콤마
	if (comma)
		width += ((GetNumFigure(numOrigin) - 1) / 3) * (float)(22 + 6 * _2X) * zoom;

	return width + (float)(2 * _2X) * zoom;
}

float GetNumDx(long long int num, int sign, int font, int digit, bool comma, float zoom, bool fixed)
{
	int i;
	float width = 0;
	num = Abs(num);
	long long int numOrigin = num;
	int figureNum = GetNumFigure(num);
	int widthNum = 0;
	int widestNum = 5;//이미지 숫자중에 가장 넓이가 넓은 것은 5


	if (fixed == true) {
		for (i = 0; i < figureNum; i++)
			widthNum += widestNum * pow(10, i);

		do {
			switch (font) {
			case NUM_FONT_SMALL:
				width += (float)(4 * _2X) * zoom;
				break;
			case NUM_FONT_NORMAL:
				width += (float)(mediumNumData[10 + widthNum % 10]) * zoom;
				break;
			default:
				width += (float)(largeNumData[10 + widthNum % 10]) * zoom;// *(sign + 1);
				break;
			}

			widthNum = widthNum / 10;
			digit--;
		} while (widthNum != 0 || digit > 0);
	}
	else {
		do {
			switch (font) {
			case NUM_FONT_SMALL:
				width += (float)(4 * _2X) * zoom;
				break;
			case NUM_FONT_NORMAL:
				width += (float)(mediumNumData[10 + num % 10]) * zoom;
				break;
			default:
				width += (float)(largeNumData[10 + num % 10]) * zoom;// *(sign + 1);
				break;
			}

			num = num / 10;
			digit--;
		} while (num != 0 || digit > 0);
	}

	if (sign) {
		switch (font) {
		case NUM_FONT_SMALL:
			width += (float)8 * _2X * zoom;
			break;
		case NUM_FONT_NORMAL:
			width += (float)9 * _2X * zoom;
			break;
		case NUM_FONT_LARGE:
			width += (float)12 * _2X * zoom;
			break;
		}
	}
	//자릿수 콤마
	if (comma)
		switch (font) {
		case NUM_FONT_SMALL:
			width += (float)((GetNumFigure(numOrigin) - 1) / 3) * 3 * _2X * zoom;
			break;
		case NUM_FONT_NORMAL:
			width += ((GetNumFigure(numOrigin) - 1) / 3) * (float)4 * _2X * zoom;
			break;
		default:
			width += ((GetNumFigure(numOrigin) - 1) / 3) * (float)6 * _2X * zoom;
			break;
		}

	switch (font) {
	case NUM_FONT_NORMAL:
		return (float)(width - 1 * _2X * zoom);
	case NUM_FONT_SMALL:
		return (float)(width + 1 * _2X * zoom);
	default:
		return (float)(width - 1 * _2X * zoom);
	}
}

float GetGoldNumDx(long long int num, int sign, int digit, bool comma, float zoom)
{
	long long int numOrigin = num;
	float width = 0;

	do {
		width += (float)(goldNumData[num % 10] - 1 * _2X) * zoom;
		num = num / 10;
		digit--;
	} while (num != 0 || digit > 0);

	if (sign > 0) {
		width += (float)31 * zoom;
	}
	else if (sign < 0) {
		width += (float)27 * zoom;
	}

	//자릿수 콤마
	if (comma)
		width += (float)((GetNumFigure(numOrigin) - 1) / 3) * (float)16 * zoom;

	return width;
}

float GetBigNumGoldDx(long long int num, int sign, int font, int digit, bool comma, float width, float zoom)
{
	int alphaArray[] = { ALPHA_NUM_K, ALPHA_NUM_M, ALPHA_NUM_B, ALPHA_NUM_T, ALPHA_NUM_Q, ALPHA_NUM_Z, ALPHA_NUM_Y };

	int gap = 0;//줄여야 되는 자리수
	float gapWidth;
	long long gapNum = num;
	int alphaIdx;
	float dotWidth = (float)(17) * zoom;//소수점 도트의 넓이
	int figureNum = GetNumFigure(num);
	int num2;

	if (GetGoldNumDx(num, sign, digit, comma, zoom) <= width || width == false) {
		return GetGoldNumDx(num, sign, digit, comma, zoom);
	}

	do {
		gapNum /= 10;
		gap++;//줄여야 되는 자리수
		gapWidth = GetGoldNumDx(gapNum, sign, digit, comma, zoom);
	} while (gapWidth > width && gapNum > 0);


	//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.
	if (gap % 3) {
		do {
			gap++;
			if (gapNum >= 10)
				gapNum /= 10;
			gapWidth = GetGoldNumDx(gapNum, sign, digit, comma, zoom);
		} while (gap % 3);
	}

	figureNum -= gap;

	alphaIdx = alphaArray[(gap - 3) / 3];
	gapWidth += GetGoldAlphaWidth(alphaIdx, font, zoom);

	if (figureNum == 0) {
		num2 = gapNum;
		gapNum = 0;

		gapWidth = GetGoldNumDx(num2, sign, digit, comma, zoom) + dotWidth + GetGoldNumDx(gapNum, false, digit, false, zoom) + GetGoldAlphaWidth(alphaIdx, font, zoom);
	}
	else if (figureNum == 1) {

		temp = num - gapNum * pow(10, GetNumFigure(num) - 1);//소수위 자리수들을 제거한 나머지 숫자를 구한다.
		num2 = temp / pow(10, GetNumFigure(num) - 2);

		gapWidth += dotWidth + GetGoldNumDx(num2, sign, digit, comma, zoom);
	}
	else
		num2 = 0;

	return gapWidth;
}

float GetNumDxTTF(long long int num, int sign, int font, int digit, bool comma, float zoom, bool fixed)
{
	int i;
	Size textSize;
	float width;
	return GetNumDx(num, sign, font, digit, comma, zoom, fixed);
	memset(&tempStr, 0, sizeof(tempStr));
	addCommasToNumber(num, sign, tempStr, sizeof(tempStr));
	fontLabelWidth = Label::createWithTTF(tempStr, "fonts/font.ttf", FONT_HEIGHT + 1 * _2X);
	textSize = fontLabelWidth->getContentSize();
	width = textSize.width;
	//fontLabelWidth->release();
	return width;
}

float GetBigNumDxTTF(long long int num, int sign, int font, int digit, bool comma, float width, float zoom, bool fixed)
{
	int i;
	int alphaArray[] = { TEXT_ALPHA_K, TEXT_ALPHA_M, TEXT_ALPHA_B, TEXT_ALPHA_T, TEXT_ALPHA_Q, TEXT_ALPHA_Z, TEXT_ALPHA_Y };

	int gap = 0;//줄여야 되는 자리수
	float gapWidth;
	long long gapNum = num;
	int alphaIdx;
	float dotWidth = (float)(3 * _2X) * zoom;// = StringWidthTTF(".", zoom);//소수점 도트의 넓이
	int figureNum = GetNumFigure(num);
	int num2;
	int widthNum = 0;
	int widestNum = 5;//이미지 숫자중에 가장 넓이가 넓은 것은 5

	return GetBigNumDx(num, sign, NUM_FONT_NORMAL, false, comma, width, zoom, fixed);

	if (fixed) {
		for (i = 0; i < figureNum; i++)
			widthNum += widestNum * pow(10, i);
	}

	if (GetNumDxTTF(num, sign, font, digit, comma, zoom, fixed) <= width || width == false || num == 0) {
		return GetNumDxTTF(num, sign, font, digit, comma, zoom, fixed);
	}

	if (fixed) {
		do {
			gapNum /= 10;
			widthNum /= 10;
			gap++;//줄여야 되는 자리수
			gapWidth = GetNumDxTTF(gapNum, sign, font, digit, comma, zoom, fixed);
		} while (gapWidth > width);


		//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.
		if (gap % 3) {
			do {
				gap++;
				if (gapNum >= 10) {
					gapNum /= 10;
					widthNum /= 10;
				}
				gapWidth = GetNumDxTTF(gapNum, sign, font, digit, comma, zoom, fixed);
			} while (gap % 3);
		}
	}
	else {
		do {
			gapNum /= 10;
			gap++;//줄여야 되는 자리수
			gapWidth = GetNumDxTTF(gapNum, sign, font, digit, comma, zoom, fixed);
		} while (gapWidth > width);


		//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.
		if (gap % 3) {
			do {
				gap++;
				if (gapNum >= 10) {
					gapNum /= 10;
				}
				gapWidth = GetNumDxTTF(gapNum, sign, font, digit, comma, zoom, fixed);
			} while (gap % 3);
		}
	}

	figureNum -= gap;

	alphaIdx = alphaArray[(gap - 3) / 3];
	gapWidth += StringWidthTTF(textId[alphaIdx], zoom);

	if (figureNum == 0) {
		num2 = gapNum;
		gapNum = 0;

		gapWidth = GetNumDxTTF(num2, sign, font, digit, comma, zoom, fixed) + dotWidth + GetNumDx(gapNum, false, font, digit, false, zoom, fixed) + GetAlphaWidth(alphaIdx, font, zoom);
	}
	else if (figureNum == 1) {

		temp = num - gapNum * pow(10, GetNumFigure(num) - 1);//소수위 자리수들을 제거한 나머지 숫자를 구한다.
		num2 = temp / pow(10, GetNumFigure(num) - 2);

		gapWidth += dotWidth + GetNumDxTTF(num2, sign, font, digit, comma, zoom, fixed);
	}
	else
		num2 = 0;

	return gapWidth;
}

float GetBigNumDx(long long int num, int sign, int font, int digit, bool comma, float width, float zoom, bool fixed)
{
	int i;
	int alphaArray[] = { ALPHA_NUM_K, ALPHA_NUM_M, ALPHA_NUM_B, ALPHA_NUM_T, ALPHA_NUM_Q, ALPHA_NUM_Z, ALPHA_NUM_Y };

	int gap = 0;//줄여야 되는 자리수
	float gapWidth;
	long long gapNum = num;
	int alphaIdx;
	float dotWidth = (float)(3 * _2X) * zoom;//소수점 도트의 넓이
	int figureNum = GetNumFigure(num);
	int num2;
	int widthNum = 0;
	int widestNum = 5;//이미지 숫자중에 가장 넓이가 넓은 것은 5

	if (fixed) {
		for (i = 0; i < figureNum; i++)
			widthNum += widestNum * pow(10, i);
	}

	if (GetNumDx(num, sign, font, digit, comma, zoom, fixed) <= width || width == false || num == 0) {
		return GetNumDx(num, sign, font, digit, comma, zoom, fixed);
	}

	if (fixed) {
		do {
			gapNum /= 10;
			widthNum /= 10;
			gap++;//줄여야 되는 자리수
			gapWidth = GetNumDx(widthNum, sign, font, digit, comma, zoom, fixed);
		} while (gapWidth > width);


		//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.
		if (gap % 3) {
			do {
				gap++;
				if (gapNum >= 10) {
					gapNum /= 10;
					widthNum /= 10;
				}
				gapWidth = GetNumDx(widthNum, sign, font, digit, comma, zoom, fixed);
			} while (gap % 3);
		}
	}
	else {
		do {
			gapNum /= 10;
			gap++;//줄여야 되는 자리수
			gapWidth = GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed);
		} while (gapWidth > width);


		//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.
		if (gap % 3) {
			do {
				gap++;
				if (gapNum >= 10) {
					gapNum /= 10;
				}
				gapWidth = GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed);
			} while (gap % 3);
		}
	}

	figureNum -= gap;

	alphaIdx = alphaArray[(gap - 3) / 3];
	gapWidth += GetAlphaWidth(alphaIdx, font, zoom);

	if (figureNum == 0) {
		num2 = gapNum;
		gapNum = 0;

		gapWidth = GetNumDx(num2, sign, font, digit, comma, zoom, fixed) + dotWidth + GetNumDx(gapNum, false, font, digit, false, zoom, fixed) + GetAlphaWidth(alphaIdx, font, zoom);
	}
	else if (figureNum == 1) {

		temp = num - gapNum * pow(10, GetNumFigure(num) - 1);//소수위 자리수들을 제거한 나머지 숫자를 구한다.
		num2 = temp / pow(10, GetNumFigure(num) - 2);

		gapWidth += dotWidth + GetNumDx(num2, sign, font, digit, comma, zoom, fixed);
	}
	else
		num2 = 0;

	return gapWidth;
}


void DrawXNumGold(long long int num, int x, int y, bool ani, float zoom, int align, int digit)
{
	//if (ani)
	//	MemRect(x - 2 * _2X, y + 2 * _2X, 16 * _2X + GetNumDx(num, false, NUM_FONT_LARGE, 2, false), 24 * _2X, itemColor[frame % 6], cvtDest, cvtLayer, buffering);
	//num = 100;
	float width = GetGoldNumDx(num, false, digit, false, zoom * 1.3f) + GetGoldAlphaWidth(ALPHA_X, FONT_GOLD_LARGE, zoom * 0.8f) + (float)(2 * _2X * zoom);

	switch (align) {
	case LEFT:
		break;
	case RIGHT:
		x -= width;
		break;
	case CENTER:
		x -= width / 2;
		break;
	}

	DrawGoldAlpha(x, y - (float)(4 * _2X) * zoom, ALPHA_X, FONT_GOLD_LARGE, zoom * 0.8f, LEFT, false, false);
	DrawGoldNum(num, x + GetGoldAlphaWidth(ALPHA_X, FONT_GOLD_LARGE, zoom * 0.8f) + (float)(2 * _2X * zoom), y + (float)4 * _2X * zoom, LEFT, digit, false, false, zoom * 1.3f);

}

void DrawXNum(long long int num, int x, int y, bool ani, float zoom)
{
	DrawAlpha(x, y - 4 * _2X, TEXT_ALPHA_X, FONT_LARGE, zoom, false);
	DrawNum(num, x + 12 * _2X, y, NUM_FONT_LARGE, LEFT, 2, false, false, zoom, false);
}

void DrawSlashNum(int min, int max, int x, int y, float width, float zoom)
{
	float w = GetNumDx2(min, false, false, true, 1.1f * NUM2ZOOM * zoom, false) + GetNumDx2(max, false, false, true, 1.1f * NUM2ZOOM * zoom, false) + (float)9 * _2X * zoom;
	//DrawNumTTF(min, x, y, NUM_FONT_NORMAL, RIGHT, 0, false, true, zoom, true, cvtDest, cvtLayer, buffering);
	//DrawText(TEXT_SLASH, x + (float)(4 * _2X) * zoom, y, zoom, cvtDest, cvtLayer, buffering);
	//DrawNumTTF(max, x + (float)(12 * _2X) * zoom, y, NUM_FONT_NORMAL, LEFT, 0, false, true, zoom, true, cvtDest, cvtLayer, buffering);
	//DrawNum(min, x, y, NUM_FONT_NORMAL, RIGHT, 0, false, true, zoom, true, cvtDest, cvtLayer, buffering);
	x -= w / 2;
	DrawNum2AutoSpaceing(min, x, y, LEFT, 0, false, width, true, 1.1f * NUM2ZOOM * zoom, false, true);
	DrawText(TEXT_SLASH, x + GetNumDx2(min, false, false, true, 1.1f * NUM2ZOOM * zoom, false) + (float)(2 * _2X) * zoom, y + (float)(0 * _2X) * zoom, zoom);
	DrawNum2AutoSpaceing(max, x + GetNumDx2(min, false, false, true, 1.1f * NUM2ZOOM * zoom, false) + (float)(9 * _2X) * zoom, y, LEFT, 0, false, width, true, 1.1f * NUM2ZOOM * zoom, true, true);
	//DrawNum(max, x + (float)(12 * _2X) * zoom, y, NUM_FONT_NORMAL, LEFT, 0, false, true, zoom, true, cvtDest, cvtLayer, buffering);

}


float DrawNumTTF(long long int num, int x, int y, int font, int align, int digit, bool sign, bool comma, float zoom, bool fixed)
{
	float numWidth = GetNumDx(num, sign, font, digit, comma, zoom, fixed);
	memset(&tempStr, 0, sizeof(tempStr));
	addCommasToNumber(num, sign, tempStr, sizeof(tempStr));
	numWidth = DrawTextStrSystem(tempStr, x, y, 1.0f * zoom, align, true);
	//DrawNum(num, x, y, font, align, digit, sign, comma, zoom, fixed, cvtDest, cvtLayer, buffering);
	return numWidth;
}

void DrawNum2(long long int num, int x, int y, int align, int digit, int sign, bool comma, float zoom, bool fixed)
{
	long long int tempNum = num;
	int numbers = 1;

	switch (align) {
	case CENTER:
		//�������
		x += GetNumDx2(num, sign, digit, comma, zoom, fixed) / 2;
		break;
	case LEFT:
		//��������
		x += GetNumDx2(num, sign, digit, comma, zoom, fixed);
		break;
	}

	x += (float)(2 * _2X) * zoom;

	num = Abs(num);

	//if (sign > 0)
	//{
	//	tempNum = tempNum;
	//}

	//숫자
	do {
		//��ǥ �׷��ֱ�
		if (numbers % 4 == 0 && numbers > 0 && comma) {
			x -= (float)(22 + 6 * _2X) * zoom;
			DrawImage(22, 28, 640, 58, x + (float)(3 * _2X) * zoom, y - (float)(58) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[NUM2_IMG], NUM2_IMG);
		}
		//
		else {
			x -= (float)(num2Off[(num % 10) * 6 + 0] + 2 * _2X) * zoom;
			DrawImage(num2Off[(num % 10) * 6 + 0], num2Off[(num % 10) * 6 + 1], num2Off[(num % 10) * 6 + 2], num2Off[(num % 10) * 6 + 3], x, y, false, false, false, false, m_lgrpAlpha, zoom, sprite[NUM2_IMG], NUM2_IMG);

			num = num / 10;
			digit--;
		}

		numbers++;
	} while (num != 0 || digit > 0);

	//+, - ��ȣǥ��
	if (sign != 0) {
		if (sign == PLUS) {
			x -= (float)(52 + 1 * _2X) * zoom;
			DrawImage(52, 53, 698, 15, x, y - (float)(14) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[NUM2_IMG], NUM2_IMG);
		}
		else {
			x -= (float)(53 + 1 * _2X) * zoom;
			DrawImage(53, 21, 756, 31, x, y - (float)(30) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[NUM2_IMG], NUM2_IMG);
		}
	}
}

void DrawNum(long long int num, int x, int y, int font, int align, int digit, bool sign, bool comma, float zoom, bool fixed)
{
	long long int tempNum = num;
	int numbers = 1;

 	switch (align) {
	case CENTER:
		//�������
		x += GetNumDx(num, sign, font, digit, comma, zoom, fixed) / 2;
		break;
	case LEFT:
		//��������
		x += GetNumDx(num, sign, font, digit, comma, zoom, fixed);
		break;
	}

	switch (font) {
	case NUM_FONT_LARGE:
		x += (float)(1 * _2X) * zoom;
		break;
	default:
		x += (float)(1 * _2X) * zoom;
		break;
	case NUM_FONT_SMALL:
		x -= (float)(1 * _2X) * zoom;
		break;
	}

	num = Abs(num);

	//if (sign > 0)
	//{
	//	tempNum = tempNum;
	//}

	//숫자
	do {
		//��ǥ �׷��ֱ�
		if (numbers % 4 == 0 && numbers > 0 && comma) {
			switch (font) {
			case NUM_FONT_SMALL:
				x -= (float)(3 * _2X) * zoom;
				//c.bmp
				DrawImage(4 * _2X, 5 * _2X, 196 * _2X, 222 * _2X, x, y - (float)(4 * _2X) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[COMMON_IMG], COMMON_IMG);
				break;
			case NUM_FONT_NORMAL:
				x -= (float)(4 * _2X) * zoom;
				DrawImage(5 * _2X, 6 * _2X, 200 * _2X, 222 * _2X, x, y - (float)(8 * _2X) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[COMMON_IMG], COMMON_IMG);
				break;
			default:
				x -= (float)(6 * _2X) * zoom;
				DrawImage(7 * _2X, 8 * _2X, 205 * _2X, 222 * _2X, x, y - (float)(12 * _2X) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[COMMON_IMG], COMMON_IMG);
				break;
			}
		}
		else {
			switch (font) {
			case NUM_FONT_SMALL:
				x -= (float)(4 * _2X) * zoom;
				//c.bmp
				DrawImage(5 * _2X, 7 * _2X, 1 + (num % 10) * (5 * _2X + 1), 63, x, y, false, false, false, false, m_lgrpAlpha, zoom, sprite[NUM_IMG], NUM_IMG);
				break;
			case NUM_FONT_NORMAL:
				x -= (float)(mediumNumData[10 + (num % 10)]) * zoom;
				DrawImage(mediumNumData[10 + (num % 10)], 12 * _2X, mediumNumData[num % 10], mediumNumData[30 + num % 10], x + (float)mediumNumData[20 + (num % 10)] * zoom, y, false, false, false, false, m_lgrpAlpha, zoom, sprite[NUM_IMG], NUM_IMG);
				break;
			default:
				x -= (float)(largeNumData[10 + (num % 10)]) * zoom;// *(sign + 1);
				if (font >= NUM_FONT_LARGE_BACKLIGHTEN) {
					if (font == NUM_FONT_LARGE_BACKLIGHTEN2)
						SetAlpha(16);

					//ef.bmp
					DrawImage(18 * _2X, 20 * _2X, 78 * _2X, 166 * _2X, x - (1) * _2X, y + (1) * _2X, false, false, false, true, false, zoom, sprite[EFFECT_IMG], EFFECT_IMG);

					SetAlpha(32);
				}
				DrawImage(largeNumData[10 + (num % 10)], 18 * _2X, largeNumData[num % 10], largeNumData[30 + num % 10], x + (float)(largeNumData[20 + (num % 10)]) * zoom, y, false, false, false, false, m_lgrpAlpha, zoom, sprite[NUM_IMG], NUM_IMG);
				if (font == NUM_FONT_LARGE_FORELIGHTEN)
					DrawImage(18 * _2X, 20 * _2X, 78 * _2X, 166 * _2X, x - (1) * _2X, y + (1) * _2X, false, false, false, true, false, zoom, sprite[EFFECT_IMG], EFFECT_IMG);

				break;
			}

			num = num / 10;
			digit--;
		}

		numbers++;
	} while (num != 0 || digit > 0);

	//+, - ��ȣǥ��
	if (sign != 0) {
		switch (font) {
		case NUM_FONT_SMALL:
			x -= (float)(7 * _2X) * zoom;
			//c.bmp
			DrawImage(7 * _2X, 7 * _2X, (sign == PLUS ? 168 : 175) * _2X, 27 * _2X, x, y, false, false, false, false, m_lgrpAlpha, zoom, sprite[COMMON_IMG], COMMON_IMG);
			break;
		case NUM_FONT_NORMAL:
			x -= (float)(7 * _2X) * zoom;
			//c.bmp
			DrawImage(7 * _2X, (sign == PLUS ? 7 : 3) * _2X, 215 * _2X, (sign == PLUS ? 133 : 130) * _2X, x, y - (float)((sign == PLUS ? 2 : 4) * _2X + 1) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[EFFECT_IMG], EFFECT_IMG);
			break;
		case NUM_FONT_LARGE:
			x -= (float)(12 * _2X) * zoom;
			if (sign == PLUS)
				DrawImage(12 * _2X, 12 * _2X, 227 * _2X, 134 * _2X, x, y - (float)(3 * _2X) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[EFFECT_IMG], EFFECT_IMG);
			else
				DrawImage(12 * _2X, 4 * _2X, 222 * _2X, 130 * _2X, x, y - (float)(7 * _2X) * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[EFFECT_IMG], EFFECT_IMG);
			break;
		}
	}
}

void DrawGoldNum(long long int num, int x, int y, int align, int digit, int sign, bool comma, float zoom)
{
	int i, j;
	long long int tempNum = num;
	int mul, mule;
	int numbers = 1;
	float width = 0;

	switch (align) {
	case CENTER:
		x += GetGoldNumDx(num, sign, digit, comma, zoom) / 2;
		break;
	case LEFT:
		x += GetGoldNumDx(num, sign, digit, comma, zoom);
		break;
	}

	num = Abs(num);

	//숫자
	do {
		//��ǥ �׷��ֱ�
		if (numbers % 4 == 0 && numbers > 0 && comma) {
			x -= (float)16 * zoom;
			SetColor(COLOR_BROWN);
			for (j = 0; j < 4; j++) {
				DrawImage(17, 21, 191, 381, x + solidPosition[2 * j + 0] * zoom, y + solidPosition[2 * j + 1] * zoom - (float)30 * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			}
			SetColor(false);
			DrawImage(17, 21, 191, 381, x, y - (float)30 * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
		}
		else {
			x -= (float)(goldNumData[num % 10] - 1 * _2X) * zoom;
			SetColor(COLOR_BROWN);
			for (j = 0; j < 4; j++) {
				DrawImage(goldNumData[(num % 10)], goldNumData[10 + (num % 10)], goldNumData[20 + (num % 10)], goldNumData[30 + (num % 10)], x + solidPosition[2 * j + 0] * zoom, y + solidPosition[2 * j + 1] * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			}
			SetColor(false);
			DrawImage(goldNumData[(num % 10)], goldNumData[10 + (num % 10)], goldNumData[20 + (num % 10)], goldNumData[30 + (num % 10)], x, y, false, false, false, false, m_lgrpAlpha, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);

			num = num / 10;
			digit--;
		}

		numbers++;
	} while (num != 0 || digit > 0);


	//+, - ��ȣǥ��
	//+면 1, 0이면 부호없고 -면 -1
	if (sign == PLUS) {
		x -= 30 * zoom;
		DrawImage(29, 28, 266, 360, x, y - 8 * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
	}
	else if (sign == MINUS) {
		x -= 27 * zoom;
		DrawImage(27, 10, 298, 370, x, y - 16 * zoom, false, false, false, false, m_lgrpAlpha, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
	}
}

void DrawBigNumGold(long long int num, int x, int y, int font, int align, int digit, int sign, float width, bool comma, float zoom)
{
	int alphaArray[] = { ALPHA_NUM_K, ALPHA_NUM_M, ALPHA_NUM_B, ALPHA_NUM_T, ALPHA_NUM_Q, ALPHA_NUM_Z, ALPHA_NUM_Y };
	int num1;//소수점 위 숫자(최대 3자리)
	int dot;//소수점 도트의 유무
	int num2;//소수점 아래 숫자(최대 2자리)
	int alpha;//알파자리수
	float num1Width;//num1의 숫자
	float dotWidth = (float)(3 * _2X) * zoom;//소수점 도트의 넓이
	float num2Width;//num2의 숫자
	//int alphaIdx = ALPHA_NUM_A + ((GetNumFigure(num) - 1) / 3) - 1;
	int alphaIdx = GetNumFigure(num) < 6 ? 0 : alphaArray[Min(2, (GetNumFigure(num) - 2) / 3 - 1)];
	int alphaFont = FONT_GOLD_LARGE;//숫자에 따른 알파 폰트

	float alphaGapY;
	float dotGapY;
	int figureNum = GetNumFigure(num);

	float totalWidth;
	long long int temp;

	int gap = 0;//줄여야 되는 자리수
	float gapWidth;
	long long gapNum = num;

	if (width == 0)
		return;

	switch (font) {
	default:
		alphaGapY = (float)(0 * _2X) * zoom;
		dotGapY = (float)(0 * _2X) * zoom;
		break;
	}

	if (GetGoldNumDx(num, sign, digit, comma, zoom) <= width || width == false) {
		DrawGoldNum(num, x, y, align, digit, sign, comma, zoom);
		return;
	}

	do {
		gapNum /= 10;
		gap++;//줄여야 되는 자리수
		gapWidth = GetGoldNumDx(gapNum, sign, digit, comma, zoom);
	} while (gapWidth > width);

	//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.

	if (gap % 3) {
		do {
			gap++;
			if (gapNum >= 10)
				gapNum /= 10;
			gapWidth = GetGoldNumDx(gapNum, sign, digit, comma, zoom);
		} while (gap % 3);
	}

	figureNum -= gap;

	alphaIdx = alphaArray[(gap - 3) / 3];
	gapWidth += GetGoldAlphaWidth(alphaIdx, font, zoom);

	if (figureNum == 0) {
		num2 = gapNum;
		gapNum = 0;

		gapWidth = GetGoldNumDx(num2, sign, digit, comma, zoom) + dotWidth + GetGoldNumDx(gapNum, false, digit, false, zoom) + GetGoldAlphaWidth(alphaIdx, font, zoom);
	}
	else if (figureNum == 1) {

		temp = num - gapNum * pow(10, GetNumFigure(num) - 1);//소수위 자리수들을 제거한 나머지 숫자를 구한다.
		num2 = temp / pow(10, GetNumFigure(num) - 2);

		gapWidth += dotWidth + GetGoldNumDx(num2, sign, digit, comma, zoom);
	}
	else
		num2 = 0;

	switch (align) {
	case LEFT:
		DrawGoldNum(gapNum, x, y, LEFT, digit, sign, comma, zoom);
		if (figureNum <= 1) {
			DrawGoldAlpha(x + GetGoldNumDx(gapNum, sign, 0, comma, zoom), y + alphaGapY, ALPHA_DOT, alphaFont, zoom, LEFT, false, false);
			DrawGoldNum(num2, x + GetGoldNumDx(gapNum, sign, 0, comma, zoom) + dotWidth, y, LEFT, digit, false, comma, zoom);
			DrawGoldAlpha(x + GetGoldNumDx(gapNum, sign, digit, comma, zoom) + dotWidth + GetGoldNumDx(num2, false, 0, comma, zoom), y + alphaGapY, alphaIdx, alphaFont, zoom, LEFT, false, false);
		}
		else
			DrawGoldAlpha(x + GetGoldNumDx(gapNum, sign, digit, comma, zoom), y + alphaGapY, alphaIdx, alphaFont, zoom, LEFT, false, false);
		break;
	case CENTER:
		DrawGoldNum(gapNum, x - gapWidth / 2, y, LEFT, digit, sign, comma, zoom);
		if (figureNum <= 1) {
			DrawGoldAlpha(x - gapWidth / 2 + GetGoldNumDx(gapNum, sign, 0, comma, zoom), y + alphaGapY, ALPHA_DOT, alphaFont, zoom, LEFT, false, false);
			DrawGoldNum(num2, x - gapWidth / 2 + GetGoldNumDx(gapNum, sign, 0, comma, zoom) + dotWidth, y, LEFT, digit, false, comma, zoom);
			DrawGoldAlpha(x - gapWidth / 2 + GetGoldNumDx(gapNum, sign, digit, comma, zoom) + dotWidth + GetGoldNumDx(num2, false, 0, comma, zoom), y + alphaGapY, alphaIdx, alphaFont, zoom, LEFT, false, false);
		}
		else
			DrawGoldAlpha(x - gapWidth / 2 + GetGoldNumDx(gapNum, sign, digit, comma, zoom), y + alphaGapY, alphaIdx, alphaFont, zoom, LEFT, false, false);
		break;
	case RIGHT:
		DrawGoldNum(gapNum, x - gapWidth, y, LEFT, digit, sign, comma, zoom);
		if (figureNum <= 1) {
			DrawGoldAlpha(x - gapWidth + GetGoldNumDx(gapNum, sign, 0, comma, zoom), y + alphaGapY, ALPHA_DOT, alphaFont, zoom, LEFT, false, false);
			DrawGoldNum(num2, x - gapWidth + GetGoldNumDx(gapNum, sign, 0, comma, zoom) + dotWidth, y, LEFT, digit, false, comma, zoom);
			DrawGoldAlpha(x - gapWidth + GetGoldNumDx(gapNum, sign, digit, comma, zoom) + dotWidth + GetGoldNumDx(num2, false, 0, comma, zoom), y + alphaGapY, alphaIdx, alphaFont, zoom, LEFT, false, false);
		}
		else
			DrawGoldAlpha(x - gapWidth + GetGoldNumDx(gapNum, sign, 0, comma, zoom), y + alphaGapY, alphaIdx, alphaFont, zoom, LEFT, false, false);
		break;
	}
}

float DrawBigNumTTF(long long int num, int x, int y, int font, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed)
{

	int alphaArray[] = { TEXT_ALPHA_K, TEXT_ALPHA_M, TEXT_ALPHA_B, TEXT_ALPHA_T, TEXT_ALPHA_Q, TEXT_ALPHA_Z, TEXT_ALPHA_Y };
	int num1;//소수점 위 숫자(최대 3자리)
	int dot;//소수점 도트의 유무
	int num2;//소수점 아래 숫자(최대 2자리)
	int alpha;//알파자리수
	float num1Width;//num1의 숫자
	float dotWidth = (float)3 * _2X * zoom;// StringWidthTTF(".", zoom);//소수점 도트의 넓이
	float num2Width;//num2의 숫자
	//int alphaIdx = ALPHA_NUM_A + ((GetNumFigure(num) - 1) / 3) - 1;
	int alphaIdx = GetNumFigure(num) < 6 ? 0 : alphaArray[Min(2, (GetNumFigure(num) - 2) / 3 - 1)];
	int alphaFont = (font == NUM_FONT_SMALL ? FONT_SMALL : FONT_LARGE);//숫자에 따른 알파 폰트
	float numWidth;

	float alphaGapY;
	float dotGapY;
	int figureNum = GetNumFigure(num);

	float totalWidth;
	long long int temp;

	int gap = 0;//줄여야 되는 자리수
	float gapWidth;
	long long gapNum = num;

	if (width == 0)
		return false;

	memset(tempStr, 0, sizeof(tempStr));
	memset(tempStr2, 0, sizeof(tempStr2));

	alphaGapY = (float)(0 * _2X) * zoom;
	dotGapY = (float)(0 * _2X) * zoom;

	if ((int)GetNumDx(num, sign, font, digit, comma, zoom, fixed) <= (int)width || width == false) {
		DrawNumTTF(num, x, y, font, align, digit, sign, comma, zoom, fixed);
		return true;
	}

	do {
		gapNum /= 10;
		gap++;//줄여야 되는 자리수
		gapWidth = GetNumDxTTF(gapNum, sign, font, digit, comma, zoom, fixed);
	} while (gapWidth > width);

	//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.

	if (gap % 3) {
		do {
			gap++;
			if (gapNum >= 10)
				gapNum /= 10;
			gapWidth = GetNumDxTTF(gapNum, sign, font, digit, comma, zoom, fixed);
		} while (gap % 3);
	}

	figureNum -= gap;

	alphaIdx = alphaArray[(gap - 3) / 3];
	gapWidth += StringWidthTTF(textId[alphaIdx], zoom);

	if (figureNum == 0) {
		num2 = gapNum;
		gapNum = 0;

		gapWidth = GetNumDxTTF(num2, sign, font, digit, comma, zoom, fixed) + dotWidth + GetNumDx(gapNum, false, font, digit, false, zoom, fixed) + GetAlphaWidth(alphaIdx, font, zoom);
	}
	else if (figureNum == 1) {

		temp = num - gapNum * pow(10, GetNumFigure(num) - 1);//소수위 자리수들을 제거한 나머지 숫자를 구한다.
		num2 = temp / pow(10, GetNumFigure(num) - 2);

		gapWidth += dotWidth + GetNumDxTTF(num2, sign, font, digit, comma, zoom, fixed);
	}
	else
		num2 = 0;

	switch (align) {
	case LEFT:
		if (figureNum <= 1) {
			//sprintf(tempStr, "%ld.%ld%s", gapNum, num2, textId[alphaIdx]);

			addCommasToNumber(gapNum, sign, tempStr2, sizeof(tempStr2));
			sprintf(tempStr, "%s.%ld%s", tempStr2, num2, textId[alphaIdx]);

			gapWidth = DrawTextStrSystem(tempStr, x, y, zoom, LEFT, true);

		}
		else {
			//sprintf(tempStr, "%ld%s", gapNum, textId[alphaIdx]);
			addCommasToNumber(gapNum, sign, tempStr2, sizeof(tempStr2));
			sprintf(tempStr, "%s%s", tempStr2, textId[alphaIdx]);

			gapWidth = DrawTextStrSystem(tempStr, x, y, zoom, LEFT, true);
		}
		break;
	case CENTER:
		if (figureNum <= 1) {
			//sprintf(tempStr, "%ld.%ld%s", gapNum, num2, textId[alphaIdx]);
			addCommasToNumber(gapNum, sign, tempStr2, sizeof(tempStr2));
			sprintf(tempStr, "%s.%ld%s", tempStr2, num2, textId[alphaIdx]);

			gapWidth = DrawTextStrSystem(tempStr, x, y, zoom, CENTER, true);
		}
		else {
			//sprintf(tempStr, "%ld%s", gapNum, textId[alphaIdx]);
			addCommasToNumber(gapNum, sign, tempStr2, sizeof(tempStr2));
			sprintf(tempStr, "%ls%s", tempStr2, textId[alphaIdx]);

			gapWidth = DrawTextStrSystem(tempStr, x, y, zoom, CENTER, true);
		}
		break;
	case RIGHT:
		if (figureNum <= 1) {
			//sprintf(tempStr, "%ld.%ld%s", gapNum, num2, textId[alphaIdx]);
			addCommasToNumber(gapNum, sign, tempStr2, sizeof(tempStr2));
			sprintf(tempStr, "%ls.%ld%s", tempStr2, num2, textId[alphaIdx]);

			gapWidth = DrawTextStrSystem(tempStr, x, y, zoom, RIGHT, true);
		}
		else {
			//sprintf(tempStr, "%ld%s", gapNum, textId[alphaIdx]);
			addCommasToNumber(gapNum, sign, tempStr2, sizeof(tempStr2));
			sprintf(tempStr, "%s%s", tempStr2, textId[alphaIdx]);

			gapWidth = DrawTextStrSystem(tempStr, x, y, zoom, RIGHT, true);
		}
		break;
	}

	return gapWidth;
}

void DrawBigNum(long long int num, int x, int y, int font, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed)
{
	int alphaArray[] = { ALPHA_NUM_K, ALPHA_NUM_M, ALPHA_NUM_B, ALPHA_NUM_T, ALPHA_NUM_Q, ALPHA_NUM_Z, ALPHA_NUM_Y };
	int num1;//소수점 위 숫자(최대 3자리)
	int dot;//소수점 도트의 유무
	int num2;//소수점 아래 숫자(최대 2자리)
	int alpha;//알파자리수
	float num1Width;//num1의 숫자
	float dotWidth = (float)(3 * _2X) * zoom;//소수점 도트의 넓이
	float num2Width;//num2의 숫자
	//int alphaIdx = ALPHA_NUM_A + ((GetNumFigure(num) - 1) / 3) - 1;
	int alphaIdx = GetNumFigure(num) < 6 ? 0 : alphaArray[Min(2, (GetNumFigure(num) - 2) / 3 - 1)];
	int alphaFont = (font == NUM_FONT_SMALL ? FONT_SMALL : FONT_LARGE);//숫자에 따른 알파 폰트

	float alphaGapY;
	float dotGapY;
	int figureNum = GetNumFigure(num);

	float totalWidth;
	long long int temp;

	int gap = 0;//줄여야 되는 자리수
	float gapWidth;
	long long gapNum = num;

	if (width == 0)
		return;

	switch (font) {
	case NUM_FONT_SMALL:
		alphaGapY = (float)(0 * _2X) * zoom;
		dotGapY = (float)(0 * _2X) * zoom;
		break;
	case NUM_FONT_NORMAL:
		alphaGapY = (float)(-1 * _2X) * zoom;
		dotGapY = (float)(0 * _2X) * zoom;
		//dotGapY = -5 * _2X;
		break;
	default://NUM_FONT_LARGE
		alphaGapY = (float)(-6 * _2X) * zoom;
		dotGapY = (float)(0 * _2X) * zoom;
		//dotGapY = -11 * _2X;
		break;
	}

	if ((int)GetNumDx(num, sign, font, digit, comma, zoom, fixed) <= (int)width || width == false) {
		DrawNum(num, x, y, font, align, digit, sign, comma, zoom, fixed);
		return;
	}

	do {
		gapNum /= 10;
		gap++;//줄여야 되는 자리수
		gapWidth = GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed);
	} while (gapWidth > width);

	//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.

	if (gap % 3) {
		do {
			gap++;
			if (gapNum >= 10)
				gapNum /= 10;
			gapWidth = GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed);
		} while (gap % 3);
	}

	figureNum -= gap;

	alphaIdx = alphaArray[(gap - 3) / 3];
	gapWidth += GetAlphaWidth(alphaIdx, font, zoom);

	if (figureNum == 0) {
		num2 = gapNum;
		gapNum = 0;

		gapWidth = GetNumDx(num2, sign, font, digit, comma, zoom, fixed) + dotWidth + GetNumDx(gapNum, false, font, digit, false, zoom, fixed) + GetAlphaWidth(alphaIdx, font, zoom);
	}
	else if (figureNum == 1) {

		temp = num - gapNum * pow(10, GetNumFigure(num) - 1);//소수위 자리수들을 제거한 나머지 숫자를 구한다.
		num2 = temp / pow(10, GetNumFigure(num) - 2);

		gapWidth += dotWidth + GetNumDx(num2, sign, font, digit, comma, zoom, fixed);
	}
	else
		num2 = 0;

	switch (align) {
	case LEFT:
		DrawNum(gapNum, x, y, font, LEFT, digit, sign, comma, zoom, fixed);
		if (figureNum <= 1) {
			DrawAlpha(x + GetNumDx(gapNum, sign, font, 0, comma, zoom, fixed), y + alphaGapY, ALPHA_DOT, alphaFont, zoom, false);
			DrawNum(num2, x + GetNumDx(gapNum, sign, font, 0, comma, zoom, fixed) + dotWidth, y, font, LEFT, digit, false, comma, zoom, fixed);
			DrawAlpha(x + GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed) + dotWidth + GetNumDx(num2, false, font, 0, comma, zoom, fixed), y + alphaGapY, alphaIdx, alphaFont, zoom, false);
		}
		else
			DrawAlpha(x + GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed), y + alphaGapY, alphaIdx, alphaFont, zoom, false);
		break;
	case CENTER:
		DrawNum(gapNum, x - gapWidth / 2, y, font, LEFT, digit, sign, comma, zoom, fixed);
		if (figureNum <= 1) {
			DrawAlpha(x - gapWidth / 2 + GetNumDx(gapNum, sign, font, 0, comma, zoom, fixed), y + alphaGapY, ALPHA_DOT, alphaFont, zoom, false);
			DrawNum(num2, x - gapWidth / 2 + GetNumDx(gapNum, sign, font, 0, comma, zoom, fixed) + dotWidth, y, font, LEFT, digit, false, comma, zoom, fixed);
			DrawAlpha(x - gapWidth / 2 + GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed) + dotWidth + GetNumDx(num2, false, font, 0, comma, zoom, fixed), y + alphaGapY, alphaIdx, alphaFont, zoom, false);
		}
		else
			DrawAlpha(x - gapWidth / 2 + GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed), y + alphaGapY, alphaIdx, alphaFont, zoom, false);
		break;
	case RIGHT:
		DrawNum(gapNum, x - gapWidth, y, font, LEFT, digit, sign, comma, zoom, fixed);
		if (figureNum <= 1) {
			DrawAlpha(x - gapWidth + GetNumDx(gapNum, sign, font, 0, comma, zoom, fixed), y + alphaGapY, ALPHA_DOT, alphaFont, zoom, false);
			DrawNum(num2, x - gapWidth + GetNumDx(gapNum, sign, font, 0, comma, zoom, fixed) + dotWidth, y, font, LEFT, digit, false, comma, zoom, fixed);
			DrawAlpha(x - gapWidth + GetNumDx(gapNum, sign, font, digit, comma, zoom, fixed) + dotWidth + GetNumDx(num2, false, font, 0, comma, zoom, fixed), y + alphaGapY, alphaIdx, alphaFont, zoom, false);
		}
		else
			DrawAlpha(x - gapWidth + GetNumDx(gapNum, sign, font, 0, comma, zoom, fixed), y + alphaGapY, alphaIdx, alphaFont, zoom, false);
		break;
	}
}

void DrawNum2AutoSpaceing(long long int num, int x, int y, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed, bool bold)
{
	float originZoom = zoom;
	if ((int)GetNumDx2(num, sign, digit, comma, zoom, fixed) > (int)width) {
		do {
			zoom -= originZoom * 0.1f;
		} while ((int)GetNumDx2(num, sign, digit, comma, zoom, fixed) > (int)width);
	}

	if (bold == true)
		DrawBigNum2Bold(num, x, y - (float)80 * (originZoom - zoom) / 2, align, digit, sign, width, comma, zoom, fixed);
	else
		DrawBigNum2(num, x, y - (float)80 * (originZoom - zoom) / 2, align, digit, sign, width, comma, zoom, fixed);


}

void DrawBigNum2Bold(long long int num, int x, int y, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed)
{
	int i;

	SetColor(COLOR_BROWN);
	for (i = 0; i < 4; i++) {
		DrawBigNum2(num, x + (float)solidPosition[2 * i + 0] * 2 * _2X * zoom, y + (float)solidPosition[2 * i + 1] * 2 * _2X * zoom, align, digit, sign, width, comma, zoom, fixed);
	}

	SetColor(COLOR_WHITE);
	DrawBigNum2(num, x, y, align, digit, sign, width, comma, zoom, fixed);
	SetColor(false);
}

void DrawBigNum2(long long int num, int x, int y, int align, int digit, int sign, float width, bool comma, float zoom, bool fixed)
{
	int alphaArray[] = { ALPHA_NUM_K, ALPHA_NUM_M, ALPHA_NUM_B, ALPHA_NUM_T, ALPHA_NUM_Q, ALPHA_NUM_Z, ALPHA_NUM_Y };
	int num1;//소수점 위 숫자(최대 3자리)
	int dot;//소수점 도트의 유무
	int num2;//소수점 아래 숫자(최대 2자리)
	int alpha;//알파자리수
	float num1Width;//num1의 숫자
	float dotWidth = (float)(22) * zoom;//소수점 도트의 넓이
	float num2Width;//num2의 숫자
	//int alphaIdx = ALPHA_NUM_A + ((GetNumFigure(num) - 1) / 3) - 1;
	int alphaIdx = GetNumFigure(num) < 6 ? 0 : alphaArray[Min(2, (GetNumFigure(num) - 2) / 3 - 1)];

	float alphaGapY;
	float dotGapY;
	int figureNum = GetNumFigure(num);

	float totalWidth;
	long long int temp;

	int gap = 0;//줄여야 되는 자리수
	float gapWidth;
	long long gapNum = num;

	if (width == 0)
		return;

	alphaGapY = (float)(0 * _2X) * zoom;
	dotGapY = (float)(-60 * _2X) * zoom;

	if ((int)GetNumDx2(num, sign, digit, comma, zoom, fixed) <= (int)width || width == false) {
		DrawNum2(num, x, y, align, digit, sign, comma, zoom, fixed);
		return;
	}

	do {
		gapNum /= 10;
		gap++;//줄여야 되는 자리수
		gapWidth = GetNumDx2(gapNum, sign, digit, comma, zoom, fixed);
	} while (gapWidth > width);

	//3������ �ڸ��� ���� ���?���ڸ��� �ٿ��� �Ǵ� �� �����Ѵ�.

	if (gap % 3) {
		do {
			gap++;
			if (gapNum >= 10)
				gapNum /= 10;
			gapWidth = GetNumDx2(gapNum, sign, digit, comma, zoom, fixed);
		} while (gap % 3);
	}

	figureNum -= gap;

	alphaIdx = alphaArray[(gap - 3) / 3];
	gapWidth += GetAlphaWidth2(alphaIdx, zoom);

	if (figureNum == 0) {
		num2 = gapNum;
		gapNum = 0;

		gapWidth = GetNumDx2(num2, sign, digit, comma, zoom, fixed) + dotWidth + GetNumDx2(gapNum, false, digit, false, zoom, fixed) + GetAlphaWidth2(alphaIdx, zoom);
	}
	else if (figureNum == 1) {

		temp = num - gapNum * pow(10, GetNumFigure(num) - 1);//소수위 자리수들을 제거한 나머지 숫자를 구한다.
		num2 = temp / pow(10, GetNumFigure(num) - 2);

		gapWidth += dotWidth + GetNumDx2(num2, sign, digit, comma, zoom, fixed);
	}
	else
		num2 = 0;

	switch (align) {
	case LEFT:
		DrawNum2(gapNum, x, y, LEFT, digit, sign, comma, zoom, fixed);
		if (figureNum <= 1) {
			DrawAlpha2(x + GetNumDx2(gapNum, sign, 0, comma, zoom, fixed) + (float)3 * _2X * zoom, y, ALPHA_DOT, zoom, false);
			DrawNum2(num2, x + GetNumDx2(gapNum, sign, 0, comma, zoom, fixed) + (float)3 * _2X * zoom + dotWidth, y, LEFT, digit, false, comma, zoom, fixed);
			DrawAlpha2(x + GetNumDx2(gapNum, sign, digit, comma, zoom, fixed) + (float)3 * _2X * zoom + dotWidth + GetNumDx2(num2, false, 0, comma, zoom, fixed), y + alphaGapY, alphaIdx, zoom, false);
		}
		else
			DrawAlpha2(x + GetNumDx2(gapNum, sign, digit, comma, zoom, fixed), y + alphaGapY, alphaIdx, zoom, false);
		break;
	case CENTER:
		DrawNum2(gapNum, x - gapWidth / 2, y, LEFT, digit, sign, comma, zoom, fixed);
		if (figureNum <= 1) {
			DrawAlpha2(x - gapWidth / 2 + GetNumDx2(gapNum, sign, 0, comma, zoom, fixed) + (float)3 * _2X * zoom, y, ALPHA_DOT, zoom, false);
			DrawNum2(num2, x - gapWidth / 2 + GetNumDx2(gapNum, sign, 0, comma, zoom, fixed) + (float)3 * _2X * zoom + dotWidth, y, LEFT, digit, false, comma, zoom, fixed);
			DrawAlpha2(x - gapWidth / 2 + GetNumDx2(gapNum, sign, digit, comma, zoom, fixed) + (float)3 * _2X * zoom + dotWidth + GetNumDx2(num2, false, 0, comma, zoom, fixed), y + alphaGapY, alphaIdx, zoom, false);
		}
		else
			DrawAlpha2(x - gapWidth / 2 + GetNumDx2(gapNum, sign, digit, comma, zoom, fixed), y + alphaGapY, alphaIdx, zoom, false);
		break;
	case RIGHT:
		DrawNum2(gapNum, x - gapWidth, y, LEFT, digit, sign, comma, zoom, fixed);
		if (figureNum <= 1) {
			DrawAlpha2(x - gapWidth + GetNumDx2(gapNum, sign, 0, comma, zoom, fixed) + (float)3 * _2X * zoom, y, ALPHA_DOT, zoom, false);
			DrawNum2(num2, x - gapWidth + GetNumDx2(gapNum, sign, 0, comma, zoom, fixed) + (float)3 * _2X * zoom + dotWidth, y, LEFT, digit, false, comma, zoom, fixed);
			DrawAlpha2(x - gapWidth + GetNumDx2(gapNum, sign, digit, comma, zoom, fixed) + (float)3 * _2X * zoom + dotWidth + GetNumDx2(num2, false, 0, comma, zoom, fixed), y + alphaGapY, alphaIdx, zoom, false);
		}
		else
			DrawAlpha2(x - gapWidth + GetNumDx2(gapNum, sign, 0, comma, zoom, fixed), y + alphaGapY, alphaIdx, zoom, false);
		break;
	}
}

void DrawScroll(int x, int y, int h, int type)
{
	MemRect(x, y, 4 * _2X, h, 0x999999);

	if (scT[type] <= 1)
		return;

	int barH = h / scT[type];

	if (barH < 16 * _2X)
		barH = 16 * _2X;

	if (barH > h)
		barH = h;

	int moveRange = h - barH;

	int barY = y - moveRange * scY[type] / (scT[type] - 1);

	MemRect(x, barY, 4 * _2X, barH, 0xFF9900);
}

void DrawStarNum(int icon, int star, int x, int y, float zoom)
{
	DrawIcon(icon, x, y, zoom, COLOR_BROWN, false, false, true);
	//memset(&tempStr, 0, sizeof(tempStr));
	//sprintf(tempStr, "%d", star);
	//CenterTextStr(tempStr, x + (float)(ITEMICONSIZE / 2) * zoom, y - (float)5 * _2X * zoom, 0.65f * zoom, cvtDest, cvtLayer, buffering);
	//DrawNumTTF(star, x + (float)(ITEMICONSIZE / 2) * zoom, y - (float)0.8f * 5 * _2X * zoom, NUM_FONT_LARGE, CENTER, false, false, true, 0.8f * zoom, false, cvtDest, cvtLayer, buffering);
	DrawNum2AutoSpaceing(star, x + (float)(ITEMICONSIZE / 2) * zoom, y - (float)16 * _2X * NUM2ZOOM * zoom, CENTER, false, false, (float)ITEMICONSIZE * zoom, false, 1.0f * zoom * NUM2ZOOM, false, true);
}

//size�� ����, �̵��? ����
//cnt�� ������ ������ �׸��°� ���� 0�̸� �׸��� �ϵ� ���� �κ��� ����.
//max�� cnt�� ������ �� ���?�׸��°Ű� max�� ũ�� �������� �����Ѵ�.

void DrawStar(int icon, int x, int y, int cnt, int curMax, int max, int align, bool bigStar, float zoom)
{
	int i;
	float width;
	int drawCnt = max;
	int baseColorBack = baseColor;
	int STARGAP = 12 * _2X;

	if (drawCnt <= 5 || bigStar == false) {
		width = (float)(STARGAP * (drawCnt - 1) + ITEMICONSIZE) * zoom;
		y += (float)(4 * _2X) * zoom;
	}
	//��պ�?
	else {
		zoom = zoom * 1.8f;
		width = (float)(16 * _2X * 1) * zoom;
		y += (float)(4 * _2X) * zoom;
	}

	switch (align) {
	case LEFT:
		break;
	case RIGHT:
		x -= width;
		break;
	case CENTER:
		x -= width / 2;
		break;
	}

	if (drawCnt <= 5 || bigStar == false) {
		for (i = 0; i < drawCnt; i++) {

			if (i >= curMax) {
				SetColor(COLOR_BLACK);
				DrawIcon(icon, x + (float)(i * STARGAP) * zoom, y, 1.1f * zoom, false, false, false, true);
				SetColor(false);
				grayScale = 32;
				DrawIcon(icon, x + (float)(i * STARGAP + 2) * zoom, y - (float)(1) * zoom, zoom * 1.0f, false, false, false, true);
				grayScale = false;

				//SetColor(COLOR_BLACK);
				//DrawIcon(ICON_STAR, x + (float)(i * STARGAP) * zoom, y, zoom, false, false, false, cvtDest, cvtLayer, buffering);
				//SetColor(false);

			}
			else if (i >= cnt) {
				SetColor(COLOR_BLACK);
				DrawIcon(icon, x + (float)(i * STARGAP) * zoom, y, 1.1f * zoom, false, false, false, true);

				SetColor(false);
				DrawIcon(icon, x + (float)(i * STARGAP + 2) * zoom, y - (float)(1) * zoom, zoom * 1.0f, false, false, false, true);
				SetColor(false);
			}
			//else
			//	DrawIcon(icon, x + (float)(i * STARGAP) * zoom, y, zoom, COLOR_BROWN, false, false, cvtDest, cvtLayer, buffering);

		}

		for (i = 0; i < drawCnt; i++) {

			if (i >= curMax) {
				/*
				SetColor(COLOR_BLACK);
				DrawIcon(icon, x + (float)(i * STARGAP) * zoom, y, 1.1f * zoom, false, false, false);
				SetColor(false);
				grayScale = 32;
				DrawIcon(icon, x + (float)(i * STARGAP + 2) * zoom, y - (float)(1) * zoom, zoom * 1.0f, false, false, false);
				grayScale = false;

				//SetColor(COLOR_BLACK);
				//DrawIcon(ICON_STAR, x + (float)(i * STARGAP) * zoom, y, zoom, false, false, false, cvtDest, cvtLayer, buffering);
				//SetColor(false);
				*/
			}
			else if (i >= cnt) {
				/*
				SetColor(COLOR_BLACK);
				DrawIcon(icon, x + (float)(i * STARGAP) * zoom, y, 1.1f * zoom, false, false, false);

				SetColor(COLOR_RED);
				DrawIcon(icon, x + (float)(i * STARGAP + 2) * zoom, y - (float)(1) * zoom, zoom * 1.0f, false, false, false);
				SetColor(false);
				*/
			}
			else {
				//SetColor(itemColor[cnt]);
				DrawIcon(icon, x + (float)(i * STARGAP - 1 * _2X) * zoom, y + (float)1 * _2X * zoom, 1.1f * zoom, COLOR_BROWN, false, false, true);
				//SetColor(false);
			}
		}
	}
	else {
		DrawStarNum(icon, drawCnt, x, y, zoom);
	}

	SetColor(baseColorBack);
}


void DrawShield(int x, int y, int cnt, int max, int align, float zoom)
{
	int i;
	float width;
	float shieldZoom = 1.5f;
	float gapX = Min(14 * _2X, (float)(SHIELDBARWIDTH - ITEMICONSIZE * shieldZoom) / (max - 1));
	int drawCnt = max;
	int baseColorBack = baseColor;

	width = (float)((gapX * (drawCnt - 1) + (float)ITEMICONSIZE * shieldZoom) * shieldZoom);
	y -= (float)(2 * _2X) * zoom;

	switch (align) {
	case LEFT:
		break;
	case RIGHT:
		x -= width;
		break;
	case CENTER:
		x -= width / 2;
		break;
	}

	for (i = drawCnt - 1; i >= 0; i--) {
		if (i >= cnt)
			SetColor(COLOR_STARGREY);
		//아이콘으로 그리는거
		DrawIcon(ICON_SHIELD, x + (float)(i * gapX) * shieldZoom, y, shieldZoom, COLOR_WHITE, false, false, true);
		SetColor(false);
	}

	SetColor(baseColorBack);
}

void DrawHeart(int x, int y, int cnt, int max, int align, float zoom)
{
	int i;
	float width;
	int drawCnt = max;
	int baseColorBack = baseColor;

	width = (float)(14 * _2X * drawCnt) * zoom;
	y += (float)(4 * _2X) * zoom;

	switch (align) {
	case LEFT:
		break;
	case RIGHT:
		x -= width;
		break;
	case CENTER:
		x -= width / 2;
		break;
	}

	for (i = 0; i < drawCnt; i++) {
		if (i >= cnt)
			SetColor(COLOR_STARGREY);
		//아이콘으로 그리는거
		DrawIcon(ICON_HEART, x + (float)(i * 14 * _2X) * zoom, y, zoom, COLOR_BROWN, false, false, true);
		SetColor(false);
	}

	SetColor(baseColorBack);
}

void DrawRaidButton(float zoom, bool ani)
{
	//하트버튼
	int x = xOffset + DX / 2 - 36 * _2X * zoom;
	int y = STATUSWIN_Y + HEARTBUTTONGAP;
	float width = (float)(12 * _2X) * zoom + GetNumDx(raidChance, false, NUM_FONT_NORMAL, false, true, zoom, false) + (float)(ITEMICONSIZE + 4 * _2X) * zoom;

	if (width == 0)
		return;

	if (ani == true)
		MemRect(x - (float)(4 * _2X) * zoom, y - (float)(2 * _2X) * zoom, (float)(72 * _2X + 8 * _2X) * zoom, 18 * _2X, itemColor[frame % 6]);
	DrawAlpha(x + (float)(72 * _2X) * zoom / 2 - width / 2, y - (float)(5 * _2X) * zoom, ALPHA_X, FONT_LARGE, zoom, false);
	DrawNum(raidChance, x + (float)(72 * _2X) * zoom / 2 - width / 2 + (float)(12 * _2X) * zoom, y - (float)(4 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, 1, false, false, zoom, false);

	DrawIcon(ICON_RAID, x + (float)(72 * _2X) * zoom / 2 - width / 2 + (float)(12 * _2X) * zoom + GetNumDx(raidChance, false, NUM_FONT_NORMAL, false, true, zoom, false) + (float)(4 * _2X) * zoom, y - (float)(3 * _2X) * zoom + (float)(6 * _2X) * zoom, zoom, false, false, false, true);

}

void DrawGoldButton(int itemType, int itemDetail, int itemGrade, int itemLv, int x, int y, float zoom, bool ani)
{
	//하트버튼
	float width = (float)(ITEMICONSIZE + 10 * _2X + 1 * _2X) * zoom + GetNumDx(GetBetGold(itemDetail, itemGrade), false, NUM_FONT_NORMAL, false, true, zoom, false) + (float)(ITEMICONSIZE + 1 * _2X) * zoom;

	if (width == 0)
		return;

	if (ani == true)
		MemRect(x - (float)(4 * _2X) * zoom, y - (float)(2 * _2X) * zoom, (float)(72 * _2X + 8 * _2X) * zoom, (float)(18 * _2X) * zoom, itemColor[frame % 6]);

	DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + (float)(72 * _2X) * zoom / 2 - width / 2, y - (float)(3 * _2X) * zoom, zoom, false, false, false, true);
	DrawAlpha(x + (float)(72 * _2X) * zoom / 2 - width / 2 + (float)(ITEMICONSIZE + 1 * _2X) * zoom, y - (float)(5 * _2X) * zoom, ALPHA_X, FONT_LARGE, zoom, false);
	DrawNum(GetBetGold(itemDetail, itemGrade), x + (float)(72 * _2X) * zoom / 2 - width / 2 + (float)(ITEMICONSIZE + 1 * _2X + 10 * _2X) * zoom, y - (float)(4 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, false, false, true, zoom, false);

	DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)72 * _2X * zoom / 2 - width / 2 + (float)(ITEMICONSIZE + 1 * _2X + 10 * _2X) * zoom + GetNumDx(GetBetGold(itemDetail, itemGrade), false, NUM_FONT_NORMAL, false, true, zoom, false) + (float)(1 * _2X) * zoom, y - (float)(3 * _2X) * zoom, zoom, false, false, false, true);

}

void DrawCoinButton(int cnt, int x, int y, float zoom, bool ani, bool betFrame)
{
	float GOLDALPHAZOOM = 0.5f;
	//하트버튼
	//float width = (float)(ITEMICONSIZE + 10 * _2X + 1 * _2X) * zoom + GetNumDx(GetBetHeart(itemDetail, itemGrade, bet), false, NUM_FONT_NORMAL, false, true, zoom, false) + (float)(ITEMICONSIZE + 1 * _2X) * zoom;
	//float width = (float)(ITEMICONSIZE + 2 * _2X + 8 * _2X) * 1.1f * zoom + GetGoldNumDx(cnt, PLUS, false, false, zoom * 0.65f);
	float width = (float)(ITEMICONSIZE + 2 * _2X) * zoom + GetGoldNumDx(cnt, PLUS, false, false, zoom * GOLDALPHAZOOM);

	if (width == 0)
		return;

	//if (ani == true)
	//	MemRect(x - (float)(4 * _2X) * zoom, y - (float)(2 * _2X) * zoom, (float)(72 * _2X + 8 * _2X) * zoom, (float)(18 * _2X) * zoom, itemColor[frame % 6], cvtDest, cvtLayer, buffering);

	//DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + (float)(72 * _2X) * zoom / 2 - width / 2, y - (float)(3 * _2X) * zoom, zoom, false, false, false, cvtDest, cvtLayer, buffering);
	//DrawXMark(x, y, zoom, cvtDest, cvtLayer, buffering);
	DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(COINBUTTONWIDTH - width) / 2 * zoom, y + (float)(-2 * _2X) * zoom, zoom, false, false, false, true);
	DrawXNumGold(cnt, x + (float)(COINBUTTONWIDTH - width) / 2 + (float)(ITEMICONSIZE + 2 * _2X) * zoom, y - (float)(4 * _2X) * zoom, false, GOLDALPHAZOOM * zoom, LEFT, false);

	//Bet�϶��?����
	if (betFrame)
		if (robin.gold > betCoin[betBattle] * GetStageAdmissionFee()) {
			//�ִ� bet�̸� �ִ밪�ΰ� ǥ�����ְ�
			if (IsMaxCoinBet() == true) {
				//DrawFrame(x - (float)8 * _2X * zoom, y + (float)16 * _2X * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), (float)32 * _2X * zoom, (float)18 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
				//DrawText(TEXT_ALPHA_MAX, x - (float)(8 * _2X - 4 * _2X) * zoom, y + (float)(16 * _2X - 4 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), zoom, cvtDest, cvtLayer, buffering);
				DrawFrame(xOffset + x - (float)40 * _2X * zoom, y + (float)4 * _2X * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), (float)44 * _2X * zoom, (float)20 * _2X * zoom, FRAME_SHOPBALLOON);
				DrawGoldAlpha(xOffset + x - (float)(40 * _2X - 4 * _2X) * zoom, y + (float)(4 * _2X - 4 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), ALPHA_MAX, FONT_GOLD_LARGE, 0.5f * zoom, LEFT, false, false);
			}
			else {
				//DrawFrame(x - (float)8 * _2X * zoom, y + (float)16 * _2X * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), (float)28 * _2X * zoom, (float)18 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
				//DrawText(TEXT_ALPHA_BET, x - (float)(8 * _2X - 4 * _2X) * zoom, y + (float)(16 * _2X - 4 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), zoom, cvtDest, cvtLayer, buffering);
				DrawFrame(xOffset + x - (float)40 * _2X * zoom, y + (float)4 * _2X * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), (float)36 * _2X * zoom, (float)20 * _2X * zoom, FRAME_SHOPBALLOON);
				DrawGoldAlpha(xOffset + x - (float)(40 * _2X - 4 * _2X) * zoom, y + (float)(4 * _2X - 4 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), ALPHA_BET, FONT_GOLD_LARGE, 0.5f * zoom, LEFT, false, false);
			}
		}

}

void DrawHeartButton(int cnt, int x, int y, float zoom, bool ani, bool betFrame)
{
	float GOLDALPHAZOOM = 0.4f;
	int MAXPUSHDOWN = AUTOPLAYFRAME;
	int i;

	//하트버튼
	float width = (float)(ITEMICONSIZE + 2 * _2X) * zoom + GetGoldNumDx(cnt, PLUS, false, false, zoom * GOLDALPHAZOOM);

	if (width == 0)
		return;

	DrawIcon(ICON_HEART, xOffset + x + (float)6 * _2X * zoom, y, 1.8f * zoom, (ani == true ? itemColor[robin.playtime % 10] : COLOR_WHITE), false, false, 1.0f * zoom);
	DrawGoldNum(cnt, xOffset + x + (float)(6 * _2X + ITEMICONSIZE * 1.6f / 2) * zoom, y - (float)5 * _2X * zoom, CENTER, false, false, false, 0.8f * zoom);
	//DrawXNumTTF(cnt, xOffset + x + (float)(8 * _2X + ITEMICONSIZE * 1.6f / 2) * zoom, y - (float)6 * _2X * zoom, 1.0f * zoom, CENTER, cvtDest, cvtLayer, buffering);

	//��ų�� ������ �׷��ִ°�
	//Test Setting

	//Bet�϶��?����
	//등급과 robin.bet을 비교해서 해당 공격이 등장할지 확인한다.
	//���� ���?��ų������ 0�̸� �ٷ� �����?�� �ְ�,
	//��ų������ 1�̸� ��Ʈ�� 3�̻� �����ؾ� �����?�� �ִ�.
	//��ų�����?����
	//�׷��� ���� ���� �ִ� ��ų�׷��̵�(GRADE_NORMAL,....) �̰� ������ �Ѵ�.
	//그리고 뜬금포지만 골드를 어떻게 내려줄거냐.
	//���?ü�¿� �����ϸ� �ָ��ؼ� �⺻������ �˿� � �� ȹ���ϴ� ���?�ھ��ְ�, ���ݷ°� ���ȹ��?���?�����ؾ� �ɵ�
	//�׷��� 1Ÿ�� 

	if (betFrame)
		if (robin.heart > 1 && ani == true) {
			zoom = zoom * 0.8f;
			//�ִ� bet�̸� �ִ밪�ΰ� ǥ�����ְ�
			if (IsMaxBet() == true) {
				//DrawFrame(x - (float)8 * _2X * zoom, y + (float)16 * _2X * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), (float)32 * _2X * zoom, (float)18 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
				//DrawText(TEXT_ALPHA_MAX, x - (float)(8 * _2X - 4 * _2X) * zoom, y + (float)(16 * _2X - 4 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), zoom, cvtDest, cvtLayer, buffering);
				DrawFrame(xOffset + x, y + (float)20 * _2X * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), (float)60 * _2X * zoom, (float)20 * _2X * zoom, FRAME_SHOPBALLOON);
				DrawIcon(ICON_HEART, xOffset + x - (float)(- 2 * _2X) * zoom, y + (float)(20 * _2X - 2 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), 1.0f * zoom, false, false, false, true);
				DrawGoldAlpha(xOffset + x + (float)( + 4 * _2X + ITEMICONSIZE) * zoom, y + (float)(20 * _2X - 4 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), ALPHA_MAX, FONT_GOLD_LARGE, 0.5f * zoom, LEFT, false, false);
			}
			else {
				//DrawFrame(x - (float)8 * _2X * zoom, y + (float)16 * _2X * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), (float)28 * _2X * zoom, (float)18 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
				//DrawText(TEXT_ALPHA_BET, x - (float)(8 * _2X - 4 * _2X) * zoom, y + (float)(16 * _2X - 4 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), zoom, cvtDest, cvtLayer, buffering);
				DrawFrame(xOffset + x, y + (float)20 * _2X * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), (float)42 * _2X * zoom, (float)20 * _2X * zoom, FRAME_SHOPBALLOON);
				DrawIcon(ICON_HEART, xOffset + x + (float)(2 * _2X) * zoom, y + (float)(20 * _2X - 2 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), 1.0f * zoom, false, false, false, true);
				DrawGoldAlpha(xOffset + x + (float)(4 * _2X + ITEMICONSIZE) * zoom, y + (float)(20 * _2X - 4 * _2X) * zoom + 8 - Abs(frame / MOTIONDIV % 8 - 4), ALPHA_UP, FONT_GOLD_LARGE, 0.5f * zoom, LEFT, false, false);
			}

			DrawHand(x - (float)4 * _2X * zoom, y + (float)4 * _2X * zoom, robin.playtime / MOTIONDIV, 1.5f * zoom);
		}

}

void DrawBattleButton(int x, int y, float zoom, bool ani)
{
	float heartZoom = 0.5f * zoom;
	int heartX, heartY;

	DrawIcon(ICON_EVENT_2SWORD, x, y, zoom, COLOR_BROWN/*(ani == true ? itemColor[robin.playtime % 10] : COLOR_BROWN)*/, false, false, 1.0f);
	CenterText(TEXT_ADVENTURE, x + (float)(ITEMICONSIZE / 2) * zoom, y - (float)(ITEMICONSIZE - 2 * _2X) * zoom, 0.5f * zoom);
	//입장료
	//
	if (frame % FPS < 15)
		heartZoom += (float)(frame % FPS) * 0.02f;
	
	heartX = x + (float)14 * _2X * zoom + (float)8 * _2X * zoom;
	heartY = y - (float)6 * _2X * zoom - (float)8 * _2X * zoom;
	DrawIcon(ICON_HEART, heartX - (float)(heartZoom) * 16 * _2X / 2, heartY + (float)(heartZoom) * 16 * _2X / 2, heartZoom, COLOR_WHITE, false, false, 1 * _2X);
	DrawNumTTF(-GetStageAdmissionHeart(nearestIndex), heartX, heartY + (float)3 * _2X * zoom, FONT_LARGE, CENTER, 2, false, false, 0.35f * zoom, false);

	if (ani == true) {
		DrawHand(x - (float)4 * _2X * zoom, y + (float)4 * _2X * zoom, robin.playtime / MOTIONDIV, 0.8f * zoom);
	}
}


void JoyStickDraw(int cnt, int x, int y, float joyDx, float joyDy, float joyPower, float zoom, bool ani, bool betFrame, int downFrame)
{
	int baseW = 108;
	int baseH = 93;

	int knobW = 65;
	int knobH = 66;

	int ringW = 82;
	int ringH = 48;

	float knobX = x + joyDx;
	float knobY = y + joyDy + (float)16 * zoom;

	// 1. 노란 베이스
	DrawImageScale(
		baseW, baseH,
		0, 140,
		x - baseW * zoom / 2,
		y + baseH * zoom / 2,
		false, false, false, false, false,
		zoom, zoom,
		sprite[PLAYBUTTON_IMG],
		PLAYBUTTON_IMG);

	// 2. 회색 가이드 링
	DrawImageScale(
		ringW, ringH,
		109, 208,
		x - ringW * zoom / 2,
		y + ringH * zoom / 2,
		false, false, false, false, false,
		zoom, zoom,
		sprite[PLAYBUTTON_IMG],
		PLAYBUTTON_IMG);
	// 4. 노란 손잡이
	DrawImageScale(
		knobW, knobH,
		109, 141,
		knobX - knobW * zoom / 2,
		knobY + knobH * zoom / 2,
		false, false, false, false, false,
		zoom, zoom,
		sprite[PLAYBUTTON_IMG],
		PLAYBUTTON_IMG);
}

void DrawJumpButton(int cnt, int x, int y, float zoom, bool ani, bool betFrame, int downFrame)
{
	float GOLDALPHAZOOM = 0.4f;
	int MAXPUSHDOWN = 12;
	int i;

	//하트버튼
	float width = (float)(ITEMICONSIZE + 2 * _2X) * zoom + GetGoldNumDx(cnt, PLUS, false, false, zoom * GOLDALPHAZOOM);

	if (ani == true) {
		SetColor(itemColor[frame % 10]);

		for (i = 0; i < 4; i++) {
			DrawImage(192 / 2, 69, 0, 70, x + (float)solidPosition[2 * i + 0] * zoom, y + (float)solidPosition[2 * i + 1] * zoom - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, false, false, false, false, false, 0.8f * zoom, sprite[PLAYBUTTON_IMG], PLAYBUTTON_IMG);
			DrawImage(192 / 2, 69, 192 / 2, 70, x + (float)solidPosition[2 * i + 0] * zoom, y + (float)solidPosition[2 * i + 1] * zoom, false, false, false, false, false, 0.8f * zoom, sprite[PLAYBUTTON_IMG], PLAYBUTTON_IMG);

		}

		SetColor(false);
	}
	DrawImage(192 / 2, 69, 0, 70, x, y - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, false, false, false, false, false, 0.8f * zoom, sprite[PLAYBUTTON_IMG], PLAYBUTTON_IMG);
	DrawImage(192 / 2, 69, 192 / 2, 70, x, y, false, false, false, false, false, 0.8f * zoom, sprite[PLAYBUTTON_IMG], PLAYBUTTON_IMG);

	ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + (float)(192 / 2 * 0.8f - 24 * _2X) / 2 * zoom, y - (float)2.0f * zoom - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, SHADOW_IMG, zoom);
	
	if (ao[PLAYER].equip[EQUIP_BOOTS].type)
		DrawIcon(GetItemIcon(ao[PLAYER].equip[EQUIP_BOOTS].type, ao[PLAYER].equip[EQUIP_BOOTS].detail, ao[PLAYER].equip[EQUIP_BOOTS].grade), x + (float)(192 / 2 * 0.8f - ITEMICONSIZE * 0.8f) / 2 * zoom, y - (float)2.0f * zoom - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, 0.8f * zoom, COLOR_BROWN, false, false, 2.0f * zoom);
	else
		DrawIcon(GetItemIcon(ITEM_BOOTS, 0, GRADE_NORMAL), x + (float)(192 / 2 * 0.8f - ITEMICONSIZE * 0.8f) / 2 * zoom, y - (float)2.0f * zoom - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, 0.8f * zoom, COLOR_BROWN, false, false, 2.0f * zoom);

	if (ani == true) {
		DrawHand(x - (float)4 * _2X * zoom, y + (float)4 * _2X * zoom, robin.playtime / MOTIONDIV, 1.2f * zoom);
	}

}

void DrawAttackButton(int cnt, int x, int y, float zoom, bool ani, bool betFrame, int downFrame)
{
	float GOLDALPHAZOOM = 0.4f;
	int MAXPUSHDOWN = 12;
	int i;

	//하트버튼
	float width = (float)(ITEMICONSIZE + 2 * _2X) * zoom + GetGoldNumDx(cnt, PLUS, false, false, zoom * GOLDALPHAZOOM);

	if (ani == true) {
		SetColor(itemColor[frame % 10]);

		for (i = 0; i < 4; i++) {
			DrawImage(192 / 2, 69, 0, 0, x + (float)solidPosition[2 * i + 0] * zoom, y + (float)solidPosition[2 * i + 1] * zoom - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, false, false, false, false, false, 0.8f * zoom, sprite[PLAYBUTTON_IMG], PLAYBUTTON_IMG);
			DrawImage(192 / 2, 69, 192 / 2, 0, x + (float)solidPosition[2 * i + 0] * zoom, y + (float)solidPosition[2 * i + 1] * zoom, false, false, false, false, false, 0.8f * zoom, sprite[PLAYBUTTON_IMG], PLAYBUTTON_IMG);

		}

		SetColor(false);
	}
	DrawImage(192 / 2, 69, 0, 0, x, y - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, false, false, false, false, false, 0.8f * zoom, sprite[PLAYBUTTON_IMG], PLAYBUTTON_IMG);
	DrawImage(192 / 2, 69, 192 / 2, 0, x, y, false, false, false, false, false, 0.8f * zoom, sprite[PLAYBUTTON_IMG], PLAYBUTTON_IMG);

	ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + (float)(192 / 2 * 0.8f - 24 * _2X) / 2 * zoom, y - (float)2.0f * zoom - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, SHADOW_IMG, zoom);
	DrawIcon(GetItemIcon(ao[PLAYER].equip[EQUIP_WEAPON].type, ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade), x + (float)(192 / 2 * 0.8f - ITEMICONSIZE * 0.8f) / 2 * zoom, y - (float)2.0f * zoom - (float)Min(MAXPUSHDOWN, downFrame) * zoom * 0.8f, 0.8f * zoom, COLOR_BROWN, false, false, 2.0f * zoom);


	if (ani == true) {
		DrawHand(x - (float)4 * _2X * zoom, y + (float)4 * _2X * zoom, robin.playtime / MOTIONDIV, 1.2f * zoom);
	}

}

//현재 최대 맥스 
int GetMaxShield(void)
{
	return MAXSHIELD;
	//return Min(MAXSHIELD, MINSHIELD + (robin.stage * TOTALROOM + robin.room) / 10);
}

int GetInitHeart(void)
{
	return 50 + ((robin.lv + 1) / 10) * 10;
}

int GetHeartAmount(void)
{
	return 10 + ((robin.lv + 1) / 10);
	//return 1;
}

void LoadingBarDraw(int x, int y, int loadingBarFrame)
{
	int text;
	DrawImage(165, 21, 180, 519, x, y, false, false, false, false, false, 2.0f, sprite[THEATER_IMG], THEATER_IMG);
	MemRect(x + 3 * _2X, y - 3 * _2X, Min(159 * _2X, loadingBarFrame * 5 * _2X), 16 * _2X, COLOR_ORANGE);

	CenterText(Min(TEXT_LOADING_5, TEXT_LOADING_1 + frame / 5), x + 165 * _2X / 2, y - 6 * _2X, 1.0f);
}

void DrawCheckBox(int x, int y, int w, int h, bool checked, float zoom)
{
	MemRect(x, y, (float)w * zoom, (float)h * zoom, COLOR_BLACK);
	MemRect(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, (float)(w - 4 * _2X) * zoom, (float)(h - 4 * _2X) * zoom, COLOR_WHITE);
	if (checked == true)
		DrawImage(32 * _2X, 27 * _2X, 0 * _2X, 0 * _2X, x + (float)0 * _2X * zoom, y - (float)0 * _2X * zoom, false, false, false, false, false, 0.65f * zoom, sprite[ETC_IMG], ETC_IMG);
}

void DrawCheckButton(int x, int y, int w, int h, int gray, bool checked, int currency, int amount, float zoom)
{
	float numWidth = GetBigNumDx(amount, false, NUM_FONT_NORMAL, false, true, w - (float)(ITEMICONSIZE + 1 * _2X) * zoom - ((float)18 * _2X * 0.65f) * zoom - (float)(4 + 4 + 2) * _2X * zoom, zoom, false);

	float width = numWidth + (float)(ITEMICONSIZE + 1 * _2X) * zoom;
	DrawButtonFrame(x, y, w, h, gray, zoom);
	DrawCheckBox(x + (float)4 * _2X * zoom, y - (float)9 * _2X * zoom, (float)18 * _2X, (float)18 * _2X, checked, 0.65f * zoom);
	DrawIcon(currencyIcon[currency] == ICON_GOLD ? currencyIcon[currency] + frame % GOLDICONFRAME : currencyIcon[currency], x + w - (float)(4 * _2X) * zoom - width, y - (float)7 * _2X * zoom, zoom, COLOR_BROWN, false, false, true);

	DrawBigNum(amount, x + w - (float)(4 * _2X) * zoom, y - (float)9 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, 0, false, width - (float)(ITEMICONSIZE + 1 * _2X) * zoom, true, zoom, false);
}
//frameColor는 FRAME_GREEN 이상
void DrawButtonFrame(int x, int y, int w, int h, int frameColor, float zoom)
{
	int i;

	/*
	//����
	DrawImage(16 * _2X, BUYBUTTON_Y, 1, 1 + (frameColor - FRAME_GREEN) * 63, x, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);

	for (i = 0; i < (float)(w - (float)32 * _2X * zoom) / (float)(8 * _2X * zoom) + 1; i++)
		DrawImage(8 * _2X + 1, BUYBUTTON_Y, 33, 1 + (frameColor - FRAME_GREEN) * 63, x + (float)(16 * _2X + 8 * _2X * i) * zoom - 1, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);

	//������
	DrawImage(16 * _2X, BUYBUTTON_Y, 137, 1 + (frameColor - FRAME_GREEN) * 63, x + w - (float)(16 * _2X) * zoom, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);
	*/
}

void DrawBuyButton(int x, int y, int w, int h, int fra, int frameColor, long long amount, int currency, float zoom, bool ani, int sign, float discount)
{
	int curGray = grayScale;
	float BUYBUTTONZOOM = 1.2f;
	int numFont = NUM_FONT_NORMAL;
	float width = GetBigNumDxTTF(amount, sign, numFont, false, true, w - (float)(ITEMICONSIZE + 6 * _2X) * zoom, BUYBUTTONZOOM * zoom, false) + (float)(ITEMICONSIZE + 6 * _2X) * zoom;
	int tempAlpha = m_lgrpAlpha;
	int i;

	//DrawButtonFrame(x, y, w, h, frameColor, zoom, cvtDest, cvtLayer, buffering);
	/*
	//����
	DrawImage(16 * _2X, BUYBUTTON_Y, 1, 1 + (gray == false ? FRAME_GREEN - FRAME_GREEN : FRAME_GREY - FRAME_GREEN) * 63, x, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);

	for (i = 0; i < (float)(w - (float)32 * _2X * zoom) / (float)(8 * _2X * zoom) + 1; i++)
		DrawImage(8 * _2X + 1, BUYBUTTON_Y, 33, 1 + (gray == false ? FRAME_GREEN - FRAME_GREEN : FRAME_GREY - FRAME_GREEN) * 63, x + (float)(16 * _2X + 8 * _2X * i) * zoom - 1, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);

	//������
	DrawImage(16 * _2X, BUYBUTTON_Y, 137, 1 + (gray == false ? FRAME_GREEN - FRAME_GREEN : FRAME_GREY - FRAME_GREEN) * 63, x + w - (float)(16 * _2X) * zoom, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);
	*/
	grayScale = curGray;

	DrawImageScale(176, 40, 1, 679, x, y, false, false, false, false, false, 1.0f * zoom, 1.0f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

	//무료
	if (amount == 0) {
		CenterText(TEXT_FREE, x + (float)w / 2, y - (float)8 * _2X * zoom, BUYBUTTONZOOM * zoom);
	}
	else {
		//DrawSolidIcon(currencyIcon[currency], x + w / 2 - width / 2, y - 5 * _2X * zoom, zoom, false, cvtDest, cvtLayer, buffering);
		DrawIcon(currencyIcon[currency] == ICON_GOLD ? currencyIcon[currency] + frame % GOLDICONFRAME : currencyIcon[currency], x + w / 2 - width / 2 + (float)1 * _2X * zoom, y - (float)7 * _2X * zoom, zoom, COLOR_BROWN, false, false, true);

		if (discount > 0) {
			MemRect(x + w / 2 - width / 2 + (float)(ITEMICONSIZE + 2 * _2X) * zoom, y - (float)(9 * _2X) * zoom - (float)4 * _2X * zoom + (discount > 0 ? -(float)6 * _2X * zoom : 0), GetBigNumDx(amount, sign, numFont, false, true, w - (ITEMICONSIZE * zoom + 4 * _2X * zoom), zoom, true) + (float)8 * _2X * zoom, (float)4 * _2X * zoom, COLOR_REALRED);
		}
#ifdef NUMTTF
		DrawBigNumTTF(amount, x + w / 2 - width / 2 + (float)(ITEMICONSIZE + 2 * _2X) * zoom, y - (float)8 * _2X * zoom + (discount > 0 ? -(float)6 * _2X * zoom : 0), numFont, LEFT, 0, sign, width - (float)(ITEMICONSIZE + 2 * _2X) * zoom, true, BUYBUTTONZOOM * zoom, false);
#else
		DrawBigNum(amount, x + w / 2 - width / 2 + (float)(ITEMICONSIZE + 4 * _2X) * zoom, y - (float)8 * _2X * zoom + (discount > 0 ? -(float)6 * _2X * zoom : 0), numFont, LEFT, 0, sign, width - (float)(ITEMICONSIZE + 2 * _2X) * zoom, true, BUYBUTTONZOOM * zoom, false);
#endif
		if (discount > 0) {
			SetAlpha(Max(0, tempAlpha - 12));
			MemRect(x + w / 2 - width / 2 + (float)ITEMICONSIZE * zoom, y - (float)(9 * _2X) * zoom - (float)4 * _2X * zoom + (discount > 0 ? -(float)6 * _2X * zoom : 0), GetBigNumDx(amount, sign, numFont, false, true, w - (ITEMICONSIZE * zoom + 4 * _2X * zoom), zoom, true) + (float)8 * _2X * zoom, (float)4 * _2X * zoom, COLOR_REALRED);
			SetAlpha(tempAlpha);

			amount -= (float)amount * discount / 100;
#ifdef NUMTTF
			DrawBigNumTTF(amount, x + w / 2 - width / 2 + (float)ITEMICONSIZE * zoom + 2 * _2X * zoom, y - (float)(8 * _2X) * zoom + (float)12 * _2X * zoom + (discount > 0 ? -(float)6 * _2X * zoom : 0), numFont, LEFT, 0, sign, w - (float)(ITEMICONSIZE + 8 * _2X + 4 * _2X) * zoom, true, BUYBUTTONZOOM * zoom, false);
#else
			DrawBigNum(amount, x + w / 2 - width / 2 + (float)ITEMICONSIZE * zoom + 3 * _2X * zoom, y - (float)(8 * _2X) * zoom + (float)12 * _2X * zoom + (discount > 0 ? -(float)6 * _2X * zoom : 0), numFont, LEFT, 0, sign, w - (float)(ITEMICONSIZE + 8 * _2X + 4 * _2X) * zoom, true, BUYBUTTONZOOM * zoom, false);
#endif
		}
	}
}

void DrawTextButton(int x, int y, int w, int h, int fra, int gray, float zoom, bool ani, int textIdx)
{
	int curGray = grayScale;
	int numFont = zoom == 1 ? NUM_FONT_NORMAL : NUM_FONT_LARGE;
	int frameColor;

	if (gray > grayScale)
		grayScale = gray;

	if (grayScale == 32)
		frameColor = FRAME_GREY;
	else {
		frameColor = (ani == true ? FRAME_GREEN + (frame % 4) : FRAME_GREEN);
	}

	DrawFrame(x, y, w, h, frameColor);

	grayScale = curGray;

	if (textIdx > 0)
		CenterText(textIdx, x + w / 2, y - (float)(8 * _2X) * zoom, zoom);
}

void DrawMaxButton(int x, int y, int w, int h, int alphaIdx, float zoom)
{
	int gray = 32;
	int curGray = grayScale;
	int i;

	if (gray > grayScale)
		grayScale = gray;

	//DrawFrame(x, y, width, (float)(28 * _2X) * zoom, FRAME_GREEN, cvtDest, cvtLayer, buffering);
	//����
	DrawImage(16 * _2X, BUYBUTTON_Y, 1, 1 + (gray == false ? FRAME_GREEN - FRAME_GREEN : FRAME_GREY - FRAME_GREEN) * 63, x, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);

	for (i = 0; i < (float)(w - (float)32 * _2X * zoom) / (float)(8 * _2X * zoom) + 1; i++)
		DrawImage(8 * _2X + 1, BUYBUTTON_Y, 33, 1 + (gray == false ? FRAME_GREEN - FRAME_GREEN : FRAME_GREY - FRAME_GREEN) * 63, x + (float)(16 * _2X + 8 * _2X * i) * zoom - 1, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);

	//������
	DrawImage(16 * _2X, BUYBUTTON_Y, 137, 1 + (gray == false ? FRAME_GREEN - FRAME_GREEN : FRAME_GREY - FRAME_GREEN) * 63, x + w - (float)(16 * _2X) * zoom, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);

	grayScale = curGray;

	DrawGoldAlpha(x + w / 2, y - (float)(h - FONT_HEIGHT * 0.7f) / 2 * zoom, alphaIdx, FONT_GOLD_LARGE, zoom * 0.7f, CENTER, false, false);
}

void DrawTouchButton(int x, int y, const char* text, int func)
{
	DrawFrame(x, y, StringWidth(text, 1) + 4 * _2X, 20 * _2X, FRAME_CHOICEBUTTON);
	SetRectPoint(x, y, StringWidth(text, 1) + 4 * _2X, 20 * _2X, func);

	SetFontColor(COLOR_BROWN);
	CenterTextStrSolid(text, x + StringWidth(text, 1) / 2 + 2 * _2X, y - 3 * _2X, 1.0f);
	SetFontColor(COLOR_WHITE);
}


void DrawTouchLargeButton(int x, int y, int w, int h, const char* text, int func, int color, float zoom)
{
	//DrawFrame(x, y, (float)w * zoom, (float)h * zoom, color, cvtDest, cvtLayer, buffering);

	DrawImage(192, 62, 1, 1 + (color - FRAME_GREEN) * 63, x, y, false, false, false, false, false, zoom, sprite[BUTTON_IMG], BUTTON_IMG);


	//SetFontColor(COLOR_BROWN);
	DrawTextStr(text, x + ((float)w * zoom - StringWidth(text, zoom)) / 2, y - ((float)h / 2 * zoom + (float)(12) * zoom) / 2, 1.0f * zoom);
	//SetFontColor(COLOR_WHITE);
	if (func)
		SetRectPoint(x, y, (float)w * zoom, (float)h * zoom, func);

}

void DrawAlarmMark(int x, int y, int count, float zoom)
{
	DrawFrame(x, y, (float)(16 * _2X) * zoom, (float)(20 * _2X) * zoom, FRAME_RED);
	if (count > 99)
		DrawNum(99, x, y - (float)(6 * _2X) * zoom, NUM_FONT_SMALL, LEFT, 2, PLUS, false, zoom, true);
	else
		DrawNum(count, x + (float)(4 * _2X) * zoom, y - (float)(6 * _2X) * zoom, NUM_FONT_SMALL, LEFT, 2, false, false, zoom, true);

}

//화폐같은것을 더할 때는 이 마크고
void DrawPlusMark(int x, int y, float zoom)
{
	DrawImage(64, 64, 521, 640, x, y, false, false, false, false, false, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	//DrawImage(27 * _2X, 27 * _2X, 65 * _2X, 0 * _2X, x, y, false, false, false, false, false, zoom, sprite[ETC_IMG], cvtDest, cvtLayer, ETC_IMG, buffering);
}

void DrawXMark(int x, int y, float zoom)
{
	DrawImage(64, 62, 389, 639, x, y, false, false, false, false, false, zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
}

void DrawInfoMark(int x, int y, float zoom)
{
	DrawFrame(x, y, (float)(20 * _2X) * zoom, (float)(24 * _2X) * zoom, FRAME_BLUE);
	CenterText(TEXT_I, x + (float)(10 * _2X) * zoom, y - (float)(5 * _2X) * zoom, zoom);
}

// Item Showing
void DrawIcon(int idx, int x, int y, float zoom, int solid, bool ani, bool shadow, float thickness)
{
	int i;
	int beforeColor = baseColor;
	ITEM* it;
	int collectionIdx;
	int swordSkillIdx;
	int itemType;
	int itemDetail;
	int itemGrade;
	int enemyIdx = idx - ICON_SUMMON;
	int dMotion;
	OBJECT* pObj;

	if (idx >= ICON_BOX) {
		DrawBox(idx - ICON_BOX, x + (float)ITEMICONSIZE * zoom / 2, y - (float)ITEMICONSIZE * zoom / 2, LEFT, false, solid, false, false, true, zoom);
	}
	else if (idx >= ICON_SUMMON && idx < ICON_WEAPON) {
		enemyIdx = idx - ICON_SUMMON;

		SetSectionClip(x + (float)ITEMICONSIZE * zoom / 2 - (float)(ITEMICONSIZE + 6 * _2X) * zoom / 2, y + (float)8 * _2X * zoom, (float)(ITEMICONSIZE + 6 * _2X) * zoom, (float)(REWARDCARDSIZE_Y - 2 * _2X) * zoom, false);
		//ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)ITEMICONSIZE * zoom / 2 - (float)(40 * _2X / 2) * zoom, y + (float)(-ITEMICONSIZE + 8 * _2X) * zoom, SHADOW_IMG, zoom, cvtDest, cvtLayer, buffering);

		DrawCmfDetail(enemyData[enemyIdx * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[3 * enemyIdx + 0], x + (float)ITEMICONSIZE * zoom / 2/* + (float)(enemyBigIconPos[3 * enemyIdx + 1]) * zoom*/, y + (float)(-ITEMICONSIZE /*+ enemyBigIconPos[3 * enemyIdx + 2] + 4 * _2X*/) * zoom, RIGHT, zoom * ENEMYICONZOOM * enemyIconZoom[enemyIdx], false, false);

		UnSectionClip(false);
	}
	else if (idx >= ICON_DEBUF && idx < ICON_DEBUF + 1000) {
		pObj = &ao[ao[PLAYER].target];
		enemyIdx = pObj->type;

		SetSectionClip(x + (float)ITEMICONSIZE * zoom / 2 - (float)(ITEMICONSIZE + 6 * _2X) * zoom / 2, y + (float)1 * _2X * zoom, (float)(ITEMICONSIZE + 6 * _2X) * zoom, (float)(ITEMICONSIZE + 4 * _2X) * zoom, false);
		//ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)ITEMICONSIZE * zoom / 2 - (float)(40 * _2X / 2) * zoom, y + (float)(-ITEMICONSIZE + 8 * _2X) * zoom, SHADOW_IMG, zoom, cvtDest, cvtLayer, buffering);
		MemRect(x + (float)ITEMICONSIZE * zoom / 2 - (float)(ITEMICONSIZE + 6 * _2X) * zoom / 2, y + (float)1 * _2X * zoom, (float)(ITEMICONSIZE + 6 * _2X) * zoom, (float)(ITEMICONSIZE + 6 * _2X) * zoom, COLOR_GREY);
		DrawCmfDetail(enemyData[enemyIdx * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[3 * enemyIdx + 0], x + (float)ITEMICONSIZE * zoom / 2/* + (float)(enemyBigIconPos[3 * enemyIdx + 1]) * zoom*/, y + (float)(-ITEMICONSIZE /*+ enemyBigIconPos[3 * enemyIdx + 2] + 4 * _2X*/) * zoom, LEFT, zoom * ENEMYICONZOOM * enemyIconZoom[enemyIdx], false, false);

		dMotion = debufEffect[(idx - ICON_DEBUF) * 12 + (frame / MOTIONDIV % 12)];

		DrawEffect(dMotion, x + (float)ITEMICONSIZE * zoom / 2/* + (float)(enemyBigIconPos[3 * enemyIdx + 1]) * zoom*/, y + (float)(-ITEMICONSIZE - 6 * _2X + ((idx - ICON_DEBUF == BLIND || idx - ICON_DEBUF == POISON || idx - ICON_DEBUF == CURSE) ? 4 * _2X : 0)) * zoom, LEFT, false, zoom * ENEMYICONZOOM);

		UnSectionClip(false);
	}
	else {
		if (idx >= ICON_SKILL && idx < ICON_SUMMON) {
		}
		//장비류이면
		else if (idx >= ICON_WEAPON && idx < ICON_DEBUF) {

			idx = GetItemIcon(ITEM_SWORD, idx - ICON_WEAPON, GRADE_NORMAL);
		}
		else {
			switch (idx) {
			case ICON_BATTLE:
				idx = ITEM_BATTLE_ICON;
				break;
			case ICON_QUEST:
				idx = GetItemIcon(questRequestItem[robin.quest * 3 + 0], questRequestItem[robin.quest * 3 + 1], questRequestItem[robin.quest * 3 + 2]);
				break;
			}
		}

		if (shadow)
			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + (float)(ITEMICONSIZE / 2 - 12 * _2X) * zoom, y + (float)(-ITEMICONSIZE + 10 * _2X) * zoom, SHADOW_IMG, zoom);

		if (solid) {
			if (ani)
				SetColor(itemColor[frame / 2 % 6]);
			else
				SetColor(solid);

			for (i = 0; i < 4; i++) {
				DrawImage(16 * _2X, 16 * _2X, 1 + (idx & 0x07) * (16 * _2X + 1), 1 + ((idx & 0x3F) >> 3) * (16 * _2X + 1), x + (float)solidPosition[2 * i + 0] * thickness * zoom, y + (float)solidPosition[2 * i + 1] * thickness * zoom, false, false, false, false, false, zoom, sprite[ITEM_IMG + (idx >> 6)], ITEM_IMG + (idx >> 6));
			}
			SetColor(beforeColor);
		}

		if (idx == ICON_RAID)
			DrawNeutral(OBJ_BOX0 + boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], x + (float)(ITEMICONSIZE + 2 * _2X) * zoom / 2, y - (float)(ITEMICONSIZE + 2 * _2X) * zoom, LEFT, 0.8f * zoom);
		else
			DrawImage(16 * _2X, 16 * _2X, 1 + (idx & 0x07) * (16 * _2X + 1), 1 + ((idx & 0x3F) >> 3) * (16 * _2X + 1), x, y, false, false, false, false, false, zoom, sprite[ITEM_IMG + (idx >> 6)], ITEM_IMG + (idx >> 6));
	}
}

void DrawSkillIcon(int idx, int x, int y, float zoom)
{
	DrawImage(SKILLICONSIZE, SKILLICONSIZE, (idx & 0x07) * SKILLICONSIZE, ((idx & 0x3F) >> 3) * 16 * _2X, x, y, false, false, false, false, m_lgrpAlpha, zoom, sprite[SICON_IMG], SICON_IMG);
}

void DrawCrewBulletIcon(int idx, int x, int y, float zoom)
{
	DrawImage(CREWBULLETICONSIZE, CREWBULLETICONSIZE, (idx % CREWBULLETICONPERLINE) * CREWBULLETICONSIZE, (idx / CREWBULLETICONPERLINE) * CREWBULLETICONSIZE, x, y, false, false, false, false, m_lgrpAlpha, zoom, sprite[CREWBULLET_IMG], CREWBULLET_IMG);
}

//총탄 아이콘이 날아가는 모양. 표에 없는 번호는 그냥 날아가는 것으로 둔다.
int GetCrewBulletAni(int idx)
{
	if (idx < 0 || idx >= (int)(sizeof(crewBulletAni) / sizeof(crewBulletAni[0])))
		return CREWBULLETANI_NONE;

	return crewBulletAni[idx];
}

//총탄 한 개를 자기 패턴에 맞춰 그린다.
//DrawCrewBulletIcon()과 달리 x, y는 아이콘의 한가운데다 - 회전/확대가 중심 기준이라야
//총탄이 제자리에서 돌고 커진다(좌상단 기준으로 돌리면 궤도를 그리며 흔들린다).
//aniFrame은 계속 늘어나는 값이면 된다. 회전각과 맥동 위상의 기준으로만 쓴다.
void DrawCrewBulletAni(int idx, int x, int y, float zoom, int ani, int aniFrame)
{
	int xs = (idx % CREWBULLETICONPERLINE) * CREWBULLETICONSIZE;
	int ys = (idx / CREWBULLETICONPERLINE) * CREWBULLETICONSIZE;

	if (aniFrame < 0)
		aniFrame = -aniFrame;

	switch (ani) {
	case CREWBULLETANI_SPIN:
		RotateImage(CREWBULLETICONSIZE, CREWBULLETICONSIZE, xs, ys, x, y, false,
			(float)(aniFrame % CREWBULLET_SPINFRAME) * 360.0f / (float)CREWBULLET_SPINFRAME,
			false, false, zoom, Vec2(0.5f, 0.5f), sprite[CREWBULLET_IMG], CREWBULLET_IMG);
		break;
	case CREWBULLETANI_PULSE:
	{
		//0 -> +최대 -> 0 -> -최대 -> 0. 커졌다 원래대로 돌아오는 것이 반복된다.
		float pulse = 1.0f + CREWBULLET_PULSEAMP
			* sinf(3.141592f * 2.0f * (float)(aniFrame % CREWBULLET_PULSEFRAME) / (float)CREWBULLET_PULSEFRAME);

		RotateImage(CREWBULLETICONSIZE, CREWBULLETICONSIZE, xs, ys, x, y, false, 0.0f,
			false, false, zoom * pulse, Vec2(0.5f, 0.5f), sprite[CREWBULLET_IMG], CREWBULLET_IMG);
		break;
	}
	default:
		//그냥 날아간다. 기존 그리기를 그대로 쓰되 중심좌표를 좌상단으로 되돌려 넘긴다.
		DrawCrewBulletIcon(idx,
			x - (float)(CREWBULLETICONSIZE / 2) * zoom,
			y + (float)(CREWBULLETICONSIZE / 2) * zoom,
			zoom);
		break;
	}
}

//�ϴ� ��Ƽ�� ��ų�� ��쿡��?����Ѵ�?
void DrawSkillCard(int skillIdx, int lv, int x, int y, float zoom)
{
	int i, j;
	float width;
	long long realValue;
	float w = (float)SKILLCARDSIZE_X * zoom;
	float h = (float)SKILLCARDSIZE_Y * zoom;
	float numWidth = (float)(SKILLCARDSIZE_X - 12 * _2X) * zoom;
	int curStar, maxStar;
	float itemValueZoom = 0.8f;
	float bigNumWidth = (float)(SKILLCARDSIZE_X - ITEMICONSIZE - 1 * _2X) * itemValueZoom * zoom;
	int enemyIdx;

	int rewardIcon = 0;
	int rewardValue = 0;
	int str;

	//curStar = maxStar = GetItemStar(type, detail, grade);
	curStar = 0;
	maxStar = ITEMMAXLEVEL;

	DrawFrame(x, y, w, h, FRAME_SHOPBALLOON);

	//DrawTextStrSystem(TEXTPTR(TEXT_SKILLNAME_COMMON_ROBIN1 + skillIdx), x + (float)REWARDCARDSIZE_X / 2 * zoom, y + (float)(-REWARDCARDSIZE_Y + 16 * _2X / 2) * zoom, zoom / 2, CENTER, true, cvtDest, cvtLayer, buffering);


	switch (skillData[skillIdx * SKILLDATASIZE]) {
	case SUMMON:
		enemyIdx = skillData[skillIdx * SKILLDATASIZE + SKILLDATA_OBJECTINFO];

		SetSectionClip(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, w - (float)(2 * _2X) * zoom, h - (float)(2 * _2X) * zoom, false);
		ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + w / 2 - (float)(40 * _2X / 2) * zoom, y + (float)(-36 * _2X + 8 * _2X) * zoom, SHADOW_IMG, zoom);

		DrawCmfDetail(enemyData[enemyIdx * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[3 * enemyIdx + 0], x + w / 2 + (float)(enemyBigIconPos[3 * enemyIdx + 1]) * zoom, y + (float)(-36 * _2X + enemyBigIconPos[3 * enemyIdx + 2] + 2 * _2X) * zoom, LEFT, 1.2f * zoom, false, false);

		UnSectionClip(false);
		break;
	default:
		DrawSkillIcon(skillData[skillIdx * SKILLDATASIZE + SKILLDATA_ICON], x + w / 2 - (float)(ITEMICONSIZE)*zoom, y - h / 2 + (float)(ITEMICONSIZE)*zoom, zoom * 2);
		break;
	}
}


void DrawLock(int lv, int x, int y, float zoom)
{
	DrawIcon(ICON_EVENT_LOCK, x, y, zoom, COLOR_BROWN, false, false, true);
	DrawStarNum(ICON_CROWN, lv, x + (float)(2 * _2X) * zoom, y - (float)(4 * _2X) * zoom, 0.7f * zoom);
	//DrawLv(lv, x + (float)(ITEMICONSIZE / 2 + 1 * _2X) * zoom, y - (float)(ITEMICONSIZE / 4 + 5 * _2X) * zoom, 0.4f * zoom, CENTER, cvtDest, cvtLayer, buffering);
}

void DrawPercent(float num, int x, int y, float zoom, int align)
{
	float width;

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%.2f %s", num, "%");

	width = StringWidth(tempStr, zoom);

	switch (align) {
	case RIGHT:
		x -= width;
		break;
	case CENTER:
		x -= width / 2;
		break;
	}

	DrawTextStr(tempStr, x, y, zoom);

}

void DrawXNumTTF(int num, int x, int y, float zoom, int align)
{
	float width;

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "x%d", num);

	width = StringWidth(tempStr, zoom);

	switch (align) {
	case RIGHT:
		x -= width;
		break;
	case CENTER:
		x -= width / 2;
		break;
	}

	DrawTextStr(tempStr, x, y, zoom);
}

void DrawLv(int lv, int x, int y, float zoom, int align)
{
	float width;

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s %d", TEXTPTR(TEXT_ALPHA_LV), lv);

	width = StringWidth(tempStr, zoom);

	switch (align) {
	case RIGHT:
		x -= width;
		break;
	case CENTER:
		x -= width / 2;
		break;
	}

	DrawTextStr(tempStr, x, y, zoom);
}

void DrawItemIcon(ITEM* it, OBJECT* pObj, int x, int y, float zoom)
{
	int i;

	if (it->type == EMPTY)
		return;

	if (!EquipCheck(pObj, it) && it->type != ITEM_GEM)
		grayScale = 20;

	if (it->type == ITEM_RECIPE) {
		int type = GetItemIcon(it->detail >> 3, it->detail & 0x07, it->grade);

		DrawImage(16 * _2X, 16 * _2X, 1 + (1 + 16 * _2X) * (it->icon & 0x07), 1 + (16 * _2X + 1) * ((it->icon & 0x3F) >> 3), x, y, false, false, false, false, false, zoom, sprite[ITEM_IMG + (it->icon >> 6)], ITEM_IMG + (it->icon >> 6));
		SetAlpha(16);
		MemRect(x, y, (float)16 * _2X * zoom, (float)16 * _2X * zoom, 0x000000);
		SetAlpha(32);
		DrawImage(10 * _2X, 10 * _2X, 1 + (16 * _2X + 1) * (type & 0x07), 1 + (16 * _2X + 1) * ((type & 0x3F) >> 3), x + (float)4 * _2X * zoom, y + (float)4 * _2X * zoom, false, false, false, false, false, zoom, sprite[ITEM_IMG + (type >> 6)], ITEM_IMG + (type >> 6));
	}
	else if (it->type == ITEM_SKILL) {
		DrawSkillIcon(it->detail, x, y, zoom);
	}
	else
		DrawImage(16 * _2X, 16 * _2X, 1 + (16 * _2X + 1) * (it->icon & 0x07), 1 + (16 * _2X + 1) * ((it->icon & 0x3F) >> 3), x, y, false, false, false, false, false, zoom, sprite[ITEM_IMG + (it->icon >> 6)], ITEM_IMG + (it->icon >> 6));

	if (grayScale == 32) {
		grayScale = 0;
		SetAlpha(8);
		MemRect(x, y, (float)16 * _2X * zoom, (float)16 * _2X * zoom, 0x000000);
	}
	else if (grayScale == 20) {
		grayScale = 0;
		SetAlpha(8);
		MemRect(x, y, (float)16 * _2X * zoom, (float)16 * _2X * zoom, 0xFF0000);
	}

	SetAlpha(32);

	if (it->type > ITEM_GEM && it->type != ITEM_RECIPE && (it->type != ITEM_NETITEM || it->detail < ITEM_NET_BOX_WEAPON_HIGH))
		DrawNum(it->count, x + (float)16 * _2X * zoom, y + (float)9 * _2X * zoom, NUM_FONT_SMALL, RIGHT, 0, 0, false, zoom, true);

	if (it->type == ITEM_WASTE && it->cooldown)
		DrawCycle(x, y, (float)16 * _2X * zoom, (float)16 * _2X * zoom, it->cooldown, itemCooltime[it->detail] * 12, zoom);
	else if (it->type == ITEM_RING && it->cooldown)
		DrawCycle(x, y, (float)16 * _2X * zoom, (float)16 * _2X * zoom, it->cooldown, ringOption[it->detail * RINGOPTIONDATASIZE + 3 + Min(3, it->grade)] * 120, zoom);

	MemRectFrameThick(x - (float)1 * _2X * zoom, y + (float)1 * _2X * zoom, (float)(ITEMICONSIZE + 2 * _2X) * zoom, (float)(ITEMICONSIZE + 2 * _2X) * zoom, itemColor[it->grade], 1 * _2X);
	DrawStar(ICON_STAR, x + (float)ITEMICONSIZE * zoom / 2, y + (float)(5 * _2X) * zoom, GetItemStar(it->type, it->detail, it->grade), GetItemStar(it->type, it->detail, it->grade), GetItemStar(it->type, it->detail, it->grade), CENTER, true, 0.3f * zoom);
	//DrawLv(it->cooldown + 1, x + (float)ITEMICONSIZE * zoom / 2, y - (float)(ITEMICONSIZE + 1 * _2X) * zoom, 0.4f * zoom, CENTER, cvtDest, cvtLayer, buffering);
	//DrawStar(ICON_STAR, x + (float)ITEMICONSIZE * zoom / 2, y - (float)(ITEMICONSIZE + 2 * _2X) * zoom, GetItemStar(it->type, it->detail, it->grade), GetItemStar(it->type, it->detail, it->grade), CENTER, true, 0.3f * zoom, cvtDest, cvtLayer, buffering);

}

void DrawSlotIndex(int idx, int x, int y, int color, float zoom)
{
	MemRect(x, y, (float)(7 * _2X) * zoom, (float)(9 * _2X) * zoom, color);
	DrawNum(idx, x + (float)(1 * _2X) * zoom, y - (float)(1 * _2X) * zoom, FONT_SMALL, LEFT, 1, false, true, zoom, true);
}

void DrawMedalReward(int attackTypeIdx, int x, int y, int w, int h, int step, int str, bool ani, float zoom)
{
	int icon = pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0];
	int value;
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int crewIdx = GetCrewIdxFromType(ao[ENEMY].type);
	int itemType = crewReward[crewIdx * CREWREWARDDATASIZE + 0];
	int itemDetail = crewReward[crewIdx * CREWREWARDDATASIZE + 1];
	int itemGrade = crewReward[crewIdx * CREWREWARDDATASIZE + 2];
	int itemCnt = crewReward[crewIdx * CREWREWARDDATASIZE + 3];
	int itemLv = 1;
	float width;

	if (attackTypeIdx == ROULETTE_BATTLE)
		value = battleRewardMedal[str] * GetBetHeart(it->detail, it->grade, bet);
	else if (attackTypeIdx == ROULETTE_RAID)
		value = raidRewardMedal[str] * GetBetHeart(it->detail, it->grade, bet);

	DrawGoldAlpha(x + (float)(12 * _2X) * zoom, y - (float)(12 * _2X) * zoom, attackTypeIdx == ROULETTE_BATTLE ? hitAlpha[str] : raidAlpha[str], FONT_GOLD_LARGE, zoom, LEFT, false, false);

	DrawIcon(icon, x + (float)(160 * _2X) * zoom, y + (float)(-10 * _2X) * zoom, 1.5f * zoom, false, false, false, true);

	if (attackTypeIdx == ROULETTE_BATTLE) {
		DrawBigNum(value, x + (float)(160 * _2X + ITEMICONSIZE * 1.5f + 2 * _2X) * zoom, y - (float)(14 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, (float)(32 * _2X) * zoom, true, zoom, true);
		value = (float)enemyHouse.gold / BATTLEREWARDGOLDDIV * (str + 1);
		DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(228 * _2X) * zoom, y + (float)(-10 * _2X + 1 * _2X) * zoom, 1.5f * zoom, false, false, false, true);
		DrawBigNum(value, x + (float)(228 * _2X + ITEMICONSIZE * 1.5f + 2 * _2X) * zoom, y - (float)(14 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, (float)(32 * _2X) * zoom, true, zoom, true);
	}
	else {
		DrawBigNum(value, x + (float)(160 * _2X + ITEMICONSIZE * 1.5f + 2 * _2X) * zoom, y - (float)(14 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, (float)(128 * _2X) * zoom, true, zoom, true);
		switch (str) {
		case MISS:
			value = (float)enemyHouse.gold * 0.3f;
			break;
		case GOOD:
			value = (float)enemyHouse.gold * 0.85f;
			break;
		case PERFECT:
			value = enemyHouse.gold;
			break;
		}

		DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(228 * _2X) * zoom, y + (float)(-10 * _2X + 1 * _2X) * zoom, 1.5f * zoom, false, false, false, true);
		DrawBigNum(value, x + (float)(228 * _2X + ITEMICONSIZE * 1.5f + 2 * _2X) * zoom, y - (float)(14 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, (float)(32 * _2X) * zoom, true, zoom, true);
	}
}

void DrawRedDot(int x, int y, int color, int num, float zoom)
{
	int i;
	//칼라가 있으면 테두리를 쳐준다.
	if (color) {
		SetColor(color);
		for (i = 0; i < 4; i++) {
			DrawImage(9 * _2X, 9 * _2X, 42 * _2X, 45 * _2X, x + solidPosition[2 * i + 0] * zoom, y + solidPosition[2 * i + 1] * zoom, false, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);
		}
		SetColor(false);
	}

	DrawImage(9 * _2X, 9 * _2X, 42 * _2X, 45 * _2X, x, y, false, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);

	if (num) {
		DrawNum(num, x + (float)9 * _2X * zoom / 2, y - (float)9 * _2X * zoom / 2 + (float)7 * _2X * zoom / 2, NUM_FONT_SMALL, CENTER, false, false, false, zoom, false);
	}
}

//type
//LVUPREWARD_MENUOPEN_AUTOROLL..
//grade
//0~xx
void DrawLevelUpCard(int type, int lv, bool locked, int x, int y, float zoom)
{
	DrawImage(22 * _2X, 28 * _2X, 63 * _2X, 56 * _2X, x, y - (float)(0 * _2X) * zoom, false, false, false, false, false, 3.0f * zoom, sprite[COMMON_IMG], COMMON_IMG);

	ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + (float)(10 * _2X) * zoom, y - (float)(44 * _2X) * zoom, SHADOW_IMG, 2.0f * zoom);

	CenterText(TEXT_LVUPREWARD_AUTOROLL + type, x + (float)(33 * _2X) * zoom, y - (float)(8 * _2X) * zoom, zoom);

	if (locked == true)
		grayScale = 32;

	switch (type) {
	case LVUPREWARD_AUTOROLL:
		DrawNeutral(OBJ_BOX0 + (locked == false ? ((frame / (MOTIONDIV * 2 * 2)) % 6) : 0), x + (float)(34 * _2X) * zoom, y - (float)(80 * _2X) * zoom, LEFT, 2.0f * zoom);
		break;
	case LVUPREWARD_COLLECTIONS:
		DrawImage(40 * _2X, 40 * _2X, 40 * _2X * MENUICON_COLLECTIONS, 0 * _2X, x + (float)(13 * _2X) * zoom, y - (float)(31 * _2X) * zoom, false, false, false, false, 32, zoom, sprite[MENUICON_IMG], MENUICON_IMG);
		break;
	case LVUPREWARD_DAILYREWARDS:
		DrawIcon(ICON_EVENT_GREENBOOK, x + (float)(18 * _2X) * zoom, y - (float)(36 * _2X) * zoom, 2.0f * zoom, COLOR_WHITE, locked == false ? true : false, false, true);
		break;
	case LVUPREWARD_DAILYQUEST:
		DrawImage(40 * _2X, 40 * _2X, 40 * _2X * MENUICON_DAILYQUEST, 0 * _2X, x + (float)(13 * _2X) * zoom, y - (float)(31 * _2X) * zoom, false, false, false, false, 32, zoom, sprite[MENUICON_IMG], MENUICON_IMG);
		break;
	case LVUPREWARD_HEARTMAX:
		DrawIcon(ICON_HEART, x + (float)(18 * _2X) * zoom, y - (float)(36 * _2X) * zoom, 2.0f * zoom, COLOR_WHITE, locked == false ? true : false, false, true);

		break;
	case LVUPREWARD_HEARTPERHOUR:
		DrawIcon(ICON_HEART, x + (float)(18 * _2X) * zoom, y - (float)(36 * _2X) * zoom, 2.0f * zoom, COLOR_WHITE, locked == false ? true : false, false, true);
		break;
	case LVUPREWARD_SHILED:
		DrawIcon(ICON_SHIELD, x + (float)(18 * _2X) * zoom, y - (float)(36 * _2X) * zoom, 2.0f * zoom, COLOR_WHITE, locked == false ? true : false, false, true);
		break;
	case LVUPREWARD_GETHERO:
		if (IsGetHero(DIANA) == false)
			grayScale = 32;
		DrawPlayerCostume(
			DIANA,
			0, false,
			-1, false,
			-1, false,
			-1, false,
			-1, false,
			-1, false,

			x + (float)(16 * _2X) * zoom, y - (float)(68 * _2X) * zoom, RIGHT, false, zoom * HOUSEZOOM);
		grayScale = 0;
		if (IsGetHero(MAXX) == false)
			grayScale = 32;
		DrawPlayerCostume(
			MAXX,
			0, false,
			-1, false,
			-1, false,
			-1, false,
			-1, false,
			-1, false,

			x + (float)(48 * _2X) * zoom, y - (float)(68 * _2X) * zoom, LEFT, false, zoom * HOUSEZOOM);
		grayScale = 0;
		break;
	case LVUPREWARD_GETSKILL:
		DrawSkillIcon(0, x + (float)(18 * _2X) * zoom, y - (float)(36 * _2X) * zoom, 2.0f * zoom);
		break;
	case LVUPREWARD_STARBOX:
		//DrawNeutral(OBJ_BOX0 + boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], x + (float)(34 * _2X) * zoom, y - (float)(80 * _2X) * zoom, LEFT, 2.0f * zoom, cvtDest, cvtLayer, buffering);
		DrawBox(BOX_REWARD0, x + (float)(32 * _2X) * zoom, y - (float)(72 * _2X) * zoom, LEFT, false, COLOR_WHITE, locked == false ? true : false, false, false, 2.0f * zoom);
		DrawIcon(ICON_STAR, x + (float)(32 * _2X) * zoom, y - (float)(36 * _2X) * zoom, 1.0f * zoom, COLOR_WHITE, locked == false ? true : false, false, true);
		break;
	case LVUPREWARD_HEART:
		DrawIcon(ICON_HEART, x + (float)(18 * _2X) * zoom, y - (float)(36 * _2X) * zoom, 2.0f * zoom, COLOR_WHITE, locked == false ? true : false, false, true);
		break;
	}

	grayScale = 0;

	if (GetLevelUpRewardLv(type, lv) == MAXLV)
		CenterText(TEXT_ALPHA_MAX, x + (float)(34 * _2X) * zoom, y - (float)(76 * _2X) * zoom, zoom);
	else if (GetLevelUpRewardLv(type, lv) > 0)
		DrawLv(GetLevelUpRewardLv(type, lv), x + (float)(34 * _2X) * zoom, y - (float)(76 * _2X) * zoom, zoom, CENTER);

}

void DrawRewardCardRange(int type, int detail, int grade, long long startCnt, long long endCnt, int x, int y, float zoom, bool cardFrame)
{
	int icon;
	float w = (float)REWARDCARDSIZE_X * zoom;
	float h = (float)REWARDCARDSIZE_Y * zoom;
	float width;

	if (type == BOX_RANDOM || type == BOX_CREW)
		icon = ITEM_CARDBACK_ICON;
	else
		icon = GetItemIcon(type, detail, grade);

	if (cardFrame) {
		//DrawImage(REWARDCARDSIZE_X, ITEMCARDSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_CARD_LARGE_FRONT_IMG], cvtDest, cvtLayer, UI_CARD_LARGE_FRONT_IMG, buffering);
		//DrawWindow4(x, y, w, h, type == ITEM_CREW ? crewData[detail * CREWDATASIZE + 4] : itemBg[itemStartCnt[type] + detail * TOTALGRADE + grade], zoom, cvtDest, cvtLayer, buffering);

	}

	//DrawRewardCard(type, detail, grade, 0, startCnt, x, y, false, zoom, true, false, true, GetItemStar(type, detail, grade) + 1, GetItemStar(type, detail, grade) + 1, true, 0, cvtDest, cvtLayer, buffering);
	ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + w / 2 - (float)24 * _2X * zoom, y + (float)(-ITEMCARDSIZE_Y + ITEMICONSIZE * 4 + 8 * _2X) * zoom, SHADOW_IMG, zoom * 2);

	switch (type) {
	case BOX_EQUIP:
		//장비가 들어있는 박스
		if (detail <= BOX_REWARD0) {
			icon = GetItemIcon(boxEquipType[frame % 8], frame % itemTypeCnt[boxEquipType[frame % 8]], GRADE_NORMAL);
		}
		//몬스터가 들어있는 박스
		else if (detail <= BOX_REWARD1) {
			icon = ICON_SUMMON + crewData[(frame % TOTAL_CREW) * CREWDATASIZE];
		}
		//기타 박스
		else {
		}

		DrawIcon(icon, x + w / 2 - (float)ITEMICONSIZE * zoom, y + (float)(-ITEMCARDSIZE_Y + ITEMICONSIZE * 5) * zoom, zoom * 2, false, false, false, true);
		DrawStarNum(ICON_STAR, startCnt, x + (float)0 * _2X * zoom, y + (float)(-ITEMCARDSIZE_Y + ITEMICONSIZE * 3 - 4 * _2X) * zoom, zoom);
		DrawTextStr("-", x + (float)(1 * ITEMICONSIZE / 2 + 10 * _2X) * zoom, y + (float)(-ITEMCARDSIZE_Y + ITEMICONSIZE * 3 - 8 * _2X) * zoom, zoom);
		DrawStarNum(ICON_STAR, endCnt, x + (float)(1 * ITEMICONSIZE / 2 + 18 * _2X) * zoom, y + (float)(-ITEMCARDSIZE_Y + ITEMICONSIZE * 3 - 4 * _2X) * zoom, zoom);

		break;
	default:
		DrawIcon(icon, x + w / 2 - (float)ITEMICONSIZE * zoom, y + (float)(-ITEMCARDSIZE_Y + ITEMICONSIZE * 5) * zoom, zoom * 2, false, false, false, true);
		//���� ��ŸƮ�� ���尡 ������ �׳� ���� �ϳ��� ������
		if (startCnt == endCnt) {
#ifdef NUMTTF
			DrawBigNumTTF(endCnt, x + w / 2, y - (float)ITEMCARDSIZE_Y * zoom + (float)(ITEMICONSIZE * 2 + 8 * _2X) * zoom, NUM_FONT_NORMAL, CENTER, false, false, (float)(ITEMCARDSIZE_X - 8 * _2X) * zoom, true, 0.7f * zoom, true);
#else
			DrawBigNum(endCnt, x + w / 2, y - (float)ITEMCARDSIZE_Y * zoom + (float)(ITEMICONSIZE * 1 + 8 * _2X) * zoom, NUM_FONT_LARGE, CENTER, false, false, (float)(ITEMCARDSIZE_X - 8 * _2X) * zoom, false, zoom * 2 / 3, true);
#endif
		}
		//�׷��� ������ �����̱� ������ A-B���·� �־�����.
		else {
#ifdef NUMTTF
			width = GetBigNumDx(startCnt, false, NUM_FONT_NORMAL, false, false, (float)((REWARDCARDSIZE_X - 8 * _2X) / 2) * zoom, zoom / 2, true) + GetBigNumDx(endCnt, MINUS, NUM_FONT_NORMAL, false, false, ((REWARDCARDSIZE_X - 8 * _2X) / 2 + 12 * _2X) * zoom, 0.7f * zoom, true);
			DrawBigNumTTF(startCnt, x + w / 2 - width / 2, y - (float)REWARDCARDSIZE_Y * zoom + (float)(16 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, false, false, (float)((REWARDCARDSIZE_X - 8 * _2X) / 2) * zoom, false, 0.7f * zoom, true);
			DrawBigNumTTF(-endCnt, x + w / 2 - width / 2 + GetBigNumDx(startCnt, false, NUM_FONT_NORMAL, false, false, (float)((REWARDCARDSIZE_X - 8 * _2X) / 2), (zoom / 2), true), y - (float)REWARDCARDSIZE_Y * zoom + (float)(16 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, false, MINUS, (float)((REWARDCARDSIZE_X - 8 * _2X) / 2 + 12 * _2X) * zoom, false, 0.7f * zoom, true);
#else
			width = GetBigNumDx(startCnt, false, NUM_FONT_LARGE, false, false, (float)((ITEMCARDSIZE_X - 8 * _2X) / 2) * zoom, zoom * 2 / 3, true) + GetBigNumDx(endCnt, MINUS, NUM_FONT_LARGE, false, false, ((ITEMCARDSIZE_X - 8 * _2X) / 2 + 12 * _2X) * zoom, zoom * 2 / 3, true) + (float)(4 * _2X) * zoom;
			DrawBigNum(startCnt, x + w / 2 - width / 2, y - (float)ITEMCARDSIZE_Y * zoom + (float)(ITEMICONSIZE * 1 + 8 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, (float)((ITEMCARDSIZE_X - 8 * _2X) / 2) * zoom, false, zoom * 2 / 3, true);
			DrawBigNum(endCnt, x + w / 2 - width / 2 + GetBigNumDx(startCnt, false, NUM_FONT_LARGE, false, false, (float)((ITEMCARDSIZE_X - 8 * _2X) / 2), (zoom * 2 / 3), true) + (float)(4 * _2X) * zoom, y - (float)ITEMCARDSIZE_Y * zoom + (float)(ITEMICONSIZE * 1 + 8 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, MINUS, (float)((ITEMCARDSIZE_X - 8 * _2X) / 2 + 12 * _2X) * zoom, false, (zoom * 2 / 3), true);

#endif
		}
		break;
	}

}

//보상을 표현하기 
void DrawRewardCard(int type, int detail, int grade, int lv, long long count, int x, int y, bool ani, float zoom, int cardFrame, bool newItem, bool showValue, int curStar, int maxStar, bool shadow, int openFrame)
{
	int i, j;
	float width;
	int icon = GetItemIcon(type, detail, grade);
	long long realValue;
	int itemName = GetItemName(type, detail, grade);
	float w = (float)REWARDCARDSIZE_X * zoom;
	float h = (float)REWARDCARDSIZE_Y * zoom;
	int itemIdx = GetInvenIdx(type, detail, grade);
	float numWidth = (float)(REWARDCARDSIZE_X - 12 * _2X) * zoom;

	ITEM* it;

	DrawItemCard(type, detail, grade, lv, count, false, x, y, false, zoom, false, false, false, true, openFrame);
	return;
	//type = ITEM_BOX;
	//detail = 2;
	//grade = 0;

	if (type < ITEM_GEM) {
		realValue = itemUpgradeValue[type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + grade * (ITEMMAXLEVEL + 1) + lv];
	}
	else if (type == ITEM_CREW)
		realValue = crewReward[detail * CREWREWARDDATASIZE + 3];
	else
		realValue = count;

	if (itemIdx != -1)
		it = GetItemPtr(ITEMPTR_INVEN + GetInvenIdx(type, detail, grade));

	if (cardFrame == true) {
		//if (newItem == true)
		//	MemRect(x - (float)2 * _2X * zoom, y + (float)2 * _2X * zoom, w + (float)(4 * _2X) * zoom, h + (float)(4 * _2X) * zoom, cardFrameColorData[frame % 60], gScreenBuffer, gScreenLayer, false);

		//DrawWindow4(x, y, w, h, type == ITEM_CREW ? crewData[detail * CREWDATASIZE + 4] : itemBg[itemStartCnt[type] + detail * TOTALGRADE + grade], zoom, cvtDest, cvtLayer, buffering);

		//SetAlpha(28);
		//MemRect(x - (float)(1 * _2X) * zoom, y + (float)(-REWARDCARDSIZE_Y + 19 * _2X / 2) * zoom, w + (float)(2 * _2X) * zoom, (float)18 * _2X * zoom / 2, itemColor[GetItemStar(type, detail, grade) - 1], cvtDest, cvtLayer, buffering);
		//SetAlpha(32);
		//���� ȹ���� ���� ���� ī������ �ű�ȹ�涧 �����ټ��� �ֱ� ������
		//if (lv == -1) {
		//	CenterText(TEXT_QUESTION, x + (float)(REWARDCARDSIZE_X) / 2 * zoom, y + (float)(-REWARDCARDSIZE_Y + 15 * _2X / 2) * zoom, zoom / 2, cvtDest, cvtLayer, buffering);
		//}
		//else {
		switch (type) {
		default:
			DrawTextStrSystem(type == ITEM_CREW ? TEXTPTR(TEXT_MONSTERNAME_START + crewData[detail * CREWDATASIZE + 0]) : TEXTPTR(TEXT_ITEMNAME_START + GetItemName(type, detail, grade)), x + (float)REWARDCARDSIZE_X / 2 * zoom, y + (float)(-REWARDCARDSIZE_Y + 15 * _2X / 2) * zoom, zoom / 2, CENTER, true);
			break;
		case ITEM_SKILL:
			DrawTextStrSystem(TEXTPTR(TEXT_SKILLNAME_COMMON_ROBIN1 + detail), x + (float)REWARDCARDSIZE_X / 2 * zoom, y + (float)(-REWARDCARDSIZE_Y + 15 * _2X / 2) * zoom, zoom / 2, CENTER, true);
			break;
		}
		//}
	}

	if (lv == -1) {
		SetColor(COLOR_BLACK);

		//grayScale = 32;
	}

	switch (type) {
	default:
		if (shadow == true)
			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + w / 2 - (float)24 * _2X / 2 * zoom, y + (float)(-REWARDCARDSIZE_Y + ITEMICONSIZE + 22 * _2X) * zoom, SHADOW_IMG, zoom);

		DrawIcon(icon, x + w / 2 - (float)ITEMICONSIZE * 1.4f * zoom / 2, y + (float)(-REWARDCARDSIZE_Y + ITEMICONSIZE + ITEMICONSIZE + 18 * _2X) * zoom, 1.4f * zoom, false, false, false, true);
		break;
	case ITEM_NETITEM:
		switch (detail) {
		default:
			if (shadow == true)
				ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + w / 2 - (float)24 * _2X / 2 * zoom, y + (float)(-REWARDCARDSIZE_Y + ITEMICONSIZE + 60 * _2X + 2 * _2X) * zoom, SHADOW_IMG, zoom);

			DrawIcon(icon, x + w / 2 - (float)ITEMICONSIZE * zoom / 2, y + (float)(-REWARDCARDSIZE_Y + ITEMICONSIZE + 4 * ITEMICONSIZE + 60 * _2X) * zoom, zoom, false, false, false, true);
			break;
		case ITEM_NET_BOX_WEAPON_HIGH:
		case ITEM_NET_BOX_WEAPON_MID:
		case ITEM_NET_BOX_WEAPON_LOW:
		case ITEM_NET_BOX_DEFENSE_HIGH:
		case ITEM_NET_BOX_DEFENSE_MID:
		case ITEM_NET_BOX_DEFENSE_LOW:
		case ITEM_NET_BOX_ACCESSORY_HIGH:
		case ITEM_NET_BOX_ACCESSORY_MID:
		case ITEM_NET_BOX_ACCESSORY_LOW:
		case ITEM_NET_BOX_RANDOM:
		case ITEM_NET_BOX_GEM:
		case ITEM_NET_PACKAGE_NEWBIE:
		case ITEM_NET_PACKAGE_ENCHANT:
		case ITEM_NET_PACKAGE_STONE:
		case ITEM_NET_PACKAGE_ARENA:
		case ITEM_NET_PACKAGE_LUCK:
			DrawBox(detail, x + w / 2, y + (float)(-BOXSIZE_Y / 2 - 4 * _2X) * zoom, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], false, false, false, true, 1.2f * zoom);
			break;
		}
		break;
	case ITEM_BOX:
		DrawBox(detail, x + w / 2, y + (float)(-BOXSIZE_Y / 2 - 4 * _2X) * zoom, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], false, false, false, true, 1.2f * zoom);
		break;
	case ITEM_CREW:
		if (shadow == true)
			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + w / 2 - (float)24 * _2X / 2 * zoom, y + (float)(-REWARDCARDSIZE_Y + ITEMICONSIZE + 24 * _2X + 2 * _2X) * zoom, SHADOW_IMG, zoom);

		EnemyProfileDraw(x + w / 2 - (float)(36 * _2X / 2) * zoom, y + (float)(-REWARDCARDSIZE_Y + ITEMICONSIZE + 38 * _2X) * zoom + (float)(cardFrame == false ? -4 * _2X : 0) * zoom, crewData[detail * CREWDATASIZE + 0], false, false, zoom);
		break;
	case ITEM_SKILL:
		DrawSkillIcon(skillData[detail * SKILLDATASIZE + 5], x + w / 2 - (float)(32 * _2X / 2) * zoom, y + (float)(-REWARDCARDSIZE_Y + ITEMICONSIZE + 36 * _2X) * zoom + (float)(cardFrame == false ? -4 * _2X : 0) * zoom, 2 * zoom);
		break;
	}

	SetColor(false);

	if (showValue == true)
		switch (type) {
		default:

			if (lv != -1 && type < ITEM_GEM) {
				if (cardFrame == true) {
					////개수마크
					//DrawAlarmMark(x + (float)(2 * _2X) * zoom / 2, y - (float)(4 * _2X) * zoom / 2, count, zoom / 2, cvtDest, cvtLayer, buffering);
					////i마크
					//DrawInfoMark(x + w - (float)(18 * _2X) * zoom / 2, y - (float)(4 * _2X) * zoom / 2, zoom / 2, cvtDest, cvtLayer, buffering);
					//개수마크
					if (count)
						DrawAlarmMark(x + w - (float)(18 * _2X) * zoom / 2, y - (float)(4 * _2X) * zoom / 2, count, zoom / 2);

				}

				//DrawItemValue(type, detail, grade, lv, x + (float)REWARDCARDSIZE_X * zoom / 2, y + (float)(-REWARDCARDSIZE_Y + 26 * _2X) * zoom, CENTER, false, zoom / 2, 32 * _2X * zoom, cvtDest, cvtLayer, buffering);

				if (type < ITEM_GEM) {
					//if (lv) {
						//����ǥ��
					DrawLv(lv + 1, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 48 * _2X / 2) * zoom, zoom / 2, CENTER);
					//sprintf(tempStr, "%s %d", TEXTPTR(TEXT_ALPHA_LV), lv + 1);
					//CenterTextStr(tempStr, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 48 * _2X / 2) * zoom, zoom / 2, cvtDest, cvtLayer, buffering);
				//}
				//else
				//	CenterText(TEXT_NOTACQUIRED, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 32 * _2X / 2) * zoom, zoom / 2, cvtDest, cvtLayer, buffering);
				}
			}

			else if (count > 1) {
				numWidth = (float)(REWARDCARDSIZE_X - 24 * _2X) * zoom;
#ifdef NUMTTF
				DrawBigNumTTF(count, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 27 * _2X) * zoom, NUM_FONT_LARGE, CENTER, false, false, numWidth, false, zoom * 0.71f, true);
#else
				DrawBigNum(count, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 27 * _2X) * zoom, NUM_FONT_LARGE, CENTER, false, false, numWidth, false, zoom / 2, true);
#endif
			}

			//별 그려주기
			if (cardFrame == true) {

				DrawStar(ICON_STAR, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 16 * _2X) * zoom, curStar, maxStar, maxStar, CENTER, true, zoom * 0.40f);

			}
#ifdef NEWITEMMARKSHOW
			//new mark
			if (newItem == true) {
				DrawImage(27 * _2X, 27 * _2X, 31 * _2X, 1 * _2X, x - (float)(frame / MOTIONDIV % 10) * 0.01f * zoom * 27 * _2X / 2, y + (float)(frame / MOTIONDIV % 10) * 0.01f * zoom * 27 * _2X / 2, false, false, false, false, false, zoom / 2 + (float)(frame / MOTIONDIV % 10) * 0.01f * zoom, sprite[TOUCH_IMG], TOUCH_IMG);
			}
#endif
			break;
		case ITEM_CREW:
			//if (lv != -1) {
			if (cardFrame == true) {
				////개수마크
				//DrawAlarmMark(x + (float)(2 * _2X) * zoom / 2, y - (float)(2 * _2X) * zoom / 2, count, zoom / 2, cvtDest, cvtLayer, buffering);
				////i마크
				//DrawInfoMark(x + w - (float)(18 * _2X) * zoom / 2, y - (float)(2 * _2X) * zoom / 2, zoom / 2, cvtDest, cvtLayer, buffering);
				//개수마크
				DrawAlarmMark(x + w - (float)(18 * _2X) * zoom / 2, y - (float)(2 * _2X) * zoom / 2, count, zoom / 2);

			}

			if (crewReward[detail * CREWREWARDDATASIZE + 0] == ITEM_BOX) {
				DrawBox(crewReward[detail * CREWREWARDDATASIZE + 1], x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 16 * _2X) * zoom, LEFT, false, false, true, false, false, zoom / 5);
			}
			else {
				width = (float)(ITEMICONSIZE)*zoom / 2 + GetBigNumDx(realValue, false, NUM_FONT_LARGE, false, true, numWidth / 2, zoom / 2, true);

				DrawIcon(GetItemIcon(crewReward[detail * CREWREWARDDATASIZE + 0], crewReward[detail * CREWREWARDDATASIZE + 1], crewReward[detail * CREWREWARDDATASIZE + 2]), x + w / 2 - width / 2, y + (float)(-REWARDCARDSIZE_Y + 26 * _2X + (cardFrame == false ? -12 * _2X : 0)) * zoom, zoom / 2, COLOR_BROWN, false, false, true);
#ifdef NUMTTF
				DrawBigNumTTF(realValue, x + w / 2 - width / 2 + (float)(ITEMICONSIZE + 2 * _2X) * zoom / 2, y + (float)(-REWARDCARDSIZE_Y + 27 * _2X + (cardFrame == false ? -12 * _2X : 0)) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth / 2, false, zoom / 2, true);
#else
				DrawBigNum(realValue, x + w / 2 - width / 2 + (float)(ITEMICONSIZE + 2 * _2X) * zoom / 2, y + (float)(-REWARDCARDSIZE_Y + 27 * _2X + (cardFrame == false ? -12 * _2X : 0)) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth / 2, false, zoom / 2, true);
#endif
			}
			if (cardFrame == true) {
				//����ǥ��
				sprintf(tempStr, TEXTPTR(TEXT_ALPHA_LV), lv + 1);
				//DrawText(TEXT_LV, x + w / 2 - 24 * _2X, y - REWARDCARDSIZE_Y + 32 * _2X, cvtDest, cvtLayer, buffering);
				CenterTextStr(tempStr, x + w / 2 + (float)2 * _2X * zoom, y + (float)(-REWARDCARDSIZE_Y + 32 * _2X / 2) * zoom, zoom / 2);
			}
			//}
			//else
			//	CenterText(TEXT_NOTACQUIRED, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 32 * _2X / 2) * zoom, zoom / 2, cvtDest, cvtLayer, buffering);
#ifdef NEWITEMMARKSHOW
			//new mark
			if (newItem == true) {
				DrawImage(27 * _2X, 27 * _2X, 31 * _2X, 1 * _2X, x, y, false, false, false, false, false, zoom / 2, sprite[TOUCH_IMG], TOUCH_IMG);
			}
#endif
			break;
		case ITEM_STATUE:
			switch (detail) {
			case ITEM_STATUE_WIND:
			case ITEM_STATUE_DIMENSION:
			case ITEM_STATUE_SUN:
			case ITEM_STATUE_FLAME:
			case ITEM_STATUE_THUNDER:
			case ITEM_STATUE_DRAGON:
				for (i = 0; i < 6; i++) {
					if (skillInitData[i * 3 + 2] == detail) {
						realValue = skillData[skillInitData[i * 3 + 0] * SKILLDATASIZE + 6];

					}
				}
				break;
			}
			width = (float)ITEMICONSIZE * zoom + GetNumDx(realValue, false, NUM_FONT_LARGE, false, false, zoom, true) + (float)(16 * _2X) * zoom;

			DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + w / 2 - width / 2, y - (float)REWARDCARDSIZE_Y * zoom + (float)30 * _2X * zoom, zoom, false, false, false, true);
			//DrawAlpha(x + w / 2 - width / 2 + (float)ITEMICONSIZE * zoom, y - (float)REWARDCARDSIZE_Y * zoom + (float)(30 * _2X) * zoom - (float)(4 * _2X) * zoom, ALPHA_X, FONT_LARGE, zoom, false, cvtDest, cvtLayer, buffering);
			DrawTextStr("x", x + w / 2 - width / 2 + (float)ITEMICONSIZE * zoom, y - (float)REWARDCARDSIZE_Y * zoom + (float)(30 * _2X) * zoom - (float)(4 * _2X) * zoom, zoom);
#ifdef NUMTTF
			DrawNumTTF(realValue, x + w / 2 - width / 2 + (float)ITEMICONSIZE * zoom + (float)8 * _2X * zoom, y - (float)REWARDCARDSIZE_Y * zoom + (float)30 * _2X * zoom, NUM_FONT_LARGE, LEFT, false, false, true, zoom, false);
#else
			DrawNum(realValue, x + w / 2 - width / 2 + (float)ITEMICONSIZE * zoom + (float)8 * _2X * zoom, y - (float)REWARDCARDSIZE_Y * zoom + (float)30 * _2X * zoom, NUM_FONT_LARGE, LEFT, false, false, true, zoom, false);
#endif
			break;
		case ITEM_NETITEM:
			switch (detail) {
			case ITEM_NET_BOX_WEAPON_HIGH: //고급무기상자(168)	//BOX_H2
			case ITEM_NET_BOX_WEAPON_MID: //중급무기상자(169)	//BOX_H1
			case ITEM_NET_BOX_WEAPON_LOW: //하급무기상자(170)	//BOX_H1
			case ITEM_NET_BOX_DEFENSE_HIGH: //고급방어구상자(171)	//BOX_H2
			case ITEM_NET_BOX_DEFENSE_MID: //중급방어구상자(172)	//BOX_H1
			case ITEM_NET_BOX_DEFENSE_LOW: //하급방어구상자(173)	//BOX_H1
			case ITEM_NET_BOX_ACCESSORY_HIGH: //고급악세사리상자(174)	//BOX_H2
			case ITEM_NET_BOX_ACCESSORY_MID: //중급악세사리상자(175)	//BOX_H1
			case ITEM_NET_BOX_ACCESSORY_LOW: //하급악세사리상자(176)	//BOX_H1
			case ITEM_NET_BOX_RANDOM:	//랜덤아이템상자(177)	//BOX_EQUIP_SILVER
			case ITEM_NET_BOX_GEM:	//고급보석(178)	//BOX_S5
				break;
			default:
				width = GetNumDx(count, false, NUM_FONT_LARGE, false, false, zoom / 2, false);
#ifdef NUMTTF
				DrawBigNumTTF(count, x + w / 2, y - (float)REWARDCARDSIZE_Y * zoom + (float)(30 * _2X) * zoom, NUM_FONT_LARGE, CENTER, false, false, width, false, zoom / 2, false);
#else
				DrawBigNum(count, x + w / 2, y - (float)REWARDCARDSIZE_Y * zoom + (float)(30 * _2X) * zoom, NUM_FONT_LARGE, CENTER, false, false, width, false, zoom / 2, false);
#endif
				break;
			}
			break;
		case ITEM_SKILL:
			//DrawLv(lv, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + REWARDCARDSIZE_Y + 4 * _2X) * zoom, zoom / 2, CENTER, cvtDest, cvtLayer, buffering);
			DrawStar(ICON_STAR, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + REWARDCARDSIZE_Y + 2 * _2X) * zoom, skillData[detail * SKILLDATASIZE + SKILLDATASIZE - 1], skillData[detail * SKILLDATASIZE + SKILLDATASIZE - 1], skillData[detail * SKILLDATASIZE + SKILLDATASIZE - 1], CENTER, true, zoom * 0.45f);

			DrawXNumGold(10, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 34 * _2X / 2) * zoom, false, 0.35f * zoom, CENTER, false);
			break;
			//case ITEM_BOX:

			//	break;
			//default:
			//	//width = GetBigNumDx(count, false, NUM_FONT_LARGE, false, false, REWARDCARDSIZE_X - 32 * _2X, zoom / 2);
			//	numWidth = (float)(REWARDCARDSIZE_X - 24 * _2X) * zoom;

			//	DrawBigNum(count, x + w / 2, y + (float)(-REWARDCARDSIZE_Y + 27 * _2X) * zoom, NUM_FONT_LARGE, CENTER, false, false, numWidth, false, zoom / 2, true, cvtDest, cvtLayer, buffering);
			//	break;
		}

	switch (type) {
	default:
		//��ǥ��
	//starCnt = GetItemStar(type, detail, grade);
		//DrawStar(ICON_STAR, x + w / 2, y + (float)6 * _2X * zoom / 2, curStar, maxStar, CENTER, true, zoom / 2, cvtDest, cvtLayer, buffering);

		break;
	case ITEM_CREW:
		//��ǥ��
		//starCnt = crewData[detail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
		//DrawStar(ICON_STAR, x + w / 2, y + (float)6 * _2X * zoom / 2, curStar, maxStar, CENTER, true, zoom / 2, cvtDest, cvtLayer, buffering);

		break;

	}

	//새로운 아이템이면 별을 
	if (newItem == true && (type < ITEM_GEM || type == ITEM_CREW)) {
		DrawEffect(1000 + newCardEffect[(frame / MOTIONDIV % 28) * 3 + 0], x + (float)(newCardEffect[(frame / MOTIONDIV % 28) * 3 + 1]) * zoom, y - (float)(newCardEffect[(frame / MOTIONDIV % 28) * 3 + 2]) * zoom, ao[PLAYER].dirF, false, 0.5f * zoom);
	}
}

float GetEquipIconWidth(int itemType, int itemDetail, int itemGrade, float zoom)
{
	float width = 0;
	int i;
	int collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);

	width = (float)(ITEMICONSIZE + 2 * _2X) * zoom;

	return width;
}

//type = DATATYPE_ABSOLUTE / DATATYPE_MULTIPLE / DATATYPE_PERCENT
//x
//y
//align
//return 값은 넓이이다.
void DrawEquipIcon(int itemType, int itemDetail, int itemGrade, int x, int y, float zoom, bool iconAni)
{
	int i;
	int collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);

	signed short icon;// = statIcon[itemEquipSlot[itemType]];

	float width = 0;

	icon = ICON_GOLD;
	DrawIcon(icon, x, y, zoom, false, false, false, true);
}

void DrawItemValue(int itemType, int itemDetail, int itemGrade, int itemLv, int x, int y, int align, int plusLv, float zoom, float numWidth)
{
	float width;
	int icon;
	long long realValue;
	int upperValue;
	int underValue;
	int collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);


	switch (itemEquipSlot[itemType]) {
	default:
		realValue = itemUpgradeValue[itemType * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv];
		break;
	}


	itemLv += plusLv;

	switch (equipDataType[itemEquipSlot[itemType]]) {
	case DATATYPE_ABSOLUTE:

		width = GetBigNumDx(realValue, false, NUM_FONT_LARGE, false, false, numWidth, zoom, true) + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom);
		switch (align) {
		case LEFT:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x, y, zoom, true);
			DrawBigNum(realValue, x + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y + (float)(1 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			break;
		case RIGHT:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x - width, y, zoom, true);
			DrawBigNum(realValue, x - width + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y + (float)(1 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			break;
		case CENTER:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x - width / 2, y, zoom, true);
			DrawBigNum(realValue, x - width / 2 + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y + (float)(1 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			break;
		}
		break;
	case DATATYPE_MULTIPLE:
		width = GetBigNumDx(realValue, false, NUM_FONT_LARGE, false, false, numWidth, zoom, true) + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom) + (float)(10 * _2X) * zoom;

		switch (align) {
		case LEFT:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x, y, zoom, true);
			DrawAlpha(x + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y - (float)(4 * _2X) * zoom, ALPHA_X, FONT_LARGE, zoom, false);
			DrawBigNum(realValue, x + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom) + (float)(8 * _2X + 2 * _2X) * zoom, y + (float)(1 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			break;
		case RIGHT:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x - width, y, zoom, true);
			DrawAlpha(x - width + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y - (float)(4 * _2X) * zoom, ALPHA_X, FONT_LARGE, zoom, false);
			DrawBigNum(realValue, x - width + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom) + (float)(8 * _2X + 2 * _2X) * zoom, y + (float)(1 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			break;
		case CENTER:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x - width / 2, y, zoom, true);
			DrawAlpha(x - width / 2 + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y - (float)(4 * _2X) * zoom, ALPHA_X, FONT_LARGE, zoom, false);
			DrawBigNum(realValue, x - width / 2 + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom) + (float)(8 * _2X + 2 * _2X) * zoom, y + (float)(DY / 2 - 12 * _2X - ITEMICONSIZE + 1 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			break;
		}
		break;
	case DATATYPE_PERCENT:
		width = GetBigNumDx(realValue, false, NUM_FONT_LARGE, false, false, numWidth, zoom, true) + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom) + (float)(8 * _2X + 2 * _2X) * zoom;

		switch (align) {
		case LEFT:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x, y, zoom, true);
			DrawBigNum(realValue, x + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y + (float)(1 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			DrawImage(8 * _2X, 11 * _2X, 216 * _2X, 141 * _2X, x + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom) + GetNumDx(realValue, false, NUM_FONT_LARGE, false, false, zoom, true) + (float)(2 * _2X) * zoom, y - (float)(3 * _2X) * zoom, false, false, false, false, false, zoom, sprite[EFFECT_IMG], EFFECT_IMG);
			break;
		case RIGHT:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x - width, y, zoom, true);
			DrawBigNum(realValue, x - width + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y + 1 * _2X, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			DrawImage(8 * _2X, 11 * _2X, 216 * _2X, 141 * _2X, x - width + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom) + GetNumDx(realValue, false, NUM_FONT_LARGE, false, false, zoom, true) + (float)(2 * _2X) * zoom, y - (float)(3 * _2X) * zoom, false, false, false, false, false, zoom, sprite[EFFECT_IMG], EFFECT_IMG);
			break;
		case CENTER:
			DrawEquipIcon(itemType, itemDetail, itemGrade, x - width / 2, y, zoom, true);
			DrawBigNum(realValue, x - width / 2 + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom), y + 1 * _2X, NUM_FONT_LARGE, LEFT, false, false, numWidth, false, zoom, true);
			DrawImage(8 * _2X, 11 * _2X, 216 * _2X, 141 * _2X, x - width / 2 + GetEquipIconWidth(itemType, itemDetail, itemGrade, zoom) + GetNumDx(realValue, false, NUM_FONT_LARGE, false, false, zoom, true) + (float)(2 * _2X) * zoom, y - (float)(3 * _2X) * zoom, false, false, false, false, false, zoom, sprite[EFFECT_IMG], EFFECT_IMG);
			break;
		}
		break;
	}
}

void HitCountCheck(OBJECT* pObj)
{
	int realAttacker = GetObjFromPtr(pObj);

	if (realAttacker >= BULLET && ao[realAttacker].target < TOTALCHAR)
		realAttacker = ao[realAttacker].target;

	if (ao[realAttacker].attack >= ATTACK_SKILL) {
		ao[realAttacker].hitCount = ao[realAttacker].hitCountFrame = 0;
	}
}

void DrawHitCount(OBJECT* pObj, int x, int y, float zoom)
{
	if (pObj->hitCount > 1) {
		//DrawGoldNum(pObj->hitCount, x, y, LEFT, false, false, true, 2 * zoom, cvtDest, cvtLayer, buffering);
		DrawXNumGold(pObj->hitCount, x, y, false, zoom, CENTER, false);
		//DrawNum(pObj->hitCount, x - (float)(4 * _2X) * zoom, y, NUM_FONT_NORMAL, RIGHT, false, false, true, 2 * zoom, true, cvtDest, cvtLayer, buffering);
		//DrawImage(24 * _2X, 11 * _2X, 215 * _2X, 179 * _2X, x + (float)(4 * _2X) * zoom, y - (float)2 * _2X * zoom, false, false, false, false, false, 2 * zoom, sprite[EFFECT_IMG], cvtDest, cvtLayer, EFFECT_IMG, buffering);
		//PlayMusic(M_SWORDHIT);
	}
}

void DrawSocket(int socket, int x, int y, float zoom)
{
	DrawArray(IMG_SOCKET, x, y, zoom);

	if (socket < EMPTY) {
		SetAlpha(32 - Abs(frame % 8 - 4) * 4);
		DrawArray(IMG_RUBY + socket % 10, x + (float)1 * _2X * zoom, y - (float)1 * _2X * zoom, zoom);
		SetAlpha(32);
	}
}

void DrawCycle(int x, int y, int w, int h, int cycle, int full, float zoom)
{
	int tRect[4];
	w = float(w) * zoom;
	h = float(h) * zoom;
	int t;

//if (rect[0])
//	return;
//cycle = frame % FPS;
//full = FPS;

if (cycle < FPS) {
	SetAlpha(cycle);
	MemRect(x, y, w, h, COLOR_WHITE);
}
else {
	SetAlpha(16);

	if (cycle == full)
		MemRect(x, y, w, h, 0x000000);
	else {
		MemRect(x, y, w, (float)h * cycle / full, 0x000000);
		//tRect[0] = Max(clipX, x + offX);
		//tRect[1] = Max(clipY, y + offY);
		//tRect[2] = Min(clipX2, tRect[0] + w);
		//tRect[3] = Min(clipY2, tRect[1] + h);

		//if (tRect[0] < tRect[2] && tRect[1] < tRect[3]) {
		//	t = ((full - cycle) * 360 / (full - 4)) / 9 * 9;

		//}
	}
}

SetAlpha(32);
}

void DrawSelect(int x, int y, int w, int h, int grade)
{
	int tRect[4];

	if (w > 20 || h > 20)
		//fillRectAlpha(x, y, w, h, COLOR_WHITE, 0x20);
		return;

	tRect[0] = x + offX;
	tRect[1] = y + offY;
	tRect[2] = x + w + offX;
	tRect[3] = y + h + offY;
	//SetColor(itemColor[grade]);

}


void DrawTime(int x, int y, int atime, int type, int align, float zoom)
{
	//atime은 초다.
	//atime * 60 = 1m
	//atime * 3600 = 1h
	//atime * 144000 = 1d
	//1일 이상이면 xx d:yy h:zz m
	float width;

	switch (type) {
	case TIME_HOUR_MINUTE:
		//1�ð��� ������ XX�ð� YY��
		memset(&tempStr, 0, sizeof(tempStr));
		sprintf(tempStr, "%02d:%02d", atime / 3600, ((atime - (atime / 3600) * 3600) / 60));

		break;
	case TIME_MINUTE_SECONDS:
		memset(&tempStr, 0, sizeof(tempStr));
		sprintf(tempStr, "%02d:%02d", atime / 60, atime % 60);

		break;
	}

	width = StringWidth(tempStr, zoom);
	switch (align) {
	case CENTER:
		x -= width / 2;
		break;
	case RIGHT:
		x -= width;
		break;
	}

	DrawTextStr(tempStr, x, y, zoom);
}

void DrawRemainTime(int x, int y, long long remainSec, int align, float zoom)
{
	if (remainSec < 0) remainSec = 0;

	long long totalSec = remainSec / 1000;

	int day = totalSec / 86400;
	int hour = (totalSec / 3600) % 24;
	int min = (totalSec / 60) % 60;
	int sec = totalSec % 60;
	int ms = remainSec % 1000;

	char str[32];

	if (day > 0)
	{
		sprintf(str, "%dD:%2dH", day, hour);
	}
	else if (hour > 0)
	{
		sprintf(str, "%2dH:%2dM", hour, min);
	}
	else if (min > 0)
	{
		sprintf(str, "%2dM:%2dS", min, sec);
	}
	else if (sec > 0)
	{
		sprintf(str, "%2dS:%2d", sec, ms);
	}
	else {
		sprintf(str, "%2d", ms);
	}

	DrawTextStrSystem(str, x, y, zoom, align, true);
}

void DrawDetailTimeGold(int x, int y, int atime, int font, int align, float zoom)
{
	//atime은 초다.
	//atime * 60 = 1m
	//atime * 3600 = 1h
	//atime * 144000 = 1d
	//1일 이상이면 xx d:yy h:zz m
	float width;

	//x = x + (float)30 * _2X * zoom;

	switch (font) {
	default:
		if (atime >= 144000) {
			//00d:00h:00m
			DrawGoldNum(atime / 144000, x + (float)38 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)40 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_D, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			//DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], cvtDest, cvtLayer, GOLDFONT_IMG, buffering);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum((atime % 144000) / 3600, x + (float)108 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)110 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_H, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			//DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], cvtDest, cvtLayer, GOLDFONT_IMG, buffering);
			//DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], cvtDest, cvtLayer, GOLDFONT_IMG, buffering);
			//DrawGoldNum((atime % 3600) / 60, x + (float)180 * _2X * zoom, y, RIGHT, 2, false, false, zoom, cvtDest, cvtLayer, buffering);
			//DrawGoldAlpha(x + (float)182 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_M, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false, cvtDest, cvtLayer, buffering);

		}
		else if (atime >= 3600) {
			//00h:00m:00s
			DrawGoldNum(atime / 3600, x + (float)38 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)40 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_H, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum((atime % 3600) / 60, x + (float)108 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)110 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_M, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			//DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], cvtDest, cvtLayer, GOLDFONT_IMG, buffering);
			//DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], cvtDest, cvtLayer, GOLDFONT_IMG, buffering);
			//DrawGoldNum(atime % 60, x + (float)180 * _2X * zoom, y, RIGHT, 2, false, false, zoom, cvtDest, cvtLayer, buffering);
			//DrawGoldAlpha(x + (float)182 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_S, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false, cvtDest, cvtLayer, buffering);

		}
		else {
			//00m:00s:00
			DrawGoldNum(atime / 60, x + (float)38 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)40 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_M, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum(atime % 60, x + (float)108 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)110 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_S, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			//DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], cvtDest, cvtLayer, GOLDFONT_IMG, buffering);
			//DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], cvtDest, cvtLayer, GOLDFONT_IMG, buffering);
			//DrawGoldNum(frame % FPS, x + (float)180 * _2X * zoom, y, RIGHT, 2, false, false, zoom, cvtDest, cvtLayer, buffering);
			
			//DrawGoldAlpha(x + (float)177 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_S, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false, cvtDest, cvtLayer, buffering);

		}
		break;
	}
	//SetAlpha(16);
	/*
	switch (font) {
	default:
		if (atime >= 144000) {
			//00d:00h:00m
			DrawGoldNum(atime / 144000, x + (float)38 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)40 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_D, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum((atime % 144000) / 3600, x + (float)108 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)110 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_H, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum((atime % 3600) / 60, x + (float)180 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)182 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_M, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);

		}
		else if (atime >= 3600) {
			//00h:00m:00s
			DrawGoldNum(atime / 3600, x + (float)38 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)40 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_H, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum((atime % 3600) / 60, x + (float)108 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)110 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_M, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum(atime % 60, x + (float)180 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)182 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_S, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);

		}
		else {
			//00m:00s:00
			DrawGoldNum(atime / 60, x + (float)38 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)40 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_M, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawImage(17, 16, 207, 363, x + (float)62 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum(atime % 60, x + (float)108 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			DrawGoldAlpha(x + (float)110 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_S, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawImage(17, 16, 207, 363, x + (float)132 * _2X * zoom, y - (float)(11 * _2X) * zoom, false, false, false, false, false, zoom, sprite[GOLDFONT_IMG], GOLDFONT_IMG);
			DrawGoldNum(frame % FPS, x + (float)180 * _2X * zoom, y, RIGHT, 2, false, false, zoom);
			//DrawGoldAlpha(x + (float)177 * _2X * zoom, y - (float)(2 * _2X) * zoom, ALPHA_NUM_S, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false, cvtDest, cvtLayer, buffering);

		}
		break;
	}
	*/
}

void DrawDate(int x, int y, int atime, float zoom)
{
	struct tm* tm;
	time_t timep;

	timeval tv;
	gettimeofday(&tv, nullptr);
	timep = tv.tv_sec;

	tm = localtime(&timep);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int min = tm->tm_min;
	int second = tm->tm_sec;

	DrawNum(hour, x, y, FONT_SMALL, LEFT, 2, false, true, zoom, true);
	DrawAlpha(x + (float)(10 * _2X) * zoom, y, ALPHA_COLON, FONT_SMALL, zoom, false);
	DrawNum(min, x + (float)(15 * _2X) * zoom, y, FONT_SMALL, LEFT, 2, false, true, zoom, true);

	DrawNum(month, x + (float)(30 * _2X) * zoom, y, FONT_SMALL, LEFT, 2, false, true, zoom, true);
	DrawAlpha(x + (float)(40 * _2X) * zoom, y, ALPHA_SLA, FONT_SMALL, zoom, false);
	DrawNum(day, x + (float)(45 * _2X) * zoom, y, FONT_SMALL, LEFT, 2, false, true, zoom, true);

}

void DrawDateText(int x, int y, int atime, int type, float zoom)
{
	struct tm* tm;
	time_t timep;

	timeval tv;
	gettimeofday(&tv, nullptr);
	timep = tv.tv_sec;

	timep = atime;

	tm = localtime(&timep);
	int year = tm->tm_year + 1900;
	int month = tm->tm_mon + 1;
	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int min = tm->tm_min;
	int second = tm->tm_sec;
	//일
	DrawNum(day, x, y + (float)(1 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, 2, false, true, zoom, true);//초
	DrawText(TEXT_DAY, x + (float)(20 * _2X) * zoom, y, zoom);

	//�ð�
	DrawNum(hour, x + (float)(20 * _2X * 2) * zoom, y + (float)(1 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, 2, false, true, zoom, true);//초
	DrawText(TEXT_HOUR, x + (float)(20 * _2X * 3) * zoom, y, zoom);

	//분
	DrawText(TEXT_MINUTE, x + (float)(20 * _2X * 5) * zoom + (float)(10 * _2X) * zoom, y, zoom);

	//초
	DrawNum(second, x + (float)(20 * _2X * 6) * zoom + (float)(10 * _2X) * zoom, y + (float)(1 * _2X) * zoom, NUM_FONT_NORMAL, LEFT, 2, false, true, zoom, true);//초
	DrawText(TEXT_SECONDS, x + (float)(20 * _2X * 7) * zoom + (float)(10 * _2X) * zoom, y, zoom);
}

void PushButtonDraw(int betType, int x, int y, int motion, float zoom, bool autoPlayText)
{
	int MAXPUSHDOWN = AUTOPLAYFRAME;

	if (autoPlayText == true)
		if (autoPlay == false) {
			SetAlpha(32);
			CenterTextSolid(TEXT_ALPHA_HOLD, x + (float)0 * zoom, y - (float)16 * _2X * zoom, 0.8f * zoom);
			SetAlpha(32);
		}
		else {
			SetAlpha(32);
			CenterTextSolid(TEXT_STOP, x + (float)0 * zoom, y - (float)16 * _2X * zoom, 0.8f * zoom);
			SetAlpha(32);
		}
}

void DrawHand(int x, int y, int hFrame, float zoom)
{
	int imgIdx = IMG_HAND1 + (hFrame % 7 < 5 ? 0 : (hFrame % 7 - 4));

	DrawImage(imgArray[imgIdx * 4 + 2], imgArray[imgIdx * 4 + 3], imgArray[imgIdx * 4 + 0], imgArray[imgIdx * 4 + 1], x + (float)(hFrame % 7 < 5 ? 0 : (hFrame % 7 == 5 ? 1 : 0)) * _2X * zoom, y - (float)(hFrame % 7 < 5 ? 0 : (hFrame % 7 == 5 ? -4 : -3)) * _2X * zoom, false, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);
}
void YesNoDraw(int x, int y)
{
	DrawTouchLargeButton(x - 80 * _2X, y, 64 * _2X, 32 * _2X, textId[TEXT_YES], false, FRAME_GREEN, 1.0f);
	DrawTouchLargeButton(x + 16 * _2X, y, 64 * _2X, 32 * _2X, textId[TEXT_NO], false, FRAME_RED, 1.0f);

	switch (alert) {
	case ALERT_INVENFULL:
		SetRectPoint(x - 80 * _2X, y, 64 * _2X, 32 * _2X, TOUCH_ALERT_INVENTORYFULL_YES);
		SetRectPoint(x + 16 * _2X, y, 64 * _2X, 32 * _2X, TOUCH_ALERT_NO);
		break;
	case ALERT_SELL:
		SetRectPoint(x - 80 * _2X, y, 64 * _2X, 32 * _2X, TOUCH_ALERT_ITEMSELL);
		SetRectPoint(x + 16 * _2X, y, 64 * _2X, 32 * _2X, TOUCH_ALERT_NO);
		break;
	}
}

//�޴��� ���µǾ��� �� ���̶���Ʈ�� �ִ� 
void AccountDraw(int x, int y)
{

}

void PolicyDraw(int x, int y)
{

}

void CommunityDraw(int x, int y)
{

}

void DrawSelectBox(int x, int y, int hFrame, int grade)
{
	DrawSelect(x + 1 * _2X, y + 1 * _2X, 16 * _2X, 16 * _2X, grade);
	MemRectFrame(x, y, 18 * _2X, 18 * _2X, selectColor[hFrame % 4]);
}

void DrawEmptyBox(int x, int y, int w, int h)
{
	int i;
	MemRectBoth(x, y, w, h, 0x00295E, 0x000F34);
	for (i = 0; i < 4; i++)
		MemRect(x + (i % 2) * (w - 1 * _2X), y - (i / 2) * (h - 1 * _2X), 1 * _2X, 1 * _2X, 0x043B74);
}

void BoxInfoDraw(int boxType, int x, int y, float zoom)
{
	int i;
	int plusY = 32 * _2X;
	float width;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	DrawBox(boxType, x + (float)POPUPWINDOWSIZE_X / 2 * zoom, y + plusY - (float)64 * _2X * zoom, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], LEFT, false, true, false, true, 2.0f * zoom);
	CenterText(TEXT_ITEMNAME_BOX + boxType, x + (float)POPUPWINDOWSIZE_X / 2 * zoom, y + plusY - (float)72 * _2X * zoom, zoom);
	//DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 80 * _2X) / 2 * zoom, y - (float)88 * _2X * zoom, TEXT_ITEMNAME_BOX + boxType, zoom, cvtDest, cvtLayer, buffering);

	//골드
	MemRect(x + (float)12 * _2X * zoom, y + plusY - (float)140 * _2X * zoom + (float)24 * _2X * 2 * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(24 * _2X) * zoom, 0xFFFFFF);
	DrawRouletteNumIcon(GetBoxGold(boxType), ICON_GOLD, x + (float)16 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * 2) * zoom, false, LEFT, zoom);
	DrawPercent(boxDropPercent[boxType][BOXDROP_COIN], x + (float)292 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * 2 + 6 * _2X) * zoom, zoom, RIGHT);

	//골드백
	MemRect(x + (float)12 * _2X * zoom, y + plusY - (float)140 * _2X * zoom + (float)24 * _2X * 1 * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(24 * _2X) * zoom, 0xEEEEEE);
	width = DrawRouletteNumIcon(GetBoxGold(boxType), ICON_GOLD, x + (float)16 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * 1) * zoom, false, LEFT, zoom);
	DrawXNumGold(COINPER, x + (float)(12 + 8) * _2X * zoom + width, y + plusY - (float)144 * _2X * zoom + (float)24 * _2X * 1 * zoom, false, 0.6f * zoom, LEFT, false);
	DrawPercent(boxDropPercent[boxType][BOXDROP_COINBAG], x + (float)292 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * 1 + 6 * _2X) * zoom, zoom, RIGHT);

	//퀘스트 아이템
	MemRect(x + (float)12 * _2X * zoom, y + plusY - (float)140 * _2X * zoom + (float)24 * _2X * 0 * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(24 * _2X) * zoom, 0xFFFFFF);
	DrawRouletteNumIcon(GetBoxQuestItem(boxType), GetItemIcon(questRequestItem[robin.quest * 3 + 0], questRequestItem[robin.quest * 3 + 1], questRequestItem[robin.quest * 3 + 2]), x + (float)16 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * 0) * zoom, false, LEFT, zoom);
	DrawPercent(boxDropPercent[boxType][BOXDROP_QUESTITEM], x + (float)292 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * 0 + 6 * _2X) * zoom, zoom, RIGHT);

	//퀘스트 아이템 백
	MemRect(x + (float)12 * _2X * zoom, y + plusY - (float)140 * _2X * zoom + (float)24 * _2X * -1 * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(24 * _2X) * zoom, 0xEEEEEE);
	width = DrawRouletteNumIcon(GetBoxQuestItem(boxType), GetItemIcon(questRequestItem[robin.quest * 3 + 0], questRequestItem[robin.quest * 3 + 1], questRequestItem[robin.quest * 3 + 2]), x + (float)16 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * -1) * zoom, false, LEFT, zoom);
	DrawXNumGold(QUESTPER, x + (float)(12 + 8) * _2X * zoom + width, y + plusY - (float)144 * _2X * zoom + (float)24 * _2X * -1 * zoom, false, 0.6f * zoom, LEFT, false);
	DrawPercent(boxDropPercent[boxType][BOXDROP_QUESTITEMBAG], x + (float)292 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * -1 + 6 * _2X) * zoom, zoom, RIGHT);

	//하트 아이템
	MemRect(x + (float)12 * _2X * zoom, y + plusY - (float)140 * _2X * zoom + (float)24 * _2X * -2 * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(24 * _2X) * zoom, 0xFFFFFF);
	DrawRouletteNumIcon(GetBoxHeartItem(boxType), ICON_HEART, x + (float)16 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * -2) * zoom, false, LEFT, zoom);
	DrawPercent(boxDropPercent[boxType][BOXDROP_HEART], x + (float)292 * _2X * zoom, y + plusY - (float)(142 * _2X - 24 * _2X * -2 + 6 * _2X) * zoom, zoom, RIGHT);

	//
	//for (i = 0; i < STAR10 + 1; i++) {
	//	MemRect(x + (float)12 * _2X * zoom, y + plusY - (float)140 * _2X * zoom - (float)24 * _2X * (i + 3) * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(24 * _2X) * zoom, i % 2 == 1 ? 0xFFFFFF : 0xEEEEEE, cvtDest, cvtLayer, buffering);
	//	if (boxDropPercent[boxType][BOXDROP_STAR1 + i] == 0)
	//		grayScale = 32;
	//	DrawStar(ICON_STAR, x + (float)16 * _2X * zoom, y + plusY - (float)148 * _2X * zoom - (float)24 * _2X * (i + 3) * zoom, boxStar[boxType * 2] + 1 + i, boxStar[boxType * 2] + 1 + i, LEFT, false, zoom, cvtDest, cvtLayer, buffering);
	//	grayScale = 0;
	//	DrawPercent(boxDropPercent[boxType][BOXDROP_STAR1 + i], x + (float)292 * _2X * zoom, y + plusY - (float)148 * _2X * zoom - (float)24 * _2X * (i + 3) * zoom, zoom, RIGHT, cvtDest, cvtLayer, buffering);

	//}
}

void DrawBox(int boxType, int x, int y, int dirX, int motion, int solid, bool ani, bool opened, bool shadow, float zoom)
{
	if (shadow) {
		switch (boxType) {
		default:
			ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x - (float)40 * _2X / 2 * zoom, y + (float)12 * _2X * zoom, SHADOW_IMG, zoom);
			break;
		case BOX_CASTLE0:
		case BOX_CASTLE1:
		case BOX_CASTLE2:
		case BOX_CASTLE3:
		case BOX_CASTLE4:
		case BOX_CASTLE5:
		case BOX_CASTLE6:
		case BOX_CASTLE7:
		case BOX_CASTLE8:
		case BOX_CASTLE9:
		case BOX_CASTLE10:
		case BOX_CASTLE11:
		case BOX_CASTLE12:
		case BOX_CASTLE13:
		case BOX_CASTLE14:
		case BOX_CASTLE15:
		case BOX_CASTLE16:
		case BOX_CASTLE17:
		case BOX_CASTLE18:

		case BOX_REWARD0:
		case BOX_REWARD1:
		case BOX_REWARD2:
		case BOX_REWARD3:
		case BOX_REWARD4:
		case BOX_REWARD5:
		case BOX_REWARD6:
		case BOX_REWARD7:
			ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x - (float)40 * _2X / 2 * zoom, y + (float)12 * _2X * zoom, SHADOW_IMG, 2.0f * zoom);
			break;
		}
	}

	switch (boxType) {
	case BOX_INGAME:
		DrawNeutral(OBJ_BOX0 + motion, x, y, dirX, zoom);
		break;
	default:
		/*
	case BOX_CASTLE0:
	case BOX_CASTLE1:
	case BOX_CASTLE2:
	case BOX_CASTLE3:
	case BOX_CASTLE4:
	case BOX_CASTLE5:
	case BOX_CASTLE6:
	case BOX_CASTLE7:
	case BOX_CASTLE8:
	case BOX_CASTLE9:
	case BOX_CASTLE10:
	case BOX_CASTLE11:
	case BOX_CASTLE12:
	case BOX_CASTLE13:
	case BOX_CASTLE14:
	case BOX_CASTLE15:
	case BOX_CASTLE16:
	case BOX_CASTLE17:
	case BOX_CASTLE18:

	case BOX_REWARD0:
	case BOX_REWARD1:
	case BOX_REWARD2:
	case BOX_REWARD3:
	case BOX_REWARD4:
	case BOX_REWARD5:
	case BOX_REWARD6:
	case BOX_REWARD7:
	*/
		DrawCastleBoxXY(boxType, motion == BOXSTATUS_OPENED ? true : false, dirX, x - (float)512 * zoom / 2, y + (float)512 * zoom, itemColor[frame % 6], zoom);
		break;
	}
}

void OpenBox(OBJECT* pObj)
{
	if (pObj->motion == BOXSTATUS_CLOSED)
	{
		pObj->motion = BOXSTATUS_OPENING;
		pObj->frame = 0;
	}
}

void CloseBox(OBJECT* pObj)
{
	if (pObj->status == BOXSTATUS_OPENED)
	{
		pObj->status = BOXSTATUS_CLOSING;
		pObj->frame = 0;
	}
}

float EaseOutBack(float t)
{
	float c1 = 1.70158f;
	float c3 = c1 + 1.0f;

	t = t - 1.0f;
	return 1.0f + c3 * t * t * t + c1 * t * t;
}

float Clamp01(float v)
{
	if (v < 0.0f) return 0.0f;
	if (v > 1.0f) return 1.0f;
	return v;
}

void DrawCastleBoxXY(int index, bool opened, int dirX, int x, int y, int color, float zoom)
{
	int i;
	int img = BOX0_IMG + index - BOX_CASTLE0;

	SetAlpha(32 - Abs(frame / 2 % 32 - 16));
	SetColor(color);

	for (i = 0; i < 4; i++)
	{
		DrawImage(
			512,
			512,
			opened == true ? 512 : 0,
			0,
			x + solidPosition[i * 2 + 0] * 3,
			y + solidPosition[i * 2 + 1] * 3,
			1 - dirX,
			false,
			false,
			false,
			false,
			zoom,
			sprite[img],
			img);
	}

	SetAlpha(32);
	SetColor(false);

	DrawImage(
		512,
		512,
		opened == true ? 512 : 0,
		0,
		x,
		y,
		1 - dirX,
		false,
		false,
		false,
		false,
		zoom,
		sprite[img],
		img);

}

void DrawCastleBox(OBJECT* pObj)
{
	int i;
	int img = BOX0_IMG + pObj->etc - BOX_CASTLE0;

	bool openedImage = false;

	float drawZoom = pObj->zoom;
	float shakeX = 0;
	float shakeY = 0;
	int color;

	switch (pObj->motion)
	{
	case BOXSTATUS_OPENED:
		openedImage = true;
		break;

	case BOXSTATUS_OPENING:
		if (pObj->frame < 3)
		{
			openedImage = false;
			shakeX = ((pObj->frame & 1) ? 3 : -3) * _2X;
		}
		else if (pObj->frame < BOX_OPEN_CHANGE_FRAME)
		{
			openedImage = false;

			float t = (float)(pObj->frame - 3) / (float)(BOX_OPEN_CHANGE_FRAME - 3);
			drawZoom = pObj->zoom * (1.0f + 0.08f * t);
		}
		else
		{
			openedImage = true;

			float t = (float)(pObj->frame - BOX_OPEN_CHANGE_FRAME) / (float)(BOX_OPEN_FRAME - BOX_OPEN_CHANGE_FRAME);
			drawZoom = pObj->zoom * (1.08f - 0.08f * t);
		}
		break;

	case BOXSTATUS_CLOSING:
		if (pObj->frame < BOX_CLOSE_FRAME / 2)
		{
			openedImage = true;

			float t = (float)pObj->frame / (float)(BOX_CLOSE_FRAME / 2);
			drawZoom = pObj->zoom * (1.0f + 0.04f * t);
		}
		else
		{
			openedImage = false;

			float t = (float)(pObj->frame - BOX_CLOSE_FRAME / 2) / (float)(BOX_CLOSE_FRAME / 2);
			drawZoom = pObj->zoom * (1.04f - 0.04f * t);
		}
		break;

	case BOXSTATUS_APPEAR:
	case BOXSTATUS_CLOSED:
	default:
		openedImage = false;
		break;
	}

	float drawX =
		xOffset + pObj->x
		- (float)512 / 2 * drawZoom
		- rx
		+ shakeX;

	float drawY =
		STATUSWIN_Y + (rh - 4) * TSIZE
		- ry
		- (pObj->y - (float)512 * drawZoom - OBJIMGGAP + 16)
		+ shakeY;

	switch (pObj->etc)
	{
	default:
		color = castleBoxColor[castleOrder[robin.castle]];
		break;

	case BOX_CASTLE15:
	case BOX_CASTLE16:
	case BOX_CASTLE17:
	case BOX_CASTLE18:

	case BOX_REWARD0:
	case BOX_REWARD1:
	case BOX_REWARD2:
	case BOX_REWARD3:
	case BOX_REWARD4:
	case BOX_REWARD5:
	case BOX_REWARD6:
	case BOX_REWARD7:
		color = itemColor[frame % 10];
		break;
	}

	
	if (pObj->motion == BOXSTATUS_OPENING)
	{
		pObj->frame++;

		if (pObj->frame >= BOX_OPEN_FRAME)
		{
			pObj->frame = 0;
			pObj->motion = BOXSTATUS_OPENED;
		}
	}
	else if (pObj->motion == BOXSTATUS_CLOSING)
	{
		pObj->frame++;

		if (pObj->frame >= BOX_CLOSE_FRAME)
		{
			pObj->frame = 0;
			pObj->motion = BOXSTATUS_CLOSED;
		}
	}

	DrawCastleBoxXY(pObj->etc, openedImage, pObj->dirX, drawX, drawY, color, pObj->zoom);
}

void BoxDraw(OBJECT* pObj)
{
	int i;
	switch (pObj->etc) {
	case BOX_INGAME:
		DrawNeutral(OBJ_BOX0 + pObj->motion, xOffset + pObj->x, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - OBJIMGGAP), pObj->dirX, pObj->zoom);
		break;
	default:
	/*
	case BOX_CASTLE0:
	case BOX_CASTLE1:
	case BOX_CASTLE2:
	case BOX_CASTLE3:
	case BOX_CASTLE4:
	case BOX_CASTLE5:
	case BOX_CASTLE6:
	case BOX_CASTLE7:
	case BOX_CASTLE8:
	case BOX_CASTLE9:
	case BOX_CASTLE10:
	case BOX_CASTLE11:
	case BOX_CASTLE12:
	case BOX_CASTLE13:
	case BOX_CASTLE14:
	case BOX_CASTLE15:
	case BOX_CASTLE16:
	case BOX_CASTLE17:
	case BOX_CASTLE18:

	case BOX_REWARD0:
	case BOX_REWARD1:
	case BOX_REWARD2:
	case BOX_REWARD3:
	case BOX_REWARD4:
	case BOX_REWARD5:
	case BOX_REWARD6:
	case BOX_REWARD7:
	*/
		DrawCastleBox(pObj);
		break;
	}
}