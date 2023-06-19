#ifndef _H_FUNCIONES
#define _H_FUNCIONES

#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

// Descripción: Estructura que contiene los parameros del programa.
struct _params {
	char file_in[100];
	int has_file_in;
	char file_out[100];
	int has_file_out;
	int flag_verbose;
};
typedef struct _params params_t;

// Entradas: Recibe una estructura donde guardar los paramatros de entrada junto
//           con los mismos parameros que recibe la funcion main.
// Salidas: No retorna. Guarda información en la estructura "params".
// Descripción: Procesa los parameros que recibe el main, en forma de valores string
//              o flags booleanos para guardarlos en una estructura especial que va
//              a contener toda esa información.
void parse_params(params_t *params, int argc, char *argv[]);

// Entradas: Recibe los mismos parametros que "fprintf", junto con un "flag".
// Salidas: No retorna. Se espera que la funcion escriba en un archivo y opcionalmente
//          imprima texto en la terminal.
// Descripción: Recibe los mismos parametros que "fprintf" para poder escribir texto
//              en un archivo. El flag "flag_verbose" sirve ademas, para habilitar
//              la escritura de la misma informacion en el STDOUT del proceso. 
void dup_printf(int flag_verbose, FILE *f, char const *fmt, ...);

// Entradas: Recibe "string" (arreglo de carácteres).
// Salidas: Retorna el mismo puntero del arreglo de caracteres.
// Descripción: Remueve todos los carácteres "blancos" del inicio y final del string.
char *strtrim(char *s);

#endif