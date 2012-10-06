#include "MemoryInputStream.h"

MemoryInputStream::MemoryInputStream(const unsigned char *memory, size_t limit) : _memory(memory), _limit(limit), _cursor(0)
{
}

bool MemoryInputStream::Read(unsigned char *pOctets, size_t iOctets, size_t &iRead)
{
	size_t iRemains = _limit - _cursor;

	if (iRemains > 0)
	{
		if (iOctets > iRemains)
			iOctets = iRemains;
		memcpy(pOctets, _memory + _cursor, iOctets);
		iRead = iOctets;
		_cursor += iOctets;
		return true;
	}
	return false;
}

void MemoryInputStream::Close()
{
	_cursor = 0;
}
