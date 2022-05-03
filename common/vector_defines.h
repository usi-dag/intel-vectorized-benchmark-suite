#ifndef VECTOR_DEFINITION
#define VECTOR_DEFINITION

#include <stdio.h>

#if defined(VECTOR_SIZE_128)
#include "./size_128/vector_128.h"
#elif defined(VECTOR_SIZE_256)
#include "./size_256/vector_256.h"
#elif defined(VECTOR_SIZE_512)
#include "./size_512/vector_512.h"
#endif






#endif // VECTOR_DEFINITION
