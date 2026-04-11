#include "Core.h"
#include "Func.h"
#include "Data.h"
#include "Text.h"

// Text Handling
int StringLength(const char* str)
{
	int i, rtn = 0, byte_len = strlen(str);

	for (i = 0; i < byte_len; i++) {
		rtn++;

		if (str[i] < 0 || str[i] > 127)
			i++;
	}

	return rtn;
}

int SubstringLength(const char* str, unsigned int offset, unsigned int length)
{
	unsigned int i, byte_len;
	int wide = 0, rtn = 0;

	for (i = 0; i < offset; i++) {
		if (str[i] < 0 || str[i] > 127)
			wide = 1 - wide;
	}

	offset = offset - wide;
	byte_len = Min(offset + length, strlen(str));

	for (i = offset; i < byte_len; i++) {
		if (str[i] == '|')
			i++;
		else
			rtn++;

		if (str[i] < 0 || str[i] > 127) {
			wide = 1 - wide;
			i++;
		}
	}

	return rtn - wide;
}

float StringWidthTTF(const char* str, float zoom)
{
	Size textSize;
	float width;

	fontLabelWidth = Label::createWithTTF(str, "fonts/font.ttf", FONT_HEIGHT + 1 * _2X);
	textSize = fontLabelWidth->getContentSize();
	width = textSize.width;
	//fontLabelWidth->release();
	return width;
}
//문자열의 길이 리턴
float StringWidth(const char* str, float zoom)
{
	int i, rtn = 0, byte_len = strlen(str);

	for (i = 0; i < byte_len; i++) {
		if (str[i] < 0 || str[i] > 127) {
			rtn += NEXT_FONT_WIDTH;
			i++;
		}
		else if (str[i] == '@')
			continue;
		else if (str[i] == '|')
			i++;
		else
			rtn += NEXT_ALPHAFONT_WIDTH;
	}

	return (float)(rtn + 2 * _2X) * zoom;
}

//서브문자열의 길이 리턴
float SubstringWidth(const char* str, int offset, int length, float zoom)
{
	int i, byte_len, rtn = 0;
	int start = 0, end, wide = 0;

	for (i = 0; i < offset; i++, start++) {
		if (str[start] < 0 || str[start] > 127) {
			if (wide == 0)
				i--;

			wide = 1 - wide;
		}
	}

	start -= wide;
	byte_len = Min(offset + length, StringLength(str));

	for (i = offset, end = start; i < byte_len; i++, end++) {
		if (str[end] < 0 || str[end] > 127) {
			rtn += NEXT_FONT_WIDTH;
			end++;
		}
		else if (str[end] == '|') {
			end++;
			i++;
		}
		else
			rtn += NEXT_ALPHAFONT_WIDTH;
	}

	return (float)(rtn + 2 * _2X) * zoom;
}

void ResetLabel()
{
	int i;

	for (i = 0; i < curFontLabelCnt; i++) {
		curScene->removeChild(fontLabel[i]);
	}
	curFontLabelCnt = 0;

	for (i = 0; i < totalFontLabelCnt; i++) {
		fontLabel[i]->release();
	}
	totalFontLabelCnt = 0;


	memset(&fontLabelIndex, -1, sizeof(fontLabelIndex));
	memset(&fontLabelMotherIndex, -1, sizeof(fontLabelMotherIndex));
	memset(&sameFontLabelMax, 0, sizeof(sameFontLabelMax));
	memset(&sameFontLabelCur, 0, sizeof(sameFontLabelCur));
	memset(&sameFontLabelArr, 0, sizeof(sameFontLabelArr));
	memset(&curFontLabelArr, 0, sizeof(curFontLabelArr));

}

void EraiseColorFont(const char* str)
{
	int i;
	int length = strlen(str);
	int offset = 0;
	int cursor = 0;

	//일단 폰트 컬러데이터를 현재 폰트 컬러로 바꿔주고
	//for (i = 0; i < 256; i++)
	//	bmFontColor[i] = fontColor;
	memset(&bmFontColor, fontColor, sizeof(bmFontColor));
	//색상기호나 줄바꿈 기호를 짤라내고 남은 텍스트가 담길 공간
	memset(&labelStr, 0, sizeof(labelStr));

	//문자열의 길이
	for (i = 0; i < length; i++, offset++) {
		//ASCII 문자면
		if (str[offset] >= 0 && str[offset] <= 127) {

			//만약 '|'가 나왔으면
			if (fontInfo[str[offset]] == 127) {
				//'|' 다음 나오는 알파벳을 기준으로 폰트색을 정하고
				ParseText(str[offset + 1]);

				//'|'와 알파벳을 제거한다.
				offset++;
				i++;
			}
			else {
				//각 글자마다 폰트색상을 정해준다.
				bmFontColor[cursor] = fontColor;

				labelStr[cursor] = str[offset];
				cursor++;
			}

		}
		//한글이면
		else {
			bmFontColor[cursor] = fontColor;
			bmFontColor[cursor + 1] = fontColor;
			labelStr[cursor] = str[offset];
			labelStr[cursor + 1] = str[offset + 1];

			cursor += 2;

			offset++;
			i++;
		}
	}

}

