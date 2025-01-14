; asmsyntax=fasm

macro Print msg
{
	xor ax, ax
	mov si, ax
	mov si, msg
	mov ah, 0eh
	call PrintLine
}

PrintLine:
	lodsb
	int 10h
	cmp al, 0
	jne PrintLine
	; print new line
	mov al, 13
	int 10h
	mov al, 10
	int 10h
	ret
