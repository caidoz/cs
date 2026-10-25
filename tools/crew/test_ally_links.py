"""Compile and execute the independent event/cooldown regression with MSVC."""
from pathlib import Path
import subprocess
import sys

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools/content'))
import dump_ids

out=ROOT/'output/ally-links-model'
out.mkdir(parents=True,exist_ok=True)
vcvars=dump_ids.find_vs()
assert vcvars, 'MSVC environment not found'
for name in ['test_ally_links','test_ally_balance']:
    source=ROOT/f'tools/crew/{name}.cpp'
    exe=out/f'{name}.exe'
    command=f'call "{vcvars}" >nul 2>&1 && cl /nologo /EHsc /std:c++14 /utf-8 "{source}" /Fe:"{exe}" /Fo:"{out / (name+".obj")}"'
    subprocess.run(command,shell=True,cwd=out,check=True)
    subprocess.run([str(exe)],check=True)
