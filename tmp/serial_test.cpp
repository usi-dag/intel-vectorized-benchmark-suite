//
// Created by mini on 04.08.22.
//

#include <iostream>
#include <cstring>
#include <vector>
#include "immintrin.h"


#define _MMR_MASK_i32 std::vector<bool>
#define _MMR_MASK_i64 std::vector<bool>
#define SPECIES_32 8
#define SPECIES_64 4
#define _MMR_f32 __m256
#define _MMR_i32 __m256i
#define _MMR_i64 __m256i
#define  _MMR_f64 __m256d


void print_mask32(_MMR_MASK_i32  k) {

    for (int i = 0; i < SPECIES_32; ++i) {
        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
    }
}

void print_mask64(_MMR_MASK_i32  k) {

    for (int i = 0; i < SPECIES_32; ++i) {
        std::cout << "vec[" << i << "] = " << k[i] << ", ";
    }

    std::cout << std::endl;
}

void print_vec32(_MMR_f32 k) {

    for (int i = 0; i < SPECIES_32; ++i) {
        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
    }
}

void print_vec32i(_MMR_i32 k) {


    for (int i = 0; i < SPECIES_32; ++i) {
        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
    }

}

void print_vec64i(_MMR_i32 k) {

    for (int i = 0; i < SPECIES_64; ++i) {
        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
    }
}

void print_vec64(_MMR_f64 k) {

    for (int i = 0; i < SPECIES_64; ++i) {
        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
    }
}

inline int true_count_int32(_MMR_MASK_i32 k) {
    int res = 0;
    for (int i = 0; i < SPECIES_32; i++) {
        if (k[i] != 0) res++;
    }

    return res;
}

inline _MMR_f32 mask_blend_ps(_MMR_MASK_i32 k, _MMR_f32 a, _MMR_f32 b) {


    for (int i = 0; i < SPECIES_32; ++i) {
        if (k[i]) {
            a[i] = b[i];
        }
    }

    return a;
}


inline _MMR_MASK_i32 eq_ps_mask(_MMR_f32 a, _MMR_f32 b) {

    _MMR_MASK_i32 k_ = std::vector<bool>(SPECIES_32, 0);


    for (int i = 0; i < SPECIES_32; ++i) {
        k_[i] = a[i] == b[i];
    }

    return k_;
}
 int first_true_int64(_MMR_MASK_i64 k) {

    for (int i = 0; i < SPECIES_64; i++) {
        if (k[i]) {
            return i;
        }
    }

    return -1;
}
 int true_count_int64(_MMR_MASK_i64 k) {
    int res = 0;

    for (int i = 0; i < SPECIES_64; i++) {
        if (k[i]) res++;
    }

    return res;
}

int main(int argc, char *argv[]) {

    _MMR_f32  a = _mm256_set_ps(1, 1, 1, 1, 1, 1, 1, 1);
    _MMR_f32  b = _mm256_set_ps(1, 0, 1, 0, 1, 0, 1, 0);
    _MMR_f32  c = _mm256_set_ps(2, 2, 2, 2, 2, 2, 2, 2);

    _MMR_i32 d = _mm256_set_epi32(1, 0, 1, 0, 1, 0, 1, 0);
    _MMR_i64 f = _mm256_set_epi64x(1, 0, 1, 0);
    _MMR_f64 g = _mm256_set_pd(1.2, 0, 1, 0);


//    _MMR_MASK_i32 mask =  eq_ps_mask(a, b);
//    print_mask32(mask);
//    std::cout << "res = " << true_count_int32(mask) << std::endl;
//
//    _MMR_f32 r = mask_blend_ps(mask, a, c);
//    print_vec32(r);

    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_64, 0);
    k[0] = 1;
    k[1] = 1;
    k[3] = 1;

    std::cout << "index = " << first_true_int64(k) << std::endl;
    std::cout << "res = " << true_count_int64(k) << std::endl;




    return 1;
}
