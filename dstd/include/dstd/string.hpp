#pragma once
#include "dstd/cstdint.hpp"
#include "dstd/cstdlib.hpp"
#include "dstd/concepts.hpp"
#include "dstd/utility.hpp"

namespace dstd {

class String
{
public:
    // cppcheck-suppress noExplicitConstructor
    String(const char*);
    String(const String&);
    String(String&&);
    String& operator=(const String&);
    String& operator=(String&&);
    ~String();

    char& operator[](uint32_t index);
    const char& operator[](uint32_t index) const;
    const char* data() const;
    bool empty() const;
    uint32_t length() const;

private:
    uint32_t length_;
    char* raw_str_;
};

template<typename T>
requires dstd::integral<T>
String to_string(const T val_)
{
    char buf[30];
    const auto base = 10;
    auto num = dstd::abs(val_);

    if (val_ == 0)
        return String("0");

    auto i = 0;
    while (num != 0)
    {
        const auto remainder = num % base;
        buf[i++] = remainder + '0';
        num = num / 10;
    }

    if (val_ < 0)
        buf[i++] = '-';

    buf[i] = '\0';

    // decrement size, as we will reverse the string
    // but we can keep the '\0' in same place
    --i;
    int start = 0;
    while (start < i)
    {
        dstd::swap(*(buf + start), *(buf + i));
        start++;
        i--;
    }

    return String(buf);
}

bool operator==(const String&, const String&);

}

#ifdef DSTD_GLOBAL_INTS
dstd::String operator "" _s(const char*, uint32_t);
#else
dstd::String operator "" _s(const char*, dstd::uint32_t);
#endif
