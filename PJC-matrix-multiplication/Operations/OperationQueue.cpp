//
//  OperationQueue.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 17/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <algorithm>
#include "Operation.hpp"
#include "OperationQueue.hpp"

bool OperationQueue::PriorityComparator::operator()(const OperationQueue::op_ptr& lhs,
                                                     const OperationQueue::op_ptr& rhs) {
    return lhs->priority() < rhs->priority();
}

bool OperationQueue::PointerPredicate::operator()(const op_ptr &check) {
    return check.get() == m_ptr;
}

OperationQueue::PointerPredicate::PointerPredicate(Operation * const pointer)
    :m_ptr(pointer) { }

OperationQueue::op_ptr OperationQueue::next() {
    std::lock_guard<std::mutex> lk(m_queueLock);

    // If no more return nullptr
    if(m_queueHeap.empty()) {
        return op_ptr(nullptr);
    }

    // pop with highest priority from m_queueHeap
    std::pop_heap(m_queueHeap.begin(), m_queueHeap.end(), m_cmp);
    auto operation = m_queueHeap.back();
    m_queueHeap.pop_back();

    // Push to m_executing
    m_executing.push_back(operation);

    return operation;
}

void OperationQueue::operationDidFinish(Operation * op) {
    std::lock_guard<std::mutex> lk(m_queueLock);

    PointerPredicate predicate(op);
    auto remove_it = std::find_if(m_executing.begin(), m_executing.end(), predicate);

    // if was not found, then there's nothing we can do
    if(remove_it == m_executing.end()) {
        return;
    }

    // Remove dependencies - might affect operations priority/state
    Operation::removeFromDependent(*remove_it);

    // Rebuild operations heap
    std::make_heap(m_queueHeap.begin(), m_queueHeap.end(), m_cmp);

    // Remove finished operation from executing
    m_executing.erase(remove_it);
}
