#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <limits.h>

// Entradas:    Recibe la ruta del archivo.
// Salidas:     Retorna verdadero o falso dependiendo de si el archivo existe.
// Descripción: Comprueba si un archivo existe.
bool file_exists(char *filename){
	struct stat buffer;   
	return(stat(filename, &buffer) == 0);
}

// Descripción: Estructura que contiene los parameros del programa.
typedef struct {
	char file_in[100];
	int has_file_in;
	char file_out[100];
	int has_file_out;
	int flag_verbose;
	int total_workers;
	int chunk_size;
} params_t;

// Entradas:    Recibe una estructura donde guardar los paramatros de entrada junto
//              con los mismos parameros que recibe la funcion main.
// Salidas:     No retorna. Guarda información en la estructura "params".
// Descripción: Procesa los parameros que recibe el main, en forma de valores string
//              o flags booleanos para guardarlos en una estructura especial que va
//              a contener toda esa información.
void parse_params(params_t *params, int argc, char *argv[])
{
	int option;
	char tmp[48];
	params->flag_verbose = 0;
	params->has_file_in = 0;
	params->has_file_out = 0;
	params->chunk_size = INT_MIN;
	params->total_workers = INT_MIN;
	while((option = getopt(argc, argv, "i:o:n:c:b")) != -1){
		switch(option) { 
			case 'i':
				strcpy(params->file_in, optarg);
				params->has_file_in = 1;
				break;
			case 'o':
				strcpy(params->file_out, optarg);
				params->has_file_out = 1;
				break;
			case 'b':
				params->flag_verbose = 1;
				break;
			case 'n':
				strcpy(tmp, optarg);
				params->total_workers = atoi(tmp);
				break;
			case 'c':
				strcpy(tmp, optarg);
				params->chunk_size = atoi(tmp);
				break;
		}
	}
};
