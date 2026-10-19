[Current display policy](../fixed-width-layout.md)

현재 등록은 [원본 비율 복원](../uniform-registration.md)을 따른다. 아래 고정 규격·구간별 등록 설명은 이전 제작 기록이다.

# 일곱 번째 성 · 흑대리석 불사조성 · 기본형과 업그레이드 1~5

내장 imagegen으로 통합 외관을 먼저 생성하고, 이를 바탕으로 업그레이드 5종과 7개 방의 내부 및 내부 업그레이드를 제작했습니다. 각 단계의 `master-prompt.txt`, `room-prompt.txt`에 생성 지침을 보존했습니다. 앞선 성의 그림은 채색·게임 배치 참고용이며, 일곱 번째의 소재와 비대칭 건축은 새로 구성했습니다.

검은 대리석의 드문 밝은 결, 붉은 지붕과 불사조 문양, 금색 테두리를 사용합니다. 높은 오른쪽 주탑과 낮은 왼쪽 지붕, 후퇴한 외벽과 사선 보강재를 조합했습니다. 같은 폭으로 비교하면 여섯 번째보다 높습니다. 주포는 오른쪽으로 향한 하나의 얼음 수정포이며, 다른 장식 포를 추가하지 않았습니다.

## 확인 자료

- [단계별 외관·내부 갤러리](upgrades.html)
- [첫 일곱 성의 같은 폭·접지 비교](castle-01-07-comparison.png)
- [외관 6단계](upgrade-overview.png), [내부 6단계](room-overview.png)
- `game-overview-closed.png`, `game-overview-open.png`: 실제 게임의 6단계 캡처 모음.
- `generated-master.png`, `generated-interior.png`: 생성 원본. 오른쪽을 비운 1536×1024 레이아웃입니다.
- `assembled-master.png`: 공통 조립 좌표로 등록한 390×1024 외관.
- `interior-source.png`: 보존한 전체 내부 원본. 각 방을 따로 공통 칸에 등록합니다.
- `reassembled-game-closed.png`, `reassembled-game-open.png`: 저장 PNG를 재조립한 결과.
- `parts.json`, `partition-check.txt`: 파츠 좌표와 재조립 검증. 등록 외관의 보이는 픽셀 RGBA 불일치 0개.
- 실제 게임 캡처·검증 로그: `output/seventh-upgrades-review`.

## 등록과 규격

`register_seventh_sd.ps1`은 생성 원본을 보존하고, 두 바퀴의 접지 윤곽과 붉은 허브, 오른쪽 발판 표면을 찾아 공통 조립 좌표로 등록합니다. 바퀴는 원형으로 따로 등록합니다. 수정포의 부피가 증가하는 순서로 외관 변형을 1·3·2·5·4 순서로 선택했습니다. 내부 가구는 원래 단계 순서대로 강화됩니다.

등록된 외관을 지붕·외벽·중간 구조·주포·주포 받침·전투 발판·차대·좌우 바퀴의 9조각으로 정확히 분할합니다. 저장 PNG를 다시 읽어 **등록을 마친 외관**과 비교합니다. 검증 기준이 생성 원본과 동일한 픽셀이라는 의미는 아닙니다. 외관을 조립 좌표로 등록한 뒤 분할한 PNG가 그 등록 외관과 일치하는지 확인합니다.

390×1024 좌표에서 바퀴 축은 `(90,950)`, `(255,950)`, 반지름은 45, 접지 기준은 Y=995입니다. 전면 동료 발판은 X=15부터 폭 275이며, 히어로는 별도 오른쪽 발판의 X=315에 섭니다. 공통 캐릭터 배치 기준은 Y=900이고, 렌더링되는 발바닥과 닿는 발판 윗면은 Y=892에 맞춥니다. 수정포 발사 기준은 `(382,682)`입니다. 바퀴는 레일 이동 거리/반지름으로 회전합니다.

내부 개구부는 `(140,228,120,672)`, 층 간격은 96px입니다. 위에서 지휘실·서재·연구실·침실·창고·공방·주방의 7개 방을 배치합니다. 생성된 내부의 층마다 공통 크기로 등록하며, 외관 알파 마스크를 적용해 주탑 밖으로 내부가 새지 않도록 합니다. 닫힌 상태에서는 실내 동료와 그림자를 그리지 않습니다. 터치를 유지하면 기존의 두 배 반경으로 내부를 공개하며, 거주 동료는 각 층 안에서 클립합니다. 전투에 소환된 동료 6명은 외벽 앞 발판을 사용합니다.

## 기존 리소스와 게임 연결

기존 `castle_07_roof`, `wall`, `hollow`, `heavy_cannon`, `command_platform`, `combat_deck`, `base`, `wheel`의 stage 0~5 파일명과 `castle_room_07_0~5.png`를 유지했습니다. 지붕·외벽·내부·주포·이동부를 독립적으로 올릴 수 있습니다.

기존 리소스 54개는 각 단계의 `original-resources`와 `Resources/res/castle_sd_seventh_legacy`에 보존하고 별도 이미지 ID와 이름으로 등록했습니다. Release 및 공유 방을 사용하는 기존 조립 경로는 보존 리소스를 사용합니다. SD 조립은 현재 Debug의 첫 일곱 성에 연결되어 있습니다. 폭 상한 55%, 로비 상단 정보 및 전투 준비 공간에 맞춘 높이 제한, 레일 접점 8px 겹침을 적용합니다.

## 실행

```powershell
powershell -ExecutionPolicy Bypass -File tools/castles/preview_seventh_sd.ps1 -Stage 0
powershell -ExecutionPolicy Bypass -File tools/castles/preview_seventh_sd.ps1 -Stage 5
powershell -ExecutionPolicy Bypass -File tools/castles/verify_seventh_upgrades.ps1
```

미리보기 실행 파일은 `proj.win32/Debug.win32/cs.seventh-modular-preview.exe`입니다. 실제 사용자 저장과 분리된 프로필을 사용합니다. 검증은 6단계와 혼합 조합 3개, 텍스처 및 파츠 범위, 화면 범위와 접지, 바퀴 회전, 터치 공개, 층 간격, 히어로 발판 범위와 실제 동료 6명의 좌표를 확인합니다. 최종 결과는 `validation.txt`에 기록합니다.
