#include <io.h>

#include <stdtypes.h>

u8 InB(u16 port)
{
	u8 res;
	__asm__("inb %1, %0" : "=a"(res) : "Nd"(port));
	return res;
}

u16 InW(u16 port)
{
	u16 res;
	__asm__("inw %1, %0" : "=a"(res) : "Nd"(port));
	return res;
}

u32 InL(u16 port)
{
	u32 res;
	__asm__("inl %1, %0" : "=a"(res) : "Nd"(port));
	return res;
}

void OutB(u16 port, u8 data)
{
	__asm__("outb %0, %1" : : "a"(data), "Nd"(port));
}

void OutW(u16 port, u16 data)
{
	__asm__("outw %0, %1" : : "a"(data), "Nd"(port));
}

void OutL(u16 port, u32 data)
{
	__asm__("outl %0, %1" : : "a"(data), "Nd"(port));
}

u8 MMInB(u32 addr)
{
	return *((u8 *)(addr));
}

u16 MMInW(u32 addr)
{
	return *((u16 *)(addr));
}

u32 MMInL(u32 addr)
{
	return *((u32 *)(addr));
}

void MMOutB(u32 addr, u8 val)
{
	*((u8 *)(addr)) = val;
}

void MMOutW(u32 addr, u16 val)
{
	*((u16 *)(addr)) = val;
}

void MMOutL(u32 addr, u32 val)
{
	*((u32 *)(addr)) = val;
}
