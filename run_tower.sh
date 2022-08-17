make install SIZE=VECTOR_SIZE_512 INTEL_INTRINSIC="mavx512f -mavx512vl -mavx512dq" MACHINE=tower

make install SIZE=VECTOR_SIZE_256 INTEL_INTRINSIC="mavx512f -mavx512vl -mavx512dq" MACHINE=tower

make install SIZE=VECTOR_SIZE_128 INTEL_INTRINSIC="mavx512f -mavx512vl -mavx512dq" MACHINE=tower

make clean



