[Current display policy](../fixed-width-layout.md)

# 네 번째 현무암 요새 · 기본형과 업그레이드 1~5

내장 imagegen으로 생성한 통합 외관과 네 방의 내부 원화다. 각 단계의 `master-prompt.txt`, `room-prompt.txt`가 최종 생성 지침이다. 앞선 세 성과 같은 밝은 SD 입체 채색을 유지하되, 반복적인 벽 패널과 뾰족한 탑 대신 넓은 녹청 돔, 검은 현무암 곡면 방벽, 구리 보강재와 큰 거북 방패를 사용했다. 주포는 오른쪽을 향한 하나의 개틀링 포탑이며 여러 총열이 하나의 본체와 받침에 결합되어 있다.

## 확인할 이미지

- `upgrades.html`: 기본형~5단계 외관/내부 전환과 실제 게임 화면.
- `upgrade-overview.png`, `room-overview.png`: 6단계 외관/내부 비교.
- `castle-01-04-comparison.png`: 첫 네 성을 같은 폭과 바퀴 접지선에 놓은 높이·건축 비교.
- 기본형은 현재 폴더, 업그레이드는 `upgrade-1`~`upgrade-5`에 저장한다.
- `generated-master.png`: 생성 원본. `assembled-master.png`: 공통 좌표에 등록한 통합 외관.
- `interior-source.png`: 방 4개를 그린 원본. 외부 픽셀은 재사용하지 않는다.
- `reassembled-game-closed.png`, `reassembled-game-open.png`: 실제 파츠로 재조립한 외관/내부.
- `parts.json`, `partition-check.txt`: 파츠 좌표와 저장한 PNG를 다시 읽어 수행한 검증. 보이는 외관 픽셀의 RGBA 불일치 0개.

투명 영역은 실제 배경색 위에 합성해 검사했다. 외곽의 투명 픽셀에 남은 RGB 색상은 보이는 배경이 아니며, 재조립 이미지에서는 보이지 않는 픽셀의 색도 비운다. 게임에서는 성과 포탑의 물리적 윤곽만 합성된다.

## 구조와 규격

1024×1536 공통 원화 좌표를 사용한다. 바퀴 축은 `(260,1370)`, `(690,1370)`, 분할 반지름은 102, 접지 기준은 Y=1472다. 전체 폭 동료 발판과 별도의 오른쪽 히어로 발판은 Y=1220 보행면을 공유한다. 히어로는 X=860, 주포 발사점은 `(995,880)`이다. 원화 외관을 먼저 만든 뒤 지붕, 벽, 중공 구조, 개틀링, 포대 받침, 전투 발판, 차대, 좌우 바퀴의 외관 9조각과 내부로 분할했다. 바퀴는 레일 이동 거리/반지름으로 각각 회전한다.

내부 개구부는 `(180,380,480,800)`이며, 위에서부터 지휘실·침실·무기 작업실·주방을 높이 200씩 배치한다. 생성된 네 방의 바닥선을 각각 고정 칸에 맞춰 등록한다. `register_fourth_sd.ps1`은 생성 원본을 보존하고 3단계 원화의 바퀴 위치를 30px 아래로 맞춘다. `split_fourth_sd.ps1`은 등록된 외관의 색을 다시 그리지 않고 정확히 나눈다.

기존 `castle_04_roof`, `wall`, `hollow`, `heavy_cannon`, `command_platform`, `combat_deck`, `base`, `wheel`의 stage 0~5 파일명을 유지한다. 네 방은 기존 `castle_room_04_0~5.png`에 공통 내부 아틀라스로 저장한다. 지붕·벽(중공 포함)·내부·주포(받침 포함)·이동부(발판/차대/바퀴)의 레벨을 독립적으로 섞을 수 있다. 기존 리소스 54개는 `original-resources` 및 `Resources/res/castle_sd_fourth_legacy`에 보존하고 별도 이미지 ID/이름으로 등록했다. Release와 기존 크기 조립 및 상위 성이 공유하는 방은 보존 리소스를 사용한다.

## 게임 적용

Debug의 첫 네 성에 SD 조립을 연결했다. 폭 상한은 기존 요청의 화면 55%다. 네 번째 성은 로비 상단 정보 영역과 전투 준비 화면의 가용 높이에 맞춰 성·히어로·동료를 함께 줄인다. 공간이 충분해지면 원래 배율로 복귀한다. 투명한 잡음 픽셀이 배율에 영향을 주지 않도록 네 번째 성의 상단은 실제 불투명 외관 기준으로 계산한다. 왼쪽도 화면 안에 여백을 확보한다. 바퀴 접점은 기존 레일 기준보다 8px 내려 맞춘다.

닫힌 방의 동료와 그림자는 아예 그리지 않는다. 터치 중에는 기존 두 배 반경으로 내부를 공개하며, 동료를 네 층에 나눠 층별로 클립한다. 전투 발판에 나온 동료는 외벽 앞에서 그린다.

## 실행과 검증

```powershell
powershell -ExecutionPolicy Bypass -File tools/castles/preview_fourth_sd.ps1 -Stage 0
powershell -ExecutionPolicy Bypass -File tools/castles/preview_fourth_sd.ps1 -Stage 5
powershell -ExecutionPolicy Bypass -File tools/castles/verify_fourth_upgrades.ps1
```

미리보기는 격리된 저장 경로를 사용한다. 기본 실행 파일은 `proj.win32/Debug.win32/cs.fourth-modular-preview.exe`이며, 검증 로그와 캡처는 `output/fourth-upgrades-review`에 있다. 검증은 6단계와 혼합 조합 3개, 리소스 로딩/범위, 폭·상단·좌우 범위와 접지, 바퀴 회전, 주포 방향, 닫힘/공개 시 내부 인원 렌더 수, 실제 전투 동료의 발판 좌표를 확인한다.
