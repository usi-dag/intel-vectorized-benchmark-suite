//
// Created by mini on 28.07.22.
//

#ifndef INTEL_VECTORIZED_BENCHMARK_SUITE_VECTOR_SPECIES_H
#define INTEL_VECTORIZED_BENCHMARK_SUITE_VECTOR_SPECIES_H

#if defined(VECTOR_SIZE_128)
#define SPECIES_32 4 // species for 32 bit type
#define SPECIES_64 2 // species for 64 bit type

// TYPES
#define _MMR_f64        	__m128d
#define _MMR_f32        	__m128

#define _MMR_i64        	__m128i
#define _MMR_i32        	__m128i

#define _MMR_MASK_i64   	__mmask8
#define _MMR_MASK_i32   	__mmask8

#elif defined(VECTOR_SIZE_256)
#define SPECIES_32 8 // species for 32 bit type
#define SPECIES_64 4 // species for 64 bit type

// TYPES
#define _MMR_f64        	__m256d
#define _MMR_f32        	__m256

#define _MMR_i64        	__m256i
#define _MMR_i32        	__m256i

#define _MMR_MASK_i64   	__mmask8
#define _MMR_MASK_i32   	__mmask8

#elif defined(VECTOR_SIZE_512)
#define SPECIES_32 16 // species for 32 bit type
#define SPECIES_64 8 // species for 64 bit type

// TYPES
#define _MMR_f64        	__m512d
#define _MMR_f32        	__m512

#define _MMR_i64        	__m512i
#define _MMR_i32        	__m512i

#define _MMR_MASK_i64   	__mmask16
#define _MMR_MASK_i32   	__mmask16

#endif


//---------------------------------------------------------------------------
// UTILITY FUNCTION
inline int loop_bound(int species_size, int length) {
    return floor(abs(length)/species_size) * species_size;
}

#endif //INTEL_VECTORIZED_BENCHMARK_SUITE_VECTOR_SPECIES_H
