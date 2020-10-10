#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#pragma once

struct stack{
	double can_1;
	double poison;
	int size;
	int capacity;
	double* data;
	size_t hash;
	double can_2;
};

enum errors{
	NO_ERRORS = 0,
	INCORRECT_CAPASITY = 1,
	NULL_DATA = 2,
	NULL_POINTER = 3, 
	STACK_OVERFLOW = 4,
	STACK_EMPTY = 5,
	INDEX_OUT_OF_RANGE = 6,
	INVASION = 7,
	BAD_HASH = 8
};

extern const char* path_logs;

void StackConstruct(struct stack* thou, int capacity);
void StackPush(struct stack* thou, double value);
double StackPop(struct stack* thou);
void StackDestruct(struct stack* thou);
void StackDelete(struct stack* thou);
int StackError(struct stack* thou);
size_t CountHashStack(struct stack* thou);
size_t CountHashData(struct stack* thou);
size_t RollHash(int hash);

void Dump(struct stack* thou, int error, const char* func, int line);
void PrintErrorLogs(char* error, const char* func, int line, int error_number);
void PrintStackLogs(struct stack* thou);
char* TimeNow();