//
// Created by mini on 28.07.22.
//

#ifndef INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H
#define INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H

#include <cstring>
#include <stdlib.h>

#include "../vector_species.h"

inline _MMR_i64 mask_add_epi64(_MMR_i64 src, _MMR_MASK_i64 k, _MMR_i64 a, _MMR_i64 b) {

    for (int i = 0; i < SPECIES_64; i++) {
        if (k[i]) a[i] = a[i] + b[i];
        else a[i] = src[i];
    }

    return a;
}

inline _MMR_i64 srav_epi64(_MMR_i64 a, _MMR_i64 count) {

    int64_t dst_[SPECIES_64];

    for (int i = 0; i < SPECIES_64; i++) {
        if (SPECIES_64 - count[i] <= i) {
            dst_[i] = a[i - count[i]];
        } else {
            dst_[i] = 0;
        }
    }

    _MMR_i64 dst[SPECIES_64];
    memcpy(dst, dst_, sizeof(dst_));


    return *dst;
}

inline int reduce_lane_add_epi32(_MMR_i32 a) {


    int result = 0;
    for (int i = 0; i < SPECIES_32; ++i) {
        result += a[i];
    }

    return result;
}

inline int mask_reduce_lane_add_epi32(_MMR_MASK_i32 k, _MMR_i32 a) {

    int result = 0;

    for (int i = 0; i < SPECIES_32; ++i) {
        if (k[i]) {
            result += a[i];
        }
    }

    return result;
}

inline _MMR_i64 mask_blend_epi64 (_MMR_MASK_i64 k, _MMR_i64 a, _MMR_i64 b) {

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k[i]) {
            a[i] = b[i];
        }
    }

    return a;
}

inline _MMR_f32 mask_load_ps(_MMR_f32 src, _MMR_i32 k, float const * mem_addr) {

    int32_t dst_[SPECIES_32];


    for (int i = 0; i < SPECIES_32; ++i) {
        if (k[i]) {
            dst_[i] = mem_addr[i];
        } else {
            dst_[i] = src[i];
        }
    }

    _MMR_f32 dst[SPECIES_32];
    memcpy(dst, dst_, sizeof(dst_));


    return *dst;
}


inline _MMR_f64 mask_sub_pd(_MMR_f64 src, _MMR_MASK_i64 k, _MMR_f64 a,_MMR_f64 b) {


    for (int i = 0; i < SPECIES_64; ++i) {
        if (k[i]) {
            a[i] -= b[i];
        } else {
            a[i] = src[i];
        }
    }

    return a;
}

inline _MMR_f32 mask_sub_ps(_MMR_f32 src, _MMR_MASK_i32 k, _MMR_f32 a,_MMR_f32 b) {

    for (int i = 0; i < SPECIES_32; ++i) {
        if (k[i]) {
            a[i] -= b[i];
        } else {
            a[i] = src[i];
        }
    }

    return a;
}

inline _MMR_f64 mask_add_pd(_MMR_f64 src, _MMR_MASK_i64 k, _MMR_f64 a,_MMR_f64 b) {

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k[i]) {
            a[i] += b[i];
        } else {
            a[i] = src[i];
        }
    }

    return a;
}

inline _MMR_f64 mask_blend_pd(_MMR_MASK_i64 k, _MMR_f64 a, _MMR_f64 b) {

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k[i]) {
            a[i] = b[i];
        }
    }

    return a;
}

inline _MMR_f32 mask_blend_ps(_MMR_MASK_i32 k, _MMR_f32 a, _MMR_f32 b) {

    for (int i = 0; i < SPECIES_32; ++i) {
        if (k[i]) {
            a[i] = b[i];
        }
    }

    return a;
}


// TODO vectorize https://stackoverflow.com/questions/49941645/get-sum-of-values-stored-in-m256d-with-sse-avx
inline double reduce_pd(_MMR_f64 a) {
    int result = 0;

    for (int i = 0; i < SPECIES_64; ++i) {
        result += a[i];
    }

    return result;
}

inline float reduce_ps(_MMR_f32 a) {
    float result = 0;

    for (int i = 0; i < SPECIES_32; ++i) {
        result += a[i];
    }
    return result;
}

inline int first_true_int64(_MMR_MASK_i64 k) {

    for (int i = 0; i < SPECIES_64; i++) {
        if (k[i]) {
            return i;
        }
    }

    return -1;
}

inline int true_count_int64(_MMR_MASK_i64 k) {
    int res = 0;

    for (int i = 0; i < SPECIES_64; i++) {
        if (k[i]) res++;
    }

    return res;
}

inline _MMR_MASK_i64 kor(_MMR_MASK_i64 a, _MMR_MASK_i64 b) {

    for (int i = 0; i < SPECIES_64; ++i) {
        a[i] = a[i] || b[i];
    }


    return a;
}

inline _MMR_MASK_i64 kxor(_MMR_MASK_i64 a, _MMR_MASK_i64 b) {

    for (int i = 0; i < SPECIES_64; ++i) {
        a[i] = a[i] ^ b[i];
    }

    return a;
}

inline _MMR_MASK_i64 knot(_MMR_MASK_i64 a) {

    for (int i = 0; i < SPECIES_64; ++i) {
        a[i] = !a[i];
    }

    return a;
}

inline _MMR_MASK_i64 lt_epi64_mask(_MMR_i64 a, _MMR_i64 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_64, 0);

    for (int i = 0; i < SPECIES_64; ++i) {
        k[i] = a[i] < b[i];
    }

    return k;
}

inline _MMR_MASK_i64 eq_epi64_mask(_MMR_i64 a, _MMR_i64 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_64, 0);


    for (int i = 0; i < SPECIES_64; ++i) {
        k[i] = a[i] == b[i];
    }

    return k;
}

inline _MMR_MASK_i32 eq_epi32_mask(_MMR_i32 a, _MMR_i32 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_32, 0);


    for (int i = 0; i < SPECIES_32; ++i) {
        k[i] = a[i] == b[i];
    }

    return k;
}


inline _MMR_MASK_i64 eq_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_64, 0);

    for (int i = 0; i < SPECIES_64; ++i) {
        k[i] = a[i] == b[i];
    }

    return k;
}


inline _MMR_MASK_i32 eq_ps_mask(_MMR_f32 a, _MMR_f32 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_32, 0);


    for (int i = 0; i < SPECIES_32; ++i) {
        k[i] = a[i] == b[i];
    }

    return k;
}


inline _MMR_MASK_i64 gt_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_64, 0);


    for (int i = 0; i < SPECIES_64; ++i) {
        k[i] = a[i] > b[i];
    }


    return k;
}

inline _MMR_MASK_i64 ge_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_64, 0);


    for (int i = 0; i < SPECIES_64; ++i) {
        k[i] = a[i] >= b[i];
    }

    return k;
}

inline _MMR_MASK_i64 lt_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_64, 0);

    for (int i = 0; i < SPECIES_64; ++i) {
        k[i] = a[i] < b[i];
    }

    return k;
}


inline _MMR_MASK_i32 lt_ps_mask(_MMR_f32 a, _MMR_f32 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_32, 0);

    for (int i = 0; i < SPECIES_32; ++i) {
        k[i] = a[i] < b[i];
    }

    return k;
}


inline _MMR_MASK_i64 le_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    _MMR_MASK_i32 k = std::vector<bool>(SPECIES_64, 0);


    for (int i = 0; i < SPECIES_64; ++i) {
        k[i] = a[i] <= b[i];
    }

    return k;
}
#endif //INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H
