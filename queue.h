#ifndef QUEUE_H
#define QUEUE_H

struct linked_item
{
    struct linked_item* next;
    struct linked_item* previous;
    char data;
};

struct queue
{
    unsigned int count;
    struct linked_item* start;
    struct linked_item* end;
};

struct queue new_queue();
void queue_push(struct queue* q, char data);
char queue_pop(struct queue* q);

#endif