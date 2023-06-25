#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

// Descripción: Estructura que contiene datos relevantes para trabajar con un "worker".
typedef struct {
	pid_t pid;
	int n_tasks;
	int n_results;
	int fd_b2w[2];
	int fd_w2b[2];
} worker_t;

// Descripción: Una función auxiliar que ayuda a liberar la memoria de un arreglo
//              de workers (worker_t).
// Entradas:    El arreglo de workers y el tamaño de este.
// Salidas:     No retorna.
void free_workers(worker_t **workers, size_t total){
	for(int i = 0; i < total; ++i) free(workers[i]);
	free(workers);
}

// Descripción: Recibe los mismos parametros que "fprintf" para poder escribir texto
//              en un archivo. El flag "flag_verbose" sirve ademas, para habilitar
//              la escritura de la misma informacion en el STDOUT del proceso. 
// Entradas:    Recibe los mismos parametros que "fprintf", junto con un "flag".
// Salidas:     No retorna. Se espera que la funcion escriba en un archivo y opcionalmente
//              imprima texto en la terminal.
void dup_printf(bool flag_verbose, FILE *f, char const *fmt, ...) { 
    va_list ap;
    if(flag_verbose){
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
    }
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
};

// Descripción: Comprueba si un string termina con otro string dado.
// Entradas:    El string a comprobar y el string que representa el "sufijo".
// Salidas:     Retorna verdadero o falso dependiendo del caso.
bool str_endswith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return false;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return false;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

// Descripción: Comprueba si un caracter dado es de tipo "espacio".
// Entradas:    Un character.
// Salidas:     Retorna verdadero o falso dependiendo del caso.
bool is_space(char c){
	return((c >= 0 && c <=32) || c == 127);
};

// Descripción: Remueve todos los carácteres "blancos" del inicio y final del string.
// Entradas:    Recibe "string" (arreglo de carácteres).
// Salidas:     Retorna el mismo puntero del arreglo de caracteres.
char *strtrim(char *s) {
	int start_index = 0;
	int end_index = strlen(s);
	char buffer[1000];
	// left trim
    while(is_space(s[start_index])) ++start_index;
	// right tirm
    while(is_space(s[end_index])) --end_index;
    s[end_index + 1] = '\0';

	// usar buffer para mover caracteres
	strcpy(buffer, &s[start_index]);
	strcpy(s, buffer);
    return s;
};