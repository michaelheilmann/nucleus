// A command is split into an array of strings named arguments.
// Argument 0 is (normally) the command name, argument 1, the first element following the command, and so on.
//
// - An "option" is a documented type of argument modifying the behaviour of a command
// e.g. "-v" or "--verbose" are options.
//
// - A "parameter" is an argument that provides information to either the command or one of its options,
// e.g. in "-o file", "file" is the parameter of the "-o" option.
#pragma once

#include "Nucleus/Annotations.h"
#include "Nucleus/Status.h"
#include <stddef.h> // For size_t.

typedef struct Nucleus_CommandLine_Parameter Nucleus_CommandLine_Parameter;
typedef struct Nucleus_CommandLine_Option Nucleus_CommandLine_Option;
typedef struct Nucleus_CommandLine_Command Nucleus_CommandLine_Command;

/// @brief Create a @a (Nucleus_CommandLine_Command) object.
/// @param [out] command a pointer to a @a (Nucleus_CommandLine_Command) variable
/// @param numberOfArguments the number of command-line arguments
/// @param arguments a pointer to an array of @a numberOfArguments pointers to command-line arguments
/// @return #Nucleus_Status_Success on success, one of the following status codes on failure:
/// - #Nucleus_Status_InvalidArgument @a command is a null pointer
/// - #Nucleus_Status_AllocationFailed an allocation failed
/// @post @a (*command) was assigned a pointer to a @a (Nucleus_CommandLine_Command) object
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_parse
    (
        Nucleus_CommandLine_Command **command,
        int numberOfArguments,
        char **arguments
    );

/// @brief Create a @a (Nucleus_CommandLine_Command) object.
/// @param [out] command a pointer to a @a (Nucleus_CommandLine_Command) variable
/// @return #Nucleus_Status_Success on success, one of the following status codes on failure:
/// - #Nucleus_Status_InvalidArgument @a command is a null pointer
/// - #Nucleus_Status_AllocationFailed an allocation failed
/// @post @a (*command) was assigned a pointer to a @a (Nucleus_CommandLine_Command) object
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_create
    (
        Nucleus_CommandLine_Command **command
    );

/// @brief Destroy a @a (Nucleus_CommandLine_Command) object.
/// @param command a pointer to the @a (Nucleus_CommandLine_Command) object
Nucleus_NonNull() void
Nucleus_CommandLine_Command_destroy
    (
        Nucleus_CommandLine_Command *command
    );

/// @brief Get the number of parameters of a @a (Nucleus_CommandLine_Command) object.
/// @param command a pointer to the @a (Nucleus_CommandLine_Command) object
/// @return #Nucleus_Status_Success on success, one of the folowing status codes is returned on failure:
/// - #Nucleus_Status_InvalidArgument @a command or @a parameterCount is a null pointer
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_getParameterCount
    (
        Nucleus_CommandLine_Command *command,
        size_t *parameterCount
    );

/// @brief Get the number of parameters of a @a (Nucleus_CommandLine_Option) object.
/// @param command a pointer to the @a (Nucleus_CommandLine_Option) object
/// @return #Nucleus_Status_Success on success, one of the folowing status codes is returned on failure:
/// - #Nucleus_Status_InvalidArgument @a command or @a parameterCount is a null pointer
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Option_getParameterCount
    (
        Nucleus_CommandLine_Option *option,
        size_t *parameterCount
    );

// i-th parameter
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_getParameter
    (
        Nucleus_CommandLine_Command *command,
        size_t index,
        Nucleus_CommandLine_Parameter **parameter
    );

// i-th parameter
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Option_getParameter
    (
        Nucleus_CommandLine_Option *option,
        size_t index,
        Nucleus_CommandLine_Parameter **parameter
    );

/// @brief Add a parameter to a @a (Nucleus_CommandLine_Command) object.
/// @param command a pointer to the @a (Nucleus_CommandLine_Command) object
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_addParameter
    (
        Nucleus_CommandLine_Command *command,
        const char *parameterValue
    );

/// @brief Add a parameter to a @a (Nucleus_CommandLine_Option) object.
/// @param option a pointer to the @a (Nucleus_CommandLine_Option) object
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Option_addParameter
    (
        Nucleus_CommandLine_Option *option,
        const char *parameterValue
    );

/// Add an option to a command.
/// @param command a pointer to the @a (Nucleus_CommandLine_Command) object
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_addOption
    (
        Nucleus_CommandLine_Command *command,
        const char *optionName,
        Nucleus_CommandLine_Option **opt
     );

// Find option: Return NULL if option was not found.
/// @param command a pointer to the @a (Nucleus_CommandLine_Command) object
/// @param optionName a pointer to constant C string, the option name
/// @param [out] option a pointer to a @a (Nucleus_CommandLine_Option) variable
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_getOption
    (
        Nucleus_CommandLine_Command *command,
        const char *optionName,
        Nucleus_CommandLine_Option **option
    );

/// @brief Get the value of a @a (Nucleus_CommandLine_Parameter) object.
/// @param parameter a pointer to the @a (Nucleus_CommandLine_Parameter) object
/// @param [out] parameterValue a pointer to a @a (const char *) variable
Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Parameter_getValue
    (
        const Nucleus_CommandLine_Parameter *parameter,
        const char **parameterValue
    );
