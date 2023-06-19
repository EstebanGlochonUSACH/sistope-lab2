#ifndef _H_FUNCIONES
#define _H_FUNCIONES

#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

// Entradas: recibe un script con la ruta al archivo.
// Salidas: Retorna "true" o "false" dependiendo de si el archivo existe.
// Descripción: Comprueba si un archivo existe.
bool file_exists(char *filename);

// Descripción: Estructura que contiene los parameros del programa.
struct _params {
	char file_in[100];
	int has_file_in;
	char file_out[100];
	int has_file_out;
	int flag_verbose;
	int total_workers;
	int chunk_size;
};
typedef struct _params params_t;

// Entradas: Recibe una estructura donde guardar los paramatros de entrada junto
//           con los mismos parameros que recibe la funcion main.
// Salidas: No retorna. Guarda información en la estructura "params".
// Descripción: Procesa los parameros que recibe el main, en forma de valores string
//              o flags booleanos para guardarlos en una estructura especial que va
//              a contener toda esa información.
void parse_params(params_t *params, int argc, char *argv[]);

#endif