#include "console.h"

void WriteChar(char c, int row, int col, uint8 color)
{
	uint8 *vidmem = (uint8*)VIDEO_MEM_ADDRESS;
	if(!color)
		color = WHITE_ON_BLACK;
	
	uint32 offset;
	if(row >= 0 && col >=0)
		offset = GetConsoleOffset(row, col);
	else
		offset = GetCursor();
	
	if(c == '\n')
	{
		uint32 rows = offset / (2 * CONSOLE_WIDTH);
		offset = GetConsoleOffset(rows, 79);
	}
	else
	{
		vidmem[offset++] = c;
		vidmem[offset] = color;
	}
}

uint32 GetConsoleOffset(int row, int col)
{
	return (row * CONSOLE_WIDTH + col) * 2;
}