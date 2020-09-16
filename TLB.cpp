#include "TLB.hpp"

TLB::TLB(int alg)
	: pages{ -1 }, frames{ -1 }, accesses(0), faults(0), algorithm(alg), index(0)
{
	clear();
}

int TLB::getFrame(int page)
{
	for (int i = 0; i < 16; i++)
	{
		//Look through the table to see if the page is loaded.
		if (pages[i] == page)
		{	//If LRU is set, then the table must be reordered
			if (algorithm == 2)
			{
				int topPage = pages[i];
				int topFrame = frames[i];
				
				//Shift down all entries above i by one
				for (int x = i - 1; x >= 0; x--)
				{
					pages[x + 1] = pages[x];
					frames[x + 1] = frames[x];
				}
				pages[0] = topPage;
				frames[0] = topFrame;

				return frames[0];
			}
			//If FIFO is set, the ordering does not need to change
			return frames[i];

		}
		if (pages[i] == -1)
			break;
	}
	//The page is not in the table, -1 reflects this
	return -1;
}

void TLB::clear()
{
	for (int i = 0; i < 16; i++)
	{
		pages[i] = -1;
		frames[i] = -1;
	}
}

void TLB::insert(int page, int frame)
{
	//Use LRU
	if (algorithm == 1)
	{
		for (int i = 15; i > 0; i--)
		{
			pages[i] = pages[i - 1];
			frames[i] = frames[i - 1];
		}
		pages[0] = page;
		frames[0] = frame;

		//Keep track of the size of entries in the table
		index = 16 < index + 1 ? 16 : index + 1;
	}
	//Use FIFO
	else
	{
		pages[index] = page;
		frames[index] = frame;

		index++;
		index %= 16;
	}
}
