/// @file Nucleus/FileSystem/getFileContentsLinux.h
/// @brief Get the contents of a file (Linux).
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann

#pragma once

#include "Nucleus/Configuration.h"

#if (Nucleus_OperatingSystem == Nucleus_OperatingSystem_LINUX)  || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_CYGWIN) || \
    (Nucleus_OperatingSystem == Nucleus_OperatingSystem_MACOS)

#include "Nucleus/FileSystem/getFileContentsInterface.h"

#endif
