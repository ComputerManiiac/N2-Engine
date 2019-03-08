#include "MemoryAlloc.h"

MemoryAlloc::MemoryAlloc(const char* file, int line)
{
	this->file = strrchr(file, '\\') ? strrchr(file, '\\') + 1 : file;
	this->line = line;
}

MemoryAlloc::MemoryAlloc() {}
MemoryAlloc::~MemoryAlloc() {}

const char* MemoryAlloc::getFile() const
{
	return file;
}

const int& MemoryAlloc::getLine() const
{
	return line;
}

