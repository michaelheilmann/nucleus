#include "Nucleus/C/strrstr.h"
#include "Nucleus/Status.h"
#include <stdlib.h>
#include <stdio.h>

Nucleus_Status
test
    (
    )
{
	static const struct {
		const char *h, *n;
		int pos;
	} test_array[] = {
		/* 0123456789 */
		{ "baaabaaab",  "aaa", 5  },
		{ "baaabaaaab", "aaa", 6  },
		{ "baaabaab",   "aaa", 1  },
		{ "aaa",        "aaa", 0  },
		{ "aaa",        "a",   2  },
		{ "aaa",        "bbb", -1 },
		{ "a",          "aaa", -1 },
		{ "aaa",        "",    3  },
		{ "",           "aaa", -1 },
		{ "",           "",    0  },
	};

	int i;

	i = 0;
	while (i < sizeof(test_array) / sizeof(test_array[0])) {
		const char *r = strrstr(test_array[i].h, test_array[i].n);
		printf("'%s' vs. '%s': '%s' - ", test_array[i].h, test_array[i].n, r);
		if (r == NULL)
			r = test_array[i].h - 1;
		printf("%s\n", r == test_array[i].h + test_array[i].pos ? "PASSED" : "FAILED");
        if (!(r == test_array[i].h + test_array[i].pos))
        {
            return Nucleus_Status_InternalError;
        }
		i++;
	}

	return Nucleus_Status_Success;
}

int main(int argc, char **argv)
{
    if (test()) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
