#include "../Tree/tree.h"
#include "../Text/text.h"
#include <math.h>
#include <ctype.h>
#include "../Data/DSL.h"

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
	OPERATION = 3,
	FUNCTION = 4
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

// РБНФ
// G ::= E$
// E ::= T{[+-]T}*
// T ::= D{[*/]D}*
// P ::= (E) | N | F | V
// N ::= ['0'-'9']+
// D ::= F{[^]F}*
// V ::= a - z
// F ::= {[a - z, A - Z]P}*

extern char* str_expr;

struct NodeTree* GetG(char* str);
struct NodeTree* GetN();
struct NodeTree* GetE();
struct NodeTree* GetT();
struct NodeTree* GetP();
struct NodeTree* GetD();
struct NodeTree* GetV();
struct NodeTree* GetF();

void Require(char symb);
void SyntaxError();

struct NodeTree* ReadMathExpression(char* path);
char* ReadExpr(struct NodeTree* node, char* text);
char* WriteNodeTreeData(struct NodeTree* node, char* text, char end);
int IsOper(char c);
int IsFunc(char c);
double Eval(struct NodeTree* node);
char* WithoutSpaces(char* str, size_t lenght);
void PrintExpr(struct NodeTree* node);
void PrintFunc(int num_func);

struct NodeTree* Differentation(struct NodeTree* node, struct Tree* tree, FILE* file);
struct NodeTree* DifferentationLatex(struct NodeTree* node, struct Tree* tree, FILE* file) ;
struct NodeTree* CreateNode(int type_data, TYPE_TREE data, struct NodeTree* node_left, struct NodeTree* node_right);
struct NodeTree* CopyNode(struct NodeTree* node);
struct NodeTree* Simplify(struct NodeTree* node, int* simp);
int SizeTree(struct NodeTree* node, int size);

void PrintLatexStart(struct NodeTree* node, struct Tree* tree, FILE* file);
void PrintLatexEnd(struct NodeTree* node_old, struct NodeTree* node, struct Tree* tree, FILE* file);
void PrintNodeLatex(struct NodeTree* node, struct Tree* tree, FILE* file);
struct NodeTree* PrintEqual(struct NodeTree* node_1, struct NodeTree* node_2, struct Tree* tree, FILE* file);
void PrintRandomLatex(FILE* file);