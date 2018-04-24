# `Nucleus_fillMemory`
*Set the contents of a memory block.*

## C Specification
```
Nucleus_Status
Nucleus_fillMemory
    (
        void *p,
        Nucleus_Byte v,
        Nucleus_Size n
    )
```

## Parameters
- `p` a pointer to the first Byte of the target memory block
- `v` the value to be assigned
- `n` the number of Byte to assign. Note that `0` is a valid number of Bytes.

## Description
This function sets the contents of a memory block.

If this function succeeds, `n` Bytes of the memory block pointed to by `p` were assigned the value `v`.
This function fails if and only if `p` is a null pointer. `Nucleus_Status_InvalidArgument` in that case.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
