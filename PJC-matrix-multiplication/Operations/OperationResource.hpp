//
//  OperationResource.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 18/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef OperationResource_hpp
#define OperationResource_hpp

#include <stdio.h>
#include <vector>

class Operation;

/// Supplies additional work to the OperationQueue
/// Not threadsafe
class OperationResource {
public:
    /// Determines whether there is more work to be done.
    virtual bool isWork() = 0;
    /// Generates new Operations with proper dependencies if necessary and return vector of them
    virtual std::vector<Operation *> getWork() = 0;
};

#endif /* OperationResource_hpp */
