#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lib7z.h"

int main(int argc, char *argv[], char *arge[])
{
	CSzArEx db;
	ISzAlloc allocImp;
	ISzAlloc allocTempImp;
	SRes res;
	CFileInStream archiveStream;
	CLookToRead2 lookStream;

	assert(argv != NULL && argv[1] != NULL);
	allocImp = g_Alloc;
	allocTempImp = g_Alloc;

	assert(!InFile_Open(&archiveStream.file, argv[1]));
	FileInStream_CreateVTable(&archiveStream);
	LookToRead2_CreateVTable(&lookStream, False);
	lookStream.buf = NULL;

	{
		lookStream.buf = ISzAlloc_Alloc(&allocImp, kInputBufSize);
		if (!lookStream.buf)
			res = SZ_ERROR_MEM;
		else
		{
			lookStream.bufSize = kInputBufSize;
			lookStream.realStream = &archiveStream.vt;
			LookToRead2_Init(&lookStream);
		}
	}


	CrcGenerateTable(); 
	SzArEx_Init(&db); 

	res = SzArEx_Open(&db, &lookStream.vt, &allocImp, &allocTempImp);
	
	{
		UInt32 i;
		UInt16 *temp = NULL;
		size_t tempSize = 0;
		UInt64 fileSize;
		size_t len;

		for (i = 0; i < db.NumFiles; i++)
		{
			len = SzArEx_GetFileNameUtf16(&db, i, NULL);
			{
				SzFree(NULL, temp);
				tempSize = len;
				temp = (UInt16 *)SzAlloc(NULL, tempSize * sizeof(temp[0]));
			}
			SzArEx_GetFileNameUtf16(&db, i, temp);
			fileSize = SzArEx_GetFileSize(&db, i);

			PrintString(temp);
			printf(" %10d\n", (int)fileSize);
		}
	}
	exit(0);
}
