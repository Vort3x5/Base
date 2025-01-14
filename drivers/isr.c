#include <interrupts.h>

#include <stdtypes.h>
#include <video.h>

void ISRsInstall()
{
	IDTSetGate(0, (dword) ISR_0);
	IDTSetGate(1, (dword) ISR_1);
	IDTSetGate(2, (dword) ISR_2);
	IDTSetGate(3, (dword) ISR_3);
	IDTSetGate(4, (dword) ISR_4);
	IDTSetGate(5, (dword) ISR_5);
	IDTSetGate(6, (dword) ISR_6);
	IDTSetGate(7, (dword) ISR_7);
	IDTSetGate(8, (dword) ISR_8);
	IDTSetGate(9, (dword) ISR_9);
	IDTSetGate(10, (dword) ISR_10);
	IDTSetGate(11, (dword) ISR_11);
	IDTSetGate(12, (dword) ISR_12);
	IDTSetGate(13, (dword) ISR_13);
	IDTSetGate(14, (dword) ISR_14);
	IDTSetGate(15, (dword) ISR_15);
	IDTSetGate(16, (dword) ISR_16);
	IDTSetGate(17, (dword) ISR_17);
	IDTSetGate(18, (dword) ISR_18);
	IDTSetGate(19, (dword) ISR_19);
	IDTSetGate(20, (dword) ISR_20);
	IDTSetGate(21, (dword) ISR_21);
	IDTSetGate(22, (dword) ISR_22);
	IDTSetGate(23, (dword) ISR_23);
	IDTSetGate(24, (dword) ISR_24);
	IDTSetGate(25, (dword) ISR_25);
	IDTSetGate(26, (dword) ISR_26);
	IDTSetGate(27, (dword) ISR_27);
	IDTSetGate(28, (dword) ISR_28);
	IDTSetGate(29, (dword) ISR_29);
 	IDTSetGate(30, (dword) ISR_30);
	IDTSetGate(31, (dword) ISR_31);
}

char *exceptions[] = 
{
    "Divide By Zero",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "OOB",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unrecognized Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED"
};

void FaultHandler(s32 int_num)
{
	if (int_num < 32)
	{
		Print(exceptions[int_num], RED);
		Print(" Exception. System Halted!\n", RED);
	}
	else
		Print("Exception Out Of ISR Range. System Halted!\n", RED);
	_Halt();
}
