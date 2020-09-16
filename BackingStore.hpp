#include <fstream>
#ifndef BACKING_STORE_H
#define BACKING_STORE_H

class BackingStore
{
public:
	BackingStore(int size);
	void getFrame(char fullFrame[256], int frame);
	~BackingStore();
private:
	std::ifstream media;
	int frameSize;
};
#endif // !BACKING_STORE_H