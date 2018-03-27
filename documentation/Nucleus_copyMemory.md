# `Nucleus_copyMemory`
*Copy contents of a memory block to another memory block.*

## C Specification
```
Nucleus_Status
Nucleus_copyMemory
    (
        void *p,
        void *q,
        size_t n
    )
```

## Parameters
- `p` a pointer to the first Byte of the target memory block
- `q` a pointer to the first Byte of the source memory block
- `n` the number of Byte to copy. Note that @a 0 is a valid number of Bytes.

## Description
This function copies contents of a memory block to another memory block.

If this function succeeds, `n` Bytes were copied from the memory block pointed to by `q` to the memory block pointed to by `p`.
Otherwise a non-zero status code is returned. In particular, if `p` or `q` is a null pointer `Nucleus_Status_InvalidArgument` is returned.
The source and the target memory blocks may or may not overlap.
