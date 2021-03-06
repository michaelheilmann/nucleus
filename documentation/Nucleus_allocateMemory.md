# `Nucleus_allocateMemory`
*Allocate a memory block.*

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
- `p` a pointer to a `void *` variable
- `n` the size, in Bytes, of the memory block to allocate. Note that `0` is a valid size.

## Description
This function allocates a memory block of a specified size.

If this function succeeds, `*p` is assigned a pointer to a new memory block and `Nucleus_Status_Success` is returned.
Otherwise a non-zero status code is returned. In particular, if `p` is a null pointer `Nucleus_Status_InvalidArgument` is returned and if an allocation failed `Nucleus_Status_AllocationFailed` is returned.

## Undefined behavior
If `p` is not a null pointer and does not point to a `void *` variable, the behavior of this function is undefined.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
