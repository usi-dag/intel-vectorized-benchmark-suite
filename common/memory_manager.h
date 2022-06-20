//
// Created by mini on 03.06.22.
//

#ifndef INTEL_VECTORIZED_BENCHMARK_SUITE_MEMORY_MANAGER_H
#define INTEL_VECTORIZED_BENCHMARK_SUITE_MEMORY_MANAGER_H

#include <memory>
#include <benchmark/benchmark.h>

class CustomMemoryManager: public benchmark::MemoryManager {
public:

    int64_t num_allocs;
    int64_t max_bytes_used;


    void Start() BENCHMARK_OVERRIDE {
        num_allocs = 0;
        max_bytes_used = 0;
    }

    void Stop(Result* result) BENCHMARK_OVERRIDE {
        result->num_allocs = num_allocs;
        result->max_bytes_used = max_bytes_used;
    }
};

std::unique_ptr<CustomMemoryManager> mm(new CustomMemoryManager());

#ifdef MEMORY_PROFILER
void *custom_malloc(size_t size) {
    void *p = malloc(size);
//    std::cout << "Size: " << size << std::endl;
    mm.get()->num_allocs += 1;
    mm.get()->max_bytes_used += size;
    return p;
}
#define malloc(size) custom_malloc(size)
#endif

#endif //INTEL_VECTORIZED_BENCHMARK_SUITE_MEMORY_MANAGER_H
