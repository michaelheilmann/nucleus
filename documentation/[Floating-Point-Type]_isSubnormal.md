# `Nucleus_[Floating-Point-Type]_isNaN`
*Get if a floating point value is a subnormal value.*

## C Signature
```
Nucleus_Status
[Floating-Point-Type]_isSubnormal
    (
        [Floating-Point-Type] x,
        bool *r
    )
```
where `[Floating-Point-Type]` is one of `Nucleus_Single`, `Nucleus_Double`, or `Nucleus_Quadruple`.

## Parameters
- `x` a `[Floating-Point-Type]` value
- `r` a pointer to a `bool` variable

## Description
This function gets if a floating point value is a subnormal value.

A boolean value was stored in the variable pointed to by `r` and `Nucleus_Status_Success` is returned
if this function succeeds. 
The boolean value is `true` if `x` is a subnormal value and is `false` if `x` is not a subnormal value.
This function fails if and only if `r` is a null pointer.
In that case `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/FloatingPoint.h`| `Nucleus/FloatingPoint.h` |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
