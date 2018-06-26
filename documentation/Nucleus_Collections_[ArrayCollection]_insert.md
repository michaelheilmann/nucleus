# `Nucleus_Collections_[ArrayCollection]_insert`
*Insert Bytes into the list of Bytes in a `Nucleus_Collections_[ArrayCollection]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_ByteArray_insert
    (
        Nucleus_Collections_[ArrayCollection] *arrayCollection,
        [Element] element,
        Nucleus_Size index
    );
```

## Parameters
- `arrayCollection` a pointer to an initialized `Nucleus_Collections_[ArrayCollection]` object
- `element` the element value of type [Array-Collection-Element-Type] or a const-qualified variant thereof
- `index` the index at which the Bytes shall be inserted

## Description
This function inserts an element into the list of elements of a `Nucleus_Collections_[ArrayCollection]` object.

If this function succeeds,
- the `element` was appended to the list of elements of the `Nucleus_Collections_[ArrayCollection]` object pointed to
  by `arrayCollection` and
- `Nucleus_Status_Success` was returned.

If this function succeeds,
- the `element` was  inserted into the list of elements of the `Nucleus_Collections_[ArrayCollection]` object pointed
  to by `arrayCollection` at the specified index `index` and 
- `Nucleus_Status_Success` was returned.

If this function fails, one of the non-zero status codes is returned
- `Nucleus_Status_InvalidArgument` `arrayCollection was a null pointer and/or `element` was not valid for this
  `Nucleus_Collections_[ArrayCollection]` type
- `Nucleus_Status_Overflow` the maximum number of elements was exceeded
- `Nucleus_Status_AllocationFailed` an allocation failed
- `Nucleus_Status_IndexOutOfBounds` `index` was greater than the size of the collection

If `i` is equal to `0` then the call
```
Nucleus_Collections_[ArrayCollection]_insert(c, e, i)
```
is equivalent to the call
```
Nucleus_Collections_[ArrayCollection]_prepend(c, e)
```

If `i` is the size of the collection `c` then the call
```
Nucleus_Collections_[ArrayCollection]_insert(c, e, i)
```
is equivalent to the call
```
Nucleus_Collections_[ArrayCollection]_append(c, e)
```

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Collections/[ArrayCollection].h`       | `Nucleus/Collections/[ArrayCollection].h`       |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
