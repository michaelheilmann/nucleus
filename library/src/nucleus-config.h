/// @file nucleus-config.h
/// @brief The configuration file of Nucleus.
/// @author Michael Heilmann
/// @copyright Copyright (c) Michael Heilmann 2017

#pragma once

#if defined(__clang__)
    /// @brief If defined, the compiler compiling this program is "Clang".
    #define Nucleus_Compiler_Clang
#endif

#if defined(__GNUC__)
    /// @brief If defined, then compiler compiling this program is "GCC".
    #define Nucleus_Compiler_GCC
#endif

#if defined(_MSC_VER)
    /// @brief If defined, then the compiler compiling this program is "Visual C++".
    #define Nucleus_Compiler_MSVC
#endif
