//
// Created by mini on 10.08.22.
//

#include <cstdlib>
#include "array.h"


int main(int argc, char * argv []) {
    const int N = 10;

    double ****X = new double***[3];

    init_X(N, X);

    X[0][3][3][2] = 1;
}

