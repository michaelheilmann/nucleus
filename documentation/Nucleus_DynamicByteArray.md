# Nucleus Dynamic Byte Arrays Module
This module provides dynamically resizing arrays of Bytes.

## Structures
`Nucleus_DynamicByteArray` is *defined* in `Nucleus/DynamicByteArray.h`.
Consumers of this library should not make assumptions beyond the lifetime of a program.

```
typedef struct Nucleus_DynamicByteArray
{ /* hidden */ } Nucleus/DynamicByteArray;
```

## Functions and macros
The following functions are associated wit

- [Nucleus_DynamicByteArray_initialize](Nucleus_DynamicByteArray_initialize.md)
- [Nucleus_DynamicByteArray_uninitialize](Nucleus_DynamicByteArray_uninitialize^.md)
- [Nucleus_DynamicByteArray_prependMany](Nucleus_DynamicByteArray_prependMany.md)
- [Nucleus_DynamicByteArray_appendMany](Nucleus_DynamicByteArray_appendMany.md)
- [Nucleus_DynamicByteArray_insertMany](Nucleus_DynamicByteArray_insertMany.md)

`Nucleus_DynamicByteArray` is a *Collection* i.e. supports the following properties

- [Nucleus_DynamicByteArray_getSize](Nucleus_Dynamic[Collection-Type]_getSize.md)
- [Nucleus_DynamicByteArray_clear](Nucleus_Dynamic[Collection-Type]_clear.md)

`Nucleus_DynamicByteArray` is a *ArrayCollection` (see concepts) i.e. supports the following operations

- [Nucleus_DynamicByteArray_getCapacity](Nucleus_Dynamic[Array-Collection-Type]_getCapacity.md)
- [Nucleus_DynamicByteArray_getFreeCapacity](Nucleus_Dynamic[Array-Collection-Type]_getFreeCapacity.md)
- [Nucleus_DynamicByteArray_ensureFreeCapacity](Nucleus_Dynamic[Array-Collection-Type]_ensureFreeCapacity.md)

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
