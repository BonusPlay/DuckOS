[bits 64]
[extern interrupt_handler]
section .text

%macro pushaq 0
   push rax
   push rbx
   push rcx
   push rdx
   push rbp
   push rdi
   push rsi
   push r8
   push r9
   push r10
   push r11
   push r12
   push r13
   push r14
   push r15
%endmacro

%macro popaq 0
   pop r15
   pop r14
   pop r13
   pop r12
   pop r11
   pop r10
   pop r9
   pop r8
   pop rsi
   pop rdi
   pop rbp
   pop rdx
   pop rcx
   pop rbx
   pop rax
%endmacro

%macro isr_stub 1
isr_stub_%+%1:
    ; push fake exception code onto stack
    ; credits to @chivay for this idea
    push 0
    ; push interrupt code
    push %1
    call isr_stub_common
    ; cleanup stack
    add rsp, 0x10
    iretq
%endmacro

%macro isr_err_stub 1
isr_stub_%+%1:
    ; no need to push fake exception
    ; push interrupt code
    push %1
    call isr_stub_common
    ; cleanup stack
    add rsp, 0x10
    iretq
%endmacro

isr_stub_common:
    pushaq
    ; 0x90 interrupt frame
    ; 0x88 (fake) error code
    ; 0x80 interrupt number
    ; 0x78 ret addr to stub
    ; 0x70 rax
    ; 0x68 rbx
    ; 0x60 rcx
    ; 0x58 rdx
    ; 0x50 rbp
    ; 0x48 rdi
    ; 0x40 rsi
    ; 0x38 r8
    ; 0x30 r9
    ; 0x28 r10
    ; 0x20 r11
    ; 0x18 r12
    ; 0x10 r13
    ; 0x08 r14
    ; 0x00 r15 <- rsp
    mov rdi, [rsp + 0x80]
    mov rsi, [rsp + 0x88]
    lea rdx, [rsp + 0x90]
    call interrupt_handler
    popaq
    ret

; generate stubs
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
