# `Nucleus_Collections_[Array-Collection-Type]_getCapacity`
*Get the capacity of a `Nucleus_Collections_[Array-Collection-Type]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_[Array-Collection-Type]_getCapacity
    (
        Nucleus_Collections_[Array-Collection-Type] *arrayCollection,
        Nucleus_Size *capacity
    );
```

## Parameters
- `arrayCollection` a pointer to an initialized `Nucleus_Collections_[Array-Collection-Type]` object
- `capacity` a pointer to a `Nucleus_Size` variable

## Descriptions
This function gets the capacity, in Bytes, of a `Nucleus_Collections_[Array-Collection-Type]` object.

If this function succeeds,
- the capacity, in Bytes, of the `Nucleus_Collections_[Array-Collection-Type]` object pointed to by `arrayCollection` was
  stored in the variable pointed to by `capacity` and
- `Nucleus_Status_Success` was returned

This function fails if and only if `arrayCollection` and/or `capacity` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Collections/[Array-Collection-Type].h` | `Nucleus/Collections/[Array-Collection-Type].h` |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
