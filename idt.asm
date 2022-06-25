;; ports.asm
;; IDT handling file
bits 32                         ;nasm directive - 32 bits

section .text

global load_idt

;; loads IDT table
;; args: (pointer to IDT table)
load_idt:
    ; first stack argument is the pointer to IDT table
    ; we load it to edx, where lidt will look at
    mov  edx, [esp + 4]
    ; executes load idt operation to edx
    lidt [edx]
    ; turns on interrupts
    sti
    ret