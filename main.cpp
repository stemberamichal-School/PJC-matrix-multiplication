//
//  main.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 28/01/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <vector>
#include <thread>
#include "OptionControl.hpp"
#include "OperationQueue.hpp"
#include "TestOperation.hpp"
#include "ReadOperation.hpp"
#include "MultiplicationContext.hpp"

void computeMatrixes(const OptionControl & control);
void testOperationQueue();

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

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

    computeMatrixes(option_control);
//    testOperationQueue();
}

void compute(std::shared_ptr<OperationQueue> queue) {
    OperationQueue::op_ptr op;
    while((op = queue->next()).get()) {
        op->execute();
    }
}

void computeMatrixes(const OptionControl & control) {
    auto in_files = control.getMatrixesFiles();
    std::vector<OperationQueue::op_ptr> reads;

    for (auto it = in_files.begin(); it != in_files.end(); ++it) {
        auto out_file = (*it) + ".multiplied";
        auto ctx = std::make_shared<FileMultiplicationContext>(*it, out_file);
        reads.push_back(std::make_shared<ReadOperation>(ctx));
    }

    auto op_queue = std::make_shared<OperationQueue>();
    op_queue->insertOperations(reads.begin(), reads.end());

    auto start = std::chrono::high_resolution_clock::now();

    // Create threads
    auto thread_count = control.getThreadsCount();
    std::vector<std::thread> threads;
    for (size_t i = 0; i < thread_count; ++i) {
        threads.emplace_back(compute, op_queue);
    }
    // Join threads
    for (auto& t: threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Needed " << to_ms(end - start).count() << " ms to finish.\n";
}

void testOperationQueue() {
    OperationQueue queue;
    std::vector<OperationQueue::op_ptr> operations;

    for (unsigned long int i = 0; i < 10; ++i) {
        auto op = OperationQueue::op_ptr(new TestOperation(1000000 + 1000 * i));
        operations.push_back(op);
    }

    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = i + 1; j < 10; ++j) {
            operations[i]->addDependency(operations[j]);
        }
    }


    queue.insertOperations(operations.begin(), operations.end());

    OperationQueue::op_ptr operation(nullptr);
    while((operation = queue.next()).get() != nullptr) {
        operation->execute();
    }
}
