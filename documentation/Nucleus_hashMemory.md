# `Nucleus_hashMemory`
*Compute the hash value of a memory block.*

## C Specification
```
Nucleus_Status
Nucleus_hashMemory
    (
        void *p,
        size_t n,
        unsigned int *hv
    )
```

## Parameters
- `p` a pointer to a memory block
- `n` the size, in Bytes, of the memory block pointed to by `p`
- `hv` a pointer to a `int` variable

## Description
This function computes the hash value of a memory block.

If this function succeeds, `*hv` was assigned the hash value of the memory block pointed to by `p` and `Nucleus_Status_Success` was returned.
Otherwise a non-zero status code is returned. In particular, if `p` is a null pointer `Nucleus_Status_InvalidArgument` is returned.
