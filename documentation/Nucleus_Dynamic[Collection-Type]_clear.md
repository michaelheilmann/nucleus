# `Nucleus_Dynamic[Collection-Type]_clear`
*Clear a `Nucleus_Dynamic[Collection-Type]` object.*

## C Signature
```
Nucleus_Status
Nucleus_Dynamic[Collection-Type]_clear
    (
        Nucleus_Dynamic[Collection-Type] *collection
    );
```

## Parameters
- `collection` a pointer to an initialized `Nucleus_[Collection-Type]` object
 
## Descriptions
This function clears a `Nucleus_Dynamic[Collection-Type]` object.

If this function succeeds, the size of the `Nucleus_Dynamic[Collection-Type]` object is zero.
This function fails if and only if `collection` is  null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                              | Linux                                |
|----------------------|--------------------------------------|--------------------------------------|
| *Header*             | `Nucleus/Dynamic[Collection-Type].h` | `Nucleus/Dynamic[Collection-Type].h` |
| *Static library*     | `Nucleus.Library.lib`                | `libNucleus.Library.a`               |
