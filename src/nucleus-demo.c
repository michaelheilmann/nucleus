#include "nucleus.h"
#include <stdio.h>

static void
theMain
	(
		Nucleus_Context *context,
		int numberOfArguments,
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
	Nucleus_Context context;
	if (!Nucleus_Context_initialize(&context))
	{
		return EXIT_FAILURE;
	}
	bool result = Nucleus_runMain(&context, &theMain, argc, argv);
	Nucleus_Context_uninitialize(&context);
	return result ? EXIT_SUCCESS : EXIT_FAILURE;
}