//처음 같은 문자열을 가진 라벨 인덱스를 리턴
int GetSameStringIndex(const char* str)
{
	int i;

	//일단 텍스트를 labelStr에다가 넣고 스트링형태로 바꾼 다음에
	memset(&labelStr2, 0, sizeof(labelStr2));
	TextToString(labelStr, strlen(labelStr), (char*)&labelStr2);

	//해당 텍스트에 대해서 같은 텍스트가 있는지 점검
	for (i = 0; i < totalFontLabelCnt; i++) {
		labelString = fontLabel[i]->getString();
		//문자열이 같으면
		if (!strcmp(labelString.c_str(), labelStr2))
		{
			return i;
		}
	}

	return i;
}


//현재 기로딩되어 있는것 포함해서 몇번 인덱스를 써야 되는지 
int GetFontLabelIndex(const char* str)
{
	int i;
	int index;
	int j = 0;

	//처음 같은 문자열을 가진 라벨 인덱스를 리턴
	index = GetSameStringIndex(str);

	if (sameFontLabelCur[index] < sameFontLabelMax[index]) {
		for (i = 0; i < MAXFONTLABELCNT; i++) {
			//fontLabelIndex는 몇번 라벨의 값을 가졌는지 그 몇번을 저장한다.
			if (fontLabelMotherIndex[i] == index) {
				j++;
				if (j > sameFontLabelCur[index]) {
					if (i < totalFontLabelCnt) {
						sameFontLabelArr[index][sameFontLabelCur[index]] = i;
						sameFontLabelCur[index]++;
						getFontLabelIdx = i;
						return i;
					}
					else {
						getFontLabelIdx = totalFontLabelCnt;
						return totalFontLabelCnt;
					}
				}
			}
		}
	}
	else {
		getFontLabelIdx = totalFontLabelCnt;
		return totalFontLabelCnt;
	}
	return false;
}

void LoadFontLabelFromText(const char* str)
{
	int length = strlen(str);
	int offset = 0;
	int cursor = 0;
	int fontIdx;

	fontIdx = GetSameStringIndex(str);
	getFontLabelIdx = GetFontLabelIndex(str);


	if (getFontLabelIdx == totalFontLabelCnt) {

		//str으로 변환할 char 배열을 labelStr2로 하고 초기화한다.
		memset(&labelStr2, 0, sizeof(labelStr2));
		//str으로 변환할 char 배열을 labelStr2로 하고 초기화한다.
		TextToString((char*)&labelStr, strlen(labelStr), (char*)&labelStr2);

		fontLabel[getFontLabelIdx] = Label::createWithTTF(labelStr2, "fonts/font.ttf", FONT_HEIGHT + 1 * _2X);
		fontLabel[getFontLabelIdx]->retain();
		fontLabelIndex[getFontLabelIdx] = getFontLabelIdx;
		fontLabelMotherIndex[getFontLabelIdx] = fontIdx;

		sameFontLabelArr[fontIdx][sameFontLabelCur[fontIdx]] = totalFontLabelCnt;
		sameFontLabelCur[fontIdx]++;
		sameFontLabelMax[fontIdx]++;

		curFontLabelArr[curFontLabelCnt] = getFontLabelIdx;
		curFontLabelCnt++;

		totalFontLabelCnt++;
	}
	else {

		curFontLabelArr[curFontLabelCnt] = getFontLabelIdx;
		curFontLabelCnt++;
	}

	fontLabel[getFontLabelIdx]->setOpacity((int)(m_lgrpAlpha * EMPTY / 32));
	fontLabel[getFontLabelIdx]->setRotation(0);
}


float DrawTextSystem(int index, int x, int y, float zoom, int align, bool bold, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float width;
	width = DrawTextStrSystem(textId[index], x, y, zoom, align, bold, cvtDest, cvtLayer, buffering);
	return width;
}

