#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

class CacheSimulator {
private:
    std::deque<std::string> l1;
    std::deque<std::string> l2;
    std::deque<std::string> l3;

    int l1Capacity;
    int l2Capacity;
    int l3Capacity;

    const int L1_LATENCY = 4;
    const int L2_LATENCY = 12;
    const int L3_LATENCY = 40;
    const int RAM_LATENCY = 200;

    int l1Hits;
    int l2Hits;
    int l3Hits;
    int totalMemoryRequests;

    bool contains(const std::deque<std::string>& cache, const std::string& block) const;
    void removeBlock(std::deque<std::string>& cache, const std::string& block);
    std::string insertFIFO(std::deque<std::string>& cache, int capacity, const std::string& block);
    void printCacheLevel(const std::string& levelName, const std::deque<std::string>& cache) const;

    // Inserts block into L1 and cascades any evictions down through L2 and L3.
    void bringToL1(const std::string& block);

public:
    int ramAccesses;

    CacheSimulator(int l1Cap = 4, int l2Cap = 128, int l3Cap = 512);
    int accessMemory(const std::string& block);
    void printAllCaches() const;
    void printStatistics() const;
};

#endif
