#include <interrupts.h>

#include <stdtypes.h>
#include <memory.h>

static struct IDT_Entry idt[256];
struct IDT_Ptr idtp;

void IDTSetGate(byte index, dword base)
{
	idt[index] = (struct IDT_Entry) {
		.base_lo = (base) & 0xffff,
		.base_hi = (u32)(base >> 16),
		.sel = GDT_CODE_SEGMENT,
		.flags = 0x8e,
		.always0 = 0
	};
}

void IDTInstall()
{
	idtp.limit = (sizeof (struct IDT_Entry) * 256) - 1;
	idtp.base = (dword) &idt[0];

	Memset((void *)&idt[0], 0, (sizeof (struct IDT_Entry)) * 256);

	_IDTLoad();
}
