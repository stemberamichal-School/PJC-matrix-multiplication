//
//  SquareMatrixReader.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 19/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef SquareMatrixReader_hpp
#define SquareMatrixReader_hpp

#include <stdio.h>
#include "MatrixReaderBase.hpp"
#include "MatrixBase.hpp"

class SquareMatrixReader: public MatrixReaderBase {
protected:
    virtual std::tuple<matrix_size_t, matrix_value_t *> read_first_line(const std::string & line) const;

    virtual matrix_value_t * read_following_line(const std::string & line, int expected_size) const;
public:
    virtual std::shared_ptr<MatrixBase> read(std::istream &is) const override;
};

#endif /* SquareMatrixReader_hpp */
