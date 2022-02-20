[bits 32]

GDT64:                           ; Global Descriptor Table (64-bit).
    .Kernel_Null: equ $ - GDT64  ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    .Kernel_Code: equ $ - GDT64  ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .Kernel_Data: equ $ - GDT64  ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).

    ; TODO: for now user and kernel descriptors are the same
    .User_Null: equ $ - GDT64    ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    .User_Code: equ $ - GDT64    ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .User_Data: equ $ - GDT64    ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).

    .Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.

section .text
global _setup_gdt:function (_setup_gdt.end - _setup_gdt)
_setup_gdt:
    lgdt [GDT64.Pointer]              ; Load the 64-bit global descriptor table.
    jmp GDT64.Kernel_Code:_start64bit_wrap   ; Set the code segment and enter 64-bit long mode.
.end

_start64bit_wrap:
    mov ax, GDT64.Kernel_Data            ; Set the A-register to the data descriptor.
    [extern _start64bit]
    jmp _start64bit
