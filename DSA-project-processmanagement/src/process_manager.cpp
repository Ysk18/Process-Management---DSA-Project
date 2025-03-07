#include "process_manager.h"

// process manager -- done
void initialize_process_manager(PROCESS_MANAGER *pm)
{
    // pm->deque => is array so do not need malloc
    pm->front = -1;
    pm->rear = 0;
    pm->size = 0;
}

bool isFull(PROCESS_MANAGER *pm)
{
    return pm->size == MAX_PROCESS;
}

bool isEmpty(PROCESS_MANAGER *pm)
{
    return pm->size == 0;
}

void insert_front(PROCESS_MANAGER *pm, PROCESS_QUEUE pq)
{
    if (isFull(pm))
        return;
    pm->front = (pm->front + 1) % MAX_PROCESS;
    pm->deque[pm->front] = pq;
    pm->size++;
}

void insert_rear(PROCESS_MANAGER *pm, PROCESS_QUEUE pq)
{
    if (isFull(pm))
        return;
    pm->rear = (pm->rear - 1 + MAX_PROCESS) % MAX_PROCESS;
    pm->deque[pm->rear] = pq;
    pm->size++;
}

PROCESS_QUEUE delete_front(PROCESS_MANAGER *pm)
{
    /*
    if (isEmpty(pm))
        return; // ??????????????????????????????????????????? pm->deque[0];
    */
    PROCESS_QUEUE deletedData = pm->deque[pm->front];
    pm->front = (pm->front - 1 + MAX_PROCESS) % MAX_PROCESS;
    pm->size--;
    return deletedData;
}

PROCESS_QUEUE delete_rear(PROCESS_MANAGER *pm)
{
    /*
    if (isEmpty(pm))
        return; // ???????????????????????????????????????????
    */
    PROCESS_QUEUE deletedData = pm->deque[pm->rear];
    pm->rear = (pm->rear + 1) % MAX_PROCESS;
    pm->size--;
    return deletedData;
}