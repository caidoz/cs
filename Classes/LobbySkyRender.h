#pragma once
// Included by Func_Draw.cpp after the lobby camera declarations.
#include "LobbySkyCycle.h"
#include "LobbyParallax.h"

namespace LobbySky {
static double seconds = 0;
static cocos2d::Node* root = nullptr;
static cocos2d::LayerGradient* sky = nullptr;
static cocos2d::Sprite* landscape = nullptr;
static cocos2d::Sprite* foothills = nullptr;
static cocos2d::Node* front = nullptr;
static cocos2d::DrawNode* flyers = nullptr;
static cocos2d::DrawNode* atmosphere = nullptr;
static cocos2d::Sprite* clouds[4] = {};
}

void LobbySkyUpdate(float delta) {
    // Detach the direct-render node before pooled frame drawing, including menu exits.
    if(LobbySky::root) { LobbySky::root->setVisible(false); LobbySky::root->removeFromParent(); }
    if(LobbySky::front) { LobbySky::front->setVisible(false); LobbySky::front->removeFromParent(); }
    if(drawHandle==MD_LOBBY && std::isfinite(delta) && delta>0)
        LobbySky::seconds=std::fmod(LobbySky::seconds+delta,LobbySkyCycle::PeriodSeconds);
}
