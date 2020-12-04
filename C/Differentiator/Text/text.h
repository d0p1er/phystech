#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#pragma once

struct Text{
	char* original_text;
	size_t n_symbols;
	size_t n_lines;
	char** pointers;
	size_t* lenght;
};

/*!
	\brief Данная функция возвращает текст из файла
	\param[in] PathToFile Путь к файлу с текстом
*/
struct Text FillText(char* path_file);
char* GetTextFromFile(char* path_file, size_t size_file);
size_t GetFileSize(char* path_file);
void FillStruct(struct Text* text);

/*!
	\brief Данная функция считает количество строк
	\param[in] text Текст
*/
size_t CountAmountLines(char* text);
// void WriteInFile(struct lines **lines_info, char* path_file, size_t n_lines);
// void WriteText(char* text, char* path_file, size_t n_lines);