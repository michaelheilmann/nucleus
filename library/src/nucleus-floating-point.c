/// @file nucleus-hash.h
/// @brief Support for single and double precision floating-point numbers.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "nucleus-floating-point.h"




#include <math.h>
#include "nucleus-memory.h"




Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_isSubnormal
    (
        single x,
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
        single x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_NAN == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_hash
    (
        single x,
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
        case FP_NORMAL:
        case FP_SUBNORMAL:
        {
            if (x == 0.0f) x = +0.0f; // +0.0f == -0.0f. Hence, map both to +0.0f.
            return Nucleus_hashMemory((const void *)&x, sizeof(single), hv);
        }
        case FP_ZERO:
        { 
            *hv = 0;
            return Nucleus_Status_Success;
        }
        default: exit(EXIT_FAILURE); /// @todo Use Nucleus_unreachableCodeReached.
    };
}




Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_isSubnormal
    (
        double x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_SUBNORMAL == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_isNaN
    (
        double x,
        bool *r
    )
{
    if (!r) return Nucleus_Status_InvalidArgument;
    (*r) = (FP_NAN == fpclassify(x));
    return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_hash
    (
        double x,
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
        case FP_NORMAL:
        case FP_SUBNORMAL:
        {
            if (x == 0.0) x = +0.0;    // +0.0 == -0.0. Hence, map both to +0.0.
            return Nucleus_hashMemory((const void *)&x, sizeof(double), hv);
        }
        case FP_ZERO:
        { 
            *hv = 0;
            return Nucleus_Status_Success;
        }
        default: exit(EXIT_FAILURE); /// @todo Use Nucleus_unreachableCodeReached.
    };
}
