// VMManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include "MemoryManagementUnit.hpp"
using namespace std;


#define RAM_FRAME_CAPACITY 128
#define FRAME_SIZE 256
#define FIFO 1
#define LRU 2

int main(int argc, char *argv[])
{
	int replacement = LRU; //Default replacement algorithm
	bool linux = false;
	if (linux)
	{
		if (argc < 2)
		{
			cerr << "Usage: " << argv[0] << "[1 or 2] < [input file name]\nChoose 1 for FIFO or 2 for LRU replacement";
			return 1;
		}
		if (argv[1][0] == '1')
			replacement = FIFO;
	}
	int input;



	MemoryManagementUnit MMU(RAM_FRAME_CAPACITY, FRAME_SIZE, replacement);
	while ((cin >> input))
	{
		AddressTranslator AT(input, RAM_FRAME_CAPACITY);
		Word byte = MMU.read(AT);

		cout << hex << input << " (" << AT.getPhysical() << "): " << static_cast<int>(static_cast<unsigned char>(byte.value)) << " (" << dec  << static_cast<int>(static_cast<signed char>(byte.value)) << ")\n";
	}
	MMU.printMetrics();
	return 0;
}