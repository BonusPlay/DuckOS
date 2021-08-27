[bits 32]

MAGIC    equ 0xE85250D6
ARCH     equ 0x0 ; 32b protected mode i386
MBLEN    equ multiboot_header_end - multiboot_header_end
CHECKSUM equ -(MAGIC + ARCH + MBLEN)

FLAGS_NONE equ 0x0

section .multiboot
align 8
multiboot_header_start:
    dd MAGIC
    dd ARCH
    dd MBLEN
    dd CHECKSUM
multiboot_header_end:
    ; 3.1.11 Module alignment tag
    ;     +-------------------+
    ; u16 | type = 6          |
    ; u16 | flags             |
    ; u32 | size = 8          |
    ;     +-------------------+
    align 8
    dw 6
    dw FLAGS_NONE
    dd 8
    ;     +-------------------+
    ; u32 | type = 15         |
    ; u32 | size              |
    ;     | copy of RSDPv2    |
    ;     +-------------------+
    ; align 8
    ; dw 14
    ; dd 8
    ; NOTE: I grub2 fails to boot with "unsupported tag" message
    ; if this tag is defined, but still provides it on boot, so welp
    ; end tag
    align 8
    dw 0
    dw 8

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top

    ; reset flags
    push 0
    popf

    ; push pointer to multiboot2 information structure
    push ebx

    [extern _setup_paging]
    call _setup_paging

    ; _setup_gdt jumps to _start64bit
    [extern _setup_gdt]
    jmp _setup_gdt
.end

[bits 64]
section .text
global _start64bit:function (_start64bit.end - _start64bit):
_start64bit:
    mov ds, ax                    ; Set the data segment to the A-register.
    mov es, ax                    ; Set the extra segment to the A-register.
    mov fs, ax                    ; Set the F-segment to the A-register.
    mov gs, ax                    ; Set the G-segment to the A-register.
    mov ss, ax                    ; Set the stack segment to the A-register.
    ; move multiboot2 info structure to first param
    pop rdi
    [extern kmain]
    call kmain
    hlt
.end
