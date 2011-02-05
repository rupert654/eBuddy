/**
 * @file   queue.h
 * @author Rupert Madden-Abbott
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include <pthread.h>

#include "utility.h"

typedef struct qu_node {
    void *data;
    struct qu_node *link;
} qu_node;

typedef struct qu_queue {
    pthread_mutex_t mutex;
    int size;
    qu_node *head;
    qu_node *tail;
} qu_queue;

qu_queue *qu_init(void);
void qu_free(qu_queue *queue);
int qu_push(qu_queue *queue, void *data);
void *qu_pop(qu_queue *queue);
int qu_size(qu_queue *queue);

#endif

