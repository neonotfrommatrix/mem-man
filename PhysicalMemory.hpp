#include "Word.hpp"
#include "BackingStore.hpp"
#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

class PhysicalMemory
{
public:
	PhysicalMemory();
	Word read(int, int);
	int loadPage(int replacementAlgorithm, int frame);
private:
	Word RAM[128][256];
	int entries;
	BackingStore bs;
};
#endif // !PHYSICAL_MEMORY_H