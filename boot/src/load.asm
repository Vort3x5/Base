; asmsyntax=fasm

use16
org 1000h

mov sp, 7c00h
cld

jmp Next

include '../bios_funcs/print.inc'

Next:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	Print snd_loaded_msg 

	jmp MemMapE820

mmap_addr equ 2000h
MemMapE820:
	mov di, 2004h
	xor ebx, ebx
	xor bp, bp
	mov edx, 0534d4150h
	mov eax, 0e820h
	mov [es:di + 20], dword 1
	mov ecx, 24
	int 15h
	jc .failed
	mov edx, 0534d4150h
	cmp eax, edx
	jne short .failed
	test ebx, ebx
	je short .failed
	jmp short .jmpin

	.E8201p:
		mov eax, 0e820h
		mov [es:di + 20], dword 1
		mov ecx, 24
		int 15h
		jc short .E820f
		mov edx, 0534d4150h

	.jmpin:
		jcxz .skipent	; skip 0 len entries
		cmp cl, 20		; check how many bytes is one entry
		jbe short .notext
		test byte [es:di + 20], 1
		je short .skipent

	.notext:
		mov ecx, [es:di + 8]
		or ecx, [es:di + 12]
		jz .skipent
		inc bp
		add di, 24

	.skipent:
		test ebx, ebx
		jne short .E8201p 
		
	.E820f:
		mov [mmap_addr], bp
		clc
		Print mem_map_done_msg
		jmp A20Enable

	.failed:
		Print mem_map_failed_msg
		stc
		hlt

include '../sys_init/a20.inc'
A20Enable:
	call CheckA20
	cmp ax, 1
	je A20Done

	call BIOS_A20
	call CheckA20
	cmp ax, 1
	je A20Done
	Print a20_bios_failed_msg

	call KbA20
	call CheckA20
	cmp ax, 1
	je A20Done
	Print a20_keyboard_failed_msg

	call FastA20
	call CheckA20
	cmp ax, 1
	je A20Done
	Print a20_fast_failed_msg

	Print a20_failed_to_enable_msg

A20Done:
	Print a20_enabled_msg

SetVideoMode:
	; jmp $
	xor ax, ax
	mov al, 03h
	int 10h
	Print vga_mode_enabled_msg

GDT:
	dw (GDT_End - GDT_Start - 1)
	dd GDT_Start
 
ProtectedMode:
	cli
	lgdt [GDT]
	Print gdt_loaded_msg
	
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp 08h:JumpKernel

include '../sys_init/kernel_size.inc'
use32
include '../sys_init/memcpy.inc'
JumpKernel:
	mov ax, 10h
	mov ds, ax
	mov fs, ax
	mov gs, ax
	mov es, ax
	mov ss, ax

	; Move Kernel To 1MB Addr
	Memcpyd 7e00h, 100000h, KERNEL_SIZEd

	jmp 100000h

include '../sys_init/gdt.inc'

snd_loaded_msg db 'Second Stage Loaded!', 0

mem_map_done_msg db 'Mem Map Done!', 0
mem_map_failed_msg db 'Mem Map Failed!', 0

a20_bios_failed_msg db 'BIOS Method Failed To Enable A20!', 0
a20_keyboard_failed_msg db 'Keyboard Controller Method Failed to Enable A20!', 0
a20_fast_failed_msg db 'Fast Method Failed To Enable A20!', 0
a20_failed_to_enable_msg db 'Failed To Enable A20!', 0

a20_enabled_msg db 'A20 Enabled!', 0

vga_mode_enabled_msg db 'VGA 80x25 Mode Enabled!', 0
kernel_moved_msg db 'Kernel Moved To 1M!', 0
gdt_loaded_msg db 'GDT Loaded!', 0

times 1024 - ($ - $$) db 0
