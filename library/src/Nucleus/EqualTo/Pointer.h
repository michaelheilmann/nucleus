// Copyright (c) 2018 Michael Heilmann
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include "Nucleus/Types/Boolean.h"

/// @ingroup EqualTo
/// @brief Get if two pointers are equal.
/// @param v, w pointer values which can also be null pointer values
/// @param [out] equalTo a pointer to an @a (Nucleus_Boolean) variable
/// @defaultReturn
/// @success @a (*equalTo) is assigned @a (Nucleus_Boolean_True) if @a v and @a w are equal and
///          is assigned @a (Nucleus_Boolean_False) if @a v and @a w are not equal
/// @failure @a equalTo was not dereferenced
Nucleus_NoError() Nucleus_Status
Nucleus_equalToPointer
    (
        const void *v,
		const void *w,
        Nucleus_Boolean *equalTo
    );
