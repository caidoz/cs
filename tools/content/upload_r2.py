# -*- coding: utf-8 -*-
"""매니페스트에 적힌 것을 R2 로 올린다.

    python tools/content/upload_r2.py --env <자격증명파일>
    python tools/content/upload_r2.py --env <...> --dry   #무엇을 올릴지만 본다

자격증명 파일은 이렇게 생겼다. git 에 넣지 말 것.

    R2_ACCOUNT_ID=...
    R2_ACCESS_KEY_ID=...
    R2_SECRET_ACCESS_KEY=...
    R2_BUCKET=...

캐시를 두 갈래로 나눠 건다. 이게 이 스크립트를 따로 두는 이유다.

    version.txt   짧게(60초). 갱신 확인이 이것부터 하므로 늘 새것을 봐야 한다.
    그 밖의 전부  영원히(immutable). 주소에 지문이 붙어 있어서 내용이 바뀌면
                  주소도 바뀐다. 그러니 한 번 받은 것은 다시 받을 이유가 없다.

이미 올라가 있고 크기가 같은 것은 건너뛴다. 다시 돌려도 싸다.
"""
import argparse
import concurrent.futures
import mimetypes
import os
import sys
import threading

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
RES = os.path.join(ROOT, 'Resources')
MANIFEST = 'manifest.tsv'
VERSIONFILE = 'version.txt'

CACHE_FOREVER = 'public, max-age=31536000, immutable'
CACHE_SHORT = 'public, max-age=60'

TYPES = {
    '.png': 'image/png',
    '.mp3': 'audio/mpeg',
    '.ttf': 'font/ttf',
    '.tsv': 'text/plain; charset=utf-8',
    '.txt': 'text/plain; charset=utf-8',
    '.pack': 'application/octet-stream',
}


def read_env(path):
    env = {}

    with open(path, encoding='utf-8') as fp:
        for line in fp:
            line = line.strip()

            if not line or line.startswith('#') or '=' not in line:
                continue

            k, v = line.split('=', 1)
            env[k.strip()] = v.strip()

    need = ['R2_ACCOUNT_ID', 'R2_ACCESS_KEY_ID', 'R2_SECRET_ACCESS_KEY', 'R2_BUCKET']
    missing = [k for k in need if not env.get(k)]

    if missing:
        sys.exit('자격증명이 모자란다: %s' % ', '.join(missing))

    return env


def read_manifest():
    """올릴 목록. (버킷에 놓을 이름, 로컬 경로, 지문) 을 준다."""
    path = os.path.join(RES, MANIFEST)

    with open(path, encoding='utf-8') as fp:
        text = fp.read()

    ver = 0
    items = []

    for line in text.split('\n'):
        line = line.strip()

        if not line or line.startswith('#'):
            continue

        f = line.split('\t')

        if f[0] == 'version':
            ver = int(f[1])
            continue

        if len(f) < 3:
            continue

        items.append((f[0], os.path.join(RES, f[0].replace('/', os.sep)), f[2]))

    if not ver:
        sys.exit('매니페스트에 판번호가 없다')

    return ver, items


