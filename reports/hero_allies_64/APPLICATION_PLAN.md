# 영웅·동료 64종 적용 감사 및 구현안

참조: `C:/Users/polyp/Downloads/CASTLE_SURVIVOR_HERO_ALLIES_64_DESIGN.md`, 제안 초안 v0.3.

**현재 적용 상태 (2026-10-25):** 사용자가 3종 연결을 승인한 뒤, 64종 전체의 기획·밸런스 결정 및 적용을 위임했다.
[64종 밸런스 표](BALANCE.md), [정확한 효과·상한·배치 규칙](BALANCE_RULES.md), [런타임 JSON](balance.json)이 현재 적용 기준이다.
아래의 초기 감사 결과에서 확인한 차이를 이 v1 정의로 해결했다.

## 완료한 P0

- [실제 64종 목록](CATALOG.md), [전체 필드 TSV](catalog.tsv), [JSON](catalog.json)을 생성했다.
  crew ID, 실제 표시 이름, NPC ID, CMF, 기존 PNG, 모션 소스, 기존 역할,
  3개 스킬의 ID·종류·호출 영웅, 기본 쿨타임과 점유 크기를 포함한다.
- 실제 컴파일러로 enum 값을 확인했다. 동료 64개의 ID 및 NPC ID는 중복이 없고,
  참조하는 64개 PNG가 존재한다. 기존 crewData 448개 값과 enemy의 관련 배열도
  `content_table.py ... verify`로 원본과 일치함을 확인했다.
- 검토용 실행 경로는 실제 게임의 DrawCmfDetailShadow와 표시 이름을 사용한다.
  실행 중 읽은 catalog도 별도 TSV로 내보내 정적 조사 결과와 비교한다.
- 초안 C01~C64의 임시 이름은 어느 기존 동료에도 배정하지 않았다.

## 현재 구현과 초안의 차이

| 항목 | 현재 구현 | 적용 시 처리 |
|---|---|---|
| 동료 이름 | 꼬마 마르셀, 대장장이로키, 사제 아밀 등 실제 64종 | 임시 이름으로 덮어쓰지 않음 |
| NPC_CAPTAIN | crew 57, 실제 이름 **용병단장 잭** | 코드 주석의 선장 캡틴과 구별 |
| 동료 점유 | 초기에는 모두 2×2였음 | v1의 1×1·1×2·2×2 정의를 보유·상점·공유 그리드에 통합 |
| 기존 능력 | CREWBULLET/HEROSKILL 등 3단계 스킬, 별도 역할 패시브 | 기존 스킬 유지, 새 패시브와 중복 수리 방지 |
| 로빈 | 장착 검 기본 공격, 가방 검별 시계·적 타격 | 명중 이벤트를 연결점으로 사용 |
| 디아나 | 총 기본 공격, 탄약 재고·생산·장전 런타임 없음 | 사격 이벤트부터 추가; 탄약 고갈 규칙은 미확정 유지 |
| 맥스 | 기본 부메랑 투척·명중·귀환·복귀 후 준비 | 실제 귀환 완료 이벤트에 연결, 다중 투척은 미확정 유지 |
| 장비 | 히어로 장착 8부위와 성 그리드가 공존 | 현재 1×2~1×4 무기, 갑옷 1×2, 기타 1×1 규격 유지 |
| 상태이상 | 독·둔화·실명·저주·기절·넉백, 턴 기반 중첩 상한 9 | 신규 6개 상태와 일대일 대응시키지 않음 |
| 보상 | 4개 선택지, 현재 범주가 슬롯별로 고정됨 | 적격 후보군에서 선택하는 방식으로 변경 필요 |
| 특수 아이템 | 마력 정수·작전서는 이미 별도 효과가 있음 | S01~S12로 기존 ID를 재사용하지 않음 |
| 영속성 | 런 ITEM 복사본, 장비 스냅샷 보호·종료 복원 구현됨 | 새로운 효과 시계·토큰도 동일 종료 경계에서 정리 |

## 코드 경로

- 동료 원본: `content/crew.tsv`, `content/enemy.tsv`, `content/skill.tsv`.
  ID 계약은 `content/ids/crew.tsv`, `Classes/Config/GameConfig.h`에 있다.
- 실데이터: `Classes/Data/HeroData.cpp`, `EnemyData.cpp`, `SkillData.cpp`.
  데이터팩 로딩이 이 표들을 교체할 수 있으므로 런타임 목록도 비교한다.
- 이미지: catalog의 PNG와 `Classes/Cmf/c*.h`, `Classes/Data/CmfBlob.*`.
  부트 시 CmfRelink, 슬롯 읽기는 `Classes/Func_Cmf.cpp::CmfRead`.
- 동료 스킬: `Func_Battle.cpp::UpdateStageRealtime`, `Func_Movement.cpp::AllyShootAt`.
  기존 역할과 인접 계산: `Func_Draw.cpp::GetCrewRole`, `GridItemsAreAdjacent`.
- 영웅 공격: `Func_Movement.cpp::PvpHeroStep`, `Func_Battle.cpp::StageFoeShotHit`,
  `StageMaxBoomerangStep`, `StageHeroCooldown`.
- 장비 배치: `Func_Draw.cpp::GridGearPart`, `LoadoutPreviewPack`, `GridPlaceGear`.
  동료는 `GridCrewPart` 및 PVP 빌드 경로까지 같이 확인해야 한다.
