//
//  SplitOperation.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 22/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef SplitOperation_hpp
#define SplitOperation_hpp

#include <stdio.h>
#include <vector>
#include "Operation.hpp"

class MatrixBase;

class SplitOperation: public Operation {
protected:
    using matrix_pointer = std::shared_ptr<MatrixBase>;
    using const_matrix_pointer = std::shared_ptr<const MatrixBase>;
    using operation_pointer = std::shared_ptr<Operation>;

    virtual bool hasWorkType(const OperationWorkType & type) const override;

    virtual void work() override;

public:
    SplitOperation(const_matrix_pointer left, const_matrix_pointer right);

    virtual std::vector<operation_pointer> split();
};

#endif /* SplitOperation_hpp */
