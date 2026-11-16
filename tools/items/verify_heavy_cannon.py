"""Verify all artillery types with the heavy-round preview build."""
from pathlib import Path
import importlib.util

ROOT=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('runtime',ROOT/'tools/items/verify_runtime.py')
runtime=importlib.util.module_from_spec(spec);spec.loader.exec_module(runtime)
runtime.EXE=ROOT/'proj.win32/Debug.win32/cs_heavy_cannon.exe'
for height in (850,1408):
    runtime.run(height,{'CS_MERGE_TURRET_REVIEW':'1'},f'heavy-cannon-{height}','DONE turret attack review',40)
