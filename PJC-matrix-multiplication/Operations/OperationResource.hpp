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

/// Supplies additional work to the OperationQueue
/// Not threadsafe
class OperationResource {
    /// Determines whether there is more work to be done.
    virtual bool workAvailable() = 0;
    /// Supplies operations into given vector for insertion into queue.
    virtual void insertOperations(std::vector<OperationResource> & operations) = 0;
};

#endif /* OperationResource_hpp */
