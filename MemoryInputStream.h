#include <windows.h>
#include "Stream.h"
#include <tchar.h>

#pragma once

class MemoryInputStream : public IInputStream
{
	const unsigned char *_memory;
	size_t _cursor;
	const size_t _limit;
	MemoryInputStream & operator = (const MemoryInputStream &never);
public:
	MemoryInputStream(const unsigned char *memory, size_t limit);
	virtual bool Read(unsigned char *pOctets, size_t iOctets, size_t &iRead);
	virtual void Close();
};