- 상태이상: `Func_Combat.cpp::ActivateDebuf`, `AdvanceActorDebuffs`;
  `Config/RenderConstants.h::DEBUF_MAXTURN`.
  `SkillDef.h::DEBUF_POISON0` 등은 **연출 모션**이며 상태 종류 enum이 아니다.
- 보상·정리: `GridOfferRoll`, `GridTestRelease`, `StageRunEquipmentEnd`,
  `StageRunGridClear`, `SaveGame`.

## 먼저 구현·검증한 3종 연결안

공통 이벤트에는 런 ID, 원본 공격 ID, 소스, 표적, 파생 여부를 넣는다.
동일 동료·효과가 같은 이벤트를 두 번 소비하지 못하게 하고, 파생 공격은
원본 영웅 연계를 다시 발생시키지 않는다. 메뉴·정지 중 시계는 멈춘다.

| 실제 동료 | 유지할 원본 | 추가할 시제품 능력 | 연결할 영웅 이벤트 |
|---|---|---|---|
| crew 36 / NPC_CRAFTMAN / 대장장이로키 | 이름·아트·기존 3스킬 | 8초 주기 성 수리, 기존 역할 수리와 중복 금지 | 로빈 명중 후 방어 보강 / 디아나 사격 후 공급 지원 / 맥스 비행 중 수리 |
| crew 45 / NPC_ELFMAGIC / 사제 아밀 | 이름·아트·기존 3스킬 | 성 체력 50% 이하일 때, 최소 15초 간격 회복 | 로빈 명중 / 디아나 사격 / 맥스 실제 귀환 성공 |
| crew 57 / NPC_CAPTAIN / 용병단장 잭 | 이름·아트·기존 3스킬 | 최소 3초 간격 보조 사격, 실제 머리→표적 투사체 | 로빈 명중 후 지원 사격 / 디아나 사격 연계 / 맥스 귀환 중 지원 |

P1 특수 아이템 후보는 **S03 회수기**, **S11 보호막 공명기**다. 신규 상태이상이
필요 없는 두 효과부터 검증한다. 영구 아이템 ID를 재사용하지 않고, 런 전용
정의와 인스턴스로 분리한다. 회수 단축은 공격 주기 하한을 지키고,
보호막은 최대 보호막을 넘지 않으며 이벤트당 1회만 발생한다.
최종 수치·리소스·보상 후보 배정은 기존 데이터와 구별해 검토한다.

사용자가 위 3종을 승인한 뒤 64종 기획·밸런스 결정을 위임하여,
일반 전투에서 64종의 고유 능력·공격 주기·192개 영웅 연계·상태이상을 구현했다.
원본 동료 이름과 스킬을 임시 이름이나 다른 캐릭터의 스킬로 덮어쓰지 않았다.

## P1 이후 검증 항목

- 세 히어로 각각에서 동일 3동료를 배치하고 실제 발동·사격 도달·쿨타임 표시 확인.
- 원본 이벤트 중복 호출과 파생 공격 재진입 시 추가 발동 0회.
- 보호막·회복 상한, 공격 주기 하한, 정지 중 시계 유지.
- 동료·특수 아이템이 없는 빌드는 새 효과가 발생하지 않음.
- 적격 후보 4개, 기존 장비 자동 삭제 없음, 런 종료 시 토큰·시계·아이템 초기화.
- 원본 장비·동료 ID·3단계 스킬·보유 수량이 전투 전후 동일함.

## P0 실행 검증 결과

- Win32 Debug 검토 실행 파일 `cs.allies-audit.exe` 빌드 성공.
- `tools/crew/verify_hero_allies_audit.ps1` 통과: 실제 로드된 64종의 이름,
  NPC/CMF/스킬 ID, 점유 크기와 기본 쿨타임이 생성한 목록과 모두 일치했다.
- 실제 애니메이션을 그린 검토 화면:
  [00~31](../../output/hero-allies-audit/existing-allies-0.png),
  [32~63](../../output/hero-allies-audit/existing-allies-1.png).
- 이 검토 경로는 별도 환경 변수로만 열리며 게임 내 동료 능력을 교체하지 않는다.

## v1 구현 검증

- `test_ally_links.py`: 원본 이벤트 중복·파생 재귀·런 ID 분리·정지·제거 시계 초기화 및
  64종 정의, 192개 연계, 상태이상 상한·만료·지속 피해·감전 소비·냉기 저항·출혈 중복 방지 통과.
- `verify_ally_balance.ps1`: 실제 그리드에 64종을 각 영웅과 배치하고 공격 주기를 확인했다.
  61종의 고유 능력과 183개 연계가 실제 처리 함수에서 발동하며 조건·중복·상한·종료 정리를 통과했다.
- `verify_ally_links.ps1`: 먼저 연결한 3종의 9개 영웅 연계, 실제 투사체 명중, 추가 쿨타임 표시,
  전투 정지와 런 종료를 각 영웅에서 통과했다.
- `verify_hero_allies_audit.ps1`: 런타임 64종의 원본 이름·ID·이미지·기존 스킬 및 새 점유·공격/능력 주기가
  목록의 값과 일치했다.
- 기존 전투 회귀: 장착 검 제외·머리 위 검·동료 2명 렌더링·쿨타임 표시·대포·몬스터 실제 공격·정지 시계 통과.
