//
// Created by Administrator on 10/4/2023.
//

#ifndef __QUEUE_H
#define __QUEUE_H

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"

// Define a structure for the integer queue
typedef struct {
    void **data;
    int front;
    int rear;
    size_t size;
    int capacity;
} Queue_t;

void * queue_dequeue(Queue_t *queue);

void queue_init(Queue_t *queue, void **buffer, int cap);

bool queue_isEmpty(Queue_t *queue);

bool queue_isFull(Queue_t *queue);

bool queue_enqueue(Queue_t *queue, void * data, bool fifoMode);

//bool queue_enqueue_auto(Queue_t *queue, bool fifoMode);

size_t queue_getSize(Queue_t *queue);

void * queue_getByIndex(Queue_t *queue,int index);

void queue_empty(Queue_t *queue);

#endif
