#pragma once
#include "interrupts.hpp"

namespace keyboard
{

void handle_interrupt(interrupts::Frame* interrupt_frame);

}
