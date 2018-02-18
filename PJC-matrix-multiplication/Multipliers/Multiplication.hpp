//
//  Multiplication.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 15/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef Multiplication_hpp
#define Multiplication_hpp

#include <stdio.h>
#include <iostream>
#include "MatrixBase.hpp"

struct Multiplication {
    std::shared_ptr<MatrixBase> left;
    std::shared_ptr<MatrixBase> right;

    std::shared_ptr<MatrixBase> result;

    Multiplication(std::shared_ptr<MatrixBase>left,
                   std::shared_ptr<MatrixBase> right,
                   std::shared_ptr<MatrixBase> result);
};

#endif /* Multiplication_hpp */

