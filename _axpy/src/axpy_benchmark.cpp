/*************************************************************************
* Axpy Kernel
* Author: Jesus Labarta
* Barcelona Supercomputing Center
*************************************************************************/


#include <iostream>
#include <memory>
#include <benchmark/benchmark.h>

//#ifdef __cplusplus
//extern "C"
//{
//#endif

// C header here
#include "axpy.h"
#include "../../common/vector_defines.h"
#include "../../common/memory_manager.h"

//#ifdef __cplusplus
//}
//#endif

double a=1.0;
long n = 1024*319999; // TODO how to pass value  n = 1024*atol(argv[1]);

double *dx     = (double*)malloc(n*sizeof(double));
double *dy     = (double*)malloc(n*sizeof(double));

static void DoSetup(const benchmark::State& state) {
    init_vector(dx, n, 1.0);
    init_vector(dy, n, 2.0);
}

//static void DoTeardown(const benchmark::State& state) {
//}



static void BM_serial(benchmark::State& state) {
    for (auto _ : state)
        axpy_ref(a, dx, dy, n);
}
// Register the function as a benchmark

BENCHMARK(BM_serial)->Setup(DoSetup)->Unit(benchmark::kMillisecond)->MinWarmUpTime(20)->Iterations(10);// ->ComputeStatistics(); //->RegisterMemoryManager(benchmark::MemoryManager);

// Define another benchmark
static void BM_vector(benchmark::State& state) {

    for (auto _ : state)
        axpy_intrinsics(a, dx, dy, n);
}
BENCHMARK(BM_vector)->Setup(DoSetup)->Unit(benchmark::kMillisecond)->MinWarmUpTime(20)->Iterations(10);



//static void BM_memory(benchmark::State& state) {
//    for (auto _ : state)
//        for (int i =0; i < 10; i++) {
//            benchmark::DoNotOptimize((int *) malloc(10 * sizeof(int *)));
//        }
//}
//
//BENCHMARK(BM_memory)->Unit(benchmark::kMillisecond)->Iterations(18);

//BENCHMARK_MAIN();
int main(int argc, char** argv)
{
    ::benchmark::RegisterMemoryManager(mm.get());
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::RegisterMemoryManager(nullptr);
}