// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Configuration.h"
#include "Nucleus/Status.h"
#include <wchar.h>

// One Byte in an UTF-8 string.
typedef char Nucleus_UTF8;

// Two Bytes in an UCS-16 string.
typedef wchar_t Nucleus_UCS16;

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)

// Convert a zero-terminated UCS-16 string into a zero-terminated UTF-8 string.
Nucleus_NonNull() Nucleus_Status
Nucleus_UCS16_to_UTF8
    (
        Nucleus_UTF8 **target,
        const Nucleus_UCS16 *source
    );

// Convert a zero-terminated UTF-8 string into a zero-terminated UCS-16 string.
Nucleus_NonNull() Nucleus_Status
Nucleus_UTF8_to_UCS16
    (
        Nucleus_UCS16 **target,
        const Nucleus_UTF8 *source
    );

#endif
