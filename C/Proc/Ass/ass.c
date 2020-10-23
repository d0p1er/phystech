#include "ass.h"

const double poison = NAN;


void Ass(char* path){
	struct Text text = FillText(path);
	printf("%ld\n", text.n_lines);

	FILE* output = fopen("ass_out.txt", "a");

	fprintf(output, "v0.1.2 n%ld\n", text.n_lines);

	for (size_t i = 0; i < text.n_lines; i++){
		char* cmd = strtok(text.pointers[i], " \t");

		int value = 0;
		int count = 0;

		char* str_value = strtok(NULL, " \t");
		if (str_value)
			count = sscanf(str_value, "%d", &value);

		#define DEF_CMD(name, num, arg, code) \
				if (strcmp(cmd, #name) == 0){ \
					if (!count) \
						fprintf(output, "%d\n", CMD_##name); \
					else \
						fprintf(output, "%d %d\n", CMD_##name, value);} \
				else \
					printf("SYNTAX ERROR\n");

		#include "../Data/commands.h"

		#undef DEF_CMD

		printf("%ld\n", i);
	}

	fclose(output);
	free(text.pointers);
	free(text.original_text);
}