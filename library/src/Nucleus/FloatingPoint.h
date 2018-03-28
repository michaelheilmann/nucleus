/// @file Nucleus/FloatingPoint.h
/// @brief Support for single, double, and quad precision floating-point numbers.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#pragma once




#include <stdbool.h>
#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"




/// @defgroup FloatingPoint floating-point support
/// @brief single and double precision floating-point numbers




/// @ingroup FloatingPoint
/// @brief An alias for @a (float).
typedef float Nucleus_Single;

/// @ingroup FloatingPoint
/// @brief An alias for @a (double).
typedef double Nucleus_Double;

/// @ingroup FloatingPoint
/// @brief An alias for @a (long double).
typedef long double Nucleus_Quadruple;




// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_isSubnormal.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Single_isSubnormal
    (
        Nucleus_Single x,
        bool *r
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_isSubnormal.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Double_isSubnormal
    (
        Nucleus_Double x,
        bool *r
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_isSubnormal.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Quadruple_isSubnormal
    (
        Nucleus_Quadruple x,
        bool *r
    );




// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_isNaN.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Single_isNaN
    (
        Nucleus_Single x,
        bool *r
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_isNaN.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Double_isNaN
    (
        Nucleus_Double x,
        bool *r
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_isNaN.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Quadruple_isNaN
    (
        Nucleus_Quadruple x,
        bool *r
    );




// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_hash.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Single_hash
    (
        Nucleus_Single x,
        unsigned int *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_hash.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Double_hash
    (
        Nucleus_Double x,
        unsigned int *hv
    );

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[Floating-Point-Type]_hash.md
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Quadruple_hash
    (
        Nucleus_Quadruple x,
        unsigned int *hv
    );
