//
//  MatrixBase.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <stdio.h>
#include "MatrixBase.hpp"

// MARK: - MatrixRow
MatrixRow::MatrixRow(matrix_value_t * const row, matrix_size_t offset)
:m_row(row), m_offset(offset) { }

matrix_value_t& MatrixRow::operator[](matrix_size_t index) {
    return m_row[index + m_offset];
}

MatrixRow& MatrixRow::withIncreasedOffset(matrix_size_t offset) {
    m_offset += offset;
    return *this;
}

// MARK: - MatrixBase
MatrixBase::MatrixBase(matrix_size_t rows, matrix_size_t columns)
:m_rows(rows), m_columns(columns) { }

matrix_size_t MatrixBase::rows() {
    return m_rows;
}

matrix_size_t MatrixBase::columns() {
    return m_columns;
}


