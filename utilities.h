#ifndef UTILITIES__H
#define UTILITIES__H

#include "gps.h"
#include "types.h"

#define INIT_SIZE 10
#define GROWTH_FACTOR 5
#define ID_LENGHT 6
#define SELECTED_ID "$GPGGA"
#define MASK_CHECKSUM 0x7F
#define CHECK_SUM_WIDTH 3
#define INPUT_CSV_DELIMITER ','
#define EMPTY_CSV_FILEDS_LINE ",,,,,"

status_t split (const char * s, char del, size_t * amount_fields , char *** string_array);
status_t strdupl(const char *s, char **t);
status_t read_line(FILE * fi, char ** created_string, bool_t *eof);
status_t destroy_strings(char *** string_array, size_t *l);
bool_t check_sum(char * string);
bool_t is_valid_line(char *string);
status_t swap(ADT_gps_coordinate_t *data_1, ADT_gps_coordinate_t *data_2);

#endif
