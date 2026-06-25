#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

class Task {
public:
    std::string id;
    int burstTime;
    int remainingTime;
    std::vector<std::string> memoryBlocks;
    int memoryIndex;

    Task();
    Task(const std::string& taskId, int burst, const std::vector<std::string>& memoryList);
    std::string getNextMemoryBlock();
    bool isCompleted() const;
};

#endif
