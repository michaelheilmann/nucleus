# `Nucleus_NoReturn`
*Function annotation indicating that a function never returns.*

## C Specification
```
#define Nucleus_NoReturn() ...
```

## Description
This function annotation indicates that a function never returns.
If it returns, it only returns by raising an exception or by calling `longjmp`.
