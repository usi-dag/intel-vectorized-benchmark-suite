//
// Created by mini on 28.07.22.
//

#ifndef INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H
#define INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H

#include <cstring>
#include <stdlib.h>

#include "../vector_species.h"

inline _MMR_i64 mask_add_epi64(_MMR_i64 src, _MMR_MASK_i64 k, _MMR_i64 a, _MMR_i64 b) {
    int * a_ = new int[SPECIES_64];
    int * b_ = new int[SPECIES_64];
    int * src_ = new int[SPECIES_64];
    bool * k_ = new bool[SPECIES_64];

    memcpy(a_, &a, SPECIES_64);
    memcpy(b_, &b, SPECIES_64);
    memcpy(src_, &src, SPECIES_64);
    memcpy(k_, &k, SPECIES_64);

    for (int i = 0; i < SPECIES_64; i++) {
        if (k_[i]) src_[i] = a_[i] + b_[i];
    }

    _MMR_i64 * dst = (_MMR_i64 *) malloc(SPECIES_64 * sizeof(_MMR_i64 *));
    memcpy(dst, src_, SPECIES_64);
    delete [] a_;
    delete [] b_;
    delete [] src_;
    delete [] k_;

    return *dst;
}

inline _MMR_i64 srav_epi64(_MMR_i64 a, _MMR_i64 count) {
    int * a_ = new int[SPECIES_64];
    int * count_ = new int[SPECIES_64];
    int * dst_ = new int[SPECIES_64];


    memcpy(a_, &a, SPECIES_64);
    memcpy(count_, &count, SPECIES_64);

    _MMR_i64 * dst = (_MMR_i64 *) malloc(SPECIES_64 * sizeof(_MMR_i64 *));


    for (int i = 0; i < SPECIES_64; i++) {
        if (SPECIES_64 - count_[i] <= i) {
            dst_[i] = a_[i - count_[i]];
        } else {
            dst_[i] = 0;
        }
    }

    memcpy(dst, dst_, SPECIES_64);
    delete [] a_;
    delete [] count_;
    delete [] dst_;

    return *dst;
}

inline int reduce_lane_add_epi32(_MMR_i32 a) {
    int * a_ = new int[SPECIES_32];

    memcpy(a_, &a, SPECIES_32);

    for (int i = 0; i < SPECIES_32; ++i) {
        result += a_[i];
    }

    delete [] a_;

    return result;
}

inline int mask_reduce_lane_add_epi32(_MMR_MASK_i32 k, _MMR_i32 a) {
    int result = 0;
    int * a_ = new int[SPECIES_32];
    bool * k_ = new bool[SPECIES_32];
    memcpy(a_, &a, SPECIES_32);
    memcpy(k_, &k, SPECIES_32);

    for (int i = 0; i < SPECIES_32; ++i) {
        if (k_[i] != 0) {
            result += a_[i];
        }
    }

    delete [] a_;
    delete [] k_;
    return result;
}

inline _MMR_i64 mask_blend_epi64 (_MMR_MASK_i64 k, _MMR_i64 a, _MMR_i64 b) {
    int * a_ = new int[SPECIES_64];
    int * b_ = new int[SPECIES_64];
    bool * k_ = new bool[SPECIES_64];
    memcpy(a_, &a, SPECIES_32);
    memcpy(b_, &a, SPECIES_32);
    memcpy(k_, &k, SPECIES_32);

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k_[i]) {
            a_[i] = b_[i];
        }
    }

    _MMR_i64 * dst = (_MMR_i64 *) malloc(SPECIES_64 * sizeof(_MMR_i64 *));
    memcpy(dst, a_, SPECIES_64);

    delete [] a_;
    delete [] b_;
    delete [] k_;

    return *dst;
}

inline _MMR_f32 mask_load_ps(_MMR_f32 src, _MMR_i32 k, void const * mem_addr) {
    int * src_ = new int[SPECIES_32];
    bool * k_ = new bool[SPECIES_32];
    int * dst_ = new int[SPECIES_32];
    memcpy(src_, &src, SPECIES_32);
    memcpy(k_, &k, SPECIES_32);

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k_[i]) {
            dst_[i] = *mem_addr[i];
        } else {
            dst_[i] = src_[i];
        }
    }


    _MMR_f32 * dst = (_MMR_f32 *) malloc(SPECIES_32 * sizeof(_MMR_f32 *));
    memcpy(dst, dst_, SPECIES_32);

    delete [] src_;
    delete [] k_;
    delete [] dst_;

    return * dst;
}


inline _MMR_f64 mask_sub_pd(_MMR_f64 src, _MMR_MASK_i64 k, _MMR_f64 a,_MMR_f64 b) {
    double * a_ = new double[SPECIES_64];
    double * b_ = new double[SPECIES_64];
    double * src_ = new double[SPECIES_64];
    bool * k_ = new bool[SPECIES_64];

    memcpy(a_, &a, SPECIES_64);
    memcpy(b_, &b, SPECIES_64);
    memcpy(src_, &src, SPECIES_64);
    memcpy(k_, &k, SPECIES_64);

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k_[i]) {
            a_[i] -= b_[i];
        } else {
            a_[i] = src_[i];
        }
    }

    _MMR_f64 * dst = (_MMR_f64 *) malloc(SPECIES_64 * sizeof(_MMR_f64 *));
    memcpy(dst, a_, SPECIES_64);

    delete [] a_;
    delete [] b_;
    delete [] src_;
    delete k_;

    return *dst;
}

inline _MMR_f32 mask_sub_ps(_MMR_f32 src, _MMR_MASK_i32 k, _MMR_f32 a,_MMR_f32 b) {
    double * a_ = new double[SPECIES_32];
    double * b_ = new double[SPECIES_32];
    double * src_ = new double[SPECIES_32];
    bool * k_ = new bool[SPECIES_32];

    memcpy(a_, &a, SPECIES_32);
    memcpy(b_, &b, SPECIES_32);
    memcpy(src_, &src, SPECIES_32);
    memcpy(k_, &k, SPECIES_32);

    for (int i = 0; i < SPECIES_32; ++i) {
        if (k_[i]) {
            a_[i] -= b_[i];
        } else {
            a_[i] = src_[i];
        }
    }

    _MMR_f32 * dst = (_MMR_f32 *) malloc(SPECIES_32 * sizeof(_MMR_f32 *));
    memcpy(dst, a_, SPECIES_32);

    delete [] a_;
    delete [] b_;
    delete [] src_;
    delete k_;

    return *dst;
}

inline _MMR_f64 mask_add_pd(_MMR_f64 src, _MMR_MASK_i64 k, _MMR_f64 a,_MMR_f64 b) {
    double * a_ = new double[SPECIES_64];
    double * b_ = new double[SPECIES_64];
    double * src_ = new double[SPECIES_64];
    bool * k_ = new bool[SPECIES_64];

    memcpy(a_, &a, SPECIES_64);
    memcpy(b_, &b, SPECIES_64);
    memcpy(src_, &src, SPECIES_64);
    memcpy(k_, &k, SPECIES_64);

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k_[i]) {
            a_[i] += b_[i];
        } else {
            a_[i] = src_[i];
        }
    }

    _MMR_f64 * dst = (_MMR_f64 *) malloc(SPECIES_64 * sizeof(_MMR_f64 *));
    memcpy(dst, a_, SPECIES_64);

    delete [] a_;
    delete [] b_;
    delete [] src_;
    delete k_;

    return *dst;
}



#endif //INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H
