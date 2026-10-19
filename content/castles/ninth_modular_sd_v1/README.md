# 아홉 번째 성 — 크리스탈 안광성

현재 등록은 [원본 비율 복원](../uniform-registration.md)을 따른다. 아래 300×1024 고정 규격·구간별 등록 설명은 이전 제작 기록이다.

보라색 크리스탈 면과 흑은색 골조, 눈 문양, 오른쪽을 향하는 단일 전격 코일포. 높은 크리스탈 주탑과 비대칭 어깨로 외형을 구분한다. 기본형과 업그레이드 1~5단계, 내부 방 9개를 제공한다.

## 리소스

`generated-master.png`는 생성 원본, `assembled-master.png`는 게임 규격에 등록한 조립 원화다. 각 업그레이드 폴더도 같은 구조다. 최초의 가로형 원화는 높이가 부족하다는 피드백에 따라 폐기하고, 원본 자체가 높은 세로형 원화로 다시 생성했다. 이전 이미지는 `previous-wide`에 보관한다. 세로형 원화를 균일 축소해 작업 캔버스에 놓은 뒤 바퀴와 발판 위치를 찾아 300×1024 규격에 등록하며 바퀴는 원형으로 보존한다.

기존 `castle_09_*_stage_0..5`, `castle_room_09_0..5` 파츠명을 유지한다. 원래 리소스 54개는 각 폴더의 `original-resources` 및 `Resources/res/castle_sd_ninth_legacy`에 보관한다. `parts.json`, `Classes/Data/NinthSdParts*.h`가 정확한 분할 좌표를 기록한다. 저장된 PNG를 다시 읽어 조립 원화의 보이는 RGBA 픽셀과 비교한다.

지붕·외벽·방·무기·발판/차체의 5개 요소는 독립적으로 업그레이드한다. 방은 층마다 개별 등록하고 외벽 알파로 제한한다. 외벽을 누르는 동안 내부를 반경 안에 공개한다. 인물은 리소스에 포함하지 않는다.

발사 원점은 각 단계의 실제 포구 중심을 따른다. 세로형 외관 변형의 선택 순서는 `기본형, 1, 2, 4, 5, 3`으로, 포구의 보이는 높이가 66→67→68→80→82→86px로 증가한다. 방 내부는 각 단계 순서를 유지한다. `tall-generated-variants`는 선택 전 세로형 원화, `generated-variants`는 초기 가로형 변형 보관본이다.

## 배치

- 방 영역 `(95,180,100,720)`, 9층 간격 80px.
- 동료 발판 및 별도 히어로 발판 기준 Y=900.
- 바퀴 접지 Y=995, 반지름 36px. 레일 이동 거리에 따라 회전한다.
- 로비·전투에서 다른 단계와 같은 화면 폭 55%를 유지한다.

높이에 따른 전체 축소를 제거했다. 원화의 비율대로 위로 높아지며, 화면을 넘는 위층은 로비의 세로 드래그로 확인한다. [현재 표시 정책](../fixed-width-layout.md)

새 조립 원화는 이전 1~8번째 성과 동일하게 Debug 경로에 연결한다. Release 및 공용 리소스는 보관한 기존 원화를 사용한다. 테스트 실행기는 별도 프로필을 사용한다.

```powershell
powershell -File tools/castles/register_ninth_sd.ps1 -Stage 0
powershell -File tools/castles/split_ninth_sd.ps1 -Stage 0
powershell -File tools/castles/verify_ninth_upgrades.ps1
powershell -File tools/castles/preview_ninth_sd.ps1 -Stage 0
```

[단계별 외관·내부](upgrades.html) · [세로형 생성 프롬프트](tall-generation-prompts.json) · [초기 외관·내부 생성 프롬프트](generation-prompts.json)
