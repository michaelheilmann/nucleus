# `Nucleus_Collections_[Collection-Type]_getSize`
*Get the size of a `Nucleus_Collections_[Collection-Type]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_[Collection-Type]_getSize
    (
        Nucleus_Collections_[Collection-Type] *collection,
        size_t *size
    );
```

## Parameters
- `collection` a pointer to an initialized `Nucleus_Collections_[Collection-Type]` object
- `size` a pointer to a `size_t` variable

## Descriptions
This function gets the size, in Bytes, of a `Nucleus_Collections_[Collection-Type]` object.

If this function succeeds,
- the size, in Bytes, of the `Nucleus_Collections_[Collection-Type]` object pointed to by `collection` was stored in the
  variable pointed to by `size` and
- `Nucleus_Status_Success` was returned

This function fails if and only if `collection` and/or `size` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                                   | Linux                                     |
|----------------------|-------------------------------------------|-------------------------------------------|
| *Header*             | `Nucleus/Collections/[Collection-Type].h` | `Nucleus/Collections/[Collection-Type].h` |
| *Static library*     | `Nucleus.Library.lib`                     | `libNucleus.Library.a`                    |
