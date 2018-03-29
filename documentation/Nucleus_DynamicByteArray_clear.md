# `Nucleus_DynamicByteArray_clear`
*Clear a `Nucleus_DynamicByteArray` object.*

## C Signature
```
Nucleus_Status
Nucleus_DynamicByteArray_clear
    (
        Nucleus_DynamicByteArray *dynamicByteArray
    );
```

## Parameters
- `dynamicByteArray` a pointer to an initialized `Nucleus_DynamicByteArray` object

## Descriptions
This function clears a `Nucleus_DynamicByteArray` object.

If this function succeeds,
- the size, in Bytes, of the `Nucleus_DynamicByteArray` object pointed to by `dynamicByteArray` was stored in the
  variable pointed to by `size` and `Nucleus_Status_Success` was returned

This function fails if and only if dynamicByteArray` is  null pointer. In that case, `Nucleus_Status_InvalidArgument`
is returned.

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
