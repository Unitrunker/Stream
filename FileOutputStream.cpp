#include "FileOutputStream.h"

FileOutputStream::FileOutputStream() : _hFile(INVALID_HANDLE_VALUE)
{
}

bool FileOutputStream::Open(const TCHAR *strPath)
{
	_hFile = CreateFile(strPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	return _hFile != INVALID_HANDLE_VALUE;
}

bool FileOutputStream::Write(unsigned char *pOctets, size_t iOctets, size_t &iWrote)
{
	DWORD dwWrote = 0;
	bool bOK = WriteFile(_hFile, pOctets, (DWORD)iOctets, &dwWrote, NULL) != FALSE;
	iWrote = (size_t)dwWrote;
	return bOK;
}

void FileOutputStream::Close()
{
	CloseHandle(_hFile);
	_hFile = INVALID_HANDLE_VALUE;
}
