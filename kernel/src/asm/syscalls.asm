[bits 64]
[extern syscall_handler]
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

global _SYSCALL_ENTRY_
_SYSCALL_ENTRY_:
    ; user => kernel
    swapgs
    ; save user stack
    mov gs:[0x8], rsp
    ; HACK: we use same stack for kernel
    mov gs:[0x0], rsp
    ; load kernel stack
    mov rsp, gs:[0x0]
    ; save regs
    ; TODO: we probably don't need to save all regs
    pushaq
    ; handle syscall
    call syscall_handler
    ; restore regs
    popaq
    ; load user stack
    mov rsp, gs:[0x8]
    ; kernel => user
    swapgs
    ; return to user
    ; sysretq
    o64 sysret ; bug in nasm: https://sourceforge.net/p/nasm/bugs/511/
