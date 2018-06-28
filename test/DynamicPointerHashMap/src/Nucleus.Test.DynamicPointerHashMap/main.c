// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerHashMap.h"
#include "Nucleus.Test.DynamicPointerHashMap/testCollection.h"
#include "Nucleus.Test.DynamicPointerHashMap/testGetSet.h"
#include "Nucleus.Test.DynamicPointerHashMap/testConstantEnumerator.h"
#include <stdlib.h>

int
main
    (
        int argc,
        char **argv
    )
{
    if (testCollection() || testGetSet() || testConstantEnumerator()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
