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
#include "MatrixRow.hpp"
#include "MatrixView.hpp"
#include "Shared.hpp"

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



std::shared_ptr<const MatrixBase> MatrixBase::submatrix(LeftSubmatrix submatrix) const {
    auto rows = m_rows / 2;
    auto columns = m_columns / 2;
    auto row_offset = submatrix == LeftSubmatrix::a || submatrix == LeftSubmatrix::b ? 0 : m_rows / 2;
    auto col_offset = submatrix == LeftSubmatrix::a || submatrix == LeftSubmatrix::c ? 0 : m_columns / 2;

    return this->submatrix(row_offset, col_offset, rows, columns);
}

std::shared_ptr<const MatrixBase> MatrixBase::submatrix(RightSubmatrix submatrix) const {
    auto rows = m_rows / 2;
    auto columns = m_columns / 2;
    auto row_offset = submatrix == RightSubmatrix::e || submatrix == RightSubmatrix::f ? 0 : m_rows / 2;
    auto col_offset = submatrix == RightSubmatrix::e || submatrix == RightSubmatrix::g ? 0 : m_columns / 2;

    return this->submatrix(row_offset, col_offset, rows, columns);
}

std::shared_ptr<MatrixBase> MatrixBase::submatrix(ResultSubmatrix submatrix) {
    auto rows = m_rows / 2;
    auto columns = m_columns / 2;
    auto row_offset = submatrix == ResultSubmatrix::a || submatrix == ResultSubmatrix::b ? 0 : m_rows / 2;
    auto col_offset = submatrix == ResultSubmatrix::a || submatrix == ResultSubmatrix::c ? 0 : m_columns / 2;

    return this->submatrix(row_offset, col_offset, rows, columns);
}
