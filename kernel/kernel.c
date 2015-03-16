#include "types.h"
#include "console.h"

void main()
{
	uint32 i = 0;
    ClearConsole(0);
    SetCursor(0);
	
	WriteString("SunOS, a simple operating system!", 12, 20, GREEN_ON_BLACK);
}
