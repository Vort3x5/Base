; asmsyntax=fasm

KERNEL_SIZE equ 18
; Kernel Size In Sectors(512 bytes)

KERNEL_SIZEd equ KERNEL_SIZE * (512 / 4)
; Kernel Size In Double-Words (kernel size in sectors * (bytes per sector / bytes in double-word))
