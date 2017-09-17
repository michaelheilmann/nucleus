/// @file nucleus-memory.c
/// @brief Allocation and deallocation or memory blocks, valuation and manipulation of memory blocks and their contents
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017
#include "nucleus-memory.h"

#include <malloc.h>
#include <memory.h>



/// @brief Get if two memory regions overlap.
/// @param a pointers to the first Byte of the first memory region
/// @param b pointer to the first Byte of the second memory region
/// @param n the size of the memory region prefixes
Nucleus_NoError() Nucleus_NonNull(1, 2) static bool
overlapping
	(
		const void *a,
		const void *b,
		size_t n
	)
{
	const char *x = a, *y =  b;
    return (x <= y && x + n > y) || (y <= x && y + n > x);
}

Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateMemory
	(
		void **p,
		size_t n
	)
{
	if (!p) return Nucleus_Status_InvalidArgument;
	void *q = malloc(n > 0 ? n : 1);
	if (!q) return Nucleus_Status_AllocationFailed;
	*p = q;
	return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateArrayMemory
	(
		void **p,
		size_t n,
		size_t m
	)
{
	size_t k;
	if (!__builtin_mul_overflow(n, m, &k)) return Nucleus_Status_Overflow;
	return Nucleus_allocateMemory(p, k);
}

Nucleus_NoError() void
Nucleus_deallocateMemory
	(
		void *p
	)
{
	free(p);
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyMemory
	(
		void *p,
		const void *q,
		size_t n
	)
{
	if (!p || !q) return Nucleus_Status_InvalidArgument;
	if (overlapping(p, q, n)) memmove(p, q, n);
	else memcpy(p, q, n);
	return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyArrayMemory
	(
		void *p,
		const void *q,
		size_t n,
		size_t m
	)
{
	size_t k;
	if (!__builtin_mul_overflow(n, m, &k)) return Nucleus_Status_Overflow;
	return Nucleus_copyMemory(p, q, k);
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareMemory
	(
		const void *p,
		const void *q,
		size_t n,
		bool *r
	)
{
	if (!p || !q || !r) return Nucleus_Status_InvalidArgument;
	*r = !memcmp(p, q, n);
	return Nucleus_Status_Success;
}

Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareArrayMemory
	(
		const void *p,
		const void *q,
		size_t n,
		size_t m,
		bool *r
	)
{
	size_t k;
	if (!__builtin_mul_overflow(n, m, &k)) return Nucleus_Status_Overflow;
	return Nucleus_compareMemory(p, q, k, r);
}
