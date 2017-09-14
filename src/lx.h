#pragma once

#include <stdlib.h>
#include <setjmp.h>
#include <stdbool.h>

/// @brief A function annotation indicating that the function never raises an error.
#define lx_no_error()

/// @brief A context.
typedef struct lx_context lx_context;

/// @brief An jump target.
typedef struct lx_error_handler lx_error_handler;

struct lx_error_handler
{
	lx_error_handler *previous;
	jmp_buf environment;
}; // struct lx_error_handler

struct lx_context
{
	/// @brief A null pointer or a pointer to the last element of the singly-linked list stack of @a (lx_error_handler) objects.
	lx_error_handler *error_handlers;
	/// @brief The number of allocated memory blocks.
	size_t number_of_allocated_blocks;
	/// @brief The number of allocated memory bytes.
	size_t number_of_allocated_bytes;
}; // struct lx_context

/// @brief Initialize an @a (lx_context) object.
/// @param context a pointer to the @a (lx_context) object
/// @return @a true on success, @a false on failure
lx_no_error() bool
lx_context_initialize
	(
		lx_context *context
	);

/// @brief Uninitialize an @a (lx_context) object.
/// @param context a pointer to the @a (lx_context) object
lx_no_error() void
lx_context_uninitialize
	(
		lx_context *context
	);

/// @brief Allocate a memory block.
/// @param context a pointer to an @a (lx_context) object
/// @param size the size, in Bytes, of the memory block to allocate. @a 0 is a valid size.
/// @return a pointer to the memory block of the specified size
lx_no_error() void *
lx_allocate
	(
		lx_context *context,
		size_t size
	);

/// @brief Deallocate a memory block.
/// @param context a pointer to a @a (lx_context) object
/// @param pointer a pointer to the memory block
lx_no_error() void
lx_deallocate
	(
		lx_context *context,
		void *pointer
	);

/// @brief Push an error handler on the top of the stack of error handlers.
/// @param context a pointer to the @a (lx_context) object
/// @param error_handler a pointer to the @a (lx_error_handler) object
lx_no_error() void
lx_context_push_error_handler
	(
		lx_context *context,
		lx_error_handler *error_handler
	);

/// @brief Pop an error handler from the stack of error handlers.
/// @param context a pointer to the @a (lx_context) object
/// @undefined the error handler stack of the @a (lx_context) object is empty
lx_no_error() void
lx_context_pop_error_handler
	(
		lx_context *context
	);

/// @brief Jump to the jump target on the top of the stack of jump targets.
/// @param context a pointer to the @a (lx_context) object
/// @undefined the jump target stack of the @a (lx_context) object is empty
void
lx_context_raise_error
	(
		lx_context *context
	);
	
typedef void lx_main(lx_context *, int, char **);

/// @brief Execute a main function in an @a (lx_context) object.
/// @param context a pointer to the @a (lx_context) object
/// @param number_of_arguments, arguments the program arguments specified by the C ain function
/// @return @a true on success, @a false on failure
lx_no_error() bool
lx_context_run_main
	(
		lx_context *context,
		lx_main *main,
		int number_of_arguments,
		char **arguments
	);
