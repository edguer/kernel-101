#include "queue.h"

extern void write_str_video(const char *str, short format);
extern void write_video(char chr, short format);

void program1(void)
{
    struct queue q = new_queue();
    queue_push(&q, 'a');
    queue_push(&q, 'b');
    queue_push(&q, 'c');
    write_str_video("queue count: ", 0x07);
    write_video(q.count + '0', 0x07);

    while(q.count > 0)
    {
        char res = queue_pop(&q);
        write_str_video(" res: ", 0x07);
        write_video(res, 0x07);
    }

    write_str_video(" finished ", 0x07);
}