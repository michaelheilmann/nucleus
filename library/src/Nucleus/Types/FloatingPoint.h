// Copyright (c) Michael Heilmann 2018
#pragma once

#include <float.h>  // For (FLT|DBL|LDBL)_DIG.
#include <math.h>   // For INFINITY and NAN.
#include <limits.h> // For (FLT|DBL|LDBL)_MAX.

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
typedef float Nucleus_Single;

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_Least (-FLT_MAX)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_Greatest (+FLT_MAX)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_NaN (NAN)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_PositiveInfinity (+INFINITY)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Single_NegativeInfinity (-INFINITY)

#define Nucleus_Single_MaximumNumberOfDecimalDigits (FLT_DIG)
#define Nucleus_Single_MaximumNumberOfDecimalExponentDigits (FLT_MAX_10_EXP)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
typedef double Nucleus_Double;

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_Least (-DBL_MAX)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_Greatest (+DBL_MAX)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_NaN (NAN)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_PositiveInfinity (+INFINITY)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Double_NegativeInfinity (-INFINITY)

#define Nucleus_Double_MaximumNumberOfDecimalDigits (DBL_DIG)
#define Nucleus_Double_MaximumNumberOfDecimalExponentDigits (DBL_MAX_10_EXP)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
typedef long double Nucleus_Quadruple;

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_Least (-LDBL_MAX)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_Greatest (+LDBL_MAX)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_NaN (NAN)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_PositiveInfinity (+INFINITY)

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_[FloatingPointType].md
#define Nucleus_Quadruple_NegativeInfinity (-INFINITY)

#define Nucleus_Quadruple_MaximumNumberOfDecimalDigits (LDBL_DIG)
#define Nucleus_Quadruple_MaximumNumberOfDecimalExponentDigits (LDBL_MAX_10_EXP)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
