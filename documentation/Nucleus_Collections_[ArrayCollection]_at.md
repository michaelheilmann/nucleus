# `Nucleus_Collections_[ArrayCollection]_at`
*Get the element at an index in the list of elements in a `Nucleus_Collections_[ArrayCollection]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_[ArrayCollection]_at
    (
        Nucleus_Collections_[ArrayCollection] *arrayCollection,
        Nucleus_Size index,
        [ArrayCollection.Element] *element
    )
```

## Parameters
- `arrayCollection` a pointer to an initialized `Nucleus_Collections_[ArrayCollection]` object
- `index` a zero-based index
- `element` a pointer to a `[ArrayCollection.Element]` variable

## Description 
This function gets the element at an index in the list of elements of a `Nucleus_Collections_[ArrayCollection]` object.

If this function succeeds,
- the `*element` was assigned the element and
- `Nucleus_Status_Success` was returned.

If this function fails, one of the following non-zero status codes is returned
- `Nucleus_Status_InvalidArgument` `arrayCollection` or `element` is a null pointer
- `Nucleus_Status_IndexOutOfBounds` `index` is greater than or equal to than the size of the collection
                                    ([Nucleus_Collections_[ArrayCollection]_getSize](Nucleus_Collections_[ArrayCollection]_getSize.md))
  								    number of elements was exceeded
- `Nucleus_Status_AllocationFailed` an allocation failed

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Collections/[ArrayCollection].h`       | `Nucleus/Collections/[ArrayCollection].h`       |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
