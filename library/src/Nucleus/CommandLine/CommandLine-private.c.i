// Copyright (c) 2018 Michael Heilmann
#include "Nucleus/CommandLine/CommandLine-private.h.i"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if (Nucleus_C_Compiler == Nucleus_C_Compiler_MSVC)
static char *
strndup
    (
        const char *s,
        size_t n
    )
{
    char *result;
    size_t len = strlen(s);

    if (n < len)
        len = n;
    if (Nucleus_allocateMemory((void **)&result, len + 1))
    { return NULL; }

    result[len] = '\0';
    return (char *)memcpy(result, s, len);
}
#endif

Nucleus_NonNull() static Nucleus_Status
parseArgument
    (
        Nucleus_CommandLine_Command *command,
        const char *argument
    )
{
    Nucleus_Status status;
    if (argument[0] == '-')
    {
        argument++;
        // an option argument
        if (*argument == '-')
        {
            argument++;
        }
        else if (*argument == '\0')
        {
            fprintf(stderr, "invalid command-line argument, expected name\n");
            return Nucleus_Status_InvalidArgument;
        }
        const char *p = argument;
        while (*p != '\0' && *p != '=')
        {
            p++;
        }
        if (p == argument)
        {
            fprintf(stderr, "invalid command-line argument, expeted name\n");
            return Nucleus_Status_InvalidArgument;
        }
        char *name = strndup(argument, p - argument);
        if (Nucleus_Unlikely(!name)) { fprintf(stderr, "<internal error>\n"); return Nucleus_Status_AllocationFailed; }
        Nucleus_CommandLine_Option *option;
        status = Nucleus_CommandLine_Command_getOption(command, name, &option);
        if (status && status != Nucleus_Status_NotExists)
        { Nucleus_deallocateMemory(name); return status; }
        if (status == Nucleus_Status_NotExists)
            if (Nucleus_CommandLine_Command_addOption(command, name, &option))
            { Nucleus_deallocateMemory(name); return status; }
        Nucleus_deallocateMemory(name);
        argument = p;
        if (*argument == '\0') return Nucleus_Status_Success;
        else if (*argument == '=') argument++;
        p = argument;
        while (*p != '\0')
        {
            p++;
        }
        char *value = strndup(argument, p - argument);
        if (Nucleus_Unlikely(!value)) { fprintf(stderr, "<internal error>\n"); return Nucleus_Status_AllocationFailed; }
        status = Nucleus_CommandLine_Option_addParameter(option, value);
        if (status)
        { Nucleus_deallocateMemory(value); fprintf(stderr, "<internal error>\n"); return status; }
        Nucleus_deallocateMemory(value);
    }
    else
    {
        // a command parameter argument
        status = Nucleus_CommandLine_Command_addParameter(command, argument);
        if (status) { return status; }
    }
    return Nucleus_Status_Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Nucleus_NonNull() static Nucleus_Status
hashFunction
    (
        const char *p,
        Nucleus_HashValue *hashValue
    )
{ 
    if (Nucleus_Unlikely(!p)) return Nucleus_Status_InvalidArgument;
    return Nucleus_hashMemory(p, strlen(p), hashValue);
}

Nucleus_NonNull() static Nucleus_Status
equalToFunction
    (
        const char *p,
        const char *q,
        Nucleus_Boolean *equalTo
    )
{
    if (Nucleus_Unlikely(!p || !q || !equalTo)) return Nucleus_Status_InvalidArgument;
    *equalTo = !strcmp(p, q);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
OptionSet_initialize
    (
        OptionSet *optionSet
    )
{
    return Nucleus_Collections_PointerHashMap_initialize(&optionSet->hashMap,
                                                         16,
                                                         NULL,
                                                         NULL,
                                                         NUCLEUS_HASHFUNCTION(&hashFunction),
                                                         NUCLEUS_EQUALTOFUNCTION(&equalToFunction),
                                                         NULL,
                                                         NUCLEUS_UNLOCKFUNCTION(&destroyOption));
}

Nucleus_NonNull() static Nucleus_Status
OptionSet_uninitialize
    (
        OptionSet *optionSet
    )
{ return Nucleus_Collections_PointerHashMap_uninitialize(&optionSet->hashMap); }

Nucleus_NonNull() static Nucleus_Status
OptionSet_add
    (
        OptionSet *optionSet,
        Nucleus_CommandLine_Option *option
    )
{
    if (Nucleus_Unlikely(!optionSet || !option)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status = Nucleus_Collections_PointerHashMap_set(&optionSet->hashMap, option->name, option, false);
    if (status == Nucleus_Status_Exists)
    { return status; }
    else if (status)
    { return status; }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
OptionSet_find
    (
        OptionSet *optionSet,
        const char *optionName,
        Nucleus_CommandLine_Option **option
    )
{
    if (Nucleus_Unlikely(!optionSet || !optionName || !option)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status = Nucleus_Collections_PointerHashMap_get(&optionSet->hashMap, (void *)optionName, (void **)option);
    if (status == Nucleus_Status_NotExists)
    { return status; }
    else if (status)
    { return status; }
    return Nucleus_Status_Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Nucleus_NonNull() static Nucleus_Status
ParameterList_initialize
    (
        ParameterList *parameterList
    )
{
    if (!parameterList) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_PointerArray_initialize(&parameterList->array, 8,
                                                       NULL,
                                                       NUCLEUS_UNLOCKFUNCTION(&destroyParameter));
}

Nucleus_NonNull() static Nucleus_Status
ParameterList_uninitialize
    (
        ParameterList *parameterList
    )
{ return Nucleus_Collections_PointerArray_uninitialize(&parameterList->array); }

Nucleus_NonNull() static Nucleus_Status
ParameterList_append
    (
        ParameterList *parameterList,
        Nucleus_CommandLine_Parameter *parameter
    )
{ return Nucleus_Collections_PointerArray_append(&parameterList->array, parameter); }

Nucleus_NonNull() static Nucleus_Status
ParameterList_getSize
    (
        ParameterList *parameterList,
        Nucleus_Size *size
    )
{
    if (Nucleus_Unlikely(!parameterList)) return Nucleus_Status_InvalidArgument;
    return Nucleus_Collections_PointerArray_getSize(&parameterList->array, size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Nucleus_NonNull() static Nucleus_Status
createOption
    (
        Nucleus_CommandLine_Option **option,
        const char *optionName
    )
{
    if (Nucleus_Unlikely(!option || !optionName)) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_CommandLine_Option *self = NULL;
    status = Nucleus_allocateMemory((void **)&self, sizeof(Nucleus_CommandLine_Option));
    if (status) return status;
    status = ParameterList_initialize(&self->parameterList);
    if (status) { Nucleus_deallocateMemory(self); return status; }
    self->name = _strdup(optionName);
    if (!self->name)
    {
        ParameterList_uninitialize(&self->parameterList);
        Nucleus_deallocateMemory(self);
        return Nucleus_Status_AllocationFailed;
    }
    *option = self;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
destroyOption
    (
        Nucleus_CommandLine_Option *option
    )
{
    ParameterList_uninitialize(&option->parameterList);
    if (option->name)
    {
        Nucleus_deallocateMemory(option->name);
        option->name = NULL;
    }
    Nucleus_deallocateMemory(option);
    return Nucleus_Status_Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Nucleus_NonNull() static Nucleus_Status
createParameter
    (
        Nucleus_CommandLine_Parameter **parameter,
        const char *parameterValue
    )
{
    if (!parameter || !parameterValue) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_CommandLine_Parameter *self = NULL;
    status = Nucleus_allocateMemory((void **)&self, sizeof(Nucleus_CommandLine_Parameter));
    if (status) return status;
    self->value = _strdup(parameterValue);
    if (!self->value)
    {
        Nucleus_deallocateMemory(self);
        return Nucleus_Status_AllocationFailed;
    }
    *parameter = self;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
uninitializeParameter
    (
        Nucleus_CommandLine_Parameter *parameter
    )
{
    if (parameter->value)
    {
        Nucleus_deallocateMemory(parameter->value);
        parameter->value = NULL;
    }
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
destroyParameter
    (
        Nucleus_CommandLine_Parameter *parameter
    )
{
    uninitializeParameter(parameter);
    Nucleus_deallocateMemory(parameter);
    return Nucleus_Status_Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Nucleus_NonNull() static Nucleus_Status
initializeCommand
    (
        Nucleus_CommandLine_Command *command
    )
{
    if (!command) return Nucleus_Status_InvalidArgument;

    Nucleus_Status status;

    status = ParameterList_initialize(&command->parameterList);
    if (status) return status;

    status = OptionSet_initialize(&command->optionSet);
    if (status)
    {
        ParameterList_uninitialize(&command->parameterList);
        return status;
    }

    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
uninitializeCommand
    (
        Nucleus_CommandLine_Command *command
    )
{
    ParameterList_uninitialize(&command->parameterList);
    OptionSet_uninitialize(&command->optionSet);
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
createCommand
    (
        Nucleus_CommandLine_Command **command
    )
{
    if (!command) return Nucleus_Status_InvalidArgument;
    Nucleus_Status status;
    Nucleus_CommandLine_Command *o = NULL;
    status = Nucleus_allocateMemory((void **)&o, sizeof(Nucleus_CommandLine_Command));
    if (status) return status;
    status = initializeCommand(o);
    if (status)
    {
        Nucleus_deallocateMemory(o);
        return status;
    }
    *command = o;
    return Nucleus_Status_Success;
}

Nucleus_NonNull() static Nucleus_Status
destroyCommand
    (
        Nucleus_CommandLine_Command *command
    )
{
    uninitializeCommand(command);
    Nucleus_deallocateMemory(command);
    return Nucleus_Status_Success;
}
