#include "Nucleus.Test.DecimalInteger/Negate.h"
#include "Nucleus/DecimalInteger.h"
#include "Nucleus/Types/Integer.h"
#include "Nucleus/Types/Size.h"

typedef struct Test
{
    Nucleus_Integer64 operand;
    Nucleus_Integer64 result;
} Test;

static const Test Tests[] =
{
    //
    //{   0,  0 },
    {   1, -1 },
    {  -1,  1 },
};

static const Nucleus_Size NumberOfTests = sizeof(Tests) / sizeof(Test);

Nucleus_Status
testNegation
    (
    )
{
    Nucleus_Status status = Nucleus_Status_Success;
    for (Nucleus_Size i = 0, n = NumberOfTests; i < n; ++i)
    {
        const Test *test = &(Tests[i]);

        // Create operand.
        Nucleus_DecimalInteger *d;
        status = Nucleus_DecimalInteger_fromInteger64(&d, test->operand);
        if (status) return status;

        // Clone operand and negate clone.
        Nucleus_DecimalInteger *nd;
        status = Nucleus_DecimalInteger_clone(&nd, d);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(d);
            return status;
        }
        status = Nucleus_DecimalInteger_negate(nd);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(nd);
            Nucleus_DecimalInteger_destroy(d);
            return status;
        }

        // Create (expected) result.
        Nucleus_DecimalInteger *rd;
        status = Nucleus_DecimalInteger_fromInteger64(&rd, test->result);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(nd);
            Nucleus_DecimalInteger_destroy(d);
            return status;
        }

        // Compare negation and (expected) result.
        int r;
        status = Nucleus_DecimalInteger_compare(nd, rd, &r);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(rd);
            Nucleus_DecimalInteger_destroy(nd);
            Nucleus_DecimalInteger_destroy(d);
            return status;
        }

        Nucleus_DecimalInteger_destroy(rd);
        Nucleus_DecimalInteger_destroy(nd);
        Nucleus_DecimalInteger_destroy(d);

        if (r != 0)
        {
            status = Nucleus_Status_InternalError;
            break;
        }
    }
    return status;
}
