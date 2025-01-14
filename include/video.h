#pragma once

#include <stdtypes.h>

#define VGA_ADDR 0xb8000

#define TEXT_MODE_ROWS 25
#define TEXT_MODE_COLS 80

#define VGA_CTRL_REG 0x3d4
#define VGA_DATA_REG 0x3d5

enum Colors
{
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
};

typedef struct {
	word *vga_text_buffer;
	u32 addr;
} TTY;

#ifdef TTY_DEF

static TTY *tty;

#endif

static inline word VgaEntry(byte c, enum Colors color)
	{ return (word) c | (word) color << 8; }

void TTYReset();
void Clear();
void PutC(char c, enum Colors color);
void Print(const char *msg, enum Colors color);
void PrintNum(u64 num, enum Colors color);
void PrintSepration();
void PrintIter(u64 num, enum Colors color);
