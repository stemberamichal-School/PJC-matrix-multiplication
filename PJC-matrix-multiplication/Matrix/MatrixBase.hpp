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

typedef float matrix_value_t;
typedef size_t matrix_size_t;

/// Helper class for access through [][]
class MatrixRow {
protected:
    matrix_value_t * const m_row;
    matrix_size_t m_offset;

public:
    MatrixRow(matrix_value_t * const row, matrix_size_t offset = 0);

    MatrixRow& withIncreasedOffset(matrix_size_t offset);

    virtual matrix_value_t& operator[](matrix_size_t index);
};

/// Matrix base
class MatrixBase {
protected:
    /// Number of rows
    const matrix_size_t m_rows;
    /// Number of columns
    const matrix_size_t m_columns;

public:
    MatrixBase(matrix_size_t rows, matrix_size_t columns);

    /// Number of rows in matrix
    virtual matrix_size_t rows();
    /// Number of columns in matrix
    virtual matrix_size_t columns();
    /// Access to single row of the matrix through []
    virtual MatrixRow operator[](matrix_size_t index) = 0;

    virtual ~MatrixBase() {}
};

#endif /* MatrixBase_hpp */
