#include "vga.hpp"

volatile uint16_t* framebuf = reinterpret_cast<volatile uint16_t*>(0xB8000);

inline uint8_t make_color(const VgaColor& foreground = VgaColor::WHITE, const VgaColor& background = VgaColor::BLACK)
{
    return static_cast<uint8_t>(background) << 4 | static_cast<uint8_t>(foreground);
}

inline uint16_t entry(const unsigned char data, const uint8_t color = make_color())
{
    return static_cast<uint16_t>(color) << 8 | static_cast<uint16_t>(data);
}

uint8_t x = 0;
uint8_t y = 0;

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
    *(tmp + x + y * 80) = entry(symbol);

    ++x;
}

void vga_print(const dstd::String& str)
{
    for(uint32_t i = 0; i < str.length(); ++i)
    {
        const auto chr = *(str.data() + i);

        // wrap newline
        if (chr == '\n')
        {
            x = 0;
            y += 1;
            continue;
        }
        
        if (chr == '\t')
        {
            for(auto i = 0; i < 4; ++i)
                print_char(' ');
            continue;
        }

        print_char(chr);
    }
}
