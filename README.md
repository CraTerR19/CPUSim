# CPUSim - CPU Scheduling and Cache Simulator

This is my Task 2 submission. The idea is to show, step by step, how a CPU scheduler runs tasks and how memory blocks are searched through L1, L2, L3 cache and RAM.

I have used C++.

## What is implemented

- Input file parser for tasks
- Round Robin CPU scheduling (configurable quantum)
- L1, L2, L3 and RAM memory hierarchy
- Configurable L1 cache size via command line
- FIFO cache replacement with eviction cascade
- Cache hit / miss printing with promotion on hit
- RAM access count
- Final statistics after all tasks complete

## Why I used Round Robin

I used Round Robin because it is easy to visualize cycle by cycle. In FCFS, one large task may keep running for a long time, so the output becomes less interesting. In Round Robin, every task gets a small time slice and then goes back to the queue if it is not finished.

The default quantum is 3, but it can be changed using `--quantum`.

## Cache configuration

| Level | Default Capacity | Latency |
|---|---:|---:|
| L1 | 4 slots | 4 cycles |
| L2 | 128 slots | 12 cycles |
| L3 | 512 slots | 40 cycles |
| RAM | unlimited | 200 cycles |

L1 capacity is kept small (4 slots) so that eviction actually happens with the given input. This makes the multi-level cache hierarchy meaningful — blocks cascade from L1 to L2 to L3 as the cache fills up.

## Cache logic

This simulator uses a **fully-associative, exclusive** cache model with FIFO eviction:

For every memory request, the simulator checks:

1. L1
2. L2
3. L3
4. RAM

If the block is found in a lower level (L2 or L3), it is **promoted to L1** and removed from the lower level (exclusive caching). If L1 is full, the oldest block is evicted down to L2, and so on through the hierarchy.

I used FIFO because the task describes cache levels as fixed-size queues. So, if a cache becomes full, the oldest block is removed first.

## Files

```txt
main.cpp        - starts the simulator, handles CLI arguments
Task.h/.cpp     - stores task details (id, burst, memory blocks)
Parser.h/.cpp   - reads input_task2.txt
Cache.h/.cpp    - handles L1, L2, L3, RAM logic with FIFO eviction
Scheduler.h/.cpp- Round Robin scheduling logic
Makefile        - build instructions
input_task2.txt - given task input
```

## How to build and run

Using Make:
```bash
make
./cpusim.exe
```

Using g++ directly:
```bash
g++ -Wall -Wextra -std=c++17 main.cpp Task.cpp Parser.cpp Cache.cpp Scheduler.cpp -o cpusim.exe
./cpusim.exe
```
## Output shown

The program prints:

- Current cycle
- Running task
- Memory block requested
- L1 / L2 / L3 state
- Hit or miss result
- Cache promotions and evictions between levels
- Memory latency added
- Remaining burst time
- Final total cycles, RAM accesses, and cache hit rate

## Design decisions

- **Exclusive caching with promotion**: When a block is found in L2 or L3, it moves up to L1. This models how real CPUs try to keep hot data close to the core.
- **Eviction cascade via `bringToL1()`**: All eviction logic flows through one helper function that handles the L1 → L2 → L3 → discard chain. This avoids code duplication.
- **Configurable L1 size**: Lets you experiment with different cache sizes and see how hit rate changes. For example, with L1=4 you see lots of evictions, with L1=32 almost everything stays in L1.
- **`using namespace std` only in .cpp files**: Kept out of headers to avoid namespace pollution in larger projects.

## Complexity

- **Scheduling**: O(n × max_burst / quantum) where n is the number of tasks.
- **Cache lookup**: O(k) per access where k is the cache size (linear scan). In a real implementation, this could be improved to O(1) using a hash set alongside the deque for FIFO ordering.

## Current limitations

This version uses only one CPU core. Also, I have implemented only Round Robin scheduling in this submission. LRU and multi-core execution can be added later as extensions.

## Possible improvements

- Add FCFS and SJF with a common scheduler base class
- Add LRU replacement policy
- Add multi-core simulation
- Compare scheduler and cache configuration performance
- Use `unordered_set` alongside `deque` for O(1) cache lookup
