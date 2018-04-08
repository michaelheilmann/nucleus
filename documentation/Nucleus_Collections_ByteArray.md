# Nucleus Dynamic Byte Arrays Module
This module provides dynamically resizing arrays of Bytes.

## Structures
`Nucleus_Collections_ByteArray` is *defined* in `Nucleus/Collections/ByteArray.h`.
Consumers of this library should not make assumptions beyond the lifetime of a program.

```
typedef struct Nucleus_Collections_ByteArray
{ /* hidden */ } Nucleus/Collections/ByteArray;
```

## Functions and macros
The following functions are associated wit

- [Nucleus_Collections_ByteArray_initialize](Nucleus_Collections_ByteArray_initialize.md)
- [Nucleus_Collections_ByteArray_uninitialize](Nucleus_Collections_ByteArray_uninitialize^.md)
- [Nucleus_Collections_ByteArray_prependMany](Nucleus_Collections_ByteArray_prependMany.md)
- [Nucleus_Collections_ByteArray_appendMany](Nucleus_Collections_ByteArray_appendMany.md)
- [Nucleus_Collections_ByteArray_insertMany](Nucleus_Collections_ByteArray_insertMany.md)

`Nucleus_Collections_ByteArray` is a *Collection* i.e. supports the following properties

- [Nucleus_Collections_ByteArray_getSize](Nucleus_Collections_[Collection-Type]_getSize.md)
- [Nucleus_Collections_ByteArray_clear](Nucleus_Collections_[Collection-Type]_clear.md)

`Nucleus_Collections_ByteArray` is a *ArrayCollection` (see concepts) i.e. supports the following operations

- [Nucleus_Collections_ByteArray_getCapacity](Nucleus_Collections_[Array-Collection-Type]_getCapacity.md)
- [Nucleus_Collections_ByteArray_getFreeCapacity](Nucleus_Collections_[Array-Collection-Type]_getFreeCapacity.md)
- [Nucleus_Collections_ByteArray_ensureFreeCapacity](Nucleus_Collections_[Array-Collection-Type]_ensureFreeCapacity.md)

## Requirements

|                      | Windows                           | Linux                             |
|----------------------|-----------------------------------|-----------------------------------|
| *Header*             | `Nucleus/Collections/ByteArray.h` | `Nucleus/Collections/ByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`             | `libNucleus.Library.a`            |
