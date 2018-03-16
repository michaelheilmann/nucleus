/// @file nucleus-context.h
/// @brief A library context.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

#include <stdlib.h>
#include <setjmp.h>
#include <stdbool.h>
#include "nucleus-annotations.h"

/// @brief A context.
typedef struct Nucleus_Context Nucleus_Context;

/// @brief An error handler.
typedef struct Nucleus_ErrorHandler Nucleus_ErrorHandler;

struct Nucleus_ErrorHandler
{
    Nucleus_ErrorHandler *previous;
    jmp_buf environment;
}; // struct Nucleus_ErrorHandler

struct Nucleus_Context
{
    /// @brief A null pointer or a pointer to the last element of the singly-linked list stack of @a (Nucleus_ErrorHandler) objects.
    Nucleus_ErrorHandler *errorHandlers;
    /// @brief The number of allocated memory blocks.
    size_t numberOfAllocatedBlocks;
    /// @brief The number of allocated memory bytes.
    size_t numberOfAllocatedBytes;
}; // struct Nucleus_Context

/// @brief Initialize an @a (Nucleus_Context) object.
/// @param context a pointer to the @a (Nucleus_Context) object
/// @return @a true on success, @a false on failure
Nucleus_NoError() bool
Nucleus_Context_initialize
    (
        Nucleus_Context *context
    );

/// @brief Uninitialize an @a (Nucleus_Context) object.
/// @param context a pointer to the @a (Nucleus_Context) object
Nucleus_NoError() void
Nucleus_Context_uninitialize
    (
        Nucleus_Context *context
    );

/// @brief Allocate a memory block.
/// @param context a pointer to an @a (Nucleus_Context) object
/// @param size the size, in Bytes, of the memory block to allocate. @a 0 is a valid size.
/// @return a pointer to the memory block of the specified size
Nucleus_NoError() void *
Nucleus_allocate_noError
    (
        Nucleus_Context *context,
        size_t size
    );

/// @brief Deallocate a memory block.
/// @param context a pointer to a @a (Nucleus_Context) object
/// @param pointer a pointer to the memory block
Nucleus_NoError() void
Nucleus_deallocate_noError
    (
        Nucleus_Context *context,
        void *pointer
    );

/// @brief Push an error handler on the top of the stack of error handlers.
/// @param context a pointer to the @a (Nucleus_Context) object
/// @param errorHandler a pointer to the @a (Nucleus_ErrorHandler) object
Nucleus_NoError() void
Nucleus_pushErrorHandler
    (
        Nucleus_Context *context,
        Nucleus_ErrorHandler *errorHandler
    );

/// @brief Pop an error handler from the stack of error handlers.
/// @param context a pointer to the @a (Nucleus_Context) object
/// @undefined the error handler stack of the @a (Nucleus_Context) object is empty
Nucleus_NoError() void
Nucleus_popErrorHandler
    (
        Nucleus_Context *context
    );

/// @brief Jump to the jump target on the top of the stack of jump targets.
/// @param context a pointer to the @a (Nucleus_Context) object
/// @undefined the jump target stack of the @a (Nucleus_Context) object is empty
void
Nucleus_raiseError
    (
        Nucleus_Context *context
    );
    
/// @brief The type of a Nucleus main function.
typedef void Nucleus_Main(Nucleus_Context *, int, char **);

/// @brief Execute a main function in an @a (Nucleus_Context) object.
/// @param context a pointer to the @a (Nucleus_Context) object
/// @param numberOfArguments, arguments the program arguments specified by the C ain function
/// @return @a true on success, @a false on failure
Nucleus_NoError() bool
Nucleus_runMain
    (
        Nucleus_Context *context,
        Nucleus_Main *main,
        int number_of_arguments,
        char **arguments
    );
