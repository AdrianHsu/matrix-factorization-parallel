#include "updateLR.h"

void updateLR(double *&A,
              int *&nonZeroUserIndexes,
              int *&nonZeroItemIndexes,
              double *&nonZeroElements,
              double *&L, double *&R,
              double *&StoreL, double *&StoreR,
              int &numberOfUsers, int &numberOfItems, int &numberOfFeatures,
              int &numberOfNonZeroElements,
              double &convergenceCoefficient) {

    double prediction[numberOfNonZeroElements];
    for (int i = 0; i < numberOfNonZeroElements; ++i) {
        prediction[i] = 0;
    }

    double delta[numberOfNonZeroElements];
    for (int i = 0; i < numberOfNonZeroElements; ++i) {
        delta[i] = 0;
    }

    for (int l = 0; l < numberOfNonZeroElements; l++) {
        for (int k = 0; k < numberOfFeatures; k++) {
            prediction[l] += L[nonZeroUserIndexes[l] * numberOfFeatures + k] * R[k * numberOfItems + nonZeroItemIndexes[l]];
        }
    }

    for (int l = 0; l < numberOfNonZeroElements; l++) {
        delta[l] = A[nonZeroUserIndexes[l] * numberOfItems + nonZeroItemIndexes[l]] - prediction[l];
    }

    for (int l = 0; l < numberOfNonZeroElements; l++) {
        for (int k = 0; k < numberOfFeatures; k++) {
            L[nonZeroUserIndexes[l] * numberOfFeatures + k] +=
                    convergenceCoefficient * (2 * delta[l] * StoreR[k * numberOfItems + nonZeroItemIndexes[l]]);
            R[k * numberOfItems + nonZeroItemIndexes[l]] +=
                    convergenceCoefficient * (2 * delta[l] * StoreL[nonZeroUserIndexes[l] * numberOfFeatures + k]);
        }
    }
}

