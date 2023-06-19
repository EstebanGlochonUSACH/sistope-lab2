#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
    params_t params;
    FILE *fp_input, *fp_output;
	regex_t re;
    static const char *pattern = "^(A|C|T)*G+T+C(A|C|G|T)*$";
    int match_status;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int counter_match = 0, counter_no_match = 0, counter_total = 0;

    parse_params(&params, argc, argv);

    if(!params.has_file_in){
        fprintf(stderr, "Error: Se requiere el parametro 'i'\n");
        return 1;
    }

    if(!params.has_file_out){
        fprintf(stderr, "Error: Se requiere el parametro 'o'\n");
        return 1;
    }

    if(params.chunk_size < 1){
        fprintf(stderr, "Error: El tama%co del chunk no puede ser menor a 1\n", 241);
        return 1;
    }

    if(params.chunk_size == UNDEFINED_SIZE){
        fprintf(stderr, "Error: Se requiere el parametro 'c'\n");
        return 1;
    }

    if(params.total_workers == UNDEFINED_SIZE){
        fprintf(stderr, "Error: Se requiere el parametro 'n'\n");
        return 1;
    }

    if(params.chunk_size < 1){
        fprintf(stderr, "Error: El tama%co del chunk no puede ser menor a 1\n", 241);
        return 1;
    }

    if(params.total_workers < 1){
        fprintf(stderr, "Error: El total de workers no puede ser menor a 1\n", 241);
        return 1;
    }

	if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
        fprintf(stderr, "Error: El patron regex no pudo ser compilado!\n");
		return 1;
	}

    if((fp_input = fopen(params.file_in, "r")) == NULL){
        fprintf(stderr, "Error: No se pudo acceder al archivo de entrada!\n");
        return 1;
    }

    if((fp_output = fopen(params.file_out, "w")) == NULL){
        fprintf(stderr, "Error: No se pudo acceder al archivo de salida!\n");
        fclose(fp_input);
        return 1;
    }

    while ((read = getline(&line, &len, fp_input)) != -1) {
        strtrim(line);
	    match_status = regexec(&re, line, (size_t)0, NULL, 0);
        dup_printf(params.flag_verbose, fp_output, "%s", line);
        if (match_status == 0) {
            counter_match += 1;
            dup_printf(params.flag_verbose, fp_output, " si\n");
        }
        else{
            counter_no_match += 1;
            dup_printf(params.flag_verbose, fp_output, " no\n");
        }
        counter_total += 1;
    }

    dup_printf(params.flag_verbose, fp_output, "\n");
    dup_printf(params.flag_verbose, fp_output, "Total de expresiones que Si son regulares:%d\n", counter_match);
    dup_printf(params.flag_verbose, fp_output, "Total de expresiones que No son regulares:%d\n", counter_no_match);
    dup_printf(params.flag_verbose, fp_output, "Total de lineas leídas:%d\n", counter_total);

	regfree(&re);
    fclose(fp_input);
    fclose(fp_output);
    return 0;
};