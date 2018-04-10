# `Nucleus_Collections_ByteArray_uninitialize`
*Uninitialize a `Nucleus_Collections_ByteArray` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_ByteArray_uninitialize
    (
        Nucleus_Collections_ByteArray *dynamicByteArray
    );
```

## Parameters
- `dynamicByteArray` a pointer to an initialized `Nucleus_Collections_ByteArray` object
- `initialCapacity` the initial capacity, in Bytes. `0` is a valid required initial capacity.

This function unintializes a `Nucleus_Collections_ByteArray` object.

## Requirements

|                      | Windows                           | Linux                             |
|----------------------|-----------------------------------|-----------------------------------|
| *Header*             | `Nucleus/Collections/ByteArray.h` | `Nucleus/Collections/ByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`             | `libNucleus.Library.a`            |
