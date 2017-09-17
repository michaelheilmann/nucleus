/// @file nucleus-annotations.h
/// @brief Function and parameter annotations.
#pragma once

/// @brief A function annotation indicating that the function never raises an error.
#define Nucleus_NoError()

/// @brief A function annotation which allow to indicate that pointer parameters expect non-null pointers.
/// @param ... list of 1-based parameter indices.
/// If the parameter index of a pointer parameter is in that list, then this indicates that the pointer parameter expects a non-null pointer.
/// An empty indicates that all pointer parameters expect non-null values.
/// @details For example in following declaration this macro is used to annotate the parameters
/// @a y and @a w as expecing non-null argument values.
/// @code Spine_NonNull(2,4) void f(char *x, char *y, char *z, char *w); @endcode
/// Note that the parameter indices are 1-based.
#define Nucleus_NonNull(...)

/// @brief A parameter annotation indicating a parameter is an input parameter.
/// @details
/// This macro can be used to indicate that a parameter is an output parameter.
/// @param parameter the parameter declaration
/// @remarks
/// For example in the function declaration below this macro is used
/// to annotate the parameter @a x as an input and output parameter.
/// @code
/// int f(Nucleus_InputParameter(int *x), int y);
/// @endcode
#define Nucleus_InputParameter(parameter) parameter

/// @brief A parameter annotation indicating a parameter is an output parameter.
/// @details
/// This macro can be used to indicate that a parameter is an output parameter.
/// @param parameter the parameter declaration
/// @remarks
/// For example in the following function declaration below this macro is used
/// to annotate the parameter @a x as an output parameter.
/// @code
/// int f(Nucleus_OutputParameter(int *x), int y);
/// @endcode
#define Nucleus_OutputParameter(parameter) parameter

/// @brief A parameter annotation indicating a parameter is an input and output parameter.
/// @details
/// This macro can be used to indicate that a parameter is an output parameter.
/// @param parameter the parameter declaration
/// @remarks
/// For example in the following function declaration below this macro is used
/// to annotate the parameter @a x as an input and output parameter.
/// @code
/// int f(Nucleus_InputOutputParameter(int *x), int y);
/// @endcode
#define Nucleus_InputOutputParameter(parameter) parameter

/// @brief Alias for @code{Nucleus_InputOutputParameter}.
/// @param parameter the parameter declaration
#define Nucleus_OutputInputParameter(parameter) parameter
