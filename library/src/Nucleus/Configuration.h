/// @file Nucleus/Configuration.h
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

#if defined(WIN32) || defined(_WIN32) || defined (__WIN32) || defined(__WIN32__) || defined(__WIN64__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64)
    /// @brief If defined, then the target platform is "Windows".
    #define Nucleus_Platform_Windows
#endif

#if defined(__CYGWIN__) || defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux)
    /// @brief If defined, then the target platform is "Linux".
    #define Nucleus_Platform_Linux
#endif
