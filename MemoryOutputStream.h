#include "Stream.h"
#include <vector>

#pragma once

struct MemoryOutputStream : public IOutputStream
{
	size_t _iSanity;
public:
	std::vector<unsigned char> _octets;

	MemoryOutputStream(size_t);
	bool Open();
	virtual bool Write(unsigned char *pOctets, size_t iOctets, size_t &iWrote);
	virtual void Close();
};

