#pragma once
#include "dstd/assert.hpp"
#include "dstd/cstdint.hpp"

namespace dstd
{

template<class T, T v>
struct integral_constant
{
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const { return value; }
    constexpr value_type operator()() const { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

// cursed. https://en.cppreference.com/w/cpp/language/template_argument_deduction#Non-deduced_contexts
template<class T>
struct type_identity
{
    using type = T;
};

template<class T>
using type_identity_t = typename type_identity<T>::type;

}
