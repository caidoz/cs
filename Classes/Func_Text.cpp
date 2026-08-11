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
//¹®ÀÚ¿­ÀÇ ±æÀÌ ¸®ÅÏ
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

//¼­ºê¹®ÀÚ¿­ÀÇ ±æÀÌ ¸®ÅÏ
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

	//ÀÏ´Ü ÆùÆ® ÄÃ·¯µ¥ÀÌÅÍ¸¦ ÇöÀç ÆùÆ® ÄÃ·¯·Î ¹Ù²ãÁÖ°í
	//for (i = 0; i < 256; i++)
	//	bmFontColor[i] = fontColor;
	memset(&bmFontColor, fontColor, sizeof(bmFontColor));
	//»ö»ó±âÈ£³ª ÁÙ¹Ù²Þ ±âÈ£¸¦ Â©¶ó³»°í ³²Àº ÅØ½ºÆ®°¡ ´ã±æ °ø°£
	memset(&labelStr, 0, sizeof(labelStr));

	//¹®ÀÚ¿­ÀÇ ±æÀÌ
	for (i = 0; i < length; i++, offset++) {
		//ASCII ¹®ÀÚ¸é
		if (str[offset] >= 0 && str[offset] <= 127) {

			//ï¿½ï¿½ï¿½ï¿½ '|'ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
			if (fontInfo[str[offset]] == 127) {
				//'|' ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Äºï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ®ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ï°ï¿½
				ParseText(str[offset + 1]);

				//'|'ï¿½ï¿½ ï¿½ï¿½ï¿½Äºï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ñ´ï¿½.
				offset++;
				i++;
			}
			else {
				//°¢ ±ÛÀÚ¸¶´Ù ÆùÆ®»ö»óÀ» Á¤ÇØÁØ´Ù.
				bmFontColor[cursor] = fontColor;

				labelStr[cursor] = str[offset];
				cursor++;
			}

		}
		//ÇÑ±ÛÀÌ¸é
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

//Ã³À½ °°Àº ¹®ÀÚ¿­À» °¡Áø ¶óº§ ÀÎµ¦½º¸¦ ¸®ÅÏ
int GetSameStringIndex(const char* str)
{
	int i;

	//ï¿½Ï´ï¿½ ï¿½Ø½ï¿½Æ®ï¿½ï¿½ labelStrï¿½ï¿½ï¿½Ù°ï¿½ ï¿½Ö°ï¿½ ï¿½ï¿½Æ®ï¿½ï¿½ï¿½ï¿½ï¿½Â·ï¿½ ï¿½Ù²ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	memset(&labelStr2, 0, sizeof(labelStr2));
	TextToString(labelStr, strlen(labelStr), (char*)&labelStr2);

	//ï¿½Ø´ï¿½ ï¿½Ø½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½Ø¼ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ø½ï¿½Æ®ï¿½ï¿½ ï¿½Ö´ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	for (i = 0; i < totalFontLabelCnt; i++) {
		labelString = fontLabel[i]->getString();
		//¹®ÀÚ¿­ÀÌ °°À¸¸é
		if (!strcmp(labelString.c_str(), labelStr2))
		{
			return i;
		}
	}

	return i;
}


