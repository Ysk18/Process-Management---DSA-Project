#include "type_process.h"

// type process -- done
void initialize_process(PROCESS *p, int pid, int priority)
{
    p->pid = pid;
    p->priority = priority;
}