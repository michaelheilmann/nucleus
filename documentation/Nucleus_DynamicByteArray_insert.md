# `Nucleus_DynamicByteArray_insert`
*Insert Bytes into the list of Bytes in a `Nucleus_DynamicByteArray` object.*

## C Signature
```
Nucleus_Status
Nucleus_DynamicByteArray_insert
    (
        Nucleus_Language_Context *context,
        Nucleus_Language_StringBuffer *stringBuffer,
        const char *bytes,
        size_t numberOfBytes,
        size_t index
    );
```

## Parameters
- `dynamicByteArray` a pointer to an initialized `Nucleus_DynamicByteArray` object
- `memoryBlock` a pointer to a memory block of `numberOfBytes` Bytes
- `memoryBlockSize` the size, in Bytes, of the memory block pointed to by `memoryBlock`
- `index` the index at which the Bytes shall be inserted

## Description
This function inserts Bytes into the list of Bytes in a `Nucleus_DynamicByteArray` object.

If this function succeeds,
- the `memoryBlockSize` Bytes of the memory block pointed to by `memoryBlock` were inserted into the list of Bytes of
  the `Nucleus_DynamicByteArray` object   of the `Nucleus_DynamicByteArray` object pointed to by `dynamicByteArray` at
  the specified index `index` and
- `Nucleus_Status_Success` was returned.

If this function fails, one of the non-zero status codes is returned
- `Nucleus_Status_InvalidArgument`` `dynamicByteArray` and/or `memoryBlock` is a null pointer
- `Nucleus_Status_Overflow` `numberOfBytes` is too big
- `Nucleus_Status_AllocationFailed` an allocation failed
- `Nucleus_Status_IndexOutOfBounds` `index` is greater than the size of the `Nucleus_DynamicByteArray` object

If `index` is equal to `0` then the call
```
Nucleus_DynamicByteArray_insert(dynamicByteArray, memoryBlock, memoryBlockSize, index)
```
is equivalent to the call
```
Nucleus_DynamicByteArray_prepend(dynamicByteArray, memoryBlock, memoryBlockSize, index)
```

If `index` is the size of the list of Bytes in the `Nucleus_DynamicByteArray` object then the call
```
Nucleus_DynamicByteArray_insert(dynamicByteArray, memoryBlock, memoryBlockSize, index)
```
is equivalent to the call
```
Nucleus_DynamicByteArray_append(dynamicByteArray, memoryBlock, memoryBlockSize, index)
```

## Requirements

|                      | Windows                      | Linux                        |
|----------------------|------------------------------|------------------------------|
| *Header*             | `Nucleus/DynamicByteArray.h` | `Nucleus/DynamicByteArray.h` |
| *Static library*     | `Nucleus.Library.lib`        | `libNucleus.Library.a`       |
