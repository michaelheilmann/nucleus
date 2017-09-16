#include "nucleus.h"

#include <assert.h>
#include <stdint.h>
#include <malloc.h>

Nucleus_NoError() bool
Nucleus_Context_initialize
	(
		Nucleus_Context *context
	)
{
	if (!context) return false;
	context->errorHandlers = NULL;
	context->numberOfAllocatedBlocks = 0;
	context->numberOfAllocatedBytes = 0;
	return true;
}

Nucleus_NoError() void
Nucleus_Context_uninitialize
	(
		Nucleus_Context *context
	)
{ /* Nothing to do yet. */ }

typedef struct Nucleus_MemoryBlock
{
	/// @brief The size, in Bytes, of this memory block.
	size_t size;
} Nucleus_MemoryBlock;

Nucleus_NoError() void *
Nucleus_allocate_noError
	(
		Nucleus_Context *context,
		size_t size
	)
{
	if (SIZE_MAX - sizeof(Nucleus_MemoryBlock) <= size)
	{
		return NULL;
	}
	Nucleus_MemoryBlock *block = malloc(sizeof(Nucleus_MemoryBlock) + size);
	if (!block)
	{
		return NULL;
	}
	block->size = size;
	context->numberOfAllocatedBlocks++;
	context->numberOfAllocatedBytes += size;
	return (char *)(block + 1);
	
}

Nucleus_NoError() void
Nucleus_deallocate_noError
	(
		Nucleus_Context *context,
		void *pointer
	)
{
	if (!pointer) { return; }
	Nucleus_MemoryBlock *block = ((Nucleus_MemoryBlock *)(pointer)) - 1;
	context->numberOfAllocatedBytes -= block->size;
	context->numberOfAllocatedBlocks--;
	free(block);
}

Nucleus_NoError() void
Nucleus_pushErrorHandler
	(
		Nucleus_Context *context,
		Nucleus_ErrorHandler *errorHandler
	)
{
	assert(NULL != context && NULL != errorHandler);
	errorHandler->previous = context->errorHandlers;
	context->errorHandlers = errorHandler;
}

Nucleus_NoError() void
Nucleus_popErrorHandler
	(
		Nucleus_Context *context
	)
{
	assert(NULL != context && NULL != context->errorHandlers);
	context->errorHandlers = context->errorHandlers->previous;
}

void
Nucleus_raiseError
	(
		Nucleus_Context *context
	)
{
	assert(NULL != context && NULL != context->errorHandlers);
	longjmp(context->errorHandlers->environment, -1);
}

Nucleus_NoError() bool
Nucleus_runMain
	(
		Nucleus_Context *context,
		Nucleus_Main *main,
		int numberOfArguments,
		char **arguments
	)
{
	Nucleus_ErrorHandler errorHandler;
	Nucleus_pushErrorHandler(context, &errorHandler);
	if (!setjmp(errorHandler.environment))
	{
		(*main)(context, numberOfArguments, arguments);
		Nucleus_popErrorHandler(context);
		return true;
	}
	else
	{
		Nucleus_popErrorHandler(context);
		return false;
	}
}
