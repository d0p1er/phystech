#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../Text/Text.h"
#include "../Struct/Struct.h"
#include "../Data/CMD_NAME.h"

#define N_TAGS 20

#pragma once

void Ass(char* path_in, char* path_out);
struct Text DeleteTags(double* tags, struct Text* text);