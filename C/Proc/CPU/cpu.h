#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "../Stack/Stack.h"
#include "../DisAss/disass.h"
#include "../Data/CMD_NAME.h"

#define N_TAGS 20

extern const char* path_logs_cpu;
extern const int INIT_CPU;

struct Struct_CPU {
	double* RAM;
	size_t version;
	size_t n_cmd;
	struct Stack service_stack;
	double* tags;
	double* num_code;
	double* regs;
};

int CPU(char* path);