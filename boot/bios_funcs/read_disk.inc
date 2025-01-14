; asmsyntax=fasm

macro LBAtoCHS
{
	xor bx, bx
	xor cx, cx
	xor dx, dx

	mov bx, bpbSectorsPerTrack
	div bx

	inc dx
	mov cl, dl

	mov bx, bpbHeadsPerCylinder
	xor dx, dx
	div bx

	mov ch, al
	xchg dl, dh
	
	mov dl, [bsDriveNumber]
}

macro LoadSectors size, start_lba
{
	mov ax, start_lba

	.read:
		push ax
		push bx
		LBAtoCHS

		mov al, 01h
		mov ah, 02h
		inc cl
		pop bx
		int 13h
		jc .error

		add bx, 200h
		pop ax
		inc ax
		cmp ax, start_lba + size
		jl .read

	.error:
		hlt
}

macro GetParamsCall drive_index
{
	xor ax, ax
	mov ah, 08h
	mov es, ax
	mov di, ax

	mov dl, drive_index
	int 13h
}

macro DriveParamsTODO
{
GetDriveParams:
	; first check if BIOS emulates usb as a hard drive
	GetParamsCall 80h
	cmp ax, 0
	je SetDriveParams

	GetParamsCall 81h
	cmp ax, 0
	je SetDriveParams

	; if not, check if as a floppy drive
	GetParamsCall 0h
	cmp ax, 0
	je SetDriveParams

	GetParamsCall 01h
	cmp ax, 0
	je SetDriveParams

	.failed:
		hlt

SetDriveParams:
	; dl stores Number Of Heads - 1
	mov byte [bpbHeadsPerCylinder], dh
	inc [bpbHeadsPerCylinder]

	and cl, 0x3f
	mov byte [bpbSectorsPerTrack], cl
}
