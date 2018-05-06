# `Nucleus_getPathSeparator`
*Get the path separator.*

## C Signature
```
Nucleus_Status
Nucleus_getPathSeparator`
    (
        const char **bytes,
        const Nucleus_Size *numberOfBytes
    );
```

## Parameters
- `bytes` a pointer to a `(const char *)` variable
- `numberOfBytes` a pointer to a `(const Nucleus_Size)` variable

## Description
This function gets the path separator of the execution environment.
`*bytes` is assigned a pointer to a static const array of Bytes,
`*numberOfBytes` is assigned the number of Bytes in the array,
and `Nucleus_Status_Success` is returned if this function succeeds.

This function fails if and only if `bytes` or `numberOfBytes` is a null pointer.
`Nucleus_Status_InvalidArgument` is returned in that case.

The array of Bytes returned in the current version is a zero terminated C string,
the number of Bytes is the length, in Bytes, of that string including the zero terminator.
The path separator on all known environments is `;`.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/FileSystem.h`   | `Nucleus/FileSystem.h`    |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
