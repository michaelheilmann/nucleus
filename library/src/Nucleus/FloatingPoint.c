/// @file Nucleus/FloatingPoint.h
/// @brief Support for single, double, and quad precision floating-point numbers.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "Nucleus/FloatingPoint.h"




#include <math.h>
#include "Nucleus/Memory.h"




Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_isSubnormal
    (
        Nucleus_Single x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_SUBNORMAL == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_isSubnormal
    (
        Nucleus_Double x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_SUBNORMAL == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Quadruple_isSubnormal
    (
        Nucleus_Quadruple x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_SUBNORMAL == fpclassify(x));
    return Nucleus_Status_Success;
}




Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_isNaN
    (
        Nucleus_Single x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_NAN == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_isNaN
    (
        Nucleus_Double x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_NAN == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Quadruple_isNaN
    (
        Nucleus_Quadruple x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_NAN == fpclassify(x));
    return Nucleus_Status_Success;
}




Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Single_hash
    (
        Nucleus_Single x,
        unsigned int *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    switch (fpclassify(x))
    {
        case FP_INFINITE:
        { 
            *hv = x > 0.0f ? -1 : -2;
            return Nucleus_Status_Success;
        }
        case FP_NAN:
        {
            *hv = -2;
            return Nucleus_Status_Success;
        };
        case FP_ZERO:
        { 
            *hv = 0;
            return Nucleus_Status_Success;
        }
        case FP_NORMAL:
        case FP_SUBNORMAL:
        default: // The default case handles the case when fpclassify may return an implementation defined type gracefully.
        {
            if (x == 0.0f) x = +0.0f; // +0.0f == -0.0f. Hence, map both to +0.0f.
            return Nucleus_hashMemory((const void *)&x, sizeof(Nucleus_Single), hv); // Nucleus_hashMemory fails if and only if hv is a null pointer.
                                                                                     // At this point, hv is certain to be a non-null pointer.
        }
    };
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Double_hash
    (
        Nucleus_Double x,
        unsigned int *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    switch (fpclassify(x))
    {
        case FP_INFINITE:
        { 
            *hv = x > 0.0 ? -1 : -2;
            return Nucleus_Status_Success;
        }
        case FP_NAN:
        {
            *hv = -2;
            return Nucleus_Status_Success;
        };
        case FP_ZERO:
        { 
            *hv = 0;
            return Nucleus_Status_Success;
        }
        case FP_NORMAL:
        case FP_SUBNORMAL:
        default: // The default case handles the case when fpclassify may return an implementation defined type gracefully.
        {
            if (x == 0.0) x = +0.0;    // +0.0 == -0.0. Hence, map both to +0.0.
            return Nucleus_hashMemory((const void *)&x, sizeof(Nucleus_Double), hv); // Nucleus_hashMemory fails if and only if hv is a null pointer.
                                                                                     // At this point, hv is certain to be a non-null pointer.
        }
    };
}

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_Quadruple_hash
    (
        Nucleus_Quadruple x,
        unsigned int *hv
    )
{
    if (!hv) return Nucleus_Status_InvalidArgument;
    switch (fpclassify(x))
    {
        case FP_INFINITE:
        { 
            *hv = x > 0.0 ? -1 : -2;
            return Nucleus_Status_Success;
        }
        case FP_NAN:
        {
            *hv = -2;
            return Nucleus_Status_Success;
        };
        case FP_ZERO:
        { 
            *hv = 0;
            return Nucleus_Status_Success;
        }
        case FP_NORMAL:
        case FP_SUBNORMAL:
        default: // The default case handles the case when fpclassify may return an implementation defined type gracefully.
        {
            if (x == 0.0) x = +0.0;    // +0.0 == -0.0. Hence, map both to +0.0.
            return Nucleus_hashMemory((const void *)&x, sizeof(Nucleus_Quadruple), hv); // Nucleus_hashMemory fails if and only if hv is a null pointer.
                                                                                        // At this point, hv is certain to be a non-null pointer.
        }
    };
}
