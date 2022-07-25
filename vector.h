#ifndef ADT_VECTOR__H
#define ADT_VECTOR__H

#include "types.h"
#include "gps.h"

#define OUTPUT_FILE_KML_DELIMITER ','
#define OUTPUT_FILE_CSV_DELIMITER '|'
#define INIT_CHOP 80
#define FMT_KML_HEADER "<\?xml version=\"1.0\" encoding=\"UTF-8\"\?>\n<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n<Document>\n<name>Rutas</name>\n<description>Ejemplos de rutas</description>\n<Style id=\"yellowLineGreenPoly\">\n<LineStyle>\n<color>7f00ffff</color>\n<width>4</width>\n</LineStyle>\n<PolyStyle>\n<color>7f00ff00</color>\n</PolyStyle>\n</Style>\n<Placemark>\n<name>Relieve absoluto</name>\n<description>Pared verde transparente con contornos\namarillos</description>\n<styleUrl>#yellowLineGreenPoly</styleUrl>\n<LineString>\n<extrude>1</extrude>\n<tessellate>1</tessellate>\n<altitudeMode>absolute</altitudeMode>\n<coordinates>"

#define FMT_KML_FOOTER "</coordinates>\n</LineString>\n</Placemark>\n</Document>\n</kml>"

typedef struct
{
	void **array_elements;
	size_t size;
	size_t alloc_size;
	char *header;
	char *footer;

}ADT_vector_t;


status_t ADT_vector_new( ADT_vector_t **vector);
status_t ADT_vector_append(ADT_vector_t **vector, void *element);
status_t ADT_vector_delete(ADT_vector_t **vector, destructor_gps_t pf);
status_t ADT_vector_export(const ADT_vector_t *vector, FILE *fo, void *tool_box, printer_gps_t pf);
status_t ADT_vector_set_header(ADT_vector_t *vector, char* string);
status_t ADT_vector_set_footer(ADT_vector_t *vector, char* string);
status_t export_data_as_csv(ADT_vector_t *vector, FILE *output_file, void* tool_box);
status_t export_data_as_kml(ADT_vector_t *vector, FILE *output_file, void* tool_box);
status_t ADT_vector_sort(ADT_vector_t *vector, comparator_gps_t pf);


#endif
