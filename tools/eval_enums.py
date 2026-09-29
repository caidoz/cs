import re

def eval_enums(header_path):
    enums = {}
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
                    # evaluate expr using enums dict
                    try:
                        # replace names with values
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

img_enums = eval_enums('Classes/Def/ImgDef.h')
print('TOTALIMG in ImgDef.h:', img_enums.get('TOTALIMG'))
print('MODCASTLE_V2_FIRST_IMG:', img_enums.get('MODCASTLE_V2_FIRST_IMG'))
print('CASTLE_ROOM_V4_FIRST_IMG:', img_enums.get('CASTLE_ROOM_V4_FIRST_IMG'))
print('CASTLE_BASE_FIRST_IMG:', img_enums.get('CASTLE_BASE_FIRST_IMG'))
print('CASTLE_WHEEL_FIRST_IMG:', img_enums.get('CASTLE_WHEEL_FIRST_IMG'))
print('STAGEBG_FIRST_IMG:', img_enums.get('STAGEBG_FIRST_IMG'))

# Also let's check in proj.win32/Debug.win32/cs.exe or write a test C++ program
