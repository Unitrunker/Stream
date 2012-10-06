// Copyright © 2008-2011 Rick Parrish

#include "Parser.h"

Parser::Parser() : 
	_bEOF(false), _pStream(NULL), _iCursor(0), _iBuffer(0)
{
}

// connect parser to an input stream.
bool Parser::open(IInputStream *pStream)
{
	//if (_pFile)
	if (_pStream != NULL)
		_pStream->Close();
	_pStream = pStream;
	_bEOF = pStream == NULL;
	_iBuffer = 0;
	if (!_bEOF)
		_buffer.resize(1<<15, ' '); // 32k buffer
	return !_bEOF;
}

// close parsing
void Parser::close()
{
	if (_pStream != NULL)
		_pStream->Close();
	_pStream = NULL;
	_bEOF = true;
	_iCursor = 0;
	_iBuffer = 0;
}

// True if parser has reached end of stream
// because of the read-ahead buffer, this is not the same
// as EOF on the underlying stream.
// EOF true here means the parser has reached the end of the stream.
bool Parser::eof()
{
	if (_bEOF)
		return true;
	if (_iCursor < _iBuffer)
		return false;
	if (_iCursor == _iBuffer)
		more();
	return _bEOF;
}

// replenish read-ahead buffer.
void Parser::more()
{
	// half buffer size.
	size_t iLimit = _buffer.size() >> 1;
	// unprocessed data in buffer.
	size_t iCarry = _iBuffer - _iCursor;
	// left over data?
	if (iCarry > 0)
	{
		// yes: carry forward unprocessed data.
		char *buf = &_buffer[0];
		memcpy(buf, buf + _iCursor, iCarry);
	}
	// reset cursor to start of buffer.
	_iCursor = 0;
	// update buffer length
	_iBuffer = iCarry;
	// read-ahead buffer gotten to small?
	if (iCarry < iLimit)
	{
		// yes: read more to keep it full.

		// compute free space.
		size_t iFree = _buffer.size() - iCarry;
		size_t iRead = 0;
		// don't read more than half a buffer "chunk".
		// code will tend to read data in half-buffer chunks.
		// for predictable block IO behavior.
		if (iFree > iLimit) iFree = iLimit;
		// synchronously read more content into buffer.
		_pStream->Read((unsigned char *)&_buffer[iCarry], iFree, iRead);
		// update size of buffer.f
		_iBuffer = iCarry + iRead;
		// nothing left in stream?
		if (_iBuffer == 0) _bEOF = true;
	}
}

// low-level - match text but do not advance cursor.
bool Parser::peekMatch(const char *strPattern)
{
	size_t iIgnore = 0;
	return peekMatch(strPattern, iIgnore);
}

// low-level - match text but do not advance cursor.
bool Parser::peekMatch(const char *strPattern, size_t &iLen)
{
	size_t i = 0;
	while (true)
	{
		if (strPattern[i] == 0)
			return true;

		if ( (_iCursor + i) >= _iBuffer )
			more();

		if ( (_iCursor + i) >= _iBuffer )
			return false;

		if (strPattern[i] != _buffer[_iCursor + i])
			return false;

		i++;
	}
}

// low-level - match character but do not advance cursor.
bool Parser::peekMatch(const char chPattern)
{
	return !eof() && _iCursor < _iBuffer && _buffer[_iCursor] == chPattern;
}

// low-level - match text and advance cursor.
bool Parser::parseMatch(const char *strPattern, size_t &iLen)
{
	bool bOK = peekMatch(strPattern, iLen);
	if (bOK)
		_iCursor += iLen;
	return bOK;
}

// low-level - match text and advance cursor.
bool Parser::parseMatch(const char *strPattern)
{
	size_t iLen = 0;
	bool bOK = peekMatch(strPattern, iLen);
	if (bOK)
		_iCursor += iLen;
	return bOK;
}

// low-level - match character and advance cursor.
bool Parser::parseMatch(const char chPattern)
{
	bool bOK = peekMatch(chPattern);
	if (bOK)
		_iCursor += 1;
	return bOK;
}

// get next character - but do not advance cursor.
int Parser::peek()
{
	if ( !eof() )
		return _buffer[_iCursor];
	return -1;
}

// consume count characters.
bool Parser::consume(size_t iCount)
{
	size_t iRemains = _iBuffer - _iCursor;
	if (iRemains < iCount)
		more();
	_iCursor += iCount;
	return _iCursor <= _iBuffer;
}

// skips / consumes whitespace.
bool Parser::skipspace()
{
	while ( peekMatch(' ') || peekMatch('\t') || peekMatch('\r') || peekMatch('\n') )
		consume(1);
	return true;
}

// consume characters up to the delimiter.
bool Parser::readText(std::string &strText, char chDelimiter)
{
	strText.reserve(128);
	while ( !eof() )
	{
		int ch = peek();
		if (ch == chDelimiter) 
			return true;
		strText += (char)ch;
		consume(1);
	}
	return strText.size() > 0;
}

