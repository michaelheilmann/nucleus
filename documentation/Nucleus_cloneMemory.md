# `Nucleus_cloneMemory`
*Clone a memory block.*

## C Signature
```
Nucleus_Status
Nucleus_cloneMemory
    (
        void **p,
        const void *q,
        Nucleus_Size n
     );
```

## Parameters
- `p` a pointer to a `void *` variable
- `q` a pointer to the memory block to be cloned
- `n` the size, in Bytes, of the memory block pointed to by `q`. Note that `0` is a valid size.

## Description
This function clones a memory block.

A memory block with the same size and the same contents as the specified memory block `(q,n)` is
allocated, its address is assigned to `*p` and `Nucleus_Status_Success` is returned. This function
fails if and only if
- `p` or `q` are null pointers, or
- the allocation of the memory block failed.

Under the former condition `Nucleus_Status_InvalidArgument` is returned,
under the latter condition `Nucleus_Status_AllocationFailed` is returned.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
