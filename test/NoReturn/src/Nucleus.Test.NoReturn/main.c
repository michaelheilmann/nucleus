#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include <stdlib.h>

Nucleus_NoReturn() void g()
{
    exit(EXIT_FAILURE);
}

int f(int i)
{
    if (i == 0)
    {
        return 0;
    }
    else if (i == 1)
    {
        return 1;
    }
    else
    {
        g();
    }
}

Nucleus_Status test()
{
    f(0);
    return Nucleus_Status_Success;
}

int main(int argc, char **argv)
{
    if (test()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
