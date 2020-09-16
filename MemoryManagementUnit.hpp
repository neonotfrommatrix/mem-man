#include <iostream>
#include "TLB.hpp"
#include "AddressTranslator.hpp"
#include "BackingStore.hpp"
#include "PhysicalMemory.hpp"
#ifndef MMU_H
#define MMU_H

struct PageTable
{
	PageTable();
	int pageAddress[256];
	bool validPage[256];
};
class MemoryManagementUnit
{
public:
	MemoryManagementUnit(int RAMFrameCapacity, int frameSize, int replacement);
	void clearTLB();
	Word read(AddressTranslator);
	void printMetrics();
private:
	int RAMSize;
	int bytesInFrame;
	int page_access_count;
	int page_in_faults;
	TLB tlb;
	int tlb_access_count;
	int tlb_faults;
	PageTable pageTable;
	PhysicalMemory physicalMemory;
	int replacementAlgorithm;

};
#endif // !MMU_H