//
//  main.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 28/01/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <vector>
#include "OptionControl.hpp"
#include "OperationQueue.hpp"
#include "TestOperation.hpp"

int main(int argc, char ** argv) {
    OptionControl option_control;
    bool invalid_options = option_control.parseOptions(argc, argv, std::cerr);

    // Show help if requested
    if(invalid_options || option_control.getShowHelp()) {
        option_control.printHelp(std::cout);
    }

    if (invalid_options) {
        return 1;
    } else {
        std::cout << option_control; // Print selected options
    }
}

void testOperationQueue() {
    OperationQueue queue;
    std::vector<OperationQueue::op_ptr> operations;

    for (unsigned long int i = 0; i < 10; ++i) {
        auto op = OperationQueue::op_ptr(new TestOperation(1000000 + 1000 * i));
        operations.push_back(op);
    }

    for (unsigned long int i = 0; i < 9; ++i) {
        auto op = OperationQueue::op_ptr(new TestOperation(1000000 + 1000 * i));
        Operation::addDependecy(operations[i], operations[9]);
    }


    queue.insertOperations(operations.begin(), operations.end());

    OperationQueue::op_ptr operation(nullptr);
    while((operation = queue.next()).get() != nullptr) {
        operation->execute();
    }
}
