#include "interrupts.hpp"

namespace interrupts
{

PageFaultError from_error_code(uint32_t val)
{
    auto err = PageFaultError{};
    err.protection        = val & 0b00001;
    err.write             = val & 0b00010;
    err.user              = val & 0b00100;
    err.reserved_write    = val & 0b01000;
    err.instruction_fetch = val & 0b10000;
    return err;
}

}
