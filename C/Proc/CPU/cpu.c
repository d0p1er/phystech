#include "cpu.h"

const char* path_logs_cpu = "logs_cpu.txt";
const int INIT_CPU = 1;

// RAM:
//		0 - 99 		system memory
//		100 - 199 	service stack
//		200 - 299	tags
//		300 - ...	read-write

int CPU(char* path){
	struct stat buff = {};
	stat("test.bin", &buff);

	struct Struct_CPU cpu = {};
	cpu.version = 1;

	cpu.n_cmd = (buff.st_size - N_TAGS * sizeof(cpu.tags[0])) / sizeof(cpu.num_code[0]);

	cpu.tags = (double*) calloc(N_TAGS, sizeof(cpu.tags[0]));
	cpu.num_code = (double*) calloc(cpu.n_cmd, sizeof(cpu.num_code[0]));
	cpu.regs = (double*) calloc(10, sizeof(cpu.regs[0]));
	
	StackConstruct(&(cpu.service_stack));
	
	FILE* f = fopen("test.bin", "rb");

	fread(cpu.tags, sizeof(cpu.tags[0]), N_TAGS, f);

	fread(cpu.num_code, sizeof(cpu.num_code[0]), cpu.n_cmd, f);

	struct Stack stk = {};
	StackConstruct(&stk);
	double value = 0;

	for (size_t rip = 0; rip < cpu.n_cmd; rip++) {
		// printf("%lf\n", cpu.num_code[rip]);
		value = cpu.num_code[rip + 1];

		switch ((int) cpu.num_code[rip]){
			#define DEF_CMD(name, num, arg, code) case num: if (arg != 0) rip++; code; break;

			#include "../Data/commands.h"
			#undef DEF_CMD

			default: return 0;
		}	
	}
}