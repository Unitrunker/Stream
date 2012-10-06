#include <stddef.h>

#pragma once

struct IInputStream
{
	virtual bool Read(unsigned char *pOctets, size_t iOctets, size_t &iRead) = 0;
	virtual void Close() = 0;
};

struct IOutputStream
{
	virtual bool Write(unsigned char *pOctets, size_t iOctets, size_t &iWrote) = 0;
	virtual void Close() = 0;
};
