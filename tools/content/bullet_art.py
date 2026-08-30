# -*- coding: utf-8 -*-
"""총알 아이콘을 64x64 도트로 찍어 crewBullet.png 를 만든다.

[왜 손으로 안 그리고 코드로 찍나]

동료가 64 명인데 쓰는 아이콘은 26 벌뿐이라 여럿이 같은 것을 나눠 쓴다.
1:1 로 맞추려면 38 벌을 더 그려야 한다. 그림을 그릴 손이 없으니 도형을
겹쳐 찍는다. 대신 도트라서 격자에 색을 놓는 일이 되고, 그건 코드가 할 수
있는 일이다.

[왜 64 칸인가]

처음에는 16 칸으로 갔다. sIcon.png 의 스킬 아이콘이 16 칸을 4 배로 늘린
것이라 격자를 맞추려 한 것이다. 그런데 스킬 아이콘은 칸을 꽉 채우는 그림
이고 총알은 잘라낸 물건이라 실제로 쓰는 넓이가 절반이 안 된다. 같은 16
칸이라도 쓸 수 있는 해상도가 그만큼 적어서 단검이 막대가 되고 코등이가
바둑판으로 부서졌다. 그래서 64 칸으로 올린다. 기존 총알 그림도 64 칸이라
시트를 섞어 써도 격자가 어긋나지 않는다.

[한 세트가 세 칸인 까닭]

    +0  보통     skill1 이 쓴다
    +1  강화     skill2 가 쓴다. 밝고 모서리에 빛이 돈다
    +2  각성     아직 안 쓴다. 바깥에 빛무리와 반짝임이 붙는다

세기가 오르는 것이 눈에 보여야 하므로 색만 바꾸지 않고 빛을 더한다.
+1, +2 는 +0 에서 만들어 낸다. 그려야 하는 것은 세트당 한 장이다.

[동료와 1:1]

    동료 n  ->  세트 3n     (skill1 = 3n+0, skill2 = 3n+1)

    python tools/content/bullet_art.py            #미리보기를 낸다
    python tools/content/bullet_art.py --write    #시트를 실제로 바꾼다
"""
import argparse
import colorsys
import math
import os

from PIL import Image

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
RES = os.path.join(ROOT, 'Resources', 'res')

G = 64          #도트 한 변. 시트 한 칸과 같다.
PER_LINE = 16
LV = 5          #명암 단계. 16 칸일 때는 3 이었는데 뭉툭했다.

#---------------------------------------------------------------- 재료
#바탕색 하나만 정하면 단계는 여기서 만든다. 손으로 다 적으면 아이콘마다
#명암이 제각각이 된다.
MAT = {
	'stone':  (150, 142, 126), 'wood':   (146,  92,  44),
	'metal':  (176, 188, 206), 'steel':  (132, 146, 168),
	'gold':   (240, 194,  62), 'brass':  (198, 150,  58),
	'leaf':   ( 78, 168,  60), 'petal':  (250, 246, 232),
	'red':    (214,  60,  56), 'blue':   ( 66, 126, 218),
	'water':  ( 88, 194, 226), 'bone':   (230, 226, 202),
	'dark':   ( 62,  62,  76), 'cloth':  (214, 204, 176),
	'purple': (152,  92, 196), 'pink':   (236, 134, 166),
	'orange': (238, 146,  56), 'green':  (110, 186, 100),
	'brown':  (112,  76,  50), 'ice':    (176, 226, 240),
	'glass':  ( 96, 176, 148), 'coal':   ( 44,  44,  56),
}

#그늘은 푸른 쪽으로, 빛은 노란 쪽으로 돌린다. 밝기만 올리면 회색으로 죽는다.
SHADOW = (34, 28, 52)
LIGHT = (255, 248, 220)


def mix(a, b, t):
	return tuple(int(round(a[i] + (b[i] - a[i]) * t)) for i in range(3))


def shades(name):
	c = MAT[name]

	return [mix(c, SHADOW, 0.56), mix(c, SHADOW, 0.28), c,
	        mix(c, LIGHT, 0.30), mix(c, LIGHT, 0.60)]


