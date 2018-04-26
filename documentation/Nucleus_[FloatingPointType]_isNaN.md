# `Nucleus_[FloatingPointType]_isNaN`
*Get if a floating point value is a not a number value (NaN).*

## C Signature
```
Nucleus_Status
Nucleus_[FloatingPointType]_isNaN
    (
        Nucleus_[FloatingPointType] x,
        bool *r
    )
```
where `[FloatingPointType]` is one of `Single`, `Double`, or `Quadruple`.

## Parameters
- `x` a `[Floating-Point-Type]` value
- `r` a pointer to a `bool` variable

## Description
This function gets if a floating point value is a not a number value (NaN).

A boolean value was stored in the variable pointed to by `r` and `Nucleus_Status_Success` is returned
if this function succeeds. 
The boolean value is `true` if `x` is a not a number value (NaN) and is `false` if `x` not is a number value (including infinity).
This function fails if and only if `r` is a null pointer.
In that case `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/FloatingPoint.h`| `Nucleus/FloatingPoint.h` |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
