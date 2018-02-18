//
//  ConstSubMatrix.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef ConstSubMatrix_hpp
#define ConstSubMatrix_hpp

#include "MatrixBase.hpp"
#include "Matrix.hpp"

class ConstSubMatrix: MatrixBase {
protected:
    /// Offset of submatrix in rows
    matrix_size_t m_row_offset;
    /// Offset of submatrix in columns
    matrix_size_t m_col_offset;

    /// Original Matrix
    const Matrix& m_original;

public:
    ConstSubMatrix(const Matrix& matrix,
                   matrix_size_t row_offset,
                   matrix_size_t col_offset,
                   matrix_size_t rows,
                   matrix_size_t columns);

    /// Number of rows in matrix
    virtual matrix_size_t rows();
    /// Number of columns in matrix
    virtual matrix_size_t columns();
    /// Access to single row of the matrix through []
    virtual MatrixRow operator[](matrix_size_t index);

    virtual ~ConstSubMatrix() {}
};
#endif /* SubMatrix_hpp */
