#include "log.hpp"
#include <dstd/string.hpp>
#include <dstd/type_traits.hpp>
#include "memory/phys_addr.hpp"
#include "memory/virt_addr.hpp"
#include "serial.hpp"

namespace log
{



void print(auto&& arg)
{
    if constexpr (dstd::is_same_v<decltype(arg), dstd::String>) {
        serial::print(arg);
    } else if constexpr (dstd::is_same_v<decltype(arg), memory::PhysicalAddress>) {
        serial::print(dstd::addr_to_string(arg.addr));
    } else if constexpr (dstd::is_integral_v<decltype(arg)>) {

    }
}

void debug(const auto& args...)
{
    auto debug_impl = [](const auto& self, auto&& elem, auto&&... args)
    {
        if constexpr (sizeof...(args) > 0)
            self(args);
    }

    debug(arg);
    debug(args);
}

}
