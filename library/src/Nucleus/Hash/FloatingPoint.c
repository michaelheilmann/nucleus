// Copyright (c) Michael Heilmann 2018
#include "Nucleus/Hash/FloatingPoint.h"

#include <math.h>
#include "Nucleus/Hash/Memory.h"

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashSingle
    (
        Nucleus_Single x,
        Nucleus_HashValue *hv
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
            *hv = -3;
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
Nucleus_hashDouble
    (
        Nucleus_Double x,
        Nucleus_HashValue *hv
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
            *hv = -3;
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
Nucleus_hashQuadruple
    (
        Nucleus_Quadruple x,
        Nucleus_HashValue *hv
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
            *hv = -3;
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
