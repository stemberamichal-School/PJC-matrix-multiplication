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
#include "MatrixBase.hpp"

/// Matrix representation
class Matrix: public MatrixBase {
    friend class SubMatrix;
    friend class ConstSubMatrix;
protected:
    /// All values of the matrix
    /// - First accessed by row then by column
    matrix_value_t ** const m_matrix;
public:
    Matrix(matrix_size_t rows, matrix_size_t columns);

    virtual MatrixRow operator[](matrix_size_t index);

    virtual ~Matrix();
};

#endif /* Matrix_hpp */
