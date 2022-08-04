//
// Created by mini on 04.08.22.
//

#ifndef INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_TEST_H
#define INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_TEST_H

#include "immintrin.h"
#include <cstring>
#include <iostream>
#define SPECIES_32 8
#define _MMR_i32 __m256i

inline int reduce_lane_add_epi32(_MMR_i32 a) {
    int a_[SPECIES_32];
    memcpy(a_, &a, sizeof(a_));


    int result = 0;
    for (int i = 0; i < SPECIES_32; ++i) {
        result += a_[i];
        std::cout << "a[" << i << "] = " << a_[i] << std::endl;
    }


    return result;
}


class serial_test {

};


#endif //INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_TEST_H
