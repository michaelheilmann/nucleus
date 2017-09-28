/// @file nucleus-hash-pointer.h
/// @brief Hash functions for pointer values.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#pragma once

#include "nucleus-annotations.h"
#include "nucleus-status.h"

/// @ingroup Hash
/// @brief Compute the hash value of a pointer value.
/// @param v a pointer value which can also be a null pointer value
/// @param [out] hv a pointer to an @a (unsigned int) variable
/// @defaultReturn
/// @success @a (*hv) was assigned the hash value of the @a v value
/// @failure @a hv was not dereferenced
Nucleus_NoError() Nucleus_Status
Nucleus_hash_pointer_to_unsignedInt
	(
		const void *v,
		unsigned int *hv
	);

/// @ingroup Hash
/// @brief Compute the hash value of a pointer value.
/// @param v a pointer value which can also be a null pointer value
/// @param [out] hv a pointer to an @a (signed long long) variable
/// @defaultReturn
/// @success @a (*hv) was assigned the hash value of the @a v value
/// @failure @a hv was not dereferenced
Nucleus_NoError() Nucleus_Status
Nucleus_hash_pointer_to_signedLongLongInt
	(
		const void *v,
		signed long long int *hv
	);
