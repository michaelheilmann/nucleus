/// @file nucleus-existing-file-policy.h
/// @brief An enumeration of policies for opening a file in case of that the file exists.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

/// @brief An enumeration of policies for opening a file in case of that the file exists.
/// @remarks The enumeration elements can not be combined.
typedef enum Nucleus_ExistingFilePolicy
{
	/// @brief Retaint the file.
	Nucleus_ExistingFilePolicy_Retain,

	/// @brief Truncate the file.
	Nucleus_ExistingFilePolicy_Truncate,

} Nucleus_ExistingFilePolicy;
