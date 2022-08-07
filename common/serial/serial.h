//
// Created by mini on 28.07.22.
//

#ifndef INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H
#define INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H

#include <cstring>
#include <stdlib.h>

#include "../vector_species.h"

inline _MMR_i64 mask_add_epi64(_MMR_i64 src, _MMR_MASK_i64 k, _MMR_i64 a, _MMR_i64 b) {
    int a_[SPECIES_64];
    int b_[SPECIES_64];
    int src_[SPECIES_64];
    bool k_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    memcpy(k_, &k, sizeof(k));
    memcpy(src_, &src, sizeof(src));

    for (int i = 0; i < SPECIES_64; i++) {
        if (k_[i]) src_[i] = a_[i] + b_[i];
    }

    _MMR_i64 dst[SPECIES_64];
    memcpy(dst, src_, sizeof(src_));

    return *dst;
}

inline _MMR_i64 srav_epi64(_MMR_i64 a, _MMR_i64 count) {
    int a_[SPECIES_64];
    int count_[SPECIES_64];
    int dst_[SPECIES_64];


    memcpy(a_, &a, sizeof(a));
    memcpy(count_, &count, sizeof(count));

    _MMR_i64 dst[SPECIES_64];


    for (int i = 0; i < SPECIES_64; i++) {
        if (SPECIES_64 - count_[i] <= i) {
            dst_[i] = a_[i - count_[i]];
        } else {
            dst_[i] = 0;
        }
    }

    memcpy(dst, dst_, sizeof(dst_));

    return *dst;
}

inline int reduce_lane_add_epi32(_MMR_i32 a) {
    int a_[SPECIES_32];

    memcpy(a_, &a, sizeof(a));

    int result = 0;
    for (int i = 0; i < SPECIES_32; ++i) {
        result += a_[i];
    }

    return result;
}

inline int mask_reduce_lane_add_epi32(_MMR_MASK_i32 k, _MMR_i32 a) {
    int result = 0;
    int a_[SPECIES_32];
    bool k_[SPECIES_32];
    memcpy(a_, &a, sizeof(a));
    memcpy(k_, &k, sizeof(k));

    for (int i = 0; i < SPECIES_32; ++i) {
        if (k_[i] != 0) {
            result += a_[i];
        }
    }

    return result;
}

inline _MMR_i64 mask_blend_epi64 (_MMR_MASK_i64 k, _MMR_i64 a, _MMR_i64 b) {
    int  a_[SPECIES_64];
    int  b_[SPECIES_64];
    bool k_[SPECIES_64];
    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    memcpy(k_, &k, sizeof(k));

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k_[i]) {
            a_[i] = b_[i];
        }
    }

    _MMR_i64 dst[SPECIES_64];
    memcpy(dst, a_, sizeof(a_));

    return *dst;
}

inline _MMR_f32 mask_load_ps(_MMR_f32 src, _MMR_i32 k, float const * mem_addr) {
    float  src_[SPECIES_32];
    bool k_[SPECIES_32];
    float  dst_[SPECIES_32];

    memcpy(src_, &src, sizeof(src));
    memcpy(k_, &k, sizeof(k));

    for (int i = 0; i < SPECIES_32; ++i) {
        if (k_[i]) {
            dst_[i] = mem_addr[i];
        } else {
            dst_[i] = src_[i];
        }
    }


    _MMR_f32 dst[SPECIES_32];
    memcpy(dst, dst_, sizeof(dst_));

    return *dst;
}


inline _MMR_f64 mask_sub_pd(_MMR_f64 src, _MMR_MASK_i64 k, _MMR_f64 a,_MMR_f64 b) {
    double a_[SPECIES_64];
    double b_[SPECIES_64];
    double src_[SPECIES_64];
    bool k_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    memcpy(k_, &k, sizeof(k));
    memcpy(src_, &src, sizeof(src));

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k_[i]) {
            a_[i] -= b_[i];
        } else {
            a_[i] = src_[i];
        }
    }

    _MMR_f64 dst[SPECIES_64];
    memcpy(dst, a_, sizeof(a_));


    return *dst;
}

