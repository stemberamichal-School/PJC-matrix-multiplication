//
//  MultiplicationContext.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 10/02/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef MultiplicationContext_hpp
#define MultiplicationContext_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>

class MultiplicationContext: public std::enable_shared_from_this<MultiplicationContext>  {
public:
    virtual std::istream & inputStream() = 0;
    virtual std::ostream & outputStream() = 0;
};

class FileMultiplicationContext: public MultiplicationContext {
protected:
    std::string m_input_file;
    std::string m_output_file;
    std::ifstream m_input_stream;
    std::ofstream m_output_stream;

public:
    FileMultiplicationContext(const std::string & input, const std::string & output);

    virtual std::istream & inputStream() override;
    virtual std::ostream & outputStream() override;
};
#endif /* MultiplicationContext_hpp */

