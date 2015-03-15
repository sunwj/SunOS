#ifndef PORT_IO_H
#define PORT_IO_H

#include "types.h"

uint8 ReadPort_Byte(uint16 port);
uint16 ReadPort_Word(uint16 port);
void WritePort_Byte(uint16 port, uint8 data);
void WritePort_Word(uint16 port, uint16 data);

#endif