//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Îµï¿½ï¿½Ç¾ï¿½ ï¿½Ö´Â°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ø¼ï¿½ ï¿½ï¿½ï¿½ ï¿½Îµï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ ï¿½Ç´ï¿½ï¿½ï¿½ 
int GetFontLabelIndex(const char* str)
{
	int i;
	int index;
	int j = 0;

	//Ã³À½ °°Àº ¹®ÀÚ¿­À» °¡Áø ¶óº§ ÀÎµ¦½º¸¦ ¸®ÅÏ
	index = GetSameStringIndex(str);

	if (sameFontLabelCur[index] < sameFontLabelMax[index]) {
		for (i = 0; i < MAXFONTLABELCNT; i++) {
			//fontLabelIndex´Â ¸î¹ø ¶óº§ÀÇ °ªÀ» °¡Á³´ÂÁö ±× ¸î¹øÀ» ÀúÀåÇÑ´Ù.
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

		//strÀ¸·Î º¯È¯ÇÒ char ¹è¿­À» labelStr2·Î ÇÏ°í ÃÊ±âÈ­ÇÑ´Ù.
		memset(&labelStr2, 0, sizeof(labelStr2));
		//strÀ¸·Î º¯È¯ÇÒ char ¹è¿­À» labelStr2·Î ÇÏ°í ÃÊ±âÈ­ÇÑ´Ù.
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


float DrawTextSystem(int index, int x, int y, float zoom, int align, bool bold)
{
	float width;
	width = DrawTextStrSystem(textId[index], x, y, zoom, align, bold);
	return width;
}

float DrawTextStrSystem(const char* str, int x, int y, float zoom, int align, bool bold)
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
	if (x + w < clipX || x > clipX2 || y > clipY || y < clipY2)
		return false;
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

		//ASCII ¹®ÀÚ¸é
		if (labelStr[i] >= 0 && labelStr[i] <= 127) {
			if (labelStr[i] != 32)
				fontLabel[getFontLabelIdx]->getLetter(offset)->setColor(Color3B((bmFontColor[i] >> 16) & 0xFF, (bmFontColor[i] >> 8) & 0xFF, bmFontColor[i] & 0xFF));

			offset++;
		}
		//ÇÑ±ÛÀÌ¸é
		else {
			fontLabel[getFontLabelIdx]->getLetter(offset)->setColor(Color3B((bmFontColor[i] >> 16) & 0xFF, (bmFontColor[i] >> 8) & 0xFF, bmFontColor[i] & 0xFF));

			offset++;
			i++;
		}
	}

	//AfterSpriting() ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ô¾ï¿½: ï¿½ï¿½ï¿½ï¿½ Å¸ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ Å¸ï¿½Ù¿ï¿½ ï¿½Ù·ï¿½ ï¿½ï¿½ï¿½ï¿½Ï°ï¿½,
	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Ì´ï¿½ ï¿½ï¿½ï¿½Å½ï¿½ ï¿½ï¿½Î¸ï¿½ ï¿½ï¿½ï¿½ï¿½.
	if (gRenderTarget) {
		//Label ï¿½ï¿½ 3ï¿½ï¿½ï¿½ï¿½ visit ï¿½ï¿½ï¿½ï¿½ï¿½Îµå°¡ 0ï¿½ï¿½ï¿½ï¿½ Node::visit() ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ç·ï¿½ Node* ï¿½ï¿½ ï¿½Þ¾ï¿½ È£ï¿½ï¿½ï¿½Ñ´ï¿½.
		cocos2d::Node* node = src;
		node->visit();
	}
	else
		curScene->addChild(src);

	glBlendEquation(GL_FUNC_ADD);

	SetFontColor(fontColorBack);

	return textSize.width;
}

void DrawText(int index, int x, int y, float zoom)
{
#ifdef TTFFONT
	DrawTextStrSystem(textId[index], x, y, zoom, LEFT, true);
#else
	DrawTextStr(TEXTPTR(index), x, y, zoom);
#endif
}

void DrawTextSolid(int index, int x, int y, float zoom)
{
#ifdef TTFFONT
	DrawTextStrSystem(textId[index], x, y, zoom, LEFT, false);
#else

#endif
}

void DrawTextStr(const char* str, int x, int y, float zoom)
{
	DrawTextStrSystem(str, x, y, zoom, LEFT, true);

}

void DrawSubText(const char* src, int offset, int length, int x, int y, float zoom)
{
	int i, byte_len, wide = 0;
	int start = 0, end;
	char subtext[200];

	memset(subtext, 0, 200);

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
	DrawTextStrSystem(subtext, x, y, zoom, LEFT, true);
#else
	DrawCharsZoom(subtext, 0, strlen(subtext), x, y, zoom);
#endif
}

void DrawSubTextSolid(const char* src, int offset, int length, int x, int y, float zoom)
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
	DrawTextStrSystem(subtext, x, y, zoom, LEFT, false);
#else
	DrawCharsSolid(subtext, 0, strlen(subtext), x, y);
#endif
}

float CenterText(int index, int x, int y, float zoom)
{
	float rtn;

	rtn = StringWidth(TEXTPTR(index), zoom);
#ifdef TTFFONT
	DrawTextStrSystem(TEXTPTR(index), x, y, zoom, CENTER, true);
#else
	DrawTextStr(TEXTPTR(index), x - rtn / 2, y, zoom);
#endif

	return rtn;
}

