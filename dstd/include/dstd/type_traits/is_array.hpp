#pragma once

namespace dstd
{

template<class T>
struct is_array : false_type {};

template<class T>
struct is_array<T[]> : true_type {};

template<class T, uint64_t N>
struct is_array<T[N]> : true_type {};

template<class T>
inline constexpr bool is_array_v = is_array<T>::value;

}
