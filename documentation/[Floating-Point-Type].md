# `[Floating-Point-Type]`
Aliases for the C floating point types `float`, `double`, and `long double`.*

## C Signature
```
typedef float Nucleus_Single;
typedef double Nucleus_Double;
typedef long double Nucleus_Quadruple;
```

## Description
The type definitions `Nucleus_Single`, `Nucleus_Double`, and `Nucleus_Quadruple` are aliases for the
standard C floating point types `float`, `double`, and `long double`, respectively. These       type
definitions are supporting orthogonality of naming.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/FloatingPoint.h`| `Nucleus/FloatingPoint.h` |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
