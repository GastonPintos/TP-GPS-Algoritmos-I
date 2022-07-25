#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "types.h"

#define MAX_CMD_ARGS 6
#define CMD_ARG_PRINTING_FMT_POSITION 2
#define CMD_ARG_OUTPUT_FILE_POSITION 4
#define CMD_ARG_INPUT_FILE_POSITION 5
#define	PRINTING_FMT_CSV "csv"
#define PRINTING_FMT_KML "kml"


status_t validate_args(char * argv[], size_t arg_amount );

#endif
