#pragma once
#include "Core.h"

#ifndef _FUNC_TEXT_H_
#define _FUNC_TEXT_H_

// Text Handling
int StringLength(const char*);
int SubstringLength(const char*, unsigned int, unsigned int);

float StringWidthTTF(const char* str, float zoom);
float StringWidth(const char*, float zoom);
float SubstringWidth(const char*, int, int, float zoom);

void ResetLabel(void);
void EraiseColorFont(char*);
int GetSameStringIndex(const char* str);
int GetFontLabelIndex(std::string);
void LoadFontLabelFromText(const char*);

float DrawTextSystem(int, int, int, float, int, bool, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
float DrawTextStrSystem(const char*, int, int, float, int, bool, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DrawText(int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawTextSolid(int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawTextStr(const char*, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawSubText(const char*, int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawSubTextSolid(const char*, int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
float CenterText(int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
float CenterTextSolid(int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
float CenterTextStr(const char*, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
float CenterTextStrSolid(const char*, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void FrameText(const char*, int, int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
int ParseText(char);
int LineText(int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
int LineTextSolid(int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
int LineTextStr(const char*, int, int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
int LineTextStrSolid(const char*, int, int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
int CenterLineText(const char*, int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void SetFrameText(int, int, int, float zoom);
void SetFrameTextStr(const char* str, int dx, int line, float zoom, char startCol);

// File Handling
bool StructureToJson(void*, std::string);
bool JsonToStructure(void*, std::string);

bool GameWriteFile(char*, char*, int);
bool LoadFile(char*, char*, int);

#endif