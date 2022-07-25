#ifndef TYPES__H
#define TYPES__H

typedef enum
{
	ERROR_NULL_POINTER,
	ERROR_MEMORY,
	ERROR_PROG_INVOCATION,
	ERROR_CORRUPT_FILE,
	ERROR_WRITING_FILE,
	ERROR_INVALID_DATA,
	OK
}status_t;

typedef enum{
	FALSE,
	TRUE
}bool_t;

#endif


