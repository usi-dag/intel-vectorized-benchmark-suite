//
// Created by mini on 13.08.22.
// TEST the serial implementation for missing avx 2 intrinsic
// THESE TESTS COMPILE ONLY FOR AVX2
//

#include <iostream>

#include "../vector_defines.h"


#define ASSERT_EQUALS(x, y) {if (x != y) std::cout << "On line " << __LINE__<< " -> " << __FUNCTION__ << ":" << " \033[1;31mTest failed!\033[0m Expected " << x << " but receive " << y << std::endl;}
#define ASSERT_EQUALS_VECTOR(i, x, y) {if (x != y) std::cout << "On line " << __LINE__<< " -> " << __FUNCTION__ << ":" << " \033[1;31mTest failed!\033[0m Index " << i << " Expected " << x << " but receive " << y << std::endl;}

//void print_mask32(_MMR_MASK_i32  k) {
//
//    for (int i = 0; i < SPECIES_32; ++i) {
//        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
//    }
//}
//
//void print_mask64(_MMR_MASK_i32  k) {
//
//    for (int i = 0; i < SPECIES_32; ++i) {
//        std::cout << "vec[" << i << "] = " << k[i] << ", ";
//    }
//
//    std::cout << std::endl;
//}
//
//void print_vec32(_MMR_f32 k) {
//
//    for (int i = 0; i < SPECIES_32; ++i) {
//        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
//    }
//}
//
//void print_vec32i(_MMR_i32 k) {
//
//
//    for (int i = 0; i < SPECIES_32; ++i) {
//        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
//    }
//
//}
//
//void print_vec64i(_MMR_i32 k) {
//
//    for (int i = 0; i < SPECIES_64; ++i) {
//        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
//    }
//}
//
//void print_vec64(_MMR_f64 k) {
//
//    for (int i = 0; i < SPECIES_64; ++i) {
//        std::cout << "vec[" << i << "] = " << k[i] << std::endl;
//    }
//}


void mask_add_epi64_test() {
    _MMR_i64 a = _mm256_set_epi64x(1, 1, 1, 1);
    _MMR_i64 b = _mm256_set_epi64x(0, 1, 2, 3);
    _MMR_i64 src = _mm256_set_epi64x(5, 5, 5, 5);
    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_64, 0);
    k[0] = 1;
    k[3] = 1;
    _MMR_i64 result = mask_add_epi64(src, k, a, b);

    _MMR_i64 expected = _mm256_set_epi64x(1, 5, 5, 4);

    for (int i = 0; i < SPECIES_64; i++) {
        ASSERT_EQUALS_VECTOR(i, expected[i], result[i]);
    }
}

void srav_epi64_test() {
    _MMR_i64 a = _mm256_set_epi64x(4, 3, 2, 1);
    _MMR_i64 count = _mm256_set_epi64x(1, 1, 1, 1);

    _MMR_i64 expected = _mm256_set_epi64x(3, 2, 1, 0);
    _MMR_i64 result = srav_epi64(a, count);

    for (int i = 0; i < SPECIES_64; i++) {
        ASSERT_EQUALS_VECTOR(i, expected[i], result[i]);
    }
}

void reduce_lane_add_epi32_test() {
    _MMR_i32  a = _mm256_set_epi32(1, 1, 1, 1, 1, 1, 1, 1);
    int expected = 8;
    int result = reduce_lane_add_epi32(a);

    ASSERT_EQUALS(expected, result);
}

void mask_reduce_lane_add_epi32_test() {
    _MMR_i32  a = _mm256_set_epi32(1, 1, 1, 1, 1, 1, 1, 1);

    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_32, 0);
    k[0] = 1;
    k[2] = 1;
    k[5] = 1;

    int expected = 3;
    int result = mask_reduce_lane_add_epi32(k, a);

    ASSERT_EQUALS(expected, result);
}

void mask_blend_epi64_test() {
    _MMR_i64 a = _mm256_set_epi64x(1, 1, 1, 1);
    _MMR_i64 b = _mm256_set_epi64x(5, 4, 3, 2);
    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_64, 0);
    k[0] = 1;
    k[2] = 1;

    _MMR_i64 expected = _mm256_set_epi64x(1, 4, 1, 2);
    _MMR_i64 result = mask_blend_epi64(k, a , b);

    for (int i = 0; i < SPECIES_64; i++) {
        ASSERT_EQUALS_VECTOR(i, expected[i], result[i]);
    }
}

