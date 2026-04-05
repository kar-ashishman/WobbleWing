/* Entry point for Debugger */
ENTRY(reset_hdlr)

/* name(attr) : ORIGIN/org = 0x... , LENGTH/len = 0x....; */
/* attributes are R readonly, W readwrite, X executable, A allocated */

MEMORY
{
  SRAM    (xrw)    : ORIGIN = 0x20000000,   LENGTH = 128K
  FLASH    (rx)    : ORIGIN = 0x8000000,   LENGTH = 512K
}

/* >(VMA) AT>(LMA) - VMA where loader loads data to execute */
/* location counter . always tracks VMA not LMA */
/* ALIGN aligns address to boundary */

SECTIONS {
    .text : {
        *(.vector_table)
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    }>FLASH

    .data : {
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    }>SRAM AT>FLASH

    .bss : {
        _sbss = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM
}