#pragma once

#ifndef _DEF_ITEM_H_
#define _DEF_ITEM_H_

typedef enum _itemDef {
	EQUIP_WEAPON = 0,	//臾닿린 //?숈쟾, ?숈쟾二쇰㉧?? ?섑듃, ?섏뒪???꾩씠?? PVP ?꾩씠?쒖쓽 ?띾뱷?됱쓣 ?ъ슜?섑듃?됰룄 ?덈떎.
	EQUIP_HELM,				//?ш뎄 //?≪뀡移대뱶 ?ㅽ궗?먯꽌 ?띾뱷?섎뒗 ?숈쟾??%濡?利앷??쒖폒以�??(?뚯닔??
	EQUIP_ARMOR,			//媛묒샆 //??紐ъ뒪?곗떆 類뤾린???숈쟾??%濡?媛먯냼?쒖폒以�??(?뚯닔??
	EQUIP_GLOVE,			//?κ컩 //?≪뀡移대뱶 ?숈쟾, ?숈쟾二쇰㉧?덉뿉???숈쟾??%濡?利앷??쒖폒以�??(?뚯닔??
	EQUIP_PANTS,			//諛붿? //?≪뀡移대뱶 ?덊듃?먯꽌 ?띾뱷?섎뒗 ?숈쟾??%濡?利앷??쒖폒以�??(?뚯닔??
	EQUIP_BOOTS,			//?좊컻 //?덉씠?쒓났寃⑹떆 ?띾뱷?섎뒗 ?숈쟾??%濡?利앷??쒖폒以�??(?뚯닔??
	EQUIP_NECK,			//목걸??
	EQUIP_RING,		//諛섏?
	TOTALEQUIP,

	STAR1 = 0,
	STAR2,
	STAR3,
	STAR4,
	STAR5,
	STAR6,
	STAR7,
	STAR8,
	STAR9,
	STAR10,

	TOTALSTAR,

	MAXSTAR = 6,

	GRADE_NORMAL = 0,
	GRADE_SUPERIOR,
	GRADE_RARE,
	GRADE_SET,
	GRADE_EPIC,
	GRADE_LEGEND,

	TOTALGRADE,

	ITEMMAXLEVEL = 5,
	ITEMHAMMERCNT = 5,

	TOTALCLOAK = 6,
	TOTALHELM = 11,
	TOTALARMOR = 11,
	TOTALSHIELD = 6,
	TOTALSWORD = 38,

	ITEMPTR_INVEN = 0,
	ITEMPTR_EMPTY = 1000,
	ITEMPTR_SHOP = 2000,
	ITEMPTR_EQUIP = 3000,
	ITEMPTR_NEWITEM = 4000,
	ITEMPTR_TEMPITEM = 60000,
	ITEMPTR_RANKERITEM = 61000,
	ITEMPTR_ARENAITEM = 62000,
	ITEMPTR_HELPITEM = 63000,

	MAXHELPITEM = 20,

	ITEM_SWORD = 0,
	ITEM_GUN,//1
	ITEM_BOOMERANG,//2
	ITEM_HELM,//3
	ITEM_HAT,//4
	ITEM_CAP,//5
	ITEM_ARMOR,//6
	ITEM_VEST,//7
	ITEM_COAT,//8
	ITEM_GUNTLET,//9
	ITEM_ARMLET,//10
	ITEM_GLOVE,//11
	ITEM_KILT,//12
	ITEM_SKIRT,//13
	ITEM_PANTS,//14
	ITEM_GREAVES,//15
	ITEM_SHOES,//16
	ITEM_BOOTS,//17
	ITEM_NECK,//18
	ITEM_RING,
	ITEM_GEM,
	ITEM_WASTE,
	ITEM_IRON,
	ITEM_LEATHER,
	ITEM_CLOTH,
	ITEM_WOOD,
	ITEM_ESSENCE,
	ITEM_RECIPE,
	ITEM_QUEST,
	ITEM_NETITEM,
	ITEM_GOLD,
	ITEM_KEY,
	ITEM_STATUE,
	ITEM_HEART,
	ITEM_MEDAL,
	ITEM_STAR,
	ITEM_HAMMER,
	ITEM_SHIELD,
	ITEM_BOX,
	ITEM_CREW,
	ITEM_SKILL,

	TOTALITEMTYPE,

	BOX_RANDOM = 0,//紐⑤뱺 醫낅쪟???꾩씠?쒖씠 ???섏삤??BOX
	BOX_EQUIP,//?ㅽ럹???λ퉬留??섏삤??
	BOX_CREW,//罹먮┃?곌? ?섏삤??
	BOX_SKILL,//?ㅽ궗???섏삤??

	//검 : ITEM_SWORD
	ITEM_SWORD_STICK = 0,//1//?곗뒿??紐쎈뫁??
	ITEM_SWORD_LONG,//2//롱소??
	ITEM_SWORD_CUTTER,//3//泥섑삎?먯쓽 寃�
	ITEM_SWORD_RUIN,//4//?뚮㈇??李몃쭏??
	ITEM_SWORD_SEEKER,//5//異붿쟻?먯쓽 寃�
	ITEM_SWORD_DOUBLE,//6//寃⑸끂???묐궇寃�
	ITEM_SWORD_ELVEN,//7//?섑샇?먯쓽 寃�
	ITEM_SWORD_ROYAL,//8//?뺢????섑샇??
	ITEM_SWORD_GHOST,//9//?섏같??寃�
	ITEM_SWORD_GHOST2,//10//?뚯슱 ?щ옒??
	ITEM_SWORD_FRAME,//11//?뚮젅?꾩냼??
	ITEM_SWORD_ICE,//12//?꾩씠?ㅼ냼??
	ITEM_SWORD_THUNDER,//13//?щ뜑?뚮뱶
	ITEM_SWORD_EARTH,//14//?댁뒪?뚮뱶
	ITEM_SWORD_LAEVATEINN,//15//?덈컮?뚯씤
	ITEM_SWORD_STORMBRINGER,//16//?ㅽ넱釉뚮쭅嫄?
	ITEM_SWORD_CALADBOLG,//17//移쇰씪?쒕낵洹?
	ITEM_SWORD_BALMUNG,//18//발뭉
	ITEM_SWORD_HRUNTING,//19//?먮，??
	ITEM_SWORD_GIANT,//20//嫄곗씤??移?
	ITEM_SWORD_MISTILTEINN,//21//誘몄뒪?명뀒??
	ITEM_SWORD_EXCALIBUR,//22//?묒뒪移쇰━踰?
	ITEM_SWORD_HOLY,//23//?�由ъ냼??
	ITEM_SWORD_DARK,//24//?ㅽ겕?뚮뱶
	ITEM_SWORD_LEO,//25//?덉삤?뚮뱶
	ITEM_SWORD_DEATH,//26//?ъ떊????
	ITEM_SWORD_DRAGONCLOW,//27//?쒕옒怨??대줈??
	ITEM_SWORD_DRAGONTOOTH,//28//?⑸！???닿툑??
	ITEM_SWORD_DRAGONGOD,//29//?좊！留덇컯寃�
	ITEM_SWORD_DRAGONSLAYER,//30//?쒕옒怨??щ젅?댁뼱
	ITEM_SWORD_ULTIMATE,//31//?쇳떚諛뗭냼??
	ITEM_SWORD_DIMENSIONAL,//32//차원??검
	ITEM_SWORD_HEAVEN,//33//천공??검
	ITEM_SWORD_STARDUST,//34//?ㅽ??붿뒪??
	ITEM_SWORD_KING,//35//?⑥솗??寃�
	TOTAL_SWORD,

	//珥?: ITEM_GUN
	ITEM_GUN_PISTOL = 0,//諛쒗솕??珥?
	ITEM_GUN_REVOLVER,//由щ낵踰??뚯씠??
	ITEM_GUN_MAGNUM,//45援ш꼍 ?ㅽ넗嫄?: ?ъ씪?고듃 ?щ윭
	ITEM_GUN_AUTOGUN45MM,//怨좎졇??嫄?: ??뀛由?罹먮끉
	ITEM_GUN_JEWELGUN,//?뚯쿇留덈룄珥?: 留덈룄癒몄떊嫄?
	ITEM_GUN_EXPLOSION,//?쒖뼇??珥?: ?덊띁?몃컮
	ITEM_GUN_CROSSFIRE,//?ы뙆?댁뼱 嫄?: ?명럹瑜대끂 罹먮끉 : 留덈！?댄솕??
	ITEM_GUN_INFERNO,//?щ줈???뚯씠??: ?뚯뒪?�癒쇳듃 : ?쇨렇?섎줈??
	TOTAL_GUN,

	//부메랑 : ITEM_BOOMERANG
	ITEM_BOOMERANG_BOOMERANG = 0,//?щ깷??遺�硫붾옉
	ITEM_BOOMERANG_VOYAGER,//?щ씪?댁꽌
	ITEM_BOOMERANG_WINDWALKER,//媛뺤쿋 遺�硫붾옉 : ?덈뱶 ?щ옒??
	ITEM_BOOMERANG_DOUBLECROSS,//?몃씪???ｌ? : ???몃씪?댁빑湲�
	ITEM_BOOMERANG_THUNDERMASTER,//?쇱씠?몃떇 ?ｌ? : ?쒗깂??遺�硫붾옉
	ITEM_BOOMERANG_SOULCHASER,//?뚯슱 泥댁씠??: ???щ젅?댁뼱
	ITEM_BOOMERANG_GRYPHONWING,//洹몃━????: ???ㅻ툕 ?곗뒪 : ?쒕옒怨???
	ITEM_BOOMERANG_MEGATRIAL,//濡쒖빱?ㅽ듃 ?뚰듃 : ?쒕끂?ъ씠????: ?붿옱?ㅽ꽣 ?ｌ?
	TOTAL_BOOMERANG,

	//?щĸ : ITEM_HELM
	ITEM_HELM_BRONZE = 0,//1//?ㅻ뱶 媛�??
	ITEM_HELM_BASINET,//2//바시??
	ITEM_HELM_DROW,//3//?붿??щ쫫 : ?쇱툌由ъ삩 ?щĸ
	ITEM_HELM_SPIKEHEAD,//4//寃�?ъ궗???ш뎄 : 釉붾윭???щĸ
	ITEM_HELM_GLADITOR,//5//?ㅽ뙆?댄겕 ?ㅻ뱶 : 洹�?좎쓽 ?ш뎄
	ITEM_HELM_GIANT,//6//洹몃옖???щ쫫 : ?깃린?ъ쓽 ?ш뎄
	ITEM_HELM_RUINED,//7//怨좊????ш뎄 : ?섏쁺???ш뎄 : 誘몃씪二??щ쫫
	ITEM_HELM_TITANIUM,//8//?⑹옄???ш뎄 : ?몄?癒쇳듃 ?щ㎎ : ?ㅼ떆由ъ뒪 ?щ㎎
	TOTAL_HELM,

	//모자 : ITEM_HAT
	ITEM_HAT_COWBOY = 0,//카우보이 모자
	ITEM_HAT_RIDINGGOGGLE,//?곗콉??蹂대떅
	ITEM_HAT_BERET,//?덉씤?� ??: 臾대쾿?먯쓽 紐⑥옄
	ITEM_HAT_WESTERNROMANCE,//?쒗겢由?: 怨⑤뱶 釉붾젅??
	ITEM_HAT_SCOUT,//?щ뱶 ?뚮줈??: ?섎툙 ??
	ITEM_HAT_SNIPERGOGGLE,//?ㅻ굹?댄띁 怨좉? : ?댁뙏???ㅼ퐫??
	ITEM_HAT_ELVENCAP,//?쇰???紐⑥옄 : 移댁삤???붿졇 : ?섏씠?몃찓????
	ITEM_HAT_DRAGONSKULL,//?꾨━?먯뒪?뚯뒪 : 諛쒗궎由??쒗겢??: ?ㅻ뵖 ?щ씪??
	TOTAL_HAT,

	//?먭굔 : ITEM_CAP
	ITEM_CAP_FEATHER = 0,//공작깃털 모자
	ITEM_CAP_BEASTMANE,//귀족의 머리??
	ITEM_CAP_EXPLORERHAT,//嫄곗긽??紐⑥옄 : 罹먮윭踰?由щ뜑
	ITEM_CAP_ACECAP,//?щ깷袁?紐⑥옄 : 濡쒕퉰??罹?
	ITEM_CAP_LIONMANE,//?ъ슦?ъ쓽 紐⑥옄 : 誘몃끂?�?곕Ⅴ??
	ITEM_CAP_GREAVE,//?댁쟻??紐⑥옄 : 議몃━濡쒖졇 罹?
	ITEM_CAP_DEATH,//?먯씠??罹?: 釉뚮젅?대툕 罹?: ?ㅼ씠?덉뒪??罹?
	ITEM_CAP_TROLLHEAD,//?쒕옒怨??덉뼱罹?: ?덈뱶???ㅻ뱶 : 由щ컮?댁뼱??罹?
	TOTAL_CAP,

	//갑옷 : ITEM_ARMOR
	ITEM_ARMOR_BRONZE = 0,//1//?뚰꽣 ?쒕땳
	ITEM_ARMOR_SCALE,//2//미늘 갑옷
	ITEM_ARMOR_BANDED,//3//?섑봽 ?뚮젅?댄듃 : 諛대뵒??硫붿씪
	ITEM_ARMOR_SKULL,//4//?ㅼ뺄 硫붿씪 : 留덇??ъ쓽 ?됯컩
	ITEM_ARMOR_PLATE,//5//?⑷툑?멸났 媛묒샆 : ?쒖썙釉??꾨㉧
	ITEM_ARMOR_RUNIC,//6//誘몄뒪由??꾨㉧ : ?붿젙??媛묒＜
	ITEM_ARMOR_MYTHRIL,//7//怨좊???媛묒샆 : 遺덈㈇??媛묒＜ : 釉뚮━嫄대뵖
	ITEM_ARMOR_DRAGONSKIN,//8//?⑸퉬??媛묒샆 : ?⑸！??媛묒샆 : 諛뷀븯臾댄듃 ?꾨㉧
	TOTAL_ARMOR,

	//조끼 : ITEM_VEST
	ITEM_VEST_WESTERN = 0,//카우보이 조끼
	ITEM_VEST_LEOPARD,//?ㅽ겕 議곕겮
	ITEM_VEST_SILK,//諛⑸옉?먯쓽 議곕겮 : ?쒕컮?대쾶 議곕겮
	ITEM_VEST_PIRATE,//?꾩쟻??議곕겮 : ?댁뙏??踰좎뒪??
	ITEM_VEST_BALL,//踰⑤껙 ?붿툩 : 怨좊뵓 ?붿툩
	ITEM_VEST_STAR,//洹�議깆쓽 議곕겮 : ?�?ъ뒳 議곕겮
	ITEM_VEST_SPATIOTEMPORAL,//吏꾪솉鍮??붿툩 : 遺덉궗???붿툩 : 諭�?뚯씠??濡쒕뱶
	ITEM_VEST_QUEEN,//?좉???濡쒕툕 : ?몃씪??濡쒕툕 : 猷⑥떆??濡쒕툕
	TOTAL_VEST,

	//코트 : ITEM_COAT
	ITEM_COAT_SIMPLE = 0,//?섏닔??肄뷀듃
	ITEM_COAT_PADDING,//?⑤뵫 ?꾨㉧
	ITEM_COAT_LEATHER,//?멸?二?肄뷀듃 : 洹몃━利먮━ ?ㅽ궓
	ITEM_COAT_CUREBOIL,//?먯뼱 蹂댁씪 : 肄붿븘?� ?ㅼ???
	ITEM_COAT_BEAST,//洹�議깆쓽 肄뷀듃 : ?묎퉴留덇? 肄뷀듃
	ITEM_COAT_GRIZZLY,//洹뱀???肄뷀듃 : 釉붾━?먮뱶 媛�??
	ITEM_COAT_CROCODYLE,//??肄뷀듃 : 媛�怨좎씪 肄뷀듃 : ?섍??섏뒪 肄뷀듃
	ITEM_COAT_HYDRASCALE,//諛붿씠??肄뷀듃 : 醫낅쭚??肄뷀듃 : 移댁삤???좏럹??
	TOTAL_COAT,

	//嫄댄???: ITEM_GUNTLET
	ITEM_GUNTLET_IRON = 0,//1//?몃뱶 媛�??
	ITEM_GUNTLET_CHAIN,//2//泥?룞 ?κ컩
	ITEM_GUNTLET_MONSTER,//3//泥댁씤 嫄댄???: 紐⑦뿕?먯쓽 ?κ컩
	ITEM_GUNTLET_KNIGHT,//4//?섏씠??湲�濡쒕툕 : 紐낆꽦???κ컩
	ITEM_GUNTLET_EAGLECLAW,//5//鍮꾩뒪???몃뱶 : ?ㅼ슦嫄?嫄댄???
	ITEM_GUNTLET_SINE,//6//?쇱씠吏?嫄댄???: 臾댁뙇???κ컩
	ITEM_GUNTLET_JUSTICEHAND,//7//愿묒쟾?ъ쓽 ?κ컩 : ?뚭꺽?뚯닔 : ?쒕컮???먰넲
	ITEM_GUNTLET_HOLYHAND,//8//?쒕옒怨??몃뱶 : 諛깅！???κ컩 : 諛뷀븯臾댄듃 ?몃뱶
	TOTAL_GUNTLET,

	//?붿컡 : ITEM_ARMLET
	ITEM_ARMLET_LEATHER = 0,//?ъ젣??臾듭＜
	ITEM_ARMLET_DESERT,//?ы뻾?먯쓽 ?붿컡
	ITEM_ARMLET_EXPLORER,//諛깃툑 釉뚮젅?ㅻ젢 : ?곗씤???붿컡
	ITEM_ARMLET_RAIDERS,//?꾩궗???붾젢 : ?꾪봽 ?붾젢
	ITEM_ARMLET_NOBLESS,//?먮찓?꾨뱶 ?붿컡 : ?몃툝?덉뒪 ?붾젢
	ITEM_ARMLET_DEVIL,//?대툝 ?붾젢 : 紐쎈쭏???붿컡
	ITEM_ARMLET_DIGNITY,//?꾩뾼???붿컡 : 吏�諛곗옄???붿컡 : ?좏봽?덉뒪 ?붾젢
	ITEM_ARMLET_HERO,//?곸썒???붿컡 : ?뚯슱 釉뚮젅?ㅻ젢 : 媛??몃뱶
	TOTAL_ARMLET,

	//?κ컩 : ITEM_GLOVE
	ITEM_GLOVE_TRAVELER = 0,//?ы뻾?먯쓽 ?κ컩
	ITEM_GLOVE_DUALTIE,//?댁쨷留ㅻ벊 ?κ컩
	ITEM_GLOVE_LINEN,//?뚮ℓ移섍린 ?κ컩 : ?�?꾩슦 ?몃뱶
	ITEM_GLOVE_RUNE,//?ㅽ겕 湲�濡쒕툕 : 洹�怨듭옄???κ컩
	ITEM_GLOVE_FAIRY,//?멸났?ъ쓽 ?κ컩 : 留덉뒪??湲�?щ툕
	ITEM_GLOVE_ROCKET,//留덈쾿臾몄뼇 ?κ컩 : 而ㅼ뒪??湲�濡쒕툕
	ITEM_GLOVE_LACEMITTEN,//?ы뙋????: 援ъ썝????: ?댄꽣???몄?
	ITEM_GLOVE_GLORY,//?깆옄???κ컩 : ?붾씪??湲�濡쒕툕 : ?�由??몃뱶
	TOTAL_GLOVE,

	//?ы듃 : ITEM_KILT
	ITEM_KILT_CHAIN = 0,//1//諛대뵫 ?ы듃
	ITEM_KILT_DUALCHAIN,//2//泥댁씤 ?ы듃
	ITEM_KILT_BATTLE,//3//?섏씠???ы듃 : 諛고? ?ы듃
	ITEM_KILT_NIGHTMARE,//4//?ㅼ뺄 ?ы듃 : ?щ졊??諛붿?
	ITEM_KILT_BATTLEFIELD,//5//?섎졊??諛붿? : ?좊Ⅴ??諛붿?
	ITEM_KILT_DWARVEN,//6//誘몄뒪由??ы듃 : ?섏뼱由??ы듃
	ITEM_KILT_DURAHAN,//7//?먯씤?섑듃 ?ы듃 : ?댄꽣???ы듃 : ?몃━諛??ы듃
	ITEM_KILT_EARTHQUAKE,//8//?⑹닔???ы듃 : 泥?！???ы듃 : ?⑷린??諛붿?
	TOTAL_KILT,

	//諛붿? : ITEM_SKIRT
	ITEM_SKIRT_BROCADE = 0,//?묐떒 ?ㅼ빱??
	ITEM_SKIRT_CARPSKIN,//鍮덊떚吏� ?ㅼ빱??
	ITEM_SKIRT_VELVET,//?⑦뭾?쇱깋 移섎쭏 : ?띾젴???ㅼ빱??
	ITEM_SKIRT_NOBLE,//踰⑤껙 ?ㅼ빱??: ?뚭났?�??移섎쭏
	ITEM_SKIRT_GENERAL,//??뭾???ㅼ빱??: 臾댁?媛쒕튆 移섎쭏
	ITEM_SKIRT_GLORY,//湲덉떎??移섎쭏 : ?ъ젣???ㅼ빱??
	ITEM_SKIRT_CHAOS,//?곴킅??移섎쭏 : ?꾩옄??移섎쭏 : ?깅졊??移섎쭏
	ITEM_SKIRT_HERO,//?ъ젣???ㅼ빱??: 鍮꾩뒋???ㅼ빱??: ?쒖뼇???ㅼ빱??
	TOTAL_SKIRT,

	//諛붿? : ITEM_PANTS
	ITEM_PANTS_RIDING = 0,//?밸쭏??諛붿?
	ITEM_PANTS_VINTAGEJEAN,//移댄봽?ㅽ궓 ?ъ툩
	ITEM_PANTS_BLAZE,//留앸졊???ъ툩 : 癒몃? 諛대뵒吏�
	ITEM_PANTS_ASSASSIN,//?묐떒??諛붿? : ?댁뙏???ъ툩
	ITEM_PANTS_TEMPEST,//?몄씪???ъ툩 : ?쒕룆??諛붿?
	ITEM_PANTS_SCARLETLEGGINGS,//?곗????ъ툩 : 罹먮윭諛??ъ툩
	ITEM_PANTS_HEAVEN,//移댁삤???ъ툩 : 移⑤У??諛붿? : ?꾨퉬???ъ툩
	ITEM_PANTS_SATANIC,//媛�?붿븞 ?ъ툩 : 耳덈쿋濡쒖뒪 ?덈뜑 : ?꾨늻鍮꾩뒪 諛붿?
	TOTAL_PANTS,

	//?ν솕 : ITEM_GREAVES
	ITEM_GREAVES_TRAINER = 0,//1//肄뷀띁 洹몃━釉?
	ITEM_GREAVES_CHAIN,//2//諛대뵒??洹몃━釉?
	ITEM_GREAVES_KNIGHT,//3//泥댁씤 洹몃━釉?: ?섏씠??洹몃━釉?
	ITEM_GREAVES_FROZEN,//4//?꾨줈利?洹몃━釉?: 留뚮뀈?ㅼ쓽 ?좊컻
	ITEM_GREAVES_GOLEM,//5//?뚮젅?댄듃 遺�痢?: ?쒖썙釉?洹몃━釉?
	ITEM_GREAVES_GIANT,//6//鍮낇뭼 洹몃━釉?: 怨⑤젞 洹몃━釉?
	ITEM_GREAVES_GHOST,//7//留덇??ъ쓽 ?좊컻 : ?щ졊???좊컻 : 醫낅쭚??諛쒖냼由?
	ITEM_GREAVES_LEGEND,//8//?쒕옒怨?洹몃━釉?: 留덈！??諛쒖옄援?: 媛�?댁븘 洹몃━釉?
	TOTAL_GREAVES,

	//?좊컻 : ITEM_SHOES
	ITEM_SHOES_CLEAN = 0,//?⑥뒪???덉쫰
	ITEM_SHOES_CHASER,//?ㅼ썾?대뱶 ?덉쫰
	ITEM_SHOES_LEATHER,//?쇱씠???덉쫰 : 諛�由ы꽣由??뚯빱
	ITEM_SHOES_ROCKY,//移좏쓳???덉쫰 : 留덈????덉쫰
	ITEM_SHOES_CARVING,//洹�遺�?몄쓽 ?좊컻 : 濡쒖뻹 ?�?덈툕
	ITEM_SHOES_NETHERWORLD,//由ъ튂 ?덉쫰 : ?ы? ?뚯씪利?
	ITEM_SHOES_INCARNATION,//?꾨━利??덉쫰 : 誘몃씪???덉쫰 : 洹몃씪鍮꾪떚 ?덉쫰
	ITEM_SHOES_HEAVENS,//踰좎씠洹몃???: ?섏씠???덉쫰 : ?곗뒪?곕땲 ?덉쫰
	TOTAL_SHOES,

	//遺�痢?: ITEM_BOOTS
	ITEM_BOOTS_SUEDE = 0,//?ㅻ땲而ㅼ쫰
	ITEM_BOOTS_WESTERN,//?ㅼ틦鍮덉? 遺�痢?
	ITEM_BOOTS_RIDING,//泥쒕뫁媛�二??좊컻 : ?숇ː???먭뎅
	ITEM_BOOTS_RICH,//媛�?쒕꼫 遺�痢?: ?좊젋??猷⑦듃
	ITEM_BOOTS_OGRE,//?몄씪??遺�痢?: 罹≫떞 遺�痢?
	ITEM_BOOTS_DARK,//?�?뱀쓽 ?좊컻 : ???ㅽ듃?쇱씠??
	ITEM_BOOTS_MIRACLE,//?섎젅硫섑깉 遺�痢?: 釉뚮━吏??덈뱶 : ?쒗럹?ㅽ듃 遺�痢?
	ITEM_BOOTS_DESTINY,//?먯뼱?뚯빱 : ?대씪?곕뱶 遺�痢?: ?ㅻ툙由?遺�痢?
	TOTAL_BOOTS,

	//목걸??: ITEM_NECK
	ITEM_NECK0 = 0,//紐낆삁???쒕뜕??0)
	ITEM_NECK1,//?곗삦??釉뚮줈移?1)
	ITEM_NECK2,//李곕굹???붿컡(2)
	ITEM_NECK3,//?⑷툑 諛붾뒛(3)
	ITEM_NECK4,//?뚯뿴???붿컡(4)
	ITEM_NECK5,//硫뷀뵾?ㅽ넗 ?쇰━(5)
	ITEM_NECK6,//?щ㈇???섑봽(6)
	ITEM_NECK7,//?몄뼱??癒몃━?�(7)
	ITEM_NECK8,//李ы듃???쒕뜕??8)
	ITEM_NECK9,//미래??거울(9)
	ITEM_NECK10,//?쇱쓽 紐⑤옒?쒓퀎(10)
	ITEM_NECK11,//吏�?μ쓽 留뚰솕寃?11)
	ITEM_NECK12,//?꾨뒫??釉뚮줈移?12)
	ITEM_NECK13,//?앸챸??蹂댁삦(13)
	ITEM_NECK14,//증식??목걸??14)
	ITEM_NECK15,//천공??목걸??15)
	ITEM_NECK16,//?꾩옄????16)
	ITEM_NECK17,//轅덉쓽 ?ㅼ뭅由щ굹(17) X
	ITEM_NECK18,//臾댄븳???섏묠諛?18) X
	ITEM_NECK19,//湲곗뼲???ㅻⅤ怨?19) X
	ITEM_NECK20,//?쒖웳?댁쓽 怨?20)
	ITEM_NECK21,//?먯슃????븘由?21)
	ITEM_NECK22,//?щ뜑?명삎(22)
	ITEM_NECK23,//?ㅻ쭏??釉뚮줈移?23)
	ITEM_NECK24,//?좊Ⅴ???낅낫(24)
	ITEM_NECK25,//?⑹옄???쒓퀎(25)
	ITEM_NECK26,//?낅쭏??肉뷀뵾由?26) X
	ITEM_NECK27,//?꾨쭔?붿? ?ш?(27) X
	TOTAL_NECK,

	//목걸??: ITEM_RING
	ITEM_RING0 = 0,	//?ъ떊??諛섏?(28)
	ITEM_RING1,	//?듭같??諛섏?(29)
	ITEM_RING2,	//?쒓났??諛섏?(30)
	ITEM_RING3,	//?대갑??諛섏?(31)//|e?ъ슜??i%d%%|j?뺣쪧濡??곹깭?댁긽?쒓굅
	ITEM_RING4,	//?고샇??諛섏?(32)
	ITEM_RING5,	//?앺솚??諛섏?(33)//|e?ъ슜??|jHP |i%d |j?뚮났
	ITEM_RING6,	//?ъ깮??諛섏?(34)//|e?ъ슜??|i%d%%|j?뺣쪧濡?異붽??�寃?
	ITEM_RING7,	//??＜??諛섏?(35)
	ITEM_RING8,	//怨⑤젞??諛섏?(36)
	ITEM_RING9,	//愿묐???諛섏?(37)//|e?ъ슜??|j?뚰뵾 |i%d%%|j利앷?
	ITEM_RING10,	//?먰븳??諛섏?(38)//|e?ъ슜??j愿�?듦났寃⑺솗瑜?i%d%%|j利앷?
	ITEM_RING11,	//?좊뀗??諛섏?(39)
	ITEM_RING12,	//愿묓룷??諛섏?(40)
	ITEM_RING13,	//?뱀옄??諛섏?(41)
	ITEM_RING14,	//沅곴레??諛섏?(42)
	ITEM_RING15,	//李⑥썝??諛섏?(43)//|e?ъ슜??|j?곷갑?대룄媛먯냼 -|i%d
	ITEM_RING16,	//?곹솕??諛섏?(44)
	ITEM_RING17,	//?됱슫??諛섏?(45)
	TOTAL_RING,

	//보석 : ITEM_GEM
	ITEM_GEM_RUBY = 0,	//루비(46)//PREFIX_FIRE_REGIST
	ITEM_GEM_SAPPHIRE,	//?ы뙆?댁뼱(47)//PREFIX_FROST_REGIST
	ITEM_GEM_AMETHYST,	//?먯닔??48)//PREFIX_THUNDER_REGIST
	ITEM_GEM_DIAMOND,	//?ㅼ씠?꾨が??49)//PREFIX_HOLY_REGIST
	ITEM_GEM_PERL,	//진주(50)//PREFIX_DARK_REGIST
	ITEM_GEM_EMERALD,	//?먮찓?꾨뱶(51)//SUFFIX_ARMOR
	TOTAL_GEM,

	//?뚮え?꾩씠??: ITEM_WASTE
	ITEM_WASTE_RETURN = 0,	//洹�?섏꽌(24)
	ITEM_WASTE_STAR,				//蹂꾩쓽 ?⑥븮(52)
	ITEM_WASTE_MOON,				//?ъ쓽 ?⑥븮(53)
	ITEM_WASTE_SUN,					//?쒖뼇???⑥븮(54) //怨⑤뱶 2諛??대깽??
	ITEM_WASTE_SILVER,				//?�鍮??덈툕(55)
	ITEM_WASTE_GOLD,				//湲덈튆 ?덈툕(56)
	ITEM_WASTE_SCARLET,			//吏꾪솉鍮??덈툕(57)
	ITEM_WASTE_WATER,			//?멸퀎?섏쓽 臾?58)
	ITEM_WASTE_FLUTE,				//?�?쇰━(5)
	ITEM_WASTE_EYEWASH,		//?덉빟(60)
	ITEM_WASTE_ANTIDOTE,		//?대룆??59)
	ITEM_WASTE_WING,				//由댁쓽 ?좉컻(62)
	ITEM_WASTE_HOLYWATER,	//?깆닔(61)
	ITEM_WASTE_FIRESTONE,		//遺덉쓽 ?뺣졊??63)
	ITEM_WASTE_FROSTSTONE,	//臾쇱쓽 ?뺣졊??64)
	ITEM_WASTE_THUNDERSTONE,	//踰덇컻???뺣졊??65)
	ITEM_WASTE_HOLYSTONE,					//鍮쏆쓽 ?뺣졊??66)
	ITEM_WASTE_DARKSTONE,					//?대몺???뺣졊??67)
	ITEM_WASTE_FIREELEMENTAL,			//?붿뿼???뺣졊??46)
	ITEM_WASTE_FROSTELEMENTAL,			//?쇱쓬???뺣졊??47)
	ITEM_WASTE_THUNDERELEMENTAL,	//泥쒕뫁???뺣졊??48)
	ITEM_WASTE_HOLYELEMENTAL,			//?ш킅???뺣졊??49)
	ITEM_WASTE_DARKELEMENTAL,			//移좏쓳???뺣졊??50)
	ITEM_WASTE_DAMAGE,			//|e강화??비약(207)
	ITEM_WASTE_DEFENSE,			//|e?몃궡??鍮꾩빟(208)
	ITEM_WASTE_MAGIC,				//|e치유??비약(210)
	ITEM_WASTE_SKILL,				//|e마법??비약(209)
	TOTAL_WASTE,

	//泥좉퀎???쒖옉?щ즺 : ITEM_IRON
	ITEM_IRON_LV1 = 0,	//泥좉킅??45媛?: 68)
	ITEM_IRON_LV2,	//?�愿?39媛?: 69)
	ITEM_IRON_LV3,	//?좊ⅷ ?뚰렪(39媛?: 70)
	ITEM_IRON_LV4,	//?ㅻ쭏?ㅼ빱??42媛?: 71)
	ITEM_IRON_LV5,	//?꾨떎留뚰떚?�(39媛?: 72)
	ITEM_IRON_LV6,	//誘몄뒪由?寃곗젙(42媛?: 73)
	ITEM_IRON_LV7,	//?ㅻ━?섎Ⅴ肄?48媛?: 74)
	ITEM_IRON_LV8,	//?댄꽣???먯꽍(30媛?: 75)
	TOTAL_IRON,

	//媛�二쎄퀎???쒖옉?щ즺 : ITEM_LEATHER
	ITEM_LEATHER_LV1 = 0,	//?뉗? 媛�二?45媛?: 76)
	ITEM_LEATHER_LV2,	//諛섏쭩?대뒗 鍮꾨뒛(39媛?: 77)
	ITEM_LEATHER_LV3,	//臾댁뇿 媛�二?39媛?: 78)
	ITEM_LEATHER_LV4,	//?뚯뿰蹂�??鍮꾨뒛(42媛?: 79)
	ITEM_LEATHER_LV5,	//?щ튆 媛�二?39媛?: 80)
	ITEM_LEATHER_LV6,	//諛붿떎由ъ뒪??鍮꾨뒛(42媛?: 81)
	ITEM_LEATHER_LV7,	//吏�?μ궗??媛�二?48媛?: 82)
	ITEM_LEATHER_LV8,	//遺됱? ?⑸퉬??30媛?: 83)
	TOTAL_LEATHER,

	//泥쒓퀎???쒖옉?щ즺 : ITEM_CLOTH
	ITEM_CLOTH_LV1 = 0,	//媛먯깋 ?ㅽ???44媛?: 84)
	ITEM_CLOTH_LV2,	//嫄곕?以??룰컧(41媛?: 7)
	ITEM_CLOTH_LV3,	//鍮꾨떒 ?ㅽ???40媛?: 85)
	ITEM_CLOTH_LV4,	//?ъ뿰???ㅽ???41媛?: 86)
	ITEM_CLOTH_LV5,	//?�?섏닔 ?룰컧(40媛?: 87)
	ITEM_CLOTH_LV6,	//泥쒓퀬???룰컧(45媛?: 88)
	ITEM_CLOTH_LV7,	//怨듯뿀???ㅽ???45媛?: 89)
	ITEM_CLOTH_LV8,	//猷щЦ???룰컧(28媛?: 90)
	TOTAL_CLOTH,

	//?섎Т怨꾩뿴 ?쒖옉?щ즺 : ITEM_WOOD
	ITEM_WOOD_LV1 = 0,	//踰쇰씫留욎? 媛�吏�(60媛?: 91)
	ITEM_WOOD_LV2,	//?쇱뼱遺숈? 媛�吏�(29媛?: 92)
	ITEM_WOOD_LV3,	//留⑤뱶?덉씠 肉뚮━(44媛?: 93)
	ITEM_WOOD_LV4,	//嫄곗씤??肉뚮━(37媛?: 94)
	ITEM_WOOD_LV5,	//?�二쇰컺?� 肉뚮━(44媛?: 95)
	ITEM_WOOD_LV6,	//怨좊???媛�吏�(37媛?: 96)
	ITEM_WOOD_LV7,	//吏�?μ쓽 肉뚮━(53媛?: 97)
	ITEM_WOOD_LV8,	//?멸퀎?섏쓽 媛�吏�(20媛?: 98)
	TOTAL_WOOD,

	//?뱀닔?щ즺 : ITEM_ESSENCE
	ITEM_ESSENCE0 = 0,	//?⑤떒??猿띿쭏(9媛?: 99)
	ITEM_ESSENCE1,	//?ㅼ뿼???앹엥(9媛?: 100)
	ITEM_ESSENCE2,	//?ъ뿰???덈룞??7媛?: 20)
	ITEM_ESSENCE3,	//?�二쇰컺?� ?닿낏(11媛?: 101)
	ITEM_ESSENCE4,	//?몃Ⅸ 鍮꾨뒛(9媛?: 102)
	ITEM_ESSENCE5,	//諛섏쭩?대뒗 ?ъ옣(9媛?: 103)
	ITEM_ESSENCE6,	//?쇱깮????18媛?: 104)
	ITEM_ESSENCE7,	//媛덈씪吏??닿툑??18媛?: 105)
	ITEM_ESSENCE8,	//?쇱쓽 利앸쪟??9媛?: 21)
	ITEM_ESSENCE9,	//鍮쏆쓽 源껎꽭(9媛?: 106)
	ITEM_ESSENCE10,	//吏덊뭾??議곌컖(12媛?: 107)
	ITEM_ESSENCE11,	//?덉쓽 寃곗젙(12媛?: 8)
	ITEM_ESSENCE12,	//寃곕튃???λ（(12媛?: 108)
	ITEM_ESSENCE13,	//?곕젅 媛�猷?6媛?: 109)
	ITEM_ESSENCE14,	//?뚮Ц???먭린(6媛?: 110)
	ITEM_ESSENCE15,	//留덈젰??援ъ뒳(6媛?: 13)
	ITEM_ESSENCE16,	//?붿젙???덈Ъ(27媛?: 61)
	ITEM_ESSENCE17,	//愿묓쐶???쇰즺(27媛?: 111)
	ITEM_ESSENCE18,	//?⑸㏏??利앺몴(9媛?: 56)
	ITEM_ESSENCE19,	//?щ씪???ㅽ솢??9媛?: 59)
	ITEM_ESSENCE20,	//?쇰????곸꽍(9媛?: 128)
	ITEM_ESSENCE21,	//?붿꽍 ?뚰렪(9媛?: 113)
	ITEM_ESSENCE22,	//?곹샎??瑗щ━(9媛?: 114)
	ITEM_ESSENCE23,	//?띿뿼????옄媛�(9媛?: 115)
	ITEM_ESSENCE24,	//?⑹쿇??蹂댁＜(9媛?: 0)
	ITEM_ESSENCE25,	//?좏샊???λ즺(9媛?: 116)
	ITEM_ESSENCE26,	//留뚭퀬??肉?18媛?: 117)
	ITEM_ESSENCE27,	//?꾨뒫???섏젙(18媛?: 16)
	ITEM_ESSENCE28,	//?�?섏닔 ?좉컻(9媛?: 118)
	ITEM_ESSENCE29,	//維쇰퉬?곗뒪????9媛?: 119)
	ITEM_ESSENCE30,	//?곸썝????9媛?: 1)
	ITEM_ESSENCE31,	//?몄뒪 ?쒖솗??9媛?: 27)
	ITEM_ESSENCE32,	//?щ퉬???ㅽ넠(18媛?: 120)
	ITEM_ESSENCE33,	//臾섏???諛섎뵩遺?9媛?: 121)
	ITEM_ESSENCE34,	//吏�諛곗쓽 ?쇱?李?9媛?: 122)
	ITEM_ESSENCE35,	//?좏럹???ㅽ넠(18媛?: 123)
	ITEM_ESSENCE36,	//蹂쇱??대끂 ??18媛?: 124)
	ITEM_ESSENCE37,	//?꾨줈利???18媛?: 125)
	ITEM_ESSENCE38,	//?명뵾?덊떚 蹂쇳듃(18媛?: 126)
	ITEM_ESSENCE39,	//?ㅼ쫹留??⑦봽(6媛?: 18)
	ITEM_ESSENCE40,	//媛�怨듬맂 留덉꽍(6媛?: 17)
	ITEM_ESSENCE41,	//?⑹쿇????6媛?: 127)
	ITEM_ESSENCE42,	//湲덈떒??怨쇱떎(6媛?: 128)
	ITEM_ESSENCE43,	//?곷！???④껐(6媛?: 129)
	ITEM_ESSENCE44,	//?먰샎??寃곗젙(6媛?: 19)
	TOTAL_ESSENCE,

	//?섏뒪???꾩씠??: ITEM_QUEST
	ITEM_QUEST_MUSHROOM = 0,	//?낅늼??踰꾩꽢(112)
	ITEM_QUEST_GOLD,	//留덉씪利덉쓽 ?덉＜癒몃땲(179)
	ITEM_QUEST_ARMLET,	//留덉씪利덉쓽 ?붿컡(2)
	ITEM_QUEST_DARKPIECE,	//?대몺???뚰렪(159)
	ITEM_QUEST_REEF,	//?고샇珥?187)
	ITEM_QUEST_GOLDBAR,	//?⑷툑(160)
	ITEM_QUEST_AMULET,	//?대몺???꾨???161)
	ITEM_QUEST_GHOST,	//?좊졊??188)
	ITEM_QUEST_SCRIPT,	//由ы겢猷⑥쫰???먭퀬(24)
	ITEM_QUEST_FUND,	//?ㅼ씠???덉＜癒몃땲(191)
	ITEM_QUEST_FRUIT,	//?띿뿼??怨쇱떎(189)
	ITEM_QUEST_BIOGRAPHY,	//諛붾━???곸썒??190)
	ITEM_QUEST_FANLETTER,	//?쒕젅??190)
	ITEM_QUEST_NUMMARK,		//번호??190)
	ITEM_QUEST_LETTER,		//洹몄쓣由??몄?(191)
	ITEM_QUEST_TRAINER,	//議곕젴?ъ쓽 ?몄?(191)
	ITEM_QUEST_COMPASS,	//?쒓컙???섏묠諛?197)
	ITEM_QUEST_SECRET,	//湲곕? 臾몄꽌(24)
	ITEM_QUEST_SECRET2,	//?ы??덉쓽 諛�??191)
	ITEM_QUEST_LETTER2,	//?ㅻ━?덉쓽 ?몄?(191)
	ITEM_QUEST_INVITATION,	//珥덈???191)
	ITEM_QUEST_DRUID,	//?쒕（?대뱶???몄?(191)
	ITEM_QUEST_GRANDMA,	//?좊㉧?덉쓽 ?몄?(191)
	ITEM_QUEST_KATHERINE,	//罹먯꽌由곗쓽 諛섏?(28)
	ITEM_QUEST_TREASUREMAP,	//보물지??181)
	ITEM_QUEST_REDHEART,	//?묒뿴???뚯슱(192)
	ITEM_QUEST_BLUEHEART,	//寃곕튃???뚯슱(193)
	ITEM_QUEST_THUNDERHEART,	//?꾧꺽???뚯슱(194)
	ITEM_QUEST_HOLYHEART,	//?꾧킅???뚯슱(195)
	ITEM_QUEST_DARKHEART,	//?뷀쓳???뚯슱(196)
	ITEM_QUEST_FLOWER,	//苑?198)
	ITEM_QUEST_SNOWFLOWER,	//백설??가지(92)
	ITEM_QUEST_MAP_TOTALCOMPLETE,	//?꾨꼍??吏�??190)
	ITEM_QUEST_MAP,	//지??181)
	ITEM_QUEST_MAP_COMPLETE,	//?꾩꽦??吏�??182)
	TOTAL_QUESTITEM,

	//?좊즺?꾩씠??: ITEM_NETITEM
	ITEM_NET_COUPON = 0,	//쿠폰(200)	//-1
	ITEM_NET_TICKET,	//?낆옣沅?201)	//-1
	ITEM_NET_ENCHANT,	//강화??202)	//-1
	ITEM_NET_PROTECT,	//보호??203)	//-1
	ITEM_NET_RECIPE,		//조합??204)	//-1
	ITEM_NET_RESOLUTION,	//분해??205)	//-1
	ITEM_NET_SOCKET,	//?뚯폆??206)	//-1
	ITEM_NET_CHARACTER,	//캐릭??167)	//-1
	ITEM_NET_RESURRECTION,	//遺�?쒖빟(166)	//-1
	ITEM_NET_BOX_WEAPON_HIGH, //怨좉툒臾닿린?곸옄(168)	//BOX_H2
	ITEM_NET_BOX_WEAPON_MID, //以묎툒臾닿린?곸옄(169)	//BOX_H1
	ITEM_NET_BOX_WEAPON_LOW, //?섍툒臾닿린?곸옄(170)	//BOX_H1
	ITEM_NET_BOX_DEFENSE_HIGH, //고급방어구상??171)	//BOX_H2
	ITEM_NET_BOX_DEFENSE_MID, //중급방어구상??172)	//BOX_H1
	ITEM_NET_BOX_DEFENSE_LOW, //?섍툒諛⑹뼱援ъ긽??173)	//BOX_H1
	ITEM_NET_BOX_ACCESSORY_HIGH, //怨좉툒?낆꽭?щ━?곸옄(174)	//BOX_H2
	ITEM_NET_BOX_ACCESSORY_MID, //以묎툒?낆꽭?щ━?곸옄(175)	//BOX_H1
	ITEM_NET_BOX_ACCESSORY_LOW, //?섍툒?낆꽭?щ━?곸옄(176)	//BOX_H1
	ITEM_NET_BOX_RANDOM,	//?쒕뜡?꾩씠?쒖긽??177)	//BOX_CHEST1//?대┃?섎㈃ ?꾩씠?쒖씠 ?섏삤???곸옄. 怨⑤뱶 
	ITEM_NET_BOX_GEM,	//고급보석(178)	//BOX_S5
	ITEM_NET_SINGLEBAG,	//媛�諛?162)	//-1
	ITEM_NET_NETBAG,	//李쎄퀬媛�諛?163)	//-1
	ITEM_NET_APRESET,	//AP초기??164)	//-1
	ITEM_NET_SPRESET,	//SP초기??165)	//-1
	ITEM_NET_PACKAGE_NEWBIE,	//珥덉떖???ㅽ럹??211)	//BOX_S1
	ITEM_NET_PACKAGE_ENCHANT,	//?덊띁媛뺥솕?⑦궎吏�(212)	//BOX_S2
	ITEM_NET_PACKAGE_STONE,	//?ㅽ넠?⑦궎吏�(213)	//BOX_S3
	ITEM_NET_PACKAGE_ARENA,	//?ш린???⑦궎吏�(214)	//BOX_S4
	ITEM_NET_PACKAGE_LUCK,	//?됱슫 ?⑦궎吏�(215)	//BOX_S5
	ITEM_NET_EXPORB,	//EXP?띾뱷(180)	//-1

	TOTAL_NETITEM,

	//?ㅼ븘?댄뀥 : ITEM_KEY
	ITEM_KEY0 = 0,	//湲덈떒??怨꾧끝 ?댁뇿(146)
	ITEM_KEY1,	//?대몺???뚰렪 ?댁뇿(147)
	ITEM_KEY2,	//?몃Ⅸ鍮꾨뒛 ?댁뇿(148)
	ITEM_KEY3,	//李⑥썝???댁뇿(149)
	ITEM_KEY4,	//?쇱쓬???뺣졊 ?댁뇿(150)
	ITEM_KEY5,	//踰덇컻???뺣졊 ?댁뇿(151)
	ITEM_KEY6,	//鍮쏆쓽 ?뺣졊 ?댁뇿(152)
	ITEM_KEY7,	//吏�?섏닔濡??댁뇿(153)
	ITEM_KEY8,	//怨⑤젞 ?댁뇿(154)
	ITEM_KEY9,	//?대몺???댁뇿(155)
	ITEM_KEY10,	//?쒕옒怨ㅼ쓽 臾대뜡 ?댁뇿(156)
	ITEM_KEY11,	//留앹옄???꾩떆 ?댁뇿(157)
	ITEM_KEY12,	//留덉솗?깆쓽 ?댁뇿(158)
	ITEM_KEY13,	//?뺢????쒕뜕??15)
	ITEM_KEY14,	//洹쇱꽦???덈━??183)
	ITEM_KEY15,	//?좉린猷⑥쓽 紐⑷구??184)
	ITEM_KEY16,	//?ㅼ슦嫄곗쓽 ?κ컩(185)
	TOTAL_KEYITEM,

	TOTAL_KEY = ITEM_KEY12 + 1,

	//??: ITEM_STATUE
	ITEM_STATUE_WIND = 0,	//질풍????130)
	ITEM_STATUE_DESTRUCT,	//?뚭눼????131)
	ITEM_STATUE_POWER,		//?꾨젰????132)
	ITEM_STATUE_MERMAID,	//?몄뼱????133)
	ITEM_STATUE_FLAME,		//불꽃????134)
	ITEM_STATUE_PENGUIN,		//??톬????135)
	ITEM_STATUE_ICE,				//?쇱쓬????136)
	ITEM_STATUE_THUNDER,	//번개????137)
	ITEM_STATUE_SUN,			//?쒖뼇????138)
	ITEM_STATUE_RABBIT,		//?좊겮????139)
	ITEM_STATUE_GOLEM,		//골렘????140)
	ITEM_STATUE_DIMENSION,	//차원????141)
	ITEM_STATUE_EAGLE,		//?낆닔由ъ쓽 ??142)
	ITEM_STATUE_SQUIRREL,	//?ㅻ엺伊먯쓽 ??143)
	ITEM_STATUE_DRAGON,		//?쒕옒怨ㅼ쓽 ??144)
	ITEM_STATUE_SPIRIT,		//진공????145)
	TOTAL_STATUE,


	//ITEM_BOX
	BOX_INGAME = 0,//?λ퉬媛� ?ㅼ뼱?덈뒗 諛뺤뒪
	
	BOX_CASTLE0,
	BOX_CASTLE1,
	BOX_CASTLE2,
	BOX_CASTLE3,
	BOX_CASTLE4,
	BOX_CASTLE5,
	BOX_CASTLE6,
	BOX_CASTLE7,
	BOX_CASTLE8,
	BOX_CASTLE9,
	BOX_CASTLE10,
	BOX_CASTLE11,
	BOX_CASTLE12,
	BOX_CASTLE13,
	BOX_CASTLE14,
	BOX_CASTLE15,
	BOX_CASTLE16,
	BOX_CASTLE17,
	BOX_CASTLE18,

	BOX_REWARD0,
	BOX_REWARD1,
	BOX_REWARD2,
	BOX_REWARD3,
	BOX_REWARD4,
	BOX_REWARD5,
	BOX_REWARD6,
	BOX_REWARD7,
	BOX_PAID0,
	BOX_PAID1,
	BOX_PAID2,
	BOX_PAID3,
	BOX_PAID4,
	BOX_PAID5,

	TOTAL_BOX,

	BOXDROP_COIN = 0,
	BOXDROP_COINBAG,
	BOXDROP_QUESTITEM,
	BOXDROP_QUESTITEMBAG,
	BOXDROP_HEART,
	BOXDROP_EQUIP,
	BOXDROP_BATTLE,
	BOXDROP_RAID,
	BOXDROP_SHIELD,
	TOTAL_BOXDROP,

	BOXRULE1 = 0,
	BOXRULE2,
	BOXRULE3,
	BOXRULE4,
	BOXRULE5,
	BOXRULE6,
	BOXRULE7,
	BOXRULE8,
	BOXRULE9,
	BOXRULE10,

	TOTALBOXRULE,

	BOXSTATUS_APPEAR = 0,
	BOXSTATUS_CLOSED,
	BOXSTATUS_OPENING,
	BOXSTATUS_OPENED,
	BOXSTATUS_CLOSING,
	BOXSTATUS_EMPTY,
	BOXSTATUS_SHOWGOLD,

	TOTALBOXSTATUS,

	//?숇즺??: ITEM_CREW

	////?ш린??2 ?꾩슜 ?꾩씠???섏쨷???꾨━誘몄뾼?쇰줈 二쇰㈃ ?좊벏)
	////검 : ITEM_SWORD
	//ITEM_SWORD2_HRUNTING,	//?꾩?濡??щ쫫
	//ITEM_SWORD2_GRAM,	//?몄씠???щ쫫
	//ITEM_SWORD2_ASCALON,	//?�?댄깂 ?щ쫫
	//ITEM_SWORD2_STORMBRINGER,	//?고룿 ?щ쫫
	//TOTAL_SWORD2,

	////珥?: ITEM_GUN				
	//ITEM_GUN2_GAEBOLG,	//媛�?먮낫瑜닿렇
	//ITEM_GUN2_GUNGNIR,	//沅곷땲瑜?
	//ITEM_GUN2_LONGINUS,	//濡깃린?꾩뒪
	//ITEM_GUN2_TAHULLOOM,	//留덊깂 ?�?섎８
	//TOTAL_GUN2,

	////부메랑 : ITEM_BOOMERANG				
	//ITEM_BOOMERANG2_KALADBOLG,	//移쇰씪?쒕낵洹?
	//ITEM_BOOMERANG2_GAEBOLG,	//게이볼그
	//ITEM_BOOMERANG2_ANSWERER,	//?꾨씪媛�?쇳쓲
	//ITEM_BOOMERANG2_MJOLNIR,	//臾좊땲瑜?
	//TOTAL_BOOMERANG2,

	////?щĸ : ITEM_HELM				
	//ITEM_HELM2_ACHERON,	//?꾩?濡??щ쫫
	//ITEM_HELM2_SEIREN,	//?몄씠???щ쫫
	//ITEM_HELM2_TITAN,	//?�?댄깂 ?щ쫫
	//ITEM_HELM2_TYPHON,	//?고룿 ?щ쫫
	//TOTAL_HELM2,

	////모자 : ITEM_HAT				
	//ITEM_HAT2_NEMESIS,	//?ㅻ찓?쒖뒪 ??
	//ITEM_HAT2_PSYCHE,	//?꾩떆耳� ??
	//ITEM_HAT2_ATALANTA,	//?꾪깉?�?� ??
	//ITEM_HAT2_LETHE,	//?덊뀒 ?щ씪??
	//TOTAL_HAT2,

	////?먭굔 : ITEM_CAP				
	//ITEM_CAP2_PHLEGETHON,	//?뚮젅耳�??罹?
	//ITEM_CAP2_THANATUS,	//?�?섑넗??罹?
	//ITEM_CAP2_MIDAS,	//誘몃떎??罹?
	//ITEM_CAP2_EREBOS,	//?먮젅蹂댁뒪 罹?
	//TOTAL_CAP2,

	////갑옷 : ITEM_ARMOR				
	//ITEM_ARMOR2_ACHERON,	//?꾩?濡??꾨㉧
	//ITEM_ARMOR2_SEIREN,	//?몄씠???꾨㉧
	//ITEM_ARMOR2_TITAN,	//?�?댄깂 ?꾨㉧
	//ITEM_ARMOR2_TYPHON,	//?고룿 ?꾨㉧
	//TOTAL_ARMOR2,
	//		
	////조끼 : ITEM_VEST				
	//ITEM_VEST2_NEMESIS,	//?ㅻ찓?쒖뒪 濡쒕툕
	//ITEM_VEST2_PSYCHE,	//?꾩떆耳� 濡쒕툕
	//ITEM_VEST2_ATALANTA,	//?꾪깉?�?� 濡쒕툕
	//ITEM_VEST2_LETHE,	//?덊뀒 濡쒕툕
	//TOTAL_VEST2,
	//		
	////코트 : ITEM_COAT				
	//ITEM_COAT2_PHLEGETHON,	//?뚮젅耳�??肄뷀듃
	//ITEM_COAT2_THANATUS,	//?�?섑넗??肄뷀듃
	//ITEM_COAT2_MIDAS,	//미다??코트
	//ITEM_COAT2_EREBOS,	//?먮젅蹂댁뒪 肄뷀듃
	//TOTAL_COAT2,

	////嫄댄???: ITEM_GUNTLET				
	//ITEM_GUNTLET2_ACHERON,	//?꾩?濡?嫄댄???
	//ITEM_GUNTLET2_SEIREN,	//?몄씠??嫄댄???
	//ITEM_GUNTLET2_TITAN,	//?�?댄깂 嫄댄???
	//ITEM_GUNTLET2_TYPHON,	//?고룿 嫄댄???
	//TOTAL_GUNTLET2,

	////?붿컡 : ITEM_ARMLET				
	//ITEM_ARMLET2_NEMESIS,	//?ㅻ찓?쒖뒪 ?붾젢
	//ITEM_ARMLET2_PSYCHE,	//?꾩떆耳� ?붾젢
	//ITEM_ARMLET2_ATALANTA,	//?꾪깉?�?� ?붾젢
	//ITEM_ARMLET2_LETHE,	//?덊듃 ?붾젢
	//TOTAL_ARMLET2,

	////?κ컩 : ITEM_GLOVE				
	//ITEM_GLOVE2_PHLEGETHON,	//?뚮젅耳�???몃뱶
	//ITEM_GLOVE2_THANATUS,	//?�?섑넗???몃뱶
	//ITEM_GLOVE2_MIDAS,	//誘몃떎??湲�?щ툕
	//ITEM_GLOVE2_EREBOS,	//?먮젅蹂댁뒪 ?몃뱶
	//TOTAL_GLOVE2,

	////?ы듃 : ITEM_KILT				
	//ITEM_KILT2_ACHERON,	//?꾩?濡??ы듃
	//ITEM_KILT2_SEIREN,	//?몄씠???ы듃
	//ITEM_KILT2_TITAN,	//?�?댄깂 ?ы듃
	//ITEM_KILT2_TYPHON,	//?고룿 ?ы듃
	//TOTAL_KILT2,

	////諛붿? : ITEM_SKIRT				
	//ITEM_SKIRT2_NEMESIS,	//?ㅻ찓?쒖뒪 移섎쭏
	//ITEM_SKIRT2_PSYCHE,	//?꾩떆耳� ?ㅼ빱??
	//ITEM_SKIRT2_ATALANTA,	//?꾪깉?�?� 移섎쭏
	//ITEM_SKIRT2_LETHE,	//?덊뀒 ?ㅼ빱??
	//TOTAL_SKIRT2,

	////諛붿? : ITEM_PANTS				
	//ITEM_PANTS2_PHLEGETHON,	//?뚮젅耳�???ъ툩
	//ITEM_PANTS2_THANATUS,	//?�?섑넗???ъ툩
	//ITEM_PANTS2_MIDAS,	//誘몃떎???ъ툩
	//ITEM_PANTS2_EREBOS,	//?먮젅蹂댁뒪 ?ъ툩
	//TOTAL_PANTS2,

	////?ν솕 : ITEM_GREAVES				
	//ITEM_GREAVES_ACHERON,	//?꾩?濡?洹몃━釉?
	//ITEM_GREAVES_SEIREN,	//?몄씠??洹몃━釉?
	//ITEM_GREAVES_TITAN,	//?�?댄깂 洹몃━釉?
	//ITEM_GREAVES_TYPHON,	//?고룿 洹몃━釉?
	//TOTAL_GREAVES2,

	////?좊컻 : ITEM_SHOES				
	//ITEM_SHOES_NEMESIS,	//?ㅻ찓?쒖뒪 ?덉쫰
	//ITEM_SHOES_PSYCHE,	//?꾩떆耳� ?덉쫰
	//ITEM_SHOES_ATALANTA,	//?꾪깉?�?� ?덉쫰
	//ITEM_SHOES_LETHE,	//?덊뀒 ?덉쫰
	//TOTAL_SHOES2,

	////遺�痢?: ITEM_BOOTS				
	//ITEM_BOOTS_PHLEGETHON,	//?뚮젅耳�??遺�痢?
	//ITEM_BOOTS_THANATUS,	//?�?섑넗??遺�痢?
	//ITEM_BOOTS_MIDAS,	//誘몃뱶??遺�痢?
	//ITEM_BOOTS_EREBOS,	//?먮젅蹂댁뒪 遺�痢?
	//TOTAL_BOOTS2,

	////목걸??: ITEM_NECK				
	//ITEM_NECK28,	//?ㅻ퉬?쒖뒪 ?먮（
	//ITEM_NECK29,	//?몄씠?뚯쓽 ?쇰━
	//ITEM_NECK30,	//?⑺샎???깅같
	//ITEM_NECK31,	//?ъ븰??嫄곗슱
	//ITEM_NECK32,	//濡쒖젮由곗쓽 苑?
	//ITEM_NECK33,	//?곸썒???쒖궗??
	//ITEM_NECK34,	//?좊땲肄섏쓽 肉?
	//ITEM_NECK35,	//?⑷툑 議곌컻
	//ITEM_NECK36,	//泥쒖궗???좉컻
	//ITEM_NECK37,	//금단??과실
	//ITEM_NECK38,	//二쎌쓬???ш?誘?
	//ITEM_NECK39,	//議곌컖???곹샎
	//TOTAL_NECK2,

	////목걸??: ITEM_RING				
	//ITEM_RING18,	//?덈꺼猷쎄쾺 諛섏?
	//ITEM_RING19,	//?⑹젣??諛섏?
	//ITEM_RING20,	//?�?섏닔 諛섏?
	//ITEM_RING21,	//異⑹꽦??諛섏?
	//ITEM_RING22,	//?덈? 諛섏?
	//ITEM_RING23,	//?⑷툑 諛섏?
	//ITEM_RING24,	//?붿젙??諛섏?
	//ITEM_RING25,	//?〓쭏 諛섏?
	//ITEM_RING26,	//踰덈뇤??諛섏?
	//ITEM_RING27,	//遺덉궗??諛섏?
	//ITEM_RING28,	//?쎌냽??諛섏?
	//ITEM_RING29,	//遊됱씤??諛섏?
	//TOTAL_RING2,	//?ш린??2 ?꾩씠??end

	TOTALEQUIPINDEX = TOTAL_SWORD + TOTAL_GUN + TOTAL_BOOMERANG + TOTAL_HELM + TOTAL_HAT + TOTAL_CAP + TOTAL_ARMOR + TOTAL_VEST + TOTAL_COAT + TOTAL_GUNTLET + TOTAL_ARMLET + TOTAL_GLOVE + TOTAL_KILT + TOTAL_SKIRT + TOTAL_PANTS + TOTAL_GREAVES + TOTAL_SHOES + TOTAL_BOOTS + TOTAL_NECK + TOTAL_RING,
	EQUIPINDEXHEIGHT = 48 * _2X,

	ITEM_SWORD_START = 0,
	ITEM_GUN_START = ITEM_SWORD_START + TOTAL_SWORD,
	ITEM_BOOMERANG_START = ITEM_GUN_START + TOTAL_GUN,
	ITEM_HELM_START = ITEM_BOOMERANG_START + TOTAL_BOOMERANG,
	ITEM_HAT_START = ITEM_HELM_START + TOTAL_HELM,
	ITEM_CAP_START = ITEM_HAT_START + TOTAL_HAT,
	ITEM_ARMOR_START = ITEM_CAP_START + TOTAL_CAP,
	ITEM_VEST_START = ITEM_ARMOR_START + TOTAL_ARMOR,
	ITEM_COAT_START = ITEM_VEST_START + TOTAL_VEST,
	ITEM_GUNTLET_START = ITEM_COAT_START + TOTAL_COAT,
	ITEM_ARMLET_START = ITEM_GUNTLET_START + TOTAL_GUNTLET,
	ITEM_GLOVE_START = ITEM_ARMLET_START + TOTAL_ARMLET,
	ITEM_KILT_START = ITEM_GLOVE_START + TOTAL_GLOVE,
	ITEM_SKIRT_START = ITEM_KILT_START + TOTAL_KILT,
	ITEM_PANTS_START = ITEM_SKIRT_START + TOTAL_SKIRT,
	ITEM_GREAVES_START = ITEM_PANTS_START + TOTAL_PANTS,
	ITEM_SHOES_START = ITEM_GREAVES_START + TOTAL_GREAVES,
	ITEM_BOOTS_START = ITEM_SHOES_START + TOTAL_SHOES,
	ITEM_NECK_START = ITEM_BOOTS_START + TOTAL_BOOTS,
	ITEM_RING_START = ITEM_NECK_START + TOTAL_NECK,
	ITEM_GEM_START = ITEM_RING_START + TOTAL_RING,
	ITEM_WASTES_START = ITEM_GEM_START + TOTAL_GEM,
	ITEM_IRON_START = ITEM_WASTES_START + TOTAL_WASTE,
	ITEM_LEATHER_START = ITEM_IRON_START + TOTAL_IRON,
	ITEM_CLOTH_START = ITEM_LEATHER_START + TOTAL_LEATHER,
	ITEM_WOOD_START = ITEM_CLOTH_START + TOTAL_CLOTH,
	ITEM_ESSENCE_START = ITEM_WOOD_START + TOTAL_WOOD,
	ITEM_RECIPE_START = ITEM_ESSENCE_START + TOTAL_ESSENCE,
	ITEM_QUEST_START = ITEM_RECIPE_START + 1,
	ITEM_NETITEM_START = ITEM_QUEST_START + TOTAL_QUESTITEM,
	ITEM_GOLD_START = ITEM_NETITEM_START + TOTAL_NETITEM,
	ITEM_KEY_START = ITEM_GOLD_START + 1,
	ITEM_STATUE_START = ITEM_KEY_START + TOTAL_KEYITEM,
	ITEM_HEART_START = ITEM_STATUE_START + TOTAL_STATUE,
	ITEM_MEDAL_START = ITEM_HEART_START + 1,
	ITEM_STAR_START = ITEM_MEDAL_START + 1,
	ITEM_HAMMER_START = ITEM_STAR_START + 1,
	ITEM_SHIELD_START = ITEM_HAMMER_START + 1,
	ITEM_BOX_START = ITEM_SHIELD_START + 1,
	ITEM_CREW_START = ITEM_BOX_START + TOTAL_BOX,
	ITEM_SKILL_START = ITEM_CREW_START + CAP_CREW,


	ITEM_SWORD_NAMESTART = 0,
	ITEM_GUN_NAMESTART = ITEM_SWORD_NAMESTART + TOTAL_SWORD,
	ITEM_BOOMERANG_NAMESTART = ITEM_GUN_NAMESTART + TOTAL_GUN,
	ITEM_HELM_NAMESTART = ITEM_BOOMERANG_NAMESTART + TOTAL_BOOMERANG,
	ITEM_HAT_NAMESTART = ITEM_HELM_NAMESTART + TOTAL_HELM,
	ITEM_CAP_NAMESTART = ITEM_HAT_NAMESTART + TOTAL_HAT,
	ITEM_ARMOR_NAMESTART = ITEM_CAP_NAMESTART + TOTAL_CAP,
	ITEM_VEST_NAMESTART = ITEM_ARMOR_NAMESTART + TOTAL_ARMOR,
	ITEM_COAT_NAMESTART = ITEM_VEST_NAMESTART + TOTAL_VEST,
	ITEM_GUNTLET_NAMESTART = ITEM_COAT_NAMESTART + TOTAL_COAT,
	ITEM_ARMLET_NAMESTART = ITEM_GUNTLET_NAMESTART + TOTAL_GLOVE,
	ITEM_GLOVE_NAMESTART = ITEM_ARMLET_NAMESTART + TOTAL_GUNTLET,
	ITEM_KILT_NAMESTART = ITEM_GLOVE_NAMESTART + TOTAL_ARMLET,
	ITEM_PANTS_NAMESTART = ITEM_KILT_NAMESTART + TOTAL_KILT,
	ITEM_SKIRT_NAMESTART = ITEM_PANTS_NAMESTART + TOTAL_PANTS,
	ITEM_GREAVES_NAMESTART = ITEM_SKIRT_NAMESTART + TOTAL_SKIRT,
	ITEM_BOOTS_NAMESTART = ITEM_GREAVES_NAMESTART + TOTAL_GREAVES,
	ITEM_SHOES_NAMESTART = ITEM_BOOTS_NAMESTART + TOTAL_BOOTS,
	ITEM_NECK_NAMESTART = ITEM_SHOES_NAMESTART + TOTAL_SHOES,
	ITEM_RING_NAMESTART = ITEM_NECK_NAMESTART + TOTAL_NECK,
	ITEM_GEM_NAMESTART = ITEM_RING_NAMESTART + TOTAL_RING,
	ITEM_WASTES_NAMESTART = ITEM_GEM_NAMESTART + TOTAL_GEM,
	ITEM_IRON_NAMESTART = ITEM_WASTES_NAMESTART + TOTAL_WASTE,
	ITEM_LEATHER_NAMESTART = ITEM_IRON_NAMESTART + TOTAL_IRON,
	ITEM_CLOTH_NAMESTART = ITEM_LEATHER_NAMESTART + TOTAL_LEATHER,
	ITEM_WOOD_NAMESTART = ITEM_CLOTH_NAMESTART + TOTAL_CLOTH,
	ITEM_ESSENCE_NAMESTART = ITEM_WOOD_NAMESTART + TOTAL_WOOD,
	ITEM_RECIPE_NAMESTART = ITEM_ESSENCE_NAMESTART + TOTAL_ESSENCE,
	ITEM_QUEST_NAMESTART = ITEM_RECIPE_NAMESTART + 1,
	ITEM_NETITEM_NAMESTART = ITEM_QUEST_NAMESTART + TOTAL_QUESTITEM,
	ITEM_GOLD_NAMESTART = ITEM_NETITEM_NAMESTART + TOTAL_NETITEM,
	ITEM_KEY_NAMESTART = ITEM_GOLD_NAMESTART + 1,
	ITEM_STATUE_NAMESTART = ITEM_KEY_NAMESTART + TOTAL_KEYITEM,
	ITEM_HEART_NAMESTART = ITEM_STATUE_NAMESTART + TOTAL_STATUE,
	ITEM_MEDAL_NAMESTART = ITEM_HEART_NAMESTART + 1,
	ITEM_STAR_NAMESTART = ITEM_MEDAL_NAMESTART + 1,
	ITEM_HAMMER_NAMESTART = ITEM_STAR_NAMESTART + 1,
	ITEM_SHIELD_NAMESTART = ITEM_HAMMER_NAMESTART + 1,
	ITEM_BOX_NAMESTART = ITEM_SHIELD_NAMESTART + 1,

	NETINVENSTART = 48,
	MAXNETINVEN = 52,
	MAXNETSHOP = 48,


	MAXSINGLESHOP = 13,

	SINGLESHOP_SINDEX = 0,	//0
	SINGLESHOP_SICON,	//1
	SINGLESHOP_STYPE,	//2
	SINGLESHOP_SDETAIL,	//3
	SINGLESHOP_SBROKEN,	//4
	SINGLESHOP_SCOUNT,	//5
	SINGLESHOP_SVALUE,	//6
	SINGLESHOPDATALENGTH,	//7

	MAXSOCKET = 6,

	TOTALGEMOPTION = 27,
	TOTALITEMDETAIL = 8,

	//?명듃 ?꾩씠??醫낅쪟
	SET_BEGINNER = 0,	//0 견습 기사
	SET_KINGDOM,			//1 ?뺢????섑샇??
	SET_SPACE,				//2 ?쒓났??洹좎뿴
	SET_HAWK,				//3 ?몃Ⅸ留ㅼ쓽 ??
	SET_MAGICGUN,			//4 마도총술??
	SET_SUN,					//5 ?쒖뼇???꾪쓷
	SET_WANTED,			//6 ?꾩긽湲??щ깷袁?
	SET_SOUL,					//7 ?뚯슱 ?뚰꽣
	SET_MOBIUS,				//8 維쇰퉬?곗뒪????
	SET_TRAINING,			//9 臾댁궗?섑뻾
	SET_GUNMAN,			//10 ?좊룎??珥앹옟??
	SET_ROOTLESS,			//11 ?щ깷袁?
	SET_CHALLENGER,		//12 ?꾩쟾??
	SET_HUNTER,				//13 ?뚰꽣
	SET_MERCENARY,		//14 ?⑸퀝
	SET_JUDEGMENT,		//15 ?ы뙋????
	SET_CARAVAN,			//16 罹먮윭諛??곸씤
	SET_MAPLE,				//17 ?⑦뭾?쇱깋
	SET_LOST,					//18 ?딇?吏??곸썒
	SET_DREAM,				//19 몽환??감시??
	SET_GENTLE,				//20 ?덉쓽踰붿젅
	SET_BRONZE,				//21 釉뚮줎利??섏씠??
	SET_POET,				//22 ?뚯쑀?쒖씤
	SET_GUARDIAN,			//23 遺덈㈇???섑샇??
	SET_IMMOTAL,			//24 무한??마력
	SET_MONARCH,			//25 ?대갑??援곗＜
	SET_CHASER,				//26 ?щ㈇??異붿쟻??
	SET_SMITH,				//27 ?멸났?ъ쓽 ?좏뭹
	SET_THIEF,				//28 ?꾨????꾩쟻
	SET_PICNIC,				//29 ?쇳겕??
	SET_GRAND,				//30 ?꾨????좎궛
	SET_BULL,					//31 ?뷀샊???ъ슦??
	SET_DEVIL,				//32 ?ъ떊???�二?
	SET_ROYAL,				//33 ?뺤떎 湲곗궗
	SET_OUTLAW,			//34 ?⑹빞??臾대쾿??
	SET_SKULL,				//35 ?먰븳???닿낏湲곗궗
	SET_TREASURE,			//36 보물??
	SET_HELL,					//37 吏�?μ쓽 臾듭떆濡?
	SET_LOCUST,				//38 ?ъ븙???쏀깉??
	SET_VAGABOND,		//39 踰좉?蹂몃뱶
	SET_ELEMENTAL,		//40 ?뺣졊??媛�??
	SET_ELITE,				//41 ?뺤삁 ?ㅻ굹?댄띁
	SET_CHAOS,				//42 ?쇰룉???쒕떒
	SET_COSTUME,			//43 媛�?λТ?꾪쉶
	SET_WING,				//44 泥쒓났???좉컻
	SET_NOBLE,				//45 ?쒖뼇??洹�議?
	SET_SMILE,				//46 ?ㅻ쭏???쇱씠??
	SET_VICTORY,			//47 ?뱀옄???곴킅
	SET_STRANGER,			//48 ?닿뎅??紐⑦뿕媛�
	SET_GUILLOTINE,		//49 길로??
	SET_ANCIENT,			//50 怨좊????좊Ъ
	SET_ARTHUR,				//51 ?먰긽??湲곗궗
	SET_DRAGON,			//52 ?쒕옒怨ㅼ쓽 臾대뜡
	SET_DEADMAN,			//53 ?좎쓽 ?ъ옄

	//?숆뎬 ?명듃 ?�??
	SET_RA1,	//濡쒕퉰 ?숆뎬1硫붿씤//湲곗궗???쒖빟//54
	SET_RA2,	//濡쒕퉰 ?숆뎬1蹂댁“//諛붾）??諛⑺뙣//55
	SET_RB1,	//濡쒕퉰 ?숆뎬2硫붿씤//二쎌쓬??洹몃┝??/56
	SET_RB2,	//濡쒕퉰 ?숆뎬2蹂댁“//珥앸챸???섎Т//57
	SET_RC1,	//濡쒕퉰 ?숆뎬3硫붿씤//?섎뒛???ы뙋//58
	SET_RC2,	//濡쒕퉰 ?숆뎬3蹂댁“//?꾨옒?ㅼ쓽 ?섏?//59
	SET_RD1,	//濡쒕퉰 ?숆뎬4硫붿씤//?낅쭏???좏샊//60
	SET_RD2,	//濡쒕퉰 ?숆뎬4蹂댁“//紐곕젆???쒕떒//61

	SET_DA1,	//?붿븘???숆뎬1硫붿씤//?꾩옣???섑뙏//62
	SET_DA2,	//?붿븘???숆뎬1蹂댁“//?ъ떊???좊컻//63
	SET_DB1,	//?붿븘???숆뎬2硫붿씤//留앷컖???덈Ъ//64
	SET_DB2,	//?붿븘???숆뎬2蹂댁“//吏�?쒖쓽 ?섎Ъ//65
	SET_DC1,	//?붿븘???숆뎬3硫붿씤//?좊뱾???⑺샎//66
	SET_DC2,	//?붿븘???숆뎬3蹂댁“//?꾪뀒?ㅼ쓽 異뺣났//67
	SET_DD1,	//?붿븘???숆뎬4硫붿씤//留덈????낆닠//68
	SET_DD2,	//?붿븘???숆뎬4蹂댁“//?덊뙋??蹂?/69

	SET_MA1,	//留μ뒪 ?숆뎬1硫붿씤//?꾩궗???몃옒//70
	SET_MA2,	//留μ뒪 ?숆뎬1蹂댁“//留덈뱶猷⑹쓽 媛묒샆//71
	SET_MB1,	//留μ뒪 ?숆뎬2硫붿씤//?щ컮??媛먯떆??/72
	SET_MB2,	//留μ뒪 ?숆뎬2蹂댁“//紐낆쿋??諛붿쐞//73
	SET_MC1,	//留μ뒪 ?숆뎬3硫붿씤//?곸썒??遺꾨끂//74
	SET_MC2,	//留μ뒪 ?숆뎬3蹂댁“//?뚮━?ㅼ쓽 ?꾩쓽//75
	SET_MD1,	//留μ뒪 ?숆뎬4硫붿씤//吏�?μ쓽 硫붿븘由?/76
	SET_MD2,	//留μ뒪 ?숆뎬4蹂댁“//諛붿븣???쒕Ъ//77

	TOTALSET,

	TOTALPREFIXTEXT = 30,
	TOTALSUFFIXTEXT = 31,
	TOTALSUFFIXOPTION = 46,

	//?묐몢???듭뀡
	PREFIX_WEAPON_DMG = 0,	//怨듦꺽??利앷?
	PREFIX_SWORD_DMG,			//寃� 怨듦꺽??利앷?
	PREFIX_GUN_DMG,				//珥?怨듦꺽??利앷?
	PREFIX_BOOMERANG_DMG,	//遺�硫붾옉 怨듦꺽??利앷?
	PREFIX_CRITICAL,				//移섎챸?�??利앷?
	PREFIX_PIERCE,					//愿�?듬젰 利앷?
	PREFIX_EXTRA,					//異붽??�寃??뺣쪧 利앷?
	PREFIX_STR,						//???ㅽ꺈 利앷?
	PREFIX_AGI,						//誘??ㅽ꺈 利앷?
	PREFIX_VIT,						//泥??ㅽ꺈 利앷?
	PREFIX_INT,						//吏� ?ㅽ꺈 利앷?
	PREFIX_SKILLDMG,				//?ㅽ궗怨듦꺽??利앷?
	PREFIX_DEFENSE,				//??방어??감소
	PREFIX_ARMOR,					//諛⑹뼱??利앷?
	PREFIX_ABSORB,					//臾쇰━?쇳빐 媛먯냼
	PREFIX_FIRE_REGIST,			//?붿뿼?�??젰 利앷?
	PREFIX_FROST_REGIST,		//?됯린?�??젰 利앷?
	PREFIX_THUNDER_REGIST,	//踰덇컻?�??젰 利앷?
	PREFIX_HOLY_REGIST,		//?좎꽦?�??젰 利앷?
	PREFIX_DARK_REGIST,			//?뷀쓳?�??젰 利앷?
	PREFIX_LUCK,						//?됱슫 利앷?
	PREFIX_GOLD,					//怨⑤뱶 ?띾뱷
	PREFIX_EXP,						//寃쏀뿕移??띾뱷
	PREFIX_HPRESTORE,			//HP10珥덈떦 X?뚮났
	PREFIX_MPRESTORE,			//MP10珥덈떦 X?뚮났
	PREFIX_POTION,					//臾쇱빟瑜??④낵 X利앷?
	PREFIX_BUFF,						//踰꾪봽吏�?띿떆媛?利앷?
	PREFIX_MAGIC_REGIST,			//留덈쾿怨듦꺽?뚰뵾??
	PREFIX_RESERVED2,
	PREFIX_RESERVED3,

	//?묐????듭뀡
	SUFFIX_WEAPON_DMG,	//臾쇰━怨듦꺽??異붽?
	SUFFIX_SWORD_DMG,		//寃� 異붽?
	SUFFIX_GUN_DMG,			//珥?異붽?
	SUFFIX_BOOMERANG_DMG,	//遺�硫붾옉 異붽?
	SUFFIX_FIRE_ATTACK,		//?붿뿼?띿꽦 怨듦꺽 ?뺣쪧
	SUFFIX_FROST_ATTACK,	//?됯린?띿꽦 怨듦꺽 ?뺣쪧
	SUFFIX_THUNDER_ATTACK,	//踰덇컻?띿꽦 怨듦꺽 ?뺣쪧
	SUFFIX_HOLY_ATTACK,	//?좎꽦?띿꽦 怨듦꺽 ?뺣쪧
	SUFFIX_DARK_ATTACK,	//?뷀쓳?띿꽦 怨듦꺽 ?뺣쪧
	SUFFIX_HIT,					//?곸쨷瑜?利앷?
	SUFFIX_IGNORE,				//諛⑹뼱??臾댁떆 怨듦꺽?뺣쪧 利앷?
	SUFFIX_DELAY,				//?ㅽ궗 ?ъ궗???�湲곗떆媛?媛먯냼
	SUFFIX_CRITICAL,			//移섎챸?� ?쇳빐 利앷?
	SUFFIX_EVASION,			//?뚰뵾??利앷?
	SUFFIX_STAT,				//紐⑤뱺 ?ㅽ꺈 利앷?
	SUFFIX_HP,					//?앸챸??利앷?
	SUFFIX_MP,					//留덈굹 利앷?
	SUFFIX_HPDRAIN,			//泥대젰?≪닔
	SUFFIX_MPDRAIN,			//留덈굹?≪닔
	SUFFIX_ALLREGIST,			//紐⑤뱺 ?�??젰 利앷?
	SUFFIX_ARMOR,				//諛⑹뼱??異붽?
	SUFFIX_LUCK,					//?됱슫 利앷?
	SUFFIX_GOLD,				//泥섏튂??怨⑤뱶 ??利앷?
	SUFFIX_EXP,					//寃쏀뿖移??띾뱷??利앷?
	SUFFIX_REQUIRE,			//?붽뎄移?媛먯냼
	SUFFIX_DEBUF,				//?곹깭?댁긽 吏�?띿떆媛?媛먯냼
	SUFFIX_STUN,				//湲곗젅怨듦꺽 ?뺣쪧
	SUFFIX_SKILL,					//?ㅽ궗?덈꺼 利앷?
	SUFFIX_RESERVED1,
	SUFFIX_RESERVED2,
	SUFFIX_RESERVED3,

	SUFFIX_ENEMYREGEN,
	SUFFIX_POISON_IMMUNE,	//異붽??듭뀡13: ?낅Т??
	SUFFIX_BLIND_IMMUNE,		//異붽??듭뀡16: 釉붾씪?몃뱶臾댄슚
	SUFFIX_SLOW_IMMUNE,		//異붽??듭뀡15: ?щ줈?곕Т??
	SUFFIX_CURSE_IMMUNE,		//異붽??듭뀡17: ?�二쇰Т??
	SUFFIX_STUN_IMMUNE,		//異붽??듭뀡14: 湲곗젅臾댄슚
	SUFFIX_ALWAYSCURSE,		//異붽??듭뀡17: 李⑹슜???�二?
	SUFFIX_HPDECREASE,			//異붽??듭뀡1: HP 10珥덈떦 X媛먯냼
	SUFFIX_MINUSARMOR,			//異붽??듭뀡2: 諛⑹뼱?κ컧??
	SUFFIX_MINUSDRAIN,			//異붽??듭뀡3: 怨듦꺽???곸뿉寃?以� ?곕?吏�??X%留뚰겮 HP媛먯냼
	SUFFIX_MINUSHP,				//異붽??듭뀡4: HP媛먯냼
	SUFFIX_MINUSMP,				//異붽??듭뀡5: MP媛먯냼
	SUFFIX_MINUSEVASION,		//異붽??듭뀡7: ?뚰뵾媛먯냼
	SUFFIX_MINUSHIT,				//異붽??듭뀡9: ?곸쨷媛먯냼
	SUFFIX_MINUSREGIST,			//異붽??듭뀡10: ?�??媛먯냼
	SUFFIX_MINUSINT,				//異붽??듭뀡11: INT媛먯냼
	SUFFIX_MINUSSTR,				//異붽??듭뀡12: STR媛먯냼
	SUFFIX_MINUSAGI,				//異붽??듭뀡13: AGI媛먯냼
	SUFFIX_PLUSDEBUF,			//異붽??듭뀡14: ?붾쾭??吏�?띿떆媛꾩쬆媛�
	SUFFIX_MINUSSKILL,			//異붽??듭뀡15: 紐⑤뱺 ?ㅽ궗?덈꺼 媛먯냼
	SUFFIX_MINUSSKILLDMG,		//異붽??듭뀡16: ?ㅽ궗 怨듦꺽??媛먯냼

	TOTALITEMOPTION,

	//蹂댁꽍 ?듭뀡
	GEM_STR = 0,			//??, 3, 5, 8
	GEM_AGI,					//誘?, 3, 5, 8
	GEM_VIT,					//泥?, 3, 5, 8
	GEM_INT,					//지2, 3, 5, 8
	GEM_STAT,				//紐⑤뱺 ?λ젰移?1, 2, 3
	GEM_FIRE_REG,			//?붿뿼?�??젰 3, 5
	GEM_FROST_REG,		//?됯린?�??젰 3, 5
	GEM_THUNDER_REG,	//?먯뿰?�??젰 3, 5
	GEM_HOLY_REG,			//?좎꽦?�??젰 3, 5
	GEM_DARK_REG,			//?뷀쓳?�??젰 3, 5
	GEM_REG,					//紐⑤뱺?�??젰 1, 2, 3
	GEM_CRITICAL,			//치명 1, 2%
	GEM_EVASION,			//?뚰뵾 1, 2%
	GEM_HIT,					//?곸쨷 1, 2%
	GEM_PIERCE,				//관??1, 2%
	GEM_STUN,				//기절공격 1, 2%
	GEM_EXTRA,				//異붽??� 1, 2%
	GEM_IGNORE,				//諛⑹뼱?꾨Т??1, 2%
	GEM_HPDRAIN,			//泥대젰?≪닔 1, 2%
	GEM_MPDRAIN,			//留덈굹?≪닔 1, 2%
	GEM_LUCK,					//?됱슫利앷? 5, 10%
	GEM_CRITICAL_DMG,	//移섎챸?� ?쇳빐利앷?3, 5%
	GEM_GOLD,				//골드??5, 10%
	GEM_EXP,					//경험치삥 5, 10%
	GEM_REQUIRE,			//?붽뎄移섍컧??5, 10%
	GEM_WEAPON_DMG,	//공격??1, 2%
	GEM_ADD_DMG,			//怨듦꺽?μ텛媛� 3, 5


	//?곸젏 愿�??
	SHOPTYPE_CRAFT = 0,//?λ퉬媛뺥솕
	SHOPTYPE_QUICK,//?좊즺?꾩씠??


	CRAFT_ENCHANT = 0,//강화
	CRAFT_RECIPE,//?쒖옉
	CRAFT_SOCKET,//?뚯폆?μ갑

	SHOPCOUNT_QUICK = 27,

	TOTALINVENTORY = 500,//諛깆뾽?⑹쑝濡??쒓컻

	STARTINVENTORY = TOTALINVENTORY,//120,//@@

	//1. 초보검??컬렉??
	//2. 카우보이 컬렉??
	//3. ?ы뻾??而щ젆??
	//4. 踰좎씠鍮?而щ젆??
	//5. 洹�議?而щ젆??

	//6. 금속 컬렉??
	//7. 방랑??컬렉??
	//8. 방한 컬렉??
	//9. ?뚮젅?댄듃 而щ젆??
	//10. ?꾩쟻 而щ젆??

	//11.?щ깷袁?而щ젆??
	//12.寃�?ъ궗 而щ젆??
	//13.벨벳 컬렉??
	//14.?ъ슦??而щ젆??
	//15.?ㅽ뙆?댄겕 而щ젆??

	//16.?ㅻ굹?댄띁 而щ젆??
	//17.?댁쟻 而щ젆??
	//18.그랜??컬렉??
	//19.?쇰? 而щ젆??
	//20.?먯씠??而щ젆??

	//21.怨좊? 而щ젆??
	//22.?꾨━?ㅽ듃 而щ젆??
	//23.?쒕옒怨?而щ젆??
	//24.?⑹옄 而щ젆??

	//25. 보석 컬렉??
	//26. ?띿꽦 而щ젆??
	//27. 물약 컬렉??
	//28. ??컬렉??
	//29. 媛�二?而щ젆??
	//30. 泥?而щ젆??
	//31. ?섎Т 而щ젆??
	//32. ?먯꽱??而щ젆??
	//33. ?섏뒪???꾩씠??而щ젆??
	//34. 문서컬렉??
	//35. ?뚯슱 而щ젆??
	//36. ?댁뇿 而щ젆??珥?17媛?
	//37. ??而щ젆??珥?16媛?
	//38. ?룹븘?댄뀥


	TOTAL_COLLECTIONS = 24,
	COLLECTIONSITEMCNT = 6,
	COLLECTIONSDATASIZE = 5,

	COLLECTIONMENU_EQUIP = 0,
	TOTAL_COLLECTIONMENU,

} ITEMDEF;

#endif
