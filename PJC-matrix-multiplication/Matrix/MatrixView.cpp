//
//  SubMatrix.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <stdio.h>
#include <memory.h>
#include "MatrixView.hpp"
#include "MatrixBase.hpp"

// MARK: - MatrixView

MatrixView::MatrixView(std::shared_ptr<MatrixBase> matrix,
          matrix_size_t row_offset,
          matrix_size_t col_offset,
          matrix_size_t rows,
          matrix_size_t columns)
:MatrixBase(rows, columns), m_writable(matrix), m_redable(matrix), m_row_offset(row_offset), m_col_offset(col_offset) { }

MatrixView::MatrixView(std::shared_ptr<const MatrixBase> matrix,
                       matrix_size_t row_offset,
                       matrix_size_t col_offset,
                       matrix_size_t rows,
                       matrix_size_t columns)
:MatrixBase(rows, columns), m_writable(nullptr), m_redable(matrix), m_row_offset(row_offset), m_col_offset(col_offset) { }

matrix_value_t & MatrixView::value(matrix_size_t row, matrix_value_t column) {
    return m_writable->value(m_row_offset + row, m_col_offset + column);
}

const matrix_value_t & MatrixView::value(matrix_size_t row, matrix_value_t column) const {
    return m_redable->value(m_row_offset + row, m_col_offset + column);
}

MatrixRow MatrixView::operator[](matrix_size_t index) {
    return MatrixRow(m_writable, m_row_offset + index, m_col_offset);
}
    
ConstMatrixRow MatrixView::operator[](matrix_size_t index) const {
    return ConstMatrixRow(m_redable, m_row_offset + index, m_col_offset);
}
