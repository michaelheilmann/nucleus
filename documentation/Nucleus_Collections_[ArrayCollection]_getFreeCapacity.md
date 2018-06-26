# `Nucleus_Collections_[ArrayCollection]_getCapacity`
*Get the free capacity of a `Nucleus_Collections_[ArrayCollection]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_[ArrayCollection]_getFreeCapacity
    (
        Nucleus_Collections_[ArrayCollection] *arrayCollection,
        Nucleus_Size *freeCapacity
    );
```

## Parameters
- `arrayCollection` a pointer to an initialized `Nucleus_Collections_[ArrayCollection]` object
- `freeCapacity` a pointer to a `Nucleus_Size` variable

## Description
This function gets the free capacity, in Bytes, of a `Nucleus_Collections_[ArrayCollection]` object.

If this function succeeds,
- the free capacity, in Bytes, of the `Nucleus_Collections_[ArrayCollection]` object pointed to by `arrayCollection`
  was stored in the variable pointed to by `freeCapacity` and
- `Nucleus_Status_Success` was returned

This function fails if and only if `arrayCollection` and/or `freeCapacity` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.


## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Collections/[ArrayCollection].h`       | `Nucleus/Collections/[ArrayCollection].h`       |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
