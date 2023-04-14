#pragma once
#include "dstd/vector.hpp"
#include "dstd/tuple.hpp"
#include "dstd/expected.hpp"
#include "dstd/ref.hpp"

namespace dstd
{

enum class MapError
{
    KeyNotFound,
};

template<class K, class T>
class Map
{
public:
    //void insert(const K&, const T&);
    void insert(K&&, T&&);

    [[nodiscard]]
    constexpr Expected<Ref<T>, MapError> operator[](K&&);

    [[nodiscard]]
    constexpr Expected<Ref<const T>, MapError> operator[](K&&) const;

    void clear();

private:
    Vector<Tuple<K, T>> storage;
};

//template<class K, class T>
//void Map<K, T>::insert(const K& key, const T& value)
//{
//    //assert(!keys.contains(key), "map already has this key specified");
//    storage.push_back(Tuple<K, T>(forward<K>(key), forward<T>(value)));
//}

template<class K, class T>
void Map<K, T>::insert(K&& key, T&& value)
{
    storage.push_back(Tuple<K, T>(forward<K>(key), forward<T>(value)));
}

template<class K, class T>
constexpr Expected<Ref<T>, MapError> Map<K, T>::operator[](K&& key)
{
    for (auto i = 0; i < storage.size(); ++i)
    {
        if (storage[i].template get<0>() == key)
        {
            return Expected<Ref<T>, MapError>(Ref(storage[i].template get<1>()));
        }
    }

    return Unexpected<Ref<T>, MapError>(MapError::KeyNotFound);
}

template<class K, class T>
constexpr Expected<Ref<const T>, MapError> Map<K, T>::operator[](K&& key) const
{
    for (auto i = 0; i < storage.size(); ++i)
    {
        if (storage[i].template get<0>() == key)
        {
            return Expected<Ref<const T>, MapError>(Ref(storage[i].template get<1>()));
        }
    }
    return Unexpected<Ref<T>, MapError>(MapError::KeyNotFound);
}

template<class K, class T>
void Map<K,T>::clear()
{
    storage.clear();
}

}
