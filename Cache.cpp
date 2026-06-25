#include "Cache.h"
using namespace std;

CacheSimulator::CacheSimulator(int l1Cap, int l2Cap, int l3Cap) {
    l1Capacity = l1Cap;
    l2Capacity = l2Cap;
    l3Capacity = l3Cap;
    ramAccesses = 0;
    l1Hits = 0;
    l2Hits = 0;
    l3Hits = 0;
    totalMemoryRequests = 0;
}

bool CacheSimulator::contains(const deque<string>& cache, const string& block) const {
    return find(cache.begin(), cache.end(), block) != cache.end();
}

void CacheSimulator::removeBlock(deque<string>& cache, const string& block) {
    auto it = find(cache.begin(), cache.end(), block);
    if (it != cache.end()) {
        cache.erase(it);
    }
}

// Inserts a block using FIFO policy. If something is removed, it is returned.
string CacheSimulator::insertFIFO(deque<string>& cache, int capacity, const string& block) {
    if (contains(cache, block)) {
        return "";
    }

    string evicted = "";

    if ((int)cache.size() >= capacity) {
        evicted = cache.front();
        cache.pop_front();
    }

    cache.push_back(block);
    return evicted;
}

void CacheSimulator::printCacheLevel(const string& levelName, const deque<string>& cache) const {
    cout << levelName << ": [";

    for (int i = 0; i < (int)cache.size(); i++) {
        cout << cache[i];
        if (i != (int)cache.size() - 1) {
            cout << ", ";
        }
    }

    cout << "]";
}

// Handles the eviction cascade: inserts block into L1, pushes evicted blocks
// down through L2 and L3. If L3 is also full, the oldest block is discarded.
void CacheSimulator::bringToL1(const string& block) {
    string evictedFromL1 = insertFIFO(l1, l1Capacity, block);

    if (evictedFromL1 != "") {
        cout << evictedFromL1 << " evicted from L1 and moved to L2" << endl;
        string evictedFromL2 = insertFIFO(l2, l2Capacity, evictedFromL1);

        if (evictedFromL2 != "") {
            cout << evictedFromL2 << " evicted from L2 and moved to L3" << endl;
            string evictedFromL3 = insertFIFO(l3, l3Capacity, evictedFromL2);

            if (evictedFromL3 != "") {
                cout << evictedFromL3 << " evicted from L3 (discarded)" << endl;
            }
        }
    }
}

// One memory request comes here. It checks L1, then L2, then L3, then RAM.
int CacheSimulator::accessMemory(const string& block) {
    totalMemoryRequests++;

    cout << "Before Access Cache State:" << endl;
    printAllCaches();

    cout << "Checking L1: ";
    printCacheLevel("L1", l1);

    if (contains(l1, block)) {
        l1Hits++;
        cout << " -> HIT (" << L1_LATENCY << " cycles)" << endl;
        cout << "After Access Cache State:" << endl;
        printAllCaches();
        return L1_LATENCY;
    }

    cout << " -> MISS" << endl;

    cout << "Checking L2: ";
    printCacheLevel("L2", l2);

    if (contains(l2, block)) {
        l2Hits++;
        cout << " -> HIT (" << L2_LATENCY << " cycles)" << endl;

        removeBlock(l2, block);
        cout << "Promoting " << block << " -> L1" << endl;
        bringToL1(block);

        cout << "After Access Cache State:" << endl;
        printAllCaches();
        return L2_LATENCY;
    }

    cout << " -> MISS" << endl;

    cout << "Checking L3: ";
    printCacheLevel("L3", l3);

    if (contains(l3, block)) {
        l3Hits++;
        cout << " -> HIT (" << L3_LATENCY << " cycles)" << endl;

        removeBlock(l3, block);
        cout << "Promoting " << block << " -> L1" << endl;
        bringToL1(block);

        cout << "After Access Cache State:" << endl;
        printAllCaches();
        return L3_LATENCY;
    }

    cout << " -> MISS" << endl;

    cout << "Block " << block << " not found in cache hierarchy." << endl;
    cout << "Fetching " << block << " from RAM (" << RAM_LATENCY << " cycles)" << endl;

    ramAccesses++;
    bringToL1(block);

    cout << "After Access Cache State:" << endl;
    printAllCaches();

    return RAM_LATENCY;
}

void CacheSimulator::printAllCaches() const {
    printCacheLevel("L1", l1);
    cout << endl;

    printCacheLevel("L2", l2);
    cout << endl;

    printCacheLevel("L3", l3);
    cout << endl;
}

void CacheSimulator::printStatistics() const {
    cout << "L1 Hits: " << l1Hits << endl;
    cout << "L2 Hits: " << l2Hits << endl;
    cout << "L3 Hits: " << l3Hits << endl;
    cout << "RAM Accesses: " << ramAccesses << endl;
    cout << "Total Memory Requests: " << totalMemoryRequests << endl;

    int totalHits = l1Hits + l2Hits + l3Hits;

    if (totalMemoryRequests > 0) {
        double hitRate = (double)totalHits / totalMemoryRequests * 100.0;
        cout << "Cache Hit Rate: " << hitRate << "%" << endl;
    } else {
        cout << "Cache Hit Rate: 0%" << endl;
    }
}
