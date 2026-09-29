import os

files = ['Classes/CastleMobilityNames.inc', 'Classes/CastleExteriorNames.inc', 'Classes/CastleRoomV4Names.inc']
for f in files:
    with open(f, 'r', encoding='utf-8') as fp:
        for line in fp:
            line = line.strip().strip(',').strip('"')
            if line and not line.startswith('//'):
                path = f'Resources/res/{line}.png'
                if not os.path.exists(path):
                    print(f'MISSING: {f} -> {line} ({path})')
print('Check completed.')
