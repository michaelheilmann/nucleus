#include "Nucleus/C/strrstr.h"

#include <string.h>

char *strrstr(const char *haystack, const char *needle)
{
	char *r = NULL;
	if (!needle[0]) // empty needle
		return (char*)haystack + strlen(haystack);
	while (1) {
		char *p = strstr(haystack, needle);
		if (!p)
			return r;
		r = p;
		haystack = p + 1;
	}
}
    