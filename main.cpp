#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include "Task.h"
#include "Parser.h"
#include "Cache.h"
#include "Scheduler.h"
using namespace std;

int main(int argc, char* argv[]) {
    // Default values, can be overridden with command line arguments.
    string filename = "input_task2.txt";
    int quantum = 3;
    int l1Size = 4;

    // Simple argument parsing: --quantum N, --l1 N, --input FILE
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--quantum") == 0 && i + 1 < argc) {
            quantum = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--l1") == 0 && i + 1 < argc) {
            l1Size = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--input") == 0 && i + 1 < argc) {
            filename = argv[++i];
        }
    }

    if (quantum <= 0) {
        cout << "Error: Quantum must be a positive integer." << endl;
        return 1;
    }

    if (l1Size <= 0) {
        cout << "Error: L1 cache size must be a positive integer." << endl;
        return 1;
    }

    vector<Task> tasks = Parser::readTasksFromFile(filename);

    if (tasks.empty()) {
        cout << "No tasks loaded. Please check your input file." << endl;
        return 0;
    }

    // Printing once at start helps to confirm that the input file was parsed correctly.
    Parser::printLoadedTasks(tasks);

    CacheSimulator cache(l1Size);
    RoundRobinScheduler scheduler(tasks, quantum);

    scheduler.run(cache);
    scheduler.printFinalResults(cache);

    return 0;
}
