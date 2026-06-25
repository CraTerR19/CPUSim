#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Task.h"

class Parser {
public:
    static std::vector<Task> readTasksFromFile(const std::string& filename);
    static void printLoadedTasks(const std::vector<Task>& tasks);
};

#endif
