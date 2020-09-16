#include "AddressTranslator.hpp"

AddressTranslator::AddressTranslator(int logicalAddress, int RAMSize)
{
	offset = logicalAddress & 0xFF;
	page = (logicalAddress >> 8) & 0xFF;
	physicalAddress = page * RAMSize + offset;
}

int AddressTranslator::getPage()
{
	return page;
}

int AddressTranslator::getOffset()
{
	return offset;
}

int AddressTranslator::getPhysical()
{
	return physicalAddress;
}
