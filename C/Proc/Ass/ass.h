#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Text/Text.h"
#include "../Struct/Struct.h"
#include "../Data/CMD_NAME.h"

#define N_TAGS 10

enum Modes {
	simple_mode = 		0,
	reg_mode = 			1,
	RAM_mode = 			2,
	RAM_reg_mode = 		3,
	RAM_reg_num_mode = 	4
};

#pragma once

void Ass(char* path_in, char* path_out);
struct Text DeleteTags(double* tags, struct Text* text);