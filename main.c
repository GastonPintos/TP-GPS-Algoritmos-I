#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"
#include "vector.h"
#include "gps.h"
#include "error.h"
#include "arguments.h"
#include "types.h"

int main(int argc, char* argv[])
{
	FILE *input_file, *output_file;
	status_t status;
	ADT_vector_t *vector;
	ADT_gps_coordinate_t *coordinate;
	char *created_string;
	bool_t eof;
	size_t amount_fields, num_linea; 
	char ** string_array;


	if((status=validate_args(argv,argc))!=OK)
	{
		print_error(status);
		return EXIT_FAILURE;
	}

	if((input_file=fopen(argv[CMD_ARG_INPUT_FILE_POSITION],"rt"))==NULL)
	{
		status=ERROR_CORRUPT_FILE;
		print_error(status);
		return EXIT_FAILURE;
	}

	if((output_file=fopen(argv[CMD_ARG_OUTPUT_FILE_POSITION],"wt"))==NULL)
	{
		fclose(input_file);
		status=ERROR_CORRUPT_FILE;
		print_error(status);
		return EXIT_FAILURE;
	}

	if((status=ADT_vector_new(&vector))!=OK)
	{
		ADT_vector_delete(&vector,ADT_gps_coordinate_delete);
		fclose(input_file);
		fclose(output_file);
		print_error(status);
		return EXIT_FAILURE;
	}

	num_linea=0;

	while((status=read_line(input_file, &created_string, &eof))==OK && eof!=TRUE)
	{
	
		if((is_valid_line(created_string))==TRUE)
		{
			if((status = split (created_string, INPUT_CSV_DELIMITER, &amount_fields , &string_array))!=OK)
			{
				ADT_vector_delete(&vector, ADT_gps_coordinate_delete);
				fclose(input_file);
				fclose(output_file);
				print_error(status);
				return EXIT_FAILURE;
			}
			
			if((status=load_gps_coordinate(&coordinate,string_array))!=OK)
			{
				ADT_gps_coordinate_delete(coordinate);
				ADT_vector_delete(&vector, ADT_gps_coordinate_delete);
				fclose(input_file);
				fclose(output_file);
				print_error(status);
				return EXIT_FAILURE;
			}
			
			if((status=ADT_vector_append(&vector,coordinate))!=OK)
			{
				ADT_vector_delete(&vector, ADT_gps_coordinate_delete);
				fclose(input_file);
				fclose(output_file);
				print_error(status);
				return EXIT_FAILURE;
			}			
		}
	}

	if((status = ADT_vector_sort( vector, ADT_gps_comparator))!=OK)
	{
		ADT_vector_delete(&vector, ADT_gps_coordinate_delete);
		fclose(input_file);
		fclose(output_file);
		print_error(status);
		return EXIT_FAILURE;
	}
	
	if(!strcmp(argv[CMD_ARG_PRINTING_FMT_POSITION],PRINTING_FMT_CSV))
	{
		if((status=export_data_as_csv(vector,output_file,OUTPUT_FILE_CSV_DELIMITER ))!=OK)
		{
			ADT_vector_delete(&vector, ADT_gps_coordinate_delete);
			fclose(input_file);
			fclose(output_file);
			print_error(status);
			return EXIT_FAILURE;
		}
	}

	if(!strcmp(argv[CMD_ARG_PRINTING_FMT_POSITION],PRINTING_FMT_KML))
	{
		if((status=export_data_as_kml(vector,output_file,OUTPUT_FILE_KML_DELIMITER ))!=OK)
		{
			
			ADT_vector_delete(&vector, ADT_gps_coordinate_delete);
			fclose(input_file);
			fclose(output_file);
			print_error(status);
			return EXIT_FAILURE;
		}
	}
	
	if((status=ADT_vector_delete(&vector, ADT_gps_coordinate_delete))!=OK)
	{
		fclose(input_file);
		fclose(output_file);
		print_error(status);
		return EXIT_FAILURE;
	}
	fclose(input_file);

	if(fclose(output_file)==EOF)
	{
		status=ERROR_CORRUPT_FILE;
		print_error(status);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