float CenterTextSolid(int index, int x, int y, float zoom)
{
	float rtn;

	rtn = StringWidth(TEXTPTR(index), zoom);

#ifdef TTFFONT
	DrawTextStrSystem(TEXTPTR(index), x, y, zoom, CENTER, false);
#else

#endif

	return rtn;
}

float CenterTextStr(const char* str, int x, int y, float zoom)
{
	float rtn = StringWidth(str, zoom);

#ifdef TTFFONT
	DrawTextStrSystem(str, x, y, zoom, CENTER, true);
#else
	DrawTextStr(str, x - rtn / 2, y, zoom);
#endif

	return rtn;
}

float CenterTextStrSolid(const char* str, int x, int y, float zoom)
{
	float rtn = StringWidth(str, zoom);

#ifdef TTFFONT
	DrawTextStrSystem(str, x, y, zoom, CENTER, false);
#else

#endif
	return rtn;
}

void FrameText(const char* str, int x, int y, int dx, int line, int page, float zoom)
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
				DrawSubText(str, ofs, i - ofs, x, y - (float)cnt * 13 * _2X * zoom, zoom);

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

	if (cnt < line)
		DrawSubText(str, ofs, len - ofs, x, y - (float)cnt * 13 * _2X * zoom, zoom);

	int endPage = page + line - 1;

	if (endPage >= textPage)
		endPage = textPage - 1;

	if (textFrame < textStringLength[endPage]) {
		textFrame++;
	}
}

int ParseText(char str)
{
	if (str == '0')
		return 40 * _2X;

	switch (str) {
	case 'a':
		//°ËÁ¤»ö
		oldColor = fontColor;
		fontColor = 0x111111;
		break;
	case 'b':
		//Èò»ö
		oldColor = fontColor;
		fontColor = COLOR_WHITE;
		break;
	case 'c':
		//»¡°£»ö
		oldColor = fontColor;
		fontColor = 0xFF0000;
		break;
	case 'd':
		//³ë¶õ»ö
		oldColor = fontColor;
		fontColor = 0xFFFF00;
		break;
	case 'e':
		//ÃÊ·Ï»ö
		oldColor = fontColor;
		fontColor = 0x66CC66;
		break;
	case 'f':
		//ÆÄ¶õ»ö
		oldColor = fontColor;
		fontColor = 0x0000FF;
		break;
	case 'g':
		//º¸¶ó»ö
		oldColor = fontColor;
		fontColor = 0xCC33FF;
		break;
	case 'h':
		//ÁÖÈ²»ö
		oldColor = fontColor;
		fontColor = 0xEFA536;
		break;
	case 'i':
		//ÆÄ¶õ»ö
		oldColor = fontColor;
		fontColor = 0x3399FF;
		break;
	case 'j':
		//È¸»ö
		oldColor = fontColor;
		fontColor = 0x999999;
		break;
	case 'k':
		//ï¿½ï¿½ï¿½ï¿½È²
		oldColor = fontColor;
		fontColor = 0xFFCC66;
		break;
	case 'l':
		//¹ø°³¼Ó¼º
		oldColor = fontColor;
		fontColor = 0xAA6688;
		break;
	case 'm':
		//ï¿½Å¼ï¿½ï¿½Ó¼ï¿½
		oldColor = fontColor;
		fontColor = 0xFFFFAA;
		break;
	case 'n':
		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		oldColor = fontColor;
		fontColor = 0xFF8800;
		break;
	case 'o':
		//Ä³¸¯ÅÍÀÌ¸§¸í
		oldColor = fontColor;
		fontColor = 0xFFAAFF;
		break;
	case 'p':
		//¾ÆÀÌÅÛ¸í
		oldColor = fontColor;
		fontColor = 0xAAFF00;
		break;
	case 'q':
		//ï¿½×¶ï¿½ï¿½Ì¼ï¿½ ï¿½ï¿½Æ®(ï¿½ï¿½ï¿½ï¿½Æ®ï¿½ï¿½)
	{
		fontColor = fontGradiation[frame % 21];
	}
	break;
	case 'r':
		//ï¿½ï¿½ï¿½ï¿½È«
		oldColor = fontColor;
		fontColor = 0xFFAACC;
		break;
	case 's':
		//ÀÌÀüÀ¸·Î º¹±Í
		fontColor = oldColor;
		break;
	default:
		oldColor = fontColor;
		fontColor = COLOR_WHITE;
		break;
	}

	return 0;
}

