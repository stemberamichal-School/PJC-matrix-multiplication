//
//  DivideAndConquerMerge.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 20/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef DivideAndConquerMerge_hpp
#define DivideAndConquerMerge_hpp

#include <stdio.h>
#include <memory>
#include <vector>
#include "Operation.hpp"
#include "Shared.hpp"

class MatrixBase;

class MergeOperation: public Operation {
protected:
    using pointer = std::shared_ptr<MatrixBase>;
    using const_pointer = std::shared_ptr<const MatrixBase>;

    std::vector<pointer> m_semi_results;
    const_pointer m_left;
    const_pointer m_right;
    pointer m_result;

    virtual bool hasWorkType(const OperationWorkType & type) const override;

    virtual void work() override;

public:
    /// Restraints:
    /// - left, right and result matrices have to be squared and of the same size
    /// - Also their size has to be dividable by 2
    MergeOperation(const_pointer left, const_pointer right, pointer result);

    /// Submetrix into which the result should be written, created in constructor.
    pointer semiResultSubmatrix(ResultSubmatrix submatrix);
    /// Returns original left matrix operand
    const_pointer getLeft();
    /// Returns original right matrix operand
    const_pointer getRight();
    /// Returns whole read-only result matrix
    const_pointer getResult() const;

    /// Merges the  semi results into single result matrix
    void merge();
};

#endif /* DivideAndConquerMerge_hpp */
