[Current display policy](../fixed-width-layout.md)

# 세 번째 화강암 요새 · 기본형과 업그레이드 1~5

내장 imagegen으로 외관과 내부 원화를 생성했다. 각 단계의 `master-prompt.txt`, `room-prompt.txt`가 최종 생성 지침이다. 처음 두 성과 같은 SD·부드러운 입체 채색을 유지하되, 사용자 피드백에 따라 반복적인 벽 패널과 둥근 탑의 대칭 배치를 버리고 건축 구성을 바꿨다.

왼쪽 사각 감시탑, 후퇴한 중앙 석벽, 큰 성문 아치, 오른쪽의 경사진 버팀벽과 돌출 포대로 연결되는 비대칭 요새다. 화강암·파란 지붕·은색 교차검 문양을 쓰며, 무기는 오른쪽을 향한 하나의 다연장 로켓 발사대다. 내부는 위층 침실, 중간층 무기 작업실, 아래층 주방의 방 3개다. 같은 폭에서 두 번째 성보다 높다.

## 이미지 확인

- `upgrades.html`: 6단계 외관/내부 전환 및 실제 게임 캡처 링크.
- `upgrade-overview.png`, `room-overview.png`: 기본형~5단계 비교.
- `castle-01-03-comparison.png`: 첫 세 성을 같은 폭·바퀴 접지선에 놓은 건축/높이 비교.
- 기본형은 현재 폴더, 업그레이드는 `upgrade-1`~`upgrade-5`에 있다.
- `generated-master.png`: 생성 원본. `assembled-master.png`: 1133×1388 공통 좌표에 등록한 외관.
- `interior-source.png`: 세 방을 그린 원본. 외부 픽셀은 재사용하지 않는다.
- `reassembled-game-closed.png`, `reassembled-game-open.png`: 실제 파츠로 재조립한 닫힘/내부 상태.
- `parts.json`, `partition-check.txt`: 파츠 좌표와 저장된 PNG 재로딩 검증. 보이는 외관 픽셀의 RGBA 불일치 0개.

## 규격과 파츠

현재 파일명을 유지해 `castle_03_roof`, `wall`, `hollow`, `heavy_cannon`, `command_platform`, `combat_deck`, `base`, `wheel`의 stage 0~5 리소스를 교체했다. 좌우 바퀴를 각각 분리해 외관 9조각을 조립하며, 기존 `castle_room_03_0~5.png`에는 세 방을 함께 담는다. 지붕·성벽(중공 포함)·내부·주포(받침 포함)·이동부(발판/차대/바퀴)의 서로 다른 업그레이드 레벨을 혼합할 수 있다.

원화 규격은 1133×1388, 바퀴 축은 `(274,1222)`, `(724,1222)`, 반지름 99, 접지 Y=1321이다. 전체 폭 동료 발판과 오른쪽 히어로 발판의 보행선은 Y=1082이며, 주포 발사점은 `(1095,770)`이다. 내부 개구부 `(280,510,470,530)`를 사용해 왼쪽 성문/탑과 오른쪽 버팀벽을 열림 상태에서도 보존한다. 세 방의 생성 바닥선을 각각 높이 177/176/177의 고정 영역에 맞춰 자르고 등록하며, 동료 발 위치 간격은 원화 530/3이다.

`register_third_sd.ps1`은 생성 원본을 보존하고 2·3단계의 축 간격/캔버스 차이를 좌표 변환으로 맞춘다. `split_third_sd.ps1`은 색을 다시 그리지 않고 등록된 통합 외관을 정확히 분할한다. 각 단계 원본 리소스는 `original-resources` 및 `Resources/res/castle_sd_third_legacy`에 보존하며 54개 별도 ID/이름을 등록했다. Release와 기존 고정 크기 조립 및 다른 성이 공유하는 방은 보존 리소스를 사용한다.

## 게임 적용과 테스트

Debug의 첫 세 성에 SD 조립을 적용한다. 전체 폭 상한은 기존 요청대로 화면의 55%이며, 레일 접지 보정과 이동 거리에 비례한 바퀴 회전을 유지한다. 방이 닫혔을 때 내부 동료/그림자를 그리지 않고, 터치 중 공개할 때는 층별로 클립한다. 기존 두 배 터치 반경을 유지한다. 전투 준비처럼 레일이 높은 화면에서 세 번째 성의 탑이 잘리지 않도록 가용 높이에 맞춰 성과 캐릭터를 함께 축소한다. 레일이 내려가 충분한 공간이 생기면 원래 배율로 복귀한다.

```powershell
powershell -ExecutionPolicy Bypass -File tools/castles/preview_third_sd.ps1 -Stage 0
powershell -ExecutionPolicy Bypass -File tools/castles/preview_third_sd.ps1 -Stage 5
powershell -ExecutionPolicy Bypass -File tools/castles/verify_third_upgrades.ps1
```

테스트 실행 파일은 `proj.win32/Debug.win32/cs.third-modular-preview.exe`, 캡처/로그는 `output/third-upgrades-review`다. 검증은 6단계와 혼합 조합 3개, 리소스 로딩/범위, 크기·접지·회전, 내부 동료 렌더 수, 터치 공개, 전투 준비의 탑 상단 범위, 실제 배치된 동료의 발판 좌표를 확인한다. 미리보기/검증은 격리된 저장 경로를 사용한다.
