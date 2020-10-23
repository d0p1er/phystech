#include "disass.h"

const double poison = NAN;


void DisAss(char* path){
	struct Text text = FillText(path);
	printf("%ld\n", text.n_lines);

	FILE* output = fopen("disass_out.txt", "a");

	for(size_t i = 0; i < text.n_lines; i++){
		int cmd = 0;
		sscanf(strtok(text.pointers[i], " \t"), "%d", &cmd);

		int value = 0;
		int count = 0;

		char* str_value = strtok(NULL, " \t");
		if (str_value)
			count = sscanf(str_value, "%d", &value);

		// printf("%d %d\n", cmd, value);
		#define DEF_CMD(name, num, arg, code) \
				printf("%d %d\n", cmd, num); \
				if(cmd == num){ \
					if(isnan(value))\
						fprintf(output, "%s\n", #name); \
					else \
						fprintf(output, "%s %d\n", #name, value);} \
				else \
					printf("SYNTAX ERROR\n");

		#include "../Data/commands.h"

		#undef DEF_CMD

		printf("%ld\n", i);
	}

	fclose(output);
	printf("1\n");
	free(text.pointers);
	free(text.original_text);
	printf("11\n");

}