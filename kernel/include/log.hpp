#pragma once
#include <dstd/type_traits.hpp>
#include "serial.hpp"
#include "memory/phys_addr.hpp"

namespace log
{

// SFINAE helper
template<typename T>
struct print_helper : dstd::false_type {};

template<typename T_>
void print(T_&& arg)
{
    using T = dstd::remove_cvref_t<T_>;

    if constexpr (dstd::is_same_v<T, dstd::String>) {
        serial::print(arg);
    } else if constexpr (dstd::is_same_v<T, memory::PhysicalAddress>) {
        serial::print(dstd::addr_to_string(arg.addr));
    } else if constexpr (dstd::is_integral_v<T>) {
        serial::print(dstd::to_string(arg, 16));
    } else if constexpr (dstd::is_same_v<dstd::decay_t<T>, char*>) {
        serial::print(arg);
    } else {
        static_assert(print_helper<T>::value, "Unsupported type in print");
    }
}

const auto print_wrap = [](const auto& self, auto&& elem, auto&&... rest)
{
    print(elem);
    serial::print(" ");
    if constexpr (sizeof...(rest) > 0)
        self(self, rest...);
};

// linker breaks if you move this to .cpp
void debug(auto&&... args)
{
    serial::print("[DEBUG] ");
    print_wrap(print_wrap, args...);
}

void info(auto&&... args)
{
    serial::print("[INFO] ");
    print_wrap(print_wrap, args...);
}

void warning(auto&&... args)
{
    serial::print("[INFO] ");
    print_wrap(print_wrap, args...);
}

void error(auto&&... args)
{
    serial::print("[INFO] ");
    print_wrap(print_wrap, args...);
}

}
