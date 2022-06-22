;;kernel.asm
bits 32                         ;nasm directive - 32 bits

section .text
    ;multiboot space
    align 4
    dd 0x1BADB002               ;magic
    dd 0x00                     ;flags
    dd - (0x1BADB002 + 0x00)     ;checksum, mfc should be zero

global start
extern kmain                    ;kmain is defined in the c file

start:
    cli                         ;cancel interrupts
    mov esp, stack_space        ;move stack pointer to the stack_pace variable
    call kmain
    hlt

section .bss
    resb 8192                   ;we are setting up stack stack space
    stack_space:                ;this variable works as a pointer to the top of the stack