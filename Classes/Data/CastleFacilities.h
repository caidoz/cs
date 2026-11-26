#pragma once
#include "PortraitCastleArt.h"
// Four permanent facilities; historical save arrays retain their fifth slot.
namespace CastleFacilities {
enum Kind { FoodRoom, WeaponRoom, MedicalRoom, DefenseRoom, RoomCount };
struct Facility { const char* name; const char* product; int basePerHour; };
static const int Counts[10]={4,4,4,4,4,4,4,4,4,4};
static const int SectorIndex[10][5]={{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1,2,3}};
static const char* const* Themes=PortraitCastleArt::Names;
// Names follow the live turn-combat turret types, rather than the legacy action-mode table.
static const char* TurretNames[10]={"투석기","화염 탄환포","다연장 미사일포","개틀링포","거대 포탄포","수정 포탄포","냉기 레이저포","자기장 포탑","비전 레이저포","태양 레이저포"};
static const Facility Rooms[10][4]={
 {{"텃밭·닭과 토끼 사육장","골드 생산·저장",0},{"활·무기 제작 공방","히어로 공격력",0},{"개척자의 여관","히어로 최대 체력",0},{"가죽·목제 방패 공방","히어로 방어력",0}},
 {{"숲의 과수 재배실","골드 생산·저장",0},{"화약·포탄 연금 연구실","히어로 공격력",0},{"숲의 약초 회복실","히어로 최대 체력",0},{"나무 장갑·폭압 시험실","히어로 방어력",0}},
 {{"사막 관개 재배실","골드 생산·저장",0},{"유도탄·발사 제어 연구실","히어로 공격력",0},{"사막 약초 수치료실","히어로 최대 체력",0},{"폭압 방호·장갑 시험실","히어로 방어력",0}},
 {{"어류·해조 순환 양식장","골드 생산·저장",0},{"함포 탄도·연사 제어실","히어로 공격력",0},{"해수 수영·수치료실","히어로 최대 체력",0},{"해양 방호·압력 시험실","히어로 방어력",0}},
 {{"빙하 온실 재배실","골드 생산·저장",0},{"중포탄·동력 병기 시험실","히어로 공격력",0},{"빙하 온천·체력단련실","히어로 최대 체력",0},{"중장갑 압력 시험실","히어로 방어력",0}},
 {{"증기 수경 재배실","골드 생산·저장",0},{"수정 에너지·탄환 연구실","히어로 공격력",0},{"기계식 체력·회복 시설","히어로 최대 체력",0},{"자기장 방어 연구실","히어로 방어력",0}},
 {{"화산 온실 재배실","골드 생산·저장",0},{"냉기 레이저 집속 연구실","히어로 공격력",0},{"화산 온천·재활 시설","히어로 최대 체력",0},{"광학 방호·판갑 연구실","히어로 방어력",0}},
 {{"시계탑 수경 재배실","골드 생산·저장",0},{"자기장·탄도 연구실","히어로 공격력",0},{"시계탑 재활 센터","히어로 최대 체력",0},{"자기 차폐·성벽 연구실","히어로 방어력",0}},
 {{"비전 버섯·마법 작물원","골드 생산·저장",0},{"비전 광학·집속 연구실","히어로 공격력",0},{"생체 에너지 회복실","히어로 최대 체력",0},{"수정 결계 제어실","히어로 방어력",0}},
 {{"수정 작물 온실","골드 생산·저장",0},{"태양 레이저·병기 제어실","히어로 공격력",0},{"마력 회복·스파 센터","히어로 최대 체력",0},{"태양 방호막 제어실","히어로 방어력",0}}
};
inline int Output(int castle,int room,int level){
 if(castle<0||castle>=PortraitCastleArt::Count||room<0||room>=RoomCount)return 0;
 level=level<0?0:level>5?5:level;
 return level*(room==FoodRoom?25:room==MedicalRoom?6:4);
}
inline bool Food(int castle,int room){return castle>=0&&castle<PortraitCastleArt::Count&&room==FoodRoom;}
inline bool Armory(int castle,int room){return castle>=0&&castle<PortraitCastleArt::Count&&room==WeaponRoom;}
inline int AttackUpgrade(int castle,int room,int level){return Armory(castle,room)?Output(castle,room,level):0;}
inline const char* Effect(int castle,int room){return room==FoodRoom?"골드 생산량":room==WeaponRoom?"히어로 공격력":room==MedicalRoom?"히어로 최대 체력":"히어로 방어력";}
template<class Progress> inline int Bonus(const Progress& p,int castle,bool energy){
 if(castle<0||castle>=PortraitCastleArt::Count||!(p.owned&(1u<<castle))||energy)return 0;
 return Output(castle,FoodRoom,p.rooms[castle<10?castle:9][FoodRoom]);
}
template<class Progress> inline int StorageBonus(const Progress& p,int castle){return castle>=0&&castle<PortraitCastleArt::Count?p.rooms[castle<10?castle:9][FoodRoom]*50:0;}
}
