#ifndef TDA_GPS__H
#define TDA_GPS__H

#include <time.h>

#include "types.h"

#define MAX_LENGTH 10

#define ID_MSG_POSITION 0
#define UTC_POSITION 1
#define LATITUDE_POSITION 2
#define NS_ORIENTATION_POSITION 3
#define LONGITUDE_POSITION 4
#define WE_ORIENTATION_POSITION 5
#define FIX_POSITION_POSITION 6
#define USED_SATELLITES_POSITION 7
#define HDOP_POSITION 8
#define SEA_LEVEL_POSITION 9
#define SEA_LEVEL_UNIT_POSITION 10
#define GEOID_SEPARATION_POSITION 11
#define GEOID_SEPARATION_UNIT_POSITION 12
#define AGE_DIFF_CORR_POSITION 14
#define DIFF_REFF_STATION_ID_POSITION 13

#define ID_WIDTH 6
#define DIFF_REFF_STATION_ID_WIDTH 4
#define CHECK_SUM_WIDTH 3

#define HOUR_POSITION 0
#define HOUR_WIDTH 2
#define MIN_POSITION 2
#define MIN_WIDTH 4
#define SEC_POSITION 4
#define SEC_WIDTH 6

#define DEGREES_POSITION 0

#define DEGREES_LATITUDE_WIDTH 2
#define MINUTES_LATITUDE_POSITION 2
#define MINUTES_LATITUDE_WIDTH 9

#define DEGREES_LONGITUDE_WIDTH 3
#define MINUTES_LONGITUDE_POSITION 3
#define MINUTES_LONGITUDE_WIDTH 10


#define SOUTH_INDICATOR 'S'
#define WEST_INDICATOR 'W'


typedef struct{
	double degrees;
	double minutes;
}coordinate_t;

typedef struct{
	char id_msg[ID_WIDTH];
	struct tm utc_time;
	coordinate_t latitude;
	char ns_orientation;
	coordinate_t longitude;
	char we_orientation;
	int fix_position;
	size_t used_satellites;
	float HDOP;
	double sea_level_height;
	char sea_level_height_unit;
	double geoid_separation;
	char geoid_separation_unit;
	struct tm age_diff_corr;
	size_t diff_reff_station_id;
	unsigned char check_sum;
	char eof;
}ADT_gps_coordinate_t;

typedef status_t (*destructor_gps_t)(ADT_gps_coordinate_t *coordinate);
typedef status_t (*printer_gps_t)(const ADT_gps_coordinate_t *coordinate, char delim, FILE *fo);
typedef bool_t (*comparator_gps_t)(ADT_gps_coordinate_t *coordinate_1, ADT_gps_coordinate_t *coordinate_2);

status_t load_gps_coordinate(ADT_gps_coordinate_t **coordinate, char ** data);
status_t load_coordinate_latitude(coordinate_t *orientation, char* data);
status_t load_coordinate_longitude(coordinate_t *orientation, char* data);
status_t load_diff_reff_position(size_t *coordinate, char* data);
status_t load_check_sum(unsigned char *coordinate, char* data);
status_t load_utc_time(struct tm *utc_time, char *data);
status_t load_age_diff_corr(struct tm *coordinate, char *data);
status_t ADT_gps_coordinate_delete(ADT_gps_coordinate_t *coordinate);
status_t ADT_gps_coordinate_export_as_csv(const ADT_gps_coordinate_t *coordinate, char delim, FILE *fo);
status_t ADT_gps_coordinate_export_as_kml(const ADT_gps_coordinate_t *coordinate, char delim, FILE *fo);                     
bool_t ADT_gps_comparator(ADT_gps_coordinate_t *coordinate_1, ADT_gps_coordinate_t *coordinate_2);                                                                                                                           



#endif
