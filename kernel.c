#include "constants.h"

extern void idt_init(void);
extern void init_kb(void);
extern void write_video(char chr, short format);
extern void write_str_video(const char *str, short format);
extern void reset_video(void);
extern void program1(void);

// kernel entrypoint
void kmain(void)
{
    reset_video();
    write_str_video("init kernel...", DEFAULT_VIDEO_CHAR_FORMAT);

    idt_init();
    init_kb();

    write_str_video(" finished!", DEFAULT_VIDEO_CHAR_FORMAT);

    write_str_video(" Running program1... ", DEFAULT_VIDEO_CHAR_FORMAT);

    program1();

    while (1);
}