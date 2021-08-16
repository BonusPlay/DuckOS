#pragma once
#include "dstd/cstdint.hpp"

namespace dstd {

uint32_t strlen(const char* str_);
void strcpy(char* dest_, const char* src_, uint32_t count_);
void* memcpy(void* dest_, const void* src_, uint32_t count_);

}
