// total video memory is 25 lines, 80 columns and 2 bytes for each character
const unsigned short vid_size = 80 * 25 * 2;

// at a hardware level, the vid memory starts at this physical address
char *vid_ptr = (char*)0xb8000;

// video pointer offset
unsigned short vid_offset = 0;

// writes a character to the screen
void write_char_screen(char chr, short format)
{
    vid_ptr[vid_offset] = chr;
    vid_ptr[vid_offset + 1] = format;

    vid_offset += 2;
}

// writes a string to the screen
void write_string_screen(const char *str, short format)
{
    for (unsigned short i = 0; str[i] != '\0'; i++)
    {
        write_char_screen(str[i], format);
    }
}

// resets the screen, cleans iy up
void reset_screen()
{
    for (unsigned short i = 0; i < vid_size; i += 2)
    {
        vid_ptr[i] = ' ';
        vid_ptr[i + 1] = 0x07;
    }
}

// converts a short to char
char to_char(short number)
{
    return number + '0';
}

// kernel entrypoint
void kmain(void)
{
    const char *str = "This is a kernel, somewhat...";
    const int default_format = 0x07;

    reset_screen();
    write_string_screen(str, default_format);

    for (unsigned short i = 0; i < 10; i++)
    {
        write_char_screen(to_char(i), default_format);
    }

    return;
}