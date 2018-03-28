/// @file Nucleus/MemoryManagerInterface.h
/// @brief Interfaces for plugging-in external memory managers
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

#include <stddef.h>
#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"


/// @brief The opaque type of a "memory manager state".
typedef void Nucleus_MemoryManager_State;

/// @brief The opaque type of "memory manager allocation parameters".
typedef void Nucleus_MemoryManager_AllocationParameters;

/// @brief The opaque type of "memory manager deallocation parameters".
typedef void Nucleus_MemoryManager_DeallocationParameters;

/// @brief Type of a Nucleus "allocate" function.
/// Allocate an array of Bytes of specified number of Bytes.
/// @param [out] memoryBlock a pointer to a variable receiving the address of the first Byte of the memory block
/// @param state the memory manager state
/// @param allocationParameters the memory manager allocation parameters
/// @param numberOfBytes the number of Bytes to allocate. Zero-sized arrays of Bytes are supported i.e. @a numberOfBytes can be @a 0.
/// @defaultReturn
/// @success @a (*memoryBlock) is assigned the address of the first Byte of the memory block
/// @failure A non-zero status code is returned.
typedef Nucleus_NonNull(3) Nucleus_Status
Nucleus_MemoryManager_Allocate
    (
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_State *state),
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_AllocationParameters *allocationParameters),
        Nucleus_OutputParameter(void **memoryBlock),
        Nucleus_InputParameter(size_t numberOfBytes)
    );

/// @brief Type of a Nucleus "deallocate" function.
/// Deallocates an array of Bytes.
/// @param state the memory manager state
/// @param deallocationParameters the memory manager deallocation parameters
/// @param bytes a pointer to the first Byte of the array to deallocate
/// @remark For the sake of convenience if @a bytes is @a NULL, a call to this function returns immediatly
typedef Nucleus_NonNull(3) void 
Nucleus_MemoryManager_Deallocate
    (
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_State *state),
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_DeallocationParameters *deallocationParameters),
        Nucleus_InputParameter(void *memoryBlock)
    );
