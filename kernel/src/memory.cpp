#include "memory.hpp"

// "injected" by linker
extern uint8_t* __HEAP_SECTION_START;
extern uint8_t* __HEAP_SECTION_END;

uint32_t current_offset = 0;

void* operator new(uint32_t count)
{
    auto ret = __HEAP_SECTION_START + current_offset;
    current_offset += count;
    return static_cast<void*>(ret);
}

void* operator new[](uint32_t count)
{
    auto ret = __HEAP_SECTION_START + current_offset;
    current_offset += count;
    return static_cast<void*>(ret);
}

void operator delete(void* ptr)
{
    (void)ptr;
    // TODO: implement
}

void operator delete[](void* ptr)
{
    (void)ptr;
    // TODO: implement
}
