// Copyright (c) 2018 Michael Heilmann
#pragma once

#include <float.h>  // For (FLT|DBL|LDBL)_DIG.
#include <math.h>   // For INFINITY and NAN.
#include <limits.h> // For (FLT|DBL|LDBL)_MAX.

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
typedef float Nucleus_Single;

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_Least (-FLT_MAX)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_Greatest (+FLT_MAX)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_NaN (NAN)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_PositiveInfinity (+INFINITY)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_NegativeInfinity (-INFINITY)

#define Nucleus_Single_MaximumNumberOfDecimalDigits (FLT_DIG)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_GreatestExponentValueBase10 (FLT_MAX_10_EXP)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_LeastExponentValueBase10 (FLT_MIN_10_EXP)

// All machines we're aware of define this to 2 except of IBM 360 and derivatives.
#if defined(FLT_RADIX) && 2 == FLT_RADIX
    // https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
    #define Nucleus_Single_GreatestExponentValueBase2 (FLT_MAX_EXP)
    // https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
    #define Nucleus_Single_LeastExponentValueBase2 (FLT_MIN_EXP)
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
typedef double Nucleus_Double;

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_Least (-DBL_MAX)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_Greatest (+DBL_MAX)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_NaN (NAN)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_PositiveInfinity (+INFINITY)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_NegativeInfinity (-INFINITY)

#define Nucleus_Double_MaximumNumberOfDecimalDigits (DBL_DIG)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_GreatestExponentValueBase10 (DBL_MAX_10_EXP)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_LeastExponentValueBase10 (DBL_MIN_10_EXP)

// All machines we're aware of define this to 2 except of IBM 360 and derivatives.
#if defined(FLT_RADIX) && 2 == FLT_RADIX
    // https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
    #define Nucleus_Double_GreatestExponentValueBase2 (DBL_MAX_EXP)
    // https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
    #define Nucleus_Double_LeastExponentValueBase2 (DBL_MIN_EXP)
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
typedef long double Nucleus_Quadruple;

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_Least (-LDBL_MAX)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_Greatest (+LDBL_MAX)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_NaN (NAN)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_PositiveInfinity (+INFINITY)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_NegativeInfinity (-INFINITY)

#define Nucleus_Quadruple_MaximumNumberOfDecimalDigits (LDBL_DIG)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_GreatestExponentValueBase10 (LDBL_MAX_10_EXP)

// https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_LeastExponentValueBase10 (LDBL_MIN_10_EXP)

// All machines we're aware of define this to 2 except of IBM 360 and derivatives.
#if defined(FLT_RADIX) && 2 == FLT_RADIX
    // https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
    #define Nucleus_Quadruple_GreatestExponentValueBase2 (LDBL_MAX_EXP)
    // https://github.com/primordialmachine/nucleus/blob/master/documentation/Nucleus_[FloatingPointType].md
    #define Nucleus_Quadruple_LeastExponentValueBase2 (LDBL_MIN_EXP)
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
