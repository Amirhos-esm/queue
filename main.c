#include <stdio.h>
#include "queue.h"

Queue_t queue;


int main() {
    void * array[4];
    queue_init(&queue,array,3);

    queue_enqueue(&queue,(void *)1,false);
    queue_enqueue(&queue,(void *)2,false);
    queue_enqueue(&queue,(void *)3,false);

    printf("%p\n", queue_dequeue(&queue));
    queue_enqueue(&queue,(void *)4,false);
    printf("%p\n", queue_dequeue(&queue));
    queue_enqueue(&queue,(void *)5,false);
    printf("index:1 %p\n", queue_getByIndex(&queue,1));
    printf("%p\n", queue_dequeue(&queue));
    printf("%p\n", queue_dequeue(&queue));
    printf("%p\n", queue_dequeue(&queue));
    return 0;
}
