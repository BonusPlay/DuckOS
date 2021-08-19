#pragma once
#include "dstd/type_traits.hpp"

namespace dstd
{

template < class T >
concept integral = is_integral_v<T>;

}
