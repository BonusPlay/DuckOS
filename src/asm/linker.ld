ENTRY(_start)
 
SECTIONS
{
    . = 1M;

    .multiboot : ALIGN(4K)
    {
        *(.multiboot)
    }

    .text : ALIGN(4K)
    {
        *(.text)
    }
 
    .rodata : ALIGN(4K)
    {
        *(.rodata)
    }
 
    .data : ALIGN(4K)
    {
        *(.data)
    }
 
    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    .heap : ALIGN(4K)
    {
        __HEAP_SECTION_START = .;
        . += 0x1000;
        __HEAP_SECTION_END = .;
    }
}
