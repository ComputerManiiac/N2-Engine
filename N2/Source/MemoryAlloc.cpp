#include "MemoryAlloc.h"

MemoryAlloc::MemoryAlloc(const char* file, int line)
{
	this->file = strrchr(file, '\\') ? strrchr(file, '\\') + 1 : file;
	this->line = line;
}

MemoryAlloc::MemoryAlloc() {}
MemoryAlloc::~MemoryAlloc() {}

const char* MemoryAlloc::getFile()
{
	return file;
}

int& MemoryAlloc::getLine()
{
	return line;
}