inline _MMR_f32 mask_sub_ps(_MMR_f32 src, _MMR_MASK_i32 k, _MMR_f32 a,_MMR_f32 b) {
    float a_[SPECIES_32];
    float b_[SPECIES_32];
    float src_[SPECIES_32];
    unsigned char k_[SPECIES_32];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    memcpy(k_, &k, sizeof(k));
    memcpy(src_, &src, sizeof(src));

    for (int i = 0; i < SPECIES_32; ++i) {
        if (k_[i]) {
            a_[i] -= b_[i];
        } else {
            a_[i] = src_[i];
        }
    }

    _MMR_f32 dst[SPECIES_32];
    memcpy(dst, a_, sizeof(a_));


    return *dst;
}

inline _MMR_f64 mask_add_pd(_MMR_f64 src, _MMR_MASK_i64 k, _MMR_f64 a,_MMR_f64 b) {
    double a_[SPECIES_64];
    double b_[SPECIES_64];
    double src_[SPECIES_64];
    bool   k_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    memcpy(k_, &k, sizeof(k));
    memcpy(src_, &src, sizeof(src));

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k_[i]) {
            a_[i] += b_[i];
        } else {
            a_[i] = src_[i];
        }
    }

    _MMR_f64 dst[SPECIES_64];
    memcpy(dst, a_, sizeof(a_));


    return *dst;
}

inline _MMR_f64 mask_blend_pd(_MMR_MASK_i64 k, _MMR_f64 a, _MMR_f64 b) {
    double a_[SPECIES_64];
    double b_[SPECIES_64];
    bool   k_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    memcpy(k_, &k, sizeof(k));

    for (int i = 0; i < SPECIES_64; ++i) {
        if (k_[i]) {
            a_[i] = b_[i];
        }
    }

    _MMR_f64 dst[SPECIES_64];
    memcpy(dst, a_, sizeof(a_));

    return *dst;
}

inline _MMR_f32 mask_blend_ps(_MMR_MASK_i32 k, _MMR_f32 a, _MMR_f32 b) {
    float a_[SPECIES_32];
    float b_[SPECIES_32];
    bool k_[SPECIES_32];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    memcpy(k_, &k, sizeof(k));


    for (int i = 0; i < SPECIES_32; ++i) {
        if (k_[i]) {
            a_[i] = b_[i];
        }
    }

    _MMR_f32 dst[SPECIES_32];
    memcpy(dst, a_, sizeof(a_));

    return *dst;
}


// TODO vectorize https://stackoverflow.com/questions/49941645/get-sum-of-values-stored-in-m256d-with-sse-avx
inline double reduce_pd(_MMR_f64 a) {
    double result = 0;
    double a_[SPECIES_64];
    memcpy(a_, &a, sizeof(a));

    for (int i = 0; i < SPECIES_64; ++i) {
        result += a_[i];
    }

    return result;
}

inline float reduce_ps(_MMR_f32 a) {
    float result = 0;
    float a_[SPECIES_32];
    memcpy(a_, &a, sizeof(a));

    for (int i = 0; i < SPECIES_32; ++i) {
        result += a_[i];
    }
    return result;
}

inline int first_true_int64(_MMR_MASK_i64 k) {
    bool k_[SPECIES_64];
    memcpy(k_, &k, sizeof(k));
    for (int i = 0; i < SPECIES_64; i++) {
        if (k_[i] != 0) {
            return i;
        }
    }

    return -1;
}

inline int true_count_int64(_MMR_MASK_i64 k) {
    int res = 0;
    bool k_[SPECIES_64];
    memcpy(k_, &k, sizeof(k));
    for (int i = 0; i < SPECIES_64; i++) {
        if (k_[i] != 0) res++;
    }

    return res;
}

