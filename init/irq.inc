; asmsyntax=fasm

extrn HandleIRQ

macro IRQ num
{
	public IRQ_#num
	IRQ_#num:
		cli
		push 0
		push num + 32
		call HandleIRQ
}

IRQ 0

IRQ 1

IRQ 2

IRQ 3

IRQ 4

IRQ 5

IRQ 6

IRQ 7

IRQ 8

IRQ 9

IRQ 10

IRQ 11

IRQ 12

IRQ 13

IRQ 14

IRQ 15
