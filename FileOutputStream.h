#include <windows.h>
#include "Stream.h"
#include <tchar.h>

#pragma once

class FileOutputStream : public IOutputStream
{
	HANDLE _hFile;
public:
	FileOutputStream();
	bool Open(const TCHAR *strPath);
	virtual bool Write(unsigned char *pOctets, size_t iOctets, size_t &iWrote);
	virtual void Close();
};

