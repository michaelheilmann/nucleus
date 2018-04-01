# `Nucleus_reallocateArrayMemory`
*Reallocate a memory block.*

## C Specification
```
Nucleus_Status
Nucleus_reallocateArrayMemory
    (
        void **p,
        size_t n,
        size_t m
    );
```

## Parameters
- `p` a pointer to a `void *` variable
- `n`, `m` the product of @a n and @a m is the size, in Bytes, of the memory block to allocate. Note that @a 0 is a valid size.

## Description
This function reallocates a memory block.

If this function succeeds, then this function conceptually performed the following tasks:
The function conceptually allocates a new memory block of size `n * m` and copies `min(n * m,k)` Bytes from the old
memory block pointed to by `*p` of size `k` to the new memory block. The old memory block is then deallocated.
The address of the new memory block is is assigned to `*p` and `Nucleus_Status_Success` is returned.

This function fails if and only if one or more of the following conditions are met:
- `p` or `*p` is a null pointer
- `n * m` would overflow
- the allocation of the new memory block failed

Under the first condition `Nucleus_InvalidArgument` is returned,
under the second condition `Nucleus_Overflow` is returned, and
under the third condition `Nucleus_AllocationFailed`` is returned.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
