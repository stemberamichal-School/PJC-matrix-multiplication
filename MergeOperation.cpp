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
#include "MatrixRow.hpp"

#define SUBRESULTS_COUNT 8

// MARK: - Protected

bool MergeOperation::hasWorkType(const OperationWorkType & type) const {
    return type == OperationWorkType::Computes
        || type == OperationWorkType::Releases;
}

void MergeOperation::work() {
    merge();
}

void MergeOperation::sum(ResultSubmatrix submatrix) {
    // result = left + right (for example a = ae + bg)
    pointer result = m_result->submatrix(submatrix);
    const_pointer left, right;

    switch (submatrix) {
        case ResultSubmatrix::a:
            left = semiResultSubmatrix(SemiResultSubmatrix::ae);
            right = semiResultSubmatrix(SemiResultSubmatrix::bg);
            break;
        case ResultSubmatrix::b:
            left = semiResultSubmatrix(SemiResultSubmatrix::af);
            right = semiResultSubmatrix(SemiResultSubmatrix::bh);
            break;
        case ResultSubmatrix::c:
            left = semiResultSubmatrix(SemiResultSubmatrix::ce);
            right = semiResultSubmatrix(SemiResultSubmatrix::dg);
            break;
        case ResultSubmatrix::d:
            left = semiResultSubmatrix(SemiResultSubmatrix::cf);
            right = semiResultSubmatrix(SemiResultSubmatrix::dh);
            break;
    }

    for (int i = 0; i < result->rows(); ++i) {
        for(int j = 0; j < result->columns(); ++j) {
            (*result)[i][j] = (*left)[i][j] + (*right)[i][j];
        }
    }
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
MergeOperation::pointer MergeOperation::semiResultSubmatrix(SemiResultSubmatrix submatrix) {
    switch (submatrix) {
        case SemiResultSubmatrix::ae: return m_semi_results[0];
        case SemiResultSubmatrix::bg: return m_semi_results[1];
        case SemiResultSubmatrix::af: return m_semi_results[2];
        case SemiResultSubmatrix::bh: return m_semi_results[3];
        case SemiResultSubmatrix::ce: return m_semi_results[4];
        case SemiResultSubmatrix::dg: return m_semi_results[5];
        case SemiResultSubmatrix::cf: return m_semi_results[6];
        case SemiResultSubmatrix::dh: return m_semi_results[7];
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
    sum(ResultSubmatrix::a);
    sum(ResultSubmatrix::b);
    sum(ResultSubmatrix::c);
    sum(ResultSubmatrix::d);
}
