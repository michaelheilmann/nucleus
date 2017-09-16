/// @file nucleus-file-access-mode.h
/// @brief An enumeration of file access modes to files.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

/// @brief An enumeration of file access modes to files.
/// @remarks The enumeration elements can be combined.
typedef enum Nucleus_FileAccessMode
{
	/// @brief Read access.
	/// @remark Can be combined with Nucleus_AccessMode_Write.
	Nucleus_FileAccessMode_Read = 1,

	/// @brief Write access.
	/// @remark Can be combined with Nucleus_AccessMode_Read.
	Nucleus_FileAccessMode_Write = 2,

	/// @brief Read and write access.
	/// @remark Alias for @code{Nucleus_FileAccessMode_Read|Nucleus_FileAccessMode_Write}.
	/// Alias for @code{Nucleus_FileAccessMode_WriteRead}.
	Nucleus_FileAccessMode_ReadWrite = Nucleus_FileAccessMode_Read | Nucleus_FileAccessMode_Write,
	
	/// @brief Write and read access.
	/// @remark Alias for @code{Nucleus_FileAccessMode_Write|Nucleus_FileAccessMode_Read}.
	/// Alias for @code{Nucleus_FileAccessMode_ReadWrite}.
	Nucleus_FileAccessMode_WriteRead = Nucleus_FileAccessMode_Write | Nucleus_FileAccessMode_Read,

} Nucleus_FileAccessMode;
