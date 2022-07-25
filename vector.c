#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "utilities.h"

status_t ADT_vector_new( ADT_vector_t **vector)
{
	if(vector==NULL)
		return ERROR_NULL_POINTER;

	if((*vector=(ADT_vector_t*)malloc(sizeof(ADT_vector_t)))==NULL)
		return ERROR_MEMORY;

	if(((*vector)->array_elements=(void**)malloc(INIT_CHOP*sizeof(void*)))==NULL){
		free(*vector);
		vector=NULL;
		return ERROR_MEMORY;
	}

	(*vector)->size=0;

	(*vector)->alloc_size=INIT_CHOP;

	(*vector)->header=NULL;
	(*vector)->footer=NULL;

	return OK;
}

status_t ADT_vector_append(ADT_vector_t **vector, void *element)
{
	void **aux;

	if(vector==NULL||element==NULL)
		return ERROR_NULL_POINTER;

	if(	(*vector)->size < (*vector)->alloc_size)
	{
		(*vector)->array_elements[(*vector)->size++] = element;
		return OK;
	}

	if((aux=(void**)realloc((*vector)->array_elements, (*vector)->alloc_size+INIT_CHOP*sizeof(void*)))==NULL)
		return ERROR_MEMORY;

	(*vector)->alloc_size+=INIT_CHOP;

	(*vector)->array_elements=aux;

	(*vector)->array_elements[(*vector)->size++] = element;

	return OK;
}

status_t ADT_vector_delete(ADT_vector_t **vector, destructor_gps_t pf)
{
	status_t state;
	size_t i;

	if(vector==NULL || pf ==NULL)
		return ERROR_NULL_POINTER;

	for(i=0; i< ((*vector)->size) ; i++)
	{
		if((state= pf((*vector)->array_elements[i]))!=OK)
			return state;
		(*vector)->array_elements[i]=NULL;
	}
	free((*vector)->array_elements);


	return OK;
}

status_t ADT_vector_export(const ADT_vector_t *vector, FILE *fo, void *tool_box, printer_gps_t pf)
{
	size_t i;
	status_t state;

	if( vector==NULL || fo==NULL )
		return ERROR_NULL_POINTER;

	if((vector->header)!=NULL)
		fprintf(fo, "%s\n", vector->header);

	for(i=0; i < vector->size ; i++){
		if((state=pf(vector->array_elements[i], tool_box, fo))!=OK)
			return state;
		fprintf(fo, "\n");
	
	}

	if((vector->footer)!=NULL)
		fprintf(fo, "%s\n", vector->footer);

	return OK;
}

status_t ADT_vector_set_header(ADT_vector_t *vector, char* string)
{
	if( vector==NULL)
		return ERROR_NULL_POINTER;

	if(string!=NULL)
	{
		if((vector->header=(char*)malloc((strlen(string)+2)*sizeof(char)))==NULL)
			return ERROR_MEMORY;
	
		vector->header=string;
	}
	
	return OK;
}

status_t ADT_vector_set_footer(ADT_vector_t *vector, char* string)
{
	if( vector==NULL)
		return ERROR_NULL_POINTER;

	if(string!=NULL)
	{
		if((vector->footer=(char*)malloc((strlen(string)+2)*sizeof(char)))==NULL)
			return ERROR_MEMORY;
	
		vector->footer=string;
	}
	
	return OK;
}

status_t export_data_as_csv(ADT_vector_t *vector, FILE *output_file, void* tool_box)
{
	status_t status;

	if(vector==NULL||output_file==NULL||tool_box==NULL)
		return ERROR_NULL_POINTER;

	if((status=ADT_vector_set_footer(vector, NULL))!=OK)
		return status;

	if((status=ADT_vector_set_header(vector, NULL))!=OK)
		return status;

	if((status=ADT_vector_export(vector, output_file, tool_box,ADT_gps_coordinate_export_as_csv))!=OK)
		return status;


	return OK;
}

status_t export_data_as_kml(ADT_vector_t *vector, FILE *output_file, void* tool_box)
{
	status_t status;

	if(vector==NULL||output_file==NULL||tool_box==NULL)
		return ERROR_NULL_POINTER;

	if((status=ADT_vector_set_footer(vector, FMT_KML_FOOTER))!=OK)
		return status;

	if((status=ADT_vector_set_header(vector, FMT_KML_HEADER))!=OK)
		return status;

	if((status=ADT_vector_export(vector, output_file, tool_box,ADT_gps_coordinate_export_as_kml))!=OK)
		return status;

	return OK;
}

status_t ADT_vector_sort(ADT_vector_t *vector, comparator_gps_t pf)
{
	size_t i,j,swaps;
	status_t status;

	printf("Entro en sort\n");

	if (vector == NULL)
		return ERROR_NULL_POINTER;

	for( i=0 ; i < (vector->size) -1 ; i++)
	{
		printf("Entro en primer for %lu \n", i);

		swaps=0;

		for( j=0 ; j < ((vector->size) -1 - i); j++)
		{

			printf("Entro al segundo for %lu \n",j);

			if((pf(vector->array_elements[j],vector->array_elements[j+1]))==TRUE)
			{

				printf("Entro en comparator true\n");

				if((status = swap((vector->array_elements[j]),(vector->array_elements[j+1])))!=OK)
					return status;

				swaps++;
			}
			
		}
		if(swaps==0) break;
	}
	return OK;
}


