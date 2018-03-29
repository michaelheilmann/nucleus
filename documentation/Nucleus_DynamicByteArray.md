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
- [Nucleus_DynamicByteArray_prepend](Nucleus_DynamicByteArray_prepend.md)
- [Nucleus_DynamicByteArray_append](Nucleus_DynamicByteArray_append.md)
- [Nucleus_DynamicByteArray_insert](Nucleus_insert.md)
- [Nucleus_DynamicByteArray_getSize](Nucleus_getSize.md)
- [Nucleus_DynamicByteArray_getCapacity](Nucleus_getCapacity.md)
- [Nucleus_DynamicByteArray_getFreeCapacity](Nucleus_getFreeCapacity.md)

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
