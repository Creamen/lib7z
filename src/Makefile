.DEFAULT_GOAL := lib7z.so

SDK_PATH := ../sdk/C
IN_C := 7zAlloc.c  7zArcIn.c  7zBuf2.c  7zBuf.c  7zCrc.c  7zCrcOpt.c  7zDec.c  7zFile.c  7zStream.c CpuArch.c LzmaDec.c Lzma2Dec.c Bra86.c Bra.c BraIA64.c Bcj2.c Delta.c

CC := gcc
CFLAGS = -Wall -fPIC -O3 -march=native

%.c:
	$(CC) $(CFLAGS) -g $(SDK_PATH)/$(@F) -c

lib7z.so: $(IN_C)
	@mkdir -p ../lib
	$(CC) -shared $(IN_C:.c=.o) -flto -o ../lib/lib7z.so

clean:
	rm -f *.o ../lib/lib7z.so
