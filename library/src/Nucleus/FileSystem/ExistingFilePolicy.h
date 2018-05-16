/// @file Nucleus/FileSystem/ExistingFilePolicy.h
/// @brief An enumeration of policies for opening a file in case of that the file exists.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann

#pragma once

/// @ingroup filesystem
/// @brief An enumeration of policies for opening a file in case of that the file exists.
/// @remarks The enumeration elements can not be combined.
typedef enum Nucleus_ExistingFilePolicy
{
    /// @brief Retaint the file.
    Nucleus_ExistingFilePolicy_Retain,

    /// @brief Truncate the file.
    Nucleus_ExistingFilePolicy_Truncate,

} Nucleus_ExistingFilePolicy;
