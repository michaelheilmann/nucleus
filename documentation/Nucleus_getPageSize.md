# `Nucleus_getPageSize`
*Get the page size.`

## C Specification
```
Nucleus_Status
getPageSize
    (
        size_t *pageSize
    )
```

## Parameters
- `pageSize` a pointer to a `size_t` variable

## Description
This function gets the operating system system page size, in Bytes.

If this function succeeds, `*pageSize` is assigned the size, in Bytes, of a page of the operating system system page
and `Nucleus_Status_Success` is returned. This function fails if `pageSize` is a null pointer or the function fails
to determine the page size. In the former case `Nucleus_Status_InvalidArgument` is returned, in the latter case
`Nucleus_Status_EnvironmentError` is returned.

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/getPageSize.h`  | `Nucleus/getPageSize.h`   |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
