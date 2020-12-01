#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../Text/text.h"

#pragma once

typedef char* TYPE_TREE;
#define OUTPUT_FORMAT_TREE "%s"

struct NodeTree {
	TYPE_TREE data;
	struct NodeTree* parent;
	struct NodeTree* left;
	struct NodeTree* right;
};

struct Tree {
	struct NodeTree* root;
	size_t size;
};

struct NodeTree* TreeConstruct(struct Tree* tree, TYPE_TREE value_root);
struct NodeTree* AddLeft(struct Tree* tree, TYPE_TREE value, struct NodeTree* node);
struct NodeTree* AddRight(struct Tree* tree, TYPE_TREE value, struct NodeTree* node);
void Emit(struct NodeTree* node, TYPE_TREE value, struct NodeTree* parent);
void DeleteNode(struct NodeTree* node);

void Preorder(struct NodeTree* node);
void WriteDataBase(FILE* file, struct NodeTree* node, size_t space_count);
void PrintSpaces(FILE* file, size_t space_count);
void GraphDump(struct NodeTree* node);
void GraphDumpTree(struct NodeTree* node, FILE* graph_file);

struct Tree ReadTree(char* path);
char* ReadNode(struct NodeTree* node, char* text);
char* WithoutSpaces(char* str, size_t lenght);