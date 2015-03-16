#include "console.h"

extern void WriteChar(char c, int row, int col, uint8 color)
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

extern uint32 GetConsoleOffset(int row, int col)
{
	return (row * CONSOLE_WIDTH + col) * 2;
}

extern uint32 GetCursor()
{
	// the device uses its control register as an index
	// to select its internal registers, of which we are
	// interested in
	// reg 14: which is the high byte of the cursor's offset
	// reg 15: which is the low byte of the cursor's offset
	// Once the internal register has been selected, we may read or
	// write a byte on the data register
	WritePort_Byte(REG_SCREEN_CTRL, 14);
	uint32 offset = ReadPort_Byte(REG_SCREEN_DATA) << 8;
	WritePort_Byte(REG_SCREEN_CTRL, 15);
	offset += ReadPort_Byte(REG_SCREEN_DATA);
	// Since the cursor offset reported by the VGA hardware is the
	// number of characters, we multiply by two to convert it to 
	// a character cell offset
	return offset * 2;
}

extern void SetCursor(uint16 offset)
{
    // offset represents character offset, not offset relative to VIDEO_MEM_ADDRESS
    uint8 highByte = 0;
    uint8 lowByte = 0;
    highByte = (offset & 0xF0) >> 8;
    lowByte = offset & 0X0F;

    WritePort_Byte(REG_SCREEN_CTRL, 14);
    WritePort_Byte(REG_SCREEN_DATA, highByte);
    WritePort_Byte(REG_SCREEN_CTRL, 15);
    WritePort_Byte(REG_SCREEN_DATA, lowByte);
}
