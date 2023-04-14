#pragma once
#include "dstd/cstdint.hpp"
#include "dstd/type_traits/base.hpp"
#include "dstd/type_traits/references.hpp"
#include "dstd/type_traits/qualifiers.hpp"

namespace dstd
{

namespace impl
{
    template<typename>
    struct is_integral
        : public false_type
    {};

    // WTF why is bool counted as an int
    template<>
    struct is_integral<bool>
        : public true_type
    {};

    template<>
    struct is_integral<int>
        : public true_type
    {};

    template<>
    struct is_integral<unsigned int>
        : public true_type
    {};

    template<>
    struct is_integral<int8_t>
        : public true_type
    {};

    template<>
    struct is_integral<uint8_t>
        : public true_type
    {};

    template<>
    struct is_integral<int16_t>
        : public true_type
    {};

    template<>
    struct is_integral<uint16_t>
        : public true_type
    {};

    template<>
    struct is_integral<int64_t>
        : public true_type
    {};

    template<>
    struct is_integral<uint64_t>
        : public true_type
    {};
}

template<typename _Tp>
struct is_integral
    : public impl::is_integral<typename remove_cv<_Tp>::type>::type
{};

template<class T>
inline constexpr bool is_integral_v = is_integral<T>::value;

}
