# 마지막 10번째 성 — 태양 황궁

현재 등록은 [원본 비율 복원](../uniform-registration.md)을 따른다. 아래 270×1024 고정 규격·구간별 등록 설명은 이전 제작 기록이다.

상아색 석재, 청색 돔, 금빛 태양 문양과 오른쪽을 향하는 단일 중력포. 9번째 크리스탈 성과 구분되는 둥근 왕궁 주탑 및 비대칭 어깨를 사용한다. 기본형과 업그레이드 1~5단계, 내부 방 10개를 제공한다.

## 원화와 파츠

`generated-master.png`는 원본 자체가 높은 세로형 생성 원화다. `generated-wide-candidate.png`는 채택하지 않은 첫 가로형 후보다. `assembled-master.png`는 세로 원화를 게임 규격에 등록한 조립 원화이며 각 업그레이드 폴더도 같은 구조다.

원화를 균일 축소해 작업 캔버스에 놓은 뒤, 바퀴 접지선과 청색 허브에서 축·반지름을 구하고 발판 기준점에 등록한다. 바퀴는 별도 원형 아틀라스로 분리한다. `parts.json`, `Classes/Data/TenthSdParts*.h`가 분할 좌표를 기록하며 디스크에 저장한 PNG를 다시 읽어 조립 원화의 보이는 RGBA 픽셀과 비교한다.

기존 `castle_10_*_stage_0..5`, `castle_room_10_0..5` 파츠명을 유지한다. 원래 리소스 54개는 각 단계의 `original-resources` 및 `Resources/res/castle_sd_tenth_legacy`에 보관한다. 지붕·외벽·방·무기·발판/차체 5개 요소는 독립적으로 업그레이드한다.

외관 변형은 포구 크기를 비교해 `기본형, 2, 5, 1, 3, 4` 순서로 선택했다. 보이는 포구 높이는 59→81→84→86→86→88px다. 선택 전 외관은 `generated-variants`에 보관하며 방 내부는 단계 순서를 유지한다.

## 방과 발판

방은 위에서부터 지휘 관측실, 도서관, 의무실, 주방, 무기고, 작업실, 중력 연구실, 보물창고, 병영, 물류창고다. 층마다 개별 등록하고 외벽 알파로 제한한다. 닫힌 외벽 뒤 인물은 그리지 않으며, 외벽을 누르는 동안 내부를 공개한다.

- 원화 규격 270×1024, 방 영역 `(75,160,100,740)`, 10층 간격 74px.
- 동료 발판과 별도 히어로 발판 기준 Y=900.
- 바퀴 접지 Y=995, 반지름 32px. 레일 이동 거리에 따라 회전한다.
- 발사 원점은 각 단계의 실제 포구 중심을 따른다.

새 조립 원화는 이전 1~9번째 성과 동일하게 Debug 경로에 연결한다. Release 및 공용 리소스 경로는 보관한 기존 원화를 사용한다. 로비·전투의 폭을 화면 55%로 고정하고, 원화 비율대로 위로 높아진다. 로비에서 세로 드래그로 위층을 확인할 수 있다. [현재 표시 정책](../fixed-width-layout.md). 테스트는 별도 프로필을 사용한다.

```powershell
powershell -File tools/castles/register_tenth_sd.ps1 -Stage 0
powershell -File tools/castles/split_tenth_sd.ps1 -Stage 0
powershell -File tools/castles/verify_tenth_upgrades.ps1
powershell -File tools/castles/preview_tenth_sd.ps1 -Stage 0
```

[원화·업그레이드·방 갤러리](upgrades.html) · [제작 프롬프트](generation-prompts.json)
