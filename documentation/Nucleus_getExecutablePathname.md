# `Nucleus_getExecutablePathname`
*Get the pathname of the executable.*

## C Signature
```
Nucleus_Status
Nucleus_getExecutablePathname`
    (
        char **executablePathname
    );
```

## Parameters
- `executablePathname` a pointer to a `char *` variable

## Description
This function get the pathname of the executable.
If this function succeeds, `*executablePathname` is assigned a pointer to a
zero-terminated UTF-8 string denoting the pathname of the executable.
If that string is not required anymore, it must be deallocated by a call to
[Nucleus_deallocateMemory](Nucleus_deallocateMemory.md).
If this function fails, a non-zero status code is returned.

## Requirements

|                      | Windows                          | Linux                             | macOS                             |
|----------------------|----------------------------------|-----------------------------------|------------------------------------
| *Header*             | `Nucleus/getExecutablePathname.h`| `Nucleus/getExecutablePathname.h` | `Nucleus/getExecutablePathname.h` |
| *Static library*     | `Nucleus.Library.lib`            | `libNucleus.Library.a`            | `libNucleus.Library.a`            |
