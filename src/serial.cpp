#include "serial.hpp"
#include "dstd/cstdint.hpp"
#include "io.hpp"

namespace serial
{

bool init(uint16_t port)
{
    out(port + 1, 0x00); // Disable all interrupts
    out(port + 3, 0x80); // Enable DLAB (set baud rate divisor)
    out(port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    out(port + 1, 0x00); //                  (hi byte)
    out(port + 3, 0x03); // 8 bits, no parity, one stop bit
    out(port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    out(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
    out(port + 4, 0x1E); // Set in loopback mode, test the serial chip
    out(port + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (inb(port + 0) != 0xAE) {
        return false;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    out(port + 4, 0x0F);
    return true;
}

int is_transmit_empty(uint16_t port = PORT_COM1)
{
    return inb(port + 5) & 0x20;
}
 
void write_serial(const char a, uint16_t port = PORT_COM1)
{
    while (is_transmit_empty() == 0);
    out(port, a);
}

void test()
{
    write_serial('a');
}

void xdd(uint32_t value_)
{
    for(uint32_t i = 0; i < sizeof(value_); i++)
        write_serial(static_cast<uint8_t>(value_ >> i) + 48);
}

void print(const dstd::String& str)
{
    for(uint32_t i = 0; i < str.length(); ++i)
        write_serial(str[i]);
}

}
