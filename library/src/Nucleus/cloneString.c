// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/cloneString.h"

#include <string.h> // For "strdup"/"_strdup".

Nucleus_NonNull() Nucleus_Status
Nucleus_cloneString
    (
        char **result,
        const char *string
    )
{
    if (Nucleus_Unlikely(!result || !string))
    { return Nucleus_Status_InvalidArgument; }

#if (Nucleus_C_Compiler == Nucleus_C_Compiler_MSVC)
    char *temporary = _strdup(string);
#else
    char *temporary = strdup(string);
#endif
    if (Nucleus_Unlikely(!temporary))
    { return Nucleus_Status_AllocationFailed; }

    *result = temporary;

    return Nucleus_Status_Success;
}
