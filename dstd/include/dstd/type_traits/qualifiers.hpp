#pragma once
#include "dstd/type_traits/base.hpp"

namespace dstd
{

template< class T > struct remove_reference      { typedef T type; };
template< class T > struct remove_reference<T&>  { typedef T type; };
template< class T > struct remove_reference<T&&> { typedef T type; };

template< class T >
using remove_reference_t = typename remove_reference<T>::type;

template< class T > struct remove_cv                   { typedef T type; };
template< class T > struct remove_cv<const T>          { typedef T type; };
template< class T > struct remove_cv<volatile T>       { typedef T type; };
template< class T > struct remove_cv<const volatile T> { typedef T type; };

template< class T >
using remove_cv_t = typename remove_cv<T>::type;

template< class T > struct remove_const                { typedef T type; };
template< class T > struct remove_const<const T>       { typedef T type; };

template< class T >
using remove_const_t = typename remove_const<T>::type;

template< class T > struct remove_volatile             { typedef T type; };
template< class T > struct remove_volatile<volatile T> { typedef T type; };

template< class T >
using remove_volatile_t = typename remove_volatile<T>::type;

template< class T >
struct remove_cvref {
    typedef remove_cv_t<remove_reference_t<T>> type;
};

template< class T >
using remove_cvref_t = typename remove_cvref<T>::type;

}
