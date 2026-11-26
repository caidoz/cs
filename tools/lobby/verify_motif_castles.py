"""Review every used castle hull in the native lobby and battle at both ratios."""
from pathlib import Path
import importlib.util
import subprocess,sys

root=Path(__file__).resolve().parents[2]
spec=importlib.util.spec_from_file_location('runtime_review',root/'tools/items/verify_runtime.py')
review=importlib.util.module_from_spec(spec);spec.loader.exec_module(review)
review.EXE=root/'proj.win32/Debug.win32/cs_motif_castles.exe'
for height in (850,1408):
    review.run(height,{'CS_PORTRAIT_REVIEW':'1','CS_PORTRAIT_LOBBY':'1','CS_MOTIF_SERIES_REVIEW':'1'},
               f'motif-castles-{height}','DONE motif series review',38)
    review.run(height,{'CS_PORTRAIT_REVIEW':'1','CS_PORTRAIT_STAGE':'0','CS_PORTRAIT_CATAPULT':'1'},
               f'motif-catapult-{height}','DONE portrait review',5)
    review.run(height,{'CS_PORTRAIT_REVIEW':'1','CS_PORTRAIT_STAGE':'0','CS_PORTRAIT_LOBBY':'1','CS_BASE_CAMP_REVIEW':'1'},
               f'motif-camp-{height}','DONE portrait review',6)
