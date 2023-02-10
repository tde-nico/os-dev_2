#pragma once
#include "typedefs.cpp"

struct MemoryMapEntry
{
	uint_64	base_addr;
	uint_64	region_len;
	uint_32	region_type;
	uint_32	extended_attributes;
};

extern uint_8 MemoryRegionCount;
