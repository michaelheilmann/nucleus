# `Nucleus_copyMemory`
*Get if the contents of two memory blocks are equal.*

## C Specification
```
Nucleus_Status
Nucleus_compareMemory
    (
        const void *p,
        const void *q,
        Nucleus_Size n,
        Nucleus_Boolean *r
    )
```

## Parameters
- `p`, `q` pointers to the memory blocks
- `n` the size, in Bytes, of the memory blocks. Note that `0` is a valid size.
- `r` a pointer to a `bool` variable

## Description
This function get if the contents of two memory blocks are equal.

If this function succeeds:
- `*r` was assigned @a true if the contents of the memory blocks are equal and was assigned `false` if the contents of the memory blocks are not equal.
- `Nucleus_Status_Success` was returned.

Otherwise: A non-zero status code is returned. In particular, if `p` or `q` is a null pointer, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
