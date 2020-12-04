#include "../Tree/tree.h"
#include "../Text/text.h"
#include <math.h>
#include <ctype.h>

#pragma once

#define DEBUG

#ifndef DEBUG
	#define DBG if (0)
#else
	#define DBG
#endif

enum Types {
	NUMBER = 1,
	VARIABLE = 2,
	OPERATION = 3
};

enum Operations {
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
	POW = '^'
};

struct Variable {
	char name;
	double value;
};

void ReadMathExpression(struct NodeTree* node, char* path);
char* ReadExpr(struct NodeTree* node, char* text);
char* WriteNodeTreeData(struct NodeTree* node, char* text, char end);
int IsOper(char c);
double Eval(struct NodeTree* node);
char* WithoutSpaces(char* str, size_t lenght);
void PrintExpr(struct NodeTree* node);