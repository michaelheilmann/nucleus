#include "Nucleus/FileSystem/DirectoryEnumerator.h"

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  ||\
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) ||\
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    #include "Nucleus/FileSystem/DirectoryEnumeratorLinux.h"
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    #include "Nucleus/FileSystem/DirectoryEnumeratorWindows.h"
#else
    #error("operating system not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_createDirectoryEnumerator
    (
        Nucleus_DirectoryEnumerator **directoryEnumerator
    )
{
#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)
    return Nucleus_DirectoryEnumeratorLinux_create((Nucleus_DirectoryEnumeratorLinux **)directoryEnumerator);
#elif (Nucleus_OperatingSystem == Nucleus_OperatingSystem_WINDOWS)
    return Nucleus_DirectoryEnumeratorWindows_create((Nucleus_DirectoryEnumeratorWindows **)directoryEnumerator);
#else
    #error("operating system not supported")
#endif
}
