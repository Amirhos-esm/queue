#include "queue.h"


// Function to initialize an empty integer queue
void queue_init(Queue_t *queue,void ** buffer, int cap) {
    queue->tail = 0;
    queue->head = 0;
    queue->capacity = cap;
    queue->data = buffer;
}

// Function to check if the integer queue is empty
bool queue_isEmpty(Queue_t *queue) {
    return (queue_getSize(queue) == 0);
}

// clear queue
void queue_empty(Queue_t *queue) {
    queue_init(queue,queue->data,queue->capacity);
}

// Function to check if the integer queue is full
bool queue_isFull(Queue_t *queue) {
    return (queue_getSize(queue)== queue->capacity);
}

// Function to enqueue an integer into the integer queue
bool queue_enqueue(Queue_t *queue, void * data,bool fifoMode) {
    if (queue_isFull(queue)) {
        if(fifoMode)
            queue_dequeue(queue);
        else
            return false; // Handle the error as needed
    }

    queue->data[queue->head] = data;
    queue->head = (queue->head + 1) % (queue->capacity + 1);

    return true;
}

//bool queue_enqueue_auto(Queue_t *queue,bool fifoMode) {
//    return queue_enqueue(queue,(queue->head + 1) % queue->capacity,fifoMode);
//}
//

// Function to dequeue an integer from the integer queue
void * queue_dequeue(Queue_t *queue) {
    if (queue_isEmpty(queue)) {
        return NULL; // Handle the error as needed
    }

    void * data = queue->data[queue->tail];
    queue->tail = (queue->tail + 1) % (queue->capacity + 1);
    return data;
}
// Function to dequeue an integer from the integer queue
void * queue_getByIndex(Queue_t *queue,int index) {
    if (queue_isEmpty(queue) ||   index >= queue_getSize(queue)) {
        return NULL; // Handle the error as needed
    }
    return queue->data[(queue->tail + index) % (queue->capacity + 1)];
}

// Function to get the size of the integer queue
size_t queue_getSize(Queue_t *queue) {
    if(queue->head >= queue->tail){
        return queue->head - queue->tail;
    }
    return queue->head + queue->capacity + 1 - queue->tail;
}