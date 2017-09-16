/// @file nucleus-non-existing-file-policy.h
/// @brief An enumeration of policies for opening a file in case of that the file does not exist.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

/// @brief An enumeration of policies for opening a file in case of that the file does not exist.
/// @remarks The enumeration elements can not be combined.
typedef enum Nucleus_NonExistingFilePolicy
{
	/// @brief Fail.
	Nucleus_NonExistingFilePolicy_Fail,

	/// @brief Create the file.
	Nucleus_NonExistingFilePolicy_Create,

} Nucleus_NonExistingFilePolicy;
