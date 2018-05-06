# `Nucleus_getDirectorySeparator`
*Get the directory separator.*

## C Signature
```
Nucleus_Status
Nucleus_getDirectorySeparator`
    (
        const char **bytes,
        const Nucleus_Size *numberOfBytes
    );
```

## Parameters
- `bytes` a pointer to a `(const char *)` variable
- `numberOfBytes` a pointer to a `(const Nucleus_Size)` variable

## Description
This function gets the directory separator of the execution environment.
`*bytes` is assigned a pointer to a static const array of Bytes,
`*numberOfBytes` is assigned the number of Bytes in the array,
and `Nucleus_Status_Success` is returned if this function succeeds.

This function fails if and only if `bytes` or `numberOfBytes` is a null pointer.
`Nucleus_Status_InvalidArgument` is returned in that case.

The array of Bytes returned in the current version is a zero terminated C string,
the number of Bytes is the length, in Bytes, of that string including the zero terminator.
The directory separator on all known systems is the solidus (`/`), except for Windows where it is the reverse solidus (`\\`).

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/FileSystem.h`   | `Nucleus/FileSystem.h`    |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
