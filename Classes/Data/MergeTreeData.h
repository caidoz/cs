#pragma once
// Generated from content/merge_tree.tsv by tools/merge_roulette/build_tree_data.py. Do not edit.
// 합성 6단 = 성급. 같은 역할 ★n 둘 → 그 역할 ★n+1 중 무작위.
namespace MergeTrees {
enum { Roles=4, Levels=6, CrewCount=64, MaxPerCell=8 };
struct CrewInfo { int role, star, trait; };
static const CrewInfo Crew[CrewCount]={
 {1,1,3},
 {2,1,3},
 {2,1,1},
 {0,1,1},
 {1,1,3},
 {3,1,2},
 {3,1,2},
 {0,1,1},
 {1,2,4},
 {1,2,2},
 {3,2,3},
 {0,2,0},
 {1,2,4},
 {2,2,0},
 {2,2,0},
 {3,2,4},
 {2,2,1},
 {3,2,2},
 {0,2,4},
 {0,2,4},
 {1,3,0},
 {2,3,4},
 {3,3,3},
 {2,3,0},
 {0,3,1},
 {1,3,3},
 {1,3,5},
 {1,3,5},
 {0,3,0},
 {3,3,5},
 {2,3,5},
 {3,3,1},
 {0,3,4},
 {0,3,0},
 {2,3,0},
 {2,4,2},
 {2,4,1},
 {0,4,1},
 {2,4,4},
 {3,4,2},
 {3,4,5},
 {2,4,4},
 {0,4,3},
 {1,5,2},
 {0,5,2},
 {2,4,2},
 {0,4,0},
 {1,4,2},
 {3,4,5},
 {3,4,3},
 {0,4,3},
 {1,4,4},
 {1,4,5},
 {1,4,3},
 {3,5,4},
 {0,4,3},
 {2,5,1},
 {1,5,3},
 {3,5,5},
 {0,5,0},
 {2,5,4},
 {3,6,2},
 {2,6,1},
 {0,6,1},
};
static const char* RoleName[Roles]={u8"지휘",u8"포격",u8"지원",u8"공격"};
// 릴 2·3 가중치. 역할은 전부 ★1 에서 시작하므로 같다. 장비 계열은 호출부가 4 를 준다.
static const int RoleWeight[Roles]={1,1,1,1};
inline int Role(int crew) {return crew>=0&&crew<CrewCount?Crew[crew].role:-1;}
inline int Star(int crew) {return crew>=0&&crew<CrewCount?Crew[crew].star:0;}
inline int Trait(int crew) {return crew>=0&&crew<CrewCount?Crew[crew].trait:2;}
inline int CountAt(int role,int star) {int n=0;for(int c=0;c<CrewCount;++c)if(Crew[c].role==role&&Crew[c].star==star)++n;return n;}
inline int CrewAt(int role,int star,int k) {for(int c=0;c<CrewCount;++c)if(Crew[c].role==role&&Crew[c].star==star&&k--==0)return c;return -1;}
inline int MaxStar(int role) {int m=0;for(int c=0;c<CrewCount;++c)if(Crew[c].role==role&&Crew[c].star>m)m=Crew[c].star;return m;}
// 고유 동료의 주인 히어로(0 로빈 · 1 디아나 · 2 맥스). 역할마다 두 히어로가 ★ 사다리를 나눠 갖는다 -
// 그 히어로의 룰렛에만 나오고, 그 히어로를 얻기 전에는 뽑기·창고 지급에도 안 나온다.
static const signed char Owner[CrewCount]={2,1,2,0,1,2,0,1,2,1,0,0,1,1,2,2,2,0,1,0,1,1,0,1,1,2,1,2,1,2,2,2,0,0,2,2,2,0,1,0,2,2,0,2,1,1,1,2,0,2,0,1,2,1,2,1,2,1,0,0,1,0,1,0};
inline int OwnerHero(int crew) {return crew>=0&&crew<CrewCount?Owner[crew]:-1;}
inline int OwnedCrewAt(int hero,int role,int star,int k) {for(int c=0;c<CrewCount;++c)if(Crew[c].role==role&&Crew[c].star==star&&(hero<0||Owner[c]==hero)&&k--==0)return c;return -1;}
// 코스튬 6부위의 Lv → detail. 무기는 6칸, 나머지 부위는 1칸씩 성장.
inline int GearDetail(int family,int detail,int level) {
 const int step=family==4?6:1,cap=family==4?34:7;
 return detail<0?0:(detail+(level-1)*step>cap?cap:detail+(level-1)*step);
}
}
