#include "Core.h"
#include "Func.h"
#include "Data.h"
#include "Text.h"

// Text Handling

//한 글자가 차지하는 바이트 수(1~4).
//UTF-8 시퀀스를 먼저 인식하고, 아니면 CP949 2바이트로 본다.
//소스가 전부 UTF-8로 넘어가면 CP949 분기는 죽는다.
int CharByteLen(const char* s)
{
	unsigned char c0 = (unsigned char)s[0];

	if (c0 < 0x80)
		return 1;

	if ((c0 & 0xE0) == 0xC0 && ((unsigned char)s[1] & 0xC0) == 0x80)
		return 2;

	if ((c0 & 0xF0) == 0xE0 && ((unsigned char)s[1] & 0xC0) == 0x80
		&& ((unsigned char)s[2] & 0xC0) == 0x80)
		return 3;

	if ((c0 & 0xF8) == 0xF0 && ((unsigned char)s[1] & 0xC0) == 0x80
		&& ((unsigned char)s[2] & 0xC0) == 0x80 && ((unsigned char)s[3] & 0xC0) == 0x80)
		return 4;

	//CP949 2바이트
	if (c0 >= 0x81 && s[1])
		return 2;

	return 1;
}

//첫 바이트 외에 더 차지하는 바이트 수. wide 누산기에 더해 쓴다.
int CharExtraBytes(const char* s)
{
	return CharByteLen(s) - 1;
}

int StringLength(const char* str)
{
	int i, rtn = 0, byte_len = strlen(str);

	for (i = 0; i < byte_len; i += CharByteLen(str + i))
		rtn++;

	return rtn;
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
	int i, len, rtn = 0, byte_len = strlen(str);

	for (i = 0; i < byte_len; i += len) {
		len = CharByteLen(str + i);

		if (len > 1)
			rtn += NEXT_FONT_WIDTH;
		else if (str[i] == '@')
			;	//개행표시는 폭을 차지하지 않는다
		else if (str[i] == '|')
			len = 2;	//색상코드 '|' + 색상문자
		else
			rtn += NEXT_ALPHAFONT_WIDTH;
	}

	return (float)(rtn + 2 * _2X) * zoom;
}

//서브문자열의 길이 리턴
float SubstringWidth(const char* str, int offset, int length, float zoom)
{
	int i, len, byte_len, rtn = 0;
	int start = 0, end;

	//offset은 글자수다. 그만큼 지나간 바이트 위치를 구한다.
	for (i = 0; i < offset && str[start]; i++)
		start += CharByteLen(str + start);

	byte_len = Min(offset + length, StringLength(str));

	for (i = offset, end = start; i < byte_len && str[end]; i++) {
		len = CharByteLen(str + end);

		if (len > 1) {
			rtn += NEXT_FONT_WIDTH;
			end += len;
		}
		else if (str[end] == '|') {
			end += 2;	//색상코드 '|' + 색상문자
			i++;
		}
		else {
			rtn += NEXT_ALPHAFONT_WIDTH;
			end++;
		}
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

			//���� '|'�� ��������
			if (fontInfo[str[offset]] == 127) {
				//'|' ���� ������ ���ĺ��� �������� ��Ʈ���� ���ϰ�
				ParseText(str[offset + 1]);

				//'|'�� ���ĺ��� �����Ѵ�.
				offset++;
				i++;
			}
			else {
				if (cursor + 1 >= (int)sizeof(labelStr))
					break;

				//각 글자마다 폰트색상을 정해준다.
				bmFontColor[cursor] = fontColor;

				labelStr[cursor] = str[offset];
				cursor++;
			}

		}
		//한글이면 (UTF-8은 2~4바이트)
		else {
			int len = CharByteLen(str + offset), j;

			if (cursor + len >= (int)sizeof(labelStr))
				break;

			for (j = 0; j < len; j++) {
				bmFontColor[cursor + j] = fontColor;
				labelStr[cursor + j] = str[offset + j];
			}

			cursor += len;

			offset += len - 1;
			i += len - 1;
		}
	}

}

