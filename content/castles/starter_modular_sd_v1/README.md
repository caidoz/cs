# 첫 목재성: 통합 원화와 분할 테스트

최신 배치 보정: 사용자의 추가 요청에 따라 절반 폭 샘플보다 10% 확대해 전체 폭 상한을 화면 55%로 변경했다. 바퀴는 레일 기준선에서 8픽셀 내려 닿도록 맞춘다. 방이 닫힌 프레임에서는 내부 동료와 그림자를 아예 그리지 않아 외벽 위/아래로 머리나 발이 새지 않게 했다. 터치 공개 중에도 동료와 그림자를 방 영역에 클리핑한다. 전투 발판으로 나온 동료와 히어로는 이 클리핑에서 제외한다. 업그레이드/혼합 조립 테스트는 닫힘 상태 내부 렌더 0명, 열림 상태 내부 인원 렌더 수 일치도 확인한다.

첫 성 기본 상태와 추가 업그레이드(stage 0~5)의 Debug 테스트용 조립이다. 기존 사용자 변경은 유지했다. 원화/내부는 내장 imagegen으로 생성했고, 사용자가 요청한 정확한 분할과 패키징은 System.Drawing을 사용하는 split_starter_sd.ps1로 수행한다.

2026-10-17 수정: 투석기와 우측 발판을 포함한 전체 폭을 DX의 50% 이하로 제한한다. 바퀴 회전은 레일 누적 이동거리/반지름에 맞춰 계산한다. 크기를 바꿔도 바퀴 접지점은 고정된다. 히어로와 동료 발판/방/발사 원점은 동일 축척과 좌표를 공유한다.

접지 위치 추가 수정: 호출부에서 이미 차감한 기존 바퀴 접지 오프셋과 StageBg의 grounding 보정을 새 조립 경로에서 한 번만 상쇄해, 실제 레일 기준선에 원화의 GroundY를 맞춘다. 히어로 앵커는 원화 X=1200으로 안쪽 이동하고, 스프라이트 발밑 8픽셀 보정을 반영한다. 로비에서 새 바퀴 접지점과 레일 기준선의 오차가 3픽셀 이내인지 업그레이드 검증에 추가했다.

투석기 방향 보정: 원화와 파츠 자체에 돌 받침을 왼쪽, 회전축을 오른쪽에 둔 자세를 반영했다. 런타임에서는 다시 뒤집지 않는다. 돌은 기존 대비 약 1.5배로 확대하고, 파츠에서 검출한 돌 위치를 발사 원점으로 사용한다. 발사 대상은 오른쪽이다. reassembled-game-closed/open.png와 reassembled-closed/open.png 모두 이 최종 자세를 반영한다. 이전 방향 원화는 before-large-rock.png로만 보관한다. 내장 imagegen의 돌 편집 결과를 등록 영역에서 추출하고, 정확한 크기 조정/투석기 반전은 update_starter_rock.ps1에서 수행했다.

업그레이드 비교판: upgrades.html. upgrade-1~upgrade-5에 통합 원화, 내부, 파츠별 좌표, 재조립 및 검증 결과, 생성 프롬프트를 저장했다. 단계마다 철제 보강/장식/투석기/바퀴가 강화되며 첫 성의 목재 재질과 한 개 방 구조는 유지한다. 카테고리별 업그레이드는 지붕, 벽, 방, 투석기/포 받침, 이동부/전투 데크에 각각 대응한다.

## 보기

- assembled-master.png: 캐릭터 없는 닫힌 통합 원화.
- reassembled-closed.png: 분할한 외관의 원본 픽셀 재조립.
- reassembled-open.png: 외관을 고정하고 방 영역만 교체한 내부 상태.
- parts.json: 모든 파츠의 원화 좌표와 PNG/아틀라스 위치.
- partition-check.txt: 해당 단계의 보이는 픽셀 수와 RGBA 불일치 0개 검증 결과. 저장한 PNG를 다시 읽는 검사도 포함한다.
- master-prompt.txt, master-correction-prompt.txt, room-prompt.txt: 내장 imagegen 생성 지시.

