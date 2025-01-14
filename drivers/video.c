#define TTY_DEF
#include <video.h>

#include <stdtypes.h>
#include <memory.h>
// #include <demo.h>

void TTYReset()
{
	tty->vga_text_buffer = (word *) VGA_ADDR;
	tty->addr = 0;
}

void Clear()
{
	s32 area = TEXT_MODE_COLS * TEXT_MODE_ROWS;

	for (s32 i = 0; i < area; ++i)
		tty->vga_text_buffer[i] = VgaEntry(0, WHITE);

	TTYReset();
}

void PutC(char c, enum Colors color)
{
	switch(c)
	{
		case '\n':
			tty->addr += TEXT_MODE_COLS - ((tty->addr) % TEXT_MODE_COLS);
			break;

		default:
			tty->vga_text_buffer[tty->addr] = VgaEntry(c, color);
			++(tty->addr);
			break;
	}
}

void Print(const char *msg, enum Colors color)
{
	for (s32 i = 0; msg[i]; ++i)
		PutC(msg[i], color);
}

void PrintNum(u64 num, enum Colors color)
{
	if (num == 0)
	{
		PutC('0', color);
		return;
	}
	u64 buff = num;
 	u16 len = 0;
	while (buff)
	{
		++len;
		buff /= 10;
	}

	char *backward = (char *)Malloc(len), *msg = (char *)Malloc(len + 1);
	for (s32 i = 0; i < len; ++i, num /= 10)
		backward[i] = '0' + (num % 10);

	for (s32 i = 0, j = len - 1; i < len; ++i, --j)
		msg[i] = backward[j];
	msg[len] = '\0';
	Print(msg, color);

	Free((u64)msg, len + 1);
	Free((u64)backward, len);
}

void PrintSepration()
{
	for (s32 i = 0; i < TEXT_MODE_COLS; ++i)
		PutC('-', DARK_GRAY);
}

void PrintIter(u64 num, enum Colors color)
{
	PrintNum(num, color);
	if (num == 0)
	{
		--(tty->addr);
		return;
	}
	u8 res;
	for (res = 0; num; num /= 10)
		++res;
	tty->addr -= res;
}
















