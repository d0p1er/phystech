#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../Data/CMD_NAME.h"

#define N_TAGS 10

void DisAss(char* path_in, char* path_out);
void GetAssCode(double* tags, double* num_code, size_t n_num);