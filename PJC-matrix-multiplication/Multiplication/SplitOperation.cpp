//
//  SplitOperation.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 22/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include <memory>
#include "SplitOperation.hpp"
#include "MatrixBase.hpp"
#include "Matrix.hpp"
#include "Operation.hpp"
#include "MergeOperation.hpp"
#include "MultiplyOperation.hpp"

#define MIN_SPLIT_SIZE 100

// MARK: - SplitOperation - protected

bool SplitOperation::canSplit(const_matrix_pointer left, const_matrix_pointer right) const {
    return left->rows() % 2 == 0
        && left->rows() > MIN_SPLIT_SIZE
        && right->rows() % 2 == 0
        && right->rows() > MIN_SPLIT_SIZE;
}

void SplitOperation::split(std::shared_ptr<MergeOperation> & merge,
                           std::vector<operation_pointer> & operations) {
    if(canSplit(<#const_matrix_pointer left#>, <#const_matrix_pointer right#>))
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

SplitOperation::SplitOperation(const_matrix_pointer left, const_matrix_pointer right)
: m_left(left), m_right(right) {}

std::vector<SplitOperation::operation_pointer> SplitOperation::split() {
    std::vector<operation_pointer> operations;

    if (canSplit(m_left, m_right)) {
        auto merge = std::make_shared<MergeOperation>(m_left, m_right);
        operations.push_back(merge);
        split(merge, operations);
    } else {
        auto result = std::make_shared<Matrix>(m_left->rows());
        auto multiply = std::make_shared<MultiplyOperation>(m_left, m_right, result);
        operations.push_back(multiply);
    }

    return operations;
}
