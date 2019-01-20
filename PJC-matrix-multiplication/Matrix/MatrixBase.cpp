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
#include "MatrixView.hpp"

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

// MARK: - MatrixBase
MatrixBase::MatrixBase(matrix_size_t rows, matrix_size_t columns)
:m_rows(rows), m_columns(columns) { }

matrix_size_t MatrixBase::rows() const {
    return m_rows;
}

matrix_size_t MatrixBase::columns() const {
    return m_columns;
}

std::shared_ptr<MatrixBase> MatrixBase::submatrix(matrix_size_t row_offset,
                                                  matrix_size_t col_offset,
                                                  matrix_size_t rows,
                                                  matrix_size_t columns)
{
    return std::make_shared<MatrixView>(shared_from_this(), row_offset, col_offset, rows, columns);
}

std::shared_ptr<const MatrixBase> MatrixBase::submatrix(matrix_size_t row_offset,
                                                        matrix_size_t col_offset,
                                                        matrix_size_t rows,
                                                        matrix_size_t columns) const
{
    return std::make_shared<const MatrixView>(shared_from_this(), row_offset, col_offset, rows, columns);
}


