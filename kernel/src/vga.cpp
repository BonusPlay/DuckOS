#include "vga.hpp"
#include "dstd/cstring.hpp"

namespace vga
{

constexpr const auto MAX_WIDTH = 80;
constexpr const auto MAX_HEIGHT = 25;
uint16_t* framebuf = reinterpret_cast<uint16_t*>(0xB8000);

inline uint8_t make_color(const Color& foreground = Color::WHITE, const Color& background = Color::BLACK)
{
    return static_cast<uint8_t>(background) << 4 | static_cast<uint8_t>(foreground);
}

inline uint16_t make_cell(const unsigned char data, const uint8_t color = make_color())
{
    return static_cast<uint16_t>(color) << 8 | static_cast<uint16_t>(data);
}

uint8_t x = 0;
uint8_t y = 0;
uint8_t color = make_color();

void print_char(const char symbol)
{
    auto* tmp = framebuf;

    if (x == 80)
    {
        x = 0;
        y += 1;
    }

    if (y == 25)
    {
        y = 0;
        x = 0;
    }

    // write actual character
    *(tmp + x + y * 80) = make_cell(symbol, color);

    ++x;
}

void set_pos(uint8_t x_, uint8_t y_)
{
    x = x_;
    y = y_;
}

void set_color(Color fg_, Color bg_)
{
    color = make_color(fg_, bg_);
}

void print(const dstd::String& str)
{
    for(uint32_t i = 0; i < str.length(); ++i)
    {
        const auto chr = *(str.data() + i);
        print(chr);
    }
}

void print(const char& chr)
{
    // wrap newline
    if (chr == '\n')
    {
        x = 0;
        y += 1;
        return;
    }

    // tab as 4 spaces
    if (chr == '\t')
    {
        for(auto j = 0; j < 4; ++j)
            print_char(' ');
        return;
    }

    print_char(chr);
}

void clear(Color bg_)
{
    const auto tmp = make_cell(' ', make_color(Color::WHITE, bg_)) << 16;
    const auto value = static_cast<uint32_t>(tmp << 16 & tmp);
    //dstd::memset(static_cast<void*>(framebuf), value, 80 * 24);
    for(auto i = 0; i < MAX_HEIGHT; ++i)
        for(auto j = 0; j < MAX_WIDTH; ++j)
            *(framebuf + j + i * 80) = value;
}

}
