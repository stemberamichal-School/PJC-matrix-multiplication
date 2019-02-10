//
//  MultiplicationContext.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 10/02/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#include "MultiplicationContext.hpp"


// MARK: - FileMultiplicationContext
FileMultiplicationContext::FileMultiplicationContext(const std::string & input, const std::string & output)
:m_input_file(input), m_output_file(output) { }

std::istream & FileMultiplicationContext::inputStream() {
    m_input_stream = std::ifstream(m_input_file.c_str());
    return m_input_stream;
}

std::ostream & FileMultiplicationContext::outputStream() {
    m_output_stream = std::ofstream(m_output_file.c_str());
    return m_output_stream;
};
