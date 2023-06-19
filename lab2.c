#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
	params_t params;
	parse_params(&params, argc, argv);

	if(!params.has_file_in){
		fprintf(stderr, "Error: Se requiere el parametro 'i'\n");
		return 1;
	}

	if(!params.has_file_out){
		fprintf(stderr, "Error: Se requiere el parametro 'o'\n");
		return 1;
	}

	if(params.chunk_size == INT_MIN){
		fprintf(stderr, "Error: Se requiere el parametro 'c'\n");
		return 1;
	}

	if(params.chunk_size < 1){
		fprintf(stderr, "Error: El tama%co del chunk no puede ser menor a 1!\n", 241);
		return 1;
	}

	if(params.total_workers == INT_MIN){
		fprintf(stderr, "Error: Se requiere el parametro 'n'\n");
		return 1;
	}

	if(params.total_workers < 1){
		fprintf(stderr, "Error: El total de workers no puede ser menor a 1!\n");
		return 1;
	}

	if(!file_exists(params.file_in)){
		fprintf(stderr, "Error: El archivo de entrada no existe!\n");
		return 1;
	}

	pid_t pid = fork();
	if(pid < 0){
		fprintf(stderr, "Error: No se pudo realizar fork!\n");
		return 1;
	}

	if(pid == 0){
		// Fork: Broker
		char total_workers[10];
		sprintf(total_workers, "%d", params.total_workers);
		char chunk_size[10];
		sprintf(chunk_size, "%d", params.chunk_size);
		char flag_verbose[10];
		if(params.flag_verbose) strcpy(flag_verbose, "true");
		else strcpy(flag_verbose, "false");
		char *argv[] = {"./broker", params.file_in, params.file_out, flag_verbose, total_workers, chunk_size, NULL};
		execvp(argv[0], argv);
		fprintf(stderr, "Error: No se pudo realizar execvp!\n");
		return 1;
	}
	
	// Fork: Parent
	while(wait(NULL) > 0);

	return 0;
};