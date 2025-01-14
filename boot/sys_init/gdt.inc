; asmsyntax=fasm

GDT_Start:
; null
	dq 0h
; code
	dw 0ffffh
	dw 0h
	db 0h
	db 10011010b
	db 11001111b
	db 0
; data
	dw 0ffffh
	dw 0h
	db 0h
	db 10010010b
	db 11001111b
	db 0
GDT_End:
