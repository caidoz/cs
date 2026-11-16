"""Check scaled shadow clipping and capture moving reel symbols at two sizes."""
from pathlib import Path
import importlib.util

ROOT=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('runtime',ROOT/'tools/items/verify_runtime.py')
runtime=importlib.util.module_from_spec(spec);spec.loader.exec_module(runtime)
runtime.EXE=ROOT/'proj.win32/Debug.win32/cs_reel_shadow.exe'
for height in (850,1408):
    runtime.run(height,{'CS_REEL_SHADOW_REVIEW':'1'},f'reel-shadow-{height}','DONE reel shadow review',6)
    runtime.run(height,{'CS_MIST_RESOURCE_REVIEW':'1'},f'reel-shadow-scene-{height}','DONE mist resource review',35)
