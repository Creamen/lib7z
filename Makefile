all: lib/lib7z.so

lzma-sdk: sdk/lzma1801.7z
	@7z x -osdk -y sdk/lzma1801.7z > /dev/null;

sdk/lzma1801.7z:
	@# https://www.7-zip.org/sdk.html \
	mkdir -p sdk; \
	curl -Ls https://www.7-zip.org/a/lzma1801.7z > sdk/lzma1801.7z

lib/lib7z.so:
	make -C src

clean:
	make -C src clean
