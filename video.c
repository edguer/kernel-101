#include "constants.h"

// at a hardware level, the vid memory starts at this physical address
char *vid_ptr = (char*)VIDEO_MEM_LOCATION;

// video pointer offset
unsigned short vid_offset = 0;

// writes a character to the screen
void write_video(char chr, short format)
{
    vid_ptr[vid_offset] = chr;
    vid_ptr[vid_offset + 1] = format;

    vid_offset += VIDEO_CHAR_SIZE;
}

// writes a string to the screen
void write_str_video(const char *str, short format)
{
    for (unsigned short i = 0; str[i] != '\0'; i++)
    {
        write_video(str[i], format);
    }
}

// resets the screen, cleans iy up
void reset_video()
{
    for (unsigned short i = 0; i < VIDEO_SIZE; i += VIDEO_CHAR_SIZE)
    {
        vid_ptr[i] = ' ';
        vid_ptr[i + 1] = DEFAULT_VIDEO_CHAR_FORMAT;
    }
}