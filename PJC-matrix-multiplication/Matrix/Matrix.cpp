//
//  Matrix.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <stdio.h>
#include "Matrix.hpp"

Matrix::Matrix(matrix_size_t rows, matrix_size_t columns)
:MatrixBase(rows, columns), m_matrix(new matrix_value_t * [m_rows]) {
    for (matrix_size_t i = 0; i < m_rows; ++i) {
        m_matrix[i] = new matrix_value_t [columns];
    }
}

MatrixRow Matrix::operator[](matrix_size_t index) {
    return MatrixRow(m_matrix[index]);
}

const MatrixRow Matrix::operator[](matrix_size_t index) const {
    return MatrixRow(m_matrix[index]);
}

Matrix::~Matrix() {
    for (matrix_size_t i = 0; i < m_rows; ++i) {
        delete [] m_matrix[i];
    }
    delete [] m_matrix;
}