float DrawTextStrSystem(const char* str, int x, int y, float zoom, int align, bool bold, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	int length;
	int offset = 0;
	int cursor = 0;
	float w = StringWidth(str, zoom);
	float h = FONT_HEIGHT * zoom;
	int xs = 0;
	int ys = 0;
	int fontColorBack = fontColor;
	Size textSize;


#ifdef CLIPPING
	//if (x + w < clipX || x > clipX2 || y > clipY || y < clipY2)
	//	return false;
#endif

	//y += 2 * zoom * _2X;
	if (bold) {
		//x += 2 * zoom * _2X;
		y += 2 * zoom * _2X;
	}

	cocos2d::Label* src;

	EraiseColorFont(str);

	LoadFontLabelFromText(labelStr);
	src = fontLabel[getFontLabelIdx];
	length = strlen(labelStr);
	textSize = src->getContentSize();

	switch (align) {
	case LEFT:
		src->setAnchorPoint(Vec2(0, 1.0f));
		break;
	case CENTER:
		src->setAnchorPoint(Vec2(0.5f, 1.0f));
		break;
	case RIGHT:
		src->setAnchorPoint(Vec2(1.0f, 1.0f));
		break;
	}
	src->setColor(Color3B((fontColor >> 16) & 0xFF, (fontColor >> 8) & 0xFF, fontColor & 0xFF));
	src->setScale(zoom * 1.0f, zoom * 1.0f);
	//src->setScale(zoom * 1.0f, zoom * 1.0f);
	src->setPosition(Vec2(x, y));

	//src->setVisible(true);

	//if (grayScale)
	//	src->setGLProgram(GLProgramCache::getInstance()->getGLProgram("grayscale"));


	if (bold)
		src->enableOutline(Color4B::BLACK, 1.8f);
	else
		src->enableOutline(Color4B::BLACK, 0);

	for (i = 0; i < length; i++) {

		//ASCII 문자면
		if (labelStr[i] >= 0 && labelStr[i] <= 127) {
			if (labelStr[i] != 32)
				fontLabel[getFontLabelIdx]->getLetter(offset)->setColor(Color3B((bmFontColor[i] >> 16) & 0xFF, (bmFontColor[i] >> 8) & 0xFF, bmFontColor[i] & 0xFF));

			offset++;
		}
		//한글이면
		else {
			fontLabel[getFontLabelIdx]->getLetter(offset)->setColor(Color3B((bmFontColor[i] >> 16) & 0xFF, (bmFontColor[i] >> 8) & 0xFF, bmFontColor[i] & 0xFF));

			offset++;
			i++;
		}
	}

	if (buffering) {
		if (getFontLabelIdx == totalFontLabelCnt)
			cvtLayer->addChild(src);
		cvtDest->begin();

		src->visit(renderer, parentTransform, true);
		cvtDest->end();

		renderer->render();
	}
	else {
		curScene->addChild(src);
	}

	glBlendEquation(GL_FUNC_ADD);

	SetFontColor(fontColorBack);

	return textSize.width;
}

void DrawText(int index, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
#ifdef TTFFONT
	DrawTextStrSystem(textId[index], x, y, zoom, LEFT, true, cvtDest, cvtLayer, buffering);
#else
	DrawTextStr(TEXTPTR(index), x, y, cvtDest, cvtLayer, buffering);
#endif
}

void DrawTextSolid(int index, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
#ifdef TTFFONT
	DrawTextStrSystem(textId[index], x, y, zoom, LEFT, false, cvtDest, cvtLayer, buffering);
#else

#endif
}

void DrawTextStr(const char* str, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawTextStrSystem(str, x, y, zoom, LEFT, true, cvtDest, cvtLayer, buffering);

}

void DrawSubText(const char* src, int offset, int length, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, byte_len, wide = 0;
	int start = 0, end;
	char subtext[100];

	memset(subtext, 0, 100);

	for (i = 0; i < offset; i++, start++) {
		if (src[start] < 0 || src[start] > 127) {
			if (wide == 0)
				i--;

			wide = 1 - wide;
		}
	}

	start -= wide;
	byte_len = Min(offset + length, StringLength(src));

	for (i = offset, end = start; i < byte_len; i++, end++) {
		if (src[end] < 0 || src[end] > 127)
			end++;
	}

	strncpy(subtext, src + start, end - start);
#ifdef TTFFONT
	DrawTextStrSystem(subtext, x, y, zoom, LEFT, true, cvtDest, cvtLayer, buffering);
#else
	DrawCharsZoom(subtext, 0, strlen(subtext), x, y, zoom, cvtDest, cvtLayer, buffering);
#endif
}

