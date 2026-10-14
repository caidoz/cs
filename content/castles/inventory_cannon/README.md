# 인벤토리 대포 공용 리소스

성 10종 × 시각 등급 6종 = 60개. 테마와 실루엣을 새로 설계한 `master_v2.png`를 패킹한다. 이전 `master.png`도 보존한다. 행과 열 사이의 투명 영역을 찾아 분리하고 이웃 셀의 떨어진 픽셀은 연결 성분으로 제거한다. 비율을 유지한 최근접 보간으로 축소하며, 최종 리소스는 48색 이하·이진 알파(0/255)의 픽셀 아트다.

등급마다 같은 크기로 정규화하던 처리를 없앴다. 그림의 최대 너비를 36→46→58→68→78→90픽셀로, 최대 높이를 28→34→42→48→54→58픽셀로 늘린다. 모든 성에서 단계별 실제 그림 면적 증가를 검사한다.

| 성 | 테마와 실루엣 |
|---|---|
| 1 | 목재·철제 투석기, 바위와 투척 암 |
| 2 | 검정·빨강 화염방사기, 연료 탱크와 버너 |
| 3 | 올리브색 다연장 로켓, 사각 발사관 묶음 |
| 4 | 황동 개틀링, 회전 포신과 탄띠 |
| 5 | 흰색·청록 유도미사일, 미사일 레일과 레이더 |
| 6 | 검정·진홍 공성포, 거대 포신과 반동 피스톤 |
| 7 | 하늘색·은색 빙결 수정포, 뾰족한 얼음 결정 |
| 8 | 검정·보라 레이저포, 렌즈와 집광 장치 |
| 9 | 구리·청록 테슬라 전격포, 수직 코일과 전극 |
| 10 | 감청·금색 중력포, 구체와 동심원 안정화 장치 |

## 크기와 등급

한 칸은 32×32픽셀이다. 등급 0~2는 2×2칸(64×64), 등급 3~5는 3×2칸(96×64)이다. 성 번호는 1~10이고 파일의 단계는 0~5다.

| 이미지 단계 | 아이템 등급 값 | 점유 칸 |
|---|---|---|
| 0 | NORMAL | 2×2 |
| 1 | SUPERIOR | 2×2 |
| 2 | RARE | 2×2 |
| 3 | SET | 3×2 |
| 4 | EPIC | 3×2 |
| 5 | LEGEND | 3×2 |

현재 성 업그레이드 메뉴는 같은 단계 값을 Lv.0~5로 사용한다. 아이템 등급과 성 파츠 레벨이 서로 자동으로 변경되는 기능은 추가하지 않는다.

## 파일과 사용법

- 개별 PNG: `Resources/res/inventory_cannon/castle_01_lv_0.png`부터 `castle_10_lv_5.png`까지.
- 런타임 공용 아틀라스: `Resources/res/inventory_cannon/atlas.png` (576×640).
- 크기·등급·점유 마스크·영역: 같은 폴더의 `manifest.json`.
- C++ 조회: `Classes/Data/InventoryCannonSprites.h`의 `InventoryCannons::Get(castle, tier)`. 인자는 모두 0부터 시작한다. `cols`, `rows`, `cells`로 인벤토리 점유를 확인한다. 마스크는 기존 4비트 행 간격으로 2×2=`0x33`, 3×2=`0x77`이다.
- 공용 렌더러: `DrawInventoryCannonIcon(castle, tier, x, yTop, width, height)`. 비율을 유지해 중앙에 그린다.
- 작은 상점 칸은 `DrawInventoryCannonThumbnail`로 투명 여백을 제외한 몸체를 맞춘다. 인벤토리와 업그레이드 화면은 등급별 크기 차이를 유지한다.
- 성 장착 파츠도 동일 아틀라스를 사용한다. `bodyRect`를 기준으로 밑면을 지휘대에 맞추고, 테마별 `muzzle` 좌표를 포격 이펙트에 사용한다. 이전 외장 대포 그림은 이 경로에서 더 이상 그리지 않는다.
- 별도 파츠 PNG: `Resources/res/castle_cannon_v2/`의 60개 파일. 같은 픽셀 몸체를 정확히 2배 확대한 이미지이며 독립적인 재디자인은 없다.
- 이미지 번호: `INVENTORY_CANNON_ATLAS_IMG`. `Text.h` 파일명과 `Core::init`의 이미지/텍스처 로딩을 함께 등록했다.
- 성 상세의 대포 업그레이드 화면에서 현재/다음 단계 아이콘과 점유 크기를 비교한다.
- 전체 미리보기: `preview.png`.

재생성 및 자산 검증:

```powershell
& "$env:LOCALAPPDATA/Python/bin/python.exe" tools/castles/build_inventory_cannons.py
```

60개 PNG의 크기, 0/255 알파, 팔레트 제한, 점유 마스크, 아틀라스 일치 및 단계별 몸체 면적 증가를 검사한다. 상점은 장비 2칸·동료 1칸·기타 아이템 1칸·대포 1칸으로 구성하며 대포의 구매·격자 배치·보관·판매는 기존 드래그 경로를 사용한다. 대포는 이번 판의 격자 오브젝트이며 영구 아이템 번호에는 추가하지 않는다. 성 포격은 기존 성 대포 전투 경로를 유지한다.

## Mounted proportions and projectile upgrades

The gravity cannon uses gravity_sideview.png: all six levels face right. Mounted cannons compensate early levels with scale factors 1.75, 1.50, 1.30, 1.16, 1.07, 1.00, while inventory sprites preserve their increasing physical sizes. All mounted bodies and muzzle positions come from the shared atlas.

Projectiles reuse the existing animated attack atlas. Upgrade levels 0–5 scale projectiles and impacts by 0.45, 0.55, 0.65, 0.78, 0.90, 1.05; laser thickness grows from 10 to 25 logical pixels. Higher levels add visual trails. Each shot preserves its launch upgrade level; these visual changes do not add damage or hits. Cooldown is drawn below the mounted cannon base.

All ten castles place artillery on the lower command platform at local y=-72, matching the commander and combat crew foot height. The left body edge starts 32 screen pixels right of the commander anchor (local x=600). Each themed platform extends to support its upgraded cannon body; camera bounds, menu centering, part anchors, muzzle and cooldown all follow the same placement. Castle 1 keeps its 1.30 catapult scale factor. No separate elevated pedestal or upper wall mount remains.
