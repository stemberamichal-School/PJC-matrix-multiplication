//
//  SquareMatrixReader.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 19/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "Matrix.hpp"
#include "SquareMatrixReader.hpp"

std::vector<matrix_value_t> SquareMatrixReader::parse_line(const std::string & line) const {
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

std::shared_ptr<MatrixBase> SquareMatrixReader::read(std::istream &is) const {
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
