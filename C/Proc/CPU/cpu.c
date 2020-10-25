#include "cpu.h"

const char* path_logs_cpu = "logs_cpu.txt";
const int INIT_CPU = 1;

// добавить PUSH_R

int CPU(char* path){
	struct Text text = FillText(path);

	struct Struct_CPU cpu = {};
	cpu.version = 1;
	cpu.n_cmd = text.n_symbols / 32;
	cpu.byte_code = text.original_text;
	cpu.num_code = GetByteCode(cpu.byte_code, cpu.n_cmd);
	cpu.regs = (long long int*) calloc(4, sizeof(cpu.regs[0]));

	// PrintLogs(INIT_CPU);

	struct Stack stk = {};
	StackConstruct(&stk);

	for (size_t i = 0; i < cpu.n_cmd; i++){
		switch (cpu.num_code[i]){
			#define DEF_CMD(name, num, arg, code) case num: if (arg != 0) i++; code; break;

			#include "../Data/commands.h"
			#undef DEF_CMD

			default: return 0;
		}	

		printf("%ld\n", i);
	}
}

int* GetByteCode(char* text, size_t n_num){
	int* num_code = (int*) calloc(n_num, sizeof(num_code[0]));

	char* symbols_runner = text;
	char tmp[33] = "";
	size_t symbols_counter = 0;
	size_t n_num_code = 0;

	for (; *symbols_runner; symbols_runner++){
		tmp[symbols_counter] = *symbols_runner;
		symbols_counter++;

		if (symbols_counter >= 32){
			num_code[n_num_code] = ByteDecode(tmp);
			printf("%d\n", num_code[n_num_code]);
			n_num_code++;
			symbols_counter = 0;
		}
	}

	return num_code;
}

int ByteDecode(char* str_code){
	int result = 0;
	for (int i = 0; i < 32; i++)
		result += str_code[i] == '1' ? pow(2, i) : 0;

	return result;
}

// void PrintLogs(){
// 	FILE* logs_file = fopen(path_logs, "a");

// 	char* timeNow = TimeNow();

// 	fprintf(logs_file, "\n##########################################################################################\n");
// 	fprintf(logs_file, "[%s] \n", timeNow, );

// 	fclose(logs_file);
// }

// char* TimeNow(){
// 	char* s = (char*) calloc(20, sizeof(s[0]));

// 	time_t t = time(NULL);
// 	struct tm* tt = localtime(&t);

// 	strftime(s, 20, "%d.%m.%Y %H:%M:%S ", tt);

// 	return s;
// }