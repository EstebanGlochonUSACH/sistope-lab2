#ifndef _H_BROKER_FUNCIONES
#define _H_BROKER_FUNCIONES

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	pid_t pid;
	int n_tasks;
	int n_results;
	int fd_b2w[2];
	int fd_w2b[2];
} worker_t;

void free_workers(worker_t **workers, size_t total);

void dup_printf(bool flag_verbose, FILE *f, char const *fmt, ...);

bool str_endswith(const char *str, const char *suffix);

char *strtrim(char *s);

#endif