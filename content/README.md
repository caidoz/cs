# 콘텐츠 id 계약

`content/ids/*.tsv`는 **계약 문서**다. 코드에서 뽑아낸 참고자료가 아니라, 지켜야 할 약속을 적어둔 것이다.

---

## 왜 계약인가

이 게임에서 콘텐츠의 정체성은 **열거 안에서의 위치**다.

```c
ENEMY_SNAIL = 3,   // 가시껍질달팽이
ENEMY_TREE,        // 늪의 주인   -> 4
ENEMY_ONEEYE,      // 아이볼      -> 5
```

`ENEMY_TREE`와 `ENEMY_ONEEYE` 사이에 한 줄을 끼우면 그 뒤 425마리의 번호가 전부 한 칸씩 밀린다. 그리고 그 번호는 이미 **바깥으로 나갔다**:

| 어디에 | 무엇으로 |
|---|---|
| 세이브 파일 | `battle_enemy.enemy_type`, `crew_slot.crew_type`, `inventory.item_type/detail` |
| 서버 DB | 위와 같은 컬럼 (`server/schema.sql`) |
| 플레이어 기기 | 이미 저장된 모든 세이브 |

즉 번호가 밀리면 **누군가의 슬라임이 해골로 바뀐다.** 코드를 되돌려도 이미 나간 세이브는 되돌아오지 않는다.

## 규칙 세 개

1. **중간에 끼우지 않는다.** 새 콘텐츠는 항상 목록 맨 끝에.
2. **번호를 재사용하지 않는다.** 지운 자리에 새것을 넣지 않는다.
3. **폐기는 행을 지우지 말고 `alive=0`으로.** 번호를 살려둬야 옛 세이브를 읽을 수 있다.

## 지금 박제된 것

| 표 | 개수 | id 범위 | 출처 |
|---|---|---|---|
| `enemy.tsv` | 428 | 3 ~ 430 | `Def/EnemyDef.h` |
| `crew.tsv` | 64 | 0 ~ 63 | `Config/GameConfig.h` |
| `castle.tsv` | 19 | 0 ~ 18 | `Def/CastleDef.h` |
| `skill.tsv` | 1374 | 0 ~ 1373 | `Def/SkillDef.h` |

몬스터 id가 3부터인 것은 원래 그렇다. 이 번호는 `OBJECT.type`이고 **0~2번은 히어로**(ROBIN 검사 / DIANA 거너 / MAXX 헌터)가 쓴다. `enemyData` 같은 배열도 0번부터 잡혀 있어서 앞 세 행에 히어로 값이 들어 있다.

---

## 검사 도구

```bash
python tools/content/dump_ids.py --check    # 검사만. 어긋나면 종료코드 1
python tools/content/dump_ids.py            # 검사 + 표 갱신(안전할 때만)
python tools/content/dump_ids.py --accept   # 어긋난 것을 알면서도 갱신
```

**빌드 전이나 CI에서 `--check`를 돌리면 된다.** 어긋나면 커밋을 막아야 한다.

### 값을 어떻게 아는가

C 열거는 암묵적 증가, 명시적 대입, 다른 열거 참조, `#ifdef` 분기가 섞여 있다. 파이썬으로 그 의미론을 흉내내면 언젠가 반드시 어긋난다.

그래서 흉내내지 않는다. **이름만 긁어서 값을 찍는 작은 프로그램을 만들고, 실제 컴파일러로 빌드해 실행한다.** 정의상 틀릴 수가 없다.

### 두 가지를 따로 본다

**1. 번호가 밀렸는가** — 박제된 표와 지금 소스를 대조한다.

**2. 데이터가 따라왔는가** — 배열의 초기값 개수가 기대 길이와 맞는지 센다.

```
enemyData            OK   기대 3448  실제 3448
enemyStatInfo        OK   기대 1293  실제 1293
enemyZoom            OK   기대 431   실제 431
enemyIconZoom        OK   기대 431   실제 431
enemyBossZoom        OK   기대 431   실제 431
enemyAttackPattern   OK   기대 8620  실제 8620
crewData             OK   기대 384   실제 384
skillData            OK   기대 39846 실제 39846
```

둘째 검사가 특히 중요하다. 몬스터를 하나 추가하면서 배열 12개 중 하나를 빠뜨려도 **컴파일은 그냥 된다.** 그 상태로 나가면 그 배열부터는 전 몬스터가 한 칸씩 밀린 값을 읽는다.

### 실제로 잡히는지 확인한 결과

