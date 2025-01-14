; asmsyntax=fasm

macro Memcpy src, dest, size
{
	; Src Buffer
	mov eax, src
	mov esi, eax

	; Dest Buffer
	xor eax, eax
	mov eax, dest
	mov edi, eax

	; Size In Bytes
	xor ecx, ecx
	mov ecx, size
}

macro Memcpyb src, dest, size
{
	pusha

	Memcpy src, dest, size
	rep movsb

	popa
}

macro Memcpyw src, dest, size
{
	pusha

	Memcpy src, dest, size
	rep movsw

	popa
}

macro Memcpyd src, dest, size
{
	pusha

	Memcpy src, dest, size
	rep movsd

	popa
}
