ENTRY(_start)
 
SECTIONS
{
    . = 1M;

    .multiboot : ALIGN(4K)
    {
        *(.multiboot)
        *(.multiboot.*)
    }

    .pmlt : ALIGN(4K)
    {
        _PML4T_TABLE_ = .;
        _PML3T_TABLE_ = . + 0x1000;
        _PML2T_TABLE_ = . + 0x2000;
        *(.pmlt)
        *(.pmlt.*)
    }

    .idt : ALIGN(4K)
    {
        _IDT_TABLE_ = .;
        . += (0x10 * 8 * 0x100);
    }

    .text : ALIGN(4K)
    {
        *(.text)
        *(.text.*)
    }
 
    .rodata : ALIGN(4K)
    {
        *(.rodata)
        *(.rodata.*)
    }
 
    .data : ALIGN(4K)
    {
        *(.data)
        *(.data.*)
    }
 
    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
        *(.bss.*)
    }

    .heap : ALIGN(4K)
    {
        _HEAP_START_ = .;
        . += 0x1000;
        _HEAP_END_ = .;
    }
}
