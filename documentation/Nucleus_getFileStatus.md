# `Nucleus_getFileState`
*Get the state of a file.*

## C Signature
```
Nucleus_Status
Nucleus_getFileState
    (
        const char *pathname,
        Nucleus_FileState *fileState
    )
```

## Parameters
- `pathname` a pointer to a pathname string
- `fileState` a pointer to a `Nucleus_FileState` variable

## Description
This function gets the state of a file.

If this function succeeds it returns `Nucleus_Status_Success` and `*fileState` was assigned a `Nucleus_FileState` value.

This function fails if and only if one of the following conditions is true_
- `pathname` or `fileStatus` are null pointers or the pathname pointed to by `pathname` is not a valid pathname.
   `Nucleus_Status_InvalidArgument` is returned in these cases.
- The environment fails.
  `Nucleus_Status_EnvironmentError` is returned in this case.
- An allocation fails.
  `Nucleus_Status_AllocationFailed` is returned in this case.

## Requirements

|                      | Windows                  | Linux                   |
|----------------------|--------------------------|-------------------------|
| *Header*             | `Nucleus/FileSystem.h`   | `Nucleus/FileSystem.h`  |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`  |
