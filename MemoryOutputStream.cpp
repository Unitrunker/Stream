#include "MemoryOutputStream.h"

MemoryOutputStream::MemoryOutputStream(size_t iSanity) : _iSanity(iSanity)
{
}

bool MemoryOutputStream::Open()
{
	_octets.clear();
	return true;
}

bool MemoryOutputStream::Write(unsigned char *pOctets, size_t iOctets, size_t &iWrote)
{
	if ( ( iOctets + _octets.size() ) > _iSanity )
		return false;

	_octets.insert(_octets.end(), pOctets, pOctets + iOctets);
	iWrote = iOctets;
	return true;
}

void MemoryOutputStream::Close()
{
	// do nothing.
}
