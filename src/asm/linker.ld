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
        __DATA_SECTION_START = .;
		*(.data)
        __DATA_SECTION_END = .;
	}
 
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
