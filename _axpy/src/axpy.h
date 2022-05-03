//
// Created by mini on 02.05.22.
//

#ifndef INTEL_VECTORIZED_BENCHMARK_SUITE_AXPY_H
#define INTEL_VECTORIZED_BENCHMARK_SUITE_AXPY_H

void axpy_intrinsics(double a, double *dx, double *dy, int n);

void axpy_ref(double a, double *dx, double *dy, int n);

void init_vector(double *pv, long n, double value);

#endif //INTEL_VECTORIZED_BENCHMARK_SUITE_AXPY_H
