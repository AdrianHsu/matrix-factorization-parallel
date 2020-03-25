//
// Created by Pedro Rio on 14/03/2020.
//

#ifndef SERIAL_WRITEINITIALMATRICES_H
#define SERIAL_WRITEINITIALMATRICES_H

#include <iostream>
#include <fstream>
#include <vector>

void writeInitialMatrices(std::string &matrixFileName, std::vector<std::vector<double>> &A,
                          std::vector<std::vector<double>> &L, std::vector<std::vector<double>> &R);


#endif //SERIAL_WRITEINITIALMATRICES_H


