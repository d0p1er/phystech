#include <stdio.h>
#include <stdlib.h>

#pragma once
#define UpdateFree 									\
					list->next[pos] = list->free;	\
					list->prev[pos] = 0;			\
					list->prev[list->free] = pos;	\
					list->free = pos;

extern const int poison;

// struct Node {
// 	int value;
// 	int next;
// 	int prev;
// };

struct List {
	size_t size;
	size_t capacity;
	int head;
	int tail;
	int free;
	int* values;
	int* next;
	int* prev;
};


enum ERRORS {
	EVERYTHING_OKAY = 0,
	NEXT_PREV_ERROR = 1,
	NEXT_ERROR = 2,
	PREV_ERROR = 3
};

struct List ListConstruct();
void AddValue(int pos, int value, struct List* list);
int Delete(int pos, struct List* list);
int Verification(struct List* list);
void DrawGraph(struct List* list);
void PrintAll(struct List* list);