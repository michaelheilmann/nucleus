# `Nucleus_copyArrayMemory`
*Copy contents of a memory block to another memory block.*

## C Specification
```
Nucleus_Status
Nucleus_copyMemory
    (
        void *p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Size m
    )
```

## Parameters
- `p` a pointer to the first Byte of the target memory block
- `q` a pointer to the first Byte of the source memory block
- `n`, `m` the product of `n` and `m` is the number of Bytes to copy. Note that `0` is a valid number of Bytes.

## Description
This function copies contents of a memory block to another memory block.

If this function succeeds, `n` Bytes were copied from the memory block pointed to by `q` to the memory block pointed to by `p`.
This function fails if and only if `p` or `q` is a null pointer or `n * m` would overflow. `Nucleus_Status_InvalidArgument`
is returned in the former case, `Nucleus_Status_Overflow` is returned in the latter case.
The source and the target memory blocks may or may not overlap.

The number of Bytes (to copy) is specified in terms of array semantics i.e. `n` should be thought of as the array size, in elements, and `m` as the element size, in Bytes.
The `*_ArrayMemory` functions exist for convenience as a frequent task in C program is the copying of arrays.
Another reason is safety: This function fails and return `Nucleus_Status_Overflow` if the product of `n` and `m` would overflow`.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
