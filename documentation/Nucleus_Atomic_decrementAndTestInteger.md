# `Nucleus_Atomic_decrementAndte

Atomically decrement the value of the variable pointed to by `v` by `1`.
Assign to `r` `true` if the new value is `0` and `false` otherwise.
This function always succeeds.
```
Nucleus_Status
Nucleus_Atomic_decrementAndTestInteger
    (
        volatile Nucleus_Integer *v,
        Nucleus_Boolean *r
    )
```

## Requirements

|                      | Windows                  | Linux                     |
|----------------------|--------------------------|---------------------------|
| *Header*             | `Nucleus/Atomic.h`       | `Nucleus/Atomic.h`        |
| *Static library*     | `Nucleus.Library.lib`    | `libNucleus.Library.a`    |
