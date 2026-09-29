import os

with open('Classes/Text.h', 'r', encoding='utf-8', errors='ignore') as f:
    lines = f.readlines()

count = 0
in_array = False
inven_idx = -1
for i, line in enumerate(lines):
    line_s = line.strip()
    if 'textId[' in line_s or 'const char* const textId[]' in line_s or 'textId[]' in line_s or 'char* textId[' in line_s:
        in_array = True
        continue
    if in_array:
        if line_s.startswith('//') or not line_s:
            continue
        if line_s.startswith('#include'):
            parts = line_s.split('"')
            if len(parts) >= 2:
                inc_file = parts[1]
                inc_path = 'Classes/' + inc_file
                if os.path.exists(inc_path):
                    with open(inc_path, 'r', encoding='utf-8', errors='ignore') as inc_f:
                        for inc_line in inc_f:
                            inc_s = inc_line.strip()
                            if inc_s and not inc_s.startswith('//'):
                                count += 1
            continue
        if line_s.startswith('"'):
            if 'TEXT_GAMEMENU_SINGLEINVEN' in line:
                inven_idx = count
                print(f'TEXT_GAMEMENU_SINGLEINVEN string at array index: {count} (line {i+1})')
            if 'MODCASTLE_V2' in line or 'MODCASTLE' in line:
                print(f'MODCASTLE at array index: {count} (line {i+1}): {line_s[:30]}')
            if 'CASTLE_ROOM' in line:
                print(f'CASTLE_ROOM at array index: {count} (line {i+1}): {line_s[:30]}')
            count += 1
        if line_s.startswith('};'):
            break

print(f'Total strings in textId: {count}')
