# 성 실내 NPC 배치 인수인계

2026-11-04 갱신. 10개 성의 34개 방을 지원한다. 새 실내 이미지의 실제 바닥에 맞춰 `castle_room_integrated_v4/npc_floors.json`을 작성했다. 이전 성의 Sectors 좌표를 발판으로 사용하면 창문·계단 난간 또는 성 바깥에 서게 되므로 재사용하지 않는다. 방 기본 상태와 강화 1~5단계는 동일한 배치 영역을 쓴다.

동료 크기는 `CastleWorldCharZoom` 기준으로 성 사이에 일정하며 주인공 기준 키의 절반이다. `maxHeight`/`maxWidth`를 곱해 방마다 크기를 바꾸지 않는다. 실제 바닥 폭에 들어가는 한 줄만 표시하며, 초과 보유 인원을 가짜 뒷줄에 쌓지 않는다.

## Claude가 사용할 파일

- C++: `Classes/Data/CastleNpcPlacement.h` → `CastleNpcPlacement::Areas[10][5]`
- JSON: `Resources/res/castle_room_upgrades_v3/npc_placement.json`
- 방별 기능·이름: `Classes/Data/CastleFacilities.h`
- 발판 원본: `Resources/res/castle_room_integrated_v4/npc_floors.json`
- NPC 클리핑 영역: 내보낸 JSON의 `clip` 및 `CastleParts::RoomClipScope`의 발판 기반 구역
- 원본 좌표 변경 후 재생성: `python tools/castles/export_npc_placement.py`

`Counts = [1,2,2,3,3,4,4,5,5,5]`. 성과 방 인덱스는 0부터 시작한다. 배열에서 `room < Counts[castle]`인 항목만 유효하다. JSON의 `castle_level`만 사람이 보는 1~10이다.

## 좌표와 필드

성 본체 왼쪽 위가 `(0,0)`, 오른쪽 아래가 `(1,1)`이다. 바퀴·대포·배경 전체 이미지 좌표가 아니다. **발 위치는 캐릭터의 시각적 바운딩 박스 아래 중앙**을 뜻한다.

| C++ 필드 | 의미 |
|---|---|
| `left`, `right` | 발 중심을 놓을 수 있는 가로 범위. 방 양 끝의 기둥에서 여유를 둔다. |
| `foot` | 앞줄의 바닥 기준 Y. 아래 방향이 양수다. |
| `depth` | 뒤쪽으로 발을 이동할 수 있는 깊이. 발의 Y 범위는 `[foot-depth, foot]`. |
| `maxHeight` | 캐릭터 시각적 높이 / 성 본체 높이. |
| `maxWidth` | 캐릭터 시각적 너비 / 성 본체 너비. 가로·세로를 함께 제한하고 비율을 유지한다. |
| `recommended` | 최대 크기로 배치할 때 권장하는 앞줄 인원. 강제 수용 한도가 아니다. |

JSON의 `feet_area`는 같은 범위를 직사각형 `{left, top, width, height}`로 표현한다. `anchors`는 권장 인원을 균등하게 놓은 발 중심 예시 배열이다. `clip`은 NPC 전체를 그릴 때 사용할 기존 방 영역이다. 폭과 높이는 서로 다른 본체 축을 기준으로 하므로 정규화 값끼리 직접 크기를 비교하지 않는다.

## 게임 화면으로 변환

`CastleParts::sdPlacement`의 실제 그리기 위치를 사용한다. 해상도나 로비 줌에 따라 하드코딩하지 않는다. 게임 화면 Y는 위쪽이 양수이므로 정규화 Y를 뺀다.

```cpp
const auto& p = CastleParts::sdPlacement;
const auto& zone = CastleNpcPlacement::Areas[p.castle][room];
float nx = CastleNpcPlacement::SlotX(zone, slot, count);
float ny = zone.foot; // 뒤줄이라면 [foot-depth, foot] 안에서 선택
float screenX = CastleParts::MirrorX(p.left + nx * p.width, 0);
float screenFootY = p.top - ny * p.height;

float maxHeightPx = zone.maxHeight * p.height;
float maxWidthPx = zone.maxWidth * p.width;
// motionBounds는 실제 CMF 모션의 시각적 바운딩 박스.
float zoom = Min(maxHeightPx / motionBounds.height,
                 maxWidthPx / motionBounds.width);
// 원하는 표시 크기가 더 작다면 zoom을 추가로 제한한다.
CastleParts::RoomClipScope clip(true, room);
DrawCmfDetailShadow(cmf, motion, (int)screenX, (int)screenFootY,
                   RIGHT, zoom);
```

`DrawCmfDetailShadow`에는 발 기준 좌표를 전달한다. OBJECT 기반으로 연결할 때는 `ScreenToObj`와 기존 CMF 원점 보정을 확인하고, `CASTLE_ROOM_CREW_LIFT` 같은 기존 오프셋을 발 기준 데이터에 중복 가산하지 않는다.

현재 로비의 NPC 밀도 디버그는 이 배열을 직접 읽는다. 일반 동료의 방 바닥 계산도 동일한 `foot`을 사용한다. 일반 동료의 편성·전투 중 외부 데크 이동·기존 다중 행 수용 정책은 유지했다.

## 배치 규칙

1. 방 인덱스를 검증하고 `SlotX` 또는 JSON `anchors`로 발 좌표를 고른다.
2. 실제 캐릭터 바운딩 박스에 맞춰 크기를 제한한다. 머리와 좌우 끝이 `clip` 안에 들어가는지 확인한다.
3. 실제 `sdPlacement.gunLeft/gunTop/gunWidth/gunHeight`와 캐릭터 바운딩 박스가 겹치면 다른 슬롯을 고른다. 대포는 성·강화 단계·반동에 따라 달라지므로 고정 JSON 좌표로 대체하지 않는다.
4. 가까운 캐릭터와 겹치지 않게 간격을 유지하고, 뒤줄도 `depth` 안에서만 배치한다.
5. 방 사이 이동 경로는 별도 계단/문 연결 데이터가 필요하다. 이 배열은 서 있을 수 있는 영역이며 방 사이 길찾기 메시가 아니다.

방의 기능 순서는 생산 → 장비 연구 → 식음료·공연 → 도서·종교 → 왕실 특화다. 성별 방 수에 해당하는 앞부분만 존재한다. 장비 연구 시설은 강화 시 골드 생산과 아군 공격력이 함께 증가한다.

## 외형 및 검증 자료

- 10개 성·34개 방·6상태, 사용 외형 204개: `Resources/res/castle_room_upgrades_v3/`
- 생성 방식과 전체 프롬프트: 같은 폴더의 `generation.json` (내장 image_gen 사용)
- 사용 이미지 크롭 및 해시: `registration.json`
- 실제 게임 단계별 비교: `reports/art_direction/room_upgrades.html`
- 배열 재생성 검증: `tools/castles/export_npc_placement.py`
- C++ 범위·슬롯·강화 모델 검증: `tools/castles/test_castle_menu.cpp`
- 네 비율의 실제 게임 검증: `tools/castles/verify_room_upgrades.ps1`
