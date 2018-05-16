/// @file Nucleus/FileSystem/NonExistingFilePolicy.h
/// @brief An enumeration of policies for opening a file in case of that the file does not exist.
/// @author Michael Heilmann
/// @copyright Copyright (c) 2017, 2018 Michael Heilmann

#pragma once

/// @ingroup filesystem
/// @brief An enumeration of policies for opening a file in case of that the file does not exist.
/// @remarks The enumeration elements can not be combined.
typedef enum Nucleus_NonExistingFilePolicy
{
    /// @brief Fail.
    Nucleus_NonExistingFilePolicy_Fail,

    /// @brief Create the file.
    Nucleus_NonExistingFilePolicy_Create,

} Nucleus_NonExistingFilePolicy;
