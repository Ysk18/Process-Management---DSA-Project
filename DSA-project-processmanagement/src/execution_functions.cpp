#include "execution_functions.h"
#include <iostream>

using namespace std;

// execution functions -- ??
void read_process_file(const char *filename, PROCESS_MANAGER *pm)
{
    // cout << "hello\n";
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        cout << "\nFile not found or there is a error while opening the file: " << filename << ".\n";
        return;
    }
    // Skip the first line
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), fptr) == NULL)
    {
        cout << "\nFile is empty or couldn't read the header: " << filename << ".\n";
        fclose(fptr);
        return;
    }

    int pid = 0;
    int priority = 0;
    int isHead = 0;

    PROCESS_QUEUE pq;
    initialize_process_queue(&pq);
    while (fscanf(fptr, "%d ,%d ,%d", &pid, &priority, &isHead) == 3)
    {
        PROCESS p;
        initialize_process(&p, pid, priority);

        if (isHead == 1) // last element of queue
        {
            if (!isFull(&pq))
            {
                PROCESS p_tmp = p;
                enqueue(&pq, p_tmp);
            }
            pq.priority = priority;
            // add pq to process manager, then set empty
            PROCESS_QUEUE pq_tmp = pq;
            if (priority == 1)
                insert_front(pm, pq_tmp);
            else if (priority == 0)
                insert_rear(pm, pq_tmp);
            else
                cout << "invalid priority\n";
            initialize_process_queue(&pq);
        }
        else if (isHead == 0) // not he last element of the queue
        {
            PROCESS p_tmp = p;
            enqueue(&pq, p_tmp);
        }
        if (isFull(pm))
            break;
    }

    fclose(fptr);
    fptr = NULL;
} // we assume that in queue every process element have same priority

void read_insertion_file(const char *filename, INSERTION_QUEUE *eq)
{
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        cout << "\nFile not found or there is a error while opening the file: " << filename << ".\n";
        return;
    }

    // Skip the first line
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), fptr) == NULL)
    {
        cout << "\nFile is empty or couldn't read the header: " << filename << ".\n";
        fclose(fptr);
        return;
    }

    int iteration = 0;
    int pid = 0;
    int priority = 0;
    int isHead = 0;

    PROCESS_QUEUE pq;
    initialize_process_queue(&pq);
    while (fscanf(fptr, "%d, %d, %d, %d", &iteration, &pid, &priority, &isHead) == 4)
    {
        PROCESS p;
        initialize_process(&p, pid, priority);

        if (isHead == 1) // last element of queue
        {
            if (!isFull(&pq))
            {
                PROCESS p_tmp = p;
                enqueue(&pq, p_tmp);
            }
            pq.priority = priority;
            PROCESS_QUEUE pq_tmp = pq;
            // enqueue(&pq_tmp, p);
            pq_tmp.iteration = iteration;

            enqueue(eq, pq_tmp);
            initialize_process_queue(&pq);
        }
        else if (isHead == 0) // not he last element of the queue
        {
            PROCESS p_tmp = p;
            enqueue(&pq, p_tmp);
        }
        if (isFull(eq))
            break;
    }

    fclose(fptr);
    fptr = NULL;
}

void execution_loop(PROCESS_MANAGER *pm, INSERTION_QUEUE *eq, FAILURE_STACK *fs)
{ // I ll add capacity control
    // eq iteration pm bittikten sonra geliyorsa mesela iteration 100 verse
    FILE *fptr = fopen("execution_run.txt", "w");
    int id_of_process = 0;
    char success_of_process = 'f';

    int iteration = 0;
    PROCESS_QUEUE pq;
    PROCESS p;
    PROCESS_QUEUE pq_eq;
    initialize_process_queue(&pq);
    initialize_process_queue(&pq_eq);
    initialize_process(&p, 1, 0);

    while (!isEmpty(pm) || !isEmpty(eq))
    {
        if (isEmpty(&(pm->deque[pm->front])))
            dequeue(&(pm->deque[pm->front]));
        pq = delete_front(pm);

        if (!isEmpty(eq) && isEmpty(&pq_eq))
            pq_eq = dequeue(eq);
        if (!isEmpty(&pq_eq))
        {
            if (iteration == pq_eq.iteration)
            {
                PROCESS_QUEUE pq_eq_tmp = pq_eq;
                if (pq_eq_tmp.priority == 1) // add front of the pm
                {
                    insert_front(pm, pq_eq_tmp);
                    initialize_process_queue(&pq_eq);
                }
                else if (pq_eq_tmp.priority == 0) // add back of the pm
                {
                    insert_rear(pm, pq_eq_tmp);
                    initialize_process_queue(&pq_eq);
                }
                else
                {
                    cout << "Invalid Priority!\n";
                }
            }
        }

        while (!isEmpty(&pq))
        {
            // cout << "Iteration " << iteration << ": "; // for debugging (checking)
            if (!isEmpty(eq) && isEmpty(&pq_eq))
                pq_eq = dequeue(eq);
            if (!isEmpty(&pq_eq))
            {
                if (iteration == pq_eq.iteration)
                {
                    PROCESS_QUEUE pq_eq_tmp = pq_eq;
                    if (pq_eq_tmp.priority == 1) // add front of the pm
                    {
                        insert_front(pm, pq_eq_tmp);
                        initialize_process_queue(&pq_eq);
                    }
                    else if (pq_eq_tmp.priority == 0) // add back of the pm
                    {
                        insert_rear(pm, pq_eq_tmp);
                        initialize_process_queue(&pq_eq);
                    }
                    else
                    {
                        cout << "Invalid Priority!\n";
                    }
                }
            }
            p = peek(&pq); // p = pq.queue[pq.rear];
            // cout << p.pid << "\n"; // for debugging (checking)
            id_of_process = p.pid;

            if (p.pid % 8 == 0) // add to failure stack and continue
            {
                // cout << p.pid << "Failed -> sent to failure stack\n"; // for debugging (checking)
                success_of_process = 'f';

                PROCESS_QUEUE pq_tmp = pq;
                if (!isFull(fs))
                    push(fs, pq_tmp);
                iteration++;

                fprintf(fptr, "%d ,%c\n", id_of_process, success_of_process);
                // cout << id_of_process << ", " << success_of_process << "\n";
                break;
            }
            else // process
            {
                success_of_process = 's';
                dequeue(&pq);
                // cout << "Process part\n";
            }
            fprintf(fptr, "%d ,%c\n", id_of_process, success_of_process);
            // cout << id_of_process << ", " << success_of_process << "\n";
            iteration++;
        }

        // make pq empty- make p empty
        initialize_process_queue(&pq);
        initialize_process(&p, p.pid, p.priority);
    }
    fclose(fptr);
}