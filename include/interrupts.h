#pragma once

#include <stdtypes.h>

#define GDT_CODE_SEGMENT 0x08

#ifdef IRQ_DEF

static s32 curr_irq_slot = 0;
bool k_pressed = false;

#endif

#ifndef IRQ_DEF

extern bool k_pressed;

#endif

struct IDT_Entry
{
	word base_lo;
	word sel;
	byte always0;
	byte flags;
	word base_hi;
} __attribute__((packed));

struct IDT_Ptr
{
	word limit;
	dword base;
} __attribute__((packed));

extern void _Halt();
extern void _IDTLoad();

void IDTSetGate(byte index, dword base);
void IDTInstall();

extern void ISR_0();
extern void ISR_1();
extern void ISR_2();
extern void ISR_3();
extern void ISR_4();
extern void ISR_5();
extern void ISR_6();
extern void ISR_7();
extern void ISR_8();
extern void ISR_9();
extern void ISR_10();
extern void ISR_11();
extern void ISR_12();
extern void ISR_13();
extern void ISR_14();
extern void ISR_15();
extern void ISR_16();
extern void ISR_17();
extern void ISR_18();
extern void ISR_19();
extern void ISR_20();
extern void ISR_21();
extern void ISR_22();
extern void ISR_23();
extern void ISR_24();
extern void ISR_25();
extern void ISR_26();
extern void ISR_27();
extern void ISR_28();
extern void ISR_29();
extern void ISR_30();
extern void ISR_31();

void ISRsInstall();
void FaultHandler(s32 int_num);

extern void IRQ_0();
extern void IRQ_1();
extern void IRQ_2();
extern void IRQ_3();
extern void IRQ_4();
extern void IRQ_5();
extern void IRQ_6();
extern void IRQ_7();
extern void IRQ_8();
extern void IRQ_9();
extern void IRQ_10();
extern void IRQ_11();
extern void IRQ_12();
extern void IRQ_13();
extern void IRQ_14();
extern void IRQ_15();
 
void InstallIRQHandler(void *handler, s32 irq_slot);
void UninstallIRQHandler(s32 irq);
void RemapIRQ();
void IRQsInstall();
void HandleIRQ(s32 int_num);
