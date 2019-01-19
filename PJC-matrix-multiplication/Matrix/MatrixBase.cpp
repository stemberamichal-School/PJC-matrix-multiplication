//
//  MatrixBase.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <stdio.h>
#include <memory>
#include "MatrixBase.hpp"

// MARK: - MatrixRow
template<class matrix_base_t>
MatrixRow<matrix_base_t>::MatrixRow(pointer matrix, matrix_size_t row_index, matrix_size_t column_offset)
:m_matrix(matrix), m_row_index(row_index), m_column_offset(column_offset) { }

template<class matrix_base_t>
matrix_value_t& MatrixRow<matrix_base_t>::operator[](matrix_size_t index) {
    return m_matrix->value(m_row_index, index + m_column_offset);
}

template<class matrix_base_t>
const matrix_value_t& MatrixRow<matrix_base_t>::operator[](matrix_size_t index) const {
    return m_matrix->value(m_row_index, index + m_column_offset);
}

// MARK: - MatrixBase
MatrixBase::MatrixBase(matrix_size_t rows, matrix_size_t columns)
:m_rows(rows), m_columns(columns) { }

matrix_size_t MatrixBase::rows() const {
    return m_rows;
}

matrix_size_t MatrixBase::columns() const {
    return m_columns;
}


