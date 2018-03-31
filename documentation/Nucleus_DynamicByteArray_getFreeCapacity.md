# `Nucleus_DynamicByteArray_getCapacity`
*Get the free capacity of a `Nucleus_DynamicByteArray` object.*

## C Signature
```
Nucleus_Status
Nucleus_DynamicByteArray_getFreeCapacity
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *freeCapacity
    );
```

## Parameters
- `dynamicByteArray` a pointer to an initialized `Nucleus_DynamicByteArray` object
- `freeCapacity` a pointer to a `size_t` variable

## Description
This function gets the free capacity, in Bytes, of a `Nucleus_DynamicByteArray` object.

If this function succeeds,
- the free capacity, in Bytes, of the `Nucleus_DynamicByteArray` object pointed to by `dynamicByteArray` was stored in
  the variable pointed to by `freeCapacity` and
- `Nucleus_Status_Success` was returned

This function fails if and only if dynamicByteArray` and/or `freeCapacity` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.


## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |