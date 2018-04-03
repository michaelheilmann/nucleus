# `Nucleus_Unlikely`
*Expression annotation providing branch prediction information, indicating an expression is likely to evaluate to logically false.*

## C Specification
```
#define Nucleus_Likely(expression) /* Implementation details hidden. */
```

## Description
This expression annotation indicates that the expression `expression` is likely to evaluate to logically false.

For example, given contemporary compilers and environments, it is likely that `malloc` for a small size of memory
is very likely to succeed. Henc, in the following code snipped, we tell tell the compiler that the test for success
of such a call to `malloc` is likely to to evaluate to logically true and the code in branch `(A)` is likely to
be executed whilst consequently the code in branch `(X)` is not likely to be execute.

```
char *p = malloc(sizeof(char) * 1024);
if (Nucleus_Likely(p))
{/* (A) Foaming with joy, continue execution. */}
else
{/* (X) In the heart with pain, abort execution. */}
```
