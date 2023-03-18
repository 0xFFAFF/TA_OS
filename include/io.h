#ifndef _TAOS_IO_H
#define _TAOS_IO_H

#include<types.h>

extern u8 inb(u16 port);
extern u16 inw(u16 port);

extern void outb(u16 port, u8 value);
extern void outw(u16 port, u8 value);


#endif