/// @file nucleus-hash-pointer.c
/// @brief Hash function for pointers.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "nucleus-hash-pointer.h"

Nucleus_NoError() Nucleus_Status
Nucleus_hashPointer
	(
		const void *pointer,
		unsigned int *hv
	)
{
	if (!hv) return Nucleus_Status_InvalidArgument;
	*hv = ((unsigned int) ((unsigned long)pointer));
	return Nucleus_Status_Success;
}
