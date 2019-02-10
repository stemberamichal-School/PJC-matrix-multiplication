//
//  WriteOperation.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 22/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include "WriteOperation.hpp"
#include "MatrixRow.hpp"
#include "MatrixBase.hpp"
#include "MultiplicationContext.hpp"

bool WriteOperation::hasWorkType(const OperationWorkType & type) const {
    return type == Operation::OperationWorkType::Releases;
}

void WriteOperation::work() {
    try {
        write();
    } catch(std::exception & exception) {
        // TODO: Should print something or somehow (best would be WriteExceptionOperation)
    }
}

WriteOperation::WriteOperation(const_matrix matrix, context context)
:m_ctx(context), m_matrix(matrix) { }

void WriteOperation::write() {
    std::ostream & out = m_ctx->outputStream();

    for (size_t i = 0; i < m_matrix->rows(); i++) {
        for (size_t j = 0; j < m_matrix->columns(); j++) {
            out << (*m_matrix)[i][j] << " ";
        }
        out << std::endl;
    }
}
