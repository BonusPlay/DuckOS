#pragma once
#include "dstd/cstdint.hpp"
#include "dstd/string.hpp"

namespace vga
{

enum class Color : uint16_t {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GREY = 7,
    DARK_GREY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15,
};

void test();
void set_pos(uint8_t x, uint8_t y);
void print(const dstd::String&);
void clear(Color bg = Color::BLACK);

}
