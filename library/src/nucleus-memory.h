/// @file nucleus-memory.h
/// @brief Allocation and deallocation or memory blocks, valuation and manipulation of memory blocks and their contents
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

#include "nucleus-annotations.h"
#include "nucleus-status.h"
#include <stdlib.h>
#include <stdbool.h>

/// @defgroup memory
/// @brief
/// allocation and deallocation of memory blocks, valuation and manipulation of memory blocks and their contents
/// @detail
/// @remark
/// A memory block is a sequence of Byte variables that are consecutively layed-out in memory.
/// As usual woth C, a pointer p to the first Byte increment by 1 will point to the second Byte, a pointer p to the second Byte increment by 1 will point to the third Byte an so on.
/// The number of Byte variables of a memory block is the size of a memory region.
///
/// @remar
/// The tasks of allocation and deallocation of memory blocks, valuation and manipulation of memory blocks and their contents are in C frequently performed over memory blocks
/// of which their sizes are specified in terms of array semantics: The memory block is considered as an array 
/// To support this frequent task the @a (*ArrayMemory) function exist for convenience. Another reason for their existence is safety: These function fail if the multiplication     of @a n
/// and @a m would overflow.

/// @ingroup memory
/// @brief Allocate a memory block of a specified size.
/// @param [out] p a pointer to a @a (void *) variable
/// @param n the size, in Bytes, of the memory block to allocate. Note that @a 0 is a valid size.
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post
/// - on success: a pointer to the first Byte of the memory block was assigned to @a (*p)
/// - on failure: @a p was not dereferenced
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateMemory
	(
		void **p,
		size_t n
	);
	
/// @ingroup memory
/// @brief Allocate a memory block of a specified size.
/// @param [out] p a pointer to a @a (void *) variable
/// @param n, m the product of @a n and @a m is the size, in Bytes, of the memory block to allocate. Note that @a 0 is a valid size.
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post
/// - on success: a pointer to the first Byte of the memory block was assigned to @a (*p)
/// - on failure: @a p was not dereferenced
/// @remark The size is specified in terms of array semantics i.e. @a n should be thought of as the array size, in elements, and @a m as the element size, in Bytes.
///         The @a *_ArrayMemory function exist for convenience as a frequent task in C program is the allocation of arrays.
///         Another reason is safety: This function fails if the product of @a n and @a m is not representable by @a size_t t.
Nucleus_NoError() Nucleus_NonNull(1) Nucleus_Status
Nucleus_allocateArrayMemory
	(
		void **p,
		size_t n,
		size_t m
	);
	
/// @ingroup memory
/// @brief Deallocate a memory block.
/// @param p a pointer to a memory block previously allocated by Nucleus_allocateMemory or Nucleus_allocateArrayMemory.
Nucleus_NoError() void
Nucleus_deallocateMemory
	(
		void *p
	);

/// @ingroup memory
/// @brief Copy the contents of a memory block to another memory block.
/// @param p a pointer to the first Byte of the target memory block
/// @param q a pointer to the first Byte of the source memory block
/// @param n the number of Byte to copy
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @remark The source and the target memory blocks may or may not overlap.
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyMemory
	(
		void *p,
		const void *q,
		size_t n
	);

/// @ingroup memory
/// @brief Copy the prefix of a memory block to a prefix of another memory block.
/// @param p a pointer to the first Byte of the target memory block
/// @param q a pointer to the first Byte of the source memory block
/// @param n the size, in elements, of the memory block array prefix to copy. Note that @a 0 is a valid size.
/// @param m the size, in Bytes, of an element of the memory block array prefix to copy. Note that @a 0 is a valid size.
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @remark The source and the target memory blocks may or may not overlap.
/// @remark The size is specified in terms of array semantics i.e. by an array size, in elements, and an element size, in Bytes.
///         This function fails if the product of @a n and @a m is not representable by @a size_t t.
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_copyArrayMemory
	(
		void *p,
		const void *q,
		size_t n,
		size_t m
	);

/// @ingroup memory
/// @brief Get if two memory blocks are equal.
/// @param p, q pointers to the memory blocks
/// @param n the size, in Bytes, of the memory blocks. Note that @a 0 is a valid size.
/// @param [out] r a pointer to a @a (bool) variable
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post
/// - on success: @a (*r) was assigned @a true if the memory regions are equal and was assigned @a false if the memory regions are not equal
/// - on failure: @a r was not dereferenced
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareMemory
	(
		const void *p,
		const void *q,
		size_t n,
		bool *r
	);

/// @ingroup memory
/// @brief Get if two memory blocks are equal.
/// @param p, q pointers to the memory blocks
/// @param n the size, in elements, of the memory blocks. Note that @a 0 is a valid size.
/// @param m the size, in Bytes, of an element of the memory blocks. Note that @a 0 is a valid size.
/// @return #Nucleus_Status_Success on success, a non-zero status code on failure
/// @post
/// - on success: @a (*r) was assigned @a true if the memory regions are equal and was assigned @a false if the memory regions are not equal
/// - on failure: @a r was not dereferenced
/// @remark The size is specified in terms of array semantics i.e. by an array size, in elements, and an element size, in Bytes.
///         This function fails if the product of @a n and @a m is not representable by @a size_t t.
Nucleus_NoError() Nucleus_NonNull(1, 2) Nucleus_Status
Nucleus_compareArrayMemory
	(
		const void *p,
		const void *q,
		size_t n,
		size_t m,
		bool *r
	);
