# io.asm

## function list
- `u8 inb(u16 port)`
- `void outb(u16 port, u8 value)`
- `u16 inw()`
- `void outw()`

## specific uses
- `u8 inb(u16 port)`
```
read 8 bits data from the port and then return the data
```
- `void out(u16 port, u8 value)`
```
write the 8 bits data value to u16 port
```