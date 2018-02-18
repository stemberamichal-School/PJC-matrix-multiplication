//
//  ConstSubMatrix.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <stdio.h>
#include "MatrixBase.hpp"
#include "Matrix.hpp"
#include "ConstSubMatrix.hpp"

ConstSubMatrix::ConstSubMatrix(const Matrix& matrix,
                               matrix_size_t row_offset,
                               matrix_size_t col_offset,
                               matrix_size_t rows,
                               matrix_size_t columns)
:MatrixBase(rows, columns), m_original(matrix), m_row_offset(row_offset), m_col_offset(col_offset) { }

MatrixRow ConstSubMatrix::operator[](matrix_size_t index) {
    return MatrixRow(m_original.m_matrix[index + m_row_offset] + m_col_offset);
}
