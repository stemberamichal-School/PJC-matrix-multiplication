//
//  SimpleMultiplier.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 28/01/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef Iterative_hpp
#define Iterative_hpp

#include <stdio.h>
#include <iostream>

class MatrixBase;

class IterativeMultiplier {

public:
    IterativeMultiplier();

    std::shared_ptr<MatrixBase> multiply(std::shared_ptr<const MatrixBase> left,
                                         std::shared_ptr<const MatrixBase> right);
};

#endif /* Iterative_hpp */
