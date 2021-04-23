#pragma once

#include <cstring>
#include <nmmintrin.h>
#include <xmmintrin.h>
#include <immintrin.h>

unsigned int Hash0(char* str);
unsigned int Hash1(char* str);
unsigned int Hash2(char* str);
unsigned int Hash3(char* str);
unsigned int Hash4(char* str);
unsigned int RollHash(unsigned int hash_sum);
unsigned int Hash5(char* str);