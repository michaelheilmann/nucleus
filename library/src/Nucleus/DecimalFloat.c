// Copyright (c) Michael Heilmann 2018
#include "Nucleus/DecimalFloat.h"

#include "Nucleus/Types/Boolean.h"
#include "Nucleus/Types/Integer.h"
#include "Nucleus/Memory.h"
#include "Nucleus/SafeArithmeticOperations.h"
#include <setjmp.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Parser
{
    const char *begin;
    const char *end;
    const char *current;
    jmp_buf environment;
} Parser; // struct Parser

Nucleus_NoError() Nucleus_NonNull() static inline char
current
    (
        const Parser *parser
    );

Nucleus_NoError() Nucleus_NonNull() static inline void
increment
    (
        Parser *parser
    );

Nucleus_NoError() Nucleus_NonNull() static inline char
is
    (
        const Parser *parser,
        char character
    );

Nucleus_NoError() Nucleus_NonNull() static inline void
expectAndNext
    (
        Parser *parser,
        char character
    );

Nucleus_NoError() Nucleus_NonNull() static inline bool
isExponentCharacter
    (
        const Parser *parser
    );

Nucleus_NoError() Nucleus_NonNull() static inline bool
isPlus
    (
        const Parser *parser
    );

Nucleus_NoError() Nucleus_NonNull() static inline bool
isMinus
    (
        const Parser *parser
    );

Nucleus_NoError() Nucleus_NonNull() static inline bool
isDigit
    (
        const Parser *parser
    );

Nucleus_NoError() Nucleus_NonNull() static inline bool
isDecimalSeparator
    (
        const Parser *parser
    );

Nucleus_NoError() Nucleus_NonNull() static inline bool
isEnd
    (
        const Parser *parser
    );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Nucleus_NoError() Nucleus_NonNull() static inline char
current
    (
        const Parser *parser
    )
{ return *parser->current; }

Nucleus_NoError() Nucleus_NonNull() static inline void
increment
    (
        Parser *parser
    )
{ parser->current++; }

Nucleus_NoError() Nucleus_NonNull() static inline char
is
    (
        const Parser *parser,
        char character
    )
{ return character == *parser->current; }

Nucleus_NoError() Nucleus_NonNull() static inline void
expectAndNext
    (
        Parser *parser,
        char character
    )
{
    if (is(parser, character))
    {
        increment(parser);
    }
    else
    {
        longjmp(parser->environment, -1);
    }
}

Nucleus_NoError() Nucleus_NonNull() static inline bool
isExponentCharacter
    (
        const Parser *parser
    )
{ return (parser->current != parser->end) && ('e' == current(parser) || 'E' == current(parser));}

Nucleus_NoError() Nucleus_NonNull() static inline bool
isPlus
    (
        const Parser *parser
    )
{ return (parser->current != parser->end) && ('+' == current(parser)); }

Nucleus_NoError() Nucleus_NonNull() static inline bool
isMinus
    (
        const Parser *parser
    )
{ return (parser->current != parser->end) && ('-' == current(parser)); }

Nucleus_NoError() Nucleus_NonNull() static inline bool
isDigit
    (
        const Parser *parser
    )
{ return (parser->current != parser->end) && ('0' <= current(parser) && current(parser) <= '9'); }

Nucleus_NoError() Nucleus_NonNull() static inline bool
isDecimalSeparator
    (
        const Parser *parser
    )
{ return (parser->current != parser->end) && ('.' == current(parser)); }

