// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Hash/Size.h"

#include "Nucleus/Hash/Memory.h"
#include "Nucleus/Memory.h"

Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashSize
    (
        const Nucleus_Size v,
        Nucleus_HashValue *hv
    )
{ return Nucleus_hashMemory((void *)&v, sizeof(Nucleus_Size), hv); }
