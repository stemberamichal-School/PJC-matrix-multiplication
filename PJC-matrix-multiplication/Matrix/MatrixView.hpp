//
//  SubMatrix.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef SubMatrix_hpp
#define SubMatrix_hpp

#include <stdio.h>
#include <iostream>
#include "MatrixBase.hpp"
#include "Matrix.hpp"

class MatrixView: MatrixBase {
protected:
    /// Offset of submatrix in rows
    const matrix_size_t m_row_offset;
    /// Offset of submatrix in columns
    const matrix_size_t m_col_offset;

    /// Original Matrix
    std::shared_ptr<MatrixBase> m_original;

public:
    MatrixView(std::shared_ptr<MatrixBase> matrix,
              matrix_size_t row_offset,
              matrix_size_t col_offset,
              matrix_size_t rows,
              matrix_size_t columns);

    /// Access to single row of the matrix through []
    virtual MatrixRow operator[](matrix_size_t index) override;

    /// Access to constant row of the matrix through []
    virtual ConstMatrixRow operator[](matrix_size_t index) const override;

    virtual ~MatrixView() = default;
};
#endif /* SubMatrix_hpp */
