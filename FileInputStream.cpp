#include "FileInputStream.h"

FileInputStream::FileInputStream() : _hFile(INVALID_HANDLE_VALUE)
{
}

bool FileInputStream::Open(const TCHAR *strPath)
{
	_hFile = CreateFile(strPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return _hFile != INVALID_HANDLE_VALUE;
}

bool FileInputStream::Read(unsigned char *pOctets, size_t iOctets, size_t &iRead)
{
	DWORD dwRead = 0;
	bool bOK = ReadFile(_hFile, pOctets, (DWORD)iOctets, &dwRead, NULL) != FALSE;
	iRead = (size_t)dwRead;
	return bOK;
}

void FileInputStream::Close()
{
	CloseHandle(_hFile);
	_hFile = INVALID_HANDLE_VALUE;
}
