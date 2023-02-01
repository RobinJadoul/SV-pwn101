NAME := secure_logon
ENTRYPOINT := /secure_logon
BUILD_PRODUCTS := secure_logon
EXTRA_FILES := flag.txt some_super_secret_f1l3n4m3_that_you_wont_guess.txt
SIDE_PRODUCTS :=
DIST := secure_logon secure_logon.c /lib/x86_64-linux-gnu/libc.so.6
PORT := 42001

include ../util/Makefile.base

secure_logon: secure_logon.c
	gcc -O3 -o secure_logon secure_logon.c -pie -Wl,-z,relro,-z,now