void DrawSubTextSolid(const char* src, int offset, int length, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, byte_len, wide = 0;
	int start = 0, end;
	char subtext[100];

	memset(subtext, 0, 100);

	for (i = 0; i < offset; i++, start++) {
		if (src[start] < 0 || src[start] > 127) {
			if (wide == 0)
				i--;

			wide = 1 - wide;
		}
	}

	start -= wide;
	byte_len = Min(offset + length, StringLength(src));

	for (i = offset, end = start; i < byte_len; i++, end++) {
		if (src[end] < 0 || src[end] > 127)
			end++;
	}

	strncpy(subtext, src + start, end - start);
#ifdef TTFFONT
	DrawTextStrSystem(subtext, x, y, zoom, LEFT, false, cvtDest, cvtLayer, buffering);
#else
	DrawCharsSolid(subtext, 0, strlen(subtext), x, y, cvtDest, cvtLayer, buffering);
#endif
}

float CenterText(int index, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float rtn;

	rtn = StringWidth(TEXTPTR(index), zoom);
#ifdef TTFFONT
	DrawTextStrSystem(TEXTPTR(index), x, y, zoom, CENTER, true, cvtDest, cvtLayer, buffering);
#else
	DrawTextStr(TEXTPTR(index), x - rtn / 2, y, cvtDest, cvtLayer, buffering);
#endif

	return rtn;
}

float CenterTextSolid(int index, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float rtn;

	rtn = StringWidth(TEXTPTR(index), zoom);

#ifdef TTFFONT
	DrawTextStrSystem(TEXTPTR(index), x, y, zoom, CENTER, false, cvtDest, cvtLayer, buffering);
#else

#endif

	return rtn;
}

float CenterTextStr(const char* str, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float rtn = StringWidth(str, zoom);

#ifdef TTFFONT
	DrawTextStrSystem(str, x, y, zoom, CENTER, true, cvtDest, cvtLayer, buffering);
#else
	DrawTextStr(str, x - rtn / 2, y, cvtDest, cvtLayer, buffering);
#endif

	return rtn;
}

float CenterTextStrSolid(const char* str, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float rtn = StringWidth(str, zoom);

#ifdef TTFFONT
	DrawTextStrSystem(str, x, y, zoom, CENTER, false, cvtDest, cvtLayer, buffering);
#else

#endif
	return rtn;
}

