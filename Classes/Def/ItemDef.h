#pragma once

#ifndef _DEF_ITEM_H_
#define _DEF_ITEM_H_

typedef enum _itemDef {
	EQUIP_WEAPON = 0,	//무기 //?�전, ?�전주머?? ?�트, ?�스???�이?? PVP ?�이?�의 ?�득?�을 ?�용?�트?�도 ?�다.
	EQUIP_HELM,				//?�구 //?�션카드 ?�킬?�서 ?�득?�는 ?�전??%�?증�??�켜준??(?�수??
	EQUIP_ARMOR,			//갑옷 //??몬스?�시 뺏기???�전??%�?감소?�켜준??(?�수??
	EQUIP_GLOVE,			//?�갑 //?�션카드 ?�전, ?�전주머?�에???�전??%�?증�??�켜준??(?�수??
	EQUIP_PANTS,			//바�? //?�션카드 ?�트?�서 ?�득?�는 ?�전??%�?증�??�켜준??(?�수??
	EQUIP_BOOTS,			//?�발 //?�이?�공격시 ?�득?�는 ?�전??%�?증�??�켜준??(?�수??
	EQUIP_NECK,			//목걸??
	EQUIP_RING,		//반�?
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

	BOX_RANDOM = 0,//모든 종류???�이?�이 ???�오??BOX
	BOX_EQUIP,//?�페???�비�??�오??
	BOX_CREW,//캐릭?��? ?�오??
	BOX_SKILL,//?�킬???�오??

	//검 : ITEM_SWORD
	ITEM_SWORD_STICK = 0,//1//?�습??몽둥??
	ITEM_SWORD_LONG,//2//롱소??
	ITEM_SWORD_CUTTER,//3//처형?�의 검
	ITEM_SWORD_RUIN,//4//?�멸??참마??
	ITEM_SWORD_SEEKER,//5//추적?�의 검
	ITEM_SWORD_DOUBLE,//6//격노???�날검
	ITEM_SWORD_ELVEN,//7//?�호?�의 검
	ITEM_SWORD_ROYAL,//8//?��????�호??
	ITEM_SWORD_GHOST,//9//?�찰??검
	ITEM_SWORD_GHOST2,//10//?�울 ?�래??
	ITEM_SWORD_FRAME,//11//?�레?�소??
	ITEM_SWORD_ICE,//12//?�이?�소??
	ITEM_SWORD_THUNDER,//13//?�더?�드
	ITEM_SWORD_EARTH,//14//?�스?�드
	ITEM_SWORD_LAEVATEINN,//15//?�바?�인
	ITEM_SWORD_STORMBRINGER,//16//?�톰브링�?
	ITEM_SWORD_CALADBOLG,//17//칼라?�볼�?
	ITEM_SWORD_BALMUNG,//18//발뭉
	ITEM_SWORD_HRUNTING,//19//?�룬??
	ITEM_SWORD_GIANT,//20//거인??�?
	ITEM_SWORD_MISTILTEINN,//21//미스?�테??
	ITEM_SWORD_EXCALIBUR,//22//?�스칼리�?
	ITEM_SWORD_HOLY,//23//?�리소??
	ITEM_SWORD_DARK,//24//?�크?�드
	ITEM_SWORD_LEO,//25//?�오?�드
	ITEM_SWORD_DEATH,//26//?�신????
	ITEM_SWORD_DRAGONCLOW,//27//?�래�??�로??
	ITEM_SWORD_DRAGONTOOTH,//28//?�룡???�금??
	ITEM_SWORD_DRAGONGOD,//29//?�룡마강검
	ITEM_SWORD_DRAGONSLAYER,//30//?�래�??�레?�어
	ITEM_SWORD_ULTIMATE,//31//?�티밋소??
	ITEM_SWORD_DIMENSIONAL,//32//차원??검
	ITEM_SWORD_HEAVEN,//33//천공??검
	ITEM_SWORD_STARDUST,//34//?��??�스??
	ITEM_SWORD_KING,//35//?�왕??검
	TOTAL_SWORD,

	//�?: ITEM_GUN
	ITEM_GUN_PISTOL = 0,//발화??�?
	ITEM_GUN_REVOLVER,//리볼�??�이??
	ITEM_GUN_MAGNUM,//45구경 ?�토�?: ?�일?�트 ?�러
	ITEM_GUN_AUTOGUN45MM,//고져??�?: ??���?캐논
	ITEM_GUN_JEWELGUN,//?�천마도�?: 마도머신�?
	ITEM_GUN_EXPLOSION,//?�양??�?: ?�퍼?�바
	ITEM_GUN_CROSSFIRE,//?�파?�어 �?: ?�페르노 캐논 : 마룡?�화??
	ITEM_GUN_INFERNO,//?�로???�이??: ?�스?�먼트 : ?�그?�로??
	TOTAL_GUN,

	//부메랑 : ITEM_BOOMERANG
	ITEM_BOOMERANG_BOOMERANG = 0,//?�냥??부메랑
	ITEM_BOOMERANG_VOYAGER,//?�라?�서
	ITEM_BOOMERANG_WINDWALKER,//강철 부메랑 : ?�드 ?�래??
	ITEM_BOOMERANG_DOUBLECROSS,//?�라???��? : ???�라?�앵글
	ITEM_BOOMERANG_THUNDERMASTER,//?�이?�닝 ?��? : ?�탄??부메랑
	ITEM_BOOMERANG_SOULCHASER,//?�울 체이??: ???�레?�어
	ITEM_BOOMERANG_GRYPHONWING,//그리????: ???�브 ?�스 : ?�래�???
	ITEM_BOOMERANG_MEGATRIAL,//로커?�트 ?�트 : ?�노?�이????: ?�재?�터 ?��?
	TOTAL_BOOMERANG,

	//?�멧 : ITEM_HELM
	ITEM_HELM_BRONZE = 0,//1//?�드 가??
	ITEM_HELM_BASINET,//2//바시??
	ITEM_HELM_DROW,//3//?��??�름 : ?�츄리온 ?�멧
	ITEM_HELM_SPIKEHEAD,//4//검?�사???�구 : 블러???�멧
	ITEM_HELM_GLADITOR,//5//?�파?�크 ?�드 : 귀?�의 ?�구
	ITEM_HELM_GIANT,//6//그랜???�름 : ?�기?�의 ?�구
	ITEM_HELM_RUINED,//7//고�????�구 : ?�영???�구 : 미라�??�름
	ITEM_HELM_TITANIUM,//8//?�자???�구 : ?��?먼트 ?�맷 : ?�시리스 ?�맷
	TOTAL_HELM,

	//모자 : ITEM_HAT
	ITEM_HAT_COWBOY = 0,//카우보이 모자
	ITEM_HAT_RIDINGGOGGLE,//?�책??보닛
	ITEM_HAT_BERET,//?�인?� ??: 무법?�의 모자
	ITEM_HAT_WESTERNROMANCE,//?�클�?: 골드 블레??
	ITEM_HAT_SCOUT,//?�드 ?�로??: ?�븐 ??
	ITEM_HAT_SNIPERGOGGLE,//?�나?�퍼 고�? : ?�쌔???�코??
	ITEM_HAT_ELVENCAP,//?��???모자 : 카오???�져 : ?�이?�메????
	ITEM_HAT_DRAGONSKULL,//?�리?�스?�스 : 발키�??�클??: ?�딘 ?�라??
	TOTAL_HAT,

	//?�건 : ITEM_CAP
	ITEM_CAP_FEATHER = 0,//공작깃털 모자
	ITEM_CAP_BEASTMANE,//귀족의 머리??
	ITEM_CAP_EXPLORERHAT,//거상??모자 : 캐러�?리더
	ITEM_CAP_ACECAP,//?�냥�?모자 : 로빈??�?
	ITEM_CAP_LIONMANE,//?�우?�의 모자 : 미노?�?�르??
	ITEM_CAP_GREAVE,//?�적??모자 : 졸리로져 �?
	ITEM_CAP_DEATH,//?�이??�?: 브레?�브 �?: ?�이?�스??�?
	ITEM_CAP_TROLLHEAD,//?�래�??�어�?: ?�드???�드 : 리바?�어??�?
	TOTAL_CAP,

	//갑옷 : ITEM_ARMOR
	ITEM_ARMOR_BRONZE = 0,//1//?�터 ?�닉
	ITEM_ARMOR_SCALE,//2//미늘 갑옷
	ITEM_ARMOR_BANDED,//3//?�프 ?�레?�트 : 밴디??메일
	ITEM_ARMOR_SKULL,//4//?�컬 메일 : 마�??�의 ?�갑
	ITEM_ARMOR_PLATE,//5//?�금?�공 갑옷 : ?�워�??�머
	ITEM_ARMOR_RUNIC,//6//미스�??�머 : ?�정??갑주
	ITEM_ARMOR_MYTHRIL,//7//고�???갑옷 : 불멸??갑주 : 브리건딘
	ITEM_ARMOR_DRAGONSKIN,//8//?�비??갑옷 : ?�룡??갑옷 : 바하무트 ?�머
	TOTAL_ARMOR,

	//조끼 : ITEM_VEST
	ITEM_VEST_WESTERN = 0,//카우보이 조끼
	ITEM_VEST_LEOPARD,//?�크 조끼
	ITEM_VEST_SILK,//방랑?�의 조끼 : ?�바?�벌 조끼
	ITEM_VEST_PIRATE,//?�적??조끼 : ?�쌔??베스??
	ITEM_VEST_BALL,//벨벳 ?�츠 : 고딕 ?�츠
	ITEM_VEST_STAR,//귀족의 조끼 : ?�?�슬 조끼
	ITEM_VEST_SPATIOTEMPORAL,//진홍�??�츠 : 불사???�츠 : 뱀?�이??로드
	ITEM_VEST_QUEEN,//?��???로브 : ?�라??로브 : 루시??로브
	TOTAL_VEST,

	//코트 : ITEM_COAT
	ITEM_COAT_SIMPLE = 0,//?�수??코트
	ITEM_COAT_PADDING,//?�딩 ?�머
	ITEM_COAT_LEATHER,//?��?�?코트 : 그리즐리 ?�킨
	ITEM_COAT_CUREBOIL,//?�어 보일 : 코아?� ?��???
	ITEM_COAT_BEAST,//귀족의 코트 : ?�까마�? 코트
	ITEM_COAT_GRIZZLY,//극�???코트 : 블리?�드 가??
	ITEM_COAT_CROCODYLE,//??코트 : 가고일 코트 : ?��??�스 코트
	ITEM_COAT_HYDRASCALE,//바이??코트 : 종말??코트 : 카오???�페??
	TOTAL_COAT,

	//건�???: ITEM_GUNTLET
	ITEM_GUNTLET_IRON = 0,//1//?�드 가??
	ITEM_GUNTLET_CHAIN,//2//�?�� ?�갑
	ITEM_GUNTLET_MONSTER,//3//체인 건�???: 모험?�의 ?�갑
	ITEM_GUNTLET_KNIGHT,//4//?�이??글로브 : 명성???�갑
	ITEM_GUNTLET_EAGLECLAW,//5//비스???�드 : ?�우�?건�???
	ITEM_GUNTLET_SINE,//6//?�이�?건�???: 무쌍???�갑
	ITEM_GUNTLET_JUSTICEHAND,//7//광전?�의 ?�갑 : ?�격?�수 : ?�바???�톱
	ITEM_GUNTLET_HOLYHAND,//8//?�래�??�드 : 백룡???�갑 : 바하무트 ?�드
	TOTAL_GUNTLET,

	//?�찌 : ITEM_ARMLET
	ITEM_ARMLET_LEATHER = 0,//?�제??묵주
	ITEM_ARMLET_DESERT,//?�행?�의 ?�찌
	ITEM_ARMLET_EXPLORER,//백금 브레?�렛 : ?�인???�찌
	ITEM_ARMLET_RAIDERS,//?�사???�렛 : ?�프 ?�렛
	ITEM_ARMLET_NOBLESS,//?�메?�드 ?�찌 : ?�블?�스 ?�렛
	ITEM_ARMLET_DEVIL,//?�블 ?�렛 : 몽마???�찌
	ITEM_ARMLET_DIGNITY,//?�엄???�찌 : 지배자???�찌 : ?�프?�스 ?�렛
	ITEM_ARMLET_HERO,//?�웅???�찌 : ?�울 브레?�렛 : �??�드
	TOTAL_ARMLET,

	//?�갑 : ITEM_GLOVE
	ITEM_GLOVE_TRAVELER = 0,//?�행?�의 ?�갑
	ITEM_GLOVE_DUALTIE,//?�중매듭 ?�갑
	ITEM_GLOVE_LINEN,//?�매치기 ?�갑 : ?�?�우 ?�드
	ITEM_GLOVE_RUNE,//?�크 글로브 : 귀공자???�갑
	ITEM_GLOVE_FAIRY,//?�공?�의 ?�갑 : 마스??글?�브
	ITEM_GLOVE_ROCKET,//마법문양 ?�갑 : 커스??글로브
	ITEM_GLOVE_LACEMITTEN,//?�판????: 구원????: ?�터???��?
	ITEM_GLOVE_GLORY,//?�자???�갑 : ?�라??글로브 : ?��??�드
	TOTAL_GLOVE,

	//?�트 : ITEM_KILT
	ITEM_KILT_CHAIN = 0,//1//밴딩 ?�트
	ITEM_KILT_DUALCHAIN,//2//체인 ?�트
	ITEM_KILT_BATTLE,//3//?�이???�트 : 배�? ?�트
	ITEM_KILT_NIGHTMARE,//4//?�컬 ?�트 : ?�령??바�?
	ITEM_KILT_BATTLEFIELD,//5//?�령??바�? : ?�르??바�?
	ITEM_KILT_DWARVEN,//6//미스�??�트 : ?�어�??�트
	ITEM_KILT_DURAHAN,//7//?�인?�트 ?�트 : ?�터???�트 : ?�리�??�트
	ITEM_KILT_EARTHQUAKE,//8//?�수???�트 : �?��???�트 : ?�기??바�?
	TOTAL_KILT,

	//바�? : ITEM_SKIRT
	ITEM_SKIRT_BROCADE = 0,//?�단 ?�커??
	ITEM_SKIRT_CARPSKIN,//빈티지 ?�커??
	ITEM_SKIRT_VELVET,//?�풍?�색 치마 : ?�련???�커??
	ITEM_SKIRT_NOBLE,//벨벳 ?�커??: ?�공?�??치마
	ITEM_SKIRT_GENERAL,//??��???�커??: 무�?개빛 치마
	ITEM_SKIRT_GLORY,//금실??치마 : ?�제???�커??
	ITEM_SKIRT_CHAOS,//?�광??치마 : ?�자??치마 : ?�령??치마
	ITEM_SKIRT_HERO,//?�제???�커??: 비슈???�커??: ?�양???�커??
	TOTAL_SKIRT,

	//바�? : ITEM_PANTS
	ITEM_PANTS_RIDING = 0,//?�마??바�?
	ITEM_PANTS_VINTAGEJEAN,//카프?�킨 ?�츠
	ITEM_PANTS_BLAZE,//망령???�츠 : 머�? 밴디지
	ITEM_PANTS_ASSASSIN,//?�단??바�? : ?�쌔???�츠
	ITEM_PANTS_TEMPEST,//?�일???�츠 : ?�독??바�?
	ITEM_PANTS_SCARLETLEGGINGS,//?��????�츠 : 캐러�??�츠
	ITEM_PANTS_HEAVEN,//카오???�츠 : 침묵??바�? : ?�비???�츠
	ITEM_PANTS_SATANIC,//가?�안 ?�츠 : 켈베로스 ?�더 : ?�누비스 바�?
	TOTAL_PANTS,

	//?�화 : ITEM_GREAVES
	ITEM_GREAVES_TRAINER = 0,//1//코퍼 그리�?
	ITEM_GREAVES_CHAIN,//2//밴디??그리�?
	ITEM_GREAVES_KNIGHT,//3//체인 그리�?: ?�이??그리�?
	ITEM_GREAVES_FROZEN,//4//?�로�?그리�?: 만년?�의 ?�발
	ITEM_GREAVES_GOLEM,//5//?�레?�트 부�?: ?�워�?그리�?
	ITEM_GREAVES_GIANT,//6//빅풋 그리�?: 골렘 그리�?
	ITEM_GREAVES_GHOST,//7//마�??�의 ?�발 : ?�령???�발 : 종말??발소�?
	ITEM_GREAVES_LEGEND,//8//?�래�?그리�?: 마룡??발자�?: 가?�아 그리�?
	TOTAL_GREAVES,

	//?�발 : ITEM_SHOES
	ITEM_SHOES_CLEAN = 0,//?�스???�즈
	ITEM_SHOES_CHASER,//?�웨?�드 ?�즈
	ITEM_SHOES_LEATHER,//?�이???�즈 : 밀리터�??�커
	ITEM_SHOES_ROCKY,//칠흑???�즈 : 마�????�즈
	ITEM_SHOES_CARVING,//귀부?�의 ?�발 : 로얄 ?�?�브
	ITEM_SHOES_NETHERWORLD,//리치 ?�즈 : ?��? ?�일�?
	ITEM_SHOES_INCARNATION,//?�리�??�즈 : 미라???�즈 : 그라비티 ?�즈
	ITEM_SHOES_HEAVENS,//베이그�???: ?�이???�즈 : ?�스?�니 ?�즈
	TOTAL_SHOES,

	//부�?: ITEM_BOOTS
	ITEM_BOOTS_SUEDE = 0,//?�니커즈
	ITEM_BOOTS_WESTERN,//?�캐빈�? 부�?
	ITEM_BOOTS_RIDING,//천둥가�??�발 : ?�뢰???�국
	ITEM_BOOTS_RICH,//가?�너 부�?: ?�렌??루트
	ITEM_BOOTS_OGRE,//?�일??부�?: 캡틴 부�?
	ITEM_BOOTS_DARK,//?�?�의 ?�발 : ???�트?�이??
	ITEM_BOOTS_MIRACLE,//?�레멘탈 부�?: 브리�??�드 : ?�페?�트 부�?
	ITEM_BOOTS_DESTINY,//?�어?�커 : ?�라?�드 부�?: ?�븐�?부�?
	TOTAL_BOOTS,

	//목걸??: ITEM_NECK
	ITEM_NECK0 = 0,//명예???�던??0)
	ITEM_NECK1,//?�옥??브로�?1)
	ITEM_NECK2,//찰나???�찌(2)
	ITEM_NECK3,//?�금 바늘(3)
	ITEM_NECK4,//?�열???�찌(4)
	ITEM_NECK5,//메피?�토 ?�리(5)
	ITEM_NECK6,//?�멸???�프(6)
	ITEM_NECK7,//?�어??머리?�(7)
	ITEM_NECK8,//찬트???�던??8)
	ITEM_NECK9,//미래??거울(9)
	ITEM_NECK10,//?�의 모래?�계(10)
	ITEM_NECK11,//지?�의 만화�?11)
	ITEM_NECK12,//?�능??브로�?12)
	ITEM_NECK13,//?�명??보옥(13)
	ITEM_NECK14,//증식??목걸??14)
	ITEM_NECK15,//천공??목걸??15)
	ITEM_NECK16,//?�자????16)
	ITEM_NECK17,//꿈의 ?�카리나(17) X
	ITEM_NECK18,//무한???�침�?18) X
	ITEM_NECK19,//기억???�르�?19) X
	ITEM_NECK20,//?�쟁?�의 �?20)
	ITEM_NECK21,//?�욕????���?21)
	ITEM_NECK22,//?�더?�형(22)
	ITEM_NECK23,//?�마??브로�?23)
	ITEM_NECK24,//?�르???�보(24)
	ITEM_NECK25,//?�자???�계(25)
	ITEM_NECK26,//?�마??뿔피�?26) X
	ITEM_NECK27,//?�만?��? ?��?(27) X
	TOTAL_NECK,

	//목걸??: ITEM_RING
	ITEM_RING0 = 0,	//?�신??반�?(28)
	ITEM_RING1,	//?�찰??반�?(29)
	ITEM_RING2,	//?�공??반�?(30)
	ITEM_RING3,	//?�방??반�?(31)//|e?�용??i%d%%|j?�률�??�태?�상?�거
	ITEM_RING4,	//?�호??반�?(32)
	ITEM_RING5,	//?�환??반�?(33)//|e?�용??|jHP |i%d |j?�복
	ITEM_RING6,	//?�생??반�?(34)//|e?�용??|i%d%%|j?�률�?추�??��?
	ITEM_RING7,	//??��??반�?(35)
	ITEM_RING8,	//골렘??반�?(36)
	ITEM_RING9,	//광�???반�?(37)//|e?�용??|j?�피 |i%d%%|j증�?
	ITEM_RING10,	//?�한??반�?(38)//|e?�용??j관?�공격확�?i%d%%|j증�?
	ITEM_RING11,	//?�념??반�?(39)
	ITEM_RING12,	//광포??반�?(40)
	ITEM_RING13,	//?�자??반�?(41)
	ITEM_RING14,	//궁극??반�?(42)
	ITEM_RING15,	//차원??반�?(43)//|e?�용??|j?�방?�도감소 -|i%d
	ITEM_RING16,	//?�화??반�?(44)
	ITEM_RING17,	//?�운??반�?(45)
	TOTAL_RING,

	//보석 : ITEM_GEM
	ITEM_GEM_RUBY = 0,	//루비(46)//PREFIX_FIRE_REGIST
	ITEM_GEM_SAPPHIRE,	//?�파?�어(47)//PREFIX_FROST_REGIST
	ITEM_GEM_AMETHYST,	//?�수??48)//PREFIX_THUNDER_REGIST
	ITEM_GEM_DIAMOND,	//?�이?�몬??49)//PREFIX_HOLY_REGIST
	ITEM_GEM_PERL,	//진주(50)//PREFIX_DARK_REGIST
	ITEM_GEM_EMERALD,	//?�메?�드(51)//SUFFIX_ARMOR
	TOTAL_GEM,

	//?�모?�이??: ITEM_WASTE
	ITEM_WASTE_RETURN = 0,	//귀?�서(24)
	ITEM_WASTE_STAR,				//별의 ?�앗(52)
	ITEM_WASTE_MOON,				//?�의 ?�앗(53)
	ITEM_WASTE_SUN,					//?�양???�앗(54) //골드 2�??�벤??
	ITEM_WASTE_SILVER,				//?��??�브(55)
	ITEM_WASTE_GOLD,				//금빛 ?�브(56)
	ITEM_WASTE_SCARLET,			//진홍�??�브(57)
	ITEM_WASTE_WATER,			//?�계?�의 �?58)
	ITEM_WASTE_FLUTE,				//?�?�리(5)
	ITEM_WASTE_EYEWASH,		//?�약(60)
	ITEM_WASTE_ANTIDOTE,		//?�독??59)
	ITEM_WASTE_WING,				//릴의 ?�개(62)
	ITEM_WASTE_HOLYWATER,	//?�수(61)
	ITEM_WASTE_FIRESTONE,		//불의 ?�령??63)
	ITEM_WASTE_FROSTSTONE,	//물의 ?�령??64)
	ITEM_WASTE_THUNDERSTONE,	//번개???�령??65)
	ITEM_WASTE_HOLYSTONE,					//빛의 ?�령??66)
	ITEM_WASTE_DARKSTONE,					//?�둠???�령??67)
	ITEM_WASTE_FIREELEMENTAL,			//?�염???�령??46)
	ITEM_WASTE_FROSTELEMENTAL,			//?�음???�령??47)
	ITEM_WASTE_THUNDERELEMENTAL,	//천둥???�령??48)
	ITEM_WASTE_HOLYELEMENTAL,			//?�광???�령??49)
	ITEM_WASTE_DARKELEMENTAL,			//칠흑???�령??50)
	ITEM_WASTE_DAMAGE,			//|e강화??비약(207)
	ITEM_WASTE_DEFENSE,			//|e?�내??비약(208)
	ITEM_WASTE_MAGIC,				//|e치유??비약(210)
	ITEM_WASTE_SKILL,				//|e마법??비약(209)
	TOTAL_WASTE,

	//철계???�작?�료 : ITEM_IRON
	ITEM_IRON_LV1 = 0,	//철광??45�?: 68)
	ITEM_IRON_LV2,	//?��?39�?: 69)
	ITEM_IRON_LV3,	//?�륨 ?�편(39�?: 70)
	ITEM_IRON_LV4,	//?�마?�커??42�?: 71)
	ITEM_IRON_LV5,	//?�다만티?�(39�?: 72)
	ITEM_IRON_LV6,	//미스�?결정(42�?: 73)
	ITEM_IRON_LV7,	//?�리?�르�?48�?: 74)
	ITEM_IRON_LV8,	//?�터???�석(30�?: 75)
	TOTAL_IRON,

	//가죽계???�작?�료 : ITEM_LEATHER
	ITEM_LEATHER_LV1 = 0,	//?��? 가�?45�?: 76)
	ITEM_LEATHER_LV2,	//반짝?�는 비늘(39�?: 77)
	ITEM_LEATHER_LV3,	//무쇠 가�?39�?: 78)
	ITEM_LEATHER_LV4,	//?�연변??비늘(42�?: 79)
	ITEM_LEATHER_LV5,	//?�빛 가�?39�?: 80)
	ITEM_LEATHER_LV6,	//바실리스??비늘(42�?: 81)
	ITEM_LEATHER_LV7,	//지?�사??가�?48�?: 82)
	ITEM_LEATHER_LV8,	//붉�? ?�비??30�?: 83)
	TOTAL_LEATHER,

	//천계???�작?�료 : ITEM_CLOTH
	ITEM_CLOTH_LV1 = 0,	//감색 ?��???44�?: 84)
	ITEM_CLOTH_LV2,	//거�?�??�감(41�?: 7)
	ITEM_CLOTH_LV3,	//비단 ?��???40�?: 85)
	ITEM_CLOTH_LV4,	//?�연???��???41�?: 86)
	ITEM_CLOTH_LV5,	//?�?�수 ?�감(40�?: 87)
	ITEM_CLOTH_LV6,	//천고???�감(45�?: 88)
	ITEM_CLOTH_LV7,	//공허???��???45�?: 89)
	ITEM_CLOTH_LV8,	//룬문???�감(28�?: 90)
	TOTAL_CLOTH,

	//?�무계열 ?�작?�료 : ITEM_WOOD
	ITEM_WOOD_LV1 = 0,	//벼락맞�? 가지(60�?: 91)
	ITEM_WOOD_LV2,	//?�어붙�? 가지(29�?: 92)
	ITEM_WOOD_LV3,	//맨드?�이 뿌리(44�?: 93)
	ITEM_WOOD_LV4,	//거인??뿌리(37�?: 94)
	ITEM_WOOD_LV5,	//?�주받?� 뿌리(44�?: 95)
	ITEM_WOOD_LV6,	//고�???가지(37�?: 96)
	ITEM_WOOD_LV7,	//지?�의 뿌리(53�?: 97)
	ITEM_WOOD_LV8,	//?�계?�의 가지(20�?: 98)
	TOTAL_WOOD,

	//?�수?�료 : ITEM_ESSENCE
	ITEM_ESSENCE0 = 0,	//?�단??껍질(9�?: 99)
	ITEM_ESSENCE1,	//?�염???�쿨(9�?: 100)
	ITEM_ESSENCE2,	//?�연???�동??7�?: 20)
	ITEM_ESSENCE3,	//?�주받?� ?�골(11�?: 101)
	ITEM_ESSENCE4,	//?�른 비늘(9�?: 102)
	ITEM_ESSENCE5,	//반짝?�는 ?�장(9�?: 103)
	ITEM_ESSENCE6,	//?�생????18�?: 104)
	ITEM_ESSENCE7,	//갈라�??�금??18�?: 105)
	ITEM_ESSENCE8,	//?�의 증류??9�?: 21)
	ITEM_ESSENCE9,	//빛의 깃털(9�?: 106)
	ITEM_ESSENCE10,	//질풍??조각(12�?: 107)
	ITEM_ESSENCE11,	//?�의 결정(12�?: 8)
	ITEM_ESSENCE12,	//결빙???�루(12�?: 108)
	ITEM_ESSENCE13,	//?�레 가�?6�?: 109)
	ITEM_ESSENCE14,	//?�문???�기(6�?: 110)
	ITEM_ESSENCE15,	//마력??구슬(6�?: 13)
	ITEM_ESSENCE16,	//?�정???�물(27�?: 61)
	ITEM_ESSENCE17,	//광휘???�료(27�?: 111)
	ITEM_ESSENCE18,	//?�맹??증표(9�?: 56)
	ITEM_ESSENCE19,	//?�라???�활??9�?: 59)
	ITEM_ESSENCE20,	//?��????�석(9�?: 128)
	ITEM_ESSENCE21,	//?�석 ?�편(9�?: 113)
	ITEM_ESSENCE22,	//?�혼??꼬리(9�?: 114)
	ITEM_ESSENCE23,	//?�염????��가(9�?: 115)
	ITEM_ESSENCE24,	//?�천??보주(9�?: 0)
	ITEM_ESSENCE25,	//?�혹???�료(9�?: 116)
	ITEM_ESSENCE26,	//만고??�?18�?: 117)
	ITEM_ESSENCE27,	//?�능???�정(18�?: 16)
	ITEM_ESSENCE28,	//?�?�수 ?�개(9�?: 118)
	ITEM_ESSENCE29,	//뫼비?�스????9�?: 119)
	ITEM_ESSENCE30,	//?�원????9�?: 1)
	ITEM_ESSENCE31,	//?�스 ?�왕??9�?: 27)
	ITEM_ESSENCE32,	//?�비???�톤(18�?: 120)
	ITEM_ESSENCE33,	//묘�???반딧�?9�?: 121)
	ITEM_ESSENCE34,	//지배의 ?��?�?9�?: 122)
	ITEM_ESSENCE35,	//?�페???�톤(18�?: 123)
	ITEM_ESSENCE36,	//볼�??�노 ??18�?: 124)
	ITEM_ESSENCE37,	//?�로�???18�?: 125)
	ITEM_ESSENCE38,	//?�피?�티 볼트(18�?: 126)
	ITEM_ESSENCE39,	//?�즐�??�프(6�?: 18)
	ITEM_ESSENCE40,	//가공된 마석(6�?: 17)
	ITEM_ESSENCE41,	//?�천????6�?: 127)
	ITEM_ESSENCE42,	//금단??과실(6�?: 128)
	ITEM_ESSENCE43,	//?�룡???�결(6�?: 129)
	ITEM_ESSENCE44,	//?�혼??결정(6�?: 19)
	TOTAL_ESSENCE,

	//?�스???�이??: ITEM_QUEST
	ITEM_QUEST_MUSHROOM = 0,	//?�눅??버섯(112)
	ITEM_QUEST_GOLD,	//마일즈의 ?�주머니(179)
	ITEM_QUEST_ARMLET,	//마일즈의 ?�찌(2)
	ITEM_QUEST_DARKPIECE,	//?�둠???�편(159)
	ITEM_QUEST_REEF,	//?�호�?187)
	ITEM_QUEST_GOLDBAR,	//?�금(160)
	ITEM_QUEST_AMULET,	//?�둠???��???161)
	ITEM_QUEST_GHOST,	//?�령??188)
	ITEM_QUEST_SCRIPT,	//리클루즈???�고(24)
	ITEM_QUEST_FUND,	//?�이???�주머니(191)
	ITEM_QUEST_FRUIT,	//?�염??과실(189)
	ITEM_QUEST_BIOGRAPHY,	//바리???�웅??190)
	ITEM_QUEST_FANLETTER,	//?�레??190)
	ITEM_QUEST_NUMMARK,		//번호??190)
	ITEM_QUEST_LETTER,		//그을�??��?(191)
	ITEM_QUEST_TRAINER,	//조련?�의 ?��?(191)
	ITEM_QUEST_COMPASS,	//?�간???�침�?197)
	ITEM_QUEST_SECRET,	//기�? 문서(24)
	ITEM_QUEST_SECRET2,	//?��??�의 밀??191)
	ITEM_QUEST_LETTER2,	//?�리?�의 ?��?(191)
	ITEM_QUEST_INVITATION,	//초�???191)
	ITEM_QUEST_DRUID,	//?�루?�드???��?(191)
	ITEM_QUEST_GRANDMA,	//?�머?�의 ?��?(191)
	ITEM_QUEST_KATHERINE,	//캐서린의 반�?(28)
	ITEM_QUEST_TREASUREMAP,	//보물지??181)
	ITEM_QUEST_REDHEART,	//?�열???�울(192)
	ITEM_QUEST_BLUEHEART,	//결빙???�울(193)
	ITEM_QUEST_THUNDERHEART,	//?�격???�울(194)
	ITEM_QUEST_HOLYHEART,	//?�광???�울(195)
	ITEM_QUEST_DARKHEART,	//?�흑???�울(196)
	ITEM_QUEST_FLOWER,	//�?198)
	ITEM_QUEST_SNOWFLOWER,	//백설??가지(92)
	ITEM_QUEST_MAP_TOTALCOMPLETE,	//?�벽??지??190)
	ITEM_QUEST_MAP,	//지??181)
	ITEM_QUEST_MAP_COMPLETE,	//?�성??지??182)
	TOTAL_QUESTITEM,

	//?�료?�이??: ITEM_NETITEM
	ITEM_NET_COUPON = 0,	//쿠폰(200)	//-1
	ITEM_NET_TICKET,	//?�장�?201)	//-1
	ITEM_NET_ENCHANT,	//강화??202)	//-1
	ITEM_NET_PROTECT,	//보호??203)	//-1
	ITEM_NET_RECIPE,		//조합??204)	//-1
	ITEM_NET_RESOLUTION,	//분해??205)	//-1
	ITEM_NET_SOCKET,	//?�켓??206)	//-1
	ITEM_NET_CHARACTER,	//캐릭??167)	//-1
	ITEM_NET_RESURRECTION,	//부?�약(166)	//-1
	ITEM_NET_BOX_WEAPON_HIGH, //고급무기?�자(168)	//BOX_H2
	ITEM_NET_BOX_WEAPON_MID, //중급무기?�자(169)	//BOX_H1
	ITEM_NET_BOX_WEAPON_LOW, //?�급무기?�자(170)	//BOX_H1
	ITEM_NET_BOX_DEFENSE_HIGH, //고급방어구상??171)	//BOX_H2
	ITEM_NET_BOX_DEFENSE_MID, //중급방어구상??172)	//BOX_H1
	ITEM_NET_BOX_DEFENSE_LOW, //?�급방어구상??173)	//BOX_H1
	ITEM_NET_BOX_ACCESSORY_HIGH, //고급?�세?�리?�자(174)	//BOX_H2
	ITEM_NET_BOX_ACCESSORY_MID, //중급?�세?�리?�자(175)	//BOX_H1
	ITEM_NET_BOX_ACCESSORY_LOW, //?�급?�세?�리?�자(176)	//BOX_H1
	ITEM_NET_BOX_RANDOM,	//?�덤?�이?�상??177)	//BOX_CHEST1//?�릭?�면 ?�이?�이 ?�오???�자. 골드 
	ITEM_NET_BOX_GEM,	//고급보석(178)	//BOX_S5
	ITEM_NET_SINGLEBAG,	//가�?162)	//-1
	ITEM_NET_NETBAG,	//창고가�?163)	//-1
	ITEM_NET_APRESET,	//AP초기??164)	//-1
	ITEM_NET_SPRESET,	//SP초기??165)	//-1
	ITEM_NET_PACKAGE_NEWBIE,	//초심???�페??211)	//BOX_S1
	ITEM_NET_PACKAGE_ENCHANT,	//?�퍼강화?�키지(212)	//BOX_S2
	ITEM_NET_PACKAGE_STONE,	//?�톤?�키지(213)	//BOX_S3
	ITEM_NET_PACKAGE_ARENA,	//?�기???�키지(214)	//BOX_S4
	ITEM_NET_PACKAGE_LUCK,	//?�운 ?�키지(215)	//BOX_S5
	ITEM_NET_EXPORB,	//EXP?�득(180)	//-1

	TOTAL_NETITEM,

	//?�아?�템 : ITEM_KEY
	ITEM_KEY0 = 0,	//금단??계곡 ?�쇠(146)
	ITEM_KEY1,	//?�둠???�편 ?�쇠(147)
	ITEM_KEY2,	//?�른비늘 ?�쇠(148)
	ITEM_KEY3,	//차원???�쇠(149)
	ITEM_KEY4,	//?�음???�령 ?�쇠(150)
	ITEM_KEY5,	//번개???�령 ?�쇠(151)
	ITEM_KEY6,	//빛의 ?�령 ?�쇠(152)
	ITEM_KEY7,	//지?�수�??�쇠(153)
	ITEM_KEY8,	//골렘 ?�쇠(154)
	ITEM_KEY9,	//?�둠???�쇠(155)
	ITEM_KEY10,	//?�래곤의 무덤 ?�쇠(156)
	ITEM_KEY11,	//망자???�시 ?�쇠(157)
	ITEM_KEY12,	//마왕?�의 ?�쇠(158)
	ITEM_KEY13,	//?��????�던??15)
	ITEM_KEY14,	//근성???�리??183)
	ITEM_KEY15,	//?�기루의 목걸??184)
	ITEM_KEY16,	//?�우거의 ?�갑(185)
	TOTAL_KEYITEM,

	TOTAL_KEY = ITEM_KEY12 + 1,

	//??: ITEM_STATUE
	ITEM_STATUE_WIND = 0,	//질풍????130)
	ITEM_STATUE_DESTRUCT,	//?�괴????131)
	ITEM_STATUE_POWER,		//?�력????132)
	ITEM_STATUE_MERMAID,	//?�어????133)
	ITEM_STATUE_FLAME,		//불꽃????134)
	ITEM_STATUE_PENGUIN,		//??��????135)
	ITEM_STATUE_ICE,				//?�음????136)
	ITEM_STATUE_THUNDER,	//번개????137)
	ITEM_STATUE_SUN,			//?�양????138)
	ITEM_STATUE_RABBIT,		//?�끼????139)
	ITEM_STATUE_GOLEM,		//골렘????140)
	ITEM_STATUE_DIMENSION,	//차원????141)
	ITEM_STATUE_EAGLE,		//?�수리의 ??142)
	ITEM_STATUE_SQUIRREL,	//?�람쥐의 ??143)
	ITEM_STATUE_DRAGON,		//?�래곤의 ??144)
	ITEM_STATUE_SPIRIT,		//진공????145)
	TOTAL_STATUE,


	//ITEM_BOX
	BOX_INGAME = 0,//?�비가 ?�어?�는 박스
	
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

	//?�료??: ITEM_CREW

	////?�기??2 ?�용 ?�이???�중???�리미엄?�로 주면 ?�듯)
	////검 : ITEM_SWORD
	//ITEM_SWORD2_HRUNTING,	//?��?�??�름
	//ITEM_SWORD2_GRAM,	//?�이???�름
	//ITEM_SWORD2_ASCALON,	//?�?�탄 ?�름
	//ITEM_SWORD2_STORMBRINGER,	//?�폰 ?�름
	//TOTAL_SWORD2,

	////�?: ITEM_GUN				
	//ITEM_GUN2_GAEBOLG,	//가?�보르그
	//ITEM_GUN2_GUNGNIR,	//궁니�?
	//ITEM_GUN2_LONGINUS,	//롱기?�스
	//ITEM_GUN2_TAHULLOOM,	//마탄 ?�?�룸
	//TOTAL_GUN2,

	////부메랑 : ITEM_BOOMERANG				
	//ITEM_BOOMERANG2_KALADBOLG,	//칼라?�볼�?
	//ITEM_BOOMERANG2_GAEBOLG,	//게이볼그
	//ITEM_BOOMERANG2_ANSWERER,	//?�라가?�흐
	//ITEM_BOOMERANG2_MJOLNIR,	//묠니�?
	//TOTAL_BOOMERANG2,

	////?�멧 : ITEM_HELM				
	//ITEM_HELM2_ACHERON,	//?��?�??�름
	//ITEM_HELM2_SEIREN,	//?�이???�름
	//ITEM_HELM2_TITAN,	//?�?�탄 ?�름
	//ITEM_HELM2_TYPHON,	//?�폰 ?�름
	//TOTAL_HELM2,

	////모자 : ITEM_HAT				
	//ITEM_HAT2_NEMESIS,	//?�메?�스 ??
	//ITEM_HAT2_PSYCHE,	//?�시케 ??
	//ITEM_HAT2_ATALANTA,	//?�탈?�?� ??
	//ITEM_HAT2_LETHE,	//?�테 ?�라??
	//TOTAL_HAT2,

	////?�건 : ITEM_CAP				
	//ITEM_CAP2_PHLEGETHON,	//?�레케??�?
	//ITEM_CAP2_THANATUS,	//?�?�토??�?
	//ITEM_CAP2_MIDAS,	//미다??�?
	//ITEM_CAP2_EREBOS,	//?�레보스 �?
	//TOTAL_CAP2,

	////갑옷 : ITEM_ARMOR				
	//ITEM_ARMOR2_ACHERON,	//?��?�??�머
	//ITEM_ARMOR2_SEIREN,	//?�이???�머
	//ITEM_ARMOR2_TITAN,	//?�?�탄 ?�머
	//ITEM_ARMOR2_TYPHON,	//?�폰 ?�머
	//TOTAL_ARMOR2,
	//		
	////조끼 : ITEM_VEST				
	//ITEM_VEST2_NEMESIS,	//?�메?�스 로브
	//ITEM_VEST2_PSYCHE,	//?�시케 로브
	//ITEM_VEST2_ATALANTA,	//?�탈?�?� 로브
	//ITEM_VEST2_LETHE,	//?�테 로브
	//TOTAL_VEST2,
	//		
	////코트 : ITEM_COAT				
	//ITEM_COAT2_PHLEGETHON,	//?�레케??코트
	//ITEM_COAT2_THANATUS,	//?�?�토??코트
	//ITEM_COAT2_MIDAS,	//미다??코트
	//ITEM_COAT2_EREBOS,	//?�레보스 코트
	//TOTAL_COAT2,

	////건�???: ITEM_GUNTLET				
	//ITEM_GUNTLET2_ACHERON,	//?��?�?건�???
	//ITEM_GUNTLET2_SEIREN,	//?�이??건�???
	//ITEM_GUNTLET2_TITAN,	//?�?�탄 건�???
	//ITEM_GUNTLET2_TYPHON,	//?�폰 건�???
	//TOTAL_GUNTLET2,

	////?�찌 : ITEM_ARMLET				
	//ITEM_ARMLET2_NEMESIS,	//?�메?�스 ?�렛
	//ITEM_ARMLET2_PSYCHE,	//?�시케 ?�렛
	//ITEM_ARMLET2_ATALANTA,	//?�탈?�?� ?�렛
	//ITEM_ARMLET2_LETHE,	//?�트 ?�렛
	//TOTAL_ARMLET2,

	////?�갑 : ITEM_GLOVE				
	//ITEM_GLOVE2_PHLEGETHON,	//?�레케???�드
	//ITEM_GLOVE2_THANATUS,	//?�?�토???�드
	//ITEM_GLOVE2_MIDAS,	//미다??글?�브
	//ITEM_GLOVE2_EREBOS,	//?�레보스 ?�드
	//TOTAL_GLOVE2,

	////?�트 : ITEM_KILT				
	//ITEM_KILT2_ACHERON,	//?��?�??�트
	//ITEM_KILT2_SEIREN,	//?�이???�트
	//ITEM_KILT2_TITAN,	//?�?�탄 ?�트
	//ITEM_KILT2_TYPHON,	//?�폰 ?�트
	//TOTAL_KILT2,

	////바�? : ITEM_SKIRT				
	//ITEM_SKIRT2_NEMESIS,	//?�메?�스 치마
	//ITEM_SKIRT2_PSYCHE,	//?�시케 ?�커??
	//ITEM_SKIRT2_ATALANTA,	//?�탈?�?� 치마
	//ITEM_SKIRT2_LETHE,	//?�테 ?�커??
	//TOTAL_SKIRT2,

	////바�? : ITEM_PANTS				
	//ITEM_PANTS2_PHLEGETHON,	//?�레케???�츠
	//ITEM_PANTS2_THANATUS,	//?�?�토???�츠
	//ITEM_PANTS2_MIDAS,	//미다???�츠
	//ITEM_PANTS2_EREBOS,	//?�레보스 ?�츠
	//TOTAL_PANTS2,

	////?�화 : ITEM_GREAVES				
	//ITEM_GREAVES_ACHERON,	//?��?�?그리�?
	//ITEM_GREAVES_SEIREN,	//?�이??그리�?
	//ITEM_GREAVES_TITAN,	//?�?�탄 그리�?
	//ITEM_GREAVES_TYPHON,	//?�폰 그리�?
	//TOTAL_GREAVES2,

	////?�발 : ITEM_SHOES				
	//ITEM_SHOES_NEMESIS,	//?�메?�스 ?�즈
	//ITEM_SHOES_PSYCHE,	//?�시케 ?�즈
	//ITEM_SHOES_ATALANTA,	//?�탈?�?� ?�즈
	//ITEM_SHOES_LETHE,	//?�테 ?�즈
	//TOTAL_SHOES2,

	////부�?: ITEM_BOOTS				
	//ITEM_BOOTS_PHLEGETHON,	//?�레케??부�?
	//ITEM_BOOTS_THANATUS,	//?�?�토??부�?
	//ITEM_BOOTS_MIDAS,	//미드??부�?
	//ITEM_BOOTS_EREBOS,	//?�레보스 부�?
	//TOTAL_BOOTS2,

	////목걸??: ITEM_NECK				
	//ITEM_NECK28,	//?�비?�스 ?�루
	//ITEM_NECK29,	//?�이?�의 ?�리
	//ITEM_NECK30,	//?�혼???�배
	//ITEM_NECK31,	//?�앙??거울
	//ITEM_NECK32,	//로젤린의 �?
	//ITEM_NECK33,	//?�웅???�사??
	//ITEM_NECK34,	//?�니콘의 �?
	//ITEM_NECK35,	//?�금 조개
	//ITEM_NECK36,	//천사???�개
	//ITEM_NECK37,	//금단??과실
	//ITEM_NECK38,	//죽음???��?�?
	//ITEM_NECK39,	//조각???�혼
	//TOTAL_NECK2,

	////목걸??: ITEM_RING				
	//ITEM_RING18,	//?�벨룽겐 반�?
	//ITEM_RING19,	//?�제??반�?
	//ITEM_RING20,	//?�?�수 반�?
	//ITEM_RING21,	//충성??반�?
	//ITEM_RING22,	//?��? 반�?
	//ITEM_RING23,	//?�금 반�?
	//ITEM_RING24,	//?�정??반�?
	//ITEM_RING25,	//?�마 반�?
	//ITEM_RING26,	//번뇌??반�?
	//ITEM_RING27,	//불사??반�?
	//ITEM_RING28,	//?�속??반�?
	//ITEM_RING29,	//봉인??반�?
	//TOTAL_RING2,	//?�기??2 ?�이??end

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
	ITEM_SKILL_START = ITEM_CREW_START + TOTAL_CREW,


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

	//?�트 ?�이??종류
	SET_BEGINNER = 0,	//0 견습 기사
	SET_KINGDOM,			//1 ?��????�호??
	SET_SPACE,				//2 ?�공??균열
	SET_HAWK,				//3 ?�른매의 ??
	SET_MAGICGUN,			//4 마도총술??
	SET_SUN,					//5 ?�양???�흔
	SET_WANTED,			//6 ?�상�??�냥�?
	SET_SOUL,					//7 ?�울 ?�터
	SET_MOBIUS,				//8 뫼비?�스????
	SET_TRAINING,			//9 무사?�행
	SET_GUNMAN,			//10 ?�돌??총잡??
	SET_ROOTLESS,			//11 ?�냥�?
	SET_CHALLENGER,		//12 ?�전??
	SET_HUNTER,				//13 ?�터
	SET_MERCENARY,		//14 ?�병
	SET_JUDEGMENT,		//15 ?�판????
	SET_CARAVAN,			//16 캐러�??�인
	SET_MAPLE,				//17 ?�풍?�색
	SET_LOST,					//18 ?��?�??�웅
	SET_DREAM,				//19 몽환??감시??
	SET_GENTLE,				//20 ?�의범절
	SET_BRONZE,				//21 브론�??�이??
	SET_POET,				//22 ?�유?�인
	SET_GUARDIAN,			//23 불멸???�호??
	SET_IMMOTAL,			//24 무한??마력
	SET_MONARCH,			//25 ?�방??군주
	SET_CHASER,				//26 ?�멸??추적??
	SET_SMITH,				//27 ?�공?�의 ?�품
	SET_THIEF,				//28 ?��????�적
	SET_PICNIC,				//29 ?�크??
	SET_GRAND,				//30 ?��????�산
	SET_BULL,					//31 ?�혹???�우??
	SET_DEVIL,				//32 ?�신???��?
	SET_ROYAL,				//33 ?�실 기사
	SET_OUTLAW,			//34 ?�야??무법??
	SET_SKULL,				//35 ?�한???�골기사
	SET_TREASURE,			//36 보물??
	SET_HELL,					//37 지?�의 묵시�?
	SET_LOCUST,				//38 ?�악???�탈??
	SET_VAGABOND,		//39 베�?본드
	SET_ELEMENTAL,		//40 ?�령??가??
	SET_ELITE,				//41 ?�예 ?�나?�퍼
	SET_CHAOS,				//42 ?�돈???�단
	SET_COSTUME,			//43 가?�무?�회
	SET_WING,				//44 천공???�개
	SET_NOBLE,				//45 ?�양??귀�?
	SET_SMILE,				//46 ?�마???�이??
	SET_VICTORY,			//47 ?�자???�광
	SET_STRANGER,			//48 ?�국??모험가
	SET_GUILLOTINE,		//49 길로??
	SET_ANCIENT,			//50 고�????�물
	SET_ARTHUR,				//51 ?�탁??기사
	SET_DRAGON,			//52 ?�래곤의 무덤
	SET_DEADMAN,			//53 ?�의 ?�자

	//?�굴 ?�트 ?�??
	SET_RA1,	//로빈 ?�굴1메인//기사???�약//54
	SET_RA2,	//로빈 ?�굴1보조//바룩??방패//55
	SET_RB1,	//로빈 ?�굴2메인//죽음??그림??/56
	SET_RB2,	//로빈 ?�굴2보조//총명???�무//57
	SET_RC1,	//로빈 ?�굴3메인//?�늘???�판//58
	SET_RC2,	//로빈 ?�굴3보조//?�래?�의 ?��?//59
	SET_RD1,	//로빈 ?�굴4메인//?�마???�혹//60
	SET_RD2,	//로빈 ?�굴4보조//몰렉???�단//61

	SET_DA1,	//?�아???�굴1메인//?�장???�팔//62
	SET_DA2,	//?�아???�굴1보조//?�신???�발//63
	SET_DB1,	//?�아???�굴2메인//망각???�물//64
	SET_DB2,	//?�아???�굴2보조//지?�의 ?�물//65
	SET_DC1,	//?�아???�굴3메인//?�들???�혼//66
	SET_DC2,	//?�아???�굴3보조//?�테?�의 축복//67
	SET_DD1,	//?�아???�굴4메인//마�????�술//68
	SET_DD2,	//?�아???�굴4보조//?�판??�?/69

	SET_MA1,	//맥스 ?�굴1메인//?�사???�래//70
	SET_MA2,	//맥스 ?�굴1보조//마드룩의 갑옷//71
	SET_MB1,	//맥스 ?�굴2메인//?�바??감시??/72
	SET_MB2,	//맥스 ?�굴2보조//명철??바위//73
	SET_MC1,	//맥스 ?�굴3메인//?�웅??분노//74
	SET_MC2,	//맥스 ?�굴3보조//?�리?�의 ?�의//75
	SET_MD1,	//맥스 ?�굴4메인//지?�의 메아�?/76
	SET_MD2,	//맥스 ?�굴4보조//바알???�물//77

	TOTALSET,

	TOTALPREFIXTEXT = 30,
	TOTALSUFFIXTEXT = 31,
	TOTALSUFFIXOPTION = 46,

	//?�두???�션
	PREFIX_WEAPON_DMG = 0,	//공격??증�?
	PREFIX_SWORD_DMG,			//검 공격??증�?
	PREFIX_GUN_DMG,				//�?공격??증�?
	PREFIX_BOOMERANG_DMG,	//부메랑 공격??증�?
	PREFIX_CRITICAL,				//치명?�??증�?
	PREFIX_PIERCE,					//관?�력 증�?
	PREFIX_EXTRA,					//추�??��??�률 증�?
	PREFIX_STR,						//???�탯 증�?
	PREFIX_AGI,						//�??�탯 증�?
	PREFIX_VIT,						//�??�탯 증�?
	PREFIX_INT,						//지 ?�탯 증�?
	PREFIX_SKILLDMG,				//?�킬공격??증�?
	PREFIX_DEFENSE,				//??방어??감소
	PREFIX_ARMOR,					//방어??증�?
	PREFIX_ABSORB,					//물리?�해 감소
	PREFIX_FIRE_REGIST,			//?�염?�??�� 증�?
	PREFIX_FROST_REGIST,		//?�기?�??�� 증�?
	PREFIX_THUNDER_REGIST,	//번개?�??�� 증�?
	PREFIX_HOLY_REGIST,		//?�성?�??�� 증�?
	PREFIX_DARK_REGIST,			//?�흑?�??�� 증�?
	PREFIX_LUCK,						//?�운 증�?
	PREFIX_GOLD,					//골드 ?�득
	PREFIX_EXP,						//경험�??�득
	PREFIX_HPRESTORE,			//HP10초당 X?�복
	PREFIX_MPRESTORE,			//MP10초당 X?�복
	PREFIX_POTION,					//물약�??�과 X증�?
	PREFIX_BUFF,						//버프지?�시�?증�?
	PREFIX_MAGIC_REGIST,			//마법공격?�피??
	PREFIX_RESERVED2,
	PREFIX_RESERVED3,

	//?��????�션
	SUFFIX_WEAPON_DMG,	//물리공격??추�?
	SUFFIX_SWORD_DMG,		//검 추�?
	SUFFIX_GUN_DMG,			//�?추�?
	SUFFIX_BOOMERANG_DMG,	//부메랑 추�?
	SUFFIX_FIRE_ATTACK,		//?�염?�성 공격 ?�률
	SUFFIX_FROST_ATTACK,	//?�기?�성 공격 ?�률
	SUFFIX_THUNDER_ATTACK,	//번개?�성 공격 ?�률
	SUFFIX_HOLY_ATTACK,	//?�성?�성 공격 ?�률
	SUFFIX_DARK_ATTACK,	//?�흑?�성 공격 ?�률
	SUFFIX_HIT,					//?�중�?증�?
	SUFFIX_IGNORE,				//방어??무시 공격?�률 증�?
	SUFFIX_DELAY,				//?�킬 ?�사???�기시�?감소
	SUFFIX_CRITICAL,			//치명?� ?�해 증�?
	SUFFIX_EVASION,			//?�피??증�?
	SUFFIX_STAT,				//모든 ?�탯 증�?
	SUFFIX_HP,					//?�명??증�?
	SUFFIX_MP,					//마나 증�?
	SUFFIX_HPDRAIN,			//체력?�수
	SUFFIX_MPDRAIN,			//마나?�수
	SUFFIX_ALLREGIST,			//모든 ?�??�� 증�?
	SUFFIX_ARMOR,				//방어??추�?
	SUFFIX_LUCK,					//?�운 증�?
	SUFFIX_GOLD,				//처치??골드 ??증�?
	SUFFIX_EXP,					//경헙�??�득??증�?
	SUFFIX_REQUIRE,			//?�구�?감소
	SUFFIX_DEBUF,				//?�태?�상 지?�시�?감소
	SUFFIX_STUN,				//기절공격 ?�률
	SUFFIX_SKILL,					//?�킬?�벨 증�?
	SUFFIX_RESERVED1,
	SUFFIX_RESERVED2,
	SUFFIX_RESERVED3,

	SUFFIX_ENEMYREGEN,
	SUFFIX_POISON_IMMUNE,	//추�??�션13: ?�무??
	SUFFIX_BLIND_IMMUNE,		//추�??�션16: 블라?�드무효
	SUFFIX_SLOW_IMMUNE,		//추�??�션15: ?�로?�무??
	SUFFIX_CURSE_IMMUNE,		//추�??�션17: ?�주무??
	SUFFIX_STUN_IMMUNE,		//추�??�션14: 기절무효
	SUFFIX_ALWAYSCURSE,		//추�??�션17: 착용???��?
	SUFFIX_HPDECREASE,			//추�??�션1: HP 10초당 X감소
	SUFFIX_MINUSARMOR,			//추�??�션2: 방어?�감??
	SUFFIX_MINUSDRAIN,			//추�??�션3: 공격???�에�?준 ?��?지??X%만큼 HP감소
	SUFFIX_MINUSHP,				//추�??�션4: HP감소
	SUFFIX_MINUSMP,				//추�??�션5: MP감소
	SUFFIX_MINUSEVASION,		//추�??�션7: ?�피감소
	SUFFIX_MINUSHIT,				//추�??�션9: ?�중감소
	SUFFIX_MINUSREGIST,			//추�??�션10: ?�??감소
	SUFFIX_MINUSINT,				//추�??�션11: INT감소
	SUFFIX_MINUSSTR,				//추�??�션12: STR감소
	SUFFIX_MINUSAGI,				//추�??�션13: AGI감소
	SUFFIX_PLUSDEBUF,			//추�??�션14: ?�버??지?�시간증가
	SUFFIX_MINUSSKILL,			//추�??�션15: 모든 ?�킬?�벨 감소
	SUFFIX_MINUSSKILLDMG,		//추�??�션16: ?�킬 공격??감소

	TOTALITEMOPTION,

	//보석 ?�션
	GEM_STR = 0,			//??, 3, 5, 8
	GEM_AGI,					//�?, 3, 5, 8
	GEM_VIT,					//�?, 3, 5, 8
	GEM_INT,					//지2, 3, 5, 8
	GEM_STAT,				//모든 ?�력�?1, 2, 3
	GEM_FIRE_REG,			//?�염?�??�� 3, 5
	GEM_FROST_REG,		//?�기?�??�� 3, 5
	GEM_THUNDER_REG,	//?�연?�??�� 3, 5
	GEM_HOLY_REG,			//?�성?�??�� 3, 5
	GEM_DARK_REG,			//?�흑?�??�� 3, 5
	GEM_REG,					//모든?�??�� 1, 2, 3
	GEM_CRITICAL,			//치명 1, 2%
	GEM_EVASION,			//?�피 1, 2%
	GEM_HIT,					//?�중 1, 2%
	GEM_PIERCE,				//관??1, 2%
	GEM_STUN,				//기절공격 1, 2%
	GEM_EXTRA,				//추�??� 1, 2%
	GEM_IGNORE,				//방어?�무??1, 2%
	GEM_HPDRAIN,			//체력?�수 1, 2%
	GEM_MPDRAIN,			//마나?�수 1, 2%
	GEM_LUCK,					//?�운증�? 5, 10%
	GEM_CRITICAL_DMG,	//치명?� ?�해증�?3, 5%
	GEM_GOLD,				//골드??5, 10%
	GEM_EXP,					//경험치삥 5, 10%
	GEM_REQUIRE,			//?�구치감??5, 10%
	GEM_WEAPON_DMG,	//공격??1, 2%
	GEM_ADD_DMG,			//공격?�추가 3, 5


	//?�점 관??
	SHOPTYPE_CRAFT = 0,//?�비강화
	SHOPTYPE_QUICK,//?�료?�이??


	CRAFT_ENCHANT = 0,//강화
	CRAFT_RECIPE,//?�작
	CRAFT_SOCKET,//?�켓?�착

	SHOPCOUNT_QUICK = 27,

	TOTALINVENTORY = 500,//백업?�으�??�개

	STARTINVENTORY = TOTALINVENTORY,//120,//@@

	//1. 초보검??컬렉??
	//2. 카우보이 컬렉??
	//3. ?�행??컬렉??
	//4. 베이�?컬렉??
	//5. 귀�?컬렉??

	//6. 금속 컬렉??
	//7. 방랑??컬렉??
	//8. 방한 컬렉??
	//9. ?�레?�트 컬렉??
	//10. ?�적 컬렉??

	//11.?�냥�?컬렉??
	//12.검?�사 컬렉??
	//13.벨벳 컬렉??
	//14.?�우??컬렉??
	//15.?�파?�크 컬렉??

	//16.?�나?�퍼 컬렉??
	//17.?�적 컬렉??
	//18.그랜??컬렉??
	//19.?��? 컬렉??
	//20.?�이??컬렉??

	//21.고�? 컬렉??
	//22.?�리?�트 컬렉??
	//23.?�래�?컬렉??
	//24.?�자 컬렉??

	//25. 보석 컬렉??
	//26. ?�성 컬렉??
	//27. 물약 컬렉??
	//28. ??컬렉??
	//29. 가�?컬렉??
	//30. �?컬렉??
	//31. ?�무 컬렉??
	//32. ?�센??컬렉??
	//33. ?�스???�이??컬렉??
	//34. 문서컬렉??
	//35. ?�울 컬렉??
	//36. ?�쇠 컬렉??�?17�?
	//37. ??컬렉??�?16�?
	//38. ?�아?�템


	TOTAL_COLLECTIONS = 24,
	COLLECTIONSITEMCNT = 6,
	COLLECTIONSDATASIZE = 5,

	COLLECTIONMENU_EQUIP = 0,
	TOTAL_COLLECTIONMENU,

} ITEMDEF;

#endif
