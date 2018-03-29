# `Nucleus_deallocateMemory`
*Deallocate a memory block.*

## C Specification
```
Nucleus_Status
Nucleus_deallocateMemory
    (
        void *p
    )
```

## Parameters
- `p` a pointer to a memory block previously allocated by `Nucleus_allocateMemory` or `Nucleus_allocateArrayMemory`.

## Description
This function deallocates a memory block.

If this functions terminates, the memory block pointed to by `p` was deallocated.

## Undefined behavior
If `p` is not a null pointer and does not point to a memory block previously allocated by `Nucleus_allocateMemory` or `Nucleus_allocateArrayMemory`., the behavior of this function is undefined.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Memory.h`       | `Nucleus/Memory.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
