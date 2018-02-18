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

void Operation::work() { }

Operation::Operation() { }

OperationState Operation::getState() {
    return m_state;
}

void Operation::setState(OperationState newState) {
    m_state = newState;
}

int Operation::priority() {
    switch(m_state) {
        case OperationState::Waiting:
        case OperationState::Executing:
        case OperationState::Finished:
            return std::min(0, -(int)m_dependencies.size());
        case OperationState::Ready:
            return std::max(1, (int)m_dependent.size());
    }
}

bool Operation::addDependecy(OperationQueue::op_ptr & dependent,
                             OperationQueue::op_ptr & dependency) {
    if (dependent->m_queue || dependency->m_queue) {
        return false; // TODO: throw instead??
    }

    dependent->m_dependencies.push_back(dependency);
    dependency->m_dependent.push_back(dependent);

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

void Operation::removeFromDependent(OperationQueue::op_ptr & dependency) {
    for (auto it = dependency->m_dependent.begin(); it != dependency->m_dependent.end(); ++it) {
        (*it)->removeDependency(dependency);
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

