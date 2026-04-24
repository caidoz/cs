#pragma once

#ifndef _DEF_ENEMY_H_
#define _DEF_ENEMY_H_

typedef enum _enemyDef {

	//몬스터 디파인
	ENEMY_SNAIL = 3,	//가시껍질 달팽이
	ENEMY_TREE,	//늪의 주인 4
	ENEMY_ONEEYE,	//아이볼 5
	ENEMY_SKELETON,	//칠흑의 기사 6 
	ENEMY_LIZARD,	//사하긴 병사 7
	ENEMY_JELLYFISH,	//맹독 해파리8
	ENEMY_KNIGHT,	//타락한 기사 9
	ENEMY_SLIME,	//슬라임 10
	ENEMY_SLING,	//평원의 도적 11
	ENEMY_BOAR,	//거친발 멧돼지 12
	ENEMY_FLAME,	//분노의 정령 13
	ENEMY_PHOENIX,	//마성의 불새14
	ENEMY_FACE,	//결빙의 석상15
	ENEMY_SNOWMAN,	//스노우맨16
	ENEMY_ICESUN,	//아이스마스크17
	ENEMY_LIGHTNING,	//스파크18//
	ENEMY_THUNDER,	//다크미스트19 //버그 : (소환시)이동을 안함.
	ENEMY_CRYSTAL,	//스파크 플랜트20 //버그 : (소환시)생성된 스파크가 아군을 공격함
	ENEMY_FAIRY,	//라이트 스피릿21 //버그 : (소환시) 나를 공격함
	ENEMY_CIRCLE,	//딜루젼 소울22
	ENEMY_SPIDER,	//스트라이더23 //버그 : (소환시) 레이저를 안쏨 혹은 안그려짐
	ENEMY_GOLEM,	//주인잃은 골렘24
	ENEMY_DARKGIANT,	//그레이트 아머25
	ENEMY_DARKDRAGON,	//우로보로스26(x 예는 그냥 안됨, 그래도 살려보자.)
	ENEMY_DRAGON1,	//탐욕의 살육자27 //(소환시) 공격모션은 주지만 실제 데미지가 안들어간다.
	ENEMY_DRAGON2,	//드래곤 좀비28 //(소환시) 브레스가 안보인다.
	ENEMY_GHOST,	//떠도는 영혼29 //
	ENEMY_PUMPKIN,	//무혼의 기사30
	ENEMY_CASTLE1,	//어둠의 마도사	//텔레포트공격하는놈31		//문제 : 사라지면 안돌아옴(?) //(소환시) 총탄이 안나가고 데미지가 안들어감
	ENEMY_CASTLE2,	//공허한 갑주	//큰 기사32
	ENEMY_SPACE1,	//안드로볼33
	ENEMY_SPACE2,	//메탈가우스34 //(소환시) 총탄은 쏘는데 우리편이 맞는다.
	ENEMY_FROG,	//토드뮤턴트35 //(소환시) 혓바닥이 위치가 올라가고 데미지가 뜨지 않는다.
	ENEMY_LARVA,	//아르곤36
	ENEMY_SALAMANDER,	//카툼37
	ENEMY_GIANT,	//고대의 수호자38 //(소환시)불렛이 나갈 때 아군을 공격함
	ENEMY_IFRIT,	//이프리트39
	ENEMY_MAMMOTH,	//프로스트40
	ENEMY_MACHINE,	//라이오너41
	ENEMY_ANGEL,	//호루스42 //(소환시)불렛이 나갈 때 아군도 공격함
	ENEMY_KIMERA,	//마도합성수43
	ENEMY_SHIP,	//고대의 방주44 (x)//(소환시)에러발생
	ENEMY_FOGRA,	//아리만45 //(소환시) 보조 구체가 사라지지 않고 레이저 쏠때는 적만 공격하는데 그 뒤에는 아군 공격
	ENEMY_BAHAMUT,	//티어맷46 (x) (소환시) 등장할 때 몸통에 머리가 안붙어서 떨어져서 나오고 공격을 하지 않아서 그냥 계속 연타중
	ENEMY_DEATH,	//사신47 //(소환시) 한번 공격을 한 뒤에 사라지지를 않는다.
	ENEMY_CASTLE_BOSS1,	//데브리온48 (x) //(소환시) 피아를 가리지 않고 공격하고, 엄청나게 느려진다. 
	ENEMY_CASTLE_BOSS2,	//엘케인맨티스49
	ENEMY_CASTLE_BOSS3,	//쉐도우 테트라쿤50 -> 제외 (x) //(소환시) 처음에 골조가 먼저 보이고 계속 연타를 때리다가 헤드가 사라져도 계속 남아있다.(레이저는 제대로 나감)
	ENEMY_CASTLE_BOSS4,	//다크나이트51						//(소환시) 손이 등장하고 나중에 끝나도 남아있다.
	ENEMY_LABETH,	//라베스 보스52 (x)//(소환시) 등장할 때 공격판정, 스킬 쓴 다음에 사라지지 않아서 계속 판정.
	ENEMY_ELKEIN,	//엘케인 보스53				//문제 여기서부터 4개가 어딘가 화면을 깨지게 함

	ENEMY_SNAIL_RED,	//가시껍질 달팽이
	ENEMY_TREE_RED,	//늪의 주인 4
	ENEMY_ONEEYE_RED,	//아이볼 5
	ENEMY_SKELETON_RED,	//칠흑의 기사 6 
	ENEMY_LIZARD_RED,	//사하긴 병사 7
	ENEMY_JELLYFISH_RED,	//맹독 해파리8
	ENEMY_KNIGHT_RED,	//타락한 기사 9
	ENEMY_SLIME_RED,	//슬라임 10
	ENEMY_SLING_RED,	//평원의 도적 11
	ENEMY_BOAR_RED,	//거친발 멧돼지 12
	ENEMY_FLAME_RED,	//분노의 정령 13
	ENEMY_PHOENIX_RED,	//마성의 불새14
	ENEMY_FACE_RED,	//결빙의 석상15
	ENEMY_SNOWMAN_RED,	//스노우맨16
	ENEMY_ICESUN_RED,	//아이스마스크17
	ENEMY_LIGHTNING_RED,	//스파크18
	ENEMY_THUNDER_RED,	//다크미스트19
	ENEMY_CRYSTAL_RED,	//스파크 플랜트20
	ENEMY_FAIRY_RED,	//라이트 스피릿21
	ENEMY_CIRCLE_RED,	//딜루젼 소울22
	ENEMY_SPIDER_RED,	//스트라이더23
	ENEMY_GOLEM_RED,	//주인잃은 골렘24
	ENEMY_DARKGIANT_RED,	//그레이트 아머25
	ENEMY_DARKDRAGON_RED,	//우로보로스26
	ENEMY_DRAGON1_RED,	//탐욕의 살육자27
	ENEMY_DRAGON2_RED,	//드래곤 좀비28
	ENEMY_GHOST_RED,	//떠도는 영혼29
	ENEMY_PUMPKIN_RED,	//무혼의 기사30
	ENEMY_CASTLE1_RED,	//어둠의 마도사	//텔레포트공격하는놈31		//문제 : 사라지면 안돌아옴
	ENEMY_CASTLE2_RED,	//공허한 갑주	//큰 기사32
	ENEMY_SPACE1_RED,	//안드로볼33
	ENEMY_SPACE2_RED,	//메탈가우스34
	ENEMY_FROG_RED,	//토드뮤턴트35
	ENEMY_LARVA_RED,	//아르곤36
	ENEMY_SALAMANDER_RED,	//카툼37
	ENEMY_GIANT_RED,	//고대의 수호자38
	ENEMY_IFRIT_RED,	//이프리트39
	ENEMY_MAMMOTH_RED,	//프로스트40
	ENEMY_MACHINE_RED,	//라이오너41					//문제 : 모션이 기계 모션이 나옴
	ENEMY_ANGEL_RED,	//호루스42
	ENEMY_KIMERA_RED,	//마도합성수43
	ENEMY_SHIP_RED,	//고대의 방주44
	ENEMY_FOGRA_RED,	//아리만45
	ENEMY_BAHAMUT_RED,	//티어맷46
	ENEMY_DEATH_RED,	//사신47
	ENEMY_CASTLE_BOSS1_RED,	//데브리온48
	ENEMY_CASTLE_BOSS2_RED,	//엘케인맨티스49
	ENEMY_CASTLE_BOSS3_RED,	//쉐도우 테트라쿤50 -> 제외
	ENEMY_CASTLE_BOSS4_RED,	//다크나이트51						//문제 위에 떠서 나옴
	ENEMY_LABETH_RED,	//라베스 보스52
	ENEMY_ELKEIN_RED,	//엘케인 보스53				//문제 여기서부터 4개가 어딘가 화면을 깨지게 함

	ENEMY_SNAIL_BLUE,	//가시껍질 달팽이
	ENEMY_TREE_BLUE,	//늪의 주인 4
	ENEMY_ONEEYE_BLUE,	//아이볼 5
	ENEMY_SKELETON_BLUE,	//칠흑의 기사 6 
	ENEMY_LIZARD_BLUE,	//사하긴 병사 7
	ENEMY_JELLYFISH_BLUE,	//맹독 해파리8
	ENEMY_KNIGHT_BLUE,	//타락한 기사 9
	ENEMY_SLIME_BLUE,	//슬라임 10
	ENEMY_SLING_BLUE,	//평원의 도적 11
	ENEMY_BOAR_BLUE,	//거친발 멧돼지 12
	ENEMY_FLAME_BLUE,	//분노의 정령 13
	ENEMY_PHOENIX_BLUE,	//마성의 불새14
	ENEMY_FACE_BLUE,	//결빙의 석상15
	ENEMY_SNOWMAN_BLUE,	//스노우맨16
	ENEMY_ICESUN_BLUE,	//아이스마스크17
	ENEMY_LIGHTNING_BLUE,	//스파크18
	ENEMY_THUNDER_BLUE,	//다크미스트19
	ENEMY_CRYSTAL_BLUE,	//스파크 플랜트20
	ENEMY_FAIRY_BLUE,	//라이트 스피릿21
	ENEMY_CIRCLE_BLUE,	//딜루젼 소울22
	ENEMY_SPIDER_BLUE,	//스트라이더23
	ENEMY_GOLEM_BLUE,	//주인잃은 골렘24
	ENEMY_DARKGIANT_BLUE,	//그레이트 아머25
	ENEMY_DARKDRAGON_BLUE,	//우로보로스26
	ENEMY_DRAGON1_BLUE,	//탐욕의 살육자27
	ENEMY_DRAGON2_BLUE,	//드래곤 좀비28
	ENEMY_GHOST_BLUE,	//떠도는 영혼29
	ENEMY_PUMPKIN_BLUE,	//무혼의 기사30
	ENEMY_CASTLE1_BLUE,	//어둠의 마도사	//텔레포트공격하는놈31		//문제 : 사라지면 안돌아옴
	ENEMY_CASTLE2_BLUE,	//공허한 갑주	//큰 기사32
	ENEMY_SPACE1_BLUE,	//안드로볼33
	ENEMY_SPACE2_BLUE,	//메탈가우스34
	ENEMY_FROG_BLUE,	//토드뮤턴트35
	ENEMY_LARVA_BLUE,	//아르곤36
	ENEMY_SALAMANDER_BLUE,	//카툼37
	ENEMY_GIANT_BLUE,	//고대의 수호자38
	ENEMY_IFRIT_BLUE,	//이프리트39
	ENEMY_MAMMOTH_BLUE,	//프로스트40
	ENEMY_MACHINE_BLUE,	//라이오너41					//문제 : 모션이 기계 모션이 나옴
	ENEMY_ANGEL_BLUE,	//호루스42
	ENEMY_KIMERA_BLUE,	//마도합성수43
	ENEMY_SHIP_BLUE,	//고대의 방주44
	ENEMY_FOGRA_BLUE,	//아리만45
	ENEMY_BAHAMUT_BLUE,	//티어맷46
	ENEMY_DEATH_BLUE,	//사신47
	ENEMY_CASTLE_BOSS1_BLUE,	//데브리온48
	ENEMY_CASTLE_BOSS2_BLUE,	//엘케인맨티스49
	ENEMY_CASTLE_BOSS3_BLUE,	//쉐도우 테트라쿤50 -> 제외
	ENEMY_CASTLE_BOSS4_BLUE,	//다크나이트51						//문제 위에 떠서 나옴
	ENEMY_LABETH_BLUE,	//라베스 보스52
	ENEMY_ELKEIN_BLUE,	//엘케인 보스53				//문제 여기서부터 4개가 어딘가 화면을 깨지게 함

	ENEMY_SNAIL_PURPLE,	//가시껍질 달팽이
	ENEMY_TREE_PURPLE,	//늪의 주인 4
	ENEMY_ONEEYE_PURPLE,	//아이볼 5
	ENEMY_SKELETON_PURPLE,	//칠흑의 기사 6 
	ENEMY_LIZARD_PURPLE,	//사하긴 병사 7
	ENEMY_JELLYFISH_PURPLE,	//맹독 해파리8
	ENEMY_KNIGHT_PURPLE,	//타락한 기사 9
	ENEMY_SLIME_PURPLE,	//슬라임 10
	ENEMY_SLING_PURPLE,	//평원의 도적 11
	ENEMY_BOAR_PURPLE,	//거친발 멧돼지 12
	ENEMY_FLAME_PURPLE,	//분노의 정령 13
	ENEMY_PHOENIX_PURPLE,	//마성의 불새14
	ENEMY_FACE_PURPLE,	//결빙의 석상15
	ENEMY_SNOWMAN_PURPLE,	//스노우맨16
	ENEMY_ICESUN_PURPLE,	//아이스마스크17
	ENEMY_LIGHTNING_PURPLE,	//스파크18
	ENEMY_THUNDER_PURPLE,	//다크미스트19
	ENEMY_CRYSTAL_PURPLE,	//스파크 플랜트20
	ENEMY_FAIRY_PURPLE,	//라이트 스피릿2     1
	ENEMY_CIRCLE_PURPLE,	//딜루젼 소울22
	ENEMY_SPIDER_PURPLE,	//스트라이더25
	ENEMY_GOLEM_PURPLE,	//주인잃은 골렘26
	ENEMY_DARKGIANT_PURPLE,	//그레이트 아머27
	ENEMY_DARKDRAGON_PURPLE,	//우로보로스28
	ENEMY_DRAGON1_PURPLE,	//탐욕의 살육자29
	ENEMY_DRAGON2_PURPLE,	//드래곤 좀비30
	ENEMY_GHOST_PURPLE,	//떠도는 영혼31
	ENEMY_PUMPKIN_PURPLE,	//무혼의 기사32
	ENEMY_CASTLE1_PURPLE,	//어둠의 마도사	//텔레포트공격하는놈33		//문제 : 사라지면 안돌아옴
	ENEMY_CASTLE2_PURPLE,	//공허한 갑주	//큰 기사34
	ENEMY_SPACE1_PURPLE,	//안드로볼35
	ENEMY_SPACE2_PURPLE,	//메탈가우스36
	ENEMY_FROG_PURPLE,	//토드뮤턴트37
	ENEMY_LARVA_PURPLE,	//아르곤38
	ENEMY_SALAMANDER_PURPLE,	//카툼39
	ENEMY_GIANT_PURPLE,	//고대의 수호자40
	ENEMY_IFRIT_PURPLE,	//이프리트41
	ENEMY_MAMMOTH_PURPLE,	//프로스트42
	ENEMY_MACHINE_PURPLE,	//라이오너43					//문제 : 모션이 기계 모션이 나옴
	ENEMY_ANGEL_PURPLE,	//호루스44
	ENEMY_KIMERA_PURPLE,	//마도합성수45
	ENEMY_SHIP_PURPLE,	//고대의 방주46
	ENEMY_FOGRA_PURPLE,	//아리만47
	ENEMY_BAHAMUT_PURPLE,	//티어맷48
	ENEMY_DEATH_PURPLE,	//사신49
	ENEMY_CASTLE_BOSS1_PURPLE,	//데브리온50
	ENEMY_CASTLE_BOSS2_PURPLE,	//엘케인맨티스51
	ENEMY_CASTLE_BOSS3_PURPLE,	//쉐도우 테트라쿤52 -> 제외
	ENEMY_CASTLE_BOSS4_PURPLE,	//다크나이트53						//문제 위에 떠서 나옴
	ENEMY_LABETH_PURPLE,	//라베스 보스54
	ENEMY_ELKEIN_PURPLE,	//엘케인 보스55				//문제 여기서부터 4개가 어딘가 화면을 깨지게 함

	ENEMY_SNAIL_GREEN,	//가시껍질 달팽이
	ENEMY_TREE_GREEN,	//늪의 주인 4
	ENEMY_ONEEYE_GREEN,	//아이볼 5
	ENEMY_SKELETON_GREEN,	//칠흑의 기사 6 
	ENEMY_LIZARD_GREEN,	//사하긴 병사 7
	ENEMY_JELLYFISH_GREEN,	//맹독 해파리8
	ENEMY_KNIGHT_GREEN,	//타락한 기사 9
	ENEMY_SLIME_GREEN,	//슬라임 10
	ENEMY_SLING_GREEN,	//평원의 도적 11
	ENEMY_BOAR_GREEN,	//거친발 멧돼지 12
	ENEMY_FLAME_GREEN,	//분노의 정령 13
	ENEMY_PHOENIX_GREEN,	//마성의 불새14
	ENEMY_FACE_GREEN,	//결빙의 석상15
	ENEMY_SNOWMAN_GREEN,	//스노우맨16
	ENEMY_ICESUN_GREEN,	//아이스마스크17
	ENEMY_LIGHTNING_GREEN,	//스파크18
	ENEMY_THUNDER_GREEN,	//다크미스트19
	ENEMY_CRYSTAL_GREEN,	//스파크 플랜트20
	ENEMY_FAIRY_GREEN,	//라이트 스피릿2     1
	ENEMY_CIRCLE_GREEN,	//딜루젼 소울22
	ENEMY_SPIDER_GREEN,	//스트라이더25
	ENEMY_GOLEM_GREEN,	//주인잃은 골렘26
	ENEMY_DARKGIANT_GREEN,	//그레이트 아머27
	ENEMY_DARKDRAGON_GREEN,	//우로보로스28
	ENEMY_DRAGON1_GREEN,	//탐욕의 살육자29
	ENEMY_DRAGON2_GREEN,	//드래곤 좀비30
	ENEMY_GHOST_GREEN,	//떠도는 영혼31
	ENEMY_PUMPKIN_GREEN,	//무혼의 기사32
	ENEMY_CASTLE1_GREEN,	//어둠의 마도사	//텔레포트공격하는놈33		//문제 : 사라지면 안돌아옴
	ENEMY_CASTLE2_GREEN,	//공허한 갑주	//큰 기사34
	ENEMY_SPACE1_GREEN,	//안드로볼35
	ENEMY_SPACE2_GREEN,	//메탈가우스36
	ENEMY_FROG_GREEN,	//토드뮤턴트37
	ENEMY_LARVA_GREEN,	//아르곤38
	ENEMY_SALAMANDER_GREEN,	//카툼39
	ENEMY_GIANT_GREEN,	//고대의 수호자40
	ENEMY_IFRIT_GREEN,	//이프리트41
	ENEMY_MAMMOTH_GREEN,	//프로스트42
	ENEMY_MACHINE_GREEN,	//라이오너43					//문제 : 모션이 기계 모션이 나옴
	ENEMY_ANGEL_GREEN,	//호루스44
	ENEMY_KIMERA_GREEN,	//마도합성수45
	ENEMY_SHIP_GREEN,	//고대의 방주46
	ENEMY_FOGRA_GREEN,	//아리만47
	ENEMY_BAHAMUT_GREEN,	//티어맷48
	ENEMY_DEATH_GREEN,	//사신49
	ENEMY_CASTLE_BOSS1_GREEN,	//데브리온50
	ENEMY_CASTLE_BOSS2_GREEN,	//엘케인맨티스51
	ENEMY_CASTLE_BOSS3_GREEN,	//쉐도우 테트라쿤52 -> 제외
	ENEMY_CASTLE_BOSS4_GREEN,	//다크나이트53						//문제 위에 떠서 나옴
	ENEMY_LABETH_GREEN,	//라베스 보스54
	ENEMY_ELKEIN_GREEN,	//엘케인 보스55				//문제 여기서부터 4개가 어딘가 화면을 깨지게 함

	ENEMY_SNAIL_GOLD,	//가시껍질 달팽이
	ENEMY_TREE_GOLD,	//늪의 주인 4
	ENEMY_ONEEYE_GOLD,	//아이볼 5
	ENEMY_SKELETON_GOLD,	//칠흑의 기사 6 
	ENEMY_LIZARD_GOLD,	//사하긴 병사 7
	ENEMY_JELLYFISH_GOLD,	//맹독 해파리8
	ENEMY_KNIGHT_GOLD,	//타락한 기사 9
	ENEMY_SLIME_GOLD,	//슬라임 10
	ENEMY_SLING_GOLD,	//평원의 도적 11
	ENEMY_BOAR_GOLD,	//거친발 멧돼지 12
	ENEMY_FLAME_GOLD,	//분노의 정령 13
	ENEMY_PHOENIX_GOLD,	//마성의 불새14
	ENEMY_FACE_GOLD,	//결빙의 석상15
	ENEMY_SNOWMAN_GOLD,	//스노우맨16
	ENEMY_ICESUN_GOLD,	//아이스마스크17
	ENEMY_LIGHTNING_GOLD,	//스파크18
	ENEMY_THUNDER_GOLD,	//다크미스트19
	ENEMY_CRYSTAL_GOLD,	//스파크 플랜트20
	ENEMY_FAIRY_GOLD,	//라이트 스피릿2     1
	ENEMY_CIRCLE_GOLD,	//딜루젼 소울22
	ENEMY_SPIDER_GOLD,	//스트라이더25
	ENEMY_GOLEM_GOLD,	//주인잃은 골렘26
	ENEMY_DARKGIANT_GOLD,	//그레이트 아머27
	ENEMY_DARKDRAGON_GOLD,	//우로보로스28
	ENEMY_DRAGON1_GOLD,	//탐욕의 살육자29
	ENEMY_DRAGON2_GOLD,	//드래곤 좀비30
	ENEMY_GHOST_GOLD,	//떠도는 영혼31
	ENEMY_PUMPKIN_GOLD,	//무혼의 기사32
	ENEMY_CASTLE1_GOLD,	//어둠의 마도사	//텔레포트공격하는놈33		//문제 : 사라지면 안돌아옴
	ENEMY_CASTLE2_GOLD,	//공허한 갑주	//큰 기사34
	ENEMY_SPACE1_GOLD,	//안드로볼35
	ENEMY_SPACE2_GOLD,	//메탈가우스36
	ENEMY_FROG_GOLD,	//토드뮤턴트37
	ENEMY_LARVA_GOLD,	//아르곤38
	ENEMY_SALAMANDER_GOLD,	//카툼39
	ENEMY_GIANT_GOLD,	//고대의 수호자40
	ENEMY_IFRIT_GOLD,	//이프리트41
	ENEMY_MAMMOTH_GOLD,	//프로스트42
	ENEMY_MACHINE_GOLD,	//라이오너43					//문제 : 모션이 기계 모션이 나옴
	ENEMY_ANGEL_GOLD,	//호루스44
	ENEMY_KIMERA_GOLD,	//마도합성수45
	ENEMY_SHIP_GOLD,	//고대의 방주46
	ENEMY_FOGRA_GOLD,	//아리만47
	ENEMY_BAHAMUT_GOLD,	//티어맷48
	ENEMY_DEATH_GOLD,	//사신49
	ENEMY_CASTLE_BOSS1_GOLD,	//데브리온50
	ENEMY_CASTLE_BOSS2_GOLD,	//엘케인맨티스51
	ENEMY_CASTLE_BOSS3_GOLD,	//쉐도우 테트라쿤52 -> 제외
	ENEMY_CASTLE_BOSS4_GOLD,	//다크나이트53						//문제 위에 떠서 나옴
	ENEMY_LABETH_GOLD,	//라베스 보스54
	ENEMY_ELKEIN_GOLD,	//엘케인 보스55				//문제 여기서부터 4개가 어딘가 화면을 깨지게 함

	ENEMY_SNAIL_BLACK,	//가시껍질 달팽이
	ENEMY_TREE_BLACK,	//늪의 주인 4
	ENEMY_ONEEYE_BLACK,	//아이볼 5
	ENEMY_SKELETON_BLACK,	//칠흑의 기사 6 
	ENEMY_LIZARD_BLACK,	//사하긴 병사 7
	ENEMY_JELLYFISH_BLACK,	//맹독 해파리8
	ENEMY_KNIGHT_BLACK,	//타락한 기사 9
	ENEMY_SLIME_BLACK,	//슬라임 10
	ENEMY_SLING_BLACK,	//평원의 도적 11
	ENEMY_BOAR_BLACK,	//거친발 멧돼지 12
	ENEMY_FLAME_BLACK,	//분노의 정령 13
	ENEMY_PHOENIX_BLACK,	//마성의 불새14
	ENEMY_FACE_BLACK,	//결빙의 석상15
	ENEMY_SNOWMAN_BLACK,	//스노우맨16
	ENEMY_ICESUN_BLACK,	//아이스마스크17
	ENEMY_LIGHTNING_BLACK,	//스파크18
	ENEMY_THUNDER_BLACK,	//다크미스트19
	ENEMY_CRYSTAL_BLACK,	//스파크 플랜트20
	ENEMY_FAIRY_BLACK,	//라이트 스피릿2     1
	ENEMY_CIRCLE_BLACK,	//딜루젼 소울22
	ENEMY_SPIDER_BLACK,	//스트라이더25
	ENEMY_GOLEM_BLACK,	//주인잃은 골렘26
	ENEMY_DARKGIANT_BLACK,	//그레이트 아머27
	ENEMY_DARKDRAGON_BLACK,	//우로보로스28
	ENEMY_DRAGON1_BLACK,	//탐욕의 살육자29
	ENEMY_DRAGON2_BLACK,	//드래곤 좀비30
	ENEMY_GHOST_BLACK,	//떠도는 영혼31
	ENEMY_PUMPKIN_BLACK,	//무혼의 기사32
	ENEMY_CASTLE1_BLACK,	//어둠의 마도사	//텔레포트공격하는놈33		//문제 : 사라지면 안돌아옴
	ENEMY_CASTLE2_BLACK,	//공허한 갑주	//큰 기사34
	ENEMY_SPACE1_BLACK,	//안드로볼35
	ENEMY_SPACE2_BLACK,	//메탈가우스36
	ENEMY_FROG_BLACK,	//토드뮤턴트37
	ENEMY_LARVA_BLACK,	//아르곤38
	ENEMY_SALAMANDER_BLACK,	//카툼39
	ENEMY_GIANT_BLACK,	//고대의 수호자40
	ENEMY_IFRIT_BLACK,	//이프리트41
	ENEMY_MAMMOTH_BLACK,	//프로스트42
	ENEMY_MACHINE_BLACK,	//라이오너43					//문제 : 모션이 기계 모션이 나옴
	ENEMY_ANGEL_BLACK,	//호루스44
	ENEMY_KIMERA_BLACK,	//마도합성수45
	ENEMY_SHIP_BLACK,	//고대의 방주46
	ENEMY_FOGRA_BLACK,	//아리만47
	ENEMY_BAHAMUT_BLACK,	//티어맷48
	ENEMY_DEATH_BLACK,	//사신49
	ENEMY_CASTLE_BOSS1_BLACK,	//데브리온50
	ENEMY_CASTLE_BOSS2_BLACK,	//엘케인맨티스51
	ENEMY_CASTLE_BOSS3_BLACK,	//쉐도우 테트라쿤52 -> 제외
	ENEMY_CASTLE_BOSS4_BLACK,	//다크나이트53						//문제 위에 떠서 나옴
	ENEMY_LABETH_BLACK,	//라베스 보스54
	ENEMY_ELKEIN_BLACK,	//엘케인 보스55

	NPC_CAPTAIN,//c52//잭스패너//o
	NPC_CREW,//c53//선원//o
	NPC_GRANDFA,//c54//촌장//o
	NPC_UNCLE,//c55//아저씨//o
	NPC_AUNT,//c56//아줌마//o
	NPC_MAN,//c57//자경단청년//o
	NPC_WOMAN,//c58//처녀//o
	NPC_BOY,//c59//꼬마남//o
	NPC_GIRL,//c60//꼬마녀//o
	NPC_ALMA,//c61//알마//o
	NPC_ITEM,//c62//터번//o
	NPC_FATMAN,//c63//o
	NPC_BUNNYGIRL,//c64//o
	NPC_KNIGHT,//c65//플레타//o
	NPC_DOG,//c66//o
	NPC_MERCHANT,//c67//o
	NPC_CRAFTMAN,//c68//o
	NPC_MAP,//c69//o
	NPC_USERQUEST,//c70//스튜어디스//o
	NPC_TRAVEL,//c71//이국의여행자//o
	NPC_GRANDMA,//c72//할머니//o
	NPC_FISHING,//c73//라피//o
	NPC_INN,//c74//o
	NPC_NETITEM,//c75//o
	NPC_MILESE,//c76//o
	NPC_DOBEL,//c77//o
	NPC_GAGEL,//c78//o
	NPC_MONICA,//c79//o
	NPC_SHIP,//c80//o
	NPC_SEASOLDIER,//c81//아틀란병사//o
	NPC_FRAUD,//c82//o
	NPC_DARIAN,//c83//o
	NPC_LUISE,//c84//o
	NPC_SEAUNCLE,//c85//아틀란아저씨//o
	NPC_SEABOY,//c86//아틀란소년//o
	NPC_DONALD,//c87//이소룡//o
	NPC_SCHOLAR,//c88//학자//o
	NPC_CHEF,//c89//요리대가//o
	NPC_BISTRO,//c90//비스트로//o
	NPC_MAID,//c91//시녀//o
	NPC_ADELKNIGHT,//c92//기사//o
	NPC_SEBASTIAN,//c93//세바스찬//o
	NPC_NOBLEMAN,//c94//귀족아저씨//o
	NPC_DELPIOS,//c95//델피오스//o
	NPC_LORA,//c96//로라//o
	NPC_WITCH,//c97//마녀//o
	NPC_ELFGRANDFA,//c98//엘프할아버지/o
	NPC_ELFUNCLE,//c99//엘프아저씨//o
	NPC_ELFAUNT,//c100//엘프아줌마//o
	NPC_ELFMAN,//c101//엘프청년//o
	NPC_ELFWOMAN,//c102//엘프처녀//o
	NPC_ELFBOY,//c103//엘프꼬마남//o
	NPC_ELFGIRL,//c104//엘프꼬마녀//o
	NPC_ELFDARK,//c105//엘프다크//o
	NPC_ELFMAGIC,//c106//엘프마법사//o
	NPC_ELFDANCER,//c107//엘프무희//o
	NPC_OWL,//c108//부엉이//o
	NPC_LABETH,//c109//라베스//o
	NPC_ELKEIN,//c110//엘케인//o
	NPC_ELEIN,//c111//엘레인//o
	NPC_EVAN,//c112//에번//o
	NPC_BEAD,//c113//테이블//o
	NPC_FOUNTAIN,//c114//샘물//o
	NPC_NEZAR,//c115//네자르//o
	NPC_GALLAND,//c116//갈란드//o
	NPC_DURAK,//c117//듀라크//o
	NPC_KING,//c118//에드몬드//o
	NPC_WOMANGHOST,//c119//여자유령//o
	NPC_MANGHOST,//c120//남자유령//o
	NPC_AUSTIN,//c121//오스틴(유령)//o
	NPC_SOUL,//c122//마왕의 심장//o

	TOTALENEMY,

	ENEMY_BULLET_NOSHADOW,
	ENEMY_BULLET_SKEL,

	MAXMONSTER = TOTALENEMY - NPC_CAPTAIN,

	SMALLMONSTER = 0,//공격당하면 뜨는 작은 몬스터
	BIGMONSTER,//공격당하면 뜨지 않고 밀리는 몬스터
	GIANTMONSTER,//아예 안밀리는 몬스터

	ENEMYDATA_CMF = 0,
	ENEMYDATA_MOVEHANDLER,
	ENEMYDATA_DRAWHANDLER,
	ENEMYDATA_ADDHP,
	ENEMYDATA_ADDEXP,

	ENEMYDATA_XPOS,
	ENEMYDATA_YPOS,

	ENEMYDATASIZE,




	

	END_ENEMYDEF
} ENEMYDEF;

#endif
