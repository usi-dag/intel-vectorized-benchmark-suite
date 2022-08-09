#include <iostream>
#include <memory>
#include <benchmark/benchmark.h>
#include "../../common/memory_manager.h"
//#ifdef __cplusplus
//extern "C"
//{
//#endif

// C header here
#include "axpy.h"
#include "../../common/vector_defines.h"


//#ifdef __cplusplus
//}
//#endif

double a=1.0;
long n = 1024*70000; // TODO how to pass value  n = 1024*atol(argv[1]);

double *dx     = (double*)malloc(n*sizeof(double));
double *dy     = (double*)malloc(n*sizeof(double));

static void DoSetup(const benchmark::State& state) {
    init_vector(dx, n, 1.0);
    init_vector(dy, n, 2.0);
}

//static void DoTeardown(const benchmark::State& state) {
//}



static void BM_axpy(benchmark::State& state) {
    for (auto _ : state)
#ifdef USE_VECTOR_INTRINSIC
        axpy_intrinsics(a, dx, dy, n);
#else
        axpy_ref(a, dx, dy, n);
#endif
}


BENCHMARK(BM_axpy)->Setup(DoSetup)->Unit(benchmark::kMillisecond)->MinWarmUpTime(20)->Iterations(10);


//BENCHMARK_MAIN();
int main(int argc, char** argv)
{
    ::benchmark::RegisterMemoryManager(mm.get());
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::RegisterMemoryManager(nullptr);
}