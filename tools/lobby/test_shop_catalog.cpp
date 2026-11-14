#include "../../Classes/ShopCatalogModel.h"
#include "../../Classes/CastleMenuModel.h"
#include <cassert>
#include <cstring>
#include <iostream>
int main() {
 for(int tier=0;tier<6;++tier){
  long long gems=ShopGold::Price(tier),gold=7;
  assert(ShopGold::Buy(tier,gems,gold,1000000));
  assert(gems==0&&gold==7+ShopGold::Amount(tier));
  const auto before=gold;
  assert(!ShopGold::Buy(tier,gems,gold,1000000)&&gold==before&&gems==0);
  gems=ShopGold::Price(tier);gold=1000000-ShopGold::Amount(tier)+1;
  assert(!ShopGold::Buy(tier,gems,gold,1000000)&&gems==ShopGold::Price(tier));
 }
 {long long gems=100,gold=0;assert(!ShopGold::Buy(-1,gems,gold,1000000));assert(!ShopGold::Buy(6,gems,gold,1000000));assert(gems==100&&gold==0);}
 const long long prices[]={100,500,30,100,300,1000};
 for(int tier=0;tier<6;++tier){
  assert(ShopTreasure::Price(tier)==prices[tier]);
  assert(ShopTreasure::UsesGems(tier)==(tier>=2));
  assert(ShopTreasure::HeartReward(tier,10000)<=20);
  if(tier<2)assert(ShopTreasure::GoldReward(tier,1000000)<prices[tier]);
 }
 assert(ShopTreasure::Price(-1)==-1&&ShopTreasure::Price(6)==-1);
 for(int h=0;h<3;++h)for(int k=0;k<4;++k) {
  const auto p=ShopCatalog::Supply(k,h);
  assert(ShopCatalog::MatchesHero(p,h));assert(!ShopCatalog::CanPurchase(p));
  assert(p.ownership==ShopCatalog::Persistent);assert(!ShopCatalog::Forbidden(p.id));
  if(k<2)assert(!ShopCatalog::MatchesHero(p,(h+1)%3));
 }
 assert(!std::strcmp(ShopCatalog::Supply(2,0).id,ShopCatalog::Supply(2,2).id));
 assert(ShopCatalog::Forbidden("inven_20"));assert(!ShopCatalog::DailyConfigured());
 long long stamp=100,gold=50;
 assert(!ShopCatalog::ClaimDaily(200,100,2,false,stamp,gold,100));
 assert(ShopCatalog::ClaimDaily(200,100,2,true,stamp,gold,100));
 assert(!ShopCatalog::ClaimDaily(200,100,2,true,stamp,gold,100));
 assert(!ShopCatalog::ClaimDaily(100,100,2,true,stamp,gold,100));
 assert(gold==52&&stamp==200);
 CastleMenuModel::Progress p={};p.version=1;p.owned=1;
 long long coins=777,castleGold=100000000;
 for(int c=1;c<10;++c) {
  for(int i=0;i<5;++i)p.parts[c-1][i]=5;
  const auto oldGold=castleGold;const int cost=CastleMenuModel::GoldPrice(c);
  assert(CastleMenuModel::BuyGold(p,c,castleGold));assert(castleGold==oldGold-cost&&coins==777);
  assert(CastleMenuModel::Inventory(p,c,30,4,200)>=CastleMenuModel::Inventory(p,c-1,30,4,200));
 }
 assert(!CastleMenuModel::BuyGold(p,10,castleGold));
 std::cout<<"PASS catalog filters ownership unavailable purchases daily idempotency and ten gold-only castle stages\n";
}