Nucleus_NoError() Nucleus_NonNull() static inline bool
isEnd
    (
        const Parser *parser
    )
{ return (parser->current == parser->end); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static const Nucleus_DecimalFloat_Digit NaN[] = { 'n', 'a', 'n' };

static const Nucleus_DecimalFloat_Digit Inf[] = { 'i', 'n', 'f' };

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_createNaN
    (
        Nucleus_DecimalFloat **decimalFloat
    )
{
    if (Nucleus_Unlikely(!decimalFloat)) return Nucleus_Status_InvalidArgument;
    Nucleus_DecimalFloat *temporary;
    Nucleus_Status status = Nucleus_allocateMemory((void **)&temporary, sizeof(Nucleus_DecimalFloat));
    if (status) return status;
    temporary->sign = Nucleus_Sign_Plus;
    temporary->numberOfDigits = 0;
    temporary->digits = (Nucleus_Natural8 *)NaN;
    temporary->exponent = 0;
    *decimalFloat = temporary;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_createInf
    (
        Nucleus_DecimalFloat **decimalFloat,
        Nucleus_Sign sign
    )
{
    if (Nucleus_Unlikely(!decimalFloat)) return Nucleus_Status_InvalidArgument;
    Nucleus_DecimalFloat *temporary;
    Nucleus_Status status = Nucleus_allocateMemory((void **)&temporary, sizeof(Nucleus_DecimalFloat));
    if (status) return status;
    temporary->sign = sign;
    temporary->numberOfDigits = 0;
    temporary->digits = (Nucleus_DecimalFloat_Digit *)Inf;
    temporary->exponent = 0;
    *decimalFloat = temporary;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_create_fromString
    (
        Nucleus_DecimalFloat **decimalFloat,
        const char *bytes,
        Nucleus_Size numberOfBytes
    )
{
    if (Nucleus_Unlikely(!decimalFloat || !bytes)) return Nucleus_Status_InvalidArgument;

    Nucleus_Status status;
    uint8_t *buffer = NULL;
    Nucleus_Size bufferSize = 0;
    struct { Nucleus_Size begin, end; } integral = { .begin = 0, .end = 0 };
    struct { Nucleus_Size begin, end; } fractional = { .begin = 0, .end = 0 };

    struct
    {
        Nucleus_Sign sign;
        Nucleus_Boolean isNaN;
        Nucleus_Boolean isInf;
    } info = {
        .sign = Nucleus_Sign_Plus,
        .isNaN = false,
        .isInf = false
    };

    struct
    {
        Nucleus_Boolean overflow;
        Nucleus_Sign sign;
        Nucleus_Integer32 magnitude;
    } exponent = {
        .overflow = false,
        .sign = Nucleus_Sign_Plus,
        .magnitude = 0,
    };

    status = Nucleus_allocateArrayMemory((void **)&buffer, numberOfBytes, sizeof(Nucleus_DecimalFloat_Digit));
    if (status) return status;

    Nucleus_Integer32 decimalExponent = -((Nucleus_Integer32)(fractional.end - fractional.begin));
    Parser parser = { .begin = bytes, .end = bytes + numberOfBytes, .current = bytes };
    if (!setjmp(parser.environment))
    {
        if (is(&parser,'N'))
        {
            increment(&parser);
            expectAndNext(&parser, 'a');
            expectAndNext(&parser, 'N');
            if (!isEnd(&parser)) longjmp(parser.environment, -1);
            return Nucleus_DecimalFloat_createNaN(decimalFloat);
        }
        else if (is(&parser, 'I'))
        {
            increment(&parser);
            expectAndNext(&parser, 'n');
            expectAndNext(&parser, 'f');
            if (!isEnd(&parser)) longjmp(parser.environment, -1);
            return Nucleus_DecimalFloat_createInf(decimalFloat, info.sign);
        }
        else
        {
            if (isPlus(&parser) || isMinus(&parser))
            {
                if (isMinus(&parser))
                {
                    info.sign = Nucleus_Sign_Minus;
                }
                increment(&parser);
                if (is(&parser, 'I'))
                {
                    increment(&parser);
                    expectAndNext(&parser, 'n');
                    expectAndNext(&parser, 'f');
                    if (!isEnd(&parser)) longjmp(parser.environment, -1);
                    return Nucleus_DecimalFloat_createInf(decimalFloat, info.sign);
                }
            }
            if (is(&parser, 'I'))
            {
                increment(&parser);
                expectAndNext(&parser, 'n');
                expectAndNext(&parser, 'f');
                if (!isEnd(&parser)) longjmp(parser.environment, -1);
                return Nucleus_DecimalFloat_createInf(decimalFloat, info.sign);
            }

            if (isDigit(&parser))
            {
                integral.begin = bufferSize;
                do
                {
                    buffer[bufferSize++] = current(&parser) - '0';
                    increment(&parser);
                } while (isDigit(&parser));
                integral.end = bufferSize;

                if (isDecimalSeparator(&parser))
                {
                    increment(&parser);

                    fractional.begin = bufferSize;
                    while (isDigit(&parser))
                    {
                        buffer[bufferSize++] = current(&parser) - '0';
                        increment(&parser);
                    }
                    fractional.end = bufferSize;
                }
            }
            else if (isDecimalSeparator(&parser))
            {
                integral.begin = bufferSize;
                integral.end = bufferSize;

                increment(&parser);

                if (!isDigit(&parser))
                { longjmp(parser.environment, -1); }

                fractional.begin = bufferSize;
                do
                {
                    buffer[bufferSize++] = current(&parser) - '0';
                    increment(&parser);
                } while (isDigit(&parser));
                fractional.end = bufferSize;
            }
            else
            {
                longjmp(parser.environment, -1);
            }
        }

        // At this point we have lexically/syntactically validated the integral and fractional part.

        // Remove leading zeroes from the integral part.
        // We retain the significant integral digits.
        if (integral.end - integral.begin > 0)
        {
            Nucleus_Size i = integral.begin, n = integral.end;
            for (; buffer[i + 0] == 0 && i < n; ++i)
            {}
            integral.begin = i;
        }

        // Remove trailing zeroes from the fractional part.
        // We retain the significant fractional digits.
        if (fractional.end - fractional.begin > 0)
        {
            Nucleus_Size i = fractional.end, n = fractional.begin;
            for (; buffer[i - 1] == 0 && i > n; --i)
            {}
            fractional.end = i;
        }

        if ((fractional.end - fractional.begin) > Nucleus_Integer32_Greatest)
        {
            longjmp(parser.environment, -1);
        }
        decimalExponent = -(fractional.end - fractional.begin);

        // Parse optional exponent.
        if (isExponentCharacter(&parser))
        {
            static const Nucleus_Integer32 greatestExponentMagnitude = Nucleus_Integer32_Greatest / 10; // If exponentValue >= maxExponentValue, then
                                                                                                        // the next multiplication by 10 will cause
                                                                                                        // an overflow.
            increment(&parser);
            if (isPlus(&parser) && isMinus(&parser))
            {
                if (isMinus(&parser))
                {
                    exponent.sign = Nucleus_Sign_Minus;
                }
                increment(&parser);
                if (!isDigit(&parser)) longjmp(parser.environment, -1);
                do
                {
                    if (Nucleus_Unlikely(exponent.magnitude >= greatestExponentMagnitude))
                    {
                        Nucleus_deallocateMemory(buffer);
                        return Nucleus_Status_Overflow;
                    }
                    exponent.magnitude = exponent.magnitude + (current(&parser) - '0');
                    increment(&parser);
                } while (isDigit(&parser));
            }
        }

        // Junk after the number is not acceptable.
        if (!isEnd(&parser)) longjmp(parser.environment, -1);
    }
    else
    {
        Nucleus_deallocateMemory(buffer);
        return Nucleus_Status_ConversionFailed;
    }


    // If the exponent overflowed, then return -Inf or +Inf.
    if (exponent.overflow)
    {
        Nucleus_deallocateMemory(buffer);
        return Nucleus_DecimalFloat_createInf(decimalFloat, info.sign);
    }

    // Trim leading unused digits in the buffer.
    if (integral.begin > 0)
    {
        Nucleus_copyMemory(buffer, buffer + integral.begin, integral.end - integral.begin +
                                                            fractional.end - fractional.end);
        fractional.begin -= integral.begin;
        fractional.end -= integral.begin;
        integral.end -= integral.begin;
        integral.begin = 0;
    }
    bufferSize = fractional.end;

    // Preserve invariant that there is at least one digit which is zero.
    if (bufferSize == 0)
    {
        buffer[bufferSize++] = 0;
    }

    // Trim trailing unused digits in the buffer.
    if (numberOfBytes > bufferSize)
    {
        Nucleus_reallocateMemory((void **)&buffer, bufferSize);
    }
    // Combine the decimal exponent and the exponent into one.
    status = Nucleus_safeAddInteger32(decimalExponent, (exponent.sign == Nucleus_Sign_Plus ? +exponent.magnitude
                                                                                           : -exponent.magnitude),
                                      &decimalExponent);
    if (status)
    {
        Nucleus_deallocateMemory(buffer);
        return status;
    }

    Nucleus_DecimalFloat *localDecimalFloat;
    status = Nucleus_allocateMemory((void **)&localDecimalFloat, sizeof(Nucleus_DecimalFloat));
    if (status)
    {
        Nucleus_deallocateMemory(buffer);
        return status;
    }

    localDecimalFloat->sign = info.sign;
    localDecimalFloat->numberOfDigits = bufferSize;
    localDecimalFloat->digits = buffer;
    localDecimalFloat->exponent = decimalExponent;

    *decimalFloat = localDecimalFloat;

    return Nucleus_Status_Success;
}

Nucleus_NonNull() void
Nucleus_DecimalFloat_destroy
    (
        Nucleus_DecimalFloat *decimalFloat
    )
{
    if (decimalFloat->digits != (Nucleus_DecimalFloat_Digit *)Inf &&
        decimalFloat->digits != (Nucleus_DecimalFloat_Digit *)NaN)
    {
        Nucleus_deallocateMemory(decimalFloat->digits);
        decimalFloat->digits = NULL;
    }
    Nucleus_deallocateMemory(decimalFloat);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_isNaN
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Boolean *isNaN
    )
{
    if (Nucleus_Unlikely(!decimalFloat || !isNaN)) return Nucleus_Status_InvalidArgument;
    *isNaN = decimalFloat->digits == (uint8_t *)NaN;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_isPositiveInfinity
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Boolean *isPositiveInfinity
    )
{
    if (Nucleus_Unlikely(!decimalFloat || !isPositiveInfinity)) return Nucleus_Status_InvalidArgument;
    *isPositiveInfinity = decimalFloat->sign == Nucleus_Sign_Plus && decimalFloat->digits == (uint8_t *)Inf;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_isNegativeInfinity
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Boolean *isNegativeInfinity
    )
{
    if (Nucleus_Unlikely(!decimalFloat || !isNegativeInfinity)) return Nucleus_Status_InvalidArgument;
    *isNegativeInfinity = decimalFloat->sign == Nucleus_Sign_Minus && decimalFloat->digits == (Nucleus_DecimalFloat_Digit *)Inf;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_getNumberOfDigits
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Size *numberOfDigits
    )
{
    if (Nucleus_Unlikely(!decimalFloat || !numberOfDigits)) return Nucleus_Status_InvalidArgument;
    *numberOfDigits = decimalFloat->numberOfDigits;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_DecimalFloat_getDigit
    (
        Nucleus_DecimalFloat *decimalFloat,
        Nucleus_Size indexOfDigit,
        Nucleus_DecimalFloat_Digit *digit
    )
{
    if (Nucleus_Unlikely(!decimalFloat || !digit)) return Nucleus_Status_InvalidArgument;
    if (Nucleus_Unlikely(indexOfDigit >= decimalFloat->numberOfDigits)) return Nucleus_Status_IndexOutOfBounds;
    *digit = decimalFloat->digits[indexOfDigit];
    return Nucleus_Status_Success;
}
