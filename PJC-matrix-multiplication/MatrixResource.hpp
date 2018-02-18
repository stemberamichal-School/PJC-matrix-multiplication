//
//  MatrixResource.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 28/01/2018.
//  Copyright © 2018 Michal Štembera. All rights reserved.
//

#ifndef MatrixResource_hpp
#define MatrixResource_hpp

#include <stdio.h>
#include <memory>
#include "MatrixBase.hpp"

/// Representation of solution of one matrix multiply
struct MatrixMultiplication {
    /// Matrix which is being mutliplied
    const MatrixBase& left;
    /// Matrix by which is being multiplied
    const MatrixBase& right;
    /// Result of the multiplication
    MatrixBase& result;

    MatrixMultiplication(const MatrixBase& left, const MatrixBase& right);
};

/// Closed Interval between given values
template <typename T>
struct Interval {
    /// Lower bound of the interval's values
    T lower;
    /// Upper bound of the interval's values
    T upper;

    // Trims number to the interval
    T trim(T number) const {
        return max(lower, min(upper, number));
    }
    /// Generates random number in between the interval
    T random() const {
        static std::mt19937 mt{ std::random_device{}() };
        static std::uniform_real_distribution<> dist(lower, upper);
        T number = (T) dist(mt);
        return trim(number);
    }
};

/// Factory for matrixes
template <typename T>
class MatrixFactory {
    const size_t numberOfMatrixes;
    size_t generated = 0;
    bool adhocGeneration;
    Interval<T> rowSpan;
    Interval<T> columnSpan;
    Matrix<T> * const matrixes;

    Matrix<T> randomMatrix() const;
public:
    MatrixFactory(size_t numberOfMatrixes,
                  Interval<size_t> rowSpan,
                  Interval<size_t> columnSpan,
                  bool adhocGeneration = true);
};

template<typename T>
MatrixFactory<T>::MatrixFactory(size_t numberOfMatrixes,
                                Interval<size_t> rowSpan,
                                Interval<size_t> columnSpan,
                                bool adhocGeneration)
    :numberOfMatrixes(numberOfMatrixes),
    rowSpan(rowSpan),
    columnSpan(columnSpan),
    adhocGeneration(adhocGeneration) {
        if(!adhocGeneration) {
            for(std::size_t i = 0; i < numberOfMatrixes; ++i) {

            }
        }
    };
#endif /* MatrixResource_hpp */


