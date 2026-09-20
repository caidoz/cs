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
static cocos2d::Color3B color(LobbySkyCycle::RGB c) {
    return cocos2d::Color3B((unsigned char)c.r,(unsigned char)c.g,(unsigned char)c.b);
}
static void init() {
    if (root) return;
    root=cocos2d::Node::create(); root->retain();
    front=cocos2d::Node::create(); front->retain();
    sky=cocos2d::LayerGradient::create(cocos2d::Color4B::WHITE,cocos2d::Color4B::WHITE,cocos2d::Vec2(0,-1));
    root->addChild(sky);
    if (sprite[LOBBY_LANDSCAPE_IMG]) {
        landscape=cocos2d::Sprite::createWithTexture(sprite[LOBBY_LANDSCAPE_IMG]->getTexture());
        landscape->setAnchorPoint(cocos2d::Vec2(0.5f,0));
        landscape->getTexture()->setAntiAliasTexParameters();
        root->addChild(landscape);
    }
    if(sprite[LOBBY_FOOTHILLS_IMG]) {
        foothills=cocos2d::Sprite::createWithTexture(sprite[LOBBY_FOOTHILLS_IMG]->getTexture());
        foothills->setAnchorPoint(cocos2d::Vec2(.5f,0));
        foothills->getTexture()->setAntiAliasTexParameters();
        root->addChild(foothills);
    }
    for(int i=0;i<4;++i) if(sprite[LOBBY_CLOUD_IMG]) {
        clouds[i]=cocos2d::Sprite::createWithTexture(sprite[LOBBY_CLOUD_IMG]->getTexture());
        clouds[i]->getTexture()->setAntiAliasTexParameters();
        (i<2 ? root : front)->addChild(clouds[i]);
    }
    atmosphere=cocos2d::DrawNode::create(); root->addChild(atmosphere);
    flyers=cocos2d::DrawNode::create(); front->addChild(flyers);
}
static void draw() {
    using namespace cocos2d;
    init();
    const float t=(float)seconds;
    const auto p=LobbySkyCycle::sample(LobbySkyCycle::hour(seconds));
    sky->setContentSize(Size((float)DX,(float)DY));
    sky->setStartColor(color(p.top)); sky->setEndColor(color(p.horizon));
    // Camera travel in screen pixels at base zoom, shared by every depth plane.
    float w=0,h=0; LobbyCastleSize(&w,&h);
    const float base=w>0 ? DX/w : 1;
    const float travelX=gLobbyCamX>=0 ? (w*.5f-gLobbyCamX)*base : 0;
    const float travelY=gLobbyCamImg>=0 ? (gLobbyCamY-h*.5f)*base : 0;
    const float panX=LobbyParallax::offset(travelX,LobbyParallax::Far,DX*.08f);
    const float panY=LobbyParallax::offset(travelY,LobbyParallax::Far,DY*.05f);
    if (landscape) {
        const auto size=landscape->getContentSize();
        const float scale=Max(DX*1.4f/size.width,DY*.52f/size.height)
            *LobbyParallax::scale(gLobbyCamZoom,LobbyParallax::Far);
        landscape->setScale(scale);
        // Extend below the screen, not merely behind the menu's top edge.
        // Transparent gaps between menu buttons must still have forest beneath.
        landscape->setPosition(Vec2(DX*.5f+panX,-DY*.065f+panY));
        landscape->setColor(color(p.land));
    }
    if(foothills) {
        const auto size=foothills->getContentSize();
        const float scale=Max(DX*1.6f/size.width,DY*.40f/size.height)
            *LobbyParallax::scale(gLobbyCamZoom,LobbyParallax::Near);
        foothills->setScale(scale);
        foothills->setPosition(Vec2(DX*.5f+LobbyParallax::offset(travelX,LobbyParallax::Near,DX*.16f),
            -DY*.13f+LobbyParallax::offset(travelY,LobbyParallax::Near,DY*.10f)));
        foothills->setColor(color(p.land));
    }
    atmosphere->clear();
    flyers->clear();
    for(int i=0;i<4;++i) if(clouds[i]) {
        const auto depth=i<2 ? LobbyParallax::CloudBack : LobbyParallax::CloudFront;
        const float width=DX*(.25f+i*.025f)*LobbyParallax::scale(gLobbyCamZoom,depth);
        clouds[i]->setScale(width/clouds[i]->getContentSize().width);
        const float margin=width+DX*.12f;
        const float x=std::fmod(t*DX*(.004f+i*.0007f)+i*DX*.41f,DX+2*margin)-margin
            +LobbyParallax::offset(travelX,depth,DX*.1f);
        const float y=DY*(i<2 ? .48f+i*.22f : .37f+(i-2)*.22f)
            +std::sin(t*.045f+i)*DY*.008f+LobbyParallax::offset(travelY,depth,DY*.07f);
        clouds[i]->setPosition(Vec2(x,y));
        clouds[i]->setColor(color(LobbySkyCycle::mix({254,245,240},p.land,p.night*.85f)));
        clouds[i]->setOpacity((unsigned char)((i<2?165:100)-p.night*30));
    }
    // Subtle moving layered cloud wisps, not an opaque second sky.
    for(int i=0;i<7;++i) {
        const float x=std::fmod(t*(2.0f+i*.36f)+i*DX*.247f,DX*1.45f)-DX*.22f+panX*1.5f;
        const float y=DY*(.27f+.087f*i)+std::sin(t*.035f+i)*DY*.012f-panY*1.5f;
        const auto c=LobbySkyCycle::mix({255,238,231},{106,123,170},p.night);
        for(int j=0;j<5;++j)
            atmosphere->drawSolidCircle(Vec2(x+j*DX*.025f,y+std::sin(float(j))*DX*.008f),
                DX*(.060f+.009f*(j%2)),0,32,1.6f,.38f,
                Color4F(c.r/255,c.g/255,c.b/255,.085f*(1-p.night*.45f)));
    }
    // Stars fade in and twinkle continuously; deterministic positions do not jump.
    for(int i=0;i<44;++i) {
        const float x=DX*(.04f+((i*73)%929)/1000.0f);
        const float y=DY*(.48f+((i*137)%450)/1000.0f);
        const float alpha=p.night*(.25f+.35f*(.5f+.5f*std::sin(t*(.45f+i*.017f)+i)));
        atmosphere->drawDot(Vec2(x,y),DX*(i%9==0?.002f:.001f),Color4F(.8f,.88f,1,alpha));
    }
    // Crescent is a polygon, so no sky-colored disc leaves a seam on the gradient.
    const float mx=DX*.84f,my=DY-GNBHEIGHT-DY*.10f,r=DX*.044f;
    for(int k=3;k>=1;--k)
        atmosphere->drawSolidCircle(Vec2(mx,my),r*(1+k*.25f),0,40,Color4F(.75f,.82f,1,p.night*.018f));
    Vec2 crescent[66];
    for(int i=0;i<=32;++i) {
        const float a=-1.5707963f+3.1415926f*i/32;
        crescent[i]=Vec2(mx+r*std::cos(a),my+r*std::sin(a));
        crescent[65-i]=Vec2(mx+r*.38f*std::cos(a),my+r*std::sin(a));
    }
    const Color4F moonColor(1,.96f,.80f,p.night);
    for(int i=0;i<32;++i) {
        atmosphere->drawTriangle(crescent[i],crescent[i+1],crescent[65-i],moonColor);
        atmosphere->drawTriangle(crescent[i+1],crescent[64-i],crescent[65-i],moonColor);
    }
    // Flying silhouettes live above the castle but below UI. Keep their routes
    // below the lobby's DAY/STAGE panels so large castles cannot hide them.
    const float flightBottom=BOTTOMMENUHEIGHT+DY*.18f;
    const float flightTop=Max(flightBottom+DY*.10f,DY-GNBHEIGHT-125*_2X);
    const int count=2+Max(0,Min(9,(int)robin.castle))/3;
    for(int i=0;i<count;++i) {
        const float x=std::fmod(t*DX*.023f+i*DX*.23f,DX*1.5f)-DX*.25f;
        const float y=flightBottom+(flightTop-flightBottom)*(.38f+i*.10f)
            +std::sin(t*.7f+i)*DX*.016f+panY;
        const float wing=std::sin(t*5+i)*DX*.007f;
        const Color4F c(.20f,.24f,.36f,(1-p.night)*.85f);
        flyers->drawSegment(Vec2(x-DX*.009f,y+wing),Vec2(x,y),DX*.0012f,c);
        flyers->drawSegment(Vec2(x,y),Vec2(x+DX*.009f,y+wing),DX*.0012f,c);
    }
    // Visible on entry; 24-second pass every 36 seconds, including twilight.
    const float phase=std::fmod(t+7,36.0f);
    if(phase<24) {
        const float x=DX*(-.15f+phase/24*1.3f),y=flightBottom+(flightTop-flightBottom)*.80f
            +std::sin(t*.5f)*DX*.018f+panY;
        const float s=DX*.036f*LobbyParallax::scale(gLobbyCamZoom,LobbyParallax::CloudFront);
        const float flap=std::sin(t*2.4f)*s*.6f;
        const Color4F c(.24f+p.night*.18f,.20f+p.night*.18f,.33f+p.night*.18f,.90f);
        flyers->drawTriangle(Vec2(x,y),Vec2(x-s*1.6f,y+s+flap),Vec2(x-s*.5f,y-s*.15f),c);
        flyers->drawTriangle(Vec2(x,y),Vec2(x+s*.6f,y+s*.8f+flap),Vec2(x+s*.3f,y-s*.2f),c);
        flyers->drawSegment(Vec2(x-s*.7f,y-s*.3f),Vec2(x+s*.65f,y+s*.18f),s*.10f,c);
        flyers->drawTriangle(Vec2(x+s*.5f,y+s*.3f),Vec2(x+s*1.15f,y+s*.12f),Vec2(x+s*.5f,y),c);
    }
    root->setVisible(true);
    // The main screen buffer is also a render target. IsOffscreenTarget()
    // deliberately excludes it and would skip every normal buffered lobby frame.
    if(gRenderTarget) root->visit();
    else if(!screenBuffer && !root->getParent()) curScene->addChild(root);
}
static void drawFront() {
    if(!front) return;
    front->setVisible(true);
    if(gRenderTarget) front->visit();
    else if(!screenBuffer && !front->getParent()) curScene->addChild(front);
}
}

void LobbySkyUpdate(float delta) {
    // Detach the direct-render node before pooled frame drawing, including menu exits.
    if(LobbySky::root) { LobbySky::root->setVisible(false); LobbySky::root->removeFromParent(); }
    if(LobbySky::front) { LobbySky::front->setVisible(false); LobbySky::front->removeFromParent(); }
    if(drawHandle==MD_LOBBY && std::isfinite(delta) && delta>0)
        LobbySky::seconds=std::fmod(LobbySky::seconds+delta,LobbySkyCycle::PeriodSeconds);
}
