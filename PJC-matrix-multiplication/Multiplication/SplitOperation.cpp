//
//  SplitOperation.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 22/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include <memory>
#include <stack>
#include <iostream>
#include "SplitOperation.hpp"
#include "MatrixBase.hpp"
#include "Matrix.hpp"
#include "Operation.hpp"
#include "MergeOperation.hpp"
#include "MultiplyOperation.hpp"
#include "WriteOperation.hpp"

#define MIN_SPLIT_SIZE 100

// MARK: - SplitOperation - protected

bool SplitOperation::canSplit(const_matrix_pointer left, const_matrix_pointer right) const {
    return left->rows() % 2 == 0
        && left->rows() > MIN_SPLIT_SIZE
        && right->rows() % 2 == 0
        && right->rows() > MIN_SPLIT_SIZE;
}

SplitOperation::operation_pointer SplitOperation::split(std::vector<operation_pointer> & operations,
                                                        const_matrix_pointer left,
                                                        const_matrix_pointer right,
                                                        matrix_pointer result) {
    if (canSplit(left, right)) {
        auto merge = std::make_shared<MergeOperation>(left, right, result);
        operations.push_back(merge);

        auto ae = this->split(operations,
                              left->submatrix(LeftSubmatrix::a),
                              right->submatrix(RightSubmatrix::e),
                              merge->semiResultSubmatrix(ResultSubmatrix::ae));
        auto bg = this->split(operations,
                              left->submatrix(LeftSubmatrix::b),
                              right->submatrix(RightSubmatrix::g),
                              merge->semiResultSubmatrix(ResultSubmatrix::bg));
        auto af = this->split(operations,
                              left->submatrix(LeftSubmatrix::a),
                              right->submatrix(RightSubmatrix::f),
                              merge->semiResultSubmatrix(ResultSubmatrix::af));
        auto bh = this->split(operations,
                              left->submatrix(LeftSubmatrix::b),
                              right->submatrix(RightSubmatrix::h),
                              merge->semiResultSubmatrix(ResultSubmatrix::bh));
        auto ce = this->split(operations,
                              left->submatrix(LeftSubmatrix::c),
                              right->submatrix(RightSubmatrix::e),
                              merge->semiResultSubmatrix(ResultSubmatrix::ce));
        auto dg = this->split(operations,
                              left->submatrix(LeftSubmatrix::d),
                              right->submatrix(RightSubmatrix::g),
                              merge->semiResultSubmatrix(ResultSubmatrix::dg));
        auto cf = this->split(operations,
                              left->submatrix(LeftSubmatrix::c),
                              right->submatrix(RightSubmatrix::f),
                              merge->semiResultSubmatrix(ResultSubmatrix::cf));
        auto dh = this->split(operations,
                              left->submatrix(LeftSubmatrix::d),
                              right->submatrix(RightSubmatrix::h),
                              merge->semiResultSubmatrix(ResultSubmatrix::dh));

        merge->addDependency(ae);
        merge->addDependency(bg);
        merge->addDependency(af);
        merge->addDependency(bh);
        merge->addDependency(ce);
        merge->addDependency(dg);
        merge->addDependency(cf);
        merge->addDependency(dh);

        return merge;
    } else {
        auto multiply = std::make_shared<MultiplyOperation>(left, right, result);
        operations.push_back(multiply);
        return multiply;
    }
}

bool SplitOperation::hasWorkType(const OperationWorkType & type) const  {
    return type == Operation::OperationWorkType::Allocates
        || type == Operation::OperationWorkType::AddsOperations;
}

void SplitOperation::work() {
    auto operations = split();

    if(m_queue) {
        m_queue->insertOperations(operations.begin(), operations.end());
    }
}

// MARK: - SplitOperation - public

SplitOperation::SplitOperation(context ctx, const_matrix_pointer left, const_matrix_pointer right)
:m_ctx(ctx), m_left(left), m_right(right) { }

std::vector<SplitOperation::operation_pointer> SplitOperation::split() {
    std::vector<operation_pointer> operations;
    auto result = std::make_shared<Matrix>(m_left->rows());
    auto result_op = split(operations, m_left, m_right, result);
    auto write_op = std::make_shared<WriteOperation>(result, m_ctx);
    write_op->addDependency(result_op);
    operations.push_back(write_op);

    return operations;
}
