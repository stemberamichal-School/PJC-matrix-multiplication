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
#include "Operation.hpp"


class MatrixBase;

class MultiplyOperation: public Operation {
protected:
    std::shared_ptr<const MatrixBase> m_left;
    std::shared_ptr<const MatrixBase> m_right;
    std::shared_ptr<MatrixBase> m_result;

    virtual bool hasWorkType(const OperationWorkType & type) const override;

    virtual void work() override;

public:
    MultiplyOperation(std::shared_ptr<const MatrixBase> left,
                      std::shared_ptr<const MatrixBase> right,
                      std::shared_ptr<MatrixBase> result);

    /// Multiplies left and right matrices and writes the result into result matrix.
    virtual void multiply();
};

#endif /* Iterative_hpp */
