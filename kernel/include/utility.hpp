#pragma once
#include <dstd/cstdint.hpp>

void dump_memory(uint64_t addr_from, uint64_t addr_to);
void dump_memory(uint8_t* addr_from, uint8_t* addr_to);
