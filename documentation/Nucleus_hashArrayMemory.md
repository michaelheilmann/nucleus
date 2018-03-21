# `Nucleus_hashArrayMemory`
*Compute the hash value of a memory block.*

## C Specification
```
Nucleus_Status
Nucleus_hashArrayMemory
    (
        void *p,
        size_t n,
        size_t m,
        unsigned int *hv
    )
```

## Parameters
- `p` a pointer to a memory block
- `n`, `m` the size, in Bytes, of the memory block pointed to by `p`
- `hv` a pointer to a `int` variable

## Description
This function computes the hash value of a memory block.

If this function succeeds, `*hv` was assigned the hash value of the memory block pointed to by `p` and `Nucleus_Status_Success` was returned.
Otherwise a non-zero status code is returned. In particular, if `p` is a null pointer `Nucleus_Status_InvalidArgument` is returned.

The size (of the memory block to compute the hash value of) is specified in terms of array semantics i.e. `n` should be thought of as the array size, in elements, and `m` as the element size, in Bytes.
The `*ArrayMemory*` functions exist for convenience as frequently sequences of Bytes are considered as arrays which are a consecutive sequence of elements of a fixed size.


 view (on memory blocks) is task in C program is the allocation of arrays.
Another reason is safety: This function fails and return `Nucleus_Status_Overflow` if the product of `n` and `m` would overflow.

