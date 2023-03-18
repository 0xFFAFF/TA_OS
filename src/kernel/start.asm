[bits 32]

extern kernel_init

global _start
_start:
    ; mov byte[0xb8000], 'k'
    xchg bx, bx
    call kernel_init
    xchg bx, bx
    jmp $ + 2
    jmp $ + 2
    jmp $ + 2