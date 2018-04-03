# `Nucleus_Likely`
*Expression annotation providing branch prediction information, indicating an expression is likely to evaluate to logically true.*

## C Specification
```
#define Nucleus_Likely(expression) /* Implementation details hidden. */
```

## Description
This expression annotation indicates that the expression `expression` is likely to evaluate to logically true.

For example, given contemporary compilers and environments, it is likely that `malloc` for a small size of memory
is very likely to succeed. Henc, in the following code snipped, we tell tell the compiler that the test for failure
of such a call to `malloc` is likely to to evaluate to logically false and the code in branch `(X)` is unlikely
to execute whilst consequently the code in branch `(A)` is likely to execute.

```
char *p = malloc(sizeof(char) * 1024);
if (Nucleus_Unlikely(!p))
{ /* (X) In the heart with pain, abort execution. */
}
/* (A) Foaming with joy, continue execution. */
```
