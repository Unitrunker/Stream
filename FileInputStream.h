#include <windows.h>
#include "Stream.h"
#include <tchar.h>

#pragma once

class FileInputStream : public IInputStream
{
	HANDLE _hFile;
	FileInputStream & operator = (const FileInputStream &never);
public:
	FileInputStream();
	bool Open(const TCHAR *strPath);
	virtual bool Read(unsigned char *pOctets, size_t iOctets, size_t &iRead);
	virtual void Close();
};
