# 编译链接的过程

1. 预处理
`gcc -m32 -E -I../../include main.c > test.c`
```c++
# 0 "main.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "main.c"
# 1 "../../include/taos.h" 1



void kernel_init();
# 2 "main.c" 2

int magic = 20230113;
char msg[] = "hello taos!";
char buf[1024];
void kernel_init()
{
    char * screen_ram_addr = (char *) 0xb8000;
    for (int i = 0; i < sizeof msg; i++)
    {
        screen_ram_addr[i * 2] = msg[i];
    }
}
```
2. 编译
`gcc -m32 -S test.c > test.s`
```s
	.file	"test.c"
	.text
	.globl	magic
	.data
	.align 4
	.type	magic, @object
	.size	magic, 4
magic:
	.long	20230113
	.globl	msg
	.align 4
	.type	msg, @object
	.size	msg, 12
msg:
	.string	"hello taos!"
	.globl	buf
	.bss
	.align 32
	.type	buf, @object
	.size	buf, 1024
buf:
	.zero	1024
	.text
	.globl	kernel_init
	.type	kernel_init, @function
kernel_init:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$16, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$753664, -8(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	movl	-12(%ebp), %edx
	addl	%edx, %edx
	movl	%edx, %ecx
	movl	-8(%ebp), %edx
	addl	%edx, %ecx
	leal	msg@GOTOFF(%eax), %ebx
	movl	-12(%ebp), %edx
	addl	%ebx, %edx
	movzbl	(%edx), %edx
	movb	%dl, (%ecx)
	addl	$1, -12(%ebp)
.L2:
	movl	-12(%ebp), %edx
	cmpl	$11, %edx
	jbe	.L3
	nop
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	kernel_init, .-kernel_init
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB1:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE1:
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits

```

3. 汇编以生成目标文件
`as -32 test.s -o test.o`
```elf
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          728 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           40 (bytes)
  Number of section headers:         15
  Section header string table index: 14

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .group            GROUP           00000000 000034 000008 04     12   8  4
  [ 2] .text             PROGBITS        00000000 00003c 000050 00  AX  0   0  1
  [ 3] .rel.text         REL             00000000 000220 000018 08   I 12   2  4
  [ 4] .data             PROGBITS        00000000 00008c 000010 00  WA  0   0  4
  [ 5] .bss              NOBITS          00000000 0000a0 000400 00  WA  0   0 32
  [ 6] .text.__x86.[...] PROGBITS        00000000 0000a0 000004 00 AXG  0   0  1
  [ 7] .comment          PROGBITS        00000000 0000a4 000013 01  MS  0   0  1
  [ 8] .note.GNU-stack   PROGBITS        00000000 0000b7 000000 00      0   0  1
  [ 9] .note.gnu.pr[...] NOTE            00000000 0000b8 000028 00   A  0   0  4
  [10] .eh_frame         PROGBITS        00000000 0000e0 000050 00   A  0   0  4
  [11] .rel.eh_frame     REL             00000000 000238 000010 08   I 12  10  4
  [12] .symtab           SYMTAB          00000000 000130 0000a0 10     13   4  4
  [13] .strtab           STRTAB          00000000 0001d0 00004e 00      0   0  1
  [14] .shstrtab         STRTAB          00000000 000248 00008d 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  D (mbind), p (processor specific)

COMDAT group section [    1] `.group' [__x86.get_pc_thunk.ax] contains 1 sections:
   [Index]    Name
   [    6]   .text.__x86.get_pc_thunk.ax

There are no program headers in this file.

There is no dynamic section in this file.

Relocation section '.rel.text' at offset 0x220 contains 3 entries:
 Offset     Info    Type            Sym.Value  Sym. Name
00000008  00000802 R_386_PC32        00000000   __x86.get_pc_thunk.ax
0000000d  0000090a R_386_GOTPC       00000000   _GLOBAL_OFFSET_TABLE_
0000002f  00000509 R_386_GOTOFF      00000004   msg

Relocation section '.rel.eh_frame' at offset 0x238 contains 2 entries:
 Offset     Info    Type            Sym.Value  Sym. Name
00000020  00000202 R_386_PC32        00000000   .text
00000044  00000302 R_386_PC32        00000000   .text.__x86.get_p[...]
No processor specific unwind information to decode

Symbol table '.symtab' contains 10 entries:
   Num:    Value  Size Type    Bind   Vis      Ndx Name
     0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 00000000     0 FILE    LOCAL  DEFAULT  ABS test.c
     2: 00000000     0 SECTION LOCAL  DEFAULT    2 .text
     3: 00000000     0 SECTION LOCAL  DEFAULT    6 .text.__x86.get_[...]
     4: 00000000     4 OBJECT  GLOBAL DEFAULT    4 magic
     5: 00000004    12 OBJECT  GLOBAL DEFAULT    4 msg
     6: 00000000  1024 OBJECT  GLOBAL DEFAULT    5 buf
     7: 00000000    80 FUNC    GLOBAL DEFAULT    2 kernel_init
     8: 00000000     0 FUNC    GLOBAL HIDDEN     6 __x86.get_pc_thunk.ax
     9: 00000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_

