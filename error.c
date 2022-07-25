#include <stdio.h>

#include "error.h"

void print_error(status_t status)
{
	char * errors_dictionary[MAX_ERRORS]=
	{
		"Null pointer.",
		"Insufficient memory.",
		"Incorrect program invocation.",
		"Unable to open file.",
		"Unable to write in file",
		"Invalid data"
	};

	fprintf(stderr, "%s\n", errors_dictionary[status]);
}
