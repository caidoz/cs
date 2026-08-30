# -*- coding: utf-8 -*-
"""바깥에서 받은 아이콘 시트를 잘라 crewBullet.png 를 다시 만든다.

[무엇을 자르나]

받은 그림은 한 계열이 2~4 칸으로 늘어서 있고 사이에 화살표가 있다. 그중
쓰는 것은 **맨 앞과 맨 뒤** 두 장이다. 가운데 것은 버린다.

동료의 세 번째 스킬은 늘 소환이나 히어로 스킬이라 총알 그림이 필요 없다.
그래서 한 사람에게 두 칸만 있으면 된다.

    동료 n  ->  skill1 = 2n,  skill2 = 2n + 1

예전에는 세 칸이 한 세트였고 64 명이 26 벌을 나눠 썼다. 이제 한 사람이
자기 두 칸을 가지므로 bullet_match.py 의 손으로 적은 대응표가 필요 없다.

[자를 자리를 어떻게 아나]

받은 그림은 사람이 만든 것이라 줄마다 칸 수가 다르다. 그래서 자동으로
찾지 않고 SERIES 에 적어 둔다. 줄 안에서 칸을 찾는 것만 자동이다. 잘못
잘리면 SERIES 한 줄만 고치면 된다.

    python tools/content/bullet_import.py           #확인용 그림만 낸다
    python tools/content/bullet_import.py --write   #시트를 실제로 바꾼다
"""
import argparse
import os
from collections import deque

from PIL import Image

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
RES = os.path.join(ROOT, 'Resources', 'res')
OUTDIR = os.path.join(ROOT, 'content', 'icon')

TILE = 64
PER_LINE = 16
PAD = 2             #칸 안쪽 여백. 0 으로 두면 이웃 칸과 붙어 보인다.

SRC = os.path.join(os.path.expanduser('~'), 'Downloads',
                   'ChatGPT Image 2026년 8월 30일 오전 10_10_06.png')

#줄이 시작하는 y 와 끝나는 y. 잉크가 있는 가로 띠를 세어 얻었다.
ROWS = [
	(11, 80), (90, 157), (167, 235), (245, 315), (325, 394),
	(410, 472), (481, 543), (552, 612), (620, 679), (688, 748),
	(755, 817), (823, 883), (891, 950), (958, 1018),
]

#(줄, 그 줄에서 몇 번째 칸부터, 몇 칸) 과 이름.
#윗블록은 계열마다 칸 수가 2~3 으로 들쭉날쭉하고, 가운데블록은 줄마다
#네 계열씩 가지런하다. 눈으로 읽어 적었다.
SERIES = [
	#---- 윗블록 : 원래 쓰던 26 가지 ----
	(0,  0, 3, '돌'),      (0,  3, 3, '구슬'),    (0,  6, 3, '꽃'),
	(0,  9, 3, '부채'),    (0, 12, 3, '인형'),
	(1,  0, 2, '지팡이'),  (1,  2, 3, '두루마리'), (1,  5, 3, '망치'),
	(1,  8, 3, '술병'),    (1, 11, 3, '만두'),    (1, 14, 1, '물약a'),
	(2,  0, 1, '물약b'),   (2,  1, 3, '닻'),      (2,  4, 3, '뼈'),
	(2,  7, 3, '단검'),    (2, 10, 3, '물고기'),  (2, 13, 2, '소라'),
	(3,  0, 3, '폭탄'),    (3,  3, 3, '돈주머니'), (3,  6, 3, '하프'),
	(3,  9, 3, '우산'),    (3, 12, 3, '창'),
	(4,  0, 2, '프라이팬'), (4,  2, 3, '찻잔'),   (4,  5, 3, '책'),
	(4,  8, 3, '지도'),    (4, 11, 3, '꽃다발'),

	#---- 가운데블록 : 새로 받은 것 ----
	(5,  0, 3, '유리구슬'), (5, 3, 3, '나뭇잎'),  (5, 6, 3, '방패'),
	(5,  9, 3, '빗자루'),
	(6,  0, 3, '나침반'),  (6, 3, 3, '깃펜'),    (6, 6, 3, '건틀릿'),
	(6,  9, 3, '화살'),
	(7,  0, 3, '룬돌'),    (7, 3, 3, '나비'),    (7, 6, 3, '활'),
	(7,  9, 3, '리본'),
	(8,  0, 3, '모래시계'), (8, 3, 3, '톱니바퀴'), (8, 6, 3, '끌'),
	(8,  9, 3, '독버섯'),
	(9,  0, 3, '국자'),    (9, 3, 3, '회중시계'), (9, 6, 3, '낚싯바늘'),
	(9,  9, 3, '주사위'),
	(10, 0, 3, '도토리'),  (10, 3, 3, '새총'),   (10, 6, 3, '초승달칼'),
	(10, 9, 3, '검'),
	(11, 0, 3, '왕관'),    (11, 3, 3, '철퇴'),   (11, 6, 3, '사슬'),
	(11, 9, 3, '석상머리'),
	(12, 0, 3, '별'),      (12, 3, 3, '식칼'),   (12, 6, 3, '타륜'),
	(12, 9, 3, '석궁'),
	(13, 0, 3, '날개'),    (13, 3, 4, '부메랑'), (13, 7, 4, '장미'),
	(13, 11, 4, '왕홀'),
]

