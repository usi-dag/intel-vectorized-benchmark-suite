//
// Created by mini on 15.08.22.
//

#include "../vector_defines.h"

int main(void) {

    _MMR_f64 a = _mm512_set_pd(7,6,5,4,3,2,1,0);
    _MMR_f64 b = _mm512_set_pd(7,6,5,4,3,2,1,0);

    _MMR_MASK_i64 mask = _MM_VFEQ_f64(a, b);
    print_mask64(mask);

    return 1;
}
