#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include "Task.h"
#include "Cache.h"

class RoundRobinScheduler {
private:
    std::queue<Task> readyQueue;
    int quantum;
    int cpuCycles;
    int totalCyclesWithLatency;
    int completedTasks;

public:
    RoundRobinScheduler(const std::vector<Task>& tasks, int timeQuantum);
    void run(CacheSimulator& cache);
    void printFinalResults(const CacheSimulator& cache) const;
};

#endif
