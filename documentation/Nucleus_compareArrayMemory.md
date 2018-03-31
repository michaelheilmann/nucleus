# `Nucleus_copyMemory`
*Get if the contents of two memory blocks are equal.*

## C Specification
```
Nucleus_Status
Nucleus_compareArrayMemory
    (
        void *p,
        void *q,
        size_t n,
        size_t m,
        bool *r
    )
```

## Parameters
- `p`, `q` pointers to the memory blocks
- `n`, `m` the size, in Bytes, of the memory blocks. Note that @a 0 is a valid size.
- `r` a pointer to a `bool` variable

## Description
This function get if the contents of two memory blocks are equal.

If this function succeeds:
- `*r` was assigned @a true if the contents of the memory blocks are equal and was assigned `false` if the contents of the memory blocks are not equal.
- `Nucleus_Status_Success` was returned.

Otherwise: A non-zero status code is returned. In particular, if `p` or `q` is a null pointer, `Nucleus_Status_InvalidArgument` is returned.

The size (of the memory block to allocate) is specified in terms of array semantics i.e. `n` should be thought of as the array size, in elements, and `m` as the element size, in Bytes.
The `*_ArrayMemory` functions exist for convenience as a frequent task in C program is the comparison of arrays.
Another reason is safety: This function fails and return `Nucleus_Status_Overflow` if the product of `n` and `m` would overflow.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
