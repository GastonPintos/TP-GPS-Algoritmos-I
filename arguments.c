#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arguments.h"
#include "error.h"

status_t validate_args(char * argv[], size_t arg_amount)
{
	if (argv == NULL)
		return ERROR_NULL_POINTER;

	if( arg_amount != MAX_CMD_ARGS)
		return ERROR_PROG_INVOCATION;

	return OK;
}
