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
        *(.pmlt)
        *(.pmlt.*)
    }

    .idt : ALIGN(4K)
    {
        __IDT_SECTION_START = .;
        . += 0x100;
        __IDT_SECTION_END = .;
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
        __HEAP_SECTION_START = .;
        . += 0x1000;
        __HEAP_SECTION_END = .;
    }
}
