SECTIONS {
  .text 0x80008000 : { *(.text) }
  "text" = ADDR( .text );
  "etext" = . ;
  "textEnd" = . ;
  .rodata : { *(.rodata) }
   . = ALIGN(4);
   .zPic : {
      LONG(SIZEOF(.zPic)-4);
      zPicStart = .;
      *(.zPic)
   }
  . = ALIGN(0x20);
  .data : { *(.data) *(.rodata ) }
  "data" = ADDR( .data );
  "dataEnd" = . ;
  "edata" = . ;
  .bss : { *(.bss) }
  "bstart" = ADDR( .bss );
  "bssEnd" = . ;
  "bend" = . ;
  "end" = . ;
   . = ALIGN(0x20);
  "malloc_start" = .;
}