No version information found in this file.

Displaying notes found in: .note.gnu.property
  Owner                Data size        Description
  GNU                  0x00000018       NT_GNU_PROPERTY_TYPE_0
      Properties: x86 ISA used: 
        x86 feature used: x86
```
4. 链接
`ld -m elf_i386 -static test.o -o test -e kernel_init`

    `readelf -a test`
```
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x8049000
  Start of program headers:          52 (bytes into file)
  Start of section headers:          12712 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         8
  Size of section headers:           40 (bytes)
  Number of section headers:         11
  Section header string table index: 10

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .note.gnu.pr[...] NOTE            08048134 000134 000028 00   A  0   0  4
  [ 2] .text             PROGBITS        08049000 001000 000054 00  AX  0   0  1
  [ 3] .eh_frame         PROGBITS        0804a000 002000 000050 00   A  0   0  4
  [ 4] .got.plt          PROGBITS        0804bff4 002ff4 00000c 04  WA  0   0  4
  [ 5] .data             PROGBITS        0804c000 003000 000010 00  WA  0   0  4
  [ 6] .bss              NOBITS          0804c020 003010 000400 00  WA  0   0 32
  [ 7] .comment          PROGBITS        00000000 003010 000012 01  MS  0   0  1
  [ 8] .symtab           SYMTAB          00000000 003024 0000c0 10      9   4  4
  [ 9] .strtab           STRTAB          00000000 0030e4 000066 00      0   0  1
  [10] .shstrtab         STRTAB          00000000 00314a 00005b 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  D (mbind), p (processor specific)

There are no section groups in this file.

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  LOAD           0x000000 0x08048000 0x08048000 0x0015c 0x0015c R   0x1000
  LOAD           0x001000 0x08049000 0x08049000 0x00054 0x00054 R E 0x1000
  LOAD           0x002000 0x0804a000 0x0804a000 0x00050 0x00050 R   0x1000
  LOAD           0x002ff4 0x0804bff4 0x0804bff4 0x0001c 0x0042c RW  0x1000
  NOTE           0x000134 0x08048134 0x08048134 0x00028 0x00028 R   0x4
  GNU_PROPERTY   0x000134 0x08048134 0x08048134 0x00028 0x00028 R   0x4
  GNU_STACK      0x000000 0x00000000 0x00000000 0x00000 0x00000 RW  0x10
  GNU_RELRO      0x002ff4 0x0804bff4 0x0804bff4 0x0000c 0x0000c R   0x1

 Section to Segment mapping:
  Segment Sections...
   00     .note.gnu.property 
   01     .text 
   02     .eh_frame 
   03     .got.plt .data .bss 
   04     .note.gnu.property 
   05     .note.gnu.property 
   06     
   07     .got.plt 

There is no dynamic section in this file.

There are no relocations in this file.
No processor specific unwind information to decode

Symbol table '.symtab' contains 12 entries:
   Num:    Value  Size Type    Bind   Vis      Ndx Name
     0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 00000000     0 FILE    LOCAL  DEFAULT  ABS test.c
     2: 00000000     0 FILE    LOCAL  DEFAULT  ABS 
     3: 0804bff4     0 OBJECT  LOCAL  DEFAULT    4 _GLOBAL_OFFSET_TABLE_
     4: 08049050     0 FUNC    GLOBAL HIDDEN     2 __x86.get_pc_thunk.ax
     5: 0804c004    12 OBJECT  GLOBAL DEFAULT    5 msg
     6: 08049000    80 FUNC    GLOBAL DEFAULT    2 kernel_init
     7: 0804c010     0 NOTYPE  GLOBAL DEFAULT    6 __bss_start
     8: 0804c020  1024 OBJECT  GLOBAL DEFAULT    6 buf
     9: 0804c000     4 OBJECT  GLOBAL DEFAULT    5 magic
    10: 0804c010     0 NOTYPE  GLOBAL DEFAULT    5 _edata
    11: 0804c420     0 NOTYPE  GLOBAL DEFAULT    6 _end

No version information found in this file.

Displaying notes found in: .note.gnu.property
  Owner                Data size        Description
  GNU                  0x00000018       NT_GNU_PROPERTY_TYPE_0
      Properties: x86 feature used: x86
        x86 ISA used: 
```

## gcc 集成以上的命令

`gcc --verbose -m32 main.c -I../../include -o main.out -e kernel_init -nostartfiles`