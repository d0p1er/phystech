#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma once

// #define DEBUG

#ifndef DEBUG
	#define DBG if (0)
#else
	#define DBG
#endif

typedef int TYPE_LIST;
#define OUTPUT_FORMAT_LIST "%d"

extern const TYPE_LIST poison;

struct NodeList {
	TYPE_LIST value;
	int next;
	int prev;
};

struct List {
	size_t size;
	size_t capacity;
	int head;
	int tail;
	int free;
	struct NodeList* nodes;
};


enum ERRORS {
	EVERYTHING_OKAY = 0,
	NEXT_PREV_ERROR = 1,
	NEXT_ERROR = 2,
	PREV_ERROR = 3,
	WRONG_SIZE = 4
};

void ListConstruct(struct List* list);
void ListDestruct(struct List* list);

int AddValueBefore(TYPE_LIST value, struct List* list);
int AddValueAfter(TYPE_LIST value, struct List* list);
int AddZeroSize(TYPE_LIST value, struct List* list);
TYPE_LIST Delete(int pos, struct List* list);
void UpdateFree(int pos, struct List* list);
void ResizeUp(struct List* list);
int FindElem(int pos, struct List* list);
int FindElemByValue(TYPE_LIST value, struct List* list);
TYPE_LIST GetValue(int pos, struct List* list);
void Sort(struct List* list);
void Swap(int pos, struct List* list);

int Verification(struct List* list);
void DumpList(struct List* list, const char* func, const int line);
void PrintErrorLogs(const char* error, const char* func, const int line, const int error_number);
char* TimeNow();
void DrawGraphList(struct List* list);
void PrintAllList(struct List* list);