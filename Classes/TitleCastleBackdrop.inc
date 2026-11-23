// Real combat castle bodies are cached; their native wheel sprites stay live.
namespace TitleCastleBackdrop {
struct Wheel {float x=0,y=0,radius=0;int image=0;};
struct Castle {
    cocos2d::RenderTexture* body=nullptr;
    int bottom=0,height=0;
    Wheel wheels[2];
};
static Castle castles[9];
static int width=0,height=0,drawn=0,wheelsDrawn=0;
static unsigned appearance=0;
static float elapsed=0,firstOffset=0,firstAngle=0;

bool prepare(){
    unsigned key=0;for(int c=0;c<9;++c)key=key*7+CastleVisualPartLevel(c,3)+1;
    if(width==DX&&height==DY&&appearance==key&&castles[8].body)return true;
    for(auto& c:castles){if(c.body)c.body->release();c=Castle();}
    width=DX;height=DY;appearance=key;
    for(int c=0;c<9;++c){
        auto& item=castles[c];
        item.body=cocos2d::RenderTexture::create(DX,DY);
        if(!item.body)return false;
        item.body->retain();
        const Run savedRun=run;
        const int savedHull=siegeHullStage;
        const bool savedActive=active,savedSiege=siegeActive,savedIsolate=nativeTitleIsolate,savedBodyOnly=nativeTitleBodyOnly;
        const float savedEntry=entryElapsed,savedPreview=OriginalCastle::previewScale;
        const TurretAttack::Sequence savedFire=turretFire;
        run.stage=c;run.setShape(castleShape(c));siegeHullStage=c;siegeActive=false;active=true;
        entryElapsed=MergeCastleTransition::Duration;OriginalCastle::previewScale=0;
        turretFire=TurretAttack::Sequence();nativeTitleIsolate=true;nativeTitleBodyOnly=true;
        const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2;
        PushRenderTarget(item.body,nullptr,true);SetSectionClip(0,DY,DX,DY,true);
        drawWorld(layout(),true);
        PopRenderTarget();clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;
        const float z=OriginalCastle::zoom(),lift=OriginalCastle::lift();
        float bottom=(float)DY;
        for(int side=0;side<2;++side){
            const auto& a=MistCastle::wheelAnchors[c][side];
            auto& wheel=item.wheels[side];
            wheel.x=OriginalCastle::left()+a[0]*z;
            wheel.y=(OriginalCastle::H-a[1])*z+lift;
            wheel.radius=a[2]*z;wheel.image=MistCastle::image(c,6+side);
            bottom=std::min(bottom,wheel.y-wheel.radius);
        }
        item.bottom=std::max(0,(int)std::floor(bottom-4*DX/640.f));
        const int top=std::min((int)DY,OriginalCastle::box(0,55,0,0).y+(int)(4*DX/640.f));
        item.height=std::max(1,top-item.bottom);
        for(auto& wheel:item.wheels)wheel.y-=item.bottom;
        run=savedRun;siegeHullStage=savedHull;siegeActive=savedSiege;active=savedActive;
        entryElapsed=savedEntry;OriginalCastle::previewScale=savedPreview;
        nativeTitleIsolate=savedIsolate;nativeTitleBodyOnly=savedBodyOnly;turretFire=savedFire;
    }
    return true;
}
}

bool MergeRouletteTitleCastlesDraw(){
    using namespace TitleCastleBackdrop;
    if(!prepare())return false;
    if(!(review&&reviewCapturePending))elapsed+=std::min(.05f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()));
    const float s=DX/640.f;
    SetColor(0);grayScale=0;SetAlpha(32);MemRect(0,DY,DX,DY,0xFFFFFF);
    // Match the logo and the platform-specific login button stack.
    const float logoHeight=std::min(DX*.90f*866.f/1800.f,DY*.18f);
    const float top=DY-logoHeight-38*s;
    int buttons=1;
#if CC_TARGET_PLATFORM != CC_PLATFORM_IOS
    ++buttons;
#endif
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    ++buttons;
#endif
    const int guestTop=std::max(86,std::min(150,DY/9));
    const float bottom=guestTop+(buttons-1)*54+16*s;
    const float cellWidth=DX/3.f,cellHeight=std::max(36.f,(top-bottom)/3.f);
    int sourceHeight=1;for(const auto& c:castles)sourceHeight=std::max(sourceHeight,c.height);
    // Castle size follows width only; short screens overlap the rows.
    const float zoom=std::max(.01f,(cellWidth-24*s)*1.5f/DX);
    const float rowHeight=sourceHeight*zoom;
    const float rowStep=std::min(cellHeight,std::max(0.f,(top-bottom-rowHeight)*.5f));
    const float bandHeight=std::max(cellHeight,rowHeight);
    drawn=wheelsDrawn=0;
    for(int c=0;c<9;++c){
        const auto& item=castles[c];
        const float shift=std::sin(elapsed*.85f+c*.73f)*4*s;
        const float bob=std::sin(elapsed*4.f+c*.9f)*.65f*s;
        const float left=(c%3+.5f)*cellWidth-DX*zoom*.5f+shift;
        const float upper=top-(c/3)*rowStep-(bandHeight-item.height*zoom)*.5f+bob;
        const float ground=upper-item.height*zoom+2*s;
        // Passing road marks make the forward travel readable without scenery.
        const float roadWidth=DX*zoom*.78f,roadLeft=(c%3+.5f)*cellWidth-roadWidth*.5f;
        for(int mark=0;mark<3;++mark){
            const float travel=std::fmod(elapsed*22*s+mark*roadWidth/3,roadWidth);
            MemRect((int)(roadLeft+roadWidth-travel),(int)ground,std::max(2,(int)(7*s)),std::max(1,(int)s),0xDDD9D0);
        }
        auto* body=cocos2d::Sprite::createWithTexture(item.body->getSprite()->getTexture());
        body->setTextureRect(cocos2d::Rect(0,(float)item.bottom,(float)DX,(float)item.height));
        body->setFlippedY(true);body->setAnchorPoint({0,1});body->setScale(zoom);body->setPosition({left,upper});
        body->getTexture()->setAliasTexParameters();body->visit();++drawn;
        const float angle=-elapsed*(100.f+c*3.f);
        if(c==0){firstOffset=shift;firstAngle=angle;}
        for(const auto& wheel:item.wheels){
            const int img=wheel.image;if(!sprite[img])LoadImg(img);if(!sprite[img])continue;
            const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
            RotateImage((int)size.width,(int)size.height,0,0,(int)(left+wheel.x*zoom),
                (int)(upper-(item.height-wheel.y)*zoom),false,angle,0,0,
                2*wheel.radius*zoom/size.width,cocos2d::Vec2(.5f,.5f),sprite[img],img);
            ++wheelsDrawn;
        }
    }
    return true;
}
