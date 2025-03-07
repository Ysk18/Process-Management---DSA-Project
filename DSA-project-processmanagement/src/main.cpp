#include <iostream>
#include "execution_functions.h"

using namespace std;

int main()
{
    PROCESS_MANAGER pm;
    initialize_process_manager(&pm);
    INSERTION_QUEUE eq;
    initialize_execution_queue(&eq);
    FAILURE_STACK fs;
    initialize_failed_stack(&fs);

    const char *initialFileName = "initial_processes.txt";
    const char *arrivingFileName = "arriving_processes.txt";

    cout << "Reading initial processes...\n";
    read_process_file(initialFileName, &pm);
    cout << "Reading arriving processes...\n";
    read_insertion_file(arrivingFileName, &eq);
    cout << "Starting execution loop...\n";
    execution_loop(&pm, &eq, &fs);
    cout << "Execution completed.\n";

    return 0;
}
