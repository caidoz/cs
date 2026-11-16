"""Human-reviewed source selections. IDs are CMF image IDs, never area guesses.

An entry is (image_id, semantic_name, role, optional_local_crop).
Humanoid armor is their actual depicted body; held weapons are excluded.
Energy creatures use flame/sigil/shell features instead of invented anatomy.
"""
SELECTIONS = {
3:[(8,'가시 껍질','core'),(9,'더듬이·머리','attack'),(12,'앞몸통','guard'),(13,'꼬리 몸통','attack')],
4:[(10,'나무 몸통','core'),(13,'얼굴','attack'),(19,'왼팔 가지','attack'),(20,'오른팔 가지','attack'),(9,'잎 무리','guard')],
6:[(8,'눈알','core'),(12,'날개','attack'),(14,'날개 끝','attack'),(9,'눈동자','guard')],
7:[(9,'흉갑','core'),(8,'투구','guard'),(11,'팔','attack'),(14,'다리','guard')],
10:[(10,'비늘 몸통','core'),(8,'머리·이빨','attack'),(18,'갈퀴손','attack'),(27,'꼬리지느러미','guard')],
9:[(11,'갓','core'),(12,'촉수 다발','attack'),(13,'짧은 촉수','attack')],
32:[(13,'흉갑','core'),(12,'투구','guard'),(20,'주먹','attack'),(14,'다리','guard')],
33:[(11,'젤 몸통','core'),(11,'젤 돌기','guard',(8,0,40,16)),(11,'젤 밑단','attack',(4,34,56,14))],
12:[(11,'몸통','core'),(9,'머리','guard'),(16,'주먹','attack'),(24,'다리','guard')],
13:[(9,'가시 가죽','core'),(8,'엄니·주둥이','attack',(0,20,34,24)),(20,'발굽','attack')],
15:[(10,'불꽃 몸체','core'),(10,'불꽃 끝','attack',(8,0,36,28)),(10,'화염 밑단','guard',(0,42,52,26))],
16:[(8,'불새 몸체','core'),(8,'불꽃 날개','attack',(24,0,64,62)),(8,'불꽃 꼬리','attack',(32,52,64,40))],
19:[(8,'석상 얼굴','core'),(8,'얼음 이마','guard',(16,0,40,24)),(8,'얼음 턱','attack',(20,62,32,22))],
18:[(9,'눈 몸통','core'),(18,'얼음 주먹','attack'),(19,'작은 주먹','attack')],
20:[(8,'얼음 얼굴','core'),(9,'얼음 왕관','guard')],
22:[(11,'빛 핵','core'),(11,'번개 가시','attack',(18,0,32,26)),(11,'빛 파편','guard',(0,18,26,36))],
24:[(8,'안개 핵','core'),(24,'번개 고리','attack'),(26,'핵 장식','guard')],
23:[(9,'발광 몸통','core'),(10,'왼 지지부','attack'),(11,'오른 지지부','guard')],
35:[(15,'정령 몸체','core'),(18,'빛 날개','attack'),(22,'반대 날개','guard'),(11,'별빛','attack')],
36:[(10,'문양 구체','core'),(10,'금빛 중심 문양','attack',(42,8,42,88)),(10,'하부 빛 고리','guard',(24,88,76,32))],
27:[(8,'등껍질','core'),(10,'앞다리','attack'),(9,'뒷다리','guard'),(12,'관절','guard')],
26:[(17,'바위 몸통','core'),(9,'바위 머리','attack'),(12,'바위 주먹','attack'),(16,'바위 발','guard')],
39:[(13,'흉갑','core'),(11,'투구','guard'),(12,'철갑 주먹','attack'),(16,'어깨 갑주','guard')],
38:[(8,'용머리','core'),(9,'몸통 마디','attack')],
41:[(10,'비늘 몸통','core'),(8,'머리·이빨','attack'),(13,'발톱','attack'),(11,'꼬리','guard')],
42:[(9,'늑골','core'),(10,'턱뼈','attack'),(12,'꼬리뼈','attack'),(16,'발톱','attack')],
30:[(18,'영혼 몸체','core'),(16,'영혼 손','attack'),(19,'붉은 눈','guard')],
29:[(10,'갑주 몸통','core'),(8,'호박 머리','attack'),(12,'주먹','attack'),(15,'발','guard')],
44:[(10,'마도 몸체','core'),(9,'얼굴·뿔','attack'),(12,'팔','attack'),(13,'어깨 천','guard')],
45:[(13,'갑주 몸통','core'),(19,'투구','guard'),(18,'철갑 주먹','attack'),(20,'어깨 갑주','guard')],
46:[(8,'기계 구체','core'),(8,'전면 장갑','guard',(22,22,38,38)),(8,'외곽 장갑','attack',(0,12,16,30))],
47:[(8,'기계 몸통','core'),(10,'하부 장갑','guard'),(13,'측면 장갑','guard'),(24,'기계 손','attack')],
5:[(8,'돌기 몸통','core'),(9,'머리·이빨','attack'),(10,'앞발','attack'),(13,'뒷다리','guard')],
8:[(8,'갑각 몸통','core'),(12,'가시','attack'),(13,'반대 가시','attack')],
11:[(9,'비늘 몸통','core'),(8,'머리·이빨','attack'),(17,'갈퀴손','attack'),(19,'꼬리지느러미','guard')],
14:[(11,'바위 흉부','core'),(10,'머리','attack'),(16,'주먹','attack'),(23,'발','guard')],
17:[(10,'화염 몸통','core'),(8,'머리·뿔','attack'),(9,'화염 흉갑','guard'),(13,'불꽃 끝','attack')],
21:[(11,'얼음 몸통','core'),(9,'머리·엄니','attack'),(17,'얼음 가시','attack'),(15,'앞발','guard')],
25:[(9,'기계 몸통','core'),(14,'기계 관절','attack'),(16,'연결 마디','guard'),(15,'마력 구체','attack')],
37:[(14,'흉갑','core'),(12,'머리','attack'),(21,'깃털 날개','attack'),(15,'팔','guard')],
34:[(27,'갈기 몸통','core'),(15,'용머리','attack'),(18,'새머리','attack'),(10,'발톱','attack')],
28:[(9,'방주 몸체','core'),(8,'용머리 선수','attack'),(10,'선체 장갑','guard'),(15,'상부 장갑','guard')],
40:[(8,'외피','core'),(19,'포구','attack'),(9,'금빛 촉수','attack'),(10,'하부 외피','guard')],
43:[(13,'비늘 몸통','core'),(11,'머리·뿔','attack'),(24,'발톱','attack'),(10,'꼬리','guard')],
31:[(25,'영혼 흉부','core'),(24,'해골 머리','attack'),(14,'팔','attack'),(28,'어둠의 외피','guard')],
48:[(9,'핵 몸통','core'),(8,'집게팔','attack'),(10,'갑각 마디','guard')],
49:[(21,'갑각 몸통','core'),(11,'머리·턱','attack'),(13,'낫팔','attack'),(16,'발톱','attack')],
50:[(9,'그림자 몸체','core'),(9,'송곳니 머리','attack',(0,0,174,174)),(9,'뿌리 발톱','attack',(0,188,212,120))],
51:[(10,'흉갑','core'),(8,'투구','guard'),(26,'주먹','attack'),(12,'다리','guard')],
109:[(15,'몸통','core'),(8,'머리','attack'),(22,'손','attack'),(10,'팔','guard')],
110:[(14,'몸통','core'),(12,'머리','attack'),(29,'주먹','attack'),(16,'다리','guard')],
}

# A specimen's anatomy and icon choices remain fixed. Extra blocks express
# investment in an existing body part, not extra anatomical limbs.
TIERS = [('normal','일반',4,1),('elite','정예',6,2),('boss','강적',9,4)]

# The black Ariman PNG has a different layout from its shared CMF rectangles.
# These reviewed rectangles point at the same features in that actual PNG.
SOURCE_OVERRIDES = {(347,19):[342,268,50,44],(347,10):[0,324,60,32]}

# Optional silhouette masks only remove pixels around a sampled feature.
# Every retained color and alpha value still comes from the original sheet.
MASKS = {
    (36,'금빛 중심 문양'):[(12,0),(30,0),(41,64),(30,87),(12,87),(0,64)],
    (36,'하부 빛 고리'):[(0,0),(20,8),(56,8),(75,0),(68,23),(38,31),(8,23)],
    (46,'전면 장갑'):[(10,0),(27,0),(37,10),(37,27),(27,37),(10,37),(0,27),(0,10)],
    (22,'번개 가시'):[(0,25),(5,14),(10,18),(16,0),(20,16),(26,10),(31,25)],
    (22,'빛 파편'):[(25,0),(25,35),(12,26),(0,18),(14,12)],
}
