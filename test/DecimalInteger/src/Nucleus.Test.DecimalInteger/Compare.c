#include "Nucleus.Test.DecimalInteger/Compare.h"
#include "Nucleus/DecimalInteger.h"
#include "Nucleus/Types/Integer.h"
#include "Nucleus/Types/Size.h"

typedef struct Test
{
    Nucleus_Integer64 operand1;
    Nucleus_Integer64 operand2;
    Nucleus_Integer result;
} Test;

static const Test Tests[] =
{
    //
    {  0,   0,  0 },
    //
    {  0,   1, -1 },
    {  1,   0,  1 },
    {  1,   1,  0 },
    //
    {   0, -1,  1 },
    {  -1,  0, -1 },
    {  -1, -1,  0 },
};

static const Nucleus_Size NumberOfTests = sizeof(Tests) / sizeof(Test);

Nucleus_Status
testComparison
    (
    )
{
    Nucleus_Status status = Nucleus_Status_Success;
    for (Nucleus_Size i = 0, n = NumberOfTests; i < n; ++i)
    {
        const Test *test = &(Tests[i]);

        // Create operands
        Nucleus_DecimalInteger *operand1;
        status = Nucleus_DecimalInteger_fromInteger64(&operand1, test->operand1);
        if (status) return status;
        Nucleus_DecimalInteger *operand2;
        status = Nucleus_DecimalInteger_fromInteger64(&operand2, test->operand2);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(operand1);
            return status;
        }
        // Compare operands.
        int r;
        status = Nucleus_DecimalInteger_compare(operand1, operand2, &r);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(operand2);
            Nucleus_DecimalInteger_destroy(operand1);
            return status;
        }

        Nucleus_DecimalInteger_destroy(operand2);
        Nucleus_DecimalInteger_destroy(operand1);

        if (r != test->result)
        {
            status = Nucleus_Status_InternalError;
            break;
        }
    }
    return status;
}
