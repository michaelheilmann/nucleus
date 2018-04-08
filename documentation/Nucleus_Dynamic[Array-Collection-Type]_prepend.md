# `Nucleus_Dynamic[Array-Collection-Type]_prepend`
*Prepend an element to the list of elements in a `Nucleus_Dynamic[Array-Collection-Type]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Dynamic[Array-Collection-Type]_prepend
    (
        Nucleus_Dynamic[Array-Collection-Type] *arrayCollection,
        [ElementType] element
    )
```

## Parameters
- `arrayCollection` a pointer to an initialized `Nucleus_Dynamic[Array-Collection-Type]` object
- `element` the element value of type [Array-Collection-Element-Type] or a const-qualified variant thereof

## Description
This function prepends an element the list of elements in a `Nucleus_Dynamic[Array-Collection]` object.

If this function succeeds,
- the `element` was appended to the list of elements of the `Nucleus_Dynamic[Array-Collection-Type]` object pointed to
  by `arrayCollection` and
- `Nucleus_Status_Success` was returned.

If this function fails, one of the following non-zero status codes is returned
- `Nucleus_Status_InvalidArgument` `arrayCollection` is a null pointer or and/or `element` is invalid for this
  `Nucleus_Dynamic[Array-Collection-Type]` type
- `Nucleus_Status_Overflow` the maximum number of elements was exceeded
- `Nucleus_Status_AllocationFailed` an allocation failed

## Requirements

|                      | Windows                                    | Linux                                      |
|----------------------|--------------------------------------------|--------------------------------------------|
| *Header*             | `Nucleus/Dynamic[Array-Collection-Type].h` | `Nucleus/Dynamic[Array-Collection-Type].h` |
| *Static library*     | `Nucleus.Library.lib`                      | `libNucleus.Library.a`                     |
