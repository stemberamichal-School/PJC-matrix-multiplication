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

typedef float matrix_value_t;
typedef size_t matrix_size_t;

class MatrixBase;

/// Helper class for access through [][]
template<class matrix_base_t>
class MatrixRow {
    static_assert(std::is_base_of<MatrixBase, matrix_base_t>::value, "matrix_base_t must extend MatrixBase");
protected:
    using pointer = std::shared_ptr<matrix_base_t>;
    matrix_size_t m_row_index;
    matrix_size_t m_column_offset;
    std::shared_ptr<matrix_base_t> m_matrix;

public:
    MatrixRow(pointer matrix, matrix_size_t row_index, matrix_size_t column_offset = 0);

    virtual matrix_value_t& operator[](matrix_size_t index);

    virtual const matrix_value_t& operator[](matrix_size_t index) const;
};

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
    virtual MatrixRow<MatrixBase> operator[](matrix_size_t index) = 0;
    /// Access to constant row of the matrix through []
    virtual const MatrixRow<const MatrixBase> operator[](matrix_size_t index) const = 0;

    virtual ~MatrixBase() = default;
};

#endif /* MatrixBase_hpp */
