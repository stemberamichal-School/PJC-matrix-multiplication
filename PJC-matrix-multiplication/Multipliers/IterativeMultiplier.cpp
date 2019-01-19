//
//  SimpleMultiplier.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 28/01/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include "IterativeMultiplier.hpp"
#include "MatrixBase.hpp"
#include "Matrix.hpp"


IterativeMultiplier::IterativeMultiplier() { }

std::shared_ptr<MatrixBase> multiply(std::shared_ptr<const MatrixBase> left,
                                     std::shared_ptr<const MatrixBase> right) {
    std::shared_ptr<MatrixBase> result = std::make_shared<Matrix>(left->rows(), right->columns());

    for (int i = 0; i < result->rows(); i++) {
        for (int j = 0; j < result->columns(); j++) {
            (*result)[i][j] = 0;
            for(int k = 0; k < left->columns(); k++) {
                (*result)[i][j] += (*left)[i][k] * (*right)[k][j];
            }
        }
    }

    return result;
}
