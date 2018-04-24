# `Nucleus_cloneArrayMemory`
*Clone a memory block.*

## C Signature
```
Nucleus_Status
Nucleus_cloneArrayMemory
    (
        void **p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Size m
    );
```

## Parameters
- `p` a pointer to a `void *` variable
- `q` a pointer to a memory block
- `n`, `m` the size, in Bytes, of the memory block pointed to by `q`. Note that `0` is a valid size.

## Description
This function clones a memory block.

A memory block with the same size and the same contents as the specified memory block `(q,n*m)` is allocated, its
address is assigned to `*p` and `Nucleus_Status_Success` is returned. This function fails if and only if
- `p` or `q` are null pointers, or
- the allocation of the memory block failed,
- `n * m` would overflow

Under the first condition `Nucleus_InvalidArgument` is returned,
under the second condition `Nucleus_AllocationFailed`` is returned, and
under the third condition `Nucleus_Overflow` is returned.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
