/// @file nucleus-hash-pointer.h
/// @brief Hash function for pointers.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#pragma once

#include "nucleus-annotations.h"
#include "nucleus-status.h"

/// @ingroup Hash
/// @brief Compute the hash value of a pointer.
/// @param pointer a pointer which can also be a null pointer
/// @param [out] hv a pointer to an @a (unsigned int) variable
/// @defaultReturn
/// @success @a (*hv) was assigned the hash value of the @a single value
/// @failure @a hv was not dereferenced
Nucleus_NoError() Nucleus_Status
Nucleus_hashPointer
	(
		const void *pointer,
		unsigned int *hv
	);
