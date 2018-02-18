//
//  main.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 28/01/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <iostream>
#include <getopt.h>
#include <vector>
#include "OperationQueue.hpp"
#include "TestOperation.hpp"

#define DEFAULT_MATRIXES_COUNT 1000
#define DEFAULT_THREADS_COUNT 1

enum class Option {
    Help,
    Threads,
};

class OptionControl {
    const char * const short_opts = "n:bs:w:h";
    const option longOptions[2] = {
        { "help", 0, nullptr, 'h' },
        { "threads", 1, nullptr, 't' }
    };

public:
    OptionControl(int argc, const char * argv[]) {

    }

    void printHelp(std::ostream & out) {
        // Heading
        out << "Multithread Matrix multiplier by Michal Stembera" << std::endl;
        out << std::endl;
        // Usage
        out << "Usage:" << std::endl;
        out << "matrix-mult [options]" << std::endl;
        // Options
        out << "Options:" << std::endl;
        out << "    -t --threads <count> Number of threads used [default: " << DEFAULT_THREADS_COUNT << "]." << std::endl;
        out << "    -m --matrixes <count> Number of matrixes multiplied [Default:" << DEFAULT_MATRIXES_COUNT << "]." << std::endl;
        out << "    -h --help Show help." << std::endl;
    }
};

int main(int argc, const char * argv[]) {
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

    return 0;
}
