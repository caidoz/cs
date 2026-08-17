#pragma once
#include "Core.h"

#ifndef _FUNC_TEXT_H_
#define _FUNC_TEXT_H_

// Text Handling
int CharByteLen(const char*);
int CharExtraBytes(const char*);
int StringLength(const char*);

float StringWidthTTF(const char* str, float zoom);
float StringWidth(const char*, float zoom);
float SubstringWidth(const char*, int, int, float zoom);

void ResetLabel(void);
void EraiseColorFont(char*);
int GetSameStringIndex(const char* str);
int GetFontLabelIndex(std::string);
void LoadFontLabelFromText(const char*);

float DrawTextStrSystem(const char*, int, int, float, int, bool);
void DrawText(int, int, int, float zoom);
void DrawTextSolid(int, int, int, float zoom);
void DrawTextStr(const char*, int, int, float zoom);
void DrawSubText(const char*, int, int, int, int, float zoom);
void DrawSubTextSolid(const char*, int, int, int, int, float zoom);
float CenterText(int, int, int, float zoom);
float CenterTextSolid(int, int, int, float zoom);
float CenterTextStr(const char*, int, int, float zoom);
float CenterTextStrSolid(const char*, int, int, float zoom);
void FrameText(const char* str, int x, int y, int dx, int line, int page, float zoom);
int ParseText(char);
int LineText(int, int, int, int, float zoom);
int LineTextStr(const char*, int, int, int, int, int, float zoom);
int LineTextStrSolid(const char*, int, int, int, int, int, float zoom);
void SetFrameText(int index, int dx, int line, float zoom);
void SetFrameTextStr(const char* str, int dx, int line, float zoom, char startCol);

// File Handling

bool GameWriteFile(char*, char*, int);
bool LoadFile(char*, char*, int);

#endif