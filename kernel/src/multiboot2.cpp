#include "multiboot2.hpp"

namespace multiboot2
{

void* mb2_struct_ptr;

void init(void* mb2_struct_ptr_)
{
    mb2_struct_ptr = mb2_struct_ptr_;

    for(auto* tag = reinterpret_cast<Tag*>(reinterpret_cast<uint64_t>(mb2_struct_ptr) + 8);
        tag->type != TagType::END;
        tag = reinterpret_cast<Tag*>((reinterpret_cast<uint8_t*>(tag) + ((tag->size + 7) & ~7))))
    {
        serial::print("MB2 tag: ");
        serial::println(dstd::to_string(static_cast<uint32_t>(tag->type)));
    }
}

}
