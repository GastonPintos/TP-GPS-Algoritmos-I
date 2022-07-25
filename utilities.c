#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"


status_t read_line(FILE * fi, char ** created_string, bool_t *eof)
{
	char c;
	size_t alloc_size, used_size;
	char * aux;

	if (created_string == NULL || fi == NULL)
		return ERROR_NULL_POINTER;

	if((*created_string=(char *)malloc(INIT_SIZE*sizeof(char)))== NULL)
		return ERROR_MEMORY;

	alloc_size = INIT_SIZE;
	used_size = 0;
	
	while((c = fgetc(fi)) != '\n' && c != EOF)
	{
		if(used_size == alloc_size-1)
		{
			if((aux=(char*)realloc(*created_string,alloc_size + INIT_SIZE)) == NULL)
			{
				free(*created_string);
				return ERROR_MEMORY;
			}
			*created_string = aux;
			alloc_size += INIT_SIZE; 
		}
		(*created_string)[used_size ++] = c;
	}
	
	*eof=(c==EOF)?TRUE:FALSE;

	(*created_string)[used_size]='\0';

	return OK;	
}

bool_t is_valid_line(char *string)
{
	if(!(strncmp(string,SELECTED_ID,ID_LENGHT)))
	{
		if(strstr(string,EMPTY_CSV_FILEDS_LINE)==NULL){
			if(check_sum(string)==TRUE)
			{
				return TRUE;
			}
		}
	}
	else 
		return FALSE;
}

bool_t check_sum(char * string)
{
	unsigned char sum;
	unsigned char check_sum;
	size_t position, next, i;
	char aux[CHECK_SUM_WIDTH];
	char *temp;

	for(position=1 , next=position+1, sum=string[position]; next<strlen(string)-4 ; next++){
		
		sum=string[next]^sum;
	}

	for(position=strlen(string)-3, i=0; position < strlen(string) && i<CHECK_SUM_WIDTH; position++, i++)
	{
		aux[i]=string[position];	
	}
	aux[CHECK_SUM_WIDTH]='\0';

	check_sum=strtoul(aux,&temp,16);

	return (check_sum==sum)?TRUE:FALSE;
}

status_t split (const char * s, char del, size_t * amount_fields , char *** string_array)
{
	char *str, *q, *p;
	char delims[2];
	size_t i;

	if ( s == NULL || amount_fields == NULL || string_array == NULL)
		return ERROR_NULL_POINTER;
	
	delims[0] = del;

	delims[1] = '\0';

	if(strdupl (s,&str) != OK )
	{
		*amount_fields = 0;
		return ERROR_MEMORY;
	}

	for(i = 0, *amount_fields = 0; str[i]; i++)
	{
		if(str[i] == del)
			(*amount_fields)++; 
	
	}
	(*amount_fields)++;

	if((* string_array = (char **)malloc((*amount_fields) * sizeof(char *))) == NULL)
	{
		free(str);
		*amount_fields=0;
		return ERROR_MEMORY;
	}

	for( i=0, q=str; (p = strtok(q, delims))!= NULL; q=NULL, i++)
	{
		if(strdupl(p, &(*string_array)[i]) != OK)
		{
			free(str);
			destroy_strings(string_array, amount_fields);
			*amount_fields=0;
			return ERROR_MEMORY;
		}
	}
	free(str);

	return OK;
}

status_t strdupl(const char *s, char **t)
{
	size_t i;

	if( s == NULL || t == NULL)
		return ERROR_NULL_POINTER;

	if((*t =(char *)malloc((strlen(s)+sizeof(char))*sizeof(char))) == NULL)
		return ERROR_MEMORY;

	for( i=0; ((*t)[i] = s[i]) ; i++);

	return OK;
}

status_t destroy_strings(char *** string_array, size_t *l)
{
	size_t i;

	if(string_array == NULL)
		return ERROR_NULL_POINTER;

	for(i=0; i < *l; i++)
	{
		free(*string_array[i]);
		(*string_array)[i]=NULL;
	}
	
	free(*string_array);
	
	*string_array = NULL;
	
	*l=0;
	
	return OK;
}

status_t swap(ADT_gps_coordinate_t *data_1, ADT_gps_coordinate_t *data_2)
{
	ADT_gps_coordinate_t aux;
	
	printf("Entro en swap\n");

	if(data_1==NULL || data_2==NULL)
		return ERROR_NULL_POINTER;

	aux = *data_1;
	*data_1 = *data_2;
	*data_2 = aux;
	
	return OK;
}
