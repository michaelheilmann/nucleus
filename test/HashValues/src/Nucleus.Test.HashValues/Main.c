// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Hash.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>

static Nucleus_Status
hashDouble
    (
    );

static Nucleus_Status
hashQuadrupleInteger
    (
    );

static Nucleus_Status
hashSize
    (
    );

static Nucleus_Status
hashDouble
    (
    )
{
    Nucleus_HashValue hv1, hv2;
    // H(-0.0) == H(+0.0)
    if (Nucleus_hashDouble(-0.0, &hv1) || Nucleus_hashDouble(+0.0f, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    // H(NAN) == H(NAN)
    if (Nucleus_hashDouble(NAN, &hv1) || Nucleus_hashDouble(NAN, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    // H(-INFINITY) != H(+INFINITY)
    if (Nucleus_hashDouble(-INFINITY, &hv1) || Nucleus_hashDouble(+INFINITY, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 != hv2)) return Nucleus_Status_InternalError;
    // H(+INFINITY) == H(+INFINITY)
    if (Nucleus_hashDouble(+INFINITY, &hv1) || Nucleus_hashDouble(+INFINITY, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    // H(-INFINITY) == H(-INFINITY)
    if (Nucleus_hashDouble(-INFINITY, &hv1) || Nucleus_hashDouble(-INFINITY, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    // H(DBL_MAX) == H(DBL_MAX)
    if (Nucleus_hashDouble(DBL_MAX, &hv1) || Nucleus_hashDouble(DBL_MAX, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    // H(DBL_MIN) == H(DBL_MIN)
    if (Nucleus_hashDouble(DBL_MIN, &hv1) || Nucleus_hashDouble(DBL_MIN, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    //
    return Nucleus_Status_Success;
}

static Nucleus_Status
hashQuadrupleInteger
    (
    )
{
    Nucleus_HashValue hv1, hv2;
    //
    if (Nucleus_hashQuadrupleInteger(Nucleus_QuadrupleInteger_Greatest, &hv1) ||
        Nucleus_hashQuadrupleInteger(Nucleus_QuadrupleInteger_Greatest, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    //
    if (Nucleus_hashQuadrupleInteger(Nucleus_QuadrupleInteger_Least, &hv1) ||
        Nucleus_hashQuadrupleInteger(Nucleus_QuadrupleInteger_Least, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    //
    return Nucleus_Status_Success;
}

static Nucleus_Status
hashSize
    (
    )
{
    Nucleus_HashValue hv1, hv2;
    //
    if (Nucleus_hashSize(Nucleus_Size_Greatest, &hv1) ||
        Nucleus_hashSize(Nucleus_Size_Greatest, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    //
    if (Nucleus_hashSize(Nucleus_Size_Least, &hv1) ||
        Nucleus_hashSize(Nucleus_Size_Least, &hv2)) return Nucleus_Status_InternalError;
    if (!(hv1 == hv2)) return Nucleus_Status_InternalError;
    //
    return Nucleus_Status_Success;
}

int main(int argc, char **argv)
{
    if (hashDouble() || hashQuadrupleInteger() || hashSize()) return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}
