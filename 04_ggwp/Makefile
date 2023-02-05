NAME := ggwp
ENTRYPOINT := /ggwp
BUILD_PRODUCTS := ggwp
EXTRA_FILES := flag.txt
SIDE_PRODUCTS :=
DIST := ggwp ggwp.c
PORT := 42004

include ../util/Makefile.base

ggwp: ggwp.c
	gcc -fcall-saved-rdi -O1 -o ggwp ggwp.c -no-pie -fno-stack-protector