class Cell(object):
	"""64x64 한 칸. 글자로 칠하고 나중에 색을 입힌다."""

	def __init__(self):
		self.g = [['.'] * G for _ in range(G)]

	#---- 찍기 ----
	def px(self, x, y, ch):
		x = int(round(x))
		y = int(round(y))

		if 0 <= x < G and 0 <= y < G:
			self.g[y][x] = ch

	def get(self, x, y):
		x = int(round(x))
		y = int(round(y))

		if 0 <= x < G and 0 <= y < G:
			return self.g[y][x]

		return '.'

	def rect(self, x0, y0, x1, y1, ch):
		for y in range(int(y0), int(y1) + 1):
			for x in range(int(x0), int(x1) + 1):
				self.px(x, y, ch)

	def disc(self, cx, cy, r, ch):
		self.ellipse(cx, cy, r, r, 0, ch)

	def ellipse(self, cx, cy, rx, ry, ang, ch):
		"""기울어진 타원. 꽃잎이나 칼날처럼 비스듬한 덩어리에 쓴다."""
		ca = math.cos(-ang)
		sa = math.sin(-ang)
		rr = int(max(rx, ry)) + 2

		for y in range(int(cy) - rr, int(cy) + rr + 1):
			for x in range(int(cx) - rr, int(cx) + rr + 1):
				dx = x - cx
				dy = y - cy
				u = dx * ca - dy * sa
				v = dx * sa + dy * ca

				if (u / rx) ** 2 + (v / ry) ** 2 <= 1.0:
					self.px(x, y, ch)

	def line(self, x0, y0, x1, y1, ch, w=1):
		n = int(max(abs(x1 - x0), abs(y1 - y0)) * 2) + 1
		h = (w - 1) / 2.0

		for i in range(n + 1):
			t = i / float(n)
			x = x0 + (x1 - x0) * t
			y = y0 + (y1 - y0) * t

			if w <= 1:
				self.px(x, y, ch)
			else:
				self.disc(x, y, h + 0.5, ch)

	def poly(self, pts, ch):
		ys = [p[1] for p in pts]

		for y in range(int(min(ys)), int(max(ys)) + 1):
			xs = []

			for i in range(len(pts)):
				x0, y0 = pts[i]
				x1, y1 = pts[(i + 1) % len(pts)]

				if y0 == y1:
					continue

				if min(y0, y1) <= y < max(y0, y1):
					xs.append(x0 + (x1 - x0) * (y - y0) / float(y1 - y0))

			xs.sort()

			for i in range(0, len(xs) - 1, 2):
				for x in range(int(round(xs[i])), int(round(xs[i + 1])) + 1):
					self.px(x, y, ch)

	def arc(self, cx, cy, r, a0, a1, ch, w=1):
		n = int(abs(a1 - a0) * r) + 2

		for i in range(n + 1):
			a = a0 + (a1 - a0) * i / float(n)
			self.disc(cx + math.cos(a) * r, cy + math.sin(a) * r,
			          w / 2.0 + 0.2, ch)

	#---- 다듬기 ----
	def edge(self, a, b):
		"""a 와 b 가 맞닿는 자리를 b 쪽에서 한 겹 판다.

		자동 테두리는 바깥에만 둘러서, 망치 머리와 자루처럼 재료가 붙어
		있으면 한 덩어리로 보인다. 그 한 줄이 형태를 가른다."""
		hit = [(x, y) for y in range(G) for x in range(G)
		       if self.g[y][x] == b
		       and any(self.get(x + dx, y + dy) == a
		               for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)))]

		for x, y in hit:
			self.px(x, y, 'o')

	def shade(self, src, lx=-0.70, ly=-0.72, curve=1.0):
		"""칠해 둔 한 글자를 명암 단계로 나눈다.

		빛은 왼쪽 위에서 온다. 덩어리의 무게중심에서 빛 쪽이면 밝게 한다.
		가장자리 한 겹은 한 단계 더 어둡게 해서 둥글어 보이게 한다."""
		pts = [(x, y) for y in range(G) for x in range(G)
		       if self.g[y][x] == src]

		if not pts:
			return

		cx = sum(p[0] for p in pts) / float(len(pts))
		cy = sum(p[1] for p in pts) / float(len(pts))
		rad = max(1.0, max(math.hypot(x - cx, y - cy) for x, y in pts))

		for x, y in pts:
			d = ((x - cx) * lx + (y - cy) * ly) / rad * curve
			lv = int(round((d + 0.85) / 1.70 * (LV - 1)))
			lv = max(0, min(LV - 1, lv))

			if any(self.get(x + dx, y + dy) != src
			       for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))) and lv > 0:
				lv -= 1

			self.g[y][x] = src.upper() + str(lv)

	def spec(self, cx, cy, rx, ry, ang=0.0):
		"""빛점. 칠해진 자리에만 얹는다. 유리나 쇠에 쓴다."""
		mark = []
		ca = math.cos(-ang)
		sa = math.sin(-ang)
		rr = int(max(rx, ry)) + 2

		for y in range(int(cy) - rr, int(cy) + rr + 1):
			for x in range(int(cx) - rr, int(cx) + rr + 1):
				dx = x - cx
				dy = y - cy
				u = dx * ca - dy * sa
				v = dx * sa + dy * ca

				if (u / rx) ** 2 + (v / ry) ** 2 <= 1.0:
					ch = self.get(x, y)

					if ch not in ('.', 'o'):
						mark.append((x, y, ch))

		for x, y, ch in mark:
			self.g[y][x] = ch[0] + str(LV - 1)

	def deepen(self, pts, n=1):
		"""이미 명암을 먹인 자리를 더 어둡게 한다.

		돌의 금이나 나무결처럼 재료가 바뀌지 않는 홈에 쓴다. 다른 재료로
		그리면 색이 튀고, 테두리를 넣으면 너무 굵다."""
		for x, y in pts:
			ch = self.get(x, y)

			if ch in ('.', 'o') or len(ch) < 2:
				continue

			self.px(x, y, ch[0] + str(max(0, int(ch[1]) - n)))

	def stroke(self, x0, y0, x1, y1, w=1):
		"""deepen 에 넘길 선 위의 자리를 모은다."""
		out = []
		n = int(max(abs(x1 - x0), abs(y1 - y0)) * 2) + 1
		h = int(w) // 2

		for i in range(n + 1):
			t = i / float(n)
			x = int(round(x0 + (x1 - x0) * t))
			y = int(round(y0 + (y1 - y0) * t))

			for dy in range(-h, h + 1):
				for dx in range(-h, h + 1):
					out.append((x + dx, y + dy))

		return out

	def outline(self):
		"""그린 것 바깥에 한 겹 두른다. 도트는 테두리가 있어야 형태가 산다."""
		add = [(x, y) for y in range(G) for x in range(G)
		       if self.g[y][x] == '.'
		       and any(self.get(x + dx, y + dy) not in ('.', 'o')
		               for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)))]

		for x, y in add:
			self.px(x, y, 'o')


