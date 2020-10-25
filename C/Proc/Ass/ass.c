#include "ass.h"

void Ass(char* path_in, char* path_out){
	struct Text text = FillText(path_in);
	printf("%ld\n", text.n_lines);

	FILE* output = fopen(path_out, "a");

	for (size_t i = 0; i < text.n_lines; i++){
		char* cmd = strtok(text.pointers[i], " \t");

		int value = 0;
		int count = 0;
		char str_r[3] = "";
		int r_x = -1;

		char* str_value = strtok(NULL, " \t");
		if (str_value) {
			count = sscanf(str_value, "%d", &value);
			if (!count){
				count = sscanf(str_value, "%s", str_r);
				if(str_r)
					r_x = str_r[0] - 'A';
			}
		}

		#define DEF_CMD(name, num, arg, code) \
				if (strcmp(cmd, #name) == 0){ \
					if (!count){ \
						if(r_x >= 0) { \
							char name_byte[33] = ""; \
							ByteCode(CMD_##name, name_byte); \
							char value_byte[33] = ""; \
							ByteCode(r_x, value_byte); \
							fprintf(output, "%s%s", name_byte, value_byte);} \
						else { \
							char name_byte[33] = ""; \
							ByteCode(CMD_##name, name_byte); \
							fprintf(output, "%s", name_byte);}} \
					else{ \
						char name_byte[33] = ""; \
						ByteCode(CMD_##name, name_byte); \
						char value_byte[33] = ""; \
						ByteCode(value, value_byte); \
						fprintf(output, "%s%s", name_byte, value_byte);}} \
				else \
					printf("SYNTAX ERROR\n");

		#include "../Data/commands.h"

		#undef DEF_CMD

		printf("%ld\n", i);
	}

	fclose(output);
	free(text.pointers);
	free(text.original_text);
	printf("11\n");
}

void ByteCode(int a, char* buffer){	
	for (int i = 0; i < 32; i++)
		*(buffer + 31 - i) = (a & (1 << (31 - i))) == 0 ? '0' : '1';
	
	printf("%s\n", buffer);
}