# -*- coding: utf-8 -*-
"""cN.h / cNmv 를 60프레임용으로 4배 확장한다.

원본은 최대한 건드리지 않는다.
 - cNOff / 원본 cNMI, cNMIS, cNCS 줄 : 원문 그대로 다시 출력한다(수식도 보존).
 - 중간모션만 새로 만들어 뒤에 덧붙인다.
 - cNMIC 는 다시 계산한다.
 - 중간모션의 MIS 는 앞뒤 키모션 사각형의 합집합, CS 는 앞 키모션 줄 복사.
"""
import io, re, os, glob

ROOT = r'C:\Users\polyp\Desktop\CP\cs'
CMFDIR = os.path.join(ROOT, 'Classes', 'Cmf')
CMFDATA = os.path.join(ROOT, 'Classes', 'Data', 'CmfData.h')
CMFDEF = os.path.join(ROOT, 'Classes', 'Def', 'CmfDef.h')
_2X = 2


def read(p):
    return io.open(p, encoding='utf-8-sig').read()


class Skip(Exception):
    pass


# ---------------- 상수 표 ----------------
def buildSymbols():
    """Def/Config 헤더의 enum 상수와 #define 을 숫자로 풀어둔다."""
    sym = {'_2X': _2X}
    files = []
    for d in ('Def', 'Config'):
        files += glob.glob(os.path.join(ROOT, 'Classes', d, '*.h'))
    files.append(os.path.join(ROOT, 'Classes', 'Def.h'))
    texts = []
    for f in files:
        try:
            texts.append(read(f))
        except Exception:
            pass

    # #define NAME expr
    pend = []
    for t in texts:
        for m in re.finditer(r'^#define\s+([A-Za-z_]\w*)\s+([^\r\n/]+)', t, re.M):
            pend.append((m.group(1), m.group(2).strip()))
        # enum 본문 : 값이 없으면 직전 +1
        for eb in re.finditer(r'enum\s*(?:_\w+\s*)?\{(.*?)\}\s*\w*\s*;', t, re.S):
            cur = 0
            for line in eb.group(1).split('\n'):
                line = re.sub(r'//.*', '', line)
                for item in line.split(','):
                    item = item.strip()
                    if not item:
                        continue
                    m = re.match(r'^([A-Za-z_]\w*)\s*=\s*(.+)$', item)
                    if m:
                        pend.append((m.group(1), m.group(2).strip()))
                        cur = None
                    elif re.match(r'^[A-Za-z_]\w*$', item):
                        if cur is None:
                            pend.append((item, None))     # 직전 이름 +1
                        else:
                            pend.append((item, str(cur)))
                            cur += 1
                    else:
                        cur = None

    # 여러 번 돌면서 풀 수 있는 것부터 푼다(상수가 상수를 참조한다).
    prevName = None
    order = []
    for name, expr in pend:
        order.append((name, expr, prevName))
        prevName = name
    for _ in range(8):
        progress = False
        for name, expr, prev in order:
            if name in sym:
                continue
            if expr is None:
                if prev in sym:
                    sym[name] = sym[prev] + 1
                    progress = True
                continue
            v = tryEval(expr, sym)
            if v is not None:
                sym[name] = v
                progress = True
        if not progress:
            break
    return sym


def tryEval(expr, sym):
    e = expr.strip().rstrip(',').strip()
    if not e or re.search(r'[";\'\[\]{}]', e):
        return None
    ids = set(re.findall(r'[A-Za-z_]\w*', e))
    for i in ids:
        if i not in sym:
            return None
    try:
        return int(eval(e, {'__builtins__': {}}, dict(sym)))
    except Exception:
        return None


SYM = buildSymbols()


def val(t):
    """숫자 또는 상수 수식을 정수로. 못 풀면 None."""
    if re.match(r'^-?\d+$', t.strip()):
        return int(t)
    return tryEval(t, SYM)


