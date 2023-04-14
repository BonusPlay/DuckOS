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
    String(const char*, uint32_t len);

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
requires Integral<T>
String to_string(const T val_, const uint8_t base = 10)
{
    char buf[30];
    auto num = abs(val_);

    if (val_ == 0)
    {
        if (base == 16)
            return String("0x0");
        return String("0");
    }

    auto i = 0;

    while (num != 0)
    {
        const auto remainder = num % base;
        buf[i++] = remainder > 9
            ? remainder + 'A' - 10
            : remainder + '0';
        num = num / base;
    }

    if (base == 16)
    {
        buf[i++] = 'x';
        buf[i++] = '0';
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
        swap(*(buf + start), *(buf + i));
        start++;
        i--;
    }

    return String(buf);
}

String addr_to_string(const auto* val_)
{
    return to_string(reinterpret_cast<uint64_t>(val_), 16);
}

bool operator==(const String&, const String&);

}

#ifdef DSTD_GLOBAL_INTS
dstd::String operator "" _s(const char*, uint64_t);
#else
dstd::String operator "" _s(const char*, dstd::uint64_t);
#endif
