#pragma once
#include <dstd/cstdint.hpp>

void dump_memory(uintptr_t& addr_from, uintptr_t& addr_to);
void dump_memory(uint8_t* addr_from, uint8_t* addr_to);