#동료 번호 -> 계열 이름. 한 사람이 한 계열을 가진다.
#받은 그림에 55 팽이와 59 가는검이 빠져 있어 그 둘만 남의 것을 쓴다.
CREW = [
	'돌', '꽃', '우산', '지팡이', '망치', '꽃다발', '술병', '프라이팬',
	'닻', '창', '유리구슬', '폭탄', '소라', '지도', '단검', '나뭇잎',
	'물약', '두루마리', '찻잔', '방패', '책', '빗자루', '부채', '나침반',
	'깃펜', '물고기', '건틀릿', '화살', '룬돌', '나비', '활', '리본',
	'돈주머니', '모래시계', '톱니바퀴', '만두', '끌', '인형', '뼈', '검',
	'독버섯', '국자', '회중시계', '낚싯바늘', '주사위', '구슬', '도토리',
	'새총', '초승달칼', '왕관', '철퇴', '하프', '사슬', '석상머리', '별',
	'돌', '식칼', '타륜', '석궁', '단검', '날개', '부메랑', '장미', '왕홀',
]

#받은 그림에 없어 남의 것을 쓰는 자리. 나중에 채우려면 여기를 본다.
MISSING = {55: '팽이', 59: '가는검'}

#줄을 넘어가며 이어지는 계열. 앞 조각의 첫 장과 뒤 조각의 끝 장을 쓴다.
JOIN = {'물약': ('물약a', '물약b')}


def bands(v, th, minw):
	out = []
	s = None

	for i, x in enumerate(v):
		if x > th and s is None:
			s = i
		elif x <= th and s is not None:
			out.append((s, i - 1))
			s = None

	if s is not None:
		out.append((s, len(v) - 1))

	return [b for b in out if b[1] - b[0] + 1 >= minw]


