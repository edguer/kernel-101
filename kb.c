#include "constants.h"

#define PIC_EOI_CMD 0x20

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_KEY_PORT 0x60

extern void write_port(unsigned short port, unsigned char data);
extern char read_port(unsigned short port);
extern void write_video(char chr, short format);

unsigned short char_received = 0;
char last_received_char = '\0';

// Initializes the keyboard
void init_kb(void)
{
    // Sending message to PIC1 (0x21)
    // 0xFD == 11111101, meaning we are only enabling IRQ1 (keyboard)
    write_port(PIC1_DATA_ADDRS, KEYBOARD_ONLY_IRQ_MASK);
}

void keyboard_handler_main(void)
{
    // Send a EOI (end of interrupt) command to PIC1
    write_port(PIC1_CMD_ADDRS, PIC_EOI_CMD);

    // Port 0x64 gives keyboard status
    unsigned char status = read_port(KEYBOARD_STATUS_PORT);

    // If status last bit is different than 0, then there is data in the buffer
    if (status & 0x01)
    {
        // 0x60 port gives last key stroke
        unsigned char keycode = read_port(KEYBOARD_KEY_PORT);
        if (keycode >= 0)
        {
            last_received_char = keyboard_map[keycode];
            char_received = 1;
        }

    }
}

char read_key(void)
{
    while(!char_received)
    {

        char_received = 0;
        return last_received_char;
    }
}