//
//  SquareMatrixReader.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 19/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include <memory>
#include <iostream>
#include <string>
#include "SquareMatrixReader.hpp"

std::tuple<matrix_size_t, matrix_value_t *> SquareMatrixReader::read_first_line(const std::string & line) const {
    throw std::logic_error("not implemented yet");
}

matrix_value_t * SquareMatrixReader::read_following_line(const std::string & line, int expected_size) const {
    throw std::logic_error("not implemented yet");
}

std::shared_ptr<MatrixBase> SquareMatrixReader::read(std::istream &is) const {
    std::string line;
    matrix_size_t rows_columns_count;

    if(std::getline(is, line)) {

    } else {
        
    }

    while(std::getline(std::cin, line)) {

    }


}
