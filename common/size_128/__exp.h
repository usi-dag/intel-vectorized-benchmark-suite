// 
// RISC-V VECTOR EXP FUNCTION Version by Cristóbal Ramírez Lazo, "Barcelona 2019"
// This RISC-V Vector implementation is based on the original code presented by Julien Pommier

/* 
   AVX implementation of sin, cos, sincos, exp and log

   Based on "sse_mathfun.h", by Julien Pommier
   http://gruntthepeon.free.fr/ssemath/

   Copyright (C) 2012 Giovanni Garberoglio
   Interdisciplinary Laboratory for Computational Science (LISC)
   Fondazione Bruno Kessler and University of Trento
   via Sommarive, 18
   I-38123 Trento (Italy)

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  (this is the zlib license)
*/

inline _MMR_f64 __exp_1xf64(_MMR_f64 x) {

_MMR_f64   tmp;
_MMR_f64   tmp2;
_MMR_f64   tmp4;
_MMR_f64   fx;
_MMR_f64   z;
_MMR_f64   y;
_MMR_MASK_i64  mask;
_MMR_i64  imm0;
_MMR_i64  tmp3;

        x     = _MM_MIN_f64(x, _MM_SET_f64(88.3762626647949));
        x     = _MM_MAX_f64(x, _MM_SET_f64(-88.3762626647949));

        fx    = _MM_SET_f64(0.5);
        fx    = _MM_MADD_f64(x,_MM_SET_f64(1.44269504088896341), fx);

        tmp3  = _MM_VFCVT_X_F_i64(fx);
        tmp   = _MM_VFCVT_F_X_f64(tmp3);

        mask  = _MM_VFLT_f64(fx,tmp);
        tmp2  = _MM_MERGE_f64(mask, _MM_SET_f64(0.0),_MM_SET_f64(1.0));
        fx    = _MM_SUB_f64(tmp,tmp2);
        tmp   = _MM_MUL_f64(fx, _MM_SET_f64(0.693359375));
        z     = _MM_MUL_f64(fx, _MM_SET_f64(-2.12194440e-4));
        x     = _MM_SUB_f64(x,tmp);
        x     = _MM_SUB_f64(x,z);
        z     = _MM_MUL_f64(x,x);
        y     = _MM_SET_f64(1.9875691500E-4);
        y     = _MM_MADD_f64(y,x,_MM_SET_f64(1.3981999507E-3));
        y     = _MM_MADD_f64(y,x,_MM_SET_f64(8.3334519073E-3));
        y     = _MM_MADD_f64(y,x,_MM_SET_f64(4.1665795894E-2));
        y     = _MM_MADD_f64(y,x,_MM_SET_f64(1.6666665459E-1));
        y     = _MM_MADD_f64(y,x,_MM_SET_f64(5.0000001201E-1));
        y     = _MM_MADD_f64(y,z,x);
        y     = _MM_ADD_f64(y, _MM_SET_f64(1.0));

        imm0  = _MM_VFCVT_X_F_i64(fx);
        imm0  = _MM_ADD_i64(imm0, _MM_SET_i64(1023));
        imm0  = _MM_SLL_i64(imm0, 52);

        tmp4 = (_MMR_f64)imm0;
        y     = _MM_MUL_f64(y, tmp4);
        return y;
}