def content_type(key):
    ext = os.path.splitext(key)[1].lower()

    if ext in TYPES:
        return TYPES[ext]

    return mimetypes.guess_type(key)[0] or 'application/octet-stream'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--env', required=True, help='자격증명 파일')
    ap.add_argument('--dry', action='store_true', help='올리지 않고 목록만 본다')
    ap.add_argument('--jobs', type=int, default=16, help='동시에 올릴 개수')
    ap.add_argument('--prune', action='store_true',
                    help='매니페스트에 없는 것을 버킷에서 지운다')
    args = ap.parse_args()

    env = read_env(args.env)
    ver, items = read_manifest()

    print('판 %d, 파일 %d개' % (ver, len(items)))

    total = 0
    missing = []

    for key, local, _d in items:
        if os.path.isfile(local):
            total += os.path.getsize(local)
        else:
            missing.append(key)

    if missing:
        sys.exit('로컬에 없는 파일이 %d개다. 첫 번째: %s' % (len(missing), missing[0]))

    print('합계 %s 바이트' % format(total, ','))

    if args.dry:
        print('--dry 라 여기서 멈춘다')
        return 0

    import boto3
    from botocore.config import Config

    s3 = boto3.client(
        's3',
        endpoint_url='https://%s.r2.cloudflarestorage.com' % env['R2_ACCOUNT_ID'],
        aws_access_key_id=env['R2_ACCESS_KEY_ID'],
        aws_secret_access_key=env['R2_SECRET_ACCESS_KEY'],
        region_name='auto',
        config=Config(retries={'max_attempts': 5, 'mode': 'standard'},
                      max_pool_connections=args.jobs + 4))

    bucket = env['R2_BUCKET']

    #이미 올라가 있는 것을 미리 훑는다. 하나씩 물어보면 왕복이 903번이다.
    have = {}
    token = None

    while True:
        kw = {'Bucket': bucket, 'MaxKeys': 1000}

        if token:
            kw['ContinuationToken'] = token

        page = s3.list_objects_v2(**kw)

        for o in page.get('Contents', []):
            have[o['Key']] = o['Size']

        if not page.get('IsTruncated'):
            break

        token = page.get('NextContinuationToken')

    print('버킷에 이미 %d개 있다' % len(have))

    #무엇을 다시 안 올려도 되는가.
    #
    #크기로 거르면 안 된다. 팩은 값을 고쳐도 크기가 그대로인 일이 흔하다
    #(칸 수가 안 변하니까). 그러면 매니페스트는 새 지문을 적어 내보내는데
    #CDN 은 옛 파일을 들고 있게 되고, 받는 쪽은 지문이 안 맞는 파일을
    #영영 다시 받는다.
    #
    #그래서 버킷에 놓인 매니페스트를 한 번 받아, 지문이 같은 것만 건너뛴다.
    #왕복 한 번이면 902개를 정확히 가릴 수 있다.
    remote = {}

    try:
        got = s3.get_object(Bucket=bucket, Key=MANIFEST)['Body'].read()

        for line in got.decode('utf-8').split('\n'):
            f = line.strip().split('\t')

            if len(f) >= 3 and f[0] != 'version':
                remote[f[0]] = f[2]

        print('버킷의 매니페스트에 %d개 적혀 있다' % len(remote))
    except Exception:
        #매니페스트가 없으면 빈 버킷으로 본다. 다 올린다.
        print('버킷에 매니페스트가 없다. 전부 올린다')

    lock = threading.Lock()
    done = [0]
    skipped = [0]
    failed = []

    def put(key, local, digest):
        if key in have and remote.get(key) == digest:
            with lock:
                skipped[0] += 1
            return

        try:
            with open(local, 'rb') as fp:
                s3.put_object(Bucket=bucket, Key=key, Body=fp,
                              ContentType=content_type(key),
                              CacheControl=CACHE_FOREVER)
        except Exception as e:
            with lock:
                failed.append((key, str(e)))
            return

        with lock:
            done[0] += 1

            if done[0] % 100 == 0:
                print('  %d개 올림' % done[0])

    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        list(ex.map(lambda t: put(t[0], t[1], t[2]), items))

    #매니페스트에 없는 것을 치운다.
    #
    #안 지우면 지난 판의 파일이 버킷에 영영 쌓인다. 주소에 지문이 붙어 있어서
    #누가 그것을 다시 받을 일은 없지만, 저장료를 계속 문다.
    if args.prune:
        keep = set(k for k, _l, _d in items)
        keep.add(MANIFEST)
        keep.add(VERSIONFILE)

        junk = [k for k in have if k not in keep]

        for at in range(0, len(junk), 1000):
            batch = junk[at:at + 1000]
            s3.delete_objects(Bucket=bucket,
                              Delete={'Objects': [{'Key': k} for k in batch]})

        if junk:
            print('버킷에서 %d개 치웠다: %s%s'
                  % (len(junk), ', '.join(junk[:3]),
                     ' ...' if len(junk) > 3 else ''))

    #매니페스트는 마지막에 올린다. 이게 올라가야 "그 판이 준비됐다"는 뜻이다.
    with open(os.path.join(RES, MANIFEST), 'rb') as fp:
        s3.put_object(Bucket=bucket, Key=MANIFEST, Body=fp,
                      ContentType=TYPES['.tsv'], CacheControl=CACHE_FOREVER)

    #약관. 콘텐츠가 아니라 서비스 쪽 파일이라 매니페스트에 안 들어간다.
    #
    #계정을 만들기 전에 봐야 하는 것이라 CDN 에 둔다. 서버에 물으면 로그인
    #전에는 자격증명이 없고, 부팅마다 물으면 백만 명이 백만 번 묻는다.
    terms = os.path.join(ROOT, 'server', 'terms.tsv')

    if os.path.isfile(terms):
        with open(terms, 'rb') as fp:
            s3.put_object(Bucket=bucket, Key='terms.tsv', Body=fp,
                          ContentType=TYPES['.tsv'], CacheControl=CACHE_SHORT)

        print('약관도 올렸다')

    #약관 전문과 확률 정보. 게임 안 설정 메뉴에서 웹뷰로 연다.
    #
    #확률 정보는 게임 밖에서도 볼 수 있어야 한다(게임산업법 시행령). 그래서
    #스토어 소개와 홈페이지가 가리킬 주소가 필요하고, 그 주소가 여기다.
    #
    #짧게 캐시한다. 약관은 고치는 일이 드물지만, 고쳤는데 엣지가 옛것을
    #들고 있으면 동의를 받아놓고 다른 글을 보여주는 꼴이 된다.
    for name in ('terms.html', 'privacy.html', 'rates.html'):
        path = os.path.join(ROOT, 'server', 'web', name)

        if not os.path.isfile(path):
            continue

        with open(path, 'rb') as fp:
            s3.put_object(Bucket=bucket, Key=name, Body=fp,
                          ContentType='text/html; charset=utf-8',
                          CacheControl=CACHE_SHORT)

        print('%s 올렸다' % name)

    #판번호는 맨 마지막이다. 클라이언트는 이것부터 보므로, 이게 바뀌는 순간
    #모두가 새 판을 보러 온다. 나머지가 다 올라간 뒤여야 한다.
    s3.put_object(Bucket=bucket, Key=VERSIONFILE,
                  Body=('%d\n' % ver).encode('utf-8'),
                  ContentType=TYPES['.txt'], CacheControl=CACHE_SHORT)

    print('올림 %d개 / 건너뜀 %d개 / 실패 %d개' % (done[0], skipped[0], len(failed)))

    for key, err in failed[:5]:
        print('  실패: %s — %s' % (key, err[:80]))

    if failed:
        return 1

    print('끝. 판 %d 가 올라갔다' % ver)
    return 0


if __name__ == '__main__':
    sys.exit(main())
