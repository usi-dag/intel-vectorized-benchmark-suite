//
// Created by mini on 04.08.22.
//

#include <iostream>
#include <cstring>
#include <vector>
#include "immintrin.h"

#define _MMR_MASK_i32 __mmask8
#define SPECIES_32 8
#define SPECIES_64 4
#define _MMR_f32 __m256
#define _MMR_i32 __m256i
#define _MMR_i64 __m256i
#define  _MMR_f64 __m256d

void print_mask32(_MMR_MASK_i32 k) {

    bool dst[SPECIES_32];
    memcpy(dst, &k, sizeof(k));

    for (int i = 0; i < SPECIES_32; ++i) {
        printf("maks[%d] = %d\n", i, (__mmask8)*(dst + i));
    }
}

void print_vec32(_MMR_f32 k) {

    float dst[SPECIES_32];
    memcpy(dst, &k, sizeof(k));

    for (int i = 0; i < SPECIES_32; ++i) {
        std::cout << "vec[" << i << "] = " << dst[i] << std::endl;
    }
}

void print_vec32i(_MMR_i32 k) {

    int dst[SPECIES_32];
    memcpy(dst, &k, sizeof(k));

    for (int i = 0; i < SPECIES_32; ++i) {
        std::cout << "vec[" << i << "] = " << dst[i] << std::endl;
    }
}

void print_vec64i(_MMR_i32 k) {

    int64_t dst[SPECIES_64];
    memcpy(dst, &k, sizeof(k));

    for (int i = 0; i < SPECIES_64; ++i) {
        std::cout << "vec[" << i << "] = " << dst[i] << std::endl;
    }
}

void print_vec64(_MMR_f64 k) {

    double dst[SPECIES_64];
    memcpy(dst, &k, sizeof(k));

    for (int i = 0; i < SPECIES_64; ++i) {
        std::cout << "vec[" << i << "] = " << dst[i] << std::endl;
    }
}

inline int true_count_int32(_MMR_MASK_i32 k) {
    int res = 0;
    bool k_[SPECIES_32];
    memcpy(k_, &k, sizeof(k));
    for (int i = 0; i < SPECIES_32; i++) {
        if (k_[i] != 0) res++;
        std::cout << "mask[" << i << "] = " <<  k_[i] << std::endl;

    }

    return res;
}

inline _MMR_f32 mask_blend_ps(_MMR_MASK_i32 k, _MMR_f32 a, _MMR_f32 b) {
    float a_[SPECIES_32];
    float b_[SPECIES_32];
    bool k_[SPECIES_32];

    memcpy(a_, &a, sizeof(a));
    memcpy(b_, &b, sizeof(b));
    memcpy(k_, &k, sizeof(k));


    for (int i = 0; i < SPECIES_32; ++i) {
        if (*(&k + i)) {
            a_[i] = -1;
        }

        std::cout << (bool)*(&k + i) << std::endl;
    }

    _MMR_f32 dst[SPECIES_32];
    memcpy(dst, a_, sizeof(a_));

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

//    for (int i = 0; i < SPECIES_32; ++i) {
//        printf("mask[%d] = %i, %p\n", i, *(&dst + i), (&dst + i));
//    }

    return *dst;
}

int main(int argc, char *argv[]) {

    _MMR_f32  a = _mm256_set_ps(1, 1, 1, 1, 1, 1, 1, 1);
    _MMR_f32  b = _mm256_set_ps(1, 0, 1, 0, 1, 0, 1, 0);

    _MMR_i32 d = _mm256_set_epi32(1, 0, 1, 0, 1, 0, 1, 0);
    _MMR_i64 f = _mm256_set_epi64x(1, 0, 1, 0);
    _MMR_f64 g = _mm256_set_pd(1.2, 0, 1, 0);

    print_vec32i(d);
    print_vec64i(f);
    print_vec64(g);

//
//    float a_[SPECIES_32];
//    float b_[SPECIES_32];
//
//    memcpy(b_, &b, sizeof(b));
//    _MMR_f32 c[SPECIES_32];
//    memcpy(c, b_, sizeof(b));
//    print_vec32(*c);



//    _MMR_MASK_i32 mask = eq_ps_mask(a, b);

//    for (int i = 0; i < SPECIES_32; ++i) {
//        printf("dst[%d] = %d, %p\n", i, *(&mask + i), (&mask + i));
//    }

//    print_mask32(mask);

//    a = mask_blend_ps(mask, a, b);
//    print_vec32(a);
//    int res = true_count_int32(mask);
//    std::cout << res << std::endl;
//    print_mask32(mask);

    return 1;
}
