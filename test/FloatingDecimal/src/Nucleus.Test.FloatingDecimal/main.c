#include "Nucleus/DecimalFloat.h"
#include <stdlib.h>
#include <string.h>

typedef struct Test
{
    const char *inputString;
    Nucleus_Boolean isNaN;
    Nucleus_Boolean isPositiveInfinity;
    Nucleus_Boolean isNegativeInfinity;
    Nucleus_Size numberOfDigits;
    Nucleus_Integer64 exponent;
} Test;

static const Test Tests[] =
{
    { "NaN",  true,  false, false,  -1 },
    { "+Inf", false, true,  false,  -1 },
    { "-Inf", false, false, true,   -1 },
    { "Inf",  false, true,  false,  -1 },
    //
    { "0.0",   false, false, false,  +1, 0 },
    { "0.00",  false, false, false,  +1, 0 },
    { "00.0",  false, false, false,  +1, 0 },
    { "00.00", false, false, false,  +1, 0 },
    //
    { "10.1",   false, false, false,  +3, -1 },
    { "10.10",  false, false, false,  +3, -1 },
    { "010.1",  false, false, false,  +3, -1 },
    { "010.10", false, false, false,  +3, -1 },
};

static const Nucleus_Size NumberOfTests = sizeof(Tests) / sizeof(Test);

static Nucleus_Status
test
    (
    )
{
    Nucleus_Status status = Nucleus_Status_Success;
    for (Nucleus_Size i = 0, n = NumberOfTests; i < n; ++i)
    {
        const Test *test = &(Tests[i]);
        const char *inputString = test->inputString;
        const Nucleus_Size inputStringLength = strlen(test->inputString);

        Nucleus_DecimalFloat *decimalFloat;
        status = Nucleus_DecimalFloat_create_fromString(&decimalFloat, inputString, inputStringLength);
        if (status) return status;

        // Check if NaN.
        Nucleus_Boolean isNaN;
        status = Nucleus_DecimalFloat_isNaN(decimalFloat, &isNaN);
        if (status) goto End;
        if (isNaN != test->isNaN) { status = Nucleus_Status_InternalError; goto End; }

        // Check if +Infinity.
        Nucleus_Boolean isPositiveInfinity;
        status = Nucleus_DecimalFloat_isPositiveInfinity(decimalFloat, &isPositiveInfinity);
        if (status) goto End;
        if (isPositiveInfinity != test->isPositiveInfinity) { status = Nucleus_Status_InternalError; goto End; }

        // Check if -Infinity.
        Nucleus_Boolean isNegativeInfinity;
        status = Nucleus_DecimalFloat_isNegativeInfinity(decimalFloat, &isNegativeInfinity);
        if (status) goto End;
        if (isNegativeInfinity != test->isNegativeInfinity) { status = Nucleus_Status_InternalError; goto End; }

        // If neither NaN nor Infinity ...
        if (!isNaN && !isPositiveInfinity && !isNegativeInfinity)
        {
            // ... assert the number of digits is proper.
            if (decimalFloat->numberOfDigits != test->numberOfDigits) { status = Nucleus_Status_InternalError; goto End; }
            if (decimalFloat->exponent != test->exponent) { status = Nucleus_Status_InternalError; goto End; }
        }

End:
        Nucleus_DecimalFloat_destroy(decimalFloat);
        if (status) break;
    }
    return status;
}

int main(int argc, char **argv)
{
    if (test()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
