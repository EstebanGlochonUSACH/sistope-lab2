#ifndef _H_FUNCIONES
#define _H_FUNCIONES

#include <stdbool.h>

bool file_exists(char *filename);

typedef struct {
	char file_in[100];
	int has_file_in;
	char file_out[100];
	int has_file_out;
	int flag_verbose;
	int total_workers;
	int chunk_size;
} params_t;

void parse_params(params_t *params, int argc, char *argv[]);

#endif