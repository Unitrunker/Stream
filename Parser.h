// Copyright © 2008-2011 Rick Parrish

#include "../Stream/Stream.h"
#include <string>
#include <vector>

// Left-matching recursive descent parser.
struct Parser
{
	Parser();
	// connect parser to an input stream.
	bool open(IInputStream *pStream);
	// close parsing
	void close();
	// True if parser has reached end of stream because of the read-ahead 
	// buffer, this is not the same as EOF on the underlying stream.
	// EOF true here means the parser has reached the end of the stream
	// eg. both the stream and the read-ahead buffer have been exhausted.
	bool eof();
	// match text but do not advance cursor (return pattern length).
	bool peekMatch(const char *strPattern, size_t &iLen);
	// match text but do not advance cursor.
	bool peekMatch(const char *strPattern);
	// match character but do not advance cursor.
	bool peekMatch(const char);
	// match text and advance cursor (return pattern length).
	bool parseMatch(const char *strPattern, size_t &iLen);
	// match text and advance cursor.
	bool parseMatch(const char *strPattern);
	// match character and advance cursor.
	bool parseMatch(const char);
	// get next character - but do not advance cursor.
	int peek();
	// get next character and advance cursor.
	int readChar();
	// consume count characters.
	bool consume(size_t iCount);
	// consume characters up to the delimiter.
	bool readText(std::string &strText, char chDelimiter);
	// skips / consumes whitespace.
	// bInside - true if inside an element declaration eg. between '<' and '>'.
	bool skipspace();
	// true if peek() returns an ASCII digit (may be base 10, hex, etc.)
	bool isdigit(unsigned char base = 10);
private:
	// replenish read-ahead buffer.
	void more();
	// the input stream.
	IInputStream *_pStream;
	// true when stream reaches EOF.
	bool _bEOF;
	// read-ahead buffer
	std::vector<char> _buffer;
	// number of characters in current buffer.
	size_t _iBuffer;
	// relative position in current buffer.
	size_t _iCursor;
};
