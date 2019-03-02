#include "MemoryLeak.hpp"

std::map<void*, MemoryAlloc> MemoryLeak::allocations = {};


void* operator new(size_t size, const char* file, int line)
{
	return MemoryLeak::Allocate(size, file, line);
}

void* operator new[](size_t size, const char* file, int line) {
	return MemoryLeak::Allocate(size, file, line);
}

void operator delete(void* ptr)
{
	std::map<void*, MemoryAlloc>* allocations = &MemoryLeak::allocations;
	if (allocations->find(ptr) != allocations->end())
	{
		allocations->erase(ptr);
		free(ptr);
	}
}

void operator delete[](void* ptr) {
	operator delete(ptr);
}

void operator delete(void* ptr, const char* file, int line)
{
	operator delete(ptr);
}


void* MemoryLeak::Allocate(size_t size, const char* file, int line)
{
	void* ptr = std::malloc(size);
	allocations[ptr] = MemoryAlloc(file, line);
	return ptr;
}

void MemoryLeak::Dump()
{

	for (auto &pair : allocations)
	{
		MemoryAlloc* alloc = &pair.second;
		std::cout << "[MEMORY LEAK] " << pair.first << ", " << alloc->getFile() << " at Line " << alloc->getLine() << std::endl;
		delete pair.first;
	}
}

