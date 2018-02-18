//
//  SubMatrix.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <stdio.h>
#include <memory.h>
#include "SubMatrix.hpp"
#include "Matrix.hpp"

SubMatrix::SubMatrix(std::shared_ptr<MatrixBase> matrix,
          matrix_size_t row_offset,
          matrix_size_t col_offset,
          matrix_size_t rows,
          matrix_size_t columns)
:MatrixBase(rows, columns), m_original(matrix), m_row_offset(row_offset), m_col_offset(col_offset) { }

/// Access to single row of the matrix through []
MatrixRow SubMatrix::operator[](matrix_size_t index) {
    return (*m_original)[index].withIncreasedOffset(m_row_offset);
}