int LineText(int index, int x, int y, int width, float zoom)
{
	return LineTextStr(TEXTPTR(index), x, y, width, -1, -1, zoom);
}

int LineTextSolid(int index, int x, int y, int width, float zoom)
{
	return LineTextStrSolid(TEXTPTR(index), x, y, width, -1, -1, zoom);
}

int LineTextStr(const char* str, int x, int y, int dx, int lines, int lines2, float zoom)
{

	int i, cnt, ofs, end, wide = 0;

	if (!str)
		return 0;

	end = StringLength(str);
	for (i = 0, cnt = 0, ofs = 0; i < end; i++) {
		if (SubstringWidth(str, ofs, i - ofs, zoom) > dx - (float)(NEXT_FONT_WIDTH - 1 * _2X) * zoom || str[i + wide] == '@') {
			if ((lines < 0 || cnt >= lines) && (lines2 < 0 || cnt < lines2))
				DrawSubText(str, ofs, i - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * FONT_HEIGHT_LINE * zoom, zoom);

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
		DrawSubText(str, ofs, end - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * FONT_HEIGHT_LINE * zoom, zoom);


	return cnt + 1;

}

int LineTextStrSolid(const char* str, int x, int y, int dx, int lines, int lines2, float zoom)
{

	int i, cnt, ofs, end, wide = 0;

	if (!str)
		return 0;

	end = StringLength(str);
	for (i = 0, cnt = 0, ofs = 0; i < end; i++) {
		if (SubstringWidth(str, ofs, i - ofs, zoom) > dx - (float)(NEXT_FONT_WIDTH - 1 * _2X) * zoom || str[i + wide] == '@') {
			if ((lines < 0 || cnt >= lines) && (lines2 < 0 || cnt < lines2))
				DrawSubTextSolid(str, ofs, i - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * (FONT_HEIGHT_LINE - 1 * _2X) * zoom, zoom);

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
		DrawSubTextSolid(str, ofs, end - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * (FONT_HEIGHT_LINE - 1 * _2X) * zoom, zoom);

	return cnt + 1;

}

int CenterLineText(const char* str, int x, int y, int dx, int type, float zoom)
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
			DrawSubText(str, ofs, i - ofs, x - ((type) ? w : dx) / 2, y - (float)(cnt * FONT_HEIGHT_LINE) * zoom, zoom);
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

	DrawSubText(str, ofs, end - ofs, x - (float)((type) ? SubstringWidth(str, ofs, end - ofs, zoom) : dx) / 2, y - (float)(cnt * FONT_HEIGHT_LINE) * zoom, zoom);

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
	textFrame = 0;	//ÅØ½ºÆ® ÇÁ·¹ÀÓÃÊ±âÈ­
	textLines = line;
}

//Æ¯ï¿½ï¿½ ï¿½ï¿½Æ®ï¿½ï¿½ï¿½Ä¸ï¿½ Æ¯ï¿½ï¿½ jsonï¿½ï¿½ï¿½Ï·ï¿½ ï¿½Û¼ï¿½ï¿½Ï´ï¿½ ï¿½Ô¼ï¿½
//bool StructureToJson(rapidjson::Writer<rapidjson::StringBuffer> * writer)
bool StructureToJson(void* structure, std::string jsonFileName)
{
	return true;
}
//ï¿½ï¿½ï¿½Ì½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ®ï¿½ï¿½ï¿½Ä·ï¿½ ï¿½Îµï¿½ï¿½Ï´ï¿½ ï¿½Ô¼ï¿½
bool JsonToStructure(void* structure, std::string jsonFileName)
{
	return true;
}

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ð±ï¿½ï¿½ ï¿½ï¿½ï¿½â°¡ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Â·ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½.
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

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ð±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ð¾ï¿½Â´ï¿½.
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
