#include "Word.hpp"
#ifndef ADDRESS_H
#define ADDRESS_H


class AddressTranslator
{
public:
	AddressTranslator(int logicalAddress, int RAMSize);
	int getPage();
	int getOffset();
	int getPhysical();
private:
	int page;
	int offset;
	int physicalAddress;
};
#endif // !ADDRESS_H