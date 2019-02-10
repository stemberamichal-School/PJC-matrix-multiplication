//
//  TestOperation.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 18/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include "TestOperation.hpp"

bool TestOperation::hasWorkType(const OperationWorkType & type) const {
    return type == Operation::OperationWorkType::Computes;
}

void TestOperation::work() {
    unsigned long int sum = 0;
    for (unsigned long int i = 0; i < m_loopCount; ++i) {
        sum += i;
    }
}

TestOperation::TestOperation(unsigned long int loopCount)
    :m_loopCount(loopCount) { }
