#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#pragma once

typedef double type;
#define OUTPUT_FORMAT "%lf"

struct Stack {
	type can_1;
	size_t size;
	size_t capacity;
	type* data;
	unsigned long long hash_sum;
	type can_2;
};

enum errors{
	NO_ERRORS = 0,
	INCORRECT_CAPASITY = 1,
	NULL_DATA = 2,
	NULL_POINTER = 3, 
	Stack_OVERFLOW = 4,
	Stack_EMPTY = 5,
	INDEX_OUT_OF_RANGE = 6,
	INVASION = 7,
	BAD_HASH = 8
};

extern const char* path_logs;
extern const type poison;

void StackConstruct(struct Stack* thou);
void StackPush(struct Stack* thou, type value);
void ResizeUp(struct Stack* thou);
type StackPop(struct Stack* thou);
void ResizeDown(struct Stack* thou);
void StackDestruct(struct Stack* thou);
void StackDelete(struct Stack* thou);
int StackError(struct Stack* thou);
unsigned long long CountHash(char* str, size_t i_start, size_t i_end);
unsigned long long RollHash(unsigned long long hash);

void Dump(struct Stack* thou, int error, const char* func, const int line);
void PrintErrorLogs(const char* error, const char* func, const int line, const int error_number);
void PrintStackLogs(struct Stack* thou);
char* TimeNow();