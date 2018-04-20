#include "Nucleus/stringToBoolean.h"

#include "Nucleus/Memory.h"

Nucleus_NonNull() Nucleus_Status
Nucleus_stringToBoolean
    (
        const char *bytes,
        Nucleus_Size numberOfBytes,
        Nucleus_Boolean *value
    )
{
    if (Nucleus_Unlikely(!bytes || !value)) return Nucleus_Status_InvalidArgument;
    switch (numberOfBytes)
    {
        case sizeof("true") - sizeof(char):
        {
            Nucleus_Status status;
            bool equal;
            status = Nucleus_compareMemory(bytes, "true", sizeof("true") - sizeof(char), &equal);
            if (status) return status;
            *value = Nucleus_Boolean_True;
            return Nucleus_Status_Success;
        } break;
        case sizeof("false") - sizeof(char):
        {
            Nucleus_Status status;
            bool equal;
            status = Nucleus_compareMemory(bytes, "false", sizeof("false") - sizeof(char), &equal);
            if (status) return status;
            *value = Nucleus_Boolean_False;
            return Nucleus_Status_Success;
        } break;
        default:
        {
            return Nucleus_Status_ConversionFailed;
        } break;
    };
}
