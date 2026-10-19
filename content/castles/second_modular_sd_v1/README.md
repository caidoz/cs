# 두 번째 사암성 · 기본형과 업그레이드 1~5

내장 imagegen으로 통합 외관과 두 방의 내부를 생성했다. 생성 지침은 각 단계의 `master-prompt.txt`, `room-prompt.txt`에 보관했다. 첫 성의 SD·부드러운 입체 채색을 유지하며 사암, 붉은 지붕, 멧돼지 문양, 오른쪽 화염방사 주포 한 기로 구분했다.

## 구성

- 기본형은 현재 폴더, 업그레이드는 `upgrade-1`~`upgrade-5`에 저장한다.
- `upgrades.html`: 외관/내부 전환 비교. `upgrade-overview.png`: 6단계 비교 이미지.
- `assembled-master.png`: 캐릭터 없는 통합 외관 원화, 1254×1254 RGBA.
- `interior-source.png`: 두 방을 그린 생성 원본. 외관 픽셀은 재사용하지 않는다.
- `reassembled-game-closed.png`, `reassembled-game-open.png`: 실제 파츠 좌표로 재조립한 외관/내부.
- `parts.json`, `partition-check.txt`: 좌표와 저장된 PNG를 다시 읽어 수행한 외관 픽셀 검증. 보이는 픽셀의 RGBA 불일치 0개.

## 런타임

기존 두 번째 성 파일명을 유지한다. 지붕, 벽, 중공 구조, 주포, 주포 받침, 전투 발판, 차대, 좌우 바퀴를 분리하고 두 방은 기존 `castle_room_02_0~5.png`에 공통 방 영역으로 저장한다. 외관 9조각(좌우 바퀴 별도)과 내부를 원화 좌표로 조립한다. 방 내부의 두 층을 모두 담기 위해 생성 원본의 `(140,535,710,415)` 영역을 고정 외벽 개구부 `(140,535,710,345)`에 맞춘다. 바퀴는 레일 이동 거리와 반지름으로 회전한다.

Debug에서 첫 번째·두 번째 성에 SD 조립을 적용한다. 폭 상한은 이전 요청의 10% 확대한 화면 55%이며, 두 번째 성은 같은 폭에서 첫 성보다 높다. 바퀴 접점은 레일 기준선보다 8px 내려 맞춘다. 전체 폭 동료 발판과 별도의 오른쪽 히어로 발판은 원화 Y=925의 보행면을 공유한다. 주포 발사점은 원화 `(1210,610)`이다. 방 내부 동료는 두 층에 나누고 층별로 클립하며, 닫혔을 때는 내부 동료·그림자를 그리지 않는다. 기존 터치 반경 2배 공개를 지원한다.

카테고리는 지붕, 성벽(중공 포함), 내부(두 방), 주포(주포 받침 포함), 이동부(전투 발판·차대·바퀴)이다. 서로 다른 레벨을 혼합할 수 있다. 원본 54개는 `original-resources`와 `Resources/res/castle_sd_second_legacy`에 보존하며 별도 ID로 등록했다. Release 및 기존 크기 조립 경로, 다른 성이 공유하는 기존 방은 보존 리소스를 사용한다.

## 실행과 검증

```powershell
powershell -ExecutionPolicy Bypass -File tools/castles/preview_second_sd.ps1 -Stage 0
powershell -ExecutionPolicy Bypass -File tools/castles/preview_second_sd.ps1 -Stage 5
powershell -ExecutionPolicy Bypass -File tools/castles/verify_second_upgrades.ps1
```

기본 실행 파일은 `proj.win32/Debug.win32/cs.second-modular-preview.exe`이다. 미리보기는 격리된 저장 경로를 사용한다. 일반 Debug 실행은 소유한 두 번째 성을 선택하면 새 외관을 표시한다.

검증 스크립트는 6단계 및 3개 혼합 조합의 리소스 범위, 크기, 레일 접지, 바퀴 회전, 닫힘/터치 공개와 내부 인원 렌더 수, 실제 전투 동료 발판 좌표를 확인한다. 캡처와 로그는 `output/second-upgrades-review`에 저장한다. `tools/castles/split_second_sd.ps1 -Stage N -Source ... -Interior ...`로 다시 분할할 수 있다.
