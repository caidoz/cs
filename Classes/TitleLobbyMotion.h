#pragma once
// Only UI draw calls inside a motion scope receive this offset. World sprites remain fixed.
extern float titleLobbyClock;
extern float uiSceneMotionY;
void BeginTitleLobbyMotion();
void AdvanceTitleLobbyMotion(float dt);
float TitleLobbyEase(float begin,float end);
void DrawTitleLobbyDeparture();
void DrawTitleCampOverlay();
extern float titleEntranceClock;
extern float uiSceneMotionX;
float TitleEntranceEase(float begin,float end);
float LobbyTopbarDrop();
float LobbyNavPop(int index);
void PlayCampMusic();
