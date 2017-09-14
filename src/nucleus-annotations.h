/// @file nucleus-annotations.h
/// @brief Function and parameter annotations.
#pragma once

/// @brief A function annotation indicating that the function never raises an error.
#define Nucleus_NoError()

/// @brief A function annotation which allow to indicate that pointer parameters expect non-null pointers.
/// @param ... list of 1-based parameter indices.
/// If the parameter index of a pointer parameter is in that list, then this indicates that the pointer parameter expects a non-null pointer.
/// An empty indicates that all pointer parameters expect non-null values.
#define Nucleus_NonNull(...)

/// @brief A parameter annotation indicating a parameter is an input parameter.
#define Nucleus_InputParameter(parameter) parameter

/// @brief A parameter annotation indicating a parameter is an output parameter.
#define Nucleus_OutputParameter(parameter) parameter

/// @brief A paraeter annotation indicating a parameter is an input and output parameter.
#define Nucleus_InputOutputParameter(parameter) parameter

/// @brief Alias for @a lx_input_output_parameter.
#define Nucleus_OutputInputParameter(parameter) parameter
