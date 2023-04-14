#pragma once
#include "dstd/utility.hpp"

namespace dstd
{

template<typename T>
class Ref
{
public:
    explicit Ref(T& t);
    Ref(const Ref& other);
    Ref& operator=(const Ref& other);

    operator T&() const
    {
        return *ptr;
    }

    T& get() const;

private:
    T* ptr;
};

// type deduction
template<typename T>
Ref(T&) -> Ref<T>;

template<typename T>
Ref<T>::Ref(T& t)
    : ptr(dstd::addressof(t))
{};

template<typename T>
Ref<T>::Ref(const Ref& other)
    : ptr(other.ptr)
{};

template<typename T>
Ref<T>& Ref<T>::operator=(const Ref& other)
{
    ptr = other.ptr;
    return *this;
}

template<typename T>
T& Ref<T>::get() const
{
    return *ptr;
}


}
