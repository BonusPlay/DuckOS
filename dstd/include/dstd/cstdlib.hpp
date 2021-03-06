#pragma once
#include "dstd/concepts.hpp"

namespace dstd
{

template<typename T>
requires integral<T>
constexpr T abs(const T val_)
{
    return val_ > 0
        ? val_
        : -val_;
}

}
