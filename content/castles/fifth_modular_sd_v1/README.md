[Current display policy](../fixed-width-layout.md)

# 다섯 번째 성 · 흑철 사자성 · 기본형과 업그레이드 1~5

내장 imagegen으로 통합 외관을 먼저 생성하고, 동일 원화를 바탕으로 5개 방의 내부 및 업그레이드 1~5단계를 제작했습니다. 생성 지침은 각 단계의 `master-prompt.txt`, `room-prompt.txt`에 있습니다. 첫 생성의 석재 같은 벽 질감을 큰 흑철 판재로 수정한 지침도 보존했습니다.

앞선 네 번째 성의 둥근 현무암 돔과 구분되는 높은 각진 장갑 구조, 파란 맨사드 지붕, 황동 사자 방패가 특징입니다. 큰 면과 돌출·후퇴한 구조를 사용하고 동일한 층 패널 반복을 피했습니다. 단일 유도미사일 발사대는 오른쪽을 바라봅니다. 여러 장식 포를 추가하지 않았습니다.

## 확인 자료

- [단계별 외관·내부 갤러리](upgrades.html)
- [첫 다섯 성의 동일 폭·접지 비교](castle-01-05-comparison.png)
- [6단계 외관](upgrade-overview.png), [6단계 내부](room-overview.png)
- 각 단계의 `generated-master.png`: 생성 원본. `assembled-master.png`: 분할 기준 원화. 원본 크기 887×1774를 유지합니다.
- `interior-source.png`: 생성된 5개 방의 내부 원화.
- `reassembled-game-closed.png`, `reassembled-game-open.png`: 저장한 파츠를 재조립한 결과.
- `parts.json`, `partition-check.txt`: 좌표와 저장 PNG 재조립 검증. 보이는 픽셀 RGBA 불일치 0개.
- 실제 게임 캡처 및 로그: `output/fifth-upgrades-review`.

## 규격과 파츠

원화는 887×1774입니다. 바퀴 중심은 `(218,1586)`, `(618,1586)`, 분할 반지름은 102이며 접지 기준은 Y=1688입니다. 바퀴는 독립 파츠로 레일 이동 거리/반지름에 따라 회전합니다. 전면 전체의 동료 발판과 오른쪽 히어로 발판은 Y=1440 보행면을 공유합니다. 동료 발판은 X=45부터 폭 625, 히어로는 X=780입니다. 미사일 발사 기준은 `(875,1115)`입니다.

내부 개구부는 `(290,400,330,1030)`입니다. 위에서 지휘실·침실·창고·작업실·주방을 206px 높이로 배치합니다. 생성된 내부의 각 층을 이 공통 좌표로 등록합니다. 거주 동료를 층별로 배치하고 해당 층 안에서 클립합니다. 닫힌 상태에서는 내부 동료와 그림자를 그리지 않으며, 터치를 유지하면 기존의 두 배 반경으로 내부를 공개합니다. 전투 동료는 외벽 앞 발판에 섭니다.

기존 `castle_05_roof`, `wall`, `hollow`, `heavy_cannon`, `command_platform`, `combat_deck`, `base`, `wheel`의 stage 0~5 파일명을 유지했습니다. 내부도 `castle_room_05_0~5.png`를 사용합니다. 지붕·외벽·내부·주포·이동부를 독립적으로 업그레이드할 수 있습니다. 원화 외관을 다시 그리지 않고 정확히 분할한 뒤, 저장된 PNG를 다시 읽어 재조립 일치를 검사합니다.

기존 리소스 54개는 각 단계의 `original-resources` 및 `Resources/res/castle_sd_fifth_legacy`에 보존하고 별도 이미지 ID/이름으로 등록했습니다. Release 및 기존 조립 경로가 공유하는 방은 보존 리소스를 사용합니다. 현재 SD 조립은 Debug의 첫 다섯 성에 연결되어 있습니다. 화면 폭 55% 상한, 로비 상단 정보와 전투 준비 공간에 맞춘 높이 제한, 바퀴 접지 8px 겹침을 적용합니다.

## 실행

```powershell
powershell -ExecutionPolicy Bypass -File tools/castles/preview_fifth_sd.ps1 -Stage 0
powershell -ExecutionPolicy Bypass -File tools/castles/preview_fifth_sd.ps1 -Stage 5
powershell -ExecutionPolicy Bypass -File tools/castles/verify_fifth_upgrades.ps1
```

미리보기 실행 파일은 `proj.win32/Debug.win32/cs.fifth-modular-preview.exe`입니다. 실제 사용자 저장과 분리된 프로필을 사용합니다. 검증은 6단계와 혼합 조합 3개, 리소스 및 내부 텍스처 크기, 화면 범위, 접지, 회전, 터치 공개, 실제 6명 동료의 발판 좌표를 확인합니다. 최종 결과는 `validation.txt`에 기록합니다.
