# `Nucleus_[Floating-Point-Type]_hash
*Compute the hash value of a floating point value.*

## C Signature
```
Nucleus_Status
[Floating-Point-Type]_hash
    (
        [Floating-Point-Type] x,
        unsigned int *hv
    )
```
where `[Floating-Point-Type]` is one of `Nucleus_Single`, `Nucleus_Double`, or `Nucleus_Quadruple`.

## Parameters
- `x` a `[Floating-Point-Type]` value
- `hv` a pointer to an @a (unsigned int) variable

## Description
This function compues the hash value of a floating point value.

The hash value of the floating point value `x` was stored in the variable pointed to by `hv` and `Nucleus_Status_Success` is returned
if this function succeeds. 
This function fails if and only if `hv` is a null pointer.
In that case `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/FloatingPoint.h`| `Nucleus/FloatingPoint.h` |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |