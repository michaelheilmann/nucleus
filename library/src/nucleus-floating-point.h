/// @file nucleus-floating-point.h
/// @brief Support for single and double precision floating-point numbers.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#pragma once




#include "nucleus-annotations.h"
#include "nucleus-status.h"
#include <stdbool.h>




/// @defgroup FloatingPoint floating-point support
/// @brief single and double precision floating-point numbers




/// @ingroup FloatingPoint
/// @brief An alias for @a float.
typedef float single;




/// @ingroup FloatingPoint
/// @brief Get if a @a single value is subnormal.
/// @param x the @a single value
/// @param [out] r a pointer to an @a bool variable
/// @defaultReturn
/// @success @a (*r) was assigned @a true if the @a single value @a x is subnormal and was assigned @a false otherwise
/// @failure @a r was not dereferenced
Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_isSubnormal
	(
		single x,
		bool *r
	);

/// @ingroup FloatingPoint
/// @brief Get if a @a single value is not a number (NaN).
/// @param x the @a single value
/// @param [out] r a pointer to an @a bool variable
/// @defaultReturn
/// @success @a (*r) was assigned @a true if the @a single value @a x is NaN and is assigned @a false otherwise
/// @failure @a r was not dereferenced
Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_isNaN
	(
		single x,
		bool *r
	);

/// @ingroup FloatingPoint Hash
/// @brief Compute the hash value of a @a single value.
/// @param x the @a single value
/// @param [out] hv a pointer to an @a (unsigned int) variable
/// @defaultReturn
/// @success @a (*hv) was assigned the hash value of the @a single value
/// @failure @a hv was not dereferenced
Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Single_hash
	(
		single x,
		unsigned int *hv
	);

	


/// @ingroup FloatingPoint
/// @brief Get if a @a double value is subnormal.
/// @param x the @a double value
/// @param [out] r a pointer to an @a bool variable
/// @defaultReturn
/// @success @a (*r) was assigned @a true if the @a double value @a x is subnormal and was assigned @a false otherwise
/// @failure @a r was not dereferenced
Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_isSubnormal
	(
		double x,
		bool *r
	);

/// @ingroup FloatingPoint
/// @brief Get if a @a double value is not a number (NaN).
/// @param x the @a double value
/// @param [out] r a pointer to an @a bool variable
/// @defaultReturn
/// @success @a (*r) was assigned @a true if the @a double value @a x is NaN and is assigned @a false otherwise
/// @failure @a r was not dereferenced
Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_isNaN
	(
		double x,
		bool *r
	);

/// @ingroup FloatingPoint Hash
/// @brief Compute the hash value of a @a single value.
/// @param x the @a single value
/// @param [out] hv a pointer to an @a (unsigned int) variable
/// @defaultReturn
/// @success @a (*hv) was assigned the hash value of the @a single value
/// @failure @a hv was not dereferenced
Nucleus_NoError() Nucleus_NonNull(2) Nucleus_Status
Nucleus_Double_hash
	(
		double x,
		unsigned int *hv
	);
