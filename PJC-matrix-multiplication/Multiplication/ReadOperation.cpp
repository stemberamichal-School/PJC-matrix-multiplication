//
//  ReadOperation.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 22/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include <vector>
#include <sstream>
#include "ReadOperation.hpp"
#include "MatrixBase.hpp"
#include "MatrixRow.hpp"
#include "Matrix.hpp"
#include "SplitOperation.hpp"
#include "MultiplicationContext.hpp"

std::vector<matrix_value_t> parse_line(const std::string & line) {
    std::istringstream is(line);
    matrix_value_t value;
    std::vector<matrix_value_t> row;

    while(is >> value) {
        row.push_back(value);
    }

    if(!is.eof()) {
        throw InvalidValueException();
    }

    return row;
}

std::shared_ptr<MatrixBase> read_matrix(std::istream &is) {
    std::string line;
    matrix_size_t side = 0;
    std::shared_ptr<MatrixBase> matrix;

    for(int i = 0; std::getline(is, line); ++i) {
        std::vector<matrix_value_t> row = parse_line(line);

        if (i == 0 && row.size() != 0) {
            side = row.size();
            matrix = std::make_shared<Matrix>(side);
        } else if (row.size() == 0 || row.size() != side) {
            throw InvalidSizeException();
        }

        for(int j = 0; j < side; ++j) {
            (*matrix)[i][j] = row[j];
        }
    }

    return matrix;
}

// MARK: - ReadOperation - protected

bool ReadOperation::hasWorkType(const OperationWorkType & type) const {
    return type == Operation::OperationWorkType::Allocates
        || type == Operation::OperationWorkType::AddsOperations;
}

void ReadOperation::work() {
    try {
        read();

        if (m_queue) {
            auto split_op = std::make_shared<SplitOperation>(m_ctx, m_left_matrix, m_right_matrix);
            m_queue->insertOperation(split_op);
        }
    } catch(std::exception & exception) {
        // TODO: Should print something or somehow (best would be WriteExceptionOperation)
    }
}

// MARK: - ReadOperation - public

ReadOperation::ReadOperation(ReadOperation::context ctx)
:m_ctx(ctx) { }

void ReadOperation::read() {
    std::istream & input = m_ctx->inputStream();

    // Read left matrix
    m_left_matrix = read_matrix(input);
    // Read empty line
    std::string line;
    if (!std::getline(input, line) || line.size() != 0) {
        throw InvalidFormatException();
    }
    // Read right matrix
    m_right_matrix = read_matrix(input);

    // Check if matrixes are realy squared and if they have same size.
    if(m_left_matrix->rows() != m_left_matrix->columns()
       || m_right_matrix->rows() != m_right_matrix->rows()
       || m_left_matrix->rows() != m_right_matrix-> rows()) {
        throw InvalidSizeException();
    }
}

ReadOperation::matrix_pointer ReadOperation::getLeftMatrix() const {
    return m_left_matrix;
}


ReadOperation::matrix_pointer ReadOperation::getRightMatrix() const {
    return m_right_matrix;
}

