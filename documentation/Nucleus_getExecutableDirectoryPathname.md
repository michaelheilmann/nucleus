# `Nucleus_getExecutableDirectoryPathname`
*Get the pathname of the executable directory.*

## C Signature
```
Nucleus_Status
Nucleus_getExecutableDirectory`
    (
        char **executableDirectoryPathname
    );
```

## Parameters
- `executableDirectoryPathname` a pointer to a `char *` variable

## Description
This function get the pathname of the executable directory.
If this function succeeds, `*executableDirectoryPathname` is assigned a pointer to a
zero-terminated UTF-8 string denoting the pathname of the executable directory.
If that string is not required anymore, it must be deallocated by a call to
[Nucleus_deallocateMemory](Nucleus_deallocateMemory.md).
If this function fails, a non-zero status code is returned.

## Requirements

|                      | Windows                                   | Linux                                      | macOS                                      |
|----------------------|-------------------------------------------|--------------------------------------------|---------------------------------------------
| *Header*             | `Nucleus/getExecutableDirectoryPathname.h`| `Nucleus/getExecutableDirectoryPathname.h` | `Nucleus/getExecutableDirectoryPathname.h` |
| *Static library*     | `Nucleus.Library.lib`                     | `libNucleus.Library.a`                     | `libNucleus.Library.a`                     |
