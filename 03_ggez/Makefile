NAME := ggez
ENTRYPOINT := /ggez
BUILD_PRODUCTS := ggez
EXTRA_FILES := flag.txt
SIDE_PRODUCTS :=
DIST := ggez ggez.c
PORT := 42003

include ../util/Makefile.base

ggez: ggez.c
	gcc -o ggez ggez.c -no-pie -fno-stack-protector
