// Copyright (c) 2018 Michael Heilmann
#pragma once

#include <stdint.h>
#include <limits.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_Integer8_Literal(x) (x)
typedef int8_t Nucleus_Integer8;
#define Nucleus_Integer8_Least (INT8_MIN)
#define Nucleus_Integer8_Greatest (INT8_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_Integer16_Literal(x) (x)
typedef int16_t Nucleus_Integer16;
#define Nucleus_Integer16_Least (INT16_MIN)
#define Nucleus_Integer16_Greatest (INT16_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_Integer32_Literal(x) (x)
typedef int32_t Nucleus_Integer32;
#define Nucleus_Integer32_Least (INT32_MIN)
#define Nucleus_Integer32_Greatest (INT32_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_Integer64_Literal(x) (x)
typedef int64_t Nucleus_Integer64;
#define Nucleus_Integer64_Least (INT64_MIN)
#define Nucleus_Integer64_Greatest (INT64_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_QuarterInteger_Literal(x) (x)
typedef signed char Nucleus_QuarterInteger;
#define Nucleus_QuarterInteger_Least (SCHAR_MIN)
#define Nucleus_QuarterInteger_Greatest (SCHAR_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_HalfInteger_Literal(x) (x)
typedef short int Nucleus_HalfInteger;
#define Nucleus_HalfInteger_Least (SHORT_MIN)
#define Nucleus_HalfInteger_Greatest (SHORT_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_Integer_Literal(x) (x)
typedef int Nucleus_Integer;
#define Nucleus_Integer_Least (INT_MIN)
#define Nucleus_Integer_Greatest (INT_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_DoubleInteger_Literal(x) (x)
typedef long int Nucleus_DoubleInteger;
#define Nucleus_DoubleInteger_Least (LONG_MIN)
#define Nucleus_DoubleInteger_Greatest (LONG_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Nucleus_QuadrupleInteger_Literal(x) (x)
typedef long long int Nucleus_QuadrupleInteger;
#define Nucleus_QuadrupleInteger_Least (LLONG_MIN)
#define Nucleus_QuadrupleInteger_Greatest (LLONG_MAX)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
