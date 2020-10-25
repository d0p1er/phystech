#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Text/Text.h"
#include "../Struct/Struct.h"
#include "../Data/CMD_NAME.h"

#pragma once

void DisAss(char* path_in, char* path_out);
int* GetByteCode(struct Text* text, size_t n_num);
int ByteDecode(char* str_code);