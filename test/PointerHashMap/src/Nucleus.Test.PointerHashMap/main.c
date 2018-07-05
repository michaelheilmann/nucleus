// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/Collections/PointerHashMap.h"
#include "Nucleus.Test.PointerHashMap/testCollection.h"
#include "Nucleus.Test.PointerHashMap/testGetSet.h"
#include "Nucleus.Test.PointerHashMap/testConstantEnumerator.h"
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
