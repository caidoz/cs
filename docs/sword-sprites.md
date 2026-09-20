# 세로 검 리소스와 CMF 회전

`Resources/res/w0_1.png`부터 `w0_35.png`까지 투명 배경의 세로 검 한 자루다.
기존 시트는 `content/swords/source/`에 보관한다. 수평 검만 분리해서 90도
돌렸으며 리샘플링, 색 변경, 도트 재생성을 하지 않았다. 기존부터 손잡이가
짧거나 없는 형태도 원본 그대로 유지한다.

## 칸 크기와 손잡이

- 한 칸은 원본 텍스처에서 32×32픽셀. 캔버스는 항상 정수 칸 크기다.
- `w0_35`: 96×384, 3×12. 돌검 `w0_20`: 5×8, 나무검 `w0_21`: 5×9.
  원본 픽셀을 담는 최소 칸 수로 맞추며 추가 테두리 여백은 넣지 않는다.
- `content/swords/profiles.json`: 원본 시트상의 손잡이 픽셀 좌표.
- `content/swords/sprites.json`: 생성 결과, 크기, 손잡이 중심, 원본 잘라낸 영역, 해시.
- `Classes/Data/SwordSprites.h`: 가방과 전투가 공유하는 생성 데이터.
  `swordTileSize[detail * 2]`가 가로, `[detail * 2 + 1]`이 세로 칸 수다.
- 아이템 `detail=0`이 `w0_1`, `detail=34`가 `w0_35`다.
- `DrawSwordInBox`는 가방/드래그/상점 표시, `DrawSwordAtHand`는 손잡이 기준 회전이다.
  좌우 반전 때 기준점도 함께 뒤집는다. 점 샘플링을 유지한다.

현재 가방의 네 검 상품은 이 크기 표를 사용하며 기존 상품 구성과 가격은 유지한다.
수납 가능 여부는 성별 가방 칸 배치와 검의 실제 칸 수로 판단한다.

## CMF 확장

기존 `[image, x, y, flags]` 및 content.pack 형식은 유지하고 검 전용 확장 트랙을
추가했다. `CmfSwordPose`의 `handX`, `handY`, `angleDegrees`, `scale`, `opacity`,
`flipX`는 독립 필드다. 각도는 세로 위쪽이 0도, 시계 방향이며 소수 각도도 가능하다.
손 위치는 캐릭터 기준 오른쪽 +X, 아래쪽 +Y다. 반전은 각도와 따로 보관한다.

`Classes/Data/RobinSwordTrack.h`는 로빈의 검 모션 544개를 포함하며, 기존 60fps
모션 체인의 중간 381개에서 손 위치와 최단 경로 회전각을 보간한다. 대각선/수평
검을 동시에 표시하던 중간 프레임도 검 한 자루만 그린다. 원래 키 모션의 부착
위치는 기존 사각형 기준점에서 손 위치로 변환한다. 원본 대각선 그림의 기울기는
약 30도이므로 세로 기준 60도로 변환한다.

`content/swords/pose_overrides.json`에 모션 이름별 보정을 넣을 수 있다. 예:

```json
{
  "PO_C0_A0": {"handX": -12, "handY": -36, "angleDegrees": 45, "flipX": false}
}
```

키 모션 보정은 중간 모션에도 보간된다. 중간 모션 자체를 지정하면 해당 값을
우선한다. 생성 결과는 `content/swords/poses.json`에서 확인한다.
런타임 CMF 내용과 트랙의 서명이 다르면 잘못된 모션 좌표를 사용하지 않고
현재 CMF의 사각형 기준점을 변환한다. 변경된 CMF의 부드러운 보간을 유지하려면
트랙도 다시 생성해야 한다. 다른 캐릭터와 빈 무기 슬롯은 기존 경로를 사용한다.

## 재생성 및 검증

Python과 Pillow가 필요하다. 저장소 루트에서 실행한다.

```text
python tools/swords/prepare_swords.py
python tools/swords/build_sword_poses.py
python tools/swords/test_swords.py
python tools/swords/review_swords.py
python tools/content/make_manifest.py
```

Developer Command Prompt에서 독립적인 C++ 변환 검사를 실행할 수 있다.

```text
cl /EHsc /std:c++14 /Fooutput/swords/test_transform.obj /Feoutput/swords/test_transform.exe tools/swords/test_transform.cpp
output\swords\test_transform.exe
```

`output/swords/upright-review.png`는 35개 이미지/칸 규격과 빨간 손잡이 기준점이다.
`output/swords/motion-review.png`는 기존/신규와 좌우 방향의 오프라인 합성 비교다.
오프라인 합성은 효과를 생략하므로 실제 게임 화면을 완전히 대신하지 않는다.
새 PNG와 새 실행 파일은 함께 배포해야 한다. 이전 실행 파일은 두 방향 시트의
잘라내기 좌표를 사용하므로 새 이미지와 호환되지 않는다.
