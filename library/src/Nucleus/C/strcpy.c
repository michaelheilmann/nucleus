#include "Nucleus/C/strcpy.h"

#include <string.h>

char *
C_strcpy
    (
        char *destination,
        const char *source
    )
{ return strcpy(destination, source); }
