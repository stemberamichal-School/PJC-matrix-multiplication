//
//  MatrixRow.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 27/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef MatrixRow_hpp
#define MatrixRow_hpp

#include <stdio.h>
#include <memory>
#include "Shared.hpp"

class MatrixBase;

/// Helper class for access through [][]
class MatrixRow {
protected:
    using pointer = std::shared_ptr<MatrixBase>;
    matrix_size_t m_row_index;
    matrix_size_t m_column_offset;
    pointer m_matrix;

public:
    MatrixRow(pointer matrix, matrix_size_t row_index, matrix_size_t column_offset = 0);

    virtual matrix_value_t& operator[](matrix_size_t index);

    virtual const matrix_value_t& operator[](matrix_size_t index) const;
};

/// Helper class for const access through [][]
class ConstMatrixRow {
protected:
    using const_pointer = std::shared_ptr<const MatrixBase>;
    matrix_size_t m_row_index;
    matrix_size_t m_column_offset;
    const_pointer m_matrix;

public:
    ConstMatrixRow(const_pointer matrix, matrix_size_t row_index, matrix_size_t column_offset = 0);

    virtual const matrix_value_t& operator[](matrix_size_t index) const;
};

#endif /* MatrixRow_hpp */
