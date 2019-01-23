//
//  WriteOperation.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 22/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef WriteOperation_hpp
#define WriteOperation_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include "Operation.hpp"

class MatrixBase;

class WriteOperation: public Operation {
protected:
    using const_matrix = std::shared_ptr<const MatrixBase>;
    using stream = std::shared_ptr<std::ostream>;

    const_matrix m_matrix;
    stream os;

    virtual bool hasWorkType(const OperationWorkType & type) const override;

    virtual void work() override;

public:
    WriteOperation(const_matrix & matrix, stream & os);

    /// Writes the matrix to stream provided in constructor.
    virtual void write();
};

#endif /* WriteOperation_hpp */
