#include "queue.h"




// Function to initialize an empty integer queue
int queue_init(Queue_t *queue,void ** buffer, int cap) {
#ifdef THREAD_SAFE
    if (pthread_mutex_init(&queue->lock, NULL) != 0) {
        return -1;
    }
#endif
    queue_empty(queue);
    queue->capacity = cap;
    queue->data = buffer;
    return 1;
}
int queue_deInit(Queue_t *queue){
#ifdef THREAD_SAFE
    pthread_mutex_destroy(&queue->lock);
#endif
}
// Function to check if the integer queue is empty
bool queue_isEmpty(Queue_t *queue) {
    return (queue->size == 0);
}

// clear queue
void queue_empty(Queue_t *queue) {
#ifdef THREAD_SAFE
    pthread_mutex_lock(&queue->lock);
#endif
    queue->tail = 0;
    queue->head = -1;
    queue->size = 0;
#ifdef THREAD_SAFE
    pthread_mutex_unlock(&queue->lock);
#endif
}

// Function to check if the integer queue is full
bool queue_isFull(Queue_t *queue) {
    return (queue->size == queue->capacity);
}

// Function to enqueue an integer into the integer queue
bool queue_enqueue(Queue_t *queue, void * data,bool fifoMode) {
#ifdef THREAD_SAFE
    pthread_mutex_lock(&queue->lock);
#endif
    if (queue_isFull(queue)) {
        if(fifoMode)
            queue_dequeue(queue);
        else
            return false; // Handle the error as needed
    }

    queue->head = (queue->head + 1) % queue->capacity;
    queue->data[queue->head] = data;
    queue->size++;
#ifdef THREAD_SAFE
    pthread_mutex_unlock(&queue->lock);
#endif
    return true;
}

//bool queue_enqueue_auto(Queue_t *queue,bool fifoMode) {
//    return queue_enqueue(queue,(queue->head + 1) % queue->capacity,fifoMode);
//}
//

// Function to dequeue an integer from the integer queue
void * queue_dequeue(Queue_t *queue) {
#ifdef THREAD_SAFE
    pthread_mutex_lock(&queue->lock);
#endif
    if (queue_isEmpty(queue)) {
        return NULL; // Handle the error as needed
    }

    void * data = queue->data[queue->tail];
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size--;
#ifdef THREAD_SAFE
    pthread_mutex_unlock(&queue->lock);
#endif
    return data;
}
// Function to dequeue an integer from the integer queue
void * queue_getByIndex(Queue_t *queue,int index) {
#ifdef THREAD_SAFE
    pthread_mutex_lock(&queue->lock);
#endif
    if (queue_isEmpty(queue) ||   index >= queue->size) {
        return NULL; // Handle the error as needed
    }
    void * ret = queue->data[(queue->tail + index) % queue->capacity];
#ifdef THREAD_SAFE
    pthread_mutex_unlock(&queue->lock);
#endif
    return ret ;
}

// Function to get the size of the integer queue
size_t queue_getSize(Queue_t *queue) {
    return queue->size;
}