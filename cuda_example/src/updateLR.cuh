#ifndef SERIAL_UPDATELR_H
#define SERIAL_UPDATELR_H

__global__ void updateLR(double *A,
              double *prediction, double *delta,
              int *nonZeroUserIndexes,
              int *nonZeroItemIndexes,
              double *L, double *R,
              int *numberOfUsers, int *numberOfItems, int *numberOfFeatures,
              int *numberOfNonZeroElements,
              double *convergenceCoefficient);

#endif //SERIAL_UPDATELR_H
