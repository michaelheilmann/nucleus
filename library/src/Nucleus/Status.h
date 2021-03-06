/// @file Nucleus/Status.h
/// @brief Status codes.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann

#pragma once




/// @brief Type of a value indicating the success or failure of an operation.
typedef int Nucleus_Status;




/// @brief Status codes are assigned cateogies.
typedef enum Nucleus_Status_Category
{
    /// @brief Status code category for general status codes.
    Nucleus_Status_Category_General = 0,

    /// @brief Status code category for aggregate-related status codes.
    Nucleus_Status_Category_Aggregate = 1000,

    /// @brief Status code category for memory-related status codes.
    Nucleus_Status_Category_Memory = 2000,

    /// @brief Status code category for concurrency-related status codes.
    Nucleus_Status_Category_Concurrency = 3000,

    /// @brief Status code category for conversion-related status codes.
    Nucleus_Status_Category_Conversion = 4000,

    /// @brief Status code category for input/output-related status codes.
    Nucleus_Status_Category_InputOutput = 5000,

} Nucleus_Status_Category;




/// @brief Status code indicating success.
#define Nucleus_Status_Success (Nucleus_Status_Category_General | 0)




/// @brief Status code indicating a failure because an invalid argument was passed.
#define Nucleus_Status_InvalidArgument (Nucleus_Status_Category_General | 1)

/// @brief Status code indicating a failure because something was already initialized.
#define Nucleus_Status_Initialized (Nucleus_Status_Category_General | 2)

/// @brief Status code indicating a failure because something was not initialized.
#define Nucleus_Status_NotInitialized (Nucleus_Status_Category_General | 3)

/// @brief Status code indicating a failure because something overflowed.
#define Nucleus_Status_Overflow (Nucleus_Status_Category_General | 4)

/// @brief Status code indicating a failure because something underflowed.
#define Nucleus_Status_Underflow (Nucleus_Status_Category_General | 5)

/// @brief Status code indicating a failure because of an internal error.
#define Nucleus_Status_InternalError (Nucleus_Status_Category_General | 6)

/// @brief Status code indicating a failure because something exists.
#define Nucleus_Status_Exists (Nucleus_Status_Category_General | 7)
/// @brief Status code indicating that something not exists.
#define Nucleus_Status_NotExists (Nucleus_Status_Category_General | 8)

/// @brief Status code indicating that something is found.
#define Nucleus_Status_Found (Nucleus_Status_Category_General | 9)
/// @brief Status code indicating that something is not found.
#define Nucleus_Status_NotFound (Nucleus_Status_Category_General | 10)

/// @brief Status code indicating that something is open.
#define Nucleus_Status_Open (Nucleus_Status_Category_General | 11)
/// @brief Status code indicating that something is not open.
#define Nucleus_Status_NotOpen (Nucleus_Status_Category_General | 12)

/// @brief Status code indicating a failure because a length was too long.
#define Nucleus_Status_TooLong (Nucleus_Status_Category_General | 13)

/// @brief Status code indicating a failure because an operation of the environment failed.
#define Nucleus_Status_EnvironmentFailed (Nucleus_Status_Category_General | 14)

/// @brief Status code indicating a failure because a functionality is not currently/yet available.
#define Nucleus_Status_NotAvailable (Nucleus_Status_Category_General | 15)



/// @ingroup Aggregate
/// @brief Status code indicating a failure because an aggregate is empty.
#define Nucleus_Status_Empty (Nucleus_Status_Category_Aggregate | 1)

/// @ingroup Aggregate
/// @brief Status code indicating a failure because an index into an index-based aggregate is out of bounds.
#define Nucleus_Status_IndexOutOfBounds (Nucleus_Status_Category_Aggregate | 1)




/// @ingroup Conversion
/// @brief Status code indicating a failure because a conversion failed.
#define Nucleus_Status_ConversionFailed (Nucleus_Status_Category_Conversion | 1)




/// @ingroup Memory
/// @brief Status code indicating a failure because an allocation failed.
#define Nucleus_Status_AllocationFailed  (Nucleus_Status_Category_Memory | 1)




/// @ingroup Concurrency
/// @brief Status code indicating a failure because something (e.g. a mutex) is already locked.
#define Nucleus_Status_AlreadyLocked (Nucleus_Status_Category_Concurrency | 1)

/// @ingroup Concurrency
/// @brief Status code indicating a failure because something (e.g. a thread) was already started.
#define Nucleus_Status_AlreadyStarted (Nucleus_Status_Category_Concurrency | 4)

/// @ingroup Concurrency
/// @brief Status code indicating a failure because something (e.g. a thread) was not started.
#define Nucleus_Status_NotStarted (Nucleus_Status_Category_Concurrency | 8)

/// @ingroup Concurrency
/// @brief Status code indicating a failure because something (e.g. a thread) was already stopped.
#define Nucleus_Status_AlreadyStopped (Nucleus_Status_Category_Concurrency | 16)




/// @ingroup InputOutput
/// @brief Status code indicating a write error.
#define Nucleus_Status_WriteError (Nucleus_Status_Category_InputOutput | 1)

/// @ingroup InputOutput
/// @brief Status code indicating a read error.
#define Nucleus_Status_ReadError  (Nucleus_Status_Category_InputOutput | 2)

/// @ingroup InputOutput
/// @brief Status code indicating a failure because a file exists.
#define Nucleus_Status_FileExists (Nucleus_Status_Category_InputOutput | 3)

/// @ingroup InputOutput
/// @brief Status code indicating a failure because a file does not exist.
#define Nucleus_Status_FileDoesNotExist (Nucleus_Status_Category_InputOutput | 4)

/// @ingroup InputOutput
/// @brief Status code indicating a failure because a file is closed.
#define Nucleus_Status_FileClosed (Nucleus_Status_Category_InputOutput | 5)
