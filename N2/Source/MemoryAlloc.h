#ifndef MEMORYALLOC_H
#define MEMORYALLOC_H

#include <string>

class MemoryAlloc
{
public:
	MemoryAlloc(const char* file, int line);
	MemoryAlloc();
	~MemoryAlloc();
	const char* getFile() const;
	const int& getLine() const;
private:
	const char* file;
	int line;
};

#endif