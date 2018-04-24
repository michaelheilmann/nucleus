# `Nucleus_copyMemory`
*Copy contents of a memory block to another memory block.*

## C Specification
```
Nucleus_Status
Nucleus_copyMemory
    (
        void *p,
        const void *q,
        Nucleus_Size n
    )
```

## Parameters
- `p` a pointer to the first Byte of the target memory block
- `q` a pointer to the first Byte of the source memory block
- `n` the number of Byte to copy. Note that `0` is a valid number of Bytes.

## Description
This function copies contents of a memory block to another memory block.

If this function succeeds, `n` Bytes were copied from the memory block pointed to by `q` to the memory block pointed to by `p`.
This function fails if and only if `p` or `q` is a null pointers. `Nucleus_Status_InvalidArgument` is returned in that case.
The source and the target memory blocks may or may not overlap.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
