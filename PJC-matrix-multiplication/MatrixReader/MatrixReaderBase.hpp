//
//  MatrixReader.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 19/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef MatrixReader_hpp
#define MatrixReader_hpp

#include <stdio.h>
#include <memory>
#include <valarray>

class MatrixBase;

class MatrixReaderException: public std::exception {
};

class InvalidDimensionException: MatrixReaderException {
};

class InvalidValueException: MatrixReaderException {
};

class MatrixReaderBase {
public:
    virtual std::shared_ptr<MatrixBase> read(std::istream &is) const = 0;
};

#endif /* MatrixReader_hpp */
