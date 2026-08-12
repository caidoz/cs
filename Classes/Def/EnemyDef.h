#pragma once

#ifndef _DEF_ENEMY_H_
#define _DEF_ENEMY_H_

typedef enum _enemyDef {

	//紐ъ뒪???뷀뙆??
	ENEMY_SNAIL = 3,	//가시껍질달팽이
	ENEMY_TREE,	//늪의 주인 4
	ENEMY_ONEEYE,	//아이볼 5
	ENEMY_SKELETON,	//칠흑의 기사 6 
	ENEMY_LIZARD,	//사하긴병사 7
	ENEMY_JELLYFISH,	//맹독해파리 8
	ENEMY_KNIGHT,	//타락한 기사 9
	ENEMY_SLIME,	//슬라임 10
	ENEMY_SLING,	//평원의 도적 11
	ENEMY_BOAR,	//거친발멧돼지 12
	ENEMY_FLAME,	//분노의 정령 13
	ENEMY_PHOENIX,	//마성의 불새 14
	ENEMY_FACE,	//결빙의 석상 15
	ENEMY_SNOWMAN,	//스노우맨 16
	ENEMY_ICESUN,	//아이스마스크 17
	ENEMY_LIGHTNING,	//스파크 18
	ENEMY_THUNDER,	//다크미스트 19
	ENEMY_CRYSTAL,	//스파크플랜트 20
	ENEMY_FAIRY,	//라이트스피릿 21
	ENEMY_CIRCLE,	//딜루전소울 22
	ENEMY_SPIDER,	//스트라이더 23
	ENEMY_GOLEM,	//二쇱씤?껋? 怨⑤젞24
	ENEMY_DARKGIANT,	//洹몃젅?댄듃 ?꾨㉧25
	ENEMY_DARKDRAGON,	//?곕줈蹂대줈??6(x ?덈뒗 洹몃깷 ?덈맖, 洹몃옒???대젮蹂댁옄.)
	ENEMY_DRAGON1,	//?먯슃???댁쑁??7 //(?뚰솚?? 怨듦꺽紐⑥뀡?� 二쇱?留??ㅼ젣 ?곕?吏�媛� ?덈뱾?닿컙??
	ENEMY_DRAGON2,	//?쒕옒怨?醫�鍮?8 //(?뚰솚?? 釉뚮젅?ㅺ? ?덈낫?몃떎.
	ENEMY_GHOST,	//?좊룄???곹샎29 //
	ENEMY_PUMPKIN,	//무혼??기사30
	ENEMY_CASTLE1,	//?대몺??留덈룄??//?붾젅?ы듃怨듦꺽?섎뒗??1		//臾몄젣 : ?щ씪吏�硫??덈룎?꾩샂(?) //(?뚰솚?? 珥앺깂???덈굹媛�怨??곕?吏�媛� ?덈뱾?닿컧
	ENEMY_CASTLE2,	//공허??갑주	//??기사32
	ENEMY_SPACE1,	//?덈뱶濡쒕낵33
	ENEMY_SPACE2,	//硫뷀깉媛�?곗뒪34 //(?뚰솚?? 珥앺깂?� ?섎뒗???곕━?몄씠 留욌뒗??
	ENEMY_FROG,	//?좊뱶裕ㅽ꽩??5 //(?뚰솚?? ?볥컮?μ씠 ?꾩튂媛� ?щ씪媛�怨??곕?吏�媛� ?⑥? ?딅뒗??
	ENEMY_LARVA,	//?꾨Ⅴ怨?6
	ENEMY_SALAMANDER,	//카툼37
	ENEMY_GIANT,	//怨좊????섑샇??8 //(?뚰솚??遺덈젢???섍컝 ???꾧뎔??怨듦꺽??
	ENEMY_IFRIT,	//?댄봽由ы듃39
	ENEMY_MAMMOTH,	//?꾨줈?ㅽ듃40
	ENEMY_MACHINE,	//?쇱씠?ㅻ꼫41
	ENEMY_ANGEL,	//?몃（??2 //(?뚰솚??遺덈젢???섍컝 ???꾧뎔??怨듦꺽??
	ENEMY_KIMERA,	//留덈룄?⑹꽦??3
	ENEMY_SHIP,	//怨좊???諛⑹＜44 (x)//(?뚰솚???먮윭諛쒖깮
	ENEMY_FOGRA,	//?꾨━留?5 //(?뚰솚?? 蹂댁“ 援ъ껜媛� ?щ씪吏�吏� ?딄퀬 ?덉씠?� ?좊븣???곷쭔 怨듦꺽?섎뒗??洹??ㅼ뿉???꾧뎔 怨듦꺽
	ENEMY_BAHAMUT,	//?곗뼱留?6 (x) (?뚰솚?? ?깆옣????紐명넻??癒몃━媛� ?덈텤?댁꽌 ?⑥뼱?몄꽌 ?섏삤怨?怨듦꺽???섏? ?딆븘??洹몃깷 怨꾩냽 ?고?以?
	ENEMY_DEATH,	//?ъ떊47 //(?뚰솚?? ?쒕쾲 怨듦꺽?????ㅼ뿉 ?щ씪吏�吏�瑜??딅뒗??
	ENEMY_CASTLE_BOSS1,	//?곕툕由ъ삩48 (x) //(?뚰솚?? ?쇱븘瑜?媛�由ъ? ?딄퀬 怨듦꺽?섍퀬, ?꾩껌?섍쾶 ?먮젮吏꾨떎. 
	ENEMY_CASTLE_BOSS2,	//?섏??몃㎤?곗뒪49
	ENEMY_CASTLE_BOSS3,	//?먮룄???뚰듃?쇱엘50 -> ?쒖쇅 (x) //(?뚰솚?? 泥섏쓬??怨⑥“媛� 癒쇱? 蹂댁씠怨?怨꾩냽 ?고?瑜??뚮━?ㅺ? ?ㅻ뱶媛� ?щ씪?몃룄 怨꾩냽 ?⑥븘?덈떎.(?덉씠?�???쒕?濡??섍컧)
	ENEMY_CASTLE_BOSS4,	//?ㅽ겕?섏씠??1						//(?뚰솚?? ?먯씠 ?깆옣?섍퀬 ?섏쨷???앸굹???⑥븘?덈떎.
	ENEMY_LABETH,	//?쇰쿋??蹂댁뒪52 (x)//(?뚰솚?? ?깆옣????怨듦꺽?먯젙, ?ㅽ궗 ???ㅼ쓬???щ씪吏�吏� ?딆븘??怨꾩냽 ?먯젙.
	ENEMY_ELKEIN,	//?섏???蹂댁뒪53				//臾몄젣 ?ш린?쒕???4媛쒓? ?대뵖媛� ?붾㈃??源⑥?寃???

	ENEMY_SNAIL_RED,	//媛�?쒓퍖吏??ы뙺??
	ENEMY_TREE_RED,	//?れ쓽 二쇱씤 4
	ENEMY_ONEEYE_RED,	//?꾩씠蹂?5
	ENEMY_SKELETON_RED,	//칠흑??기사 6 
	ENEMY_LIZARD_RED,	//?ы븯湲?蹂묒궗 7
	ENEMY_JELLYFISH_RED,	//留밸룆 ?댄뙆由?
	ENEMY_KNIGHT_RED,	//?�?쏀븳 湲곗궗 9
	ENEMY_SLIME_RED,	//?щ씪??10
	ENEMY_SLING_RED,	//?됱썝???꾩쟻 11
	ENEMY_BOAR_RED,	//嫄곗튇諛?硫㏓뤌吏� 12
	ENEMY_FLAME_RED,	//遺꾨끂???뺣졊 13
	ENEMY_PHOENIX_RED,	//마성??불새14
	ENEMY_FACE_RED,	//寃곕튃???앹긽15
	ENEMY_SNOWMAN_RED,	//?ㅻ끂?곕㎤16
	ENEMY_ICESUN_RED,	//?꾩씠?ㅻ쭏?ㅽ겕17
	ENEMY_LIGHTNING_RED,	//?ㅽ뙆??8
	ENEMY_THUNDER_RED,	//?ㅽ겕誘몄뒪??9
	ENEMY_CRYSTAL_RED,	//?ㅽ뙆???뚮옖??0
	ENEMY_FAIRY_RED,	//?쇱씠???ㅽ뵾由?1
	ENEMY_CIRCLE_RED,	//?쒕（???뚯슱22
	ENEMY_SPIDER_RED,	//?ㅽ듃?쇱씠??3
	ENEMY_GOLEM_RED,	//二쇱씤?껋? 怨⑤젞24
	ENEMY_DARKGIANT_RED,	//洹몃젅?댄듃 ?꾨㉧25
	ENEMY_DARKDRAGON_RED,	//?곕줈蹂대줈??6
	ENEMY_DRAGON1_RED,	//?먯슃???댁쑁??7
	ENEMY_DRAGON2_RED,	//?쒕옒怨?醫�鍮?8
	ENEMY_GHOST_RED,	//?좊룄???곹샎29
	ENEMY_PUMPKIN_RED,	//무혼??기사30
	ENEMY_CASTLE1_RED,	//?대몺??留덈룄??//?붾젅?ы듃怨듦꺽?섎뒗??1		//臾몄젣 : ?щ씪吏�硫??덈룎?꾩샂
	ENEMY_CASTLE2_RED,	//공허??갑주	//??기사32
	ENEMY_SPACE1_RED,	//?덈뱶濡쒕낵33
	ENEMY_SPACE2_RED,	//硫뷀깉媛�?곗뒪34
	ENEMY_FROG_RED,	//?좊뱶裕ㅽ꽩??5
	ENEMY_LARVA_RED,	//?꾨Ⅴ怨?6
	ENEMY_SALAMANDER_RED,	//카툼37
	ENEMY_GIANT_RED,	//怨좊????섑샇??8
	ENEMY_IFRIT_RED,	//?댄봽由ы듃39
	ENEMY_MAMMOTH_RED,	//?꾨줈?ㅽ듃40
	ENEMY_MACHINE_RED,	//?쇱씠?ㅻ꼫41					//臾몄젣 : 紐⑥뀡??湲곌퀎 紐⑥뀡???섏샂
	ENEMY_ANGEL_RED,	//?몃（??2
	ENEMY_KIMERA_RED,	//留덈룄?⑹꽦??3
	ENEMY_SHIP_RED,	//怨좊???諛⑹＜44
	ENEMY_FOGRA_RED,	//?꾨━留?5
	ENEMY_BAHAMUT_RED,	//?곗뼱留?6
	ENEMY_DEATH_RED,	//?ъ떊47
	ENEMY_CASTLE_BOSS1_RED,	//?곕툕由ъ삩48
	ENEMY_CASTLE_BOSS2_RED,	//?섏??몃㎤?곗뒪49
	ENEMY_CASTLE_BOSS3_RED,	//?먮룄???뚰듃?쇱엘50 -> ?쒖쇅
	ENEMY_CASTLE_BOSS4_RED,	//?ㅽ겕?섏씠??1						//臾몄젣 ?꾩뿉 ?좎꽌 ?섏샂
	ENEMY_LABETH_RED,	//?쇰쿋??蹂댁뒪52
	ENEMY_ELKEIN_RED,	//?섏???蹂댁뒪53				//臾몄젣 ?ш린?쒕???4媛쒓? ?대뵖媛� ?붾㈃??源⑥?寃???

	ENEMY_SNAIL_BLUE,	//媛�?쒓퍖吏??ы뙺??
	ENEMY_TREE_BLUE,	//?れ쓽 二쇱씤 4
	ENEMY_ONEEYE_BLUE,	//?꾩씠蹂?5
	ENEMY_SKELETON_BLUE,	//칠흑??기사 6 
	ENEMY_LIZARD_BLUE,	//?ы븯湲?蹂묒궗 7
	ENEMY_JELLYFISH_BLUE,	//留밸룆 ?댄뙆由?
	ENEMY_KNIGHT_BLUE,	//?�?쏀븳 湲곗궗 9
	ENEMY_SLIME_BLUE,	//?щ씪??10
	ENEMY_SLING_BLUE,	//?됱썝???꾩쟻 11
	ENEMY_BOAR_BLUE,	//嫄곗튇諛?硫㏓뤌吏� 12
	ENEMY_FLAME_BLUE,	//遺꾨끂???뺣졊 13
	ENEMY_PHOENIX_BLUE,	//마성??불새14
	ENEMY_FACE_BLUE,	//寃곕튃???앹긽15
	ENEMY_SNOWMAN_BLUE,	//?ㅻ끂?곕㎤16
	ENEMY_ICESUN_BLUE,	//?꾩씠?ㅻ쭏?ㅽ겕17
	ENEMY_LIGHTNING_BLUE,	//?ㅽ뙆??8
	ENEMY_THUNDER_BLUE,	//?ㅽ겕誘몄뒪??9
	ENEMY_CRYSTAL_BLUE,	//?ㅽ뙆???뚮옖??0
	ENEMY_FAIRY_BLUE,	//?쇱씠???ㅽ뵾由?1
	ENEMY_CIRCLE_BLUE,	//?쒕（???뚯슱22
	ENEMY_SPIDER_BLUE,	//?ㅽ듃?쇱씠??3
	ENEMY_GOLEM_BLUE,	//二쇱씤?껋? 怨⑤젞24
	ENEMY_DARKGIANT_BLUE,	//洹몃젅?댄듃 ?꾨㉧25
	ENEMY_DARKDRAGON_BLUE,	//?곕줈蹂대줈??6
	ENEMY_DRAGON1_BLUE,	//?먯슃???댁쑁??7
	ENEMY_DRAGON2_BLUE,	//?쒕옒怨?醫�鍮?8
	ENEMY_GHOST_BLUE,	//?좊룄???곹샎29
	ENEMY_PUMPKIN_BLUE,	//무혼??기사30
	ENEMY_CASTLE1_BLUE,	//?대몺??留덈룄??//?붾젅?ы듃怨듦꺽?섎뒗??1		//臾몄젣 : ?щ씪吏�硫??덈룎?꾩샂
	ENEMY_CASTLE2_BLUE,	//공허??갑주	//??기사32
	ENEMY_SPACE1_BLUE,	//?덈뱶濡쒕낵33
	ENEMY_SPACE2_BLUE,	//硫뷀깉媛�?곗뒪34
	ENEMY_FROG_BLUE,	//?좊뱶裕ㅽ꽩??5
	ENEMY_LARVA_BLUE,	//?꾨Ⅴ怨?6
	ENEMY_SALAMANDER_BLUE,	//카툼37
	ENEMY_GIANT_BLUE,	//怨좊????섑샇??8
	ENEMY_IFRIT_BLUE,	//?댄봽由ы듃39
	ENEMY_MAMMOTH_BLUE,	//?꾨줈?ㅽ듃40
	ENEMY_MACHINE_BLUE,	//?쇱씠?ㅻ꼫41					//臾몄젣 : 紐⑥뀡??湲곌퀎 紐⑥뀡???섏샂
	ENEMY_ANGEL_BLUE,	//?몃（??2
	ENEMY_KIMERA_BLUE,	//留덈룄?⑹꽦??3
	ENEMY_SHIP_BLUE,	//怨좊???諛⑹＜44
	ENEMY_FOGRA_BLUE,	//?꾨━留?5
	ENEMY_BAHAMUT_BLUE,	//?곗뼱留?6
	ENEMY_DEATH_BLUE,	//?ъ떊47
	ENEMY_CASTLE_BOSS1_BLUE,	//?곕툕由ъ삩48
	ENEMY_CASTLE_BOSS2_BLUE,	//?섏??몃㎤?곗뒪49
	ENEMY_CASTLE_BOSS3_BLUE,	//?먮룄???뚰듃?쇱엘50 -> ?쒖쇅
	ENEMY_CASTLE_BOSS4_BLUE,	//?ㅽ겕?섏씠??1						//臾몄젣 ?꾩뿉 ?좎꽌 ?섏샂
	ENEMY_LABETH_BLUE,	//?쇰쿋??蹂댁뒪52
	ENEMY_ELKEIN_BLUE,	//?섏???蹂댁뒪53				//臾몄젣 ?ш린?쒕???4媛쒓? ?대뵖媛� ?붾㈃??源⑥?寃???

	ENEMY_SNAIL_PURPLE,	//媛�?쒓퍖吏??ы뙺??
	ENEMY_TREE_PURPLE,	//?れ쓽 二쇱씤 4
	ENEMY_ONEEYE_PURPLE,	//?꾩씠蹂?5
	ENEMY_SKELETON_PURPLE,	//칠흑??기사 6 
	ENEMY_LIZARD_PURPLE,	//?ы븯湲?蹂묒궗 7
	ENEMY_JELLYFISH_PURPLE,	//留밸룆 ?댄뙆由?
	ENEMY_KNIGHT_PURPLE,	//?�?쏀븳 湲곗궗 9
	ENEMY_SLIME_PURPLE,	//?щ씪??10
	ENEMY_SLING_PURPLE,	//?됱썝???꾩쟻 11
	ENEMY_BOAR_PURPLE,	//嫄곗튇諛?硫㏓뤌吏� 12
	ENEMY_FLAME_PURPLE,	//遺꾨끂???뺣졊 13
	ENEMY_PHOENIX_PURPLE,	//마성??불새14
	ENEMY_FACE_PURPLE,	//寃곕튃???앹긽15
	ENEMY_SNOWMAN_PURPLE,	//?ㅻ끂?곕㎤16
	ENEMY_ICESUN_PURPLE,	//?꾩씠?ㅻ쭏?ㅽ겕17
	ENEMY_LIGHTNING_PURPLE,	//?ㅽ뙆??8
	ENEMY_THUNDER_PURPLE,	//?ㅽ겕誘몄뒪??9
	ENEMY_CRYSTAL_PURPLE,	//?ㅽ뙆???뚮옖??0
	ENEMY_FAIRY_PURPLE,	//?쇱씠???ㅽ뵾由?     1
	ENEMY_CIRCLE_PURPLE,	//?쒕（???뚯슱22
	ENEMY_SPIDER_PURPLE,	//?ㅽ듃?쇱씠??5
	ENEMY_GOLEM_PURPLE,	//二쇱씤?껋? 怨⑤젞26
	ENEMY_DARKGIANT_PURPLE,	//洹몃젅?댄듃 ?꾨㉧27
	ENEMY_DARKDRAGON_PURPLE,	//?곕줈蹂대줈??8
	ENEMY_DRAGON1_PURPLE,	//?먯슃???댁쑁??9
	ENEMY_DRAGON2_PURPLE,	//?쒕옒怨?醫�鍮?0
	ENEMY_GHOST_PURPLE,	//?좊룄???곹샎31
	ENEMY_PUMPKIN_PURPLE,	//무혼??기사32
	ENEMY_CASTLE1_PURPLE,	//?대몺??留덈룄??//?붾젅?ы듃怨듦꺽?섎뒗??3		//臾몄젣 : ?щ씪吏�硫??덈룎?꾩샂
	ENEMY_CASTLE2_PURPLE,	//공허??갑주	//??기사34
	ENEMY_SPACE1_PURPLE,	//?덈뱶濡쒕낵35
	ENEMY_SPACE2_PURPLE,	//硫뷀깉媛�?곗뒪36
	ENEMY_FROG_PURPLE,	//?좊뱶裕ㅽ꽩??7
	ENEMY_LARVA_PURPLE,	//?꾨Ⅴ怨?8
	ENEMY_SALAMANDER_PURPLE,	//카툼39
	ENEMY_GIANT_PURPLE,	//怨좊????섑샇??0
	ENEMY_IFRIT_PURPLE,	//?댄봽由ы듃41
	ENEMY_MAMMOTH_PURPLE,	//?꾨줈?ㅽ듃42
	ENEMY_MACHINE_PURPLE,	//?쇱씠?ㅻ꼫43					//臾몄젣 : 紐⑥뀡??湲곌퀎 紐⑥뀡???섏샂
	ENEMY_ANGEL_PURPLE,	//?몃（??4
	ENEMY_KIMERA_PURPLE,	//留덈룄?⑹꽦??5
	ENEMY_SHIP_PURPLE,	//怨좊???諛⑹＜46
	ENEMY_FOGRA_PURPLE,	//?꾨━留?7
	ENEMY_BAHAMUT_PURPLE,	//?곗뼱留?8
	ENEMY_DEATH_PURPLE,	//?ъ떊49
	ENEMY_CASTLE_BOSS1_PURPLE,	//?곕툕由ъ삩50
	ENEMY_CASTLE_BOSS2_PURPLE,	//?섏??몃㎤?곗뒪51
	ENEMY_CASTLE_BOSS3_PURPLE,	//?먮룄???뚰듃?쇱엘52 -> ?쒖쇅
	ENEMY_CASTLE_BOSS4_PURPLE,	//?ㅽ겕?섏씠??3						//臾몄젣 ?꾩뿉 ?좎꽌 ?섏샂
	ENEMY_LABETH_PURPLE,	//?쇰쿋??蹂댁뒪54
	ENEMY_ELKEIN_PURPLE,	//?섏???蹂댁뒪55				//臾몄젣 ?ш린?쒕???4媛쒓? ?대뵖媛� ?붾㈃??源⑥?寃???

	ENEMY_SNAIL_GREEN,	//媛�?쒓퍖吏??ы뙺??
	ENEMY_TREE_GREEN,	//?れ쓽 二쇱씤 4
	ENEMY_ONEEYE_GREEN,	//?꾩씠蹂?5
	ENEMY_SKELETON_GREEN,	//칠흑??기사 6 
	ENEMY_LIZARD_GREEN,	//?ы븯湲?蹂묒궗 7
	ENEMY_JELLYFISH_GREEN,	//留밸룆 ?댄뙆由?
	ENEMY_KNIGHT_GREEN,	//?�?쏀븳 湲곗궗 9
	ENEMY_SLIME_GREEN,	//?щ씪??10
	ENEMY_SLING_GREEN,	//?됱썝???꾩쟻 11
	ENEMY_BOAR_GREEN,	//嫄곗튇諛?硫㏓뤌吏� 12
	ENEMY_FLAME_GREEN,	//遺꾨끂???뺣졊 13
	ENEMY_PHOENIX_GREEN,	//마성??불새14
	ENEMY_FACE_GREEN,	//寃곕튃???앹긽15
	ENEMY_SNOWMAN_GREEN,	//?ㅻ끂?곕㎤16
	ENEMY_ICESUN_GREEN,	//?꾩씠?ㅻ쭏?ㅽ겕17
	ENEMY_LIGHTNING_GREEN,	//?ㅽ뙆??8
	ENEMY_THUNDER_GREEN,	//?ㅽ겕誘몄뒪??9
	ENEMY_CRYSTAL_GREEN,	//?ㅽ뙆???뚮옖??0
	ENEMY_FAIRY_GREEN,	//?쇱씠???ㅽ뵾由?     1
	ENEMY_CIRCLE_GREEN,	//?쒕（???뚯슱22
	ENEMY_SPIDER_GREEN,	//?ㅽ듃?쇱씠??5
	ENEMY_GOLEM_GREEN,	//二쇱씤?껋? 怨⑤젞26
	ENEMY_DARKGIANT_GREEN,	//洹몃젅?댄듃 ?꾨㉧27
	ENEMY_DARKDRAGON_GREEN,	//?곕줈蹂대줈??8
	ENEMY_DRAGON1_GREEN,	//?먯슃???댁쑁??9
	ENEMY_DRAGON2_GREEN,	//?쒕옒怨?醫�鍮?0
	ENEMY_GHOST_GREEN,	//?좊룄???곹샎31
	ENEMY_PUMPKIN_GREEN,	//무혼??기사32
	ENEMY_CASTLE1_GREEN,	//?대몺??留덈룄??//?붾젅?ы듃怨듦꺽?섎뒗??3		//臾몄젣 : ?щ씪吏�硫??덈룎?꾩샂
	ENEMY_CASTLE2_GREEN,	//공허??갑주	//??기사34
	ENEMY_SPACE1_GREEN,	//?덈뱶濡쒕낵35
	ENEMY_SPACE2_GREEN,	//硫뷀깉媛�?곗뒪36
	ENEMY_FROG_GREEN,	//?좊뱶裕ㅽ꽩??7
	ENEMY_LARVA_GREEN,	//?꾨Ⅴ怨?8
	ENEMY_SALAMANDER_GREEN,	//카툼39
	ENEMY_GIANT_GREEN,	//怨좊????섑샇??0
	ENEMY_IFRIT_GREEN,	//?댄봽由ы듃41
	ENEMY_MAMMOTH_GREEN,	//?꾨줈?ㅽ듃42
	ENEMY_MACHINE_GREEN,	//?쇱씠?ㅻ꼫43					//臾몄젣 : 紐⑥뀡??湲곌퀎 紐⑥뀡???섏샂
	ENEMY_ANGEL_GREEN,	//?몃（??4
	ENEMY_KIMERA_GREEN,	//留덈룄?⑹꽦??5
	ENEMY_SHIP_GREEN,	//怨좊???諛⑹＜46
	ENEMY_FOGRA_GREEN,	//?꾨━留?7
	ENEMY_BAHAMUT_GREEN,	//?곗뼱留?8
	ENEMY_DEATH_GREEN,	//?ъ떊49
	ENEMY_CASTLE_BOSS1_GREEN,	//?곕툕由ъ삩50
	ENEMY_CASTLE_BOSS2_GREEN,	//?섏??몃㎤?곗뒪51
	ENEMY_CASTLE_BOSS3_GREEN,	//?먮룄???뚰듃?쇱엘52 -> ?쒖쇅
	ENEMY_CASTLE_BOSS4_GREEN,	//?ㅽ겕?섏씠??3						//臾몄젣 ?꾩뿉 ?좎꽌 ?섏샂
	ENEMY_LABETH_GREEN,	//?쇰쿋??蹂댁뒪54
	ENEMY_ELKEIN_GREEN,	//?섏???蹂댁뒪55				//臾몄젣 ?ш린?쒕???4媛쒓? ?대뵖媛� ?붾㈃??源⑥?寃???

	ENEMY_SNAIL_GOLD,	//媛�?쒓퍖吏??ы뙺??
	ENEMY_TREE_GOLD,	//?れ쓽 二쇱씤 4
	ENEMY_ONEEYE_GOLD,	//?꾩씠蹂?5
	ENEMY_SKELETON_GOLD,	//칠흑??기사 6 
	ENEMY_LIZARD_GOLD,	//?ы븯湲?蹂묒궗 7
	ENEMY_JELLYFISH_GOLD,	//留밸룆 ?댄뙆由?
	ENEMY_KNIGHT_GOLD,	//?�?쏀븳 湲곗궗 9
	ENEMY_SLIME_GOLD,	//?щ씪??10
	ENEMY_SLING_GOLD,	//?됱썝???꾩쟻 11
	ENEMY_BOAR_GOLD,	//嫄곗튇諛?硫㏓뤌吏� 12
	ENEMY_FLAME_GOLD,	//遺꾨끂???뺣졊 13
	ENEMY_PHOENIX_GOLD,	//마성??불새14
	ENEMY_FACE_GOLD,	//寃곕튃???앹긽15
	ENEMY_SNOWMAN_GOLD,	//?ㅻ끂?곕㎤16
	ENEMY_ICESUN_GOLD,	//?꾩씠?ㅻ쭏?ㅽ겕17
	ENEMY_LIGHTNING_GOLD,	//?ㅽ뙆??8
	ENEMY_THUNDER_GOLD,	//?ㅽ겕誘몄뒪??9
	ENEMY_CRYSTAL_GOLD,	//?ㅽ뙆???뚮옖??0
	ENEMY_FAIRY_GOLD,	//?쇱씠???ㅽ뵾由?     1
	ENEMY_CIRCLE_GOLD,	//?쒕（???뚯슱22
	ENEMY_SPIDER_GOLD,	//?ㅽ듃?쇱씠??5
	ENEMY_GOLEM_GOLD,	//二쇱씤?껋? 怨⑤젞26
	ENEMY_DARKGIANT_GOLD,	//洹몃젅?댄듃 ?꾨㉧27
	ENEMY_DARKDRAGON_GOLD,	//?곕줈蹂대줈??8
	ENEMY_DRAGON1_GOLD,	//?먯슃???댁쑁??9
	ENEMY_DRAGON2_GOLD,	//?쒕옒怨?醫�鍮?0
	ENEMY_GHOST_GOLD,	//?좊룄???곹샎31
	ENEMY_PUMPKIN_GOLD,	//무혼??기사32
	ENEMY_CASTLE1_GOLD,	//?대몺??留덈룄??//?붾젅?ы듃怨듦꺽?섎뒗??3		//臾몄젣 : ?щ씪吏�硫??덈룎?꾩샂
	ENEMY_CASTLE2_GOLD,	//공허??갑주	//??기사34
	ENEMY_SPACE1_GOLD,	//?덈뱶濡쒕낵35
	ENEMY_SPACE2_GOLD,	//硫뷀깉媛�?곗뒪36
	ENEMY_FROG_GOLD,	//?좊뱶裕ㅽ꽩??7
	ENEMY_LARVA_GOLD,	//?꾨Ⅴ怨?8
	ENEMY_SALAMANDER_GOLD,	//카툼39
	ENEMY_GIANT_GOLD,	//怨좊????섑샇??0
	ENEMY_IFRIT_GOLD,	//?댄봽由ы듃41
	ENEMY_MAMMOTH_GOLD,	//?꾨줈?ㅽ듃42
	ENEMY_MACHINE_GOLD,	//?쇱씠?ㅻ꼫43					//臾몄젣 : 紐⑥뀡??湲곌퀎 紐⑥뀡???섏샂
	ENEMY_ANGEL_GOLD,	//?몃（??4
	ENEMY_KIMERA_GOLD,	//留덈룄?⑹꽦??5
	ENEMY_SHIP_GOLD,	//怨좊???諛⑹＜46
	ENEMY_FOGRA_GOLD,	//?꾨━留?7
	ENEMY_BAHAMUT_GOLD,	//?곗뼱留?8
	ENEMY_DEATH_GOLD,	//?ъ떊49
	ENEMY_CASTLE_BOSS1_GOLD,	//?곕툕由ъ삩50
	ENEMY_CASTLE_BOSS2_GOLD,	//?섏??몃㎤?곗뒪51
	ENEMY_CASTLE_BOSS3_GOLD,	//?먮룄???뚰듃?쇱엘52 -> ?쒖쇅
	ENEMY_CASTLE_BOSS4_GOLD,	//?ㅽ겕?섏씠??3						//臾몄젣 ?꾩뿉 ?좎꽌 ?섏샂
	ENEMY_LABETH_GOLD,	//?쇰쿋??蹂댁뒪54
	ENEMY_ELKEIN_GOLD,	//?섏???蹂댁뒪55				//臾몄젣 ?ш린?쒕???4媛쒓? ?대뵖媛� ?붾㈃??源⑥?寃???

	ENEMY_SNAIL_BLACK,	//媛�?쒓퍖吏??ы뙺??
	ENEMY_TREE_BLACK,	//?れ쓽 二쇱씤 4
	ENEMY_ONEEYE_BLACK,	//?꾩씠蹂?5
	ENEMY_SKELETON_BLACK,	//칠흑??기사 6 
	ENEMY_LIZARD_BLACK,	//?ы븯湲?蹂묒궗 7
	ENEMY_JELLYFISH_BLACK,	//留밸룆 ?댄뙆由?
	ENEMY_KNIGHT_BLACK,	//?�?쏀븳 湲곗궗 9
	ENEMY_SLIME_BLACK,	//?щ씪??10
	ENEMY_SLING_BLACK,	//?됱썝???꾩쟻 11
	ENEMY_BOAR_BLACK,	//嫄곗튇諛?硫㏓뤌吏� 12
	ENEMY_FLAME_BLACK,	//遺꾨끂???뺣졊 13
	ENEMY_PHOENIX_BLACK,	//마성??불새14
	ENEMY_FACE_BLACK,	//寃곕튃???앹긽15
	ENEMY_SNOWMAN_BLACK,	//?ㅻ끂?곕㎤16
	ENEMY_ICESUN_BLACK,	//?꾩씠?ㅻ쭏?ㅽ겕17
	ENEMY_LIGHTNING_BLACK,	//?ㅽ뙆??8
	ENEMY_THUNDER_BLACK,	//?ㅽ겕誘몄뒪??9
	ENEMY_CRYSTAL_BLACK,	//?ㅽ뙆???뚮옖??0
	ENEMY_FAIRY_BLACK,	//?쇱씠???ㅽ뵾由?     1
	ENEMY_CIRCLE_BLACK,	//?쒕（???뚯슱22
	ENEMY_SPIDER_BLACK,	//?ㅽ듃?쇱씠??5
	ENEMY_GOLEM_BLACK,	//二쇱씤?껋? 怨⑤젞26
	ENEMY_DARKGIANT_BLACK,	//洹몃젅?댄듃 ?꾨㉧27
	ENEMY_DARKDRAGON_BLACK,	//?곕줈蹂대줈??8
	ENEMY_DRAGON1_BLACK,	//?먯슃???댁쑁??9
	ENEMY_DRAGON2_BLACK,	//?쒕옒怨?醫�鍮?0
	ENEMY_GHOST_BLACK,	//?좊룄???곹샎31
	ENEMY_PUMPKIN_BLACK,	//무혼??기사32
	ENEMY_CASTLE1_BLACK,	//?대몺??留덈룄??//?붾젅?ы듃怨듦꺽?섎뒗??3		//臾몄젣 : ?щ씪吏�硫??덈룎?꾩샂
	ENEMY_CASTLE2_BLACK,	//공허??갑주	//??기사34
	ENEMY_SPACE1_BLACK,	//?덈뱶濡쒕낵35
	ENEMY_SPACE2_BLACK,	//硫뷀깉媛�?곗뒪36
	ENEMY_FROG_BLACK,	//?좊뱶裕ㅽ꽩??7
	ENEMY_LARVA_BLACK,	//?꾨Ⅴ怨?8
	ENEMY_SALAMANDER_BLACK,	//카툼39
	ENEMY_GIANT_BLACK,	//怨좊????섑샇??0
	ENEMY_IFRIT_BLACK,	//?댄봽由ы듃41
	ENEMY_MAMMOTH_BLACK,	//?꾨줈?ㅽ듃42
	ENEMY_MACHINE_BLACK,	//?쇱씠?ㅻ꼫43					//臾몄젣 : 紐⑥뀡??湲곌퀎 紐⑥뀡???섏샂
	ENEMY_ANGEL_BLACK,	//?몃（??4
	ENEMY_KIMERA_BLACK,	//留덈룄?⑹꽦??5
	ENEMY_SHIP_BLACK,	//怨좊???諛⑹＜46
	ENEMY_FOGRA_BLACK,	//?꾨━留?7
	ENEMY_BAHAMUT_BLACK,	//?곗뼱留?8
	ENEMY_DEATH_BLACK,	//?ъ떊49
	ENEMY_CASTLE_BOSS1_BLACK,	//?곕툕由ъ삩50
	ENEMY_CASTLE_BOSS2_BLACK,	//?섏??몃㎤?곗뒪51
	ENEMY_CASTLE_BOSS3_BLACK,	//?먮룄???뚰듃?쇱엘52 -> ?쒖쇅
	ENEMY_CASTLE_BOSS4_BLACK,	//?ㅽ겕?섏씠??3						//臾몄젣 ?꾩뿉 ?좎꽌 ?섏샂
	ENEMY_LABETH_BLACK,	//?쇰쿋??蹂댁뒪54
	ENEMY_ELKEIN_BLACK,	//?섏???蹂댁뒪55

	NPC_CAPTAIN,//c52//??뒪?⑤꼫//o
	NPC_CREW,//c53//?좎썝//o
	NPC_GRANDFA,//c54//촌장//o
	NPC_UNCLE,//c55//?꾩???/o
	NPC_AUNT,//c56//?꾩쨲留?/o
	NPC_MAN,//c57//?먭꼍?⑥껌??/o
	NPC_WOMAN,//c58//泥섎?//o
	NPC_BOY,//c59//꼬마??/o
	NPC_GIRL,//c60//瑗щ쭏?�//o
	NPC_ALMA,//c61//?뚮쭏//o
	NPC_ITEM,//c62//?곕쾲//o
	NPC_FATMAN,//c63//o
	NPC_BUNNYGIRL,//c64//o
	NPC_KNIGHT,//c65//?뚮젅?�//o
	NPC_DOG,//c66//o
	NPC_MERCHANT,//c67//o
	NPC_CRAFTMAN,//c68//o
	NPC_MAP,//c69//o
	NPC_USERQUEST,//c70//?ㅽ뒠?대뵒??/o
	NPC_TRAVEL,//c71//?닿뎅?섏뿬?됱옄//o
	NPC_GRANDMA,//c72//?좊㉧??/o
	NPC_FISHING,//c73//?쇳뵾//o
	NPC_INN,//c74//o
	NPC_NETITEM,//c75//o
	NPC_MILESE,//c76//o
	NPC_DOBEL,//c77//o
	NPC_GAGEL,//c78//o
	NPC_MONICA,//c79//o
	NPC_SHIP,//c80//o
	NPC_SEASOLDIER,//c81//?꾪??�蹂묒궗//o
	NPC_FRAUD,//c82//o
	NPC_DARIAN,//c83//o
	NPC_LUISE,//c84//o
	NPC_SEAUNCLE,//c85//?꾪??�?꾩???/o
	NPC_SEABOY,//c86//?꾪??�?뚮뀈//o
	NPC_DONALD,//c87//?댁냼猷?/o
	NPC_SCHOLAR,//c88//?숈옄//o
	NPC_CHEF,//c89//?붾━?�媛�//o
	NPC_BISTRO,//c90//鍮꾩뒪?몃줈//o
	NPC_MAID,//c91//?쒕?//o
	NPC_ADELKNIGHT,//c92//기사//o
	NPC_SEBASTIAN,//c93//?몃컮?ㅼ갔//o
	NPC_NOBLEMAN,//c94//洹�議깆븘?�??/o
	NPC_DELPIOS,//c95//?명뵾?ㅼ뒪//o
	NPC_LORA,//c96//로라//o
	NPC_WITCH,//c97//留덈?//o
	NPC_ELFGRANDFA,//c98//?섑봽?좎븘踰꾩?/o
	NPC_ELFUNCLE,//c99//?섑봽?꾩???/o
	NPC_ELFAUNT,//c100//?섑봽?꾩쨲留?/o
	NPC_ELFMAN,//c101//?섑봽泥?뀈//o
	NPC_ELFWOMAN,//c102//?섑봽泥섎?//o
	NPC_ELFBOY,//c103//?섑봽瑗щ쭏??/o
	NPC_ELFGIRL,//c104//?섑봽瑗щ쭏?�//o
	NPC_ELFDARK,//c105//?섑봽?ㅽ겕//o
	NPC_ELFMAGIC,//c106//?섑봽留덈쾿??/o
	NPC_ELFDANCER,//c107//?섑봽臾댄씗//o
	NPC_OWL,//c108//遺�?됱씠//o
	NPC_LABETH,//c109//?쇰쿋??/o
	NPC_ELKEIN,//c110//?섏???/o
	NPC_ELEIN,//c111//?섎젅??/o
	NPC_EVAN,//c112//?먮쾲//o
	NPC_BEAD,//c113//?뚯씠釉?/o
	NPC_FOUNTAIN,//c114//?섎Ъ//o
	NPC_NEZAR,//c115//?ㅼ옄瑜?/o
	NPC_GALLAND,//c116//媛덈???/o
	NPC_DURAK,//c117//?�?쇳겕//o
	NPC_KING,//c118//?먮뱶紐щ뱶//o
	NPC_WOMANGHOST,//c119//?ъ옄?좊졊//o
	NPC_MANGHOST,//c120//?⑥옄?좊졊//o
	NPC_AUSTIN,//c121//?ㅼ뒪???좊졊)//o
	NPC_SOUL,//c122//留덉솗???ъ옣//o

	TOTALENEMY,

	ENEMY_BULLET_NOSHADOW,
	ENEMY_BULLET_SKEL,

	MAXMONSTER = TOTALENEMY - NPC_CAPTAIN,

	SMALLMONSTER = 0,//怨듦꺽?뱁븯硫??⑤뒗 ?묒? 紐ъ뒪??
	BIGMONSTER,//怨듦꺽?뱁븯硫??⑥? ?딄퀬 諛�由щ뒗 紐ъ뒪??
	GIANTMONSTER,//?꾩삁 ?덈?由щ뒗 紐ъ뒪??

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
