#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../Text/Text.h"

#pragma once

typedef char* DATA_TYPE;
#define DATA_TYPE_PRT "%s"

struct Node {
	DATA_TYPE data;
	struct Node* parent;
	struct Node* left;
	struct Node* right;
};

struct Tree {
	struct Node* root;
	size_t size;
};

struct Node* TreeConstruct(struct Tree* tree, DATA_TYPE value_root);
struct Node* AddLeft(struct Tree* tree, DATA_TYPE value, struct Node* node);
struct Node* AddRight(struct Tree* tree, DATA_TYPE value, struct Node* node);
void Emit(struct Node* node, DATA_TYPE value, struct Node* parent);
void DeleteNode(struct Node* node);

void Preorder(struct Node* node);
void WriteDataBase(FILE* file, struct Node* node, size_t space_count);
void PrintSpaces(FILE* file, size_t space_count);
void GraphDump(struct Node* node);
void GraphDumpTree(struct Node* node, FILE* graph_file);

struct Tree ReadTree(char* path);
char* ReadNode(struct Node* node, char* text);
char* WithoutSpaces(char* str, size_t lenght);