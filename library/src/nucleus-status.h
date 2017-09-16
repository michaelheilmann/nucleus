/// @file nucleus-status.h
/// @brief Status codes.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

/// @brief Type of a value indicating the success or failure of an operation.
typedef int Nucleus_Status;

/// @brief Status code indicating success.
#define Nucleus_Status_Success (0)

/// @brief Status code indicating a failure because an invalid argument was passed.
#define Nucleus_Status_InvalidArgument (1)

/// @brief Status code indicating a failure because an allocation failed.
#define Nucleus_Status_AllocationFailed (2)

/// @brief Status code indicating a failure because an operation of the environment failed.
#define Nucleus_Status_EnvironmentFailed (3)

/// @brief Status code indicating a failure because something was already initialized.
#define Nucleus_Status_Initialized (4)

/// @brief Status code indicating a failure because something was not initialized.
#define Nucleus_Status_NotInitialized (5)

/// @brief Status code indicating a failure because something overflowed.
#define Nucleus_Status_Overflow (6)

/// @brief Status code indicating a failure because something underflowed.
#define Nucleus_Status_Underflow (7)

/// @brief Status code indicating a failure because of an internal error.
#define Nucleus_Status_InternalError (8)

/// @brief Status code indicating a failure because something exists.
#define Nucleus_Status_Exists (9)

/// @brief Status code indicating a failure because an index was out of bounds.
#define Nucleus_Status_IndexOutOfBounds (10)

/// @brief Status code indicating a failure because something is empty.
#define Nucleus_Status_Empty (11)

/// @brief Status code indicating a failure because a length was too long.
#define Nucleus_Status_TooLong (1024)