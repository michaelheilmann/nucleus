#pragma once

#include "Nucleus/CommandLine/CommandLine.h"
#include "Nucleus/Memory.h"
#include "Nucleus/DynamicPointerArray.h"
#include "Nucleus/DynamicPointerHashMap.h"
#include <malloc.h> // For malloc() and free().
#include <string.h> // For strcmp() and strdup().
#include <stdio.h>  // For fprintf().

#if defined(Nucleus_Compiler_MSVC)
static char *
strndup
    (
        const char *s,
        size_t n
    );
#else
#define _strdup strdup
#endif

Nucleus_NonNull() static Nucleus_Status
parseArgument
    (
        Nucleus_CommandLine_Command *command,
        const char *argument
    );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct ParameterList
{ Nucleus_DynamicPointerArray array; } ParameterList;

Nucleus_NonNull() static Nucleus_Status
ParameterList_initialize
    (
        ParameterList *parameterList
    );

Nucleus_NonNull() static void
ParameterList_uninitialize
    (
        ParameterList *parameterList
    );

Nucleus_NonNull() static Nucleus_Status
ParameterList_append
    (
        ParameterList *parameterList,
        Nucleus_CommandLine_Parameter *parameter
    );

Nucleus_NonNull() static Nucleus_Status
ParameterList_getSize
    (
        ParameterList *parameterList,
        size_t *size
    );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct OptionSet
{ Nucleus_DynamicPointerHashMap hashMap; } OptionSet;

Nucleus_NonNull() static Nucleus_Status
hashFunction
    (
        const char *p,
        unsigned int *hv
    );

Nucleus_NonNull() static Nucleus_Status
equalToFunction
    (
        const char *p,
        const char *q,
        bool *r
    );

Nucleus_NonNull() static Nucleus_Status
OptionSet_initialize
    (
        OptionSet *optionSet
    );

Nucleus_NonNull() static void
OptionSet_uninitialize
    (
        OptionSet *optionSet
    );

Nucleus_NonNull() static Nucleus_Status
OptionSet_add
    (
        OptionSet *optionSet,
        Nucleus_CommandLine_Option *option
    );

Nucleus_NonNull() static Nucleus_Status
OptionSet_find
    (
        OptionSet *optionSet,
        const char *optionName,
        Nucleus_CommandLine_Option **option
    );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Nucleus_CommandLine_Command
{
    OptionSet optionSet;
    ParameterList parameterList;
}; // struct Nucleus_CommandLine_Command


Nucleus_NonNull() static Nucleus_Status
initializeCommand
    (
        Nucleus_CommandLine_Command *command
    );

Nucleus_NonNull() static void
uninitializeCommand
    (
        Nucleus_CommandLine_Command *command
    );

Nucleus_NonNull() static Nucleus_Status
createCommand
    (
        Nucleus_CommandLine_Command **command
    );

Nucleus_NonNull() static void
destroyCommand
    (
        Nucleus_CommandLine_Command *command
    );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Nucleus_CommandLine_Option
{
    char *name;
    ParameterList parameterList;
}; // struct Nucleus_CommandLine_Option

Nucleus_NonNull() static Nucleus_Status
createOption
    (
        Nucleus_CommandLine_Option **option,
        const char *optionName
    );

Nucleus_NonNull() static void
destroyOption
    (
        Nucleus_CommandLine_Option *option
    );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Nucleus_CommandLine_Parameter
{
    char *value;
}; // struct Nucleus_CommandLine_Parameter

Nucleus_NonNull() static Nucleus_Status
createParameter
    (
        Nucleus_CommandLine_Parameter **parameter,
        const char *parameterValue
    );

Nucleus_NonNull() static void
uninitializeParameter
    (
        Nucleus_CommandLine_Parameter *parameter
    );

Nucleus_NonNull() static void
destroyParameter
    (
        Nucleus_CommandLine_Parameter *parameter
    );