def cut_white(im):
	"""가장자리에서 스며들어 가며 흰 바탕만 지운다.

	통째로 흰색을 지우면 하이라이트에 구멍이 난다. 바깥에서 이어진 흰색
	만 지워야 안쪽 흰 점이 남는다."""
	#둘레를 흰색으로 한 겹 덧대고 시작한다. 아이콘이 자른 자리에 딱 붙어
	#있으면 바깥에서 스며들 틈이 없어 바탕이 통째로 남는다.
	src = im.convert('RGBA')
	im = Image.new('RGBA', (src.width + 4, src.height + 4), (255, 255, 255, 255))
	im.paste(src, (2, 2))
	w, h = im.size
	px = im.load()
	seen = [[False] * w for _ in range(h)]
	q = deque()

	def thru(x, y):
		"""지나갈 수 있는가. 카드 둘레의 아주 옅은 테를 넘기 위한 것이다."""
		r, g, b, _ = px[x, y]

		return min(r, g, b) >= 226

	def white(x, y):
		"""지울 것인가. 통과보다 엄해야 아이콘의 흰 점이 안 지워진다."""
		r, g, b, _ = px[x, y]

		return min(r, g, b) >= 236

	for x in range(w):
		for y in (0, h - 1):
			if not seen[y][x] and thru(x, y):
				seen[y][x] = True
				q.append((x, y))

	for y in range(h):
		for x in (0, w - 1):
			if not seen[y][x] and thru(x, y):
				seen[y][x] = True
				q.append((x, y))

	while q:
		x, y = q.popleft()

		if white(x, y):
			px[x, y] = (0, 0, 0, 0)

		for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
			nx, ny = x + dx, y + dy

			if 0 <= nx < w and 0 <= ny < h and not seen[ny][nx] and thru(nx, ny):
				seen[ny][nx] = True
				q.append((nx, ny))

	return drop_arrow(im)


def drop_arrow(im):
	"""붙어 들어온 주황 화살표를 지운다.

	칸을 가르는 화살표가 아이콘과 한 덩어리로 잡히는 자리가 있다. 가장 큰
	덩어리가 아이콘이고, 그보다 작으면서 주황이 대부분인 덩어리가 화살표다.
	금빛 아이콘도 주황에 가깝지만 그건 가장 큰 덩어리라 살아남는다."""
	w, h = im.size
	px = im.load()
	seen = [[False] * w for _ in range(h)]
	blobs = []

	for y in range(h):
		for x in range(w):
			if seen[y][x] or px[x, y][3] == 0:
				continue

			q = deque([(x, y)])
			seen[y][x] = True
			cells = []
			hot = 0

			while q:
				cx, cy = q.popleft()
				rr, gg, bb, _ = px[cx, cy]
				cells.append((cx, cy))

				if rr > 190 and 90 < gg < 215 and bb < 135:
					hot += 1

				for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1)):
					nx, ny = cx + dx, cy + dy

					if (0 <= nx < w and 0 <= ny < h and not seen[ny][nx]
					        and px[nx, ny][3]):
						seen[ny][nx] = True
						q.append((nx, ny))

			blobs.append((cells, hot))

	if not blobs:
		return im

	big = max(len(c) for c, _ in blobs)

	for cells, hot in blobs:
		if len(cells) == big:
			continue

		if hot > len(cells) * 0.55:
			for cx, cy in cells:
				px[cx, cy] = (0, 0, 0, 0)

	return im

