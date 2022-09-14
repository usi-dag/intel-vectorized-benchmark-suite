//
// Created by mini on 02.05.22.
// FROM THE WORK OF
/*************************************************************************
* Vectorized Axpy Kernel
* Author: Jesus Labarta
* Barcelona Supercomputing Center
*************************************************************************/

#include "axpy.h"


#ifdef USE_VECTOR_INTRINSIC
#include "../../common/vector_defines.h"


void axpy_intrinsics(double a, double *dx, double *dy, int n) {
  int i;

//  long gvl = __builtin_epi_vsetvl(n, __epi_e64, __epi_m1);
  int limit = loop_bound(SPECIES_64, n);
//    _MMR_f64 v_a = _MM_SET_f64(a, gvl);
  _MMR_f64 v_a = _MM_SET_f64(a);

  for (i = 0; i < limit;) {
//    gvl = __builtin_epi_vsetvl(n - i, __epi_e64, __epi_m1);
    _MMR_f64 v_dx = _MM_LOAD_f64(&dx[i]);
    _MMR_f64 v_dy = _MM_LOAD_f64(&dy[i]);
    _MMR_f64 v_res = _MM_MADD_f64(v_a, v_dx, v_dy);
    _MM_STORE_f64(&dy[i], v_res);

    i += SPECIES_64;
  }


  for (; i < n; ++i) {
      dy[i] += dx[i] * a;
  }

//FENCE();
}
#endif

// Ref version
void axpy_ref(double a, double *dx, double *dy, int n) {
    int i;
    for (i=0; i<n; i++) {
        dy[i] += a*dx[i];
    }
}

void init_vector(double *pv, long n, double value)
{
    for (int i=0; i<n; i++) {
        pv[i] = value;
    }
}

// int main(void){}
