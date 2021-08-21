#include "memory.hpp"

// "injected" by linker
extern uint64_t _HEAP_START_;
extern uint64_t _HEAP_END_;

uint32_t current_offset = 0;

void* operator new(uint64_t count)
{
    auto ret = &_HEAP_START_ + current_offset;
    current_offset += count;
    return static_cast<void*>(ret);
}

void* operator new[](uint64_t count)
{
    auto ret = &_HEAP_START_ + current_offset;
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