void mask_load_ps_test() {
    _MMR_f32  src = _mm256_set_ps(1, 1, 1, 1, 1, 1, 1, 1);
    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_32, 0);
    k[0] = 1;
    k[1] = 1;
    k[3] = 1;
    float mem_addr[SPECIES_32] = {2,2,2,2,2,2,2,2};
    _MMR_f32  result = mask_load_ps(src, k, mem_addr);
    _MMR_f32  expected = _mm256_set_ps(1, 1, 1, 1, 2, 1, 2, 2);

    for (int i = 0; i < SPECIES_32; i++) {
        ASSERT_EQUALS_VECTOR(i, expected[i], result[i]);
    }

}

void mask_sub_pd_test() {
    _MMR_f64  src = _mm256_set_pd(1, 1, 1, 1);
    _MMR_f64  a = _mm256_set_pd(2, 2, 2, 2);
    _MMR_f64  b = _mm256_set_pd(2, 2, 2, 2);
    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_64, 0);
    k[0] = 1;
    k[1] = 1;
    k[3] = 1;
    _MMR_f64  result = mask_sub_pd(src, k, a, b);
    _MMR_f64  expected = _mm256_set_pd(0, 1, 0, 0);

    for (int i = 0; i < SPECIES_64; i++) {
        ASSERT_EQUALS_VECTOR(i, expected[i], result[i]);
    }

}

void mask_sub_ps_test() {
    _MMR_f32  src = _mm256_set_ps(1, 1, 1, 1, 1, 1, 1, 1);
    _MMR_f32  a = _mm256_set_ps(2, 2, 2, 2, 2, 2, 2, 2);
    _MMR_f32  b = _mm256_set_ps(2, 2, 2, 2, 2, 2, 2, 2);
    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_32, 0);
    k[0] = 1;
    k[1] = 1;
    k[3] = 1;
    _MMR_f32  result = mask_sub_ps(src, k, a, b);
    _MMR_f32  expected = _mm256_set_ps(1, 1, 1, 1, 0, 1, 0, 0);

    for (int i = 0; i < SPECIES_32; i++) {
        ASSERT_EQUALS_VECTOR(i, expected[i], result[i]);
    }

}

void mask_add_pd_test() {
    _MMR_f64  src = _mm256_set_pd(1, 1, 1, 1);
    _MMR_f64  a = _mm256_set_pd(2, 2, 2, 2);
    _MMR_f64  b = _mm256_set_pd(2, 2, 2, 2);
    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_64, 0);
    k[0] = 1;
    k[1] = 1;
    k[3] = 1;
    _MMR_f64  result = mask_add_pd(src, k, a, b);
    _MMR_f64  expected = _mm256_set_pd(4, 1, 4, 4);

    for (int i = 0; i < SPECIES_64; i++) {
        ASSERT_EQUALS_VECTOR(i, expected[i], result[i]);
    }

}

void mask_blend_pd_test() {
    _MMR_f64  a = _mm256_set_pd(1, 1, 1, 1);
    _MMR_f64  b = _mm256_set_pd(2, 2, 2, 2);
    _MMR_MASK_i64 k = std::vector<bool>(SPECIES_64, 0);
    k[0] = 1;
    k[1] = 1;
    k[3] = 1;
    _MMR_f64  result = mask_blend_pd(k, a, b);
    _MMR_f64  expected = _mm256_set_pd(2, 1, 2, 2);

    for (int i = 0; i < SPECIES_64; i++) {
        ASSERT_EQUALS_VECTOR(i, expected[i], result[i]);
    }

}







int main(void) {

    mask_add_epi64_test();
    srav_epi64_test();
    reduce_lane_add_epi32_test();
    mask_reduce_lane_add_epi32_test();
    mask_blend_epi64_test();
    mask_load_ps_test();
    mask_sub_ps_test();
    mask_add_pd_test();
    mask_blend_pd_test();
    return 1;
}