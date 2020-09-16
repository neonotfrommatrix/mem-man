#include "BackingStore.hpp"
#include <iostream>

BackingStore::BackingStore(int size)
	: media("BACKING_STORE.bin", std::ios::in | std::ios::out | std::ios::binary), frameSize(size)
{
	
}

void BackingStore::getFrame(char  fullFrame[256], int frame)
{
	int byteToRead = frame * frameSize;
	if (!media.is_open())
	{
		std::cerr << "File BACKING_STORE.bin not found in the local directory!\n";
		exit(1);
	}
	media.seekg(byteToRead);
	media.read(fullFrame, frameSize);
}

BackingStore::~BackingStore()
{
	media.close();
}
