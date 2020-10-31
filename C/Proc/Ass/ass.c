#include "ass.h"

void Ass(char* path_in, char* path_out) {
	struct Text text = FillText(path_in);

	double* tags = (double*) calloc(N_TAGS, sizeof(tags[0]));

	text = DeleteTags(tags, &text);
	text.n_lines -= 1;

	double* buffer = (double*) calloc(2 * text.n_lines, sizeof(buffer[0]));
	size_t counter_elem = 0;	// counter n_cmd + n_value

	fclose(fopen("listing.txt", "w"));
	FILE* listing = fopen("listing.txt", "a");

	for (size_t i = 0; i < text.n_lines; i++) {
		char* cmd = strtok(text.pointers[i], " \t");

		double value = 0;
		int count = 0;
		char str_r[3] = "";
		int r_x = -1;

		char* str_value = strtok(NULL, " \t");
		if (str_value != NULL) {
			count = sscanf(str_value, "%lf", &value);
			if (!count){
				count = sscanf(str_value, "%s", str_r);

				if(count && str_r)
					r_x = str_r[0] - 'A';
					
				}
			}

		#define EMIT(val) 					\
			buffer[counter_elem] = val; 	\
			counter_elem++; 

		#define DEF_CMD(name, num, arg, code) 															\
				if (strcmp(cmd, #name) == 0){ 															\
					if (count){ 																		\
						if (r_x >= 0) { 																\
							EMIT(CMD_##name)															\
							EMIT(r_x) 																	\
							fprintf(listing, "%s %s -> %d %d\n", #name, str_r, CMD_##name, r_x);		\
						}																				\
						else { 																			\
							EMIT(CMD_##name)															\
							EMIT(value)																	\
							fprintf(listing, "%s %lf -> %d %lf\n", #name, value, CMD_##name, value);	\
						}																				\
					}																					\
					else { 																				\
						EMIT(CMD_##name)																\
						fprintf(listing, "%s -> %d\n", #name, CMD_##name);								\
					}																					\
				}																					
				// else 									\
				// 	printf("SYNTAX ERROR\n");

		#include "../Data/commands.h"

		#undef DEF_CMD
		#undef EMIT
	}

	FILE* f = fopen("test.bin", "wb");

	fwrite(tags, N_TAGS, sizeof(tags[0]), f);
	fwrite(buffer, counter_elem, sizeof(buffer[0]), f);

	fclose(f);

	free(text.pointers);
	free(text.original_text);
	free(tags);
	free(buffer);
}

struct Text DeleteTags(double* tags, struct Text* text) {
	fclose(fopen("ass_without.txt", "w"));
	FILE* code_without_tags = fopen("ass_without.txt", "a");
	size_t counter_elem = 0;

	for (size_t i = 0; i < text->n_lines; i++) {
		int n_tag = -1;

		char* pointer = strchr(text->pointers[i], ':');
		if (pointer != NULL) {
			int count = sscanf(text->pointers[i], "%d", &n_tag);

			if (count)
				tags[(int) n_tag] = counter_elem;
		}
		else
			fprintf(code_without_tags, "%s\n", text->pointers[i]);

		char* cmd = strtok(text->pointers[i], " \t");
		printf("%s\n", cmd);

		#define DEF_CMD(name, num, arg, code)			\
				if (!strcmp(cmd, #name))				\
					counter_elem += 1 + arg;
		#include "../Data/commands.h"
		#undef DEF_CMD

		printf("%ld\n", counter_elem);

	}

	fclose(code_without_tags);

	struct Text text_without_tags = FillText("ass_without.txt");

	return text_without_tags;
}