ENTRY(_start)

MEMORY
{
    /* Targeting Internal SYSRAM */
    SRAM (rwx) : ORIGIN = 0x0E000000, LENGTH = 128K
}

SECTIONS
{
    .text :
    {
        . = ALIGN(8);
        KEEP(*(.text.boot))
        *(.text*)
    } > SRAM

    .rodata :
    {
        . = ALIGN(8);
        *(.rodata*)
    } > SRAM

    .data :
    {
        . = ALIGN(16);
        __data_start = .;
        *(.data*)
        __data_end = .;
    } > SRAM

    .bss :
    {
        . = ALIGN(16);
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    } > SRAM

    /* Stack at the end of the reserved SRAM block */
    .stack (NOLOAD) :
    {
        . = ALIGN(16);
        . = . + 0x2000; /* 8KB Stack */
        __stack_top = .;
    } > SRAM
}
