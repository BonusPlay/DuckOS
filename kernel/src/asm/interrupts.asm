[bits 64]
[extern interrupt_handler]
section .text

%macro isr_stub 1
isr_stub_%+%1:
    call interrupt_handler
    iretq
%endmacro

%macro isr_err_stub 1
isr_stub_%+%1:
    call interrupt_handler
    iretq
%endmacro

isr_stub     0
isr_stub     1
isr_stub     2
isr_stub     3
isr_stub     4
isr_stub     5
isr_stub     6
isr_stub     7
isr_err_stub 8
isr_stub     9
isr_err_stub 10
isr_err_stub 11
isr_err_stub 12
isr_err_stub 13
isr_err_stub 14
isr_stub     15
isr_stub     16
isr_err_stub 17
isr_stub     18
isr_stub     19
isr_stub     20
isr_stub     21
isr_stub     22
isr_stub     23
isr_stub     24
isr_stub     25
isr_stub     26
isr_stub     27
isr_stub     28
isr_stub     29
isr_err_stub 30
isr_stub     31

global _ISR_STUB_TABLE_
_ISR_STUB_TABLE_:
%assign i 0 
%rep    32 
    dq isr_stub_%+i
%assign i i+1 
%endrep
