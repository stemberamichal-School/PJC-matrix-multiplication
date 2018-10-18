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
    /// Max heap storing operations
    std::vector<op_ptr> m_queueHeap;
    /// Operations currenlty being executed
    std::vector<op_ptr> m_executing;
    /// Compares by priority and returns true if first has higher, false otherwise
    PriorityComparator m_cmp;
    /// Resource to supply work when runs out of operations
    std::weak_ptr<OperationResource> m_operationResource;
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

public:
    /// Sets resource for additional operations when current are finished/waiting.
    void setOperationResource(std::weak_ptr<OperationResource> & operationResource);

    /// Retrives next element from the queue
    /// If there are no more operations ends returns nil
    /// Waits on conditional variable for solving dependecies if all operations are Waiting.
    op_ptr next();

    /// Updates operations state within the queue. Can be used to finish operation
    void operationDidFinish(Operation * operation);

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
        std::lock_guard<std::mutex> lk(m_queueLock);
        m_queueHeap.insert(m_queueHeap.end(), first, end);
        std::make_heap(m_queueHeap.begin(), m_queueHeap.end(), m_cmp);
    }
};

#endif /* OperationQueue_hpp */
