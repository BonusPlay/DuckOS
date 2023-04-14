#pragma once
#include "dstd/type_traits/is_same.hpp"
#include "dstd/type_traits/qualifiers.hpp"

namespace dstd
{

template< class T >
struct is_void : is_same<void, typename remove_cv<T>::type>
{};

template< class T >
inline constexpr bool is_void_v = is_void<T>::value;

}