`ENEMY_ONEEYE` 앞에 몬스터를 하나 끼워 넣고 돌려봤다.

```
exit=1
!! id 5 가 ENEMY_ONEEYE 에서 ENEMY_TESTMONSTER 로 바뀌었다
!! id 6 가 ENEMY_SKELETON 에서 ENEMY_ONEEYE 로 바뀌었다
... (426곳)

enemyData   틀림  기대 3456  실제 3448   <-- -8
enemyZoom   틀림  기대 432   실제 431    <-- -1
6개 배열의 길이가 안 맞는다.
```

두 검사가 각각 독립적으로 잡아낸다.

---

## 몬스터 하나를 추가하려면 (지금 기준)

목록 **맨 끝**에 이름을 붙이고, 아래 **11곳**에 값을 하나씩 더한다.

| 파일 | 배열 | 한 마리가 쓰는 칸 |
|---|---|---|
| `Data/EnemyData.h` | `enemyData` | 8 |
| | `enemyStatInfo` | 3 |
| | `enemyAttackPattern` | 20 |
| | `enemyZoom` `enemyIconZoom` `enemyBossZoom` | 1씩 |
| `Data/UIData.h` | `crewPos` | 5 |
| | `enemyBigIconPos` `enemySkillIconPos` | 3씩 |
| `Data/HeroData.h` | `monXYGap` | 2 |
| `Def/TextDef.h` + `Text.h` | 이름 문자열 | 1 |

숫자 칸만 **47개**다.

`attackDelayFrame`은 이름 때문에 몬스터 배열처럼 보이지만 아니다. 원소가 3개뿐인 **히어로** 배열이다(`ROBIN/DIANA/MAXX`). `Func_Movement.cpp`에 `attackDelayFrame[pObj->type]`로 쓰인 곳이 있는데, `pObj->type != ROBIN ||` 가 앞에 있어서 단축평가로 항상 0번만 읽는다. 우연히 안전하지만 읽는 사람을 헷갈리게 한다.

## 이제는 `content/*.tsv` 가 원본이다 (B단계 완료)

아래 배열들은 **`content/` 의 tsv에서 생성된다.** 헤더를 손으로 고치지 말 것.

| 표 | 행 | 컬럼 | 담당 배열 |
|---|---|---|---|
| `content/enemy.tsv` | 431 | 50 | 10개 (`enemyData` `crewPos` `monXYGap` …) |
| `content/crew.tsv` | 64 | 9 | `crewData` |
| `content/skill.tsv` | 1374 | 32 | `skillData` |

```bash
python tools/content/content_table.py --all verify        # CI용
python tools/content/content_table.py enemy generate --write
python tools/content/content_table.py skill extract       # 헤더 -> tsv (이주용)
```

`verify`가 **59,443칸을 한 칸씩** 대조한다. 누가 헤더를 손으로 고치면 여기서 걸린다.

### 왜 스킬까지 표로 만들었나

몬스터 428마리가 스킬을 3개씩 쓴다(1284개). **몬스터를 추가하면 스킬도 같이 늘어난다.** `skillData`는 1374행 × 29컬럼 = 39,846칸으로 게임에서 가장 큰 표인데, 그중 6~20번 칸이 레벨 1~15의 값이고 27번이 아이콘이다. 번호로만 보면 아무도 못 읽는다. 이제 `lv1`~`lv15`, `icon`, `kind` 같은 이름이 붙는다.

`crew`는 배열이 `crewData` 하나뿐이라 급하지 않지만, 동료가 어떤 몬스터 그림을 쓰고 어떤 스킬 3개를 가지는지가 한 줄에 보이므로 같이 만들었다.

### 값 규칙

칸 수가 맞는 것과 값이 쓸 만한 것은 다른 문제다. `verify`는 대조가 끝난 뒤 값 자체도 본다. 어긋나면 게임이 죽거나 눈에 띄게 망가지는 것만 규칙으로 둔다.

| 컬럼 | 규칙 | 왜 |
|---|---|---|
| `pose_frames` | 0이면 안 됨 | `frame % crewPos[type*5+1]` 로 나눗셈에 쓰인다. 0이면 죽는다 |

```
값 규칙
  pose_frames      1행 위반 : 0이면 안 된다. ...
      id 3    ENEMY_SNAIL              = '0'
```

규칙은 새 크래시를 만날 때마다 늘리면 된다. 크래시 하나를 고치고 그 조건을 여기 적어두면 같은 크래시가 다시 나올 수 없다.

