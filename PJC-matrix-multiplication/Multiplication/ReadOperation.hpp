//
//  ReadOperation.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 22/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef ReadOperation_hpp
#define ReadOperation_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include "Operation.hpp"

class MatrixBase;

class MatrixReaderException: public std::exception {
};

class InvalidSizeException: MatrixReaderException {
};

class InvalidValueException: MatrixReaderException {
};

class ReadOperation: public Operation {
protected:
    using resource_pointer = std::unique_ptr<std::istream>;
    using matrix_pointer = std::shared_ptr<MatrixBase>;

    resource_pointer m_left_resource;
    resource_pointer m_right_resource;

    matrix_pointer m_left_matrix;
    matrix_pointer m_right_matrix;

    virtual bool hasWorkType(const OperationWorkType & type) const override;

    virtual void work() override;
public:
    /// Takes ownership of the provided resource stream
    ReadOperation(resource_pointer & m_left_resource, resource_pointer & m_right_resource);

    /// Reads both matrices from streams provided in constructor into a new matrices.
    virtual void read();

    /// Get left matrix read from the provided resource.
    /// When be called before read method finishes then behaviour is undefined, pointer can be nullptr.
    matrix_pointer getLeftMatrix() const;

    /// Get left matrix read from the provided resource.
    /// When be called before read method finishes then behaviour is undefined, pointer can be nullptr.
    matrix_pointer getRightMatrix() const;
};

#endif /* ReadOperation_hpp */
