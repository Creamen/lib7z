all: lib/lib7z.so headers

lzma-sdk: sdk/lzma1801.7z
	@7z x -osdk -y sdk/lzma1801.7z > /dev/null;

sdk/lzma1801.7z:
	@# https://www.7-zip.org/sdk.html \
	mkdir -p sdk; \
	curl -Ls https://www.7-zip.org/a/lzma1801.7z > sdk/lzma1801.7z

lib/lib7z.so:
	make -C src

headers: include
	@for h in sdk/C/Precomp.h sdk/C/CpuArch.h sdk/C/7z.h sdk/C/7zAlloc.h \
		sdk/C/7zBuf.h sdk/C/7zCrc.h sdk/C/7zFile.h sdk/C/7zVersion.h \
		sdk/C/Compiler.h sdk/C/7zTypes.h; do \
		cp -fLv $$h include/; \
	done

include:
	mkdir -p include

clean:
	make -C src clean
