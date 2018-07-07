#include "Nucleus/C/strdup.h"

#include <string.h>

char *
C_strdup
    (
        const char *string
    )
{
    if (!string) return NULL;
#if (_MSC_VER)
    return _strdup(string);
#else
    return strdup(string);
#endif
}