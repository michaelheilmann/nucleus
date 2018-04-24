#include "Nucleus.Test.DecimalInteger/Compare.h"
#include "Nucleus.Test.DecimalInteger/Add.h"
#include "Nucleus.Test.DecimalInteger/Subtract.h"
#include "Nucleus.Test.DecimalInteger/Negate.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (testComparison() || testAddition() || testSubtraction()|| testNegation()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