#---------------------------------------------------------------- 색 입히기
OUTLINE = (36, 30, 44, 255)


def paint(cell, mats, tier):
	"""글자판을 그림으로 바꾼다. tier 가 오르면 밝아지고 빛이 붙는다."""
	im = Image.new('RGBA', (G, G), (0, 0, 0, 0))
	px = im.load()
	boost = ((0.0, 0.0), (0.30, 0.06), (0.55, 0.12))[tier]

	for y in range(G):
		for x in range(G):
			ch = cell.g[y][x]

			if ch == '.':
				continue

			if ch == 'o':
				px[x, y] = OUTLINE
				continue

			lv = int(ch[1]) if len(ch) > 1 and ch[1].isdigit() else LV // 2
			c = shades(mats[ch[0].lower()])[lv]

			px[x, y] = charge(c, boost) + (255,)

	if tier >= 1:
		rim(im, cell)

	if tier >= 2:
		aura(im, cell)

	return im


def charge(c, boost):
	"""등급이 오른 색. 흰색을 섞으면 밝아지는 게 아니라 바랜다.

	그래서 채도를 올리고 밝기는 조금만 손댄다. 숯처럼 애초에 채도가 없는
	재료는 채도를 올려도 그대로라, 검은 것이 회색으로 뜨는 일이 없다."""
	s_up, l_up = boost

	if not s_up and not l_up:
		return c

	h, l, s = colorsys.rgb_to_hls(*[v / 255.0 for v in c])
	s = min(1.0, s * (1.0 + s_up))
	l = min(1.0, l + (1.0 - l) * l_up)

	return tuple(int(round(v * 255)) for v in colorsys.hls_to_rgb(h, l, s))


