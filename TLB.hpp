#ifndef TLB_H
#define TLB_H

class TLB
{
public:
	TLB(int algorithm);
	//returns the mapping to the RAM's first argument
	int getFrame(int);
	void clear();
	void insert(int page, int frame);
private:
	//Number from 0-255 representing the page to read
	int pages[16];
	//Mapping to the RAM where the page is located, from 0 to sizeof(RAM)
	int frames[16];
	int accesses;
	int faults;
	int algorithm;
	int index;
};
#endif // !TLB_H