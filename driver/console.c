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
		vidmem[offset] = c;
		vidmem[offset + 1] = color;
	}

    // set cursor to next character position
    offset += 2;
	offset = HandleScroll(offset);
    SetCursor(offset >> 1);
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
    highByte = (offset & 0xFF00) >> 8;
    lowByte = offset & 0X00FF;

    WritePort_Byte(REG_SCREEN_CTRL, 14);
    WritePort_Byte(REG_SCREEN_DATA, highByte);
    WritePort_Byte(REG_SCREEN_CTRL, 15);
    WritePort_Byte(REG_SCREEN_DATA, lowByte);
}

extern void ClearConsole(uint8 color)
{
    if(color == 0)
        color = WHITE_ON_BLACK;
    uint8 *p = (uint8*)VIDEO_MEM_ADDRESS;
    uint32 end = CONSOLE_WIDTH * CONSOLE_HEIGHT * 2;
    uint32 i;
    for(i = 0; i < end; ++i)
    {
        p[i++] = 0;
        p[i] = color;
    }
}

uint32 HandleScroll(uint16 offset)
{
	if(offset < (CONSOLE_WIDTH * CONSOLE_HEIGHT * 2))
		return offset;
	else
	{
		uint8 *start = (uint8*)VIDEO_MEM_ADDRESS;
		uint8 *p = start + CONSOLE_WIDTH * 2;
		uint32 i;
		for(i = 0; i < CONSOLE_WIDTH * (CONSOLE_HEIGHT - 1) * 2; ++i)
			*start++ = *p++;
		
		// clear last line
		for(i = 0; i < CONSOLE_WIDTH * 2; i += 2)
			start[i] = 0;
		
		return offset - 2 * CONSOLE_WIDTH;
	}
}

extern void WriteString(string s, int row, int col, uint8 color)
{
	uint32 offset;
	uint8 *p = s;
	if(row >= 0 && col >= 0)
	{
		offset = GetConsoleOffset(row, col);
		SetCursor(offset >> 1);
	}
	else
		offset = GetCursor();
	
	if(color == 0)
		color = WHITE_ON_BLACK;
	
	while(*p != '\0')
	{
		WriteChar(*p, -1, -1, color);
		p++;
	}
}