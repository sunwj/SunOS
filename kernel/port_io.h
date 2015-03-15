#ifndef PORT_IO_H
#define PORT_IO_H

#include "types.h"

extern uint8 ReadPort_Byte(uint16 port);
extern uint16 ReadPort_Word(uint16 port);
extern void WritePort_Byte(uint16 port, uint8 data);
extern void WritePort_Word(uint16 port, uint16 data);

#endif
