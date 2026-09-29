import re

def eval_enums(header_path, initial_enums=None):
    enums = dict(initial_enums or {})
    last_val = -1
    with open(header_path, 'r', encoding='utf-8', errors='ignore') as f:
        for line in f:
            line = re.sub(r'//.*', '', line).strip()
            if not line or line.startswith('#'):
                continue
            if '{' in line or '}' in line or 'enum' in line or ';' in line:
                line = line.replace('{', '').replace('}', '').replace(';', '').replace('enum', '').strip()
            parts = [p.strip() for p in line.split(',') if p.strip()]
            for part in parts:
                if '=' in part:
                    name, expr = part.split('=', 1)
                    name = name.strip()
                    expr = expr.strip()
                    try:
                        val_expr = expr
                        for k in sorted(enums.keys(), key=len, reverse=True):
                            val_expr = re.sub(r'\b' + k + r'\b', str(enums[k]), val_expr)
                        val = eval(val_expr)
                        enums[name] = val
                        last_val = val
                    except Exception as e:
                        pass
                elif part.isidentifier():
                    last_val += 1
                    enums[part] = last_val
    return enums

# We also need values defined in Def.h if any
def_enums = eval_enums('Classes/Def.h')
img_enums = eval_enums('Classes/Def/ImgDef.h', def_enums)
all_enums = dict(img_enums)
all_enums.update(def_enums)

text_enums = eval_enums('Classes/Def/TextDef.h', all_enums)

img_start = text_enums.get('TEXT_IMGNAME_START')
inven_enum = text_enums.get('TEXT_GAMEMENU_SINGLEINVEN')
total_img = img_enums.get('TOTALIMG')

print(f'TEXT_IMGNAME_START: {img_start}')
print(f'TOTALIMG: {total_img}')
print(f'Calculated TEXT_GAMEMENU_SINGLEINVEN (img_start + TOTALIMG): {img_start + total_img if img_start and total_img else None}')
print(f'Actual TEXT_GAMEMENU_SINGLEINVEN in TextDef.h: {inven_enum}')
