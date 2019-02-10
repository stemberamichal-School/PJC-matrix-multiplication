//
//  MatrixBase.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef MatrixBase_hpp
#define MatrixBase_hpp

#include <stdio.h>
#include <memory>
#include "Shared.hpp"

class MatrixRow;
class ConstMatrixRow;

/// Matrix base
class MatrixBase: public std::enable_shared_from_this<MatrixBase> {
protected:
    /// Number of rows
    const matrix_size_t m_rows;
    /// Number of columns
    const matrix_size_t m_columns;

public:
    MatrixBase(matrix_size_t rows, matrix_size_t columns);

    /// Number of rows in matrix
    virtual matrix_size_t rows() const;
    /// Number of columns in matrix
    virtual matrix_size_t columns() const;

    /// Access value in given row and column
    virtual matrix_value_t & value(matrix_size_t row, matrix_value_t column) = 0;
    /// Access constant in given row and column
    virtual const matrix_value_t & value(matrix_size_t row, matrix_value_t column) const = 0;

    /// Access to single row of the matrix through []
    virtual MatrixRow operator[](matrix_size_t index) = 0;
    /// Access to constant row of the matrix through []
    virtual ConstMatrixRow operator[](matrix_size_t index) const = 0;

    /// Create writable submatrix
    virtual std::shared_ptr<MatrixBase> submatrix(matrix_size_t row_offset,
                                                  matrix_size_t col_offset,
                                                  matrix_size_t rows,
                                                  matrix_size_t columns);
    /// Create redable submatrix
    virtual std::shared_ptr<const MatrixBase> submatrix(matrix_size_t row_offset,
                                                        matrix_size_t col_offset,
                                                        matrix_size_t rows,
                                                        matrix_size_t columns) const;

    /// Create readable submatrix
    virtual std::shared_ptr<const MatrixBase> submatrix(LeftSubmatrix submatrix) const;
    /// Create readable submetrix
    virtual std::shared_ptr<const MatrixBase> submatrix(RightSubmatrix submatrix) const;
    /// Create writable submetrix
    virtual std::shared_ptr<MatrixBase> submatrix(ResultSubmatrix submatrix);

    virtual ~MatrixBase() = default;
};

#endif /* MatrixBase_hpp */
