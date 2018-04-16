# `Nucleus_combineHashValues`
*Combine hash values.*

## C Specification
```
Nucleus_Status
Nucleus_allocateMemory
    (
        void **p,
        size_t n
    )
```

## Parameters
- `x` the first `Nucleus_HashValue` values
- `y` the second `Nucleus_HashValue` value
- `z` a pointer to a `Nucleus_HashValue` value

## Description
This function combines hash values.

If this function succeeds, `*z` is assigned a combination of a the hash values `x` and `y` and `Nucleus_Status_Success`
is returned. This function fails if and only if `z` is a null pointer. In that case `Nucleus_Status_InvalidArgument` is
returned.

## Undefined behavior
If `z` is not a null pointer and does not point to a `Nucleus_HashValue` variable, the behavior of this function is undefined.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Hash.h`         | `Nucleus/Hash.h`          |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
