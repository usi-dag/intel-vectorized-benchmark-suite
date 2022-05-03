//
// Created by mini on 02.05.22.
// FROM THE WORK OF
/*************************************************************************
* Axpy Kernel
* Author: Jesus Labarta
* Barcelona Supercomputing Center
*************************************************************************/


#include <iostream>

//#ifdef __cplusplus
//extern "C"
//{
//#endif

// C header here
#include "axpy.h"

//#ifdef __cplusplus
//}
//#endif




#include <benchmark/benchmark.h>
static void BM_serial(benchmark::State& state) {
    double a=1.0;
    long n;
    n = 1024*10; // TODO how to pass value  n = 1024*atol(argv[1]);

    double *dx     = (double*)malloc(n*sizeof(double));
    double *dy     = (double*)malloc(n*sizeof(double));

    init_vector(dx, n, 1.0);

    init_vector(dy, n, 2.0);



    for (auto _ : state)
        axpy_ref(a, dx, dy, n);
}
// Register the function as a benchmark
BENCHMARK(BM_serial);

// Define another benchmark
//static void BM_fullVec(benchmark::State& state) {
//    double a=1.0;
//    long n;
//    n = 1024*10; // TODO how to pass value  n = 1024*atol(argv[1]);
//
//    double *dx     = (double*)malloc(n*sizeof(double));
//    double *dy     = (double*)malloc(n*sizeof(double));
//
//    init_vector(dx, n, 1.0);
//    init_vector(dy, n, 2.0);
//    for (auto _ : state)
//        axpy_intrinsics(a, dx, dy, n);
//}
//BENCHMARK(BM_fullVec);

BENCHMARK_MAIN();