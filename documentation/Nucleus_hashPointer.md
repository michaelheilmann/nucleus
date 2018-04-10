#`Nucleus_hash[NumberType]`
*Compute the hash value of a pointer.*

# C Signature
```
Nucleus_NoError() Nucleus_NonNull() Nucleus_Status
Nucleus_hashPointer
    (
        const void *v,
        Nucleus_HashValue *hv
    );
```

## Parameters
- `v` a pointer value including the null pointer value
- `hv` a pointer to a `Nucleus_HashValue` variable

## Description
This function computes the hash value a pointer value.

`*hv* was assigned the hash value of `v` and `Nucleus_Status_Success` was returned if this function succeeded.
This function fails if and only if `hv` is a null pointer.
In that case, `Nucleus_Status_InvalidArgument` is returned.

## Requirements

|                      | Windows                                         | Linux                                           |
|----------------------|-------------------------------------------------|-------------------------------------------------|
| *Header*             | `Nucleus/Hash.h`                                | `Nucleus/Hash.h`                                |
| *Static library*     | `Nucleus.Library.lib`                           | `libNucleus.Library.a`                          |
