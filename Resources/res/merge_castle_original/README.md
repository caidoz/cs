# 원본 픽셀 기반 1단계 성

`reference.png`는 승인된 `output/imagegen/cs-lobby-battlebase-v2/lobby-concept.png`의 변경 없는 복사본이다. 1089×1445 원본 좌표에 `DX / 1089` 한 배율을 적용한다.

`Classes/MergeCastleOriginal.inc`의 네이티브 폴리곤은 원본 텍스처의 외장·버튼·바퀴·포를 잘라 그린다. RGB 픽셀을 다시 그리거나 별도 가로·세로 배율로 늘리지 않는다. 원본 전체 이미지를 배경으로 깔지 않으며, 기존 게임 배경을 유지한다.

`deck-repair.png`는 인물이 가렸던 데크를 복원한 이미지다. `generation.json`에 기록된 세 영역에서만 사용하고, 나머지 외장 픽셀은 원본에서 읽는다. 방 5개의 생산시설 역할과 독립 강화 데이터, 실제 게임의 캐릭터 리소스는 유지한다. 방 그림은 동일 배율로 채운 뒤 넘치는 부분을 자른다.

단순 사각형과 폴리곤은 렌더 스프라이트 풀을 서로 다른 이미지 인덱스로 분리한다. 동일한 텍스처를 공유해도 폴리곤 형상이 일반 사각형 드로우에 남지 않도록 하기 위한 구분이다.

검증: `tools/merge_roulette/verify_original.py`. 원본 전체를 같은 네이티브 배율로 그린 화면과 실제 로비를 비교한다. 버튼 3개와 첨탑의 기준 영역은 RGB 차이 0, 가로 보의 경계는 GL 필터링의 작은 오차를 허용한다. 이 검증은 변경된 생산시설 그림·메뉴 이름·게임 캐릭터·기존 배경까지 원본과 같다는 의미는 아니다.

wheel.png: standalone transparent wooden wheel reconstructed from reference.png with built-in imagegen. The native renderer rotates this independent sprite around its hub; baked chassis/menu pixels are excluded. Original reference wheel-circle meshes are no longer animated or drawn in the live castle.
