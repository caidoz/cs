from pathlib import Path
import ctypes,time,subprocess,os,shutil
from ctypes import wintypes
root=Path(__file__).resolve().parents[2]
work=root/'asset_library/work/rollback-tour-20261126';work.mkdir(parents=True,exist_ok=True)
shutil.copy2(Path(__file__).with_name('current_version_tour_caption.txt'),work/'video-caption.txt')
out=work/'session';out.mkdir(exist_ok=True)
(out/'phases.log').write_text('');(out/'recording.start').unlink(missing_ok=True)
env=dict(os.environ,CS_CURRENT_VERSION_TOUR='1',CS_CASTLE_REVIEW_PATH=out.as_posix()+'/',CS_BATTLE_MENU_REVIEW='1',CS_BATTLE_MENU_HEIGHT='850')
u=ctypes.windll.user32;u.SetProcessDPIAware()
si=subprocess.STARTUPINFO();si.dwFlags|=subprocess.STARTF_USESHOWWINDOW;si.wShowWindow=1
log=(out/'game.log').open('w')
game=subprocess.Popen([str(root/'proj.win32/Debug.win32/cs_rollback_tour.exe')],cwd=root/'Resources',env=env,startupinfo=si,stdout=log,stderr=log)
rec=None
try:
 hwnd=0;deadline=time.monotonic()+45
 while not hwnd and time.monotonic()<deadline:
  found=[]
  @ctypes.WINFUNCTYPE(wintypes.BOOL,wintypes.HWND,wintypes.LPARAM)
  def enum(h,l):
   pid=wintypes.DWORD();u.GetWindowThreadProcessId(h,ctypes.byref(pid))
   if pid.value==game.pid and u.IsWindowVisible(h):found.append(h)
   return True
  u.EnumWindows(enum,0)
  if found:hwnd=found[0]
  if game.poll() is not None:raise RuntimeError('Game exited')
  time.sleep(.1)
 if not hwnd:raise RuntimeError('No recording window')
 u.ShowWindow(hwnd,9);u.SetForegroundWindow(hwnd);time.sleep(3)
 title=ctypes.create_unicode_buffer(256);u.GetWindowTextW(hwnd,title,256)
 raw=work/'current-version-rollback-raw.mp4'
 ff=(work/'record.log').open('w')
 rec=subprocess.Popen([shutil.which('ffmpeg'),'-hide_banner','-loglevel','warning','-f','gdigrab','-framerate','30','-i','title='+title.value,'-an','-c:v','libx264','-preset','ultrafast','-crf','19','-pix_fmt','yuv420p','-y',str(raw)],stdin=subprocess.PIPE,stdout=ff,stderr=ff,creationflags=subprocess.CREATE_NO_WINDOW)
 time.sleep(.6);(out/'recording.start').write_text('start')
 begin=time.monotonic()
 while time.monotonic()-begin<61:
  trace=(out/'phases.log').read_text(encoding='utf8',errors='replace')
  if 'FAIL' in trace:raise RuntimeError(trace)
  if 'DONE current version tour' in trace:break
  if game.poll() is not None:raise RuntimeError('Game exited')
  time.sleep(.15)
 else:raise RuntimeError('Tour timeout')
 print(trace,flush=True)
 rec.communicate(b'q\n',timeout=15);rec=None;ff.close()
 # Local capture only; annotate the isolated final-boss resume fixture honestly.
 final=work/'current-version-first-castle-rollback.mp4'
 vf="pad=iw:ih+40:0:0:color=0x07111b,drawtext=fontfile='C\\:/Windows/Fonts/malgun.ttf':textfile='video-caption.txt':fontcolor=white:fontsize=16:x=(w-tw)/2:y=h-29"
 subprocess.run([shutil.which('ffmpeg'),'-hide_banner','-loglevel','error','-i',str(raw),'-vf',vf,'-c:v','libx264','-preset','fast','-crf','20','-movflags','+faststart','-an','-t','59','-y',str(final)],cwd=work,creationflags=subprocess.CREATE_NO_WINDOW,check=True)
 print('SAVED',final,flush=True)
finally:
 if rec and rec.poll() is None:rec.communicate(b'q\n',timeout=10)
 if game.poll() is None:game.terminate()
 game.wait(timeout=10);log.close()
