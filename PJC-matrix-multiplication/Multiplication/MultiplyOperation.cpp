//
//  SimpleMultiplier.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 28/01/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include "MultiplyOperation.hpp"
#include "MatrixBase.hpp"
#include "Matrix.hpp"


MultiplyOperation::MultiplyOperation(std::shared_ptr<const MatrixBase> left,
                                     std::shared_ptr<const MatrixBase> right,
                                     std::shared_ptr<MatrixBase> result)
:Operation(), m_left(left), m_right(right), m_result(result) { }

void MultiplyOperation::work() {
    multiply();
}

void MultiplyOperation::multiply() {
    for (int i = 0; i < m_result->rows(); i++) {
        for (int j = 0; j < m_result->columns(); j++) {
            (*m_result)[i][j] = 0;
            for(int k = 0; k < m_left->columns(); k++) {
                (*m_result)[i][j] += (*m_left)[i][k] * (*m_right)[k][j];
            }
        }
    }
}
