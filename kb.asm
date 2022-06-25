;; ports.asm
;; keyboard handling file
bits 32                         ;nasm directive - 32 bits

section .text

global keyboard_handler
extern keyboard_handler_main

;; function that handles keyboard interrupts - the one loaded into IDT
keyboard_handler:
    ; calls our C function
    call keyboard_handler_main
    ; iretd should be used with interrupt handlers
    iretd