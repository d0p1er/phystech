#include <stdio.h>

#pragma once

struct Text{
	char* original_text;
	size_t n_symbols;
	size_t n_lines;
	char** pointers;
	size_t* lenght;
};