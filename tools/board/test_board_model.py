from pathlib import Path
import subprocess
import sys
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'tools/content'))
import dump_ids
out=ROOT/'output/board-model'
out.mkdir(parents=True,exist_ok=True)
vcvars=dump_ids.find_vs()
assert vcvars
source=ROOT/'tools/board/test_board_model.cpp'
exe=out/'test_board_model.exe'
command=f'call "{vcvars}" >nul 2>&1 && cl /nologo /EHsc /std:c++14 /utf-8 /W4 "{source}" /Fe:"{exe}" /Fo:"{out / "test_board_model.obj"}"'
subprocess.run(command,shell=True,cwd=out,check=True)
subprocess.run([str(exe)],check=True)
