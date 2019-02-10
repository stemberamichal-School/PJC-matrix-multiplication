//
//  Operation.cpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 17/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#include <algorithm>
#include <vector>
#include "Operation.hpp"
#include "OperationQueue.hpp"

Operation::Operation() { }

unsigned char Operation::workTypePriority() const {
    unsigned char workPriority = 0;

    if (hasWorkType(OperationWorkType::Releases)) {
        workPriority |= 1 << 3;
    }
    if (hasWorkType(OperationWorkType::Computes)) {
        workPriority |= 1 << 2;
    }
    if (hasWorkType(OperationWorkType::Allocates)) {
        workPriority |= 1 << 1;
    }
    if (hasWorkType(OperationWorkType::AddsOperations)) {
        workPriority |= 1 << 0;
    }

    return workPriority;
}

OperationState Operation::getState() {
    return m_state;
}

void Operation::setState(OperationState newState) {
    m_state = newState;
}

unsigned long int Operation::priority() const {
    switch(m_state) {
        case OperationState::Waiting:
        case OperationState::Executing:
        case OperationState::Finished:
            return 0;
        case OperationState::Ready:
            return (m_dependent.size() << 8) | workTypePriority();
    }
}

bool Operation::addDependency(OperationQueue::op_ptr & dependency) {
    // Cannot add dependencies while in operation queue
    if (this->m_queue || dependency->m_queue) {
        return false; // TODO: throw instead??
    }

    this->m_dependencies.push_back(dependency);
    dependency->m_dependent.push_back(shared_from_this());

    return true;
}

void Operation::removeDependency(OperationQueue::op_ptr & dependency) {
    auto remove_it = std::find(m_dependencies.begin(), m_dependencies.end(), dependency);

    if(remove_it != m_dependencies.end()) {
        m_dependencies.erase(remove_it);
    }

    if(m_dependencies.empty() && m_state == OperationState::Waiting) {
        m_state = OperationState::Ready;
    }
}

void Operation::removeFromDependent() {
    auto this_ptr = shared_from_this();
    for (auto it = this->m_dependent.begin(); it != this->m_dependent.end(); ++it) {
        (*it)->removeDependency(this_ptr);
    }
}

void Operation::prepareForInsertionIntoQueue(OperationQueue* queue) {
    m_state = m_dependencies.empty() ? OperationState::Ready : OperationState::Waiting;
    m_queue = queue;
}

void Operation::execute() {
    m_state = OperationState::Executing;

    work();

    m_state = OperationState::Finished;
    if(m_queue) {
        m_queue->operationDidFinish(this);
    }
}

