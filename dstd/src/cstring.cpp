#include "dstd/cstring.hpp"

namespace dstd
{

uint32_t strlen(const char* str)
{
    const char* it = str;
    while(*it != '\0')
        ++it;

    return it - str;
}

// TODO: check if strlen + memcpy won't be faster
void strcpy(char* dest_, const char* src_, const uint32_t count_)
{
    for(uint32_t i = 0; i < count_; ++i)
    {
        *(dest_ + i) = *(src_ + i);
        if (*(dest_ + i) == '\0')
            break;
    }
}

void* memcpy(void* dest_, const void* src_, uint32_t count_)
{
    void* original_dest = dest_;
    __asm__(".intel_syntax;"
        "rep movsb;"
        : "+D"(dest_), "+S"(src_), "+c"(count_)
        :
        : "memory");
    return original_dest;
}

void* memset(void* dest_, uint32_t value_, int32_t count_)
{
    void* original_dest = dest_;
	__asm__(
        ".intel_syntax;"
        "rep stosb;"
        : "=D" (dest_), "=c" (value_)
        : "0" (dest_), "1" (value_), "a" (count_)
        : "memory");
	return original_dest;
}

}
