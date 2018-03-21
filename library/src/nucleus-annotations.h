/// @file nucleus-annotations.h
/// @brief Function, parameter, and expression annotations.
#pragma once

#include "nucleus-config.h"

/// @defgroup Annotations annotations
/// @brief Function, parameter, and expression annotations.

/// @ingroup Annotations
/// @brief A function annotation indicating that the function never raises an error.
#define Nucleus_NoError()

// https://github.com/primordialmachine/blob/master/documentation/Nucleus_NonNull.md
#if defined(Nucleus_Compiler_GCC)
    #define Nucleus_NonNull(...) __attribute__ ((nonnull(__VA_ARGS__))) /**< @hideinitializer */
#else
    #define Nucleus_NonNull(...)
#endif

/// @ingroup Annotations
/// @brief A function annotation indicating that a function return value should be a non-null pointer.
#if defined(Nucleus_Compiler_GCC) && !defined(DOXYGEN)
    #define Nucleus_ReturnNonNull() __attribute__ ((returns_nonnull) /**< @hideinitializer */
#else
    #define Nucleus_ReturnNonNull()
#endif

// // https://github.com/primordialmachine/blob/master/documentation/Nucleus_NoReturn.md
#if defined(Nucleus_Compiler_GCC) && !defined(DOXYGEN)
    #define Nucleus_NoReturn() __attribute__ ((noreturn)) /**< @hideinitializer */
#elif defined(Nucleus_Compiler_MSVC) && !defined(DOXYGEN)
    #define Nucleus_NoReturn() __declspec(noreturn) /**< @hideinitializer */
#else
    #define Nucleus_NoReturn()
#endif

/// @ingroup Annotations
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
#define Nucleus_InputParameter(parameter) parameter /**< @hideinitializer */

/// @ingroup Annotations
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
#define Nucleus_OutputParameter(parameter) parameter /**< @hideinitializer */

/// @ingroup Annotations
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
#define Nucleus_InputOutputParameter(parameter) parameter /**< @hideinitializer */

/// @ingroup Annotations
/// @brief Alias for Nucleus_InputOutputParameter.
/// @param parameter the parameter declaration
#define Nucleus_OutputInputParameter(parameter) parameter /**< @hideinitializer */

/// @ingroup Annotations
/// @brief Expression annotation. Provides branch prediction information.
/// @details Given an expression @a e this macro evaluates to @a 1 or @a 0.depending on wether @a e evalutates to logically true or logically false.
///          The branch prediction assumption is that @a e is more likely to evaluate to logically true.
/// @param expression an expression
#if defined(Nucleus_Compiler_GCC)
    #define Nucleus_Likely(expression) (__builtin_expect((expression) ? 1 : 0, 1)) /**< @hideinitializer */
#else
    #define Nucleus_Likely(expression) (expression) /**< @hideinitializer */
#endif

/// @ingroup Annotations
/// @brief Expression annotation. Provides branch prediction information.
/// @details Given an expression @a e this macro evaluates to @a 1 or @a 0.depending on wether @a e evaluates to logically true or logically false.
///          The branch prediction assumption is that @a e is more likely to evaluate to logically false.
/// @param expresion an expression
#if defined(Nucleus_Compiler_GCC)
    #define Nucleus_Unlikely(expression) (__builtin_expect((expression) ? 1 : 0, 0)) /**< @hideinitializer */
#else
    #define Nucleus_Unlikely(expression) (expression) /**< @hideinitializer */
#endif