def rim(im, cell):
	"""왼쪽 위 모서리에 빛을 한 겹 얹는다."""
	px = im.load()

	for y in range(G):
		for x in range(G):
			if cell.g[y][x] in ('.', 'o'):
				continue

			if cell.get(x - 1, y) in ('.', 'o') or cell.get(x, y - 1) in ('.', 'o'):
				px[x, y] = mix(px[x, y][:3], (255, 252, 236), 0.50) + (255,)


def aura(im, cell):
	"""바깥에 빛무리를 두르고 반짝임을 찍는다."""
	px = im.load()
	ring = [(x, y) for y in range(G) for x in range(G)
	        if cell.g[y][x] == '.'
	        and any(cell.get(x + dx, y + dy) == 'o'
	                for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)))]

	for x, y in ring:
		px[x, y] = (255, 226, 130, 130)

	#외곽선을 살짝만 덥힌다. 다 밝히면 형태를 잡아 주던 테가 풀린다.
	for y in range(G):
		for x in range(G):
			if cell.g[y][x] == 'o':
				px[x, y] = (58, 44, 44, 255)

	for cx, cy, r in ((7, 6, 3), (56, 10, 2), (9, 55, 2), (54, 56, 3)):
		if cell.get(cx, cy) != '.':
			continue

		for k in range(-r, r + 1):
			for a, b in ((cx + k, cy), (cx, cy + k)):
				if cell.get(a, b) == '.':
					px[a, b] = (255, 240, 170, 255 if abs(k) < 2 else 150)


#---------------------------------------------------------------- 아이콘
# 그리는 이는 (칸, 재료표) 를 낸다. 재료표는 칠한 글자가 어떤 재료인지다.
# 글자는 아이콘 안에서만 뜻이 있으므로 a, b, c 순으로 쓴다.
# 순서는 동료 번호와 같다. 동료 n 이 세트 n 을 쓴다.
PI = math.pi


def i00_stone(c):
	"""소년 - 돌"""
	c.disc(31, 35, 21, 'a')
	c.disc(20, 27, 14, 'a')
	c.disc(44, 32, 13, 'a')
	c.disc(33, 47, 15, 'a')
	c.shade('a', curve=0.95)

	#금. 재료가 바뀌는 게 아니라 홈이므로 어둡게만 한다.
	c.deepen(c.stroke(19, 24, 30, 38), 2)
	c.deepen(c.stroke(30, 38, 24, 50), 2)
	c.deepen(c.stroke(30, 38, 45, 34), 1)
	c.spec(22, 24, 7, 5, -0.7)

	return c, {'a': 'stone'}


def i01_marble(c):
	"""소년 - 유리구슬. 돌과 달리 속이 비친다."""
	c.disc(32, 32, 24, 'a')
	c.ellipse(32, 34, 17, 9, -0.5, 'b')
	c.ellipse(32, 34, 9, 4, -0.5, 'a')
	c.shade('a', curve=1.15)
	c.shade('b', curve=0.9)
	c.spec(21, 20, 9, 6, -0.6)
	c.spec(45, 46, 4, 3, -0.6)

	return c, {'a': 'blue', 'b': 'water'}


def i02_flower(c):
	"""소녀 - 꽃"""
	for k in range(6):
		a = -PI / 2 + k * PI / 3
		c.ellipse(32 + math.cos(a) * 17, 32 + math.sin(a) * 17, 12, 8, a, 'a')

	c.shade('a', curve=0.8)

	#꽃잎 사이를 판다. 안 그러면 한 덩어리가 된다.
	for k in range(6):
		a = -PI / 2 + (k + 0.5) * PI / 3
		c.deepen(c.stroke(32 + math.cos(a) * 8, 32 + math.sin(a) * 8,
		                  32 + math.cos(a) * 26, 32 + math.sin(a) * 26), 3)

	c.disc(32, 32, 9, 'b')
	c.shade('b', curve=1.1)
	c.edge('b', 'a')

	for k in range(5):
		a = k * 2 * PI / 5
		c.deepen([(int(32 + math.cos(a) * 5), int(32 + math.sin(a) * 5))], 2)

	return c, {'a': 'pink', 'b': 'gold'}


