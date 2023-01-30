NAME := secure_logon
ENTRYPOINT := /secure_logon
BUILD_PRODUCTS := secure_logon
SIDE_PRODUCTS :=
DIST := secure_logon secure_logon.c
PORT := 42001

include ../util/Makefile.base

secure_logon: secure_logon.c
	gcc -O3 -o secure_logon secure_logon.c -pie -Wl,-z,relro,-z,now
