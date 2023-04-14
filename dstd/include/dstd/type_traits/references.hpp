#pragma once
#include "dstd/type_traits/base.hpp"

namespace dstd
{

namespace impl {
    template<class T>
    auto add_lvalue_reference(int) -> dstd::type_identity<T&>;

    template<class T>
    auto add_lvalue_reference(...) -> dstd::type_identity<T>;

    template<class T>
    auto add_rvalue_reference(int) -> dstd::type_identity<T&&>;

    template<class T>
    auto add_rvalue_reference(...) -> dstd::type_identity<T>;
}

template<class T>
struct add_lvalue_reference
    : decltype(impl::add_lvalue_reference<T>(0))
{};

template<class T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template<class T>
struct add_rvalue_reference
    : decltype(impl::add_rvalue_reference<T>(0))
{};

template<class T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template<class T> struct is_lvalue_reference      : false_type{};
template<class T> struct is_lvalue_reference<T&>  : true_type {};
template<class T> struct is_rvalue_reference      : false_type{};
template<class T> struct is_rvalue_reference<T&&> : true_type {};

template <class T> struct is_reference      : false_type {};
template <class T> struct is_reference<T&>  : true_type {};
template <class T> struct is_reference<T&&> : true_type {};

template< class T >
inline constexpr bool is_reference_v = is_reference<T>::value;

}
