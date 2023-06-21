#ifndef _H_BROKER_FUNCIONES
#define _H_BROKER_FUNCIONES

#include <stdbool.h>

// Entradas: Recibe los mismos parametros que "fprintf", junto con un "flag".
// Salidas: No retorna. Se espera que la funcion escriba en un archivo y opcionalmente
//          imprima texto en la terminal.
// Descripción: Recibe los mismos parametros que "fprintf" para poder escribir texto
//              en un archivo. El flag "flag_verbose" sirve ademas, para habilitar
//              la escritura de la misma informacion en el STDOUT del proceso. 
void dup_printf(bool flag_verbose, FILE *f, char const *fmt, ...);

#endif