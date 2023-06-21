#include <string.h>

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