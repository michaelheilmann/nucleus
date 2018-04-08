# `Nucleus_Collections_[Collection-Type]_clear`
*Clear a `Nucleus_Collections_[Collection-Type]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Collections_[Collection-Type]_clear
    (
        Nucleus_Collections_[Collection-Type] *collection
    );
```

## Parameters
- `collection` a pointer to an initialized `Nucleus_[Collection-Type]` object
 
## Descriptions
This function clears a `Nucleus_Collections_[Collection-Type]` object.

If this function succeeds, the size of the `Nucleus_Collections_[Collection-Type]` object is zero.
This function fails if and only if `collection` is  null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                                   | Linux                                     |
|----------------------|-------------------------------------------|-------------------------------------------|
| *Header*             | `Nucleus/Collections/[Collection-Type].h` | `Nucleus/Collections/[Collection-Type].h` |
| *Static library*     | `Nucleus.Library.lib`                     | `libNucleus.Library.a`                    |