## 기존 리소스명 유지

| 리소스 | 내용 |
|---|---|
| castle_exterior/castle_01_roof_stage_0.png | 낮은 망루와 지붕 |
| castle_exterior/castle_01_wall_stage_0.png | 터치로 걷히는 외벽 |
| castle_exterior/castle_01_hollow_stage_0.png | 방 양옆의 고정 구조 |
| castle_exterior/castle_01_cannon_stage_0.png | 우측을 향한 투석기 |
| castle_exterior/castle_01_balcony_stage_0.png | 상부 포 받침과 지지대 |
| castle_exterior/castle_01_combat_deck_stage_0.png | 전체 폭 동료 발판 및 우측 히어로 발판 |
| castle_mobility/castle_01_base_stage_0.png | 하부 차대 |
| castle_mobility/castle_01_wheel_stage_0.png | 원화의 좌/우 바퀴를 별도 영역으로 보관한 아틀라스 |
| castle_room_01_0.png | 같은 외벽 영역에 맞춘 한 개의 방 |

각 단계는 외관 9조각(바퀴 2개 포함) + 방 1개다. 각 PNG는 단순 리사이즈하지 않고 원본 픽셀을 추출한 크기이며, Classes/Data/StarterSdParts.h 및 StarterSdPartsStage1~5.h의 공유 좌표로 조립한다. 전체 방 좌표는 170,535,920,185다. 바퀴는 별도 원형 영역으로 추출해 각각 회전시킨다. 가려진 면 전체를 복원한 자유 이동형 3D 파츠는 아니다.

Release 및 이전 고정 크기 조립 경로는 Resources/res/castle_sd_legacy에 보존한 원래 텍스처 54개와 별도 등록 ID를 사용한다. 원래 리소스 백업은 각 단계 original-resources에도 있다. Debug 첫 성은 카테고리별 0~5단계 파츠와 서로 다른 단계의 혼합 조립을 지원한다.

## 테스트

빌드된 테스트 실행 파일: proj.win32/Debug.win32/cs.starter-modular-preview.exe

사용자가 직접 눌러 보는 격리 샘플 실행:

    powershell -NoProfile -ExecutionPolicy Bypass -File tools/castles/preview_starter_sd.ps1

이 실행은 첫 성 0단계를 고정해 로비에서 시작하며 자동 터치나 장면 전환을 하지 않는다. 외벽을 길게 누르면 내부를 확인할 수 있다.

최대 업그레이드 직접 확인:

    powershell -NoProfile -ExecutionPolicy Bypass -File tools/castles/preview_starter_sd.ps1 -Stage 5

업그레이드 전체 및 혼합 조립 자동 검증:

    powershell -NoProfile -ExecutionPolicy Bypass -File tools/castles/verify_starter_upgrades.ps1

output/starter-upgrades-review에 0~5단계 및 3개 혼합 조립의 닫힌/열린 상태 18장을 저장한다. 폭 50% 제한, 바퀴 회전, 내부 공개, 리소스 영역 및 이전 리소스 로딩을 검사한다.

자동 검증:

    powershell -NoProfile -ExecutionPolicy Bypass -File tools/castles/verify_sd_room_deck.ps1 -Executable proj.win32/Debug.win32/cs.starter-modular-preview.exe

출력: output/sd-room-deck-review. 외관/터치 내부/복원/동료 6명 외부 배치/소환 후 내부 등 5장을 저장한다. 기존 실행 중인 게임이나 사용자 세이브를 수정하지 않는 격리된 검증이다. 9개 신규 조립 리소스와 9개 기존 호환 리소스 로딩, 발판이 전체 폭의 60% 이상인 점, 히어로와 동료 바닥 높이가 같은 점, 실제 전투 오브젝트 좌표도 검사한다.