//inline _MMR_f32 __exp_2xf32(_MMR_f32 x ,unsigned long int gvl) {
//
//_MMR_f32   tmp;
//_MMR_f32   tmp2;
//_MMR_f32   tmp4;
//_MMR_f32   fx;
//_MMR_f32   z;
//_MMR_f32   y;
//_MMR_MASK_i32  mask;
//_MMR_i32  imm0;
//_MMR_i32  tmp3;
//
//        x     = _MM_MIN_f32(x, _MM_SET_f32(88.3762626647949,gvl),gvl);
//        x     = _MM_MAX_f32(x, _MM_SET_f32(-88.3762626647949,gvl),gvl);
//
//        fx    = _MM_SET_f32(0.5,gvl);
//        fx    = _MM_MACC_f32(fx,x,_MM_SET_f32(1.44269504088896341,gvl),gvl);
//
//        tmp3  = _MM_VFCVT_X_F_i32(fx,gvl);
//        tmp   = _MM_VFCVT_F_X_f32(tmp3,gvl);
//
//        mask  = _MM_VFLT_f32(fx,tmp,gvl);
//        tmp2  = _MM_MERGE_f32( _MM_SET_f32(0.0,gvl),_MM_SET_f32(1.0,gvl), mask,gvl);
//        fx    = _MM_SUB_f32(tmp,tmp2,gvl);
//        tmp   = _MM_MUL_f32(fx, _MM_SET_f32(0.693359375,gvl),gvl);
//        z     = _MM_MUL_f32(fx, _MM_SET_f32(-2.12194440e-4,gvl),gvl);
//        x     = _MM_SUB_f32(x,tmp,gvl);
//        x     = _MM_SUB_f32(x,z,gvl);
//
//        z     = _MM_MUL_f32(x,x,gvl);
//        y     = _MM_SET_f32(1.9875691500E-4,gvl);
//        y     = _MM_MADD_f32(y,x,_MM_SET_f32(1.3981999507E-3,gvl),gvl);
//        y     = _MM_MADD_f32(y,x,_MM_SET_f32(8.3334519073E-3,gvl),gvl);
//        y     = _MM_MADD_f32(y,x,_MM_SET_f32(4.1665795894E-2,gvl),gvl);
//        y     = _MM_MADD_f32(y,x,_MM_SET_f32(1.6666665459E-1,gvl),gvl);
//        y     = _MM_MADD_f32(y,x,_MM_SET_f32(5.0000001201E-1,gvl),gvl);
//        y     = _MM_MADD_f32(y,z,x,gvl);
//        y     = _MM_ADD_f32(y, _MM_SET_f32(1.0,gvl),gvl);
//
//        imm0  = _MM_VFCVT_X_F_i32(fx,gvl);
//        imm0  = _MM_ADD_i32(imm0, _MM_SET_i32(0x7f,gvl),gvl);
//        imm0  = _MM_SLL_i32(imm0, _MM_SET_i32(23,gvl),gvl);
//
//        tmp4 = (_MMR_f32)imm0;
//        y     = _MM_MUL_f32(y, tmp4,gvl);
//        return y;
//}

inline _MMR_f32 __exp_32_scalar(_MMR_f32 x) {
    float val[SPECIES_32];
    memcpy(val, &x, sizeof(val));

    for (int i = 0; i < SPECIES_32; ++i) {
        val[i] = exp(val[i]);
    }

    return _MM_SETV_f32(val[3], val[2], val[1], val[0]);
}

inline _MMR_f64 __exp_64_scalar(_MMR_f64 x) {
    double val[SPECIES_64];
    memcpy(val, &x, sizeof(val));

    for (int i = 0; i < SPECIES_64; ++i) {
        val[i] = exp(val[i]);
    }

    return _MM_SETV_f64(val[1], val[0]);
}

inline _MMR_f32 __exp_2xf32(_MMR_f32 x) {

    _MMR_f32   tmp;
    _MMR_f32   tmp2;
    _MMR_f32   tmp4;
    _MMR_f32   fx;
    _MMR_f32   z;
    _MMR_f32   y;
    _MMR_MASK_i32  mask;
    _MMR_i32  imm0;
    _MMR_i32  tmp3;

    x     = _MM_MIN_f32(x, _MM_SET_f32(88.3762626647949));
    x     = _MM_MAX_f32(x, _MM_SET_f32(-88.3762626647949));

    fx    = _MM_SET_f32(0.5);
    fx    = _MM_MADD_f32(_MM_SET_f32(1.44269504088896341), fx, x);

    tmp3  = _MM_VFCVT_X_F_i32(fx);
    tmp   = _MM_VFCVT_F_X_f32(tmp3);

    mask  = _MM_VFLT_f32(fx, tmp);
    tmp2  = _MM_MERGE_f32( mask, _MM_SET_f32(0.0),_MM_SET_f32(1.0));
    fx    = _MM_SUB_f32(tmp,tmp2);
    tmp   = _MM_MUL_f32(fx, _MM_SET_f32(0.693359375));
    z     = _MM_MUL_f32(fx, _MM_SET_f32(-2.12194440e-4));
    x     = _MM_SUB_f32(x,tmp);
    x     = _MM_SUB_f32(x,z);

    z     = _MM_MUL_f32(x,x);
    y     = _MM_SET_f32(1.9875691500E-4);
    y     = _MM_MADD_f32(y,x,_MM_SET_f32(1.3981999507E-3));
    y     = _MM_MADD_f32(y,x,_MM_SET_f32(8.3334519073E-3));
    y     = _MM_MADD_f32(y,x,_MM_SET_f32(4.1665795894E-2));
    y     = _MM_MADD_f32(y,x,_MM_SET_f32(1.6666665459E-1));
    y     = _MM_MADD_f32(y,x,_MM_SET_f32(5.0000001201E-1));
    y     = _MM_MADD_f32(y,z,x);
    y     = _MM_ADD_f32(y, _MM_SET_f32(1.0));

    imm0  = _MM_VFCVT_X_F_i32(fx);
    imm0  = _MM_ADD_i32(imm0, _MM_SET_i32(0x7f));
    imm0  = _MM_SLL_i32(imm0, _MM_SET_i32(23));

    tmp4 = (_MMR_f32)imm0;
    y     = _MM_MUL_f32(y, tmp4);
    return y;
}