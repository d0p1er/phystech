#include "disass.h"

// добавить PUSH_R

void DisAss(char* path_in, char* path_out){
	struct Text text = FillText(path_in);
	size_t n_num = text.n_symbols / 32;

	int* num_code = GetByteCode(&text, n_num);

	FILE* output = fopen("disass_out.txt", "a");

	int value = 0;

	for (size_t i = 0; i < n_num; i++){
		#define DEF_CMD(name, num, arg, code) \
				if (num_code[i] == num) { \
					if (arg == 0) \
						fprintf(output, "%s\n", #name); \
					else { \
						value = num_code[++i]; \
						fprintf(output, "%s %d\n", #name, value);}} \
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

int* GetByteCode(struct Text* text, size_t n_num){
	int* num_code = (int*) calloc(n_num, sizeof(num_code[0]));

	char* symbols_runner = text->original_text;
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