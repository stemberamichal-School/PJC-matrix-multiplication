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

class MatrixBase;

/// Four submetrixes into which original left multiplicaton operand squared matrix can be split
enum LeftOperandSubmatrix { a, b, c, d };
/// Four submetrixes into which original right multiplication operand squared matrix can be split
enum RightOperandSubmatrix { e, f, g, h };
/// Eight results of split matrix multiplications
enum ResultSubmatrix { ae, bg, af, bh, ce, dg, cf, dh };

class MergeOperation: public Operation {
protected:
    using pointer = std::shared_ptr<MatrixBase>;
    using const_pointer = std::shared_ptr<const MatrixBase>;

    const_pointer m_left;
    const_pointer m_right;

    std::vector<pointer> m_semi_results;
    pointer m_result;

    virtual bool hasWorkType(const OperationWorkType & type) const override;

    virtual void work() override;

public:
    /// Restraints:
    /// - left, right and result matrices have to be squared and of the same size
    /// - Also their size has to be dividable by 2
    MergeOperation(const_pointer left, const_pointer right);

    /// MatrixView into according part of the left operand matrix
    const_pointer leftOperandSubmatrix(LeftOperandSubmatrix submatrix) const;
    /// MatrixView into according part of the right operand
    const_pointer rightOperandSubmatrix(RightOperandSubmatrix submatrix) const;
    /// Submetrix into which the result should be written, created in constructor.
    pointer resultSubmatrix(ResultSubmatrix submatrix);
};

#endif /* DivideAndConquerMerge_hpp */
