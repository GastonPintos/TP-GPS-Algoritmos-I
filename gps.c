#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "gps.h"

status_t load_gps_coordinate(ADT_gps_coordinate_t **coordinate, char ** data)
{
	status_t status;
	char* temp;
	
	/*cargo la estructura*/
	if((*coordinate=(ADT_gps_coordinate_t*)malloc(sizeof(ADT_gps_coordinate_t)))==NULL)
		return EXIT_FAILURE;

	/*id_msg*/
	strcpy((*coordinate)->id_msg,data[ID_MSG_POSITION]);

	/*utc_time*/
	if((status=load_utc_time(&((*coordinate)->utc_time), data[UTC_POSITION]))!=OK)
	{
		return status;
	}

	/*latitude*/
	if((status=load_coordinate_latitude(&((*coordinate)->latitude),data[LATITUDE_POSITION]))!=OK)
	{
		return status;
	}

	/*ns_orientation*/
	(*coordinate)->ns_orientation=data[NS_ORIENTATION_POSITION][0];

	/*longitude*/
	if((status=load_coordinate_longitude(&((*coordinate)->longitude),data[LONGITUDE_POSITION]))!=OK)
	{
		return status;
	}

	/*ws_orientation*/
	(*coordinate)->we_orientation=data[WE_ORIENTATION_POSITION][0];

	/*fix_position*/
	(*coordinate)->fix_position=strtod(data[FIX_POSITION_POSITION], &temp);
	if(*temp)
	{
		return ERROR_INVALID_DATA;
	}

	/*used_satellites*/
	(*coordinate)->used_satellites=strtoul(data[USED_SATELLITES_POSITION],&temp,10);
	if(*temp)
	{
		return ERROR_INVALID_DATA;
	}

	/* HDOP */
	(*coordinate)->HDOP=strtod(data[HDOP_POSITION],&temp);
	if(*temp)
	{
		return ERROR_INVALID_DATA;
	}

	/*sea_level_height*/
	(*coordinate)->sea_level_height = strtod(data[SEA_LEVEL_POSITION], &temp);
	if(*temp)
	{
		return ERROR_INVALID_DATA;
	}

	/*sea_level_height_unit*/
	(*coordinate)->sea_level_height_unit = data[SEA_LEVEL_UNIT_POSITION][0];

	/*geoid_separation*/
	(*coordinate)->geoid_separation=strtod(data[GEOID_SEPARATION_POSITION], &temp);
	if(*temp)
	{
		return ERROR_INVALID_DATA;
	}

	/*age_diff_corr*/
	if((status=load_age_diff_corr(&((*coordinate)->age_diff_corr),data[AGE_DIFF_CORR_POSITION]))!=OK)
	{
		return status;
	}

	/*geoid_separation_unit*/
	(*coordinate)->geoid_separation_unit=data[GEOID_SEPARATION_UNIT_POSITION][0];
	
	/*diff_reff_position*/
	if((status=load_diff_reff_position(&((*coordinate)->diff_reff_station_id),data[DIFF_REFF_STATION_ID_POSITION])))
	{
		return status;
	}

	/*check_sum*/
	if((status=load_check_sum(&((*coordinate)->check_sum),data[DIFF_REFF_STATION_ID_POSITION])))
	{
		return status;
	}
	return OK;
}

status_t load_coordinate_latitude(coordinate_t *orientation, char* data)
{
	size_t i, position;
	char *temp, string[MAX_LENGTH];

	if(orientation==NULL||data==NULL)
		return ERROR_NULL_POINTER;

	/*latitude*/
	for(i=0, position=DEGREES_POSITION; i<DEGREES_LATITUDE_WIDTH; i++, position++)
		string[i]=data[i];

	string[DEGREES_LATITUDE_WIDTH]='\0';

	orientation->degrees = strtod(string,&temp);;
	
	if(*temp)
		return ERROR_INVALID_DATA;

	/*Minutes*/
	for(i=0, position=MINUTES_LATITUDE_POSITION; i<MINUTES_LATITUDE_WIDTH; i++, position++)
		string[i]=data[position];

	string[MINUTES_LATITUDE_WIDTH]='\0';

	orientation->minutes=strtod(string,&temp);

	if(*temp)
		return ERROR_INVALID_DATA;

	return OK;
}

status_t load_coordinate_longitude(coordinate_t *orientation, char* data)
{
	size_t i, position;
	char *temp, string[MAX_LENGTH];

	if(orientation==NULL||data==NULL)
		return ERROR_NULL_POINTER;

	/*longitude*/
	for(i=0, position=DEGREES_POSITION; i<DEGREES_LONGITUDE_WIDTH; i++, position++)
		string[i]=data[i];

	string[DEGREES_LONGITUDE_WIDTH]='\0';

	orientation->degrees = strtod(string,&temp);;
	
	if(*temp)
		return ERROR_INVALID_DATA;

	/*Minutes*/
	for(i=0, position=MINUTES_LONGITUDE_POSITION; i<MINUTES_LONGITUDE_WIDTH; i++, position++)
		string[i]=data[position];

	string[MINUTES_LONGITUDE_WIDTH]='\0';

	orientation->minutes=strtod(string,&temp);

	if(*temp)
		return ERROR_INVALID_DATA;

	return OK;
}

status_t load_diff_reff_position(size_t *coordinate, char *data)
{
	size_t i;
	char string[MAX_LENGTH];
	char *temp;

	for(i=0; data[i] != '*'; i++)
	{
		string[i] = data[i];
	}
	string[i]='\0';

	*coordinate=strtoul(string,&temp,10);

	if(*temp)
		return ERROR_INVALID_DATA;

	return OK;
}

