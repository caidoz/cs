[Current display policy](../fixed-width-layout.md)

현재 등록은 [원본 비율 복원](../uniform-registration.md)을 따른다. 아래 고정 규격·구간별 등록 설명은 이전 제작 기록이다.

# 여덟 번째 성 — 백대리석 독수리성

백대리석·푸른 지붕·은빛 독수리 문양과 오른쪽을 향하는 단일 레이저포. 왼쪽 주탑과 낮은 오른쪽 어깨를 조합해 일곱 번째 성과 실루엣을 구분한다. 기본형과 업그레이드 1~5단계, 8개 방을 제공한다.

## 리소스와 조립

- `generated-master.png`는 생성 원본, `assembled-master.png`는 게임 규격에 등록한 조립 원화다. 각 업그레이드 폴더도 같은 구조다.
- 원본의 바퀴·발판을 찾아 340×1024 규격에 등록한다. 두 바퀴는 원형을 유지하며 별도 아틀라스로 분리한다.
- 기존 `castle_08_*_stage_0..5`, `castle_room_08_0..5` 이름을 유지한다. 원래 파일 54개는 `original-resources` 및 `Resources/res/castle_sd_eighth_legacy`에 보관한다.
- `parts.json`, `Classes/Data/EighthSdParts*.h`가 정확한 분할 좌표를 기록한다. PNG를 디스크에서 다시 읽어 조립 원화의 보이는 RGBA 픽셀과 비교한다.
- 방은 층마다 따로 맞추며 외벽 알파로 제한한다. 외벽을 누르는 동안 확대된 반경 안에 내부를 표시한다.
- 지붕·외벽·방·무기·발판/차체의 5개 업그레이드 요소는 서로 독립적으로 조합한다.
- 생성 변형 4·5는 레이저포의 크기를 비교해 외관 순서를 교환했다. 선택 순서는 기본형, 1, 2, 3, 5, 4이며 방 내부는 각 단계 순서다. 선택 전 원본도 보관한다.

## 배치

방 영역 `(60,196,120,704)`, 8층 간격 88px. 동료 발판과 히어로 발판의 기준 Y는 900, 바퀴 접지는 995다. 바퀴 반지름은 40이며 레일 이동 거리에 맞춰 회전한다. 화면 폭 상한과 상단 안전영역은 기존 배치 로직을 따른다.

현재 새 조립 원화 연결은 기존 1~7번째 성과 같은 Debug 경로다. 기존 원화는 Release 및 공용 리소스 경로에 남긴다. 테스트 실행기는 별도 프로필을 사용한다.

```powershell
powershell -File tools/castles/register_eighth_sd.ps1 -Stage 0
powershell -File tools/castles/split_eighth_sd.ps1 -Stage 0
powershell -File tools/castles/verify_eighth_upgrades.ps1
powershell -File tools/castles/preview_eighth_sd.ps1 -Stage 0
```

[기본형·업그레이드 갤러리](upgrades.html)
