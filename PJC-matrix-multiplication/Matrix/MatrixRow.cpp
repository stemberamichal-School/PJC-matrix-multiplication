//
//  MatrixRow.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 27/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include "MatrixRow.hpp"
#include "MatrixBase.hpp"

// MARK: - MatrixRow
MatrixRow::MatrixRow(pointer matrix, matrix_size_t row_index, matrix_size_t column_offset)
:m_matrix(matrix), m_row_index(row_index), m_column_offset(column_offset) { }

matrix_value_t& MatrixRow::operator[](matrix_size_t index) {
    return m_matrix->value(m_row_index, index + m_column_offset);
}

const matrix_value_t& MatrixRow::operator[](matrix_size_t index) const {
    return m_matrix->value(m_row_index, index + m_column_offset);
}

// MARK: - ConstMatrixRow
ConstMatrixRow::ConstMatrixRow(const_pointer matrix, matrix_size_t row_index, matrix_size_t column_offset)
:m_matrix(matrix), m_row_index(row_index), m_column_offset(column_offset) { }

const matrix_value_t& ConstMatrixRow::operator[](matrix_size_t index) const {
    return m_matrix->value(m_row_index, index + m_column_offset);
}
