// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/CommandLine/CommandLine-private.c.i"

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_parse
    (
        Nucleus_CommandLine_Command **command,
        int numberOfArguments,
        char **arguments
    )
{
    if (!command || !arguments) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_CommandLine_Command *command_;
    status = Nucleus_CommandLine_Command_create(&command_);
    if (status) return status;

    // Add command parameters, command options, and option parameters.
    for (int argumentIndex = 1; argumentIndex < numberOfArguments; ++argumentIndex)
    {
        const char *argument = arguments[argumentIndex];
        status = parseArgument(command_, argument);
        if (status) { Nucleus_CommandLine_Command_destroy(command_); return status; }
    }
    *command = command_;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_create
    (
        Nucleus_CommandLine_Command **command
    )
{ return createCommand(command); }

Nucleus_NonNull() void
Nucleus_CommandLine_Command_destroy
    (
        Nucleus_CommandLine_Command *command
    )
{ destroyCommand(command); }

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_getParameterCount
    (
        Nucleus_CommandLine_Command *command,
        Nucleus_Size *parameterCount
    )
{
    if (!command) return Nucleus_Status_InvalidArgument;
    return ParameterList_getSize(&command->parameterList, parameterCount);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Option_getParameterCount
    (
        Nucleus_CommandLine_Option *option,
        Nucleus_Size *parameterCount
    )
{
    if (!option) return Nucleus_Status_InvalidArgument;
    return ParameterList_getSize(&option->parameterList, parameterCount);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_getParameter
    (
        Nucleus_CommandLine_Command *command,
        size_t index,
        Nucleus_CommandLine_Parameter **parameter
    )
{
    if (!command) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_PointerArray_at(&command->parameterList.array, index, (void **)parameter);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Option_getParameter
    (
        Nucleus_CommandLine_Option *option,
        size_t index,
        Nucleus_CommandLine_Parameter **parameter)
{
    if (!option) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_PointerArray_at(&option->parameterList.array, index, (void **)parameter);
}

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_addParameter
    (
        Nucleus_CommandLine_Command *command,
        const char *parameterValue
    )
{
    if (!command || !parameterValue) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_CommandLine_Parameter *parameter = NULL;
    status = Nucleus_allocateMemory((void **)&parameter, sizeof(Nucleus_CommandLine_Parameter));
    if (status) return status;
    status = Nucleus_cloneString(&parameter->value, parameterValue);
    if (status)
    {
        Nucleus_deallocateMemory(parameter);
        return Nucleus_Status_AllocationFailed;
    }
    status = ParameterList_append(&(command->parameterList), parameter);
    if (status) { destroyParameter(parameter); return status; }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_addOption
    (
        Nucleus_CommandLine_Command *command,
        const char *optionName,
        Nucleus_CommandLine_Option **option
    )
{
    if (!command || !optionName || !option) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_CommandLine_Option *option_;

    status = createOption(&option_, optionName);
    if (status) return status;

    status = OptionSet_add(&command->optionSet, option_);
    if (status) { destroyOption(option_); return status; }
    *option = option_;

    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Command_getOption
    (
        Nucleus_CommandLine_Command *command,
        const char *optionName,
        Nucleus_CommandLine_Option **option
    )
{ return OptionSet_find(&command->optionSet, optionName, option); }

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Option_addParameter
    (
        Nucleus_CommandLine_Option *option,
        const char *parameterValue
    )
{
    if (!option || !parameterValue) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;

    Nucleus_CommandLine_Parameter *parameter;
    status = createParameter(&parameter, parameterValue);
    if (status) return status;

    status = ParameterList_append(&(option->parameterList), parameter);
    if (status) { destroyParameter(parameter); return status; }

    return Nucleus_Status_Success;
}

Nucleus_NonNull() Nucleus_Status
Nucleus_CommandLine_Parameter_getValue
    (
        const Nucleus_CommandLine_Parameter *parameter,
        const char **parameterValue
    )
{
    if (!parameter || !parameterValue) return Nucleus_Status_InvalidArgument;
    *parameterValue = parameter->value;
    return Nucleus_Status_Success;
}
