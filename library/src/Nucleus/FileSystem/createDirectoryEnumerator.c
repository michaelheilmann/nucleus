#include "Nucleus/FileSystem/DirectoryEnumerator.h"

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux)
#include "Nucleus/FileSystem/DirectoryEnumeratorLinux.h"
#endif

#if defined(Nucleus_Platform_Windows)
#include "Nucleus/FileSystem/DirectoryEnumeratorWindows.h"
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_createDirectoryEnumerator
    (
        Nucleus_DirectoryEnumerator **directoryEnumerator
    )
{
#if defined(Nucleus_Platform_Linux)
    return Nucleus_DirectoryEnumeratorLinux_create((Nucleus_DirectoryEnumeratorLinux **)directoryEnumerator);
#endif

#if defined(Nucleus_Platform_Windows)
    return Nucleus_DirectoryEnumeratorWindows_create((Nucleus_DirectoryEnumeratorWindows **)directoryEnumerator);
#endif
}
