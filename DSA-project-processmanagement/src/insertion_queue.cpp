#include "insertion_queue.h"

// insertion queue -- done
void initialize_execution_queue(INSERTION_QUEUE *iq)
{
    // iq->queue => is array so do not need malloc
    iq->front = -1;
    iq->rear = 0;
    iq->size = 0;
}

bool isFull(INSERTION_QUEUE *iq)
{
    return iq->size == MAX_OPERATION;
}

bool isEmpty(INSERTION_QUEUE *iq)
{
    return iq->size == 0;
}

PROCESS_QUEUE peek(INSERTION_QUEUE *iq)
{
    /*
    if (isEmpty(iq))
        return; // ??????????????????????????????????????????? iq->queue[0]
    */
    return iq->queue[iq->front];
}

void enqueue(INSERTION_QUEUE *iq, PROCESS_QUEUE data)
{
    if (isFull(iq))
        return;
    iq->front = (iq->front + 1) % MAX_OPERATION;
    iq->queue[iq->front] = data;
    iq->size++;
}

PROCESS_QUEUE dequeue(INSERTION_QUEUE *iq)
{

    if (isEmpty(iq))
    {
        PROCESS_QUEUE pq;
        initialize_process_queue(&pq);
        return pq; // ???????????????????????????????????????????
    }
    PROCESS_QUEUE deletedData = iq->queue[iq->rear];
    iq->rear = (iq->rear + 1) % MAX_OPERATION;
    iq->size--;
    return deletedData;
}