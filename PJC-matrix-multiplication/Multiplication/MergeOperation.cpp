//
//  DivideAndConquerMerge.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 20/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include "MatrixBase.hpp"
#include "Matrix.hpp"
#include "MergeOperation.hpp"

#define SUBRESULTS_COUNT 8

// MARK: - Protected

bool MergeOperation::hasWorkType(const OperationWorkType & type) const {
    return type == OperationWorkType::Computes
        || type == OperationWorkType::Releases;
}

void MergeOperation::work() {
    merge();
}

// MARK: - Public
MergeOperation::MergeOperation(const_pointer left, const_pointer right, pointer result)
:m_left(left), m_right(right), m_result(result), m_semi_results(std::vector<pointer>()) {
    m_semi_results.reserve(SUBRESULTS_COUNT);
    auto submatrix = left->submatrix(LeftSubmatrix::a);

    for (int i = 0; i < SUBRESULTS_COUNT; ++i) {
        m_semi_results.push_back(std::make_shared<Matrix>(submatrix->rows(), submatrix->columns()));
    }
}

/// Submetrix into which the result should be written, created in constructor.
MergeOperation::pointer MergeOperation::semiResultSubmatrix(ResultSubmatrix submatrix) {
    switch (submatrix) {
        case ResultSubmatrix::ae: return m_semi_results[0];
        case ResultSubmatrix::bg: return m_semi_results[1];
        case ResultSubmatrix::af: return m_semi_results[2];
        case ResultSubmatrix::bh: return m_semi_results[3];
        case ResultSubmatrix::ce: return m_semi_results[4];
        case ResultSubmatrix::dg: return m_semi_results[5];
        case ResultSubmatrix::cf: return m_semi_results[6];
        case ResultSubmatrix::dh: return m_semi_results[7];
    }
}

MergeOperation::const_pointer MergeOperation::getLeft() {
    return m_left;
}

MergeOperation::const_pointer MergeOperation::getRight() {
    return m_right;
}

MergeOperation::const_pointer MergeOperation::getResult() const {
    return m_result;
}

void MergeOperation::merge() {
    // TODO: Implement merge
}
