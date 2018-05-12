#include "Nucleus/FileSystem/DirectoryEnumerator.h"

#include "Nucleus/Configuration.h"

#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)
	#include "Nucleus/FileSystem/DirectoryEnumeratorLinux.h"
#elif defined(Nucleus_Platform_Windows)
	#include "Nucleus/FileSystem/DirectoryEnumeratorWindows.h"
#else
	#error("platform not supported")
#endif

Nucleus_NonNull() Nucleus_Status
Nucleus_createDirectoryEnumerator
    (
        Nucleus_DirectoryEnumerator **directoryEnumerator
    )
{
#if defined(Nucleus_Platform_Linux) || defined(Nucleus_Platform_Osx)
    return Nucleus_DirectoryEnumeratorLinux_create((Nucleus_DirectoryEnumeratorLinux **)directoryEnumerator);
#elif defined(Nucleus_Platform_Windows)
    return Nucleus_DirectoryEnumeratorWindows_create((Nucleus_DirectoryEnumeratorWindows **)directoryEnumerator);
#else
	#error("platform not supported")
#endif
}
