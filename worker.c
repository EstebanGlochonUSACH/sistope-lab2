#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <regex.h>
#include <string.h>
#include "fworker.h"

int main(int argc, char *argv[])
{
	bool flag_loop = true;
	char line_buffer[4096];
	// FILE* pipe_fp = fdopen(stdin, "r");
	regex_t re;
	static const char *pattern = "^(A|C|T)*G+T+C(A|C|G|T)*$";
	int match_status;

	if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
		fprintf(stderr, "Error: El patron regex no pudo ser compilado!\n");
		return 1;
	}

	while(flag_loop){
		while(fgets(line_buffer, sizeof(line_buffer), stdin) != 0){
			strtrim(line_buffer);
			if(strcmp(line_buffer, "FIN")){
				flag_loop = false;
				break;
			}
			match_status = regexec(&re, line_buffer, (size_t)0, NULL, 0);
			if (match_status == 0) {
				printf("%s si\n", line_buffer);
			}
			else{
				printf("%s no\n", line_buffer);
			}
		}
		sleep(1);
	}

	regfree(&re);

	return 0;
}