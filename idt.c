#include "constants.h"

#define IDT_SIZE 256

extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

/*
 * x86 processors stablished a data structure called Interrupt Descriptor Table
 * They are composed of 64 bits, in this schema:
 *   - 1 to 16 bit: lower bits of the instruction address that will be executed when an interrupt comes in
 *   - 17 to 32 bit: kernel data segment, by default it is 0x08 address
 *   - 33 to 40 bit: fill with zeros
 *   - 41 to 48: defines the type of interrupt, or interrupt gate
 *   - 39 to 64: higher bits of the instruction address that will be executed when an interrupt comes in
 *
 * Because C structs are stored on contiguous linear memory, we can use them to design the descriptor.
 */
struct idt_struct
{
    unsigned short offset_lowerbits;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_higherbits;
};

struct idt_struct idt[IDT_SIZE];

// Initializes IDT and PICs
void idt_init(void)
{
    unsigned long keyboard_address = (unsigned long)keyboard_handler;
    unsigned long idt_address = (unsigned long)idt;
    unsigned long idt_ptr[] =
    {
        (sizeof(struct idt_struct) * IDT_SIZE) + ((idt_address & 0xffff) << 16),
        idt_address >> 16
    };

    /*
     * we are choosing to push the IDT for PIC1 (Programmable Interrupt Controller)
     * whose address is 0x20. It is composed of 8 interrupt request numbers
     * keyboards use IRQ1, so their IDT should be located at the first byte after PIC1 address
     * meaning 0x21.
     */
    idt[0x21].offset_lowerbits = keyboard_address & 0xffff;
    idt[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET; // kernel data segment offset
    idt[0x21].zero = 0;
    idt[0x21].type_attr = INTERRUPT_GATE; // interrupt gate address
    idt[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    /*
     * We must now initialize PIC1 and PIC2
     * PIC1 uses address 0x20 for command and 0x21 for data
     * PIC2 uses address 0xA0 for command and 0xA1 for data
     *
     * We need to send Initialization Command Words (ICW) for each, here is how it works:
     *  - First send the command for initialization, then PIC will wait for 4 words to come
     *  - Send first word, which is the address for the IDT
     *  - Send cascading config
     *  - Send environment info
     *  - Send interrupt mask to enabled/disable the 8 interrupts - it is a bit map, 0 means it is turned on
     */

    // ICW command
    write_port(PIC1_CMD_ADDRS, 0x11);
    write_port(PIC2_CMD_ADDRS, 0x11);

    // ICW IDT address
    write_port(PIC1_DATA_ADDRS, 0x20);
    write_port(PIC2_DATA_ADDRS, 0x28);

    // ICW cascading, we don't use it
    write_port(PIC1_DATA_ADDRS, 0x01);
    write_port(PIC2_DATA_ADDRS, 0x01);

    // interrupt mask, disable all
    write_port(PIC1_DATA_ADDRS, 0xff);
    write_port(PIC2_DATA_ADDRS, 0xff);

    // load idt to the processor
    load_idt(idt_ptr);
}

