#include "port_io.h"

uint8 ReadPort_Byte(uint16 port)
{
	// C wrapper function that reads a byte from the specified port
	// "=a" (result) means: put AL register in variable RESULT when finished
	// "d" (port) means: load EDX with port
	uint8 result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void WritePort_Byte(uint16 port, uint8 data)
{
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16 ReadPort_Word(uint16 port)
{
	uint16 result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void WritePort_Word(uint16 port, uint16 data)
{
	__asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
