//
// Created by mini on 10.08.22.
//

#include "array.h"

extern double **** init_X (int N, double ****X) {
    for (int i = 0; i < 3; ++i) {
        X[i] = new double **[N];
        for (int j = 0; j < N; ++j) {
            X[i][j] = new double *[N];
            for (int k = 0; k < N; ++k) {
                X[i][j][k] = new double[N];
            }
        }
    }

    return X;
}
