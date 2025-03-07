#include "failure_stack.h"

// failure stack -- done
void initialize_failed_stack(FAILURE_STACK *fs)
{
    // fs->stack => is array so do not need malloc
    fs->top = -1;
}

bool isFull(FAILURE_STACK *fs)
{
    return fs->top + 1 == MAX_FAILED;
}

bool isEmpty(FAILURE_STACK *fs)
{
    return fs->top == -1;
}

void push(FAILURE_STACK *fs, PROCESS_QUEUE data)
{
    if (isFull(fs))
        return;
    fs->top++; // no need for mode
    fs->stack[fs->top] = data;
}

PROCESS_QUEUE pop(FAILURE_STACK *fs)
{
    /*
    if (isEmpty(fs))
        return; // ??????????????????????????????????????????????????  fs->stack[0];
    */
    PROCESS_QUEUE deletedData = fs->stack[fs->top];
    fs->top--;
    return deletedData;
}