//이 파일은 content/shop_part.tsv 에서 자동으로 났다.
//손으로 고치지 마라 - 다음 생성에서 지워진다.
//값을 고칠 곳은 content/shop_part.tsv (또는 content/balance.xlsx) 다.
//    python tools/content/make_balance.py


static const GridPart kShopPart[GRIDTEST_SHOPCNT+2] = {
	{ ITEM_SWORD      ,  1, GRADE_NORMAL  , 1, 2,  6, "롱소드", false, 0 },
	{ ITEM_SWORD      , 10, GRADE_RARE    , 1, 3, 18, "플레임소드", false, 0 },
	{ ITEM_SWORD      , 11, GRADE_RARE    , 1, 3, 20, "아이스소드", false, 0 },
	{ ITEM_SWORD      , 21, GRADE_LEGEND  , 1, 3, 60, "엑스칼리버", false, 0 },
	{ ITEM_HELM       ,  1, GRADE_SUPERIOR, 1, 1,  8, "강철투구", false, 0 },
	{ ITEM_ARMOR      ,  1, GRADE_SUPERIOR, 1, 1, 14, "판금갑옷", false, 0 },
	{ ITEM_GUNTLET    ,  1, GRADE_NORMAL  , 1, 1,  4, "건틀릿", false, 0 },
	{ ITEM_KILT       ,  1, GRADE_NORMAL  , 1, 1,  7, "판금바지", false, 0 },
	{ ITEM_GREAVES    ,  1, GRADE_NORMAL  , 1, 1,  4, "강철장화", false, 0 },
	{ ITEM_RING       ,  0, GRADE_EPIC    , 1, 1, 20, "룬반지", false, 0 },
	{ GRID_ITEM_CANNON,  0, GRADE_NORMAL  , 2, 2,  6, "대포", false, 0 },
	{ ITEM_ESSENCE    ,  0, GRADE_NORMAL  , 1, 1,  4, "마력 정수", false, 0 },
};
