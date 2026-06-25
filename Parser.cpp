#include "Parser.h"
using namespace std;

// Reads lines like: TASK T1 BURST 5 MEM M1 M4 M7
vector<Task> Parser::readTasksFromFile(const string& filename) {
    vector<Task> tasks;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open input file: " << filename << endl;
        return tasks;
    }

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string taskKeyword;
        string taskId;
        string burstKeyword;
        int burst;
        string memKeyword;
        vector<string> memoryBlocks;

        ss >> taskKeyword;
        ss >> taskId;
        ss >> burstKeyword;
        ss >> burst;
        ss >> memKeyword;

        string memoryBlock;
        while (ss >> memoryBlock) {
            memoryBlocks.push_back(memoryBlock);
        }

        if (taskKeyword == "TASK" && burstKeyword == "BURST" && memKeyword == "MEM") {
            tasks.push_back(Task(taskId, burst, memoryBlocks));
        } else {
            cout << "Invalid line skipped: " << line << endl;
        }
    }

    file.close();
    return tasks;
}

void Parser::printLoadedTasks(const vector<Task>& tasks) {
    cout << "Loaded Tasks:" << endl;
    cout << "----------------------------------------" << endl;

    for (const Task& task : tasks) {
        cout << "Task ID: " << task.id << endl;
        cout << "Burst Time: " << task.burstTime << endl;
        cout << "Memory Blocks: ";

        for (const string& block : task.memoryBlocks) {
            cout << block << " ";
        }

        cout << endl;
        cout << "----------------------------------------" << endl;
    }
}
