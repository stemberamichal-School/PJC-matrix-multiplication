//
//  Matrix.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 04/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <vector>
#include "MatrixBase.hpp"

/// Matrix representation
class Matrix: public MatrixBase {
protected:
    /// All values of the matrix
    /// - First accessed by row then by column
    std::vector<matrix_value_t> m_matrix;
public:
    Matrix(matrix_size_t rows, matrix_size_t columns);

    // Instantiates squared metrix
    Matrix(matrix_size_t side);

    virtual matrix_value_t & value(matrix_size_t row, matrix_value_t column) override;

    virtual const matrix_value_t & value(matrix_size_t row, matrix_value_t column) const override;

    virtual MatrixRow operator[](matrix_size_t index) override;

    virtual ConstMatrixRow operator[](matrix_size_t index) const override;

    virtual ~Matrix() = default;
};

#endif /* Matrix_hpp */
