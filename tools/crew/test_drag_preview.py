from pathlib import Path
import subprocess
import sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools/content'))
import dump_ids
out=ROOT/'output/drag-preview-review'
out.mkdir(parents=True,exist_ok=True)
vcvars=dump_ids.find_vs()
assert vcvars
source=ROOT/'tools/crew/test_drag_preview.cpp'
exe=out/'test_drag_preview.exe'
command=f'call "{vcvars}" >nul 2>&1 && cl /nologo /EHsc /std:c++14 /utf-8 "{source}" /Fe:"{exe}" /Fo:"{out / "test_drag_preview.obj"}"'
subprocess.run(command,shell=True,cwd=out,check=True)
subprocess.run([str(exe)],check=True)
