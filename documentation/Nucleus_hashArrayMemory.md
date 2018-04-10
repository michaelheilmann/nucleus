# `Nucleus_hashArrayMemory`
*Compute the hash value of a memory block.*

## C Specification
```
Nucleus_Status
Nucleus_hashArrayMemory
    (
        const void *p,
        size_t n,
        size_t m,
        Nucleus_HashValue *hv
    )
```

## Parameters
- `p` a pointer to a memory block
- `n`, `m` the size, in Bytes, of the memory block pointed to by `p`
- `hv` a pointer to a `int` variable

## Description
This function computes the hash value of a memory block.

If this function succeeds, `*hv` was assigned the hash value of the memory block pointed to by `p` and
`Nucleus_Status_Success` was returned. Otherwise this function fails.

This function fails if and only if
- `p` or `hv` is a null pointer or
- `n * m` overflows
In the former case `Nucleus_InvalidArgument` is returned and in the latter case `Nucleus_Status_Overflow` is returned.

The size (of the memory block to compute the hash value of) is specified in terms of array semantics i.e. `n` should be
thought of as the array size, in elements, and `m` as the element size, in Bytes. The `*ArrayMemory*` functions exist
for convenience as frequently sequences of Bytes are considered as arrays which are a consecutive sequence of elements
of a fixed size. Another reason is safety: This function fails and return `Nucleus_Status_Overflow` if the product of
`n` and `m` would overflow.

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Hash.h`                                | `Nucleus/Hash.h`                                |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
