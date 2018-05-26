# `Nucleus_Atomic_decrementInteger`

Atomically increment the value of the variable pointed to by `v` by `1`.
This function always succeeds.
```
Nucleus_Status
Nucleus_Atomic_decrementInteger
    (
        volatile Nucleus_Integer *v
    )
```

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Atomic.h`       | `Nucleus/Atomic.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
