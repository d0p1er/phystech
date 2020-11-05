#include "ass.h"

// неогр колво меток
//Добавить возможность push [ax + 10]
void Ass(char* path_in, char* path_out) {
	struct Text text = FillText(path_in);

	double* tags = (double*) calloc(N_TAGS, sizeof(tags[0]));

	text = DeleteTags(tags, &text);
	text.n_lines -= 1;

	double* buffer = (double*) calloc(2 * text.n_lines, sizeof(buffer[0]));
	size_t counter_elem = 0;	// counter n_cmd + n_value

	// fclose(fopen("listing.txt", "w"));
	FILE* listing = fopen("listing.txt", "w");

	for (size_t i = 0; i < text.n_lines; i++) {
		char* cmd = strtok(text.pointers[i], " \t");

		int mode = simple_mode;
		double value = 0;
		int count = 0;
		char str_r[5] = "";

		//Сделать обработчик для проверки мода(isalpha, isnumber), а потом в зависимости от мода выполнять необходимые действия (switch)
		char* str_value = strtok(NULL, " \t");
		if (str_value != NULL) {
			count = sscanf(str_value, "%lf", &value);
			if (!count) {
				count = sscanf(str_value, "[%lf]", &value);
				//ENUM
				if (count) 
					mode = RAM_mode;
				else {
					char* pointer = strchr(str_value, '[');
					if (pointer != NULL) {
						count = sscanf(pointer, "[%s]", str_r);
						if (count && str_r) {
							value = str_r[0] - 'A';
							mode = RAM_reg_mode;
						}
					}
					else {
						count = sscanf(str_value, "%s", str_r);

						if(count && str_r) {
							value = str_r[0] - 'A';
							mode = reg_mode;
						}
					}	
				}
			}
		}

		printf("cmd : %s\n", cmd);
		printf("mode : %d\n", mode);
		printf("value : %lf\n", value);

		#define DEF_CMD(name, num, m, arg, code) 																\
				if (strcmp(cmd, #name) == 0) { 																	\
					if (count) { 																				\
						if (m != 0) {																			\
							buffer[counter_elem++] = CMD_##name;												\
							buffer[counter_elem++] = value;														\
							buffer[counter_elem++] = mode;	 													\
							fprintf(listing, "%s %lf -> %d %lf %d\n", #name, value, CMD_##name, value, mode);	\
						}																						\
						else { 																					\
							buffer[counter_elem++] = CMD_##name;												\
							buffer[counter_elem++] = value;														\
							fprintf(listing, "%s %lf -> %d %lf\n", #name, value, CMD_##name, value);			\
						}																						\
					}																							\
					else { 																						\
						buffer[counter_elem++] = CMD_##name;													\
						fprintf(listing, "%s -> %d\n", #name, CMD_##name);										\
					}																							\
				}																								
				// else 									\
				// 	printf("SYNTAX ERROR\n");

		#include "../Data/commands.h"

		#undef DEF_CMD
		#undef EMIT
	}
	fclose(listing);

	// for (size_t i = 0; i < counter_elem; i++){
	// 	printf("%lf\n", buffer[i]);
	// }
	//for (size_t i = 0; i < N_TAGS; i++){
	//	printf("%lf\n", tags[i]);
	//}

	FILE* ff = fopen("test.bin", "wb");

	fwrite(tags, N_TAGS, sizeof(tags[0]), ff);
	fwrite(buffer, counter_elem, sizeof(buffer[0]), ff);

	fclose(ff);

	free(text.pointers);
	free(text.original_text);
	free(tags);
	free(buffer);
}


struct Text DeleteTags(double* tags, struct Text* text) {
	// fclose(fopen("ass_without.txt", "w"));
	FILE* code_without_tags = fopen("ass_without.txt", "w");
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

		#define DEF_CMD(name, num, m, arg, code)		\
				if (!strcmp(cmd, #name))				\
					counter_elem += 1 + arg + m;
		#include "../Data/commands.h"
		#undef DEF_CMD

		printf("%ld\n", counter_elem);
		// записывать в сужебную часть
	}

	fclose(code_without_tags);

	struct Text text_without_tags = FillText("ass_without.txt");

	return text_without_tags;
}