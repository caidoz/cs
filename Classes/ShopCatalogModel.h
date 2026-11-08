#pragma once
#include "Config/ShopConfig.h"
// Stable catalog identities; prices/probabilities are never inferred from artwork.
namespace ShopCatalog {
//---- 상점은 큰 셋이다 ----
//
//전에는 추천 · 보급품 · 패키지였다. 그런데 추천이 보급품의 카드를 그대로
//한 번 더 깔아서, 같은 상자가 두 탭에 나왔다 - 어느 쪽이 진짜인지가
//안 읽힌다.
//
//파는 물건의 성격으로 가른다.
//    장비    상자다. 골드로 연다. 영구 창고로 간다.
//    패키지  현금 묶음.
//    재화    하트 · 캐시. 골드는 안 판다 - 판에서 벌어 상자와 성에 쓰는
//            순환 재화이지 사고파는 물건이 아니다.
//
//동료는 여기 없다. 성에서 모집한다 - 동료는 성 방에 사는 사람들이고,
//상점에서 사는 것보다 성에서 맞아들이는 쪽이 읽힌다.
enum Tab { Gear, Packages, Currency, TabCount };
enum Kind { Daily, Weapon, Armor, Companion, Special, ExistingBox, CashBundle };
enum Ownership { Persistent, RunTemporary };
enum Source { Shop, RunReward };
enum Availability { Ready, BalancePending, StorePending };
struct Product {
 const char* id; Kind kind; int hero; int rewardRef; Availability availability;
 bool visible; int sortOrder; Ownership ownership; Source source;
};
inline Product Supply(int index,int hero) {
 static const char* weapons[]={"SHOP_WEAPON_ROBIN","SHOP_WEAPON_DIANA","SHOP_WEAPON_MAX"};
 static const char* armors[]={"SHOP_ARMOR_ROBIN","SHOP_ARMOR_DIANA","SHOP_ARMOR_MAX"};
 hero=hero<0?0:hero>2?2:hero;
 if(index==0) return {weapons[hero],Weapon,hero,hero,BalancePending,true,10,Persistent,Shop};
 if(index==1) return {armors[hero],Armor,hero,hero,BalancePending,true,20,Persistent,Shop};
 if(index==2) return {"SHOP_COMPANION",Companion,-1,0,BalancePending,true,30,Persistent,Shop};
 return {"SHOP_SPECIAL",Special,-1,0,BalancePending,true,40,Persistent,Shop};
}
inline Product DailySlot() {return {"SHOP_DAILY_FREE",Daily,-1,0,BalancePending,true,0,Persistent,Shop};}
inline Product GenericBox(int i) {
 static const char* ids[]={"BOX_PAID0","BOX_PAID1","BOX_PAID2","BOX_PAID3","BOX_PAID4","BOX_PAID5"};
 i=i<0?0:i>5?5:i;return {ids[i],ExistingBox,-1,i,Ready,true,50+i,Persistent,Shop};
}
inline bool MatchesHero(const Product& p,int hero) {return p.hero<0||p.hero==hero;}
inline bool Forbidden(const char* id) {
 const char* names[]={"SHOP_CASTLE_MATERIAL","SHOP_REPAIR_PART","SHOP_GRID_SLOT","SHOP_CASTLE_LEVEL_UP","SHOP_FLOOR_UNLOCK","SHOP_BUILDING_TICKET","inven_20"};
 for(const char* name:names) {
  const char *a=id,*b=name;while(*a&&*a==*b){++a;++b;}if(!*a&&!*b)return true;
 }
 return false;
}
inline bool CanPurchase(const Product& p) {return p.visible&&p.availability==Ready&&!Forbidden(p.id)&&p.ownership==Persistent;}
// No daily economy/reset policy has been approved. Keep the slot, not a fake claim.
inline bool DailyConfigured() {return SHOP_DAILY_ENABLED&&SHOP_DAILY_GOLD>0&&SHOP_DAILY_RESET_SECONDS>0;}
inline bool ClaimDaily(long long now,long long resetSeconds,long long reward,bool enabled,
                      long long& last,long long& gold,long long cap) {
 if(!enabled||reward<=0||resetSeconds<=0||now<last||now-last<resetSeconds||gold>cap-reward)return false;
 gold+=reward;last=now;return true;
}
}
