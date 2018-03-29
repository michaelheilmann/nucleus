# `Nucleus_DynamicByteArray_getCapacity`
*Get the capacity of a `Nucleus_DynamicByteArray` object.*

## C Signature
```
Nucleus_Status
Nucleus_DynamicByteArray_getCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *capacity
    );
```

## Parameters
- `dynamicByteArray` a pointer to an initialized `Nucleus_DynamicByteArray` object
- `capacity` a pointer to a `size_t` variable

## Descriptions
This function gets the capacity, in Bytes, of a `Nucleus_DynamicByteArray` object.

If this function succeeds,
- the capacity, in Bytes, of the `Nucleus_DynamicByteArray` object pointed to by `dynamicByteArray` was stored in the
  variable pointed to by `capacity` and
- `Nucleus_Status_Success` was returned

This function fails if and only if dynamicByteArray` and/or `capacity` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
