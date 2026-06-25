#include "Scheduler.h"
using namespace std;

RoundRobinScheduler::RoundRobinScheduler(const vector<Task>& tasks, int timeQuantum) {
    quantum = timeQuantum;
    cpuCycles = 0;
    totalCyclesWithLatency = 0;
    completedTasks = 0;

    for (const Task& task : tasks) {
        readyQueue.push(task);
    }
}

// Runs all tasks using Round Robin scheduling.
void RoundRobinScheduler::run(CacheSimulator& cache) {
    cout << "CPUSim - CPU Scheduler & Cache Simulator" << endl;
    cout << "Scheduler: Round Robin" << endl;
    cout << "Quantum: " << quantum << endl;

    while (!readyQueue.empty()) {
        Task currentTask = readyQueue.front();
        readyQueue.pop();

        // If task has less remaining time than quantum, only run for remaining time.
        int timeSlice = min(quantum, currentTask.remainingTime);

        cout << endl;
        cout << "CPU allocated to " << currentTask.id << " for up to " << timeSlice << " cycle(s)." << endl;
        cout << "====" << endl;

        for (int i = 0; i < timeSlice; i++) {
            cpuCycles++;

            string requestedBlock = currentTask.getNextMemoryBlock();

            cout << endl;
            cout << "Cycle " << cpuCycles << " - Running: " << currentTask.id;
            cout << " | Requesting: " << requestedBlock << endl;
            cout << "----" << endl;

            int memoryLatency = cache.accessMemory(requestedBlock);
            totalCyclesWithLatency += memoryLatency;

            currentTask.remainingTime--;

            cout << "Memory latency added: " << memoryLatency << " cycles" << endl;
            cout << "Remaining burst time of " << currentTask.id << ": " << currentTask.remainingTime << endl;
            cout << "----" << endl;

            if (currentTask.isCompleted()) {
                break;
            }
        }

        if (currentTask.isCompleted()) {
            completedTasks++;
            cout << endl;
            cout << currentTask.id << " completed execution." << endl;
            cout << "===" << endl;
        } else {
            readyQueue.push(currentTask);
            cout << endl;
            cout << currentTask.id << " quantum expired. Moving back to ready queue." << endl;
            cout << "===" << endl;
        }
    }
}

void RoundRobinScheduler::printFinalResults(const CacheSimulator& cache) const {
    cout << endl;
    cout << "Final Results" << endl;
    cout << "Total CPU Cycles: " << cpuCycles << endl;
    cout << "Total Cycles including Memory Latency: " << totalCyclesWithLatency << endl;
    cout << "Tasks Completed: " << completedTasks << endl;
    cout << "Scheduler: Round Robin (quantum = " << quantum << ")" << endl;
    cout << "RAM Accesses: " << cache.ramAccesses << endl;

    cout << endl;
    cout << "Final Cache State:" << endl;
    cache.printAllCaches();

    cout << endl;
    cout << "Cache Statistics:" << endl;
    cache.printStatistics();
}
