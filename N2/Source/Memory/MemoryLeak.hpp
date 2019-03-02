#ifndef MEMORYLEAK_H
#define MEMORYLEAK_H


#include "MemoryAlloc.h"
#include <iostream>
#include <map>

extern void* operator new(size_t size, const char* file, int line);
extern void* operator new[](size_t size, const char* file, int line);
extern void operator delete(void* ptr);
extern void operator delete[](void* ptr);
extern void operator delete(void* ptr, const char* file, int line);

class MemoryLeak {

public:
	static void* Allocate(size_t size, const char * file, int line);
	static void Dump();
	static std::map<void*, MemoryAlloc> allocations;

};

#endif
