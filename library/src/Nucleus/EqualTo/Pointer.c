// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/EqualTo/Pointer.h"

#include <stdint.h>

Nucleus_NoError() Nucleus_Status
Nucleus_equalToPointer
    (
        const void *v,
		const void *w,
        Nucleus_Boolean *equalTo
    )
{
    if (Nucleus_Unlikely(!equalTo)) return Nucleus_Status_InvalidArgument;
    *equalTo = (v == w);
    return Nucleus_Status_Success;
}
