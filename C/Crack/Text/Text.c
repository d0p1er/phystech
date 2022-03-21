#include "Text.h"

struct Text FillText(char* path_file){
	struct Text text = {};

	text.n_symbols = GetFileSize(path_file);

	text.original_text = GetTextFromFile(path_file, text.n_symbols);

	text.n_lines = CountAmountLines(text.original_text);

	text.pointers = (char**) calloc(text.n_lines, sizeof(text.pointers[0]));
	text.lenght = (size_t*) calloc(text.n_lines, sizeof(text.lenght[0]));
	FillStruct(&text);

	return text;
}

char* GetTextFromFile(char* path_file, size_t size_file){
	FILE* file_with_text = fopen(path_file, "rb");
	
	if (file_with_text == NULL){
		printf("[Error] Unable to open file\n");
		exit(EXIT_FAILURE);
	}

	char* buffer = (char*) calloc(size_file, sizeof(char));
	
	if (buffer == NULL){
		printf("[Error] Unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	fread(buffer, sizeof(char), size_file, file_with_text);
	fclose (file_with_text);

	return buffer;
}

size_t GetFileSize(char* path_file){
	struct stat info_file = {};
	stat(path_file, &info_file);

	size_t size_file = info_file.st_size;
	
	if (size_file == 0){
		printf("[Error] Unable to get file size\n");
		exit(EXIT_FAILURE);
	}

	return size_file;
}


size_t CountAmountLines(char* text){
	char* symbols_runner = text;
	size_t counter = 1;	// Счетчик \n

	for (; *symbols_runner; symbols_runner++)
		if (*symbols_runner == '\n' && *(symbols_runner - 1) != '\n')
			counter++;

	return counter;
}


void FillStruct(struct Text* text){
	char* symbol_runner = text->original_text;

	size_t counter_symbols = 0;	// Счетчик символов в строке
	size_t counter_lines = 0;	// Счетчик строк

	for (; *symbol_runner; symbol_runner++){
		if (*symbol_runner != '\n' && *(symbol_runner - 1) == '\0')
			text->pointers[counter_lines] = symbol_runner;
		
		if (*symbol_runner == '\n'){
			if (*(symbol_runner - 1) != '\0'){
				text->lenght[counter_lines] = counter_symbols;
				counter_lines++;
			}

			*symbol_runner = '\0';
			counter_symbols = 0;
		}

		counter_symbols++;
	}

	text->lenght[counter_lines] = counter_symbols;	
}


void WriteText(char* text, char* path_file, size_t size_file){
	FILE* file_write = fopen(path_file, "wb");

	if (file_write == NULL){
		printf("[Error] Unable to open file\n");
		exit(EXIT_FAILURE);
	}

	fwrite(text, sizeof(text[0]), size_file, file_write);
}