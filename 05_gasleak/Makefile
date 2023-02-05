NAME := gasleak
ENTRYPOINT := /gasleak
BUILD_PRODUCTS := gasleak
EXTRA_FILES := flag.txt
SIDE_PRODUCTS :=
DIST := gasleak gasleak.c
PORT := 42005

include ../util/Makefile.base

gasleak: gasleak.c
	gcc -fcall-saved-rdi -O1 -o gasleak gasleak.c -fno-stack-protector
