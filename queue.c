#include "queue.h"

extern void write_video(char chr, short format);

struct queue new_queue()
{
    struct queue q = { 0, 0, 0 };
    return q;
}

void queue_push(struct queue* q, char data)
{
    struct linked_item item = { .next = 0, .previous = 0, .data = data };
    if (!q->start || q->count == 0)
    {
        q->count = 1;
        q->start = &item, q->end = &item;
        write_video(item.data, 0x07);
        write_video(item.next->data, 0x07);
    }
    else
    {
        write_video(item.data, 0x07);
        write_video(q->start->data, 0x07);

        item.next = q->start;

        q->start->previous = &item;
        q->start = &item;
        q->count++;

        // write_video(q->start->data, 0x07);
        // write_video('-', 0x07);
        // write_video(q->end->data, 0x07);
    }
}

char queue_pop(struct queue* q)
{
    struct linked_item* item = q->end;

    if (!item)
    {
        return 0;
    }
    else if (item->previous)
    {
        q->end = item->previous;
    }
    else
    {
        q->start = 0, q->end = 0;
    }

    q->count--;

    return item->data;
}