# `Nucleus_getDirectorySeparator`
*Get the directory separator.*

## C Signature
```
Nucleus_Status
Nucleus_getDirectorySeparator`
    (
        const char **directorySeparator
    );
```

## Parameters
- `directorySeparator` a pointer to a `(const char *)` variable

## Description
This function gets the directory separator of the execution environment.
`*directorySeparator` is assigned a pointer to a static constant zero-terminated UTF-8 string
and `Nucleus_Status_Success` is returned if this function succeeds.

This function fails if and only if `directorySeparator` is a null pointer.
`Nucleus_Status_InvalidArgument` is returned in that case.

The directory separator on all known systems is the solidus (`/`), except for Windows where it is the reverse solidus (`\\`).

## Requirements

|                      | Windows                  | Linux                     | macOS                  |
|----------------------|--------------------------|---------------------------|-------------------------
| *Header*             | `Nucleus/FileSystem.h`   | `Nucleus/FileSystem.h`    | `Nucleus/FileSystem.h` |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    | `libNucleus.Library.a` |
