#pragma once
#include "dstd/cstdint.hpp"

[[nodiscard]]
void* operator new(uint32_t count);

[[nodiscard]]
void* operator new[](uint32_t count);
