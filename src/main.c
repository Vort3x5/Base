#include <stdtypes.h>
#include <video.h>
#include <interrupts.h>
#include <memory.h>

void Main() 
{
	TTYReset();

	Clear();
	Print("Start!\n", BLUE);

	InitDMem();
	Print("Dynamic Memory Initialized\n", GREEN);

	IDTInstall();
	ISRsInstall();
	IRQsInstall();
	__asm__("sti");
	Print("Interrupts Installed\n", GREEN);

	PrintSepration();

	Print("Finish!", BLUE);

	_Halt();
}
