#pragma once
#include <algorithm>
#include <vector>
namespace LobbyCamp {
struct Owned {int id,star,level;};
inline std::vector<Owned> highestOwned(const std::vector<Owned>& inventory){
 std::vector<Owned> unique;
 for(const auto& item:inventory){
  if(item.id<0||item.id>=64||item.level<=0||item.star<=0)continue;
  auto found=std::find_if(unique.begin(),unique.end(),[&](const Owned& q){return q.id==item.id;});
  if(found==unique.end())unique.push_back(item);else if(item.level>found->level)*found=item;
 }
 std::sort(unique.begin(),unique.end(),[](const Owned& a,const Owned& b){
  if(a.star!=b.star)return a.star>b.star;
  if(a.level!=b.level)return a.level>b.level;
  return a.id<b.id;
 });
 if(unique.size()>3)unique.resize(3);return unique;
}
}
