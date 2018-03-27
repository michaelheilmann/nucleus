# `Nucleus_allocateMemory`
*Allocate a memory block of a specified size.*

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
- `n`, `m` the product of @a n and @a m is the size, in Bytes, of the memory block to allocate. Note that @a 0 is a valid size.

## Description
This function allocates a memory block of a specified size.

If this function succeeds, `*p` is assigned a pointer to a new memory block and `Nucleus_Status_Success` is returned.
Otherwise a non-zero status code is returned. In particular, if `p` is a null pointer `Nucleus_Status_InvalidArgument` is returned and if an allocation failed `Nucleus_Status_AllocationFailed` is returned.

The size (of the memory block to allocate) is specified in terms of array semantics i.e. `n` should be thought of as the array size, in elements, and `m` as the element size, in Bytes.
The `*_ArrayMemory` functions exist for convenience as a frequent task in C program is the allocation of arrays.
Another reason is safety: This function fails and return `Nucleus_Status_Overflow` if the product of `n` and `m` would overflow.

## Undefined behavior
If `p` is not a null pointer and does not point to a `void *` variable, the behavior of this function is undefined.
