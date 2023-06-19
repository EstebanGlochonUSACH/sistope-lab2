#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <limits.h>

bool file_exists(char *filename){
	struct stat buffer;   
	return(stat(filename, &buffer) == 0);
}

struct _params {
	char file_in[100];
	int has_file_in;
	char file_out[100];
	int has_file_out;
	int flag_verbose;
	int total_workers;
	int chunk_size;
};

void parse_params(struct _params *params, int argc, char *argv[])
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
