#include "MemoryManagementUnit.hpp"
#include <iomanip>

MemoryManagementUnit::MemoryManagementUnit(int RAMFrameCapacity, int frameSize, int replacement)
	: RAMSize(RAMFrameCapacity), bytesInFrame(frameSize), page_access_count(0), page_in_faults(0), tlb(replacement), tlb_access_count(0), tlb_faults(0),
	pageTable(), physicalMemory(), replacementAlgorithm(replacement)
{

}

void MemoryManagementUnit::clearTLB()
{
	tlb.clear();
}

Word MemoryManagementUnit::read(AddressTranslator AT)
{
	int page = AT.getPage();
	int offset = AT.getOffset();

	//Look in the TLB first. If it returns -1, that means it is not in the TLB,
	//		so we look in the page table next.
	int frame = tlb.getFrame(AT.getPage());
	tlb_access_count++;
	if (frame == -1)
	{
		tlb_faults++;
		page_access_count++;
		//Check if the page is already loaded
		if (pageTable.validPage[page])
		{
			//Get the physical address of the request
			int physicalAddress = pageTable.pageAddress[page];

			tlb.insert(page, physicalAddress);
			return physicalMemory.read(physicalAddress, offset);
		}
		else
		{
			page_in_faults++;
			int victim = physicalMemory.loadPage(replacementAlgorithm, page);
			//Set the victim's bit to invalid
			for (int i = 0; i < 256; i++)
			{
				if (pageTable.pageAddress[i] == victim)
				{
					//Resetting the info of the victim page
					pageTable.pageAddress[i] = -1;
					pageTable.validPage[i] = false;

					break;
				}
				
			}
			//Set the new page as valid
			int newAddress = victim;
			pageTable.pageAddress[page] = newAddress;
			pageTable.validPage[page] = true;

			tlb.insert(page, newAddress);
			return physicalMemory.read(newAddress, offset);
		}
	}
	else
		return physicalMemory.read(frame, offset);
}

void MemoryManagementUnit::printMetrics()
{
	std::cout << "\n\n***** Program Metrics *****\n";
	if (replacementAlgorithm == 1)
		std::cout << "Replacement Method: First In First Out (FIFO)\n";
	else
		std::cout << "Replacement Method: Least Recently Used (LRU)\n";
	std::cout << "Page accesses: " << page_access_count << std::endl;
	std::cout << "Page faults: " << page_in_faults << std::endl;
	std::cout << "TLB accesses: " << tlb_access_count << std::endl;
	std::cout << "TLB faults: " << tlb_faults << std::endl;
	std::cout << "Page fault percentage: " << std::fixed << std::setprecision(2) << 100 * (static_cast<float>(page_in_faults) / static_cast<float>(tlb_access_count)) << std::endl;
	std::cout << "TLB resolution percentage: " << std::fixed << std::setprecision(2) << 100 * (static_cast<float>((tlb_access_count - tlb_faults)) / static_cast<float>(tlb_access_count)) << std::endl;
	std::cout << "***************************\n\n";
}

PageTable::PageTable()
	: pageAddress{ 0 }
{
	for (int i = 0; i < 256; i++)
	{
		pageAddress[i] = -1;
		validPage[i] = false;
	}
}