inline _MMR_MASK_i64 kor(_MMR_MASK_i64 a, _MMR_MASK_i64 b) {
    bool a_[SPECIES_64];
    bool b_[SPECIES_64];
    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_64; ++i) {
        a_[i] = a_[i] || b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, a_, sizeof(a_));

    return *dst;
}

inline _MMR_MASK_i64 kxor(_MMR_MASK_i64 a, _MMR_MASK_i64 b) {
    bool a_[SPECIES_64];
    bool b_[SPECIES_64];
    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_64; ++i) {
        a_[i] = a_[i] ^ b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, a_, sizeof(a_));

    return *dst;
}

inline _MMR_MASK_i64 knot(_MMR_MASK_i64 a) {
    bool a_[SPECIES_64];
    memcpy(a_, &a, sizeof(a));

    for (int i = 0; i < SPECIES_64; ++i) {
        a_[i] = !a_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, a_, sizeof(a_));

    return *dst;
}

inline _MMR_MASK_i64 lt_epi64_mask(_MMR_i64 a, _MMR_i64 b) {
    bool k_[SPECIES_64];
    int a_[SPECIES_64];
    int b_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_64; ++i) {
        k_[i] = a_[i] < b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}

inline _MMR_MASK_i64 eq_epi64_mask(_MMR_i64 a, _MMR_i64 b) {
    bool k_[SPECIES_64];
    int a_[SPECIES_64];
    int b_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_64; ++i) {
        k_[i] = a_[i] == b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}

inline _MMR_MASK_i32 eq_epi32_mask(_MMR_i32 a, _MMR_i32 b) {
    bool k_[SPECIES_32];
    int a_[SPECIES_32];
    int b_[SPECIES_32];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_32; ++i) {
        k_[i] = a_[i] == b_[i];
    }

    _MMR_MASK_i32 dst[SPECIES_32];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}


inline _MMR_MASK_i64 eq_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    bool k_[SPECIES_64];
    double a_[SPECIES_64];
    double b_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    for (int i = 0; i < SPECIES_64; ++i) {
        k_[i] = a_[i] == b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}


inline _MMR_MASK_i32 eq_ps_mask(_MMR_f32 a, _MMR_f32 b) {

    bool k_[SPECIES_32];
    float a_[SPECIES_32];
    float b_[SPECIES_32];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_32; ++i) {
        k_[i] = a_[i] == b_[i];
    }

    _MMR_MASK_i32 dst[SPECIES_32];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}


inline _MMR_MASK_i64 gt_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    bool k_[SPECIES_64];
    double a_[SPECIES_64];
    double b_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_64; ++i) {
        k_[i] = a_[i] > b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}

inline _MMR_MASK_i64 ge_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    bool k_[SPECIES_64];
    double a_[SPECIES_64];
    double b_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_64; ++i) {
        k_[i] = a_[i] >= b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}

inline _MMR_MASK_i64 lt_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    bool k_[SPECIES_64];
    double a_[SPECIES_64];
    double b_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_64; ++i) {
        k_[i] = a_[i] < b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}


inline _MMR_MASK_i32 lt_ps_mask(_MMR_f32 a, _MMR_f32 b) {
    bool k_[SPECIES_32];
    float a_[SPECIES_32];
    float b_[SPECIES_32];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_32; ++i) {
        k_[i] = a_[i] < b_[i];
    }

    _MMR_MASK_i32 dst[SPECIES_32];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}


inline _MMR_MASK_i64 le_pd_mask(_MMR_f64 a, _MMR_f64 b) {
    bool k_[SPECIES_64];
    double a_[SPECIES_64];
    double b_[SPECIES_64];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));

    for (int i = 0; i < SPECIES_64; ++i) {
        k_[i] = a_[i] <= b_[i];
    }

    _MMR_MASK_i64 dst[SPECIES_64];
    memcpy(dst, k_, sizeof(k_));

    return *dst;
}
#endif //INTEL_VECTORIZED_BENCHMARK_SUITE_SERIAL_H
