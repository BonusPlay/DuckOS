#pragma once
#include "dstd/type_traits.hpp"

namespace dstd
{

template <class T>
concept Integral = is_integral_v<T>;

}