def num(v):
    if v % _2X == 0:
        return '%d * _2X' % (v // _2X)
    return '%d' % v


def grab(name, text):
    m = re.search(r'\b' + name + r'\[\]\s*=\s*\{(.*?)\n\};', text, re.S)
    return m.group(1) if m else None


def toks(block):
    out = []
    for line in block.split('\n'):
        line = re.sub(r'//.*', '', line)
        for t in line.split(','):
            t = t.strip()
            if t:
                out.append(t)
    return out


def rowTexts(block, per):
    """토큰을 per개씩 묶되 원문 텍스트를 유지한다."""
    t = toks(block)
    return [t[i:i + per] for i in range(0, len(t), per)]


# ---------------- 상태 이름 -> 값 ----------------
def buildStateVals():
    body = read(CMFDEF)
    vals, cur = {}, 0
    for line in body.split('\n'):
        line = re.sub(r'//.*', '', line)
        for item in line.split(','):
            item = item.strip()
            if not item:
                continue
            m = re.match(r'^([A-Z][A-Z0-9_]*)\s*=\s*(\d+)$', item)
            if m:
                vals[m.group(1)] = int(m.group(2))
                cur = int(m.group(2)) + 1
                continue
            if re.match(r'^[A-Z][A-Z0-9_]*$', item):
                vals.setdefault(item, cur)
                cur += 1
            else:
                cur = 0
    return vals


STATEVAL = buildStateVals()


# ---------------- cN.h ----------------
class Cmf(object):
    def __init__(self, n, source=None):
        self.n = n
        self.path = os.path.join(CMFDIR, 'c%d.h' % n)
        self.ok, self.why = True, ''
        try:
            self.src = source if source is not None else read(self.path)
            self._parse()
        except Skip as e:
            self.ok, self.why = False, str(e)

    def _parse(self):
        n = self.n
        body = re.search(r'typedef enum _C%d_DEF \{(.*?)\n\} C%d_DEF;' % (n, n), self.src, re.S)
        if not body:
            raise Skip('enum 못 찾음')
        eb = body.group(1)
        head = eb.split('TOTALC%dMOTION' % n)[0]
        # 이름이 PO_C<다른번호>_ 로 되어 있는 줄도 있으므로 접두어를 고정하지 않는다.
        self.motNames = re.findall(r'\b(PO_[A-Z0-9_]+)\s*=\s*\d+', head)
        m = re.search(r'TOTALC%dMOTION\s*=\s*(\d+)' % n, eb)
        if not m:
            raise Skip('TOTALMOTION 못 찾음')
        self.totalMotion = int(m.group(1))
        if len(self.motNames) != self.totalMotion:
            raise Skip('모션이름 %d != TOTALMOTION %d' % (len(self.motNames), self.totalMotion))
        m = re.search(r'TOTALC%dOFF\s*=\s*(\d+)' % n, eb)
        if not m:
            raise Skip('TOTALOFF 못 찾음')
        self.totalOff = int(m.group(1))

        for a in ('Off', 'MI', 'MIC', 'MIS', 'CS'):
            if grab('c%d%s' % (n, a), self.src) is None:
                raise Skip('c%d%s 없음' % (n, a))

        self.offBlock = grab('c%dOff' % n, self.src)
        miRows = rowTexts(grab('c%dMI' % n, self.src), 4)
        mic = [int(t) for t in toks(grab('c%dMIC' % n, self.src))]
        misRows = rowTexts(grab('c%dMIS' % n, self.src), 4)
        csRows = rowTexts(grab('c%dCS' % n, self.src), 8)

        if len(mic) != self.totalMotion * 2:
            raise Skip('MIC 길이 %d' % len(mic))
        if len(misRows) != self.totalMotion:
            raise Skip('MIS 줄수 %d' % len(misRows))
        if len(csRows) != self.totalMotion:
            raise Skip('CS 줄수 %d' % len(csRows))

        self.motions, self.miRawRows = [], []
        for k in range(self.totalMotion):
            st, cnt = mic[k * 2], mic[k * 2 + 1]
            if st + cnt > len(miRows):
                raise Skip('MI 범위 초과')
            parts, raws = [], []
            for j in range(cnt):
                r = miRows[st + j]
                g = re.match(r'IMG_C\d+_(\d+)$', r[0])
                if not g:
                    raise Skip('이미지 토큰 %s' % r[0])
                x, y = val(r[1]), val(r[2])
                if x is None or y is None:
                    raise Skip('좌표 못 품 (%s, %s)' % (r[1], r[2]))
                parts.append((int(g.group(1)), x, y, r[3]))
                raws.append(list(r))
            if not parts:
                raise Skip('파츠 0개 모션 %d' % k)
            self.motions.append(parts)
            self.miRawRows.append(raws)

        self.mis = []
        for r in misRows:
            v = [val(t) for t in r]
            if any(x is None for x in v):
                raise Skip('MIS 못 품')
            self.mis.append(v)
        self.misRawRows = misRows
        self.csRawRows = csRows

    # ---------- 확장 ----------
    def beginExpand(self):
        self.newMotions = list(self.motions)
        self.newMiRaw = [list(r) for r in self.miRawRows]
        self.newNames = list(self.motNames)
        self.newMis = list(self.mis)
        self.newMisRows = list(self.misRawRows)
        self.newCsRows = list(self.csRawRows)
        self.tweenIdx = {}

    def _tween(self, a, b, frac):
        fp_, tp_ = self.newMotions[a], self.newMotions[b]
        usedTo = [False] * len(tp_)
        pairs = []
        for fp in fp_:
            hit = None
            for j, tp in enumerate(tp_):
                if not usedTo[j] and tp[0] == fp[0] and tp[3] == fp[3]:
                    hit = j
                    break
            if hit is not None:
                usedTo[hit] = True
                pairs.append((fp, tp_[hit]))
            else:
                pairs.append((fp, None))
        # 이미지나 type이 다른 남은 파츠를 순서대로 강제 대응시키면 무기가
        # 몸 파츠로 변하거나, 회전 기준점이 다른 무기의 좌표가 크게 튄다.
        # 정확히 같은 파츠를 찾지 못한 경우에는 현재 원본 파츠를 보간 구간
        # 끝까지 유지하고 다음 원본 모션에서 새 파츠로 전환한다.
        out = []
        for fp, tp in pairs:
            if tp is None:
                out.append(fp)
            else:
                lp = lambda x, y: int(round(x + (y - x) * frac))
                out.append((fp[0] if frac < 0.5 else tp[0], lp(fp[1], tp[1]), lp(fp[2], tp[2]),
                            fp[3] if frac < 0.5 else tp[3]))
        return out

    def getTween(self, a, b, k):
        key = (a, b, k)
        if key in self.tweenIdx:
            return self.tweenIdx[key]
        idx = len(self.newMotions)
        parts = self._tween(a, b, k / 4.0)
        self.newMotions.append(parts)
        self.newMiRaw.append([['IMG_C%d_%d' % (self.n, p[0]), num(p[1]), num(p[2]), p[3]] for p in parts])
        self.newNames.append(None)
        ra, rb = self.newMis[a], self.newMis[b]
        x0, y0 = min(ra[0], rb[0]), min(ra[1], rb[1])
        x1, y1 = max(ra[0] + ra[2], rb[0] + rb[2]), max(ra[1] + ra[3], rb[1] + rb[3])
        r = [x0, y0, x1 - x0, y1 - y0]
        self.newMis.append(r)
        self.newMisRows.append([num(v) for v in r])
        self.newCsRows.append(list(self.newCsRows[a]))
        self.tweenIdx[key] = idx
        return idx

    def nameTweens(self):
        dests = {}
        for (a, b, k) in self.tweenIdx:
            dests.setdefault(a, set()).add(b)
        pre = 'PO_C%d_' % self.n
        used = set(self.motNames)
        for (a, b, k), idx in sorted(self.tweenIdx.items(), key=lambda kv: kv[1]):
            base = self.motNames[a]
            to = self.motNames[b].replace(pre, '').replace('PO_', '')
            # 원본에 이미 같은 이름이 있을 수 있어(c39의 PO_C39_W4_1) 겹치면 다른 후보로 넘어간다.
            if len(dests[a]) > 1:
                cands = ['%s_%s_%d' % (base, to, k), '%s_T%s_%d' % (base, to, k)]
            else:
                cands = ['%s_%d' % (base, k), '%s_T%d' % (base, k), '%s_T%s_%d' % (base, to, k)]
            cands.append('%s_TW%d' % (base, idx))
            for nm in cands:
                if nm not in used:
                    break
            else:
                raise Skip('중간모션 이름을 못 정함')
            used.add(nm)
            self.newNames[idx] = nm
        if not all(self.newNames):
            raise Skip('이름 없는 모션')
        if len(set(self.newNames)) != len(self.newNames):
            raise Skip('모션 이름 중복')

    def render(self):
        n = self.n
        L = ['//*** Generated by Divider ***//', '#pragma once', '#include "../Def.h"', '',
             '#ifndef _C%d_DATA_H_' % n, '#define _C%d_DATA_H_' % n, '',
             '//60프레임 대응 : 원본 키모션(0~%d)은 그대로 두고' % (self.totalMotion - 1),
             '//뒤에 4분할 중간모션을 덧붙였다. 앞쪽 인덱스는 다른 cmf가 참조할 수 있다.',
             'typedef enum _C%d_DEF {' % n, '\t//MOTION']
        for i, nm in enumerate(self.newNames):
            L.append('\t%s\t= %d,' % (nm, i))
        L += ['', '\tTOTALC%dMOTION\t= %d,' % (n, len(self.newNames)), '', '\t//IMAGE']
        for i in range(self.totalOff):
            L.append('\tIMG_C%d_%d\t= %d,' % (n, i, i))
        L += ['', '\tTOTALC%dOFF\t= %d' % (n, self.totalOff), '} C%d_DEF;' % n, '']

        L += ['static const unsigned short c%dOff[] = {' % n, self.offBlock.strip('\n'), '};', '']

        L.append('static const signed short c%dMI[] = {' % n)
        micOut, cur = [], 0
        for i, rows in enumerate(self.newMiRaw):
            L.append('\t//%s' % self.newNames[i])
            for k, r in enumerate(rows):
                L.append('\t%s, %s, %s, %s,\t//%d' % (r[0], r[1], r[2], r[3], cur + k))
            L.append('')
            micOut.append((cur, len(rows)))
            cur += len(rows)
        L += ['};', '']
        if cur > 60000:
            raise Skip('MI %d줄 - MIC unsigned short 한계' % cur)

        L.append('static const unsigned short c%dMIC[] = {' % n)
        for i, (st, c) in enumerate(micOut):
            L.append('\t%d, %d,\t//%d' % (st, c, i))
        L += ['};', '']

        L.append('static const signed short c%dMIS[] = {' % n)
        for i, r in enumerate(self.newMisRows):
            L.append('\t%s, %s, %s, %s,\t//%d' % (r[0], r[1], r[2], r[3], i))
        L += ['};', '']

        L.append('static const signed short c%dCS[] = {' % n)
        for i, b in enumerate(self.newCsRows):
            L.append('\t%s, %s, %s, %s,\t\t%s, %s, %s, %s,\t//%d' % tuple(list(b) + [i]))
        L += ['};', '#endif']
        return '\n'.join(L) + '\n'


# ---------------- cNmv ----------------
def grabMv(n, data):
    return re.search(r'const signed short c%dmv\[\]\s*=\s*\{(.*?)\n\};' % n, data, re.S)


def motionIdMap(cmf, allEnumVals):
    """자기 모션 이름 + 다른 cmf 이름(PO_C3_N0 같은 상호참조)을 인덱스로 푼다."""
    m = {nm: i for i, nm in enumerate(cmf.motNames)}
    for nm, v in allEnumVals.items():
        if nm not in m and v < cmf.totalMotion:
            m[nm] = v
    return m


def parseMv(block, motId):
    t = toks(block)
    states, p = [], 0
    while p < len(t) and t[p] != '-1':
        cnt = val(t[p])
        if cnt is None or cnt <= 0:
            raise Skip('상태 프레임 카운트 %s' % t[p])
        p += 1
        cond = t[p]; p += 1
        if p + cnt * 3 > len(t):
            raise Skip('mv 길이 부족')
        mo = t[p:p + cnt]; p += cnt
        mx = [val(v) for v in t[p:p + cnt]]; p += cnt
        my = [val(v) for v in t[p:p + cnt]]; p += cnt
        if any(v is None for v in mx + my):
            raise Skip('이동폭 못 품')
        for v in mo:
            if v not in motId:
                raise Skip('모르는 모션 %s' % v)
        states.append([cnt, cond, [motId[v] for v in mo], mx, my])
    p += 1
    return states, t[p:]


def loopStates(states, tail):
    """상태전이표에 무조건 탈출(조건 0, 보정 0)이 없으면 순환하는 상태로 본다."""
    hard = set()
    for i in range(0, max(0, len(tail) - 1), 6):
        row = tail[i:i + 6]
        if len(row) < 6:
            break
        s = STATEVAL.get(row[0], val(row[0]))
        if s is None:
            continue
        if row[2] == '0' and row[4] == '0':
            hard.add(s)
    return set(range(len(states))) - hard


def expandStates(cmf, states, loops):
    out = []
    for si, (cnt, cond, mo, mx, my) in enumerate(states):
        runs = []
        for m in mo:
            if runs and runs[-1][0] == m:
                runs[-1][1] += 1
            else:
                runs.append([m, 1])
        newMo = []
        for ri, (m, hold) in enumerate(runs):
            H = hold * 2
            if ri + 1 < len(runs):
                nxt = runs[ri + 1][0]
            elif si in loops and len(runs) > 1:
                nxt = runs[0][0]
            else:
                nxt = None
            if nxt is None or nxt == m:
                newMo += [m] * H
                continue
            b = [int(k * H / 4.0 + 0.5) for k in range(5)]
            for k in range(4):
                span = b[k + 1] - b[k]
                if span > 0:
                    newMo += [m if k == 0 else cmf.getTween(m, nxt, k)] * span
        if len(newMo) != cnt * 2:
            raise Skip('상태 %d 프레임 수 안 맞음' % si)

        def split(arr):
            o = []
            for v in arr:
                if v >= 100 or v <= -100:
                    o += [v, 0]          # 100 이상은 특수명령이라 나누지 않는다
                else:
                    h = v // 2 if v >= 0 else -((-v) // 2)
                    o += [h, v - h]
            return o

        if (cnt * 2) * 3 + 2 > 1024:
            raise Skip('상태 %d 가 cmf_status_data[1024] 를 넘는다' % si)
        out.append([cnt * 2, cond, newMo, split(mx), split(my)])
    return out


def renderMv(n, cmf, newStates, tail, names):
    def wrap(items, per=8):
        return ['\t' + ', '.join(items[i:i + per]) + ',' for i in range(0, len(items), per)]

    body = ['\t//상태 데이터']
    for si, (cnt, cond, mo, mx, my) in enumerate(newStates):
        if si < len(names):
            body.append('\t//%s' % names[si])
        body.append('\t%d,\t//상태 프레임 카운트' % cnt)
        body.append('\t%s,\t//초기화 조건' % cond)
        body += wrap([cmf.newNames[m] for m in mo])
        body[-1] += '\t//상태 프레임별 모션'
        body += wrap([num(v) for v in mx])
        body[-1] += '\t//상태 프레임별 이동폭 X'
        body += wrap([num(v) for v in my])
        body[-1] += '\t//상태 프레임별 이동폭 Y'
        body.append('')
    body.append('\t-1,')
    if len(tail) > 1:
        body += ['', '\t//ACTIONRPG', '\t//상태변경']
        for i in range(0, len(tail) - 1, 6):
            body.append('\t' + ',\t'.join(tail[i:i + 6]) + ',')
    body.append('\t-1,')
    return 'const signed short c%dmv[] = {\n' % n + '\n'.join(body) + '\n};'


def stateNames(block):
    out = []
    for line in block.split('\n'):
        m = re.match(r'\s*//([A-Z][A-Z0-9_]+)\s*$', line)
        if m and m.group(1) != 'ACTIONRPG':
            out.append(m.group(1))
    return out
