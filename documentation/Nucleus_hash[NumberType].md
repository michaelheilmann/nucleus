#`Nucleus_hash[NumberType]`
*Compute the hash value of an [NumberType].*

# C Signature
```
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hash[NumberType]
    (
        const Nucleus_Integer8 v,
        Nucleus_HashValue *hv
    );
```

## Parameters
- `v` an `[NumberType]` value
- `hv` a pointer to a `Nucleus_HashValue` variable

## Description
This function computes the hash value an [NumberType].

`*hv* was assigned the hash value of `v` and `Nucleus_Status_Success` was returned if this function succeeded.
This function fails if and only if `hv` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Hash.h`                                | `Nucleus/Hash.h`                                |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |