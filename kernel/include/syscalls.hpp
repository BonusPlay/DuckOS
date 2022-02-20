#pragma once

namespace syscalls
{
    void setup();

    extern "C"
    void syscall_handler();
}
