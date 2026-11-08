//이 파일은 content/gear_role.tsv 에서 자동으로 났다.
//손으로 고치지 마라 - 다음 생성에서 지워진다.
//값을 고칠 곳은 content/gear_role.tsv (또는 content/balance.xlsx) 다.
//    python tools/content/make_balance.py


static const GearRoleSpec kGearRole[] = {
	{ ITEM_SWORD    , GEAR_AXIS_ATK  , GEAR_AXIS_REGEN, GEAR_LINE_ROBIN ,   0,   0,   0,  10,   0,   0,  10,   0,   0,   0 },
	{ ITEM_GUN      , GEAR_AXIS_ATK  , GEAR_AXIS_ATK  , GEAR_LINE_DIANA ,   0,   0,   0,  15,  10,   0,   0,   0,   0,   0 },
	{ ITEM_BOOMERANG, GEAR_AXIS_ATK  , GEAR_AXIS_UTIL , GEAR_LINE_MAXX  ,   0,   0,   0,   5, 100,   0,   0,   0,   0,   0 },
	{ ITEM_HELM     , GEAR_AXIS_DEF  , GEAR_AXIS_ATK  , GEAR_LINE_ROBIN ,  25,   0,   0,  10,   0,   0,   0,   0,   0,   0 },
	{ ITEM_HAT      , GEAR_AXIS_UTIL , GEAR_AXIS_ATK  , GEAR_LINE_DIANA ,   0,   0,   0,  15, 150,   0,   0,   0,   0,   0 },
	{ ITEM_CAP      , GEAR_AXIS_UTIL , GEAR_AXIS_DEF  , GEAR_LINE_MAXX  ,  12,   0,   0,   5, 100,   0,   0,   0,   0,   0 },
	{ ITEM_ARMOR    , GEAR_AXIS_DEF  , GEAR_AXIS_DEF  , GEAR_LINE_ROBIN ,  40,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
	{ ITEM_VEST     , GEAR_AXIS_DEF  , GEAR_AXIS_UTIL , GEAR_LINE_DIANA ,  25,  80,   0,   0,   0,   0,   0,   0,   0,   0 },
	{ ITEM_COAT     , GEAR_AXIS_DEF  , GEAR_AXIS_REGEN, GEAR_LINE_MAXX  ,  20,   0,   0,   0,   0,   0,   0,   0,   5,   0 },
	{ ITEM_GUNTLET  , GEAR_AXIS_ATK  , GEAR_AXIS_DEF  , GEAR_LINE_ROBIN ,  10,   0,  30,   0,   0,   0,   0,   0,   0,   0 },
	{ ITEM_ARMLET   , GEAR_AXIS_ATK  , GEAR_AXIS_UTIL , GEAR_LINE_DIANA ,   0,   0,  20,   0,  20,   0,   0,   0,   0,   0 },
	{ ITEM_GLOVE    , GEAR_AXIS_ATK  , GEAR_AXIS_REGEN, GEAR_LINE_MAXX  ,   0,   0,  15,   0,   0,   0,  10,   0,   0,   0 },
	{ ITEM_KILT     , GEAR_AXIS_UTIL , GEAR_AXIS_REGEN, GEAR_LINE_ROBIN ,   0, 180,   0,   0,   0,   0,   0,   4,   0,   0 },
	{ ITEM_SKIRT    , GEAR_AXIS_UTIL , GEAR_AXIS_ATK  , GEAR_LINE_DIANA ,   0, 120,   0,  10,   0,  10,   0,   0,   0,   0 },
	{ ITEM_PANTS    , GEAR_AXIS_UTIL , GEAR_AXIS_DEF  , GEAR_LINE_MAXX  ,  10, 250,   0,   0,   0,   0,   0,   0,   0,   0 },
	{ ITEM_GREAVES  , GEAR_AXIS_DEF  , GEAR_AXIS_REGEN, GEAR_LINE_ROBIN ,  20,   0,   0,   0,   0,   0,   0,   0,   4,  10 },
	{ ITEM_SHOES    , GEAR_AXIS_UTIL , GEAR_AXIS_REGEN, GEAR_LINE_DIANA ,   0,   0,   0,   0,   0,  15,   0,   3,   0,  10 },
	{ ITEM_BOOTS    , GEAR_AXIS_REGEN, GEAR_AXIS_DEF  , GEAR_LINE_MAXX  ,  10,   0,   0,   0,   0,   0,   0,   0,   8,  20 },
	{ ITEM_SHIELD   , GEAR_AXIS_DEF  , GEAR_AXIS_REGEN, GEAR_LINE_COMMON,  30,   0,   0,   0,   0,   0,   0,   0,   6,   0 },
	{ ITEM_NECK     , GEAR_AXIS_REGEN, GEAR_AXIS_UTIL , GEAR_LINE_COMMON,   0,  50,   0,   0,   0,   0,   0,   8,   0,   0 },
	{ ITEM_RING     , GEAR_AXIS_ATK  , GEAR_AXIS_REGEN, GEAR_LINE_COMMON,   0,   0,  10,  20,   0,   0,   5,   0,   0,   0 },
	{ ITEM_GEM      , GEAR_AXIS_NONE , GEAR_AXIS_NONE , GEAR_LINE_SOCKET,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 },
};
