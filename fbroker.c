#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

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

int is_space(char c){
	return((c >= 0 && c <=32) || c == 127);
};

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