#include "PhysicalMemory.hpp"
#include <string.h>

PhysicalMemory::PhysicalMemory()
	:entries(0), bs(256)
{
	
}

Word PhysicalMemory::read(int frame, int offset)
{
	return RAM[frame][offset];
}

int PhysicalMemory::loadPage(int algorithm, int frame)
{
	//Read in an entire frame from the backing store
	char fullFrame[256];
	bs.getFrame(fullFrame, frame);

	//Determine where in physical memory the frame will go
	int victim = 0;
	//FIFO
	if (algorithm)
	{
		victim = entries;
		entries++;
		entries %= 128;
	}


	//Read in each character from the frame into the physical memory
	for (int i = 0; i < 256; i++)
	{
		RAM[victim][i] = fullFrame[i];
	}

	//Let the caller know where that frame is stored in physical memory
	return victim;
}
