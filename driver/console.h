#ifndef CONSOLE_H
#define CONSOLE_H

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25
#define CONSOLE_BUFFER_SIZE (CONSOLE_WIDTH * CONSOLE_HEIGHT * 2) 

#define VIDEO_MEM_ADDRESS 0xB8000

//the high 4 bits represent background color and
//the low 4 bits represnet foreground color
/*
	0	black
	1	blue
	2	green
	3	cyan
	4	red
	5	magenta
	6	brown
	7	light gray
	8	dark gray
	9	light blue
	a	light green
	b	light cyan
	c	light red
	d	light magenta
	e	yellow
	f	white
*/
#define WHITE_ON_BLACK 0x0F
#define GREEN_ON_BLACK 0x02
#define RED_ON_BLACK 0x04
#define BLUE_ON_BLACK 0x09

// screen device io ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#include "types.h"

void WriteChar(char c, int row, int col, uint8 color);
uint32 GetConsoleOffset(int row, int col);

#endif