def fit(im, scale=None):
	"""칸을 꽉 채운다. 받은 그림은 칸마다 여백이 달라 그대로 쓰면 크기가
	제각각으로 보인다.

	scale 을 주면 그 배율로 그린다. 한 세트의 두 장을 같은 배율로 맞추기
	위한 것이다. 뒷장에는 반짝임이 둘려 있어 저마다 맞추면 반짝임까지
	칸에 넣느라 본체가 줄어든다. 앞장보다 뒷장의 별이 작아 보이던 까닭이
	이것이다. 본체 크기가 같아야 세진 것으로 읽힌다."""
	box = im.getchannel('A').getbbox()

	if box is None:
		return Image.new('RGBA', (TILE, TILE), (0, 0, 0, 0)), 1.0

	im = im.crop(box)
	room = TILE - PAD * 2
	s = scale if scale else min(room / float(im.width), room / float(im.height))

	w = max(1, int(round(im.width * s)))
	h = max(1, int(round(im.height * s)))
	im = im.resize((w, h), Image.LANCZOS)

	#가장자리 반투명을 없앤다. 도트는 테두리가 흐려지면 흐물거린다.
	a = im.getchannel('A').point(lambda v: 255 if v >= 128 else 0)
	im.putalpha(a)

	#앞장 배율을 물려받아 칸을 넘치면 넘치는 만큼만 잘라 낸다. 잘리는 것은
	#바깥쪽 반짝임이라 본체는 그대로 남는다.
	out = Image.new('RGBA', (TILE, TILE), (0, 0, 0, 0))
	out.paste(im, ((TILE - w) // 2, (TILE - h) // 2))

	return out, s

def slice_sheet():
	"""계열 이름 -> [첫 장, 끝 장]"""
	src = Image.open(SRC).convert('RGB')
	ink = [[min(src.getpixel((x, y))) < 232 for x in range(src.width)]
	       for y in range(src.height)]

	def orange(x, y):
		r, g, b = src.getpixel((x, y))

		return r > 195 and 95 < g < 210 and b < 125

	cols = []

	for y0, y1 in ROWS:
		prof = [sum(ink[y][x] for y in range(y0, y1 + 1))
		        for x in range(src.width)]
		keep = []

		#화살표도 잉크라 칸으로 잡힌다. 주황이 대부분이면 화살표다.
		for b in bands(prof, 0, 14):
			n = hot = 0

			for y in range(y0, y1 + 1):
				for x in range(b[0], b[1] + 1):
					if ink[y][x]:
						n += 1
						hot += orange(x, y)

			if n and hot < n * 0.35:
				keep.append(b)

		cols.append(keep)

	out = {}

	for row, start, n, name in SERIES:
		cb = cols[row]

		if start + n > len(cb):
			raise SystemExit('%s : %d 줄에 칸이 %d 개뿐인데 %d..%d 를 찾는다'
			                 % (name, row, len(cb), start, start + n - 1))

		y0, y1 = ROWS[row]
		pick = [cb[start], cb[start + n - 1]]
		cut = [cut_white(src.crop((b[0] - 2, y0 - 2, b[1] + 3, y1 + 3)))
		       for b in pick]

		#앞장으로 배율을 정하고 뒷장도 같은 배율로 그린다.
		first, s = fit(cut[0])
		out[name] = [first, fit(cut[1], s)[0]]

	for name, (a, b) in JOIN.items():
		out[name] = [out.pop(a)[0], out.pop(b)[-1]]

	return out


def build(series):
	sheet = Image.new('RGBA', (1024, 1024), (0, 0, 0, 0))

	for i, name in enumerate(CREW):
		for k in range(2):
			idx = i * 2 + k
			im = series[name][k]
			sheet.paste(im, ((idx % PER_LINE) * TILE, (idx // PER_LINE) * TILE))

	return sheet


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument('--write', action='store_true')
	a = ap.parse_args()

	if not os.path.isfile(SRC):
		raise SystemExit('원본 그림이 없다 : %s' % SRC)

	series = slice_sheet()
	print('계열 %d 개를 잘랐다' % len(series))

	miss = [n for n in CREW if n not in series]

	if miss:
		raise SystemExit('CREW 가 가리키는데 없는 계열 : %s' % sorted(set(miss)))

	sheet = build(series)

	if not os.path.isdir(OUTDIR):
		os.makedirs(OUTDIR)

	prev = os.path.join(OUTDIR, '_crewBullet_new.png')
	sheet.save(prev)
	print('%s (%d 칸 = 동료 %d 명 x 2)' % (prev, len(CREW) * 2, len(CREW)))

	for n, what in sorted(MISSING.items()):
		print('  동료 %d 는 %s 그림이 없어 %s 를 빌려 썼다' % (n, what, CREW[n]))

	if a.write:
		dst = os.path.join(RES, 'crewBullet.png')
		bak = os.path.join(RES, 'crewBullet_old.png')

		if not os.path.isfile(bak):
			Image.open(dst).save(bak)
			print('  예전 시트를 %s 로 남겼다' % bak)

		sheet.save(dst)
		print('%s 를 바꿨다' % dst)


main()
