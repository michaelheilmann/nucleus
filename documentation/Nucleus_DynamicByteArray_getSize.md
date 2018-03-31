# `Nucleus_DynamicByteArray_getSize`
*Get the size of a `Nucleus_DynamicByteArray` object.*

## C Signature
```
Nucleus_Status
Nucleus_DynamicByteArray_getSize
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        size_t *size
    );
```

## Parameters
- `dynamicByteArray` a pointer to an initialized `Nucleus_DynamicByteArray` object
- `size` a pointer to a `size_t` variable

## Descriptions
This function gets the size, in Bytes, of a `Nucleus_DynamicByteArray` object.

If this function succeeds,
- the size, in Bytes, of the `Nucleus_DynamicByteArray` object pointed to by `dynamicByteArray` was stored in the
  variable pointed to by `size` and
- `Nucleus_Status_Success` was returned

This function fails if and only if dynamicByteArray` and/or `size` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
