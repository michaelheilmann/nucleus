# `Nucleus_hashMemory`
*Compute the hash value of a memory block.*

## C Specification
```
Nucleus_Status
Nucleus_hashMemory
    (
        const void *p,
        size_t n,
        Nucleus_HashValue *hv
    )
```

## Parameters
- `p` a pointer to a memory block
- `n` the size, in Bytes, of the memory block pointed to by `p`. `0` is a valid size.
- `hv` a pointer to a `int` variable

## Description
This function computes the hash value a memory block.

`*hv* was assigned the hash value of `v` and `Nucleus_Status_Success` was returned if this function succeeded.
This function fails if and only if  `p` or `hv` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Hash.h`                                | `Nucleus/Hash.h`                                |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