def i03_leaf(c):
	"""엘프 소녀 - 나뭇잎"""
	c.ellipse(35, 31, 22, 13, -0.72, 'a')
	c.poly([(53, 7), (49, 19), (38, 16)], 'a')
	c.poly([(17, 55), (21, 43), (32, 46)], 'a')
	c.line(17, 53, 8, 59, 'b', 3)
	c.shade('a', curve=0.85)
	c.shade('b')

	c.deepen(c.stroke(50, 11, 18, 52), 2)          #가운데 힘줄

	for k in range(5):                              #잎맥
		t = 0.18 + k * 0.16
		x = 50 + (18 - 50) * t
		y = 11 + (52 - 11) * t
		c.deepen(c.stroke(x, y, x + 12 - k * 2, y - 2 + k), 1)

	return c, {'a': 'leaf', 'b': 'wood'}


def i04_umbrella(c):
	"""할머니 - 우산"""
	c.ellipse(32, 34, 27, 22, 0, 'a')
	c.rect(0, 35, 63, 63, '.')

	for k in range(4):                              #가리비 모양 밑단
		c.disc(9 + k * 15, 34, 7.5, 'a')

	c.rect(0, 42, 63, 63, '.')
	c.shade('a', curve=0.75)

	for k in range(3):                              #우산살 골
		c.deepen(c.stroke(32, 12, 9 + k * 15, 36), 2)

	c.line(31, 20, 31, 48, 'b', 3)
	c.arc(25, 48, 6, 0, PI, 'b', 3)
	c.line(31, 12, 31, 20, 'b', 2)
	c.shade('b')
	c.edge('b', 'a')

	return c, {'a': 'red', 'b': 'wood'}


def i05_staff(c):
	"""할아버지 - 지팡이"""
	c.line(44, 20, 14, 54, 'a', 6)
	c.shade('a', curve=0.7)
	c.deepen(c.stroke(42, 24, 16, 52), 1)           #나무결

	c.disc(48, 14, 11, 'b')
	c.shade('b', curve=1.2)
	c.spec(43, 9, 4, 3, -0.6)

	c.line(41, 23, 46, 28, 'c', 4)
	c.shade('c')
	c.edge('c', 'a')
	c.edge('b', 'c')

	return c, {'a': 'wood', 'b': 'water', 'c': 'gold'}


def i06_hammer(c):
	"""아저씨 - 망치. 머리는 네모나게, 자루는 그 밑을 파고들게."""
	c.line(31, 24, 20, 58, 'a', 8)
	c.shade('a', curve=0.7)
	c.deepen(c.stroke(29, 28, 22, 54), 1)

	#머리. 때리는 면을 오른쪽에 두고 반대쪽은 좁혀 망치꼴을 만든다.
	c.poly([(10, 14), (24, 10), (52, 8), (54, 30), (24, 30), (10, 26)], 'b')
	c.shade('b', curve=0.8)
	c.deepen(c.stroke(45, 9, 47, 29, 2), 2)         #때리는 면의 모서리
	c.deepen(c.stroke(24, 10, 24, 30), 1)           #자루가 박힌 자리
	c.spec(18, 16, 8, 3, -0.15)

	c.line(27, 20, 27, 34, 'c', 6)                  #쇠테
	c.shade('c')
	c.edge('b', 'a')
	c.edge('c', 'a')
	c.edge('b', 'c')

	return c, {'a': 'wood', 'b': 'steel', 'c': 'brass'}


def i07_dagger(c):
	"""엘프 소년 - 단검"""
	c.poly([(54, 4), (58, 11), (30, 39), (24, 33)], 'a')
	c.shade('a', curve=1.0)
	c.spec(52, 8, 3, 8, -0.78)                      #날 등의 빛
	c.deepen(c.stroke(50, 12, 27, 35), 1)           #피홈

	c.line(17, 29, 35, 47, 'c', 5)
	c.shade('c', curve=0.9)

	c.line(24, 40, 13, 51, 'b', 8)
	c.shade('b', curve=0.7)
	c.disc(10, 54, 6, 'c')
	c.shade('c', curve=0.9)

	c.edge('c', 'a')
	c.edge('c', 'b')

	return c, {'a': 'metal', 'b': 'wood', 'c': 'gold'}


