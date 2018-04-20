#include "Nucleus/booleanToString.h"
#include "Nucleus/stringToBoolean.h"
#include "Nucleus/Memory.h"
#include <stdlib.h>


Nucleus_NonNull(3) static Nucleus_Status
allocate
    (
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_State *state),
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_AllocationParameters *allocationParameters),
        Nucleus_OutputParameter(void **memoryBlock),
        Nucleus_InputParameter(size_t numberOfBytes)
    );

Nucleus_NonNull(3) static void 
deallocate
    (
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_State *state),
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_DeallocationParameters *deallocationParameters),
        Nucleus_InputParameter(void *memoryBlock)
    );

static Nucleus_Status
testTrue
    (
    );

static Nucleus_Status
testFalse
    (
    );

Nucleus_NonNull(3) static Nucleus_Status
allocate
    (
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_State *state),
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_AllocationParameters *allocationParameters),
        Nucleus_OutputParameter(void **memoryBlock),
        Nucleus_InputParameter(size_t numberOfBytes)
    )
{ return Nucleus_allocateMemory(memoryBlock, numberOfBytes); }

Nucleus_NonNull(3) static void 
deallocate
    (
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_State *state),
        Nucleus_InputOutputParameter(Nucleus_MemoryManager_DeallocationParameters *deallocationParameters),
        Nucleus_InputParameter(void *memoryBlock)
    )
{ Nucleus_deallocateMemory(memoryBlock); }

static Nucleus_Status
testTrue
    (
    )
{
    Nucleus_Status status;
    char *bytes;
    Nucleus_Boolean equal;
    Nucleus_Size numberOfBytes;
    status = Nucleus_booleanToString(Nucleus_Boolean_True, &bytes, &numberOfBytes, NULL, &allocate, &deallocate);
    if (status) return status;
    if (numberOfBytes != sizeof("true")-sizeof(char))
    {
        Nucleus_deallocateMemory(bytes);
        return Nucleus_Status_InternalError;
    }
    status = Nucleus_compareMemory(bytes, "true", sizeof("true") - sizeof(char), &equal);
    if (status) 
    {
        Nucleus_deallocateMemory(bytes);
        return Nucleus_Status_InternalError;
    }
    if (!equal)
    {
        Nucleus_deallocateMemory(bytes);
        return Nucleus_Status_InternalError;
    }
    Nucleus_Boolean value;
    status = Nucleus_stringToBoolean(bytes, numberOfBytes, &value);
    Nucleus_deallocateMemory(bytes);
    if (status) return status;
    if (value != Nucleus_Boolean_True) return Nucleus_Status_InternalError;
    return Nucleus_Status_Success;
}

static Nucleus_Status
testFalse
    (
    )
{
    Nucleus_Status status;
    char *bytes;
    Nucleus_Boolean equal;
    Nucleus_Size numberOfBytes;
    status = Nucleus_booleanToString(Nucleus_Boolean_False, &bytes, &numberOfBytes, NULL, &allocate, &deallocate);
    if (status) return status;
    if (numberOfBytes != sizeof("false")-sizeof(char))
    {
        Nucleus_deallocateMemory(bytes);
        return Nucleus_Status_InternalError;
    }
    status = Nucleus_compareMemory(bytes, "false", sizeof("false") - sizeof(char), &equal);
    if (status) 
    {
        Nucleus_deallocateMemory(bytes);
        return Nucleus_Status_InternalError;
    }
    if (!equal)
    {
        Nucleus_deallocateMemory(bytes);
        return Nucleus_Status_InternalError;
    }
    Nucleus_Boolean value;
    status = Nucleus_stringToBoolean(bytes, numberOfBytes, &value);
    Nucleus_deallocateMemory(bytes);
    if (status) return status;
    if (value != Nucleus_Boolean_False) return Nucleus_Status_InternalError;
    return Nucleus_Status_Success;
}

int main(int argc, char **argv)
{
    if (testTrue() || testFalse()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
