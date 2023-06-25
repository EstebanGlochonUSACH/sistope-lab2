#include <stdio.h>
#include <regex.h>
#include <string.h>
#include "fworker.h"

int main(int argc, char *argv[])
{
	char line_buffer[4096];
	regex_t re;
	static const char *pattern = "^(A|C|T)*G+T+C(A|C|G|T)*$";
	int match_status;

	if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
		fprintf(stderr, "Error: El patron regex no pudo ser compilado!\n");
		return 1;
	}

	while(fgets(line_buffer, sizeof(line_buffer), stdin) != 0){
		strtrim(line_buffer);
		if(strcmp(line_buffer, "FIN") == 0) break;
		match_status = regexec(&re, line_buffer, (size_t)0, NULL, 0);
		if (match_status == 0) {
			fprintf(stdout, "%s si\n", line_buffer);
		}
		else{
			fprintf(stdout, "%s no\n", line_buffer);
		}
	}

	regfree(&re);
	return 0;
}