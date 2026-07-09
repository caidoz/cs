#pragma once

#ifndef _DEF_ENEMY_H_
#define _DEF_ENEMY_H_

typedef enum _enemyDef {

	//몬스???�파??
	ENEMY_SNAIL = 3,	//���ò���������
	ENEMY_TREE,	//���� ���� 4
	ENEMY_ONEEYE,	//���̺� 5
	ENEMY_SKELETON,	//ĥ���� ��� 6 
	ENEMY_LIZARD,	//���ϱ亴�� 7
	ENEMY_JELLYFISH,	//�͵����ĸ� 8
	ENEMY_KNIGHT,	//Ÿ���� ��� 9
	ENEMY_SLIME,	//������ 10
	ENEMY_SLING,	//����� ���� 11
	ENEMY_BOAR,	//��ģ�߸���� 12
	ENEMY_FLAME,	//�г��� ���� 13
	ENEMY_PHOENIX,	//������ �һ� 14
	ENEMY_FACE,	//����� ���� 15
	ENEMY_SNOWMAN,	//������ 16
	ENEMY_ICESUN,	//���̽�����ũ 17
	ENEMY_LIGHTNING,	//����ũ 18
	ENEMY_THUNDER,	//��ũ�̽�Ʈ 19
	ENEMY_CRYSTAL,	//����ũ�÷�Ʈ 20
	ENEMY_FAIRY,	//����Ʈ���Ǹ� 21
	ENEMY_CIRCLE,	//�������ҿ� 22
	ENEMY_SPIDER,	//��Ʈ���̴� 23
	ENEMY_GOLEM,	//주인?��? 골렘24
	ENEMY_DARKGIANT,	//그레?�트 ?�머25
	ENEMY_DARKDRAGON,	//?�로보로??6(x ?�는 그냥 ?�됨, 그래???�려보자.)
	ENEMY_DRAGON1,	//?�욕???�육??7 //(?�환?? 공격모션?� 주�?�??�제 ?��?지가 ?�들?�간??
	ENEMY_DRAGON2,	//?�래�?좀�?8 //(?�환?? 브레?��? ?�보?�다.
	ENEMY_GHOST,	//?�도???�혼29 //
	ENEMY_PUMPKIN,	//무혼??기사30
	ENEMY_CASTLE1,	//?�둠??마도??//?�레?�트공격?�는??1		//문제 : ?�라지�??�돌?�옴(?) //(?�환?? 총탄???�나가�??��?지가 ?�들?�감
	ENEMY_CASTLE2,	//공허??갑주	//??기사32
	ENEMY_SPACE1,	//?�드로볼33
	ENEMY_SPACE2,	//메탈가?�스34 //(?�환?? 총탄?� ?�는???�리?�이 맞는??
	ENEMY_FROG,	//?�드뮤턴??5 //(?�환?? ?�바?�이 ?�치가 ?�라가�??��?지가 ?��? ?�는??
	ENEMY_LARVA,	//?�르�?6
	ENEMY_SALAMANDER,	//카툼37
	ENEMY_GIANT,	//고�????�호??8 //(?�환??불렛???�갈 ???�군??공격??
	ENEMY_IFRIT,	//?�프리트39
	ENEMY_MAMMOTH,	//?�로?�트40
	ENEMY_MACHINE,	//?�이?�너41
	ENEMY_ANGEL,	//?�루??2 //(?�환??불렛???�갈 ???�군??공격??
	ENEMY_KIMERA,	//마도?�성??3
	ENEMY_SHIP,	//고�???방주44 (x)//(?�환???�러발생
	ENEMY_FOGRA,	//?�리�?5 //(?�환?? 보조 구체가 ?�라지지 ?�고 ?�이?� ?�때???�만 공격?�는??�??�에???�군 공격
	ENEMY_BAHAMUT,	//?�어�?6 (x) (?�환?? ?�장????몸통??머리가 ?�붙?�서 ?�어?�서 ?�오�?공격???��? ?�아??그냥 계속 ?��?�?
	ENEMY_DEATH,	//?�신47 //(?�환?? ?�번 공격?????�에 ?�라지지�??�는??
	ENEMY_CASTLE_BOSS1,	//?�브리온48 (x) //(?�환?? ?�아�?가리�? ?�고 공격?�고, ?�청?�게 ?�려진다. 
	ENEMY_CASTLE_BOSS2,	//?��??�맨?�스49
	ENEMY_CASTLE_BOSS3,	//?�도???�트?�쿤50 -> ?�외 (x) //(?�환?? 처음??골조가 먼�? 보이�?계속 ?��?�??�리?��? ?�드가 ?�라?�도 계속 ?�아?�다.(?�이?�???��?�??�감)
	ENEMY_CASTLE_BOSS4,	//?�크?�이??1						//(?�환?? ?�이 ?�장?�고 ?�중???�나???�아?�다.
	ENEMY_LABETH,	//?�베??보스52 (x)//(?�환?? ?�장????공격?�정, ?�킬 ???�음???�라지지 ?�아??계속 ?�정.
	ENEMY_ELKEIN,	//?��???보스53				//문제 ?�기?��???4개�? ?�딘가 ?�면??깨�?�???

	ENEMY_SNAIL_RED,	//가?�껍�??�팽??
	ENEMY_TREE_RED,	//?�의 주인 4
	ENEMY_ONEEYE_RED,	//?�이�?5
	ENEMY_SKELETON_RED,	//칠흑??기사 6 
	ENEMY_LIZARD_RED,	//?�하�?병사 7
	ENEMY_JELLYFISH_RED,	//맹독 ?�파�?
	ENEMY_KNIGHT_RED,	//?�?�한 기사 9
	ENEMY_SLIME_RED,	//?�라??10
	ENEMY_SLING_RED,	//?�원???�적 11
	ENEMY_BOAR_RED,	//거친�?멧돼지 12
	ENEMY_FLAME_RED,	//분노???�령 13
	ENEMY_PHOENIX_RED,	//마성??불새14
	ENEMY_FACE_RED,	//결빙???�상15
	ENEMY_SNOWMAN_RED,	//?�노?�맨16
	ENEMY_ICESUN_RED,	//?�이?�마?�크17
	ENEMY_LIGHTNING_RED,	//?�파??8
	ENEMY_THUNDER_RED,	//?�크미스??9
	ENEMY_CRYSTAL_RED,	//?�파???�랜??0
	ENEMY_FAIRY_RED,	//?�이???�피�?1
	ENEMY_CIRCLE_RED,	//?�루???�울22
	ENEMY_SPIDER_RED,	//?�트?�이??3
	ENEMY_GOLEM_RED,	//주인?��? 골렘24
	ENEMY_DARKGIANT_RED,	//그레?�트 ?�머25
	ENEMY_DARKDRAGON_RED,	//?�로보로??6
	ENEMY_DRAGON1_RED,	//?�욕???�육??7
	ENEMY_DRAGON2_RED,	//?�래�?좀�?8
	ENEMY_GHOST_RED,	//?�도???�혼29
	ENEMY_PUMPKIN_RED,	//무혼??기사30
	ENEMY_CASTLE1_RED,	//?�둠??마도??//?�레?�트공격?�는??1		//문제 : ?�라지�??�돌?�옴
	ENEMY_CASTLE2_RED,	//공허??갑주	//??기사32
	ENEMY_SPACE1_RED,	//?�드로볼33
	ENEMY_SPACE2_RED,	//메탈가?�스34
	ENEMY_FROG_RED,	//?�드뮤턴??5
	ENEMY_LARVA_RED,	//?�르�?6
	ENEMY_SALAMANDER_RED,	//카툼37
	ENEMY_GIANT_RED,	//고�????�호??8
	ENEMY_IFRIT_RED,	//?�프리트39
	ENEMY_MAMMOTH_RED,	//?�로?�트40
	ENEMY_MACHINE_RED,	//?�이?�너41					//문제 : 모션??기계 모션???�옴
	ENEMY_ANGEL_RED,	//?�루??2
	ENEMY_KIMERA_RED,	//마도?�성??3
	ENEMY_SHIP_RED,	//고�???방주44
	ENEMY_FOGRA_RED,	//?�리�?5
	ENEMY_BAHAMUT_RED,	//?�어�?6
	ENEMY_DEATH_RED,	//?�신47
	ENEMY_CASTLE_BOSS1_RED,	//?�브리온48
	ENEMY_CASTLE_BOSS2_RED,	//?��??�맨?�스49
	ENEMY_CASTLE_BOSS3_RED,	//?�도???�트?�쿤50 -> ?�외
	ENEMY_CASTLE_BOSS4_RED,	//?�크?�이??1						//문제 ?�에 ?�서 ?�옴
	ENEMY_LABETH_RED,	//?�베??보스52
	ENEMY_ELKEIN_RED,	//?��???보스53				//문제 ?�기?��???4개�? ?�딘가 ?�면??깨�?�???

	ENEMY_SNAIL_BLUE,	//가?�껍�??�팽??
	ENEMY_TREE_BLUE,	//?�의 주인 4
	ENEMY_ONEEYE_BLUE,	//?�이�?5
	ENEMY_SKELETON_BLUE,	//칠흑??기사 6 
	ENEMY_LIZARD_BLUE,	//?�하�?병사 7
	ENEMY_JELLYFISH_BLUE,	//맹독 ?�파�?
	ENEMY_KNIGHT_BLUE,	//?�?�한 기사 9
	ENEMY_SLIME_BLUE,	//?�라??10
	ENEMY_SLING_BLUE,	//?�원???�적 11
	ENEMY_BOAR_BLUE,	//거친�?멧돼지 12
	ENEMY_FLAME_BLUE,	//분노???�령 13
	ENEMY_PHOENIX_BLUE,	//마성??불새14
	ENEMY_FACE_BLUE,	//결빙???�상15
	ENEMY_SNOWMAN_BLUE,	//?�노?�맨16
	ENEMY_ICESUN_BLUE,	//?�이?�마?�크17
	ENEMY_LIGHTNING_BLUE,	//?�파??8
	ENEMY_THUNDER_BLUE,	//?�크미스??9
	ENEMY_CRYSTAL_BLUE,	//?�파???�랜??0
	ENEMY_FAIRY_BLUE,	//?�이???�피�?1
	ENEMY_CIRCLE_BLUE,	//?�루???�울22
	ENEMY_SPIDER_BLUE,	//?�트?�이??3
	ENEMY_GOLEM_BLUE,	//주인?��? 골렘24
	ENEMY_DARKGIANT_BLUE,	//그레?�트 ?�머25
	ENEMY_DARKDRAGON_BLUE,	//?�로보로??6
	ENEMY_DRAGON1_BLUE,	//?�욕???�육??7
	ENEMY_DRAGON2_BLUE,	//?�래�?좀�?8
	ENEMY_GHOST_BLUE,	//?�도???�혼29
	ENEMY_PUMPKIN_BLUE,	//무혼??기사30
	ENEMY_CASTLE1_BLUE,	//?�둠??마도??//?�레?�트공격?�는??1		//문제 : ?�라지�??�돌?�옴
	ENEMY_CASTLE2_BLUE,	//공허??갑주	//??기사32
	ENEMY_SPACE1_BLUE,	//?�드로볼33
	ENEMY_SPACE2_BLUE,	//메탈가?�스34
	ENEMY_FROG_BLUE,	//?�드뮤턴??5
	ENEMY_LARVA_BLUE,	//?�르�?6
	ENEMY_SALAMANDER_BLUE,	//카툼37
	ENEMY_GIANT_BLUE,	//고�????�호??8
	ENEMY_IFRIT_BLUE,	//?�프리트39
	ENEMY_MAMMOTH_BLUE,	//?�로?�트40
	ENEMY_MACHINE_BLUE,	//?�이?�너41					//문제 : 모션??기계 모션???�옴
	ENEMY_ANGEL_BLUE,	//?�루??2
	ENEMY_KIMERA_BLUE,	//마도?�성??3
	ENEMY_SHIP_BLUE,	//고�???방주44
	ENEMY_FOGRA_BLUE,	//?�리�?5
	ENEMY_BAHAMUT_BLUE,	//?�어�?6
	ENEMY_DEATH_BLUE,	//?�신47
	ENEMY_CASTLE_BOSS1_BLUE,	//?�브리온48
	ENEMY_CASTLE_BOSS2_BLUE,	//?��??�맨?�스49
	ENEMY_CASTLE_BOSS3_BLUE,	//?�도???�트?�쿤50 -> ?�외
	ENEMY_CASTLE_BOSS4_BLUE,	//?�크?�이??1						//문제 ?�에 ?�서 ?�옴
	ENEMY_LABETH_BLUE,	//?�베??보스52
	ENEMY_ELKEIN_BLUE,	//?��???보스53				//문제 ?�기?��???4개�? ?�딘가 ?�면??깨�?�???

	ENEMY_SNAIL_PURPLE,	//가?�껍�??�팽??
	ENEMY_TREE_PURPLE,	//?�의 주인 4
	ENEMY_ONEEYE_PURPLE,	//?�이�?5
	ENEMY_SKELETON_PURPLE,	//칠흑??기사 6 
	ENEMY_LIZARD_PURPLE,	//?�하�?병사 7
	ENEMY_JELLYFISH_PURPLE,	//맹독 ?�파�?
	ENEMY_KNIGHT_PURPLE,	//?�?�한 기사 9
	ENEMY_SLIME_PURPLE,	//?�라??10
	ENEMY_SLING_PURPLE,	//?�원???�적 11
	ENEMY_BOAR_PURPLE,	//거친�?멧돼지 12
	ENEMY_FLAME_PURPLE,	//분노???�령 13
	ENEMY_PHOENIX_PURPLE,	//마성??불새14
	ENEMY_FACE_PURPLE,	//결빙???�상15
	ENEMY_SNOWMAN_PURPLE,	//?�노?�맨16
	ENEMY_ICESUN_PURPLE,	//?�이?�마?�크17
	ENEMY_LIGHTNING_PURPLE,	//?�파??8
	ENEMY_THUNDER_PURPLE,	//?�크미스??9
	ENEMY_CRYSTAL_PURPLE,	//?�파???�랜??0
	ENEMY_FAIRY_PURPLE,	//?�이???�피�?     1
	ENEMY_CIRCLE_PURPLE,	//?�루???�울22
	ENEMY_SPIDER_PURPLE,	//?�트?�이??5
	ENEMY_GOLEM_PURPLE,	//주인?��? 골렘26
	ENEMY_DARKGIANT_PURPLE,	//그레?�트 ?�머27
	ENEMY_DARKDRAGON_PURPLE,	//?�로보로??8
	ENEMY_DRAGON1_PURPLE,	//?�욕???�육??9
	ENEMY_DRAGON2_PURPLE,	//?�래�?좀�?0
	ENEMY_GHOST_PURPLE,	//?�도???�혼31
	ENEMY_PUMPKIN_PURPLE,	//무혼??기사32
	ENEMY_CASTLE1_PURPLE,	//?�둠??마도??//?�레?�트공격?�는??3		//문제 : ?�라지�??�돌?�옴
	ENEMY_CASTLE2_PURPLE,	//공허??갑주	//??기사34
	ENEMY_SPACE1_PURPLE,	//?�드로볼35
	ENEMY_SPACE2_PURPLE,	//메탈가?�스36
	ENEMY_FROG_PURPLE,	//?�드뮤턴??7
	ENEMY_LARVA_PURPLE,	//?�르�?8
	ENEMY_SALAMANDER_PURPLE,	//카툼39
	ENEMY_GIANT_PURPLE,	//고�????�호??0
	ENEMY_IFRIT_PURPLE,	//?�프리트41
	ENEMY_MAMMOTH_PURPLE,	//?�로?�트42
	ENEMY_MACHINE_PURPLE,	//?�이?�너43					//문제 : 모션??기계 모션???�옴
	ENEMY_ANGEL_PURPLE,	//?�루??4
	ENEMY_KIMERA_PURPLE,	//마도?�성??5
	ENEMY_SHIP_PURPLE,	//고�???방주46
	ENEMY_FOGRA_PURPLE,	//?�리�?7
	ENEMY_BAHAMUT_PURPLE,	//?�어�?8
	ENEMY_DEATH_PURPLE,	//?�신49
	ENEMY_CASTLE_BOSS1_PURPLE,	//?�브리온50
	ENEMY_CASTLE_BOSS2_PURPLE,	//?��??�맨?�스51
	ENEMY_CASTLE_BOSS3_PURPLE,	//?�도???�트?�쿤52 -> ?�외
	ENEMY_CASTLE_BOSS4_PURPLE,	//?�크?�이??3						//문제 ?�에 ?�서 ?�옴
	ENEMY_LABETH_PURPLE,	//?�베??보스54
	ENEMY_ELKEIN_PURPLE,	//?��???보스55				//문제 ?�기?��???4개�? ?�딘가 ?�면??깨�?�???

	ENEMY_SNAIL_GREEN,	//가?�껍�??�팽??
	ENEMY_TREE_GREEN,	//?�의 주인 4
	ENEMY_ONEEYE_GREEN,	//?�이�?5
	ENEMY_SKELETON_GREEN,	//칠흑??기사 6 
	ENEMY_LIZARD_GREEN,	//?�하�?병사 7
	ENEMY_JELLYFISH_GREEN,	//맹독 ?�파�?
	ENEMY_KNIGHT_GREEN,	//?�?�한 기사 9
	ENEMY_SLIME_GREEN,	//?�라??10
	ENEMY_SLING_GREEN,	//?�원???�적 11
	ENEMY_BOAR_GREEN,	//거친�?멧돼지 12
	ENEMY_FLAME_GREEN,	//분노???�령 13
	ENEMY_PHOENIX_GREEN,	//마성??불새14
	ENEMY_FACE_GREEN,	//결빙???�상15
	ENEMY_SNOWMAN_GREEN,	//?�노?�맨16
	ENEMY_ICESUN_GREEN,	//?�이?�마?�크17
	ENEMY_LIGHTNING_GREEN,	//?�파??8
	ENEMY_THUNDER_GREEN,	//?�크미스??9
	ENEMY_CRYSTAL_GREEN,	//?�파???�랜??0
	ENEMY_FAIRY_GREEN,	//?�이???�피�?     1
	ENEMY_CIRCLE_GREEN,	//?�루???�울22
	ENEMY_SPIDER_GREEN,	//?�트?�이??5
	ENEMY_GOLEM_GREEN,	//주인?��? 골렘26
	ENEMY_DARKGIANT_GREEN,	//그레?�트 ?�머27
	ENEMY_DARKDRAGON_GREEN,	//?�로보로??8
	ENEMY_DRAGON1_GREEN,	//?�욕???�육??9
	ENEMY_DRAGON2_GREEN,	//?�래�?좀�?0
	ENEMY_GHOST_GREEN,	//?�도???�혼31
	ENEMY_PUMPKIN_GREEN,	//무혼??기사32
	ENEMY_CASTLE1_GREEN,	//?�둠??마도??//?�레?�트공격?�는??3		//문제 : ?�라지�??�돌?�옴
	ENEMY_CASTLE2_GREEN,	//공허??갑주	//??기사34
	ENEMY_SPACE1_GREEN,	//?�드로볼35
	ENEMY_SPACE2_GREEN,	//메탈가?�스36
	ENEMY_FROG_GREEN,	//?�드뮤턴??7
	ENEMY_LARVA_GREEN,	//?�르�?8
	ENEMY_SALAMANDER_GREEN,	//카툼39
	ENEMY_GIANT_GREEN,	//고�????�호??0
	ENEMY_IFRIT_GREEN,	//?�프리트41
	ENEMY_MAMMOTH_GREEN,	//?�로?�트42
	ENEMY_MACHINE_GREEN,	//?�이?�너43					//문제 : 모션??기계 모션???�옴
	ENEMY_ANGEL_GREEN,	//?�루??4
	ENEMY_KIMERA_GREEN,	//마도?�성??5
	ENEMY_SHIP_GREEN,	//고�???방주46
	ENEMY_FOGRA_GREEN,	//?�리�?7
	ENEMY_BAHAMUT_GREEN,	//?�어�?8
	ENEMY_DEATH_GREEN,	//?�신49
	ENEMY_CASTLE_BOSS1_GREEN,	//?�브리온50
	ENEMY_CASTLE_BOSS2_GREEN,	//?��??�맨?�스51
	ENEMY_CASTLE_BOSS3_GREEN,	//?�도???�트?�쿤52 -> ?�외
	ENEMY_CASTLE_BOSS4_GREEN,	//?�크?�이??3						//문제 ?�에 ?�서 ?�옴
	ENEMY_LABETH_GREEN,	//?�베??보스54
	ENEMY_ELKEIN_GREEN,	//?��???보스55				//문제 ?�기?��???4개�? ?�딘가 ?�면??깨�?�???

	ENEMY_SNAIL_GOLD,	//가?�껍�??�팽??
	ENEMY_TREE_GOLD,	//?�의 주인 4
	ENEMY_ONEEYE_GOLD,	//?�이�?5
	ENEMY_SKELETON_GOLD,	//칠흑??기사 6 
	ENEMY_LIZARD_GOLD,	//?�하�?병사 7
	ENEMY_JELLYFISH_GOLD,	//맹독 ?�파�?
	ENEMY_KNIGHT_GOLD,	//?�?�한 기사 9
	ENEMY_SLIME_GOLD,	//?�라??10
	ENEMY_SLING_GOLD,	//?�원???�적 11
	ENEMY_BOAR_GOLD,	//거친�?멧돼지 12
	ENEMY_FLAME_GOLD,	//분노???�령 13
	ENEMY_PHOENIX_GOLD,	//마성??불새14
	ENEMY_FACE_GOLD,	//결빙???�상15
	ENEMY_SNOWMAN_GOLD,	//?�노?�맨16
	ENEMY_ICESUN_GOLD,	//?�이?�마?�크17
	ENEMY_LIGHTNING_GOLD,	//?�파??8
	ENEMY_THUNDER_GOLD,	//?�크미스??9
	ENEMY_CRYSTAL_GOLD,	//?�파???�랜??0
	ENEMY_FAIRY_GOLD,	//?�이???�피�?     1
	ENEMY_CIRCLE_GOLD,	//?�루???�울22
	ENEMY_SPIDER_GOLD,	//?�트?�이??5
	ENEMY_GOLEM_GOLD,	//주인?��? 골렘26
	ENEMY_DARKGIANT_GOLD,	//그레?�트 ?�머27
	ENEMY_DARKDRAGON_GOLD,	//?�로보로??8
	ENEMY_DRAGON1_GOLD,	//?�욕???�육??9
	ENEMY_DRAGON2_GOLD,	//?�래�?좀�?0
	ENEMY_GHOST_GOLD,	//?�도???�혼31
	ENEMY_PUMPKIN_GOLD,	//무혼??기사32
	ENEMY_CASTLE1_GOLD,	//?�둠??마도??//?�레?�트공격?�는??3		//문제 : ?�라지�??�돌?�옴
	ENEMY_CASTLE2_GOLD,	//공허??갑주	//??기사34
	ENEMY_SPACE1_GOLD,	//?�드로볼35
	ENEMY_SPACE2_GOLD,	//메탈가?�스36
	ENEMY_FROG_GOLD,	//?�드뮤턴??7
	ENEMY_LARVA_GOLD,	//?�르�?8
	ENEMY_SALAMANDER_GOLD,	//카툼39
	ENEMY_GIANT_GOLD,	//고�????�호??0
	ENEMY_IFRIT_GOLD,	//?�프리트41
	ENEMY_MAMMOTH_GOLD,	//?�로?�트42
	ENEMY_MACHINE_GOLD,	//?�이?�너43					//문제 : 모션??기계 모션???�옴
	ENEMY_ANGEL_GOLD,	//?�루??4
	ENEMY_KIMERA_GOLD,	//마도?�성??5
	ENEMY_SHIP_GOLD,	//고�???방주46
	ENEMY_FOGRA_GOLD,	//?�리�?7
	ENEMY_BAHAMUT_GOLD,	//?�어�?8
	ENEMY_DEATH_GOLD,	//?�신49
	ENEMY_CASTLE_BOSS1_GOLD,	//?�브리온50
	ENEMY_CASTLE_BOSS2_GOLD,	//?��??�맨?�스51
	ENEMY_CASTLE_BOSS3_GOLD,	//?�도???�트?�쿤52 -> ?�외
	ENEMY_CASTLE_BOSS4_GOLD,	//?�크?�이??3						//문제 ?�에 ?�서 ?�옴
	ENEMY_LABETH_GOLD,	//?�베??보스54
	ENEMY_ELKEIN_GOLD,	//?��???보스55				//문제 ?�기?��???4개�? ?�딘가 ?�면??깨�?�???

	ENEMY_SNAIL_BLACK,	//가?�껍�??�팽??
	ENEMY_TREE_BLACK,	//?�의 주인 4
	ENEMY_ONEEYE_BLACK,	//?�이�?5
	ENEMY_SKELETON_BLACK,	//칠흑??기사 6 
	ENEMY_LIZARD_BLACK,	//?�하�?병사 7
	ENEMY_JELLYFISH_BLACK,	//맹독 ?�파�?
	ENEMY_KNIGHT_BLACK,	//?�?�한 기사 9
	ENEMY_SLIME_BLACK,	//?�라??10
	ENEMY_SLING_BLACK,	//?�원???�적 11
	ENEMY_BOAR_BLACK,	//거친�?멧돼지 12
	ENEMY_FLAME_BLACK,	//분노???�령 13
	ENEMY_PHOENIX_BLACK,	//마성??불새14
	ENEMY_FACE_BLACK,	//결빙???�상15
	ENEMY_SNOWMAN_BLACK,	//?�노?�맨16
	ENEMY_ICESUN_BLACK,	//?�이?�마?�크17
	ENEMY_LIGHTNING_BLACK,	//?�파??8
	ENEMY_THUNDER_BLACK,	//?�크미스??9
	ENEMY_CRYSTAL_BLACK,	//?�파???�랜??0
	ENEMY_FAIRY_BLACK,	//?�이???�피�?     1
	ENEMY_CIRCLE_BLACK,	//?�루???�울22
	ENEMY_SPIDER_BLACK,	//?�트?�이??5
	ENEMY_GOLEM_BLACK,	//주인?��? 골렘26
	ENEMY_DARKGIANT_BLACK,	//그레?�트 ?�머27
	ENEMY_DARKDRAGON_BLACK,	//?�로보로??8
	ENEMY_DRAGON1_BLACK,	//?�욕???�육??9
	ENEMY_DRAGON2_BLACK,	//?�래�?좀�?0
	ENEMY_GHOST_BLACK,	//?�도???�혼31
	ENEMY_PUMPKIN_BLACK,	//무혼??기사32
	ENEMY_CASTLE1_BLACK,	//?�둠??마도??//?�레?�트공격?�는??3		//문제 : ?�라지�??�돌?�옴
	ENEMY_CASTLE2_BLACK,	//공허??갑주	//??기사34
	ENEMY_SPACE1_BLACK,	//?�드로볼35
	ENEMY_SPACE2_BLACK,	//메탈가?�스36
	ENEMY_FROG_BLACK,	//?�드뮤턴??7
	ENEMY_LARVA_BLACK,	//?�르�?8
	ENEMY_SALAMANDER_BLACK,	//카툼39
	ENEMY_GIANT_BLACK,	//고�????�호??0
	ENEMY_IFRIT_BLACK,	//?�프리트41
	ENEMY_MAMMOTH_BLACK,	//?�로?�트42
	ENEMY_MACHINE_BLACK,	//?�이?�너43					//문제 : 모션??기계 모션???�옴
	ENEMY_ANGEL_BLACK,	//?�루??4
	ENEMY_KIMERA_BLACK,	//마도?�성??5
	ENEMY_SHIP_BLACK,	//고�???방주46
	ENEMY_FOGRA_BLACK,	//?�리�?7
	ENEMY_BAHAMUT_BLACK,	//?�어�?8
	ENEMY_DEATH_BLACK,	//?�신49
	ENEMY_CASTLE_BOSS1_BLACK,	//?�브리온50
	ENEMY_CASTLE_BOSS2_BLACK,	//?��??�맨?�스51
	ENEMY_CASTLE_BOSS3_BLACK,	//?�도???�트?�쿤52 -> ?�외
	ENEMY_CASTLE_BOSS4_BLACK,	//?�크?�이??3						//문제 ?�에 ?�서 ?�옴
	ENEMY_LABETH_BLACK,	//?�베??보스54
	ENEMY_ELKEIN_BLACK,	//?��???보스55

	NPC_CAPTAIN,//c52//??��?�너//o
	NPC_CREW,//c53//?�원//o
	NPC_GRANDFA,//c54//촌장//o
	NPC_UNCLE,//c55//?��???/o
	NPC_AUNT,//c56//?�줌�?/o
	NPC_MAN,//c57//?�경?�청??/o
	NPC_WOMAN,//c58//처�?//o
	NPC_BOY,//c59//꼬마??/o
	NPC_GIRL,//c60//꼬마?�//o
	NPC_ALMA,//c61//?�마//o
	NPC_ITEM,//c62//?�번//o
	NPC_FATMAN,//c63//o
	NPC_BUNNYGIRL,//c64//o
	NPC_KNIGHT,//c65//?�레?�//o
	NPC_DOG,//c66//o
	NPC_MERCHANT,//c67//o
	NPC_CRAFTMAN,//c68//o
	NPC_MAP,//c69//o
	NPC_USERQUEST,//c70//?�튜?�디??/o
	NPC_TRAVEL,//c71//?�국?�여?�자//o
	NPC_GRANDMA,//c72//?�머??/o
	NPC_FISHING,//c73//?�피//o
	NPC_INN,//c74//o
	NPC_NETITEM,//c75//o
	NPC_MILESE,//c76//o
	NPC_DOBEL,//c77//o
	NPC_GAGEL,//c78//o
	NPC_MONICA,//c79//o
	NPC_SHIP,//c80//o
	NPC_SEASOLDIER,//c81//?��??�병사//o
	NPC_FRAUD,//c82//o
	NPC_DARIAN,//c83//o
	NPC_LUISE,//c84//o
	NPC_SEAUNCLE,//c85//?��??�?��???/o
	NPC_SEABOY,//c86//?��??�?�년//o
	NPC_DONALD,//c87//?�소�?/o
	NPC_SCHOLAR,//c88//?�자//o
	NPC_CHEF,//c89//?�리?�가//o
	NPC_BISTRO,//c90//비스?�로//o
	NPC_MAID,//c91//?��?//o
	NPC_ADELKNIGHT,//c92//기사//o
	NPC_SEBASTIAN,//c93//?�바?�찬//o
	NPC_NOBLEMAN,//c94//귀족아?�??/o
	NPC_DELPIOS,//c95//?�피?�스//o
	NPC_LORA,//c96//로라//o
	NPC_WITCH,//c97//마�?//o
	NPC_ELFGRANDFA,//c98//?�프?�아버�?/o
	NPC_ELFUNCLE,//c99//?�프?��???/o
	NPC_ELFAUNT,//c100//?�프?�줌�?/o
	NPC_ELFMAN,//c101//?�프�?��//o
	NPC_ELFWOMAN,//c102//?�프처�?//o
	NPC_ELFBOY,//c103//?�프꼬마??/o
	NPC_ELFGIRL,//c104//?�프꼬마?�//o
	NPC_ELFDARK,//c105//?�프?�크//o
	NPC_ELFMAGIC,//c106//?�프마법??/o
	NPC_ELFDANCER,//c107//?�프무희//o
	NPC_OWL,//c108//부?�이//o
	NPC_LABETH,//c109//?�베??/o
	NPC_ELKEIN,//c110//?��???/o
	NPC_ELEIN,//c111//?�레??/o
	NPC_EVAN,//c112//?�번//o
	NPC_BEAD,//c113//?�이�?/o
	NPC_FOUNTAIN,//c114//?�물//o
	NPC_NEZAR,//c115//?�자�?/o
	NPC_GALLAND,//c116//갈�???/o
	NPC_DURAK,//c117//?�?�크//o
	NPC_KING,//c118//?�드몬드//o
	NPC_WOMANGHOST,//c119//?�자?�령//o
	NPC_MANGHOST,//c120//?�자?�령//o
	NPC_AUSTIN,//c121//?�스???�령)//o
	NPC_SOUL,//c122//마왕???�장//o

	TOTALENEMY,

	ENEMY_BULLET_NOSHADOW,
	ENEMY_BULLET_SKEL,

	MAXMONSTER = TOTALENEMY - NPC_CAPTAIN,

	SMALLMONSTER = 0,//공격?�하�??�는 ?��? 몬스??
	BIGMONSTER,//공격?�하�??��? ?�고 밀리는 몬스??
	GIANTMONSTER,//?�예 ?��?리는 몬스??

	ENEMYDATA_CMF = 0,
	ENEMYDATA_STAR,
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
