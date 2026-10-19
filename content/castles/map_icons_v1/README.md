# 성 10종 기본형 · 맵 위치 아이콘

각 성의 업그레이드 전 기본형을 바탕으로 만든 1024×1024 투명 PNG 10장이다. 유저 위치 표시용으로 재질·문양·무기·바퀴를 유지하고, 같은 3/4 시점의 SD 디오라마와 받침으로 정리했다. 긴 게임용 측면 원화를 작은 정사각형 안에 단순 축소하는 대신, 각 성의 건물 덩어리를 아이콘용으로 다시 그렸다.

| 성 번호 | 기본형 식별 요소 | 파일 |
|---|---|---|
| 1 | 목재 · 보라 왕관 · 투석기 | `png/castle-map-01.png` |
| 2 | 사암 · 붉은 지붕 · 멧돼지 · 화염포 | `png/castle-map-02.png` |
| 3 | 화강암 · 청색 지붕 · 교차검 · 다연장 로켓 | `png/castle-map-03.png` |
| 4 | 현무암 · 녹청 돔 · 거북 · 개틀링 | `png/castle-map-04.png` |
| 5 | 철제 · 사자 · 유도미사일 | `png/castle-map-05.png` |
| 6 | 은빛 금속 · 청록 · 기어 · 대형 포탄포 | `png/castle-map-06.png` |
| 7 | 검은 대리석 · 붉은 지붕 · 불사조 · 얼음포 | `png/castle-map-07.png` |
| 8 | 백대리석 · 청색 지붕 · 독수리 · 레이저포 | `png/castle-map-08.png` |
| 9 | 보라 크리스탈 · 눈 문양 · 전격 코일포 | `png/castle-map-09.png` |
| 10 | 상아색 · 금빛 · 청색 돔 · 태양 · 중력포 | `png/castle-map-10.png` |

`manifest.json`의 `castleIndex`는 게임 성 인덱스 0~9, `castleLevel`은 표시 번호 1~10, `upgradeStage`는 모두 0이다. 아이콘에는 유저 아바타·이름·등급 숫자를 넣지 않았다. 맵에서 별도 UI로 표시할 수 있다.

- [PNG 10장 ZIP](castle-map-icons-1024.zip): 1024px PNG만 포함한다.
- [갤러리](index.html): 배경 전환과 작은 표시 크기를 확인한다.
- [전체 비교](overview-dark.png) · [밝은 배경 비교](overview-light.png).
- [96px·64px 확인](small-size-check.png): 위쪽 96px, 아래쪽 64px의 실제 표시 크기다.
- `preview-64/96/128/256`은 확인용 축소본이다.
- `originals`는 생성 원본, `references`는 기본형 파츠 조립본에서 만든 참고 이미지다.
- `generation-prompts.json`은 각 생성 요청, `validation.json`은 크기·알파·파일 검증 결과다.

아트는 `imagegen` 내장 도구로 개별 생성했다. 받침 끝이 잘린 생성본은 같은 도구로 복원했다. `System.Drawing`은 참고 이미지·미리보기 제작과 투명 여백 정리, 종횡비를 유지한 1024px PNG 내보내기에 사용했다. 최종 PNG는 32px 이상의 공통 여백과 바닥 기준을 사용한다.

## 게임 리소스 등록

동일한 PNG를 `Resources/res/castle_map_icons/castle_map_01.png`부터 `10.png`까지 복사했다. 이미지 ID는 `CASTLE_MAP_ICON_01_IMG`~`CASTLE_MAP_ICON_10_IMG`이며, 성 인덱스 0~9에서 `CASTLE_MAP_ICON_FIRST_IMG + castleIndex`로 선택할 수 있다. `CastleMapIconNames.inc`를 `Text.h`에 연결했고 `Core.cpp`에서 시작 시 `LoadImg`와 `LoadTexture`를 모두 수행한다. 작은 아이콘용 선형 텍스처 필터도 설정한다.

등록 검증은 `tools/castles/verify_map_icon_resources.ps1`이다. 별도 프로필로 게임을 시작해 10개 ID의 경로, 시작 시 로드된 스프라이트·텍스처 캐시, 1024px 크기와 원본 PNG 해시를 확인한다.

```powershell
powershell -File tools/castles/export_map_icons.ps1
& "$env:LOCALAPPDATA/Python/bin/python.exe" tools/castles/verify_map_icons.py
```
