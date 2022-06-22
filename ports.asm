;; ports.asm
;; ports handling file
bits 32                         ;nasm directive - 32 bits

section .text

global read_port
global write_port

;; reads from bus port
;; args: (port number)
read_port:
    ; gets port number from first argument from stack and put it into edx
    mov edx, [esp + 4]
    ; 'in' reads the port number from dx (lower bits from edx) and put them in al (lower bits from eax)
    in  al,  dx
    ; as the the data received is in eax, and C uses eax as the return value, we will be returning the data
    ret

;; writes to a bus port
;; args: (port number, data to be sent)
write_port:
    ; gets port number from first argument from stack and put it into edx
    mov edx, [esp + 4]
    ; puts second argument from the stack into al
    mov al,  [esp + 4 + 4]
    ; 'out' will write data from al into bus port located in dx
    out dx,  al
    ret