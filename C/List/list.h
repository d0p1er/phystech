#include <stdio.h>
#include <stdlib.h>

#pragma once

extern const int poison;

struct List {
	size_t size;
	size_t capacity;
	int pos;
	int* values;
	int* next;
	int* prev;
	int free;
};


struct List ListConstruct();
void AddValue(int pos, int value, struct List* list);
void PrintAll(struct List* list);