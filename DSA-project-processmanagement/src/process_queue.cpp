#include "process_queue.h"

// process queue -- done
void initialize_process_queue(PROCESS_QUEUE *pq)
{
    //  pq->queue => is array so do not need malloc
    pq->front = -1;
    pq->rear = 0;
    pq->iteration = 0;
    pq->priority = 0;
    pq->size = 0;
}

bool isFull(PROCESS_QUEUE *pq)
{ // done
    return pq->size == QUEUE_SIZE;
}

bool isEmpty(PROCESS_QUEUE *pq)
{ // done
    return pq->size == 0;
}

PROCESS peek(PROCESS_QUEUE *pq)
{
    /*
    if (isEmpty(pq))
        return;                 // I will think this condition - pq->queue[pq->rear]
    */

    return pq->queue[pq->rear]; // done correctly
}

void enqueue(PROCESS_QUEUE *pq, PROCESS data)
{
    if (isFull(pq))
        return;
    pq->front = (pq->front + 1) % QUEUE_SIZE;
    pq->queue[pq->front] = data;
    pq->size++;
}

PROCESS dequeue(PROCESS_QUEUE *pq)
{

    if (isEmpty(pq))
    {
        PROCESS p;
        initialize_process(&p, -1, 0);
        return p; // ???????????????????????????????????????????
    }

    PROCESS deletedData = pq->queue[pq->rear];
    pq->rear = (pq->rear + 1) % QUEUE_SIZE;
    pq->size--;
    return deletedData;
}