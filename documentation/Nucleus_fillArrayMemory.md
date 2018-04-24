# `Nucleus_filArrayMemory`
*Set the contents of a memory block.*

## C Specification
```
Nucleus_Status
Nucleus_fillMemory
    (
        void *p,
        Nucleus_Byte v,
        Nucleus_Size n,
        Nucleus_Size m
    )
```

## Parameters
- `p` a pointer to the first Byte of the target memory block
- `v` the value to be assigned
- `n`, `m` the product of `n` and `m` is the number of Bytes to assign. Note that `0` is a valid number of Bytes.

## Description
This function sets the contents of a memory block.

If this function succeeds, `n * m` Bytes of the memory block pointed to by `p` were assigned the value `v`.
This function fails if and only if `p` is a null pointer or if the product of `n * m` overflows.
`Nucleus_Status_InvalidArgument` is returned in the former case,
`Nucleus_Status_Overflow` is returned in the latter case.

The number of Bytes (to assign) is specified in terms of array semantics i.e. `n` should be thought of as the array size, in elements, and `m` as the element size, in Bytes.
The `*_ArrayMemory` functions exist for convenience as a frequent task in C program is the allocation of arrays.
Another reason is safety: This function fails and return `Nucleus_Status_Overflow` if the product of `n` and `m` would overflow.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
