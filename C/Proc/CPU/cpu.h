#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "../Stack/Stack.h"
#include "../DisAss/disass.h"
#include "../Data/CMD_NAME.h"

#define N_TAGS 10

extern const char* path_logs_cpu;
extern const double delta;
extern const char COLORS[10][10];

struct Struct_CPU {
	int color;
	size_t counter_RAM;
	double* RAM;
	size_t version;
	size_t n_cmd;
	struct Stack service_stack;
	double* tags;
	double* num_code;
	double* regs;
};

int CPU(char* path);
int AreNumbersEqual(double num_1, double num_2);