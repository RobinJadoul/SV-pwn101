NAME := calculatron
ENTRYPOINT := /calculatron
BUILD_PRODUCTS := calculatron
EXTRA_FILES := flag.txt
SIDE_PRODUCTS :=
DIST := calculatron calculatron.c
PORT := 42002

include ../util/Makefile.base

calculatron: calculatron.c
	gcc -o calculatron calculatron.c -pie -Wl,-z,relro,-z,now -fno-stack-protector
