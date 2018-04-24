#include "Nucleus.Test.DecimalInteger/Add.h"
#include "Nucleus/DecimalInteger.h"
#include "Nucleus/Types/Integer.h"
#include "Nucleus/Types/Size.h"

typedef struct Test
{
    Nucleus_Integer64 operand1;
    Nucleus_Integer64 operand2;
    Nucleus_Integer64 result;
} Test;

static const Test Tests[] =
{
    //
    {  0,  0,  0 },
    //
    {  0,  1,  1 },
    {  1,  0,  1 },
    {  1,  1,  2 },
    //
    {  0, -1, -1 },
    { -1,  0, -1 },
    { -1, -1, -2 },
    //
    {  1, -1,  0 },
    { -1,  1,  0 },
};

static const Nucleus_Size NumberOfTests = sizeof(Tests) / sizeof(Test);

Nucleus_Status
testAddition
    (
    )
{
    Nucleus_Status status = Nucleus_Status_Success;
    for (Nucleus_Size i = 0, n = NumberOfTests; i < n; ++i)
    {
        const Test *test = &(Tests[i]);
        const int x = test->operand1;
        const int y = test->operand2;
        Nucleus_DecimalInteger *dx, *dy;

        status = Nucleus_DecimalInteger_fromInteger64(&dx, x);
        if (status) return status;
        status = Nucleus_DecimalInteger_fromInteger64(&dy, y);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(dx);
            return status;
        }
        status = Nucleus_DecimalInteger_add(dx, dy);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(dy);
            Nucleus_DecimalInteger_destroy(dx);
            return status;
        }
        Nucleus_DecimalInteger *dr;
        status = Nucleus_DecimalInteger_fromInteger64(&dr, test->result);
        if (status)
        {
            Nucleus_DecimalInteger_destroy(dy);
            Nucleus_DecimalInteger_destroy(dx);
            return status;
        }
        Nucleus_DecimalInteger_destroy(dy);
        Nucleus_DecimalInteger_destroy(dx);
    }
    return status;
}
