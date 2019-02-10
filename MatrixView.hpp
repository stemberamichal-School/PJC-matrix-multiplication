//
//  SubMatrix.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef MatrixView_hpp
#define MatrixView_hpp

#include <stdio.h>
#include <iostream>
#include "MatrixBase.hpp"
#include "Matrix.hpp"

class MatrixView: public MatrixBase {
protected:
    using pointer = std::shared_ptr<MatrixBase>;
    using const_pointer = std::shared_ptr<const MatrixBase>;
    /// Offset of submatrix in rows
    const matrix_size_t m_row_offset;
    /// Offset of submatrix in columns
    const matrix_size_t m_col_offset;

    /// Writable original matrix
    pointer m_writable;
    /// Const original matrix
    const_pointer m_redable;

public:
    MatrixView(pointer matrix,
               matrix_size_t row_offset,
               matrix_size_t col_offset,
               matrix_size_t rows,
               matrix_size_t columns);

    MatrixView(const_pointer matrix,
               matrix_size_t row_offset,
               matrix_size_t col_offset,
               matrix_size_t rows,
               matrix_size_t columns);

    /// Access value in given row and column
    virtual matrix_value_t & value(matrix_size_t row, matrix_value_t column) override;
    /// Access constant in given row and column
    virtual const matrix_value_t & value(matrix_size_t row, matrix_value_t column) const override;
    /// Access to single row of the matrix through []
    virtual MatrixRow operator[](matrix_size_t index) override;
    /// Access to constant row of the matrix through []
    virtual ConstMatrixRow operator[](matrix_size_t index) const override;

    virtual ~MatrixView() = default;
};

#endif /* MatrixView_hpp */
