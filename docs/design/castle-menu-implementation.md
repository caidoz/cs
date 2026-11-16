# 성 메뉴 구현

하단 성 메뉴는 기존 재화 바·성 리소스·하단 내비게이션을 사용한다. 방 강화는 2×2 블록이며 대포 강화는 가로형 블록이다. 640×850에서는 블록 높이를 줄이되 강화 버튼은 48 이상으로 유지한다. 작은 화면에서 내용이 넘치면 본문만 스크롤하며 내비게이션과 제목 줄은 고정한다.

## 표시 항목과 실제 데이터 연결

| 표시 항목 | 저장 인덱스 | 실제 단계당 효과 | 리소스 |
|---|---|---|---|
| 체력 증가 | rooms[c][2] | 히어로 최대 체력 +6% | 기존 하트 아이콘 |
| 방어력 증가 | rooms[c][3] | 히어로 방어력 +4% | 기존 방패 아이콘 |
| 공격력 증가 | rooms[c][1] | 히어로 공격력 +4% | 기존 검 아이콘 |
| 성 생산력 향상 | rooms[c][0] | 골드 생산 +25%, 저장 한도 +50% | 기존 골드 주머니 아이콘 |
| 대포 공격력 증가 | parts[c][3] | 지원 포격 계수 50/80/110/150/200/250% | 성별·단계별 기존 대포 아틀라스 |

수치는 `Classes/Data/CastleFacilities.h`와 `CastleMenuModel::CannonTurnPercent`에서 읽는다. 적재·배치 업그레이드는 이 화면에 표시하지 않는다. 실제 생산량과 수금액은 현재 출정 성 기준이다.

## 동작

- 블록 전체 또는 큰 강화 버튼을 누르면 현재/다음 효과, 필요/보유 골드가 보이는 강화 확인창을 연다.
- 취소는 재화를 차감하지 않는다. 확인 시 기존 단계·비용·보유 골드를 다시 검사하고 기존 저장 경로로 저장한다.
- 방 강화는 모든 성에 공유되며 대포는 성별로 독립한다. 모든 항목은 Lv.0~5다.
- 비용은 기존 모델을 유지한다. 방은 `240 × (현재 단계 + 1)`, 대포는 `300 × (성 번호 + 1) × (현재 단계 + 1)` 골드다. 성 번호는 0부터 시작한다.
- 디버그에서는 블록을 눌러 0~5단계 외형/효과를 무료로 순환 비교한다. 골드와 저장 데이터는 바꾸지 않는다.

## 소스와 리소스

- `Classes/Data/CastleUpgradeBlocks.h`: 표시 이름, 기존 저장 인덱스 매핑, 화면 높이별 레이아웃.
- `Classes/CastleFourFacilityMenu.inc`: 블록, 기존 아이콘/버튼 리소스 렌더링, 강화 확인창, 본문 스크롤 표시.
- `Classes/CastleMenuFinal.inc`: 본문 영역·스크롤 한도·성 미리보기.
- `Classes/CastleMenuRuntime.inc`: 기존 강화·저장 명령과 시설 바로가기.
- 기존 리소스를 직접 사용하므로 생성형 시안 이미지를 게임 텍스처로 로드하지 않는다. 방 상세는 `Resources/res/castle_four_rooms_v5/rooms-{01..10}.png`, 대포는 기존 inventory cannon atlas를 사용한다.

## 검증 실행

검증용 실행 파일은 `proj.win32/Debug.win32/cs.castle-blocks.exe`다. 아래 Python 검증은 640×850과 640×1408에서 게임을 직접 실행한다.

```
python tools/castles/verify_upgrade_blocks.py
python tools/castles/verify_four_facility_menu.py --exe cs.castle-blocks.exe
python tools/castles/verify_debug_preview.py --exe cs.castle-blocks.exe
```

각 블록 제목 영역의 실제 터치, 다섯 효과 매핑, 취소, 중복 차감 방지, 공유/독립 강화 범위, 최대 단계, 디버그 무료 비교를 검사한다. 실제 서버 저장 왕복은 별도 확인이 필요하다.
