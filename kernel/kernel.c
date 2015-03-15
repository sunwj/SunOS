#include "console.h"

void main()
{
	ClearConsole(GREEN_ON_BLACK);

    WriteChar('S', GREEN_ON_BLACK);
    WriteChar('U', GREEN_ON_BLACK);
    WriteChar('N', GREEN_ON_BLACK);
	
	WriteString("a simple Operating System. SunOS", GREEN_ON_BLACK);
}
