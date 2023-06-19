#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include "fbroker.h"

typedef struct {
	pid_t pid;
	int n_tasks;
	int n_results;
	int fd_b2w[2];
	int fd_w2b[2];
} worker_t;

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

int main(int argc, char *argv[])
{
	if(argc != 5){
		fprintf(stderr, "Error: Parámetros incorrectos en broker!\n");
		return 1;
	}

	FILE *fp_input, *fp_output;
	regex_t re;
	static const char *pattern = "^(A|C|T)*G+T+C(A|C|G|T)*$";
	size_t total_workers = 0, chunk_size = 0;
	pid_t fork_pid;
	bool flag_verbose = false;
	worker_t *children;
	worker_t tmp_worker;
	int i;

	if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0) {
		fprintf(stderr, "Error: El patron regex no pudo ser compilado!\n");
		return 1;
	}
	
	if((fp_input = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "Error: No se pudo acceder al archivo de entrada!\n");
		return 1;
	}

	if((fp_output = fopen(argv[2], "w")) == NULL){
		fprintf(stderr, "Error: No se pudo acceder al archivo de salida!\n");
		fclose(fp_input);
		return 1;
	}

	if(strcmp(argv[3], "true") == 0) flag_verbose = true;

	total_workers = atoi(argv[4]);
	chunk_size = atoi(argv[5]);
	children = (worker_t*)malloc(sizeof(worker_t) * total_workers);

	for(i = 0; i < total_workers; ++i){
		tmp_worker = children[i];
		tmp_worker.n_tasks = 0;
		if(pipe(tmp_worker.fd_b2w) == -1){
			fprintf(stderr, "Error: No se pudo crear el pipe en el borker!\n");
			regfree(&re);
			fclose(fp_input);
			fclose(fp_output);
			free(children);
			return 1;
		}
		if(pipe(tmp_worker.fd_w2b) == -1){
			fprintf(stderr, "Error: No se pudo crear el pipe en el borker!\n");
			regfree(&re);
			fclose(fp_input);
			fclose(fp_output);
			free(children);
			return 1;
		}
		fork_pid = fork();
		if(fork_pid == 0){
			// Fork: Worker
            close(STDIN_FILENO);
            dup(tmp_worker.fd_b2w[0]);
            close(tmp_worker.fd_b2w[1]);
            close(tmp_worker.fd_b2w[0]);

            close(STDOUT_FILENO);
            dup(tmp_worker.fd_w2b[1]);
            close(tmp_worker.fd_w2b[0]);
            close(tmp_worker.fd_w2b[1]);

			char *argv[] = {"./worker", NULL};
			execvp(argv[0], argv);
			fprintf(stderr, "Error: No se pudo realizar execvp en broker!\n");
			return 1;
		}
		else{
			// Fork: Borker
			tmp_worker.pid = fork_pid;
            close(tmp_worker.fd_w2b[1]);
            close(tmp_worker.fd_b2w[0]);
		}
	}

	// Read lines from input file
	char line_buffer[4096];
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int counter_match = 0, counter_no_match = 0, counter_total = 0;
	int current_worker = 0;
	int chunk_counter = 0;

	while ((read = getline(&line, &len, fp_input)) != -1) {
		counter_total += 1;

		tmp_worker = children[current_worker];
		if(!str_endswith(line, "\n")){
			strcpy(line_buffer, line);
			strcat(line_buffer, "\n");
			write(tmp_worker.fd_b2w[1], line_buffer, len+1);
		}
		else{
			write(tmp_worker.fd_b2w[1], line, len);
		}
		tmp_worker.n_tasks += 1;

		chunk_counter += 1;
		if(chunk_counter == chunk_size){
			current_worker = (current_worker + 1) % total_workers;
			chunk_counter = chunk_counter % chunk_size;
		}

		// match_status = regexec(&re, line, (size_t)0, NULL, 0);
		// dup_printf(flag_verbose, fp_output, "%s", line);
		// if (match_status == 0) {
		// 	counter_match += 1;
		// 	dup_printf(flag_verbose, fp_output, " si\n");
		// }
		// else{
		// 	counter_no_match += 1;
		// 	dup_printf(flag_verbose, fp_output, " no\n");
		// }
	}

	// Send "FIN" to workers
	strcpy(line_buffer, "FIN\n");
	for(i = 0; i < total_workers; ++i){
		write(children[i].fd_b2w[1], line_buffer, 10);
	}

	// Read Results from workers
	int n_results;
	int counter_total2 = 0;
	FILE* pipe_fp;
	for(i = 0; i < total_workers; ++i){
		tmp_worker = children[i];
		n_results = 0;
		pipe_fp = fdopen(tmp_worker.fd_w2b[0], "r");
		while(fgets(line_buffer, sizeof(line_buffer), pipe_fp) != 0){
			dup_printf(flag_verbose, fp_output, line_buffer);
			n_results += 1;
			if(str_endswith(line_buffer, " si\n")) counter_match += 1;
			else if(str_endswith(line_buffer, " no\n")) counter_no_match += 1;
		}
		fclose(pipe_fp);
		tmp_worker.n_results = n_results;
		counter_total2 += n_results;
	}

	// Wait children to exit
	for(i = 0; i < total_workers; ++i) wait(NULL);

	dup_printf(flag_verbose, fp_output, "\n");
	dup_printf(flag_verbose, fp_output, "Total de expresiones que Si son regulares:%d\n", counter_match);
	dup_printf(flag_verbose, fp_output, "Total de expresiones que No son regulares:%d\n", counter_no_match);
	dup_printf(flag_verbose, fp_output, "Total de lineas leídas:%d\n", counter_total);
	dup_printf(flag_verbose, fp_output, "Total de lineas procesadas:%d\n", counter_total2);

	sprintf(line_buffer, "%ld", total_workers);
	int zeropad = strlen(line_buffer);
	if(zeropad < 2) zeropad = 2;
	for(i = 0; i < total_workers; ++i){
		tmp_worker = children[i];
		dup_printf(flag_verbose, fp_output,
			"[Worker #%0*d, PID=%ld] Total de expresiones leídas:%d\n",
			zeropad, i+1, (long)tmp_worker.pid, tmp_worker.n_tasks
		);
		dup_printf(flag_verbose, fp_output,
			"[Worker #%0*d, PID=%ld] Total de expresiones procesadas:%d\n",
			zeropad, i+1, (long)tmp_worker.pid, tmp_worker.n_results
		);
		close(tmp_worker.fd_w2b[0]);
		close(tmp_worker.fd_b2w[1]);
	}

	free(children);
	regfree(&re);
	fclose(fp_input);
	fclose(fp_output);
	return 0;
};