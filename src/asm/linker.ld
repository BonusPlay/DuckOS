ENTRY(_start)
 
SECTIONS
{
	. = 1M;
 
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
 
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
 
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
 
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

    .heap BLOCK(4K) : ALIGN(4K)
    {
        __HEAP_SECTION_START = .;
        . += 0x1000;
        __HEAP_SECTION_END = .;
    }
}
