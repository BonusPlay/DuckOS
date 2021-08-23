#pragma once
#include <dstd/cstdint.hpp>

[[nodiscard]]
void* operator new(uint64_t count);

[[nodiscard]]
void* operator new[](uint64_t count);

void operator delete(void* ptr);
void operator delete[](void* ptr);
