#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Text/Text.h"
#include "../Stack/Stack.h"
#include "../Data/CMD_NAME.h"

#define RAX 0
#define RBX 1
#define RCX 2
#define RDX 3

extern const char* path_logs_cpu;
extern const int INIT_CPU;

#pragma once

struct Struct_CPU {
	size_t version;
	size_t n_cmd;
	char* byte_code;
	int* num_code;
	long long int* regs;
};

int CPU(char* path);
int* GetByteCode(char* text, size_t n_num);
int ByteDecode(char* str_code);