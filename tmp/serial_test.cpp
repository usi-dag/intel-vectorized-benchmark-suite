//
// Created by mini on 04.08.22.
//

#include "serial_test.h"
#include <iostream>
#include <cstring>


int main(int argc, char *argv[]) {



    _MMR_i32  a_ = _mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0);
    int res = reduce_lane_add_epi32(a_);

    std::cout << res << std::endl;
}
