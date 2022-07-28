//
// Created by mini on 28.07.22.
//

#include <iostream>


int main(int argc, char *argv[]) {
#ifdef __AVX512F__
    std::cout << "512" << std::endl;

#elif __AVX2__
    std::cout << "256" << std::endl;

#elif __AVX__
    std::cout << "128" << std::endl;
#endif
    std::cout << "HELLO, WORLD!" << std::endl;

//#ifdef __AVX512F__
//
//#elif __AVX2__
//
//#elif __AVX__
//
//#endif
}