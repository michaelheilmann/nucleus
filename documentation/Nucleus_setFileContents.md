# `Nucleus_setFileContents`
*Set the contents of a file.*

## C Signature
```
Nucleus_Status
Nucleus_setFileContents
    (
        const char *pathname,
        const char *memoryBlock,
        size_t memoryBlockSize
    )
```

## Parameters
- `pathname`: a pointer to the pathname of the file
- `memoryBlock` the address of aa memory block of `numberOfBytes` Bytes
- `memoryBlockSize` the size, in Bytes, of the memory block pointed to by `memoryBlockPointer`
   Not that as usual `0` is a valid size, in Bytes, of a memory block.

## Description
This function sets the contents of a file.

If this function succeeds, the contents of the file equal the contents of the memory block specified by
`memoryBlock` and `memoryBlockSize` and `Nucleus_Status_Success` is returned. If the file did not exist,
it was created, if it did exist it was overwritten.

This function fails if `pathname` or `memoryBlock` is a null pointer. `Nucleus_Status_InvalidArgument`
is returned in that case. If this function fails with `Nucleus_Status_EnvironmentFailed`, then the
environment failed or refused to provide service. In that case it is undetermined wether the file
exists and if it exists what its contents are.
