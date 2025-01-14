; asmsyntax=fasm

CheckA20: ; returns 0 if a20 is disabled and 1 if enabled
	pushf
	push ds
	push es
	push di
	push si

	cli
	xor ax, ax
	mov es, ax
	mov di, 0500h
	mov ax, 0ffffh
	mov ds, ax
	mov si, 0510h
	mov al, byte [es:di]
	push ax
	mov al, byte [ds:si]
	push ax
	mov byte [es:di], 00h
	mov byte [ds:si], 0ffh
	cmp byte [es:di], 0ffh
	pop ax
	mov byte [ds:si], al
	pop ax
	mov byte [es:di], al
	
	mov ax, 0
	je EndCheck
	mov ax, 1

EndCheck:
	pop si
	pop di
	pop es
	pop ds
	popf
	ret

BIOS_A20:
	mov ax, 2401h
	int 15h
	ret

KbA20:
	cli

	call A20WaitCommand
	mov al, 0adh
	out 64h, al

	call A20WaitCommand
	mov al, 0d0h
	out 64h, al

	call A20WaitData
	in al, 60h
	push eax

	call A20WaitCommand
	mov al, 0d1h
	out 64h, al

	call A20WaitCommand
	pop eax
	or al, 2
	out 60h, al

	call A20WaitCommand
	mov al, 0aeh
	out 64h, al

	call A20WaitCommand

	sti
	ret

A20WaitCommand:
	in al, 64h
	test al, 2
	jnz A20WaitCommand
	ret

A20WaitData:
	in al, 64h
	test al, 1
	jz A20WaitData
	ret

FastA20:
	in al, 92h
	or al, 2
	out 92h, al
	ret
