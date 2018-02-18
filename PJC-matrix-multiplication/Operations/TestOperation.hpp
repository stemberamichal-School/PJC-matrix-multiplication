//
//  TestOperation.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 18/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef TestOperation_hpp
#define TestOperation_hpp

#include <stdio.h>
#include "Operation.hpp"

class TestOperation: public Operation {
private:
    const unsigned long int m_loopCount;

    virtual void work();

public:
    TestOperation(unsigned long int loopCount);
};

#endif /* TestOperation_hpp */
