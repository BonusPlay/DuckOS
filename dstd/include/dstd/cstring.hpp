#pragma once
#include "dstd/cstdint.hpp"

namespace dstd {

uint32_t strlen(const char* str_);
void strcpy(char* dest_, const char* src_, uint32_t count_);
int32_t strcmp(const char* lhs, const char* rhs);
void* memcpy(void* dest_, const void* src_, uint32_t count_);
void* memset(void* dest_, uint32_t value_, int32_t count_);

}
