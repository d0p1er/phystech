#include "cpu.h"

const char* path_logs_cpu = "logs_cpu.txt";
const double delta = 0.5;
const char COLORS[10][10] = {"\x1B[1m",	// bold
							 "\x1B[30m",	// black
							 "\x1B[31m",	// red
							 "\x1B[32m",	// green
							 "\x1B[33m",	// yellow
							 "\x1B[34m",	// blue
							 "\x1B[35m",	// magenta
							 "\x1B[36m",	// cyan
							 "\x1B[37m"};	// white

int CPU(char* path){
	struct stat buff = {};
	stat("test.bin", &buff);

	struct Struct_CPU cpu = {};
	cpu.version = 1;
	cpu.color = 8;

	cpu.n_cmd = (buff.st_size - N_TAGS * sizeof(cpu.tags[0])) / sizeof(cpu.num_code[0]);


	cpu.RAM = (double*) calloc(20000, sizeof(cpu.RAM[0]));
	cpu.tags = (double*) calloc(N_TAGS, sizeof(cpu.tags[0]));
	cpu.num_code = (double*) calloc(cpu.n_cmd, sizeof(cpu.num_code[0]));
	cpu.regs = (double*) calloc(10, sizeof(cpu.regs[0]));
	
	StackConstruct(&(cpu.service_stack));
	
	FILE* f = fopen("test.bin", "rb");

	fread(cpu.tags, sizeof(cpu.tags[0]), N_TAGS, f);

	fread(cpu.num_code, sizeof(cpu.num_code[0]), cpu.n_cmd, f);

	struct Stack stk = {};
	StackConstruct(&stk);

	// printf("%ld\n", cpu.n_cmd);

	for (size_t rip = 0; rip < cpu.n_cmd; rip++) {
		double value = cpu.num_code[rip + 1];
		double mode = cpu.num_code[rip + 2];

		// printf("cmd %lf\n", cpu.num_code[rip]);
		// printf("value %lf\n", value);
		// printf("mode %d\n", (int) mode);

		switch ((int) cpu.num_code[rip]){
			#define DEF_CMD(name, num, m, arg, code) case num: if (arg != 0) rip++; code; break;

			#include "../Data/commands.h"
			#undef DEF_CMD

			default: printf("unknown\n");;
		}	
	}
}

int AreNumbersEqual(double num_1, double num_2) {
	if(fabs(num_1 - num_2) <= delta)
		return 1;

	return 0;
}