#pragma once
#include "dstd/cstdint.hpp"

[[nodiscard]]
void* operator new(uint32_t count);

[[nodiscard]]
void* operator new[](uint32_t count);

void operator delete(void* ptr);
void operator delete[](void* ptr);
