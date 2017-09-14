#include "lx.h"

#include <assert.h>
#include <stdint.h>
#include <malloc.h>

lx_no_error() bool
lx_context_initialize
	(
		lx_context *context
	)
{
	if (!context) return false;
	context->error_handlers = NULL;
	context->number_of_allocated_blocks = 0;
	context->number_of_allocated_bytes = 0;
	return true;
}

lx_no_error() void
lx_context_uninitialize
	(
		lx_context *context
	)
{ /* Nothing to do yet. */ }

typedef struct lx_memory_block
{
	size_t size;
} lx_memory_block;

lx_no_error() void *
lx_allocate
	(
		lx_context *context,
		size_t size
	)
{
	if (SIZE_MAX - sizeof(lx_memory_block) <= size)
	{
		return NULL;
	}
	lx_memory_block *block = malloc(sizeof(lx_memory_block) + size);
	if (!block)
	{
		return NULL;
	}
	block->size = size;
	context->number_of_allocated_blocks++;
	context->number_of_allocated_bytes += size;
	return (char *)(block + 1);
	
}

lx_no_error() void
lx_deallocate_no_error
	(
		lx_context *context,
		void *pointer
	)
{
	if (!pointer) { return; }
	lx_memory_block *block = ((lx_memory_block *)(pointer)) - 1;
	context->number_of_allocated_bytes -= block->size;
	context->number_of_allocated_blocks--;
	free(block);
}

lx_no_error() void
lx_context_push_error_handler
	(
		lx_context *context,
		lx_error_handler *error_handler
	)
{
	assert(NULL != context && NULL != error_handler);
	error_handler->previous = context->error_handlers;
	context->error_handlers = error_handler;
}

lx_no_error() void
lx_context_pop_error_handler
	(
		lx_context *context
	)
{
	assert(NULL != context && NULL != context->error_handlers);
	context->error_handlers = context->error_handlers->previous;
}

void
lx_context_raise_error
	(
		lx_context *context
	)
{
	assert(NULL != context && NULL != context->error_handlers);
	longjmp(context->error_handlers->environment, -1);
}

lx_no_error() bool
lx_context_run_main
	(
		lx_context *context,
		lx_main *main,
		int number_of_arguments,
		char **arguments
	)
{
	lx_error_handler error_handler;
	lx_context_push_error_handler(context, &error_handler);
	if (!setjmp(error_handler.environment))
	{
		(*main)(context, number_of_arguments, arguments);
		lx_context_pop_error_handler(context);
		return true;
	}
	else
	{
		lx_context_pop_error_handler(context);
		return false;
	}
}
