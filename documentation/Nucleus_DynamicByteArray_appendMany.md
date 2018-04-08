# `Nucleus_DynamicByteArray_append`
*Append Bytes to the list of Bytes in a `Nucleus_DynamicByteArray` object.*

## C Signature
```
Nucleus_Status
Nucleus_DynamicByteArray_append
    (
        Nucleus_DynamicByteArray *dynamicByteArray,
        const char *bytes,
        size_t numberOfBytes
    )
```

## Parameters
- `dynamicByteArray` a pointer to an initialized `Nucleus_DynamicByteArray` object
- `memoryBlock` a pointer to a memory block of `numberOfBytes` Bytes
- `memoryBlockSize` the size, in Bytes, of the memory block pointed to by `memoryBlock`

## Description 
This function appends Bytes to the list of Bytes in a `Nucleus_DynamicByteArray` object.

If this function succeeds,
- the `memoryBlockSize` Bytes of the memory block pointed to by `memoryBlock` were appended to the list of Bytes of the
  `Nucleus_DynamicByteArray` object pointed to by `dynamicByteArray`
- `Nucleus_Status_Success` was returned.

If this function fails, one of the following non-zero status codes is returned
- `Nucleus_Status_InvalidArgument` `dynamicByteArray` and/or `memoryBlock` is a null pointer
- `Nucleus_Status_Overflow` `numberOfBytes` is too big
- `Nucleus_Status_AllocationFailed` an allocation failed

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
