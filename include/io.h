#pragma once

#include <stdtypes.h>

u8 InB(u16 port);
u16 InW(u16 port);
u32 InL(u16 port);
void OutB(u16 port, u8 data);
void OutW(u16 port, u16 data);
void OutL(u16 port, u32 data);

u8 MMInB(u32 addr);
u16 MMInW(u32 addr);
u32 MMInL(u32 addr);
void MMOutB(u32 addr, u8 val);
void MMOutW(u32 addr, u16 val);
void MMOutL(u32 addr, u32 val);
