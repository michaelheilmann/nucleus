# `Nucleus_NoWarnUnused`
*Function annotation indicating that no warning is emitted if a function is determined by the compiler as not used.*

## C Specification
```
#define Nucleus_NoWarnUnused() ...
```

## Description
This function annotation indicates that no warning is emitted if a function is determined by the compiler as not used.

For example, this macro is used to annotate the function `f` such no warning is emitted if it is determined by the
compiler as not used.
```
Nucleus_NoWarnUnused() static void f();
```

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Annotations.h`  | `Nucleus/Annotations.h`   |
| *Static library*     |          -               |           -               |
