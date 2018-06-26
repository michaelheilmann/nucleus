# `Nucleus_Collections_[ArrayCollection]_getCapacity`
*Ensure the free capacity of a `Nucleus_Collections_[ArrayCollection]` is greater than or equal to a required free capacity.*

## C Specification
```
Nucleus_Status
Nucleus_Collections_[ArrayCollection]_ensureFreeCapacity
    (
        Nucleus_Collections_[ArrayCollection] *arrayCollection,
        Nucleus_Size requiredFreeCapacity
    )
```

## Parameters
- `arrayCollection` a pointer to an initialized `Nucleus_Collections_[ArrayCollection]` object
- `requiredFreeCapacity` the required free capacity

## Description
*Ensure the free capacity of a `Nucleus_Collections_[ArrayCollection]` is greater than or equal to a required free capacity.*

If this function succeeds the free capacity of the `Nucleus_Collections_[ArrayCollection]` pointed to by `arrayCollection`
is greater than or equal to the required free capacity `requiredFreeCapacity` and `Nucleus_Status_Success` is returned.
If this function fails, one of the following non-zero status codes is returned
- `Nucleus_Status_InvalidArgument` `arrayCollection` is a null pointer
- `Nucleus_Status_Overflow` `requiredFreeCapacity` is too big
- `Nucleus_Status_AllocationFailed` an allocation failed

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Collections/[ArrayCollection].h`       | `Nucleus/Collections/[ArrayCollection].h`       |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
