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
class MergeOperation;

class SplitOperation: public Operation {
protected:
    using matrix_pointer = std::shared_ptr<MatrixBase>;
    using const_matrix_pointer = std::shared_ptr<const MatrixBase>;
    using operation_pointer = std::shared_ptr<Operation>;

    const_matrix_pointer m_left;
    const_matrix_pointer m_right;

    virtual bool hasWorkType(const OperationWorkType & type) const override;

    virtual void work() override;

    /// Decides whether the multiplication can be further split based on the size of left and right matrices
    virtual bool canSplit(const_matrix_pointer left, const_matrix_pointer right) const;
    /// Splits the given operation if it can be further split, otherwise ends it with multiplications.
    virtual void split(std::shared_ptr<MergeOperation> & merge, std::vector<operation_pointer> & operations);

public:
    SplitOperation(const_matrix_pointer left, const_matrix_pointer right);

    virtual std::vector<operation_pointer> split();
};

#endif /* SplitOperation_hpp */