### 값을 바꾸는 절차

1. `content/enemy.tsv` 에서 해당 행의 칸을 고친다
2. `generate --write`
3. 빌드

값은 **소스에 적힌 글자 그대로** 담겨 있다(`CMF_SNAIL`, `TSIZE * 3`, `1.0f`, `PO_C3_N0`). 숫자로 바꾸지 않으므로 읽고 고칠 수 있다.

### 아직 tsv가 다루지 않는 것

새 콘텐츠를 추가할 때 **열거 이름(`Def/*.h`)과 이름 문자열(`Text.h`)은 여전히 손으로** 넣어야 한다. tsv는 숫자 칸만 담당한다. 그 둘까지 생성하려면 `TEXTDEF` 열거와 `textId[]` 배열을 함께 생성해야 하는데, 그건 텍스트 전체를 건드리는 별도 작업이다.

### 생성을 거부하는 경우

배열 본문 안에 `#ifdef` 같은 전처리 분기가 있으면 생성하지 않고 멈춘다. 생성하면 조건부가 통째로 사라지기 때문이다. 지금 대상 배열 12개에는 없지만, 나중에 누가 넣으면 여기서 걸린다.

---

## 작업 중 발견한 것

### crewPos 색인 두 곳이 틀렸다

`crewPos`의 stride는 5인데 두 곳이 다르게 읽고 있었다. 나머지 24곳은 정상이다.

**`Func_Menu.cpp` 웨이브 보스 — 고쳤다**

```c
// 전
frame / 4 % crewPos[stageBossType * CREWDATASIZE]
// 후
crewPos[stageBossType * 5 + 0] + (frame / 4 % crewPos[stageBossType * 5 + 1])
```

`CREWDATASIZE`는 `crewData`의 칸수(6)라 5칸짜리 이 배열에는 맞지 않는다. 엉뚱한 칸을 읽었고, 대기 모션의 첫 장을 더하지도 않았다. 게다가 **읽은 값이 0이면 `% 0` 이라 정수 나눗셈으로 죽는다.** 지금 보스 18종에서는 0이 안 나와 터지지 않았을 뿐이다.

고친 식은 같은 파일 108번 줄과 `Func_Bar.cpp` 등 나머지 24곳이 쓰는 것과 같다.

`pose_frames`(나눗셈 대상)는 431행 전부 0이 아님을 확인했다. 값 분포는 `4`가 381개, 그 외 `1 3 6 7 8 12 17`. 앞으로 0이 들어오면 아래 **값 규칙**이 잡는다.

**`Func_Menu.cpp:96`** — `crewPos[<cmf 값>]`  ← 아직 안 고침
`* 5 + 0` 없이 cmf로 바로 색인한다. 크래시는 없고 엉뚱한 모션이 나온다.

### crewPos의 5칸 중 3칸은 아무도 안 읽는다

코드가 읽는 것은 `+0`(대기 모션)과 `+1`(모션 장수)뿐이다. `+2`, `+3`은 전부 `0 * _2X`이고 `+4`는 `CASTLE_*`인데 읽는 곳이 없다. 지금은 그대로 두었다 — 칸을 줄이면 stride가 바뀌어 색인식을 전부 손봐야 한다.

### attackDelayFrame 은 몬스터 배열이 아니다

이름 때문에 그렇게 보이지만 원소가 3개뿐인 히어로 배열이다(`ROBIN/DIANA/MAXX`). `Func_Movement.cpp:3780`에 `attackDelayFrame[pObj->type]`로 쓰인 곳이 있는데, `pObj->type != ROBIN ||` 가 앞에 있어 단축평가로 항상 0번만 읽는다. 우연히 안전하지만 읽는 사람을 속인다.

## 데이터로 되는 것과 코드가 필요한 것

`ENEMYDATA_MOVEHANDLER` / `ENEMYDATA_DRAWHANDLER`가 이미 데이터 컬럼이다. 고를 수 있는 행동이 **이동 90개, 그리기 20개**다.

- **기존 행동을 재사용하는 새 몬스터** → 데이터만. 코드 변경 없음.
- **새 행동이 필요한 몬스터** → 핸들러 함수를 새로 써야 한다. 코드 변경.

기존 몬스터에는 `case ENEMY_XXX:` 특수 분기가 **353군데** 박혀 있다. 새 콘텐츠를 데이터만으로 넣으려면 그 분기에 걸리지 않는 범위에서 설계해야 한다. 기획 단계에서 이 경계를 먼저 정해야 헛돌지 않는다.
