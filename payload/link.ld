OUTPUT_ARCH( "riscv" )
ENTRY( _entry )

MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 64M
}

PHDRS
{
  text PT_LOAD;
  rodata PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS
{
  . = ORIGIN(RAM);
  _entry = .;

  .text : {
    *(.text .text.*)
    PROVIDE(etext = .);
  } >RAM AT>RAM :text

  .rodata : {
    . = ALIGN(16);
    *(.srodata .srodata.*)
    . = ALIGN(16);
    *(.rodata .rodata.*)
  } >RAM AT>RAM :rodata
  
  .data : {
    . = ALIGN(16);
    *(.sdata .sdata.*)
    . = ALIGN(16);
    *(.data .data.*)
    PROVIDE(edata = .);
  } >RAM AT>RAM :data

  .bss : {
    . = ALIGN(16);
    *(.sbss .sbss.*)
    . = ALIGN(16);
    *(.bss .bss.*)
    PROVIDE(end = .);
  } >RAM AT>RAM :bss
}