status_t load_check_sum(unsigned char *coordinate, char *data)
{
	size_t position, i;
	char string[MAX_LENGTH];
	char *temp;

	for(position=strlen(data)-3, i=0; position < strlen(data) && i<CHECK_SUM_WIDTH; position++, i++)
	{
		string[i] = data[position];
	}
	string[CHECK_SUM_WIDTH]='\0';

	*coordinate=strtoul(string,&temp,10);

	if(*temp)
		return ERROR_INVALID_DATA;

	return OK;
}

status_t load_utc_time(struct tm *utc_time, char *data)
{
	size_t i, position;
	char string[MAX_LENGTH];
	char *temp;

	for(i=0, position=HOUR_POSITION; position<HOUR_WIDTH; i++, position++)
		string[i]=data[position];
	string[i]='\0';

	utc_time->tm_hour = strtoul(string, &temp, 10);
	if(*temp)
		return ERROR_INVALID_DATA;


	for(i=0, position = MIN_POSITION; position < MIN_WIDTH; i++, position++)
	{
		string[i]=data[position];
	}
	string[i]='\0';

	utc_time->tm_min = strtoul(string, &temp, 10);
	if(*temp)
		return ERROR_INVALID_DATA;


	for(i=0, position=SEC_POSITION; position < SEC_WIDTH; i++, position++)
		string[i]=data[position];
	string[i]='\0';

	utc_time->tm_sec = strtoul(string, &temp, 10);
	if(*temp)
		return ERROR_INVALID_DATA;

	return OK;
}

status_t load_age_diff_corr(struct tm *coordinate, char *data)
{
	char string[1];
	char *temp;

	if(coordinate==NULL)
		return ERROR_NULL_POINTER;

	if(data==NULL)
	{
		string[0]='\0';
		coordinate->tm_sec =strtoul(string,&temp,10);
		if(*temp)
			return ERROR_INVALID_DATA;
	}

	return OK;
}

status_t ADT_gps_coordinate_delete(ADT_gps_coordinate_t *coordinate)
{
	if(coordinate == NULL)
		return ERROR_NULL_POINTER;
	
	free(coordinate);
	coordinate = NULL;
	return OK;
}

status_t ADT_gps_coordinate_export_as_csv(const ADT_gps_coordinate_t *coordinate, char delim, FILE *fo)
{
	time_t aux;
	struct tm* filled_time; 

	if(coordinate == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	/*Manejo de la fecha*/
	time(&aux);
	filled_time = localtime(&aux); 	

	/*Impresion de datos*/	
	fprintf(fo,"%i " ,1900+filled_time->tm_year);
	
	fprintf(fo,"%i  ", filled_time->tm_mon);

	fprintf(fo, "%i ", filled_time->tm_mday);

	fprintf(fo, "%i ", coordinate->utc_time.tm_hour);

	fprintf(fo, "%i ", coordinate->utc_time.tm_min);

	fprintf(fo, "%i ", coordinate->utc_time.tm_sec);

	fprintf(fo, "%c", delim);

	fprintf(fo, "%f %f ", coordinate->latitude.degrees, coordinate->latitude.minutes);

	fprintf(fo, "%c", delim);

	fprintf(fo, "%f %f ", coordinate->longitude.degrees, coordinate->longitude.minutes);

	fprintf(fo, "%c", delim);

	fprintf(fo, "%f ", coordinate->sea_level_height);

	return OK;
}

status_t ADT_gps_coordinate_export_as_kml(const ADT_gps_coordinate_t *coordinate, char delim, FILE *fo)
{
	double decimal_coordinate;

	if(coordinate == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	decimal_coordinate = coordinate->longitude.degrees + ((coordinate->longitude.minutes)/60);

	if(coordinate->ns_orientation == SOUTH_INDICATOR)
		decimal_coordinate=-decimal_coordinate;

	fprintf(fo, "%.11f", decimal_coordinate);

	fprintf(fo, "%c", delim);


	decimal_coordinate=coordinate->latitude.degrees + (coordinate->latitude.minutes)/60;

	if(coordinate->we_orientation == WEST_INDICATOR)
		decimal_coordinate=-decimal_coordinate;

	fprintf(fo, "%.11f", decimal_coordinate);

	fprintf(fo, "%c", delim);

	fprintf(fo, "%.11f", coordinate->sea_level_height);

	return OK;
}

bool_t ADT_gps_comparator(ADT_gps_coordinate_t *coordinate_1, ADT_gps_coordinate_t  *coordinate_2)
{
	int ret1, ret2;
	double dif_time;

	printf("Entro en comparator\n");


	ADT_gps_coordinate_export_as_csv(coordinate_1, ',', stdout);
	printf("\n");
	ADT_gps_coordinate_export_as_csv(coordinate_2, ',', stdout);

	ret1 = mktime(&(coordinate_1 ->utc_time));
	ret2 = mktime(&(coordinate_2 ->utc_time));

	if(ret1 == (-1) || ret2 == (-1))
	{
		printf("ret1 %i ret 2%i\n",ret1,ret2 );
		return FALSE;
	}

	dif_time = difftime(ret1,ret2);

	printf("dif_time %d\n",dif_time );

	if(dif_time == 0 || dif_time < 0)
		return FALSE;
	else
		return TRUE;
}