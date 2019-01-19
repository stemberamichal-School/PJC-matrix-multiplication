//
//  Matrix.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <stdio.h>
#include <memory>
#include "Matrix.hpp"
#include "MatrixBase.hpp"

Matrix::Matrix(matrix_size_t rows, matrix_size_t columns)
:MatrixBase(rows, columns), m_matrix(std::vector<matrix_value_t>(rows * columns)) {
}

Matrix::Matrix(matrix_size_t side)
:MatrixBase(side, side), m_matrix(std::vector<matrix_value_t>(side * side)){

}

matrix_value_t & Matrix::value(matrix_size_t row, matrix_value_t column) {
    return m_matrix[row * m_columns + column];
}

const matrix_value_t & Matrix::value(matrix_size_t row, matrix_value_t column) const {
    return m_matrix[row * m_columns + column];
}

MatrixRow<MatrixBase> Matrix::operator[](matrix_size_t index) {
    return MatrixRow<MatrixBase>(shared_from_this(), index);
}

const MatrixRow<const MatrixBase> Matrix::operator[](matrix_size_t index) const {
    return MatrixRow<const MatrixBase>(shared_from_this(), index);
}

