#include "Nucleus/C/strdup.h"

#include <string.h>

char *
C_strcat
    (
        char *destination,
        const char *source
    )
{ return strcat(destination, source); }
