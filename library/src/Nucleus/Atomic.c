#include "Nucleus/Atomic.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    #include "Nucleus/IncludesWindows.h"
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_Integer_increment
    (
        volatile Nucleus_Integer *v
    )
{
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    static_assert(sizeof(Nucleus_Integer) == 4, "Nucleus_Integer not of size 4");
    InterlockedIncrement(v);
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    __sync_add_and_fetch(v, 1);
#else
    #error("environment not supported")
#endif
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Integer_decrement
    (
        volatile Nucleus_Integer *v
    )
{
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    static_assert(sizeof(Nucleus_Integer) == 4, "Nucleus_Integer not of size 4");
    InterlockedDecrement(v);
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    __sync_sub_and_fetch(v, 1);
#else
    #error("environment not supported")
#endif
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_Integer_decrementAndTest
    (
        volatile Nucleus_Integer *v,
        Nucleus_Boolean *r
    )
{
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    static_assert(sizeof(Nucleus_Integer) == 4, "Nucleus_Integer not of size 4");
    *r = (0 == InterlockedDecrement(v));
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
      (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    *r = (0 == __sync_sub_and_fetch(v, 1));
#else
    #error("environment not supported")
#endif
    return Nucleus_Status_Success;
}
