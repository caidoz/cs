"""Validate PE/PDB RSDS identity and current source CodeView SHA256 records."""
from pathlib import Path
import argparse, hashlib, struct

parser=argparse.ArgumentParser()
parser.add_argument('executable',type=Path)
parser.add_argument('pdb',type=Path)
parser.add_argument('sources',nargs='+',type=Path)
args=parser.parse_args()
pdb=args.pdb.read_bytes();exe=args.executable.read_bytes()
assert pdb.startswith(b'Microsoft C/C++ MSF 7.00'), 'Not a native MSF7 PDB'
block_size,_,_,directory_size,_,block_map=struct.unpack_from('<6I',pdb,32)
directory_blocks=(directory_size+block_size-1)//block_size
blocks=struct.unpack_from(f'<{directory_blocks}I',pdb,block_map*block_size)
directory=b''.join(pdb[b*block_size:(b+1)*block_size] for b in blocks)[:directory_size]
count=struct.unpack_from('<I',directory,0)[0]
sizes=struct.unpack_from(f'<{count}I',directory,4)
cursor=4+4*count;info=None
for index,size in enumerate(sizes):
    block_count=0 if size==0xffffffff else (size+block_size-1)//block_size
    stream_blocks=struct.unpack_from(f'<{block_count}I',directory,cursor) if block_count else ()
    cursor+=block_count*4
    if index==1:
        info=b''.join(pdb[b*block_size:(b+1)*block_size] for b in stream_blocks)[:size]
        break
assert info is not None and len(info)>=28
age=struct.unpack_from('<I',info,8)[0];guid=info[12:28]
signature=b'RSDS'+guid+struct.pack('<I',age)
offset=exe.find(signature)
assert offset>=0, 'Executable and PDB GUID/age differ'
embedded=exe[offset+24:].split(b'\0',1)[0].decode('utf-8',errors='replace')
print(f'PASS EXE/PDB GUID and age; embedded symbols: {embedded}')
for source in args.sources:
    digest=hashlib.sha256(source.read_bytes()).digest()
    # A CodeView file-checksum record prefixes the digest with byte length and
    # algorithm (0x20=32 bytes; 0x03=SHA256). Fresh /ZH:SHA_256 builds emit these.
    assert b'\x20\x03'+digest in pdb, f'Current source checksum absent: {source}'
    print(f'PASS CodeView SHA256 {source}: {digest.hex()}')