//처음 같은 문자열을 가진 라벨 인덱스를 리턴
int GetSameStringIndex(const char* str)
{
	int i;

	//�ϴ� �ؽ�Ʈ�� labelStr���ٰ� �ְ� ��Ʈ�����·� �ٲ� ������
	memset(&labelStr2, 0, sizeof(labelStr2));
	TextToString(labelStr, strlen(labelStr), (char*)&labelStr2);

	//�ش� �ؽ�Ʈ�� ���ؼ� ���� �ؽ�Ʈ�� �ִ��� ����
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


//���� ��ε��Ǿ� �ִ°� �����ؼ� ��� �ε����� ��� �Ǵ��� 
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


float DrawTextStrSystem(const char* str, int x, int y, float zoom, int align, bool bold)
{
	int i, len;
	int length;
	int offset = 0;
	float w = StringWidth(str, zoom);
	float h = FONT_HEIGHT * zoom;
	int fontColorBack = fontColor;
	Size textSize;

	//타격 줌. 월드 안에서 찍히는 글자(데미지 숫자 등)도 같이 커져야 한다.
	//w/h는 클리핑 판정에만 쓰이므로 같이 늘려 준다.
	if (HitZoomOn()) {
		HitZoomPoint(&x, &y);
		zoom *= hitZoom;
		w *= hitZoom;
		h *= hitZoom;
	}

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

	//bmFontColor[]는 바이트 첨자, getLetter()는 글자 첨자다.
	//글자 단위로 전진하면서 둘을 맞춘다.
	for (i = 0; i < length; i += len) {
		cocos2d::Sprite* letter;

		len = CharByteLen(labelStr + i);

		//공백은 Label이 letter를 만들지 않는다
		if (len == 1 && labelStr[i] == 32) {
			offset++;
			continue;
		}

		letter = fontLabel[getFontLabelIdx]->getLetter(offset);

		if (letter)
			letter->setColor(Color3B((bmFontColor[i] >> 16) & 0xFF, (bmFontColor[i] >> 8) & 0xFF, bmFontColor[i] & 0xFF));

		offset++;
	}

	//AfterSpriting() �� ���� �Ծ�: ���� Ÿ���� ���� ������ �� Ÿ�ٿ� �ٷ� ����ϰ�,
	//������ ���� ���̴� ���Ž� ��θ� ����.
	if (gRenderTarget) {
		//Label �� 3���� visit �����ε尡 0���� Node::visit() �� �����Ƿ� Node* �� �޾� ȣ���Ѵ�.
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
	int i, byte_len;
	int start = 0, end;
	char subtext[200];

	memset(subtext, 0, 200);

	//offset, length는 글자수다. 해당하는 바이트 구간을 구한다.
	for (i = 0; i < offset && src[start]; i++)
		start += CharByteLen(src + start);

	byte_len = Min(offset + length, StringLength(src));

	for (i = offset, end = start; i < byte_len && src[end]; i++)
		end += CharByteLen(src + end);

	strncpy(subtext, src + start, Min(end - start, (int)sizeof(subtext) - 1));
#ifdef TTFFONT
	DrawTextStrSystem(subtext, x, y, zoom, LEFT, true);
#else
	DrawCharsZoom(subtext, 0, strlen(subtext), x, y, zoom);
#endif
}

void DrawSubTextSolid(const char* src, int offset, int length, int x, int y, float zoom)
{
	int i, byte_len;
	int start = 0, end;
	char subtext[100];

	memset(subtext, 0, 100);

	//offset, length는 글자수다. 해당하는 바이트 구간을 구한다.
	for (i = 0; i < offset && src[start]; i++)
		start += CharByteLen(src + start);

	byte_len = Min(offset + length, StringLength(src));

	for (i = offset, end = start; i < byte_len && src[end]; i++)
		end += CharByteLen(src + end);

	strncpy(subtext, src + start, Min(end - start, (int)sizeof(subtext) - 1));
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

		wide += CharExtraBytes(str + i + wide);
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
		//����Ȳ
		oldColor = fontColor;
		fontColor = 0xFFCC66;
		break;
	case 'l':
		//번개속성
		oldColor = fontColor;
		fontColor = 0xAA6688;
		break;
	case 'm':
		//�ż��Ӽ�
		oldColor = fontColor;
		fontColor = 0xFFFFAA;
		break;
	case 'n':
		//������
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
		//�׶��̼� ��Ʈ(����Ʈ��)
	{
		fontColor = fontGradiation[frame % 21];
	}
	break;
	case 'r':
		//����ȫ
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

int LineText(int index, int x, int y, int width, float zoom)
{
	return LineTextStr(TEXTPTR(index), x, y, width, -1, -1, zoom);
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

		wide += CharExtraBytes(str + i + wide);
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

		wide += CharExtraBytes(str + i + wide);
	}

	if ((lines < 0 || cnt >= lines) && (lines2 < 0 || cnt < lines2))
		DrawSubTextSolid(str, ofs, end - ofs, x, y - (float)(cnt - (lines < 0 ? 0 : lines)) * (FONT_HEIGHT_LINE - 1 * _2X) * zoom, zoom);

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

		if (CharByteLen(textString + i + wide) > 1)
			wide += CharExtraBytes(textString + i + wide);
		else if (textString[i + wide] == '|')
			color = textString[i + wide + 1];
	}

	textStringLength[textPage] = StringLength(textString);
	textPage++;
	textCurPage = 0;
	textFrame = 0;	//텍스트 프레임초기화
	textLines = line;
}

//������ �б�� ���Ⱑ ������ ���·� ������ ����.
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
	fclose(fp);
	return true;
}

//������ �б��������� ������ �� ������ �о�´�.
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
	fclose(fp);
	return true;
}
