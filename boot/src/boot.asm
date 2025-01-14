; asmsyntax=fasm

use16
org 7c00h

jmp Start

include '../sys_init/OEMpb.inc'
F12OEM

SND_SIZE equ 2
include '../sys_init/kernel_size.inc'

include '../bios_funcs/print.inc'

Start:
	xor ax, ax

	mov ds, ax
	mov fs, ax
	mov gs, ax
	mov es, ax

	mov sp, 7c00h
	cld

	Print start_msg

	; jmp GetDriveParams
	jmp LoadSND

include '../bios_funcs/read_disk.inc'

LoadSND:
	xor ax, ax
	mov es, ax
	mov bx, 1000h

	LoadSectors SND_SIZE, 0
	Print snd_read_msg

LoadKernel:
	xor ax, ax
	mov es, ax
	mov bx, 7e00h

	LoadSectors KERNEL_SIZE, SND_SIZE
	Print kernel_read_msg

JumpSND:
	xor ax, ax

	mov ds, ax
	mov fs, ax
	mov gs, ax
	mov es, ax
	mov ss, ax

	jmp 0h:1000h

start_msg db 'Initializing!', 0
snd_read_msg db 'Second Stage Read!', 0
kernel_read_msg db 'Kernel Read!', 0

times 510 - ($ - $$) db 0
dw 0xaa55
