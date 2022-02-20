#include "serial.hpp"
#include "io.hpp"

namespace serial
{

bool init(uint16_t port)
{
    io::out(port + 1, 0x00); // Disable all interrupts
    io::out(port + 3, 0x80); // Enable DLAB (set baud rate divisor)
    io::out(port + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    io::out(port + 1, 0x00); //                  (hi byte)
    io::out(port + 3, 0x03); // 8 bits, no parity, one stop bit
    io::out(port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    io::out(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
    io::out(port + 4, 0x1E); // Set in loopback mode, test the serial chip
    io::out(port + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (io::inb(port + 0) != 0xAE) {
        return false;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    io::out(port + 4, 0x0F);
    return true;
}

int is_transmit_empty(uint16_t port = PORT_COM1)
{
    return io::inb(port + 5) & 0x20;
}
 
void write_serial(const char a, uint16_t port = PORT_COM1)
{
    while (is_transmit_empty() == 0);
    io::out(port, a);
}

void print(const dstd::String& str)
{
    for(uint32_t i = 0; i < str.length(); ++i)
        write_serial(str[i]);
}

void println(const dstd::String& str)
{
    print(str);
    write_serial('\n');
}

}
