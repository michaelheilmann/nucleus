# `Nucleus_DynamicByteArray_uninitialize`
*Uninitialize a `Nucleus_DynamicByteArray` object.*

## C Signature
```
Nucleus_Status
Nucleus_DynamicByteArray_uninitialize
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    );
```

## Parameters
- `dynamicByteArray` a pointer to an initialized `Nucleus_DynamicByteArray` object
- `initialCapacity` the initial capacity, in Bytes. `0` is a valid required initial capacity.

This function unintializes a `Nucleus_DynamicByteArray` object.

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
