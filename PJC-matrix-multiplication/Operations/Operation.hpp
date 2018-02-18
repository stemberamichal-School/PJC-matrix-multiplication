//
//  Operation.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 17/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef Operation_hpp
#define Operation_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "OperationQueue.hpp"

enum class OperationState {
    Waiting,    ///< Waiting for dependencies to finish
    Ready,      ///< All dependencies finished
    Executing,  ///< Currenttly beign executed
    Finished    ///< Operation is finished and can update its dependent operations
};

/// Operation once created is in state Waiting
/// If it is added to operation queue. Its state is changed to Ready if it has no dependencies.
/// Otherwise it remains in waiting
class Operation {
private:
    /// OperationQueue to get notified about status updates.
    /// Can be nil if queue does not belong to any operation queue.
    OperationQueue * m_queue = nullptr;
    /// Current operation state
    OperationState m_state = OperationState::Waiting;

    /// Operations this depends on
    std::vector<OperationQueue::op_ptr> m_dependencies;
    /// Operations dependent on this on
    std::vector<OperationQueue::op_ptr> m_dependent;

    /// Actual work done by the operation
    virtual void work();

public:
    /// Reference to OperationQueue to update its status
    Operation();

    /// Access to private operation's state
    OperationState getState();

    /// OperationSatate setter
    void setState(OperationState newState);

    /// OperationQueue priority.
    /// Highest when ready.
    int priority();

    /// Adds dependecy on another Operation.
    /// Dependecies can't be added once the Operation was added to operation queue.
    /// In that casthe operation will return false;
    static bool addDependecy(OperationQueue::op_ptr & dependent, OperationQueue::op_ptr & dependency);

    // Remove dependecy and update state if no dependencies are necesssary to finish.
    void removeDependency(OperationQueue::op_ptr & dependency);

    /// Removes itself from all dependent operations.
    static void removeFromDependent(OperationQueue::op_ptr & dependency);

    /// Saves pointer to the queue and updates state.
    void prepareForInsertionIntoQueue(OperationQueue * queue);

    /// In the end of its execution operation has to notify queue about its completion
    virtual void execute();
};

#endif /* Operation_hpp */
