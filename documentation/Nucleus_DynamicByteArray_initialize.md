# `Nucleus_DynamicByteArray_initialize`
*Initialize a `Nucleus_DynamicByteArray` object.`

## C Signature
```
Nucleus_Status
Nucleus_DynamicByteArray_initialize`
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t initializeCapacity
    )
```

## Parameters
- `dynamicByteArray` a pointer to an uninitialized `Nucleus_DynamicByteArray` object
- `initialCapacity` the initial capacity, in Bytes. `0` is a valid required initial capacity.

## Description
This function intializes a `Nucleus_DynamicByteArray` object.
If this function succeeds,
- the Nucleus_DynamicByteArray` object is initialized and has a capacity equal to `initialCapacity`
- `Nucleus_Status_Success` is returned
If this function fails, one of the non-zero status codes is returned
- `Nucleus_Status_InvalidArgument`` `dynamicByteArray` is a null pointer
- `Nucleus_Status_Overflow` `initialCapacity` is too big
- `Nucleus_Status_AllocationFailed` an allocation failed

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