void FrameText(const char* str, int x, int y, int dx, int line, int page, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int len = Min(textFrame, StringLength(str)) - (page == 0 ? 0 : textStringLength[page - 1]);
	int i, cnt, ofs, wide = 0;

	if (!str)
		return;

	str += textStringOffset[page];
	ParseText(textStartColor[page]);

	for (i = 0, cnt = 0, ofs = 0; i < len; i++) {
		if (SubstringWidth(str, ofs, i - ofs, zoom) > dx - (float)(cnt % 3 == 2 ? 18 * _2X : 9 * _2X) * zoom || strcmp(str, "@") == 0) {
			if (cnt < line)
				DrawSubText(str, ofs, i - ofs, x, y + (float)cnt * 13 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

			ofs = i;
			cnt++;

			if (str[i + wide] == ' ') {
				ofs++;
				i++;
			}
			else if (str[i + wide] == '@')
				ofs++;
		}

		if (str[+wide] < 0 || str[i + wide] > 127)
			wide++;
	}

	if (cnt < line)
		DrawSubText(str, ofs, len - ofs, x, y + (float)cnt * 13 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	if (textFrame < textStringLength[page]) {
		textFrame++;
	}
}

int ParseText(char str)
{
	if (str == '0')
		return 40 * _2X;

	switch (str) {
	case 'a':
		//검정색
		oldColor = fontColor;
		fontColor = 0x111111;
		break;
	case 'b':
		//흰색
		oldColor = fontColor;
		fontColor = COLOR_WHITE;
		break;
	case 'c':
		//빨간색
		oldColor = fontColor;
		fontColor = 0xFF0000;
		break;
	case 'd':
		//노란색
		oldColor = fontColor;
		fontColor = 0xFFFF00;
		break;
	case 'e':
		//초록색
		oldColor = fontColor;
		fontColor = 0x66CC66;
		break;
	case 'f':
		//파란색
		oldColor = fontColor;
		fontColor = 0x0000FF;
		break;
	case 'g':
		//보라색
		oldColor = fontColor;
		fontColor = 0xCC33FF;
		break;
	case 'h':
		//주황색
		oldColor = fontColor;
		fontColor = 0xEFA536;
		break;
	case 'i':
		//파란색
		oldColor = fontColor;
		fontColor = 0x3399FF;
		break;
	case 'j':
		//회색
		oldColor = fontColor;
		fontColor = 0x999999;
		break;
	case 'k':
		//연주황
		oldColor = fontColor;
		fontColor = 0xFFCC66;
		break;
	case 'l':
		//번개속성
		oldColor = fontColor;
		fontColor = 0xAA6688;
		break;
	case 'm':
		//신성속성
		oldColor = fontColor;
		fontColor = 0xFFFFAA;
		break;
	case 'n':
		//지역명
		oldColor = fontColor;
		fontColor = 0xFF8800;
		break;
	case 'o':
		//캐릭터이름명
		oldColor = fontColor;
		fontColor = 0xFFAAFF;
		break;
	case 'p':
		//아이템명
		oldColor = fontColor;
		fontColor = 0xAAFF00;
		break;
	case 'q':
		//그라데이션 폰트(퀘스트용)
	{
		fontColor = fontGradiation[frame % 21];
	}
	break;
	case 'r':
		//연분홍
		oldColor = fontColor;
		fontColor = 0xFFAACC;
		break;
	case 's':
		//이전으로 복귀
		fontColor = oldColor;
		break;
	default:
		oldColor = fontColor;
		fontColor = COLOR_WHITE;
		break;
	}

	return 0;
}

int LineText(int index, int x, int y, int width, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	return LineTextStr(TEXTPTR(index), x, y, width, -1, -1, zoom, cvtDest, cvtLayer, buffering);
}

int LineTextSolid(int index, int x, int y, int width, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	return LineTextStrSolid(TEXTPTR(index), x, y, width, -1, -1, zoom, cvtDest, cvtLayer, buffering);
}

int LineTextStr(const char* str, int x, int y, int dx, int lines, int lines2, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{

	int i, cnt, ofs, end, wide = 0;

	if (!str)
		return 0;

	end = StringLength(str);
	for (i = 0, cnt = 0, ofs = 0; i < end; i++) {
		if (SubstringWidth(str, ofs, i - ofs, zoom) > dx - (float)(NEXT_FONT_WIDTH - 1 * _2X) * zoom || str[i + wide] == '@') {
			if ((lines < 0 || cnt >= lines) && (lines2 < 0 || cnt < lines2))
				DrawSubText(str, ofs, i - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * FONT_HEIGHT_LINE * zoom, zoom, cvtDest, cvtLayer, buffering);

			ofs = i;
			cnt++;

			if (str[i + wide] == ' ') {
				ofs++;
				i++;
			}
			else if (str[i + wide] == '@')
				ofs++;
		}

		if (str[i + wide] < 0 || str[i + wide] > 127)
			wide++;
	}

	if ((lines < 0 || cnt >= lines) && (lines2 < 0 || cnt < lines2))
		DrawSubText(str, ofs, end - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * FONT_HEIGHT_LINE * zoom, zoom, cvtDest, cvtLayer, buffering);


	return cnt + 1;

}

int LineTextStrSolid(const char* str, int x, int y, int dx, int lines, int lines2, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{

	int i, cnt, ofs, end, wide = 0;

	if (!str)
		return 0;

	end = StringLength(str);
	for (i = 0, cnt = 0, ofs = 0; i < end; i++) {
		if (SubstringWidth(str, ofs, i - ofs, zoom) > dx - (float)(NEXT_FONT_WIDTH - 1 * _2X) * zoom || str[i + wide] == '@') {
			if ((lines < 0 || cnt >= lines) && (lines2 < 0 || cnt < lines2))
				DrawSubTextSolid(str, ofs, i - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * (FONT_HEIGHT_LINE - 1 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

			ofs = i;
			cnt++;

			if (str[i + wide] == ' ') {
				ofs++;
				i++;
			}
			else if (str[i + wide] == '@')
				ofs++;
		}

		if (str[i + wide] < 0 || str[i + wide] > 127)
			wide++;
	}

	if ((lines < 0 || cnt >= lines) && (lines2 < 0 || cnt < lines2))
		DrawSubTextSolid(str, ofs, end - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * (FONT_HEIGHT_LINE - 1 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

	return cnt + 1;

}

int CenterLineText(const char* str, int x, int y, int dx, int type, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{

	int i, cnt, ofs, wide = 0, w;
	float end;

	if (!str)
		return 0;

	end = StringWidth(str, zoom);
	dx = Min(dx, (end + 20 * _2X) * zoom / (end / dx + 1));
	end = StringLength(str);

	for (i = 0, cnt = 0, ofs = 0; i < end; i++) {
		w = SubstringWidth(str, ofs, i - ofs, zoom);

		if (w > dx - (float)(NEXT_FONT_WIDTH - 1 * _2X) * zoom || str[i + wide] == '@') {
			DrawSubText(str, ofs, i - ofs, x - ((type) ? w : dx) / 2, y - (float)(cnt * FONT_HEIGHT_LINE) * zoom, zoom, cvtDest, cvtLayer, buffering);
			ofs = i;
			cnt++;

			if (str[i + wide] == ' ') {
				ofs++;
				i++;
			}
			else if (str[i + wide] == '@')
				ofs++;
		}

		if (str[i + wide] < 0 || str[i + wide] > 127)
			wide++;
	}

	DrawSubText(str, ofs, end - ofs, x - (float)((type) ? SubstringWidth(str, ofs, end - ofs, zoom) : dx) / 2, y - (float)(cnt * FONT_HEIGHT_LINE) * zoom, zoom, cvtDest, cvtLayer, buffering);

	return cnt + 1;
}

void SetFrameText(int index, int dx, int line, float zoom)
{
	SetFrameTextStr(textId[index], dx, line, zoom, COLOR_BLACK);
}

void SetFrameTextStr(const char* str, int dx, int line, float zoom, char startCol)
{
	int i, cnt, ofs, end, wide = 0;
	char color;

	textString = str;
	end = StringLength(textString);
	textPage = 0;
	color = startCol;
	textStartColor[0] = startCol;
	textStringOffset[0] = 0;

	for (i = 0, cnt = 1, ofs = 0; i < end; i++) {
		if (SubstringWidth(textString, ofs, i - ofs, zoom) > dx - (float)(cnt % 3 == 0 ? 18 : 9) * _2X * zoom || textString[i + wide] == '@') {
			ofs = i;
			cnt++;

			if (textString[i + wide] == ' ') {
				ofs++;
				i++;

				textStringLength[textPage] = i;
			}
			else if (textString[i + wide] == '@') {
				i++;
				ofs++;

				textStringLength[textPage] = i - 1;
			}

			textPage++;
			textStringOffset[textPage] = i + wide;
			textStartColor[textPage] = color;

		}

		if (textString[i + wide] < 0 || textString[i + wide] > 127)
			wide++;
		else if (textString[i + wide] == '|')
			color = textString[i + wide + 1];
	}

	textStringLength[textPage] = StringLength(textString);
	textPage++;
	textCurPage = 0;
	textFrame = 0;	//텍스트 프레임초기화
	textLines = line;
}

//특정 스트럭쳐를 특정 json파일로 작성하는 함수
//bool StructureToJson(rapidjson::Writer<rapidjson::StringBuffer> * writer)
bool StructureToJson(void* structure, std::string jsonFileName)
{
	return true;
}
//제이슨 파일을 스트럭쳐로 로딩하는 함수
bool JsonToStructure(void* structure, std::string jsonFileName)
{
	return true;
}

//파일을 읽기와 쓰기가 가능한 상태로 내용을 쓴다.
bool GameWriteFile(char* filename, char* buf, int size)
{
	std::string path = FileUtils::sharedFileUtils()->getWritablePath();
	path.append(filename);

	FILE* fp = fopen(path.c_str(), "wb");

	if (!fp) {
		//log("can not create file %s", path.c_str());
		return false;
	}

	fwrite(buf, sizeof(char), size, fp);
	//fputs(buf, fp);
	fclose(fp);
	return true;
}

//파일을 읽기전용으로 오픈한 후 내용을 읽어온다.
bool LoadFile(char* filename, char* buf, int size)
{
	std::string path = FileUtils::sharedFileUtils()->getWritablePath();
	path.append(filename);

	FILE* fp = fopen(path.c_str(), "rb");

	if (!fp) {
		//log("can not create file %s", path.c_str());
		return false;
	}

	fread(buf, sizeof(char), size, fp);
	//fgets(buf, size, fp);
	fclose(fp);
	return true;
}
