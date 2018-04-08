# `Nucleus_Collections_[Array-Collection-Type]_getCapacity`
*Get the free capacity of a `Nucleus_Collections_[Array-Collection-Type]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_[Array-Collection-Type]_getFreeCapacity
    (
        Nucleus_Collections_[Array-Collection-Type] *arrayCollection,
        size_t *freeCapacity
    );
```

## Parameters
- `arrayCollection` a pointer to an initialized `Nucleus_Collections_[Array-Collection-Type]` object
- `freeCapacity` a pointer to a `size_t` variable

## Description
This function gets the free capacity, in Bytes, of a `Nucleus_Collections_[Array-Collection-Type]` object.

If this function succeeds,
- the free capacity, in Bytes, of the `Nucleus_Collections_[Array-Collection-Type]` object pointed to by `arrayCollection`
  was stored in the variable pointed to by `freeCapacity` and
- `Nucleus_Status_Success` was returned

This function fails if and only if `arrayCollection` and/or `freeCapacity` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.


## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Collections/[Array-Collection-Type].h` | `Nucleus/Collections/[Array-Collection-Type].h` |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
