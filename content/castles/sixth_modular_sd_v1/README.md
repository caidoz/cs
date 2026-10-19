[Current display policy](../fixed-width-layout.md)

현재 등록은 [원본 비율 복원](../uniform-registration.md)을 따른다. 아래 고정 규격·구간별 등록 설명은 이전 제작 기록이다.

# 여섯 번째 성 · 실버 기어성 · 기본형과 업그레이드 1~5

내장 imagegen으로 통합 외관을 먼저 생성하고, 이를 바탕으로 업그레이드 5종과 6개 방의 내부 및 내부 업그레이드를 제작했습니다. 생성 요청은 각 단계의 `master-prompt.txt`, `room-prompt.txt`에 보존했습니다. 참고 원화는 앞선 성의 채색·SD 표현을 위한 것으로, 여섯 번째의 소재와 실루엣은 새로 구성했습니다.

알루미늄·실버의 큰 곡면 장갑, 청록색 에나멜, 황동 결합부와 기어 문양을 사용합니다. 왼쪽의 높은 원형 탑과 평평한 성가퀴, 오른쪽으로 후퇴한 지붕과 휘어진 보강재를 조합했습니다. 같은 폭으로 비교하면 다섯 번째보다 높습니다. 주포는 오른쪽을 향한 하나의 거대 포탄포입니다.

## 확인 자료

- [단계별 외관·내부 갤러리](upgrades.html)
- [첫 여섯 성의 같은 폭·접지 비교](castle-01-06-comparison.png)
- [외관 6단계](upgrade-overview.png), [내부 6단계](room-overview.png)
- `game-overview-closed.png`, `game-overview-open.png`: 실제 게임 6단계 캡처 모음.
- `generated-master.png`, `generated-interior.png`: 생성된 원본. 오른쪽 빈 공간을 둔 1536×1024 레이아웃입니다.
- `assembled-master.png`: 공통 조립 좌표로 등록한 450×1024 외관.
- `interior-source.png`: 내부 원본에서 작업 영역을 잘라낸 이미지.
- `reassembled-game-closed.png`, `reassembled-game-open.png`: 저장 PNG를 재조립한 결과.
- `parts.json`, `partition-check.txt`: 파츠 좌표와 저장 PNG 검증. 등록한 외관의 보이는 픽셀 RGBA 불일치 0개.
- 실제 게임 캡처·검증 로그: `output/sixth-upgrades-review`.

## 등록 및 분할

생성 결과의 바퀴 간격과 포신 돌출 길이가 단계마다 달라 `register_sixth_sd.ps1`에서 공통 조립 좌표로 등록합니다. 기본형은 원본을 네이티브 크기로 자릅니다. 업그레이드는 바퀴 축과 외곽 기준으로 구간별 좌표를 맞추고, 바퀴를 원형으로 별도 등록합니다. 원본은 변경하지 않습니다. 원화 선택 후 포신의 부피를 비교해 외관 변형 순서를 1·5·3·2·4로 정렬했습니다. 내부는 가구가 강화되는 원래 단계 순서를 유지합니다.

등록된 외관을 지붕·외벽·중간 구조·주포·주포 받침·전투 발판·차대·좌우 바퀴의 9조각으로 정확히 분할합니다. 저장한 PNG를 다시 읽어 등록 외관과 보이는 픽셀을 비교합니다. 따라서 검증 기준은 생성 원본이 아닌 **좌표 등록을 마친 외관**입니다.

450×1024 좌표에서 바퀴 축은 `(105,949)`, `(302,949)`, 반지름은 50, 접지 기준은 Y=999입니다. 동료 발판은 X=15부터 폭 280이며 보행면은 Y=884입니다. 별도 히어로 발판도 같은 높이이고 히어로는 X=385에 섭니다. 포탄 발사 기준은 `(441,635)`입니다. 바퀴는 레일 이동 거리/반지름으로 각각 회전합니다.

내부 개구부는 `(68,150,160,732)`이며 층당 122px입니다. 위에서 항법 지휘실·연구실·침실·창고·공방·주방의 6개 방을 배치합니다. 생성된 내부의 각 층을 공통 칸에 따로 등록합니다. 닫힌 외벽에서는 실내 동료와 그림자를 그리지 않습니다. 터치를 유지하면 기존의 두 배 반경으로 내부를 보여주며 거주 동료는 각 층 안에서 클립합니다. 전투에 소환된 동료 6명은 외벽 앞 발판을 사용합니다.

## 기존 리소스와 게임 연결

기존 `castle_06_roof`, `wall`, `hollow`, `heavy_cannon`, `command_platform`, `combat_deck`, `base`, `wheel`의 stage 0~5 파일명과 `castle_room_06_0~5.png`를 유지했습니다. 내부·외벽·지붕·주포·이동부를 독립적으로 올릴 수 있습니다.

원래 리소스 54개는 각 단계의 `original-resources`와 `Resources/res/castle_sd_sixth_legacy`에 보존하고 별도 이미지 ID 및 이름으로 등록했습니다. Release 및 기존 공유 방을 사용하는 조립 경로는 보존 리소스를 사용합니다. SD 조립은 현재 Debug의 첫 여섯 성에 연결되어 있습니다. 폭 상한 55%, 로비 상단 정보 및 전투 준비 공간에 맞춘 높이 제한, 레일 접점 8px 겹침을 적용합니다.

## 실행

```powershell
powershell -ExecutionPolicy Bypass -File tools/castles/preview_sixth_sd.ps1 -Stage 0
powershell -ExecutionPolicy Bypass -File tools/castles/preview_sixth_sd.ps1 -Stage 5
powershell -ExecutionPolicy Bypass -File tools/castles/verify_sixth_upgrades.ps1
```

미리보기 실행 파일은 `proj.win32/Debug.win32/cs.sixth-modular-preview.exe`입니다. 실제 사용자 저장과 분리된 프로필을 사용합니다. 자동 검증은 6단계와 혼합 조합 3개, 내부 텍스처와 파츠 범위, 화면 범위와 접지, 회전, 터치 공개, 층 간격, 실제 동료 6명의 발판 좌표를 확인합니다. 최종 결과는 `validation.txt`에 기록합니다.
