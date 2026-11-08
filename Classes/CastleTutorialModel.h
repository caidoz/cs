#pragma once
namespace CastleTutorial {
enum Step { Welcome, Depart, Place, Ready, Start, Fight, Shop, Continue, Growth, Done };
enum Event { Next, Entered, Placed, Setup, Started, ShopOpened, Bought };
inline int Clamp(int step){return step<0?-1:step>Done?Done:step;}
inline int Advance(int step,Event event){
 if((step==Welcome&&event==Next)||(step==Depart&&event==Entered)||
    (step==Place&&event==Placed)||(step==Ready&&event==Setup)||
    (step==Start&&event==Started)||(step==Fight&&event==ShopOpened)||
    (step==Shop&&event==Bought)||(step==Continue&&event==Started)||
    (step==Growth&&event==Next))return step+1;
 return step;
}
}
