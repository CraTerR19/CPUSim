#include "Task.h"
using namespace std;

Task::Task() {
    id = "";
    burstTime = 0;
    remainingTime = 0;
    memoryIndex = 0;
}

Task::Task(const string& taskId, int burst, const vector<string>& memoryList) {
    id = taskId;
    burstTime = burst;
    remainingTime = burst;
    memoryBlocks = memoryList;
    memoryIndex = 0;
}

string Task::getNextMemoryBlock() {
    if (memoryBlocks.empty()) {
        // No memory blocks assigned, return a default placeholder.
        return "M0";
    }

    string block = memoryBlocks[memoryIndex];
    memoryIndex++;

    // Wrap around so memory blocks repeat cyclically.
    if (memoryIndex >= (int)memoryBlocks.size()) {
        memoryIndex = 0;
    }

    return block;
}

bool Task::isCompleted() const {
    return remainingTime <= 0;
}
