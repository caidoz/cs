"""Read-only audit of the 64 existing companions; never assigns draft C-slots."""
import csv
import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools/content'))
import dump_ids


def rows(name):
    with (ROOT / 'content' / f'{name}.tsv').open(encoding='utf-8-sig') as source:
        return list(csv.DictReader((line for line in source if not line.startswith('#')), delimiter='\t'))


def main():
    crews = rows('crew')
    enemies = {r['enum_name']: r for r in rows('enemy') if r['enum_name']}
    skills = {int(r['id']): r for r in rows('skill')}
    assert len(crews) == 64
    requested = {'TOTAL_CREW', 'CREW_GRID_W', 'CREW_GRID_H', 'FPS'}
    balance_path=ROOT/'content/hero_allies_balance.tsv'
    balance={}
    if balance_path.exists():
        with balance_path.open(encoding='utf-8') as source:
            balance={int(r['id']):r for r in csv.DictReader(source,delimiter='\t')}
    for crew in crews:
        requested.update(crew[k] for k in ('enum_name', 'enemy_type', 'skill1', 'skill2', 'skill3'))
        requested.add(enemies[crew['enemy_type']]['cmf'])
    values = dump_ids.ask_compiler(sorted(requested))
    if values is None:
        raise RuntimeError('C++ enum probe failed')
    source = (ROOT / 'Classes/Func_Draw.cpp').read_text(encoding='utf-8-sig')
    roles = {int(i): role for role, i in re.findall(r'(CREW_ROLE_\w+),\s*//\s*(\d+)\s+NPC_', source)}
    result = []
    for crew in crews:
        enemy = enemies[crew['enemy_type']]
        index = int(crew['id'])
        tuning=balance.get(index)
        assert values[crew['enum_name']] == index
        cmf = values[enemy['cmf']]
        asset = f'Resources/res/c{cmf}.png'
        assert (ROOT / asset).is_file(), asset
        entry = dict(crew_id=index, crew_enum=crew['enum_name'], name=enemy['label'],
                     npc_id=values[crew['enemy_type']], npc_enum=crew['enemy_type'],
                     cmf_id=cmf, cmf_enum=enemy['cmf'], sprite=asset,
                     motion_source=f'Classes/Cmf/c{cmf}.h', role=roles.get(index, 'UNKNOWN'),
                     grid=f"{tuning['cols']}x{tuning['rows']}" if tuning else f"{values['CREW_GRID_W']}x{values['CREW_GRID_H']}",
                     base_cooldown_frames=int(crew['boss_cool']),
                     attack_cooldown_frames=round(float(tuning['attack_seconds'])*values['FPS']) if tuning else int(crew['boss_cool']),
                     ability_cooldown_frames=round(float(tuning['ability_seconds'])*values['FPS']) if tuning else 0,
                     draft_slot='EXISTING_ID_BALANCE_V1' if tuning else 'UNASSIGNED')
        for level in range(1, 4):
            symbol = crew[f'skill{level}']
            skill_id = values[symbol]
            skill = skills.get(skill_id, {})
            entry[f'skill{level}_id'] = skill_id
            entry[f'skill{level}_enum'] = symbol
            entry[f'skill{level}_name'] = skill.get('label', '')
            entry[f'skill{level}_kind'] = skill.get('kind', '')
            entry[f'skill{level}_hero'] = skill.get('hero_type', '')
        result.append(entry)
    assert len({r['npc_id'] for r in result}) == 64
    out = ROOT / 'reports/hero_allies_64'
    out.mkdir(parents=True, exist_ok=True)
    with (out / 'catalog.tsv').open('w', encoding='utf-8-sig', newline='') as target:
        writer = csv.DictWriter(target, fieldnames=list(result[0]), delimiter='\t')
        writer.writeheader()
        writer.writerows(result)
    (out / 'catalog.json').write_text(json.dumps(result, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')
    lines = ['# 실제 동료 64종 매핑표', '',
             '기존 ID·표시 이름·리소스·스킬과 현재 적용한 점유·공격 주기를 조사한 표입니다. 임시 C이름으로 기존 이름을 덮어쓰지 않습니다.', '',
             '| ID | 실제 이름 | NPC ID / enum | CMF / 리소스 | 스킬 ID (1/2/3) | 크기 | 기본 쿨타임 |',
             '|---|---|---|---|---|---|---|']
    for row in result:
        skill_ids = '/'.join(str(row[f'skill{n}_id']) for n in range(1,4))
        lines.append(f"| {row['crew_id']} | {row['name']} | {row['npc_id']} / `{row['npc_enum']}` | {row['cmf_id']} / [이미지](../../{row['sprite']}) | {skill_ids} | {row['grid']} | {row['attack_cooldown_frames']} frames |")
    lines += ['', '스킬 이름·종류·호출 영웅과 원본 enum은 catalog.tsv / catalog.json을 확인하세요.',
              '기존 역할 배속 및 전투 가속 효과는 기본 쿨타임과 별도로 적용됩니다.', '']
    (out / 'CATALOG.md').write_text('\n'.join(lines), encoding='utf-8')
    print('PASS 64 unique companion IDs, NPC IDs and existing sprites; original names preserved')


if __name__ == '__main__':
    main()
