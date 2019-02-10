//
//  Typedefs.hpp
//  PJC-matrix-multiplication
//
//  Created by Michal Štembera on 27/01/2019.
//  Copyright © 2019 Michal Štembera. All rights reserved.
//

#ifndef Shared_hpp
#define Shared_hpp

#include <stdio.h>

typedef float matrix_value_t;
typedef size_t matrix_size_t;

/// Four submetrixes into which original left multiplicaton operand squared matrix can be split
enum class LeftSubmatrix { a, b, c, d };
/// Four submetrixes into which original right multiplication operand squared matrix can be split
enum class RightSubmatrix { e, f, g, h };
/// Eight results of split matrix multiplications
enum class ResultSubmatrix { ae, bg, af, bh, ce, dg, cf, dh };

#endif /* Typedefs_hpp */
