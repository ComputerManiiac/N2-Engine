#ifndef MEMORYALLOC_H
#define MEMORYALLOC_H

#include <string>

class MemoryAlloc
{
public:
	MemoryAlloc(const char* file, int line);
	MemoryAlloc();
	~MemoryAlloc();
	const char* getFile();
	int& getLine();
private:
	const char* file;
	int line;
};

#endif