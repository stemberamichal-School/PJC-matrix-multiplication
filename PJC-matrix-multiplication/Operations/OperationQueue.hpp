//
//  OperationQueue.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 17/02/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef OperationQueue_hpp
#define OperationQueue_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

class Operation;
enum class OperationState;
class OperationResource;

template class std::shared_ptr<Operation>; // Prevent from inlining
template class std::vector<std::shared_ptr<Operation>>; // Prevent from inlining

class OperationQueue {
public:
    using op_ptr = std::shared_ptr<Operation>;
    
private:
    /// Compares two operations and returns if the first has higher priority
    struct PriorityComparator {
        bool operator()(const op_ptr& lhs, const op_ptr& rhs);
    };
    /// Compares if the shared_ptr points to same address as given pointer
    struct PointerPredicate {
        Operation const * const m_ptr;
        bool operator()(const op_ptr& check);
        PointerPredicate(Operation * const op);
    };

    /// Lock which must be locked when making changes to the operation queue
    std::mutex m_queueLock;
    /// Condition variable to keep waiting for work to be added
    std::condition_variable m_queueCondVar;
    /// Max heap storing operations
    std::vector<op_ptr> m_queueHeap;
    /// Operations currenlty being executed
    std::vector<op_ptr> m_executing;
    /// Compares by priority and returns true if first has higher, false otherwise
    PriorityComparator m_cmp;
    /// Internal function which can insert to already locked queue
    template<class InputIterator>
    void __unlockedInsertOperations(InputIterator first,
                                    InputIterator end) {
        // Update for insertion to queue
        for(auto it = first; it != end; ++it) {
            (*it)->prepareForInsertionIntoQueue(this);
        }
        // After that we lock the queue and insert operations
        m_queueHeap.insert(m_queueHeap.end(), first, end);
        std::make_heap(m_queueHeap.begin(), m_queueHeap.end(), m_cmp);
    }

    /// Checks if there are no operations in queue or executing
    bool hasFinished() const;
    /// Checks if there is at least one operation in queue in state Ready
    bool hasReadyOperation() const;

public:
    /// Retrives next element from the queue
    /// If there are no more operations ends returns nil
    /// Waits on conditional variable for solving dependecies if all operations are Waiting.
    op_ptr next();

    /// Updates operations state within the queue. Can be used to finish operation
    void operationDidFinish(Operation * operation);

    /// Inserts single operation into the operation queue
    /// Reorders operation queue
    /// Notifies waiting threads through condition variable
    void insertOperation(op_ptr op);

    /// Insert multiple operations into operation queue
    /// Reorders operation queue
    /// Notifies waiting threads throuhgh condition variable
    template<class InputIterator>
    void insertOperations(InputIterator first, InputIterator end) {
        // Update for insertion to queue
        for(auto it = first; it != end; ++it) {
            (*it)->prepareForInsertionIntoQueue(this);
        }
        // After that we lock the queue and insert operations
        {
            std::unique_lock<std::mutex> lk(m_queueLock);
            m_queueHeap.insert(m_queueHeap.end(), first, end);
            std::make_heap(m_queueHeap.begin(), m_queueHeap.end(), m_cmp);
        }
        m_queueCondVar.notify_all();
    }
};

#endif /* OperationQueue_hpp */
