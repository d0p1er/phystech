#include "disass.h"

void DisAss(char* path_in, char* path_out) {
	struct stat buff = {};
	stat("test.bin", &buff);

	size_t n_cmd = (buff.st_size - N_TAGS * sizeof(double)) / sizeof(double);

	double* tags = (double*) calloc(N_TAGS, sizeof(tags[0]));
	double* num_code = (double*) calloc(n_cmd, sizeof(num_code[0]));

	FILE* f = fopen("test.bin", "rb");
	
	fread(tags, sizeof(tags[0]), N_TAGS, f);
	fread(num_code, sizeof(num_code[0]), n_cmd, f);

	fclose(f);


	GetAssCode(tags, num_code, n_cmd);

	free(tags);
	free(num_code);
}

void GetAssCode(double* tags, double* num_code, size_t n_cmd) {
	char* str_code = (char*) calloc(n_cmd * sizeof(double) * 2, sizeof(str_code[0]));

	for (size_t i = 0; i < n_cmd; i++) {
		char tmp[50];
		for (size_t j = 0; j < N_TAGS; j++) {
			if ((int) tags[j] > 0 && (int) tags[j] == i) {
				sprintf(tmp, "%ld:\n", j);
				strcat(str_code, tmp);
				continue;
			}
		}

		#define DEF_CMD(name, num, arg, code) 								\
				if ((int) num_code[i] == num) { 							\
					if (arg != 0) {											\
						double value = num_code[++i]; 						\
						sprintf(tmp, "%s %lf\n", #name, value);				\
						strcat(str_code, tmp); 								\
						printf("%s\n", tmp);								\
						continue;											\
					}														\
					else {													\
						sprintf(tmp, "%s\n", #name);						\
						strcat(str_code, tmp); 								\
						printf("%s\n", tmp);								\
						continue;											\
					}														\
				}															
				// else 													\
				// 	printf("SYNTAX ERROR\n");

		#include "../Data/commands.h"

		#undef DEF_CMD

	}

	FILE* f = fopen("disass_out.txt", "w");

	fprintf(f, "%s\n", str_code);

	fclose(f);
}