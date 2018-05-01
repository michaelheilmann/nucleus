# `Nucleus_FileState`
*Enumeration of the states of a file.*

## C Signature
```
typedef enum Nucleus_FileState
{
    Nucleus_FileStatus_NotFound,
    Nucleus_FileStatus_Unknown,
    Nucleus_FileStatus_IsDirectory,
    Nucleus_FileStatus_IsRegular.
} Nucleus_FileState;
```

## Members
- `Nucleus_FileStatus_NotFound` the file was not found.
- `Nucleus_FileStatus_Unknown` the file was found but is of an unknown type.
- `Nucleus_FileStatus_IsDirectory` the file is a directory file
- `Nucleus_FileStatus_IsRegular` the file is a regular file

## Description
This is an enumeration of the states of a file.
Values of this type are created by `Nucleus_getFileState`.

## Requirements

|                      | Windows                  | Linux                   |
|----------------------|--------------------------|-------------------------|
| *Header*             | `Nucleus/FileSystem.h`   | `Nucleus/FileSystem.h`  |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`  |
