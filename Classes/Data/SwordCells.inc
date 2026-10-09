// tools/swords/build_cells.py 가 만든다. 손으로 고치지 마라.
// 검 그림이 바뀌면 다시 돌려라.
//
// 그 검이 쓰는 칸. bit(row * 4 + col), row 0 이 맨 아랫줄이다.
// 0 이면 네모를 다 쓴다는 뜻이다.
static const unsigned short swordTileCells[35] = {
	0x000,	//w0_1   1x2 2칸  O O
	0x000,	//w0_2   1x2 2칸  O O
	0x000,	//w0_3   1x2 2칸  O O
	0x000,	//w0_4   2x2 4칸  OO OO
	0x000,	//w0_5   1x3 3칸  O O O
	0x000,	//w0_6   2x2 4칸  OO OO
	0x000,	//w0_7   2x2 4칸  OO OO
	0x000,	//w0_8   2x2 4칸  OO OO
	0x000,	//w0_9   2x2 4칸  OO OO
	0x000,	//w0_10  2x3 6칸  OO OO OO
	0x000,	//w0_11  2x3 6칸  OO OO OO
	0x000,	//w0_12  2x3 6칸  OO OO OO
	0x000,	//w0_13  2x3 6칸  OO OO OO
	0x000,	//w0_14  2x3 6칸  OO OO OO
	0x131,	//w0_15  2x3 4칸  O. OO O.
	0x000,	//w0_16  2x3 6칸  OO OO OO
	0x000,	//w0_17  2x3 6칸  OO OO OO
	0x000,	//w0_18  1x4 4칸  O O O O
	0x000,	//w0_19  2x3 6칸  OO OO OO
	0x000,	//w0_20  2x3 6칸  OO OO OO
	0x2722,	//w0_21  3x4 6칸  .O. OOO .O. .O.
	0x000,	//w0_22  2x3 6칸  OO OO OO
	0x000,	//w0_23  2x3 6칸  OO OO OO
	0x000,	//w0_24  2x3 6칸  OO OO OO
	0x000,	//w0_25  2x3 6칸  OO OO OO
	0x000,	//w0_26  2x4 8칸  OO OO OO OO
	0x000,	//w0_27  2x3 6칸  OO OO OO
	0x000,	//w0_28  2x3 6칸  OO OO OO
	0x000,	//w0_29  2x3 6칸  OO OO OO
	0x000,	//w0_30  2x4 8칸  OO OO OO OO
	0x000,	//w0_31  2x4 8칸  OO OO OO OO
	0x000,	//w0_32  2x4 8칸  OO OO OO OO
	0x000,	//w0_33  2x4 8칸  OO OO OO OO
	0x000,	//w0_34  2x4 8칸  OO OO OO OO
	0x000,	//w0_35  2x4 8칸  OO OO OO OO
};
