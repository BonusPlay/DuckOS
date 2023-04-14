#pragma once
#include "dstd/assert.hpp"
#include "dstd/utility.hpp"
#include "dstd/impl/storage.hpp"

namespace dstd
{

template<class T>
class Optional
{
public:
    [[nodiscard]]
    constexpr explicit Optional();
    [[nodiscard]]
    constexpr explicit Optional(T value_);

    constexpr const T* operator->() const;
    constexpr T* operator->();
    constexpr const T& operator*() const&;
    constexpr T& operator*() &;
    constexpr const T&& operator*() const&&;
    constexpr T&& operator*() &&;

    constexpr explicit operator bool() const;
    constexpr bool has_value() const;

    // TODO: T must meet the requirements of CopyConstructible in order to use overload (1).
    // TODO: T must meet the requirements of MoveConstructible in order to use overload (2).
    // TODO: U&& must be convertible to T
    /* template<class U> */
    /* constexpr T value_or(U&& default_value) const&; */

    /* template<class U> */
    /* constexpr T value_or(U&& default_value) &&; */


private:
    bool empty;
    impl::storage_t<T> storage;
};

template<class T>
constexpr Optional<T>::Optional()
    : empty(true),
      storage(impl::dummy_init)
{}

template<class T>
constexpr Optional<T>::Optional(T value_)
    : empty(false),
      storage(dstd::forward<T>(value_))
{}

template<class T>
constexpr Optional<T>::operator bool() const
{
    return !empty;
}

template<class T>
constexpr bool Optional<T>::has_value() const
{
    return !empty;
}

template<class T>
constexpr const T* Optional<T>::operator->() const
{
    assert(!this->empty, "dereferenced empty Optional");
    return &this->storage.value;
}

template<class T>
constexpr T* Optional<T>::operator->()
{
    assert(!this->empty, "dereferenced empty Optional");
    return &this->storage.value;
}

template<class T>
constexpr const T& Optional<T>::operator*() const&
{
    assert(!this->empty, "dereferenced empty Optional");
    return this->storage.value;
}

template<class T>
constexpr T& Optional<T>::operator*() &
{
    assert(!this->empty, "dereferenced empty Optional");
    return this->storage.value;
}

template<class T>
constexpr const T&& Optional<T>::operator*() const&&
{
    assert(!this->empty, "dereferenced empty Optional");
    return &this->storage.value;
}

template<class T>
constexpr T&& Optional<T>::operator*() &&
{
    assert(!this->empty, "dereferenced empty Optional");
    return &this->storage.value;
}

}