def i08_spear(c):
	"""아틀란 병사 - 창. 날은 마름모로. 타원으로 하면 붓이 된다."""
	c.line(5, 59, 36, 30, 'a', 5)
	c.shade('a', curve=0.7)
	c.deepen(c.stroke(8, 56, 34, 32), 1)

	c.poly([(59, 4), (54, 21), (36, 30), (42, 13)], 'b')
	c.shade('b', curve=1.0)
	c.deepen(c.stroke(58, 6, 37, 29), 1)            #가운데 능선
	c.spec(50, 11, 2, 8, -0.78)

	c.line(34, 32, 40, 38, 'c', 7)                  #날을 물린 자리
	c.shade('c')
	c.edge('c', 'a')
	c.edge('c', 'b')

	return c, {'a': 'wood', 'b': 'metal', 'c': 'gold'}


def i09_anchor(c):
	"""뱃사람 - 닻"""
	c.arc(32, 40, 20, PI * 0.08, PI * 0.92, 'a', 6)
	c.poly([(6, 34), (18, 44), (8, 50)], 'a')       #날개
	c.poly([(58, 34), (46, 44), (56, 50)], 'a')
	c.line(32, 12, 32, 54, 'a', 6)
	c.line(15, 20, 49, 20, 'a', 5)
	c.arc(32, 10, 8, 0, 2 * PI, 'a', 5)
	c.shade('a', curve=0.8)
	c.spec(24, 16, 3, 2)

	return c, {'a': 'steel'}


def i10_bottle(c):
	"""아저씨 - 술병"""
	c.ellipse(32, 42, 17, 17, 0, 'a')
	c.poly([(24, 22), (40, 22), (43, 40), (21, 40)], 'a')
	c.rect(26, 12, 38, 24, 'a')
	c.shade('a', curve=1.1)
	c.spec(22, 34, 4, 10, 0.1)

	c.rect(25, 6, 39, 14, 'b')
	c.shade('b')
	c.edge('b', 'a')

	c.rect(21, 38, 43, 50, 'c')
	c.shade('c', curve=0.5)
	c.edge('c', 'a')

	return c, {'a': 'glass', 'b': 'wood', 'c': 'cloth'}


def i11_bomb(c):
	"""소년 - 폭탄"""
	c.disc(30, 38, 21, 'a')
	c.shade('a', curve=1.25)
	c.spec(20, 27, 6, 4, -0.6)

	c.rect(25, 13, 37, 22, 'b')
	c.shade('b')
	c.edge('b', 'a')

	c.arc(44, 16, 12, PI * 0.55, PI * 1.25, 'c', 3)
	c.shade('c')

	for dx, dy in ((0, 0), (3, -3), (-3, -3), (3, 3), (-3, 3), (5, 0), (-5, 0)):
		c.disc(50 + dx, 6 + dy, 1.6, 'd')

	c.shade('d')

	return c, {'a': 'coal', 'b': 'brass', 'c': 'brown', 'd': 'orange'}


ICONS = [
	i00_stone, i01_marble, i02_flower, i03_leaf,
	i04_umbrella, i05_staff, i06_hammer, i07_dagger,
	i08_spear, i09_anchor, i10_bottle, i11_bomb,
]


def render(fn):
	c, mats = fn(Cell())
	c.outline()

	return [paint(c, mats, t) for t in range(3)]


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument('--out', default='')
	ap.add_argument('--cols', type=int, default=4)
	a = ap.parse_args()

	n = len(ICONS)
	cols = a.cols
	rows = (n + cols - 1) // cols
	im = Image.new('RGBA', (G * 3 * cols, G * rows), (236, 236, 240, 255))

	for i, fn in enumerate(ICONS):
		for t, t_im in enumerate(render(fn)):
			im.paste(t_im, ((i % cols) * G * 3 + t * G, (i // cols) * G), t_im)

	out = a.out or os.path.join(ROOT, 'content', 'icon', '_bullet_preview.png')
	im.resize((im.width * 2, im.height * 2), Image.NEAREST).save(out)
	print('%d 세트, %s' % (n, out))


main()
