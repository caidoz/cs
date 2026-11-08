#pragma once
// TODO: enable only after the actual adapter and verifier replace their stubs.
#define SHOP_STORE_CONNECTED 0
#define SHOP_RECEIPTS_VERIFIED 0
// TODO: balance approval. Zero means unavailable, never a zero-price live reward.
#define SHOP_DAILY_ENABLED 0
#define SHOP_DAILY_GOLD 0LL
#define SHOP_DAILY_RESET_SECONDS 0LL

// Purchase prices are independent of stage reward-box valuation.
namespace ShopTreasure {
inline long long Price(int tier){static const long long p[]={100,500,30,100,300,1000};return tier>=0&&tier<6?p[tier]:-1;}
inline bool UsesGems(int tier){return tier>=2&&tier<6;}
inline int GoldReward(int tier,int amount){static const int cap[]={25,125,300,1000,3000,10000};return tier>=0&&tier<6&&amount>cap[tier]?cap[tier]:amount;}
inline int HeartReward(int tier,int amount){static const int cap[]={3,5,8,12,16,20};return tier>=0&&tier<6&&amount>cap[tier]?cap[tier]:amount;}
}
