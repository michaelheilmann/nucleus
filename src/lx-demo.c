#include "lx.h"

static void
the_main
	(
		lx_context *context,
		int number_of_arguments,
		char **arguments
	)
{
	printf("Hello, World!\n");
}

int
main
	(
		int argc,
		char **argv
	)
{
	lx_context context;
	if (!lx_context_initialize(&context))
	{
		return EXIT_FAILURE;
	}
	bool result = lx_context_run_main(&context, &the_main, argc, argv);
	lx_context_uninitialize(&context);
	return result ? EXIT_SUCCESS : EXIT_FAILURE;
}